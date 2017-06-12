#include <stdio.h>
#include <stdlib.h>

#define MAPSIZE 32

void mapinit(char map[][MAPSIZE], int width, int height);
void mapgen(char map[][MAPSIZE], int mapwidth, int mapheight, int startx, int starty, int endx, int endy);
void mapprint(char map[][MAPSIZE], int width, int height);

void mapinit(char map[][MAPSIZE], int width, int height){
    int i,j;

    //Generate walls around the edges
    for( i = 0; i < width; i++ ){
        map[0][i] = 1;
        map[height-1][i] = 1;
    }
    for( j = 0; j < height; j++ ){
        map[j][0] = 1;
        map[j][width-1] = 1;
    }
}

#define HORIZONTAL 0
#define VERTICAL 1
#define MIN_WIDTH 6
#define MIN_HEIGHT 8
void mapgen(char map[][MAPSIZE], int mapwidth, int mapheight, int startx, int starty, int endx, int endy){
    int i,j,orientation,position,door,doorcount;
    int width = endx-startx;
    int height = endy-starty;

    if( width < MIN_WIDTH && height < MIN_HEIGHT ){
        return;
    }

    //Determine whether we will split the space
    //horizontally or vertically by choosing whichever
    //orientation is larger (this avoids extremely long rooms)
    if( width >= height ){
        //If there is a door (or more than one door!) into a small room,
        //we may not be able to generate a wall in any location!
        //so abort if room is min + number of horiz door tiles
        doorcount = 0;
        for( i = startx; i < endx; i++ ){
            if( map[starty][i] == 0 ) doorcount++;
            if( map[endy][i] == 0 ) doorcount++;
        }
        if( width < MIN_WIDTH + doorcount ){
            return;
        }
        orientation = VERTICAL;
        //puts("Trying vertical");
    }else{
        //If there is a door (or more than one door!) into a small room,
        //we may not be able to generate a wall in any location!
        //so abort if room is min + number of vert door tiles
        doorcount = 0;
        for( i = starty; i < endy; i++ ){
            if( map[i][startx] == 0 ) doorcount++;
            if( map[i][endx] == 0 ) doorcount++;
        }
        if( height < MIN_HEIGHT + doorcount ){
            return;
        }
        orientation = HORIZONTAL;
        //puts("Trying horizontal");
    }
    //printf("startx %d, starty %d\n",startx,starty);
    //mapprint(map,MAPSIZE,MAPSIZE);
    position = -1;
    if( orientation == HORIZONTAL ){
        //Make sure the position is valid:
        //1. It must have generated at least one number
        //2. It must not be too close to existing walls
        //3. It must not be over a door
        while( position == -1 || position < starty + (MIN_HEIGHT/2) || position > endy - (MIN_HEIGHT/2) || map[position][startx] == 0 || map[position][endx] == 0 ){
            position = starty + (rand()%height);
        }
        //Generate a door at a random position
        door = startx + 1 + (rand()%(width-1));
        //printf("HORIZ %d\n",position);
        for( i = startx; i < startx + width; i++ ){
            if( i != door )
                map[position][i] = 1;
        }
        //Recursively call to fill the two new spaces we generated
        mapgen(map, mapwidth, mapheight, startx, starty, endx,position);
        mapgen(map, mapwidth, mapheight, startx, position, endx, endy);
    }else if( orientation == VERTICAL ){
        //Make sure the position is valid:
        //1. It must have generated at least one number
        //2. It must not be too close to existing walls
        //3. It must not be over a door
        while( position == -1 || position < startx + (MIN_WIDTH/2) || position > endx - (MIN_WIDTH/2) || map[starty][position] == 0 || map[endy][position] == 0 ){
            position = startx + (rand()%width);
        }
        //Generate a door at a random position
        //(allocating space for it to be 2 high)
        door = starty + 1 + (rand()%(height-2));
        //printf("VERT %d\n",position);
        for( i = starty; i < starty + height; i++ ){
            if( i != door && i != door+1 )
                map[i][position] = 1;
        }
        //Recursively call to fill the two new spaces we generated
        mapgen(map, mapwidth, mapheight, startx, starty, position,endy);
        mapgen(map, mapwidth, mapheight, position, starty, endx, endy);
    }
}

void mapprint(char map[][MAPSIZE], int width, int height){
    int i,j;

    for( i = 0; i < height; i++ ){
        for( j = 0; j < width; j++ ){
            if( map[i][j] == 0 ){
                printf("0");
            }else if( map[i][j] == 1 ){
                printf("1");
            }
        }
        puts("");
    }
}

void mappretty(char map[][MAPSIZE],int width, int height){
    int i,j;
    for (i=0; i < height-1; i++) {
        for (j=0;j<width-1;j++){
            if (map[i][j]==1 && map[i+1][j]==0){
                map[i+1][j]=2;
            }
        }
    }
}


//char map[MAPSIZE][MAPSIZE];

/*
int main(int argc, char** argv){
    srand(42);//Can choose the seed to get the same map every time

    mapinit(map,MAPSIZE,MAPSIZE);
    mapgen(map,MAPSIZE,MAPSIZE,0,0,MAPSIZE-1,MAPSIZE-1);

    mapprint(map,MAPSIZE,MAPSIZE);
}
*/

