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
unsigned int mines, flags,sizex,sizey,solutie;
int x,y;
char data[18][32];
char real[18][32];
bool okey1,okey2;
void addBombs() {
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
				real[x][y] = 'm';
				break;
			}
		}
	}
}
void nrmines( int x, int y, int &m){
	if (x >= 0 && x < sizex && y >= 0 && y < sizey)
	{
		if (data[x][y] == 'm') m++;
	}
}
void initNumbers() {
	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			if (data[x][y] != 'm')
			{
				int m = 0;
				nrmines(x-1,y-1,m);
				nrmines(x, y - 1, m);
				nrmines(x + 1, y - 1, m);
				nrmines(x - 1, y, m);
				nrmines(x + 1, y, m);
				nrmines(x - 1, y + 1, m);
				nrmines(x, y + 1, m);
				nrmines(x + 1, y + 1, m);
				char c =m;
				data[x][y] = c;
			}
		}
	}
}

void drawBoard()
{
    cout<<"Numar bombe : "<<mines<<"\n";
    cout<<"Numar flags : "<<flags<<"\n";
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
			if (real[x][y]=='F')
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
    for(int i=0;i<=sizey;i++)
        {
        data[0][i]=0;
        real[0][i]=0;
        }
	addBombs();
	initNumbers();
	drawBoard();
	cout << endl;
	okey2=false;
	while (okey2 != true)
	{
	    cout<<"\n";
	    cout<<"If you want to flag press 1 else press 0"<<"\n";
	    cin>>okey1;

		cout << "Input x grid to check." <<"\n";
		cin >> x;
		cout <<"\n"<< "Input y grid to check." <<"\n";
		cin >> y;
		real[x][y]='1';
        if(!okey1)
            {
            if(data[x][y]=='m')
                {
                cout<<"BOOOOM";
                okey2=true;
                break;
                }
            else real[x][y]=1;
            system("cls");
            drawBoard();
            }
        else
            {
            if(real[x][y]=='F')
                {
                cout<<"intrat";
                cin>>x;
                flags++;
                real[x][y]='0';
                }
            else
                {
                real[x][y]='F';
                cout<<real[x][y];
                flags--;
                }
            system("cls");
            drawBoard();
            }
	}

	return 0;
}
