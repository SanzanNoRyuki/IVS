//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     ROMAN FULLA <xfulla00@stud.fit.vutbr.cz>
// $Date:       $2019-03-05
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author ROMAN FULLA
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

Matrix TestMatrix(5,5);

TEST (Matrix,set) {
	EXPECT_EQ (TestMatrix.set(0,0,10),true);
	EXPECT_EQ (TestMatrix.set(10,10,10),false);
}

TEST (Matrix,get) {
	TestMatrix.set(4,2,0);

	EXPECT_EQ (TestMatrix.get(4,2),0);
	EXPECT_NE (TestMatrix.get(4,2),5);
}

/*** Konec souboru white_box_tests.cpp ***/
