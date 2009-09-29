#include <numeric>
#include <boost/array.hpp>
#include <iterator>
#include <iostream>


int main(int argc, char** argv) {

	{
		const int N = 10;
		boost::array<int, N> A;

		std::fill(A.begin(), A.end(), 1);
		std::cout << "A:		";
		std::copy(A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		std::cout << "Partial sums of A: ";
		std::partial_sum(A.begin(), A.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}

	{
		int A[] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
		const int N = sizeof(A) / sizeof(int);
		int B[N];

		std::cout << "A[]:         ";
		std::copy(A, A + N, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		std::adjacent_difference(A, A + N, B);
		std::cout << "Differences: ";
		std::copy(B, B + N, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;

		std::cout << "Reconstruct: ";
		std::partial_sum(B, B + N, std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
	return (EXIT_SUCCESS);
}
