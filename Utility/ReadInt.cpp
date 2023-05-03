#include <sys/stat.h>
#include <sys/mman.h>
   struct stat st; fstat(0, &st);
   char* p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
   auto readInt = [&]() {
      int ret = 0;
      for (char c = *p++; c & 16; ret = 10 * ret + (c & 15), c = *p++);
      return ret;
   };