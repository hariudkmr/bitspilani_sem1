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
unsigned int Num1,Num2,Sum;
char Lowstring[] = "Low Voltage";
char Highstring[] = "High Voltage";
char *ptr;


void update_lcd(unsigned int num)
{
   LCD_Command(0x01);            //clear display screen
   LCD_Command(0x80);               //Initialize cursor to first Position
   LCDOutput(num);
   if(num > 100)
   {
       ptr = (char *)Highstring;
   }
   else
   {
       ptr = (char *)Lowstring;
   }
   LCD_Command(0xC0);
   while(*ptr != '\0')
      LCD_Data(*ptr++);
   Delay_ms(1000);
}


 void main()
 {
     Init();
     Num1 = 0;                               //Assign the first value
     Num2 = 255;                               //Assign the second value
     while(1)
     {
       update_lcd(Num1++);
       update_lcd(Num2--);
     }
 }
/*end main program*/
void Init(void)
{
  TRISD = 0x00;                   //Initialize the PORTD as output
  TRISE = 0x00;                   //Initialise the PORT C as output
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
void LCDOutput(unsigned int i)
{
    unsigned char s,j=1;
    m=i;                                  //assign formal argument to other variable
    while(m!=0)                           //check that value is zero or not
    {       
        s = m-(m/10)*10;
                                          //store the reminder of m/10 in s
       k[j] = s;                          //move s to an array
       j++;                               //Increment the array address
       m = m/10;                          //Divide the value by 10, store the Quotient in'm'
    }
    k[j] = '\0';                          //assign the NULL value at the end of the array
    j = j-1;                              //decrement the array address
    while(j!=0)                           //check the k[] array address is zero or not
    {
      n=0x30+k[j];                        //convert to ascii value
      Lcd_Data(n);                        //pass that value to display function
      j--;                                //decrement the array address
    }
}

void LCD_Command(unsigned char i)
{
     PORTE&=~0x04;               // RS=0
     PORTD=i;
     PORTE |=0x02;               // RS=0,R/W=0,EN=1
     PORTE&= ~0x02;              // RS=0,R/W=0,EN=0
     Delay(100);
}

void LCD_Data(char i)
{
    PORTE|=0x04;              //RS=1
    PORTD=i;                  //Assign the value to PORTD to display
    PORTE|=0x02;              // RS=1,R/W=0,EN=1
    PORTE&=~0x02;             // RS=1,R/W=0,EN=0
    Delay(100);
}
    
void Delay(unsigned int DelayCount)
{
    while(--DelayCount);
}