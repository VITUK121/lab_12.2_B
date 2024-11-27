#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12.2_B/lab_12.2_B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest122B
{
	TEST_CLASS(UnitTest122B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(calc_n(1000), 4);
		}
	};
}
