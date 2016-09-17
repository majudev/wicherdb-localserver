#include <iostream>
#include <gtkmm.h>
#include "Splash.h"
#include "Main.h"
#include "Database.h"

int main(int argc, char * argv[]){
    Wicher::Splash * splash = new Wicher::Splash(argc, argv);
    if(splash->show()){
        delete splash;
        Wicher::Main main(argc, argv);
        main.run();
        return 0;
    }
    delete splash;
    return -1;
}

