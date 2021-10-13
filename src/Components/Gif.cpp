#include "Components/Gif.hpp"

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

DEFINE_TYPE(ImageFactory::Components, Gif);

void ImageFactory::Components::Gif::Update() {}

void ImageFactory::Components::Gif::Initialize(std::string p,
                                               UnityEngine::Transform* t) {
  Update();
}

void ImageFactory::Components::Gif::ctor() {}