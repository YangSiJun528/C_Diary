#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define MAX_MEMO_LENGTH 300

int get_date_file_name_memo(int year, int month, int day);
void scan_description(char description[]);
void put_diary(int date, char description[]);
int get_diary(int date, char description[]);
void memo_main();
void gotoxy(int x, int y);
void paper();

int main(void)
{
	int menu, date, year, month, day;
	char description[MAX_MEMO_LENGTH] = "";

	while (1)
	{
		description[0] = '\0';
		memo_main();
		scanf("%d", &menu);
		system("cls");
		switch (menu)
		{
		case 1:
			//메모 쓰기 시작
			scan_description(description);
			system("cls");
			printf("날짜 입력: ");
			scanf("%d.%d.%d", &year, &month, &day);	//코드 연결하기 전에 임시로 날짜 받는 함수
			date = get_date_file_name_memo(year, month, day);
			put_diary(date, description);
			system("cls");
			printf("\n\n=[%d_memo.txt] 메모 작성 성공.=\n\n", date);
			break;
		case 2:
			//메모 보기 시작
			printf("확인하고 싶은 날짜를 입력해주세요 (YYYY.MM.DD): ");
			scanf("%d.%d.%d", &year, &month, &day);
			system("cls");
			date = (year * 10000 + month * 100 + day);

			if (get_diary(date, description)) {
			}
			else
				puts("그 날에는 메모를 작성하지 않았습니다.\n(아무 키나 눌러 메인화면으로 돌아가기.)\n");

			getchar();
			getchar();
			system("cls");
			break;
		case 3:
			//프로그램 종료
			return 0;
		default:
			//잘못된 번호 입력
			system("cls");
			puts("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
			break;
		}
	}
	return 0;
}

void memo_main()
{
	printf("====================\n\n");
	Sleep(250);
	printf("▷메모 작성\n");
	Sleep(250);
	printf("▷메모 보기\n");
	Sleep(250);
	printf("▷뒤로가기\n");
	printf("\n====================\n");

}

int get_date_file_name_memo(int year, int month, int day)
{
	return (year * 10000 + month * 100 + day);
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "메모를 입력하십시오(종료하려면 ctrl + Z를 누르고 enter.)";

	getchar();
	printf("%s(0/%d)\n", guide, MAX_MEMO_LENGTH - 1);

	while ((ch = getchar()) != EOF)
	{
		description[index] = ch;
		index = strlen(description);

		system("cls");
		printf(
			"%s(%d/%d):\n%s",
			guide,
			index,
			MAX_MEMO_LENGTH - 1,
			description
		);

		if (index + 1 == MAX_MEMO_LENGTH - 1)
		{
			puts("\n글자 제한을 초과하여 작성을 종료하고 저장합니다.");
			break;
		}
	}

	description[index + 1] = '\0';
}

void put_diary(int date, char description[])
{
	char filename[20];
	FILE* fp;

	sprintf(filename, "%d", date);
	strcat(filename, "_memo.txt");
	fp = fopen(filename, "w");

	fprintf(fp, "%s", description);
	fclose(fp);
}

int get_diary(int date, char description[])
{
	char filename[20];
	FILE* fp;
	int i = 0;

	sprintf(filename, "%d", date);
	strcat(filename, "_memo.txt");
	fp = fopen(filename, "r");

	if (fp == NULL)
		return 0;
	gotoxy(20, 3);
	printf("[%d 메모]", date);
	printf("\t\t(종료하려면 ctrl + Z를 누르고 enter.)\n");
	paper();

	while (feof(fp) == 0) {
		fgets(description, MAX_MEMO_LENGTH, fp);
		gotoxy(3, 7 + i);
		if (feof(fp) != 0)
			break;
		printf("%s\n", description);
		i++;

	}

	fclose(fp);
	return 1;
}



void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void paper()
{
	for (int i = 0; i < 100; i++)
		printf("=");
	printf("\n");
	for (int i = 0; i < 40; i++) {
		gotoxy(NULL, 5 + i);
		printf("||");
	}
	for (int i = 0; i < 40; i++) {
		gotoxy(98, 5 + i);
		printf("|");

		printf("|");
	}


	printf("\n");
	for (int i = 0; i < 100; i++)
		printf("=");
	gotoxy(3, 7);
}