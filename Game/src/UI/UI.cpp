#include "UI.h"

namespace FallingSandEngine
{
    UI::UI()
        : m_GridRows(0), m_GridCols(0), m_CellSize(0.0f), m_MousePos(0.0f), m_MouseClicked(false) 
    {
        
    }

    void UI::SetStyle(const UIStyle& style) {
        // Copy the style into the currentStyle member variable
        currentStyle = style;
    }

    void UI::SetGrid(int rows, int cols, const glm::vec2& screenSize) {
        // Set the number of rows and columns
        m_GridRows = rows;
        m_GridCols = cols;

        // Calculate the size of each grid cell
        m_CellSize.x = screenSize.x / static_cast<float>(cols);  // Cell width
        m_CellSize.y = screenSize.y / static_cast<float>(rows);  // Cell height

        //FSE_INFO("Grid set: Rows = {0}, Cols = {1}, ScreenSize = ({2}, {3}), CellSize = ({4}, {5})",
            //rows, cols, screenSize.x, screenSize.y, m_CellSize.x, m_CellSize.y);
    }

    void UI::DrawMenu(int startX, int startY, int endX, int endY) {
        // Ensure we have a valid style for the menu window
        const ScalableTexture& menuTexture = currentStyle.MenuWindow;

        // Pass the grid coordinates directly into DrawScalingTexture
        DrawScalingTexture(startX, startY, endX, endY, menuTexture);
    }

    bool UI::DrawButton(int startX, int startY, int endX, int endY, float padding, const std::string& label) {
        // Calculate the position and size of the button based on grid coordinates
        glm::vec2 position = GetCellPosition(startX, startY);
        glm::vec2 size = CalculateElementSize(startX, startY, endX, endY);

        // Check if the button is hovered or clicked
        bool hovered = IsMouseOver(startX, startY, endX, endY, padding);
        bool clicked = IsMouseClicked(startX, startY, endX, endY, padding);

        // Choose the button texture based on the state (idle, hovered, pressed)
        const ScalableTexture* buttonTexture;
        if (clicked) {
            buttonTexture = &currentStyle.ButtonPressed;
            m_MouseClicked = false;
        }
        else if (hovered) {
            buttonTexture = &currentStyle.ButtonHovered;
        }
        else {
            buttonTexture = &currentStyle.ButtonIdle;
        }

        // Draw the button as a 9-slice scaling texture
        DrawScalingTexture(startX, startY, endX, endY, *buttonTexture);

        // Pass relevant data to DrawUiText (handle the text drawing separately)
        DrawUiText(startX, startY, endX, endY, padding, label);

        // Return true if the button was clicked, false otherwise
       
        return clicked;
    }

    float UI::DrawSlider(int startX, int startY, int endX, int endY, float* value, float min, float max, float xPadding, float yPadding) {
        // Calculate the grid cell position and size for the slider
        glm::vec2 position = GetCellPosition(startX, startY);
        glm::vec2 size = CalculateElementSize(startX, startY, endX, endY);

        // Draw the slider track as a horizontally scaling texture
        DrawHorizontallyScalingTexture(startX, startY, endX, endY, currentStyle.SliderTrack);


        // Scale the padding based on the cell size (assuming textures are 64x64)
        float scaleFactorX = m_CellSize.x / 64.0f;
        float scaleFactorY = m_CellSize.y / 64.0f;
        glm::vec2 scaledXPadding = glm::vec2(xPadding * scaleFactorX, yPadding * scaleFactorY);

        // Calculate the effective width for the knob to slide (account for padding and knob width)
        float availableTrackWidth = size.x - (scaledXPadding.x * 2.0f);
        
        // Knob size: Should span the entire height of the track (minus padding)
        float knobHeight = size.y - (scaledXPadding.y * 2.0f);
        float knobWidth = knobHeight;  // Assuming square knob
        glm::vec2 knobSize = glm::vec2(knobWidth*2, knobHeight*2);

        // Calculate the knob's position based on the current value
        float normalizedValue = (*value - min) / (max - min);  // Normalize the value between 0 and 1
        
        // Center the knob horizontally within the available track (accounting for knob width)
        float knobPositionX = position.x + scaledXPadding.x + normalizedValue * (availableTrackWidth - knobWidth);

        // Center the knob vertically within the track (account for padding)
        glm::vec2 knobPosition = glm::vec2(knobPositionX, position.y + (scaledXPadding.y));

        // Draw the knob (centered horizontally on the track, scaled to fit the track's height)
        Renderer2D::DrawQuad(glm::vec3(knobPosition + glm::vec2(knobWidth / 2.0f, knobHeight / 2.0f), Depth + 0.001f), knobSize, currentStyle.Knob);

        // Handle mouse input for dragging the knob
        if (IsMouseClicked(startX, startY, endX, endY, yPadding)) {
            glm::vec2 mousePos = m_MousePos;  // Use the stored mouse position from the event

            // Subtract half of the knob's width to center the knob on the mouse click
            float newNormalizedValue = (mousePos.x - position.x - scaledXPadding.x - knobWidth / 2.0f) / (availableTrackWidth - knobWidth);

            newNormalizedValue = glm::clamp(newNormalizedValue, 0.0f, 1.0f);  // Clamp between 0 and 1

            *value = newNormalizedValue * (max - min) + min;  // Update the slider value based on mouse position
        }

        // Return the updated value
        return *value;
    }


    float UI::DrawScrollBar(int startX, int startY, int endX, int endY, float* value, float min, float max) {
        // Calculate the position and size of the scroll bar based on grid coordinates
        glm::vec2 position = GetCellPosition(startX, startY);
        glm::vec2 size = CalculateElementSize(startX, startY, endX, endY);

        // Draw the scroll track as a vertically scaling texture
        DrawVerticallyScalingTexture(startX, startY, endX, endY, currentStyle.ScrollTrack);

        // Calculate the thumb position based on the current value
        float normalizedValue = (*value - min) / (max - min);  // Normalize the value between 0 and 1
        float thumbHeight = size.x;  // Assume the thumb is square, using the width of the scrollbar as the thumb size
        glm::vec2 thumbPosition = position + glm::vec2(0.0f, normalizedValue * size.y - thumbHeight / 2.0f);

        // Draw the thumb (stretched to fit the scroll bar's width)
        Renderer2D::DrawQuad(thumbPosition, glm::vec2(size.x, thumbHeight), currentStyle.ScrollThumb);

        // Handle mouse input (dragging the thumb to change the value)
        if (IsMouseClicked(startX, startY, endX, endY) || IsMouseOver(startX, startY, endX, endY)) {
            glm::vec2 mousePos = m_MousePos;  // Use the stored mouse position from the event
            float newNormalizedValue = (mousePos.y - position.y) / size.y;
            newNormalizedValue = glm::clamp(newNormalizedValue, 0.0f, 1.0f);  // Clamp between 0 and 1

            *value = newNormalizedValue * (max - min) + min;  // Update the scroll value based on mouse position
        }

        // Return the updated scroll value
        return *value;
    }

    void UI::DrawUiText(int startX, int startY, int endX, int endY, float padding, const std::string& text) {
        // Calculate the grid cell position and size for the UI text area
        glm::vec2 position = GetCellPosition(startX, startY);
        glm::vec2 size = CalculateElementSize(startX, startY, endX, endY);

        // Calculate scaled padding based on the cell size and texture size (64x64 texture assumed)
        float scaleFactorX = m_CellSize.x / 64.0f;  // Assuming 64x64 textures
        float scaleFactorY = m_CellSize.y / 64.0f;

        glm::vec2 scaledPadding = glm::vec2(padding * scaleFactorX, padding * scaleFactorY);

        // Calculate available area after padding
        glm::vec2 availableArea = size - glm::vec2(scaledPadding.x * 2.0f, scaledPadding.y * 2.0f);

        // Measure the width of the text and the typical character height
        float textWidth = CalculateTextWidth(text, currentStyle.font);
        float textHeight = currentStyle.font->GetGlyph('A').Height;  // Assuming 'A' represents a typical character height

        // Scale the text to fit within the available space, preserving aspect ratio
        float scaleX = availableArea.x / textWidth;
        float scaleY = availableArea.y / textHeight;
        float scale = glm::min(scaleX, scaleY);  // Use the smaller scale to ensure the text fits

        // Compute the final size of the scaled text
        glm::vec2 scaledTextSize(textWidth * scale, textHeight * scale);

        // Calculate the text's starting position to center it within the available area
        glm::vec2 textPosition = position + glm::vec2(
            (availableArea.x - scaledTextSize.x) / 2.0f,  // Horizontal centering
            (availableArea.y - scaledTextSize.y) / 2.0f   // Vertical centering
        ) + scaledPadding;

        // Adjust the vertical position slightly for baseline alignment (optional, if needed)
        float baselineOffset = 32.0f * scale;  // Arbitrary value, adjust as necessary
        textPosition += baselineOffset;

        // Draw each character of the text, adjusting position for each glyph
        glm::vec3 currentPos = glm::vec3{ textPosition.x, textPosition.y, Depth + 0.001f };
        for (char c : text) {
            const Glyph& glyph = currentStyle.font->GetGlyph(c);

            // Draw the character at the current position, scaled appropriately
            glm::vec2 charSize = glm::vec2(glyph.Width * scale, glyph.Height * scale);
            Renderer2D::DrawQuad(currentPos, charSize, glyph.SubTexture);

            // Advance the position by the character's advance value, scaled
            currentPos.x += glyph.AdvanceX * scale;
            currentPos.z += 0.001f;  // Increment depth slightly for each character
        }
    }

    void UI::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseMovedEvent>(FSE_BIND_EVENT_FN(UI::OnMouseMoved));
        dispatcher.Dispatch<MouseButtonPressedEvent>(FSE_BIND_EVENT_FN(UI::OnMouseButtonPressed));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(FSE_BIND_EVENT_FN(UI::OnMouseButtonReleased));
    }
    bool UI::OnMouseMoved(MouseMovedEvent& e) {
        m_MousePos = glm::vec2(e.GetX(), e.GetY());
        return false;  // Return false if we don't want to block the event
    }

    bool UI::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
        if (e.GetMouseButton() == FSE_MOUSE_BUTTON_LEFT) {
            m_MouseClicked = true;
        }
        return false;
    }

    bool UI::OnMouseButtonReleased(MouseButtonReleasedEvent& e) {
        if (e.GetMouseButton() == FSE_MOUSE_BUTTON_LEFT) {
            m_MouseClicked = false;
        }
        return false;
    }


    bool UI::IsMouseOver(int startX, int startY, int endX, int endY, float padding) {
        // Calculate the position and size of the UI element based on grid coordinates
        glm::vec2 position = GetCellPosition(startX, startY);
        glm::vec2 size = CalculateElementSize(startX, startY, endX, endY);

        // Calculate scaled padding based on the cell size and texture size (64x64 texture assumed)
        float scaleFactorX = m_CellSize.x / 64.0f;  // Assuming 64x64 texture
        float scaleFactorY = m_CellSize.y / 64.0f;
        glm::vec2 scaledPadding = glm::vec2(padding * scaleFactorX, padding * scaleFactorY);

        // Adjust position and size by the scaled padding
        glm::vec2 adjustedPosition = position + scaledPadding;
        glm::vec2 adjustedSize = size - glm::vec2(scaledPadding.x * 2.0f, scaledPadding.y * 2.0f);

        // Calculate screen height using the number of rows and the cell height
        float screenHeight = m_GridRows * m_CellSize.y;

        // Flip the mouse Y coordinate to match the grid's coordinate system
        float flippedMouseY = screenHeight - m_MousePos.y;

        // Check if the mouse is within the bounds of the adjusted element (with padding considered)
        return (m_MousePos.x >= adjustedPosition.x && m_MousePos.x <= adjustedPosition.x + adjustedSize.x &&
            flippedMouseY >= adjustedPosition.y && flippedMouseY <= adjustedPosition.y + adjustedSize.y);
    }
    bool UI::IsMouseClicked(int startX, int startY, int endX, int endY, float padding) {
        // Check if the mouse is over the element
        if (IsMouseOver(startX, startY, endX, endY, padding)) {
            // Check if the mouse button was clicked
            return m_MouseClicked;
        }
        return false;
    }

    glm::vec2 UI::GetCellPosition(int x, int y)
    {
        return glm::vec2(x * m_CellSize.x, y * m_CellSize.y);
    }

    glm::vec2 UI::CalculateElementSize(int startX, int startY, int endX, int endY) {
        // Calculate the width and height of the element in screen space
        float width = (endX - startX) * m_CellSize.x;
        float height = (endY - startY) * m_CellSize.y;

        

        // Return the size as a glm::vec2
        return glm::vec2(width, height);
    }

    float UI::CalculateTextWidth(const std::string& text, const Ref<Font>& font) {
        float totalWidth = 0.0f;

        // Loop through all but the last character
        for (size_t i = 0; i < text.length(); ++i) {
            const Glyph& glyph = font->GetGlyph(text[i]);

            // For all but the last character, add the advance value
            if (i < text.length() - 1) {
                totalWidth += glyph.AdvanceX;
            }
            else {
                // For the last character, add the actual width instead of the advance
                totalWidth += glyph.Width;
            }
        }


        // Return the total width of the string
        return totalWidth;
    }

    void UI::DrawScalingTexture(int startX, int startY, int endX, int endY, const ScalableTexture& texture) {

        int widthCells = endX - startX;
        int heightCells = endY - startY;

        //FSE_INFO("Drawing menu: StartX = {0}, StartY = {1}, EndX = {2}, EndY = {3}, WidthCells = {4}, HeightCells = {5}",
            //startX, startY, endX, endY, widthCells, heightCells);

        glm::vec2 BottomLeftPos = GetCellPosition(startX, startY);
        glm::vec2 TopRightPos = GetCellPosition(endX, endY);

        //FSE_INFO("BottomLeftPos: ({0}, {1}), TopRightPos: ({2}, {3})",
            //BottomLeftPos.x, BottomLeftPos.y, TopRightPos.x, TopRightPos.y);

        // Offset by half the cell size to align with the grid
        glm::vec2 offset(m_CellSize.x / 2.0f, m_CellSize.y / 2.0f);

        // Assume the corners always take up one cell, so the center and edges are based on this
        int cornerCells = 1;

        // Draw corners (top-left, top-right, bottom-left, bottom-right)
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, startY + heightCells - cornerCells) + offset, Depth), glm::vec2(m_CellSize), texture.topLeftCorner);  // Top-left
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(endX - cornerCells, startY + heightCells - cornerCells) + offset, Depth), glm::vec2(m_CellSize), texture.topRightCorner);  // Top-right
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, startY) + offset, Depth) , glm::vec2(m_CellSize), texture.bottomLeftCorner);  // Bottom-left
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(endX - cornerCells, startY) + offset, Depth) , glm::vec2(m_CellSize), texture.bottomRightCorner);  // Bottom-right

        // Draw edges
        // Horizontal edges (top and bottom, stretching horizontally)
        for (int i = startX + cornerCells; i < endX - cornerCells; ++i) {
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(i, startY + heightCells - cornerCells) + offset, Depth), glm::vec2(m_CellSize), texture.topEdge);  // Top edge
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(i, startY) + offset, Depth), glm::vec2(m_CellSize), texture.bottomEdge);  // Bottom edge
        }

        // Vertical edges (left and right, stretching vertically)
        for (int i = startY + cornerCells; i < endY - cornerCells; ++i) {
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, i) + offset, Depth), glm::vec2(m_CellSize), texture.leftEdge);  // Left edge
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(endX - cornerCells, i) + offset, Depth), glm::vec2(m_CellSize), texture.rightEdge);  // Right edge
        }

        // Draw center (filling the remaining grid cells)
        for (int i = startX + cornerCells; i < endX - cornerCells; ++i) {
            for (int j = startY + cornerCells; j < endY - cornerCells; ++j) {
                Renderer2D::DrawQuad(glm::vec3(GetCellPosition(i, j) + offset, Depth), glm::vec2(m_CellSize), texture.center);
            }
        }
    }

    void UI::DrawVerticallyScalingTexture(int startX, int startY, int endX, int endY, const VerticallyScalingTexture& texture) {
        int heightCells = endY - startY;

        // Offset by half the cell size to align with the grid
        glm::vec2 offset(m_CellSize.x / 2.0f, m_CellSize.y / 2.0f);

        // Top section goes in the top-most grid cell
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, startY + heightCells - 1) + offset, Depth), glm::vec2(m_CellSize), texture.top);

        // Bottom section goes in the bottom-most grid cell
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, startY) + offset, Depth), glm::vec2(m_CellSize), texture.bottom);

        // Middle section stretches between the top and bottom
        for (int i = startY + 1; i < startY + heightCells - 1; ++i) {
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, i) + offset, Depth), glm::vec2(m_CellSize), texture.middle);
        }
    }

    void UI::DrawHorizontallyScalingTexture(int startX, int startY, int endX, int endY, const HorizontallyScalingTexture& texture) {
        int widthCells = endX - startX;

        // Offset by half the cell size to align with the grid
        glm::vec2 offset(m_CellSize.x / 2.0f, m_CellSize.y / 2.0f);

        // Left section goes in the left-most grid cell
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX, startY) + offset, Depth), glm::vec2(m_CellSize), texture.left);

        // Right section goes in the right-most grid cell
        Renderer2D::DrawQuad(glm::vec3(GetCellPosition(startX + widthCells - 1, startY) + offset, Depth), glm::vec2(m_CellSize), texture.right);

        // Middle section stretches between the left and right
        for (int i = startX + 1; i < startX + widthCells - 1; ++i) {
            Renderer2D::DrawQuad(glm::vec3(GetCellPosition(i, startY) + offset, Depth), glm::vec2(m_CellSize), texture.middle);
        }
    }

}