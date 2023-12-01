//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <math.h>
#include <main.h>
#include "SDFileSystem.h"

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);


/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int px, py;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved;   // flag when game is complete
    bool talked_to_npc;
    bool learned_move; // flag when you've talked to npc
    bool has_item;
    bool has_tofu;
    bool has_hat;

    //You will need to add more flags as needed

} Player;



/////////////////////////
// Get Action
/////////////////////////

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 * Get Actions from User (pushbuttons, and nav_switch)
 * Based on push button and navigation switch inputs, determine which action
 * needs to be performed (may be no action).
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define ATTACK_BUTTON 3
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_UP 6
#define GO_DOWN 7

#define RUN_LEFT 8
#define RUN_RIGHT 9
#define RUN_UP 10
#define RUN_DOWN 11

int get_action(GameInputs inputs)
{
    //******************
    // TODO: Implement
    //******************
    // 1. Check your action and menu button inputs and return the corresponding action value
    if (inputs.b1) {
        return ACTION_BUTTON;
    }
    if (inputs.b2) {
        return MENU_BUTTON;
    }
    if (inputs.b3) {
        return ATTACK_BUTTON;
    }
    // 2. Check for your navigation switch inputs and return the corresponding action value
    if (inputs.ns_up && inputs.b4) {
        return RUN_UP;
    }
    if (inputs.ns_down && inputs.b4) {
        return RUN_DOWN;
    }
    if (inputs.ns_left && inputs.b4) {
        return RUN_LEFT;
    }
    if (inputs.ns_right && inputs.b4) {
        return RUN_RIGHT;
    }

    if (inputs.ns_up) {
        return GO_UP;
    }
    if (inputs.ns_down) {
        return GO_DOWN;
    }
    if (inputs.ns_left) {
        return GO_LEFT;
    }
    if (inputs.ns_right) {
        return GO_RIGHT;
    }
    // If no button is pressed, just return no action value
    return NO_ACTION;
}




/////////////////////////
// Helper Functions:
/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    MapItem* item = NULL;
    

    //******************
    // TODO: Implement
    //******************

    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.

    switch(action)
    {
        case RUN_UP:
            //TODO: Implement
            //1. Check the item north of the player
            if(get_north(Player.x, Player.y)->walkable) {
                Player.y--;
                draw_game(0);
                if (get_north(Player.x, Player.y)->walkable) {
                    Player.py = Player.y;
                    Player.y--;
                }
            }
            //2. Make sure to not walk through walls
            //3. If it is not a wall, the walk up by updating player's coordinates
            break;
            
        case RUN_LEFT:
            //TODO: Implement
            if(get_west(Player.x, Player.y)->walkable) {
                Player.x--;
                draw_game(0);
            if (get_west(Player.x, Player.y)->walkable) {
                Player.px = Player.x;
                Player.x--;
            }
            }
            break;
            
        case RUN_DOWN:
            //TODO: Implement
            if(get_south(Player.x, Player.y)->walkable) {
                Player.y++;
                draw_game(0);
            if (get_south(Player.x, Player.y)->walkable) {
                Player.py = Player.y;
                Player.y++;
            }
            }
            break;
            
        case RUN_RIGHT:
            //TODO: Implement
            if(get_east(Player.x, Player.y)->walkable) {
                Player.x++;
                draw_game(0);
            if (get_east(Player.x, Player.y)->walkable) {
                Player.px = Player.x;
                Player.x++;
            }
            }
            break;

        case GO_UP:
            //TODO: Implement
            //1. Check the item north of the player
            if(get_north(Player.x, Player.y)->walkable) {
                Player.y--;
            }
            //2. Make sure to not walk through walls
            //3. If it is not a wall, the walk up by updating player's coordinates
            break;
            
        case GO_LEFT:
            //TODO: Implement
            if(get_west(Player.x, Player.y)->walkable) {
                Player.x--;
            }
            break;
            
        case GO_DOWN:
            //TODO: Implement
            if(get_south(Player.x, Player.y)->walkable) {
                Player.y++;
            }
            break;
            
        case GO_RIGHT:
            //TODO: Implement
            if(get_east(Player.x, Player.y)->walkable) {
                Player.x++;
            }
            break;
            


        case ACTION_BUTTON:

        if (get_north(Player.x, Player.y)->type == GOLD ||
            get_south(Player.x, Player.y)->type == GOLD ||
            get_east(Player.x, Player.y)->type == GOLD ||
            get_west(Player.x, Player.y)->type == GOLD) {
                return GAME_OVER;
            }
        
        if (get_north(Player.x, Player.y)->type == NPC2 ||
            get_south(Player.x, Player.y)->type == NPC2 ||
            get_east(Player.x, Player.y)->type == NPC2 ||
            get_west(Player.x, Player.y)->type == NPC2) {
                if (!Player.has_hat) {
                const char* lines[3];
                        lines[0] = "Go find the man  ";
                        lines[1] = "with the hat...  ";
                        lines[2] = "AND STEAL IT!!   ";
                        long_speech(lines, 3);
                        return FULL_DRAW;
                } else {
                    speech("Great Job,","Nice Hat!");
                    return FULL_DRAW;
                }
            }
            //******************
            // TODO: Implement
            //******************

            // 1. Check if near NPC, 
            //     - if so, mark the player has talked and give instructions on what to do
            //     - if the game is solved (defeated Buzz), give the player the key
            //     - return FULL_DRAW to redraw the scene
            if (get_north(Player.x, Player.y)->type == NPC) {
                    if (!Player.talked_to_npc) {
                        add_exclamation_mark(Player.x, Player.y-2);
                        draw_game(true);
                        const char* lines [4];
                        lines[0] = "Nice to meet you ";
                        lines[1] = "My name is       ";
                        lines[2] = "Cappello. Come   ";
                        lines[3] = "back for a quest.";
                        long_speech(lines, 4);
                        Player.talked_to_npc = true;
                        add_nothing(Player.x, Player.y-2);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (Player.has_key) {
                        add_exclamation_mark(Player.x, Player.y-2);
                        draw_game(true);
                        speech("Great Job! Go","unlock the door");
                        add_nothing(Player.x, Player.y-2);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (!Player.has_item) {
                    add_exclamation_mark(Player.x, Player.y-2);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "Go acquire tofu   ";
                    lines[1] = "from the ninja Koh";
                    lines[2] = "ler. And I will te";
                    lines[3] = "ach you the tofu  ";
                    lines[4] = "shuriken. You     ";
                    lines[5] = "need this attack  ";
                    lines[6] = "to defeat Aaron   ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    add_nothing(Player.x + (get_east(Player.x, Player.y)->type == NPC ? 1 : 0), Player.y);
                    add_npc(25, 25);
                    add_nothing(Player.x, Player.y-2);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    if (Player.has_item) {
                    add_exclamation_mark(Player.x, Player.y-2);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "I will teach you  ";
                    lines[1] = "tofu shuriken. You";
                    lines[2] = "must harvest poiso";
                    lines[3] = "nous tofu in the  ";
                    lines[4] = "cave. Now, go into";
                    lines[5] = "the cave and      ";
                    lines[6] = "defeat Aaron!     ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    Player.learned_move = true;
                    add_nothing(Player.x, Player.y-2);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    
                    return FULL_DRAW;
                }

                if (get_south(Player.x, Player.y)->type == NPC) {
                    if (!Player.talked_to_npc) {
                        const char* lines [4];
                        lines[0] = "Nice to meet you ";
                        lines[1] = "My name is       ";
                        lines[2] = "Cappello. Come   ";
                        lines[3] = "back for a quest.";
                        long_speech(lines, 4);
                        Player.talked_to_npc = true;
                        return FULL_DRAW;
                    }
                    if (Player.has_key) {
                        speech("Great Job! Go","unlock the door");
                        return FULL_DRAW;
                    }
                    if (!Player.has_item) {
                    const char* lines [7];
                    lines[0] = "Go acquire tofu   ";
                    lines[1] = "from the ninja Koh";
                    lines[2] = "ler. And I will te";
                    lines[3] = "ach you the tofu  ";
                    lines[4] = "shuriken. You     ";
                    lines[5] = "need this attack  ";
                    lines[6] = "to defeat Aaron   ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    add_nothing(Player.x + (get_east(Player.x, Player.y)->type == NPC ? 1 : 0), Player.y);
                    add_npc(25, 25);
                    return FULL_DRAW;
                    }
                    if (Player.has_item) {
                    const char* lines [7];
                    lines[0] = "I will teach you  ";
                    lines[1] = "tofu shuriken. You";
                    lines[2] = "must harvest poiso";
                    lines[3] = "nous tofu in the  ";
                    lines[4] = "cave. Now, go into";
                    lines[5] = "the cave and      ";
                    lines[6] = "defeat Aaron!     ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    Player.learned_move = true;
                    return FULL_DRAW;
                    }
                    
                    return FULL_DRAW;
                }

                if (get_east(Player.x, Player.y)->type == NPC) {
                    if (!Player.talked_to_npc) {
                        add_exclamation_mark(Player.x+1, Player.y-1);
                        draw_game(true);
                        const char* lines [4];
                        lines[0] = "Nice to meet you ";
                        lines[1] = "My name is       ";
                        lines[2] = "Cappello. Come   ";
                        lines[3] = "back for a quest.";
                        long_speech(lines, 4);
                        Player.talked_to_npc = true;
                        add_nothing(Player.x+1, Player.y-1);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (Player.has_key) {
                        add_exclamation_mark(Player.x+1, Player.y-1);
                        draw_game(true);
                        speech("Great Job! Go","unlock the door");
                        add_nothing(Player.x+1, Player.y-2);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (!Player.has_item) {
                    add_exclamation_mark(Player.x+1, Player.y-1);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "Go acquire tofu   ";
                    lines[1] = "from the ninja Koh";
                    lines[2] = "ler. And I will te";
                    lines[3] = "ach you the tofu  ";
                    lines[4] = "shuriken. You     ";
                    lines[5] = "need this attack  ";
                    lines[6] = "to defeat Aaron   ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    add_nothing(Player.x + (get_east(Player.x, Player.y)->type == NPC ? 1 : 0), Player.y);
                    add_npc(25, 25);
                    add_nothing(Player.x+1, Player.y-1);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    if (Player.has_item) {
                    add_exclamation_mark(Player.x+1, Player.y-1);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "I will teach you  ";
                    lines[1] = "tofu shuriken. You";
                    lines[2] = "must harvest poiso";
                    lines[3] = "nous tofu in the  ";
                    lines[4] = "cave. Now, go into";
                    lines[5] = "the cave and      ";
                    lines[6] = "defeat Aaron!     ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    Player.learned_move = true;
                    add_nothing(Player.x+1, Player.y-1);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    
                    return FULL_DRAW;
                }

            if (get_west(Player.x, Player.y)->type == NPC) {
                    if (!Player.talked_to_npc) {
                        add_exclamation_mark(Player.x-1, Player.y-1);
                        draw_game(true);
                        const char* lines [4];
                        lines[0] = "Nice to meet you ";
                        lines[1] = "My name is       ";
                        lines[2] = "Cappello. Come   ";
                        lines[3] = "back for a quest.";
                        long_speech(lines, 4);
                        Player.talked_to_npc = true;
                        add_nothing(Player.x-1, Player.y-1);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (Player.has_key) {
                        add_exclamation_mark(Player.x-1, Player.y-1);
                        draw_game(true);
                        speech("Great Job! Go","unlock the door");
                        add_nothing(Player.x, Player.y-2);
                        draw_game(true);
                        return FULL_DRAW;
                    }
                    if (!Player.has_item) {
                    add_exclamation_mark(Player.x-1, Player.y-1);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "Go acquire tofu   ";
                    lines[1] = "from the ninja Koh";
                    lines[2] = "ler. And I will te";
                    lines[3] = "ach you the tofu  ";
                    lines[4] = "shuriken. You     ";
                    lines[5] = "need this attack  ";
                    lines[6] = "to defeat Aaron   ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    add_nothing(Player.x + (get_east(Player.x, Player.y)->type == NPC ? 1 : 0), Player.y);
                    add_npc(25, 25);
                    add_nothing(Player.x-1, Player.y-1);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    if (Player.has_item) {
                    add_exclamation_mark(Player.x-1, Player.y-1);
                    draw_game(true);
                    const char* lines [7];
                    lines[0] = "I will teach you  ";
                    lines[1] = "tofu shuriken. You";
                    lines[2] = "must harvest poiso";
                    lines[3] = "nous tofu in the  ";
                    lines[4] = "cave. Now, go into";
                    lines[5] = "the cave and      ";
                    lines[6] = "defeat Aaron!     ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    Player.learned_move = true;
                    add_nothing(Player.x-1, Player.y-1);
                    draw_game(true);
                    return FULL_DRAW;
                    }
                    
                    return FULL_DRAW;
                }


            // 2. Check if near a door
            //    - if the player has the key, you win the game
            //    - if not, show speech bubbles that the play needs to get the key 
            //     -return FULL_DRAW to redraw the scene
            if (get_north(Player.x, Player.y)->type == DOOR) {
                    if(Player.has_key) {
                        erase_door(Player.x, Player.y - 1);
                        return FULL_DRAW;
                    }
                    speech("Get a key", "To open this door");
                    return FULL_DRAW;
                }

            if (get_north(Player.x, Player.y)->type == TOFU) {
                Player.has_tofu = true;
                speech("Tofu has been", "farmed");
                erase_tofu(Player.x, Player.y - 1);
                return FULL_DRAW;
            }
            if (get_south(Player.x, Player.y)->type == TOFU) {
                Player.has_tofu = true;
                speech("Tofu has been", "farmed");
                erase_tofu(Player.x, Player.y + 1);
                return FULL_DRAW;
            }
            if (get_east(Player.x, Player.y)->type == TOFU) {
                Player.has_tofu = true;
                speech("Tofu has been", "farmed");
                erase_tofu(Player.x + 1, Player.y);
                return FULL_DRAW;
            }
            if (get_west(Player.x, Player.y)->type == TOFU) {
                Player.has_tofu = true;
                speech("Tofu has been", "farmed");
                erase_tofu(Player.x - 1, Player.y);
                return FULL_DRAW;
            }

            if (get_here(Player.x, Player.y)->type == TOFU) {
                Player.has_tofu = true;
                speech("Tofu has been", "farmed");
                erase_tofu(Player.x, Player.y);
                return FULL_DRAW;
            }

            // 3. Check if on Pete's cave
            //    - if the player has talked to the npc, then start the speech bubble to fight buzz
            //    - set the players coordinates for the small map
            //    - and set the map to the small map
            //     -return FULL_DRAW to redraw the scene
            if (get_here(Player.x, Player.y)->type == CAVE) {
                    if (Player.learned_move) {
                        speech("You must fight", "The mighty Aaron");
                        map_erase(0,0);
                        Player.x = Player.y = 5;
                        set_active_map(1);
                        return FULL_DRAW;
                    } else {
                    const char* lines [3];
                    lines[0] = "Go find Capello   ";
                    lines[1] = "He will teach you ";
                    lines[2] = "hidden tofu arts  ";
                    long_speech(lines, 3);
                        return FULL_DRAW;
                    }
                }

            // 4. Check if on a stairs
            //    - if so, move the player the correct coordinates
            //    - and set the map back to the main big map
            //     -return FULL_DRAW to redraw the scene
            if (get_here(Player.x, Player.y)->type == STAIRS) {
                        speech("Great job!", "Returning home");
                        map_erase(0,0);
                        set_active_map(0);
                        return FULL_DRAW;
                    }

            // Feel free to add more functions as you make the game!

    
            break;
        
        case ATTACK_BUTTON:
            //******************
            // TODO: Implement
            //******************

            // 1. Check if near enemy, 
            //     - if so, mark enemy as defeated
            //      use speech bubbled to show what item was dropped
            //      update the player struct as needed
            //      if enemy is Pete, make sure that the right attack is being used
            //      If pete is defeated, update game as nescessary
            if (get_north(Player.x, Player.y)->type == ENEMY ) {
                    speech("I've been beaten", "Here's some tofu");
                    add_nothing(Player.x, Player.y - 1);
                    playSound((char *)"/sd/oof.wav");
                    Player.talked_to_npc = true;
                    Player.has_item = true;
                    return FULL_DRAW;
                }
            if (get_south(Player.x, Player.y)->type == ENEMY ) {
                    speech("I've been beaten", "Here's some tofu");
                    add_nothing(Player.x, Player.y + 1);
                    playSound((char *)"/sd/oof.wav");
                    Player.talked_to_npc = true;
                    Player.has_item = true;
                    return FULL_DRAW;
                }
            if (get_east(Player.x, Player.y)->type == ENEMY ) {
                    speech("I've been beaten", "Here's some tofu");
                    add_nothing(Player.x + 1, Player.y);
                    playSound((char *)"/sd/oof.wav");
                    Player.talked_to_npc = true;
                    Player.has_item = true;
                    return FULL_DRAW;
                }
            if (get_west(Player.x, Player.y)->type == ENEMY ) {
                    speech("I've been beaten", "Here's some tofu");
                    add_nothing(Player.x - 1, Player.y);
                    playSound((char *)"/sd/oof.wav");
                    Player.talked_to_npc = true;
                    Player.has_item = true;
                    return FULL_DRAW;
                }



            if (get_north(Player.x, Player.y)->type == HATENEMY ) {
                    speech("I've been beaten", "Here's my hat");
                    add_nothing(Player.x, Player.y - 1);
                    Player.has_hat = true;
                    return FULL_DRAW;
                }
            if (get_south(Player.x, Player.y)->type == HATENEMY ) {
                    speech("I've been beaten", "Here's my hat");
                    add_nothing(Player.x, Player.y + 1);
                    Player.has_hat = true;
                    return FULL_DRAW;
            }
            if (get_east(Player.x, Player.y)->type == HATENEMY ) {
                    speech("I've been beaten", "Here's my hat");
                    add_nothing(Player.x + 1, Player.y);
                    Player.has_hat = true;
                    return FULL_DRAW;
            }
            if (get_west(Player.x, Player.y)->type == HATENEMY ) {
                    speech("I've been beaten", "Here's my hat");
                    add_nothing(Player.x - 1, Player.y);
                    Player.has_hat = true;
                    return FULL_DRAW;
            }



            if (Player.has_tofu) {
            for (int i = 0; i < 5; i++) {
            if (get_here(Player.x, Player.y - i)->type == BOSS ) {
                    for (int j = 1; j <= i; j++) {
                        add_tofu(Player.x, Player.y-j);
                        draw_game(true);
                        pc.printf("Throwing Loop");
                    }
                    speech("Tofu no! I've", "been slain!");
                    Player.has_key = true;
                    return FULL_DRAW;
                }
            if (get_here(Player.x, Player.y + i)->type == BOSS ) {
                    for (int j = 1; j <= i; j++) {
                        add_tofu(Player.x, Player.y+j);
                        draw_game(true);
                        pc.printf("Throwing Loop");
                    }
                    speech("Tofu no! I've", "been slain!");
                    Player.has_key = true;
                    return FULL_DRAW;
                }
            if (get_here(Player.x - i, Player.y)->type == BOSS ) {
                    for (int j = 1; j <= i; j++) {
                        add_tofu(Player.x-j, Player.y);
                        draw_game(true);
                        pc.printf("Throwing Loop");
                    }
                    speech("Tofu no! I've", "been slain!");
                    Player.has_key = true;
                    return FULL_DRAW;
                }
            if (get_here(Player.x + i, Player.y)->type == BOSS ) {
                    for (int j = 1; j <= i; j++) {
                        add_tofu(Player.x+j, Player.y);
                        draw_game(true);
                        pc.printf("Throwing Loop");
                    }
                    speech("Tofu no! I've", "been slain!");
                    Player.has_key = true;
                    return FULL_DRAW;
                }
            }
            }

            if (!Player.has_tofu) {
            if (get_north(Player.x, Player.y)->type == BOSS ) {
                    const char* lines [3];
                    lines[0] = "You'll never beat ";
                    lines[1] = "me untill you find";
                    lines[2] = "my weakness       ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    return FULL_DRAW;
                }
            if (get_south(Player.x, Player.y)->type == BOSS ) {
                    const char* lines [3];
                    lines[0] = "You'll never beat ";
                    lines[1] = "me untill you find";
                    lines[2] = "my weakness       ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    return FULL_DRAW;
                }
            if (get_east(Player.x, Player.y)->type == BOSS ) {
                    const char* lines [3];
                    lines[0] = "You'll never beat ";
                    lines[1] = "me untill you find";
                    lines[2] = "my weakness       ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    return FULL_DRAW;
                }
            if (get_west(Player.x, Player.y)->type == BOSS ) {
                    const char* lines [3];
                    lines[0] = "You'll never beat ";
                    lines[1] = "me untill you find";
                    lines[2] = "my weakness       ";
                    long_speech(lines, sizeof(lines)/sizeof(lines[0]));
                    return FULL_DRAW;
                }
            }
            return FULL_DRAW;
        //***********
        // Add more cases as needed
        //***********
        case MENU_BUTTON:
            break;
    }
    
    return NO_RESULT;
}




/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    if (Player.px != Player.x || Player.py != Player.y) {
    update_status(Player.x, Player.y);
    }
    // Draw game border first
    if(init) {
        draw_border();
        update_status(Player.x, Player.y);
        }
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if ( i == 0 && j == 0) // always draw the player
            {
                draw_player(u, v, Player.has_key, Player.has_hat);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);

                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();
}




/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    //Initialize and sets current map to the first map
    Map* map = set_active_map(0);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////

    //Adding random plants
    pc.printf("Adding Plants!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    //Adding extra chamber borders 
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    add_door(33, 10, HORIZONTAL, 4);

    add_gold(31, 1, HORIZONTAL, 8);

    //Adding extra cave to Buzz's evil lair
    pc.printf("Add cave\r\n");
    add_cave(cb_loc[0],cb_loc[1],1,1,5,5);      //Cave is set as a 4x4 block to be bigger
    add_cave(cb_loc[0]+1,cb_loc[1],2,1,5,5);
    add_cave(cb_loc[0],cb_loc[1]+1,3,1,5,5);
    add_cave(cb_loc[0]+1,cb_loc[1]+1,4,1,5,5);

    pc.printf("Initial environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(10, 5);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    add_npc2(21, 21);
    
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project
    add_enemy(15, 10);
    add_hat_enemy(27, 34);


    //Prints out map
    print_map();
}





void init_small_map()
{
    //Sets current map to the second map
    set_active_map(1);


    //***********************************
    // TODO: Implement 
    //***********************************

    // 1. Add walls to the smaller map.
    //    Set the dimensions to be 16x16  <-- you may change to your liking, but must be smaller than the main map
    //    Hint: See how walls are initialized in the main map

    //
    //Adding wall borders 
    pc.printf("Adding Fire!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 10)
    {
        add_fire(i % map_width(), i / map_width());
    }

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    // 2. Add a way to access your special attacks either here or in update_game() or anywhere you feel would be the best
    //
    // 3. Add Boss in the map
    add_boss(5, 12);
    add_tofu(6, 9);

    // You may add any extra characters/items here for your project


    // Add stairs back to main (map 0)
    add_stairs(4, 6, 0, cb_loc[0], cb_loc[1]);
    
}


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");


    uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE  <-- It is a temporary indicator that your LCD is working before you implement your code
    

    // Initialize the maps
    maps_init();
    init_main_map();
    init_small_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.has_key = false;
    Player.game_solved = false;
    Player.learned_move = false;
    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {

        ////////////////////////////////
        // TODO: Implement 
        ////////////////////////////////

        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actually do the game update:
        // 1. Read inputs
        GameInputs in = read_inputs();        
        // 2. Determine action (get_action)       
        int action = get_action(in);
        // 3. Update game (update_game)
        int result = update_game(action);  // Set this variable "result" for the resulting state after update game
        // 3b. Check for game over based on update game result
        if (result == GAME_OVER) {
            break;
        }
        // 4. Draw screen to uLCD
        bool full_draw = false;
        if (result == FULL_DRAW) full_draw = true;
        draw_game(full_draw);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    draw_game_over();

}




/////////////////////////////
//Advanced Features
/////////////////////////////

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        pc.printf("File opened successfully\n");

        //play wav file
        pc.printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        pc.printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    pc.printf("Could not open file for reading - %s\n", wav);
    return;
}
