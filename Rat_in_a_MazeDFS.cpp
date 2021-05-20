#include<iostream>
#include<vector>
#include<stack>
#include<string.h>
#include<process.h>
using namespace std;

stack<pair<int,int>>pos;
pair<int,int>src,dest;
int i,j,N,flag=0;

void print_maze(vector<vector<int>>V)
{
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            cout<<V[i][j]<<" ";
        cout<<endl;
    }
}
void initialize_matrix(vector<vector<int>>&V)
{
    cout<<endl<<"---------------- Initialize Matrix----------------"<<endl;
    cout<<" Enter number of rows or columns ('cause it's a N*N matrix) : ";
        cin>>N;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cout<<"Enter element "<<j+1<<" of row "<<i+1<<" : ";
                cin>>V[i][j];
        }
        cout<<"-----"<<endl;
    }
    cout<<"The final matrix is : "<<endl;
    print_maze(V);
}

void src_n_dest(pair<int,int>&src,pair<int,int>&dest)
{
    pos.pop();

 start1:
    cout<<"Enter source and destination coordinates (Seperated by spaces) "<<endl;
    cout<<"Src : "; cin>>i>>j;  
    if(i<0 || i>=N || j<0 || j>=N)
    {
        cout<<"ERROR! COORDS OUTSIDE AREA SPECIFIED!"<<endl;
        goto start1;
    }
    src=make_pair(i,j);

 start2:
    cout<<"Dest : "; cin>>i>>j;  
    if(i<0 || i>=N || j<0 || j>=N)
    {
        cout<<"ERROR! COORDS OUTSIDE AREA SPECIFIED!"<<endl;
        goto start2;
    }
    dest=make_pair(i,j);
    //cout<<src.first<<","<<src.second<<" "<<dest.first<<","<<dest.second<<endl;
    pos.push(src);
}

void Menu_Screen(vector<vector<int>>&V)
{
    int choice;
    src=make_pair(0,0);
    dest=make_pair(V.size()-1,V.size()-1);
    pos.push(src);
    N=V.size();

 restart:
    cout<<"---------------- RAT IN A MAZE ALGORITHM---------------"<<endl;
    cout<<endl<<"Do you want to...";
    cout<<endl<<" 1) Initialize the Maze Matrix";
    cout<<endl<<" 2) Provide Source and Destination for the Maze";
    cout<<endl<<" 3) Find Path";
    cout<<endl<<" 4) Print Maze Matrix";
    cout<<endl<<" 5) Exit"<<endl<<" NOTE: Options 1 and 2 are not mandatory. The program already has values initialized.";
    cout<<endl<<" Enter your choice here (... as 1 or 2 or 3 or 4 or 5) : ";
        cin>>choice;
    switch(choice)
    {
        case 1:     initialize_matrix(V);
        case 2:     src_n_dest(src,dest);
                    goto restart;
        case 3:     break;
        case 4:     print_maze(V);
                    goto restart;
        case 5:     exit(0);
        default:    cout<<"Wrong Option!"<<endl;
                    goto restart;
    }
}

void findPath(vector<vector<int>>&V, int i, int j, vector<vector<int>>&soln)
{
    //cout<<dest.first<<","<<dest.second<<endl;
    if((j+1)<N)                                       //Right
    {
        if(V[i][j+1]==1)          
        {
            soln[i][j+1]=1;
            V[i][j]=0;
            pos.push(make_pair(i,j+1));
            findPath(V,pos.top().first,pos.top().second,soln);
        }
    }
    i=pos.top().first,j=pos.top().second;
    if((i+1)<N)                                       //Down
    {
        if(V[i+1][j]==1)          
        {
            soln[i+1][j]=1;
            V[i][j]=0;
            pos.push(make_pair(i+1,j));
            findPath(V,pos.top().first,pos.top().second,soln);
        }
    }
    i=pos.top().first,j=pos.top().second;
    if((j-1)>=0)                                            //Left
    {
        if(V[i][j-1]==1)          
        {
            soln[i][j-1]=1;
            V[i][j]=0;
            pos.push(make_pair(i,j-1));
            findPath(V,pos.top().first,pos.top().second,soln);
        }
    }
    i=pos.top().first,j=pos.top().second;
    if((i-1)>=0)                                            //Up
    {
        if(V[i-1][j]==1)          
        {
            soln[i-1][j]=1;
            V[i][j]=0;
            pos.push(make_pair(i-1,j));
            findPath(V,pos.top().first,pos.top().second,soln);
        }
    }

    if(i==dest.first && j==dest.second && V[i][j]==1)        //If destination is reached...
    {
        flag=1;
        for(int i=0;i<soln.size();i++)
        {
            for(int j=0;j<soln[i].size();j++)
                cout<<soln[i][j]<<" ";
            cout<<endl;
        }
    }
    V[i][j]=0;
    soln[i][j]=0;
    pos.pop();
}

int main()
{
    vector<vector<int>>V=
    {
        {1,0,1,1,1},
        {1,0,1,0,1},
        {1,1,1,0,1},
        {1,0,1,0,1},
        {1,1,1,0,1}
    };
    Menu_Screen(V);
    vector<vector<int>>soln(N,vector<int>(N));
    soln[src.first][src.second]=1;
    findPath(V,src.first,src.second,soln);
    if(flag==0)
        cout<<endl<<"Path doesn't exist!";
    return 0;
}