#include "../../MyStg2nd/src/MyStg2ndHeader.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

int main() {
	char rankstr[80];
	MyStgUtil::getRankStr(1111, (char*)rankstr);
	_TRACE_(rankstr);
}




int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
