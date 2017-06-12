#include "Pokitto.h"
#include <vector>
#include "sprites.h"
#include "mapgen.c"
#include "classes.cpp"

#define SEED 32 //Change this value for unique map every time. Hoping for RTC on Hardware!

bool solid(char map[][MAPSIZE],int x, int y){
    return map[y][x]==1 || map[y][x]==2;
}

void addDecent(char map[][MAPSIZE]){
    int x=random(1,MAPSIZE-1);
    int y=random(1,MAPSIZE-1);
    if (!solid(map,x,y) && !solid(map,x-1,y) && !solid(map,x+1,y) && !solid(map,x,y-1) && !solid(map,x,y+1)) {
        map[y][x]=4;
    }
    else {
        addDecent(map);
    }
}

Pokitto::Core game;
int playerX = 4;
int playerY = 4;


void Ent::draw(){ //Classes are not implemented yet. This wont work either
    game.display.drawBitmap(playerX-x*14,playerY-y*14,sprites[id]);
}

char dungeon[MAPSIZE][MAPSIZE];

#define ID_SKELETON_MAGE     9+3
#define ID_SKELETON_ARCHER   10+3
#define ID_SKELETON_WARIOR   11+3
#define ID_BLOOD_SKELETON    12+3
#define ID_BLOOD             13+3
#define ID_RAT               14+3
#define ID_SCROLL            15+3
#define ID_CHEST             16+3
#define ID_CHEST_OPEN        17+3
#define ID_MIMIC             18+3
#define ID_COIN              19+3
#define ID_COINS             20+3
#define ID_BAG               21+3

//globals
//std::vector<entity> entities(entities_size);
char printer[40] = "";
int playerGold = 0;
int playerHP = 100;


void drawHP(int hp){
    //gui
        game.display.drawBitmap(212,0,UI1);
        game.display.drawFastVLine(219,3,158);
        game.display.drawFastVLine(211,3,158);
        game.display.drawBitmap(212,162,UI2);
        int UI_hp = hp * 0.78;

        if(hp >= 0){
            for(int i = 0; i < UI_hp; i++){
                game.display.drawBitmap(213,159-(i*2),UI4);
            }
            game.display.drawBitmap(213,160-((UI_hp+1)*2),UI3);
            game.display.drawBitmap(213,161,UI5);
        }
}
using namespace std;
int main () {
srand(SEED);
mapinit(dungeon,MAPSIZE,MAPSIZE);
mapgen(dungeon,MAPSIZE,MAPSIZE,0,0,MAPSIZE-1,MAPSIZE-1);
mappretty(dungeon,MAPSIZE,MAPSIZE);
addDecent(dungeon);
std::vector<Ent> ents;
ents.push_back(Ent{3,3});
game.begin();
//mapgen(0,0,0,20,20);
game.display.loadRGBPalette(paletteCGA);
//game.display.setFont(fontAdventurer);
//game.display.persistence = true;
game.display.setInvisibleColor(0);


while (game.isRunning()) {

    if (game.update()) {
        if (game.buttons.repeat(BTN_UP,4)){
            if (!dungeon[playerY-1][playerX]){
                playerY --;
            }
        }
        if (game.buttons.repeat(BTN_DOWN,4)){
            if (!dungeon[playerY+1][playerX]){
                playerY ++;
            }
        }
        if (game.buttons.repeat(BTN_LEFT,4)){
            if (!dungeon[playerY][playerX-1]){
                playerX --;
            }
        }
        if (game.buttons.repeat(BTN_RIGHT,4)){
            if (!dungeon[playerY][playerX+1]){
                playerX ++;
            }
        }
        for(int x =playerX-7; x<playerX+8; x++){ //7
            for(int y =playerY-6; y<playerY+6; y++){
                if(x >= 0 && y >= 0 && x <MAPSIZE && y < MAPSIZE){
                    game.display.drawBitmap(14*(x-playerX+7),14*(y-playerY+6),sprites[dungeon[y][x]]);
                }
            }
        }

        game.display.setCursor(0,168);
        game.display.color = 1;
        game.display.print(printer);



        drawHP(playerHP);
        ents[0].draw();

        game.display.drawBitmap(14*(7),14*(6),sprites[6]);
    }

}

return 1;
}

