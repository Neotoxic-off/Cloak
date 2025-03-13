# Cloak
🤹 Cloak is a DLL made to simplify hooks

## About
- Cloak is a project made to simplify dll building to reverse process memory
- By default Cloak provides simple debugger and presence hidder (more comming soon)
- Cloak doesn't provide any offset
- Cloak must be rebuild for your own usage and edit the files

## Features
- Auto hooking
- Auto unhook
- Auto rehook
- Auto module management
- Auto pattern scanning
- Keys interactions

## Usage
- Edit the offsets in `include/constants/offsets.h`
- Edit the modules in `include/constants/modules.h`
- Go in `src/user/sample.cpp`
- Set you **game module** the **offset** and the **method** (can be edited / created / deleted)
```CPP
void Sample::Run()
{
    this->factory.cheats = {
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_1, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_2, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_3, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_4, DummyZero, nullptr),
        Cheat(MODULE_GAME_ASSEMBLY, OFFSET_SAMPLE_5, DummyZero, nullptr)
    };

    this->factory.Initialize();
}
```
- Compile the project for x64
- Inject `Cloak.dll`

## Demo
<image src="Assets/demo.gif"/>

## Important
I provide my tools and resources as-is, without any guarantees or warranties regarding their usage.
In any case, I am not responsible for how these tools are used, nor for any consequences, damages, or issues arising from their application.
Users are solely responsible for ensuring that they comply with all applicable laws, regulations, and ethical considerations when using my tools.
