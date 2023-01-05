//Séquence de fils, il y a une plaque avec 6 bornes: A,B,C,1,2,3 et il faudra se servir de la fonction Stringcompare
const int sortielettre[3][7]={                      //Tableau contenant la liste des LEDs qui doivent être allumés pour former les lettes
  {1,1,1,0,1,1,1},  //A
  {0,0,1,1,1,1,1},  //B
  {1,0,0,1,1,1,0},  //C
};
const int sortiechiffre[3][7]={                    //Tableau contenant la liste des LEDs qui doivent être allumés pour former les chiffes      
  {0,1,1,0,0,0,0},  //1
  {1,1,0,1,1,0,1},  //2
  {1,1,1,1,0,0,1},  //3
};
const int cablerouge[5][3]={                       //Tableau contenant le récapitulatif des cas où il faut couper en fonction des points d'arrivée pour les cables rouges
  {0,0,1},
  {0,1,0},
  {1,0,0},
  {1,0,1},
  {0,1,0},
};
const int cablevert[5][3]={                        //Tableau contenant le récapitulatif des cas où il faut couper en fonction des points d'arrivée pour les cables verts
  {1,1,1},
  {1,0,1},
  {0,1,0},
  {1,0,1},
  {0,1,0},
};
const int cablebleu[5][3]={                        //Tableau contenant le récapitulatif des cas où il faut couper en fonction des points d'arrivée pour les cables bleus
  {0,1,0},
  {1,0,1},
  {0,1,0},
  {1,0,0},
  {0,1,0},
};
String String1="0";                                //On définit deux strings variables pour
String String2="0";
int L=3;                                           //On définit une variable qui servira a allumer les LEDs de réussite
int eb=0,b1=0,b2=0;                                //On définit une variable eb qui nous servira avec la fonction etatbouton
const int pinleds[]={22,23,24,26,27,28,29,30,31};  //On définit les pins de la LED RGB et des LEDs de réussite 
const int pinAfficheur[7]={2,3,4,5,6,7,8};         //On définit les pins des LEDs de l'afficheur
const int Bouton1=0, Bouton2=1;                  //On définit les pins des boutons
int r1=0,r2=0,r3=0,r=0;                            //On définit une liste des constantes r qui nous serviront avec la fonction random
int R[3]={r1,r2,r3};
int LR=-1,LG=-1,LB=-1;                             //On définit les lignes des tableaux cables par couleur
int C=0;                                           //On définit les colones de chaque tableau
int couleur=0;                                     //On définit cette variable pour indiquer la couleur du fil dans la fonction conversion
String c[3][3];                                    //On définit un tableau vide 3x3 qui contiendra les combinaisons issues du tableau ci dessous
String fils[3][12]={                               //On définit un tableau avec tout les combinaisons possibles de fils
                                                   //Les Strings se lisent de cette manière:
                                                   //Premier caractère: point de départ du fil
                                                   //Deuxième caractère: couleur du fil (R=Rouge,G=Vert,B=Bleu,N=Absence de fil)
  {"AR1","AR2","AR3","AG1","AG2","AG3","AB1","AB2","AB3","AN1","AN2","AN3"},
  {"BR1","BR2","BR3","BG1","BG2","BG3","BB1","BB2","BB3","BN1","BN2","BN3"},
  {"CR1","CR2","CR3","CG1","CG2","CG3","CB1","CB2","CB3","CN1","CN2","CN3"},
  };

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  r1=random(1,12);
  r2=random(1,12);
  r3=random(1,12);
  for (int i=2;i<10;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  pinMode(Bouton1,INPUT_PULLUP);
  pinMode(Bouton2,INPUT_PULLUP);
  for (int i=0;i<9;i++){
    pinMode(pinleds[i],OUTPUT);
  }
  c[0][0]=fils[0][r1].charAt(0); //c[0][0] = premier caractère du mot fils[0][r1]    aspect tableau:   C00            C01           C02
  c[1][0]=fils[0][r1].charAt(1); //c[1][0] = deuxième caractère du mot fils[0][r1]
  c[2][0]=fils[0][r1].charAt(2); //c[2][0] = troisième caractère du mot fils[0][r1]
  c[0][1]=fils[1][r2].charAt(0); //c[0][1] = premier caractère du mot fils[1][r2]                      C10            C11           C12
  c[1][1]=fils[1][r2].charAt(1); //c[1][1] = deuxième caractère du mot fils[1][r2]
  c[2][1]=fils[1][r2].charAt(2); //c[2][1] = troisième caractère du mot fils[1][r2]
  c[0][2]=fils[2][r3].charAt(0); //c[0][2] = premier caractère du mot fils[2][r3]                      C20            C21           C22
  c[1][2]=fils[2][r3].charAt(1); //c[1][2] = deuxième caractère du mot fils[2][r3]
  c[2][2]=fils[2][r3].charAt(2); //c[2][2] = troisième caractère du mot fils[2][r3]
  
}

void loop() {                              //Dans ce code l'utilisazteur traite les cas par séries de 3 (A,B, et C) pour être plus fidèle au module original
  etatBouton();                            //On regarde la valeur eb au tout début quand personne n'a touché aux boutons
  randomSeed(analogRead(0));               //on définit des randoms pour les cas A,B et C
  r1=random(1,12);
  r2=random(1,12);
  r3=random(1,12);
  for(int p = 0;p<3;p++){                  //Pour chaque cas
    r=R[p];                                //On utilise un random différent
    while (eb==2){                         //Tant que personne n'a appuyé sur un bouton
      digitalWrite(9,LOW);                 //On affiche sur le 7 segements de droite la lettre de l'entrée (la première lettre de la combinaison)
      digitalWrite(10,HIGH);
      for(int k=0;k<7;k++){
        if(sortielettre[p][k]==1){
        digitalWrite(k+2,LOW);
        }
        else if(sortielettre[p][k]==0){
          digitalWrite(k+2,HIGH);
        }
     }
     if(c[1][p].equals("R")){             //La led s'allumera de la couleur du fil a couper ou non
      Serial.println("ROUGE");
      digitalWrite(pinleds[0],LOW);
     }
     if(c[1][p].equals("G")){
      Serial.println("VERT");
      digitalWrite(pinleds[1],LOW);
     }
     if(c[1][p].equals("B")){
      Serial.println("BLEU");
      digitalWrite(pinleds[2],LOW);
     }
     if(c[1][p].equals("N")){             // N pour "non" c'est-à-dire qu'il n'y a pas de fil
      Serial.println("PAS DE FIL");
       }
       if(c[2][p].equals("1")){           //Ici l'afficheur 7 segements de gauche affichera le chiffre dans la combinaison pour indiquer le point d'arrivée du fil 
        Serial.println(1);
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        for(int k=0;k<7;k++){
          if(sortiechiffre[1][k]==1){
            digitalWrite(k+2,LOW);
          }
          else if(sortiechiffre[1][k]==0){
            digitalWrite(k+2,HIGH);
          } 
        }
      }
    
      if(c[2][p].equals("2")){
        Serial.println(2);
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        for(int k=0;k<7;k++){
          if(sortiechiffre[2][k]==1){
            digitalWrite(k+2,LOW);
          }
          else if(sortiechiffre[2][k]==0){
            digitalWrite(k+2,HIGH);
          }
        }
      }
      if(c[2][p].equals("3")){
        Serial.println(3);
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        for(int k=0;k<7;k++){
          if(sortiechiffre[3][k]==1){
            digitalWrite(k+2,LOW);
          }
          else if(sortiechiffre[3][k]==0){
            digitalWrite(k+2,HIGH);
          }
         }
      }
      etatBouton();                                  //On revérifie l'état des boutons
    }                                                //Maintenant on s'intéresse aux boutons                                 
    String1=fils[p][r].charAt(1);                    //Pour cela on s'intéresse aux deux derniers caractères de notre combinaison que l'on stocke dans String1 et String2
    String2=fils[p][r].charAt(2);
    if (String1.equals("R")){                        //Cette partie du code se penche sur l'avant dernier caractère de notre combinaison (lié à la couleur du fil)
      LR=LR+1;                                       //LR représente le nombre de fois que l'on a croisé un fil rouge or comme la première ligne du tableau est la ligne "0" alors LR commence à "-1"
      couleur=1;                                     //La variable couleur servira a identifier la couleur (rouge ici)
    }
    if (String1.equals("G")){                        //Même chose pour les fils verts
      LG=LG+1;
      couleur=2;
    }
    if (String1.equals("B")){                        //Même chose pour les fils bleus
      LB=LB+1;
      couleur=3;
    }
    if (String1.equals("N")){                       //Quand il n'y a pas de fil dans tout les cas on ne peut pas couper donc pas beoins de tableau
      couleur=4;
    }
    if (String2.equals("1")){                       //Ici on s'intéresse au dernier caractère lié au point d'arrivée
      C=0;                                          //Ici la variable C est une sorte de conversion car le 1/2/3 sont des string
    }
    if (String2.equals("2")){
      C=1;
    }
    if (String2.equals("3")){
      C=2;
    }                                                     
    switch(couleur){                                     //C'est à cet endroit du code que tout va se décider pour l'utilisateur
      case 1:                                            //Le switch sert à diférencier la marche à suivre en fonction de la couleur du fil
      if (cablerouge[LR][C] != digitalRead(Bouton1)){    //on regarde ensuite la valeur dans le tableau de la couleurs du fil aux coordonnées données par
        digitalWrite(pinleds[L],HIGH);                   //le nombre de fois qu'on a croisé un fil de la couleur du case (ligne) et le point d'arrivée (colonne) 
        L = L + 1;                                       //Dans les tableaux de couleur, 0="ne pas couper" et 1="couper"
        delay(500);                                      //Sachant qu'un 0="LOW" et un 1="HIGH" et que cette partie du code s'active qu'à l'appuie d'un bouton
      }                                                  //alors on a les conditions suivantes: 
      //else{                                            //Si la valeur du tableau est 0 (donc "LOW")
        //reset                                          //alors le bouton "couper" (celui de droite) ne doit pas être appuyé donc être en "HIGH"
      //}                                                //En revanche si la valeur du tableau est 1 (donc "HIGH")
      break;                                             //alors le bouton "couper" (toujours celui de droite) doit être appuyé donc être en "LOW"
      case 2:                                            //D'où le signe "!="
      if (cablevert[LG][C] != digitalRead(Bouton1)){     //Ensuite on allume une led qui veut dire qu'on a réussi le cas A et après avoir réussi le cas C le loop redémarre 
      digitalWrite(pinleds[L],HIGH);                     //à 6 Leds allumé le module est terminé
      L = L + 1;                                         //Si l'utilisateur se trompe alors la carte se reset du coup il recommence à 0 (cheh)
      delay(500);
      }
      //else{ 
        //reset
      //}
      break;  
      case 3:
      if (cablebleu[LB][C] != digitalRead(Bouton1)){
      digitalWrite(pinleds[L],HIGH);
      L = L + 1;
      delay(500);
      }
      //else{
        //reset
      //}
      break;
      default:
      if (digitalRead(Bouton1)==HIGH){
        digitalWrite(pinleds[L],HIGH);
        L = L + 1;
        delay(500);
      }
      //else{
        //reset
      //}
      break; 
    } 
  }
  if(L == 6){
    delay(10000000000);
  }
}

void etatBouton(){                //cette fonction permet de connaitre les états des deux boutons à la fois
  b1=digitalRead(Bouton1);        //On regarde l'état du bouton 1
  b2=digitalRead(Bouton2);        //On regarde l'état du bouton 2
  eb=b1+b2;                       //On fait la somme des deux états
  return eb;                      //Si eb varie alors l'utilisateur a appuyé sur un bouton
}






  
