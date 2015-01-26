using UnrealBuildTool;
using System.IO;
 
public class Kinect18Plugin : ModuleRules
{
    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

     private string ThirdPartyPath
     {
         get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
     }

    public Kinect18Plugin(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(new string[] { "Kinect18Plugin/Private", "Kinect18Plugin/Public", "Kinect18Plugin/Private/UDKinect" });

        PrivateIncludePathModuleNames.AddRange(new string[] { "Kinect18Plugin" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
				"Core",
				"CoreUObject",
				"Slate",
				"SlateCore",
				"Engine",
                "InputCore",
                "ClassViewer",
				"AssetTools",
				"UnrealEd", // for FAssetEditorManager
				"KismetWidgets",
				"GraphEditor",
				"Kismet",  // for FWorkflowCentricApplication
				"PropertyEditor",
				"RenderCore",
				"LevelEditor",
				"EditorStyle",
                "Kinect18Plugin",
                "Projects",
                //"SourceControl",
			}
            );

        DynamicallyLoadedModuleNames.AddRange(
            new string[] {
                "Kinect18Plugin",
            });
			
		// Finally load all external libraries
		LoadKinectDLL(Target);
        LoadUDKinectDLL(Target);
    }


    public bool LoadKinectDLL(TargetInfo Target)
    {
        bool IsLibrarySupported = true;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            IsLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "amd64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Kinect", "Lib", PlatformString);

            //Dependency libraries
            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Qt5Core.lib"));

            // Lib
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Kinect10.lib"));            
        }

        if (IsLibrarySupported)
        {
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Kinect", "Include"));
        }

        Definitions.Add(string.Format("WITH_KINECT={0}", IsLibrarySupported ? 1 : 0));

        return IsLibrarySupported;
    }


    public bool LoadUDKinectDLL(TargetInfo Target)
    {
        bool IsLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            IsLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "amd64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "UDKinect", "Lib", PlatformString);
            
            // Lib
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "UDKinect18.lib"));
        }

        if (IsLibrarySupported)
        {
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "UDKinect", "Include"));
        }

        Definitions.Add(string.Format("WITH_KINECT={0}", IsLibrarySupported ? 1 : 0));

        return IsLibrarySupported;
    }
	
}