#pragma once

#include "SelfOrderedListADT.h"
#include "llist.h"

#ifndef SELFORDEREDLIST_H
#define SELFORDEREDLIST_H

template <typename E>
class SelfOrderedList : SelfOrderedListADT<E> {
private:
	LList<E>* list;
	int compares;
	unsigned char heuristic;
public:
	SelfOrderedList(unsigned char heur = 0) {
		list = new LList<E>();
		heuristic = heur;
		compares = 0;
	}
	~SelfOrderedList() {

	}
	void reset(int heur = 0) {
		list->clear();
		compares = 0;
		heuristic = heur;
	}
	bool find(const E& it) {
		list->moveToStart();
		for (int i = 0; i < list->length(); i++) {
			list->next();
			if (equals(list->getValue(), it)) {
				list->incCurrFreq();
				switch (heuristic) {
				case 0: //count
					list->count();
					break;
				case 1: //move to front
					list->moveToFront(i + 1);
					break;
				case 2: //transpose
					if (i > 0) {
						list->transpose(i);
					}
					break;
				default:
					Assert(1, "heuristic not found");
					break;
				}
				return 1;
			}
			compares++;
		}
		add(it);
		return 0;
	}

	void add(const E& it) {
		list->append(it);
	}
	void remove(int n) {
		list->moveToPos(n);
		list->remove();
	}

	int getCompares() const {
		return compares;
	}
	int size() const {
		return list->length();
	}
	void printlist() {
		printlist(list->length());
	}
	void printlist(int n) {
		say("#Words: ");
		say(list->length());
		say(" #Compares: ");
		sayl(compares);
		list->print(n);

		sayl("\n");
	}
	void printHeadTailCurr() {
		list->printHeadTailCurr();
	}
	void printSize() {
		say("size: ");
		sayl(list->length());
	}
	void setHeuristic(unsigned char heur) {
		heuristic = heur;
	}
};

#endif