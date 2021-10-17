#include "Components/IFImage.hpp"

#include "GlobalNamespace/OVRInput.hpp"
#include "GlobalNamespace/PlayerVRControllersManager.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "HMUI/Touchable.hpp"
#include "Presenters/PresentorManager.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "Utils/FileUtils.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "beatsaber-hook/shared/utils/utils.h"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(ImageFactory::Components, IFImage);

using namespace UnityEngine;

bool isHolding = false;
float grabDist = 0.0f;
UnityEngine::Vector3 raycastPos;
UnityEngine::Quaternion raycastRot;
bool hasRendered = false;

custom_types::Helpers::Coroutine
ImageFactory::Components::IFImage::UpdateEveryTick() {
  while (!inSong) {
    if (screen) {
      x = screen->get_transform()->get_position().x;
      y = screen->get_transform()->get_position().y;
      z = screen->get_transform()->get_position().z;
      raycastRot = screen->get_transform()->get_rotation();
    }
    co_yield nullptr;
  }
  co_return;
}

void ImageFactory::Components::IFImage::Render() {
  if (screen) {
    UnityEngine::Object::Destroy(screen);
  }
  if (image) {
    UnityEngine::Object::Destroy(image);
  }
  screen = BeatSaberUI::CreateFloatingScreen(
      Vector2(scaleX * (width / 3), scaleY * (height / 3)), Vector3(x, y, z),
      Vector3(angleX, angleY, angleZ), 0.0f, false, true, 4);

  image = BeatSaberUI::CreateImage(
      screen->get_transform(), sprite, Vector2(x, y),
      Vector2(scaleX * (width / 3), scaleY * (height / 3)));
  GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(
      reinterpret_cast<custom_types::Helpers::enumeratorT*>(
          custom_types::Helpers::CoroutineHelper::New(UpdateEveryTick())));
}

void ImageFactory::Components::IFImage::Despawn() {
  if (inSong) {
    if (inSongScreen && inSongImage) {
      inSongScreen->SetActive(false);
      inSongImage->get_gameObject()->SetActive(false);
    }
  }
  if (screen) {
    screen->SetActive(false);
  }
  if (image) {
    image->get_gameObject()->SetActive(false);
  }
}

void ImageFactory::Components::IFImage::Spawn() {
  il2cpp_utils::getLogger().info("[ImageFactory] Spawning Image");
  if (inSong) {
    il2cpp_utils::getLogger().info(
        "[ImageFactory] Deleting existing images and screens");
    UnityEngine::Object::Destroy(inSongImage);
    UnityEngine::Object::Destroy(inSongScreen);

    il2cpp_utils::getLogger().info("[ImageFactory] creating floating screen");
    inSongScreen = BeatSaberUI::CreateFloatingScreen(
        Vector2(scaleX * (width / 3), scaleY * (height / 3)), Vector3(x, y, z),
        raycastRot.get_eulerAngles(), 0.0f, true, true, 4);
    inSongScreen->SetActive(true);
    il2cpp_utils::getLogger().info("[ImageFactory] Creating Image");

    inSongImage = BeatSaberUI::CreateImage(
        inSongScreen->get_transform(), sprite, Vector2(x, y),
        Vector2(scaleX * (width / 3), scaleY * (height / 3)));
    inSongImage->get_gameObject()->SetActive(true);
    il2cpp_utils::getLogger().info("[ImageFactory] done");
  }
  if (screen) {
    screen->SetActive(true);
  }
  if (image) {
    image->get_gameObject()->SetActive(true);
  }
}

void ImageFactory::Components::IFImage::Update() {
  if (image) {
    UnityEngine::Object::Destroy(image);
  }
  image = BeatSaberUI::CreateImage(
      screen->get_transform(), sprite, Vector2(x, y),
      Vector2(scaleX * (width / 3), scaleY * (height / 3)));
  if (!enabled) {
    screen->SetActive(false);
    image->get_gameObject()->SetActive(false);
  } else {
    screen->SetActive(true);
    image->get_gameObject()->SetActive(true);
  }
}

void ImageFactory::Components::IFImage::ctor(UnityEngine::Sprite* sprite,
                                             Il2CppString* path) {
  this->sprite = sprite;
  this->width = sprite->get_textureRect().get_width();
  this->height = sprite->get_textureRect().get_height();
  this->x = 0.0f;
  this->y = 3.0f;
  this->z = 5.0f;
  this->name = FileUtils::GetFileName(to_utf8(csstrtostr(path)), false);
  raycastPos = Vector3(x, y, z);
  this->angleX = raycastRot.x;
  this->angleY = raycastRot.y;
  this->angleZ = raycastRot.z;
  this->enabled = true;
  scaleX = 1.0f;
  scaleY = 1.0f;
  this->presentationoption = "Everywhere";
  inSong = false;
}
