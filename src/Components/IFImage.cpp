#include "Components/IFImage.hpp"

DEFINE_TYPE(ImageFactory::Components, IFImage);

void ImageFactory::Components::IFImage::ctor(UnityEngine::Sprite* sprite,
                                             System::TimeSpan timeSpan) {
  this->loadTime = timeSpan;
  this->sprite = sprite;
}
