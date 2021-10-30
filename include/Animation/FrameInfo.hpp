#pragma once

#include <string_view>

#include "Animation/FrameInfo.hpp"
#include "UnityEngine/Color32.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"

DECLARE_CLASS_CODEGEN(ImageFactory::Animations, FrameInfo,
                      UnityEngine::MonoBehaviour, int width;
                      int height; int delay;
                      std::vector<UnityEngine::Color32*> colors;

                      DECLARE_CTOR(ctor, int width, int height);
                      DECLARE_SIMPLE_DTOR();)