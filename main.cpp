/*  LCD Screen Test
*   Designed to test basic functionality of the Nokia N5110 LCD display.    
*   The screen is 84 x 48 pixels with the upper lefthand corner having the
*   designation of (0,0). The x,y co-ordinates of each image and sprite relate
*   to the upper left hand corner of each image.
*
*   Required library: N5110
*   Author: Andrew Knowles 2021. Modified Feb 2022 by Dr Tim Amsdon
*/

#include "mbed.h"
#include "N5110.h"

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);

const int Fish[4][9]= {
    { 1,0,0,1,1,1,1,1,0, },
    { 1,1,1,1,1,1,1,0,1, },
    { 1,1,1,1,1,1,1,1,1, },
    { 1,0,0,1,1,1,1,1,0, },
};

int main(){
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)

    lcd.clear();

    // note: each char is 8x6 pixels, therefore the maximum number of chars in a string is 14 (84/6 = 14), including spaces
    // note: due to the height of each char the screen is divided into 6 rows, therefore the range of y values is 0-5 (48/8 = 6)
    //lcd.printString(string, x, y)
    lcd.printString(" LCD  Working ", 0, 1);
    lcd.printString(" ============ ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(2s);  //sleep for 2 seconds

    lcd.clear();
    lcd.printString("  Begin Test  ", 0, 1);
    lcd.printString("  ==========  ", 0, 2);
    lcd.refresh();
    ThisThread::sleep_for(2s);

    while(1){
        lcd.clear();

        //lcd.drawCircle(x, y, radius, fill_type)
        lcd.drawCircle(5, 5, 4, FILL_BLACK);            //solid circle
        lcd.drawCircle(17, 5, 4, FILL_TRANSPARENT);     //outlined circle

        //             origin  finish
        //lcd.drawLine(x0, y0, x1, y1, fill_type)
        lcd.drawLine(0, 20, 84, 20, 1);                 //solid line
        lcd.drawLine(0, 25, 84, 25, 2);                 //dotted line

        //lcd.drawRect(x, y, width, height, fill_type)
        lcd.drawRect(0, 30, 84, 4, FILL_BLACK);         //solid black rectangle
        lcd.drawRect(0, 39, 84, 4, FILL_TRANSPARENT);   //outlined rectangle

        //lcd.drawSprite(x, y, rows, columns, int)
        lcd.drawSprite(30, 5, 4, 9, (int*)Fish);        //draws 'fish' sprite

        //lcd.setPixel(x, y, bool state)
        lcd.setPixel(45, 5, 1);                         //turn pixel at co-ordinate (45,5) 'on'

        //lcd.printChar(char, x, y) - refer to printString notes
        lcd.printChar('C', 50, 1);
        lcd.refresh();
    }
}
