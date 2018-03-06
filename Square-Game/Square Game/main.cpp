#include "../SDL/include/SDL.h"
#include "../SDL_IMAGE/include/SDL_image.h"
#include <iostream>
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#pragma comment (lib, "../SDL_IMAGE/libx86/SDL2_image.lib")

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window*window = NULL; //Create window
SDL_Renderer*renderer = NULL;//Create render
SDL_Texture* Texture = NULL;// Create texture 1

//Texture Funcion
	  SDL_Texture* loadTexture(std::string path) { 
		SDL_Texture* ATexture=NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		ATexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
		return ATexture;
	}
int main(int argc, char*args[]) {
	
	SDL_Init(SDL_INIT_VIDEO);

	//Create Window
	window = SDL_CreateWindow("Create Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	int imgFlags = IMG_INIT_PNG;
	

	Texture = loadTexture("../Photos/Background.png");

	
	


	(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"));
	
	//Create the items
	SDL_Rect rectangle; //Creem rectangle
	rectangle.x = 260;// Posició x en l'espai
	rectangle.y = 190;// Posició y en l'espai
	rectangle.w = 120;// Amplada
	rectangle.h = 80;// ALt

	SDL_Rect rectangle1; //Creem el segon rectangle
	rectangle1.x = NULL;
	rectangle1.y = NULL;
	rectangle1.w = NULL;
	rectangle1.h = NULL; 


		//Inicialize the render
	

//Bucle
	bool loop = true;
	bool moveup = false;
	bool movedown = false;
	bool moveright = false;
	bool moveleft = false;
	// Inicialize the loop
	bool Bala = false;// Create an afirmation
	while (loop)
	{
		SDL_Event event; // Inputs
		if (SDL_PollEvent(&event) != 0)// When its 0 it means that there isnt an input, when that changes to a 1 means that there is an input
		{
			if (event.type == SDL_QUIT) {
				loop = false;
			}

			if(event.type==SDL_KEYDOWN){   //Moviment i atac
				if (event.key.keysym.sym== SDLK_UP) {// Move up the red rec.
					moveup = true;
					}
					
				if (event.key.keysym.sym == SDLK_DOWN) {// Move down the red rec.
					movedown = true;
				}
					
				if (event.key.keysym.sym == SDLK_RIGHT) {// Move right the red rec.
					moveright = true;
				}
				if (event.key.keysym.sym == SDLK_LEFT) {// Move left the red rec.
					moveleft = true;
				}

				if (event.key.keysym.sym == SDLK_SPACE) {//Create the bullet

					Bala = true;//If we presss space then the bullet appears
					rectangle1.x = (rectangle.x) + 120;
					rectangle1.y = (rectangle.y) + 25;
					rectangle1.h = 20;
					rectangle1.w = 30;
				}
			}
			if (event.type == SDL_KEYUP) {   //Moviment i atac
				if (event.key.keysym.sym == SDLK_UP) {// Move up the red rec.
					moveup = false;
				}

				if (event.key.keysym.sym == SDLK_DOWN) {// Move down the red rec.
					movedown = false;
				}

				if (event.key.keysym.sym == SDLK_RIGHT) {// Move right the red rec.
					moveright = false;
				}
				if (event.key.keysym.sym == SDLK_LEFT) {// Move left the red rec.
					moveleft = false;
				}
			}
			
		}

//Borders in the screen
		if (rectangle.y < 0) {
			rectangle.y = 0;
		}
		if (rectangle.y > 400) {
			rectangle.y = 400;
		}
		if (rectangle.x < 0) {
			rectangle.x = 0 ;
		}
		if (rectangle.x > 520) {
			rectangle.x = 520;
		}
		//Movement
		if (moveup == true){
				rectangle.y -= 15;
		}
		if (movedown == true) {
			rectangle.y += 15;
		}
		if (moveleft == true) {
				rectangle.x -= 15;
		}
		if (moveright == true) {
			rectangle.x += 15;
		}

	SDL_RenderCopy(renderer, Texture, 0, 0);

		//Render  rojo
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);// Color quadrat gran
		SDL_RenderFillRect(renderer, &rectangle);// Rellenem el quadrat amb el color

												
	    //Renderizar Cuadrado verde
		if (Bala = true) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rectangle1);
			rectangle1.x += 10;
			
		}
		
		//Renderitzar finerstra

		
		SDL_RenderClear(renderer);//Pinta la pantalla de color
								  /*if (rectangle.x <= 520) {
								  rectangle.x++;
								  if (rectangle.x == 520) {
								  rectangle.x = 0;
								  }
								  }*/
								  //Render Textura
	
		SDL_Delay(18);
		SDL_DestroyTexture(Texture);
		Texture = NULL;
	}
	SDL_DestroyTexture(Texture);
    Texture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return 0;
}