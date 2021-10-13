#include "Utils/FileUtils.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

std::vector<std::string> ImageFactory::FileUtils::getFiles(
    std::string_view path) {
  std::vector<std::string> directories;
  if (!std::filesystem::is_directory(path)) return directories;
  std::error_code ec;
  auto directory_iterator = std::filesystem::directory_iterator(
      path, std::filesystem::directory_options::none, ec);
  if (ec) {
  }
  for (const auto& entry : directory_iterator) {
    if (entry.is_regular_file()) directories.push_back(entry.path().string());
  }
  return directories;
}

std::string ImageFactory::FileUtils::RemoveExtension(std::string path) {
  if (path.find_last_of(".") != std::string::npos)
    return path.substr(0, path.find_last_of("."));
  return path;
}

std::string ImageFactory::FileUtils::GetFileName(std::string path,
                                                 bool removeExtension) {
  std::string result = "";
  if (path.find_last_of("/") != std::string::npos)
    result = path.substr(path.find_last_of("/") + 1);
  else
    result = path;
  if (removeExtension) result = RemoveExtension(result);
  return result;
  ;
}

bool ImageFactory::FileUtils::isImageFile(std::string path) {
  if (path.ends_with(".png") || path.ends_with(".jpg")) {
    return true;
  }
  return false;
}

bool ImageFactory::FileUtils::isGifFile(std::string path) {
  if (path.ends_with(".gif")) {
    return true;
  }
  return false;
}

bool ImageFactory::FileUtils::isJsonFile(std::string path) {
  if (path.ends_with(".json")) {
    return true;
  }
  return false;
}