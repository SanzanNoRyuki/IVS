//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     ROMAN FULLA <xfulla00@stud.fit.vutbr.cz>
// $Date:       $2019-03-05
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author ROMAN FULLA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

using namespace std;

BinaryTree EmptyTree;
BinaryTree NonEmptyTree;

bool  b;
void *p;
pair<bool,void*> test_node(b,p);

void *test_ptr;

vector<Node_t*> leaf_pointers;
vector<Node_t*> node_pointers;

TEST (EmptyTree,InsertNode) {
	ASSERT_EQ	(EmptyTree.GetRoot(),nullptr);

	test_node = EmptyTree.InsertNode(42);
	EXPECT_TRUE	(test_node.first);
	EXPECT_EQ	(EmptyTree.GetRoot(),test_node.second);

	EmptyTree.DeleteNode(42);
}

TEST (EmptyTree,DeleteNode) {
	ASSERT_EQ   (EmptyTree.GetRoot(),nullptr);

	EXPECT_FALSE(EmptyTree.DeleteNode(42));
}

TEST (EmptyTree,FindNode) {
	ASSERT_EQ   (EmptyTree.GetRoot(),nullptr);

	EXPECT_EQ   (EmptyTree.FindNode(42),nullptr);
}

TEST (NonEmptyTree,InsertNode) {
	for(int i=0;i<42;i++) {
		test_node = NonEmptyTree.InsertNode(i);
		ASSERT_TRUE (test_node.first);

		if(i == 5) test_ptr = test_node.second;														//Ukladanie hodnoty pre potreby testovania
	}

	test_node = NonEmptyTree.InsertNode(2805);
	EXPECT_TRUE	(test_node.first);

	test_node = NonEmptyTree.InsertNode(5);
	EXPECT_FALSE(test_node.first);
	EXPECT_EQ	(test_node.second,test_ptr);
}

TEST (NonEmptyTree,DeleteNode) {
	NonEmptyTree.InsertNode(20);

	EXPECT_TRUE	(NonEmptyTree.DeleteNode(20));
	EXPECT_FALSE(NonEmptyTree.DeleteNode(420));
}

TEST (NonEmptyTree,FindNode) {
	test_node = NonEmptyTree.InsertNode(4);
	test_ptr = NonEmptyTree.FindNode(4);
	EXPECT_EQ   (test_node.second, test_ptr);

	EXPECT_EQ   (NonEmptyTree.FindNode(2001), nullptr);
}

TEST (TreeAxioms,Axiom1) {
	NonEmptyTree.GetLeafNodes(leaf_pointers);

	for(int i=0;i<leaf_pointers.size();i++) {
		EXPECT_EQ (leaf_pointers[i]->color,BLACK);
	}
}

TEST (TreeAxioms,Axiom2) {
	NonEmptyTree.GetAllNodes(node_pointers);

	for(int i=0;i<node_pointers.size();i++){
		if(node_pointers[i]->color == RED)	{
			EXPECT_EQ (node_pointers[i]->pRight->color, BLACK);
			EXPECT_EQ (node_pointers[i]->pLeft->color, BLACK);	
		}
	}
}

TEST (TreeAxioms,Axiom3) {
	unsigned path_counter=0;
	unsigned previous_counter;

	Node_t *temp_ptr;

	NonEmptyTree.GetLeafNodes(leaf_pointers);

	for(int i=0;i<leaf_pointers.size();i++) {
		temp_ptr = leaf_pointers[i];																//Zabranenie prepisovaniu pola

		while(temp_ptr != NonEmptyTree.GetRoot()) {													//Cyklus: Kym nie sme pri koreni
			if (temp_ptr->color == BLACK) path_counter++;											//Podmienka: uzol je cierny -> zapocitaj ho do cesty
			temp_ptr = temp_ptr->pParent;
		}

		if(i == 0) previous_counter = path_counter;													//Testovanie OKREM prveho clena

		EXPECT_EQ (previous_counter,path_counter);
		previous_counter = path_counter;
		path_counter = 0;
	}
}

/*** Konec souboru black_box_tests.cpp ***/
