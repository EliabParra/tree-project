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
    cout << "Error: No se pudo cargar el arbol o esta vacio. Verifique bin/datos.csv" << endl;
    royalTree.loadFromCSV("datos.csv");
  }

  if (royalTree.getRoot() == nullptr) {
    cout << "Fallo al cargar datos. Saliendo." << endl;
    return 1;
  }

  int option = 0;
  while (option != 5) {
    printMenu();
    if (!(cin >> option)) {
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }

    switch (option) {
    case 1:
      cout << "Linea de sucesion:" << endl;
      break;
    case 2:
      cout << "Actualizar persona:" << endl;
      break;
    case 3:
      cout << "Evaluar corona:" << endl;
      break;
    case 4:
      cout << "Rey actual:" << endl;
      break;
    case 5:
      cout << "Saliendo..." << endl;
      break;
    default:
      cout << "Opcion invalida." << endl;
    }
  }

  return 0;
}