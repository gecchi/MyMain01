#include "jp/ggaf/core/util/GgafLogger.h"

#include <iostream>
#include <windows.h>

using namespace GgafCore;

void GgafLogger::writeln(std::stringstream& prm_ssmsg) {
    std::stringstream ss;
    ss << timeGetTime() << " <DEBUG> " << prm_ssmsg.str() << "\n";
#ifdef _MSC_VER
    std::cout << ss.str() << std::flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
#else
    std::cout << ss.str() << std::flush;
#endif
}

void GgafLogger::write(std::stringstream& prm_ssmsg) {
#ifdef _MSC_VER
    std::cout << prm_ssmsg.str() << std::flush;
    OutputDebugStringA((LPSTR)(prm_ssmsg.str().c_str()));
#else
    std::cout << prm_ssmsg.str() << std::flush;
#endif
}
