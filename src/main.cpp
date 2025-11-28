#include "Tree/Tree.h"
#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void printMenu() {
  cout << "\n=== SISTEMA DE SUCESION REAL ===" << endl;
  cout << "1. Mostrar Linea de Sucesion" << endl;
  cout << "2. Actualizar Persona (Muerte/Edad)" << endl;
  cout << "3. Evaluar Corona (Buscar nuevo Rey)" << endl;
  cout << "4. Mostrar Rey Actual" << endl;
  cout << "5. Salir" << endl;
  cout << "Ingrese opcion: ";
}

int main() {
  setlocale(LC_ALL, "Spanish");
  Tree royalTree;
  string csvPath = "bin/datos.csv";

  cout << "Cargando datos desde " << csvPath << "..." << endl;
  royalTree.loadFromCSV(csvPath);

  if (royalTree.getRoot() == nullptr) {
    cout << "Error: No se pudo cargar el arbol o esta vacio. Verifique "
            "bin/datos.csv"
         << endl;
    royalTree.loadFromCSV("datos.csv");
  }

  if (royalTree.getRoot() == nullptr) {
    cout << "Fallo al cargar datos. Saliendo." << endl;
    return 1;
  }
    return 0;
}