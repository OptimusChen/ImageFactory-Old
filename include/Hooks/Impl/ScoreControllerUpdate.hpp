#pragma once

#include "Hooks/IHook.hpp"
#include "main.hpp"
using namespace ImageFactory;

namespace ImageFactory::Hooks {
class ScoreControllerUpdate : IHook {
 public:
  void AddHooks() override;
  explicit ScoreControllerUpdate(const std::string& name) : IHook(name) {}
};
}  // namespace ImageFactory::Hooks