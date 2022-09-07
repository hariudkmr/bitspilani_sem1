//RA2-RA5 - Transistor Mux
//RD0-RD7 - LED OUTPUT

#define D0 0x3F
#define D1 0x06
#define D2 0x5B
#define D3 0x4F
#define D4 0x66
#define D5 0x6D
#define D6 0x7D
#define D7 0x07
#define D8 0x7F
#define D9 0x6F

unsigned int digits[10] = {D0, D1, D2, D3, D4, D5, D6, D7, D8, D9};

#if 0

void print_output(unsigned int num)
{
   unsigned int tdata,m;
   unsigned int i,j;
   unsigned int segled;

   tdata = num;
   for(i=0; i < 4;  i++)
   {
      m = tdata - (tdata/10) * 10;
      digits[i] = m;
      tdata = tdata/10;
   }

   for(i=0; i < 4; i++)
   {

    }
}
#endif

void main() 
{

  unsigned int i,j;

  TRISD = 0x00;   //7 Segment Display output
  TRISA = 0x00;   //Transistor Multiplexer output

  while(1)
   {
      for(i =0; i < 10; i++)
      {
        PORTD = digits[i];
        for(j= 0; j <4 ; j++)
        {
          PORTA = 0x20 >> j;
          Delay_ms(30);
        }
        Delay_ms(50);
      }
   }

}
