#include <iostream>
#include <vector>

using vvi = std::vector<std::vector<int>>;

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

// funciones_imprimir matriz

/*Funcion para imprimir una matriz en la consola, considerando un fondo de color*/
void imprimirMatriz(int fila, int columna, const vvi& matriz, const vvi& fondo) {
    
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            
            //esto ayudara a saltar la impresion de los elementos que son iguales al fondo, para no sobreescribirlos
            if (matriz[i][j] == fondo[i][j]) {
                continue; 
            }

            gotoxy(columna + j, fila + i);
            
            switch (matriz[i][j]) {
                case 0: // color neutral
                    std::cout << "\033[0m";
                    break;
                case 1: // color rojo puro
                    std::cout << "\033[38;2;255;0;0m";
                    break;
                case 2: // color verde puro
                    std::cout << "\033[38;2;0;255;0m";
                    break;
                case 3: // color azul puro
                    std::cout << "\033[38;2;0;0;255m";
                    break;
                case 4: // color amarillo puro
                    std::cout << "\033[38;2;255;255;0m";
                    break;
                case 5: // color naranja puro
                    std::cout << "\033[38;2;255;165;0m";
                    break;
                case 6: // color negro puro
                    std::cout << "\033[38;2;0;0;0m";
                    break;
            }        
            std::cout << char(219);             
        }
    }
    resetColor(); // Reset de color por defecto al final de la impresión
}

//matrices

#pragma region matrices





#pragma endregion

//menus

#pragma region menus




#pragma endregion




