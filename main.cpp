#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <cmath>

const int GRID_SIZE = 60;
const int SCREEN_WIDTH = GRID_SIZE*9;
const int SCREEN_HEIGHT = GRID_SIZE*9;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
std::vector<SDL_Surface*> surfaces;

std::vector<std::vector<char>> board {{'5','3','.','.','7','.','.','.','.'},
{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},
{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},
{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},
{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};

bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &screenSurface, std::string name);
void close(SDL_Window* &window, SDL_Renderer* renderer);

int main( int argc, char* args[] ){
	TTF_Init();
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;
	std::vector<Uint8> selectColor = {127, 127, 127};
	struct {
		int x = -1;
		int y = -1;
	} selectedPosition;

	const int FONT_SIZE = 30;
	TTF_Font* Swansea = TTF_OpenFont("Swansea.ttf", FONT_SIZE);
	const int FONT_PADDING = (GRID_SIZE - FONT_SIZE)/2;

	if(initSDL(window, renderer, screenSurface, "Sudoku")){
			SDL_Event e; 
			SDL_Rect rectangle;
			rectangle.x = 0;
			rectangle.y = 0;
			rectangle.w = GRID_SIZE+1;
			rectangle.h = GRID_SIZE+1;
			bool isRunning = true; 

			int FPS = 24;
			int desiredDelta = 1000/FPS;

			std::vector<std::vector<SDL_Rect>> boxes(10, std::vector<SDL_Rect>(10));
			for (int i = 0; i < 9; i++){
				for (int j = 0; j < 9; j++){
					SDL_Rect rect;
					rect.x = i*GRID_SIZE + FONT_PADDING;
					rect.y = j*GRID_SIZE + FONT_PADDING;
					rect.w = FONT_SIZE;
					rect.h = FONT_SIZE;
					boxes[j][i] = rect;
				}
			}
			
			std::vector<SDL_Surface*> numSurfaces;
			SDL_Color Black = {0, 0, 0};
			for (int i = 0; i <= 9; i++){
				numSurfaces.push_back(TTF_RenderText_Solid(Swansea, std::to_string(i).c_str(), Black));
				surfaces.push_back(numSurfaces[i]);
			}

			std::vector<SDL_Texture*> numbers;
			for (int i = 0; i <= 9; i++){
				numbers.push_back(SDL_CreateTextureFromSurface(renderer, numSurfaces[i]));
			}

			while( isRunning ){ 

				int startLoop = SDL_GetTicks();

				while( SDL_PollEvent( &e ) ){ 
					int x, y;
					switch (e.type){
					case SDL_QUIT:
						isRunning = false; 
						break;
					case SDL_TEXTINPUT:
						if(isdigit(e.text.text[0])){
							std::cout<<e.text.text<<"\n";
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						selectedPosition.x = e.button.x/GRID_SIZE;
						selectedPosition.y = e.button.y/GRID_SIZE;
						break;
					default:
						break;
					}
				}

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderClear(renderer);
				SDL_SetRenderDrawColor(renderer, 0 ,0 , 0, 1);
				
				for(int i=0; i<=SCREEN_HEIGHT; i+=GRID_SIZE){
					if(i%(GRID_SIZE*3) == 0){
						SDL_SetRenderDrawColor(renderer,0,0,0,1);
					}else{
						SDL_SetRenderDrawColor(renderer,160,160,160,1);
					}
					SDL_RenderDrawLine(renderer,0, i, 540, i);
					SDL_RenderDrawLine(renderer,i, 0, i, 540);
				}

				if(selectedPosition.x != -1 && selectedPosition.y != -1){;
					rectangle.x = selectedPosition.x*GRID_SIZE;
					rectangle.y = selectedPosition.y*GRID_SIZE;
					SDL_SetRenderDrawColor(renderer,127,127,0,1);
					SDL_RenderFillRect(renderer, &rectangle);
					std::cout<<selectedPosition.x<<" "<<selectedPosition.y<<"\n";
				}

				for (int i = 0; i < 9; i++){
					for (int j = 0; j < 9; j++){
						if(board[i][j] != '.'){
							switch (board[i][j])
							{
							case '1':
								SDL_RenderCopy(renderer, numbers[1], NULL, &boxes[i][j]);
								break;
							case '2':
								SDL_RenderCopy(renderer, numbers[2], NULL, &boxes[i][j]);
								break;
							case '3':
								SDL_RenderCopy(renderer, numbers[3], NULL, &boxes[i][j]);
								break;
							case '4':
								SDL_RenderCopy(renderer, numbers[4], NULL, &boxes[i][j]);
								break;
							case '5':
								SDL_RenderCopy(renderer, numbers[5], NULL, &boxes[i][j]);
								break;
							case '6':
								SDL_RenderCopy(renderer, numbers[6], NULL, &boxes[i][j]);
								break;
							case '7':
								SDL_RenderCopy(renderer, numbers[7], NULL, &boxes[i][j]);
								break;
							case '8':
								SDL_RenderCopy(renderer, numbers[8], NULL, &boxes[i][j]);
								break;
							case '9':
								SDL_RenderCopy(renderer, numbers[9], NULL, &boxes[i][j]);
								break;
							
							default:
								break;
							}
						}
					}
				}

				SDL_RenderPresent(renderer);

				int delta = SDL_GetTicks() - startLoop;
				if(delta < desiredDelta) SDL_Delay(desiredDelta - delta);
			}
	}
	close(window, renderer);
	return 0;
}

bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &screenSurface, std::string name){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		return false;
	}else{
		window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) return false;
		renderer = SDL_CreateRenderer( window , -1, SDL_RENDERER_ACCELERATED );
		screenSurface = SDL_GetWindowSurface( window );
	}
	return true;
}

void close(SDL_Window* &window, SDL_Renderer* renderer){
	for(int i=0; i<surfaces.size(); i++){
		SDL_FreeSurface(surfaces[i]);
		surfaces[i] = NULL;
	}
	SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
	TTF_Quit();
    SDL_Quit();
}
