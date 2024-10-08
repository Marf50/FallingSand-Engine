#pragma once
#include "Texture.h"
#include "SubTexture2D.h"
#include "FallingSandEngine/Core/Core.h"
struct stbtt_fontinfo;


namespace FallingSandEngine
{
	
	
	struct Glyph
	{
		Ref<SubTexture2D> SubTexture;
		float Width, Height;
		float OffsetX, OffsetY;
		float AdvanceX;
	};

	class Font
	{
	public:
		Font() = default;

		void SetGlyph(int asciiNumber, const Ref<SubTexture2D>& subTexture, float width, float height, float advanceX, float offsetX, float offsetY);
		const Glyph& GetGlyph(char character) const;

	private:
		
		std::unordered_map<int, Glyph> m_Glyphs;
		
	};
}