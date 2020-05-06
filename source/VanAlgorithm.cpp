// VanAlgorithm.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "directedGraph.h"


int main()
{
    /*ADE::DirectedGraph<int> my_graph('a', 2);

    
    int letter = 97;
    
    list<ADE::Node<char>*> S;
    S.push_back(my_graph.get_root_ptr());
    int niveles = 4;
    int n_last_level,n= n_last_level = pow(2, niveles) - 2;
    n_last_level = pow(2, niveles - 1);
    while (n>0) {
        
        letter++;
        ADE::Node<char>* u = S.front();
        *(u->data_) = char(letter);
        S.pop_front();
        
        if (n > n_last_level) {
            for (int i = 0; i < 2; i++) {
                my_graph.insert_vertex('.', u, i);
                S.push_back(u->forward_[i]);
            }
        }
        n--;

    }*/

    ADE::DirectedGraph<int> my_graph(1, 2);




    //Aquí solo voy a crear un árbol de la forma: (Intenté hacerlo con letras, pero tenía un error cuando las asignaba)
    //                      1
    //              2               3
    //          4       5       6       7
    //        8   9   10 11   12 13   14 15

    int letter = 1;

    list<ADE::Node<int>*> S;
    S.push_back(my_graph.get_root_ptr());
    int niveles = 4;
    int n_last_level, n = n_last_level = pow(2, niveles) - 2;
    n_last_level = pow(2, niveles - 1);
    while (n > 0 && !S.empty()) {

        
        ADE::Node<int>* u = S.front();
        *(u->data_) = letter;
        S.pop_front();

        if (n > n_last_level) {
            for (int i = 0; i < 2; i++) {
                my_graph.insert_vertex(-1, u, i);
                S.push_back(u->forward_[i]);
            }
        }
        letter++;
        n--;

    }


    //Tiene 3 parámetros, el primero es el método: 1=BFS 2=DFS 3=VanDaBose
    //el segundo es el B
    //el tercero es el valor a buscar
    my_graph.look_for(1, 3, 7);     //esta función está implementada en directedGraph.h


}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
