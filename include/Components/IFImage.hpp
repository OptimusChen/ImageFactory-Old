#pragma once

#include "System/TimeSpan.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/SpriteRenderer.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Vector3.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "questui/shared/QuestUI.hpp"

using namespace QuestUI;
using namespace std;

DECLARE_CLASS_CODEGEN(ImageFactory::Components, IFImage,
                      UnityEngine::MonoBehaviour,
                      DECLARE_INSTANCE_FIELD(int, width);
                      DECLARE_INSTANCE_FIELD(int, height);
                      DECLARE_INSTANCE_FIELD(UnityEngine::Sprite*, sprite);
                      DECLARE_INSTANCE_FIELD(System::TimeSpan, loadTime);
                      DECLARE_CTOR(ctor, UnityEngine::Sprite* sprite,
                                   System::TimeSpan timespan);
                      DECLARE_SIMPLE_DTOR();)
