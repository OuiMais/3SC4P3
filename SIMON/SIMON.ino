/*
    Projet : 3SC4P3 / SIMON
    Date Creation : 29/10/2019
    Date Revision : 28/08/2023
    Entreprise : 3SC4P3
    Auteur: Florian HOFBAUER
    Contact : 
    But : Code du module SIMON seul
*/

int pinBouton[4] = {6, 7, 8, 9}; //4 boutons couleurs //bouton[1] = boutonRouge;bouton[2] = boutonBleu;bouton[3] = boutonVert;bouton[4] = boutonJaune;
int pinLed[4] = {2, 5, 4, 3};//4 leds de couleurs diff //ledVerte = pinLed[1];ledRouge = pinLed[2];ledBleu = pinLed[3];ledJaune = pinLed[4];
int b1, b2, b3, b4, eB, tour;
int wrong = 0;
int perteTps = 12;
int communication = {11};//pin de validation pour Master
int nb[5] = {0, 0, 0, 0, 0};
int etape = 0;

void setup() {
  Serial.begin(9600);
  pinMode(perteTps, OUTPUT);
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }
  pinMode(communication, OUTPUT);
  digitalWrite(communication, LOW);

  for (int i = 0; i < 4; i++)
  {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], LOW);//LED off
  }
  randomSeed(analogRead(0));
  ranDomNombre();
  etatBouton();
}

void loop() {
  etatBouton();
  while (eB == 4) {
    delay(0);
    etatBouton();
  }
  for (etape = 1; etape < 6; etape++) {
    if (wrong == 0) {
      Serial.println(wrong);
      aucuneFaute(etape);
    }
    if (wrong == 1) {
      Serial.println(wrong);
      uneFaute(etape);
    }
    if (wrong == 2) {
      Serial.println(wrong);
      deuxFautes(etape);
    }
    if (wrong == 3) {
      delay(3000);
      pushReset();
    }
  }
  Serial.println("GGGGGGGGGGGGG");
  digitalWrite(communication, HIGH);
}

void aucuneFaute(int etape) {
  for (int l = 0; l < etape; l++) {
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], HIGH);
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], LOW);
  }
  for (tour = 0; tour < etape; tour++) {
    if (nb[tour] == 1) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[3]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 2) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[1]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 3) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[0]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 4) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[2]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
  }
}

void uneFaute(int etape) {
  for (int l = 0; l < etape; l++) {
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], HIGH);
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], LOW);
  }
  for (tour = 0; tour < etape; tour++) {
    if (nb[tour] == 1) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[1]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 2) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[3]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 3) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[2]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 4) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[0]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
  }
}

void deuxFautes(int etape) {
  for (int l = 0; l < etape; l++) {
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], HIGH);
    delay(1000);
    digitalWrite(pinLed[nb[l] - 1], LOW);
  }
  for (tour = 0; tour < etape; tour++) {
    if (nb[tour] == 1) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[3]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 2) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[2]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 3) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[0]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
    if (nb[tour] == 4) {
      etatBouton();
      while (eB == 4) {
        delay(0);
        etatBouton();
      }
      if (digitalRead(pinBouton[1]) == 0) {
        delay(500);
      }
      else {
        wrong += 1;
        break;
      }
    }
  }
}

void ranDomNombre() {
  nb[0] = random(1, 5);
  nb[1] = random(1, 5);
  nb[2] = random(1, 5);
  nb[3] = random(1, 5);
  nb[4] = random(1, 5);
  for(int h=0;h<4;h++){
    Serial.println(nb[h]);
  }
}

void etatBouton() {
  b1 = digitalRead(pinBouton[0]);
  b2 = digitalRead(pinBouton[1]);
  b3 = digitalRead(pinBouton[2]);
  b4 = digitalRead(pinBouton[3]);
  eB = b1 + b2 + b3 + b4;
  return eB;
}

void pushReset() {
  int pin = 13;
  digitalWrite(perteTps, HIGH);
  delay(10);
  pinMode(pin, OUTPUT);// active la broche en sortie (OUTPUT)
  digitalWrite(pin, LOW);// Déactive le reset forçant la sortie au niveau bas
}
