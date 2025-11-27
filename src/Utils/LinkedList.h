#pragma once
#include <iostream>

template <typename T> struct ListNode {
  T data;
  ListNode *next;

  ListNode(T val) : data(val), next(nullptr) {}
};

template <typename T> class LinkedList {
private:
  ListNode<T> *head;
  ListNode<T> *tail;
  int size;

public:
  LinkedList() : head(nullptr), tail(nullptr), size(0) {}

  ~LinkedList() { clear(); }

  void push_back(T val) {
    ListNode<T> *newNode = new ListNode<T>(val);
    if (!head) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    size++;
  }

  void clear() {
    ListNode<T> *current = head;
    while (current) {
      ListNode<T> *next = current->next;
      delete current;
      current = next;
    }
    head = tail = nullptr;
    size = 0;
  }

  int getSize() const { return size; }

  bool isEmpty() const { return size == 0; }

  ListNode<T> *getHead() const { return head; }

  T get(int index) {
    if (index < 0 || index >= size) return T();
    ListNode<T> *current = head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
  }
};
