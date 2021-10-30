#pragma once

#include <string_view>

#include "Animation/FrameInfo.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"

DECLARE_CLASS_CODEGEN(ImageFactory::Animations, AnimationInfo,
                      UnityEngine::MonoBehaviour,
                      std::vector<ImageFactory::Animations::FrameInfo*> frames;
                      int frameCount; bool initialized; DECLARE_CTOR(ctor);
                      DECLARE_SIMPLE_DTOR();)