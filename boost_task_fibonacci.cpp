#include <iostream>
#include <boost/task.hpp>

long fibonacci(long n) {
	if ( n==0) return 0;
	if ( n==1) return 1;
	long k1(1), k2(0);
	for(int i(2); i<=n; ++i) {
		long tmp(k1);
		k1 = k1 + k2;
		k2 = tmp;
	}
	return k1;
}

int main(int argc, char** argv)
{
	// create a thread-pool
	boost::task::static_pool< boost::task::unbounded_twolock_fifo > > pool(boost::task::poolsize(5));

	// execute tasks in thread-pool
	// move tasks ownership to executor
	boost::task::handle< long > h1(
		boost::task::async(
			boost::task::make_task( fibonacci, 10),
			pool);
	boost::task::handle<long> h2(
		boost::task::async(
			boost::task::make_task( fibonacci, 5),
			boost::move(t2),
			pool);

	std::cout << "h1: is ready == " << std::boolalpha << h1.is_ready() << "\n";
	std::cout << "h2: is ready == " << std::boolalpha << h2.is_ready() << "\n";

	// wait for completion of both tasks
	boost::task::waitfor_all( h1, h2);

	std::cout << "h1: is ready == " << std::boolalpha << h1.is_ready() << "\n";
	std::cout << "h2: is ready == " << std::boolalpha << h2.is_ready() << "\n";
	std::cout << "h1: has value == " << std::boolalpha << h1.has_value() << "\n";
	std::cout << "h2: has value == " << std::boolalpha << h2.has_value() << "\n";
	std::cout << "h1: has exception == " << std::boolalpha << h1.has_exception() << "\n";
	std::cout << "h2: has exception == " << std::boolalpha << h2.has_exception() << "\n";

	// get results
	std::cout << "fibonacci(10) == " << h1.get() << std::endl;
	std::cout << "fibonacci(5) == " << h2.get() << std::endl;
} 

