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
	sleep(1);
	system("clear");
	
}

unsigned long long movedownPiece(unsigned long long Map, int current, int depth) {
	
	unsigned long long current_long=0b0000000000000000000000000000000000000000000000000000000000000000;
	current_long=current_long|current;
	current_long = current_long << (6-depth)*8;
	
	ShowMap(current_long);

	if(1) {
		Map=Map|current_long;
		return Map;
	}else {
		return 0;
	}
}

int shiftPiece(int Piece, int move) {
	int mask=0b00000000000000001000000000000001;
	if(move>0) {
		while(move!=0 && mask&Piece==0) {
			move--;
			Piece=Piece>>1;
		}	
	}
	else {
		while(move!=0 && mask&Piece==0) {
			move++;
			Piece=Piece<<1;
		}
	}
	return Piece;
}

int main() {
	
	unsigned long long Map, Stable_Map;
	int Nr_pieces;
	int Pieces[10][10];

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

			Pieces[i][0]= shiftPiece(Pieces[i][0], Pieces[i][j]);
			Map = movedownPiece(Stable_Map, Pieces[i][0], j-1);
			ShowMap(Map);

		}
	}

}
