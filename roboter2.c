
#include <pololu/3pi.h>


uint16_t threshold=800;

int main() {
	set_motors(0,0);
	print("[B]Start");
	wait_for_button(BUTTON_B);
	pololu_3pi_init( 2000 );

	uint16_t values[5];

	clear();
	int i;
	int d=0;
	
	while (d<3) {
		red_led(0);
		green_led(0);
		read_line_sensors( values, IR_EMITTERS_ON);
		delay(5);
		clear ();
		i=0;
		while (i<5) {
			if (values  [i] > threshold) {
				print_character('0');
			}
			else {
				print_character('-');
			}
			i++;
			
		}
		if (values[0]>threshold) {
			set_motors(10,110);
			green_led(0);
			red_led(1);
			delay(5);
		}
		
		
		if (values[1]>threshold) {
			set_motors(50,100);
			green_led(0);
			red_led(1);
			delay(5);
		}
		
			
		if (values[2]>threshold) {
			set_motors(114,110);
			green_led(1);
			red_led(1);
			delay(5);
			
		}
		
		
		if (values[3]>threshold) {
			set_motors(103,50);
			green_led(1);
			red_led(0);
			delay(5);
			
		}

		
		if (values[4]>threshold) {
			set_motors(114,10);
			green_led(1);
			red_led(0);
			delay(5);
			
		}
		
		
		
		
		switch (d) {
			case 0: // warten auf 1. Querlinie
				if ((values[0] > threshold) && (values[1] > threshold) && (values[2] > threshold) && (values[3] > threshold) && (values[4] > threshold)) {
					// Ueberall Linie
					d = 1;
					set_motors(20,20);
					delay(300);
				}
				break;
				
			case 1: // warten auf Zwischenraum
				if ((values[0] < threshold) && (values[1] < threshold) && (values[2] < threshold) && (values[3] < threshold) && (values[4] < threshold)) {
					// Keine Linie mehr
					d = 2;
					set_motors(20,20);
					delay(800);
					set_motors(0,0);
					clear();
					print("Ziel");
					lcd_goto_xy(0,1);
					print("erreicht");
					while (1) {
						red_led(1);
						green_led(1);
						delay(1000);
						red_led(0);
						green_led(0);
						delay(1000);
					}
				} else {
					d = 0;
				}
				break;
			
				
		}
		
		
		/*if ((values[0] > threshold) && (values[1] > threshold) && (values[2] > threshold) && (values[3] > threshold) && (values[4] > threshold) && (d==1)) {
			d=0;
			print_long(d);
			print(",");
		}*/
		
		if ((values[0] < threshold) && (values[1] < threshold) && (values[2] < threshold) && (values[3] < threshold) && (values[4] < threshold) && (d==0)) {
			set_motors(80,80);
			//delay(100);
			clear();
			print("Linie");
			lcd_goto_xy(0,1);
			print("verloren");
		}
		
		/*if ((values[0] > threshold) && ( values[1] > threshold) &&(values[2] > threshold) && (values[3] > threshold) && (values[4] > threshold) && (d==0)) {
			set_motors(120,120);
			delay(1000);
			clear();
			print("Linie");
			lcd_goto_xy(0,1);
			print("verloren");
		}*/
	}
return 0;
}