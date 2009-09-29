

#include <iostream>

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <boost/bind.hpp>

using std::cout;

namespace nA {
	struct A {
		/*explicit*/ A(int id) : id_(id) {
		}
		int id_;
	};

	void f(A a) {
		cout << "nA::f(A) = " << a.id_ << "\n";
	}

	void swap(A &a1, A &a2) {
		cout << "swap a1 = " << a1.id_ << " a2 = " << a2.id_ << "\n";
		std::swap(a1, a2);
		cout << "swapped a1 = " << a1.id_ << " a2 = " << a2.id_ << "\n";
	};

	struct less : std::binary_function<A, A, bool> {
		bool operator()(const A &a1, const A &a2) const {
			std::cout << "nA::less(const A& " << a1.id_ << ", const A& " << a2.id_ << ")\n";
			return a1.id_ < a2.id_;
		};
	};

	bool cmp(const A &a1, const A &a2) {
		std::cout << "nA::cmp(const A& " << a1.id_ << ", const A& " << a2.id_ << ")\n";
		return a1.id_ < a2.id_;
	};

	std::ostream &operator<<(std::ostream &o, const A &a) {
		return o << "std::ostream &nA::operator<<(std::ostream &, const nA::A&)" << a.id_ << "\n";
	}

	bool operator<(const A &a1, const A &a2) {
		std::cout << "nA::operator<(const A& " << a1.id_ << ", const A& " << a2.id_ << ")\n";
		return a1.id_ < a2.id_;
	};
};

namespace nB {
	void f(nA::A a) {
		cout << "nB::f(nA::A a) = " << a.id_ << "\n";
	}

	struct less : std::binary_function<nA::A, nA::A, bool> {
		bool operator()(const nA::A &a1, const nA::A &a2) const {
			std::cout << "nB::less(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
			return a1.id_ > a2.id_;
		};
	};

	bool cmp(const nA::A &a1, const nA::A &a2) {
		std::cout << "nB::cmp(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
		return a1.id_ > a2.id_;
	};

	bool operator<(const nA::A &a1, const nA::A &a2) {
		std::cout << "nB::operator<(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
		return a1.id_ > a2.id_;
	};
};

void f(nA::A a) {
	cout << "::f(nA:A a) = " << a.id_ << "\n";
};


struct less : std::binary_function<nA::A, nA::A, bool> {
	bool operator()(const nA::A &a1, const nA::A &a2) const {
		std::cout << "::less(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
		return a1.id_ > a2.id_;
	};
};

bool cmp(const nA::A &a1, const nA::A &a2) {
	std::cout << "::cmp(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
	return a1.id_ > a2.id_;
};

bool operator<(const nA::A &a1, const nA::A &a2) {
	std::cout << "::operator<(const nA::A& " << a1.id_ << ", const nA::A& " << a2.id_ << ")\n";
	return a1.id_ > a2.id_;
};

//using namespace nB;

int inc(int &i) {
	return ++i;
}

int main(int argc, char **argv) {
	int a_counter = 0;
	nA::A a1(++a_counter);
	nA::A a2(++a_counter);
	::f(a1);
	nA::f(a1);
	nB::f(a1);

	swap(a1, a2);
	std::swap(a1, a2);

	cout << "________________________________________\n";

	std::vector<nA::A> vA;
	std::generate_n(std::back_inserter(vA), 10, boost::bind(&inc, boost::ref(a_counter)));
	vA.push_back(a2);
	vA.push_back(a1);
	std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	std::for_each(vA.begin(), vA.end(), f);
	std::for_each(vA.begin(), vA.end(), nA::f);
	std::for_each(vA.begin(), vA.end(), nB::f);

	bool b1 = nA::operator<(a1, a2);
	// bool b2 = a1 < a2;
	// bool b3 = a1 < a2;

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end());
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(), less());
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(), nA::less());
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(), cmp);
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(), nA::cmp);
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));

	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(),
	// 	  boost::bind(std::logical_not<bool>(), boost::bind(nA::less(), _1, _2)));
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));



	// cout << "________________________________________\n";
	// std::sort(vA.begin(), vA.end(),
	// 	  boost::bind(std::logical_not<bool>(), boost::bind(nA::less(), _1, _2)));
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));
	// cout << "________________________________________\n";
	// std::random_shuffle(vA.begin(), vA.end());
	// std::copy(vA.begin(), vA.end(), std::ostream_iterator<nA::A>(std::cout, ""));
	// cout << "________________________________________\n";
	// std::set<nA::A> sA(vA.begin(), vA.end());
	// std::copy(sA.begin(), sA.end(), std::ostream_iterator<nA::A>(std::cout, ""));
	// cout << "________________________________________\n";
	// std::set<nA::A, nA::less> sA1(vA.begin(), vA.end());
	// std::copy(sA1.begin(), sA1.end(), std::ostream_iterator<nA::A>(std::cout, ""));
};
