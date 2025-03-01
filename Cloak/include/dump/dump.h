
#pragma once

#include <Windows.h>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <psapi.h>
#include <tlhelp32.h>

class Dump
{
    private:
        typedef void* (*il2cpp_domain_get_t)();
        typedef void** (*il2cpp_domain_get_assemblies_t)(void* domain, size_t* size);
        typedef void* (*il2cpp_assembly_get_image_t)(void* assembly);
        typedef const char* (*il2cpp_image_get_name_t)(void* image);
        typedef void* (*il2cpp_image_get_class_count_t)(void* image);
        typedef void* (*il2cpp_image_get_class_t)(void* image, size_t index);
        typedef const char* (*il2cpp_class_get_name_t)(void* klass);
        typedef const char* (*il2cpp_class_get_namespace_t)(void* klass);
        typedef void* (*il2cpp_class_get_methods_t)(void* klass, void** iter);
        typedef const char* (*il2cpp_method_get_name_t)(void* method);
        typedef void* (*il2cpp_class_get_fields_t)(void* klass, void** iter);
        typedef const char* (*il2cpp_field_get_name_t)(void* field);
        typedef size_t(*il2cpp_field_get_offset_t)(void* field);
        typedef void* (*il2cpp_type_get_name_t)(void* type);
        typedef void* (*il2cpp_field_get_type_t)(void* field);
        typedef void* (*il2cpp_method_get_return_type_t)(void* method);
        typedef void* (*il2cpp_method_get_param_count_t)(void* method);
        typedef void* (*il2cpp_method_get_param_t)(void* method, uint32_t index);
        typedef void* (*il2cpp_type_get_object_t)(void* type);
        typedef void* (*il2cpp_class_get_parent_t)(void* klass);

        struct IL2CPPApiFunctions {
            il2cpp_domain_get_t domain_get;
            il2cpp_domain_get_assemblies_t domain_get_assemblies;
            il2cpp_assembly_get_image_t assembly_get_image;
            il2cpp_image_get_name_t image_get_name;
            il2cpp_image_get_class_count_t image_get_class_count;
            il2cpp_image_get_class_t image_get_class;
            il2cpp_class_get_name_t class_get_name;
            il2cpp_class_get_namespace_t class_get_namespace;
            il2cpp_class_get_methods_t class_get_methods;
            il2cpp_method_get_name_t method_get_name;
            il2cpp_class_get_fields_t class_get_fields;
            il2cpp_field_get_name_t field_get_name;
            il2cpp_field_get_offset_t field_get_offset;
            il2cpp_type_get_name_t type_get_name;
            il2cpp_field_get_type_t field_get_type;
            il2cpp_method_get_return_type_t method_get_return_type;
            il2cpp_method_get_param_count_t method_get_param_count;
            il2cpp_method_get_param_t method_get_param;
            il2cpp_type_get_object_t type_get_object;
            il2cpp_class_get_parent_t class_get_parent;
        };

        struct FieldInfo {
            std::string fieldName;
            std::string fieldType;
            size_t offset;
        };

        struct MethodInfo {
            std::string methodName;
            std::string returnType;
            int paramCount;
            void* methodPtr;
        };

        struct ClassInfo {
            std::string className;
            std::string namespaceName;
            std::string fullName;
            std::string parentClass;
            std::vector<FieldInfo> fields;
            std::vector<MethodInfo> methods;
        };

        HMODULE g_GameAssembly = NULL;
        IL2CPPApiFunctions g_IL2CPPFunctions = {};
        std::vector<ClassInfo> g_Classes;
        std::string g_OutputPath = ".";

        bool InitializeIL2CPPFunctions();
        std::string GetParentClassName(void*);
        std::string GetTypeName(void*);
        void ExtractMethods(void*, ClassInfo&);
        void ExtractFields(void*, ClassInfo&);
	public:
		Dump();
		~Dump();

		void Start();
};
