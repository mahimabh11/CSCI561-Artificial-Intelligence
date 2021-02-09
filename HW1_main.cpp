//
//  homework11.cpp
//  Homeworkcpp
//
//  Created by Mahima Bhargava on 9/15/19.
//  Copyright © 2019 Mahima Bhargava. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;
// We are declaring the node structure for BFS. We record the row,column and distance values along with a vector to remember path
struct Node
{
    int a, b;
    int distance;
    vector<Node> parent;
};
// r1 and c1 are row and column vectors employed to extract the 8 neighbors of a cell
int r1 []= {0,0,-1,1,-1,-1,1,1};
int c1 []= {-1,1,0,0,-1,1,-1,1};
string out=""; //Stores the

int isAllowed(int height_cell, int curr_height,int threshold)
{
    
    if (abs(height_cell-curr_height) > threshold) // Check if cell height difference within threshold
        return 0;
    return 1;
}

int isInBounds(int h,int w,int a,int b)
{
    if (a < h && a >= 0 && b < w && b >= 0) // Check if indices are within limits
        return 1;
    
    return 0;
}
int printInOutFile(vector<Node> path) // prints the path for BFS function
{
    if (path.size() == 0) //no elements in path
        return 0;
    printInOutFile(path[0].parent);
    out = out + to_string(path[0].b) + "," + to_string(path[0].a) + " ";
    return 1;
}
int Breadth_First_Search(vector< vector<int> > &terrain, int h,int w,int x,int y,int threshold,int d_col, int d_row)
{
    int visited[h][w],a,b,r,c,explored[h][w],i,j;
    for (i=0;i<h;i++)
    {
        for(j=0;j<w;j++){
            visited[i][j]=0;
            explored[i][j]=0;
        }
    }
    queue<Node> Queue;
    Node current_node;
    visited[y][x] = 1;
    if (y==d_row && x==d_col)
    {
        out= out + to_string(x)+","+ to_string(y);
        return 1;
    }
    Queue.push({y,x,0,{}});
    while (!Queue.empty())
    {
        current_node= Queue.front();
        a = current_node.a;
        b = current_node.b;
        Queue.pop();
        explored[a][b]=1;
        for (i = 0; i < 8; i++)
        {
            r= a + r1[i];
            c= b + c1[i];
            if (isInBounds(h,w,r,c) && isAllowed(terrain[r][c],terrain[a][b],threshold) && visited[r][c]==0 )
            {
                if (r==d_row && c==d_col)
                {
                    cout<< current_node.distance + 1;
                    int path_exists= printInOutFile({current_node});
                    out= out + to_string(c)+","+ to_string(r);
                    return path_exists;
                }
                visited[r][c] = 1;
                Queue.push({r,c, current_node.distance+1, {current_node}});
            }
        }
    }
    return -1;
}
// We are declaring the node structure for UCS and A*. We record the row,column,g(n) and f(n) values along with a vector to remember path
struct cell {
    
    int a;
    int b;
    int distance ;
    int f;
    vector<cell> parent;
    cell(int a,int b,int distance,int f,vector<cell> parent)
    : a(a), b(b) , distance(distance),f(f),parent(parent)
    {
    }
};
//This is used to compare key values and employ a min heap
struct CompareDistance {
    int operator()(cell const& c1, cell const& c2)
    {
        return c1.f > c2.f;
    }
};
int printInOut(vector<cell> path) //prints the path for UCS and A* functions
{
    if (path.size() == 0) //no elements in path
        return 0;
    printInOut(path[0].parent);
    out = out + to_string(path[0].b) + "," + to_string(path[0].a) + " ";
    return 1;
}
int Uniform_Cost_Search(vector< vector<int> > &terrain, int h,int w,int x,int y,int threshold,int d_col, int d_row)
{
    int visited[h][w],a,b,r,c,explored[h][w],i,j;
    for (i=0;i<h;i++)
    {
        for(j=0;j<w;j++){
            visited[i][j]=0;
            explored[i][j]=0;
        }
    }
    priority_queue<cell, vector<cell>, CompareDistance> Queue;
    Queue.push({y,x,0,0,{}});
    visited[y][x] = 1;
    while (!Queue.empty())
    {
        cell current_node= Queue.top();
        a = current_node.a;
        b = current_node.b;
        if (visited[a][b]==1 && explored[a][b]==1)
        {
            Queue.pop();
            continue;
        }
        explored[a][b]=1;
        Queue.pop();
        
        if (a==d_row && b==d_col)
        {
            cout << current_node.distance;
            int path_exists= printInOut({current_node});
            return path_exists;
        }
        
        for (i = 0; i < 4; i++) //for 4 neighbors
        {
            r= a + r1[i];
            c= b + c1[i];
            if (isInBounds(h,w,r,c) && isAllowed(terrain[r][c],terrain[a][b],threshold) && (visited[r][c]==0 || explored[r][c]==0))
            {
                visited[r][c] = 1;
                Queue.push({r,c, current_node.distance + 10,current_node.distance + 10, {current_node}});
            }
        }
        for (j = 4; j < 8; j++) //for diagonal neighbors
        {
            r= a + r1[j];
            c= b + c1[j];
            if (isInBounds(h,w,r,c) && isAllowed(terrain[r][c],terrain[a][b],threshold) && (visited[r][c]==0 || explored[r][c]==0))
            {
                visited[r][c] = 1;
                Queue.push({r,c, current_node.distance + 14,current_node.distance + 14, {current_node}});
            }
        }
    }
    return -1;
}
int A_Search(vector< vector<int> > &terrain, int h,int w,int x,int y,int threshold,int d_col, int d_row)
{
    int visited[h][w],a,b,r,c,explored[h][w],i,j,diff,heuristic,g;
    for (i=0;i<h;i++)
    {
        for(j=0;j<w;j++)
        {
            visited[i][j]=0;
            explored[i][j]=0;
        }
    }
    priority_queue<cell, vector<cell>, CompareDistance> Queue;
    heuristic=abs(sqrt( pow(y-d_row,2) + pow(x-d_col,2)));
    Queue.push({y,x,0,heuristic,{}});
    visited[y][x] = 1;
    while (!Queue.empty())
    {
        cell current_node= Queue.top();
        a = current_node.a;
        b = current_node.b;
        if (visited[a][b]==1 && explored[a][b]==1)
        {
            Queue.pop();
            continue;
        }
        explored[a][b]=1;
        Queue.pop();
        
        if (a==d_row && b==d_col)
        {
            cout<< current_node.distance;
            int path_exists= printInOut({current_node});
            return path_exists;
        }
        
        for (i = 0; i < 4; i++) //for 4 neighbors
        {
            r= a + r1[i];
            c= b + c1[i];
            if (isInBounds(h,w,r,c) && isAllowed(terrain[r][c],terrain[a][b],threshold) && (visited[r][c]==0 || explored[r][c]==0))
            {
                visited[r][c] = 1;
                heuristic= abs(sqrt( pow(r-d_row,2) + pow(c-d_col,2)))*10;
                diff= abs(terrain[r][c]-terrain[a][b]);
                g= current_node.distance + 10 + diff;
                Queue.push({r,c,g,g+ heuristic,{current_node}});
            }
        }
        for (j = 4; j < 8; j++) //for diagonal neighbors
        {
            r= a + r1[j];
            c= b + c1[j];
            if (isInBounds(h,w,r,c) && isAllowed(terrain[r][c],terrain[a][b],threshold) && (visited[r][c]==0 || explored[r][c]==0))
            {
                visited[r][c] = 1;
                heuristic= abs(sqrt( pow(r-d_row,2) + pow(c-d_col,2)))*10;
                diff= abs(terrain[r][c]-terrain[a][b]);
                g= current_node.distance + 14 + diff;
                Queue.push({r,c, g,g+ heuristic,{current_node}});
            }
        }
    }
    return -1;
}

int getInput ()
{
    fstream file;
    string line,algo;
    int i,j,w,h,x,y,threshold,n,d_row, d_col;
    vector<vector<int>> terrain;
    vector<vector<int>> targets;
    
    file.open("input13.txt",ios::in);
    
    
    if(!file)
    {
        cout<<"Error in opening file!!!"<<endl;
        return 0;
    }
    getline(file, algo);
    file>>w>> h >> x >> y >> threshold >> n;
    vector<int> single_target(2);
    
    for (i=0;i<n;i++)
    {
        targets.push_back(single_target);
        for(j=0;j<2;j++)
            file >> targets[i][j];
    }
    vector<int> terrainData(w);
    for (i=0;i<h;i++)
    {
        terrain.push_back(terrainData);
        for(j=0;j<w;j++)
            file >> terrain[i][j];
    }
    file.close();
    for(i=0;i<n;i++)
    {
        if(i>0)
            out= out + "\n";
        d_row=targets[i][1];
        d_col=targets[i][0];
        int result;
        if (algo.compare("BFS")==0)
            result=Breadth_First_Search(terrain,h,w,x,y,threshold,d_col,d_row);
        else if (algo.compare("UCS")==0)
            result=Uniform_Cost_Search(terrain,h,w,x,y,threshold,d_col,d_row);
        else
            result=A_Search(terrain,h,w,x,y,threshold,d_col,d_row);
        if (result==-1){
            out = out + "FAIL";
        }
    }
    fstream outfile;
    outfile.open("output.txt",fstream::out);
    outfile <<out;
    outfile.close();
    return 0;
}
int main()
{
    getInput();
    return 0;
}










