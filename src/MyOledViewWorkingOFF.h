/**
    Class MyOledViewWorkingHeat : Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingHeat.h
    @author David Tremblay
    @version 1.1 2022-12-01

   
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune

    Exemple d'utilisation

    myOledViewWorkingOff->setParams("temperature", vv.str());
    myOled->displayView(myOledViewWorkingOff);
       
**/


#ifndef MYOLEDVIEWWORKINGOFF.h
#define MYOLEDVIEWWORKINGOOFF .h
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MyOledViewWorking.h>

class MyOledViewWorkingOFF : public MyOledViewWorking
{
private:
    void display(Adafruit_SSD1306 *adafruit);
};
#endif