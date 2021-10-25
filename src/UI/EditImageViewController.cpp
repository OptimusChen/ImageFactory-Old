#include "UI/EditImageViewController.hpp"

#include <iostream>
#include <vector>

#include "../include/PluginConfig.hpp"
#include "Components/IFImage.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "Presenters/PresentorManager.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UI/ImageFactoryFlowCoordinator.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
#include "Utils/FileUtils.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "bs-utils/shared/utils.hpp"
#include "extern/config-utils/shared/config-utils.hpp"
#include "main.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace ImageFactory::ViewControllers;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;
using namespace ImageFactory::Presentors;

DEFINE_TYPE(ImageFactory::ViewControllers, EditImageViewController);

bool didEditDeactivate = false;

custom_types::Helpers::Coroutine EditImageViewController::UpdateImage() {
  while (!didEditDeactivate) {
    image->x = image->screen->get_transform()->get_localPosition().x;
    image->y = image->screen->get_transform()->get_localPosition().y;
    image->z = image->screen->get_transform()->get_localPosition().z;
    image->angleX =
        image->screen->get_transform()->get_rotation().get_eulerAngles().x;
    image->angleY =
        image->screen->get_transform()->get_rotation().get_eulerAngles().y;
    image->angleZ =
        image->screen->get_transform()->get_rotation().get_eulerAngles().z;
    co_yield nullptr;
  }
  co_return;
}

void EditImageViewController::DidActivate(bool firstActivation,
                                          bool addedToHierarchy,
                                          bool screenSystemEnabling) {
  if (firstActivation) {
    if (!get_gameObject()) return;
    didEditDeactivate = false;

    get_gameObject()->AddComponent<Touchable*>();

    GameObject* mainLayout = GameObject::New_ctor();
    RectTransform* parent = mainLayout->AddComponent<RectTransform*>();
    parent->SetParent(get_transform(), false);
    parent->set_localPosition(UnityEngine::Vector3(38.0f, 0.0f));

    il2cpp_utils::getLogger().info("[ImageFactory] Rendering Image...");
    image->SpawnEditorDummy();
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
    auto settingsLayout =
        QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(this->get_transform());
    RectTransform* settingsLayoutTransform =
        settingsLayout->GetComponent<RectTransform*>();
    auto bg = settingsLayout->get_gameObject()->AddComponent<Backgroundable*>();
    bg->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    bg->background->set_color(Color(0.0f, 0.0f, 0.0f, 0.8f));
    settingsLayout->set_spacing(1.2f);
    settingsLayout->set_padding(UnityEngine::RectOffset::New_ctor(3, 3, 2, 2));
    settingsLayout->get_transform()->set_localPosition(
        Vector3(0.0f, -13.5f, 0.0f));
    settingsLayoutTransform->set_sizeDelta(Vector2(90.0f, 38.0f));
    auto settingsElement =
        settingsLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
    settingsElement->set_minHeight(40.0f);
    settingsElement->set_minWidth(90.0f);

    UnityEngine::UI::ContentSizeFitter* contentSizeFitter =
        settingsLayout->get_gameObject()
            ->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
    contentSizeFitter->set_horizontalFit(
        UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);
    contentSizeFitter->set_verticalFit(
        UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);

    auto optionsLayout =
        QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(this->get_transform());
    RectTransform* optionsLayoutTransform =
        optionsLayout->GetComponent<RectTransform*>();
    auto bg1 = optionsLayout->get_gameObject()->AddComponent<Backgroundable*>();
    bg1->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
    bg1->background->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
    optionsLayout->set_spacing(1.2f);
    optionsLayout->set_padding(UnityEngine::RectOffset::New_ctor(3, 3, 2, 2));
    optionsLayout->get_transform()->set_localPosition(
        Vector3(0.0f, 2.0f, 0.0f));
    optionsLayoutTransform->set_sizeDelta(Vector2(90.0f, 38.0f));
    auto optionsElement =
        optionsLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
    optionsElement->set_minWidth(90.0f);
    optionsElement->set_minHeight(10.0f);
    optionsLayout->set_childControlHeight(false);

    UnityEngine::UI::ContentSizeFitter* contentSizeFitter1 =
        optionsLayout->get_gameObject()
            ->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
    contentSizeFitter1->set_horizontalFit(
        UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);
    contentSizeFitter1->set_verticalFit(
        UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);

    HMUI::SimpleTextDropdown* results_when;
    HMUI::SimpleTextDropdown* percent_when;
    QuestUI::IncrementSetting* percent_percent;
    QuestUI::IncrementSetting* percent_range_above;
    QuestUI::IncrementSetting* percent_range_below;
    QuestUI::IncrementSetting* combo_on_combo;
    QuestUI::IncrementSetting* combo_duration;
    QuestUI::IncrementSetting* combo_inc_every_combo;
    QuestUI::IncrementSetting* combo_inc_duration;
    HMUI::SimpleTextDropdown* combo_hold_when;
    QuestUI::IncrementSetting* combo_hold_combo;
    QuestUI::IncrementSetting* combo_drop_duration;
    QuestUI::IncrementSetting* last_note_duration;

    auto dropDown = BeatSaberUI::CreateDropdown(
        optionsElement->get_transform(), "Presentation Options",
        image->presentationoption,
        ImageFactory::Presentors::PresentorManager::SET,
        [this, optionsElement, optionsLayout, optionsLayoutTransform, bg1,
         contentSizeFitter1, results_when, percent_when, percent_percent,
         percent_range_above, percent_range_below, combo_on_combo,
         combo_duration, combo_inc_every_combo, combo_inc_duration,
         combo_hold_when, combo_hold_combo, combo_drop_duration,
         last_note_duration](std::string_view s) mutable -> void {
          image->presentationoption = to_utf8(to_utf16(s));
          Presentors::PresentorManager::Parse(
              image, il2cpp_utils::createcsstr(to_utf8(to_utf16(s))));
          UnityEngine::GameObject::Destroy(optionsLayout);
          optionsLayout = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(
              this->get_transform());
          optionsLayoutTransform =
              optionsLayout->GetComponent<RectTransform*>();
          bg1 =
              optionsLayout->get_gameObject()->AddComponent<Backgroundable*>();
          bg1->ApplyBackground(il2cpp_utils::createcsstr("round-rect-panel"));
          bg1->background->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
          optionsLayout->set_spacing(1.2f);
          optionsLayout->set_padding(
              UnityEngine::RectOffset::New_ctor(3, 3, 2, 2));
          optionsLayout->get_transform()->set_localPosition(
              Vector3(0.0f, 2.0f, 0.0f));
          optionsLayoutTransform->set_sizeDelta(Vector2(90.0f, 38.0f));
          optionsElement =
              optionsLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
          optionsElement->set_minWidth(90.0f);
          optionsElement->set_minHeight(10.0f);
          optionsLayout->set_childControlHeight(false);

          contentSizeFitter1 =
              optionsLayout->get_gameObject()
                  ->AddComponent<UnityEngine::UI::ContentSizeFitter*>();
          contentSizeFitter1->set_horizontalFit(
              UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);
          contentSizeFitter1->set_verticalFit(
              UnityEngine::UI::ContentSizeFitter::FitMode::MinSize);
          QuestUI::BeatSaberUI::CreateDropdown(optionsElement->get_transform(),
                                               "", "", {""},
                                               [this](std::string_view s) {

                                               })
              ->get_gameObject()
              ->SetActive(false);
          static auto labelName =
              il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>(
                  "Label");

          if (results_when) {
            results_when->get_gameObject()->SetActive(false);
            results_when->get_transform()
                ->GetParent()
                ->get_transform()
                ->Find(labelName)
                ->get_gameObject()
                ->SetActive(false);
          }
          if (percent_when) {
            percent_when->get_gameObject()->SetActive(false);
            percent_when->get_transform()
                ->GetParent()
                ->get_transform()
                ->Find(labelName)
                ->get_gameObject()
                ->SetActive(false);
          }
          if (percent_percent) {
            percent_percent->get_gameObject()->SetActive(false);
          }
          if (percent_range_above) {
            percent_range_above->get_gameObject()->SetActive(false);
          }
          if (percent_range_below) {
            percent_range_below->get_gameObject()->SetActive(false);
          }
          if (combo_on_combo) {
            combo_on_combo->get_gameObject()->SetActive(false);
          }
          if (combo_duration) {
            combo_duration->get_gameObject()->SetActive(false);
          }
          if (combo_inc_every_combo) {
            combo_inc_every_combo->get_gameObject()->SetActive(false);
          }
          if (combo_inc_duration) {
            combo_inc_duration->get_gameObject()->SetActive(false);
          }
          if (combo_hold_when) {
            combo_hold_when->get_gameObject()->SetActive(false);
            combo_hold_when->get_transform()
                ->GetParent()
                ->get_transform()
                ->Find(labelName)
                ->get_gameObject()
                ->SetActive(false);
          }
          if (combo_hold_combo) {
            combo_hold_combo->get_gameObject()->SetActive(false);
          }
          if (combo_drop_duration) {
            combo_drop_duration->get_gameObject()->SetActive(false);
          }
          if (last_note_duration) {
            last_note_duration->get_gameObject()->SetActive(false);
          }

          if (image->presentationoption.compare(
                  PresentorManager::RESULTS_SCREEN) == 0) {
            results_when = QuestUI::BeatSaberUI::CreateDropdown(
                optionsElement->get_transform(), "When",
                image->GetExtraData("results_when", "Finished"),
                {"Finished", "Passed", "Failed"}, [this](std::string_view s) {
                  image->SetExtraData("results_when", to_utf8(to_utf16(s)));
                });

            results_when->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::PERCENT) == 0) {
            percent_when = QuestUI::BeatSaberUI::CreateDropdown(
                optionsElement->get_transform(), "When",
                image->GetExtraData("percent_when", "Above"),
                {"Above", "Below"}, [this](std::string_view s) {
                  image->SetExtraData("percent_when", to_utf8(to_utf16(s)));
                });
            percent_when->get_gameObject()->SetActive(true);
            percent_percent = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "%", 0, 1.0f,
                stof(image->GetExtraData("percent_percent", "80")),
                [this](float f) {
                  image->SetExtraData("percent_percent", std::to_string(f));
                });
            percent_percent->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::PERCENT_RANGE) == 0) {
            percent_range_above = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "When Above (%)", 0, 1.0f,
                stof(image->GetExtraData("percent_range_above", "90")),
                [this](float f) {
                  image->SetExtraData("percent_range_above", std::to_string(f));
                });
            percent_range_above->get_gameObject()->SetActive(true);
            percent_range_below = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "and Below (%)", 0, 1.0f,
                stof(image->GetExtraData("percent_range_below", "80")),
                [this](float f) {
                  image->SetExtraData("percent_range_below", std::to_string(f));
                });
            percent_range_below->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::COMBO) == 0) {
            combo_on_combo = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "On Combo", 0, 1.0f,
                stof(image->GetExtraData("combo_on_combo", "100")),
                [this](float f) {
                  image->SetExtraData("combo_on_combo", std::to_string(f));
                });
            combo_on_combo->get_gameObject()->SetActive(true);
            combo_duration = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "Duration (Seconds)", 2, 0.25f,
                stof(image->GetExtraData("combo_duration", "1")),
                [this](float f) {
                  image->SetExtraData("combo_duration", std::to_string(f));
                });
            combo_duration->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::COMBO_INCREMENT) == 0) {
            combo_inc_every_combo =
                QuestUI::BeatSaberUI::CreateIncrementSetting(
                    optionsElement->get_transform(), "On Every X Combo", 0,
                    1.0f,
                    stof(image->GetExtraData("combo_inc_every_combo", "100")),
                    [this](float f) {
                      image->SetExtraData("combo_inc_every_combo",
                                          std::to_string(f));
                    });
            combo_inc_every_combo->get_gameObject()->SetActive(true);
            combo_inc_duration = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "Duration (Seconds)", 2, 0.25f,
                stof(image->GetExtraData("combo_inc_duration", "1")),
                [this](float f) {
                  image->SetExtraData("combo_inc_duration", std::to_string(f));
                });
            combo_inc_duration->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::COMBO_HOLD) == 0) {
            combo_hold_when = QuestUI::BeatSaberUI::CreateDropdown(
                optionsElement->get_transform(), "When",
                image->GetExtraData("combo_hold_when", "Above"),
                {"Above", "Below"}, [this](std::string_view s) {
                  image->SetExtraData("combo_hold_when", to_utf8(to_utf16(s)));
                });
            combo_hold_when->get_gameObject()->SetActive(true);
            combo_hold_combo = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "Combo", 0, 1.0f,
                stof(image->GetExtraData("combo_hold_combo", "100")),
                [this](float f) {
                  image->SetExtraData("combo_hold_combo", std::to_string(f));
                });
            combo_hold_combo->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::COMBO_DROP) == 0) {
            combo_drop_duration = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "Duration (Seconds)", 2, 0.25f,
                stof(image->GetExtraData("combo_drop_duration", "1")),
                [this](float f) {
                  image->SetExtraData("combo_drop_duration", std::to_string(f));
                });
            combo_drop_duration->get_gameObject()->SetActive(true);
          } else if (image->presentationoption.compare(
                         PresentorManager::LAST_NOTE) == 0) {
            last_note_duration = QuestUI::BeatSaberUI::CreateIncrementSetting(
                optionsElement->get_transform(), "Duration (Seconds)", 2, 0.25f,
                stof(image->GetExtraData("last_note_duration", "1")),
                [this](float f) {
                  image->SetExtraData("last_note_duration", std::to_string(f));
                });
            last_note_duration->get_gameObject()->SetActive(true);
          }
        });

    auto cancelButton = BeatSaberUI::CreateUIButton(
        this->get_transform(), "", Vector2(-22.0f, -38.0f),
        Vector2(40.0f, 8.0f), [this]() { leaveViewController(); });
    QuestUI::BeatSaberUI::CreateText(cancelButton->get_transform(), "CANCEL")
        ->set_alignment(TMPro::TextAlignmentOptions::Center);
    auto saveButton = BeatSaberUI::CreateUIButton(
        this->get_transform(), "", Vector2(22.0f, -38.0f), Vector2(40.0f, 8.0f),
        [this]() {
          ConfigDocument& configDoc = getPluginConfig().config->config;
          if (configDoc.HasMember(image->internalName)) {
            rapidjson::Value& configValue = configDoc[image->internalName];
            configValue["x"].SetFloat(image->x);
            configValue["y"].SetFloat(image->y);
            configValue["z"].SetFloat(image->z);
            configValue["angleX"].SetFloat(image->angleX);
            configValue["angleY"].SetFloat(image->angleY);
            configValue["angleZ"].SetFloat(image->angleZ);
            configValue["scaleX"].SetFloat(image->scaleX);
            configValue["scaleY"].SetFloat(image->scaleY);
            configValue["width"].SetFloat(image->width);
            configValue["height"].SetFloat(image->height);
            configValue["name"].SetString(image->name.c_str(),
                                          configDoc.GetAllocator());
            configValue["presentationOption"].SetString(
                image->presentationoption.c_str(), configDoc.GetAllocator());
            configValue["path"].SetString(image->path.c_str(),
                                          configDoc.GetAllocator());
            configValue["enabled"].SetBool(image->enabled);
            PresentorManager::Parse(
                image, il2cpp_utils::createcsstr(image->presentationoption));
            getPluginConfig().config->Write();
            getPluginConfig().config->Reload();
          }
          hasSaved = true;
          leaveViewController();
        });
    QuestUI::BeatSaberUI::CreateText(saveButton->get_transform(), "SAVE")
        ->set_alignment(TMPro::TextAlignmentOptions::Center);
  }
  GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(
      reinterpret_cast<custom_types::Helpers::enumeratorT*>(
          custom_types::Helpers::CoroutineHelper::New(UpdateImage())));
}

void EditImageViewController::DidDeactivate(bool removedFromHierarchy,
                                            bool screenSystemEnabling) {
  didEditDeactivate = true;
}

void EditImageViewController::Initialize(
    ImageFactory::Components::IFImage* image) {
  this->image = image;
  hasSaved = false;
  il2cpp_utils::getLogger().info("[IF] complete");
}