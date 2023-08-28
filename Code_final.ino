/*
    Projet : 3SC4P3
    Date Creation : 29/10/2019
    Date Revision : 28/08/2023
    Entreprise : 3SC4P3
    Auteur: Florian HOFBAUER
    Contact : 
    But : Fichier principal
*/

// Déclaration des différentes bilbiothèques utilisées
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Déclaration des différents pin utilisés
int pinBouton = 2; // Bouton incrémentation
int pinBouton2 = 3; // Bouton changement de case sur l'écran LCD
int pinBoutonF = 5; // Bouton de validation du module 
int pinLed = 4; // Led d'état du module 
LiquidCrystal_I2C ecran(0X27, 16, 2); // Ecran LCD

int Final[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // Tableau stockant les chiffres affichés sur l'écran LCD
// Les 5 lettres associées au code final à retrouver
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int eb = 0; // Etat du premeir bouton
int ebs = 0; // Etat du second bouton
int ebf = 0; // Etat du troisième bouton
int p = 0; // Variable associée à la colonne sur l'écran LCD
int chiffre = 0; // Chiffre affiché sur l'écran

void setup() {
  // Déclaration des entrées et sorties et de l'état de la led
  pinMode(pinBouton, INPUT_PULLUP);
  pinMode(pinBouton2, INPUT_PULLUP);
  pinMode(pinBoutonF, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, HIGH);
  randomSeed(analogRead(0));
  // Le mot code est créé de façon aléatoire et est composé de 7 chiffres 
  a = random(0, 10);
  b = random(0, 10);
  c = random(0, 10);
  d = random(0, 10);
  e = random(0, 10);
  f = random(0, 10);
  g = random(0, 10);
  Serial.begin(9600);
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  Serial.println(e);
  Serial.println(f);
  Serial.println(g);
  // Déclarationd des différents paramètres de l'écran LCD
  ecran.init();
  ecran.backlight();
  ecran.setCursor(6, 0);
  delay(10);
  Serial.begin(9600);
  delay(10);
  ecran.clear();
  for (int k = 0; k < 1; k++) {
    defiler();
  }
  ecran.setCursor(0, 0);
  ecran.print(chiffre);
}

void loop() {
  changement();
  nombre();
  validation();
}

void defiler() { // Fonction permettant de faire défiler le nombre code sur l'écran 
  for (int i = 0; i < 17; i++) {
    ecran.clear();
    ecran.setCursor(i, 0);
    ecran.print(a);
    ecran.leftToRight();
    ecran.print(b);
    ecran.print(c);
    ecran.print(d);
    ecran.print(e);
    ecran.print(f);
    ecran.print(g);
    delay(150);
    ecran.clear();
    delay(400);
  }
}

void changement() { // Fonction permettant de changer la place du curseur sur l'écran
  ebs = digitalRead(pinBouton2); // Lecture de l'état du second bouton
  if (!ebs) { // Si l'état a changé
    ebs = digitalRead(pinBouton2);
    p = p + 1; // Incrémentation de 1 pour la variable associée à la case de l'écran sur laquelle est affichée le chiffre
    Final[p] = chiffre; // Sauvegarde du chiffre avant le changement de case
    chiffre = -1; // Remise à 0 du chiffre pour la prochaine case
    delay(1000);
  }
}

void nombre() { // Fonction permettant d'afficher le nombre voulu sur la case de l'écran LCD
  eb = digitalRead(pinBouton); // Lecture de l'état du premier bouton
  if (!eb) { // Si 'létat a changé
    eb = digitalRead(pinBouton);
    ebs = digitalRead(pinBouton2); // Lecture de l'état du second bouton
    if (!ebs) { // Si l'état du second bouton a changé, la fonction continue mais sur la case d'après
      changement();
    }
    chiffre = chiffre + 1; // Incrémentation du chiffre affiché à l'écran
    delay(250);
    if (chiffre == 10) {
      chiffre = 0;
    }
    ecran.clear();
    ecran.setCursor(p, 0);
    ecran.print(chiffre);
  }
}

void validation() { // Fonction de validation du module
  ebf = digitalRead(pinBoutonF); // Lecture de l'état du troisième bouton
  if (!ebf) { // Si l'état a changé
    if ((a == Final[1]) && (b == Final[2]) && (c == Final[3]) && (d == Final[4]) && (e == Final[5]) && (f == Final[6]) && (g == Final[7])) { // Conditions afin de valider ou non le module 
      digitalWrite(pinLed, LOW);
    }
    else { // Si les conditions ne sont pas respectées
      for (int k = 0; k < 8; k++) { // Remise à 0 du tableau sauvegardant les nombres entrés par l'utilisateur
        Final[k] = 0;
      }
      p = 0; // Retour à la première case de l'écran 
      ecran.clear();
      ecran.setCursor(0, 0);
      chiffre = 0;
      ecran.print(chiffre);
    }
  }
}
