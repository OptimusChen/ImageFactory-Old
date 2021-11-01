#include "AnimationInfo.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "custom-types/shared/coroutine.hpp"

using namespace System::Collections;

namespace ImageFactory {
namespace Animations {
namespace Gif {

class GIFUnityDecoder {
 public:
  static custom_types::Helpers::Coroutine Process(
      std::vector<std::byte> gifData,
      std::function<void(Animations::AnimationInfo*)> callback);
  static void ProcessingThread(std::vector<std::byte> gifData,
                               AnimationInfo* animationInfo);
}
}  // namespace Gif
}  // namespace Animations
}  // namespace ImageFactory