#include <stdio.h>
int main() {
	for(int i = 0; i < 10; i++) {
		if(i%2 == 0){
			i++;
			continue;
		}
		printf("%d ", i);
	}
	printf("end!\n");


	return 0;
}
