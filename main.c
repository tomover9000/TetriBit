#include <stdio.h>
#include <math.h>

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
}

int main() {
	
	unsigned long long Map;

	scanf("%llu", &Map);
	ShowMap(Map);	
}
