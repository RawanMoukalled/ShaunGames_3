#ifndef SHAUNGAMESTEST_H
#define SHAUNGAMESTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class ShaunGamesTest : public CPPUNIT_NS :: TestFixture

{

    CPPUNIT_TEST_SUITE (ShaunGamesTest);
    CPPUNIT_TEST (toRadiansTest);
    CPPUNIT_TEST (getRandomSheepNumberTest);
    CPPUNIT_TEST_SUITE_END ();


public:
    ShaunGamesTest();
    void setUp ();
    void tearDown ();
protected:
    void toRadiansTest ();
    void getRandomSheepNumberTest ();
private:
    double a,b;
    int c;

};

#endif // SHAUNGAMESTEST_H

