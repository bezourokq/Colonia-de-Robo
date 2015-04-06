#include <18f2520.h>
#use delay(internal=4Mhz)

int distancia_1 = 0;
int distancia_2 = 0;
int ultima_distancia = 0;
int x = 0;
int y = 0;
int x0 = 0;
int y0 = 0;
int u = 0;
int u0 = 0;

//Interrupçao para exerna 0
#INT_EXT
void externa_0(void){
   if(input(PIN_B0)){
    distancia_1 = distancia_1 + 1;
   }
}
//Interrupção para externa 1
#INT_EXT1
void externa_1(void){
   if(input(PIN_B1)){
   distancia_2 = distancia_2 + 1;
   }
}

//#int_ssp
//void ssp_isr(void){
  // if(SPI_DATA_is_IN()) {
     //x = spi_read(); 
     //x = 15;
     //spi_write(x);
   //}
//}

int AnguloTrajeto(){
   u = u0 + (distancia_1*60 - distancia_2*60)/9600;
}

int coseno(int ul){
   return 2;
}

int seno(int ul){
   return 2;
}

int MCinematico(){
 x = x0 + (distancia_1*60 + distancia_2*60)*(3,14/120)/coseno(u);
 y = y0 + (distancia_1*60 + distancia_2*60)*(3,14/30)/seno(u);
}

void main()
   {
   setup_spi(spi_slave | spi_h_to_l);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts(INT_RB);
   enable_interrupts(INT_SSP);
   enable_interrupts(GLOBAL);
   
 

   while(1)
   {
      //if(ultima_distancia == distancia_1 || ultima_distancia == distancia_1+1){
      // spi_write(1);
      // ultima_distancia = distancia_1;
      //}
   //delay_ms(40);
   //if(spi_read() == 1){
      //spi_write(distancia_1);
   //}else if(spi_read() == 0){
      distancia_2 = spi_read();
      spi_write(2);
  // }
}
   }

