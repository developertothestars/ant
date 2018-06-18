/* langton's ant */
/* set up sdl2 with */
/* $ sudo apt-get install libsdl2-2.0 libsdl2-dev */
/* compile with */
/* $ gcc ant.c -lSDL2 */

#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define CELL_WIDTH 10

#define GRID_X (SCREEN_WIDTH / CELL_WIDTH)
#define GRID_Y (SCREEN_HEIGHT / CELL_WIDTH)

Uint32 COLOR_BLACK;
Uint32 COLOR_DARK_BLUE;
Uint32 COLOR_DARK_PURPLE;
Uint32 COLOR_DARK_GREEN;
Uint32 COLOR_BROWN;
Uint32 COLOR_DARK_GRAY;
Uint32 COLOR_LIGHT_GRAY;
Uint32 COLOR_WHITE;
Uint32 COLOR_RED;
Uint32 COLOR_ORANGE;
Uint32 COLOR_YELLOW;
Uint32 COLOR_GREEN;
Uint32 COLOR_BLUE;
Uint32 COLOR_INDIGO;
Uint32 COLOR_PINK;
Uint32 COLOR_PEACH;
SDL_Rect a1;
SDL_Rect r1;
char grid[GRID_X][GRID_Y];

void setup_colors(const SDL_PixelFormat* format)
{
  COLOR_BLACK       = SDL_MapRGB(format,   0,   0,   0);
  COLOR_DARK_BLUE   = SDL_MapRGB(format,  29,  43,  83);
  COLOR_DARK_PURPLE = SDL_MapRGB(format, 126,  37,  83);
  COLOR_DARK_GREEN  = SDL_MapRGB(format,   0, 135,  81);
  COLOR_BROWN       = SDL_MapRGB(format, 171,  82,  54);
  COLOR_DARK_GRAY   = SDL_MapRGB(format,  95,  87,  79);
  COLOR_LIGHT_GRAY  = SDL_MapRGB(format, 194, 195, 199);
  COLOR_WHITE       = SDL_MapRGB(format, 255, 195, 199);
  COLOR_RED         = SDL_MapRGB(format, 255,   0,  77);
  COLOR_ORANGE      = SDL_MapRGB(format, 255, 163,   0);
  COLOR_YELLOW      = SDL_MapRGB(format, 255, 236,  39);
  COLOR_GREEN       = SDL_MapRGB(format,   0, 228,  54);
  COLOR_BLUE        = SDL_MapRGB(format,  41, 173, 255);
  COLOR_INDIGO      = SDL_MapRGB(format, 131, 118, 156);
  COLOR_PINK        = SDL_MapRGB(format, 255, 119, 168);
  COLOR_PEACH       = SDL_MapRGB(format, 255, 204, 170);
}

void setup_grid(SDL_Surface *surface)
{
  int i;
  int j;
  Uint32 color;

  for (i = 0; i < GRID_X; i++)
    for (j = 0; j < GRID_Y; j++)
    {
      grid[i][j] = 0;
//    grid[i][j] = (i + j) % 2;
//    color = grid[i][j] ? COLOR_BLUE : COLOR_YELLOW;
//    r1.x = i * CELL_WIDTH;
//    r1.y = j * CELL_WIDTH;
//    SDL_FillRect(surface, &r1, color);
    }
  r1.w = CELL_WIDTH;
  r1.h = CELL_WIDTH;
  a1.x = GRID_X / 2;
  a1.y = GRID_Y / 2;
  a1.w = 0;
}

void update_ant(SDL_Surface *surface)
{
  Uint32 color;

  if ((a1.x >= 0) && (a1.x < GRID_X) &&
      (a1.y >= 0) && (a1.y < GRID_Y))
  {
    grid[a1.x][a1.y] = 1 - grid[a1.x][a1.y];
    if (grid[a1.x][a1.y])
    {
      color = COLOR_BLUE;
      a1.w += 1;
    }
    else
    {
      color = COLOR_YELLOW;
      a1.w -= 1;
    }
    r1.x = a1.x * CELL_WIDTH;
    r1.y = a1.y * CELL_WIDTH;
    SDL_FillRect(surface, &r1, color);
    switch (a1.w)
    {
    case -1:
    case  3:
      a1.w = 3;
      a1.x -= 1;
      break;
    case  0:
    case  4:
      a1.w = 0;
      a1.y -= 1;
      break;
    case  1:
      a1.x += 1;
      break;
    case  2:
      a1.y += 1;
      break; 
    }
  }
  else
  {
    setup_grid(surface);
    SDL_FillRect(surface, NULL, COLOR_LIGHT_GRAY);
  }
}

int main(int argc, char* args[])
{
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow(
			    "langton's ant",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );
  if (window == NULL)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);
  setup_colors(screenSurface->format);
  setup_grid(screenSurface);

  while (1)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        break;
      }
    }
    update_ant(screenSurface);
    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
