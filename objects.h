
#include<iostream>
using namespace std;



//Constantes
const int WIDTH=660;
const int HEIGHT=440;
const int FPS = 60;

const int NUM_BALAS=20;
const int NUM_BALAS2=10;
const int NUM_ENEM=20;

//Enumeradores
enum {X, Y};
enum KEYS{UP, DOWN, LEFT, RIGHT};
enum ID{JUGADOR, ESCUDO, BALA, BALA2, ENEM1, ENEM2, ENEM3, JEFE};
enum ID_ESP{ESC, SBALA, VIDA, BOMBA};

//Boleanos
bool keys[4] = {false, false, false, false};
bool pause = false;
bool isGameOver = false;
bool jefe = false;
bool jugar = false;
//Clase Punto
class Punto
{
      public:
             int coor[2];
             int get_x();
             int get_y();
             void set_x(int v);
             void set_y(int v);
};

//Clase Base
class Base: public Punto
{
      public:
             int velocidad;
             int bound[2];
             
             float dir[2];
             float angulo;
             
             bool vivo;
             //imagen
             //ALLEGRO_BITMAP *image;
             int imageWidth;
             int imageHeight;
             
             //Destructor
             ~Base();
             
             //Metodos
             void establecerImagen(ALLEGRO_BITMAP *imagen);
             void establecerImagen(ALLEGRO_BITMAP *imagen, int x, int y);
             void dibujar(ALLEGRO_BITMAP *image);//dibujar y girar
             void establecerBound(int x, int y);//
             void establecerDireccion(int x, int y);//Da vector unitario y angulo
             void establecerCoordenadas(int x, int y);//pone el objeto en las coordenadas indicadas
};

//Clase Proyectil
class Proyectil: public Base
{
      public:
             int vidas;
             //Constructores
             Proyectil();
             //Destructor
             ~Proyectil();
             
             //Metodos
             void mover();//velocidad * direccion
//desaparecer cuando salga de pantalla
};

//Clase Jugador
class Jugador: public Base
{
      public:
             int vidas;
             bool escudo;
             int sbala;
             int puntos;
             int bombas;
             int vidas_extra; 
             int bombas_extra;
             int multiplicador;
             int n;
             
             //Constructores
             Jugador();
             Jugador(ALLEGRO_BITMAP *imagen);
             
             //Destructor
             ~Jugador();
             
             //Metodos
             void mover(bool keys[4]);
             void sumarMultiplicador();
             void reiniciarMultiplicador();
             void sumarPuntos(int p);
             void vidaExtra();
             void bombaExtra();
//disparar
};

//Clase Enemigo
class Enemigo: public Proyectil
{
      public:
             int id;
             //Constructores
             Enemigo();
             //Destructor
             ~Enemigo();
             
             //Metodos
             void mover(int x, int y);
             void mover(int x, int y, float ang);
             void establecerDireccion(int x, int y, float ang);
             void crear(int i, ALLEGRO_BITMAP *imagen, int v, int boundx, int boundy,
                    int n);//revisar q no choque con jugador, cargar imagen, y establecer velocidad, bound, vidas, id
             bool establecerCoordenadas(int x, int y, Jugador &jugador);//Revisa que no haya colisiones al crear el objeto
//explotar
             bool encontrarColisiones(Jugador &jugador);//Encuentra colisiones Enemigo-Jugador
             bool detectarColisiones(Jugador &jugador);//Colisiones Enemigo-Jugador
             bool detectarColisiones(Proyectil &bala, Jugador &jugador);//Colisiones Enemigo-Proyectil
};
//Clase Jefe????????????




//Clase Especial
class Especial:public Base
{
      public:
             int id;
             int t;
             //Destructores
             ~Especial();
             
             //Metodos
             void crear(int i, ALLEGRO_BITMAP *imagen, int v, int boundx, int boundy,
                            int n);//revisar q no choque con jugador, cargar imagen, y establecer velocidad, bound, vidas, id
             bool encontrarColisiones(Jugador &jugador);//Encuentra colisiones Especial-Jugador
             void detectarColisiones(Jugador &jugador);//Colisiones EspecialJugador
             void dibujar(ALLEGRO_BITMAP *image);
             
};
//Clase Bomba
class Bomba: public Base
{
      public:
             Bomba();
             
             ~Bomba();
             
             void dibujar(ALLEGRO_BITMAP *image);
};
                      
             










/********************************************************/
/********************************************************/
/********************************************************/
/********************************************************/
//Metodos de Punto
int Punto::get_x()
{
  return coor[X];
}

int Punto::get_y()
{
  return coor[Y];
}

void Punto::set_x(int v)
{
  coor[X]=v;
}

void Punto::set_y(int v)
{
  coor[Y]=v;
}
/********************************************************/
/********************************************************/
/********************************************************/
//Metodos de Base
//Constructores

//Destructor
Base::~Base()
{
 //al_destroy_bitmap(image);
}

//Metodos
void Base::establecerImagen(ALLEGRO_BITMAP *imagen)
{
     //image=imagen;
     imageWidth =  al_get_bitmap_width(imagen);
     imageHeight = al_get_bitmap_height(imagen);
}

void Base::establecerImagen(ALLEGRO_BITMAP *imagen, int x, int y)
{
     //image=imagen;
     imageWidth =  al_get_bitmap_width(imagen);
     imageHeight = al_get_bitmap_height(imagen);
     establecerBound(imageWidth/2+x, imageHeight/2+y);
}

void Base::dibujar(ALLEGRO_BITMAP *image)//dibujar y girar
{
     al_draw_rotated_bitmap(image, imageWidth / 2, imageHeight / 2, get_x(), get_y(),  angulo, 0);
     //al_draw_filled_rectangle(coor[X]+bound[X], coor[Y]+bound[Y], coor[X]-bound[X], coor[Y]-bound[Y], al_map_rgb(0,0,255));
}

void Base::establecerBound(int x, int y)//
{
     bound[X]=x;
     bound[Y]=y;
}

void Base::establecerDireccion(int x, int y)//Da vector unitario y angulo
{
     float dx = x-coor[X];
     float dy = y-coor[Y];
     float m = sqrt((dx)*(dx)+(dy)*(dy));
     m = (m!=0)? m : 1;//No se puede dividir entre 0
     
     dir[X] = dx / m;
     dir[Y] = dy / m;
    
     angulo=atan2(dy, dx);
}

void Base::establecerCoordenadas(int x, int y)//pone el objeto en las coordenadas indicadas
{
     coor[X]=x;
     coor[Y]=y;
}

/********************************************************/
/********************************************************/
/********************************************************/
//Metodos de Proyectil
//Constructores
Proyectil::Proyectil()
{
    vidas=0;
}

//Destructor
Proyectil::~Proyectil()
{
//    al_destroy_bitmap(image);
}

//Metodos
void Proyectil::mover()//velocidad * direccion
{
    coor[Y] += int(round(dir[Y] * velocidad));
    coor[X] += int(round(dir[X] * velocidad));
}

//desaparecer cuando salga de pantalla
/********************************************************/
/********************************************************/
/********************************************************/
//Metodos de Enemigo
Enemigo::Enemigo()
{
    vivo = false;
}
//Destructor
Enemigo::~Enemigo()
{
  //  al_destroy_bitmap(image);
}

//Metodos
void Enemigo::mover(int x, int y)
{///////////////////////////////////////////////////////////////////////////////////////////////////////////////
     //Encontrar direccion
     Base::establecerDireccion(x, y);
     
     coor[Y] += int(round(dir[Y] * velocidad));
     coor[X] += int(round(dir[X] * velocidad));
     
     
     if(coor[X] > WIDTH)
          coor[X] = WIDTH;
     else if(coor[X] < 0)
          coor[X] = 0;

     if (coor[Y] > HEIGHT)
          coor[Y] = HEIGHT;
     else if(coor[Y] < 0)
          coor[Y] = 0; 
}

void Enemigo::mover(int x, int y, float ang)
{
     //Encontrar direccion
     establecerDireccion(x, y, ang);
     
     coor[Y] += int(round(dir[Y] * velocidad));
     coor[X] += int(round(dir[X] * velocidad));
     
     
     if(coor[X] > WIDTH)
          coor[X] = WIDTH;
     else if(coor[X] < 0)
          coor[X] = 0;

     if (coor[Y] > HEIGHT)
          coor[Y] = HEIGHT;
     else if(coor[Y] < 0)
          coor[Y] = 0;
}

void Enemigo::establecerDireccion(int x, int y, float ang)
{
    float dx = x-coor[X];
    float dy = y-coor[Y];
    float m = sqrt((dx)*(dx)+(dy)*(dy));
    m = (m!=0)? m : 1;//No se puede dividir entre 0
    
    dir[X] = dx / m;
    dir[Y] = dy / m;
    
    angulo=ang;
}
void Enemigo::crear(int i, 
                    ALLEGRO_BITMAP *imagen, 
                    int v, 
                    int boundx, int boundy,
                    int n)//revisar q no choque con jugador, cargar imagen, y establecer velocidad, bound, vidas, id
{
     establecerImagen(imagen, boundx, boundy);
     id=i;
     velocidad=v;
     vidas=n;
     vivo=true;
}
bool Enemigo::establecerCoordenadas(int x, int y, Jugador &jugador)//Revisa que no haya colisiones
{
     Base::establecerCoordenadas(x, y);
     if(encontrarColisiones(jugador))
         return true;
     return false;
}

//explotar

bool Enemigo::encontrarColisiones(Jugador &jugador)//Encuentra colisiones Enemigo-Jugador
{
     if(get_x() - bound[X] < jugador.get_x() + jugador.bound[X] &&
        get_x() + bound[X] > jugador.get_x() - jugador.bound[X] &&
	    get_y() - bound[Y] < jugador.get_y() + jugador.bound[Y] &&
	    get_y() + bound[Y] > jugador.get_y() - jugador.bound[Y])
     {
          return true;
     }
     return false;
}

bool Enemigo::detectarColisiones(Jugador &jugador)//Colisiones Enemigo-Jugador
{
     if(encontrarColisiones(jugador))
     {
         if (id != JEFE)
         {
                vidas=0;
                vivo=false;
         }
         else
         {
              int x, y;
              do 
              {
                   x = rand()%WIDTH;
                   y = rand()%HEIGHT;                                         
              } while(establecerCoordenadas(x, y, jugador));
         }
         if(jugador.escudo)
                        jugador.escudo=false;
         else
		 {
             jugador.vidas--;
             jugador.reiniciarMultiplicador();
             if (jugador.vidas <= 0)
                        jugador.vivo=false;
         }
         return true;
      }
    return false;
}

bool Enemigo::detectarColisiones(Proyectil &bala, Jugador &jugador)//Colisiones Enemigo-Proyectil
{
     if(vivo &&
        get_x() - bound[X] < bala.get_x() + bala.bound[X] &&
        get_x() + bound[X] > bala.get_x() - bala.bound[X] &&
	    get_y() - bound[Y] < bala.get_y() + bala.bound[Y] &&
	    get_y() + bound[Y] > bala.get_y() - bala.bound[Y])
       {
          int n;//Puntos a sumar
		  int v = bala.vidas;
		  bala.vidas -= vidas;
		  vidas -= v;
		  
		  if (vidas <= 0)
		  {
                         vivo=false;
                         jugador.sumarMultiplicador();
                         switch(id)
                         {
                                        case ENEM1:
                                             n=10;
                                             break;
                                        case ENEM2:
                                             n=15;
                                             break;
                                        case ENEM3:
                                             n=25;
                                             break;
                                        case JEFE:
                                             jefe=false;
                                             n=50;
                                             break;
                         }
          } 
          else
              n=1;
          if (bala.vidas <= 0)
                         bala.vivo=false;
          jugador.sumarPuntos(n);
          return true;
       }
    return false;
}
/********************************************************/
/********************************************************/
/********************************************************/
//Constructores
Jugador::Jugador()
{
    velocidad=5;
    bound[X]=0;
    bound[Y]=0;
    set_x(WIDTH/2);
    set_y(HEIGHT/2);
}
Jugador::Jugador(ALLEGRO_BITMAP *imagen)
{
    establecerImagen(imagen);
    velocidad=5;
}

//Destructor
Jugador::~Jugador()
{
     //al_destroy_bitmap(image);
}

//Metodos de Jugador
void Jugador::mover(bool keys[4])
{
     coor[Y] -= keys[UP]*velocidad;
     coor[Y] += keys[DOWN]*velocidad;
     coor[X] += keys[RIGHT]*velocidad;
     coor[X] -= keys[LEFT]*velocidad;

     if(coor[X] > WIDTH)
          coor[X] = WIDTH;
     else if(coor[X] < 0)
          coor[X] = 0;

     if (coor[Y] > HEIGHT)
          coor[Y] = HEIGHT;
     else if(coor[Y] < 0)
          coor[Y] = 0;
}
 
void Jugador::sumarPuntos(int p)
{
      puntos += (p * multiplicador);
      vidaExtra();
      bombaExtra();
}

void Jugador::vidaExtra()
{
       if(puntos-500*(vidas_extra+1) >=0 )
       {
           vidas+=1;
           vidas_extra+=1;
       }
}

void Jugador::bombaExtra()
{
       if(puntos-750*(bombas_extra+1) >=0 )
       {
           bombas+=1;
           bombas_extra+=1;
       } 
} 

void Jugador::sumarMultiplicador()
{
       n++;
       if(n-(10) >= 0)
       {
           multiplicador+=1;
           n=0;
       }
}

void Jugador::reiniciarMultiplicador()
{
       n=0;
       multiplicador=1;
}

/********************************************************/
/********************************************************/
/********************************************************/
//Clase Especial
//Destructores
Especial::~Especial()
{
    //al_destroy_bitmap(image);
}

//Metodos
void Especial::crear(int i, ALLEGRO_BITMAP *imagen, int boundx, int boundy, int x, int y)//revisar q no choque con jugador, cargar imagen, y establecer velocidad, bound, vidas, id
{
     t=5*FPS;//segundos*FPS
     id = i;
     establecerImagen(imagen, boundx, boundy);
     
     establecerCoordenadas(x,y);
     vivo=true;
}
bool Especial::encontrarColisiones(Jugador &jugador)//Encuentra colisiones Especial-Jugador
{
     if(get_x() - bound[X] < jugador.get_x() + jugador.bound[X] &&
        get_x() + bound[X] > jugador.get_x() - jugador.bound[X] &&
	    get_y() - bound[Y] < jugador.get_y() + jugador.bound[Y] &&
	    get_y() + bound[Y] > jugador.get_y() - jugador.bound[Y])
     {
          return true;
     }
     return false;
}
void Especial::detectarColisiones(Jugador &jugador)//Colisiones EspecialJugador
{
     if(encontrarColisiones(jugador))
     {
         vivo=false;
         switch(id)
         {
                   case SBALA:
                        jugador.sbala=50;
                        break;
                   case ESC:
                        jugador.escudo=true;
                        break;
                   case VIDA:
                        jugador.vidas++;
                        break;
                   case BOMBA:
                        jugador.bombas++;
                        break;
         }
//         return true;
      }
//    return false;
}
void Especial::dibujar(ALLEGRO_BITMAP *image)
{
     t--;
     if(t == 0)
     {
             vivo=false;
     }
     angulo += 0.05;
     Base::dibujar(image);
}

/********************************************************/
/********************************************************/
/********************************************************/
//Clase Bomba
Bomba::Bomba()
{
              angulo=0;
}
//Destructores
Bomba::~Bomba()
{
    //al_destroy_bitmap(image);
}
//Metodos
//bool Bomba::encontrarColisiones(Enemigo &enem)
//{
//     if(get_x() - bound[X] < enem.get_x() + enem.bound[X] &&
//        get_x() + bound[X] > enem.get_x() - enem.bound[X] &&
//	    get_y() - bound[Y] < enem.get_y() + enem.bound[Y] &&
//	    get_y() + bound[Y] > enem.get_y() - enem.bound[Y])
//     {
//          return true;
//     }
//     return false;
//}
//void Bomba::detectarColisiones(Enemigo &enem)
//{
//     if(enem.vivo && enem.id!= 0 && encontrarColisiones(enem))
//     {
//                  enem.vidas=0;
//                  enem.vivo=0;
//     }
//}
void Bomba::dibujar(ALLEGRO_BITMAP *image)
{
     int x=get_x()+10;
     if(x <= WIDTH)
     {
         for(int y = 0; y <= HEIGHT; y += imageHeight)
         {
                         establecerCoordenadas(x,y);
                         Base::dibujar(image);
                        
         }
     }
}
             
/********************************************************/
/********************************************************/
/********************************************************/
