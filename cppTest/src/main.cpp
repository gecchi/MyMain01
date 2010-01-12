//#include "../../MyStg2nd/src/MyStg2ndHeader.h"
#include "../../GgafCore/include/GgafCommonHeader.h"
using namespace std;

using namespace GgafCore;
//using namespace GgafDx9Core;
//using namespace GgafDx9LibStg;
//using namespace MyStg2nd;

int main() {
    //char rankstr[80];

    char moji[] = { '\0','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                    '1','2','3','4','5','6','7','8','9','0','_',' ', '\0'};
    int len = strlen(moji);
    char str[256];
    for (int q = 0; q < 256; q++) {
        str[q] = '\0';
    }




    for (int n = 1; n < len; n++) {
        str[n] = n;
        for (int j = 1 ; j < len; j++) {
            str[i] =  moji[j];
            unsigned int u = GgafUtil::easy_hash(str);
            _TRACE_(str<<"="<<u);
        }
    }


 }




int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
