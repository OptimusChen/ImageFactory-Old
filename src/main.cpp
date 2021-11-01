#include "main.hpp"

#include "../include/PluginConfig.hpp"
#include "Hooks/IHook.hpp"
#include "Hooks/Impl/PresentorHooks.hpp"
#include "Hooks/Impl/ScoreControllerUpdate.hpp"
#include "UI/ImageFactoryFlowCoordinator.hpp"
#include "Utils/FileUtils.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "extern/config-utils/shared/config-utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace ImageFactory;
using namespace ImageFactory::FileUtils;
using namespace GlobalNamespace;
using namespace QuestUI::BeatSaberUI;

static ModInfo modInfo;  // Stores the ID and version of our mod, and is sent to
                         // the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
  static Configuration config(modInfo);
  config.Load();
  return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
  static Logger* logger = new Logger(modInfo);
  return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
  info.id = ID;
  info.version = VERSION;
  modInfo = info;

  getConfig().Load();
  getPluginConfig().Init(info);
  getConfig().Reload();
  getConfig().Write();  // Load the config file
  getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
  il2cpp_functions::Init();

  QuestUI::Init();
  custom_types::Register::AutoRegister();
  QuestUI::Register::RegisterMainMenuModSettingsFlowCoordinator<
      ImageFactory::ImageFactoryFlowCoordinator*>(modInfo);
  QuestUI::Register::RegisterModSettingsFlowCoordinator<
      ImageFactory::ImageFactoryFlowCoordinator*>(modInfo);

  new ImageFactory::Hooks::PresentorHooks("PresentorHooks");

  getLogger().info("Installing hooks...");
  if (!ImageFactory::IHook::InstallHooks()) {
    getLogger().info("Failed to install hooks.");
  } else {
    getLogger().info("Finished installing hooks!");
  }
}