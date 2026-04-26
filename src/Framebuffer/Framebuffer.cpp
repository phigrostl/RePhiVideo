#include "Framebuffer.h"

namespace PhiVideo {

    static Vec3 SkColorToVec3(SkColor color) {
        float r = SkColorGetR(color) / 255.0f;
        float g = SkColorGetG(color) / 255.0f;
        float b = SkColorGetB(color) / 255.0f;
        return Vec3(r, g, b);
    }

    static SkColor Vec3ToSkColor(const Vec3& color) {
        uint8_t r = (uint8_t)(color.X * 255.0f);
        uint8_t g = (uint8_t)(color.Y * 255.0f);
        uint8_t b = (uint8_t)(color.Z * 255.0f);
        return SkColorSetARGB(255, r, g, b);
    }

    static Vec4 SkColorToVec4(SkColor color) {
        float r = SkColorGetR(color) / 255.0f;
        float g = SkColorGetG(color) / 255.0f;
        float b = SkColorGetB(color) / 255.0f;
        float a = SkColorGetA(color) / 255.0f;
        return Vec4(r, g, b, a);
    }

    static SkColor Vec4ToSkColor(Vec4& color) {
        uint8_t r = (uint8_t)(color.X * 255.0f);
        uint8_t g = (uint8_t)(color.Y * 255.0f);
        uint8_t b = (uint8_t)(color.Z * 255.0f);
        uint8_t a = (uint8_t)(color.W * 255.0f);
        return SkColorSetARGB(a, r, g, b);
    }

    Framebuffer::Framebuffer(const int width, const int height)
        : m_Width(width), m_Height(height){
        Init();
    }

    Framebuffer::~Framebuffer() {
        Terminate();
    }

    void Framebuffer::Init() {
        m_Ii = SkImageInfo::Make(m_Width, m_Height, kBGRA_8888_SkColorType, kPremul_SkAlphaType);
        m_Bitmap.allocPixels(m_Ii, m_Ii.minRowBytes());
        m_Font = SkFont(SkTypeface::MakeFromName("Source Han Sans CN", SkFontStyle::Normal()));
        m_Canvas = new SkCanvas(m_Bitmap);
    }

    void Framebuffer::Terminate() {
        delete m_Canvas;
    }

    void Framebuffer::SetColor(const int x, const int y, const Vec4& c) {
        if (x < 0 || y < 0 || x >= m_Bitmap.width() || y >= m_Bitmap.height()) return;

        uint8_t r = static_cast<uint8_t>(c.X * 255.0f + 0.5f);
        uint8_t g = static_cast<uint8_t>(c.Y * 255.0f + 0.5f);
        uint8_t b = static_cast<uint8_t>(c.Z * 255.0f + 0.5f);
        uint8_t a = static_cast<uint8_t>(c.W * 255.0f + 0.5f);

        uint32_t* dst = m_Bitmap.getAddr32(x, y);

        if (a == 255) {
            *dst = SkColorSetARGB(a, r, g, b);
            return;
        }

        uint32_t dstColor = *dst;

        uint8_t dstA = SkColorGetA(dstColor);
        uint8_t dstR = SkColorGetR(dstColor);
        uint8_t dstG = SkColorGetG(dstColor);
        uint8_t dstB = SkColorGetB(dstColor);

        float alpha = a / 255.0f;
        float invAlpha = 1.0f - alpha;

        uint8_t outA = static_cast<uint8_t>(a + dstA * invAlpha + 0.5f);
        uint8_t outR = static_cast<uint8_t>(r * alpha + dstR * invAlpha + 0.5f);
        uint8_t outG = static_cast<uint8_t>(g * alpha + dstG * invAlpha + 0.5f);
        uint8_t outB = static_cast<uint8_t>(b * alpha + dstB * invAlpha + 0.5f);

        *dst = SkColorSetARGB(outA, outR, outG, outB);
    }

    Vec4 Framebuffer::GetColor(const int x, const int y) {
        if (x < 0 || y < 0 || x >= m_Bitmap.width() || y >= m_Bitmap.height()) return Vec4(0, 0, 0, 0);

        SkColor color = *m_Bitmap.getAddr32(x, y);

        float r = SkColorGetR(color) / 255.0f;
        float g = SkColorGetG(color) / 255.0f;
        float b = SkColorGetB(color) / 255.0f;
        float a = SkColorGetA(color) / 255.0f;

        return Vec4(r, g, b, a);
    }

    unsigned char* Framebuffer::GetPixelData() {
        return reinterpret_cast<unsigned char*>(m_Bitmap.getPixels());
    }

    void Framebuffer::ToPNG(const std::string& path) {
        if (!m_Bitmap.getPixels())  return;
        SkFILEWStream stream(path.c_str());
        SkPngEncoder::Encode(&stream, m_Bitmap.pixmap(), {});
    }

    void Framebuffer::DrawTexture(float x, float y, const Texture* texture, float w, float h, float rotation, Vec4 color, float ox, float oy) {
        if (!texture || !m_Bitmap.getPixels()) return;

        sk_sp<SkImage> img = texture->GetImage();
        int imgW = img->width();
        int imgH = img->height();

        if (h < 0) {
            h = w * (float)imgH / (float)imgW;
        }

        SkColor skColor = SkColorSetARGB(
            (uint8_t)(color.W * 255.0f + 0.5f),
            (uint8_t)(color.X * 255.0f + 0.5f),
            (uint8_t)(color.Y * 255.0f + 0.5f),
            (uint8_t)(color.Z * 255.0f + 0.5f)
        );

        SkPaint paint;
        paint.setColor(skColor);
        paint.setBlendMode(SkBlendMode::kSrcOver);
        paint.setAntiAlias(true);

        SkRect dst = SkRect::MakeXYWH(x - w * ox, y - h * oy, w, h);

        m_Canvas->save();
        if (rotation != 0.0f) {
            m_Canvas->rotate(-rotation, x, y);
        }

        m_Canvas->drawImageRect(img, dst, SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone), &paint);
        m_Canvas->restore();
    }

    void Framebuffer::DrawRect(float x, float y, float w, float h, const Vec4& color, float rotation) {
        if (!m_Bitmap.getPixels()) return;

        SkColor skColor = SkColorSetARGB(
            static_cast<uint8_t>(color.W * 255.0f + 0.5f),
            static_cast<uint8_t>(color.X * 255.0f + 0.5f),
            static_cast<uint8_t>(color.Y * 255.0f + 0.5f),
            static_cast<uint8_t>(color.Z * 255.0f + 0.5f)
        );

        SkPaint paint;
        paint.setColor(skColor);
        paint.setBlendMode(SkBlendMode::kSrcOver);
        paint.setAntiAlias(true);
        paint.setStyle(SkPaint::kFill_Style);

        SkRect rect = SkRect::MakeXYWH(x, y, w, h);

        m_Canvas->save();

        if (rotation != 0.0f) {
            m_Canvas->rotate(-rotation, x, y);
        }

        m_Canvas->drawRect(rect, paint);

        m_Canvas->restore();
    }

    void Framebuffer::DrawTextTTF(float x, float y, const std::string& text, float fontSize, const Vec4& color, float rotation, float ox, float oy) {
        if (!m_Canvas || text.empty()) return;

        SkFont font = m_Font;
        font.setSize(fontSize);

        SkColor skColor = SkColorSetARGB(
            static_cast<uint8_t>(color.W * 255.0f + 0.5f),
            static_cast<uint8_t>(color.X * 255.0f + 0.5f),
            static_cast<uint8_t>(color.Y * 255.0f + 0.5f),
            static_cast<uint8_t>(color.Z * 255.0f + 0.5f)
        );

        SkPaint paint;
        paint.setColor(skColor);
        paint.setAntiAlias(true);
        paint.setBlendMode(SkBlendMode::kSrcOver);

        SkRect textBounds;
        font.measureText(text.c_str(), text.size(), SkTextEncoding::kUTF8, &textBounds);

        float w = textBounds.width();
        float h = textBounds.height();

        float tx = -textBounds.left();
        float ty = -textBounds.top();

        m_Canvas->save();

        if (rotation != 0.0f) {
            m_Canvas->rotate(-rotation, x, y);
        }

        float offsetX = -w * ox;
        float offsetY = -h * oy;

        m_Canvas->drawSimpleText(
            text.c_str(),
            text.size(),
            SkTextEncoding::kUTF8,
            x + tx + offsetX,
            y + ty + offsetY,
            font,
            paint
        );

        m_Canvas->restore();
    }

    void Framebuffer::Clear(const Vec4& c) {
        if (!m_Bitmap.getPixels()) return;

        SkColor color = SkColorSetARGB(
            static_cast<uint8_t>(c.W * 255.0f + 0.5f),
            static_cast<uint8_t>(c.X * 255.0f + 0.5f),
            static_cast<uint8_t>(c.Y * 255.0f + 0.5f),
            static_cast<uint8_t>(c.Z * 255.0f + 0.5f)
        );

        m_Canvas->clear(color);
    }

}
