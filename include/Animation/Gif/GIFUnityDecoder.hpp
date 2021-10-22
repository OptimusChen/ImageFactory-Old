#include "System/Collections/IEnumerator.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "custom-types/shared/macros.hpp"

namespace ImageFactory {
namespace Animations {
namespace Gif {
class GIFUnityDecoder {
 public:
  static System::Collections::IEnumerator Process(
      byte[] gifData, std::function<void()> callback);
  static void ProcessingThread(byte[] gifData);
};
}  // namespace Gif
}  // namespace Animations
}  // namespace ImageFactory