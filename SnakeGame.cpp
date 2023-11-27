#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
using namespace std;
bool GameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100],tailY[100],nTail;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;
void Setup()
{
    srand(time(NULL));
    GameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score=0;
    nTail=0;
    while(x==fruitX&& y==fruitY){
     fruitX = rand() % width;
     fruitY = rand() % height;
    }
}
void Draw()
{
    system("clear");
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if(i==y && j==x){ 
                cout<<"O";
            }else if(i==fruitY && j==fruitX){ 
                cout<<"F";
            }else{
                bool print=false;
                for (int k = 0; k < nTail; k++)
                {
                    if(tailX[k]==j && tailY[k]==i){
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
            if(j==width-1)
            cout<<"#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout<<endl;
    cout<<"Score: "<<score<<endl;
    cout<<"High Score: ";
            fstream HighScore;
    HighScore.open("HighScore.txt",ios::in);
    if(!HighScore){
        cout<<"Data not found";
    }else{
        char x;
        while(!HighScore.eof()){
            HighScore>>x;
            cout<<x;
        }
    }
    HighScore.close();
    cout<<endl;
}
void Input()
{
    if(_kbhit()){
        switch(getch()){
            case 'a': 
             if(dir!=RIGHT) 
            dir=LEFT;
            break;
            case 'd': 
             if(dir!=LEFT)
             dir=RIGHT;
             break;
            case 'w': 
            if(dir!=DOWN) 
            dir=UP;
            break;
            case 's': 
            if(dir!=UP)
            dir=DOWN;
            break;
            case 'x': 
            GameOver=true;
            break;
        }
    }

}
void Logic()
{
    srand(time(NULL));
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for (int i = nTail-1; i >0; i--)
    {
        // prev2X=tailX[i];
        // prev2Y=tailY[i];
        // tailX[i]=prevX;
        // tailY[i]=prevY;
        // prevX=prev2X;
        // prevY=prev2Y;
        tailX[i]=tailX[i-1];
        tailY[i]=tailY[i-1];
        if(i==1)
        {
            tailX[i]=prevX;
            tailY[i]=prevY;
        }
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
    default:
        break;
    }

    if(x<=0||x>=width||y<=0||y>=height){
        GameOver=true;
    }
    for (int i = 0; i < nTail; i++)
    {
        if(tailX[i]==x && tailY[i]==y)
         GameOver=true;
    }
    if(x==fruitX && y==fruitY){
        score+=10;
        fruitX=rand()%width;
        fruitY=rand()%height;
        nTail++;
    }
    
}
int main()
{
    Setup();
    while (!GameOver)
    {
        Draw();
        Input();
        Logic();
        usleep(500000);
    }
    fstream HighScore;
    HighScore.open("HighScore.txt",ios::out);
    if(!HighScore){
        cout<<"Error while creating file.";
    }else{
    HighScore<<score<<"\n";
    HighScore.close();
    }
    return 0;
}