void main() {
TRISB = 0x07;
TRISD = 0x00;

  while(1)
  {
      
      while(!(PORTB & 0x01))
      {
         PORTD ^= 0x03;
         Delay_ms(1000);
      }

      while(!(PORTB & 0x02))
      {
         PORTD ^= 0xC0;
         Delay_ms(1000);
      }

      while(!(PORTB & 0x04))
      {
         PORTD ^= 0xE7;
         Delay_ms(1000);
      }
      PORTD = 0x00;
    }
}