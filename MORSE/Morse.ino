// Déclaration des différents tableaux utilisés
//String lettres[18] = {"A", "B", "C", "E", "F", "G", "H", "I", "K", "L", "M", "N", "O", "R", "S", "T", "V", "X"}; // Lettres utilisées pour coder le mot en morse
String mots[16] = {"SHELL", "HALLS", "SLICK", "TRICK", "BOXES", "LEAKS", "STROBE", "BISTRO", "FLICK", "BOMBS", "BREAK", "BRICK", "STEAK", "STING", "VECTOR", "BEATS"}; // Liste des 16 mots pouvant être utilisés et codés en morse
const byte etat[16] = {119, 127, 57, 63, 121, 113, 125, 118, 6, 30, 56, 115, 109, 62, 110, 91}; //Déclaration des lettres pouvant être entrées dans l'afficheur
char code[6] = {'D', 'D', 'D', 'D', 'D', 'D'}; // Tableau spécifique au mot codé afin de stocker les différentes lettres du mot code

// Déclaration des pin utilisés pour les différents composants
const int pinLeds[7] = {2, 3, 4, 5, 6, 7, 8}; // Déclaration des 7 leds de l'afficheur 7 segments
int pinLed = 9; // Led pour le mot en morse
int pinLedF = 11; // Led pour l'état du module
int pinBouton = 10; // Bouton pour l'afficheur

// Déclaration des différentes variables utiles au programme
int n = 0; // Variable désignant la colonne du tableau "mots", pour savoir le mot code
int taille = 0; // Variable pour le nombre de lettres dans le mot code
int unite = 0; //Variable associée à la lettre affichée sur l'afficheur 7 segments
int eb = 0; // Variable pour l'état du bouton
unsigned long t = 0; // Variable associée au temps afin de distinguer un appui court ou long du bouton

void setup()
{
  // Déclaration des différentes entrées et sorties et des états des leds
  pinMode(pinLed, OUTPUT);
  pinMode(pinLedF, OUTPUT);
  pinMode(pinBouton, INPUT_PULLUP);
  digitalWrite(pinLed, HIGH);
  digitalWrite(pinLedF, LOW);
  for (int i = 0; i < 7; i++) {
    pinMode(pinLeds[i], OUTPUT);
    digitalWrite(pinLeds[i], LOW);
  }
  Serial.begin(9600);
  // Définition du mot code
  randomSeed(analogRead(0));
  n = random(1, 17) - 1; // Nombre aléatoire qui définit quel est le mot code
  taille = mots[n].length(); // Définition du nombre de lettres dans le mot code
  for (int k = 0; k < taille + 1; k++) { // Boucle pour stocker les lettres du mot code dans un tableau
    code[k] = mots[n].charAt(k);
    Serial.println(code[k]);
  }
}

void loop()
{
  bouton();
  for (int i = 0; i < taille; i++) { // Boucle afin de pouvoir faire passer le mot code en morse avec la led selon les lettres qui sont stockées dans le tableau "code"
    switch (code[i]) {
      case 'A':
        A();
        break;
      case 'B':
        B();
        break;
      case 'C':
        C();
        break;
      case 'E':
        E();
        break;
      case 'F':
        F1();
        break;
      case 'G':
        G();
        break;
      case 'H':
        H();
        break;
      case 'I':
        I();
        break;
      case 'K':
        K();
        break;
      case 'L':
        L();
        break;
      case 'M':
        M();
        break;
      case 'N':
        N();
        break;
      case 'O':
        O();
        break;
      case 'R':
        R();
        break;
      case 'S':
        S();
        break;
      case 'T':
        T();
        break;
      case 'V':
        V();
        break;
      case 'X':
        X();
        break;
    }
  }
}

void afficher(int chiffre) { // Fonction pour afficher chaque lettre sur l'afficheur afin de valider ou non le mot code
  for (int j = 0; j < 7; j++) {
    digitalWrite(pinLeds[j], bitRead(etat[chiffre], j));
  }
}

void point() { // Fonction permettant de faire un point lors du codage du mot avec la led
  digitalWrite(pinLed, HIGH);
  for (int i = 0; i < 25; i++) {
    bouton();
    delay(10);
  }
  digitalWrite(pinLed, LOW);
  for (int i = 0; i < 25; i++) {
    bouton();
    delay(10);
  }
}

void trait() { // Fonction permettant de faire un trait lors du codage du mot avec la led
  digitalWrite(pinLed, HIGH);
  for (int i = 0; i < 80; i++) {
    bouton();
    delay(10);
  }
  digitalWrite(pinLed, LOW);
  for (int i = 0; i < 25; i++) {
    bouton();
    delay(10);
  }
}

// Toutes les fonctions permettant de coder en morse avec la led les différentes lettres possibles
void A() {
  point();
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void B() {
  trait();
  point();
  point();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void C() {
  trait();
  point();
  trait();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void E() {
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void F1() {
  point();
  point();
  trait();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void G() {
  trait();
  trait();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void H() {
  point();
  point();
  point();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void I() {
  point();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void K() {
  trait();
  point();
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}

void L() {
  point();
  trait();
  point();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void M() {
  trait();
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void N() {
  trait();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void O() {
  trait();
  trait();
  trait();
  //delay(1750);
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void R() {
  point();
  trait();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void S() {
  point();
  point();
  point();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void T() {
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void V() {
  point();
  point();
  point();
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}
void X() {
  trait();
  point();
  point();
  trait();
  for (int i = 0; i < 175; i++) {
    bouton();
    delay(10);
  }
}

void bouton() { // Fonction permettant de prendre d'analyser le temps d'appui du bouton pour soit incrémenter la lettre sur l'afficheur ou pour valider la lettre
  eb = digitalRead(pinBouton); // Définition de l'état du bouton
  if (!eb) {
    t = millis(); // Comptabilisation du temps d'appui du bouton
    Serial.println(t);
    eb = digitalRead(pinBouton);
    while (!eb) { // Boucle si le bouton est appuyé
      eb = digitalRead(pinBouton);
      if (millis() >= (t + 3000)) { // Appui long du bouton (3 secondes ou plus)
        if ((unite - 1 == n) || (unite == 0 && n == 15)) { // Conditions pour valider le module
          digitalWrite(pinLedF, HIGH);
          delay(100000);
        }
        else {
          for (int tuAsFaux = 0; tuAsFaux < 3; tuAsFaux++) {
            for (int k = 0; k < 7; k++) {
              digitalWrite(pinLeds[k], HIGH);
            }
            delay(100);
            for (int k = 0; k < 7; k++) {
              digitalWrite(pinLeds[k], LOW);
            }
            delay(100);
          }
        }
        unite=0;
      }
    }
    if (millis() < (t + 3000)) { // Appui court du bouton (moins de 3 secondes)
      afficher(unite); // Affichage de la lettre sur l'afficheur 7 segments
      unite = unite + 1;
      if (unite == 16) {
        unite = 0;
      }
    }
  }
}
