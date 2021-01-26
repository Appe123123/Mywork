#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int ary1[100][100] = {0};
	int ary2[100][100] = {0};
	int check[2][100] = {0};
	int N, L;
	int result = 0;
	

	scanf("%d %d", &N, &L);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf(" %d", &ary1[i][j]);
		}
	}

//testing for row
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N-1; j++) {
			if(abs(ary1[i][j] - ary1[i][j+1]) < 2)
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
			if(abs(ary1[i][j] - ary1[i][j]) < 2)
				check[1][j] = 1;
			else {
				check[1][j] = 0;
				break;
			}
		}
	}

//경사로 설치 가능한지 확인

	for(int i = 0; i < N; i++) {
		int hill[100] = {0};
		int len = 1;
		if(check[0][i]) {
			for(int j = 0; j < N; j++) {
				printf("Checking for (%d, %d)! \n", i, j);
				int diff = ary1[i][j+1] - ary1[i][j];

				// 좌우 일치
				if(diff == 0) { 
					len++;
					continue;
				}

				//올라갈때
				else if(diff > 0) { 
					if(len >= L) { //경사로 설치가능
						for(int k = j; k > j - L; k--) {
							if(hill[k] == 1) {
								check[0][i] = 0;
								break;
							}
						}
						len = 1;
						continue;
					}
					else {//경사로 설치 불가능
						check[0][i] = 0;
						break;
					}
				}

				//내려갈때
				else if(diff < 0) {
					int n = ary1[i][j+1];
					int tmp = 0;
					for(int k = 1; k <= L; k++) {

						if(n != ary1[i][j+k]) { //경사로 설치 불가능
							check[0][i] = 0;
							break;
						}
						tmp++;
					}

					//경사로 설치 가능
					if(tmp == L){
						for(int k = j+1; k <= L + j; k++) {
							hill[k] = 1;
						}
						j = j + L - 2;
						continue;								
					}
				}	
			}
		}
	}	
//=================================================================================================================================

	for(int j = 0; j < N; j++) {
		int hill[100] = {0};
		int len = 1;
		if(check[1][j]) {
			for(int i = 0; i < N; i++) {
				int diff = ary1[i+1][j] - ary1[i][j];

				// 좌우 일치
				if(diff == 0) { 
					len++;
					continue;
				}

				//올라갈때
				else if(diff > 0) { 
					if(len >= L) { //경사로 설치가능
						for(int k = j; k > i - L; k--) {
								if(hill[k] == 1) {
									check[0][i] = 0;
									break;
								}
						}
						len = 1;
						continue;
					}
					else  {//경사로 설치 불가능
						check[1][j] = 0;
						break;
					}
				}

				//내려갈때
				else if(diff < 0) {
					int n = ary1[i+1][j];
					int tmp = 0;
					for(int k = 1; k <= L; k++) {

						if(n != ary1[i+k][j]) { //경사로 설치 불가능
							check[1][j] = 0;
							break;
						}
						tmp++;
					}

					//경사로 설치 가능
					if(tmp == L){ 
						for(int k = i+1; k <= L + i; k++) {
							hill[k] = 1;
						}
						i = i + L - 2;
						len = 1;
						continue;								
					}
				}	
			}
		}
	}

	for(int k = 0; k < 2; k++) {
		for(int i = 0; i < N; i++) {
			if(check[k][i] == 1){
				printf("%d / %d번째 줄\n",k, i+1);
				result++;
			}
		}

	}
	printf("%d\n", result);


	return 0;
}
