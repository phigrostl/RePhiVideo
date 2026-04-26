#pragma once

#include "Texture.h"

namespace PhiVideo {

    class Framebuffer {
    public:
        Framebuffer(const int width, const int height);
        ~Framebuffer();

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        void SetColor(const int x, const int y, const Vec4& c);
        Vec4 GetColor(const int x, const int y);
        unsigned char* GetPixelData();

        // Rotation unit = 360!
        void DrawTexture(float x, float y, const Texture* texture, float w, float h = -1.0, float rotation = 0.0f, Vec4 color = Vec4(1.0f), float ox = 0.5f, float oy = 0.5f);
        void DrawRect(float x, float y, float w, float h, const Vec4& color = Vec4(1.0f), float rotation = 0.0f);
        void DrawTextTTF(float x, float y, const std::string& text, float fontSize, const Vec4& color = Vec4(1.0f), float rotation = 0.0f, float ox = 0.5f, float oy = 0.5f);
        void Clear(const Vec4& c = Vec4(0.0f));
        void ToPNG(const std::string& path);

        static Framebuffer* Create(const int width, const int height) {
            return new Framebuffer(width, height);
        }

    private:
        void Init();
        void Terminate();

    private:
        int m_Width, m_Height;
        SkBitmap m_Bitmap;
        SkImageInfo m_Ii;
        SkFont m_Font;
        SkPaint m_Paint;
        SkCanvas* m_Canvas = nullptr;
    };

}
