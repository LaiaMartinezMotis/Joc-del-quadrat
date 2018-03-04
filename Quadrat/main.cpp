#include "../SDL/include/SDL.h"
#include <stdio.h>
#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char*args[]) {

	SDL_Window*window = NULL;
	SDL_Renderer*renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);

	//Create Window
	window = SDL_CreateWindow("Create Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Create the items
	SDL_Rect rectangle; //Creem rectangle
	rectangle.x = 240;// Posició x en l'espai
	rectangle.y = 180;// Posició y en l'espai
	rectangle.w = 120;// Amplada
	rectangle.h = 80;// ALt

	SDL_Rect rectangle1; //Creem el segon rectangle
	rectangle1.x = NULL;
	rectangle1.y = NULL;
	rectangle1.w = NULL;
	rectangle1.h = NULL; 


		//Inicialize the render
		renderer = SDL_CreateRenderer(window, -1, 0);// Window=pantalla on vols que tho renderitzi, 0 imprimis en 2d
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);// Color de la window
	SDL_RenderClear(renderer);// Pintar pantalla d'un color

							  //Bucle
	bool loop = true;
	// Inicialize the loop
	bool Bala = false;// Create an afirmation
	while (loop)
	{
		SDL_Event event; // Inputs
		if (SDL_PollEvent(&event) != 0)// When its 0 it means that there isnt an input, when that changes to a 1 means that there is an input
		{
			switch (event.type)//Type of the input
			{
			case SDL_QUIT: // Quit program. Press x
				loop = false;
				break;

			case  SDL_KEYDOWN: //Moviment i atac
				switch (event.key.keysym.sym) {
				case SDLK_UP:// Move up the red rec.

					if (rectangle.y > 0) {
						rectangle.y -= 15;
					}
					break;
				case SDLK_DOWN://Move up the red rec.

					if (rectangle.y < 480 - rectangle.h) {
						rectangle.y += 15;
					}
					break;
				case SDLK_LEFT://Move left the red rec.
					if (rectangle.x > 0) {
						rectangle.x -= 15;
					}
					break;
				case SDLK_RIGHT://Move right the red rec.
					if (rectangle.x < 640 - rectangle.w) {
						rectangle.x += 15;
					}

					break;

				case SDLK_SPACE://Create the bullet
					Bala = true;//If we presss space then the bullet appears
					rectangle1.x = (rectangle.x) + 120;
					rectangle1.y = (rectangle.y) + 25;
					rectangle1.h = 20;
					rectangle1.w = 30;
					break;
				}
				break;
			}
		}





		//Render  rojo
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);// Color quadrat gran
		SDL_RenderFillRect(renderer, &rectangle);// Rellenem el quadrat amb el color

												 //Renderizar Cuadrado verde
		if (Bala = true) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &rectangle1);
			rectangle1.x += 10;
			SDL_Delay(10);
		}

		//Renderitzar finerstra

		SDL_RenderPresent(renderer); //Renderitza tot el que hi ha a la pantalla
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Color window
		SDL_RenderClear(renderer);//Pinta la pantalla de color
								  /*if (rectangle.x <= 520) {
								  rectangle.x++;
								  if (rectangle.x == 520) {
								  rectangle.x = 0;
								  }
								  }*/

	}
	return 0;
}