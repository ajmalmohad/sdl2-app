#include <SDL.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initSDL(SDL_Window* &window, SDL_Surface* &screenSurface);
bool loadMedia(SDL_Surface* &helloWorld, char* filePath);
void close(SDL_Window* &window, std::vector<SDL_Surface*> &surfaces);

int main( int argc, char* args[] ){
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* helloWorld = NULL;
	std::vector<SDL_Surface*> surfaces;
	surfaces.push_back(screenSurface);
	surfaces.push_back(helloWorld);

	if(initSDL(window, screenSurface)){
		if(loadMedia(helloWorld, "hello_world.bmp")){
			SDL_UpperBlit( helloWorld, NULL, screenSurface, NULL );
			SDL_UpdateWindowSurface( window );
			SDL_Event e; 
			bool quit = false; 
			while( quit == false ){ 
				while( SDL_PollEvent( &e ) ){ 
					if( e.type == SDL_QUIT ) quit = true; 
				} 
			}
		}
	}
	close(window, surfaces);
	return 0;
}

bool initSDL(SDL_Window* &window, SDL_Surface* &screenSurface){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		return false;
	}else{
		window = SDL_CreateWindow( "Simple", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) return false;
		else screenSurface = SDL_GetWindowSurface( window );
	}

	return true;
}

bool loadMedia(SDL_Surface* &surface, char* filePath){
    surface = SDL_LoadBMP(filePath);
    if( surface == NULL ) return false;
    return true;
}

void close(SDL_Window* &window, std::vector<SDL_Surface*> &surfaces){
	for(auto surface : surfaces){
		SDL_FreeSurface( surface );
    	surface = NULL;
	}
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_Quit();
}