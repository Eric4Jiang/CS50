/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

//global variables
int d;
int spaceX;
int spaceY;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }
    else
    {
        //location of the blankspace in the beginning
        spaceX = d-1;
        spaceY = d-1;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int num = d*d -1; // -1 to include for the blank space
    
    //initializes number backwards starting from num to 0;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = num;
            num--;
        }
    }
    
    //swaps 1 and 2 if odd number of tiles. GAME UNSOLVABLE otherwise
    if((d*d-1) % 2 == 1)
    {
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //draws blank space
            if(board[i][j] == 0)
                printf("   ");
                
            //adds 0 in front of numbers less than 10. (to look nice)
            else if(board[i][j] - 10 < 0)
                printf("0%i " , board[i][j]);
            
            //all other numbers
            else
                printf("%i ", board[i][j]);
        }
        printf("\n");
    }
}


/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //iterates through to find where the tile is on the board
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //if tile is found
            if(board[i][j] == tile)
            {   
                //if tile is within one space of the space
                if( ((spaceX == (i-1)) && (spaceY == j)) || ((spaceX == (i + 1)) && (spaceY == j)) || 
                ((spaceX == i) && (spaceY == (j+1))) || ((spaceX == i) && (spaceY == (j-1))) )
                {
                    //stores space
                    int blankSpace = 0;
                    
                    //swap space and tile
                    board[spaceX][spaceY] = board[i][j];
                    board[i][j] = blankSpace;
                    spaceX = i;
                    spaceY = j;
                    return true;
                }
            }
        }
    }
    
    
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int tileNum = 1;
    //iterates and check if tiles are in correct order
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] != tileNum) return false;
            tileNum++;
            
            // checks for empty space in last tile
            if(tileNum == d*d) tileNum = 0;
        }
    }
    return true;
}