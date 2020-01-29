#include <iostream>
#include <SDL2/SDL.h>
#include </usr/include/SDL2/SDL_image.h>
#include </usr/include/SDL2/SDL2_gfxPrimitives.h>
#include</usr/include/SDL2/SDL2_rotozoom.h>
#include <string>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<SDL2/SDL_ttf.h>
using namespace std;
/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
SDL_Event e;
bool quit = false ;

//Screen dimension constants
const int SCREEN_WIDTH = 10;
const int SCREEN_HEIGHT = 800;
class Block{
  public:
  int number;
  bool show=0;
};


int main( int argc, char* args[] )
{
	int r,g,b;
	r=255;g=140;b=140;
	srand(time(0));
	Block block[9][6];
	SDL_Window* window = NULL;
	  SDL_Init(SDL_INIT_VIDEO);
	 window=SDL_CreateWindow("SDL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,300,450,SDL_WINDOW_SHOWN);
	  SDL_Renderer* grenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	int level=1;
	int total_show_box;
	int a[6] = {0 , 0 , 0 , 0 , 0 , 0} ;
	int count_show_box=0;
	while (!quit)
	{
		total_show_box=rand()%6+1;
		for(int i=0 ; i < 6 ; i++)
		{
			a[i]=0;
		}
		count_show_box=0;
		while(count_show_box <= total_show_box){
			int s=rand()%6;
			int flag=1;
			for (int i=0;i<6;i++)
			{
				if (a[i]==s && s!=0)
					flag=0;
			}
			if (flag==1)
			{
				block[0][s].show=1;
				block[0][s].number=level;				
			}


			count_show_box++;
		}
			
			
		for(int i=0;i<9;i++){
			for(int j=0;j<6;j++){
				if (block[i][j].show==1)
					boxRGBA(grenderer,j*50,i*50,(j*50)+50,(i*50)+50,r,g,b,255);
			}
		}
	  SDL_RenderPresent(grenderer);
	  SDL_Delay(1000);
	  SDL_SetRenderDrawColor(grenderer, 0, 0, 0, 0);
	  SDL_RenderClear(grenderer);
		for(int i=8;i>=0;i--)
		{
			for(int j=5;j>=0;j--){
				if(block[i][j].show==1){
					block[i][j].show=0;
					block[i+1][j].show=1;
					block[i+1][j].number=block[i][j].number;
					block[i+1][j].number=0;}
					}}
	
	level++;

	while( SDL_PollEvent( &e ) != 0 )
         	{
            	//User requests quit
            	if( e.type == SDL_QUIT )
            	{
                	quit = true ;
            	}
        	}

	}

  //SDL_DestroyWindow(window);
	return 0;
}
