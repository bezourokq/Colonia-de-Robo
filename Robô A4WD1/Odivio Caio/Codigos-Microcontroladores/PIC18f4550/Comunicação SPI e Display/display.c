/* Codigo desenvolvido por Odivio Caio, com a finalidade de efeturar 
uma comunicação SPI entre um PIC18f4550 e o Microcontrolador do Robo A4WD1.
Foi ultilizado o CSS como IDE e seus proprios compiladores.
*/
 

#include <18F4550.H> 
#fuses XT, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP 
#fuses inths                                
#use delay(clock=20000000)    
#include <flex_lcd.c>

int x = 0; //variavel onde será guardado o valor recebido.
int contador = 0;//contador do evento gerado pela interrupção externa.

#INT_EXT //Interrupção externa
void externa(void){
      if(input(PIN_B2)){
      contador++; 
   }
}

#int_ssp //Interrupção do SPI
void ssp_isr(void){
   if(spi_data_is_in()) {
         disable_interrupts(INT_SSP); 
         x = spi_read();//Leitura do Valor recebido pela comunicação
         printf(lcd_putc, "\f Hex %x \n",x); //Escreve no display o valor recebido em Hexa
         printf(lcd_putc, "\Long1 %d",x); //Escreve no display o valor recebido em Long
         enable_interrupts(INT_SSP); 
      }
}

void main() 
{
   output_low(PIN_A2); //Apaga LED_1
   output_low(PIN_B2); //Apaga LED_2
   enable_interrupts(INT_EXT);//Ativação da interrupção externa      
   lcd_init();//Inicialização da biblioteca para o uso do LCD
   enable_interrupts(INT_SSP);//Ativação da interrupção SPI 
   enable_interrupts(GLOBAL); //Ativação da interrupção Global 
   setup_spi(spi_master | spi_l_to_h |SPI_SAMPLE_AT_END | SPI_SS_DISABLED);
   
   while(1)
   {
   delay_ms(40);
   spi_write(15);
  } 
}
