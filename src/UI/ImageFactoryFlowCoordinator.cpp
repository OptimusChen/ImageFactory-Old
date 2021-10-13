#include "UI/ImageFactoryFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "UI/ImageCreationViewController.hpp"
#include "UI/ImageEditingViewController.hpp"
#include "UI/ImageFactoryViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace ImageFactory;

DEFINE_TYPE(ImageFactory, ImageFactoryFlowCoordinator);

void ImageFactoryFlowCoordinator::DidActivate(bool firstActivation,
                                              bool addedToHierarchy,
                                              bool screenSystemEnabling) {
  if (firstActivation) {
    this->SetTitle(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>(
                       "IMAGEFACTORY"),
                   HMUI::ViewController::AnimationDirection::Vertical);
    this->showBackButton = true;
    if (!this->imageFactoryView) {
      this->imageFactoryView = QuestUI::BeatSaberUI::CreateViewController<
          ImageFactory::ViewControllers::ImageFactoryViewController*>();
    }
    if (!this->imageCreationView) {
      this->imageCreationView = QuestUI::BeatSaberUI::CreateViewController<
          ImageFactory::ViewControllers::ImageCreationViewController*>();
    }
    if (!this->imageEditingView) {
      this->imageEditingView = QuestUI::BeatSaberUI::CreateViewController<
          ImageFactory::ViewControllers::ImageEditingViewController*>();
    }

    ImageFactoryFlowCoordinator::ProvideInitialViewControllers(
        imageFactoryView, imageCreationView, imageEditingView, nullptr,
        nullptr);
  }
}

void ImageFactoryFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topView) {
  this->parentFlowCoordinator->DismissFlowCoordinator(
      this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr,
      false);
}
