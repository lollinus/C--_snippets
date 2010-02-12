/**
 * Program to chek behaviour of snprintf function when buffer is too short to contain whole formatted string
 *
 */
#include <stdio.h>

int snprintf(char*, int, char*, ...);

int main(int argc, char** argv) {
	
	char buf[5];
	char const * const s1234 = "1234";
	char const * const s12345 = "12345";
	char const * const s123456 = "123456";

	int result = snprintf(buf, sizeof(buf), "%s", s1234);
	if(result>=sizeof(buf)) {
		buf[sizeof(buf)] = '\0';
		printf("buffer too short, setting null at buffer end\n");
	};

	printf("%s result: %d\n", buf, result);

	if((result=snprintf(buf, sizeof(buf), "%s", s12345))>=sizeof(buf)) {
		buf[sizeof(buf)] = '\0';
		printf("buffer too short, setting null at buffer end\n");
	};

	printf("%s result: %d\n", buf, result);

	if((result=snprintf(buf, sizeof(buf), "%s", s123456))>=sizeof(buf)) {
		buf[sizeof(buf)] = '\0';
		printf("buffer too short, setting null at buffer end\n");
	};

	printf("%s result: %d\n", buf, result);

	return 0;
}
