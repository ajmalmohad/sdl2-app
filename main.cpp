#include <SDL.h>
#include <iostream>
#include <vector>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 576;
std::vector<SDL_Surface*> surfaces;

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool initSDL(SDL_Window* &window, SDL_Surface* &screenSurface, std::string name);
bool loadMedia(SDL_Surface* &surface, std::string filePath);
void close(SDL_Window* &window);

int main( int argc, char* args[] ){
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* mapSurface = NULL;
	struct pos {
		int x = 0;
		int y = 0;
	} player;

	if(initSDL(window, screenSurface, "Game")){
		if(loadMedia(mapSurface, "hello_world.bmp")){
			SDL_BlitSurface( mapSurface, NULL, screenSurface, NULL );
			SDL_UpdateWindowSurface( window );
			SDL_Event e; 
			bool isRunning = true; 
			while( isRunning ){ 
				while( SDL_PollEvent( &e ) ){ 
					std::cout<<player.x<<" "<<player.y<<"\n";
					if( e.type == SDL_QUIT ) isRunning = false; 
					else if( e.type == SDL_KEYDOWN ){
                        switch( e.key.keysym.sym ){
							case SDLK_UP:
                            	player.y++;
                            	break;

                            case SDLK_DOWN:
								player.y--;
                            	break;

                            case SDLK_LEFT:
								player.x--;
								break;

                            case SDLK_RIGHT:
								player.x++;
								break;

                            default:
								break;
                        }
                    }
				}
			}
		}
	}
	close(window);
	return 0;
}

bool initSDL(SDL_Window* &window, SDL_Surface* &screenSurface, std::string name){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		return false;
	}else{
		window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) return false;
		else screenSurface = SDL_GetWindowSurface( window );
	}
	return true;
}

bool loadMedia(SDL_Surface* &surface, std::string filePath){
    surface = SDL_LoadBMP(filePath.c_str());
    if( surface == NULL ) return false;
	surfaces.push_back(surface);
    return true;
}

void close(SDL_Window* &window){
	for(int i=0; i<surfaces.size(); i++){
		SDL_FreeSurface(surfaces[i]);
		surfaces[i] = NULL;
	}
    SDL_DestroyWindow( window );
    window = NULL;
    SDL_Quit();
}