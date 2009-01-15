#include "stdafx.h"

using namespace Ggaf;

// o—ÍŠÖ”
void GgafLogger::write(string prm_msg) {
	std::stringstream ss;
	ss << timeGetTime() << " <DEBUG> " << prm_msg << "\n";
	cout << ss.str() << flush;
    OutputDebugStringA((LPSTR)(ss.str().c_str()));
}

