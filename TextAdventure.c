#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct info{
    int location;
    char name[15];
    char description[600];
};

struct game{
    struct info items[15];
    struct info traps[4];
    struct info rooms[5];
    struct info uses[6];
};

void ENTER(int n){
    int c;
    if (n){
        printf(" Press Enter to continue...");
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
    }
    else{
        printf(" Press Enter to continue...");
        while (getchar() != '\n');
        getchar(); 
    }
    printf("\n");
}

void FOREST_INTRO(){
    printf(" Jake, Lily, and Mark, all walk in silence, except for crunching leaves underfoot.\n"
    " Moonlight barely slips through the twisted branches.\n"
    " Up ahead, a house appears, ancient, crooked, wrong.\n"
    " They stop. Windows dark, door half open. No one speaks.\n"
    " A cold breeze pushes at their backs, like a whisper: go in.\n");
    
    ENTER(1);

    printf(" They stare at the house, unsure.\n"
    " “It’s probably abandoned,” one says.\n"
    " “Let’s just peek inside,” another whispers.\n"
    " They argue—joking, daring, hesitating.\n"
    " Finally, they agree: one of them will go first.\n");
}

int CHOOSE_PLAYER(int player, int *inventory_spaces, struct game *objects, int *light){
    printf(" Jake – The Brave One\n"
    " Carries a sturdy wooden bat.\n"
    " Quick to act, not big on plans.\n"
    " Inventory Slots: 3\n\n"

    " Lily – The Cautious One\n"
    " Holds a dim but reliable flashlight.\n"
    " Prefers to think before she moves.\n"
    " Inventory Slots: 2\n\n"

    " Mark – The Prepared One\n"
    " Wears a backpack with a bandage inside.\n"
    " Likes to be ready for anything.\n"
    " Inventory Slots: 4\n\n");

    char name[5];

    while (player != 1 && player != 2 && player != 3){
        printf(" Who will go in first?\n ");
        scanf("%s", name);

        if (strcasecmp(name, "Jake") == 0){
            player = 1;
            *inventory_spaces = 3;
            objects->items[12].location = 5;
        }
        else if (strcasecmp(name, "Lily") == 0){
            player = 2;
            *inventory_spaces = 2;
            *light = 1;
            objects->items[13].location = 5;
        }
        else if (strcasecmp(name, "Mark") == 0){
            player = 3;
            *inventory_spaces = 4;
            objects->items[14].location = 5;
        }
        else{
            printf(" Invalid player name, try again.\n");
        }
    }
    return player;
}

void ENTER_HOUSE(int player){
    if (player == 1){
        printf("\n Jake grips his bat, pushes the door, and steps inside without a word. It slams shut behind him.\n");
    }
    else if (player == 2){
        printf("\n Lily flicks on her flashlight, takes a deep breath, and enters. The door creaks closed on its own.\n");
    }
    else{
        printf("\n Mark adjusts his backpack, mutters “Here goes nothing,” and walks in. The door clicks shut behind him.\n");
    }
    
}

void COMMANDS_LIST(){
    printf(" COMMANDS\n"
    " - go north/east/south/west.....| move from room to room with directions\n"
    " - inspect [object name]/room...| desccription of room and objects both in inventory and room\n"
    " - use [object name]............| some objects are usable, find out what everything does\n"
    " - drop [object name]...........| drops objects from inventory into current room\n"
    " - help please..................| shows this commands list again\n"
    " - quit game....................| it's game over, your brain can't handle the adrenaline\n"
    " * all commands are case insensitive\n");
}

void COMMANDS(int room, char command[], char action[]){
    printf(" CHOOSE ACTION  :  ");
    scanf("%s %s", command, action);
    printf("\n");
}

void LIFES(int lifes, int *game_over){
    if (lifes == 1){
        printf(" A sharp pain shoots through you.\n You're hurt, but still standing.\n");
    }
    else if (lifes == 0){
        printf(" Pain overwhelms you, can't go on.\n Everything fades as the house swallows you whole..\n");
        *game_over = 1;
    }
}

void ROOM(int room, struct game *objects, int *lifes, int *game_over, int light){
    if (room == 0){    
        printf("%s\n", objects->rooms[room].description);}
    else if (room == 1){
        printf("%s\n", objects->rooms[room].description);}
    else if (room == 2){
        printf("%s\n", objects->rooms[room].description);}
    else if (room == 3){
        if (objects->traps[2].location == 3 && !light){
            printf("%s", objects->traps[2].description);
            (*lifes)--;
            LIFES(*lifes, game_over);
            objects->traps[2].location = 6;
        }
        printf("%s\n", objects->rooms[room].description);}
    else if (room == 4){
        if (objects->traps[3].location == 4){
            if (objects->items[12].location == 5){
                printf(" Bats swarm out of the darkness, screeching wildly.\n You are able to swing the bat with force.\n The creatures scatter, fleeing up the stairs and out breaking a window.\n");
            }
            else{
                printf("%s", objects->traps[3].description);
                (*lifes)--;
                LIFES(*lifes, game_over);
                objects->traps[3].location = 6;
            }
        }
        printf("%s\n", objects->rooms[room].description);}
}

void GO(char direction[15], int *room, struct game *objects, int *lifes, int *game_over, int bathroom, int *basement, int exit, int code, int *win, int light){
    if (*room == 0){
        if (strcasecmp(direction, "north") == 0){    
            printf(" You step into the kitchen, where stale air and shadows cling to empty shelves.\n");
            *room = 1;
            ROOM(*room, objects, lifes, game_over, light);}
        else if (strcasecmp(direction, "east") == 0){
            printf(" You push the door open and step into the cold, silent bedroom.\n");
            *room = 2;
            ROOM(*room, objects, lifes, game_over, light);}
        else if (strcasecmp(direction, "west") == 0){
            if (*basement){
                if (objects->traps[3].location == 4){
                    char confirmation[5];
                    printf(" As you take the first steps down, a noise increasingly echoes up from the darkness.\n");
                    printf(" Do you want to continue (yes/no): ");
                    scanf("%s", confirmation);
                    if (strcasecmp(confirmation, "yes") == 0){
                        printf(" You descend the dark wooden stairs, each step creaking into the damp, heavy air below.\n");
                        *room = 4;
                        ROOM(*room, objects, lifes, game_over, light);
                    }
                    else{
                        printf(" You back off to the living room, when suddenly bats swarm up the stairs.\n Bursting past you and shattering a window as they escape.\n You duck just in time.\n The darkness now lies quiet.\n");
                        objects->traps[3].location = 6;
                    }
                }
                else{
                    printf(" You descend the dark wooden stairs, each step creaking into the damp, heavy air below.\n");
                    *room = 4;
                    ROOM(*room, objects, lifes, game_over, light);
                }
            }
            else {
                int password;
                printf(" You tug the handle, but it won’t budge.\n A 4-digit lock keeps the basement door sealed.\n Enter the code: ");
                scanf("%d", &password);
                if (code == password){
                    printf(" The lock clicks open.\n The door creaks slowly, revealing the dark wooden stairs descending below.\n");
                    *basement = 1;}
                else
                    printf(" You enter the code *click*.\n Nothing happens. Still locked.\n");
            }          
        }
        else if (strcasecmp(direction, "south") == 0){
            if (!exit)
                printf(" You reach for the front door, but it’s sealed tight.\n It won’t open, something’s keeping you inside.\n");
            else{
                *win = 1;
                printf(" You step through the front door into the cool night.\n Free at last from the house’s grip.\n");
            }
        }
        else{
            printf(" Can't go in that direction\n");}
    }
    else if (*room == 1){
        if (strcasecmp(direction, "west") == 0){
            printf(" You approach the window, but it’s too small and too high.\n There’s no way out that way\n");}
        else if (strcasecmp(direction, "south") == 0){
            printf(" You step into the living room. Back to the starting point.\n");
            *room = 0;
            ROOM(*room, objects, lifes, game_over, light);}
        else{
            printf(" Can't go in that direction\n");}
    }

    else if (*room == 2){
        if (strcasecmp(direction, "north") == 0){
            if (bathroom){
                if (!light && objects->traps[2].location == 3){
                    char confirmation[5];
                    printf(" It’s pitch black inside. You can’t see a thing.\n It’s too dangerous to enter without light.\n");
                    printf(" Do you want to continue (yes/no): ");
                    scanf("%s", confirmation);
                    if (strcasecmp(confirmation, "yes") == 0){
                        printf(" You step into the bathroom, the air damp and heavy, water slick beneath your feet.\n");
                        *room = 3;
                        ROOM(*room, objects, lifes, game_over, light);}
                    else{
                        printf(" You decide to back out and look for other options");
                    }
                }
                else if (!light && objects->traps[2].location == 6){
                    printf(" You step carefully into the bathroom, remembering the slippery floor beneath.\n");
                    *room = 3;
                    ROOM(*room, objects, lifes, game_over, light);
                }
                else{
                    printf(" You step into the bathroom.\n With your light on, you spot the puddles and step around them, avoiding the slippery floor.\n");
                    *room = 3;
                    ROOM(*room, objects, lifes, game_over, light);
                }
            }
            else
                printf(" You pull on the door, but it won’t open, something’s caught in the latch.\n You notice a sharp object could help.\n");
        }
        else if (strcasecmp(direction, "east") == 0){
            printf(" You reach the window, but rusty iron bars block the way.\n There’s no scape through here.\n");}
        else if (strcasecmp(direction, "west") == 0){
            printf(" You step into the living room. Again at the beginning.\n");
            *room = 0;
            ROOM(*room, objects, lifes, game_over, light);}
        else{
            printf(" Can't go in that direction\n");}
    }

    else if (*room == 3){
        if (strcasecmp(direction, "south") == 0){    
            printf(" You carefully pull the door open and step into the cold, silent bedroom.\n");
            *room = 2;
            ROOM(*room, objects, lifes, game_over, light);}
        else{
            printf(" Can't go in that direction\n");}
    }

    else if (*room == 4){
        if (strcasecmp(direction, "east") == 0){    
            printf(" You step into the living room. Where the nightmare began.\n");
            *room = 0;
            ROOM(*room, objects, lifes, game_over, light);}
        else{
            printf(" Can't go in that direction\n");}
    }
}

int INVENTORY_SPACES(int inventory_spaces, struct game *objects){
    for (int i = 0; i < 15; i++){
        if (objects->items[i].location == 5) inventory_spaces--;}
    if (inventory_spaces > 0){
        return 1;
    }
    else{
        return 0;
    }
}

void INSPECT(char object[15], struct game *objects, int room, int inventory_spaces, int *lifes, int *game_over, int *light){
    int found = 0;
    for (int i = 0; i < 15; i++){
        if (strcasecmp(object, objects->items[i].name) == 0){
            if (objects->items[i].location == 5){    
                printf("\n\n%s\n%s\n\n", objects->items[i].name, objects->items[i].description);
                found = 1;}
            else if (objects->items[i].location == room){
                printf("\n%s\n", objects->items[i].description);
                found = 1;
                char take[3];
                printf(" Would you like to grab the %s (yes/no): ", object);
                scanf("%s", take);
                if (strcasecmp(take, "yes") == 0){
                    int avilability = INVENTORY_SPACES(inventory_spaces, objects);
                    if (avilability){
                        objects->items[i].location = 5;
                        printf(" You took the %s\n", object);
                        if (i == 0 && objects->items[4].location == 6)
                            *light = 1;
                        else if (i == 13)
                            *light = 1;
                    }
                    else{
                        printf(" You can't carry any more objects. Left the %s where you found it\n", object);
                    }
                }
                else{
                    printf(" You left the %s where you took it from.\n", object);
                }
            }
            
        }
    }
    if (!found){
        for (int i = 0; i < 4; i++){
            if (strcasecmp(object, objects->traps[i].name) == 0 && objects->traps[i].location == room){
                printf("\n%s\n", objects->traps[i].description);
                found = 1;
                objects->traps[i].location = 6;
                (*lifes)--;
                LIFES(*lifes, game_over);
            }
        }
    }
    if (!found){
        if (strcasecmp(object, "room") == 0){
            printf("\n%s\n", objects->rooms[room].description);
            found = 1;
        }
    }
    if (!found){
        printf(" The %s was not found in your pocket or in the room.\n", object);
    }
}

void USE(char object[15], int room, struct game *objects, int *light, int *lifes, int *bathroom, int *exit, int *game_over){
    int found = 0;
    int n;
    for (int i = 0; i < 15; i++){
        if (strcasecmp(object, objects->items[i].name) == 0 && (objects->items[i].location == room || objects->items[i].location == 5)){
            found = 1;
            n = i;
        }
    }
    if (!found){
        for (int i = 0; i < 4; i++){
            if (strcasecmp(object, objects->traps[i].name) == 0 && objects->traps[i].location == room){
                printf("%s", objects->traps[i].description);
                objects->traps[i].location = 6;
                (*lifes)--;
                LIFES(*lifes, game_over);
                return;                
            }
        }
    }
    if (found){
        int usable = 0;
        for (int i = 0; i < 6; i++){
            if (strcasecmp(object, objects->uses[i].name) == 0){
                usable = 1;
                if (objects->uses[i].location == 5){

                    if (i == 2){
                        if (objects->items[0].location == 5){
                            printf("%s", objects->uses[i].description);
                            objects->uses[i].location = 6;
                            objects->items[n].location = 6;
                            *light = 1;
                        }
                        else{
                            printf(" You have nothing to light up with the matches.\n");
                        }
                    }
                    else if (i == 3){
                        printf("%s", objects->uses[i].description);
                    }
                    else if (i == 1){
                        printf("%s", objects->uses[i].description);
                        objects->uses[i].location = 6;
                        objects->items[n].location = 6;
                    }
                    else if (i == 5){
                        if (*lifes == 1){
                            printf("%s", objects->uses[i].description);
                            objects->uses[i].location = 6;
                            objects->items[n].location = 6;
                            (*lifes)++;
                        }
                        else{
                            printf(" You can't use the %s whithout being injured.\n", object);
                        }
                    }
                }
                else{
                    if (objects->uses[i].location == room){
                        printf("%s", objects->uses[i].description);
                        objects->uses[i].location = 6;
                        objects->items[n].location = 6;
                        if (i == 0){
                            *bathroom = 1;
                        }
                        else if (i == 4){
                            *exit = 1;
                        }
                    }
                    else{
                        printf(" You can't find anywhere to use the %s in this room\n", object);
                    }
                }
            }
        }
        if (!usable){
            printf(" You don't find any use for the %s\n", object);
        }
    }
    else
        printf(" Can't find the %s to use.\n", object);
}

void DROP(char object[15], struct game *objects, int room, int *light){
    int in_inventory = 0;
    for (int i = 0; i < 15; i++){
        if (strcasecmp(object, objects->items[i].name) == 0 && objects->items[i].location == 5){
            printf(" You left the %s in the current room\n", object);
            objects->items[i].location = room;
            in_inventory = 1;
            if (i == 0 && objects->items[13].location != 5)
                *light = 0;
            else if (i == 13 && (objects->items[4].location != 6 || (objects->items[4].location == 6 && objects->items[0].location != 5)))
                *light = 0;
        }
    }
    if (!in_inventory){
        printf(" Imposible to drop the %s as it is not in your possesion.\n", object);
    }
}

int QUIT(){
    char confirmation[5];
    printf(" Confirm quit to leave the game (yes/no): ");
    scanf("%s", confirmation);
    if (strcasecmp(confirmation, "yes") == 0)
        return 1;
    else
        return 0;
}

void GUI(int part, int room, int light, int lifes, struct game *objects){
    if (part){
        printf("=========================================================\n");
        printf(" LOCATION       :  %s\n", objects->rooms[room].name);
        printf(" LIGHT          :  %s\n", light ? "On" : "Off");
        printf(" STATUS         :  %s\n", (lifes == 1) ? "Injured" : "Healthy");
        printf("---------------------------------------------------------\n");
        printf(" INVENTORY      :  ");
        for (int i = 0; i < 15; i++){
            if (objects->items[i].location == 5)
                printf("%s  ", objects->items[i].name);}
        printf("\n---------------------------------------------------------\n");
        printf(" ROOM OBJECTS   :  ");
        for (int i = 0; i < 15; i++){
            if (objects->items[i].location == room)
                printf("%s  ", objects->items[i].name);
        }
        for (int i = 0; i < 2; i++){
            if (objects->traps[i].location == room)
                printf("%s  ", objects->traps[i].name);
        }
        printf("\n---------------------------------------------------------\n");

    }
    else{
        printf("=========================================================\n");
    }
}

void WIN(){
    printf(" Your friends are just beyond the trees.\n"
    " You emerge into the night, and your friends rush toward you, eyes wide with relief.\n"
    " No words, just the comfort of being together again, safe far away from the house.\n");
}

void GAME_OVER(){
    printf(" This house overwhelmed your brain. Now your soul will be trapped inside the house for eternity.\n");
}

int main(){
    int win = 0;
    int game_over = 0;
    int room = 0;
    int player = 0;
    int inventory_spaces;
    int lifes = 2;
    int light = 0;
    int part;
    int bathroom = 0;
    int basement = 0;
    int exit = 0;
    char command[15] = "";
    char action[15] = "";
    int code = 4729;
    
    struct game objects = {
        .items = {{0, "Candle", " A thick candle, unlit.\n Could provide light if you find a way to light it.\n"}, {0, "Screwdriver", " A sturdy flathead screwdriver.\n Might come in handy for getting things open or removing screws.\n"}, {1, "Knife", " A sharp kitchen knife.\n It might help you open something, or protect yourself, in a pinch.\n"}, {1, "Apple", " A slightly bruised red apple.\n Looks edible, though it’s not very fresh.\n"}, {2, "Matches", " A small box of matches.\n Could light a fire or illuminate dark areas briefly.\n"}, {2, "Football", " A worn-out football.\n Not very useful... unless you're planning a break.\n"}, {2, "Journal", " A dusty personal journal.\n Most pages are torn or illegible, but a few words might still be readable.\n"}, {3, "Letter", " A sealed envelope.\n There's a handwritten code inside—it looks important. Something about a basement...\n"}, {3, "Toothbrush", " An old, slightly bent toothbrush.\n Not much use in your situation, unless you get really desperate.\n"}, {3, "Toiletpaper", " A single roll of toilet paper.\n Clean. Soft. Strangely comforting.\n"}, {4, "Key", " A small metal key.\n It’s labeled “Front Door,” not much else to it.\n"}, {4, "Wine", " A dusty bottle of red wine.\n Probably expired, but you never know, it could still be useful.\n"}, {6, "Bat", " A wooden baseball bat.\n Heavy enough to defend yourself with.\n"}, {6, "Flashlight", " A compact flashlight.\n It works, for now.\n"}, {6, "Bandage", " A clean, rolled bandage.\n Perfect for treating wounds or stopping bleeding.\n"}},
        .traps = {{1, "Cabinets", " You open the cabinets carefully.\n Shadows shift inside.\n Suddenly, plates crash down, smashing at your feet with a deafening clatter.\n"}, {2, "Coat", " You slip on the old coat.\n At first, it’s warm and comforting.\n But suddenly it tightens, choking the air from your lungs.\n You struggle wildly, fighting until you finally tear free, gasping for breath."}, {3, "Slippery floor", " You step blindly and your foot slides on the wet floor.\n Lossing balance and falling hard.\n"}, {4, "Bats", " Suddenly, a swarm of bats flies at you from the shadows.\n You stumble and fall onto the hard wooden corner of the stairs.\n The creatures flee up the stairs and out breaking a window"}},
        .rooms = {{0, "Living room", " Dust dances in the beam of moonlight slipping through a cracked window.\n Old furniture sits like shadows, still and dark.\n Faded wallpaper peels like curling skin.\n Four doors:\n South leads back outside, sealed shut.\n North, east, and west doors stand closed, each hiding what’s beyond.\n"}, {1, "Kitchen", " The air smells faintly of rot and rusted metal.\n Cabinets hang half open, shadows pooling inside.\n A broken fridge hums weakly in the corner.\n A small window to the west is too narrow to escape.\n The door south leads back to the living room.\n"}, {2, "Bed room", " The bed is untouched, but the sheets are wrinkled, like someone just left.\n A cracked mirror leans against the wall, reflecting nothing clearly.\n To the east, a locked window is barred with rusty iron.\n A door to the west leads back to the living room.\n Another door stands closed to the north.\n"}, {3, "Bath room", " No light comes in here—only darkness and cold.\n Water pools on the cracked floor, slippery and deep.\n The smell of mold fills the air.\n The only exit is the door to the south, leading back to the bedroom.\n"}, {4, "Basement", " The air is thick and damp, filled with the scent of decay.\n Shadows cling to old crates stacked against the walls.\n A faint metal glint catches your eye near the cracked floorboards in the corner.\n Unstable wooden stairs lead east, back up to the living room.\n"}},
        .uses = {{2, "Knife", " You insert the knife into the latch and twist.\n With a sharp snap, whatever was stuck gives way.\n The door creaks open.\n"}, {5, "Apple", " You take a bite of the apple. Crisp, sweet, and just a little sour.\n It refreshes you instantly.\n"}, {5, "Matches", " You strike a match, its flame flickering to life.\n Carefully, you light the candle.\n Warm light fills the room, pushing back the shadows.\n"}, {5, "Letter", " If you’re reading this, then maybe you’re still safe.\n\n I bought this house thinking it was a fresh start. Quiet. Remote. Perfect.\n But the noises began the first week, whispers under the floorboards, footsteps at night.\n I thought it was just the wind, or maybe my mind playing tricks on me.\n\n Then I found the door to the basement... and locked it. Whatever's down there isn't natural.\n Sometimes, I hear it breathing.\n\n The code is 4729. Use it only if you must.\n And if you go down, don’t go alone.\n\n M\n"}, {0, "Key", " The lock clicks open.\n The heavy door swings wide to cool night air.\n"}, {5, "Bandage", " You wrap the bandage around the wound, steadying your breath.\n The pain fades away, giving you a moment to catch your strength.\n"}}
    };

    FOREST_INTRO();

    ENTER(1);

    player = CHOOSE_PLAYER(player, &inventory_spaces, &objects, &light);

    ENTER_HOUSE(player);

    ENTER(0);

    ROOM(room, &objects, &lifes, &game_over, light);

    ENTER(1);

    COMMANDS_LIST();

    ENTER(1);

    while (win == 0 && game_over == 0){
        part = 1;
        GUI(part, room, light, lifes, &objects);

        COMMANDS(room, command, action);
        
        if (strcasecmp(command, "go") == 0){
            GO(action, &room, &objects, &lifes, &game_over, bathroom, &basement, exit, code, &win, light);
        }
        else if (strcasecmp(command, "use") == 0){
            USE(action, room, &objects, &light, &lifes, &bathroom, &exit, &game_over);
        }
        else if (strcasecmp(command, "inspect") == 0){
            INSPECT(action, &objects, room, inventory_spaces, &lifes, &game_over, &light);
        }
        else if (strcasecmp(command, "drop") == 0){
            DROP(action, &objects, room, &light);
        }
        else if (strcasecmp(command, "help") == 0){
            COMMANDS_LIST();
        }
        else if (strcasecmp(command, "quit") == 0){
            game_over = QUIT();
        }
        else{
            printf("Command %s %s is invalid.\n", command, action);
        }
        
        part = 0;
        GUI(part, room, light, lifes, &objects);

        ENTER(0);
    }

    if (win){
        WIN();
    }
    else if (game_over){
        GAME_OVER();
    }
    
    printf("\n\nThanks for playing");
    
    return 0;
    
}