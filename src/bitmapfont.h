#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <GL/glfw.h>
#include <string>

class BitmapFont
{
public:
    BitmapFont();
    BitmapFont(GLuint t);
    virtual ~BitmapFont();

    int STYLE_NORMAL;
    int STYLE_LIMIT;
    int STYLE_SHADOW;
    int STYLE_CENTER;
    int STYLE_SHINE;
    int STYLE_DEPTH;

    int charWidth;
    int charHeight;

    void genLists();
    void drawString2D(float x, float y, float size, int style, float r, float g, float b, std::string text, float extraData);
protected:
private:
    GLuint texture;
    GLuint glLists3D;
    GLuint glLists2D;
};

#endif // BITMAPFONT_H
