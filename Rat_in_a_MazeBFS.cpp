#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;
 
#define MAX 200
int n;
pair<int,int>src,dest;

void print_maze(int maze[][MAX])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<maze[i][j]<<" ";
        cout<<endl;
    }
}

void initialize_matrix(int maze[][MAX])
{
    cout<<endl<<"---------------- Initialize Matrix----------------"<<endl;
    cout<<" Enter number of rows or columns ('cause it's a N*N matrix) : ";
        cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<"Enter element "<<j+1<<" of row "<<i+1<<" : ";
                cin>>maze[i][j];
        }
        cout<<"-----"<<endl;
    }
    cout<<"The final matrix is : "<<endl;
    print_maze(maze);
}

void src_n_dest(pair<int,int>&src,pair<int,int>&dest)
{
    int i,j;
 start1:
    cout<<"Enter source and destination coordinates (Seperated by spaces) "<<endl;
    cout<<"Src : "; cin>>i>>j;  
    if(i<0 || i>=n || j<0 || j>=n)
    {
        cout<<"ERROR! COORDS OUTSIDE AREA SPECIFIED!"<<endl;
        goto start1;
    }
    src=make_pair(i,j);

 start2:
    cout<<"Dest : "; cin>>i>>j;  
    if(i<0 || i>=n || j<0 || j>=n)
    {
        cout<<"ERROR! COORDS OUTSIDE AREA SPECIFIED!"<<endl;
        goto start2;
    }
    dest=make_pair(i,j);
}

void Menu_Screen(int maze[][MAX])
{
    int choice;
    src=make_pair(0,0);
    dest=make_pair(n-1,n-1);

 restart:
    cout<<"---------------- RAT IN A MAZE ALGORITHM (BFS) ---------------"<<endl;
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
        case 1:     initialize_matrix(maze);
        case 2:     src_n_dest(src,dest);
                    goto restart;
        case 3:     break;
        case 4:     print_maze(maze);
                    goto restart;
        case 5:     exit(0);
        default:    cout<<"Wrong Option!"<<endl;
                    goto restart;
    }
}

struct Node
{
    int x, y, dist;
};
int row[]={ -1, 0, 0, 1 };
int col[]={ 0, -1, 1, 0 };

bool isValid(int maze[][MAX], bool visited[][MAX], int row, int col)
{
    return (row >= 0) && (row < n) && (col >= 0) && (col < n) && maze[row][col] && !visited[row][col];
}

void BFS(int maze[][MAX], int i, int j, int x, int y)
{
    bool visited[MAX][MAX];
    memset(visited, false, sizeof visited);
    queue<Node> q;
    visited[i][j] = true;
    q.push({i, j, 0});
    int minDist = INT_MAX;
    
    while(!q.empty())
    {
        Node node=q.front();
        q.pop();
        int i=node.x,j=node.y,dist=node.dist;
        if(i==x && j==y)
        {
            minDist = dist;
            visited[i][j]=true;
            break;
        }
        for(int k=0;k<4;k++)
        {
            if(isValid(maze, visited, i+row[k], j+col[k]))
            {
                visited[i+row[k]][j+col[k]]=true;
                q.push({ i+row[k], j+col[k], dist+1 });
            }
        }
    }
    if (minDist != INT_MAX)
        cout <<endl<<"The shortest path from source to destination has length " << minDist;
    else 
        cout <<endl<< "Destination can't be reached from a given source";
}

int main()
{
    int maze[MAX][MAX] =
    {
        /*{1,0,0,0}, 
        {1,1,0,1}, 
        {1,1,0,0}, 
        {0,1,1,1}*/
        {1,0,1,1,1},
        {1,0,1,0,1},
        {1,1,1,0,1},
        {1,0,1,0,1},
        {1,1,1,0,1}
    };
    n=5;
    Menu_Screen(maze);
    BFS(maze, src.first, src.second, dest.first, dest.second);
    return 0;
}