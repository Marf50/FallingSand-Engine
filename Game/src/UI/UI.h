#pragma once

#include "FallingSandEngine.h"
#include "UIStyle.h"


namespace FallingSandEngine
{
    class UI
    {
    public:
        UI();

        void SetGrid(int rows, int cols, const glm::vec2& screenSize);

        void SetStyle(const UIStyle& style);

        void DrawMenu(int startX, int startY, int endX, int endY);
        bool DrawButton(int startX, int startY, int endX, int endY , float padding , const std::string& label);
        float DrawSlider(int startX, int startY, int endX, int endY, float* value, float min, float max, float paddingX, float paddingY);
        float DrawScrollBar(int startX, int startY, int endX, int endY, float* value, float min ,float max);

        void DrawUiText(int startX, int startY, int endX, int endY, float padding, const std::string& text);

        void OnEvent(Event& e);
        bool UI::OnMouseMoved(MouseMovedEvent& e);
        bool UI::OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool UI::OnMouseButtonReleased(MouseButtonReleasedEvent& e);

        float Depth = 0.0f;

    private:
        int m_GridRows;
        int m_GridCols;
        glm::vec2 m_CellSize;

        


        UIStyle currentStyle;
        //Input Helpers
        bool IsMouseOver(int startX, int startY, int endX, int endY, float padding = 0.0f);
        bool IsMouseClicked(int startX, int startY, int endX, int endY, float padding = 0.0f);

        glm::vec2 m_MousePos;
        bool m_MouseClicked;
        
        //Render Helpers
        glm::vec2 GetCellPosition(int x, int y);
        glm::vec2 CalculateElementSize(int startX, int startY, int endX, int endY);
        float CalculateTextWidth(const std::string& text, const Ref<Font>& font);

        void DrawScalingTexture(int startX, int startY , int endX, int endY, const ScalableTexture& texture);
        void DrawVerticallyScalingTexture(int startX, int startY, int endX, int endY, const VerticallyScalingTexture& texture);
        void DrawHorizontallyScalingTexture(int startX, int startY, int endX, int endY, const HorizontallyScalingTexture& texture);
            

    };
}