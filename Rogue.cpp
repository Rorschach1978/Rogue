// Rogue.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>
#include <list>
#include <string>
#include <cstdlib>
#include <time.h>

#define SCRN_X_MIN 0
#define SCRN_X_MAX 799

#define SCRN_Y_MIN 0
#define SCRN_Y_MAX 599

#define WORLD_WIDTH	2000
#define WORLD_HEIGHT	2000

#define SCRN_WIDTH	800
#define SCRN_HEIGHT	600

#define BLOCK_WIDTH	32
#define BLOCK_HEIGHT	32

#define CHARACTER_WIDTH  32
#define CHARACTER_HEIGHT 32



SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* world_buffer = NULL;


struct Grid {

	int n_blocchi_x;

	int n_blocchi_y;

	int resto_x;

	int resto_y;

};

static  int viewport_x = 0;

static  int viewport_y = 0;

static  int character_x = 0;

static  int character_y = 0;

static Grid world_grid;

void create_grid()
{

	world_grid.n_blocchi_x = int(WORLD_WIDTH / BLOCK_WIDTH);

	world_grid.n_blocchi_y = int(WORLD_HEIGHT / BLOCK_HEIGHT);

	//calcolo numero blocchi orizzontali e posizioni
	int resto_x = 0;

	if (WORLD_WIDTH % BLOCK_WIDTH != 0)
	{
		world_grid.resto_x = (WORLD_WIDTH - BLOCK_WIDTH * world_grid.n_blocchi_x) / 2;

	}

	//calcolo blocchi verticali e posizioni


	if (WORLD_HEIGHT % BLOCK_HEIGHT != 0)
	{
		world_grid.resto_y = (WORLD_HEIGHT - BLOCK_HEIGHT * world_grid.n_blocchi_y) / 2;

	}
	
}

int draw_grid()
{



  int y = world_grid.resto_y;

	SDL_Surface * world_surface = SDL_CreateRGBSurface(0, WORLD_WIDTH, WORLD_HEIGHT, 32, 0, 0, 0, 0);

	SDL_LockSurface(world_surface);
 
	while (y< (WORLD_HEIGHT - BLOCK_HEIGHT))
	  {
	    int x = world_grid.resto_x;

	    while (x<(WORLD_WIDTH - BLOCK_WIDTH))
	      {

		SDL_Rect r = {x,y,BLOCK_WIDTH,BLOCK_HEIGHT};

		SDL_FillRect(world_surface,&r, SDL_MapRGB(world_surface->format,std::rand() % 256,std::rand() % 256,std:: rand() % 256));
      
		x+=BLOCK_WIDTH;
	}

      y +=BLOCK_HEIGHT;  
    }

	int x = world_grid.resto_x;

	unsigned int * ptr = (unsigned int *) (world_surface->pixels);

	while (x <WORLD_WIDTH)
	{
		//linee verticali
		for (unsigned int y = world_grid.resto_y; y<WORLD_HEIGHT - world_grid.resto_y; ++y)
		{
			ptr[x + WORLD_WIDTH * y] = 0x00FF0000;
		}

		x += (BLOCK_WIDTH);
	}

	y = world_grid.resto_y;

	while (y <WORLD_HEIGHT)
	{
		//linee orizzontali
		for (unsigned int x = world_grid.resto_x; x<WORLD_WIDTH - world_grid.resto_x; ++x)
		{

			ptr[x + WORLD_WIDTH * y] = 0x00FF0000;

		}
		y += (BLOCK_HEIGHT);
	}

	SDL_UnlockSurface(world_surface);

	world_buffer = SDL_CreateTextureFromSurface(renderer, world_surface);

	SDL_FreeSurface(world_surface);


	return 1;
}

int color_grid()
{


  return 1;
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Error initialising SDL! " << std::endl;

		exit(EXIT_FAILURE);
	}

	if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0)
	{
		std::cout << "Error creating SDL Windows and Renderer! " << std::endl;

		exit(EXIT_FAILURE);
	}

	world_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WORLD_WIDTH, WORLD_HEIGHT);

	if (world_buffer == NULL)
	{
		std::cout << "Error creating SDL Surface! " << std::endl;

		exit(EXIT_FAILURE);
	}


	srand ( time(NULL) );
	
	std::string font_path = ".//freefont-20120503//FreeMono.ttf";
	
	    TTF_Init();

	    TTF_Font *font = TTF_OpenFont(font_path.c_str(), 25);

	    if (font == NULL)
	      {

		std::cout <<"TTF error: font not found"<<std::endl;

		exit(EXIT_FAILURE);
	    }

	create_grid();

	color_grid();
	
	draw_grid();

	SDL_bool done = SDL_FALSE;

	SDL_Rect srcrect;

	SDL_Rect dstrect;

	SDL_Event event;
	
	while (!done)
	  {	
		while (SDL_PollEvent(&event))
		  {

		    switch(event.type)
		      {

		      case SDL_QUIT : done = SDL_TRUE; break;

			/* Look for a keypress */
		      case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch( event.key.keysym.sym )
			  {

			  case SDLK_a:
			    character_x -= 1;
			    break;

			  case SDLK_d:
			    character_x += 1;
			    break;

			  case SDLK_w:
			    character_y -= 1;
			    break;

			  case SDLK_s:
			    character_y += 1;
			    break;
			    
			  case SDLK_LEFT:
			    viewport_x -= 8;
			    break;

			  case SDLK_RIGHT:
			    viewport_x += 8;
			    break;

			  case SDLK_UP:
			    viewport_y -= 8;
			    break;

			  case SDLK_DOWN:
			    viewport_y += 8;
			    break;

			  default:
			    break;
			  }//end of switch(event.key)			
		      }	//end of switch(event.type)   
		  }//end of while

		if (viewport_x < 0) viewport_x = 0;
		
		if (viewport_x >= (WORLD_WIDTH - SCRN_WIDTH )) viewport_x = (WORLD_WIDTH - SCRN_WIDTH );
				
		if (viewport_y < 0) viewport_y = 0;
		
		if (viewport_y >= (WORLD_HEIGHT - SCRN_HEIGHT ))  viewport_y = (WORLD_HEIGHT - SCRN_HEIGHT );

		if (character_x <0 ) character_x =0;

		if (character_x > SCRN_WIDTH - CHARACTER_WIDTH) character_x = SCRN_WIDTH - CHARACTER_WIDTH; 

		if (character_y <0 ) character_y =0;

		if (character_y > SCRN_HEIGHT - CHARACTER_HEIGHT) character_y = SCRN_HEIGHT - CHARACTER_HEIGHT; 
		
		//Clear Background Black
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		
	        SDL_RenderClear(renderer);

		//Draw World

		srcrect = { viewport_x ,viewport_y, SCRN_WIDTH, SCRN_HEIGHT };
		
		dstrect = { 0 , 0 , SCRN_WIDTH , SCRN_HEIGHT };
		
		SDL_SetRenderTarget(renderer, world_buffer);

		SDL_RenderCopy(renderer, world_buffer, &srcrect, &dstrect);

		SDL_Color color = { 255, 255, 255 };

		std::string pos = "ViewPort position -  x : " + std::to_string(viewport_x) + " y : " + std::to_string(viewport_y);

		SDL_Surface * font_surface = TTF_RenderText_Solid(font, pos.c_str(), color);

		SDL_Texture * font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);

		int texW = 0;

		int texH = 0;

		SDL_QueryTexture(font_texture, NULL, NULL, &texW, &texH);

		SDL_Rect font_dstrect = { 200, 550, texW, texH };
		
		SDL_RenderCopy(renderer, font_texture, NULL, &font_dstrect);

		//Draw Character

		SDL_Rect r {character_x,character_y, CHARACTER_WIDTH, CHARACTER_HEIGHT};
  
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255 );
	       
		SDL_RenderFillRect( renderer, &r );

		//Draw Everything

		SDL_RenderPresent(renderer);

		//

		SDL_DestroyTexture(font_texture);

		SDL_FreeSurface(font_surface);

	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	
	if (window) {
		SDL_DestroyWindow(window);
	}

	

	SDL_DestroyTexture(world_buffer);
	
	TTF_CloseFont(font);

	TTF_Quit();
	
	SDL_Quit();

	return 0;
}
