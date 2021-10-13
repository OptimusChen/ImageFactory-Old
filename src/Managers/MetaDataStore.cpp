#include "Managers/MetaDataStore.hpp"

#include "Components/IFImage.hpp"
#include "System/IO/Directory.hpp"
#include "System/IO/FileInfo.hpp"
#include "Utils/FileUtils.hpp"

using namespace ImageFactory;

void ImageFactory::Managers::MetaDataStore::ctor() {
  saveDirectory = System::IO::DirectoryInfo::New_ctor(il2cpp_utils::createcsstr(
      "/sdcard/ModData/com.beatgames.beatsaber/Mods/ImageFactory/"
      "Images/"));
  metaDataStore = {};
  AllowedExtensions = {".png", ".apng", ".gif", ".jpg", ".jpeg"};
}

void ImageFactory::Managers::MetaDataStore::Initialize() {
  if (!this->saveDirectory->get_Exists()) {
    this->saveDirectory->Create();
  }

  ::Array<::Il2CppString*>* files =
      System::IO::Directory::GetFiles(saveDirectory->FullPath);
  for (int i = 0; i < files->get_Length(); i++) {
    Il2CppString* file = files->get(i);
    System::IO::FileInfo* info = new System::IO::FileInfo(file);
    if (FileUtils::isImageFile(to_utf8(csstrtostr(info->FullPath)))) {
      auto trimmed = info->get_FullName()->Replace(
          saveDirectory->get_FullName(), Il2CppString::_get_Empty());
    }
  }
}

std::unordered_map<std::string, ImageFactory::Components::IFImage>
ImageFactory::Managers::MetaDataStore::AllMetaData() {
  return metaDataStore;
}