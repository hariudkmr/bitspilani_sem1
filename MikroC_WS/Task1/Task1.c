void main() {
TRISB = 0x07;   //RB0, RB1, RB2 as Input Pins
TRISD = 0x00;   //All the Pins in Port configured as Output
PORTD = 0x00;

 while(1)
 {
    PORTD ^= 0x01;
    Delay_ms(1000);
    }
}