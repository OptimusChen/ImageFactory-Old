#pragma once
#include "Components/IFImage.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"
#include "main.hpp"

DECLARE_CLASS_CODEGEN(
    ImageFactory::ViewControllers, NewImageViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate,
                            il2cpp_utils::FindMethodUnsafe("HMUI",
                                                           "ViewController",
                                                           "DidActivate", 3),
                            bool firstActivation, bool addedToHierarchy,
                            bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, DidDeactivate,
                            il2cpp_utils::FindMethodUnsafe("HMUI",
                                                           "ViewController",
                                                           "DidDeactivate", 2),
                            bool removedFromHierarchy,
                            bool screenSystemEnabling);
    DECLARE_INSTANCE_FIELD(bool, hasSaved); public
    : std::string path;
    std::function<void()> leaveViewController;
    void Initialize(Il2CppString* str);
    DECLARE_INSTANCE_FIELD(ImageFactory::Components::IFImage*, image););