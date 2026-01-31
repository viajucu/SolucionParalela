// SolucionParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

//Incluye librerías
#include <iostream>
#include <omp.h>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

//Declara las constantes
#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);

int main()
{
    //Muestra mensaje inicial y declara los arreglos
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Semilla para que los aleatorios cambien en cada ejecución
    srand((unsigned)time(nullptr));

    for (i = 0; i < N; i++)
    {
        // Asignación original
        // a[i] = i * 10;
        // b[i] = (i + 3) * 3.7;

        // Asignación aleatoria
        a[i] = (float)(rand() % 100);      // [0, 99]
        b[i] = (rand() % 100) / 10.0f;     // [0.0, 9.9]
    }

    int pedazos = chunk;

    //Paralelización con OpenMP
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    //Imprime los resultados
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}