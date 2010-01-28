#include "../../MyStg2nd/src/MyStg2ndHeader.h"
//#include "../../GgafCore/include/GgafCommonHeader.h"
using namespace std;

using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



void getAnother(int rz1,int ry1) {

	int rz2, ry2;
	if (0 <= rz1 && rz1 < 90) {
		rz2 = 180 - rz1;

		if (0 <= ry1 && ry1 < 180) {
			ry2 = ry1 + 180;
		} else {
			ry2 = ry1 - 180;
		}
	} else if (90 <= rz1 && rz1 < 180) {
		rz2 = 180 - rz1;
		if (0 <= ry1 && ry1 < 180) {
			ry2 = ry1 + 180;
		} else {
			ry2 = ry1 - 180;
		}
	} else if (180 <= rz1 && rz1 < 270) {

		rz2 = 180 + (360 - rz1);
		if (0 <= ry1 && ry1 < 180) {
			ry2 = ry1 + 180;
		} else {
			ry2 = ry1 - 180;
		}
	} else if (270 <= rz1 && rz1 <= 360) {
		rz2 = 180 + (360 - rz1);
		if (0 <= ry1 && ry1 < 180) {
			ry2 = ry1 + 180;
		} else {
			ry2 = ry1 - 180;
		}
	}

	if (rz1+ry1 > rz2+ry2) {
		_TEXT_("Å~"<<rz1<<","<<ry1<<" = Åõ"<<rz2<<","<<ry2);
	} else if (rz1+ry1 < rz2+ry2) {
		_TEXT_("Åõ"<<rz1<<","<<ry1<<" = Å~"<<rz2<<","<<ry2);
	} else {
		_TEXT_("Å¢"<<rz1<<","<<ry1<<" = Å¢"<<rz2<<","<<ry2);
	}



}
int main() {
	GgafDx9Util::init();
				angle Rz,Ry;
				float x,y,z;
	for (int i = 0; i <= 360; i+=10) {
		for (int j = 0; j <= 360; j+=10) {
			getAnother(i,j);


			GgafDx9Util::getNormalizeVectorZY(i*1000,j*1000,x,y,z);
			//_TRACE_("getNormalizeVectorZY="<<(int)(xx*10000)<<","<<(int)(y*10000)<<","<<(int)(z*10000));
			GgafDx9Util::getRzRyAngle((int)(x*10000), (int)(y*10000), (int)(z*10000), Rz, Ry);
			_TEXT_(" >> "<<(int)(Rz/1000)<<","<<(int)(Ry/1000)<<" (");getAnother((int)(Rz/1000),(int)(Ry/1000));
			_TEXT_(")\n");
		}
	}
 
    //super->hoge(((Base* )base));

}

int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
