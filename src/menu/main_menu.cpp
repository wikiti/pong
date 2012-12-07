#include "menu.h"
#include "menu_vars.h"
#include "../temporizador.h"

const int FRAMES_PER_SECOND = 60;

bool menu_cargar()
{
  img_fondo_menu = cargar_img("media/img/fondo_menu.png", false);
  ttf_consolas = TTF_OpenFont("media/ttf/consolab.ttf", 16);

  if(ttf_consolas == false)
	return false;

  return true;
}

void menu_limpiar()
{
  SDL_FreeSurface(img_fondo_menu);

  TTF_CloseFont(ttf_consolas);
}

int main_menu()
{
  if(!menu_cargar())
    return -1;

  color = SDL_MapRGB(pantalla->format, 255, 255, 255);

  CTemporizador fps;
  int frame = 0;

  CBoton* botones = new CBoton[4];
  botones[0] = CBoton(100, 200, 150, 25, "Un Jugador");
  botones[1] = CBoton(100, 230, 150, 25, "Multijugador");
  botones[2] = CBoton(100, 260, 150, 25, "Opciones");
  botones[3] = CBoton(100, 290, 150, 25, "Salir");

  CMenu menu(botones, 4);

  int caso = 0;
  while(caso == 0)
  {
	fps.empezar();
	while(SDL_PollEvent(&event))
	{
	  caso = menu.eventuar();
      if(event.type == SDL_QUIT)
      {
        caso = -1;
      }
	}

	aplicar_superficie(0, 0, img_fondo_menu, pantalla);
	menu.mostrar();

    if(SDL_Flip(pantalla) == -1)
      return 0;

    frame++;
    if((fps.getTicks() < (1000 / FRAMES_PER_SECOND)))
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.getTicks());
  }

  menu_limpiar();

  return caso;
}