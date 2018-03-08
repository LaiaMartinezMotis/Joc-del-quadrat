#include "../SDL/include/SDL.h"
#include "../SDL_IMAGE/include/SDL_image.h"
#include "../SDL_Mixer/include/SDL_mixer.h"
#include <iostream>


#pragma comment(lib, "../SDL/libx86/SDL2.lib")
#pragma comment(lib, "../SDL/libx86/SDL2main.lib")
#pragma comment (lib, "../SDL_IMAGE/libx86/SDL2_image.lib")
#pragma comment (lib, "../SDL_Mixer/libx86/SDL2_mixer.lib")

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;


SDL_Window* window; //Create window
SDL_Renderer* renderer;//Create render
SDL_Texture* background;// Create texture 1
SDL_Texture* character;//Create texture 27
SDL_Texture* bullet;
Mix_Music *music;
Mix_Chunk *gomu;
//Create texture 3

//Texture Funcion
SDL_Texture* loadTexture(std::string path) { 

//Creating the texture
		SDL_Texture* ATexture=NULL;
		//Surface where we load it
		SDL_Surface* loadSurface = IMG_Load(path.c_str());
		ATexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		SDL_FreeSurface(loadSurface);
		return ATexture;
	}




int main(int argc, char*args[]) {

	int aim=0;

	//Inicializing SDL
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);//frequency(44100 o 22050), Uint format, channels, chunksize

	//Create Window
	window = SDL_CreateWindow("Square-Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);




	//Player Surface
	SDL_Rect* Player_Surface = new SDL_Rect;
	Player_Surface->x = 0;
	Player_Surface->y = 0;
	Player_Surface->w = 120;
	Player_Surface->h = 80;



	//Bullet Surface
	SDL_Rect* Bull_Surface[5];
	for (int c = 0; c < 5; c++)
	{
		Bull_Surface[c] = new SDL_Rect;
		Bull_Surface[c]->x;
		Bull_Surface[c]->y;
		Bull_Surface[c]->w=40;
		Bull_Surface[c]->h=40;
	}
	//Textures
	background = loadTexture("Background.png");
	character = loadTexture("luffy.png");
	bullet = loadTexture("arm.png");

	music = Mix_LoadMUS("music.ogg");
	gomu = Mix_LoadWAV("arm.wav");


	Mix_PlayMusic(music, 1);
	Mix_VolumeMusic(45);
	//Bucle
	// Inicialize the loop
	bool loop = true;
	bool moveup = false;
	bool movedown = false;
	bool moveright = false;
	bool moveleft = false;

	bool shooting = false;
	while (loop)
	{
		SDL_Event event; // Inputs
		if (SDL_PollEvent(&event) != 0)// When its 0 it means that there isnt an input, when that changes to a 1 means that there is an input
		{
			if (event.type == SDL_QUIT) {
				loop = false;
			}

			if (event.type == SDL_KEYDOWN) {   //Moviment i atac

				if (event.key.keysym.sym == SDLK_ESCAPE) {
					loop = false;
				}

				if (event.key.keysym.sym == SDLK_UP) {// Move up the red rec.
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
					shooting = true;

				}
			}
			if (event.type == SDL_KEYUP) {   //Moviment and atac
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
				if (event.key.keysym.sym == SDLK_SPACE) {// Move left the red rec.

					 shooting = false;
				}
			}

		}

		//Borders in the screen
		if (Player_Surface->x < 0) {
			Player_Surface->x = 0;
		}
		if (Player_Surface->x > SCREEN_WIDTH - Player_Surface->w) {
			Player_Surface->x = SCREEN_WIDTH - Player_Surface->w;
		}
		if (Player_Surface->y < 0) {
			Player_Surface->y = 0;
		}
		if (Player_Surface->y > SCREEN_HEIGHT - Player_Surface->h) {
			Player_Surface->y = SCREEN_HEIGHT - Player_Surface->h;
		}

		SDL_RenderCopy(renderer, background, 0, 0);
		SDL_RenderCopy(renderer, character, 0, Player_Surface);
		


		//Texture Bullet
		for (int c = 0; c < 5; c++) {
			SDL_RenderCopy(renderer, bullet, 0, Bull_Surface[c]);
			Bull_Surface[c]->x += 5;
		}

		//Shooting
		if (shooting) {
			Bull_Surface[aim]->x = (Player_Surface->x) + (Player_Surface->w);
			Bull_Surface[aim]->y = (Player_Surface->y) + ((Player_Surface->h) / 2 - Bull_Surface[1]->h);
			Mix_PlayChannel(-1, gomu, 0);
			aim++;
			if (aim == 5) {
				aim = 0;
			}
			shooting = false;
		}

		//Movement

		if (moveleft == true) {
			Player_Surface->x -= 15;
		}
		if (moveright == true) {
			Player_Surface->x += 15;
		}
		if (moveup == true) {
			Player_Surface->y -= 15;
		}
		if (movedown == true) {
			Player_Surface->y += 15;
		}
	
		SDL_RenderPresent(renderer);
		SDL_Delay(18);
	}
	Mix_FreeMusic(music);
	Mix_FreeChunk(gomu);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(character);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	
	IMG_Quit();
	SDL_Quit();
	return 0;
}