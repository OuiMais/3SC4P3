/*
  Programme MEMOIRE pour 3SC4PE
  21/10/2019 - 20/11/2019 Saint-Quentin
  Florian HOFBAUER
*/

#include <LiquidCrystal_I2C.h>

int pinBouton[4] = {3, 4, 5, 6};
int pinLed [5] = {2, 7, 8, 9, 10};//vert si correct, éteint sinon
int communication = {11};//pin de validation pour Master
int perteTps = {12};//pin perte de temps unique sur Master
int bouton[4];
int nb[5] = {0, 0, 0, 0, 0};
int e[5] = {0, 0, 0, 0, 0};//bouton de l etape
int etape = 0;
int wrong = 0;
int eB; //etatbouton

LiquidCrystal_I2C screen(0x3F, 16, 2);

void setup() {
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 5; i++)
  {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], LOW);//LED off
  }
  pinMode(communication, OUTPUT);
  digitalWrite(communication, LOW);
  randomSeed(analogRead(0));
  ranDomNombre();
  int nb0 = nb[0];
  int nb1 = nb[1];
  int nb2 = nb[2];
  int nb3 = nb[3];
  int nb4 = nb[4];
  etape1(nb0,nb1,nb2,nb3,nb4);
  screen.init();
  screen.backlight();
  screen.setCursor(5,0);
  screen.print("BONJOUR");
  delay(2500);
  etatBouton();
  screen.clear();
}

void loop() {
  for (etape = 0; etape < 5; etape++) {
    screen.setCursor(8,0);
    screen.print(nb[etape]);
    etatBouton();
    while (eB == 4) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[e[etape]-1]) == 0) {
      digitalWrite(pinLed[2*etape], HIGH);
      delay(500);
    }
    else {
      wrong = wrong + 1;
      delay(500);
    }
    if (wrong == 2){
      screen.clear();
      screen.setCursor(4,0);
      screen.print("YOU LOOSE");
      screen.setCursor(5,1);
      screen.print("RESTART");
      delay(10000);
      pushReset();
    }
    screen.setCursor(0,0);
    screen.print("->");
    delay(1000);
    screen.clear();
  }
  if (wrong == 1) {
    screen.clear();
    screen.print("YOU LOOSE 10 MIN");
    screen.setCursor(4,1);
    screen.println("GOOD LUCK");
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(pinLed[i], LOW);
    }
    digitalWrite(perteTps, HIGH);
    delay(100);
    digitalWrite(perteTps, LOW);
    delay(100);
    digitalWrite(communication, HIGH);
  }
  if (wrong == 0) {
    screen.clear();
    screen.setCursor(5,0);
    screen.print("YOU WIN");
    for (int i = 0; i < 10; i++)
    {
      digitalWrite(pinLed[i], LOW);//sortie des pin, LED éteintes
    }
    digitalWrite(communication, HIGH);
  }
  delay(10000);
}

void etape1(int nb0, int nb1, int nb2, int nb3, int nb4) {
  if (nb0 == 1) {
    e[0] = 2;
  }
  if (nb0 == 2) {
    e[0] = 2;
  }
  if (nb0 == 3) {
    e[0] = 3;
  }
  if (nb0 == 4) {
    e[0] = 4;
  }
  if (nb1 == 1) {
    e[1] = 4;
  }
  if (nb1 == 2) {//meme bouton que etape 1
    e[1] = e[0];
  }
  if (nb1 == 3) {
    e[1] = 1;
  }
  if (nb1 == 4) {//meme bouton que etape 1
    e[1] = e[0];
  }
  if (nb2 == 1) {//meme bouton que etape 2
    e[2] = e[1];
  }
  if (nb2 == 2) {//meme bouton que etape 1
    e[2] = e[0];
  }
  if (nb2 == 3) {
    e[2] = 3;
  }
  if (nb2 == 4) {
    e[2] = 4;
  }
  if (nb3 == 1) {//meme bouton que etape 1
    e[3] = e[0];
  }
  if (nb3 == 2) {
    e[3] = 1;
  }
  if (nb3 == 3) {//meme bouton que etape 2
    e[3] = e[1];
  }
  if (nb3 == 4) {//meme bouton que etape 2
    e[3] = e[1];
  }
  if (nb4 == 1) {//meme bouton que etape 1
    e[4] = e[0];
  }
  if (nb4 == 2) {//meme bouton que etape 2
    e[4] = e[1];
  }
  if (nb4 == 3) {//meme bouton que etape 4
    e[4] = e[3];
  }
  if (nb4 == 4) {//meme bouton que etape 3
    e[4] = e[2];
  }
}

void ranDomNombre() {
  nb[0] = random(1, 5);
  nb[1] = random(1, 5);
  nb[2] = random(1, 5);
  nb[3] = random(1, 5);
  nb[4] = random(1, 5);
}

void etatBouton() {
  bouton[0] = digitalRead(pinBouton[0]);
  bouton[1] = digitalRead(pinBouton[1]);
  bouton[2] = digitalRead(pinBouton[2]);
  bouton[3] = digitalRead(pinBouton[3]);
  eB = bouton[0] + bouton[1] + bouton[2] + bouton[3];
  return eB;
}

void pushReset() {
  int pin = 13;// active la broche en sortie (OUTPUT)
  pinMode(pin, OUTPUT);// Déactive le reset forçant la sortie au niveau bas
  digitalWrite(pin, LOW);
}
