//============================================================================
  // Name        : hw.cpp
  // Author      :
  // Version     :
  // Copyright   : Your copyright notice
  // Description : For the Path -
  //	  			 1 = Move Forward
  //				 2 = Move Backward
  //				 8 = Vertical
  //				 4 = Horizontal
  //============================================================================

#include <ev3.h>
#include <string>
#include <iostream>
using namespace std;

//					     					 1 1
int map[10][12] =   {//  0 1 2 3 4 5 6 7 8 9 0 1
  				/*0*/	{1,1,1,1,1,1,1,1,1,1,1,1},
  				/*1*/	{1,0,0,1,0,0,1,0,0,1,1,1},
  				/*2*/	{1,0,0,1,0,0,1,0,0,1,1,1},
  				/*3*/	{1,0,0,1,0,0 ,1,1,1,1,1,1},
  				/*4*/	{1,1,1,1,0,0,1,1,1,1,1,1},
  				/*5*/	{1,1,1,1,0,0,1,1,1,1,1,1},
  				/*6*/	{1,1,1,1,0,0,1,1,1,1,1,1},
  				/*7*/	{0,0,0,1,0,0,1,0,0,0,0,1},
  				/*8*/	{0,0,0,1,0,0,1,0,0,0,0,1},
  				/*9*/	{0,0,0,1,1,1,1,1,1,1,1,1}
  					};
  int path[50];
  int n=0;
  int Start_Pos[2] = {5,1};
  int Goal_Pos[2] = {5,9};
  int x_to_target = Start_Pos[1]-Goal_Pos[1];
  int y_to_target = Start_Pos[0]-Goal_Pos[0];
  int orientation = 1;
  int current_orientation = 9;
  int Current_Pos[7] = {Start_Pos[0], Start_Pos[1], orientation, 1, 1, 1 ,1};// L R U D
  int * position;
  int flag,it = 0;
  int orient_flag = 0;
  //------------------------------------------------------------------------------------------------------------------------------------------------------
  int * Set_Neighbours(int y, int x, int orient)
  {
  	static int ret_neighbours[7] = {y,x, orient ,0,0,0,0};
  	if(orient == 1) //Facing Up
  	{
  		ret_neighbours[0] = y;
  		ret_neighbours[1] = x;
  		ret_neighbours[2] = orient;
  		ret_neighbours[3] = map[y][x-1];
  		ret_neighbours[4] = map[y][x+1];
  		ret_neighbours[5] = map[y-1][x];
  		ret_neighbours[6] = map[y+1][x];
  	}
  	return ret_neighbours;
  }
  //----------------------------------------------------------------------------------------------------------------------------------------------------



int main()
{
  InitEV3();

  std::string greeting("Hello World 90,1000!");

  LcdPrintf(1, "%s\n", greeting.c_str());

  	cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  	while(Current_Pos[0]!=Goal_Pos[0] || Current_Pos[1]!=Goal_Pos[1])
  	{
  		while(y_to_target!=0)
  		{
  			position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  			if(y_to_target < 0)
  			{
  				if(position[6] == 1)
  				{
  					Current_Pos[0] = Current_Pos[0]+1;
  					Current_Pos[1] = Current_Pos[1]+0;
  					y_to_target = Current_Pos[0]-Goal_Pos[0];
  					path[n] = 8;
  					n++;
  					path[n] = 2;
  					n++;
  					//cout<<"\nGoing Down";
  					//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  					//go down
  				}
  				else
  				{
  					//cout<<"\nObstacle 1! At  " <<Current_Pos[0] <<" "<< Current_Pos[1];
  					break;
  				}
  			}

  			else if(y_to_target > 0)
  			{
  				if(position[5] == 1)
  				{
  				Current_Pos[0] = Current_Pos[0]-1;
  				Current_Pos[1] = Current_Pos[1]-0;
  				y_to_target = Current_Pos[0]-Goal_Pos[0];
  				path[n] = 8;
  				n++;
  				path[n] = 1;
  				n++;
  				//cout<<"\nGoing Up";
  				//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  				//go up
  				}
  				else
  				{
  					//cout<<"\nObstacle 2! At  " <<Current_Pos[0] <<" "<< Current_Pos[1];
  					break;
  				}
  			}

  		}

  		while(x_to_target!=0)
  		{
  			position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  			if(x_to_target < 0)
  				{
  					if(position[4] == 1)
  					{
  						Current_Pos[0] = Current_Pos[0]+0;
  						Current_Pos[1] = Current_Pos[1]+1;
  						x_to_target = Current_Pos[1]-Goal_Pos[1];
  						path[n] = 9;
  						n++;
  						path[n] = 1;
  						n++;
  						//cout<<"\nGoing Right";
  						//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  						//go right
  					}
  					else
  					{
  						//cout<<"\nObstacle 3! At  " <<Current_Pos[0] <<" "<< Current_Pos[1];
  						//-------------------------------------------------------------------------------------------------------------
  						if(flag == 0)
  						{
  							while(Current_Pos[0]!=9)
  							{
  								position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  								if(position[6] == 1)
  									{
  									Current_Pos[0] = Current_Pos[0]+1;
  									Current_Pos[1] = Current_Pos[1]+0;   //Going Down
  									path[n]=8;
  									n++;
  									path[n]=2;
  									n++;
  									//cout<<"\nGoing Down";
  									//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  									y_to_target = Current_Pos[0]-Goal_Pos[0];
  									position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  									if(position[4] == 1)
  									{
  										Current_Pos[0] = Current_Pos[0]+0;
  										Current_Pos[1] = Current_Pos[1]+1;
  										path[n]=9;
  										n++;
  										path[n]=1;
  										n++;
  										//cout<<"\nGoing Right";
  										x_to_target = Current_Pos[1]-Goal_Pos[1];
  										//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  										break;
  										//go right
  									}
  								}
  							};
  							flag = 1;
  						}

  						else
  						{
  							while(Current_Pos[0]!=0)
  							{
  								position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  								if(position[5] == 1)
  								{
  									Current_Pos[0] = Current_Pos[0]-1;
  									Current_Pos[1] = Current_Pos[1]+0;   //Going Up
  									path[n] = 8;
  									n++;
  									path[n] = 1;
  									n++;
  									//cout<<"\nGoing UP";
  									//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  									y_to_target = Current_Pos[0]-Goal_Pos[0];
  									position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  									if(position[4] == 1)
  									{
  										Current_Pos[0] = Current_Pos[0]+0;
  										Current_Pos[1] = Current_Pos[1]+1;
  										path[n] = 9;
  										n++;
  										path[n] = 1;
  										n++;
  										//cout<<"\nGoing Right";
  										x_to_target = Current_Pos[1]-Goal_Pos[1];
  										//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  										break;
  									//go right
  									}
  								}
  							};
  						}
  						//-------------------------------------------------------------------------------------------------------------
  					}
  				}
  				else if(x_to_target > 0)
  				{
  					if(position[3] == 1)
  					{
  					Current_Pos[0] = Current_Pos[0]-0;
  					Current_Pos[1] = Current_Pos[1]-1;
  					x_to_target = Current_Pos[1]-Goal_Pos[1];
  					path[n] = 9;
  					n++;
  					path[n] = 2;
  					n++;
  					//cout<<"\nGoing Left";
  					//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  					//go left
  					}
  					else
  						{
  							//cout<<"\nObstacle 4! At  " <<Current_Pos[0] <<" "<< Current_Pos[1];
  							//-------------------------------------------------------------------------------------------------------------

  							while(Current_Pos[0]!=9)
  								{
  									Current_Pos[0] = Current_Pos[0]+1;
  									Current_Pos[1] = Current_Pos[1]+0;   //Going Down
  									path[n] = 8;
  									n++;
  									path[n] = 2;
  									n++;
  									//cout<<"\nGoing Down";
  									//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  									y_to_target = Current_Pos[0]-Goal_Pos[0];
  									position = Set_Neighbours(Current_Pos[0],Current_Pos[1],Current_Pos[3]);
  									if(position[3] == 1)
  									{
  										Current_Pos[0] = Current_Pos[0]-0;
  										Current_Pos[1] = Current_Pos[1]-1;
  										x_to_target = Current_Pos[1]-Goal_Pos[1];
  										path[n] = 9;
  										n++;
  										path[n] = 2;
  										n++;
  										//cout<<"\nGoing Left";
  										//cout<<"\nCurrent Position: " <<Current_Pos[0] <<" "<< Current_Pos[1];
  										break;
  										//go left
  									}
  								};

  							//-------------------------------------------------------------------------------------------------------------
  							//break;
  						}
  				}
  			break;
  		}
  	}
  	/*
  	cout<<"\nFinal Position  "<<Current_Pos[0]<<" "<<Current_Pos[1];
  	cout<<"\nPath is ::";
  	for(int i = 0; i<n; i=i+2)
  	{
  		cout<<"\t"<<path[i];
  	}
  	cout<<"\n\t";
  	for(int j = 1; j<n; j=j+2)
  	{
  		cout<<"\t"<<path[j];
  	}
*/
  	while (it != n)
  	{
  			if(path[it] == current_orientation)
  			 {
  				it++;
  				if(path[it] == 2)
  				{
  					OnRevSync(OUT_AB,30.5);
  					Wait(2000);//move backwards
  					it++;
  				}
  				else if(path[it] == 1)
  				{
  					OnFwdSync(OUT_AB,30.5);
  					Wait(2000);//move forwards
  					it++;
  				}
  			 }
  			else
  			{
  				if(orient_flag == 0)
  				{
  					//Rotate 90 degrees clockwise
  					OnFwdReg(OUT_A, 20);
					OnRevReg(OUT_B, 20);
					Wait(1000);

  					current_orientation = 8;
  					orient_flag = 1;
  				}
  				else if (orient_flag == 1)
  				{
  					//Rotate 90 degrees anti-clockwise
  					OnFwdReg(OUT_B, 20);
					OnRevReg(OUT_A, 20);
					Wait(1000);
  					current_orientation = 9;
  					orient_flag = 0;
  				}
  				it++;
  				if(path[it] == 2)
  				{
  					OnRevSync(OUT_AB,30.5);
  					Wait(2000);
  					//move backwards
  					it++;
  				}
  				else if(path[it] == 1)
  				{
  					OnFwdSync(OUT_AB,30.5);
  					Wait(2000);//move forwards
  					it++;
  				}
  			}
  	}

    FreeEV3();
  	return 0;
  }

