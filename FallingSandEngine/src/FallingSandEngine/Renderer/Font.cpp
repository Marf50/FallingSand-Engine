#include "fsepch.h"
#include "Font.h"


namespace FallingSandEngine
{
    void Font::SetGlyph(int asciiNumber, const Ref<SubTexture2D>& subTexture, float width, float height, float advanceX, float offsetX, float offsetY)
    {
        Glyph glyph;
        glyph.SubTexture = subTexture;
        glyph.Width = width;
        glyph.Height = height;
        glyph.AdvanceX = advanceX;
        glyph.OffsetX = offsetX;
        glyph.OffsetY = offsetY;

        m_Glyphs[asciiNumber] = glyph;
    }

    const Glyph& Font::GetGlyph(char character) const
    {
        auto it = m_Glyphs.find((int)character);
        if (it != m_Glyphs.end())
        {
            return it->second;
        }
        else
        {
            static Glyph defaultGlyph;
            return defaultGlyph;
        }
    }
}


