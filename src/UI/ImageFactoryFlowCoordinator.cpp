#include "UI/ImageFactoryFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "Presenters/PresentorManager.hpp"
#include "UI/EditImageViewController.hpp"
#include "UI/ImageCreationViewController.hpp"
#include "UI/ImageEditingViewController.hpp"
#include "UI/ImageFactoryViewController.hpp"
#include "UI/NewImageViewController.hpp"
#include "include/PluginConfig.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace ImageFactory;
using namespace ImageFactory::Presentors;

DEFINE_TYPE(ImageFactory, ImageFactoryFlowCoordinator);

void ImageFactoryFlowCoordinator::DidActivate(bool firstActivation,
                                              bool addedToHierarchy,
                                              bool screenSystemEnabling) {
  if (firstActivation) {
    this->SetTitle(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>(
                       "IMAGEFACTORY"),
                   HMUI::ViewController::AnimationDirection::Horizontal);
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

    this->imageCreationViewController = reinterpret_cast<
        ImageFactory::ViewControllers::ImageCreationViewController*>(
        imageCreationView);

    this->imageEditingViewController = reinterpret_cast<
        ImageFactory::ViewControllers::ImageEditingViewController*>(
        imageEditingView);

    std::function<void(std::string)> addImage = std::bind(
        &ImageFactoryFlowCoordinator::AddedImage, this, std::placeholders::_1);
    std::function<void(IFImage*)> editImage = std::bind(
        &ImageFactoryFlowCoordinator::EditImage, this, std::placeholders::_1);
    std::function<void(IFImage*)> deleteImage = std::bind(
        &ImageFactoryFlowCoordinator::DeleteImage, this, std::placeholders::_1);
    imageCreationViewController->set_createImageFunction(addImage);
    imageEditingViewController->set_editImageFunction(editImage);
    imageEditingViewController->set_deleteImageFunction(deleteImage);

    ImageFactoryFlowCoordinator::ProvideInitialViewControllers(
        imageFactoryView, imageCreationViewController,
        imageEditingViewController, nullptr, nullptr);
  }
}
void ImageFactoryFlowCoordinator::DeleteImage(
    ImageFactory::Components::IFImage* image) {
  this->imageEditingViewController->Refresh();
  this->SetRightScreenViewController(
      QuestUI::BeatSaberUI::CreateViewController<HMUI::ViewController*>(),
      HMUI::ViewController::AnimationType::In);
  ConfigDocument& configDoc = getPluginConfig().config->config;
  if (configDoc.HasMember(image->internalName)) {
    configDoc.RemoveMember(image->internalName.c_str());
    getPluginConfig().Amount.SetValue(getPluginConfig().Amount.GetValue() - 1);
    getPluginConfig().Images.SetValue(to_utf8(csstrtostr(
        il2cpp_utils::createcsstr(getPluginConfig().Images.GetValue())
            ->Replace(il2cpp_utils::createcsstr("/" + image->internalName),
                      Il2CppString::_get_Empty()))));
    getPluginConfig().config->Write();
    getPluginConfig().config->Reload();
    // PresentorManager::ClearInfo(image);
    image->Despawn();
    image->x = 1000.0f;
    image->y = 1000.0f;
    image->z = 1000.0f;
    image->enabled = false;
    // UnityEngine::GameObject::Destroy(image);
  }

  this->SetRightScreenViewController(imageEditingViewController,
                                     HMUI::ViewController::AnimationType::In);
}

void ImageFactoryFlowCoordinator::EditImage(
    ImageFactory::Components::IFImage* image) {
  ImageFactory::ViewControllers::EditImageViewController* viewController =
      reinterpret_cast<ImageFactory::ViewControllers::EditImageViewController*>(
          QuestUI::BeatSaberUI::CreateViewController<
              ImageFactory::ViewControllers::EditImageViewController*>());
  viewController->Initialize(image);
  viewController->leaveViewController = [this]() {
    this->SetLeftScreenViewController(imageCreationViewController,
                                      HMUI::ViewController::AnimationType::In);
    this->SetRightScreenViewController(imageEditingViewController,
                                       HMUI::ViewController::AnimationType::In);
    this->ReplaceTopViewController(
        imageFactoryView, this, this, nullptr,
        HMUI::ViewController::AnimationType::In,
        HMUI::ViewController::AnimationDirection::Horizontal);
    PresentorManager::SpawnInMenu();
  };
  this->SetLeftScreenViewController(
      QuestUI::BeatSaberUI::CreateViewController<HMUI::ViewController*>(),
      HMUI::ViewController::AnimationType::In);
  this->SetRightScreenViewController(
      QuestUI::BeatSaberUI::CreateViewController<HMUI::ViewController*>(),
      HMUI::ViewController::AnimationType::In);
  PresentorManager::DespawnAll();
  this->ReplaceTopViewController(
      viewController, this, this, nullptr,
      HMUI::ViewController::AnimationType::In,
      HMUI::ViewController::AnimationDirection::Horizontal);
  imageEditingViewController->Refresh();
}

void ImageFactoryFlowCoordinator::AddedImage(std::string s) {
  il2cpp_utils::getLogger().info("[ImageFactory] Creating ViewController");
  ImageFactory::ViewControllers::NewImageViewController* viewController =
      reinterpret_cast<ImageFactory::ViewControllers::NewImageViewController*>(
          QuestUI::BeatSaberUI::CreateViewController<
              ImageFactory::ViewControllers::NewImageViewController*>());
  il2cpp_utils::getLogger().info(
      "[ImageFactory] Finished Creating ViewController");
  if (!viewController) {
    il2cpp_utils::getLogger().info("[ImageFactory] Viewcontroller is null");
    return;
  }
  viewController->Initialize(il2cpp_utils::createcsstr(s));
  viewController->leaveViewController = [this]() {
    this->SetLeftScreenViewController(imageCreationViewController,
                                      HMUI::ViewController::AnimationType::In);
    this->SetRightScreenViewController(imageEditingViewController,
                                       HMUI::ViewController::AnimationType::In);
    this->ReplaceTopViewController(
        imageFactoryView, this, this, nullptr,
        HMUI::ViewController::AnimationType::In,
        HMUI::ViewController::AnimationDirection::Horizontal);
    PresentorManager::SpawnInMenu();
  };
  il2cpp_utils::getLogger().info(
      "[ImageFactory] transitioning view controllers");
  this->SetLeftScreenViewController(
      QuestUI::BeatSaberUI::CreateViewController<HMUI::ViewController*>(),
      HMUI::ViewController::AnimationType::In);
  this->SetRightScreenViewController(
      QuestUI::BeatSaberUI::CreateViewController<HMUI::ViewController*>(),
      HMUI::ViewController::AnimationType::In);
  this->ReplaceTopViewController(
      viewController, this, this, nullptr,
      HMUI::ViewController::AnimationType::In,
      HMUI::ViewController::AnimationDirection::Horizontal);
  PresentorManager::DespawnAll();
  imageEditingViewController->Refresh();
}

void ImageFactoryFlowCoordinator::BackButtonWasPressed(
    HMUI::ViewController* topView) {
  PresentorManager::DespawnAll();
  PresentorManager::SpawnInMenu();
  this->parentFlowCoordinator->DismissFlowCoordinator(
      this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr,
      false);
}
