//
//  main.cpp
//  Assignment 2
//
//  Created by Mahima Bhargava on 10/7/19.
//  Copyright © 2019 Mahima Bhargava. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <tuple>
#include <climits>
#include <ctime>
#include <cstdlib>
using namespace std;
int r1 []= {-1,-1,1,1,0,0,-1,1};
int c1 []= {-1,1,-1,1,-1,1,0,0};
string player,max_player,min_player;
int movecount=0;
char character;
struct Tile
{
    int x;
    int y;
};
vector <Tile > white_goal= {{0,0},{0,1},{0,2},{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{1,4},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{4,0},{4,1}};
vector <Tile > black_goal= {{11,14},{11,15},{12,13},{12,14},{12,15},{13,12},{13,13},{13,14},{13,15},{14,11},{14,12},{14,13},{14,14},{14,15},{15,11},{15,12},{15,13},{15,14},{15,15}};
vector <vector <int >> camps=
{
    {2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
};
int x=100;
int y=0;
int z=1;
int n=INT_MIN;

vector <vector <int >> diagw=
{
    {100,95,90,85,80,n,n,n,n,n,n,n,n,n,n,n},
    {95,95,90,85,80,z,n,n,n,n,n,n,n,n,n,n},
    {90,90,85,80,z,z,z,n,n,n,n,n,n,n,n,n},
    {85,85,80,z,z,z,z,z,n,n,n,n,n,n,n,n},
    {80,80,z,z,z,z,z,z,z,n,n,n,n,n,n,n},
    {n,n,z,z,z,z,z,z,z,z,n,n,n,n,n,n},
    {n,n,z,z,z,z,z,z,z,z,z,n,n,n,n,n},
    {n,n,n,z,z,z,z,z,z,z,z,z,n,n,n,n},
    {n,n,n,n,z,z,z,z,z,z,z,z,z,n,n,n},
    {n,n,n,n,n,z,z,z,z,z,z,z,z,z,n,n},
    {n,n,n,n,n,n,z,z,z,z,z,z,z,z,z,n},
    {n,n,n,n,n,n,n,z,z,z,z,z,z,z,y,y},
    {n,n,n,n,n,n,n,n,z,z,z,z,z,y,y,y},
    {n,n,n,n,n,n,n,n,n,z,z,z,y,y,y,y},
    {n,n,n,n,n,n,n,n,n,n,z,y,y,y,y,y},
    {n,n,n,n,n,n,n,n,n,n,n,y,y,y,y,y},
   
};
vector <vector <int >> diagb=
{
    {y,y,y,y,y,n,n,n,n,n,n,n,n,n,n,n},
    {y,y,y,y,y,z,n,n,n,n,n,n,n,n,n,n},
    {y,y,y,y,z,z,z,n,n,n,n,n,n,n,n,n},
    {y,y,y,z,z,z,z,z,n,n,n,n,n,n,n,n},
    {y,y,z,z,z,z,z,z,z,n,n,n,n,n,n,n},
    {n,z,z,z,z,z,z,z,z,z,n,n,n,n,n,n},
    {n,n,z,z,z,z,z,z,z,z,z,n,n,n,n,n},
    {n,n,n,z,z,z,z,z,z,z,z,z,n,n,n,n},
    {n,n,n,n,z,z,z,z,z,z,z,z,z,n,n,n},
    {n,n,n,n,n,z,z,z,z,z,z,z,z,z,n,n},
    {n,n,n,n,n,n,z,z,z,z,z,z,z,z,n,n},
    {n,n,n,n,n,n,n,z,z,z,z,z,z,z,80,80},
    {n,n,n,n,n,n,n,n,z,z,z,z,z,80,85,85},
    {n,n,n,n,n,n,n,n,n,z,z,z,80,85,90,90},
    {n,n,n,n,n,n,n,n,n,n,z,80,85,90,95,95},
    {n,n,n,n,n,n,n,n,n,n,n,80,85,90,95,100}
   
};

struct HalmaMove {
    Tile from;  // Position of piece to be moved.
    Tile to;      // Square it is to move to.
    char movetype;
    vector <Tile > sequence;
    HalmaMove(char type, Tile start,Tile end, vector <Tile > seq) {
        movetype=type;
        from= start;
        to= end;
        sequence= seq;
    }
};

struct combineResult
{
    int eval;
    HalmaMove move;
};
vector <HalmaMove > finalMoves;

int isInBounds(int a,int b)
{
    if (a < 16 && a >= 0 && b < 16 && b >= 0) // Check if indices are within limits
        return 1;
    
    return 0;
}
bool compare(const HalmaMove& a, const HalmaMove& b)
{
    return a.sequence.size() > b.sequence.size();
}

Tile canJump(vector<vector<char> > &boardnow,int r,int c, int adjr,int adjc)
{
    Tile newtile;
    if(boardnow[adjr][adjc]!='.' && boardnow[adjr][adjc]!='X')
    {
        if((adjr==r)&&(adjc== c+1) && isInBounds(adjr,adjc+1)&& (boardnow[adjr][adjc+1]=='.'))
            {
                newtile.x=adjr; newtile.y=adjc+1;
            }
        else if((adjr==r) && (adjc== c-1) && isInBounds(adjr,adjc-1)&&(boardnow[adjr][adjc-1]=='.'))
            {
                newtile.x=adjr; newtile.y=adjc-1;
            }
        else if((adjr==r-1)&&(adjc== c+1) && isInBounds(adjr-1,adjc+1)&&(boardnow[adjr-1][adjc+1]=='.'))
            {
                newtile.x=adjr-1; newtile.y=adjc+1;
            }
        else if((adjr==r-1)&&(adjc== c-1) && isInBounds(adjr-1,adjc-1)&& (boardnow[adjr-1][adjc-1]=='.'))
            {
                newtile.x=adjr-1; newtile.y=adjc-1;
            }
        else if((adjr==r-1)&&(adjc== c) && isInBounds(adjr-1,adjc)&& (boardnow[adjr-1][adjc]=='.'))
            {
                newtile.x=adjr-1; newtile.y=adjc;
            }
        else   if((adjr==r+1) &&(adjc== c+1) && isInBounds(adjr+1,adjc+1)&&(boardnow[adjr+1][adjc+1]=='.'))
            {
                newtile.x=adjr+1; newtile.y=adjc+1;
            }
        else if((adjr==r+1) &&(adjc== c-1) && isInBounds(adjr+1,adjc-1)&& (boardnow[adjr+1][adjc-1]=='.'))
            {
                newtile.x=adjr+1; newtile.y=adjc-1;
            }
        else if((adjr==r+1) &&(adjc==c) && isInBounds(adjr+1,adjc) && (boardnow[adjr+1][adjc]=='.'))
            {
                newtile.x=adjr+1; newtile.y=adjc;
            }
        else
            {
                newtile.x=-1; newtile.y=-1;
            }
     }
    else
    {
        newtile.x=-1; newtile.y=-1;
    }
    //cout<<"newtile"<< newtile.x<< ","<<newtile.y<<"\n";
    return newtile;
}
int isAGoalState(int r,int c)
{
    if(character=='W' && camps[r][c]==2)
        return 1;
    else if(character=='B' && camps[r][c]==1)
        return 1;
    else
        return 0;
    
}
int isInOwnCamp(int r,int c)
{
    if(character=='W' && camps[r][c]==1)
        return 1;
    else if(character=='B' && camps[r][c]==2)
        return 1;
    else
        return 0;
    
}
int GameOver(vector<vector<char> > boardnow)
{
    int i,row,col,count=0;
    if(character=='W')
    {
        for(i=0;i<19;i++)
        {
            row= white_goal[i].x;
            col= white_goal[i].y;
            if(boardnow[row][col]=='.' || boardnow[row][col]=='x')
                return 0;
            if(boardnow[row][col]=='W')
                count++;
        }
        if(count>0)
            return 1;
    }
    else
   {
        count=0;
        for(i=0;i<19;i++)
        {
            row= black_goal[i].x;
            col= black_goal[i].y;
            if(boardnow[row][col]=='.' || boardnow[row][col]=='x')
                return 0;
            if(boardnow[row][col]=='B')
                count++;
        }
        if(count>0)
            return 2;
    }
    return 0;
}

vector<Tile> possible_jumps(Tile start, vector< vector<char >>& boardnow)
{
    Tile result;
    vector<Tile > pos_jumps;
    int i,r,c;
    for (i = 0; i < 8; i++)
    {
        r= start.x + r1[i];
        c= start.y + c1[i];
        if(isInBounds(r, c)==0)
            continue;
        result= canJump(boardnow,start.x, start.y, r, c);
        if(result.x!= -1)
            pos_jumps.push_back(result);
    }
    return pos_jumps;
}

/*vector< vector<char >> apply_move(vector< vector<char >> boardnow, Tile start, Tile move)
{
    //char ch=boardnow[start.x][start.y];
    //boardnow[start.x][start.y]= 'X';
    boardnow[move.x][move.y]='X';
    return boardnow;
} */

vector< vector<char >> do_move(vector< vector<char >> boardnow, Tile start, Tile move)
{
    char ch=boardnow[start.x][start.y];
    boardnow[start.x][start.y]= '.';
    boardnow[move.x][move.y]=ch;
    return boardnow;
}
void display(vector<vector <char >>boardnow)
{
     cout<<"\n";
    for(int i=0;i<16;i++)
    {
    for(int j=0;j<16;j++)
        cout<< boardnow[i][j];
    cout<<"\n";
    }
}
vector< vector<char >> currentboard;
struct jump_seq {
    vector<vector<Tile >> jumps;
    jump_seq(Tile start)
    {
        explore_jumps({}, start);
    }

    void explore_jumps(vector<Tile > sequence, Tile start) {
        vector<Tile > moves = possible_jumps(start, currentboard);
        //cout << moves.size()<<"size \n";
        if(!sequence.empty())
        {
             //jumps.insert(jumps.begin(),sequence); // save individual jump sub-sequences too
            jumps.push_back(sequence);
        }
        if(!moves.empty())
        {
            //cout << moves.size()<<"size \n";
            for ( const auto move : moves)
            {
                //cout<<"move" << move.x <<"," <<move.y<<" \n";
                if(currentboard[move.x][move.y]=='X')
                    continue;
                currentboard[move.x][move.y]='X';
                vector<Tile> new_seq = sequence;
               // currentboard = apply_move(currentboard, start, move);
                //display(currentboard);
                new_seq.push_back(move);
                explore_jumps(new_seq, move);
             }
           // cout<<"\n \n";
            
        }
    }
};

vector<vector <Tile >> getMovesForTile(vector<vector<char> > &boardnow,int a,int b)
{
    int i,r,c;
    //vector<vector <Tile >> moves = jump_seq({a,b}, boardnow).jumps;
    currentboard= boardnow;
    vector<vector <Tile >> moves = jump_seq({a,b}).jumps;
    for (i = 0; i < 8; i++)
    {
        r= a + r1[i];
        c= b + c1[i];
        if(!isInBounds(r,c)) // check if not in bounds
            continue;
       if(boardnow[r][c]=='.')
        {
            //current.clear();
           // current.push_back({r,c});
            moves.push_back({{r,c}});
        }
    }
    //cout << result.size()<<"size \n";
    return moves;
}

vector <HalmaMove > get_next_moves(vector<vector<char> > &boardnow)
{
    //cout<<"player is " << player <<"\n";
    finalMoves.clear();
    int i,j;
    vector <Tile > incamp={};
    vector <Tile > outofcamp={};
    vector <Tile > goalcamp={};
    vector <Tile > move;
    vector<vector <Tile >> result;
    vector<HalmaMove> outmoves;
    vector<HalmaMove> inmoves;
    vector <HalmaMove > normalmoves;
    character=player.at(0);
   for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            
            if(boardnow[i][j] != character)
                continue;
            if(isInOwnCamp(i,j))
            {
                incamp.push_back({i,j}); // vector of pcs in own camp
                //cout<< i <<"," <<j <<"\n";
            }
            else if(isAGoalState(i,j))
            {
                goalcamp.push_back({i,j});
                //cout<<"at goal" << i  <<"," <<j <<"\n";
            }
            else
            {
                outofcamp.push_back({i,j}); // vector of pcs outside own camp
                //cout<< i <<"," <<j <<"\n";
            }
        }
    }
      //cout<<"sizeof" <<outofcamp.size();
    if(!incamp.empty())
    {
        for(i=0;i< incamp.size();i++)
        {
            Tile current= incamp[i];
            //cout<< current.x <<"," <<current.y <<"\n";
            result.clear();
            result = getMovesForTile(boardnow,current.x,current.y);
           if(!result.empty())
            {
                 //cout<< "\n current"<<current.x <<"," <<current.y <<"\n";
                  for(int k=0;k<result.size();k++)
                  {
                      move= result[k];
                      auto size= move.size();
                      
                      Tile temp= move[size-1];
                     // cout<<"end " <<temp.x <<","<< temp.y<<"\n";
                      if(!isInOwnCamp(temp.x, temp.y)) // new tile in not in own camp, its out of the camp
                      {
                          char type;
                          if((abs(current.x-temp.x)>1) || (abs(current.y-temp.y)>1))
                              type='J';
                          else
                              type='E';
                         HalmaMove newMove= HalmaMove(type,current, temp,move);
                         outmoves.push_back(newMove);
                        //cout<< "out \n";
                      }
                      else
                      {
                          if((character=='W') && (temp.x <= current.x) && (temp.y <= current.y))
                          {
                              char type;
                              if((abs(current.x-temp.x)>1) || (abs(current.y-temp.y)>1))
                                  type='J';
                              else
                                  type='E';
                              HalmaMove newMove= HalmaMove(type,current, temp,move);
                              inmoves.push_back(newMove);
                          }
                          else if((character=='B') && (temp.x >= current.x) && (temp.y >= current.y))
                          {
                              char type;
                              if((abs(current.x-temp.x)>1) || (abs(current.y-temp.y)>1))
                                    type='J';
                              else
                                    type='E';
                            HalmaMove newMove= HalmaMove(type,current, temp,move);
                            inmoves.push_back(newMove);
                          }
                      }
                  }
            }
        }
        if(!outmoves.empty())
            return outmoves;
        else if(!inmoves.empty())
            return inmoves;
    } // end of incamp conditions
    
   if(!outofcamp.empty())
    {// more conditions have to be added
        for(i=0;i< outofcamp.size();i++)
        {
            Tile current= outofcamp[i];
            //cout<< current.x <<"," <<current.y <<"\n";
            result = getMovesForTile(boardnow,current.x,current.y);
           // cout<< "result size" << result.size() <<"\n";
            if(!result.empty())
            {
                 //cout<< "\n current"<<current.x <<"," <<current.y <<"\n";
               // cout<< "result size" << result.size() <<"\n";
                  for(int k=0;k<result.size();k++)
                  {
                      move= result[k];
                      auto size= move.size();
                      Tile temp= move[size-1];
                      //cout<<"end" <<temp.x <<","<< temp.y;
                      if(isInOwnCamp(temp.x,temp.y)) // if is not in own camp and move ends in own camp, skip
                            continue;
                      char type;
                      if((abs(current.x-temp.x)>1) || (abs(current.y-temp.y)>1))
                          type='J';
                      else
                          type='E';
                    HalmaMove newMove= HalmaMove(type,current, temp,move);
                    finalMoves.push_back(newMove);
                   }
            }
        }
     //   if(finalMoves.size()<10)
       //     return finalMoves;
    }
    
        for(i=0;i< goalcamp.size();i++)
        {
        Tile current= goalcamp[i];
         //cout<< current.x <<"," <<current.y <<"\n";
         result = getMovesForTile(boardnow,current.x,current.y);
        // cout<< "result size" << result.size() <<"\n";
         if(!result.empty())
         {
              //cout<< "\n current"<<current.x <<"," <<current.y <<"\n";
            // cout<< "result size" << result.size() <<"\n";
               for(int k=0;k<result.size();k++)
               {
                   move= result[k];
                   auto size= move.size();
                   Tile temp= move[size-1];
                   //cout<<"end" <<temp.x <<","<< temp.y;
                  if(!isAGoalState(temp.x,temp.y)) // if in goal state and goes to non-goal state,skip
                         continue;
                    char type;
                    if((abs(current.x-temp.x)>1) || (abs(current.y-temp.y)>1))
                         type='J';
                     else
                       type='E';
                   HalmaMove newMove= HalmaMove(type,current, temp,move);
                   finalMoves.push_back(newMove);
               }
          }
        }
    return finalMoves;
}
/*int evaluate(vector<vector <char >>boardnow)
{
    int score=0;
    char ch;
    if(character=='W')
    {
        ch= 'W';
        for(int i=0;i<16;i++)
            for(int j=0;j<16;j++)
            {
                if(boardnow[i][j]!=ch)
                    continue;
                if(isInOwnCamp(i, j))
                {
                    score=score;
                }
                else if(isAGoalState(i, j))
                {
                    score= score+50;
                }
                else if(i>=8)
                {
                    score=score+2;
                }
                else if(i<=7 && j<=7)
                {
                    score=score+15;
                }
                else
                {
                    score=score+4;
                }
            }
    }
    else
    {
        ch= 'B';
        for(int k=0;k<16;k++)
        {
            for(int l=0;l<16;l++)
            {
                if(boardnow[k][l]!=ch)
                    continue;
                if(isInOwnCamp(k,l))
                {
                    score=score+1;
                }
                else if(isAGoalState(k,l))
                {
                    score= score+50;
                }
                else if(k<=7)
                {
                    score=score+2;
                }
                else if(k>=8 && l>=8)
                {
                    score=score+15;
                }
                else
                {
                    score=score+4;
                }
            }
        }
    }
    return score;
} */

/*int evaluate(vector<vector <char >>boardnow)
{
    int score=0,ingoalb=0,ingoalw;
    if(character=='W')
    {
        for(int i=0;i<16;i++)
            for(int j=0;j<16;j++)
            {
                if(boardnow[i][j]=='W')
                {
                if(isAGoalState(i, j))
                {
                    ingoalw++;
                    continue;
                }
                else if(i>=8)
                {
                    score=score+2;
                }
                else if(i<=7 && j<=7)
                {
                    score=score+15;
                }
                else
                {
                    score=score+4;
                }
                }
            }
    }
    else
    {
        ch= 'B';
        for(int k=0;k<16;k++)
        {
            for(int l=0;l<16;l++)
            {
                if(boardnow[k][l]!=ch)
                    continue;
                if(isInOwnCamp(k,l))
                {
                    score=score+1;
                }
                else if(isAGoalState(k,l))
                {
                    score= score+50;
                }
                else if(k<=7)
                {
                    score=score+2;
                }
                else if(k>=8 && l>=8)
                {
                    score=score+15;
                }
                else
                {
                    score=score+4;
                }
            }
        }
    }
    return score;
} 
/ *int evaluate(vector<vector <char >>boardnow)
{
    int score,ingoalw=0,ingoalb=0,cw=0,cb=0,maxval=0,d,extra=0,win=0,bin=0;
    if(character=='W')
    {
    int bdist=0,wdist=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(boardnow[i][j]=='W')
            {
                if(isAGoalState(i,j))
                {
                    ingoalw++;
                    continue;
                }
                else if(isInOwnCamp(i, j))
                    win++;
                d= sqrt(i^2 + j^2);;
                wdist=wdist + d;
                maxval= max(maxval,d);
                if(j>=7)
                    cw= cw + sqrt((7-i)^2 + (7-j)^2);
                else
                    extra=extra+abs(15-j)*10;
               
            }
            else if(boardnow[i][j]=='B')
            {
                bdist= bdist + sqrt((15-i)^2 + (15-j)^2);
            }
        }
    }
            score= (bdist-wdist) * 21 +  ingoalw*30 + cw*-6 + maxval*-10 + extra +(-20*win);
      
    }
    else //B
    {
        int bdist=0,wdist=0;
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(boardnow[i][j]=='B')
                {
                    if(isAGoalState(i,j))
                    {
                        ingoalb++;
                        continue;
                    }
                    else if(isInOwnCamp(i, j))
                        bin++;
                    d= sqrt((15-i)^2 + (15-j)^2);;
                    bdist= bdist + d;
                    maxval= max(maxval,d);
                    if(j<=7)
                        cb= cb + sqrt((7-i)^2 + (7-j)^2);
                    else
                        extra= extra + j*10;
                }
                else if(boardnow[i][j]=='W')
                {
                    wdist=wdist + sqrt(i^2 + j^2);
                }
            }
        }
            score= (bdist-wdist) * 21 + ingoalb*30 + cb*-6 + maxval*-10 +extra + (-20*bin);
        }
    
    return score;
} */
// MY MOST TRY
/* int evaluate(vector<vector <char >>boardnow)
{
    int score=0,ingoalw=0,ingoalb=0,cw=0,cb=0,maxval=0,d,extra=0,win=0,bin=0;
    if(character=='W')
    {
    int bdist=0,wdist=0;
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(boardnow[i][j]=='W')
            {
                if(isAGoalState(i,j))
                {
                     score= score + diagw[i][j];
                     continue;
                }
                score= score + diagw[i][j];
                d= sqrt(i^2 + j^2);;
                wdist=wdist + d;
                maxval= max(maxval,d);
               //if(j>=7)
                //    cw= cw + sqrt((7-i)^2 + (7-j)^2);
              //  else
               //     extra=extra+abs(15-j)*10;
              //  score= score + (15-i+15-j)*2;
            }
            else if(boardnow[i][j]=='B')
            {
                bdist= bdist + sqrt((15-i)^2 + (15-j)^2);
            }
        }
    }
        score= score   - maxval ;
      
    }
    else //B
    {
        int bdist=0,wdist=0;
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(boardnow[i][j]=='B')
                {
                   // if(isAGoalState(i,j))
                   // {
                     //   score=
                       // continue;
                   // }
                   // else
                    score= score + diagb[i][j];
                    d= sqrt((15-i)^2 + (15-j)^2);;
                    bdist= bdist + d;
                    maxval= max(maxval,d);
                    //if(j<=7)
                      //  cb= cb + sqrt((7-i)^2 + (7-j)^2);
                    //else
                      //  extra= extra + j*10;
                    score= score + (i+j)*2;
                }
                else if(boardnow[i][j]=='W')
                {
                    wdist=wdist + sqrt(i^2 + j^2);
                }
            }
        }
        score= score + (bdist-wdist)*10  + ingoalb*20 - maxval  ;
        }
    
    return score;
} */
//final
int evaluate(vector<vector <char >>boardnow)
{
   // int min=INT_MAX;
    vector<Tile > out;
    int score=0,maxd=0,d=0,goalw=0,goalb=0,score2=0;
    if(character=='B')
    {
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
          //  if(min>(i+j))
           //     min=i+j;
            if(boardnow[i][j]=='B')
            {
              //  if(isAGoalState(i,j))
                //{
                    //goalb++;
                    //score=score +diagb[i][j] +(i+j);
              //  }
               // else
               // {
                    score= score + (i+j) + diagb[i][j] ;
               // }
               // d= sqrt((15-i)^2 + (15-j)^2);
                //maxd=max(maxd,d);
            }

            
        }
    }
   
    }
    else
    {
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
               // if(min>(30-i-j))
                 //   min=30-i-j;
                if(boardnow[i][j]=='W')
                {
                    //if(isAGoalState(i,j))
                    //{
                      
                        score=score +diagw[i][j] + 30-i-j;
                   // }
                    //else
                  //  {
                        //out.push_back({i,j});
                       // score= score + (30-i-j) + diagw[i][j] ;
                    //}
                   // d= sqrt((i)^2 + (j)^2);
                   // maxd=max(maxd,d);
                    
                   // score=score +diagw[i][j]+30 -i-j;
                }
            }
        }
       //  score= score + min*10;
    }

    return score;
}


 


/*int evaluate(vector<vector <char >>boardnow)
{
    int total=0,x,y;
    if(character=='W')
    {
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            if(isAGoalState(i, j))
                continue;
            if(boardnow[i][j]=='W')
            {
                for(int k=0;k<19;k++)
                {
                    x=white_goal[k].x;
                    y=white_goal[k].y;
                    if(boardnow[x][y]=='W')
                        continue;
                    total = total - sqrt((x-i)^2 + (y-j)^2);
                }
            }
        }
    }
    }
    else
    {
        for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                if(isAGoalState(i, j))
                    continue;
                if(boardnow[i][j]=='B')
                {
                    for(int k=0;k<19;k++)
                    {
                        x=black_goal[k].x;
                        y=black_goal[k].y;
                        if(boardnow[x][y]=='B')
                            continue;
                        total = total - sqrt((x-i)^2 + (y-j)^2);
                    }
                }
            }
        }
    }
    return total;
} */

combineResult alphabeta(vector<vector <char >> boardnow, int depth, int isMaximizingPlayer, int alpha,int beta)
{
    int bestVal;
    if (GameOver(boardnow) || depth==0)
        return {evaluate(boardnow), {' ',{-1,-1},{-1,-1}, {}}};

if (isMaximizingPlayer)
{
    HalmaMove decision= HalmaMove(' ',{-1,-1},{-1,-1}, {});
    bestVal = INT_MIN;
    player=max_player;
     vector <HalmaMove > moveList = get_next_moves(boardnow); // get the possible legal moves
   //  sort(moveList.begin(),moveList.end(), compare); //sorting the moves according the move length(giving preference to jumps)
    for(int i=0;i< moveList.size();i++)
    {
        //time check
        vector< vector<char >> newBoard= do_move( boardnow,moveList[i].from,moveList[i].to);
        //cout<<"\n";
        combineResult res = alphabeta(newBoard,depth-1,0,alpha,beta);
        int value= res.eval;
        if(bestVal < value)
        {
            decision= moveList[i];
            bestVal=value;
        }
        
       //cout<< moveList[i].movetype <<" "<< moveList[i].from.x <<"," <<moveList[i].from.y << " to " <<moveList[i].to.x <<"," <<moveList[i].to.y<<" "<<value<<"\n";
        alpha = max(alpha, bestVal);
        if( beta <= alpha)
            break;
    }
    return {bestVal, decision};
}
else
{
    HalmaMove decision= HalmaMove(' ',{-1,-1},{-1,-1}, {});
    bestVal = INT_MAX;
    player= min_player;
    vector <HalmaMove > moveList2 = get_next_moves(boardnow);
    sort(moveList2.begin(),moveList2.end(), compare);
    //sort(moveList2.begin(),moveList2.end(), compare);
   // display(boardnow);
    
     for(int i=0;i< moveList2.size();i++)
    {
        //time check
        vector< vector<char >> newBoard= do_move( boardnow,moveList2[i].from,moveList2[i].to); // get an updated board
        combineResult res = alphabeta(newBoard,depth-1,1,alpha,beta); // get the best move
        int value= res.eval;
        if(bestVal > value)
        {
            decision= moveList2[i]; // saving the best move in the data structure decision
            bestVal=value;
        }
        beta= min(beta, bestVal);
        if( beta <= alpha)
            break;
    }
    return {bestVal, decision};
 }
}
void master_Agent(vector<vector<char >> config)
{
    int winner;
    double time1=300, time2=300;
    char check='W';
    display(config);
    while(!GameOver(config))
    {
        if(check=='W')
        {
            movecount++;
            cout<<check<<"\n";
            min_player= "BLACK";
            max_player="WHITE";
            time_t start,end;
            time(&start);
            combineResult ans= alphabeta(config,3, 1, INT_MIN, INT_MAX);
            config= do_move(config, ans.move.from, ans.move.to);
            time(&end);
            double time_taken = double(end - start);
            time1=time1 - time_taken;
            cout<< ans.eval <<"\n";
            display(config);
            //cout << "Time taken by alpha beta is : " << fixed << time_taken << setprecision(5);
            //cout << " sec " << endl;
            check='B';
            winner=GameOver(config);
            if(winner)
            {
                cout<< "winner is" << winner;
                break;
            }
            if(time1==0)
            {
                cout<<"time1 " << time1 <<"\n";
                cout<<"time2 " << time2 <<"\n";
                break;
            }
        }
        else
        {
            movecount++;
            cout<<check<<"\n";
            max_player= "BLACK";
            min_player="WHITE";
          
            time_t start,end;
            time(&start);
            combineResult ans= alphabeta(config,3, 1, INT_MIN, INT_MAX);
            config= do_move(config, ans.move.from, ans.move.to);
            time(&end);
            double time_taken = double(end - start);
            time2=time2 - time_taken;
            cout<< ans.eval <<"\n";
            display(config);
            check='W';
            winner= GameOver(config);
            if(winner)
            {
                cout<< "winner is" << winner;
                break;
            }
            if(time2==0)
            {
                cout<<"time 1" << time1 <<"\n";
                cout<<"time 2" << time2 <<"\n";
                break;
            }
        }
       
    }
    cout<<"Winner is "<< winner;
}
int getInput ()
{
    fstream file;
    string temp;
    vector<vector<char> > board;
    string mode,play;
    float rem_time;
    int i,j,depth;
    file.open("input.txt",ios::in);
    if(!file)
    {
        cout<<"Error in opening file!!!"<<endl;
        return 0;
    }
    getline(file,mode);
    getline(file,temp);
    /*if(temp.at(0)=='W')
    {
        max_player="WHITE";
        min_player= "BLACK";
    }
    else
    {
        max_player="Black";
        min_player= "WHITE";
    }
        */
  //  player="BLACK";
    file>> rem_time;
    vector<char> row(16);
    for (i=0;i<16;i++)
    {
        board.push_back(row);
        for(j=0;j<16;j++)
            file >> board[i][j];
    }
    file.close();
   
    master_Agent(board);
    
   /* if(mode.at(0)=='S')
        depth=3;
   
    else
        depth=3;
   // time_t start,end;
    //time(&start);
    combineResult ans= alphabeta(board,depth, 1, INT_MIN, INT_MAX);
   
    fstream outfile;
    outfile.open("output.txt",fstream::out);
    Tile ex= ans.move.from;
    Tile curr= ans.move.sequence[0];
    for(int m=1;m<=ans.move.sequence.size();m++)
    {
        cout<< "sequence is "<<ans.move.movetype<< " " <<ex.y <<"," <<ex.x << " "<< curr.y <<","<<curr.x<<"\n";
        outfile<< ans.move.movetype<< " " <<ex.y <<"," <<ex.x << " "<< curr.y <<","<<curr.x<<"\n";;
        ex=curr;
        curr= ans.move.sequence[m];
    }
   outfile.close(); */
    
    return 0;
}
// time(&end);
/*double time_taken = double(end - start);
cout << "Time taken by alpha beta is : " << fixed << time_taken << setprecision(5);
cout << " sec " << endl; */
//cout<< C <<" "<< ans.move.from.x <<"," <<ans.move.from.y << " to " << ans.move.to.x <<"," <<ans.move.to.y;


/*player=max_player;
   vector <HalmaMove > moveList = get_next_moves(board);
   cout<< moveList.size()<<"\n";
   //auto result = getMovesForTile(board,12,13,0,1);
   for (i = 0; i < moveList.size(); i++)
      {
          cout<< "move type " << moveList[i].movetype <<"\n";
          cout<< "from " << moveList[i].from.x <<"," << moveList[i].from.y << "\n";
          cout << "to "  << moveList[i].to.x <<"," << moveList[i].to.y << "\n";
          for(j=0;j<moveList[i].sequence.size();j++)
              cout<< moveList[i].sequence[j].x <<"," << moveList[i].sequence[j].y <<" ";
          cout<<"\n\n";
      }*/
   //Tile canjumpthis= canJump(board, 11, 12, 12, 12);
   //cout<< board[11][12] << board[12][12] <<board[13][12];


int main() {
    time_t start,end;
    time(&start);
    getInput();
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    cout << " sec " << endl;
    cout<<movecount<<"is the count";
    return 0;
}








