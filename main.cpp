/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include </usr/include/SDL2/SDL.h>
#include <stdio.h>
#include </usr/include/SDL2/SDL2_gfxPrimitives.h>
#include </usr/include/SDL2/SDL_image.h>
#include <math.h>
#include <string>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<SDL2/SDL_ttf.h>


//Screen dimension constants
const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 450;
const int SOLID = 255;
const int BALL_RAD = 10;
const int b_r = 255;
const int b_g = 99;
const int b_b = 71;

//Main loop flag
bool quit = false;
bool sec1_end = false;
bool sec2_end = false;
//Event handler
SDL_Event e;
SDL_Event p;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Balz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

class Block{
  public:
  int number;
  bool show=0;
};

class Ball
{
	public:
		double v;
		double v_x;
		double v_y;
		int x;
		int y;
		int ball_show_number;
};

int main(int argc, char *args[])
{
	init();
	int x = SCREEN_WIDTH/2 , x_stop = SCREEN_WIDTH/2 ;
	int y = SCREEN_HEIGHT-10 , y_stop = SCREEN_HEIGHT - BALL_RAD ;
	double degree = 20 ;
    double l = 100 , rad = (M_PI / 180)*degree;
	double v=3 , v_x =v * cos(rad) , v_y = v * sin(rad) ;
	SDL_Rect fillRect;
	int r,g,b;
	r=255;g=140;b=140;
	srand(time(0));
	Block block[9][6];
	int level=1;
	Ball ball[100];
	int total_show_box;
	int a[6] = {0 , 0 , 0 , 0 , 0 , 0} ;
	int count_show_box=0;
	int ball_count_shoot=1;
	int index_counter_shoot=0;
	int ball_count_stop=0;
	bool flag_stop=false;
	while (!quit)
	{
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer);

		//show blocks
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
		//end of show blocks
		
		//secanse 1 starts:
		while(!sec1_end)
		{
			//Clear screen; and show 
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer);
		
		
			//fillRect = {0, 0, 50, 50};
			SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0xAB );		
			SDL_RenderFillRect( gRenderer, &fillRect);
		
			filledCircleRGBA(gRenderer, x_stop, y_stop, BALL_RAD, b_b, b_g, b_r, SOLID);

			SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF );

			while (SDL_PollEvent(&e) != 0) 
			{
				if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
						case SDLK_RIGHT:
						{
							degree--;
							break;
						}
						case SDLK_LEFT:
						{
							degree++;
							break;
						}
						case SDLK_SPACE :
						{
							sec2_end = false ;
							sec1_end = true ;
							break;
						}
					}
				}
				if(degree > 170)
				{
					degree = 170 ;
				}
				if(degree < 10)
				{
					degree = 10 ;
				}
			}

			rad = (M_PI / 180)*degree;
			SDL_RenderDrawLine( gRenderer, x_stop , y_stop , x_stop + l*cos(rad) , y_stop - l*sin(rad));

			//show blocks
			for(int i=0;i<9;i++){
			for(int j=0;j<6;j++){
				if (block[i][j].show==1)
					boxRGBA(gRenderer,j*50,i*50,(j*50)+50,(i*50)+50,r,g,b,255);
			}
		}
			
			SDL_RenderPresent( gRenderer );


			while( SDL_PollEvent( &e ) != 0 )
        	{
            	//User requests quit
            	if( e.type == SDL_QUIT )
            	{
					sec1_end = true ;
					sec2_end = true ;
                	quit = true;
            	}
        	}


		}//secance 1 ends


		//clear secance 1
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer);
		SDL_RenderPresent( gRenderer );



		rad = (M_PI / 180)*degree;
		v=3 ;
		v_x =v * cos(rad) ; 
		v_y = v * sin(rad) ;
		for(int i=0 ; i<4 ; i++)
		{
			ball[i].v = v;
			ball[i].v_x = v_x;
			ball[i].v_y = v_y;
			ball[i].x = x_stop;
			ball[i].y = y_stop;
		}
		//sec 2 start:
		//ball_count_shoot = 1;
		ball_count_stop = 0;
		index_counter_shoot = 0;
		flag_stop=false;
		while(!sec2_end)
		{
			/*rad = (M_PI / 180)*degree;
			v=10 ; v_x =v * cos(rad) ; v_y = v * sin(rad) ;*/
			//Clear screen; and show 
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer);
		
		
			//fillRect = {0, 0, 50, 50};
			SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0xAB );		
			SDL_RenderFillRect( gRenderer, &fillRect);
		
			for(int i=0 ; i<2 ; i++)
			{
				filledCircleRGBA(gRenderer, ball[i].x, ball[i].y, BALL_RAD, b_b, b_g, b_r, SOLID);
			}

			SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF );


			//show blocks
			for(int i=0;i<9;i++){
			for(int j=0;j<6;j++){
				if (block[i][j].show==1)
					boxRGBA(gRenderer,j*50,i*50,(j*50)+50,(i*50)+50,r,g,b,255);
			}
		}


			SDL_RenderPresent( gRenderer );

			/*for(int i=0 ; i<2 ; i++)
			{
				ball[i].ball_show_number = i;
				if(i )
			}*/




			for(int i=0 ; i < ball_count_shoot ; i++)
			{
				if(ball[i].x >= SCREEN_WIDTH - BALL_RAD) 
				{
					ball[i].x = SCREEN_WIDTH - BALL_RAD ;
					ball[i].v_x = -1 * ball[i].v_x  ;
				}
				if(ball[i].x <= BALL_RAD)
				{
					ball[i].x = BALL_RAD ;
					ball[i].v_x  = -1 * ball[i].v_x  ;
				}
				if(ball[i].y <= BALL_RAD)
				{
					ball[i].y = BALL_RAD  ;
					ball[i].v_y = -1 * ball[i].v_y ;
				}


				ball[i].x += ball[i].v_x;
				ball[i].y -= ball[i].v_y;
			}
			



			index_counter_shoot++;
			if(ball_count_shoot >= 3)
			{
				ball_count_shoot= 3 ;
			}
			if(index_counter_shoot >=10)
			{
				ball_count_shoot++;
			}



			/*if(y >= SCREEN_HEIGHT - BALL_RAD)
			{
				sec2_end = true ;
				sec1_end = false ;
				x_stop = x;
				y = SCREEN_HEIGHT - BALL_RAD ;
				y_stop = y ;
			}*/


			for(int i=0 ; i<2 ; i++)
			{
				if(ball[i].y > SCREEN_HEIGHT - BALL_RAD && flag_stop == false)
				{
					x_stop = ball[i].x;
					y_stop = SCREEN_HEIGHT - BALL_RAD ;
					flag_stop = true;
				}
				if(ball[i].y > SCREEN_HEIGHT - BALL_RAD)
				{
					ball[i].v_y = 0 ;
					ball[i].v_x =0 ;
					ball[i].x = x_stop ;
					ball[i].y = y_stop ;
					ball_count_stop++ ;
				}
				if(ball_count_stop  == 3 )
				{
					sec2_end = true ;
					sec1_end = false ;
				}
			}
			
			ball_count_stop = 0;
			


			while( SDL_PollEvent( &e ) != 0 )
         	{
            	//User requests quit
            	if( e.type == SDL_QUIT )
            	{
					sec2_end = true ;
					sec1_end = true ;
                	quit = true ;
            	}
        	}
			SDL_Delay(7);
		}//end of sec 2
		



		//move blocks
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



		//clear secance 2
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer);
		SDL_RenderPresent( gRenderer );







		//out with X
		while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
             if( e.type == SDL_QUIT )
            {
				sec2_end = true ;
				sec1_end = true ;
                quit = true;
            }
        }

		//SDL_Delay(30);
	}	
	return 0;
}