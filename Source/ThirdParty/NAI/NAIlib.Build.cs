using UnrealBuildTool;
using System;

public class NAIlib : ModuleRules
{
    public NAIlib(ReadOnlyTargetRules Target) : base(Target)
    {
        // We neeed to depend on Core in order to implement our game module in the next step
        PublicDependencyModuleNames.AddRange(new string[]{"Core"});

        bAddDefaultIncludePaths = false;

        if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            Console.Error.WriteLine("Win32 platform not supported!");
            Environment.Exit(1);

        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(ModuleDirectory + "\\include");

            PublicAdditionalLibraries.Add(ModuleDirectory + "\\lib\\NAI.lib");
        }
        else
        {
            // Some other platform
            Console.Error.WriteLine("Other target platforms not supported");
            Environment.Exit(1);
        }

    }
}