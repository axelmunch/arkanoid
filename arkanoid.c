#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "delta_time.h"

//struct { double x; double y; } ball_speed;
struct { double x; double y;  double vx; double vy;} ball;

Uint64 prev, now; // timers
double delta_t;  // durée frame en ms
int x_vault;

SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;

SDL_Rect srcBg = { 0,128, 96,128 }; // x,y, w,h (0,0) en haut a gauche
SDL_Rect srcBall = { 0,96,24,24 };
SDL_Rect scrVaiss = { 128,0,128,32 };


void init()
{
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
	plancheSprites = SDL_LoadBMP("./sprites.bmp");
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

	ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 1.0;
	ball.vy = 1.4;

	now = SDL_GetPerformanceCounter();
}


// fonction qui met à jour la surface de la fenetre "win_surf"
void draw()
{
	// remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
	for (int j = 0; j < win_surf->h; j+=128)
		for (int i = 0; i < win_surf->w; i += 96)
		{
			dest.x = i;
			dest.y = j;
			SDL_BlitSurface(plancheSprites, &srcBg, win_surf, &dest);
		}

	
	// affiche balle
	SDL_Rect dstBall = {ball.x, ball.y, 0, 0};
	SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

	// deplacement
	ball.x += ball.vx * get_delta_time_target();
	ball.y += ball.vy * get_delta_time_target();

	// collision bord
	if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
		ball.vx *= -1;
	if ((ball.y < 1) || (ball.y > (win_surf->h - 25)))
		ball.vy *= -1;

	// touche bas -> rouge
	if (ball.y >(win_surf->h - 25))
		srcBall.y = 64;
	// touche bas -> vert
	if (ball.y < 1)
		srcBall.y = 96;

	// vaisseau
	dest.x = x_vault;
	dest.y = win_surf->h - 32;
	SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);
}



int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    {
		return 1;
    }

	init();
    init_delta_time();
    
	bool quit = false;
	while (!quit)
    {
        update_delta_time();
        printf("FPS: %f\n", get_current_fps());

		SDL_PumpEvents();
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT])
            x_vault -= 10 * get_delta_time_target();
        if (keys[SDL_SCANCODE_RIGHT])
            x_vault += 10 * get_delta_time_target();

		draw();
		SDL_UpdateWindowSurface(pWindow);
		
        SDL_Delay((Uint32)GAME_FPS_MS);
	}

    SDL_Quit();
    return 0;
}
