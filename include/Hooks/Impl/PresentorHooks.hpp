#pragma once

#include "Hooks/IHook.hpp"
#include "main.hpp"
using namespace ImageFactory;

namespace ImageFactory::Hooks {
class PresentorHooks : IHook {
 public:
  void AddHooks() override;
  explicit PresentorHooks(const std::string& name) : IHook(name) {}
};
}  // namespace ImageFactory::Hooks