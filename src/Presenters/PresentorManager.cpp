#include "Presenters/PresentorManager.hpp"

#include "Components/IFImage.hpp"

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
  std::string s = to_utf8(csstrtostr(str));
  if (MAP->contains(image)) {
    MAP->erase(image);
  }
  MAP->insert({image, s});
}
void PresentorManager::SpawnforAll(std::string str) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second == str) {
      il2cpp_utils::getLogger().info("[ImageFactory] Spawning image");
      pair.first->Spawn();
    }
  }
}
void PresentorManager::DeSpawnforAll(std::string str) {
  for (std::pair<IFImage*, std::string> pair : *MAP) {
    if (pair.second == str) {
      pair.first->Despawn();
    }
  }
}
}  // namespace ImageFactory::Presentors
