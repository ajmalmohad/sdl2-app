#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] ){
	
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	// You can't call any SDL functions without initializing SDL first.
	// Since all we care about is using SDL's video subsystem, we will only be passing it the SDL_INIT_VIDEO flag.
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<"\n";
	}else{
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ){
			std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<"\n";
		}else{
			screenSurface = SDL_GetWindowSurface( window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            SDL_Event e; 
			bool quit = false;
			while( quit == false ){ 
				while( SDL_PollEvent( &e ) ){ 
					if( e.type == SDL_QUIT ) quit = true; 
				} 
			}
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
