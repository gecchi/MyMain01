#ifndef DETECT_MEMORY_LEAKS_H
#define DETECT_MEMORY_LEAKS_H
#ifdef _MSC_VER
    #pragma warning(disable: 4291)
#endif
/**
 * メモリリーク検出用
 * @version 1.00
 * @since 2008/08/21
 * @author Masatoshi Tsuge
 */


extern std::__map__<std::size_t, std::string> detectMemoryLeaksMemoryMap;

extern bool detectMemoryLeaksFlag;

void * operator new(std::size_t size, const char* strFileName, int nLineNum) throw (std::bad_alloc);

void * operator new[](std::size_t size, const char* strFileName, int nLineNum) throw (std::bad_alloc);

void operator delete(void * address);

void operator delete[](void * address);

void detectMemoryLeaksStart(std::ostream& ros);

void detectMemoryLeaksEnd(std::ostream& ros);

#endif // DETECT_MEMORY_LEAKS_H
