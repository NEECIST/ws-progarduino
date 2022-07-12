/* including needed external libraries */

/* defining CONSTANT values */
#define MIN 1
#define MAX 8
#define DURATION 30
#define TARGETNUM 2 //number of sensors

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

}

/* THE LOOP runs in a PERMANENT MODE repeating it's code sequencially */
void loop() 
{

  /* if the 30 seconds elapsed show an end game animation */
  if(millis() - start_time >= DURATION * 1000)
  {
    /* turn on and off 3 times */
    for (j = 0; j < 3; j++)
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
      Serial.println(pontos); 
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
    //Serial.println(lux[i]); /* adjust sensors */
    lux[i] = analogRead(i);
  }

  /* if it was hit while available, register points*/  
  for (i = 0; i < TARGETNUM; i++)
  {
    if (lux[i] < 100 && led[i] == 1) //careful, the threshold may vary with the ldr
    {
      /* it was hit, so turn it off again */
      digitalWrite(i+2 , LOW);
      led[i] = 0;

      /* the state started now - millis */
      off_start[i] = millis();      
      /* with new random waiting time*/
      off_time[i] = random(MIN, MAX) * 1000;
      
      /* count points and log them to console */
      pontos += 1;
      Serial.println(pontos);
    }
  }
}
