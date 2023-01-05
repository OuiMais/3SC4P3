/*
  Programme  pour Escape Game
  22/11/2019 - /2019 Saint-Quentin
  Florian HOFBAUER
*/

/*
   1) Si le bouton est bleu et est marqué Abort, appuyer sur le bouton A, puis référez-vous à bandeau couleur
   2) Si le bouton est marqué Detonate, appuyer bouton B
   3) si bouton blanc et est marqué CAR, appuyer bouton A, puis référez-vous à bandeau couleur
   4) Si le bouton est marqué FRK, appuyer bouton B
   5) Si bouton jaune appuyer bouton A, puis référez-vous à bandeau couleur
   6) Si le bouton est rouge et est marqué Hold, appuyer bouton B
   7) Si aucun cas, appuyer bouton A, puis référez-vous à bandeau couleur

  Bandeau couleur
  Bande Bleu: appuyer bouton A
  Bande Blanche: appuyer bouton B
  Bande Jaune: appuyer bouton B
  Bande autre Couleur: appuyer bouton A
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int pinBouton[2] = {7, 8};
#define REDPIN 5//pin Rouge=5
#define GREENPIN 6//pin Vert=6
#define BLUEPIN 3//pin Bleu=3

LiquidCrystal_I2C screen(0x3F, 16, 2);

int nb[3] = {0, 0, 0}; //nb[0] = nb bouton, nb[1] = nb bandeau, nb[2] = char
int couleurBandeau[7][3] = {0  , 0  , 255,//bleu
                            255, 255, 255,//blanc
                            255, 255, 0  ,//jaune
                            255, 0  , 0  ,//rouge
                            0  , 255, 0  ,//vert
                            255, 0  , 255,//rose
                            0  , 255, 255//turquoise
                           };
int couleurBouton[7][3] = {0  , 0  , 255,//bleu
                           255, 255, 255,//blanc
                           255, 255, 0  ,//jaune
                           255, 0  , 0  ,//rouge
                           0  , 255, 0  ,//vert
                           255, 0  , 255,//rose
                           0  , 255, 255//turquoise
                          };
char mot[5] = {'ABORT', 'DETONATE', 'CAR', 'FRK', 'HOLD'};
int wrong = 0;
int communication = {11};//pin de validation pour Master
int b1, b2, eB;
int colorR, colorG, colorB;

void setup() {
  randomSeed(analogRead(0));
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  for (int i = 0; i < 2; i++)
  {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }
  pinMode(communication, OUTPUT);
  digitalWrite(communication, LOW);
  ranDomNombre();
  etatBouton();
  screen.begin(16, 2);
  colorR = couleurBouton[nb[0] - 1][0];
  colorG = couleurBouton[nb[0] - 1][1];
  colorB = couleurBouton[nb[0] - 1][2];
 // screen.setRGB(colorR, colorG, colorB);
  screen.init();
  screen.backlight();
  screen.setCursor(0, 1);
  screen.print(mot[nb[2] - 1]);
}

void loop() {
  if (nb[0] == 1 && nb[2] == 1) {//bouton bleu + ABORT
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[0]) == 0) {
      delay(500);
      couleurFixeBandeau();
      if (nb[1] == 1) {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 2) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 3) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      else {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
    }
    else {
      wrong += 1;
    }
  }
  if (nb[2] == 2) {//bouton detonate
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[1]) == 0) {
      screen.print("WINNER");
      delay(1000);
      digitalWrite(communication, HIGH);
    }
    else {
      wrong += 1;
    }
  }
  if (nb[0] == 2 && nb[2] == 3) {//bouton blanc et CAR
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[0]) == 0) {
      delay(500);
      couleurFixeBandeau();
      if (nb[1] == 1) {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 2) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 3) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      else {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
    }
    else {
      wrong += 1;
    }
  }
  if (nb[2] == 4) {//bouton FRK
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[1]) == 0) {
      screen.print("WINNER");
      delay(1000);
      digitalWrite(communication, HIGH);
    }
    else {
      wrong += 1;
    }
  }
  if (nb[0] == 3) {//bouton jaune
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[0]) == 0) {
      delay(500);
      couleurFixeBandeau();
      if (nb[1] == 1) {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 2) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 3) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      else {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
    }
    else {
      wrong += 1;
    }
  }
  if (nb[0] == 4 && nb[2] == 5) {//bouton rouge et HOLD
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[1]) == 0) {
      screen.print("WINNER");
      delay(1000);
      digitalWrite(communication, HIGH);
    }
    else {
      wrong += 1;
    }
  }
  else {//autre cas
    etatBouton();
    while (eB == 2) {
      delay(0);
      etatBouton();
    }
    if (digitalRead(pinBouton[0]) == 0) {
      delay(500);
      couleurFixeBandeau();
      if (nb[1] == 1) {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 2) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      if (nb[1] == 3) {
        if (digitalRead(pinBouton[1]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
      else {
        if (digitalRead(pinBouton[0]) == 0) {
          screen.print("WINNER");
          delay(1000);
          digitalWrite(communication, HIGH);
        }
        else {
          wrong += 1;
        }
      }
    }
    else {
      wrong += 1;
    }
  }
  if (wrong == 1) {
    screen.print("YOU LOOSE, RESTART");
    delay(3000);
    pushReset();
  }
}

void ranDomNombre() {
  nb[0] = random(1, 8);
  nb[1] = random(1, 8);
  nb[2] = random(1, 6);
}

void etatBouton() {
  b1 = digitalRead(pinBouton[0]);
  b2 = digitalRead(pinBouton[1]);
  eB = b1 + b2;
  return eB;
}

void couleurFixeBandeau() {
  int red, blue, green;
  red = couleurBandeau[nb[1] - 1][0];
  green = couleurBandeau[nb[1] - 1][1];
  blue = couleurBandeau[nb[1] - 1][2];
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);
  analogWrite(REDPIN, red);
}

void pushReset() {
  int pin = 12;
  pinMode(pin, OUTPUT);// active la broche en sortie (OUTPUT)
  digitalWrite(pin, LOW);// Déactive le reset forçant la sortie au niveau bas
}
