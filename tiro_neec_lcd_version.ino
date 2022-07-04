//Esta é a versão que se mete no nosso Tir'ó NEEC (o mais bonitinho).
//Dá para dar fine tune da sensibilidade de cada LDR separadamente.

/* including needed external libraries */
#include <LiquidCrystal_I2C.h> //must be installed externally from: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <Wire.h>

//initialize lcd 
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* defining CONSTANT values */
#define MIN 1
#define MAX 8
#define DURATION 30 //the game lasts 30 seconds
#define TARGETNUM 4 //number of sensors

/* GLOBAL variables declaration */

/* and variables to our game functioning*/
/* declare timer variables */
long off_time[TARGETNUM] = {0}, off_start[TARGETNUM] = {0}, start_time; 
/* auxiliary */
int i, j, pontos = 0;
/* led and sensor state */
int led[TARGETNUM] = {0}, lux[TARGETNUM] = {0};

/* THE SETUP only runs ONCE when the arduino starts */
void setup()
{
  /* for serial communication */
  Serial.begin(9600); // https://www.arduino.cc/en/serial/begin
  /* to provide random seed with NOISE from an unused analog */
  randomSeed(analogRead(5)); // https://en.wikipedia.org/wiki/Random_seed
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Tir'o NEEC");

  /* to set pins as INPUTS for sensors and OUTPUTS for leds */
  // NOTE: making it more scalable don't use the ledsets
  for(i=0; i<TARGETNUM; i++)
    pinMode(i+2,OUTPUT); // digital 1 and 0 are for serial
  

  /* set initial states */
  for(i=0; i<TARGETNUM; i++)
  {
    /* all leds are stated to be off */
    led[i] = 0;
    digitalWrite(i+2 , LOW);
    /* and the state started now - millis */
    off_start[i] = millis();
    /* until a random decided value */
    off_time[i] = random(MIN, MAX) * 1000; //Defines off time for the LED
  }
  /* the game started now */
  start_time = millis();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Tir'o NEEC");

}

/* THE LOOP runs in a PERMANENT MODE repeating it's code sequencially */
void loop() 
{

  /* if the 30 seconds elapsed show an end game animation */
  if(millis() - start_time >= DURATION * 1000)
  {
    /* turn on and off 3 times */
    for (j = 0; j < 3; ++j)
    {
      for(i=0;i<TARGETNUM;i++)
        digitalWrite(i+2 , HIGH);
      delay(100);
      for(i=0;i<TARGETNUM;i++)
        digitalWrite(i+2 , LOW);
      delay(100);
    }
    /* and wait for game reset with some passive waiting */
    while(1)
    {
      Serial.print("Final score: ");  Serial.println(pontos); 
      delay(DURATION*1000);
    }
  }

  /* if leds timer has finished, turn them on! */
  for (i = 0; i < TARGETNUM; i++)
  {
    if (led[i] == 0 && millis() - off_start[i] >= off_time[i])
    {
      digitalWrite(i+2 , HIGH);
      led[i] = 1;
    }
  }

  /* check if sensor was hit by laser */
  for (i = 0; i < TARGETNUM; i++)
  {
    /*NOTE: while analogRead(A0) is more correct, analogRead(0) translates to read from A0 */
    //Serial.println(lux[3]); /* adjust sensors */
    lux[i] = analogRead(i);
    //Serial.print(lux[i]);
  }
  //Serial.print(lux[0]);Serial.print("\t");Serial.print(lux[1]);Serial.print("\t");Serial.print(lux[2]);Serial.print("\t");Serial.print(lux[3]);Serial.println();
  /* if it was hit while available, register points*/  
  //for (i = 0; i < TARGETNUM; i++)
  //{
    //blue target
    if (lux[0] > 820 && led[0] == 1)
    {
      /* it was hit, so turn it off again */
      digitalWrite(2 , LOW);
      led[0] = 0;

      /* the state started now - millis */
      off_start[0] = millis();      
      /* with new random waiting time*/
      off_time[0] = random(MIN, MAX) * 1000;
      
      /* count points and log them to console */
      pontos += 1;
      printPontos(pontos);
    }
    //green target
    if (lux[1] > 820 && led[1] == 1)
    {
      /* it was hit, so turn it off again */
      digitalWrite(3 , LOW);
      led[1] = 0;

      /* the state started now - millis */
      off_start[1] = millis();      
      /* with new random waiting time*/
      off_time[1] = random(MIN, MAX) * 1000;
      
      /* count points and log them to console */
      pontos += 1;
      printPontos(pontos);
    }
    //red target
    if (lux[2] > 780 && led[2] == 1)
    {
      /* it was hit, so turn it off again */
      digitalWrite(4 , LOW);
      led[2] = 0;

      /* the state started now - millis */
      off_start[2] = millis();      
      /* with new random waiting time*/
      off_time[2] = random(MIN, MAX) * 1000;
      
      /* count points and log them to console */
      pontos += 1;
      printPontos(pontos);
    }
    //yellow target
    if (lux[3] > 700 && led[3] == 1)
    {
      /* it was hit, so turn it off again */
      digitalWrite(5 , LOW);
      led[3] = 0;

      /* the state started now - millis */
      off_start[3] = millis();      
      /* with new random waiting time*/
      off_time[3] = random(MIN, MAX) * 1000;
      
      /* count points and log them to console */
      pontos += 1;
      printPontos(pontos);
    }
  //}
}

void printPontos(int pontos){
  if(pontos==10){
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Tir'o NEEC");
  }
  lcd.setCursor(7,1);
  lcd.print(pontos);
  Serial.println(pontos);
}
