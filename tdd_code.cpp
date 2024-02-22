//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     ROMAN FULLA <xfulla00@stud.fit.vutbr.cz>
// $Date:       $2019-03-05
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author ROMAN FULLA
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

#include <iostream>

using namespace std;

PriorityQueue::PriorityQueue()
{

}

PriorityQueue::~PriorityQueue()
{
	while(Head != nullptr) {
		if(Head->pNext != nullptr) {
			Head = Head->pNext;
			delete Head->pPrev;
		}
		else {
			delete Head;
			Head = nullptr;
		}
	}
}

void PriorityQueue::Insert(int value)
{	
	Element_t *new_element = new Element_t();

	if(new_element == nullptr) {																	//Alokacia pamate sa nepodarila
		cerr << "memory_allocation_has_failed"
			 << "_->_"
			 << "deconstructed_the_queue"
			 << endl;

		while(Head != nullptr) {																	//Destruktor
			if(Head->pNext != nullptr) {
				Head = Head->pNext;
				delete Head->pPrev;
			}
			else {
				delete Head;
				Head = nullptr;
			}
		}
		
		exit(EXIT_FAILURE);
	}

	new_element->value = value;

	if(Head == nullptr) {																			//Jediny prvok
		Head = new_element;
	}

	else if(Head->value >= value) {																	//Prvy prvok
		new_element->pNext = Head;
		Head->pPrev = new_element;

		Head = new_element;
	}

	else {																							//Ostatne prvky
		Element_t *og_element = Head;

		while(og_element->value < value && og_element->pNext != nullptr) {
			og_element = og_element->pNext;
		}
		
		if(og_element->pNext == nullptr && og_element->value <= value) {							//Posledny prvok
			new_element->pPrev = og_element;			
			og_element->pNext = new_element;

			return;
		}

		new_element->pPrev = og_element->pPrev;
		if(og_element->pPrev != nullptr) 	og_element->pPrev->pNext = new_element;

		new_element->pNext = og_element;
		og_element->pPrev = new_element;
	}
}

bool PriorityQueue::Remove(int value)
{	
	Element_t *rm_element = Find(value);
	if(rm_element == nullptr) return false;

	if(rm_element == Head) {																		//Prvy prvok
		Head = rm_element->pNext;
	}
	else if(rm_element->pNext == nullptr) {															//Posledny prvok
		rm_element->pPrev->pNext = nullptr;
	}
	else {																							//Ostatne prvky
		rm_element->pPrev->pNext = rm_element->pNext;
		rm_element->pNext->pPrev = rm_element->pPrev;
	}

	delete rm_element;
	rm_element = nullptr;

	return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{	
    if(Head != nullptr) {
    	Element_t *cmp_element = Head;

   		while(cmp_element->value <= value && cmp_element != nullptr) {
   			if(cmp_element->value == value) return cmp_element;
   			else cmp_element = cmp_element->pNext;
		}
    }

    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return Head;
}

/*** Konec souboru tdd_code.cpp ***/
