#pragma once

#include "HMUI/ImageView.hpp"
#include "HMUI/Touchable.hpp"
#include "System/TimeSpan.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Vector3.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;
using namespace std;

DECLARE_CLASS_CODEGEN(
    ImageFactory::Components, IFImage, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Render);
    DECLARE_INSTANCE_METHOD(void, Spawn);
    DECLARE_INSTANCE_METHOD(void, Despawn);
    DECLARE_INSTANCE_METHOD(void, Update); DECLARE_INSTANCE_FIELD(float, width);
    DECLARE_INSTANCE_FIELD(float, height); DECLARE_INSTANCE_FIELD(float, x);
    DECLARE_INSTANCE_FIELD(float, y); DECLARE_INSTANCE_FIELD(float, z);
    DECLARE_INSTANCE_FIELD(float, angleX);
    DECLARE_INSTANCE_FIELD(float, angleY);
    DECLARE_INSTANCE_FIELD(float, angleZ);
    DECLARE_INSTANCE_FIELD(float, scaleX);
    DECLARE_INSTANCE_FIELD(float, scaleY); DECLARE_INSTANCE_FIELD(bool, inSong);
    DECLARE_INSTANCE_FIELD(HMUI::Touchable*, collider);
    DECLARE_INSTANCE_FIELD(UnityEngine::Quaternion*, rot);
    DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, sprite);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, screen);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, image);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, inSongScreen);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, inSongImage);
    DECLARE_INSTANCE_FIELD(Array<VRUIControls::VRPointer*>*, pointerArray);
    DECLARE_CTOR(ctor, UnityEngine::Sprite* sprite, Il2CppString* path); public
    : std::string name;
    std::string fileName; std::string path; std::string presentationoption;
    bool enabled; custom_types::Helpers::Coroutine UpdateEveryTick();)
