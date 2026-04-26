#include "Texture.h"

#include "include/core/SkBitmap.h"
#include "include/core/SkEncodedImageFormat.h"
#include "include/codec/SkCodec.h"

namespace PhiVideo {

    Texture::Texture(const std::string& path) {
        sk_sp<SkData> data = SkData::MakeFromFileName(path.c_str());
        m_Image = SkImage::MakeFromEncoded(data);
    }

}
