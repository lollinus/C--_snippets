#include <time.h>
#include <unistd.h>

#include <iostream>


int main(int argc, char** argv) {

	time_t tNow = time(0);
	sleep(1);
	time_t tNow1 = time(0);
		
	std::cout << "tNow = " << tNow << ", tNow1 = " << tNow1 << std::endl;
	std::cout << "difftime(tNow, tNow1) = " << difftime(tNow, tNow1) << std::endl;
	std::cout << "difftime(tNow1, tNow) = " << difftime(tNow1, tNow) << std::endl;
	return EXIT_SUCCESS;
}
