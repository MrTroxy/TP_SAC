/**
    Class MyOledViewWorking : Gestion d'une VUE pour le OLed
    @file MyOledViewWorking.h
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

    myOledViewWorking->init("id : 123456");
       
**/



#ifndef MYOLEDVIEWWORKING.h 
#define MYOLEDVIEWWORKING.h 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MyOledView.h>


class MyOledViewWorking : public MyOledView
{
public:
    int init(std::string _id);

protected:
    void display(Adafruit_SSD1306 *adafruit);
    void update(Adafruit_SSD1306 *adafruit);
    void displayGifFire(Adafruit_SSD1306 *adafruitint);
    void displayGifFireAnimated(Adafruit_SSD1306 *adafruitint, int positionX, int positionY);
};
#endif