// Copyright Epic Games, Inc. All Rights Reserved.
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class MouseController : ModuleRules
    {

        public MouseController(ReadOnlyTargetRules Target) : base(Target)
        {

            PublicIncludePaths.AddRange(
                new string[] {
                Path.Combine(ModuleDirectory, "Public"),
			// ... add public include paths required here ...
		}
                );

            PrivateIncludePaths.AddRange(
                new string[] {
                Path.Combine(ModuleDirectory, "Private"),
					// ... add other private include paths required here ...
				}
                );

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core", "CoreUObject", "Engine", "InputCore",
                    "DeveloperSettings", // UE4.26+
                    "Slate", "SlateCore", "UMG"
					// ... add other public dependencies that you statically link with here ...
				}
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
					// ... add private dependencies that you statically link with here ...
				}
                );

            DynamicallyLoadedModuleNames.AddRange(
                new string[]
                {
					// ... add any modules that your module loads dynamically here ...
				}
                );
        }
    }
}