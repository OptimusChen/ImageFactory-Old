// #include "Animation/Gif/GIFUnityDecoder.hpp"

// #include "Animation/AnimationInfo.hpp"
// #include "System/Collections/IEnumerator.hpp"
// #include "System/Threading/Tasks/Task.hpp"

// using namespace System::Collections;
// using namespace ImageFactory::Animations;

// static custom_types::Helpers::Coroutine
// ImageFactory::Animations::Gif::GIFUnityDecoder::Process(
//     std::vector<std::byte> gifData,
//     std::function<void(Animations::AnimationInfo*)> callback) {
//   AnimationInfo* animationInfo = new AnimationInfo();
//   System::Threading::Tasks::Task::Run(
//       ImageFactory::Animations::Gif::GIFUnityDecoder::ProcessingThread(
//           gifData, animationInfo));
//   while (!animationInfo->initialized) {
//     co_yield nullptr;
//   }
//   callback(animationInfo);
//   co_return;
// }

// static void ImageFactory::Animations::Gif::GIFUnityDecoder::ProcessingThread(
//     std::vector<std::byte> gifData, AnimationInfo* animationInfo) {
//   Il2CppObject* gifImage =
//       il2cpp_utils::RunMethod(CRASH_UNLESS(il2cpp_utils::FindMethodUnsafe(
//           "System::Drawing", "Image", "FromStream", 1)));
// }
