#include "util.h"

typedef struct Result {
	String s;
	bool error;
} Result;

Result pcre_process(String pattern, String text);
