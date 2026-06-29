#include <iostream>
#include <vector>
#include "teclado.hpp"



// funciones cursor
#pragma region funciones_cursor
//funcion para mover el cursor a una posicion especifica en la consola
//esta funcion considera que la posicion (0,0) es la esquina superior izquierda de la consola
void gotoxy(int x, int y) {
    std::cout << "\033[" << y + 1  << ";" << x + 1  << "H";
}
/*Funcion para mostrar u ocultar el cursor en la consola
si visible es true, el cursor se mostrara
si visible es false, el cursor se ocultara*/
void cursorVisible(bool visible) {
    std::cout << "\033[?25" << (visible ? "h" : "l");
}
/*como usare codigos ansi para los colores esta funcion resetea los colores*/
void resetColor() {
    std::cout << "\033[0m";
}
#pragma endregion

