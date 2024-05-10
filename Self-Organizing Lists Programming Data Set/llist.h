#ifndef LLIST_H
#define	LLIST_H

#include "book.h"
#include "link.h"

// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This is the file to include in your code if you want access to the
// complete LList template class

// First, get the declaration for the base list class
#include "list.h"
#include "macros.h"

// This is the declaration for LList. It is split into two parts
// because it is too big to fit on one book page
// Linked list implementation
template <typename E> class LList: public List<E> {
private:
  Link<E>* head;       // Pointer to list header
  Link<E>* tail;       // Pointer to last element
  Link<E>* curr;       // Access to current element
  int cnt;    	       // Size of list

  void init() {        // Intialization helper method
    curr = tail = head = new Link<E>;
    cnt = 0;
  }

  void removeall() {   // Return link nodes to free store
    while(head != NULL) {
      curr = head;
      head = head->next;
      delete curr;
    }
  }

public:
  LList() { // Constructor
      init();
  }

  ~LList() { // Destructor
      removeall();
  }

  void clear() {
      removeall();
      init();
  }       // Clear list

  // Insert "it" at current position
  void insert(const E& it) {
    curr->next = new Link<E>(it, curr->next);
    if (tail == curr) tail = curr->next;  // New tail
    cnt++;
  }

  void append(const E& it) { // Append "it" to list
    tail->next = new Link<E>(it, NULL);
    tail = tail->next;
    cnt++;
  }

  // Remove and return current element
  E remove() {
    Assert(curr->next == NULL, "No element");
    E it = curr->next->element;      // Remember value
    Link<E>* ltemp = curr->next;     // Remember link node

    if (tail == curr->next) {
        tail = curr; // Reset tail
    }
    curr->next = curr->next->next;   // Remove from list
    delete ltemp;                    // Reclaim space
    cnt--;			     // Decrement the count
    return it;
  }

  void moveToStart() { // Place curr at list start
      curr = head;
  }

  void moveToEnd() { // Place curr at list end
      curr = tail;
  }

  // Move curr one step left; no change if already at front
  void prev() {
    if (curr == head) return;       // No previous element
    Link<E>* temp = head;
    // March down list until we find the previous element
    while (temp->next!=curr) temp=temp->next;
    curr = temp;
  }

  // Move curr one step right; no change if already at end
  void next() {
      if (curr != tail) curr = curr->next;
  }

  int length() const  { // Return length
      return cnt;
  } 

  // Return the position of the current element
  int currPos() const {
    Link<E>* temp = head;
    int i;
    for (i=0; curr != temp; i++)
      temp = temp->next;
    return i;
  }

  // Move down list to "pos" position
  void moveToPos(int pos) {
    Assert ((pos<0) || (pos>=cnt), "Position out of range");
    curr = head;
    for (int i = 0; i < pos; i++) {
        curr = curr->next;
    }
  }

  const E& getValue() const { // Return current element
    Assert(curr->element == NULL, "No value");
    return curr->element;
  }

  void incCurrFreq() {
      curr->freq++;
  }

  void print(int n) { // Print list contents
      moveToStart();
      next();
      for (int i = 0; i < n; i++) {
          say(curr->element);
          say("-");
          say(curr->freq);
          if (i < n - 1) {
              curr = curr->next;
          }
          say(" ");
          
      }
  }
  void count() {
      char Issues = 1;
      while (Issues) {
          Issues = 0;
          moveToStart();
          int valueID = 0x7FFFFFFF;
          for (int i = 0; i < cnt - 1; i++) {
              next();
              if (curr->freq < curr->next->freq) {
                  transpose(i + 1);
                  Issues = 1;
              }
          }
      }
  }
  void moveToFront(int n) {
      if (n > 2) { //element NOT ALREADY front
          moveToStart();
          Link<E>* beg = head;
          Link<E>* mid = head->next; //1
          Link<E>* end = head->next->next; //2
          Link<E>* prev = curr;
          for (int i = 0; i < n; i++) {
              prev = curr;
              next();
          }
          Link<E>* nCurr = curr;

          mid->next = nCurr->next;
          prev->next = mid;
          nCurr->next = end;
          beg->next = nCurr;
          if (n == cnt) {
              tail = mid;
          }
      }
      if (n == 2) {
          transpose(1);
      }
  }
  //swaps with the element IN FRONT of it
  void transpose(int n) {
      moveToStart();
      Link<E>* beg = curr;
      if (n > 0) {
          if (cnt >= 2) {
              if (n <= cnt - 1) {
                  for (int i = 0; i <= n - 1; i++) {
                      if (i == n - 1) {
                                //beg
                          Link<E>* mid = beg->next;
                          Link<E>* end = beg->next->next;
                          Link<E>* END = beg->next->next->next;
                          mid->next = END;
                          end->next = mid;
                          beg->next = end;
                          if (n == cnt - 1) {
                              tail = mid;
                          }
                      }
                      else {
                          next();
                          beg = curr;
                      }
                  }
              }
          }
      }
      else {
          //n is not greater than 0, so we would be modifying the head resulting in catastrophic failure
      }
  }

  void printHeadTailCurr() {
      say("Head: ");
      sayl(head->element);
      say("Tail: ");
      sayl(tail->element);
      say("Curr: ");
      sayl(curr->element);
  }
};

#endif