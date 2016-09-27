#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "cs50.h"

 char* first;   //first of 2 buffers used to store postion values
 char* second;  //second of 2 buffers used to store position values
 int flip_flop; //switch to indicate which buffer positions should be added to

//takes in position [y, x]. if flip_flop==1 add to first, else add to second
void add_to_buffer(int x, int y);

//prevMoves: 1=Up, 2=Down, 3=Right, 4=Left
// check possible move directions
bool checkMoves(int height, int width, char map[1000][1000], int x, int y, 
    int prevMove, int steps, int* finalsteps)
{
    //if we've already solved the maze in fewer steps then return
	if(steps > *finalsteps) {
		return false;
	}
    //if outside the edges of the maze then return false
    if((x > (width-1)) || (x < 0) || (y > (height-1)) || (y < 0)) {
		return false;
	}
    //if not on a blank space char then return false
	if(map[y][x] != 32) {
		return false;
	}
    //if at the end save position, mark #steps, return true
	if((x == (width-2)) && (y == (height-2))) {
        sprintf(first, "[%d, %d]\n", (y-1)/2, (x-1)/2);
		*finalsteps = steps;
		return true; 
	}
	
 	//move down
 	if(prevMove != 1) {
        //make sure char above is not a '-' to be sure we did not jump a wall
        if(map[y+1][x] != 45) {
            if(checkMoves(height, width, map, x, y+2, 2, steps+1, finalsteps)){
                //if the end was found, add position to appropriate buffer
                add_to_buffer(x, y);
                return true;
            }
        }
 	}
    //move up
 	if(prevMove != 2) {
        //make sure char below is not '_' to be sure we did not jump a wall
        if(map[y-1][x] != 45) {
            if(checkMoves(height, width, map, x, y-2, 1, steps+1, finalsteps)){
                //if the end was found, add position to appropriate buffer
                add_to_buffer(x, y);
                return true;
            }
        }
 	}
    //move right
 	if(prevMove != 3) {
        //make sure char to left is not '|' to be sure we did not jump a wall
        if(map[y][x+1] != 124) {
            if(checkMoves(height, width, map, x+2, y, 4, steps+1, finalsteps)){
                //if the end was found, add position to appropriate buffer
                add_to_buffer(x, y);
                return true;
            }
        }
 	}
    //move left
 	if(prevMove != 4) {
        //make sure char to right is not '|' to be sure we did not jump a wall
        if(map[y][x-1] != 124) {
            if(checkMoves(height, width, map, x-2, y, 3, steps+1, finalsteps)){
                //if the end was found, add position to appropriate buffer
                add_to_buffer(x, y);
                return true;
            }
        }
 	}
    
 	return false;
 	
}

//add position x and y to the correct buffer
void add_to_buffer(int x, int y) {
    if(flip_flop == 0) {
        sprintf(second, "[%d, %d]\n", (y-1)/2, (x-1)/2);
        second = realloc(second, strlen(second) + strlen(first)+ 1);
        strcat(second, first);
        flip_flop = 1;
    }
    else {
        sprintf(first, "[%d, %d]\n", (y-1)/2, (x-1)/2);
        first = realloc(first, strlen(second) + strlen(first)+ 1);
        strcat(first, second);
        flip_flop = 0;
    }
}


int main(void)
{
    first = malloc(10);
    second = malloc(10);
    flip_flop = 0;
    
    int height = 0;
    string line;
    line = GetString();
    int width = strlen(line);
    char map[1000][1000];
    
    // take in first line
    for(int i=0; i < width; i++) {
    	map[0][i] = line[i];
    }
    height++;
    // take in remaining lines for map
    while((line = GetString()) != NULL) {
    	for(int i=0; i < width; i++) {
    		map[height][i] = line[i];
    	}
    	height++;
    }
    
    //print the step in order
    int finalsteps = INT_MAX;
    checkMoves(height, width, map, 1, 1, 2, 0, &finalsteps);
    printf("[0, 0]\n");
    if(flip_flop == 1) {
        printf("%s", first);
    }
    else {
        printf("%s", second);
    }
    return 0;
}
