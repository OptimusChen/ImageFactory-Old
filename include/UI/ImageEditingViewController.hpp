#pragma once
#include "Components/IFImage.hpp"
#include "HMUI/ViewController.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(
    ImageFactory::ViewControllers, ImageEditingViewController,
    HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate,
                            il2cpp_utils::FindMethodUnsafe("HMUI",
                                                           "ViewController",
                                                           "DidActivate", 3),
                            bool firstActivation, bool addedToHierarchy,
                            bool screenSystemEnabling);
    DECLARE_INSTANCE_FIELD(bool, refresh);
    DECLARE_INSTANCE_METHOD(void, Refresh); public
    : std::function<void(ImageFactory::Components::IFImage*)>
        editImageFunction;
    custom_types::Helpers::Coroutine SetUpListElements(UnityEngine::GameObject *
                                                       parent);
    void set_editImageFunction(
        std::function<void(ImageFactory::Components::IFImage*)>
            editImageFunction);
    std::function<void(ImageFactory::Components::IFImage*)> deleteImageFunction;
    void set_deleteImageFunction(
        std::function<void(ImageFactory::Components::IFImage*)>
            deleteImageFunction););