/**************************************************************************************
                                    3SC4P3 - MEMOIRE
                                    21/11/2019 - V1
                                    28/01/2023 - V2.1
                                    Florian HOFBAUER
***************************************************************************************/

/***********************************   REGLES  ****************************************

   Etape / N°       1           2           3           4
     1          2ème pos    2eme pos    3eme pos    4eme pos
     2          chiffre 4   M etape 1   1ere pos    M etape 1
     3          M etape 2   M etape 1   3eme pos    chiffre 4
     4          M etape 1   1ere pos    M etape 2   M etape 2
     5          M etape 1   M etape 2   M etape 4   M etape 3

***************************************************************************************/

int pinBouton[4] = {3, 4, 5, 6};
int pinLed [5] = {2, 7, 8, 9, 10}; //vert si correct, éteint sinon
int pinSeptSegments[7] = {14, 15, 16, 17, 18, 19, 20}; // Afficheur n° bouton + chiffre etape
int pinMasseSegments[5] = {21, 22, 23, 24, 25}; // Bouton 1 à 4 et chiffre étpae
int ordreBouton[4];
int chiffre[4]; // bouton qui correspond à chaque chiffre

int communication = {11};//pin de validation pour Master
int etatBouton[4];
int tirage[5] = {0, 0, 0, 0, 0};
int etapeBouton[5] = {0, 0, 0, 0, 0};//bouton de l etape
int etape = 0;
int wrong = 0;
int sommeEtatBouton; //etatbouton

void setup() {
  for (int i = 0; i < 4; i++)
  {
    pinMode(pinBouton[i], INPUT_PULLUP);
  }
  for (int i = 0; i < 5; i++)
  {
    pinMode(pinLed[i], OUTPUT);
    digitalWrite(pinLed[i], LOW);//LED off
    pinMode(pinMasseSegments[i], OUTPUT);
    digitalWrite(pinMasseSegments[i], HIGH);
  }
  for (int i = 0; i < 7; i++)
  {
    pinMode(pinSeptSegments[i], OUTPUT);
    digitalWrite(pinSeptSegments[i], LOW);//LED off
  }
  pinMode(communication, OUTPUT);
  digitalWrite(communication, LOW);
  randomSeed(analogRead(0));
  tirageRandom();
  boutonEtape(tirage[0], tirage[1], tirage[2], tirage[3], tirage[4]);
  delay(2500);
  fonctionEtatBouton();
}

void loop() {
  for (etape = 0; etape < 5; etape++) {
    affichageNumero();
    fonctionEtatBouton();
    while (sommeEtatBouton == 4) {
      delay(0);
      fonctionEtatBouton();
      affichageNumero();
    }
    if (digitalRead(pinBouton[etapeBouton[etape] - 1]) == 0) {
      digitalWrite(pinLed[etape], HIGH);
      delay(500);
    }
    else {
      etape = 0;
      delay(500);
    }
  }

  for (int i = 0; i < 5; i++) {
    digitalWrite(pinLed[i], LOW);//sortie des pin, LED éteintes
    digitalWrite(pinMasseSegments[i], HIGH);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(pinSeptSegments[i], LOW);//sortie des pin, LED éteintes
  }
  digitalWrite(communication, HIGH);
  delay(10000);
}

void boutonEtape(int nb0, int nb1, int nb2, int nb3, int nb4) {
  switch (nb0) {
    case 1:
      etapeBouton[0] = 2;
      break;
    case 2:
      etapeBouton[0] = 2;
      break;
    case 3:
      etapeBouton[0] = 3;
      break;
    case 4:
      etapeBouton[0] = 4;
      break;
    default:
      break;
  }
  switch (nb1) {
    case 1:
      etapeBouton[1] = chiffre[3];
      break;
    case 2:
      etapeBouton[1] = etapeBouton[0];
      break;
    case 3:
      etapeBouton[1] = 1;
      break;
    case 4:
      etapeBouton[1] = etapeBouton[0];
      break;
    default:
      break;
  }
  switch (nb2) {
    case 1:
      etapeBouton[2] = etapeBouton[1];
      break;
    case 2:
      etapeBouton[2] = etapeBouton[0];
      break;
    case 3:
      etapeBouton[2] = 3;
      break;
    case 4:
      etapeBouton[2] = chiffre[3];
      break;
    default:
      break;
  }
  switch (nb3) {
    case 1:
      etapeBouton[3] = etapeBouton[0];
      break;
    case 2:
      etapeBouton[3] = 1;
      break;
    case 3:
      etapeBouton[3] = etapeBouton[1];
      break;
    case 4:
      etapeBouton[3] = etapeBouton[1];
      break;
    default:
      break;
  }
  switch (nb4) {
    case 1:
      etapeBouton[4] = etapeBouton[0];
      break;
    case 2:
      etapeBouton[4] = etapeBouton[1];
      break;
    case 3:
      etapeBouton[4] = etapeBouton[3];
      break;
    case 4:
      etapeBouton[4] = etapeBouton[2];
      break;
    default:
      break;
  }
}

void tirageRandom() {
  tirage[0] = random(1, 5);
  tirage[1] = random(1, 5);
  tirage[2] = random(1, 5);
  tirage[3] = random(1, 5);
  tirage[4] = random(1, 5);
  for (int i = 0; i < 4; i++) {
    int value;
    boolean check = false;
    while (check == false) {
      value = random(1, 5);
      check = true;
      for (int j = 0; j < 4; j++) {
        if (value == ordreBouton[j]) {
          check = false;
        }
      }
    }
    ordreBouton[i] = value;
  }
  for (int t = 1; t < 5; t++) {
    for (int y = 0; y < 4; y ++) {
      if (ordreBouton[y] == t) {
        chiffre[t - 1] = y;
      }
    }
  }
}

void affichageNumero() {
  const int nombre[10][7] = {1, 1, 1, 1, 1, 1, 0,
                             0, 1, 1, 0, 0, 0, 0,
                             1, 1, 0, 1, 1, 0, 1,
                             1, 1, 1, 1, 0, 0, 1,
                             0, 1, 1, 0, 0, 1, 1,
                             1, 0, 1, 1, 0, 1, 1,
                             0, 0, 1, 1, 1, 1, 1,
                             1, 1, 1, 0, 0, 0, 0,
                             1, 1, 1, 1, 1, 1, 1,
                             1, 1, 1, 0, 0, 1, 1
                            };

  int affichage[5] = {ordreBouton[0], ordreBouton[1], ordreBouton[2], ordreBouton[3], tirage[etape]};

  for (int n = 0; n < 5; n++) {
    digitalWrite(pinMasseSegments[n], HIGH);
    for (int m = 0; m < 7; m++) {
      digitalWrite(pinSeptSegments[m], !nombre[affichage[n]][m]);
    }
    delay(5);
    digitalWrite(pinMasseSegments[n], LOW);
    delay(5);
  }
}

void fonctionEtatBouton() {
  etatBouton[0] = digitalRead(pinBouton[0]);
  etatBouton[1] = digitalRead(pinBouton[1]);
  etatBouton[2] = digitalRead(pinBouton[2]);
  etatBouton[3] = digitalRead(pinBouton[3]);
  sommeEtatBouton = etatBouton[0] + etatBouton[1] + etatBouton[2] + etatBouton[3];
  return sommeEtatBouton;
}

void pushReset() {
  int pin = 13;// active la broche en sortie (OUTPUT)
  pinMode(pin, OUTPUT);// Déactive le reset forçant la sortie au niveau bas
  digitalWrite(pin, LOW);
}
