#include "Components/IFImage.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"

using namespace ImageFactory::Components;

DECLARE_CLASS_CODEGEN(
    ImageFactory::Presentors, PresentorManager, UnityEngine::MonoBehaviour,
    DECLARE_STATIC_METHOD(void, Parse, ImageFactory::Components::IFImage* image,
                          Il2CppString* str);
    DECLARE_STATIC_METHOD(void, ClearInfo,
                          ImageFactory::Components::IFImage* image);
    DECLARE_STATIC_METHOD(void, SpawnInMenu);
    DECLARE_STATIC_METHOD(void, SpawnAll);
    DECLARE_STATIC_METHOD(void, DespawnAll); public
    : static std::vector<std::string>
        SET;
    static void SpawnforAll(std::string str);
    static void DeSpawnforAll(std::string str);
    static void SpawnforAllWithExtraData(std::string str, std::string key,
                                         std::string val);
    static void DeSpawnforAllWithExtraData(std::string str, std::string key,
                                           std::string val);
    static std::unordered_map<IFImage*, std::string> * MAP;
    static std::string EVERYWHERE; static std::string IN_MENU;
    static std::string RESULTS_SCREEN; static std::string IN_SONG;
    static std::string PERCENT; static std::string PERCENT_RANGE;
    static std::string COMBO; static std::string COMBO_INCREMENT;
    static std::string COMBO_HOLD; static std::string COMBO_DROP;
    static std::string FULL_COMBO; static std::string IN_PAUSE;
    static std::string LAST_NOTE;)