#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int unlinkat(int dirfd, const char* pathname, int flags) {
	if (strstr(pathname, "FIX")) {
		errno = EPERM;
		return -1;
	}
	
	int (*f)() = dlsym(RTLD_NEXT, "unlinkat");
	return f(dirfd, pathname, flags);
}