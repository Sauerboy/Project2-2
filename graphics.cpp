// The graphics class file
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "graphics.h"
#include "globals.h"



///////////////////////////////////////////
// Drawing Images based on Characters
///////////////////////////////////////////



//Function to draw images based on characters
// - The function takes an image array and changes the color 
//   labeled by a character to a hex value (ex: 'Y' -> 0xFFF00)
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        //You can add more characters by defining their hex values above
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'B') colors[i] = BLUE;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_game_over() {
    uLCD.background_color(YELLOW);
    uLCD.cls();
    uLCD.locate(2, 5);
    uLCD.printf("You Win!");
}

///////////////////////////////////////////
//Simple drawing of objects using uLCD methods
///////////////////////////////////////////

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}
void draw_gold(int u, int v) {
    uLCD.filled_rectangle(u, v, u+10, v+10, YELLOW);
}
void draw_water(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLUE);
}

void draw_fire(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, RED);
}

void draw_tofu(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, PURPLE);
}

void draw_player(int u, int v, int key, bool hat)
{
    if (key)
    {
        uLCD.filled_rectangle(u, v, u+11, v+11, YELLOW);
    }
    else if (hat) {
        draw_hat(u, v);
    } else {
        uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    }
}


void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_enemy(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_door(int u, int v)
{
    draw_nothing(u,v);
    uLCD.line(u, v+6, u+11, v+6, 0xFFFF00);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

///////////////////////////////////////////
//Sprite drawing of objects using draw_img function
///////////////////////////////////////////

void draw_plant(int u, int v)
{
    const char* img = 
        "           "
        " GGGGGGGG  "
        " GGGGGGGGG "
        "GGGGGGGGGGG"
        "GGGGGGGGGGG"
        " GGGGGGGG  "
        "    DD     "
        "    DD     "
        "    DD     "
        "   DDDDD   "
        "  D  D  D  ";
    draw_img(u, v, img);
}

void draw_exclamation_mark(int u, int v)
{
    const char* img = 
        "    YYY    "
        "    YYY    "
        "    YYY    "
        "    YYY    "
        "    YYY    "
        "    YYY    "
        "    YYY    "
        "           "
        "           "
        "    YYY    "
        "    YYY    ";
    draw_img(u, v, img);
}

void draw_hat(int u, int v)
{
    const char* img = 
        "PPPPPPPPPPP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PGGGGGGGGGP"
        "PPPPPPPPPPP";
    draw_img(u, v, img);
}

void draw_npc(int u, int v)
{
    const char* img = 
        "     R     "
        "    RRR    "
        "   RRRRR   "
        "  RRRRRRR  "
        " RRRRYRRRR "
        "RRRRYYYRRRR"
        " RRRRYRRRR "
        "  RRRRRRR  "
        "   RRRRR   "
        "    RRR    "
        "     R     ";
    draw_img(u, v, img);
}

void draw_npc2(int u, int v)
{
    const char* img = 
        "     P     "
        "    PGP    "
        "   PGGGP   "
        "  PGGGGGP  "
        " PGGGGGGGP "
        "PGGGGGGGGGP"
        " PGGGGGGGP "
        "  PGGGGGP  "
        "   PGGGP   "
        "    PGP    "
        "     P     ";
    draw_img(u, v, img);
}

void draw_stairs(int u, int v)
{
    const char* img =
        "        333"
        "        353"
        "      33333"
        "      35553"
        "    3333333"
        "    3555553"
        "  333333333"
        "  355555553"
        "33333333333"
        "35555555553"
        "33333333333";
    draw_img(u, v, img);
}



////////////////////////////////////////////
//Examples of Piskel sprite C array export
////////////////////////////////////////////

void draw_buzz(int u, int v)
{

int new_piskel_data[121] = {
0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xff0000ff, 0xff606060, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff0000ff, 0xffffffff, 0xff0000ff, 0xffffffff, 0xffffffff, 0x00000000, 0x00000000, 
0x00000000, 0xffffff00, 0xffffff00, 0xffffff00, 0xff0000ff, 0xff0000ff, 0xff606060, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff137bff, 0xffffffff, 0x00000000, 0x00000000, 
0xff137bff, 0x00000000, 0xff137bff, 0xff58110c, 0xff58110c, 0xff58110c, 0xffffff00, 0xff58110c, 0xff137bff, 0x00000000, 0x00000000, 
0x00000000, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0xffffff00, 0xff137bff, 0xff137bff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0xffffff00, 0xffffff00, 0xff58110c, 0xff58110c, 0xff58110c, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff58110c, 0xffffff00, 0xffffff00, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}

void draw_boss(int u, int v)
{

int new_piskel_data[121] = {
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
0xff000000, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff000000,
0xff27abb6, 0xff27abb6, 0xff000000, 0xff000000, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff000000, 0xff000000, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xffdf9a1a, 0xffdf9a1a, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xffdf9a1a, 0xffdf9a1a, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6,
0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6, 0xff27abb6
};

   uLCD.BLIT(u,v, 11,11, new_piskel_data);
        
}


///////////////////////////////////////////
//Other sprites
///////////////////////////////////////////

void draw_cave1(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave2(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}
void draw_cave3(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333000"
        "33333333000"
        "33333333000";
    draw_img(u, v, img);
}
void draw_cave4(int u, int v)
{
    const char* img =
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333"
        "33333333333";
    draw_img(u, v, img);
}


void draw_mud(int u, int v)
{
   const char* img = 
        "DDDDDDDDDDD"
        "DDD3333DD3D"
        "D33D33D33DD"
        "D3DDD33D33D"
        "DD333D333DD"
        "D33D33DDDD"
        "DDD333D333D"
        "DD3DDD3DD3D"
        "D3D333D33DD"
        "DDDDD33DDDD"
        "DDDDDDDDDDD";
    draw_img(u, v, img);
}

void draw_earth(int u, int v)
{
   const char* img = 
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD"
        "DDDDDDDDDDD";
    draw_img(u, v, img);
}

