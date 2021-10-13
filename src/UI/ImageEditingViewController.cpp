#include "UI/ImageEditingViewController.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
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

DEFINE_TYPE(ImageFactory::ViewControllers, ImageEditingViewController);

custom_types::Helpers::Coroutine wait(HMUI::ModalView* modal) {
  co_yield reinterpret_cast<System::Collections::IEnumerator*>(
      CRASH_UNLESS(WaitForSeconds::New_ctor(0.5)));
  modal->Show(false, false, nullptr);
  co_return;
}

void ImageEditingViewController::DidActivate(bool firstActivation,
                                             bool addedToHierarchy,
                                             bool screenSystemEnabling) {
  if (firstActivation) {
    if (!get_gameObject()) return;

    get_gameObject()->AddComponent<Touchable*>();

    GameObject* mainLayout = GameObject::New_ctor();
    RectTransform* parent = mainLayout->AddComponent<RectTransform*>();
    parent->SetParent(get_transform(), false);
    parent->set_localPosition(UnityEngine::Vector3(38.0f, 0.0f));
    auto topBar =
        QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(get_transform());
    topBar->get_rectTransform()->set_anchoredPosition(Vector2(0.0f, 35.0f));
    auto topBarElement =
        topBar->GetComponent<UnityEngine::UI::LayoutElement*>();
    topBarElement->set_preferredWidth(20);
    topBarElement->set_preferredHeight(15);
    auto topBarBG =
        topBar->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    topBarBG->ApplyBackground(il2cpp_utils::newcsstr("panel-top"));
    topBarBG->background->set_color(UnityEngine::Color(0.1f, 0.1f, 0.1f, 0.5f));

    auto topBarTitle = QuestUI::BeatSaberUI::CreateText(
        topBarBG->get_transform(), "Edit Image", true);
    topBarTitle->set_fontSize(10);
    topBarTitle->set_alignment(TMPro::TextAlignmentOptions::Center);

    UnityEngine::GameObject* list =
        QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(
            get_transform());
  }
}