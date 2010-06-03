/* gcc -g -o dlerror_memleak dlerror_memleak.c -ldl -lpthread */

#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char* argv[])
  {
    void* obj;
    int ret;

    if (argc < 2)
      {
	fprintf(stderr, "Warning: Calling `dlopen' on self\n");
      }

    obj = dlopen(argv[1], RTLD_LAZY);
    if (!obj)
      {
	fprintf(stderr, "Error: Failed to open `%s'\n", argv[1]);
	return 1;
      }

    ret = dlclose(obj);
    if (ret)
      {
	fprintf(stderr, "Error: Failed to close `%s'\n", argv[1]);
	return 1;
      }

    return 0;
  }

