#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int ary[100][100] = {0};
	int check[2][100] = {0};
	int N, L;
	int result = 0;

	scanf("%d %d", &N, &L);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf(" %d", &ary[i][j]);
		}
	}
	

//testing for row
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N-1; j++) {
			if(abs(ary[i][j] - ary[i][j+1]) < 2)
				check[0][i] = 1;
			else {
				check[0][i] = 0;
				break;
			}
		}
	}
//checking for Column
	for(int  j = 0; j < N; j++) {
		for(int i = 0; i < N-1; i++) {
			if(abs(ary[i][j] - ary[i][j]) < 2)
				check[1][j] = 1;
			else {
				check[1][j] = 0;
				break;
			}
		}
	}

	

	//경사로 체크 for Row
	for(int i = 0; i < N; i++) {
		int temp = 1;
		if(check[0][i] == 1) {
			for(int j = 0; j < N-1; j++) {
				if(ary[i][j] == ary[i][j+1])
					temp++;
				else if(ary[i][j+1] - ary[i][j] == 1) { // 다음칸이 한칸 높을떄
					if(temp >= L) {			//경사로 설치 가능
						temp = 1;
						continue;
					}
					else {
						check[0][i] = 0;
						break;
					}

				}
				else{
					if(ary[i][j+1] != ary[i][j+L+1]) {
						check[0][i] = 0;
						break;
					}
					else {
						temp = 1;
					}	
				}
					
					

			}

					
		}
	}
/*
			for(int j = N; j > 0; j--) {
				if(ary[i][j] == ary[i][j-1])
					temp++;
				else if(ary[i][j-1] - ary[i][j] == 1) { 
					if(temp >= L) {
						temp = 1;
						continue;
					}
					else {
						check[0][i] = 0;
						break;
					}
				}
				else
					temp = 1;
			}
		}
	}
	*/
//올라갔다 내려가는거는 되는데 내려갔다 올라가는 웅덩이 모양이 해결 안됨 시발...
//경사로 체크 for Column
	for(int j = 0; j < N; j++) {
		int temp = 1;
		if(check[1][j] == 1) {
			for(int i = 0; i < N-1; i++) {
				if(ary[i][j] == ary[i+1][j])
					temp++;
				else if(ary[i+1][j] - ary[i][j] == 1) { // 다음칸이 한칸 높을떄
					if(temp >= L) {			//경사로 설치 가능
						temp = 1;
						continue;
					}
					else {
						check[1][j] = 0;
						break;
					}
				}
				else{
					if(ary[i+1][j] != ary[i+L][j]) {
						check[1][j] = 0;
						break;
					}
					else {
						temp = 1;
					}	
				}

			}
		}
	}

	for(int i = N; i > 0; i--) {
		if(ary[i][j] == ary[i-1][j])
			temp++;
		else if(ary[i-1][j] - ary[i][j] == 1) { 
			if(temp >= L) {
				temp = 1;
				continue;
			}
			else {
				check[1][j] = 0;
				break;
			}
		}
		else
			temp = 1;
	}
	
	

	for(int k = 0; k < 2; k++) {
		for(int i = 0; i < N; i++) {
			if(check[k][i] == 1){
				printf("%d / %d번째 줄\n",k, i);
				result++;
			}
		}

	}

	printf("%d\n", result);



	return 0;
}
