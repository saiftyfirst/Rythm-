/**
 * Problem: https://www.hackerrank.com/challenges/bomber-man/
 *
 * */

#include <bits/stdc++.h>

using namespace std;

void setToFull(char** grid, const int& r, const int& c){
    for_each(grid,grid+r,[=](char* row){
        for_each(row,row+c,[](char& val){val='O';});
    });
}

void deleteGrid(char** grid,int r){
    for(int i = 0; i < r; i++) delete [] grid[i];
    delete [] grid;
}

void printGrid(char** const grid,const int& r, const int& c){
    for_each(grid,grid+r,[=](char* row){
        for_each(row,row+c,[=](char val){cout<<val;});
        cout<<endl;
    });
}

void createGrid(char**& grid,const int& r, const int&c){
    grid=new char*[r];
    for(int i = 0; i < r; i++) grid[i]=new char[c];
}


void bomberMan(char**& grid,const int& r, const int& c, const int& time) {
    if(time%2==0){ setToFull(grid,r,c); return;}
    else if(time==1) return;
    int repeat=(time-1)%4==0?2:1;
    char** updateGrid;
    createGrid(updateGrid,r,c);
    char** temp;
    while(repeat>0){
        for(int i = 0; i < r; i++){
            for(int j=0;j<c;j++) {
                if(grid[i][j]=='.'){
                    if((j>0 && grid[i][j-1]=='O') || (j<c-1 && grid[i][j+1]=='O') || (i<r-1 && grid[i+1][j]=='O') || (i>0 && grid[i-1][j]=='O')) updateGrid[i][j]='.';
                    else updateGrid[i][j]='O';
                }else updateGrid[i][j]='.';
            }
        }
        temp=updateGrid;
        updateGrid=grid;
        grid=temp;
        repeat--;
    }
    deleteGrid(updateGrid,r);
}


int main() {
    int r;
    int c;
    int n;
    cin >> r >> c >> n;
    char** grid;
    //Using new to create
    grid=new char*[r];
    for(int i = 0; i < r; i++){
        grid[i]=new char[c];
        for(int j=0;j<c;j++) cin >> grid[i][j];
    }
    bomberMan(grid,r,c,n);
    printGrid(grid,r,c);
    deleteGrid(grid,r);
    return 0;
}
