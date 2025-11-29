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
      clearScreen();
      royalTree.printSuccession();
      break;
    case 2:
      int id;
      cout << "Ingrese ID de la persona a actualizar: ";
      cin >> id;
      Node *node = royalTree.getNode(id);
      if (node) {
        cout << "Actualizando a " << node->name << " " << node->last_name << endl;
        cout << "1. Marcar como Fallecido" << endl;
        cout << "2. Actualizar Edad" << endl;
        cout << "3. Cancelar" << endl;
        int subOption;
        cin >> subOption;
        if (subOption == 1) {
          node->is_dead = true;
          cout << "Marcado como fallecido." << endl;
        } else if (subOption == 2) {
          int newAge; 
          cout << "Ingrese nueva edad: ";
          cin >> newAge;
          node->age = newAge;
          cout << "Edad actualizada." << endl;
        }
        royalTree.updateKing();
      } else {
        cout << "Persona no encontrada." << endl;
      }
      break;
      
    case 3:
      royalTree.updateKing();
      break;
    case 4: {
      Node *king = royalTree.getKing();
      if (king) {
        cout << "Actual " << (king->gender == 'H' ? "Rey" : "Reina") << ": "
             << king->name << " " << king->last_name << " (Edad: " << king->age
             << ")" << endl;
      } else {
        cout << "¡No hay Rey actualmente!" << endl;
      }
      break;
    }
    case 5:
      cout << "Saliendo..." << endl;
      break;
    default:
      cout << "Opcion invalida." << endl;
    }
  }

  return 0;
}