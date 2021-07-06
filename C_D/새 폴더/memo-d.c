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
			//�޸� ���� ����
			scan_description(description);
			system("cls");
			printf("��¥ �Է�: ");
			scanf("%d.%d.%d", &year, &month, &day);	//�ڵ� �����ϱ� ���� �ӽ÷� ��¥ �޴� �Լ�
			date = get_date_file_name_memo(year, month, day);
			put_diary(date, description);
			system("cls");
			printf("\n\n=[%d_memo.txt] �޸� �ۼ� ����.=\n\n", date);
			break;
		case 2:
			//�޸� ���� ����
			printf("Ȯ���ϰ� ���� ��¥�� �Է����ּ��� (YYYY.MM.DD): ");
			scanf("%d.%d.%d", &year, &month, &day);
			system("cls");
			date = (year * 10000 + month * 100 + day);

			if (get_diary(date, description)) {
			}
			else
				puts("�� ������ �޸� �ۼ����� �ʾҽ��ϴ�.\n(�ƹ� Ű�� ���� ����ȭ������ ���ư���.)\n");

			getchar();
			getchar();
			system("cls");
			break;
		case 3:
			//���α׷� ����
			return 0;
		default:
			//�߸��� ��ȣ �Է�
			system("cls");
			puts("�߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
			break;
		}
	}
	return 0;
}

void memo_main()
{
	printf("====================\n\n");
	Sleep(250);
	printf("���޸� �ۼ�\n");
	Sleep(250);
	printf("���޸� ����\n");
	Sleep(250);
	printf("���ڷΰ���\n");
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
	char guide[] = "�޸� �Է��Ͻʽÿ�(�����Ϸ��� ctrl + Z�� ������ enter.)";

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
			puts("\n���� ������ �ʰ��Ͽ� �ۼ��� �����ϰ� �����մϴ�.");
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
	printf("[%d �޸�]", date);
	printf("\t\t(�����Ϸ��� ctrl + Z�� ������ enter.)\n");
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