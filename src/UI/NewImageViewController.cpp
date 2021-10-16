#include "UI/NewImageViewController.hpp"

#include "Components/IFImage.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UI/ImageFactoryFlowCoordinator.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
#include "Utils/FileUtils.hpp"
#include "bs-utils/shared/utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace ImageFactory::ViewControllers;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;

DEFINE_TYPE(ImageFactory::ViewControllers, NewImageViewController);

custom_types::Helpers::Coroutine waitForModalToSpawn(HMUI::ModalView* modal) {
  co_yield reinterpret_cast<System::Collections::IEnumerator*>(
      CRASH_UNLESS(WaitForSeconds::New_ctor(0.5)));
  modal->Show(false, false, nullptr);
  co_return;
}

void NewImageViewController::DidActivate(bool firstActivation,
                                         bool addedToHierarchy,
                                         bool screenSystemEnabling) {
  if (firstActivation) {
    if (!get_gameObject()) return;

    get_gameObject()->AddComponent<Touchable*>();

    GameObject* mainLayout = GameObject::New_ctor();
    RectTransform* parent = mainLayout->AddComponent<RectTransform*>();
    parent->SetParent(get_transform(), false);
    parent->set_localPosition(UnityEngine::Vector3(38.0f, 0.0f));

    il2cpp_utils::getLogger().info("[ImageFactory] Rendering Image...");
    image->Render();
    GameObject* container =
        QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(
            this->get_transform());
    BeatSaberUI::CreateStringSetting(
        container->get_transform(), "Name", image->name,
        [this](std::string_view s) { image->name = to_utf8(to_utf16(s)); });
    BeatSaberUI::CreateToggle(container->get_transform(), "Enabled",
                              image->enabled, [this](bool b) {
                                image->enabled = b;
                                image->Update();
                              });
    BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Scale X",
                                        2, 0.1f, image->scaleX,
                                        [this](float f) {
                                          image->scaleX = f;
                                          image->Update();
                                        });
    BeatSaberUI::CreateIncrementSetting(container->get_transform(), "Scale Y",
                                        2, 0.1f, image->scaleY,
                                        [this](float f) {
                                          image->scaleY = f;
                                          image->Update();
                                        });
  }
}

void NewImageViewController::Initialize(Il2CppString* s) {
  il2cpp_utils::getLogger().info("[IF] initializing vars");
  path = to_utf8(csstrtostr(s));
  il2cpp_utils::getLogger().info("[IF] set path");
  std::optional<ImageFactory::Components::IFImage*> o =
      il2cpp_utils::New<ImageFactory::Components::IFImage*>(
          BeatSaberUI::FileToSprite(path), s);
  if (o.has_value()) {
    image = o.value();
    il2cpp_utils::getLogger().info("[IF] set image");
  } else {
    il2cpp_utils::getLogger().info("[IF] couldnt create Image");
    return;
  }
  il2cpp_utils::getLogger().info("[IF] complete");
}