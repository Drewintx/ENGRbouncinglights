#include <Adafruit_CircuitPlayground.h>

const int LButtonPin = 4;
const int RButtonPin = 5;
const int SwitchPin = 7;


volatile bool ButtonFlag;
volatile bool GameState;
volatile bool SwitchFlag;
volatile bool SwitchState;
volatile int ScorePressed;
volatile int CurrentLight;
volatile int Objective;
volatile int Score;
volatile int Highscore;
volatile int GameDelay;



void setup() {
  randomSeed(analogRead(A0));
  CircuitPlayground.begin();

  attachInterrupt(LButtonPin,scoringtime,RISING);
  attachInterrupt(RButtonPin,scoringtime,RISING);
  attachInterrupt(SwitchPin,switchflip,CHANGE);
}

void loop() {
  if (ButtonFlag == 1 && GameState == 0){
    StartGame();
  }
  if (GameState == 1){
    switch (SwitchState) {
      case 0:
            BaseGame();
      case 1:
            SpeedUp();
    }
  }

}

void StartGame(){
  GameDelay = 500;
  if (SwitchFlag == 1){
    SwitchState = !SwitchState;
  }
  Score = 0;
  ButtonFlag = 0;
  GameState = 1;
  Serial.print("gamestate =");
  Serial.println(GameState);
}

void EndGame(){


}

void BaseGame(){
  Objective = random (0,9);
  CircuitPlayground.setPixelColor(Objective,0,0,255);
  for (int i = 0, x = 1; i >= 0 && i <= 9; i = i+x){
      if (i != Objective){
      CircuitPlayground.setPixelColor(i,255,0,0);}
      Serial.println(i);
      if (i != Objective+x && i > 0){
      CircuitPlayground.setPixelColor(i-x,0,0,0);}
      if (ButtonFlag == 1){
        CurrentLight = i;
        break;}
      if (i == 9){x = -1;}
      if (i == 0){x = 1;}
      else {delay(GameDelay);}

  }
}

void SpeedUp(){
    
  Objective = random (0,9);
  CircuitPlayground.setPixelColor(Objective,0,0,255);
  for (int i = 0, x = 1; i >= 0 && i <= 9; i = i+x){
      if (i != Objective){
      CircuitPlayground.setPixelColor(i,255,0,0);}
      Serial.println(i);
      if (i != Objective+x && i > 0){
      CircuitPlayground.setPixelColor(i-x,0,0,0);}
      if (ButtonFlag == 1){
        CurrentLight = i;
        break;}
      if (i == 9){x = -1;}
      if (i == 0){x = 1;}
      else {delay(GameDelay);}



}
}


void scoringtime(){
  ButtonFlag = !ButtonFlag;
  Serial.print("button");
  Serial.println(ButtonFlag);
}

void switchflip(){
  SwitchFlag = !SwitchFlag;
}