#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


#define MAX_SP_POINT 1000

SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _accuracy = 1.0;
    _classname = "";
    string data_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr);// + ".spls";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" が開けません");
    }
    double p[MAX_SP_POINT][3];
    string line;
    int n = 0;
    while( getline(ifs,line) ) {
        if (line.size() == 0 ) continue;
        if (line.c_str()[0] == '#') continue;

        LOOP_SPLFILE:

        if (line.find("[BASEPOINT]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
#ifdef MY_DEBUG
                if (n >= MAX_SP_POINT) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ポイントが"<<MAX_SP_POINT<<"を超えました。");
                }
#endif
            }
        }
        if (line.find("[ACCURACY]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> _accuracy;
            }
        }
    }
#ifdef MY_DEBUG
    if (int(_accuracy*100000000) == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" [ACCURACY] が指定されてません。");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" [BASEPOINT] に座標がありません。");
    }
#endif
    for (int i = 0; i < n; i++) {
        if (p[i][0] > GgafDx9Universe::_X_goneRight*0.9) {
            p[i][0] = GgafDx9Universe::_X_goneRight*0.9;
        }
        if (p[i][0] < GgafDx9Universe::_X_goneLeft*0.9) {
            p[i][0] = GgafDx9Universe::_X_goneLeft*0.9;
        }
        if (p[i][1] > GgafDx9Universe::_Y_goneTop*0.9) {
            p[i][1] = GgafDx9Universe::_Y_goneTop*0.9;
        }
        if (p[i][1] < GgafDx9Universe::_Y_goneBottom*0.9) {
            p[i][1] = GgafDx9Universe::_Y_goneBottom*0.9;
        }
        if (p[i][2] > GgafDx9Universe::_Z_goneFar*0.9) {
            p[i][2] = GgafDx9Universe::_Z_goneFar*0.9;
        }
        if (p[i][2] < GgafDx9Universe::_Z_goneNear*0.9) {
            p[i][2] = GgafDx9Universe::_Z_goneNear*0.9;
        }
    }
    _pSp = NEW Spline3D(p, n, _accuracy);
}

//＜説明＞
//コンストラクタで読み込む spl ファイルのフォーマット
//--------------------------------------------
//[BASEPOINT]
//#       X         Y         Z
//-1.724577  0.000000  0.000000
//-0.964337 -0.088378 -0.344892
//-0.501305 -0.055518 -0.298879
//-0.179336 -0.031628 -0.240141
// 0.123544 -0.016126 -0.165195
// 0.362343  0.000000  0.000000
// 0.545634  0.038709  0.176104
// 0.704048  0.173192  0.372772
// 0.864812  0.444651  0.516556
// 1.055714  0.626849  0.569336
// 1.246407  0.655359  0.547772
// 1.365876  0.590994  0.453279
// 1.388259  0.465998  0.332581
// 1.362117  0.328636  0.211183
// 1.242692  0.226675  0.087900
// 1.064405  0.202917  0.000000
// 0.920421  0.202917  0.000000
//
//[ACCURACY]
//0.2
//--------------------------------------------

//[BASEPOINT]
//スプライン曲線上の基点を X Y Z で設定。
//指定できるポイント数は最大1000個まで
//自機の移動範囲を -1.0 ～ 1.0 として設定する。
//但し、このスプライン座標は、絶対座標として移動を行うキャラも居るし、
//始点をキャラの現時点の座標とおき、基点は相対座標として移動するキャラも居る、
//それらの設定は各キャラのプログラムに組み込まれており、ココでの指定は不可。
//
//[ACCURACY]
//スプライン曲線の精度。BASEPOINTで指定した基点～基点の間にどのくらいの補完点を追加して、折れ線をなめらかな曲線に近づけるかという割合。
//1.0  を指定すると基点～基点の間に補完点は挿入されず、BASEPOINT指定通りのままとなる。
//0.5  を指定すると各基点～基点について、2分割される点に補完点が計算されて挿入される。(つまり補完点は1個挿入される)
//0.25 を指定すると各基点～基点について、4分割される点に補完点が計算されて挿入される。(つまり補完点は3個挿入される)
//0.1  を指定すると各基点～基点について、10分割される点に補完点が計算されて挿入される。(つまり補完点は9個挿入される)
//0.01 を指定すると各基点～基点について、100分割される点に補完点が計算されて挿入される。(つまり補完点は99個挿入される)
//といった具合。
//

SplineSource::~SplineSource() {
    DELETE_IMPOSSIBLE_NULL(_pSp);
}
