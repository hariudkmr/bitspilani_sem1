// Prg10a: Add two 8 bit numbers and display in LCD
// RS-> RC3
// EN-> RC0
// LCD data lines-> PORTD(0 to 7)

void Init(void);
void LCD_Command(unsigned char);
void LCD_Data(unsigned char);
void LCDOutput(unsigned int);
void Delay(unsigned int);
unsigned char k[10],x;
unsigned char n,m;
unsigned int hivalue,lovalue,adcv;
long value;
char Lowstring[] = "Low  Voltage";
char Highstring[] = "High Voltage";
char Normstring[] = "Normal Voltage";
char *ptr;


void update_lcd(unsigned int num)
{
   LCD_Command(0x80);               //Initialize cursor to first Position
   LCDOutput(num);
   if(num > 135)
   {
       ptr = (char *)Highstring;
   }
   else if(num < 105)
   {
      ptr = (char *)Lowstring;
   }
   else
   {
       ptr = (char *)Normstring;
   }
   LCD_Command(0xC0);
   while(*ptr != '\0')
      LCD_Data(*ptr++);
  Delay(100);
}


 void main()
 {
     Init();

     ADCON0=0x00;                            // sampling freq=osc_freq/2,ADC off initially
     ADCON0=0x81;                            //configure the A/D control registers
     ADCON1=0x8E;

     while(1)
     {
       ADCON0|=0X04;                           //start ADC conversion
       while(ADCON0&0X04);                     //wait for conversion to complete
       lovalue=ADRESL;                         //read the low 8 bit value
       hivalue=ADRESH;                         //read the upper 8 bit value
       value=((unsigned int)hivalue<<8)+(unsigned int)lovalue;
       adcv = (value*150)/1023 ;
       update_lcd(adcv);
     }
 }
/*end main program*/
void Init(void)
{
  TRISD = 0x00;                   //Initialize the PORTD as output
  TRISC = 0x00;                   //Initialise the PORT C as output
  TRISA = 0x01;
  LCD_Command(0x38);              //Initialize the 2 lines and 5*7 Matrix LCD
  Delay(100);
  LCD_Command(0x38);
  Delay(100);
  LCD_Command(0x38);
  Delay(100);
  LCD_Command(0x38);
  Delay(100);
  LCD_Command(0x06);             //Increment cursor (shift cursor to right)
  Delay(100);
  LCD_Command(0x0C);             //Display on,cursor off
  Delay(100);
  LCD_Command(0x01);             //clear display screen
  Delay(100);
}

/*define the output function*/
/*BCD conversion*/
void LCDOutput(unsigned int num)
{
    unsigned int j;
    unsigned int i;
    unsigned int tdata;

    tdata = num   ;
    if(tdata == 0)
    {
       LCD_Data(0x30);                     //assign formal argument to other variable
       LCD_Data(0x30);
       LCD_Data(0x2E);
       LCD_Data(0x30);
       LCD_Data('V');
     }
    else
    {
        j=0;
        while (tdata != 0)
                {
                        i = tdata - (tdata / 10) * 10;
                        k[j] = i+0x30;
                        tdata = tdata / 10;
                        j++;
                }
                k[j] = '\0';
                //LCD_Data(k[3]);
                LCD_Data(k[2]);
                LCD_Data(k[1]);
                LCD_Data(0x2E);
                LCD_Data(k[0]);
                LCD_Data('V');

    }
}

void LCD_Command(unsigned char i)
{
     PORTC&=~0x04;               // RS=0
     PORTD=i;
     PORTC |=0x02;               // RS=0,R/W=0,EN=1
     PORTC&= ~0x02;              // RS=0,R/W=0,EN=0
     Delay(100);
}

void LCD_Data(char i)
{
    PORTC|=0x04;              //RS=1
    PORTD=i;                  //Assign the value to PORTD to display
    PORTC|=0x02;              // RS=1,R/W=0,EN=1
    PORTC&=~0x02;             // RS=1,R/W=0,EN=0
    Delay(100);
}

void Delay(unsigned int DelayCount)
{
    while(--DelayCount);
}