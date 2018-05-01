
#include <GL/glfw.h>
#include "game.h"
#include "ball.h"
#include "stringops.h"

#include <iostream>

#include <cstdlib>
#include <time.h>

extern Game game;

Game::Game()
{
    //Do nothing
}

Game::~Game()
{
    glfwTerminate();
}

int Game::init(int w, int h)
{
    running = true;

    srand(time(NULL));

    windowWidth = w;
    windowHeight = h;

    //Set up GLFW and open a window
    glfwInit();

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);

    if(!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        return 0;
    }

    glfwSetWindowTitle("PIPONG");

    //OpenGL stuff
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

    //Adjust view matrices
    glViewport(0, 0, (GLfloat)windowWidth, (GLfloat)windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, windowHeight, 0);

    return 1;
}

int Game::load()
{
    //Load texture
    glGenTextures(7,&sprites[0]);

    glBindTexture(GL_TEXTURE_2D, sprites[0]);
    glfwLoadTexture2D("art/font.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[1]);
    glfwLoadTexture2D("art/ball_red.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[2]);
    glfwLoadTexture2D("art/ball_blue.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[3]);
    glfwLoadTexture2D("art/paddle_red.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[4]);
    glfwLoadTexture2D("art/paddle_blue.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[5]);
    glfwLoadTexture2D("art/PIPA.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, sprites[6]);
    glfwLoadTexture2D("art/bg.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Initialize font
    font = BitmapFont(sprites[0]);

    return 1;
}

int Game::reset()
{
    p1.setTexture(sprites[3]);
    p1.side = 1;
    p1.resetAll();

    p2.setTexture(sprites[4]);
    p2.side = 2;
    p2.resetAll();

    ball.resetDim();
    ball.setTexture(sprites[1]);

    ball.vel = Point2D(5, 5);

    fpsCounter.setTargetFramerate(60);
    fpsCounter.setAveragePeriod(1);

    return 1;
}

int Game::gameLoop()
{
    glClearColor( 1, 1, 1, 1.0f );

    while(running)
    {
        fpsCounter.nextFrame();

        //User input
        //CONTROLS FOR LEFT PLAYER
        if (!p1ai) {
            if (glfwGetKey(GLFW_KEY_UP))
            {
                p1.loc.y -= 10;
            }
            if (glfwGetKey(GLFW_KEY_DOWN))
            {
                p1.loc.y += 10;
            }
        } else {
            if (ball.vel.x < 0)
            {
                if (ball.loc.y < p1.loc.y - p1.size.y)
                {
                    p1.loc.y -= 10;
                }
                else if (ball.loc.y > p1.loc.y + p1.size.y)
                {
                    p1.loc.y += 10;
                }
            }
        }

        //CONTROLS FOR RIGHT PLAYER
        if (!p2ai) {
            if (glfwGetKey('W'))
            {
                p2.loc.y -= 10;
            }
            if (glfwGetKey('S'))
            {
                p2.loc.y += 10;
            }
        } else {
            if (ball.vel.x > 0)
            {
                if (ball.loc.y < p2.loc.y - p2.size.y)
                {
                    p2.loc.y -= 10;
                }
                else if (ball.loc.y > p2.loc.y + p2.size.y)
                {
                    p2.loc.y += 10;
                }
            }
        }

        //Slow down
        if (glfwGetKey('P'))
        {
            fpsCounter.setTargetFramerate(5);
        }
        //Speed up
        else if (glfwGetKey('O'))
        {
            fpsCounter.setTargetFramerate(600);
        }
        else
        {
            fpsCounter.setTargetFramerate(60);
        }

        //Physics
        p1.update();
        p2.update();

        for (int i = 0; i < 10; i++)
        {
            ball.update(0.1);

            //Player 1 paddle
            if (ball.getRect().intersect(p1.getRect()))
            {
                //ball.loc.x += 2 * (p1.loc.x + p1.size.x - (ball.loc.x - ball.size.x));
                if (ball.vel.x < 0)
                {
                    ball.vel.x = -ball.vel.x;
                    ball.vel.x += 1;
                    if (ball.vel.y < 0)
                    {
                        ball.vel.y += -.1;
                    }
                    else
                    {
                        ball.vel.y += .1;
                    }
                }
                ball.setTexture(sprites[1]);
            }

            //Player 2 paddle
            if (ball.getRect().intersect(p2.getRect()))
            {
                //ball.loc.x += 2 * ((ball.loc.x + ball.size.x) - p2.loc.x - p2.size.x);
                if (ball.vel.x > 0)
                {
                    ball.vel.x = -ball.vel.x;
                    ball.vel.x -= 1;
                    if (ball.vel.y < 0)
                    {
                        ball.vel.y += -.1;
                    }
                    else
                    {
                        ball.vel.y += .1;
                    }
                }
                ball.setTexture(sprites[2]);
            }
        }

        //Scoring
        if (ball.loc.x < 0)
        {
            //Player 1 scores
            p2.addScore(1);

            ball.resetDim();
            ball.vel = Point2D(5, 5);
            ball.loc.y = (int)(rand() % 541 + 30);
            ball.setTexture(sprites[1]);

            if (p2.score == 9)
            {
                lose();
                return 0;
            }
        }
        if (ball.loc.x > 800)
        {
            //Player 2 scores
            p1.addScore(1);

            ball.resetDim();
            ball.vel = Point2D(-5, -5);
            ball.loc.y = (int)(rand() % 541 + 30);
            ball.setTexture(sprites[2]);

            if (p1.score == 9)
            {
                win();
                return 0;
            }
        }

        //Render setup
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);

        //Begin Render

        glBindTexture(GL_TEXTURE_2D, sprites[6]);

        //Background
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(0, 0);
        glTexCoord2f(0.78125, 0.0);
        glVertex2f(800, 0);
        glTexCoord2f(0.78125, 0.5859375);
        glVertex2f(800, 600);
        glTexCoord2f(0.0, 0.5859375);
        glVertex2f(0, 600);
        glEnd();

        p1.drawMe();
        p2.drawMe();
        ball.drawMe();

        glBindTexture(GL_TEXTURE_2D, sprites[5]);

        //Cheat message
        glColor4f(1, 1, 1, 1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.52734375);
        glVertex2f(171, 50);
        glTexCoord2f(0.4462890625, 0.52734375);
        glVertex2f(629, 50);
        glTexCoord2f(0.4462890625, 0.583984375);
        glVertex2f(629, 109);
        glTexCoord2f(0.0, 0.583984375);
        glVertex2f(171, 109);
        glEnd();

        if (glfwGetKey('H')) {
            glColor4f(1, 1, 1, .25);
        } else {
            glColor4f(1, 1, 1, 1);
        }

        //Censor
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(130, 30);
        glTexCoord2f(0.52734375, 0.0);
        glVertex2f(670, 30);
        glTexCoord2f(0.52734375, 0.52734375);
        glVertex2f(670, 570);
        glTexCoord2f(0.0, 0.52734375);
        glVertex2f(130, 570);
        glEnd();

        font.drawString2D(150, 35, 22, 1, 1, 1, 1, to_string(p1.score), 0);
        font.drawString2D(650, 35, 22, 1, 1, 1, 1, to_string(p2.score), 0);

        //End render
        glPopMatrix();

        glfwSwapBuffers();

        //Window events
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);

        //Wait
        fpsCounter.wait();
    }

    return 0;
}

void Game::lose()
{
    glClearColor( 0, 0, 0, 1.0f );

    while(running)
    {
        fpsCounter.nextFrame();

        if (glfwGetKey(GLFW_KEY_ENTER))
            break;

        //Render setup
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);

        //Begin Render
        game.font.drawString2D(400, 267, 33, 1, 1, 1, 1, "YOU CAN'T STOP PIRATES.", 0);
        game.font.drawString2D(400, 300, 33, 1, 1, 1, 1, "   NEITHER CAN PIPA.   ", 0);
        game.font.drawString2D(400, 589, 11, 1, 1, 1, 1, "ENTER TO RESTART", 0);

        //End render
        glPopMatrix();

        glfwSwapBuffers();

        //Window events
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);

        //Wait
        fpsCounter.wait();
    }
}

void Game::win()
{
    glClearColor( 0, 0, 0, 1.0f );

    while(running)
    {
        fpsCounter.nextFrame();

        if (glfwGetKey(GLFW_KEY_ENTER))
            break;

        //Render setup
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);

        //Begin Render
        game.font.drawString2D(400, 267, 33, 1, 1, 1, 1, "A WINNER IS YOU", 0);
        game.font.drawString2D(400, 300, 33, 1, 1, 1, 1, "UNLESS PIPA HAPPENS.", 0);
        game.font.drawString2D(400, 589, 11, 1, 1, 1, 1, "ENTER TO RESTART", 0);

        //End render
        glPopMatrix();

        glfwSwapBuffers();

        //Window events
        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED);

        //Wait
        fpsCounter.wait();
    }
}
