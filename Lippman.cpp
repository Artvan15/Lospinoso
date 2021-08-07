#include <iostream>
#include <stdexcept>
#include <sstream>
#include <exception>
#include <functional>

#include "Tests.h"

using namespace std;


void RunTest(void(*test_function)(), const char* test_name)
{
	try
	{
		test_function();
		cout << "[+] " << test_name << " run successful\n";
	}
	catch(const exception& ex)
	{
		cout << "[-] " << test_name << " failed. " << ex.what() << endl;
	}
}





int main()
{
	RunTest(TestSpeed, "TestSpeed");
	RunTest(TestCollision, "TestCollision");
	RunTest(TestCollisionLess, "TestCollisionLess");
	RunTest(SpeedIsSaved, "SpeedIsSaved");
	RunTest(AlertWhenImminent, "AlertWhenImminent");
	
}

