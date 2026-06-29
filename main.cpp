#include "controladora.hpp"
#include <cstdlib>

int main() {
   
    #ifdef _WIN32
        system("mode con: cols=110 lines=40");
    #endif

    Controladora app;
    app.iniciar();
    
    return 0;
}