// define as portas analógicas de 0 a 3 como as bananas 0 a 3
int banana0 = A0;
int banana1 = A1;
int banana2 = A2;
int banana3 = A3;

// a rotina de setup corre uma vez no início do programa e sempre que o butão reset é pressionado
void setup() {
  Serial.begin(9600);
  
  // define as bananas como portas INPUT_PULLUP
  pinMode(banana0, INPUT_PULLUP);
  pinMode(banana1, INPUT_PULLUP);
  pinMode(banana2, INPUT_PULLUP);
  pinMode(banana3, INPUT_PULLUP);
  pinMode(0,OUTPUT);
}

// a rotina loop corre infinitamente até que o o botão reset seja pressionado
void loop() {
  //  get readings from analog ports
  int reading0 = analogRead(banana0);
  int reading1 = analogRead(banana1);
  int reading2 = analogRead(banana2);
  int reading3 = analogRead(banana3);
  
  // Convert the analog readings (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage0 = reading0 * (5.0 / 1023.0);
  float voltage1 = reading1 * (5.0 / 1023.0);
  float voltage2 = reading2 * (5.0 / 1023.0);
  float voltage3 = reading3 * (5.0 / 1023.0);
  
  // check voltages to determine which banana was pressed and play tone associated with it
  if(voltage0 < 4.9){
    tone(10, 1000);
  }
  else if(voltage1 < 4.9){
    tone(10, 800);
  }
  else if(voltage2 < 4.9){
    tone(10, 600);
  }
  else if(voltage3 < 4.9){
    tone(10, 400);
  }
  else{
    noTone(10);
  }

  // print out the value you read:
  Serial.println(voltage0);
}
