#pragma once
#include <string>

using namespace std;

struct Node {
  int id;
  string name;
  string last_name;
  char gender;
  int age;
  int id_father;
  bool is_dead;
  bool was_king;
  bool is_king;

  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;

  Node(int id, string name, string last_name, char gender, int age,
       int id_father, bool is_dead, bool was_king, bool is_king)
      : id(id), name(name), last_name(last_name), gender(gender), age(age),
        id_father(id_father), is_dead(is_dead), was_king(was_king),
        is_king(is_king) {}
};