#include "UI/NewImageViewController.hpp"

#include "Components/IFImage.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "Presenters/PresentorManager.hpp"
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
    auto topBar = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(
        container->get_transform());
    topBar->get_rectTransform()->set_anchoredPosition(Vector2(0.0f, 35.0f));
    auto topBarElement =
        topBar->GetComponent<UnityEngine::UI::LayoutElement*>();
    topBarElement->set_preferredWidth(12);
    topBarElement->set_preferredHeight(40);
    auto topBarBG =
        topBar->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    topBarBG->ApplyBackground(il2cpp_utils::newcsstr("panel-top"));
    topBarBG->background->set_color(UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.9f));

    BeatSaberUI::CreateDropdown(
        topBarElement->get_transform(), "Presentation Options",
        image->presentationoption,
        ImageFactory::Presentors::PresentorManager::SET,
        [this](std::string_view s) {
          image->presentationoption = to_utf8(to_utf16(s));
          Presentors::PresentorManager::Parse(
              image, il2cpp_utils::createcsstr(to_utf8(to_utf16(s))));
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