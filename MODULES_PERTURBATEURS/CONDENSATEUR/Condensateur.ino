#include <LiquidCrystal_I2C.h>
#include <Wire.h>


int l = 0; // Variables pour les boucles
int T = 100;
int T1 = 500; // Delays
int pinBouton = 2;
int etatBouton = 0;
LiquidCrystal_I2C ecran(0x27, 16,2); //Initialisation de l'Ecran
byte rect[8] = {
  B11111, 
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
}; // Tableau permettant de faire afficher un rectangle remplit.

void setup()
{
    ecran.init(); // Taille de l'écran
    ecran.backlight();
  ecran.createChar(5, rect);
  ecran.setCursor(0, 0);
  ecran.write((uint8_t) 0); // Test de l'écran au démarrage.
  ecran.setCursor(0, 1);
  ecran.write((uint8_t) 0); // Test de l'écran au démarrage.
  pinMode(pinBouton, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  while (l <= 16) { // Tant que le condensateur n'est pas chargé au maximum :
    ecran.setCursor(l, 0); // Déplacement en fonction de la valeur l de la charge du condensateur sur la première ligne.
    ecran.write(5);
    ecran.setCursor(l, 1); // Déplacement en fonction de la valeur l de la charge du condensateur sur la deuxième ligne.
    ecran.write(5);
    l += 1; // Augmentation de la valeur de l
    if (l == 17) {
     // return 0;
      etatBouton = digitalRead(pinBouton);
      while (etatBouton) {
        delay(10);
        etatBouton = digitalRead(pinBouton);
      }
    }
    for (int j = 0; j < 50; j++) { // Boucle avec un court délaie permettant de faciliter la detection de l'appuie du bouton.
      delay(100);
      etatBouton = digitalRead(pinBouton); // Lecture de l'état du bouton
      if (!etatBouton) { // Si il y a un appuie sur le bouton alors on décrémente l de 1.
        l -= 1;
        delay(T1);
        if (l == -1) { //Si l=-1 alors on garde l = 0
          l = 0;
        }
        ecran.clear(); //On remet à 0 l'écran
        for (int o = 0; o < l; o++) { //Puis on remet l'écran jusqu'à la valeur de l pour reprendre la boucle tant que.
          ecran.setCursor(o, 0);
          ecran.write(5);
          ecran.setCursor(o, 1);
          ecran.write(5);
        }
        delay(250);
      }
    }
  }
}
