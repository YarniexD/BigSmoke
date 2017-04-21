#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
void DrawPic(SDL_Renderer* render,int w, int h,int x, int y, char str[255])
{
	SDL_Surface* image = IMG_Load(str);
	w = image->w;
	h = image->h;
	SDL_Texture* imagetexture = SDL_CreateTextureFromSurface(render, image);
	SDL_Rect target = { x,y,w,h };
	SDL_RenderCopy(render, imagetexture, NULL, &target);
	SDL_DestroyTexture(imagetexture);
	SDL_FreeSurface(image);
}
int control(bool* running, int x1, int x2, int y1, int y2, int* score, int* flag)
{
	SDL_Event ev;
	int x, y;
	while (SDL_PollEvent(&ev) != 0)
	{
		if (ev.type == SDL_QUIT)
		{
			*running = false;
			break;
			return 0;
		}
		else
		{
			if (ev.type == SDL_MOUSEMOTION)
				SDL_GetMouseState(&x, &y);
			else
			{
				if (ev.type == SDL_MOUSEBUTTONDOWN)
				{
					if (ev.button.button == SDL_BUTTON_LEFT)
					{
						if ((ev.button.x >= x1) && (ev.button.x <= x2) && (ev.button.y <= y1) && (ev.button.y <= y2))
						{
							*score += 5;
							*flag = 0;
						}
					}
				}
			}
		}
	}
}
int main(int argc, char** argv)
{	
	srand(time(NULL));
	SDL_Point pos[9];
	SDL_Point wndw;
	pos[1].x = pos[4].x = pos[7].x = 170 - 75;
	pos[1].y = pos[2].y= pos[3].y = 130-100;
	pos[2].x = pos[5].x = pos[8].x = 520-75;
	pos[4].y = pos[5].y= pos[6].y= 385-100;
	pos[3].x = pos[6].x = pos[9].x = 860-75;
	pos[7].y = pos[8].y = pos[9].y = 645-100;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("BigSmoke", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
	bool running = true;
	int hole;
	int flag = 1;
	while (running)
	{	
		int hole = rand() % 9 + 1;
		DrawPic(render,1024,768,0,0, "Background.png");
		DrawPic(render, 140, 200, pos[hole].x,pos[hole].y, "Bigsmoke.png");
		if (flag == 0)
			continue;
		SDL_RenderPresent(render);
		SDL_Delay(300);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
	system("pause");
	return 0;
}