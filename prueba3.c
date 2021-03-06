
#define LCD_RS_PIN PIN_B0
#define LCD_RW_PIN PIN_B1
#define LCD_ENABLE_PIN PIN_B2
#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B4
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B6

 
#include <16F877a.h>
#fuses HS,NOWDT,PUT,NOPROTECT
#use delay(clock=48M)
#include <lcd.c>

#define trigger PIN_A0
#define echo PIN_A1

#use standard_io (a)





 


void mide_distancia(void);

long tiempo_eco=0;  //tiempo que dura el eco
float  distancia=0;   //distancia en cm


void main() {


  lcd_init();                 
  printf(lcd_putc,"Ultrasonico");
  delay_ms(500);
  printf(lcd_putc,"\f");
  
  setup_timer_1(T1_INTERNAL | T1_DIV_BY_8 );
  set_timer1(0);
 
  while(TRUE) {
  
    delay_ms(200);
    
    mide_distancia();
    
    
   }
   
   
   
}

void mide_distancia(void)
{
   output_high(Trigger);         // pulso de disparo
   delay_us(10);                 //Esperamos 10 us
   output_low(Trigger);          //Apagamos el pulso
   while(!input_state(Echo)){
   }                             //espera flanco de subida
   set_timer1(0);                //Iniciamos el timer1
   while(input_state(Echo)){
   }                             //esperamos flanco de bajada
   tiempo_eco = get_timer1();//Leemos el valor del timer1
   distancia = (tiempo_eco/2)*34*.000666; //Convertimos a distancia //tiempo = (4/Fosc)*prescaler = (4/48M)*8 = 0.000666 ms
   lcd_gotoxy(1,2);              //Cursor en la posicion columna 1 fila 2
   printf(lcd_putc,"\nDist: %1.2f cm", distancia); //Imprimimos la distancia
   delay_ms(200);                //Esperamos 200ms
   
   
}
