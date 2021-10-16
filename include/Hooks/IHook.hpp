#pragma once

#include <string>
#include <vector>

#include "main.hpp"


namespace ImageFactory {

/*
 * DECLARE IHOOK INTERFACE CLASS
 */

class IHook {
 private:
  static std::vector<IHook*> hooks;

 protected:
  std::string name;

 public:
  static bool InstallHooks();

  explicit IHook(const std::string& name);

  virtual void AddHooks();
};
}  // namespace ImageFactory