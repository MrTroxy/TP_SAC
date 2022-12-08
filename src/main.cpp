/* Copyright (C) 2022
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2022
 *  
    @file     main.cpp
    @author   David Tremblay
    @version  1.0 17/11/2022

    Historique des versions
           Version      Date            Auteur           Description
           1.0        17/11/2022    David Tremblay       Première version du logiciel

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
                      
            ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
            AsyncTCP-esphome                            (Pour utiliser les focntionnalités TCP)
            bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)

    Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            //Remarques
            //Pour trouver le WifiManager (dans la branche development)
            //   https://github.com/tzapu/WiFiManager/tree/development
            //   Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib
    
    Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index)
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)

    Classes du système
        MYOLED/
                    MyOled.cpp              V1.1    Gestion d'un écran Oled Utilisant un GPIO d'un contrôleur
                    MyOledView              V1.1    Gestion d'une VUE pour le OLed  
                    MyOledViewErrorWifiConnexion     V1.2
                    MyOledViewInitialisation         V1.2
                    MyOledViewWorkingWifiAp                 V1.2
                    MyOledViewWorking
                    MyOledViewWorkingOff
                    MyOledViewWorkingCold
                    MyOledViewWorkingHeat

        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)
              
 * */

#include <iostream>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "myFunctions.cpp" //fonctions utilitaires

using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

#include <Wire.h>
#include <MyOled.h>
#include <MyOledView.h>
#include <MyOledViewWorkingWifiAp.h>
#include <MyOledViewErrorWifiConnexion.h>
#include <MyOledViewWorking.h>
#include <MyOledViewInitialisation.h>
#include <MyOledViewWorking.h>
#include <MyOledViewWorkingOFF.h>
#include <MyOledViewWorkingCold.h>
#include <MyOledViewWorkingHeat.h>

MyOledViewInitialisation *viewIni = NULL;
MyOledViewWorkingWifiAp *viewWifi = NULL;
MyOledViewErrorWifiConnexion *viewErrorWifi = NULL;
MyOledViewWorking *viewWorking = NULL;
MyOledViewWorkingOFF *viewWorkingOFF = NULL;
MyOledViewWorkingCOLD *viewWorkingCOLD = NULL;
MyOledViewWorkingHEAT *viewWorkingHEAT = NULL;

//Définition des trois leds de statut
#define GPIO_PIN_LED_YELLOW   12 // Led jaune sur la pin GPIO12
#define GPIO_PIN_LED_GREEN     14 // Led verte sur la pin GPIO14
#define GPIO_PIN_LED_RED  27 // Led rouge sur la pin GPIO27

// ------------------ Gestion boutons ----------------------

#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

// ---------------------- Bool sur le fonctionnement du four ---------------------------------------

// permet de savoir si le Four est en marche
boolean demarre = false;
// permet à la page web de savoir quel est le status de l'esp
string status = "null";


#include "WiFi.h"

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "microcontrollerslab";
WiFiServer server(80);

#include "TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT11 / DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
TemperatureStub *temperatureStub = NULL;

// pour l'affichage
#define SCREEN_WIDTH 128      // taille de l'écran en longeur, en pixel
#define SCREEN_HEIGHT 64      // taille de l'écran en largeur, en pixel
#define OLED_RESET 4          // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C // Adresse I2C de l'écran Oled
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int frame_delay = 15;
MyOled *myOled = NULL;

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres
std::string CallBackMessageListener(string message)
{
    while (replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string arg1 = getValue(message, ' ', 0);
    

    if (string(arg1.c_str()).compare(string("temperature")) == 0)
    {
        float temperature = temperatureStub->getTemperature();
        String temp = (String)temperature;

        return (temp.c_str());
    }

    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);

    string actionToDo = getValue(message, ' ', 0);
    string nomDuFour = "Four #1";
    
    if(string(actionToDo.c_str()).compare(string("askNomFour")) == 0)
    {
        return(nomDuFour.c_str());
    }


std::string result = "";
return result;
}

void Connect_WiFi()
{
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(100); 
    }
}

void setup()
{ 
    Serial.begin(9600);
    Serial.println("Mac Address : " + WiFi.macAddress());
    delay(100);

 //Connexion au WifiManager
    String ssIDRandom, PASSRandom;
    String stringRandom;
    stringRandom = get_random_string(4).c_str();
    ssIDRandom = SSID;
    ssIDRandom = ssIDRandom + stringRandom;
    stringRandom = get_random_string(4).c_str();
    PASSRandom = PASSWORD;
    PASSRandom = PASSRandom + stringRandom;

char strToPrint[128];
    sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
    Serial.println(strToPrint);


 if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
        Serial.println("Erreur de connexion.");
      
        }
    else {
        Serial.println("Connexion Établie.");
        }

    // ----------- Routes du serveur ----------------
    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    // ----------- Senseur de température ----------------
    temperatureStub = new TemperatureStub();
    temperatureStub->init(DHTPIN, DHTTYPE);

    // ----------- Initialisation des LED statuts ----------------
    pinMode(GPIO_PIN_LED_YELLOW, OUTPUT);
    pinMode(GPIO_PIN_LED_GREEN, OUTPUT);
    pinMode(GPIO_PIN_LED_RED, OUTPUT);

    digitalWrite(GPIO_PIN_LED_YELLOW, LOW);
    digitalWrite(GPIO_PIN_LED_GREEN, LOW);
    digitalWrite(GPIO_PIN_LED_RED, HIGH);

    // ----------- Initialisation de l'écran Oled ----------------
    myOled = new MyOled(&Wire, OLED_I2C_ADDRESS, SCREEN_HEIGHT, SCREEN_WIDTH);
    myOled->init();
    
 }

void loop()
{

}


/***************************************************************************************************************/