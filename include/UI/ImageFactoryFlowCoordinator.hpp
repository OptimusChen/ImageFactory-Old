#pragma once
#include "HMUI/FlowCoordinator.hpp"
#include "HMUI/ViewController.hpp"
#include "UI/ImageFactoryViewController.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(
    ImageFactory, ImageFactoryFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, imageFactoryView);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, imageCreationView);
    DECLARE_INSTANCE_FIELD(HMUI::ViewController*, imageEditingView);
    DECLARE_OVERRIDE_METHOD(void, DidActivate,
                            il2cpp_utils::FindMethodUnsafe("HMUI",
                                                           "FlowCoordinator",
                                                           "DidActivate", 3),
                            bool firstActivation, bool addedToHierarchy,
                            bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(
        void, BackButtonWasPressed,
        il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator",
                                       "BackButtonWasPressed", 1),
        HMUI::ViewController* topViewController););