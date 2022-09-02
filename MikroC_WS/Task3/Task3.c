#

void print_output(unsigned int i)
{



void main() {

unsigned int i;

TRISC = 0x00;   //7 Segment Display output
TRISD = 0x00;   //Transistor Multiplexer output

while(1)

 print_output(i++);
 Delay_ms(100);

}