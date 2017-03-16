#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>

using namespace std;

int main() {
    CPPUNIT_NS::TestResult tr;
    CPPUNIT_NS::TestResultCollector trc;

    tr.addListener(&trc);

    CPPUNIT_NS::BriefTestProgressListener btpl;
    tr.addListener(&btpl);

    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());

    testrunner.run(tr);

    CPPUNIT_NS::CompilerOutputter compileroutputter(&trc, cerr);
    compileroutputter.write();

    return 0;
}

