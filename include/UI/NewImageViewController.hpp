#pragma once
#include "Components/IFImage.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(
    ImageFactory::ViewControllers, NewImageViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate,
                            il2cpp_utils::FindMethodUnsafe("HMUI",
                                                           "ViewController",
                                                           "DidActivate", 3),
                            bool firstActivation, bool addedToHierarchy,
                            bool screenSystemEnabling);
    public
    : std::string path;
    void Initialize(Il2CppString* str);
    DECLARE_INSTANCE_FIELD(ImageFactory::Components::IFImage*, image););