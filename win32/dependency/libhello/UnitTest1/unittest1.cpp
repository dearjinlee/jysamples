#include "stdafx.h"
#include "CppUnitTest.h"
#include <assert.h>
#include "hello.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: �׽�Ʈ �ڵ带 ���⿡ �Է��մϴ�.

			assert(1 == 1);
			hello();
		}

	};
}