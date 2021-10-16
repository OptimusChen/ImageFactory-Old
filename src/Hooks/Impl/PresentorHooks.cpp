#include "Hooks/Impl/PresentorHooks.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/PauseAnimationController.hpp"
#include "GlobalNamespace/PauseController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/StandardLevelScenesTransitionSetupDataSO.hpp"
#include "Presenters/PresentorManager.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "main.hpp"

using namespace GlobalNamespace;
using namespace ImageFactory::Presentors;
using namespace ImageFactory::Hooks;

MAKE_HOOK_MATCH(SongEnd, &StandardLevelScenesTransitionSetupDataSO::Finish,
                void, StandardLevelScenesTransitionSetupDataSO* self,
                LevelCompletionResults* levelCompletionResults) {
  for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
    pair.first->inSong = false;
  }
  SongEnd(self, levelCompletionResults);
}

MAKE_HOOK_MATCH(SongStart, &AudioTimeSyncController::StartSong, void,
                AudioTimeSyncController* self, float startTimeOffset) {
  for (std::pair<IFImage*, std::string> pair : *PresentorManager::MAP) {
    pair.first->inSong = true;
  }
  SongStart(self, startTimeOffset);
}

MAKE_HOOK_MATCH(PauseStart, &PauseMenuManager::ShowMenu, void,
                PauseMenuManager* self) {
  PresentorManager::SpawnforAll(PresentorManager::IN_PAUSE);
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
  INSTALL_HOOK(getLogger(), SongEnd)
  INSTALL_HOOK(getLogger(), SongStart)
  INSTALL_HOOK(getLogger(), PauseAnimationFinish)
  INSTALL_HOOK(getLogger(), PauseStart)
}