//Gabriela Alejandra de la Fuente Chavez

#include <stdint.h>

//Habilitar Reloj
#define SIM_5 (*((volatile uint32_t *) 0x40048038))
//***************LEDs************************//
//Habilitar pin de led rojo
#define PCR_PTB22 (*((volatile uint32_t *) 0x4004A058))
//Habilitar pin de led azul
#define PCR_PTB21 (*((volatile uint32_t *) 0x4004A054))
//Habilitar pin de led verde
#define PCR_PTE26 (*((volatile uint32_t *) 0x4004D068))
//********************************************//
//GPIO
#define GPIO_B_BASE_ADDR (((volatile uint32_t *) 0x400FF040))
#define GPIO_E_BASE_ADDR (((volatile uint32_t *) 0x400FF100))

typedef struct
{
	uint32_t PDOR;
	uint32_t PSOR;
	uint32_t PCOR;
	uint32_t PTOR;
	uint32_t PDIR;
	uint32_t PDDR;
}GPIO_t;

#define GPIO_B ( (GPIO_t*) GPIO_B_BASE_ADDR)
//#define GPIO_B_Blue ( (GPIO_t*) GPIO_B_BASE_ADDR)
#define GPIO_E ( (GPIO_t*) GPIO_E_BASE_ADDR)

void outs();
void leds_off();
void led_red();
void led_blue();
void led_green();
void led_white();


int main(void) {
	SIM_5 = 0x00002400; //Posicion 13(PORT E) Y 10(PORT B), activar reloj
	//Port Control Register
	PCR_PTB22 = 0x00000100; // Posicion 8, corresponde al MUX, configuracion del pin
	PCR_PTB21 = 0x00000100; // Posicion 8, corresponde al MUX, configuracion del pin
	PCR_PTE26 = 0x00000100; // Posicion 8, corresponde al MUX, configuracion del pin
	
	outs();

    while(1) {

    	led_red();
    	led_blue();
    	led_green();
    	led_white();
    }
    return 0 ;
}

void outs(){
	GPIO_B->PDDR =  0x00600000; // Posicion 21 y 22, para configurarlos como salida
	GPIO_E->PDDR = 0x04000000; // Posicion 26, para configurarlo como salida
	leds_off();
}

void leds_off(){
	GPIO_E->PDOR = 0xFFFFFFFF; //Apagar led verde
	GPIO_B->PDOR = 0xFFFFFFFF; //Apagar leds
}
void led_red(){
	leds_off();
	GPIO_B->PDOR = 0xFFBFFFFF; //Prender led rojo
}
void led_blue(){
	GPIO_B->PDOR = 0xFFFFFFFF; //Apagar leds
	GPIO_B->PDOR = 0xFFDFFFFF; //Prender led azul
}
void led_green(){
	GPIO_B->PDOR = 0xFFFFFFFF; //Apagar leds
	GPIO_E->PDOR = 0xFBFFFFFF; //Prender led verde
}
void led_white(){
	GPIO_E->PDOR = 0xFFFFFFFF; //Apagar led verde
	GPIO_E->PDOR = 0xFBFFFFFF; //Prender led verde
	GPIO_B->PDOR = 0xFF9FFFFF; //Prender led rojo y azul
}
