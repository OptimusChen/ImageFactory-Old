#include "UI/ImageEditingViewController.hpp"

#include "../include/PluginConfig.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
#include "Utils/FileUtils.hpp"
#include "bs-utils/shared/utils.hpp"
#include "extern/config-utils/shared/config-utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace ImageFactory::ViewControllers;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;

DEFINE_TYPE(ImageFactory::ViewControllers, ImageEditingViewController);

UnityEngine::UI::HorizontalLayoutGroup* listBar;
QuestUI::Backgroundable* listBG;
UnityEngine::GameObject* scrollableList;

void ImageEditingViewController::DidActivate(bool firstActivation,
                                             bool addedToHierarchy,
                                             bool screenSystemEnabling) {
  if (firstActivation) {
    refresh = true;
    if (!get_gameObject()) return;

    get_gameObject()->AddComponent<Touchable*>();

    GameObject* mainLayout = GameObject::New_ctor();
    RectTransform* parent = mainLayout->AddComponent<RectTransform*>();
    parent->SetParent(get_transform(), false);
    parent->set_localPosition(UnityEngine::Vector3(38.0f, 0.0f));
  }
  if (refresh || firstActivation) {
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

    listBar =
        QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(get_transform());
    listBar->get_rectTransform()->set_anchoredPosition(Vector2(0.0f, 0.0f));
    auto listBarElement =
        listBar->GetComponent<UnityEngine::UI::LayoutElement*>();
    listBarElement->set_preferredWidth(20);
    listBarElement->set_preferredHeight(60);
    listBG =
        listBar->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    listBG->ApplyBackground(il2cpp_utils::newcsstr("panel-top"));
    listBG->background->set_color(UnityEngine::Color(0.1f, 0.1f, 0.1f, 0.1f));

    scrollableList = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(
        listBG->get_transform());
    std::string s = getPluginConfig().Images.GetValue();
    Il2CppString* csstr = il2cpp_utils::createcsstr(s);
    ConfigDocument& config = getPluginConfig().config->config;
    for (int i = 0; i < csstr->Split('/')->get_Length(); i++) {
      Il2CppString* csfileName = csstr->Split('/')->get(i);
      std::string fileName = to_utf8(csstrtostr(csfileName));
      if (fileName.compare("") == 1) {
        il2cpp_utils::getLogger().info("[ImageFactory] %s", fileName.c_str());
        UnityEngine::UI::HorizontalLayoutGroup* levelBarLayout =
            QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(
                scrollableList->get_transform());
        UnityEngine::GameObject* prefab = levelBarLayout->get_gameObject();

        levelBarLayout->set_childControlWidth(false);
        UnityEngine::UI::LayoutElement* levelBarLayoutElement =
            levelBarLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
        levelBarLayoutElement->set_minHeight(10.0f);
        levelBarLayoutElement->set_minWidth(20.0f);
        if (config.HasMember(fileName)) {
          rapidjson::Value& configValue = config[fileName];
          Sprite* sprite = QuestUI::BeatSaberUI::FileToSprite(
              configValue["path"].GetString());
          QuestUI::BeatSaberUI::CreateImage(
              levelBarLayoutElement->get_transform(), sprite,
              Vector2(2.0f, 0.0f), Vector2(10.0f, 2.0f));
          if (!configValue["enabled"].GetBool()) {
            QuestUI::BeatSaberUI::CreateText(
                levelBarLayoutElement->get_transform(),
                configValue["name"].GetString(), true)
                ->set_color(Color(1.0f, 0.0f, 0.0f, 1.0f));
          } else {
            QuestUI::BeatSaberUI::CreateText(
                levelBarLayoutElement->get_transform(),
                configValue["name"].GetString(), true)
                ->set_color(Color(0.0f, 1.0f, 0.0f, 1.0f));
          }
          levelBarLayoutElement->set_minWidth(1.0f);
          levelBarLayoutElement->set_minHeight(1.0f);
          auto deleteButton = QuestUI::BeatSaberUI::CreateUIButton(
              levelBarLayoutElement->get_transform(), "", Vector2(0.0f, 0.0f),
              Vector2(12.0f, 9.0f), []() {

              });
          auto deleteText = QuestUI::BeatSaberUI::CreateText(
              deleteButton->get_transform(), "X");
          deleteText->set_alignment(TMPro::TextAlignmentOptions::Center);
          deleteText->set_color(Color(1.0f, 0.0f, 0.0f, 1.0f));
          auto editButton = QuestUI::BeatSaberUI::CreateUIButton(
              levelBarLayoutElement->get_transform(), "", Vector2(0.0f, 0.0f),
              Vector2(12.0f, 9.0f), []() {

              });
          auto editText = QuestUI::BeatSaberUI::CreateText(
              editButton->get_transform(), "<-");
          editText->set_alignment(TMPro::TextAlignmentOptions::Center);
        }
        refresh = false;
      }
    }
  }
}
void ImageEditingViewController::Refresh() {
  this->refresh = true;
  UnityEngine::Object::Destroy(scrollableList);
  UnityEngine::Object::Destroy(listBG);
  UnityEngine::Object::Destroy(listBar);
}