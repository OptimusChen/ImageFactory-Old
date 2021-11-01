#include "AnimationInfo.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "custom-types/shared/coroutine.hpp"

namespace ImageFactory {
namespace Animations {

class GifData {
 public:
  std::byte m_sig0, m_sig1, m_sig2;
  // Version
  std::byte m_ver0, m_ver1, m_ver2;
  // Logical Screen Width
  ushort m_logicalScreenWidth;
  // Logical Screen Height
  ushort m_logicalScreenHeight;
  // Global Color Table Flag
  bool m_globalColorTableFlag;
  // Color Resolution
  int m_colorResolution;
  // Sort Flag
  bool m_sortFlag;
  // Size of Global Color Table
  int m_sizeOfGlobalColorTable;
  // Background Color Index
  std::byte m_bgColorIndex;
  // Pixel Aspect Ratio
  std::byte m_pixelAspectRatio;
  // Global Color Table
  std::vector<std::vector<std::byte>> m_globalColorTable;
  // ImageBlock
  std::vector<ImageBlock> m_imageBlockList;
  // GraphicControlExtension
  std::vector<GraphicControlExtension> m_graphicCtrlExList;
  // Comment Extension
  std::vector<CommentExtension> m_commentExList;
  // Plain Text Extension
  std::vector<PlainTextExtension> m_plainTextExList;
  // Application Extension
  ApplicationExtension m_appEx;
  // Trailer
  std::byte m_trailer;
  std::string signature;
  std::string version;

  void Dump();
  std::string getSignature();
  std::string getVersion();
}
}  // namespace Animations
}  // namespace ImageFactory