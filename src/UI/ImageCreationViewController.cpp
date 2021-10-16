#include "UI/ImageCreationViewController.hpp"

#include <filesystem>

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "HMUI/Touchable.hpp"
#include "System/IO/Directory.hpp"
#include "System/IO/DirectoryInfo.hpp"
#include "System/IO/File.hpp"
#include "System/IO/FileInfo.hpp"
#include "System/IO/FileMode.hpp"
#include "System/IO/FileStream.hpp"
#include "System/IO/Stream.hpp"
#include "TMPro/TextAlignmentOptions.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/WaitForSeconds.hpp"
#include "Utils/FileUtils.hpp"
#include "beatsaber-hook/shared/utils/typedefs-object.hpp"
#include "bs-utils/shared/utils.hpp"
#include "custom-types/shared/types.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace HMUI;
using namespace UnityEngine;
using namespace ImageFactory::ViewControllers;
using namespace QuestUI::BeatSaberUI;
using namespace TMPro;

DEFINE_TYPE(ImageFactory::ViewControllers, ImageCreationViewController);

custom_types::Helpers::Coroutine waitForModal(HMUI::ModalView* modal) {
  co_yield reinterpret_cast<System::Collections::IEnumerator*>(
      CRASH_UNLESS(WaitForSeconds::New_ctor(0.5)));
  modal->Show(false, false, nullptr);
  co_return;
}

std::string FileSizeExtension(long size) {
  if (size > 1000000) return "MB";
  if (size > 1000)
    return "KB";
  else
    return "bytes";
}

int FileSizeDivisor(long size) {
  if (size > 1000000) return 1000000;
  if (size > 1000)
    return 1000;
  else
    return 1;
}

long GetFileSize(std::string filename, System::IO::FileStream* stream) {
  return stream->get_Length();
}

std::string removeTrailingZeros(std::string s, int amount) {
  for (int i = 0; i < amount + 1; i++) {
    s.pop_back();
  }
  return s;
}

std::vector<std::string> pictures;

void ImageCreationViewController::DidActivate(bool firstActivation,
                                              bool addedToHierarchy,
                                              bool screenSystemEnabling) {
  pictures = ImageFactory::FileUtils::getFiles(
      "/sdcard/ModData/com.beatgames.beatsaber/Mods/ImageFactory/Images/");
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
        topBarBG->get_transform(), "New Image", true);
    topBarTitle->set_fontSize(10);
    topBarTitle->set_alignment(TMPro::TextAlignmentOptions::Center);

    auto listBar =
        QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(get_transform());
    listBar->get_rectTransform()->set_anchoredPosition(Vector2(0.0f, 0.0f));
    auto listBarElement =
        listBar->GetComponent<UnityEngine::UI::LayoutElement*>();
    listBarElement->set_preferredWidth(20);
    listBarElement->set_preferredHeight(60);
    auto listBG =
        listBar->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
    listBG->ApplyBackground(il2cpp_utils::newcsstr("panel-top"));
    listBG->background->set_color(UnityEngine::Color(0.1f, 0.1f, 0.1f, 0.1f));

    UnityEngine::GameObject* list =
        QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(
            listBG->get_transform());

    HMUI::ModalView* createImage;
    UnityEngine::GameObject* createImageGO;
    HMUI::ImageView* imageDisplay;
    TMPro::TextMeshProUGUI* animText;
    TMPro::TextMeshProUGUI* widthDisplayText;
    TMPro::TextMeshProUGUI* heightText;
    TMPro::TextMeshProUGUI* fileSizeDisplayText;
    TMPro::TextMeshProUGUI* loadTimeText;
    UnityEngine::UI::Button* createButton;
    UnityEngine::UI::Button* cancelButton;

    for (auto& image : pictures) {
      UnityEngine::UI::HorizontalLayoutGroup* levelBarLayout =
          QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(
              list->get_transform());
      UnityEngine::GameObject* prefab = levelBarLayout->get_gameObject();

      levelBarLayout->set_childControlWidth(false);
      UnityEngine::UI::LayoutElement* levelBarLayoutElement =
          levelBarLayout->GetComponent<UnityEngine::UI::LayoutElement*>();
      levelBarLayoutElement->set_minHeight(10.0f);
      levelBarLayoutElement->set_minWidth(20.0f);
      Sprite* sprite = QuestUI::BeatSaberUI::FileToSprite(image.c_str());

      QuestUI::BeatSaberUI::CreateImage(levelBarLayoutElement->get_transform(),
                                        sprite, Vector2(2.0f, 0.0f),
                                        Vector2(10.0f, 2.0f));

      System::IO::FileStream* stream = System::IO::FileStream::New_ctor(
          il2cpp_utils::createcsstr(image.c_str()), System::IO::FileMode::Open);
      long fileSize = GetFileSize(image.c_str(), stream);
      QuestUI::BeatSaberUI::CreateText(
          levelBarLayoutElement->get_transform(),
          FileUtils::GetFileName(image.c_str(), false), true);
      levelBarLayoutElement->set_minWidth(1.0f);
      auto addBtn = QuestUI::BeatSaberUI::CreateUIButton(
          levelBarLayoutElement->get_transform(), "", Vector2(0.0f, 0.0f),
          Vector2(10.0f, 10.0f),
          [image, this, sprite, createImage, animText, widthDisplayText,
           heightText, fileSizeDisplayText, loadTimeText, createImageGO,
           imageDisplay, stream, fileSize, createButton,
           cancelButton]() mutable -> void {
            createImage = QuestUI::BeatSaberUI::CreateModal(
                get_transform(), UnityEngine::Vector2(70.0f, 50.0f),
                [](HMUI::ModalView* modal) {}, true);
            createImageGO =
                QuestUI::BeatSaberUI::CreateScrollableModalContainer(
                    createImage);
            imageDisplay = QuestUI::BeatSaberUI::CreateImage(
                createImage->get_transform(), sprite, Vector2(-18.0f, 8.0f),
                Vector2(30.0f, 30.0f));
            if (FileUtils::isGifFile(image.c_str())) {
              animText = QuestUI::BeatSaberUI::CreateText(
                  createImage->get_transform(), "Animated: Yes",
                  Vector2(30.0f, 17.0f));
            } else {
              animText = QuestUI::BeatSaberUI::CreateText(
                  createImage->get_transform(), "Animated: No",
                  Vector2(30.0f, 17.0f));
            }
            widthDisplayText = QuestUI::BeatSaberUI::CreateText(
                createImage->get_transform(),
                "Width: " +
                    removeTrailingZeros(
                        std::to_string(sprite->get_textureRect().get_width()),
                        6) +
                    "px",
                Vector2(30.0f, 11.0f));
            heightText = QuestUI::BeatSaberUI::CreateText(
                createImage->get_transform(),
                "Height: " +
                    removeTrailingZeros(
                        std::to_string(sprite->get_textureRect().get_height()),
                        6) +
                    "px",
                Vector2(30.0f, 5.0f));
            fileSizeDisplayText = QuestUI::BeatSaberUI::CreateText(
                createImage->get_transform(),
                "File Size: " +
                    removeTrailingZeros(
                        std::to_string(
                            round(fileSize / FileSizeDivisor(fileSize))),
                        6) +
                    " " + FileSizeExtension(fileSize),
                Vector2(30.0f, -1.0f));
            loadTimeText = QuestUI::BeatSaberUI::CreateText(
                createImage->get_transform(), "Load Time: 0 ms",
                Vector2(30.0f, -7.0f));
            createButton = QuestUI::BeatSaberUI::CreateUIButton(
                createImage->get_transform(), "CREATE", Vector2(14.0f, -17.0f),
                Vector2(30.0f, 10.0f),
                [&]() { this->createImageFunction(image.c_str()); });
            cancelButton = QuestUI::BeatSaberUI::CreateUIButton(
                createImage->get_transform(), "CANCEL", Vector2(-18.0f, -17.0f),
                Vector2(30.0f, 10.0f),
                [createImage]() { createImage->Hide(true, nullptr); });
            animText->set_fontSize(5.0f);
            widthDisplayText->set_fontSize(5.0f);
            heightText->set_fontSize(5.0f);
            fileSizeDisplayText->set_fontSize(5.0f);
            loadTimeText->set_fontSize(5.0f);
            createImage->Show(true, false, nullptr);
          });

      QuestUI::BeatSaberUI::CreateText(addBtn->get_transform(), "+")
          ->set_alignment(TMPro::TextAlignmentOptions::Center);
    }
  }
}

void ImageCreationViewController::set_createImageFunction(
    std::function<void(std::string)> createImage) {
  createImageFunction = createImage;
}
