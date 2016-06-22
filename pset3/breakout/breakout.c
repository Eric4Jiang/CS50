//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels~cs50/pset3/breakout~cs50/pset3/breakout
#define RADIUS 10
#define DIAMETER 20
// lives
#define LIVES 3

//Width and height of paddle
#define paddleWidth 65
#define paddleHeight 10

//Width and Height of bricks
#define brickWidth 35
#define brickHeight 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points, int lives);
GObject detectCollision(GWindow window, GOval ball);
bool godMode(string input);

int main(int argc, char* argv[])
{
    if(argc != 2 && argc != 1)
    {
        return -1;
    }
    
    bool GODMODE = false;
    //check for godmode
    if(argc == 2)
    {
        GODMODE = godMode(argv[1]);
    }
    // seed pseudorandom number generator
    //srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks 
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    int velocityX = 3;
    int velocityY = 4;
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0 )
    {
    
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        move(ball, velocityX, velocityY);
        
        GObject object = detectCollision(window, ball);
        
        //GODMODE: paddle follow ball 
        if(GODMODE)
        {
            double ballLocation = getX(ball) - paddleWidth/2 + RADIUS; 
            setLocation(paddle, ballLocation, 550);
        }
        
        //paddle follows mouse
        else if(event != NULL)
        {
            if(getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, 550);
            }        
        }
        
        //lose life when ball touches floor
        if(getY(ball) + DIAMETER > HEIGHT)
        {
            lives -= 1;
            setLocation(ball, WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS);
            waitForClick();
        }
        
        //bounces ball off window edges
        if((getX(ball) + DIAMETER) > WIDTH) // right edge
        {
            velocityX = -velocityX;
        }
        if(getX(ball) < 0) //left edge
        {
            velocityX = -velocityX;
        }
        if(getY(ball) < 0) //top edge
        {
            velocityY = -velocityY;
        }     
        
        // when the ball collides with object
        if(object != NULL) 
        {
            if(strcmp(getType(object), "GRect") == 0)
            {   
                //bounces ball off brick and makes brick vanish
                if(object != paddle)
                {
                    velocityY = -velocityY;
                    removeGWindow(window, object);
                    bricks--;
                    points++;
                    updateScoreboard(window, label, points, lives);
                }
                //bounces ball off paddle
                else if(object == paddle)
                {
                    velocityY = -(abs(velocityY));
                }
            }
        }
        pause(10); // slows the ball
    }

    // game over
    closeGWindow(window);
    return 0;
}

bool godMode(string input)
{
    if(strcmp(input, "GODMODE") == 0)
    {
        printf("GODMODE ACTIVATED\n");
        return true;
    }
    else
        return false;
}
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int widthLocation = 7;
    int heightLocation = 50;
    string colors[5]={"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(widthLocation, heightLocation, brickWidth, brickHeight);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
            widthLocation += brickWidth + 4;
        }
        heightLocation += brickHeight + 7;
        widthLocation = 7;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS, DIAMETER, DIAMETER);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(175, 550 , paddleWidth, paddleHeight);
    setFilled(paddle, true);
    setColor(paddle, "RED");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y - 25);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points, int lives)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y - 25);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}

//void reset()
//{

//