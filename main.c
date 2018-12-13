//This is TetriBit

#include <stdio.h>
#include <unistd.h>
#include <math.h> 
#include <stdlib.h>

int completedLines = 0;

void ShowMap(unsigned long long Map) {

	unsigned long long mask=0b1000000000000000000000000000000000000000000000000000000000000000;
	
	for(int i=0; i<64; i++) {
		if((Map&mask) == 0) {
			printf(".");
		}else {
			printf("#");
		}
		if(i%8==7)
			printf("\n");
		mask=mask>>1;
	}
	printf("\n");
	sleep(1);
}

unsigned long long movedownPiece(unsigned long long Map, int current, int depth) {
	
	unsigned long long current_long=0;
	current_long = current_long|current;
	current_long = current_long << (7-depth)*8;
	
	if((Map&current_long)==0) {
		Map=Map|current_long;
		return Map;
	}else {
		return 0;
	}
}

int shiftPiece(unsigned long long Map, int current, int move, int depth) {
	
	unsigned long long current_long=0, boundries=0;
	current_long = current_long|current;
	current_long = current_long << (7-depth)*8;

	if(move>0) {

		boundries = 0b0000000100000001000000010000000100000001000000010000000100000001;

		while(move!=0 && (boundries&current_long)==0 && ((current_long>>1)&Map)==0) {

			move--;
			current = current>>1;
			current_long = current_long>>1;
	
		}
	}else {

		boundries = 0b1000000010000000100000001000000010000000100000001000000010000000;

		while(move!=0 && (boundries&current_long)==0 && ((current_long<<1)&Map)==0) {

			move++;
			current = current<<1;
			current_long = current_long<<1;

		}
	}
	return current;
}

unsigned long long addPiece(unsigned long long Map, int current, int depth) {
	
	unsigned long long current_long=0;
	current_long = current_long|current;
	current_long = current_long << (7-depth)*8;
	
	Map = Map|current_long;
	return Map;
}

unsigned long long removeCompleteLines(unsigned long long Map) {
	
	unsigned long long mask=0b1111111111111111111111111111111111111111111111111111111111111111, linechecker=0b0000000000000000000000000000000000000000000000000000000011111111, UpperMap, LowerMap;
	int change=0;
	
	for(int i=0; i<8; i++) {

		if((Map&linechecker)==linechecker) {
		//Split Map into 2 Maps(upper and lower) 	
			change = 1;

			completedLines++;

			UpperMap = (Map&(mask<<(i+1)*8));
			if(i == 0) {
				LowerMap = 0;
			} else {
				LowerMap = (Map&(mask>>(8-i)*8));
			}
			
			UpperMap = UpperMap >> 8;
			Map = UpperMap|LowerMap;			
			i--;
		}else {
			linechecker = linechecker<<8;
		}
		
	}
	
	if(change)
		return Map;
	else
		return 0;
}

int numberOfZeros(unsigned long long Map) {
	
	unsigned long long mask = 1;
	int zeros = 0;

	for(int i = 0; i < 64; i++) {
		if((Map&mask) == 0) {
			zeros++;	
		}
		mask = mask << 1;
	}
	return zeros;
}

int main() {
	
	unsigned long long Map, Stable_Map, Prev_Map;
	int Nr_pieces;
	int Pieces[50][10], lastPiece, i, j;
	double score = 0;

	scanf("%llu", &Map);
	scanf("%d", &Nr_pieces);
	Stable_Map = Map;

	for(i=0; i<Nr_pieces; i++) {
		for(int j=0; j<9; j++) {
			scanf("%d", &Pieces[i][j]);
		}
	}

	ShowMap(Map);

	for(i=0; i<Nr_pieces; i++) {

		for(j=1; j<9; j++) { 

			lastPiece = Pieces[i][0];
			//movedown returns 0 if theres a collision
			Map = movedownPiece(Stable_Map, Pieces[i][0], j-1);

			if(Map == 0) {
				//show map if there's a part of a piece entering the Map
				if((j == 1) || (j == 2 && Pieces[i][0] > 0b0000000011111111)) {
					ShowMap(Prev_Map);
					Stable_Map = Prev_Map;
				}
				break;
			}
		
			//shift Piece
			Pieces[i][0] = shiftPiece(Stable_Map, Pieces[i][0], Pieces[i][j], j-1);
			Map = addPiece(Stable_Map, Pieces[i][0], j-1);
			ShowMap(Map);
	
			//Save the previous Map, you never know when u need it :)
			Prev_Map = Map;
		
		}
		//Break the loop if the piece didn't make it full onto the screen
		if(j == 1 || (j == 2 && Pieces[i][0] > 0b0000000011111111)) {
			break;
		}
		//display Map again if theres any lines removed
		Map = removeCompleteLines(Prev_Map);
		if(Map) {
			Stable_Map = Map;
			ShowMap(Map);
		}else {
			Stable_Map = Prev_Map;
		}
	}

	//score
	score = sqrt(numberOfZeros(Stable_Map)) + pow(1.25, completedLines);

	printf("GAME OVER! \nScore:%.2f\n", score);

}
