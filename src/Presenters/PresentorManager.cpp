#include "Presenters/PresentorManager.hpp"

#include "Components/IFImage.hpp"
#include "beatsaber-hook/shared/utils/gc-alloc.hpp"

DEFINE_TYPE(ImageFactory::Presentors, PresentorManager);

using namespace ImageFactory::Components;

namespace ImageFactory::Presentors {
std::string PresentorManager::EVERYWHERE = "Everywhere";
std::string PresentorManager::IN_MENU = "In Menu";
std::string PresentorManager::RESULTS_SCREEN = "Results Screen";
std::string PresentorManager::IN_SONG = "In Song";
std::string PresentorManager::PERCENT = "%";
std::string PresentorManager::PERCENT_RANGE = "% Range";
std::string PresentorManager::COMBO = "Combo";
std::string PresentorManager::COMBO_INCREMENT = "Combo Increment";
std::string PresentorManager::COMBO_HOLD = "Combo Hold";
std::string PresentorManager::COMBO_DROP = "Combo Drop";
std::string PresentorManager::FULL_COMBO = "Full Combo";
std::string PresentorManager::IN_PAUSE = "In Pause Menu";
std::string PresentorManager::LAST_NOTE = "On Last Note";
std::vector<std::string> PresentorManager::SET = {
    EVERYWHERE,    IN_MENU,  RESULTS_SCREEN,  IN_SONG,    PERCENT,
    PERCENT_RANGE, COMBO,    COMBO_INCREMENT, COMBO_HOLD, COMBO_DROP,
    FULL_COMBO,    IN_PAUSE, LAST_NOTE};

std::unordered_map<IFImage*, std::string>* PresentorManager::MAP =
    new std::unordered_map<IFImage*, std::string>();

void PresentorManager::Parse(ImageFactory::Components::IFImage* image,
                             Il2CppString* str) {
  if (MAP->contains(image)) {
    MAP->erase(image);
  }
  image->presentationoption;
  MAP->insert({image, to_utf8(csstrtostr(str))});
}
void PresentorManager::ClearInfo(IFImage* image) {
  if (MAP->contains(image)) {
    MAP->erase(image);
  }
}
void PresentorManager::SpawnInMenu() {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second.compare(EVERYWHERE) == 0 ||
        pair.second.compare(IN_MENU) == 0) {
      pair.first->Spawn();
    } else {
      pair.first->Despawn();
    }
  }
}
void PresentorManager::SpawnAll() {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    pair.first->Spawn();
  }
}
void PresentorManager::DespawnAll() {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    pair.first->Despawn();
  }
}
void PresentorManager::SpawnforAll(std::string str) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second.compare(str) == 0) {
      il2cpp_utils::getLogger().info("[ImageFactory] Spawning image");
      pair.first->Spawn();
    }
  }
}
void PresentorManager::DeSpawnforAll(std::string str) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second.compare(str) == 0) {
      pair.first->Despawn();
    }
  }
}
void PresentorManager::SpawnforAllWithExtraData(std::string str,
                                                std::string key,
                                                std::string val) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second.compare(str) == 0) {
      if (pair.first->GetExtraData(key, val).compare(val) == 0) {
        il2cpp_utils::getLogger().info("[ImageFactory] Spawning image");
        pair.first->Spawn();
      }
    }
  }
}
void PresentorManager::DeSpawnforAllWithExtraData(std::string str,
                                                  std::string key,
                                                  std::string val) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second.compare(str) == 0) {
      if (pair.first->GetExtraData(key, val).compare(val) == 0) {
        pair.first->Despawn();
      }
    }
  }
}
}  // namespace ImageFactory::Presentors
