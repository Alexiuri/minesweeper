#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include<conio.h>
using namespace std;
unsigned int mines, flags,sizex,sizey,solutie,aux[18][32],reveals,parcurgere[18][32];
int x,y;
char data[18][32];
int real[18][32];
bool okey2,ok;
int okey1;
void adancime(char data[18][32],int real[18][32],int ox,int oy)
{
    if(ox>=0 && ox<sizex && oy>=0 && oy<sizey)
    {
        if(real[ox][oy]==1)return;
        if(data[ox][oy]!='m' && real[ox][oy]!=-1)
        {
            real[ox][oy]=1;
            aux[ox][oy]-2;
        }
        if((aux[ox][oy])==0)
        {
            adancime(data,real,ox-1,oy-1);
            adancime(data,real,ox-1,oy);
            adancime(data,real,ox-1,oy+1);
            adancime(data,real,ox,oy-1);
            adancime(data,real,ox+1,oy-1);
            adancime(data,real,ox+1,oy+1);
            adancime(data,real,ox+1,oy);
            adancime(data,real,ox,oy+1);
        }
    }
    else return;
}
int verif(int real[18][32])
{
    for(int i=0; i<sizex; i++)
        for(int j=0; j<sizey; j++)
            if(real[i][j]==0)return 0;
    return 1;
}
void hint(char data[18][32],int real[18][32],int ox,int oy)
{
if(ok==1)return;
    else
    {
    if(parcurgere[ox][oy]==1)return;
    if(ox>=0 && ox<sizex && oy>=0 && oy<sizey)
    {

        if(data[ox][oy]=='m' && real[ox][oy]!=-1)
        {
            real[ox][oy]=-1;
            aux[ox][oy]-2;
            flags--;
            reveals++;
            ok=1;
        }
        else if(real[ox][oy]==0)
            {
            if((int)(data[ox][oy])==0)adancime(data,real,ox,oy);
            real[ox][oy]=1;
            ok=1;
            }
        parcurgere[ox][oy]=1;
        hint(data,real,ox-1,oy-1);
        hint(data,real,ox-1,oy);
        hint(data,real,ox-1,oy+1);
        hint(data,real,ox,oy-1);
        hint(data,real,ox+1,oy-1);
        hint(data,real,ox+1,oy+1);
        hint(data,real,ox+1,oy);
        hint(data,real,ox,oy+1);
        }
    else return;
    }

}
void addBombs(char data[18][32],int real[18][32])
{
    for (int i = 0; i < mines; i++)
    {
        while (true)
        {
            x = rand() % sizex;
            y = rand() % sizey;
            cout<<x<<" "<<y<<"\n";
            if (data[x][y] != 'm')
            {
                data[x][y] = 'm';
                //real[x][y] = -2;
                break;
            }
        }
    }
}
void nrmines( int x, int y, int &m,char data[18][32],int real[18][32])
{
    if (x >= 0 && x < sizex && y >= 0 && y < sizey)
    {
        if (data[x][y] == 'm') m++;
    }
}
void initNumbers (char data[18][32],int real[18][32])
{
    for (int y = 0; y < sizey; y++)
    {
        for (int x = 0; x < sizex; x++)
        {
            if (data[x][y] != 'm')
            {
                int m = 0;
                nrmines(x-1,y-1,m,data,real);
                nrmines(x, y - 1, m,data,real);
                nrmines(x + 1, y - 1, m,data,real);
                nrmines(x - 1, y, m,data,real);
                nrmines(x + 1, y, m,data,real);
                nrmines(x - 1, y + 1, m,data,real);
                nrmines(x, y + 1, m,data,real);
                nrmines(x + 1, y + 1, m,data,real);
                data[x][y] = m;
                aux[x][y]=m;
            }
        }
    }
}

void drawBoard(char data[18][32],int real[18][32]  )
{
    cout<<"Number of mines : "<<mines<<"\n";
    cout<<"Number of mines : "<<flags<<"\n";
    cout<<"\n";
    cout << "           _";
    for (int i = 0; i < sizex; i++)
    {
        if(i<10)cout<< "_"<<" "<< i;
        else if(i+1==sizex)cout<< "_"<<i<<"__";
        else cout<< "_"<<i;
    }
    cout << endl;
    for (int y = 0; y < sizey; y++)
    {
        if(y<10)cout<<"           "<<y << "|";
        else cout<<"          "<<y<< "|";
        for (int x = 0; x < sizex; x++)
        {
            if (real[x][y]==-1)
            {
                cout << " F|";
            }
            else if (real[x][y]==1)
            {
                cout <<" "<< (int)(data[x][y])<<"|";
            }
            else
            {
                cout << "__|";
            }
            if(x+1==sizex)cout<<y;
        }
        cout << endl;
    }
    cout << "           _";
    for (int i = 0; i < sizex; i++)
    {
        if(i<10)cout<< "_"<<" "<< i;
        else if(i+1==sizex)cout<< "_"<<i<<"__";
        else cout<< "_"<<i;
    }
}

int main()
{
    cout<<"     Minesweeper"<<"\n";
    while(okey1==false)
    {
        cout<<"Press 1 if you want a 9x9 board"<<"\n";
        cout<<"Press 2 if you want a 16x16 board"<<"\n";
        cout<<"Press 3 if you want a 16x30 board"<<"\n";
        cin>>solutie;
        if(solutie==1)
        {
            sizex=10;
            sizey=10;
            okey1=1;
            mines=10;
            flags=10;
        }
        else if(solutie==2)
        {
            sizex=17;
            sizey=17;
            okey1=1;
            mines=30;
            flags=30;
        }
        else if(solutie==3)
        {
            sizex=17;
            sizey=31;
            okey1=1;
            mines=99;
            flags=99;
        }
    }
    for(int i=0; i<=sizey; i++)
        for(int j=0; j<=sizex; j++)
        {
            data[j][i]=0;
            real[j][i]=0;
            aux[j][i]=0;
        }
    addBombs(data,real);
    initNumbers(data,real);
    drawBoard(data,real);
    cout << endl;
    okey2=false;
    okey1=-1;
    solutie=0;
    reveals=0;
    while (okey2 != true)
    {
        if(reveals==mines && verif(real))break;
        cout<<"\n";
        cout<<"Press 0 to choose a field"<<"\n";
        cout<<"Press 1 to put a flag "<<"\n";
        if(solutie!=0)cout<<"Press 2 to remove a flag"<<"\n";
        if(solutie!=0)cout<<"Press 3 for hint "<<"\n";
        cin>>okey1;

        if(flags==0)
        {
            while((okey1==1)||(okey1<0 || okey1>3))
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"\n";
                cout<<"\n";
                cout<<"You can not add more flags";
                cout<<"\n";
                cout<<"Press 0 to choose a field"<<"\n";
                cout<<"Press 2 to remove a flag"<<"\n";
                cout<<"Press 3 for hint "<<"\n";
                cin>>okey1;
            }
        }
        while(okey1==2 &&mines==flags)
        {

            while(((solutie!=0)&&okey1==2)||okey1<0 || okey1>3)
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"\n";
                cout<<"You don't have any flag to remove";
                cout<<"Press 0 to choose a field"<<"\n";
                cout<<"Press 1 to put a flag "<<"\n";
                cout<<"Press 3 for hint "<<"\n";
                cin>>okey1;
                if(mines==flags && okey1==2)
                {
                    okey1=-1;
                    cout<<"You don't have a flag to remove";
                }
            }
            break;
        }
        while(true)
        {
            if((okey1<0 || okey1>1)&&solutie==0)
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"\n";
                cout<<"Press 0 to choose a field"<<"\n";
                cout<<"Press 1 to put a mine "<<"\n";
                //cout<<"Press 2 to choose a flag"<<"\n";
                cin>>okey1;
            }
            else break;
        }
        while(true)
        {
            if(okey1<0 || okey1>3)
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"Press 0 to choose a field"<<"\n";
                cout<<"Press 1 to put a flag "<<"\n";
                cout<<"Press 2 to remove a flag"<<"\n";
                if(!(okey1<0 || okey1>3))cout<<"Press 3 for hint "<<"\n";
                cin>>okey1;
                if(mines==flags && okey1==2)
                {
                    okey1=-1;
                    cout<<"You don't have any flag to remove";
                }
            }

            else break;
        }
        if(okey1==3)
        {
            ok=0;
            for(int i=0; i<=sizey; i++)
                for(int j=0; j<=sizex; j++)
                    parcurgere[i][j]=0;
            hint(data,real,x,y);
            system("cls");
            drawBoard(data,real);
        }
        else
        {
            solutie=1;
            cout << "Input x grid." <<"\n";
            cin >> x;
            while(x<0 || x>=sizex)
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"\n";
                cout<<"\n";
                cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                cin>>x;
            }
            cout <<"\n"<< "Input y grid ." <<"\n";
            cin >> y;
            while(y<0 || x>=sizey)
            {
                system("cls");
                drawBoard(data,real);
                cout<<"\n";
                cout<<"\n";
                cout<<"\n";
                cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                cout<<x;
                cout<<"\n";
                cout<<"Please imput for y a number between : 0 and"<<sizey-1<<"\n";
                cin>>y;
            }
            if(okey1==0)
            {
                if(data[x][y]=='m')
                {
                    cout<<"BOOOOM";
                    okey2=true;
                    break;
                }
                while(real[x][y]==-1 || real[x][y]==1)
                {
                    system("cls");
                    drawBoard(data,real);
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"Plese choose a not-flagged field or not-revealed field "<<"\n";
                    cout << "Input x grid." <<"\n";
                    cin >> x;
                    while(x<0 || x>=sizex)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cin>>x;
                    }
                    cout <<"\n"<< "Input y grid." <<"\n";
                    cin >> y;
                    while(y<0 || x>=sizey)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cout<<x;
                        cout<<"\n";
                        cout<<"Please imput for y a number between : 0 and"<<sizey-1<<"\n";
                        cin>>y;
                    }
                    system("cls");
                    drawBoard(data,real);
                }
                if((int)(data[x][y])==0)adancime(data,real,x,y);
                else real[x][y]=1;
                aux[x][y]=-2;
                system("cls");
                drawBoard(data,real);
            }
            else if(okey1==1)
            {
                while(real[x][y]==-1 || real[x][y]==1)
                {
                    system("cls");
                    drawBoard(data,real);
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"Plese choose a not-flagged field"<<"\n";
                    cout << "Input x grid." <<"\n";
                    cin >> x;
                    while(x<0 || x>=sizex)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cin>>x;
                    }
                    cout <<"\n"<< "Input y grid." <<"\n";
                    cin >> y;
                    while(y<0 || x>=sizey)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cout<<x;
                        cout<<"\n";
                        cout<<"Please imput for y a number between : 0 and"<<sizey-1<<"\n";
                        cin>>y;
                    }
                    system("cls");
                    drawBoard(data,real);
                }
                real[x][y]=-1;
                aux[x][y]=-1;
                flags--;
                if(data[x][y]=='m')reveals++;
                system("cls");
                drawBoard(data,real);
            }
            else if(okey1==2)
            {
                while(aux[x][y]!=-1)
                {
                    system("cls");
                    drawBoard(data,real);
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"\n";
                    cout<<"Plese choose a flagged field"<<"\n";
                    cout << "Input x grid." <<"\n";
                    cin >> x;
                    while(x<0 || x>=sizex)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cin>>x;
                    }
                    cout <<"\n"<< "Input y grid." <<"\n";
                    cin >> y;
                    while(y<0 || x>=sizey)
                    {
                        system("cls");
                        drawBoard(data,real);
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"\n";
                        cout<<"Please imput for x a number between : 0 and"<<sizex-1<<"\n";
                        cout<<x;
                        cout<<"\n";
                        cout<<"Please imput for y a number between : 0 and"<<sizey-1<<"\n";
                        cin>>y;
                    }
                    system("cls");
                    drawBoard(data,real);
                }
                real[x][y]=0;
                flags++;
                if(data[x][y]=='m')reveals--;
                aux[x][y]=(int)(data[x][y]);
                system("cls");
                drawBoard(data,real);
            }
        }
    }
    cout<<"\n You WON";
    return 0;
}
