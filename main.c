/*This is TetriBit
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

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
	printf("\n\n");
	sleep(1);
}

unsigned long long movedownPiece(unsigned long long Map, int current, int depth) {
	
	unsigned long long current_long=0b0000000000000000000000000000000000000000000000000000000000000000;
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
	
	unsigned long long current_long=0b0000000000000000000000000000000000000000000000000000000000000000;
	current_long = current_long|current;
	current_long = current_long << (7-depth)*8;
	int mask;

	if(move>0) {

		mask=0b00000000000000000000000000000001;

		while(move!=0 && (mask&current)==0 && ((current_long>>1)&Map)==0) {
		
			move--;
			current = current>>1;
			current_long = current_long>>1;
	
		}
	}else {
		
  		mask=0b00000000000000001000000000000000;
	
		while(move!=0 && (mask&current)==0 && ((current_long<<1)&Map)==0) {

			move++;
			current = current<<1;
			current_long = current_long<<1;
	
		}
	}
	return current;
}

unsigned long long addPiece(unsigned long long Map, int current, int depth) {
	
	unsigned long long current_long=0b0000000000000000000000000000000000000000000000000000000000000000;
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

			UpperMap = (Map&(mask<<(i+1)*8));
			LowerMap = (Map&(mask>>(8-i)*8));
			//shift the upper one down one line so that we lose the line that was complete
			UpperMap = UpperMap>>8;
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

int main() {
	
	unsigned long long Map, Stable_Map, Prev_Map;
	int Nr_pieces;
	int Pieces[10][10], lastPiece;

	scanf("%llu", &Map);
	scanf("%d", &Nr_pieces);
	Stable_Map = Map;

	for(int i=0; i<Nr_pieces; i++) {
		for(int j=0; j<9; j++) {
			scanf("%d", &Pieces[i][j]);
		}
	}


	for(int i=0; i<Nr_pieces; i++) {
		for(int j=1; j<9; j++) { 

			lastPiece = Pieces[i][0];
			//Display the Map if the current piece moved down
		      	Map = movedownPiece(Stable_Map, Pieces[i][0], j-1);
			if(Map) {
				ShowMap(Map);
			}else {
				//if the piece cant move down, its movement ends
				break;
			}
			
			//Display the Map if the current piece shifted
			Pieces[i][0] = shiftPiece(Stable_Map, Pieces[i][0], Pieces[i][j], j-1);
			if(Pieces[i][0]!=lastPiece) {
	
				//adding the shifted piece to the Map if the piece is shifted ofc
			
				Map = addPiece(Stable_Map, Pieces[i][0], j-1);
				ShowMap(Map);
	
			}

			//Save the previous Map, you never know when u need it :)
			Prev_Map = Map;
		
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

}
