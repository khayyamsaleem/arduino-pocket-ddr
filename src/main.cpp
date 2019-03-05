#include <Arduino.h>

const int allLEDs[] = {2,3,4,5,6,7,8,9};
const int gameLEDs[] = {5, 4, 3, 2};
const int levelLEDs[] = {9,8,7};
const int loseLED = 6;
const int buttons[] = {13, 12, 11, 10};

int gameState[4] = {0, 0, 0, 0};
int prevButtonState[4] = {0, 0, 0, 0};
int currButtonState[4] = {0, 0, 0, 0};

long levelTimes[8] = {2000L, 1500L, 1000L, 900L, 800L, 700L, 600L, 500L};
int currentLevel[3] = {0, 0, 0};

void setup(){
  Serial.begin(9600);
  pinMode(loseLED, OUTPUT);
  for (int i = 0; i < 4; i++){
    pinMode(gameLEDs[i], OUTPUT);
    if (i < 3){
      pinMode(levelLEDs[i], OUTPUT);
    }
    pinMode(buttons[i], INPUT);
  }
  randomSeed(analogRead(0));
}

void int2bin(unsigned num, int *rep){
  for(int i = 0; i < 3; i++){
    rep[i] = 0;
  }
  if (num > 7){
    return;
  }
  int i = 0;
  while(num > 0){
    rep[2-i] = num % 2;
    num /= 2;
    i++;
  }
}

void printArray(int *array, int length){
  Serial.print("[ ");
  for(int i = 0; i < length; ++i){
    Serial.print(array[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

int diffStates(int *prevState, int *currState){
  for (int i = 0; i < 4; i++){
    if (prevState[i] != currState[i]){
      return 1;
    };
  }
  return 0;
}

unsigned countOn(int *state){
  unsigned count = 0;
  for (unsigned i = 0; i < 4; i++){
    if (state[i]){
      count++;
    }
  }
  return count;
}

void clearState(int *state){
  for (int i = 0; i < 4; i++){
    state[i] = 0;
  }
}

void getButtonState(int *currState, unsigned long timeout){
  clearState(&currButtonState[0]);
  uint32_t start = millis();
  while(millis() - start < timeout){
    for(int i = 0; i < 4; ++i){
      if (!currState[i]) {
        currState[i] = digitalRead(buttons[i]);
      }
    }
  }
}

void clearLEDs(int *lit){
  for(int i = 0; i < 4; i++){
    lit[i] = 0;
    digitalWrite(gameLEDs[i], LOW);
  }
}

void setLevel(int num){
  int2bin(num, &currentLevel[0]);
  for(int i = 0; i < 3; i++){
    digitalWrite(levelLEDs[i], LOW);
    if (currentLevel[i]) {
      digitalWrite(levelLEDs[i], HIGH);
    }
  }
}

void lightLEDs(int *lit){
  long i = random(4);
  long j = random(4);
  while (i == j){
    j = random(4);
  };
  digitalWrite(gameLEDs[i], HIGH);
  digitalWrite(gameLEDs[j], HIGH);
  lit[i] = 1;
  lit[j] = 1;
}

void loop(){
  for (int i = 0; i < 8; i++){
    if (i == 0) {
      for(int j = 0; j < 10; j++){
        for(int k = 0; k < 8; k++){
          digitalWrite(allLEDs[k], HIGH);
        }
        delay(200);
        for(int k = 0; k < 8; k++){
          digitalWrite(allLEDs[k], LOW);
        }
        delay(200);
      }
    }
    setLevel(i);
    if(!diffStates(&gameState[0], &currButtonState[0])){
    } else {
      digitalWrite(loseLED, HIGH);
      clearLEDs(&gameState[0]);
      setLevel(0);
      delay(5000);
      digitalWrite(loseLED, LOW);
      for(int j = 0; j < 10; j++){
        digitalWrite(loseLED, HIGH);
        delay(200);
        digitalWrite(loseLED, LOW);
        delay(200);
      }
      i = -1;
    }
    clearLEDs(&gameState[0]);
  }
  for(int i = 0; i < 20; i++){
    for (int j = 0; j < 8; j++){
      digitalWrite(allLEDs[j], HIGH);
      delay(100);
      digitalWrite(allLEDs[j], LOW);
      delay(100);
    }
  }
}
