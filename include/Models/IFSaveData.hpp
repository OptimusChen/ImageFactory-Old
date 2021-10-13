#pragma once

#include <string_view>

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "questui/shared/QuestUI.hpp"

DECLARE_CLASS_CODEGEN(OurNamespace, OurClass, UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(bool, Enabled);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Vector2, Size);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Vector3, Position);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Quaternion, Rotation);
                      std::string Name; std::string LocalPath;)