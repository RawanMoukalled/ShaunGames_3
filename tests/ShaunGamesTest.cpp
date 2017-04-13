#include "shaungamestest.h"
#include "../game1/sheep1.h"
#include "../helper.h"

CPPUNIT_TEST_SUITE_REGISTRATION (ShaunGamesTest);


ShaunGamesTest::ShaunGamesTest()
{
}

void ShaunGamesTest::setUp() {
	a = 90;
	b = 185;
	c = Sheep1::getRandomSheepNumber();
}

void listTest::tearDown() {

}

void listTest::toRadiansTest() {
    CPPUNIT_ASSERT_EQUAL (true, qAbs(Helper::toRadians(a) - 1.571) < 0.01);
    CPPUNIT_ASSERT_EQUAL (true, qAbs(Helper::toRadians(b) - 3.229) < 0.01);
}

void ShaunGamesTest::getRandomSheepNumberTest() {
    CPPUNIT_ASSERT_EQUAL (true, c >=1 && c < 10);
}


