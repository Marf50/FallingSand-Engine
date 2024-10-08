#pragma once


namespace FallingSandEngine
{
	struct ScalableTexture
	{
		Ref<SubTexture2D> topLeftCorner;
		Ref<SubTexture2D> topEdge;
		Ref<SubTexture2D> topRightCorner;
		Ref<SubTexture2D> leftEdge;
		Ref<SubTexture2D> center;
		Ref<SubTexture2D> rightEdge;
		Ref<SubTexture2D> bottomLeftCorner;
		Ref<SubTexture2D> bottomEdge;
		Ref<SubTexture2D> bottomRightCorner;
	};
	struct VerticallyScalingTexture {
		Ref<SubTexture2D> top;
		Ref<SubTexture2D> middle;
		Ref<SubTexture2D> bottom;
	};
	struct HorizontallyScalingTexture {
		Ref<SubTexture2D> left;
		Ref<SubTexture2D> middle;
		Ref<SubTexture2D> right;
	};
	struct UIStyle
	{
		UIStyle() = default;

		Ref<Font> font;
		ScalableTexture MenuWindow;
		ScalableTexture ButtonIdle;
		ScalableTexture ButtonHovered;
		ScalableTexture ButtonPressed;
		ScalableTexture TextPlate;

		HorizontallyScalingTexture SliderTrack;
		Ref<SubTexture2D> Knob;
		VerticallyScalingTexture ScrollTrack;
		Ref<SubTexture2D> ScrollThumb;
 	};
}