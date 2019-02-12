#include "jp/ggaf/core/util/Logger.h"

#include <iostream>
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

using namespace GgafCore;

void Logger::writeln(std::stringstream& prm_ssmsg) {
    std::stringstream ss;
    ss << timeGetTime() << " <DEBUG> " << prm_ssmsg.str() << "\n";
#ifdef _MSC_VER
    std::cout << ss.str() << std::flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
#else
    std::cout << ss.str() << std::flush;
#endif
}

void Logger::write(std::stringstream& prm_ssmsg) {
#ifdef _MSC_VER
    std::cout << prm_ssmsg.str() << std::flush;
    OutputDebugStringA((LPSTR)(prm_ssmsg.str().c_str()));
#else
    std::cout << prm_ssmsg.str() << std::flush;
#endif
}
