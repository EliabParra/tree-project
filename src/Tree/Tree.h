#pragma once
#include "../Node/Node.h"
#include "../Utils/LinkedList.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

class Tree {
private:
  Node *root = nullptr;
  LinkedList<Node *> allNodes;
  Node *findFirstMaleInPrimogeniture(Node *current) {
    if (!current)
      return nullptr;
    if (current->gender == 'H' && !current->is_dead && current->age < 70) {
      return current;
    }
    Node *found = findFirstMaleInPrimogeniture(current->left);
    if (found)
      return found;
    return findFirstMaleInPrimogeniture(current->right);
  }

 void collectEligibleFemales(Node *current, LinkedList<Node *> &females) {
    if (!current)
        return;
    if (current->gender == 'M' && !current->is_dead && current->age > 15 &&
        current->age < 70) {
        females.push_back(current);
    }
    collectEligibleFemales(current->left, females);
    collectEligibleFemales(current->right, females);
}

void sortFemalesByAge(LinkedList<Node *> &females) {
    if (females.getSize() < 2)
        return;
    bool swapped;
    do {
        swapped = false;
        ListNode<Node *> *current = females.getHead();
        while (current && current->next) {
            if (current->data->age > current->next->data->age) {
                Node *temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

public:
  Tree() {}

  ~Tree() {
    ListNode<Node *> *current = allNodes.getHead();
    while (current) {
      delete current->data;
      current = current->next;
    }
  }

  void loadFromCSV(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
      cerr << "Error al abrir el archivo: " << filename << endl;
      return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
      stringstream ss(line);
      string segment;
      string cols[9];
      int colIdx = 0;
      while (getline(ss, segment, ',') && colIdx < 9) {
        cols[colIdx++] = segment;
      }

      if (colIdx < 9)
        continue;

      int id = stoi(cols[0]);
      string name = cols[1];
      string last_name = cols[2];
      char gender = cols[3][0];
      int age = stoi(cols[4]);
      int id_father = (cols[5] == "" || cols[5] == "-1") ? -1 : stoi(cols[5]);
      bool is_dead = stoi(cols[6]);
      bool was_king = stoi(cols[7]);
      bool is_king = stoi(cols[8]);

      Node *newNode = new Node(id, name, last_name, gender, age, id_father,
                               is_dead, was_king, is_king);
      allNodes.push_back(newNode);

      if (id_father == -1) {
        root = newNode;
      }
    }

    file.close();
    ListNode<Node *> *current = allNodes.getHead();
    while (current) {
      Node *node = current->data;
      if (node->id_father != -1) {
        Node *father = getNode(node->id_father);
        if (father) {
          node->parent = father;
          if (father->left == nullptr) {
            father->left = node;
          } else {
            father->right = node;
          }
        }
      }
      current = current->next;
    }
  }

  Node *getKing() {
    ListNode<Node *> *current = allNodes.getHead();
    while (current) {
      if (current->data->is_king)
        return current->data;
      current = current->next;
    }
    return nullptr;
  }

  void printLineOfSuccession(Node *node) {
    if (!node)
      return;

    if (!node->is_dead) {
      cout << node->id << ". " << node->name << " " << node->last_name << " "
           << (node->gender == 'H' ? "(H)" : "(M)") << " (" << node->age
           << " años) ";
      if (node->is_king)
        cout << "[" << (node->gender == 'H' ? "REY" : "REINA") << "]";
      else if (node->was_king)
        cout << "[EX-" << (node->gender == 'H' ? "REY" : "REINA") << "]";
      cout << endl;
    }

    printLineOfSuccession(node->left);
    printLineOfSuccession(node->right);
  }

  void printSuccession() {
    cout << "--- Linea de Sucesion (Vivos) ---" << endl;
    printLineOfSuccession(root);
  }

  Node *getNode(int id) {
    ListNode<Node *> *current = allNodes.getHead();
    while (current) {
      if (current->data->id == id)
        return current->data;
      current = current->next;
    }
    return nullptr;
  }

  Node *getRoot() { return root; }
};