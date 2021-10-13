#pragma once

#include "Components/IFImage.hpp"
#include "System/IO/DirectoryInfo.hpp"
#include "UI/ImageFactoryFlowCoordinator.hpp"
#include "Zenject/IInitializable.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "modloader/shared/modloader.hpp"

DECLARE_CLASS_CODEGEN(
    ImageFactory::Managers, MetaDataStore, Zenject::IInitializable,
    DECLARE_INSTANCE_METHOD(void, Initialize);
    std::unordered_map<std::string, ImageFactory::Components::IFImage>
        AllMetaData();
    Configuration & config; System::IO::DirectoryInfo * saveDirectory;
    std::unordered_map<std::string, ImageFactory::Components::IFImage>
        metaDataStore;
    std::unordered_set<std::string> AllowedExtensions; DECLARE_CTOR(ctor);)