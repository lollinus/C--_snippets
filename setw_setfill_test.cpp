#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct indent {
	indent(int level) : level_(level) {}
	ostream& operator()(ostream& os) const {
		return os << setw(level_) << setfill(' ') << "";
	}
	int const level_;
};

ostream& operator<<(ostream& os, indent const& i) {
	return i(os);
}

//ostream &indent(ostream &o, int level) {
//	return o << setw(level) << setfill(' ') << " ";
//}

int main(int argc, char** argv) {

	int const indentSize = 4;
	int const indentLevel = 1;
	

	std::ostringstream out;
	out << setw(indentSize * indentLevel) << setfill(' ') << " " << "Hello cruel world\n" << " h " << indent(indentSize * indentLevel) << "e" << setw(indentSize * indentLevel) << "l" << setfill('-') << setw(10) << "12345890" << "o";
	out << indent(indentSize * indentLevel) << "contiues\n";

	cout << out.str();
	return EXIT_SUCCESS;
}
