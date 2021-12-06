/*----------------------
Workshop Arduino NEEC 2021
Jogo React
-----------------------/*

/*variáveis para butões*/
int button_p1 = 13;
int button_p2 = 2;

/*variáveis para leds de vida*/
int led_p1[] = {12, 11, 10};
int led_p2[] = {3, 4, 5};

/*variáveis para led rgb*/
int RGB_green = 7;
int RGB_blue = 8;
int RGB_red = 9;

/*variáveis de delay*/
int delay_max = 1000;
int delay_min = 300;
int delay_max_no_press = 900;
int delay_flash_init = 80;
int delay_end_flash = 100;

/* vidas de cada jogador */
int life_p1;
int life_p2;


/*-----------------------/setup()/----------------------*/
void setup() {
  
  // Input para os pins dos butões  
  pinMode(button_p1, INPUT);
  pinMode(button_p2, INPUT);

  // Output para os pins dos leds
  for(int i = 0; i < 3; i++) {
    pinMode(led_p1[i], OUTPUT);
    pinMode(led_p2[i], OUTPUT);
  }

  // Output para os pins do RGB
  pinMode(RGB_green, OUTPUT);
  pinMode(RGB_red, OUTPUT);
  pinMode(RGB_blue, OUTPUT);
  // Utilizar o valor de um pin analógico não utilizado para o randomize
  randomSeed(analogRead(A0));
}
/*-----------------------/setup()/----------------------*/

/*-----------------------/loop()/----------------------*/
void loop() {
  int winner;
  
  life_p1 = 3, life_p2 = 3;

  // Chamar função que inicializa o jogo
  Game_init();
  delay(delay_max);

  // Chamar função do jogo principal, a retornar o vencedor
  winner = MainGame();

  // Chamar funçao que acaba o jogo com a vitória de um player
  EndGame(winner);
  delay(delay_max);
}
/*-----------------------/loop()/----------------------*/

/*--------------------------------------------------
função de inicialização (LEDS A PISCAR)
---------------------------------------------------*/
void Game_init() {

  // Por três iterações (vezes)
  for(int j = 0; j < 3; j++) {

    // Piscar os leds (acender e apagar)
    // Apagar primeiro para ficarem as vidas "prontas"
    for(int i = 0; i < 3; i++) {
      digitalWrite(led_p1[i], LOW);
      digitalWrite(led_p2[i], LOW);
      delay(delay_flash_init);
    }
    
    for(int i = 0; i < 3; i++) {
      digitalWrite(led_p1[i], HIGH);
      digitalWrite(led_p2[i], HIGH);
      delay(delay_flash_init);
    }
  }
}

/*--------------------------------------------------
função principal para cada jogo
----------------------------------------------------*/
int MainGame() {
  int i = 2, j = 2, rand_led, winner, rand_delay, w_max;
  
  while(life_p1 != 0 && life_p2 != 0) {
     
    w_max = random(3, 10);
    
    for(int w = 0; w < w_max; w++) {
      rand_led = random(RGB_green, RGB_red + 1);
      digitalWrite(rand_led, HIGH);
      delay(50);
      digitalWrite(rand_led, LOW);
      delay(50);
    }
    
    rand_led = random(RGB_green, RGB_red + 1);
    digitalWrite(rand_led, HIGH);
    
    winner = Round_Judge(rand_led);
    digitalWrite(rand_led, LOW);
    
    
    if(winner == 1) {
      /* jogador 1 ganhou; jogador 2 perde 1 vida */
      digitalWrite(led_p2[i], LOW);
      i--;
    }

    else if(winner == 2) {
      /* jogador 2 ganhou; jogador 1 perde 1 vida */
      digitalWrite(led_p1[j], LOW);
      j--;
    }
    
    else if(winner == 3) {
      /* jogador 1 ganha 1 vida */
      if(j < 2) {
        j++;
        digitalWrite(led_p1[j], HIGH);
      }
    }
    
    else if(winner == 4) {
      /* jogador 2 ganha 1 vida */
      if(i < 2) {
        i++;
        digitalWrite(led_p2[i], HIGH);
      }
    }

    rand_delay = random(delay_min, delay_max);
    delay(rand_delay);
  }
  /* retorna sempre 1 ou 2 pois nao e fim do jogo se alguem ganhar 1 vida */
  return winner;
}


/*--------------------------------------------------
função que calcula o vencedor de cada ronda
----------------------------------------------------*/
int Round_Judge(int rand_led) {
  int over = 0, no_press = 0;
  int buttonState_p1, buttonState_p2, winner, no_press_limit;

  no_press_limit = random(500, delay_max_no_press);

  while(over == 0) {
    
    buttonState_p1 = digitalRead(button_p1);
    buttonState_p2 = digitalRead(button_p2);

    if(buttonState_p1 == HIGH) {
      
      if(rand_led == RGB_green) {
        life_p2--;
        winner = 1;
        over++;
      }
      else if(rand_led == RGB_red) {
        life_p1--;
        winner = 2;
        over++;
      }
      else if(rand_led == RGB_blue) {
       if(life_p1 < 3)
         life_p1++;
       winner = 3;
       over++;
      }
    }

    else if(buttonState_p2 == HIGH) {
      
      if(rand_led == RGB_green) {
        life_p1--;
        winner = 2;
        over++;
      }
      else if(rand_led == RGB_red) {
        life_p2--;
        winner = 1;
        over++;
      }
      else if(rand_led == RGB_blue) {
        if(life_p2 < 3)
          life_p2++;
        winner = 4;
        over++;
      }
    }

    else
      no_press++;

    
    if(no_press == no_press_limit) {
      winner = 0;
      over++;
    }

    /* truque ninja */
    delay(4);
  }

  return winner;
}


/*--------------------------------------------------
função para o pisca-pisca no final de cada jogo
---------------------------------------------------*/
void EndGame(int winner) {
  if(winner == 1) {
    for(int i = 0; i < 5; i++) {
      digitalWrite(led_p1[0], HIGH);
      digitalWrite(led_p1[1], HIGH);
      digitalWrite(led_p1[2], HIGH);
      delay(delay_end_flash);
      digitalWrite(led_p1[0], LOW);
      digitalWrite(led_p1[1], LOW);
      digitalWrite(led_p1[2], LOW);
      delay(delay_end_flash);
    }
  }
  else {
    for(int i = 0; i < 5; i++) {
      digitalWrite(led_p2[0], HIGH);
      digitalWrite(led_p2[1], HIGH);
      digitalWrite(led_p2[2], HIGH);
      delay(delay_end_flash);
      digitalWrite(led_p2[0], LOW);
      digitalWrite(led_p2[1], LOW);
      digitalWrite(led_p2[2], LOW);
      delay(delay_end_flash);
    }
  }
}


