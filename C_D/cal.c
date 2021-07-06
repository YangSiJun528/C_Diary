#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//�ϱ� �Լ� �ҷ�����
extern int diary_start(void);
extern int memo_start(void);
extern int get_date_file_name(void);
extern void scan_description(char description[]);
extern void put_diary(int date, char description[]);
extern int get_diary(int date, char description[]);
extern void diary_main();
extern void memo_main();
extern MAX_DIARY_LENGTH;
extern int get_date_file_name_memo(int year, int month, int day);
extern void scan_description_memo(char description[]);
extern void put_memo(int date, char description[]);
extern int get_memo(int date, char description[]);
extern void paper();

// 0 ���� 1��¥
int data[50][12][2] = {
    0,
};
int cal[6][7] = {
    0,
};
int selected_day[3] = {0,};
int current_year, current_mon, current_day;
int f_year, f_mon, f_day;
int x = 3, y = 2;

int is_leaf_year(int year)  // ���� ���
{
    if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        return 1;
    return 0;
}
void init_data() //�⵵, ��, ��, ���� ���� ����
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 12; j++)
            switch (j)
            {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
            case 11:
                data[i][j][1] = 31;
                break;
            case 1:
                data[i][j][1] = 28 + is_leaf_year(2001 + i);
                break;
            default:
                data[i][j][1] = 30;
                break;
            }
    }
    for (int j = 0; j < 12; j++)
    {
        switch (j)
        {
        case 1:
        case 2:
        case 10:
            data[0][j][0] = 3;
            break;
        case 0:
        case 9:
            data[0][j][0] = 0;
            break;
        case 3:
        case 7:
            data[0][j][0] = 6;
            break;
        case 4:
            data[0][j][0] = 1;
            break;
        case 5:
            data[0][j][0] = 4;
            break;
        case 6:
            data[0][j][0] = 2;
            break;
        default:
            data[0][j][0] = 5;
        }
    }
    for (int i = 1; i < 50; i++)
    {
        for (int j = 0; j < 12; j++)
            switch (j)
            {
            case 0:
                data[i][j][0] = (data[i - 1][11][0] + data[i - 1][11][1]) % 7;
                break;
            default:
                data[i][j][0] = (data[i][j - 1][0] + data[i][j - 1][1]) % 7;
                break;
            }
    }
}
void init_cal()  // 2���� �迭�� �ҷ�����
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            cal[i][j] = 0;
    int day = 0;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < (data[current_year - 2001][current_mon - 1][1]) / 7; i++)
    {
        for (j = 0; j < 7; j++)
        {
            day++;
            cal[i][j + data[current_year - 2001][current_mon - 1][0]] = day;
        }
    }
    for (k = 0; k < (data[current_year - 2001][current_mon - 1][1]) % 7; k++)
    {
        day++;
        cal[i][k + data[current_year - 2001][current_mon - 1][0]] = day;
    }
}
void print_cal()  //2���� �迭 ���
{
    printf("           %d/%d\n", current_year, current_mon);
    printf(" MON TUE WED THU FRI SAT SUN\n");
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < 7; i++)
        {
            if (cal[j][i] == 0)
                printf("    ");
            else if (selected_day[1] == current_mon && selected_day[0] == current_year && current_day == (j * 7) + i + (1 - (data[current_year - 2001][current_mon - 1][0])))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                printf("%4d", cal[j][i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } 
            else
                printf("%4d", cal[j][i]);
        }
        printf("\n");
    }
    printf("  <-                      ->");
    printf("\nw,a,s,d�� ���ϴ� ��¥�� �����̰� \noŰ�� ���� �޸�,pŰ�� ���� �ϱ⸦ �ۼ��ϼ���.");
}
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//void print_day() //��ġ Ȯ��
//{
//    gotoxy(3, 10);
//    //printf("x:%d y:%d", x, y);
//    current_day = (cal[(y - 2) / 1][(x - 3) / 4]);
//    printf("%d/%d/%d\n", current_year, current_mon, current_day);
//}

void def_select_day() {
    selected_day[0] = current_year;
    selected_day[1] = current_mon;
    selected_day[2] = current_day;
}

//void select_day() // �ӽ�
//{
//    current_day = (cal[(y - 2) / 1][(x - 3) / 4]);
//    def_select_day();
//    system("cls");
//    printf("%d/%d/%d\n", current_year, current_mon, current_day);
//    printf("�޸� or �ϱ⸦ �ۼ��Ͻðڽ��ϱ�? YES/NO\n");
//    while (1)
//    {
//        char input;
//        input = _getch();
//        if (input == 'n')
//        {
//            system("cls");
//            print_cal();
//            break;
//        }
//        else if (input == 'y')
//        {
//            system("cls");
//            printf("Q�� �Է��� ������\n");
//            printf("�޸� �ۼ��ϼ���\n");
//            while (1)
//            {
//                char input;
//                input = _getch();
//                if (input == 'q')
//                {
//                    system("cls");
//                    print_cal(); // ������
//                    break;
//                }
//                else if (input == 'i') //�ۼ� �Ϸ�
//                {
//                    system("cls");
//                    print_cal();
//                    break;
//                }
//            }
//            break;
//        }
//    }
//}

void prev_mon() //������ ���
{
    system("cls");
    if (current_mon == 1)
    {
        --current_year;
        current_mon = 12;
        init_cal();
        print_cal();
    }
    else
    {
        --current_mon;
        init_cal();
        print_cal();
    }
}

void next_mon() //������ ���
{
    system("cls");
    if (current_mon == 12)
    {
        ++current_year;
        current_mon = 1;
        init_cal();
        print_cal();
    }
    else
    {
        ++current_mon;
        init_cal();
        print_cal();
    }
}

int main()
{
    // time ����
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    current_year = tm.tm_year + 1900, current_mon = tm.tm_mon + 1, current_day = tm.tm_mday;
    def_select_day();
    f_year = current_year;
    f_mon = current_mon;
    f_day = current_day;

    // �޷� ��� �� �Է� �ޱ�
    char input;
    init_data();
    system("cls");
    init_cal();
    print_cal();
    gotoxy(1, 1);
    while (1)
    {
        input = _getch();
        if (input == 'w')
            y--;
        else if (input == 'a')
            x -= 4;
        else if (input == 's')
            y++;
        else if (input == 'd')
            x += 4;
        else if (input == 'p')
        {
            if (cal[(y - 2) / 1][(x - 3) / 4] != 0 && ((y >= 2 && y <= 7) && (x >= 3 && x <= 27))) //������ ��¥�� ���� ���� �ְ� 0�� �ƴҋ�
            {
                current_day = (cal[(y - 2) / 1][(x - 3) / 4]);
                def_select_day();
                system("cls");
                diary_start();
            }
            else if (y == 8 && x == 3)
            {
                prev_mon();
            }
            else if (y == 8 && x == 27)
            {
                next_mon();
            }
        }
        else if (input == 'o')
        {
            if (cal[(y - 2) / 1][(x - 3) / 4] != 0 && ((y >= 2 && y <= 7) && (x >= 3 && x <= 27))) //������ ��¥�� ���� ���� �ְ� 0�� �ƴҋ�
            {
                current_day = (cal[(y - 2) / 1][(x - 3) / 4]);
                def_select_day();
                system("cls");
                memo_start();
            }
            else if (y == 8 && x == 3)
            {
                prev_mon();
            }
            else if (y == 8 && x == 27)
            {
                next_mon();
            }
        }
        gotoxy(x, y);
    }
}
