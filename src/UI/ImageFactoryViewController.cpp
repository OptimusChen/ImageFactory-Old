#include "UI/ImageFactoryViewController.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "HMUI/Touchable.hpp"
#include "PluginConfig.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;
using namespace HMUI;
using namespace UnityEngine;
using namespace ImageFactory::ViewControllers;

DEFINE_TYPE(ImageFactory::ViewControllers, ImageFactoryViewController);

void SetUpButton(UnityEngine::UI::Button* btn, Sprite* sprite,
                 UnityEngine::Sprite* active, std::string hoverHint) {
  reinterpret_cast<UnityEngine::RectTransform*>(
      btn->get_transform()->GetChild(0))
      ->set_sizeDelta({18.0f, 18.0f});
  auto components = btn->GetComponentsInChildren<HMUI::ImageView*>();

  for (int i = 0; i < components->get_Length(); i++) {
    components->get(i)->skew = 0.0f;
  }

  BeatSaberUI::SetButtonSprites(btn, sprite, active);
  BeatSaberUI::AddHoverHint(btn->get_gameObject(), hoverHint);
}

void SpawnInfoModal(std::string name, std::string desc, Sprite* image,
                    UnityEngine::Transform* parent, std::string btnName,
                    std::function<void(HMUI::ModalView*)> onClick) {
  HMUI::ModalView* modal = BeatSaberUI::CreateModal(
      parent, UnityEngine::Vector2(90.0f, 50.0f), [](HMUI::ModalView* modal) {},
      true);
  UnityEngine::GameObject* scrollableModal =
      BeatSaberUI::CreateScrollableModalContainer(modal);
  modal->Show(true, true, nullptr);
  if (image) {
    if (name.compare("Help and FAQ") == 0) {
      BeatSaberUI::CreateImage(modal->get_transform(), image,
                               Vector2(-38.0f, 19.0f), Vector2(6.0f, 9.0f));

    } else {
      BeatSaberUI::CreateImage(modal->get_transform(), image,
                               Vector2(-38.0f, 19.0f), Vector2(9.0f, 9.0f));
    }
  }
  BeatSaberUI::CreateUIButton(modal->get_transform(), "DISMISS",
                              Vector2(-22.0f, -19.0f), Vector2(40.0f, 8.0f),
                              [modal]() { modal->Hide(true, nullptr); });
  BeatSaberUI::CreateUIButton(modal->get_transform(), btnName,
                              Vector2(22.0f, -19.0f), Vector2(40.0f, 8.0f),
                              [onClick, modal]() { onClick(modal); });
  BeatSaberUI::CreateImage(
      modal->get_transform(),
      BeatSaberUI::FileToSprite("/sdcard/ModData/com.beatgames.beatsaber/Mods/"
                                "ImageFactory/Icons/pixel.png"),
      Vector2(0.0f, 13.0f), Vector2(85.0f, 0.8f));
  BeatSaberUI::CreateText(modal->get_transform(), name, Vector2(-32.0f, 25.0f),
                          true)
      ->set_fontSize(10.0f);
  auto descText = BeatSaberUI::CreateText(modal->get_transform(), desc,
                                          Vector2(-42.0f, 10.0f), true);
}

void ShowLinkPanel(std::string link, HMUI::ModalView* modal) {
  HMUI::ModalView* linkHost = BeatSaberUI::CreateModal(
      modal->get_transform(), UnityEngine::Vector2(75.0f, 10.0f),
      [](HMUI::ModalView* modal) {}, true);
  UnityEngine::GameObject* linkHostScrollable =
      BeatSaberUI::CreateScrollableModalContainer(linkHost);
  BeatSaberUI::CreateText(linkHost->get_transform(), link, true)
      ->set_alignment(TMPro::TextAlignmentOptions::Center);
  linkHost->Show(true, true, nullptr);
}

void ImageFactoryViewController::DidActivate(bool firstActivation,
                                             bool addedToHierarchy,
                                             bool screenSystemEnabling) {
  if (firstActivation) {
    if (!get_gameObject()) return;

    get_gameObject()->AddComponent<Touchable*>();

    GameObject* mainLayout = GameObject::New_ctor();
    RectTransform* parent = mainLayout->AddComponent<RectTransform*>();
    parent->SetParent(get_transform(), false);
    parent->set_localPosition(UnityEngine::Vector3(38.0f, 0.0f));

    std::string iconsPath =
        "/sdcard/ModData/com.beatgames.beatsaber/Mods/ImageFactory/Icons/";
    UnityEngine::Sprite* logo =
        BeatSaberUI::FileToSprite(iconsPath + "logo.png");
    UnityEngine::Sprite* auros =
        BeatSaberUI::FileToSprite(iconsPath + "auros.png");
    UnityEngine::Sprite* bandoot =
        BeatSaberUI::FileToSprite(iconsPath + "bandoot.png");
    UnityEngine::Sprite* github =
        BeatSaberUI::FileToSprite(iconsPath + "github.png");
    UnityEngine::Sprite* help =
        BeatSaberUI::FileToSprite(iconsPath + "help.png");
    UnityEngine::Sprite* reset =
        BeatSaberUI::FileToSprite(iconsPath + "reset.png");
    UnityEngine::Sprite* settings =
        BeatSaberUI::FileToSprite(iconsPath + "settings.png");

    UnityEngine::Sprite* aurosActive =
        BeatSaberUI::FileToSprite(iconsPath + "aurosActive.png");
    UnityEngine::Sprite* bandootActive =
        BeatSaberUI::FileToSprite(iconsPath + "bandootActive.png");
    UnityEngine::Sprite* githubActive =
        BeatSaberUI::FileToSprite(iconsPath + "githubActive.png");
    UnityEngine::Sprite* helpActive =
        BeatSaberUI::FileToSprite(iconsPath + "helpActive.png");
    UnityEngine::Sprite* resetActive =
        BeatSaberUI::FileToSprite(iconsPath + "resetActive.png");
    UnityEngine::Sprite* settingsActive =
        BeatSaberUI::FileToSprite(iconsPath + "settingsActive.png");

    HMUI::ImageView* logoView =
        BeatSaberUI::CreateImage(this->get_transform(), logo,
                                 Vector2(0.0f, 0.0f), Vector2(58.0f, 58.0f));
    HMUI::ImageView* aurosView =
        BeatSaberUI::CreateImage(this->get_transform(), auros,
                                 Vector2(35.0f, -20.0f), Vector2(18.0f, 18.0f));
    HMUI::ImageView* bandootView =
        BeatSaberUI::CreateImage(this->get_transform(), bandoot,
                                 Vector2(35.0f, 0.0f), Vector2(18.0f, 18.0f));
    HMUI::ImageView* githubView =
        BeatSaberUI::CreateImage(this->get_transform(), github,
                                 Vector2(35.0f, 20.0f), Vector2(18.0f, 18.0f));
    HMUI::ImageView* helpView = BeatSaberUI::CreateImage(
        this->get_transform(), help, Vector2(-35.0f, -20.0f),
        Vector2(18.0f, 18.0f));
    HMUI::ImageView* resetView =
        BeatSaberUI::CreateImage(this->get_transform(), reset,
                                 Vector2(-35.0f, 0.0f), Vector2(18.0f, 18.0f));
    HMUI::ImageView* settingsView =
        BeatSaberUI::CreateImage(this->get_transform(), settings,
                                 Vector2(-35.0f, 20.0f), Vector2(18.0f, 18.0f));

    BeatSaberUI::CreateText(this->get_transform(), "v1.0.0", false,
                            Vector2(20.0f, -40.0f))
        ->set_fontSize(7.5f);

    aurosView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
    bandootView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
    githubView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
    helpView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
    resetView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
    settingsView->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));

    helpView->set_preserveAspect(true);

    auto aurosButton = BeatSaberUI::CreateUIButton(
        aurosView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [auros, this]() {
          SpawnInfoModal(
              "Auros", "The original PC ImageFactory mod was made by Auros.",
              auros, this->get_transform(), "Youtube Link",
              [](HMUI::ModalView* modal) {
                ShowLinkPanel(
                    "https://www.youtube.com/channel/UCmp351rR-rtljFBNkZZQrcg",
                    modal);
              });
        });
    auto bandootButton = BeatSaberUI::CreateUIButton(
        bandootView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [bandoot, this]() {
          SpawnInfoModal("Bandoot",
                         "Bandoot commissioned for the original PC "
                         "ImageFactory mod to\nbe made, go check him out!",
                         bandoot, this->get_transform(), "Twitch Link",
                         [](HMUI::ModalView* modal) {
                           ShowLinkPanel("https://www.twitch.tv/bandoot",
                                         modal);
                         });
        });
    auto helpButton = BeatSaberUI::CreateUIButton(
        helpView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [this, help, helpView]() {
          SpawnInfoModal(
              "Help and FAQ",
              "ImageFactory allows you to place custom images throughout your\n"
              "game. Everything has been designed to be easy for the user to "
              "use\nand customize. To learn more about how to use this mod, "
              "you "
              "can\nwatch this video showcasing how to use it.",
              helpView->get_sprite(), this->get_transform(), "Youtube Link",
              [](HMUI::ModalView* modal) {
                ShowLinkPanel("https://www.youtube.com/watch?v=8WZ-Jvg-OOo",
                              modal);
              });
        });
    auto githubButton = BeatSaberUI::CreateUIButton(
        githubView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [this, github]() {
          SpawnInfoModal(
              "Github",
              "ImageFactory is open source! You can view it on GitHub. Have a\n"
              "bug report or a feature request? Submit an issue on GitHub.",
              github, this->get_transform(), "Github Link",
              [](HMUI::ModalView* modal) {
                ShowLinkPanel("https://github.com/OptimusChen/ImageFactory",
                              modal);
              });
        });
    auto resetButton = BeatSaberUI::CreateUIButton(
        resetView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [this]() { this->reset(); });
    auto settingsButton = BeatSaberUI::CreateUIButton(
        settingsView->get_transform(), "", "SettingsButton", Vector2(0.0, 0.0f),
        Vector2(15.0f, 15.0f), [this]() {
          HMUI::ModalView* modal = BeatSaberUI::CreateModal(
              this->get_transform(), UnityEngine::Vector2(76.0f, 28.0f),
              [](HMUI::ModalView* modal) {}, true);
          UnityEngine::GameObject* scrollableModal =
              BeatSaberUI::CreateScrollableModalContainer(modal);
          BeatSaberUI::CreateToggle(
              scrollableModal->get_transform(), "Enabled",
              getPluginConfig().Enabled.GetValue(),
              [](bool b) { getPluginConfig().Enabled.SetValue(b); });
          BeatSaberUI::CreateToggle(
              scrollableModal->get_transform(), "Animate Images",
              getPluginConfig().AnimateImages.GetValue(),
              [](bool b) { getPluginConfig().AnimateImages.SetValue(b); });
          BeatSaberUI::CreateToggle(
              scrollableModal->get_transform(), "Ignore No Text and HUDs",
              getPluginConfig().IgnoreNoTextAndHud.GetValue(),
              [](bool b) { getPluginConfig().IgnoreNoTextAndHud.SetValue(b); });
          modal->Show(true, true, nullptr);
        });

    SetUpButton(aurosButton, auros, aurosActive, "The mod creator!");
    SetUpButton(bandootButton, bandoot, bandootActive, "The mod commissioner!");
    SetUpButton(githubButton, github, githubActive, "View the GitHub page!");
    SetUpButton(helpButton, help, helpActive, "Help and Tutorial");
    SetUpButton(resetButton, reset, resetActive, "Reset All Config Data");
    SetUpButton(settingsButton, settings, settingsActive,
                "Global Mod Settings");
  }
}

void ImageFactoryViewController::set_resetConfigFunction(
    std::function<void()> resetConfigFunction) {
  this->reset = resetConfigFunction;
}