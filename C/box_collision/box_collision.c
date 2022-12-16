
#include "box_collision.h"

int main(int argc, char* args[])
{
	// Variables
	Demo demo;
	int run;
	int loop = 1;

	CollisionBox box_a;
	box_a.rect.x = 0;
	box_a.rect.y = 0;
	box_a.rect.w = BOX_WIDTH;
	box_a.rect.h = BOX_HEIGHT;

	box_a.color.r = 0xFF;
	box_a.color.a = 0xAA;

	CollisionBox box_b;
	box_b.rect.x = WIDTH / 2;
	box_b.rect.y = HEIGHT / 2;
	box_b.rect.w = BOX_WIDTH;
	box_b.rect.h = BOX_HEIGHT;

	box_b.color.g = 0xFF;
	box_b.color.a = 0xAA;

	run = StartSDL(&demo, NAME, WIDTH, HEIGHT, SDL_FLAGS, WINDOW_FLAGS, RENDER_FLAGS);
	if (run)
	{
		// Activa Alpha Blending
		SDL_SetRenderDrawBlendMode(demo.renderer, SDL_BLENDMODE_BLEND);

		// Bucle Principal
		while (loop)
		{
			// Eventos
			while (SDL_PollEvent(&demo.event))
			{
				if (demo.event.type == SDL_QUIT)
				{
					loop = 0;
				}

				if (demo.event.type == SDL_KEYDOWN)
				{
					SDL_Keycode key = demo.event.key.keysym.sym;
					// Movimiento Box A
					if (key == SDLK_UP) box_a.rect.y -= SPEED;
					if (key == SDLK_DOWN) box_a.rect.y += SPEED;
					if (key == SDLK_LEFT) box_a.rect.x -= SPEED;
					if (key == SDLK_RIGHT) box_a.rect.x += SPEED;
					// Movimiento Box B
					if (key == SDLK_w) box_b.rect.y -= SPEED;
					if (key == SDLK_s) box_b.rect.y += SPEED;
					if (key == SDLK_a) box_b.rect.x -= SPEED;
					if (key == SDLK_d) box_b.rect.x += SPEED;
				}
			}

			// Revisa Colision
			if (box_a.rect.x <= (box_b.rect.x + box_b.rect.w) &&
				(box_a.rect.x + box_a.rect.w) >= box_b.rect.x &&
				box_a.rect.y <= (box_b.rect.y + box_b.rect.h) &&
				(box_a.rect.y + box_a.rect.h) >= box_b.rect.y)
			{
				box_a.color.b = 0xFF;
				box_b.color.b = 0xFF;
				printf("Colision!\n");
			}
			else
			{
				box_a.color.b = 0;
				box_b.color.b = 0;
			}

			// Limpia Pantalla
			SDL_SetRenderDrawColor(demo.renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(demo.renderer);

			// Box 1
			RenderCollisionBox(&demo, box_a);
			// Box 2
			RenderCollisionBox(&demo, box_b);

			// Renderiza
			SDL_RenderPresent(demo.renderer);
		}
	}

	// Termina SDL
	CloseSDL(&demo);

	return 0;
}


void RenderCollisionBox(Demo* demo, CollisionBox box)
{
	SDL_SetRenderDrawColor(demo->renderer, box.color.r, box.color.g, box.color.b, box.color.a);
	SDL_RenderFillRect(demo->renderer, &box.rect);

	SDL_Rect ref = box.rect;
	ref.x = 0;
	ref.w = 8;
	SDL_RenderFillRect(demo->renderer, &ref);

	ref = box.rect;
	ref.y = 0;
	ref.h = 8;
	SDL_RenderFillRect(demo->renderer, &ref);
}