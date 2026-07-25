#include "text.hpp"

namespace {
    GlyphAtlasPositionUV getGlyphAtlasTextureUVs(int glyph_id) {
        int index = glyph_id - 1;

        int u = 1 + (glyph_id - 1) % GLYPHS_PER_ROW * (GLYPH_WIDTH + 1);
        int v = 1 + index / GLYPHS_PER_ROW * (GLYPH_HEIGHT + 1);

        return {u, v};
    }

    int emoticons(char glyph, std::string& string, int i) {
        char next_glyph = string[i + 1];

        if (next_glyph == '1') return 96;
        else if (next_glyph == '2') return 97;
        else if (next_glyph == '3') return 98;
        else if (next_glyph == '4') return 99;
        else if (next_glyph == '5') return 100;
        else if (next_glyph == '6') return 101;
        else if (next_glyph == '7') return 102;
        else if (next_glyph == '8') return 103;
        else if (next_glyph == '9') return 104;

        return 1;
    }

    float glyphStep(char glyph, float width, TextStyle style) {
        auto stepPixel = [](int pixel, float width, TextStyle style) { return pixel * width / static_cast<float>(GLYPH_WIDTH); };
        float step = stepPixel(6, width, style);
        if (glyph == ' ') step = stepPixel(3, width, style);
        else if (glyph == 'i') step = stepPixel(4, width, style);
        else if (glyph == 'r') step = stepPixel(5, width, style);
        else if (glyph == 'h') step = stepPixel(5, width, style);
        else if (glyph == 'n') step = stepPixel(5, width, style);
        else if (glyph == 'k') step = stepPixel(5, width, style);
        else if (glyph == 'l') step = stepPixel(3, width, style);
        else if (glyph == '!') step = stepPixel(2, width, style);
        else if (glyph == '.') step = stepPixel(2, width, style);

        return step;
    }
}

Text::Text(Vector2F start_position, TextStyle style, std::string string) {
    m_start_position = start_position;
    m_style = style;
    m_string = string;
}

Primitive Text::buildPrimitives() {
    Primitive primitives;

    float width = m_style.size * static_cast<float>(GLYPH_WIDTH) / static_cast<float>(GLYPH_HEIGHT);
    float height = m_style.size;

    float advance = 0.0f;

    for (int i = 0; i < m_string.size(); i++) {
        bool special_exists = false;
        char& glyph = m_string[i];
        int glyph_id = 26;  // placeholder unknown char

        // Handle Converting '/*' Into Single-Char Emoticon 
        if (glyph == '/' && i + 1 < static_cast<int>(m_string.size())) {
            glyph_id = emoticons(glyph, m_string, i);
            special_exists = true;
        } else if (GlyphMap.find(glyph) != GlyphMap.end()) {
            glyph_id = GlyphMap.find(glyph)->second; 
            if (m_string[i - 1] == '/') glyph_id = 74;
        }

        GlyphAtlasPositionUV glyph_uv = getGlyphAtlasTextureUVs(glyph_id);

        float u0 = static_cast<float>(glyph_uv.u) / FONT_AXIS_WIDTH;
        float v0 = 1.0f - static_cast<float>(glyph_uv.v) / FONT_AXIS_HEIGHT;
        float u1 = static_cast<float>(glyph_uv.u + GLYPH_WIDTH) / FONT_AXIS_WIDTH;
        float v1 = 1.0f - static_cast<float>(glyph_uv.v + GLYPH_HEIGHT) / FONT_AXIS_HEIGHT;

        float start_x = m_start_position.u * 2.0f - 1.0f;
        float start_y = m_start_position.v * 2.0f - 1.0f;

        if (m_style.centered) {
            float text_width = 0.0f;
            for (int j = 0; j < m_string.size() - 1; j++) text_width += glyphStep(m_string[j], width, m_style);

            start_x -= text_width * 0.5f;
            start_y -= m_style.size * 0.5f;
        }

        float x0 = start_x + advance;
        float y0 = start_y;
        float x1 = x0 + width;
        float y1 = y0 + height;

        Vertex bottom_left  = {x1, y1, 0.0f, u1, v0};
        Vertex bottom_right = {x1, y0, 0.0f, u1, v1};
        Vertex top_right    = {x0, y0, 0.0f, u0, v1};
        Vertex top_left     = {x0, y1, 0.0f, u0, v0};

        primitives.appendPrimitive(quad(top_right, bottom_right, bottom_left, top_left));

        // Handle Smaller Width Characters (i, l, !, etc.)
        auto stepPixel = [](int pixel, float width, TextStyle style) { return pixel * width / static_cast<float>(GLYPH_WIDTH); };
        float step = stepPixel(6, width, m_style);
        if (glyph == ' ') step = stepPixel(3, width, m_style);
        else if (glyph == 'i') step = stepPixel(4, width, m_style);
        else if (glyph == 'r') step = stepPixel(5, width, m_style);
        else if (glyph == 'h') step = stepPixel(5, width, m_style);
        else if (glyph == 'n') step = stepPixel(5, width, m_style);
        else if (glyph == 'k') step = stepPixel(5, width, m_style);
        else if (glyph == 'l') step = stepPixel(3, width, m_style);
        else if (glyph == '!') step = stepPixel(2, width, m_style);
        else if (glyph == '.') step = stepPixel(2, width, m_style);

        if (!special_exists) advance += step;
    }
    return primitives;
}
