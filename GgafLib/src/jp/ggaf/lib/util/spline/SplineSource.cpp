#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


SplineSource::SplineSource(SplineLine* prm_pSp) : GgafObject() {
    _idstr = "Nothing";
    _pSp = prm_pSp;
    _accuracy = _pSp->_accuracy;
    _is_create_SplineLine = false;
}

SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _idstr = std::string(prm_idstr);
    _accuracy = 1.0;
    std::string data_filename = PROPERTY::DIR_SPLINE + _idstr;// + ".spls";
    std::ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<data_filename<<" が開けません");
    }
    double p[MaxSplineSize][3];
    std::string line;
    int n = 0;
    while( getline(ifs,line) ) {
        if (UTIL::trim(line).size() == 0 ) continue;
        if (line.c_str()[0] == '#') continue;

        LOOP_SPLFILE:

        if (line.find("[BASEPOINT]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) {
                    break;
                }
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
                if (n >= MaxSplineSize) {
                    throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" ポイントが"<<MaxSplineSize<<"を超えました。");
                }
            }
        }
        if (line.find("[ACCURACY]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                iss >> _accuracy;
            }
        }
    }
    if (int(_accuracy*100000000) == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [ACCURACY] が指定されてません。");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<_idstr<<" [BASEPOINT] に座標がありません。");
    }
    for (int i = 0; i < n; i++) {
        if (p[i][0] > GgafDxUniverse::_X_goneRight*0.9999) {
            p[i][0] = GgafDxUniverse::_X_goneRight*0.9999;
        }
        if (p[i][0] < GgafDxUniverse::_X_goneLeft*0.9999) {
            p[i][0] = GgafDxUniverse::_X_goneLeft*0.9999;
        }
        if (p[i][1] > GgafDxUniverse::_Y_goneTop*0.9999) {
            p[i][1] = GgafDxUniverse::_Y_goneTop*0.9999;
        }
        if (p[i][1] < GgafDxUniverse::_Y_goneBottom*0.9999) {
            p[i][1] = GgafDxUniverse::_Y_goneBottom*0.9999;
        }
        if (p[i][2] > GgafDxUniverse::_Z_goneFar*0.9999) {
            p[i][2] = GgafDxUniverse::_Z_goneFar*0.9999;
        }
        if (p[i][2] < GgafDxUniverse::_Z_goneNear*0.9999) {
            p[i][2] = GgafDxUniverse::_Z_goneNear*0.9999;
        }
    }
    _pSp = NEW SplineLine(p, n, _accuracy);
    _is_create_SplineLine = true;
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
//スプライン曲線上の制御点を X Y Z で設定。
//指定できるポイント数は最大1000個まで
//自機の移動範囲を -1.0 ～ 1.0 として設定する。
//但し、このスプライン座標は、絶対座標として移動を行うキャラも居るし、
//始点をキャラの現時点の座標とおき、制御点は相対座標として移動するキャラも居る、
//それらの設定は各キャラのプログラムに組み込まれており、ココでの指定は不可。
//
//[ACCURACY]
//スプライン曲線の精度。BASEPOINTで指定した制御点～制御点の間にどのくらいの補完点を追加して、折れ線をなめらかな曲線に近づけるかという割合。
//1.0  を指定すると制御点～制御点の間に補完点は挿入されず、BASEPOINT指定通りのままとなる。
//0.5  を指定すると各制御点～制御点について、2分割される点に補完点が計算されて挿入される。(つまり補完点は1個挿入される)
//0.25 を指定すると各制御点～制御点について、4分割される点に補完点が計算されて挿入される。(つまり補完点は3個挿入される)
//0.1  を指定すると各制御点～制御点について、10分割される点に補完点が計算されて挿入される。(つまり補完点は9個挿入される)
//0.01 を指定すると各制御点～制御点について、100分割される点に補完点が計算されて挿入される。(つまり補完点は99個挿入される)
//といった具合。
//

SplineSource::~SplineSource() {
    if (_is_create_SplineLine) {
        DELETE_IMPOSSIBLE_NULL(_pSp);
    }
}
