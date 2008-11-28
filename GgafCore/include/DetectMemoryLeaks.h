// Detect Memory Leaks.

#ifndef DETECT_MEMORY_LEAKS_H
#define DETECT_MEMORY_LEAKS_H

extern std::map<std::size_t, std::string> detectMemoryLeaksMemoryMap;

extern bool detectMemoryLeaksFlag;

void * operator new(std::size_t size, char* strFileName, int nLineNum);// throw (std::bad_alloc);

void * operator new[](std::size_t size, char* strFileName, int nLineNum);// throw (std::bad_alloc);

void operator delete(void * address);

void operator delete[](void * address);

void detectMemoryLeaksStart(std::ostream& ros);

void detectMemoryLeaksEnd(std::ostream& ros);

#endif // DETECT_MEMORY_LEAKS_H
