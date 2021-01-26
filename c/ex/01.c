#include <stdio.h>
int main(void)
{
	FILE *ofp;
	ofp = fopen("myfile", "w");
	fprintf(ofp, "test");
	getchar();  // 임의의 문자 입력을 기다림.
	fclose(ofp);
	getchar();  // 임의의 문자 입력을 기다림.
	return 0;
}