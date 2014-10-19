#include <Wire.h>
#include "LedControlMS.h"
// #include "MotionSensor.h"

// Number of matrix that are connected
const int NBR_MTX = 2;
// Clock
const int DS1307 = 0x68; // Address of DS1307 see data sheets

LedControl lc = LedControl(8,9,10, NBR_MTX);
// MotionSensor ms = MotionSensor(0);

// Arrays with the LED setup for numbers and eyes
bool number[10][8][8] = {0};
bool eye[4][8][8] = {0};
// Vars to check if time values has changed
int current_h1, current_h2, current_m1, current_m2;

// Enable or disable debug mode
bool debug = true;

void setup() {
  Serial.begin (9600);
  if (debug) Serial.println("Setup");

  Wire.begin();
  // This delay allows the MCU to read the current date and time.
  delay(2000);

  // Enble this if you want to change the datetime in the clock chip
  // setDateTime();

  for (int i=0; i< NBR_MTX; i++){
    lc.shutdown(i,false);
    // Set the brightness
    lc.setIntensity(i,1);
    // and clear the display
    lc.clearDisplay(i);
  }

  lc.clearAll();
  setNums();
  setEyes();

}


void loop() {

  if (true){
    Serial.println("----- TIME ----");
    showTime();
  }else{
    Serial.println("----- EYES ----");
    showEyes();
  }

}

/**
 * Show the current time in display
 */
void showTime() {
  int second, minute, hour, weekday, monthday, month, year;
  int h1, h2, m1, m2;

  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.endTransmission();

  Wire.requestFrom(DS1307, 7);
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);

  h1 = hour / 10;
  h2 = hour % 10;

  m1 = minute / 10;
  m2 = minute % 10;

  if (current_h1 != h1){
    animateIn( h1, 0, 0 );

    current_h1 = h1;
  }
  if (current_h2 != h2){
    animateIn( h2, 0, 4 );

    current_h2 = h2;
  }
  if (current_m1 != m1){
    animateIn( m1, 1, 0 );

    current_m1 = m1;
  }
  if (current_m2 != m2){
    animateIn( m2, 1, 4 );

    current_m2 = m2;
  }
}

/**
 * Show eyes in display
 */
void showEyes(){
  int delayPestana = 50;

  paintArray( eye[0], 0, 0, 0);
  paintArray( eye[0], 1, 0, 0);
  delay(3000);

  paintArray( eye[3], 0, 0, 0);
  paintArray( eye[3], 1, 0, 0);
  delay(delayPestana);

  paintArray( eye[2], 0, 0, 0);
  paintArray( eye[2], 1, 0, 0);
  delay(1000);

  paintArray( eye[1], 0, 0, 0);
  paintArray( eye[1], 1, 0, 0);
  delay(1000);

  paintArray( eye[2], 0, 0, 0);
  paintArray( eye[2], 1, 0, 0);
  delay(1000);

  paintArray( eye[3], 0, 0, 0);
  paintArray( eye[3], 1, 0, 0);
  delay(delayPestana);


}



/**
 * SETUP
 */


void setEyes(){
  //Centrado
  eye[0][0][5] = true;
  eye[0][0][4] = true;
  eye[0][0][3] = true;
  eye[0][0][2] = true;
  eye[0][1][6] = true;
  eye[0][1][1] = true;
  eye[0][2][6] = true;
  eye[0][2][1] = true;
  eye[0][3][6] = true;
  eye[0][3][4] = true;
  eye[0][3][3] = true;
  eye[0][3][1] = true;
  eye[0][4][6] = true;
  eye[0][4][4] = true;
  eye[0][4][3] = true;
  eye[0][4][1] = true;
  eye[0][5][6] = true;
  eye[0][5][1] = true;
  eye[0][6][6] = true;
  eye[0][6][1] = true;
  eye[0][7][5] = true;
  eye[0][7][4] = true;
  eye[0][7][3] = true;
  eye[0][7][2] = true;

  // Mirar izquierda
  eye[1][0][5] = true;
  eye[1][0][4] = true;
  eye[1][0][3] = true;
  eye[1][0][2] = true;
  eye[1][1][6] = true;
  eye[1][1][1] = true;
  eye[1][2][6] = true;
  eye[1][2][4] = true;
  eye[1][2][3] = true;
  eye[1][2][1] = true;
  eye[1][3][6] = true;
  eye[1][3][4] = true;
  eye[1][3][3] = true;
  eye[1][3][1] = true;
  eye[1][4][6] = true;
  eye[1][4][1] = true;
  eye[1][5][6] = true;
  eye[1][5][1] = true;
  eye[1][6][6] = true;
  eye[1][6][1] = true;
  eye[1][7][5] = true;
  eye[1][7][4] = true;
  eye[1][7][3] = true;
  eye[1][7][2] = true;

  // // Mirar derecha
  eye[2][0][5] = true;
  eye[2][0][4] = true;
  eye[2][0][3] = true;
  eye[2][0][2] = true;
  eye[2][1][6] = true;
  eye[2][1][1] = true;
  eye[2][2][6] = true;
  eye[2][2][1] = true;
  eye[2][3][6] = true;
  eye[2][3][1] = true;
  eye[2][4][6] = true;
  eye[2][4][4] = true;
  eye[2][4][3] = true;
  eye[2][4][1] = true;
  eye[2][5][6] = true;
  eye[2][5][4] = true;
  eye[2][5][3] = true;
  eye[2][5][1] = true;
  eye[2][6][6] = true;
  eye[2][6][1] = true;
  eye[2][7][5] = true;
  eye[2][7][4] = true;
  eye[2][7][3] = true;
  eye[2][7][2] = true;


  // pestañear
  eye[3][0][3] = true;

  eye[3][1][4] = true;
  eye[3][1][3] = true;

  eye[3][2][4] = true;
  eye[3][2][3] = true;

  eye[3][3][4] = true;
  eye[3][3][3] = true;

  eye[3][4][4] = true;
  eye[3][4][3] = true;

  eye[3][5][4] = true;
  eye[3][5][3] = true;

  eye[3][6][4] = true;
  eye[3][6][3] = true;

  eye[3][7][3] = true;


}

void setNums(){
  //Cero
  number[0][0][0] = true;
  number[0][0][1] = true;
  number[0][0][2] = true;
  number[0][0][3] = true;
  number[0][0][4] = true;
  number[0][0][5] = true;
  number[0][0][6] = true;
  number[0][0][7] = true;
  number[0][1][7] = true;
  number[0][1][0] = true;
  number[0][2][0] = true;
  number[0][2][1] = true;
  number[0][2][2] = true;
  number[0][2][3] = true;
  number[0][2][4] = true;
  number[0][2][5] = true;
  number[0][2][6] = true;
  number[0][2][7] = true;

  //Uno
  number[1][0][0] = true;
  number[1][1][0] = true;
  number[1][2][0] = true;
  number[1][1][1] = true;
  number[1][1][2] = true;
  number[1][1][3] = true;
  number[1][1][4] = true;
  number[1][1][5] = true;
  number[1][1][6] = true;
  number[1][1][7] = true;
  number[1][0][6] = true;

  //Dos
  number[2][0][7] = true;
  number[2][1][7] = true;
  number[2][1][7] = true;
  number[2][2][6] = true;
  number[2][2][5] = true;
  number[2][2][4] = true;
  number[2][1][3] = true;
  number[2][0][2] = true;
  number[2][0][1] = true;
  number[2][0][0] = true;
  number[2][1][0] = true;
  number[2][2][0] = true;

  //Tres
  number[3][0][7] = true;
  number[3][1][7] = true;
  number[3][2][6] = true;
  number[3][2][5] = true;
  number[3][2][4] = true;
  number[3][2][3] = true;
  number[3][2][2] = true;
  number[3][2][1] = true;
  number[3][1][3] = true;
  number[3][1][0] = true;
  number[3][0][3] = true;
  number[3][0][0] = true;

  //Cuatro
  number[4][0][3] = true;
  number[4][0][4] = true;
  number[4][0][5] = true;
  number[4][0][6] = true;
  number[4][0][7] = true;
  number[4][1][3] = true;
  number[4][2][4] = true;
  number[4][2][3] = true;
  number[4][2][2] = true;
  number[4][2][1] = true;
  number[4][2][0] = true;

  //Cinco
  number[5][0][0] = true;
  number[5][0][3] = true;
  number[5][0][4] = true;
  number[5][0][5] = true;
  number[5][0][6] = true;
  number[5][0][7] = true;
  number[5][1][0] = true;
  number[5][1][3] = true;
  number[5][1][7] = true;
  number[5][2][7] = true;
  number[5][2][3] = true;
  number[5][2][2] = true;
  number[5][2][1] = true;

  //Seis
  number[6][0][0]= true;
  number[6][0][1]= true;
  number[6][0][2]= true;
  number[6][0][3]= true;
  number[6][0][4]= true;
  number[6][0][5]= true;
  number[6][0][6]= true;
  number[6][1][0]= true;
  number[6][1][3]= true;
  number[6][1][7]= true;
  number[6][2][7]= true;
  number[6][2][3]= true;
  number[6][2][2]= true;
  number[6][2][1]= true;
  number[6][2][0]= true;

  //Siete
  number[7][0][7] = true;
  number[7][1][0] = true;
  number[7][1][1] = true;
  number[7][1][2] = true;
  number[7][1][3] = true;
  number[7][1][4] = true;
  number[7][1][7] = true;
  number[7][2][5] = true;
  number[7][2][6] = true;
  number[7][2][7] = true;

  //Ocho
  number[8][0][0] = true;
  number[8][0][1] = true;
  number[8][0][2] = true;
  number[8][0][3] = true;
  number[8][0][4] = true;
  number[8][0][5] = true;
  number[8][0][6] = true;
  number[8][0][7] = true;
  number[8][1][0] = true;
  number[8][1][3] = true;
  number[8][1][7] = true;
  number[8][2][0] = true;
  number[8][2][1] = true;
  number[8][2][2] = true;
  number[8][2][3] = true;
  number[8][2][4] = true;
  number[8][2][5] = true;
  number[8][2][6] = true;
  number[8][2][7] = true;

  //Nueve
  number[9][0][0] = true;
  number[9][0][3] = true;
  number[9][0][4] = true;
  number[9][0][5] = true;
  number[9][0][6] = true;
  number[9][0][7] = true;
  number[9][1][0] = true;
  number[9][1][3] = true;
  number[9][1][7] = true;
  number[9][2][1] = true;
  number[9][2][2] = true;
  number[9][2][3] = true;
  number[9][2][4] = true;
  number[9][2][5] = true;
  number[9][2][6] = true;
  number[9][2][7] = true;

}


/**
 * UTILS
 */

/**
 * This function is to set the time in the ds1307 chip.
 * No need to execute this every time.
 */
void setDateTime(){

  byte second =      00; //0-59
  byte minute =      31; //0-59
  byte hour =        19; //0-23
  byte weekDay =     1; //1-7
  byte monthDay =    19; //1-31
  byte month =       10; //1-12
  byte year  =       14; //0-99

  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));

  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekDay));
  Wire.write(decToBcd(monthDay));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));

  Wire.write(byte(0x00));

  Wire.endTransmission();

}

void animateIn( int num, int disp, int offset_x ){

  // Entrada desde abajo
  for(int i = -8; i <= 0; i++){
    paintArray(number[num], disp, offset_x, i);
    delay(10);
  }
}

void paintArray(bool array[8][8], int disp, int offset_x, int offset_y){

  for(int j = 0; j < 8; j++){
    for(int k = 0; k < 8; k++){
      if (array[j][k]){
        lc.setLed(disp, offset_x + j,offset_y + k,true);
      }else{
        lc.setLed(disp, offset_x + j,offset_y + k,false);
      }
    }
  }

}

byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}