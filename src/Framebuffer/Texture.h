#pragma once

#include "Base/Base.h"
#include "Base/Maths.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkSurface.h"
#include "include/core/SkFont.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkStream.h"
#include "include/encode/SkPngEncoder.h"

#include <fstream>

namespace PhiVideo {

    class Texture {
    public:
        Texture(const std::string& path);
        ~Texture() = default;

        int Width() const { return m_Width; }
        int Height() const { return m_Height; }

        sk_sp<SkImage> GetImage() const { return m_Image; }

        bool IsValid() const { return m_Image != nullptr; }

    private:
        int m_Width = 0;
        int m_Height = 0;
        sk_sp<SkImage> m_Image;
    };

}
