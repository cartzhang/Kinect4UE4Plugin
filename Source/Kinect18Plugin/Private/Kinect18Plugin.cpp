#include "Kinect18PrivatePCH.h"

#include "Kinect18Plugin.h"
/*
#include "PluginCreatorStyle.h"
#include "SPluginCreatorTabContent.h"
#include "SlateExtras.h"
*/


//#include "PluginCreatorCommands.h"


//#include "MultiBoxExtender.h"

static const FName PCPluginTabName("PluginCreatorPlugin");

#define LOCTEXT_NAMESPACE "PluginCreatorPluginModule"

void FPluginCreatorModule::StartupModule()
{
	//FPluginCreatorStyle::Initialize();
	//FPluginCreatorStyle::ReloadTextures();

	//FPluginCreatorCommands::Register();
	//

	//MyPluginCommands = MakeShareable(new FUICommandList);

	//MyPluginCommands->MapAction(
	//	FPluginCreatorCommands::Get().OpenPluginCreator,
	//	FExecuteAction::CreateRaw(this, &FPluginCreatorModule::MyButtonClicked),
	//	FCanExecuteAction());


	//ToolbarExtender = MakeShareable(new FExtender);
	//ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, MyPluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FPluginCreatorModule::AddToolbarExtension));

	//FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	//LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

	//TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	//MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, MyPluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FPluginCreatorModule::AddMenuExtension));

	//LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	//FGlobalTabmanager::Get()->RegisterNomadTabSpawner(PCPluginTabName, FOnSpawnTab::CreateRaw(this, &FPluginCreatorModule::HandleSpawnPictureTaleTab))
	//	.SetDisplayName(LOCTEXT("PTPluginTabTitle", "Plugin Creator"))
	//	.SetMenuType(ETabSpawnerMenuType::Hidden);
}
//
//void FPluginCreatorModule::AddMenuExtension(FMenuBuilder& builder)
//{
//	builder.AddMenuEntry(
//		FPluginCreatorCommands::Get().OpenPluginCreator,
//		NAME_None,
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetLabel(),
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetDescription(),
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetIcon(),
//		NAME_None);
//}
//
//void FPluginCreatorModule::AddToolbarExtension(FToolBarBuilder &builder)
//{
//	builder.AddToolBarButton(
//		FPluginCreatorCommands::Get().OpenPluginCreator,
//		NAME_None,
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetLabel(),
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetDescription(),
//		FPluginCreatorCommands::Get().OpenPluginCreator->GetIcon(),
//		NAME_None);
//}
//
//TSharedRef<SDockTab> FPluginCreatorModule::HandleSpawnPictureTaleTab(const FSpawnTabArgs& SpawnTabArgs)
//{
//	if (!TabContentWidget.IsValid())
//	{
//		TabContentWidget = SNew(SPluginCreatorTabContent);
//	}
//
//	return SNew(SDockTab)
//		.TabRole(ETabRole::NomadTab)
//		[
//			TabContentWidget.ToSharedRef()
//		];
//}
//
//void FPluginCreatorModule::MyButtonClicked() 
//{
//	FGlobalTabmanager::Get()->InvokeTab(PCPluginTabName);
//}

void FPluginCreatorModule::ShutdownModule()
{/*
	FPluginCreatorStyle::Shutdown();

	FPluginCreatorCommands::Unregister();*/


	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(PCPluginTabName);

}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FPluginCreatorModule, PluginCreatorPlugin)