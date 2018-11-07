#include<iostream>
#include<string>
#include<conio.h>
using namespace std;

class boton {
      public:
             ALLEGRO_BITMAP *image10 = NULL;
              ALLEGRO_BITMAP *image11 = NULL;
               ALLEGRO_BITMAP *image12 = NULL;
               
ALLEGRO_BITMAP carga_boton(){
               	
               	image10 = al_load_bitmap("boton1.bmp");
               	al_draw_bitmap(image10, 2,2, 0);
              al_flip_display();
    		al_clear_to_color(al_map_rgb(0,0,0));
        }
        };
