#include<cmath>
#include "vector.hpp"

double Vector::length() const {
    return sqrt(x*x + y*y + z*z);
}

Vector& Vector::normalize() {
    return *this = *this / length();
}

const double& Vector::operator[](size_t i) const { // see if i can have a error return if not recognized i value
    if (i == 0) {
        return x; 
    } else if (i == 1) {
        return y;
    } else {
        return z;
    }
}

std::ostream& operator<< (std::ostream& out, const Vector& vector) {
    return out << "Vector(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}


{
	// Place your snippets for cpp here. Each snippet is defined under a snippet name and has a prefix, body and 
	// description. The prefix is what is used to trigger the snippet and the body will be expanded and inserted. Possible variables are:
	// $1, $2 for tab stops, $0 for the final cursor position, and ${1:label}, ${2:another} for placeholders. Placeholders with the 
	// same ids are connected.
	// Example:
	// "Print to console": {
	// 	"prefix": "log",
	// 	"body": [
	// 		"console.log('$1');",
	// 		"$2"
	// 	],
	// 	"description": "Log output to console"
	// }
	"Print" : {
		"prefix": "sout", 
		"body" : [
			"std::cout << $1 << std::endl;",
			"$2"
		],
		"description": "prints to console"
	}

	"Include Guards" : {
		"prefix" : "guard", 
		"body" : [
			"#ifndef __${TM_FILENAME_BASE}_hpp_",
			"#define __${TM_FILENAME_BASE}_hpp_"
			"$1",
			"#endif\n"
		]
	}
}