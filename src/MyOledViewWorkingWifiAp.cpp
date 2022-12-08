/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewErrorWifiApp.cpp
    @author David Tremblay
    @version 1.1 2022-12-01
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWorkingWifiAp.h"
using namespace std;
//-------------------Setter----------------------
string MyOledViewWorkingWifiAp::setNomDuSysteme(string valNom)
{

    this->NomDuSysteme = valNom;
    return "";
}

string MyOledViewWorkingWifiAp::setSslDuSysteme(string valSsl)
{

    this->SslDuSysteme = valSsl;
    return "";
}

string MyOledViewWorkingWifiAp::setPassDuSysteme(string valPass)
{

    this->PassDuSysteme = valPass;
    return "";
}
//--------------fonctions d'affichage--------------------
void MyOledViewWorkingWifiAp::display(Adafruit_SSD1306 *display)
{

    display->clearDisplay();
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->println("Sac System");
    display->setCursor(1, 20);
    display->println(this->NomDuSysteme.c_str());
    display->setCursor(1, 40);
    display->println(this->SslDuSysteme.c_str());
    display->setCursor(1, 50);
    display->println(this->PassDuSysteme.c_str());
    display->display();
    delay(20);

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewWorkingWifiAp::update(Adafruit_SSD1306 *update)
{
    update->clearDisplay();
    update->setTextSize(1);
    update->setCursor(1, 0);
    update->println("Sac System Update");
    update->setCursor(1, 20);
    update->println(this->NomDuSysteme.c_str());
    update->setCursor(1, 40);
    update->println(this->SslDuSysteme.c_str());
    update->setCursor(1, 50);
    update->println(this->PassDuSysteme.c_str());
    update->display();
    delay(20);

    delay(20);
}