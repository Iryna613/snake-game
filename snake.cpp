#include <iostream>
#include <conio.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

bool gameover;
const int width = 30;
const int height = 15;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int ntail;
int area[width][height];
enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
edirection dir;

int GetRandomNumber(int min, int max)
{
    srand(time(NULL));
    int num = min + rand() % (max - min);
    return num;
}
void Setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitx = GetRandomNumber(1, width - 2);
    fruity = GetRandomNumber(1, height - 2);
    score = 0;
}
void Screen()
{
    system("cls");
    for(int j=1; j<height-1; j++)
        for(int i=1; i<width-1; i++)
            area[i][j]=' ';
    for(int i=0; i<width; i++)
    {
        area[i][0]='#';
        area[i][height-1]='#';
    }
    for(int j=0; j<height; j++)
    {
        area[0][j]='#';
        area[width-1][j]='#';
    }
    cout << endl;
    cout << "Score: " << score << endl;
    //Sleep(3000);
}
void Draw()
{
    //system("cls");
    area[fruitx][fruity] = '*';
    area[x][y] = 'O';
    bool print = false;
    for(int k = 0; k < ntail; k++)
    {
        if(tailx[k] == x && taily[k] == y)
        {
            print = true;
            cout << "o";
        }
    }
    if(!print)
        cout << " ";
}
void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        default:
            break;
        }
    }
}
void Logic()
{
    int prevx = tailx[0];
    int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x;
    taily[0] = y;
    for(int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if(x >= width - 1)
    {
        x = 0;
    }
    else if(x < 0)
    {
        x = width - 2;
    }
    if(y >= height)
    {
        y = 0;
    }
    else if(y < 0)
    {
        y = height - 1;
    }

    for(int i = 0; i < ntail; i++)
    {
        if(tailx[i] == x && taily[i] == y)
        {
            gameover = true;
        }
    }

    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;
    }
}
void speed(int level)
{
    int sleep(level);
    if((sleep-ntail)<0)
        Sleep(0);
    else
        Sleep(sleep-ntail/level);
}
void work(int level)
{
    Setup();
    Screen();
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        speed(level);
    }
}
int main()
{
    int level, n;
    string repeat;
    cout << "Select a level(1-5): ";
    cin >> n;
    if(n == 1)
    {
        level = 200;
    }
    else if(n == 2)
    {
        level = 100;
    }
    else if(n == 3)
    {
        level = 50;
    }
    else if(n == 4)
    {
        level = 20;
    }
    else
    {
        level = 1;
    }
    work(level);
    /*cout << "Repeat?" << endl;
    cin.ignore();
    getline(cin, repeat);
    if(repeat == "Yes")
    {
        work(level);
    }
    else*/
    return 0;
}
