#pragma once
 
#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(KinectPluginV18, Log, All);
//DEFINE_LOG_CATEGORY(KinectPluginV18Log);

class FPluginCreatorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void MyButtonClicked();
	

private: 
	/*
	void AddToolbarExtension(FToolBarBuilder &);
	void AddMenuExtension(FMenuBuilder &);

	TSharedRef<SDockTab> HandleSpawnPictureTaleTab(const FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class SWidget> TabContentWidget;

	TSharedPtr<FTabManager> TabManager;
	TSharedPtr<SDockTab> MajorTab;

	TSharedPtr<FUICommandList> MyPluginCommands;
	TSharedPtr<FExtensibilityManager> MyExtensionManager;
	TSharedPtr< const FExtensionBase > ToolbarExtension;
	TSharedPtr<FExtender> ToolbarExtender;
	*/
};

