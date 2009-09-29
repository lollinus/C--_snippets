/**
 *  @file   shared_ptr_custom_deleter_test.cpp
 *  @brief  Test program for custom deleter taking argument as pointer to pointer
 *  @author Karol Barski
 *  @date   Fri Sep 11 12:56:20 2009
 *
 *  @par history
 *  @li Fri Sep 11 12:56:20 2009 Karol Barski: Created
 *
 */

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>


struct TestStruct
{
	explicit TestStruct(int counter)
		: counter_(counter)
	{
		std::cout << "TestStruct create " << counter_ << "\n";
	};

	~TestStruct()
	{
		std::cout << "TestStruct destroy " << counter_ << "\n";
	}
private:
	int counter_;
};


TestStruct *createTest(int counter)
{
	return new TestStruct(counter);
}

void deleteTest1(TestStruct *test)
{
	if(!test)
	{
		std::cout << __func__ << "Null contained pointer passed\n";
	}

	delete test;
}

void deleteTest2(TestStruct **test)
{
	if(!test)
	{
		std::cout << __func__ << "Null pointer passed\n";
	}

	if(!*test)
	{
		std::cout << __func__ << "Null contained pointer passed\n";
	}

	delete *test;
	*test = 0;
}

TestStruct **derefPtr(TestStruct *&test)
{
	if(!test)
	{
		return 0;
	}
	return &test;
}

int main(int argc, char **argv)
{
	int testCount = 0;
	boost::shared_ptr<TestStruct> testPtr(createTest(++testCount), &deleteTest1);

	boost::shared_ptr<TestStruct> testPtr1(createTest(++testCount),
					      boost::bind(&deleteTest1,
							  _1
						      ));

	boost::shared_ptr<TestStruct> testPtr2(createTest(++testCount),
					      boost::bind(&deleteTest2,
							  boost::bind(&derefPtr, _1)
						      ));

	boost::shared_ptr<TestStruct> testPtr3(createTest(++testCount),
					      boost::bind(&deleteTest2,
							  boost::bind(&boost::addressof<TestStruct*>,
								      _1)
						      ));

	std::cout << "working\n";

}
