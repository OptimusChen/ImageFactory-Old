#include "Hooks/Impl/PresentorHooks.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/PauseAnimationController.hpp"
#include "GlobalNamespace/PauseController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "GlobalNamespace/StandardLevelScenesTransitionSetupDataSO.hpp"
#include "Presenters/PresentorManager.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "main.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace ImageFactory::Presentors;
using namespace ImageFactory::Hooks;

MAKE_HOOK_MATCH(SongEnd, &StandardLevelScenesTransitionSetupDataSO::Finish,
                void, StandardLevelScenesTransitionSetupDataSO* self,
                LevelCompletionResults* levelCompletionResults) {
  for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
    pair.first->inSong = false;
    GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(
        reinterpret_cast<custom_types::Helpers::enumeratorT*>(
            custom_types::Helpers::CoroutineHelper::New(
                pair.first->UpdateEveryTick())));
    UnityEngine::Object::Destroy(pair.first->inSongImage);
    UnityEngine::Object::Destroy(pair.first->inSongScreen);
  }
  PresentorManager::SpawnforAll(PresentorManager::IN_MENU);
  PresentorManager::DeSpawnforAll(PresentorManager::IN_SONG);
  SongEnd(self, levelCompletionResults);
}

MAKE_HOOK_MATCH(SongStart, &AudioTimeSyncController::StartSong, void,
                AudioTimeSyncController* self, float startTimeOffset) {
  for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
    pair.first->inSong = true;
  }
  PresentorManager::SpawnforAll(PresentorManager::IN_SONG);
  PresentorManager::SpawnforAll(PresentorManager::EVERYWHERE);
  PresentorManager::DeSpawnforAll(PresentorManager::IN_MENU);
  SongStart(self, startTimeOffset);
}

MAKE_HOOK_MATCH(SongUpdate, &AudioTimeSyncController::Update, void,
                AudioTimeSyncController* self) {
  // for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
  //   if (!pair.first->inSongScreen) {
  //     pair.first->inSongScreen = BeatSaberUI::CreateFloatingScreen(
  //         Vector2(pair.first->scaleX * (pair.first->width / 3),
  //                 pair.first->scaleY * (pair.first->height / 3)),
  //         Vector3(pair.first->x, pair.first->y, pair.first->z),
  //         Vector3(pair.first->angleX, pair.first->angleY,
  //         pair.first->angleZ), 0.0f, false, true, 4);
  //   }
  // }
  SongUpdate(self);
}

MAKE_HOOK_MATCH(PauseStart, &PauseMenuManager::ShowMenu, void,
                PauseMenuManager* self) {
  PresentorManager::SpawnforAll(PresentorManager::IN_PAUSE);
  for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
    il2cpp_utils::getLogger().info("[ImageFactory] %s", pair.second.c_str());
  }
  PauseStart(self);
}

MAKE_HOOK_MATCH(
    PauseAnimationFinish,
    &PauseController::HandlePauseMenuManagerDidFinishResumeAnimation, void,
    PauseController* self) {
  PresentorManager::DeSpawnforAll(PresentorManager::IN_PAUSE);
  PauseAnimationFinish(self);
}

void PresentorHooks::AddHooks() {
  INSTALL_HOOK(getLogger(), SongEnd);
  INSTALL_HOOK(getLogger(), SongStart);
  INSTALL_HOOK(getLogger(), SongUpdate);
  INSTALL_HOOK(getLogger(), PauseAnimationFinish);
  INSTALL_HOOK(getLogger(), PauseStart);
}