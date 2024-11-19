#pragma once

#undef assertUnit
#undef assertIndirect
#undef assertComplexFixture
#undef assertStandardFixture
#undef assertEmptyFixture

#define assertEquals(value, test) assertUnitParameters(closeEnough(value, test), #test, __LINE__, __FUNCTION__)
#define assertUnit(condition)              assertUnitParameters(condition, #condition, __LINE__, __FUNCTION__)

#include <iostream>  // for std::cerr
#include <iomanip>   // for std::setw
#include <string>    // for std::string
#include <vector>    // for std::vector
#include <map>       // for std::map

class UnitTest
{
public:
    UnitTest() { reset(); }

private:
    // a test failure is a failure string and a line number
    struct Failure
    {
        std::string failure;
        int         lineNumber;
    };

    // each test has a name (the key) and the list of failures(value).
    std::map<std::string, std::vector<Failure>> tests;

protected:



    // for closeEnough() and assertEquals(), what is the tolerance?
    double tolerance = 0.0001;

    // utility function because floating point numbers are approximations
    bool closeEnough(double value, double test) const
    {
        double difference = value - test;
        return (difference >= -tolerance) && (difference <= tolerance);
    }

    /*************************************************************
     * RESET
     * Reset the statistics
     *************************************************************/
    void reset()
    {
        tests.clear();
    }

    /*************************************************************
     * REPORT
     * Report the statistics
     *************************************************************/
    void report(const char* name)
    {
        // enumerate the failures, if there are any
        for (auto& test : tests)
            if (!test.second.empty())
            {
                std::cout << "\t" << test.first << "()\n";
                for (auto& failure : test.second)
                    std::cout << "\t\tline:" << failure.lineNumber
                    << " condition:" << failure.failure << "\n";
            }

        // name the test case
        std::cout << std::left << std::setw(15) << name << ":\t";

        // handle the no test case
        if (tests.empty())
        {
            std::cout << "There were no tests]\n";
            return;
        }

        // determine the success rate
        int numSuccess = 0;
        for (auto& test : tests)
            numSuccess += (test.second.empty() ? 1 : 0);
        double successRate = (double)numSuccess / (double)tests.size();

        // display the summary
        std::cout.setf(std::ios::fixed | std::ios::showpoint);
        std::cout.precision(1);
        std::cout << "There were "
            << tests.size()
            << " tests run for a success rate of: "
            << (successRate * 100.0) << "%\n";

        // after we have reported, the reset for the next report
        reset();
    }

    /*************************************************************
     * ASSERT UNIT PARAMETERS
     * Custom assert code so we can see all the errors at once
     *************************************************************/
    void assertUnitParameters(bool condition, const char* conditionString,
        int line, const char* func)
    {
        std::string sFunc(func);

        if (!condition)
        {
            // add a failure to the list of failures
            Failure failure{ std::string(conditionString), line };
            tests[sFunc].push_back(failure);
        }
        else
        {
            // this ensures there is a placeholder for the successful test
            tests[sFunc];
        }
    }


    /*************************************************************
     * VERIFY
     * Simple verification of condition
     *************************************************************/
    void verify(bool condition, const char* function)
    {
        std::string sFunc(function);
        if (!condition)
        {
            Failure failure{ "Failed", __LINE__ };
            tests[sFunc].push_back(failure);
        }
        else
        {
            tests[sFunc]; // Register successful test
        }
    }

};