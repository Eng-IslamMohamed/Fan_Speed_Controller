#include "adc.h"
#include "dc.h"
#include "pwm.h"
#include "gpio.h"
#include "lm35_sensor.h"
#include "common_macros.h"
#include "std_types.h"
#include "lcd.h"

uint16 g_temp=0;
int main(void){
	ADC_ConfigType ADC_Configurations = {INTERNAL,FOURTH_DIV}; //configures  the adc dynamically
	char OFF[]="FAN is OFF";
	char ON[]="FAN is ON ";
	char temp[]="Temp = ";

	ADC_init(&ADC_Configurations);//intializing adc and sending the dynamic structure by address
	DcMotor_init();//intializing dc motor
	LCD_init();//initializing lcd
	LCD_displayStringRowColumn(0,4,OFF);




	while(1){
		g_temp=LM35_getTemperature();//updating the value of the temperature variable every iteration


		if(g_temp>=30){
			/*
			 * the string "FAN is ON" will be displayed while the temperature is higher than 29
			 */
			LCD_displayStringRowColumn(0,4,ON);
		}
		else{
			/*
			 * the string "FAN is OFF" will be displayed while the temperature is LOWER than 30
			 */
			LCD_displayStringRowColumn(0,4,OFF);
		}
		/*rotating the motor according to temperature input*/
		if(g_temp<30){
			DcMotor_Rotate(STOP,0);
		}
		else if(g_temp>=30 && g_temp<60){
			DcMotor_Rotate(CW,25);
		}
		else if(g_temp>=60 && g_temp<90){
			DcMotor_Rotate(CW,50);
		}
		else if(g_temp>=90 && g_temp<120){
			DcMotor_Rotate(CW,75);
		}
		else if(g_temp>=120){
			DcMotor_Rotate(CW,100);
		}
		LCD_displayStringRowColumn(1,4,temp);
		LCD_intgerToString(g_temp);
		/*
		 * to fix the issue of unwanted character of being displayed on lcd while
		 * the temp goes from 3 decimals "113" to 2 decimals "49" or even 1 decimal "8"
		 */
		LCD_displayCharacter(' ');
	}
}
