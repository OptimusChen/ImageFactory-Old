#pragma once

#include <string_view>

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;
using namespace std;

DECLARE_CLASS_CODEGEN(ImageFactory::Components, Gif, UnityEngine::MonoBehaviour,
                      std::string path;
                      DECLARE_INSTANCE_METHOD(void, Update);
                      void Initialize(std::string p, UnityEngine::Transform* t);
                      DECLARE_CTOR(ctor); DECLARE_SIMPLE_DTOR();
                      DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, parent);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, sprite);)
