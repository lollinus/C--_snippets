/************************************************************
 *
 *	Copyright (c) Nokia Siemens Networks 2009
 *
 ************************************************************/

/**
 *  @file   boost_shared_ptr.cpp
 *  @brief  examples of shared_ptr usage with custom deleter
 *  @author Karol Barski
 *  @date   Thu Sep 17 09:09:41 2009
 *
 *  @history
 *  @item Thu Sep 17 09:09:41 2009 Karol Barski: Created
 *
 */

#include <boost/shared_ptr.hpp>
#include <iostream>

using std::cout;

struct A {
	A(int id) : id_(id){
		cout << "A::A(" << id_ << ")\n";
	};
	~A() {
		cout << "A::~A " << id_ << "\n";
	};
	const int id_;
};

struct CustomDeleter : std::unary_function<A, void> {
	void operator()(A *a) const {
		if(a) {
			std::cout << "CustomDeleter A(" << a->id_ << ")\n";
			delete a;
		} else {
			std::cout << "CustomDeleter A(NULL)\n";
		}
	};
};

struct LeaveDeleter : std::unary_function<A, void> {
	void operator()(A *a) const {
		if(a) {
			std::cout << "LeaveDeleter A(" << a->id_ << ")\n";
		} else {
			std::cout << "LeaveDeleter A(NULL)\n";
		}
	};
};

int main(int argc, char ** argv) {
	int counter = 0;
	A a(++counter);
	boost::shared_ptr<A> pA1(&a, LeaveDeleter());
	boost::shared_ptr<A> pA2(new A(++counter));
	boost::shared_ptr<A> pA3(new A(++counter), CustomDeleter());

	cout << "________________________________________\n";

	boost::shared_ptr<A> pA1C = pA1;
	boost::shared_ptr<A> pA2C = pA2;
	boost::shared_ptr<A> pA3C = pA3;

	cout << "________________________________________\n";
	pA1 = pA2;
	pA2 = pA3;
	cout << "pA1C.reset()\n";
	pA1C.reset();
	cout << "pA2C.reset()\n";
	pA2C.reset();
	cout << "pA3C.reset()\n";
	pA3C.reset();
	cout << "pA3.reset()\n";
	pA3.reset();
	cout << "pA1.reset()\n";
	pA1.reset();
	cout << "pA2.reset()\n";
	pA2.reset();
	cout << "________________________________________\n";
}
