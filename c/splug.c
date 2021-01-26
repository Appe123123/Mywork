#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char Name[30];
	char Address[100];
	char Phone_num[20];
	struct Node *next;
}Data;

Data *First = NULL;
void Print_INFO();

Data *makenode() {
	Data *tmp =(Data *)malloc(sizeof(Data));
	tmp->next = NULL;
	return tmp;
}


void addNode(Data **one, char Name[], char Address[], char Phone_num[]) {

	while(1) {
	if(!*one) {
		*one = makenode();
		strcpy((*one)->Name,Name);
		strcpy((*one)->Address,Address);
		strcpy((*one)->Phone_num,Phone_num);
		return;
	}
	one = &((*one)->next);
}

}

void Read_txt() {
	FILE *fp = fopen("/home/hyun/스플럭명단관리.txt", "r");

	if(fp == NULL) {
		printf(" 잘못된 파일입니다.\n");
		return;
	}
	Data *tmpNode = NULL;
	while(1) {
		Data tmp;
		fscanf(fp, "%s %s %s",tmp.Name, tmp.Address, tmp.Phone_num);
		if(feof(fp) != 0)
			break;
		tmpNode = (Data *)malloc(sizeof(Data));
		tmpNode->next = NULL;
		strcpy(tmpNode->Name,tmp.Name);
		strcpy(tmpNode->Address,tmp.Address);
		strcpy(tmpNode->Phone_num,tmp.Phone_num);
			if(First == NULL) 
				First = tmpNode;
			else {
				Data *New = First;
				while(New->next != NULL) {
					New = New->next;
				}
				New->next = tmpNode;
			}
	}
	fclose(fp);

}


void Print_INFO() {
	Data *temp = First;
	for(int i = 1 ; temp != NULL; ++i) {
		printf("===========================\n");
		printf("#%d\n",i);
		printf("이름 : %s\n",temp->Name);
		printf("주소 : %s\n", temp->Address);
		printf("전화번호 : %s\n", temp->Phone_num);
		printf("===========================\n");
		temp = temp->next;
	}
}

void Sort() {
	int i = 0;
	Data *Cur = First;
	Data *prev;
	Data *prev2;
	Data *temp;
	Data *Cur2;
	while(Cur->next != NULL) {
		Cur2 = Cur->next;
		prev2 = Cur;
		while(1) {
			if(strcmp(Cur->Name,Cur2->Name) > 0) {
				if(Cur == First) {
					if(Cur->next != Cur2) {
						First = Cur2;
						temp = Cur2->next;
						Cur2->next = Cur->next;
						prev2->next = Cur;
						Cur->next = temp;
					}
					else {
						First = Cur2;
						temp = Cur2->next;
						Cur2->next = Cur;
						Cur->next = temp;
					}
				}
				
				else {
					if(Cur->next != Cur2) {
						temp = Cur->next;
						Cur->next = Cur2->next;
						Cur2->next = temp;
						prev->next = Cur2;
						prev2->next = Cur;
					}
					else {
						prev->next = Cur2;
						temp = Cur2->next;
						Cur2->next = Cur;
						Cur->next = temp;
					}
				}

				temp = Cur;
				Cur = Cur2;
				Cur2 = temp;

			}
			if(Cur2->next == NULL)
				break;
			Cur2 = Cur2->next;
			prev2 = prev2->next;
		}
		Cur = Cur->next;
		if(i++ == 0) 
			prev = First;
		else
			prev = prev->next;
	}
			

}

void Search_INFO(char User_Name[]) {
	Data *temp = First;
	while(1) {
		if(strcmp(User_Name,temp->Name)==0)
			break;
		if(temp->next==NULL) {
			printf("회원이 존재하지 않습니다.\n");
			return;
		}
		temp = temp->next;
	}
	printf("이름 : %s\n",temp->Name);
	printf("주소: %s\n", temp->Address);
	printf("전화번호 : %s\n",temp->Phone_num);
}
void Search_INFO_2(char User_address[]) {
	Data *temp = First;
	while(1) {
		if(strcmp(User_address,temp->Address)==0)
			break;
		if(temp->next==NULL) {
			printf("회원이 존재하지 않습니다.\n");
			return;
		}
		temp = temp->next;
	}
	printf("이름 : %s\n",temp->Name);
	printf("주소: %s\n", temp->Address);
	printf("전화번호 : %s\n",temp->Phone_num);
}

void Search_INFO_3(char User_phonenum[]) {
	Data *temp = First;
	while(1) {
		if(strcmp(User_phonenum,temp->Phone_num)==0)
			break;
		if(temp->next==NULL) {
			printf("회원이 존재하지 않습니다.\n");
			return;
		}
		temp = temp->next;
	}
	printf("이름 : %s\n",temp->Name);
	printf("주소: %s\n", temp->Address);
	printf("전화번호 : %s\n",temp->Phone_num);
}

void Modify_INFO(char User_name[], char Changed_User_name[], char User_address[], char User_phonenum[]) {
	Data *temp = First;
	while(1) {
		if(strcmp(User_name,temp->Name)==0)
			break;
		if(temp->next==NULL) {
			printf("회원이 존재하지 않습니다.\n");
			return;
		}
		temp = temp->next;
	}
	strcpy(temp->Name, Changed_User_name);
	strcpy(temp->Address, User_address);
	strcpy(temp->Phone_num, User_phonenum);
	printf("\n정보가 수정되었습니다\n");
}

void Exit() {
	FILE *fp = fopen("/home/hyun/스플럭명단관리.txt", "w");
	if(First != NULL) {
		while(1) {
			Data *al = First;
			fprintf(fp, "%s %s %s\n", al->Name, al->Address, al->Phone_num);
			if(First->next == NULL)
				break;
			First = First->next;
		}

	}
}

void Delete_User(char User_name[]) {
	Data *temp = First;
	Data *prev = First;
	int i = 0;

	if(temp == First && strcmp(User_name, temp->Name) == 0) {
		First = temp->next;
		free(temp);
		temp = NULL;
		
		return;
	}
	while(1) {
		temp = temp->next;
		if(strcmp(User_name, temp->Name)==0)
			break;
		if(temp->next == NULL) {
			printf("회원이 존재하지 않습니다.\n");
			return;
		}
		prev = prev->next;

	}
	
	prev->next = temp->next;
	free(temp);
	temp = NULL;
	return;

}




int main(void){

	Read_txt();
	char User_name[30], User_address[100], User_phonenum[20];
	char Changed_User_name[30];
	char check;

	int n, menu, menu_2;
	char temp[50];
	


	//메뉴 출력 및 입력
	printf("                   = 메뉴 = \n");
	printf("\
1. 모든 주소록 정보 출력\n\
2. 회원 등록\n\
3. 회원 정보 검색\n\
4. 회원 정보 수정\n\
5. 회원 삭제\n\
6. 프로그램 종료\n\n\n");

	do{
		printf("\
===========================\n\
선택할 기능을 입력하세요 : ");
		scanf("%d", &menu);
		getchar();
		
		switch(menu) {
			case 1 :
				Sort();
				Print_INFO();
				break;

			case 2 :
				printf("주의사항 : 공백을 입력하지 마세요.\n");
				while(1) {
				printf("이름 : ");
				scanf(" %[^\n]",User_name);
				getchar();
				if(strstr(User_name, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다.\n");
				}

				while(1) {
				printf("주소 : ");
				scanf("%[^\n]",User_address);
				getchar();
				if(strstr(User_address, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다.\n");
				}


				while(1) {
				printf("전화번호 : ");
				scanf("%[^\n]",User_phonenum);
				getchar();
				if(strstr(User_phonenum, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다.\n");
				}
				
				addNode(&First,User_name, User_address,User_phonenum);
				break;

			case 3 :
				printf("어떤 정보로 검색할지 선택하세요 : \n");
				printf("1. 이름\n");
				printf("2. 주소\n");
				printf("3. 전화번호\n");
				scanf(" %d", &menu_2);
				if(menu_2 == 1) {
					printf("찾으실 회원의 이름을 입력하세요 : ");
					scanf("%s",User_name);
					getchar();
					Search_INFO(User_name);
				}
				else if(menu_2 == 2) {
					printf("찾으실 회원의 주소를 입력하세요 : ");
					scanf("%s", User_address);
					getchar();
					Search_INFO_2(User_address);
				}
				else if(menu_2 == 3) {
					printf("찾으실 회원의 전화번호를 입력하세요 : ");
					scanf("%s", User_phonenum);
					getchar();
					Search_INFO_3(User_phonenum);
				}

				break;

			case 4 :
				printf("<공백을 입력하지 마세요>\n");
				printf("수정할 회원의 이름을 입력하세요 : ");
				while(1) {
				scanf("%[^\n]",User_name);
				getchar();
				if(strstr(User_name, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다. \n");
				}
				
				while(1) {
				printf("이름 : ");
				scanf("%[^\n]",Changed_User_name);
				getchar();
				if(strstr(Changed_User_name, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다, \n");
				}

				while(1) {
				printf("주소 : ");
				scanf("%s",User_address);
				getchar();
				if(strstr(User_address, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다, \n");
				}

				while(1) {
				printf("전화번호 : ");
				scanf("%s",User_phonenum);
				getchar();
				if(strstr(User_phonenum, " ") == NULL)
					break;
				else
					printf("공백이 발견되었습니다, \n");
				}

				Modify_INFO(User_name,Changed_User_name,User_address,User_phonenum);
				break;

			case 5 :
				printf("삭제할 회원의 이름을 입력하세요 : ");
				scanf("%s",User_name);
				getchar();
				Data *head = First;
				Delete_User(User_name);
				break;


			case 6 :
				printf("저장하시겠습니까?  [Y/N]\n");
				scanf("%c",&check);
				if(check == 'Y' || check == 'y') {
					Exit();
					printf("변경사항이 저장되었습니다.\n");
				}
				else if(check == 'N' || check == 'n')
					printf("수정이 취소되었습니다.\n");
				else
				{
					printf("a잘못된 입력입니다.\n");
					printf("%c\n", check);
				}
				
				break;

			default :
				printf("잘못된 입력입니다.");
				break;

		}

		}while(menu != 6);



	return 0;
}

