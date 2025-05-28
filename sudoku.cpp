#include<bits/stdc++.h>
using namespace std;

class Board{
    public:
    vector<vector<int>>grid;
    Board(const  vector<vector<int>>input){
        grid=input;
    }
    void print(){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout<<grid[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    void set(int row,int col,int val){
        grid[row][col]=val;
    }
    int get(int  row,int col){
        return grid[row][col];
    }
    bool check(int row, int  col, int val){
        // checking for  rows
        for(int i=0;i<9;i++){
            if(grid[i][col]==val  || grid[row][i]==val) return false;
        }
        // for checking in  3X3 grid
        int srow=row-row%3;
        int scol=col-col%3;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(grid[i+srow][j+scol]==val)  return false;
            }
        }
        return  true;

    }
    bool isEmpty(int row,int col){
        return  grid[row][col]==0;
    }
};

class SudokuSolver{
    private:
    Board &b;

    public:
    SudokuSolver(Board & b):  b(b){}
    bool solve(){        

        // approach 
        // go to i
        // go to j
        // check  empty
        // put  1 to 9
        // check is valid or not
        // if true return  true
        //  else backtrack set 0
        //if empty and not found any value to be setted there.
        // return true in the end.
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(b.isEmpty(i,j)){
                    for(int k=1;k<=9;k++){
                        // b.grid[i][j]=k;
                        if(b.check(i,j,k)){
                            b.set(i,j,k);
                        
                        
                        if(solve()) return true;
                        b.set(i,j,0);
                        }
                        
                    }
                    return false;
                    
                }
                
                

            }
        }
        return true;
    }

};

int  main(){
   
     vector<vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    Board b(puzzle);
     SudokuSolver s(b);
     if(s.solve()){
        b.print();
     }
     else{
        cout<<"No possible solutions\n";
     }
    

    return 0;
}