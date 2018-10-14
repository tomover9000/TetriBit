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
		mask=mask >> 1;
	}
	sleep(1);
	system("clear");
	
}

int main() {
	
	unsigned long long Map;
	int Nr_pieces;
	


	scanf("%llu", &Map);
	scanf("%d", &Nr_pieces);

	for(int i=0; i<Nr_pieces*8; i++) {
		ShowMap(Map);
	}
}

