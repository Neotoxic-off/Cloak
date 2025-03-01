#include "pch.h"
#include "dump/dump.h"

Dump::Dump()
{
    this->g_GameAssembly = NULL;
    this->g_IL2CPPFunctions = {};
    this->g_OutputPath = ".";
}

Dump::~Dump()
{
}

template<typename T>
T GetIL2CPPFunction(const char* functionName) {
    return reinterpret_cast<T>(GetProcAddress(g_GameAssembly, functionName));
}

// Initialize the IL2CPP API function pointers
bool Dump::InitializeIL2CPPFunctions()
{
    g_GameAssembly = GetModuleHandleA("GameAssembly.dll");
    if (!g_GameAssembly) {
        MessageBoxA(NULL, "Failed to get GameAssembly.dll module handle", "Error", MB_ICONERROR);
        return false;
    }

    // Load essential functions
    g_IL2CPPFunctions.domain_get = GetIL2CPPFunction<il2cpp_domain_get_t>("il2cpp_domain_get");
    g_IL2CPPFunctions.domain_get_assemblies = GetIL2CPPFunction<il2cpp_domain_get_assemblies_t>("il2cpp_domain_get_assemblies");
    g_IL2CPPFunctions.assembly_get_image = GetIL2CPPFunction<il2cpp_assembly_get_image_t>("il2cpp_assembly_get_image");
    g_IL2CPPFunctions.image_get_name = GetIL2CPPFunction<il2cpp_image_get_name_t>("il2cpp_image_get_name");

    // Load class enumeration functions
    g_IL2CPPFunctions.image_get_class_count = GetIL2CPPFunction<il2cpp_image_get_class_count_t>("il2cpp_image_get_class_count");
    g_IL2CPPFunctions.image_get_class = GetIL2CPPFunction<il2cpp_image_get_class_t>("il2cpp_image_get_class");
    g_IL2CPPFunctions.class_get_name = GetIL2CPPFunction<il2cpp_class_get_name_t>("il2cpp_class_get_name");
    g_IL2CPPFunctions.class_get_namespace = GetIL2CPPFunction<il2cpp_class_get_namespace_t>("il2cpp_class_get_namespace");
    g_IL2CPPFunctions.class_get_parent = GetIL2CPPFunction<il2cpp_class_get_parent_t>("il2cpp_class_get_parent");

    // Load method functions
    g_IL2CPPFunctions.class_get_methods = GetIL2CPPFunction<il2cpp_class_get_methods_t>("il2cpp_class_get_methods");
    g_IL2CPPFunctions.method_get_name = GetIL2CPPFunction<il2cpp_method_get_name_t>("il2cpp_method_get_name");
    g_IL2CPPFunctions.method_get_return_type = GetIL2CPPFunction<il2cpp_method_get_return_type_t>("il2cpp_method_get_return_type");
    g_IL2CPPFunctions.method_get_param_count = GetIL2CPPFunction<il2cpp_method_get_param_count_t>("il2cpp_method_get_param_count");
    g_IL2CPPFunctions.method_get_param = GetIL2CPPFunction<il2cpp_method_get_param_t>("il2cpp_method_get_param");

    // Load field functions
    g_IL2CPPFunctions.class_get_fields = GetIL2CPPFunction<il2cpp_class_get_fields_t>("il2cpp_class_get_fields");
    g_IL2CPPFunctions.field_get_name = GetIL2CPPFunction<il2cpp_field_get_name_t>("il2cpp_field_get_name");
    g_IL2CPPFunctions.field_get_offset = GetIL2CPPFunction<il2cpp_field_get_offset_t>("il2cpp_field_get_offset");
    g_IL2CPPFunctions.field_get_type = GetIL2CPPFunction<il2cpp_field_get_type_t>("il2cpp_field_get_type");

    // Load type functions
    g_IL2CPPFunctions.type_get_name = GetIL2CPPFunction<il2cpp_type_get_name_t>("il2cpp_type_get_name");
    g_IL2CPPFunctions.type_get_object = GetIL2CPPFunction<il2cpp_type_get_object_t>("il2cpp_type_get_object");

    // Check if essential functions were found
    if (!g_IL2CPPFunctions.domain_get || !g_IL2CPPFunctions.domain_get_assemblies ||
        !g_IL2CPPFunctions.assembly_get_image || !g_IL2CPPFunctions.image_get_name) {
        MessageBoxA(NULL, "Failed to load essential IL2CPP functions", "Error", MB_ICONERROR);
        return false;
    }

    return true;
}

// Get parent class name
std::string Dump::GetParentClassName(void* klass) {
    if (!klass || !this->g_IL2CPPFunctions.class_get_parent) return "None";

    void* parentClass = g_IL2CPPFunctions.class_get_parent(klass);
    if (!parentClass) return "None";

    const char* parentName = g_IL2CPPFunctions.class_get_name(parentClass);
    if (!parentName) return "Unknown";

    const char* parentNamespace = g_IL2CPPFunctions.class_get_namespace(parentClass);
    if (!parentNamespace || parentNamespace[0] == '\0') {
        return std::string(parentName);
    }
    else {
        return std::string(parentNamespace) + "." + std::string(parentName);
    }
}

std::string Dump::GetTypeName(void* type)
{
    if (!type || !this->g_IL2CPPFunctions.type_get_name) return "Unknown";

    const char* typeName = (const char*)this->g_IL2CPPFunctions.type_get_name(type);
    if (!typeName) return "Unknown";

    return std::string(typeName);
}

void Dump::ExtractMethods(void* klass, ClassInfo& classInfo)
{
    if (!klass || !this->g_IL2CPPFunctions.class_get_methods) return;

    void* iter = NULL;
    void* method = NULL;

    while ((method = g_IL2CPPFunctions.class_get_methods(klass, &iter)) != NULL) {
        const char* methodName = g_IL2CPPFunctions.method_get_name(method);
        if (!methodName) continue;

        MethodInfo methodInfo;
        methodInfo.methodName = methodName;
        methodInfo.methodPtr = method;

        if (g_IL2CPPFunctions.method_get_param_count) {
            methodInfo.paramCount = (int)(size_t)g_IL2CPPFunctions.method_get_param_count(method);
        }
        else {
            methodInfo.paramCount = -1;
        }

        if (g_IL2CPPFunctions.method_get_return_type && g_IL2CPPFunctions.type_get_name) {
            void* returnType = g_IL2CPPFunctions.method_get_return_type(method);
            methodInfo.returnType = GetTypeName(returnType);
        }
        else {
            methodInfo.returnType = "Unknown";
        }

        classInfo.methods.push_back(methodInfo);
    }
}

void Dump::ExtractFields(void* klass, ClassInfo& classInfo)
{
    if (!klass || !g_IL2CPPFunctions.class_get_fields) return;

    void* iter = NULL;
    void* field = NULL;

    while ((field = g_IL2CPPFunctions.class_get_fields(klass, &iter)) != NULL) {
        const char* fieldName = g_IL2CPPFunctions.field_get_name(field);
        if (!fieldName) continue;

        FieldInfo fieldInfo;
        fieldInfo.fieldName = fieldName;

        // Get field offset
        if (g_IL2CPPFunctions.field_get_offset) {
            fieldInfo.offset = g_IL2CPPFunctions.field_get_offset(field);
        }
        else {
            fieldInfo.offset = 0;
        }

        // Get field type
        if (g_IL2CPPFunctions.field_get_type && g_IL2CPPFunctions.type_get_name) {
            void* fieldType = g_IL2CPPFunctions.field_get_type(field);
            fieldInfo.fieldType = GetTypeName(fieldType);
        }
        else {
            fieldInfo.fieldType = "Unknown";
        }

        classInfo.fields.push_back(fieldInfo);
    }
}

// Extract information from Assembly-CSharp.dll
bool ExtractAssemblyCSharp() {
    void* domain = g_IL2CPPFunctions.domain_get();
    if (!domain) {
        Log("Failed to get IL2CPP domain\n");
        return false;
    }

    size_t assemblyCount = 0;
    void** assemblies = g_IL2CPPFunctions.domain_get_assemblies(domain, &assemblyCount);

    if (!assemblies || assemblyCount == 0) {
        Log("Failed to get assemblies or no assemblies found\n");
        return false;
    }

    Log("Found %zu assemblies\n", assemblyCount);

    // Find Assembly-CSharp
    void* assemblyCSharpImage = NULL;

    for (size_t i = 0; i < assemblyCount; i++) {
        void* image = g_IL2CPPFunctions.assembly_get_image(assemblies[i]);
        if (!image) continue;

        const char* imageName = g_IL2CPPFunctions.image_get_name(image);
        if (!imageName) continue;

        Log("Assembly %zu: %s\n", i, imageName);

        if (strstr(imageName, "Assembly-CSharp") != NULL) {
            assemblyCSharpImage = image;
            Log("Found Assembly-CSharp at index %zu\n", i);
            break;
        }
    }

    if (!assemblyCSharpImage) {
        Log("Assembly-CSharp not found\n");
        return false;
    }

    // Extract classes from Assembly-CSharp
    if (!g_IL2CPPFunctions.image_get_class_count || !g_IL2CPPFunctions.image_get_class) {
        Log("Class enumeration functions not available\n");
        return false;
    }

    size_t classCount = (size_t)g_IL2CPPFunctions.image_get_class_count(assemblyCSharpImage);
    Log("Found %zu classes in Assembly-CSharp\n", classCount);

    for (size_t i = 0; i < classCount; i++) {
        void* klass = g_IL2CPPFunctions.image_get_class(assemblyCSharpImage, i);
        if (!klass) continue;

        const char* className = g_IL2CPPFunctions.class_get_name(klass);
        const char* namespaceName = g_IL2CPPFunctions.class_get_namespace(klass);

        if (!className) continue;

        ClassInfo classInfo;
        classInfo.className = className;
        classInfo.namespaceName = namespaceName ? namespaceName : "";

        if (namespaceName && namespaceName[0] != '\0') {
            classInfo.fullName = std::string(namespaceName) + "." + std::string(className);
        }
        else {
            classInfo.fullName = std::string(className);
        }

        // Get parent class
        classInfo.parentClass = GetParentClassName(klass);

        Log("Processing class %zu/%zu: %s\n", i + 1, classCount, classInfo.fullName.c_str());

        // Extract fields and methods
        ExtractFields(klass, classInfo);
        ExtractMethods(klass, classInfo);

        g_Classes.push_back(classInfo);
    }

    Log("Extracted %zu classes from Assembly-CSharp\n", g_Classes.size());
    return true;
}

// Create directory if it doesn't exist
bool CreateDirectoryIfNotExists(const std::string& path) {
    if (CreateDirectoryA(path.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        return true;
    }
    return false;
}

// Save the extracted information to files
void SaveExtractedData() {
    // Create output directory
    if (!CreateDirectoryIfNotExists(g_OutputPath)) {
        Log("Failed to create output directory: %s\n", g_OutputPath.c_str());
        return;
    }

    // Save offsets file
    std::string offsetsPath = g_OutputPath + "\\Offsets.h";
    std::ofstream offsetsFile(offsetsPath);

    if (!offsetsFile.is_open()) {
        Log("Failed to open offsets file: %s\n", offsetsPath.c_str());
        return;
    }

    offsetsFile << "// Assembly-CSharp Offsets - Generated " << __DATE__ << " " << __TIME__ << std::endl;
    offsetsFile << "// Total Classes: " << g_Classes.size() << std::endl << std::endl;

    offsetsFile << "#pragma once" << std::endl << std::endl;
    offsetsFile << "namespace Offsets {" << std::endl;

    for (const auto& classInfo : g_Classes) {
        if (classInfo.fields.empty()) continue;

        // Create a namespace for each class
        std::string classNameClean = classInfo.className;
        // Replace invalid characters for C++ identifiers
        std::replace(classNameClean.begin(), classNameClean.end(), '<', '_');
        std::replace(classNameClean.begin(), classNameClean.end(), '>', '_');
        std::replace(classNameClean.begin(), classNameClean.end(), '.', '_');

        offsetsFile << "    namespace " << classNameClean << " {" << std::endl;

        for (const auto& field : classInfo.fields) {
            offsetsFile << "        constexpr auto " << field.fieldName << " = 0x"
                << std::hex << std::uppercase << field.offset << "; // "
                << field.fieldType << std::dec << std::endl;
        }

        offsetsFile << "    }" << std::endl << std::endl;
    }

    offsetsFile << "}" << std::endl;
    offsetsFile.close();

    // Save class details file
    std::string classesPath = g_OutputPath + "\\Classes.txt";
    std::ofstream classesFile(classesPath);

    if (!classesFile.is_open()) {
        Log("Failed to open classes file: %s\n", classesPath.c_str());
        return;
    }

    classesFile << "Assembly-CSharp Classes - Generated " << __DATE__ << " " << __TIME__ << std::endl;
    classesFile << "Total Classes: " << g_Classes.size() << std::endl << std::endl;

    for (const auto& classInfo : g_Classes) {
        classesFile << "Class: " << classInfo.fullName << std::endl;
        classesFile << "Parent: " << classInfo.parentClass << std::endl;

        classesFile << "Fields (" << classInfo.fields.size() << "):" << std::endl;
        for (const auto& field : classInfo.fields) {
            classesFile << "    " << field.fieldType << " " << field.fieldName
                << " (Offset: 0x" << std::hex << std::uppercase << field.offset << ")" << std::dec << std::endl;
        }

        classesFile << "Methods (" << classInfo.methods.size() << "):" << std::endl;
        for (const auto& method : classInfo.methods) {
            classesFile << "    " << method.returnType << " " << method.methodName << "()";
            if (method.paramCount >= 0) {
                classesFile << " [" << method.paramCount << " params]";
            }
            classesFile << " (Addr: " << std::hex << method.methodPtr << ")" << std::dec << std::endl;
        }

        classesFile << std::endl << "----------------------------------------" << std::endl << std::endl;
    }

    classesFile.close();

    // Save addresses file (for use with tools like Cheat Engine)
    std::string addressesPath = g_OutputPath + "\\Addresses.txt";
    std::ofstream addressesFile(addressesPath);

    if (!addressesFile.is_open()) {
        Log("Failed to open addresses file: %s\n", addressesPath.c_str());
        return;
    }

    addressesFile << "Assembly-CSharp Method Addresses - Generated " << __DATE__ << " " << __TIME__ << std::endl << std::endl;

    for (const auto& classInfo : g_Classes) {
        if (classInfo.methods.empty()) continue;

        addressesFile << classInfo.fullName << ":" << std::endl;

        for (const auto& method : classInfo.methods) {
            addressesFile << "    " << method.methodName;
            if (method.paramCount >= 0) {
                addressesFile << " [" << method.paramCount << " params]";
            }
            addressesFile << " = " << std::hex << method.methodPtr << std::dec << std::endl;
        }

        addressesFile << std::endl;
    }

    addressesFile.close();

    // Create a JSON file for tools integration
    std::string jsonPath = g_OutputPath + "\\AssemblyCSharp.json";
    std::ofstream jsonFile(jsonPath);

    if (!jsonFile.is_open()) {
        Log("Failed to open JSON file: %s\n", jsonPath.c_str());
        return;
    }

    jsonFile << "{" << std::endl;
    jsonFile << "  \"classes\": [" << std::endl;

    for (size_t i = 0; i < g_Classes.size(); i++) {
        const auto& classInfo = g_Classes[i];

        jsonFile << "    {" << std::endl;
        jsonFile << "      \"name\": \"" << classInfo.className << "\"," << std::endl;
        jsonFile << "      \"namespace\": \"" << classInfo.namespaceName << "\"," << std::endl;
        jsonFile << "      \"fullName\": \"" << classInfo.fullName << "\"," << std::endl;
        jsonFile << "      \"parent\": \"" << classInfo.parentClass << "\"," << std::endl;

        jsonFile << "      \"fields\": [" << std::endl;
        for (size_t j = 0; j < classInfo.fields.size(); j++) {
            const auto& field = classInfo.fields[j];

            jsonFile << "        {" << std::endl;
            jsonFile << "          \"name\": \"" << field.fieldName << "\"," << std::endl;
            jsonFile << "          \"type\": \"" << field.fieldType << "\"," << std::endl;
            jsonFile << "          \"offset\": \"0x" << std::hex << field.offset << "\"" << std::dec << std::endl;
            jsonFile << "        }" << (j < classInfo.fields.size() - 1 ? "," : "") << std::endl;
        }
        jsonFile << "      ]," << std::endl;

        jsonFile << "      \"methods\": [" << std::endl;
        for (size_t j = 0; j < classInfo.methods.size(); j++) {
            const auto& method = classInfo.methods[j];

            jsonFile << "        {" << std::endl;
            jsonFile << "          \"name\": \"" << method.methodName << "\"," << std::endl;
            jsonFile << "          \"returnType\": \"" << method.returnType << "\"," << std::endl;
            jsonFile << "          \"paramCount\": " << method.paramCount << "," << std::endl;
            jsonFile << "          \"address\": \"0x" << std::hex << method.methodPtr << "\"" << std::dec << std::endl;
            jsonFile << "        }" << (j < classInfo.methods.size() - 1 ? "," : "") << std::endl;
        }
        jsonFile << "      ]" << std::endl;

        jsonFile << "    }" << (i < g_Classes.size() - 1 ? "," : "") << std::endl;
    }

    jsonFile << "  ]" << std::endl;
    jsonFile << "}" << std::endl;

    jsonFile.close();

    std::string message = "Extraction complete. Files saved to " + g_OutputPath;
    MessageBoxA(NULL, message.c_str(), "Assembly-CSharp Extractor", MB_ICONINFORMATION);
}


void Dump::Start()
{
    if (ExtractAssemblyCSharp()) {
        Log("Extraction successful. Saving data...\n");
        SaveExtractedData();
    }
    else {
        Log("Extraction failed\n");
        MessageBoxA(NULL, "Failed to extract data from Assembly-CSharp.dll", "Error", MB_ICONERROR);
    }
}

// Export functions for external tools or manual triggering
extern "C" {
    __declspec(dllexport) void SetOutputPath(const char* path) {
        if (path) {
            g_OutputPath = path;
        }
    }

    __declspec(dllexport) void SetVerboseLogging(bool enabled) {
        g_VerboseOutput = enabled;
    }

    __declspec(dllexport) bool StartExtraction() {
        if (InitializeIL2CPPFunctions()) {
            if (ExtractAssemblyCSharp()) {
                SaveExtractedData();
                return true;
            }
        }
        return false;
    }
}
