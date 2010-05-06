#include "stdafx.h"
using namespace std;

using namespace GgafCore;

void GgafLogger::writeln(stringstream& prm_ssmsg) {
    std::stringstream ss;
    ss << timeGetTime() << " <DEBUG> " << prm_ssmsg.str() << "\n";
#ifdef _MSC_VER
    cout << ss.str() << flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
#else
    cout << ss.str() << flush;
#endif
}

void GgafLogger::write(stringstream& prm_ssmsg) {
#ifdef _MSC_VER
    cout << prm_ssmsg.str() << flush;
    OutputDebugStringA((LPSTR)(prm_ssmsg.str().c_str()));
#else
    cout << prm_ssmsg.str() << flush;
#endif
}
