#include "bitmapfont.h"

BitmapFont::BitmapFont()
{
    STYLE_NORMAL = 1;
    STYLE_LIMIT = 2;
    STYLE_SHADOW = 4;
    STYLE_CENTER = 8;
    STYLE_SHINE = 16;
    STYLE_DEPTH = 32;
}

BitmapFont::BitmapFont(GLuint t)
{

    texture = t;
    charWidth = 11;
    charHeight = 11;
    genLists();
}

BitmapFont::~BitmapFont()
{
    //dtor
}

void BitmapFont::genLists()
{
    //Generate display lists
    glLists3D = glGenLists(256);
    glLists2D = glGenLists(256);

    for (int i = 0; i < 256; i++)
    {
        float a = (char) (i & 0x0f);
        float b = (char) ((i >> 4) & 0x0f);

        // 2D text
        glNewList(glLists2D + i, GL_COMPILE);
        glBegin(GL_QUADS);
        glTexCoord2f(a * charWidth / 256, b * charHeight / 256);
        glVertex2f(0, 0);
        glTexCoord2f((a + 1) * charWidth / 256, b * charHeight / 256);
        glVertex2f(1, 0);
        glTexCoord2f((a + 1) * charWidth / 256, (b + 1) * charHeight / 256);
        glVertex2f(1, 1);
        glTexCoord2f(a * charWidth / 256, (b + 1) * charHeight / 256);
        glVertex2f(0, 1);
        glEnd();
        glEndList();
    }
}

// Draw a string "directly" on the screen
void BitmapFont::drawString2D(float x, float y, float size, int style,
                              float r, float g, float b, std::string text, float extraData)
{

    if ((style & STYLE_CENTER) > 0)
    {
        x = x - text.length() * size / 2;
    }

    glPushMatrix();
    glColor3f(r, g, b);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    if (style & STYLE_LIMIT)
    {
        glScalef(extraData / text.length(), 1, 1);
    }

    for (uint32_t i = 0; i < text.length(); i++)
    {
        if (style & STYLE_SHADOW)
        {
            glColor4ub((char) 0, (char) 0, (char) 0, (char) 128);
            glPushMatrix();
            glTranslatef(extraData / size, extraData / size, 0);
            glCallList(glLists2D + text.at(i));
            glPopMatrix();
            glColor3f(r, g, b);
        }
        glCallList(glLists2D + text.at(i));
        glTranslatef(1, 0, 0);
    }

    glPopMatrix();
}
