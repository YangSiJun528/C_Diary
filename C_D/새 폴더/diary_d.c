#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#define MAX_DIARY_LENGTH 1000

int get_date_file_name(void);
void scan_description(char description[]);
void put_diary(int date, char description[]);
int get_diary(int date, char description[]);
void diary_main();
void gotoxy(int x, int y);
extern void print_cal();


int diary_start(void)
{
	int menu, date, year, month, day;
	char description[MAX_DIARY_LENGTH] = "";
	int exitOuterLoop = 0; // 바꿈
	while (1)
	{
	A:  // goto 사용
		description[0] = '\0';
		diary_main();
		scanf(" %d", &menu);
		system("cls");
		switch (menu)
		{
		case 1:
			//일기 쓰기 시작
			scan_description(description);
			date = get_date_file_name();
			put_diary(date, description);
			system("cls");
			printf("\n\n~~![%d.txt] 일기 작성 성공!\n\n", date);
			break;
		case 2:
			//일기 보기 시작
			printf("확인하고 싶은 날짜를 입력해주세요 (YYYY.MM.DD): ");
			scanf("%d.%d.%d", &year, &month, &day);
			system("cls");
			date = (year * 10000 + month * 100 + day);

			if (get_diary(date, description)) {
				printf("\n\n[%d 일기]\n================================================================\n%s\n\n================================(그만 보려면 아무 키나 누르세요.)\n", date, description);
			}

			else {
				puts("그 날에는 일기를 작성하지 않았습니다.\n(아무 키나 눌러 메인화면으로 돌아가기.)\n");
				getchar();
			}
			getchar();
			getchar();
			system("cls");
			goto A;
			break;
		case 3:
			//프로그램 종료
			system("cls");
			print_cal();
			exitOuterLoop = 1;
			break;
		default:
			//잘못된 번호 입력
			system("cls");
			puts("잘못된 번호를 입력하셨습니다. 다시 입력해주세요.\n");
			getchar();
			goto A;
			break;
		}
		if (exitOuterLoop == 1)
			break;
	}
	return 0;
}

int get_date_file_name(void)
{
	int year, month, day;
	struct tm* t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);

	year = t->tm_year + 1900;
	month = t->tm_mon + 1;
	day = t->tm_mday;

	return (year * 10000 + month * 100 + day);
}

void scan_description(char description[])
{
	int ch;
	unsigned int index = 0;
	char guide[] = "오늘의 일기를 입력하십시오(종료하려면 ctrl + Z를 누르고 enter.)";

	getchar();
	printf("%s(0/%d)\n", guide, MAX_DIARY_LENGTH - 1);

	while ((ch = getchar()) != EOF)
	{
		description[index] = ch;
		index = strlen(description);

		system("cls");
		printf(
			"%s(%d/%d):\n%s",
			guide,
			index,
			MAX_DIARY_LENGTH - 1,
			description
		);

		if (index + 1 == MAX_DIARY_LENGTH - 1)
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
	strcat(filename, ".txt");
	fp = fopen(filename, "w");
	fprintf(fp, "%s", description);
	fclose(fp);
}

int get_diary(int date, char description[])
{
	char filename[20];
	FILE* fp;

	sprintf(filename, "%d", date);
	strcat(filename, ".txt");
	fp = fopen(filename, "r");

	if (fp == NULL)
		return 0;

	fgets(description, MAX_DIARY_LENGTH, fp);
	fclose(fp);
	return 1;
}

void diary_main()
{
	printf("====================\n\n");
	Sleep(250);
	printf("▷일기 작성\n");
	Sleep(250);
	printf("▷일기 보기\n");
	Sleep(250);
	printf("▷뒤로가기\n");
	printf("\n====================\n");

}