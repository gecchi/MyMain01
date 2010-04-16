#include "stdafx.h"
using namespace std;

using namespace GgafCore;

// 出力関数
void GgafLogger::writeln(string prm_msg) {
    std::stringstream ss;
    ss << timeGetTime() << " <DEBUG> " << prm_msg << "\n";
    cout << ss.str() << flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
}

void GgafLogger::write(string prm_msg) {
    std::stringstream ss;
    ss << prm_msg;
    cout << ss.str() << flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
}
