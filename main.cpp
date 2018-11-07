#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>				//Our primitive header file
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <cmath>
#include <time.h>
#include "objects.h"
#include<iostream>
using namespace std;
//#include <allegro5/allegro_video.h>
//#include "objetom.h"

//objetos
Base mouse;
Base escudo;
Bomba b;
Jugador nave;
Enemigo enemigo[NUM_ENEM];
Proyectil bala[NUM_BALAS];
Proyectil sbala[NUM_BALAS2];
Especial esp;






void iniciarPartida();

int main(void)




{ 
    int asd=0;
    bool redraw = true;
	bool pausa=false;
	bool colision=false;
	bool disparar=false;int disp = 0;
	bool bomba=false;
	
    int bombt=0;
    
    srand(time(0));
    
    
    int p=0;
    int nivel=0;
	int width = 660;
	int height = 440;
//    char p=600;
    bool salida=false;
    bool salida2=false;
	bool done = false;
	bool sonido=true;
	bool salida3;
//	bool draw = true;                       //DESCOMENTAR
	int pos_x = width / 2;
	int pos_y = height / 2;
	ALLEGRO_BITMAP *bufer = NULL;
	ALLEGRO_BITMAP *image = NULL;
	ALLEGRO_BITMAP *image2 = NULL;
    ALLEGRO_BITMAP *image3 = NULL;
	ALLEGRO_BITMAP *image4 = NULL;
	ALLEGRO_BITMAP *image5 = NULL;
	ALLEGRO_BITMAP *image6 = NULL;
	ALLEGRO_BITMAP *image7 = NULL;
	ALLEGRO_BITMAP *image8 = NULL;
	ALLEGRO_BITMAP *image9 = NULL;
	ALLEGRO_BITMAP *image10 = NULL;
	ALLEGRO_BITMAP *image11 = NULL;
	ALLEGRO_BITMAP *image12 = NULL;
	ALLEGRO_BITMAP *image13 = NULL;
	ALLEGRO_BITMAP *image14 = NULL;
    ALLEGRO_BITMAP *image15 = NULL;
	ALLEGRO_BITMAP *image16 = NULL;
		ALLEGRO_BITMAP *image17 = NULL;
//	ALLEGRO_FILE *puntuacion=NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_SAMPLE *song=NULL;
	ALLEGRO_SAMPLE *Hover=NULL;  //SONIDO CONTROLADO POR TIEMPO 
	ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL; //SONIDO DE TRANSFONDO CONTINUO
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_USTR *uno = NULL;  
	ALLEGRO_FILE *puntuacion = al_fopen("puntuacione.txt", "rb");
	ALLEGRO_FILE *puntuaciones = al_fopen("puntuaciones.txt", "w");
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_MOUSE_CURSOR *cursor = NULL;
    ALLEGRO_BITMAP *imagen[8] = {NULL};
    ALLEGRO_BITMAP *especial[4] = {NULL};
    ALLEGRO_BITMAP *fondo = NULL;
    
    
//    	ALLEGRO_FILE *video=al_open_video("video.flc");
//    boton botones;
    
	if(!al_init())										//initialize Allegro
		return -1;
	
    display = al_create_display(width, height);			//create our display object
	if(!display)										//test display object
		return -1;
		
	
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_set_mouse_cursor(display, cursor);
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();	 
    al_init_font_addon();
	al_init_ttf_addon();

   //puntuacion=    //PARA ABRIR UN ARCHIVO DE TEXTO
    uno=al_fget_ustr(puntuacion); //PARA OBTENER UNA CADENA TIPO CHAR 
    
    //  al_fputs(puntuacion,uno);
   //  int al_fputs(ALLEGRO_FILE *f, char const *p)
//      al_fwrite(puntuacion,1,10, p);
	image = al_load_bitmap("fondo9.bmp");
     image2 = al_load_bitmap("fondo91.bmp");
     image3 = al_load_bitmap("fondo92.bmp");
     image4 = al_load_bitmap("fondo93.bmp");
     image5= al_load_bitmap("fondo3.bmp");
     image6= al_load_bitmap("regreso1.bmp");
     image7= al_load_bitmap("regreso2.bmp");
     image8= al_load_bitmap("opciones2.bmp");
     image9= al_load_bitmap("opciones3.bmp");
     image10= al_load_bitmap("opciones4.bmp");
     image11= al_load_bitmap("opciones5.bmp");
     image12= al_load_bitmap("escenarios1.bmp");
     image13= al_load_bitmap("escenarios2.bmp");
     image14= al_load_bitmap("escenarios3.bmp");
     image15= al_load_bitmap("escenarios4.bmp");
     image16= al_load_bitmap("escenarios5.bmp");
         image17= al_load_bitmap("instrucciones.bmp");
     
     
     
     
     //Cargar sprites
	imagen[JUGADOR] = al_load_bitmap("Sprites/nave.png");
    imagen[ENEM1] = al_load_bitmap("Sprites/enemigo1.png");
    imagen[ENEM2] = al_load_bitmap("Sprites/enemigo2.png");
    imagen[ENEM3] = al_load_bitmap("Sprites/enemigo3.png");
    imagen[JEFE] = al_load_bitmap("Sprites/jefe.png");
    imagen[BALA] = al_load_bitmap("Sprites/bala.png");
    imagen[BALA2] = al_load_bitmap("Sprites/sbala.png");
    imagen[ESCUDO] = al_load_bitmap("Sprites/shield.png");
    especial[ESC]  = al_load_bitmap("Sprites/esp1.png");
    especial[SBALA]  = al_load_bitmap("Sprites/esp2.png");
    especial[VIDA]  = al_load_bitmap("Sprites/esp3.png");
    especial[BOMBA]  = al_load_bitmap("Sprites/esp4.png");
    
    //Cargar fondo
    fondo = al_load_bitmap("Fondos/fondo6.png");
    
//al_show_mouse_cursor(display);
//mouse.establecerImagen(imagen[BALA]);
    
    nave.establecerImagen(imagen[JUGADOR]);
    nave.establecerBound((nave.imageWidth/2)-5, (nave.imageHeight/2)-5);
    escudo.establecerImagen(imagen[ESCUDO]);
    b.establecerImagen(imagen[JUGADOR], -5, -5);
   	
    for (int i = 0; i < NUM_BALAS; i++)
   	{
        bala[i].establecerImagen(imagen[BALA]);
        bala[i].establecerBound(bala[i].imageWidth, bala[i].imageHeight);
        bala[i].velocidad=5;
        bala[i].vivo=false;
    }
    for (int i = 0; i < NUM_BALAS2; i++)
   	{
        sbala[i].establecerImagen(imagen[BALA2]);
        sbala[i].establecerBound(sbala[i].imageWidth, sbala[i].imageHeight);
        sbala[i].velocidad=8;
        sbala[i].vivo=false;
    }
     
     
   // timer = al_create_timer(1.0 / FPS);
	srand(time(NULL)); 
     
     
     
//     bufer=al_create_sub_bitmap(screen,30,70,320,240)
    // puntuacion=al_fread32be("puntuacion.txt");
     font18= al_load_font("pirulen.ttf", 20, 0);
     al_reserve_samples(10);
     song = al_load_sample("Halo .wav");
     Hover=al_load_sample("Hover.wav");
     songInstance=al_create_sample_instance(song);
     al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_LOOP);
     al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());   
   	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
//	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	

//	al_hide_mouse_cursor(display);        //DESCOMENTAR
	  //cursor = al_load_bitmap("cursor.bmp",NULL); 
nojugar:
        //  puntuaciones = al_fopen("puntuaciones.txt", "w");    
        if(asd != 0)
                {
                     cout << 5;
                   al_destroy_timer(timer);
                   asd=0;
  
              }
                
                
    	//al_fwrite(puntuacion, "2", strlen("2"));
             //sonido=false;       
    		ALLEGRO_EVENT ev;
    		al_wait_for_event(event_queue, &ev);
    //      al_play_memory_fli(video,bufer,0,NULL);
    		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
    		{
    			done = true;
    		}
    		
    			 if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    		{
    			pos_x = ev.mouse.x;
    			pos_y = ev.mouse.y;
    		}
    		//if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    		//{if(ev.mouse.button & 1)
    		//clic=true;
            //}
    		
    		if(sonido){al_play_sample_instance(songInstance);}
           
         if ( ev.mouse.x < 640 && ev.mouse.x > 480 &&    //ESTAS SOBRE INICIAR PARTIDA
                  ev.mouse.y > 90 && ev.mouse.y < 121 ) 
             {  
                
                  //al_rest(.00009);
                  al_draw_bitmap(image2, -1, 0, 0);
                  al_flip_display();
        		al_clear_to_color(al_map_rgb(0,0,0));
    
                if ( ev.mouse.button & 1 )  //PUCHASTE EL BOTON DE INICIAR PARTIDA
                {
                      al_draw_bitmap(image17, 0,0, 0);
                                             //   al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                     
                     al_rest(4.0);
                     
                                                   al_draw_bitmap(image12, 0,0, 0);
                                             //   al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
        	                                  	
      //entraste al menu de escenarios
        	                                  	al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                         salida3=false;
                          while ( !salida3 )
    	                                   {
                                                 
                                            	ALLEGRO_EVENT ev;
    	                                       	al_wait_for_event(event_queue, &ev);
    		                                   	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
    	                                                 	{
                                                              done=true;
    		                                                	salida3 = true;
                                                      		}
                                            if ( ev.mouse.x > 497 && ev.mouse.x < 642 && //boton regresar menu de escenarios
                                                 ev.mouse.y > 380 && ev.mouse.y < 426) 
                                                 {
                                                 al_draw_bitmap(image12, 1, 0, 0);
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                                                            if ( ev.mouse.button & 1 )
                                                                  {
                                                                 al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                                                              //     done = true;
                                                                   salida3=true;
                                                                   
                                                                  // al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                                                                    }
                                                 }
                                                 
                                                else if ( ev.mouse.x > 20 && ev.mouse.x < 178 && //estas sobre facil
                                                 ev.mouse.y > 53 && ev.mouse.y < 206) 
                                                 {
                                                 al_draw_bitmap(image14, 1, 0, 0);
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                                                            if ( ev.mouse.button & 1 )
                                                                  {
                                                                   //salida3 = true;
                                                                   al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                                                                   nivel=1;
                                                                   fondo=al_load_bitmap("nivel1.bmp");
                                                                   
                                                                  //al_destroy_display(display);
                                                                  // display=al_create_display(WIDTH, HEIGHT);
                                                                   //al_fclose(puntuaciones);
                                                                  iniciarPartida();
                                                                  timer = al_create_timer(1.0 / FPS);
                                                                  al_start_timer(timer);
                                                                  al_register_event_source(event_queue, al_get_timer_event_source(timer));
                                                                  asd=1;
                                                                  break;
                                                                    }
                                                 }
             
             
                                                  else if ( ev.mouse.x > 272 && ev.mouse.x < 402 && //estas sobre medio
                                                 ev.mouse.y > 160 && ev.mouse.y < 280) 
                                                 {
                                                 al_draw_bitmap(image15, 1, 0, 0);
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                                                            if ( ev.mouse.button & 1 )
                                                                  {
                                                                //   salida3 = true;
                                                                
                                                                   al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                                                                   nivel=3;
                                                                   fondo=al_load_bitmap("nivel2.bmp");
                                                                   //  al_destroy_display(display);
                                                                   //display=al_create_display(WIDTH, HEIGHT);
                                                                    
                                                                   iniciarPartida();
                                                                   timer = al_create_timer(1.0 / FPS);
                                                                  al_start_timer(timer);
                                                                  al_register_event_source(event_queue, al_get_timer_event_source(timer));
                                                                   asd=1;
                                                                   break;
                                                            
                                                                   //LLAMARA A SUBRUTINA DE INICIO DE PARTIDO 
                                                                    }
                                                 }
             
             
             
                                                           else if (ev.mouse.y > 233 && ev.mouse.y < 355 && ev.mouse.x > 495 && ev.mouse.x < 625 ) //estas sobre dificil
                                                 
                                                 {
                                                 al_draw_bitmap(image16, 1, 0, 0);
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
        	                                  	
                                                            if ( ev.mouse.button & 1  )
                                                                  {
                                                                  // salida3 = true;
                                                                   al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);  
                                                                   nivel=2;
                                                                   
                                                                   iniciarPartida();
                                                                   fondo=al_load_bitmap("nivel3.bmp");
                                                                   //display=al_create_display(WIDTH, HEIGHT);
                                                                   timer = al_create_timer(1.0 / FPS);
                                                                  al_start_timer(timer);
                                                                  al_register_event_source(event_queue, al_get_timer_event_source(timer));
                                                                  asd=1;
                                                                   break;
                                                                   //LLAMAR A SUBRUTINA DE INICIO DE PARTIDA
                                                                    }
                                                 }
             
             
             
                                            else{
                                                  al_draw_bitmap(image13, 0, 0, 0);
                                                  al_flip_display();
                                                  al_clear_to_color(al_map_rgb(0,0,0));
                                                                  }
                                                   
                                                   }
                                                   }
                                            
     	
                    	
        	                                  	
                  	
        	                                  	
                    //  done = true;
                
             
             }
             else if ( ev.mouse.x < 630 && ev.mouse.x > 495 &&
                  ev.mouse.y > 200 && ev.mouse.y < 231)  //estas sobre opciones
             {  
                  al_draw_bitmap(image3, 0, 0, 0);
                  al_flip_display();
        		al_clear_to_color(al_map_rgb(0,0,0));
                if ( ev.mouse.button & 1 ) //apretaste opciones
                {
                  al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                     
                     salida2=false;
                          while ( !salida2 )
    	                                   { 
                                            	ALLEGRO_EVENT ev;
    	                                      	al_wait_for_event(event_queue, &ev);
    		                                   	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
    	                                                 	{
                                                                                           
                                                                                           
                                                              done=true;
    		                                                	salida2 = true;
                                                       		}
                                                       		
                                           if(sonido){           	
                                          if ( ev.mouse.x > 220 && ev.mouse.x < 305 &&
                                                 ev.mouse.y > 350 && ev.mouse.y < 400) 
                                                 {
                                                al_draw_bitmap(image10, 0,0, 0);
                                                al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
        	                                  	al_fwrite(puntuaciones,"800",strlen("800"));
        	                                  	
        	                                //  	al_fclose(puntuaciones);
                                                            if ( ev.mouse.button & 1 )
                                                            
                                                                  {       
                                                                      al_stop_sample_instance(songInstance) ;   
                                                                     sonido=false;       
                                                                   salida2 = true;
                                                                    }
                                                          // sonido=true  ;    //  ;
                                                
                                                 }
                                            
                                            else{
                                                 
                                                 al_draw_bitmap(image8, 0, 0, 0);
                                                // al_ustr_rtrim_ws(uno);
                                                // al_draw_text(font18,al_map_rgb(30, 255, 255) , 50, 260, 0, uno);
                  
                                                al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                // al_draw_text(font18,al_map_rgb(30, 255, 255) , 50, 260, 0, al_cstr(uno));
                                                  al_flip_display();
                                                  al_clear_to_color(al_map_rgb(0,0,0));
                                                                  }
                                                                  }
                                                                  else{
                                                                                                             if ( ev.mouse.x > 220 && ev.mouse.x < 305 &&
                                                 ev.mouse.y > 350 && ev.mouse.y < 400) 
                                                 {
                                                al_draw_bitmap(image9, 0,0, 0);
                                                al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                                                            if ( ev.mouse.button & 1 )
                                                            
                                                                  {       
                                                                      al_stop_sample_instance(songInstance) ;   
                                                                     sonido=true;       
                                                                   salida2 = true;
                                                                    }
                                                          // sonido=true  ;    //  ;
                                                
                                                 }
                                            
                                            else{
                                                 
                                                 al_draw_bitmap(image11, 0, 0, 0);
                                                // al_ustr_rtrim_ws(uno);
                                                // al_draw_text(font18,al_map_rgb(30, 255, 255) , 50, 260, 0, uno);
                                               
                                               
                                                al_draw_textf(font18, al_map_rgb(30, 255, 255), width / 2, height / 2, ALLEGRO_ALIGN_CENTRE, "Puntuacion mas alta: %s", al_cstr(uno));
                                                // al_draw_text(font18,al_map_rgb(30, 255, 255) , 50, 260, 0, al_cstr(uno));
                                                  al_flip_display();
                                                  al_clear_to_color(al_map_rgb(0,0,0));
                                                                  }
                                                        }
                 
                                                   }
                    //  done = true;
                }
             }
            
            else if ( ev.mouse.x < 630 && ev.mouse.x > 495 &&
                  ev.mouse.y > 310 && ev.mouse.y < 345)          //Estas sobre credios
             {  
                  al_draw_bitmap(image4, 0, 0, 0);
                  al_flip_display();
        		al_clear_to_color(al_map_rgb(0,0,0));
    
                if ( ev.mouse.button & 1 )                        //apretaste creditos     
                        {al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
    salida=false;
                          while ( !salida )
    	                                   {
                                            	ALLEGRO_EVENT ev;
    	                                       	al_wait_for_event(event_queue, &ev);
    		                                   	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
    	                                                 	{
                                                              done=true;
    		                                                	salida = true;
                                                      		}
                                            if ( ev.mouse.x > 375 && ev.mouse.x < 571 &&
                                                 ev.mouse.y > 370 && ev.mouse.y < 435) 
                                                 {
                                                 al_draw_bitmap(image6, -4, 1, 0);
                                                 al_flip_display();
        	                                  	al_clear_to_color(al_map_rgb(0,0,0));
                                                            if ( ev.mouse.button & 1 )
                                                                  {
                                                                   salida = true;
                                                                   al_play_sample(Hover,1,0,1, ALLEGRO_PLAYMODE_ONCE,0);
                                                                    }
                                                 }
             
                                            else{
                                                  al_draw_bitmap(image7, 0, 0, 0);
                                                  al_flip_display();
                                                  al_clear_to_color(al_map_rgb(0,0,0));
                                                                  }
                                                   }
                                       }
                            }  
                     else{
                     al_draw_bitmap(image, 0, 0, 0);
                     al_flip_display();
        	      	al_clear_to_color(al_map_rgb(0,0,0));}  		
               // blit(fondo, buffer, 0, 0, 0, 0, 640, 480);
	while(!done)
	{
         
        if(!jugar)
        {
                goto nojugar;
             }
    else
    {
         // al_stop_sample_instance(songInstance) ;  
                       ALLEGRO_EVENT ev;
                       //if(asd == 0)
//                       {//
//                         cout << 1;
//                         timer = al_create_timer(1.0 / FPS);
//                            al_start_timer(timer);   
                        //   asd =1;
                       //}
    		al_wait_for_event(event_queue, &ev);
    		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    		{
    			done = true;
    		}
    		else if(ev.type == ALLEGRO_EVENT_TIMER)
    		{
                redraw = true;
    			nave.mover(keys);
    			
                if(!isGameOver && !pause)
    	        {
                    //Aparecer enemigos
                    int n = (jefe)? 300 : 100;
                    if(!bomba && round(rand()%(n/nivel))==1)
                    {
                            for(int i=0; i < NUM_ENEM; i++)
                            {
                                    if (!enemigo[i].vivo)
                                    {
                                        int x, y;
                                        int id, v, vidas; 
                        		        bool o = (!jefe && int(round(rand()%25)) == 1)? true : false;
                                        int n = (o)? 3: int(round(rand()%3));
                                        switch (n)//Iniciar enemigos
                                        {
                                               case 0: //Enemigo 1
                                                    id = ENEM1;
                                                    v=2+int(rand()%3);
                                                    vidas=nivel*2;
                                                    enemigo[i].crear(id, imagen[id], v, 5, -10, vidas);
                                                    do 
                                                    {
                                                       x = rand()%WIDTH;
                                                       y = rand()%HEIGHT;                                         
                                                    } while(enemigo[i].establecerCoordenadas(x, y, nave));
                                                    break;
                                               case 1:
                                                    id = ENEM2;
                                                    v = 1 + int(rand()%2);
                                                    vidas = nivel * 4;
                                                    enemigo[i].crear(id, imagen[id], v, -5, -5, vidas);
                                                    do 
                                                    {
                                                        x = rand()%WIDTH;
                                                        y = rand()%HEIGHT;
                                                    } while(enemigo[i].establecerCoordenadas(x, y, nave));
                                                    break;
                                               case 2:
                                                    id = ENEM3;
                                                    v = 6 + int(rand()%4);
                                                    vidas = nivel*1;
                                                    enemigo[i].crear(id, imagen[id], v, -10, -10, vidas);
                                                    do
                                                    {
                                                        int l = int(round(rand()%4));//Iniciar en un extremo
                                                        switch (l)
                                                        {
                                                               case 0:
                                                                    x=0;
                                                                    y=nave.get_y();
                                                                    enemigo[i].Base::establecerDireccion(WIDTH, pos_y);
                                                                    break;
                                                               case 1:
                                                                    x=nave.get_x();
                                                                    y=0;
                                                                    enemigo[i].Base::establecerDireccion(pos_x, HEIGHT);
                                                                    break;
                                                               case 2:
                                                                    x = WIDTH;
                                                                    y = nave.get_y();
                                                                    enemigo[i].Base::establecerDireccion(0, pos_y);
                                                                    break;
                                                               case 3:
                                                                    x = nave.get_x();
                                                                    y = HEIGHT;
                                                                    enemigo[i].Base::establecerDireccion(pos_x, 0);
                                                                    break;
                                                        }
                                                    }while(enemigo[i].establecerCoordenadas(x, y, nave));            
                                                    break;
                                               case 3:
                                                    jefe = true;
                                                    id = JEFE;
                                                    v = 1; 
                                                    vidas = nivel * 10;
                                                    enemigo[i].crear(id, imagen[id], v, -25, -25, vidas);
                                                    do 
                                                    {
                                                       x = rand()%WIDTH;
                                                       y = rand()%HEIGHT;                                         
                                                    } while(enemigo[i].establecerCoordenadas(x, y, nave));
                                                    break;
                                        }
                                        break;
                                    }
                            }
                    }
                    
                    //Disparar     
                    if(disparar)
                    {
                                if(disp == 0)
                                {
                                        disp=5;
                                        if (nave.sbala == 0)
                                        {
                                            for(int i=0; i < NUM_BALAS; i++)
                                            {
                                                    if (!bala[i].vivo)
                                                    {
                                                        bala[i].vivo=true;
                                                        bala[i].vidas=1;
                                                        bala[i].establecerCoordenadas(nave.get_x(), nave.get_y());
                                                        bala[i].establecerDireccion(pos_x, pos_y);
                                                        
                                                        break;
                                                    }
                                            }
                                        }
                                        else
                                        {
                                            for(int i=0; i < NUM_BALAS2; i++)
                                            {
                                                    if (!sbala[i].vivo)
                                                    {
                                                        sbala[i].vivo=true;
                                                        sbala[i].vidas=10;
                                                        sbala[i].establecerCoordenadas(nave.get_x(), nave.get_y());
                                                        sbala[i].establecerDireccion(pos_x, pos_y);
                                                        
                                                        nave.sbala--;
                                                        break;
                                                    }
                                            }
                                        }
                                        
                                }
                                else
                                    disp--;
                    }
                    //Bomba
                    if(bomba)
                    {
                             if(nave.bombas > 0 && bombt == -1)
                             {
                                            b.establecerCoordenadas(0,0);
                                            bombt=2*FPS;
                                            for(int i=0; i < NUM_BALAS; i++)
                                            {
                                                    bala[i].vivo=false;
                                            }
                                            nave.bombas--;
                             }
                             if(bombt == 0)
                             {
                                      bombt--;
                                      bomba=false;
                             }
                    }
                                                    
                }
    		}
    		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
    		{
    			switch(ev.keyboard.keycode)
    			{
    				case ALLEGRO_KEY_ESCAPE:
    					done = true;
    					break;
    				case ALLEGRO_KEY_UP:
    					keys[UP] = true;
    					break;
    				case ALLEGRO_KEY_DOWN:
    					keys[DOWN] = true;
    					break;
    				case ALLEGRO_KEY_RIGHT:
    					keys[RIGHT] = true;
    					break;
    				case ALLEGRO_KEY_LEFT:
    					keys[LEFT] = true;
    					break;
    				case ALLEGRO_KEY_ENTER://Jugar otra vez
                         if(isGameOver)
                         {
                                       //isGameOver=false;
                                       
                                       jugar=false;
                                       
                         }
                         break;
                    case ALLEGRO_KEY_SPACE:
                         pause=!pause;
                         break;
    			}
    		}
    		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    		{
    			switch(ev.keyboard.keycode)
    			{
    				case ALLEGRO_KEY_UP:
    					keys[UP] = false;
    					break;
    				case ALLEGRO_KEY_DOWN:
    					keys[DOWN] = false;
    					break;
    				case ALLEGRO_KEY_RIGHT:
    					keys[RIGHT] = false;
    					break;
    				case ALLEGRO_KEY_LEFT:
    					keys[LEFT] = false;
    					break;
    			}
    		}
    	    else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
    		{
    			pos_x = ev.mouse.x;
    			pos_y = ev.mouse.y;
    		}
    		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
           {
                if(ev.mouse.button & 1)
                    disparar = true;
                //if(ev.mouse.button & 2){}
           }
           else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
           {
                if(ev.mouse.button & 1)
                    disparar = false;
                if(ev.mouse.button & 2)
                    bomba=true;
           }
                        
            
            
            
    	    if(redraw && al_is_event_queue_empty(event_queue))
    		{
    			redraw = false;
    			
    			if(!isGameOver && !pause)
    			{
                    al_draw_bitmap(fondo, 0, 0, 0);//Dibujar fondo           
                    al_draw_textf(font18, al_map_rgb(0, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Puntuacion: %i",  nave.puntos);
                    al_draw_textf(font18, al_map_rgb(0, 255, 255), 10, 25, ALLEGRO_ALIGN_LEFT, "Vidas: %i", nave.vidas);
                    al_draw_textf(font18, al_map_rgb(0, 255, 255), 10, 40, ALLEGRO_ALIGN_LEFT, "Bombas: %i", nave.bombas);
                    al_draw_textf(font18, al_map_rgb(0, 255, 255), 10, 55, ALLEGRO_ALIGN_LEFT, "Multiplicador: %i", nave.multiplicador);
                    //Dibujar bomba
                    if(bombt > 0)
                     {
                         bombt--;
                         b.dibujar(imagen[JUGADOR]);
                         for(int i=0; i < NUM_ENEM; i++)
                         {
                                 if (enemigo[i].id != JEFE && enemigo[i].get_x() <= b.get_x())
                                    enemigo[i].vivo=false;
                         }
                         cout << bombt << endl;                          
                     }
                    
                    
                    //Dibujar especial
                    if(esp.vivo)
                    {
                                esp.detectarColisiones(nave);
                                esp.dibujar(especial[esp.id]);
                    }
                                
                    //Mover balas
                    for(int i=0; i < NUM_BALAS; i++)
                    {
                            if (bala[i].vivo)
                            {
                                bala[i].mover();
                                for(int j=0; j < NUM_ENEM; j++)
                                {
                                      bool c=false;
                                      if(enemigo[j].id == JEFE)
                                      {
                                          if(enemigo[j].detectarColisiones(bala[i], nave))
                                          {                                           
                                              if(!enemigo[j].vivo)//Revisar si ya se mato al jefe
                                              {
                                                  c=true;
                                              }   
                                          }
                                          if(c)//tirar especial
                                          {
                                               int id = int(round(rand()%4));
                                               esp.crear(id, especial[id], 20, 20, enemigo[j].get_x(), enemigo[j].get_y());
                                          }
                                      }
    
                                      else if(enemigo[j].detectarColisiones(bala[i], nave))
                                                  break;
                                }
                                if(bala[i].get_x() > WIDTH || 
                                  bala[i].get_x() < 0 || 
                                  bala[i].get_y() > HEIGHT || 
                                  bala[i].get_y() <= 0)
                                {
                                      bala[i].vivo=false;//destruir bala cuando sale de pantalla
                                }    
                                bala[i].dibujar(imagen[BALA]);
                            }
                    }
                             
    
                    for(int i=0; i < NUM_BALAS2; i++)
                    {
                            if (sbala[i].vivo)
                            {
                                sbala[i].mover();
                                for(int j=0; j < NUM_ENEM; j++)
                                {
                                      bool c=false;
                                      if(enemigo[j].id == JEFE)
                                      {
                                          if(enemigo[j].detectarColisiones(sbala[i], nave))
                                          {                                           
                                              if(!enemigo[j].vivo)//Revisar si ya se mato al jefe
                                              {
                                                  c=true;
                                              }   
                                          }
                                          if(c)//tirar especial
                                          {
                                               int id = int(round(rand()%4));
                                               esp.crear(id, especial[id], 20, 20, enemigo[j].get_x(), enemigo[j].get_y());
                                          }
                                      }
    
                                      else if(enemigo[j].detectarColisiones(sbala[i], nave))
                                            if(!sbala[i].vivo)
                                                  break;
                                }
                                if(sbala[i].get_x() > WIDTH || 
                                  sbala[i].get_x() < 0 || 
                                  sbala[i].get_y() > HEIGHT || 
                                  sbala[i].get_y() <= 0)
                                {
                                      sbala[i].vivo=false;//destruir sbala cuando sale de pantalla
                                }    
                                sbala[i].dibujar(imagen[BALA2]);
                            }
                    }    
                    //Dibujar nave 
                    if(nave.vivo)
                    {
                                 nave.establecerDireccion(pos_x, pos_y);
            		             nave.dibujar(imagen[JUGADOR]);
                    }
                    //Dibujar escudo
                    if(nave.escudo)
                    {
                                   escudo.establecerCoordenadas(nave.get_x(), nave.get_y());
                                   escudo.angulo=nave.angulo;
            		               escudo.dibujar(imagen[ESCUDO]);      		
                    }
                    
                    
                    //Movimiento de enemigos
            		for(int i=0; i < NUM_ENEM; i++)
                    {
                            if (enemigo[i].vivo)
                            {
                                if(!enemigo[i].detectarColisiones(nave) || enemigo[i].id == JEFE)
                                {
                                        switch (enemigo[i].id)
                                        {
                                               case ENEM1: //Enemigo 1
                                                    enemigo[i].mover(nave.get_x(), nave.get_y());
                                                    break;
                                               case ENEM2:
                                                    enemigo[i].mover(nave.get_x(), nave.get_y(), enemigo[i].angulo+.1);
                                                    break;
                                               case ENEM3:
                                                    enemigo[i].Proyectil::mover();
                                                    if(enemigo[i].get_x() > WIDTH || enemigo[i].get_x() < 0 || enemigo[i].get_y() > HEIGHT || enemigo[i].get_x() <= 0)
                                                          enemigo[i].vivo=false;
                                                    break;
                                               case JEFE:
                                                    enemigo[i].mover(nave.get_x(), nave.get_y());
                                                    break;
                                        }
                        		        enemigo[i].dibujar(imagen[enemigo[i].id]);
                                }
                            }
                    }
    
    
                    
                    if(nave.vidas<=0)
                    {
                        nave.vivo=false;
                        isGameOver=true;
                    }
                 }
                 else if (isGameOver)
    			 {
                    al_draw_bitmap(fondo, 0, 0, 0);
    				al_draw_textf(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Puntuacion Final: %i", nave.puntos);
    				al_draw_textf(font18, al_map_rgb(255, 0, 0), WIDTH / 2, HEIGHT -20, ALLEGRO_ALIGN_CENTRE, "Presiona enter para continuar");
                    //if(nave.puntos>uno)
    			//	{
                    puntuaciones = al_fopen("puntuaciones.txt", "w");
                    char n =(nave.puntos);//int(nave.puntos);
                    
                    //n=al_cstr(uno);   
                         al_fputs(puntuaciones, &n);             
                    al_fclose(puntuaciones); 
                    //nave.puntos
//                    al_destroy_timer(timer);
    			 }
    			 else if (pause)
    			 {
                     al_draw_bitmap(image17, 0, 0, 0);
                     al_draw_textf(font18, al_map_rgb(255, 50, 0), WIDTH / 2, HEIGHT -50, ALLEGRO_ALIGN_CENTRE, "Pausado"); 
                 }
        		
        		al_flip_display();
        		al_clear_to_color(al_map_rgb(0,0,0));
            }
        }            
}       
    al_destroy_font(font18);     
    al_destroy_sample(Hover);
    al_destroy_sample(song);
    al_destroy_sample_instance(songInstance);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
    al_destroy_timer(timer);
    
    al_destroy_mouse_cursor(cursor);
    
    al_destroy_bitmap(image);
    al_destroy_bitmap(image2);
    al_destroy_bitmap(image3);
    al_destroy_bitmap(image4);
    al_destroy_bitmap(image5);
    al_destroy_bitmap(image6);
    al_destroy_bitmap(image7);
    al_destroy_bitmap(image8);
    al_destroy_bitmap(image9);
    al_destroy_bitmap(image10);
    al_destroy_bitmap(image11);
    al_destroy_bitmap(image12);
    al_destroy_bitmap(image13);
    al_destroy_bitmap(image14);
    al_destroy_bitmap(image15);
    al_destroy_bitmap(image16);
    al_destroy_bitmap(image17);
    
    for (int i=0; i < (sizeof(imagen)/sizeof(imagen[0])); i++)
    {
        al_destroy_bitmap(imagen[i]);
    }
    for (int i=0; i < 4; i++)
    {
        al_destroy_bitmap(especial[i]);
    }
    
	return 0;
}


void iniciarPartida()
{
    
     jugar = true;
     isGameOver=false;
     pause = false;
     nave.establecerCoordenadas(WIDTH/2, HEIGHT/2);
     nave.vivo=true;
     nave.puntos=0;
     nave.vidas=10;
     nave.bombas=3;
     nave.vidas_extra=0;
     nave.bombas_extra=0;
     nave.multiplicador=1;
     nave.escudo=true;
     nave.sbala=50;
     jefe = false;
     for(int i=0; i < NUM_ENEM; i++)
     {
             enemigo[i].vivo=false;
     }
     for(int i=0; i < NUM_BALAS; i++)
     {
             bala[i].vivo=false;
     }
     for(int i=0; i < NUM_BALAS2; i++)
     {
             sbala[i].vivo=false;
     }
     esp.vivo=false;
}
