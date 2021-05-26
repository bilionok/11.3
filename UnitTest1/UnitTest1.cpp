#include "pch.h"
#include "CppUnitTest.h"
#include "../11_3/11_3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test.dat", ios::binary);
			Student student;
			student.spec = KN;
			student.avarage = 200.0;
			f.write((char*)&student, sizeof(Student));
			f.close();
			ifstream file("test.dat", ios::binary);
			int x = Search("test.dat");
			Assert::AreEqual(x, -1);
			f.close();
		}
	};
}
