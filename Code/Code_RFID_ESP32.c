#include <MFRC522.h>
#include <SPI.h>

// Affectation des broches
#define RST_PIN 27       // Pin de reset du module RFID
#define SS_PIN 5         // Pin de sélection du module RFID (SDA)
#define MOSI_PIN 23      // IO23 relié au pin MOSI du RFID
#define MISO_PIN 19      // IO19 relié au pin MISO du RFID
#define SCK_PIN 18       // IO18 relié au pin SCK du RFID

MFRC522 mfrc522(SS_PIN, RST_PIN); // Création de l'objet RFID

void setup() {
  Serial.begin(115200); // Utilisation d'un débit plus élevé pour une meilleure communication
  while (!Serial); // Attente que le port série soit prêt
  SPI.begin(); // Initialisation de la communication SPI
  
  // Configuration des broches
  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH); // Activer le module RFID
  pinMode(metalSensorPin, INPUT); // Définir le pin du capteur comme entrée
  
  // Initialisation du module RFID
  mfrc522.PCD_Init(); 
  delay(100); // Attente pour stabiliser le module
  mfrc522.PCD_DumpVersionToSerial(); // Affichage des informations de la bibliothèque
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
}

void loop() {
  // Attente d'une carte RFID
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return; // Sortir si aucune carte n'est présente
  }

  // Récupération des informations de la carte RFID
  if (!mfrc522.PICC_ReadCardSerial()) {
    return; // Sortir si la lecture échoue
  }

  // Lire la valeur du capteur
  int sensorValue = digitalRead(metalSensorPin); 
  Serial.print("Valeur du capteur : ");
  Serial.println(sensorValue); // Afficher la valeur lue

  // Afficher les informations de la carte RFID
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  delay(100); // Attendre un peu avant la prochaine lecture
}


