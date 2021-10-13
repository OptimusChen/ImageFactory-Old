#pragma once

#include <string>

#include "GlobalNamespace/PlayerVRControllersManager.hpp"
#include "UnityEngine/Vector3.hpp"
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/types.hpp"

namespace ImageFactory {
namespace ControllerUtils {
int getSelectedController();
UnityEngine::Vector3 getControllerLocation();

}  // namespace ControllerUtils
}  // namespace ImageFactory