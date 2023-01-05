/**************************************************************************************
                                    3SC4P3 - BOUTON
                                    22/11/2019 - V1
                                    05/01/2023 - V2.1
                                    Florian HOFBAUER
***************************************************************************************/

/***********************************   REGLES  ****************************************

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

***************************************************************************************/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int pinBouton[2] = {7, 8}; // Bouton A et Bouton B

int pinBandeauRouge = 3, pinBandeauVert = 5, pinBandeauBleu = 6;

LiquidCrystal_I2C screen(0x3F, 16, 2);

int tirage[3] = {0, 0, 0}; //tirage[0] = tirage couleur bouton, tirage[1] = tirage couleur bandeau, tirage[2] = tirage mot

int couleurBandeau[7][3] = {0  , 0  , 255,  //bleu
                            255, 255, 255,  //blanc
                            255, 255, 0  ,  //jaune
                            255, 0  , 0  ,  //rouge
                            0  , 255, 0  ,  //vert
                            255, 0  , 255,  //rose
                            0  , 255, 255   //turquoise
                           };

int couleurBouton[7][3] =  {0  , 0  , 255,  //bleu
                            255, 255, 255,  //blanc
                            255, 255, 0  ,  //jaune
                            255, 0  , 0  ,  //rouge
                            0  , 255, 0  ,  //vert
                            255, 0  , 255,  //rose
                            0  , 255, 255   //turquoise
                           };

char mot[5] = {'ABORT', 'DETONATE', 'CAR', 'FRK', 'HOLD'};

int wrong = 0;

int communication = {11}; //pin de validation pour Master

int etatBoutonA, etatBoutonB, sommeEtatBouton;

int couleurRouge, couleurVert, couleurBleu;

void setup() {
  randomSeed(analogRead(0));

  pinMode(pinBandeauRouge, OUTPUT);
  pinMode(pinBandeauVert, OUTPUT);
  pinMode(pinBandeauBleu, OUTPUT);

  for (int i = 0; i < 2; i++)
  {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }

  pinMode(communication, OUTPUT);

  digitalWrite(communication, LOW);

  tirageRandom();
  etatBouton();
  screen.begin(16, 2);
  screen.init();
  screen.backlight();

  screen.setCursor(0, 1);
  screen.print(mot[tirage[2] - 1]);

  // Le bouton est remplacé par un écran LCD qui peux changer de couleur
  // Ici on met l'écran en couleur
  couleurRouge = couleurBouton[tirage[0] - 1][0];
  couleurVert = couleurBouton[tirage[0] - 1][1];
  couleurBleu = couleurBouton[tirage[0] - 1][2];
  // screen.setRGB(couleurRouge, couleurVert, couleurBleu);
}

void loop() {
  if (tirage[0] == 1 && tirage[2] == 1) {  //bouton bleu + ABORT
    attenteAppui();
    if (!etatBoutonA) {
      delay(500);
      refererBandeau();
    } else {
      wrong += 1;
    }
  }
  if (tirage[2] == 2) {                    //bouton detonate
    attenteAppui();
    if (!etatBoutonB) {
      winner();
    }
    else {
      wrong += 1;
    }
  }
  if (tirage[0] == 2 && tirage[2] == 3) {  //bouton blanc et CAR
    attenteAppui();
    if (!etatBoutonA) {
      delay(500);
      refererBandeau();
    }
    else {
      wrong += 1;
    }
  }
  if (tirage[2] == 4) {                    //bouton FRK
    attenteAppui();
    if (!etatBoutonB) {
      winner();
    }
    else {
      wrong += 1;
    }
  }
  if (tirage[0] == 3) {                    //bouton jaune
    attenteAppui();
    if (!etatBoutonA) {
      delay(500);
      refererBandeau();
    }
    else {
      wrong += 1;
    }
  }
  if (tirage[0] == 4 && tirage[2] == 5) {  //bouton rouge et HOLD
    attenteAppui();
    if (!etatBoutonB) {
      winner();
    }
    else {
      wrong += 1;
    }
  }
  else {                                   //autre cas
    attenteAppui();
    if (!etatBoutonA) {
      delay(500);
      refererBandeau();
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

void tirageRandom() {
  tirage[0] = random(1, 8);
  tirage[1] = random(1, 8);
  tirage[2] = random(1, 6);
}

void etatBouton() {
  etatBoutonA = digitalRead(pinBouton[0]);
  etatBoutonB = digitalRead(pinBouton[1]);
  sommeEtatBouton = etatBoutonA + etatBoutonB;
  return sommeEtatBouton;
}

void attenteAppui() {
  etatBouton();
  while (sommeEtatBouton == 2) {
    delay(1);
    etatBouton();
  }
}

void winner() {
  screen.print("WINNER");
  delay(1000);
  digitalWrite(communication, HIGH);
  delay(60000);
}

void refererBandeau() {
  couleurFixeBandeau();
  switch (tirage[1]) {
    case 1:
      attenteAppui();
      if (!etatBoutonA) {
        winner();
      } else {
        wrong += 1;
      }
      break;
    case 2:
      attenteAppui();
      if (!etatBoutonB) {
        winner();
      } else {
        wrong += 1;
      }
      break;
    case 3:
      attenteAppui();
      if (!etatBoutonB) {
        winner();
      } else {
        wrong += 1;
      }
      break;
    default:
      attenteAppui();
      if (!etatBoutonA) {
        winner();
      } else {
        wrong += 1;
      }
      break;
  }
}

void couleurFixeBandeau() {
  int red, blue, green;
  red = couleurBandeau[tirage[1] - 1][0];
  green = couleurBandeau[tirage[1] - 1][1];
  blue = couleurBandeau[tirage[1] - 1][2];
  analogWrite(pinBandeauVert, green);
  analogWrite(pinBandeauBleu, blue);
  analogWrite(pinBandeauRouge, red);
}

void pushReset() {
  int pin = 12;
  pinMode(pin, OUTPUT);// active la broche en sortie (OUTPUT)
  digitalWrite(pin, LOW);// Déactive le reset forçant la sortie au niveau bas
}
