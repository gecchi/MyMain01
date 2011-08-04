#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


#define MAX_SP_POINT 1000

SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _accuracy = 1.0;
    _spent_frame = 1;
    _ang_veloRzRyMv = 0;
    _classname = "";
    string data_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
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
        if (line.find("[CLASS]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> _classname;
                if (_classname == "FixedFrameSplineProgram") {
                    iss >> _spent_frame;
                    iss >> _ang_veloRzRyMv;
                } else if (_classname == "FixedVelocitySplineProgram") {
                    iss >> _ang_veloRzRyMv;
                    _spent_frame = 0;
                }
            }
        }
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
    if (_classname.length() == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" _classname が指定されてません。");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ポイントがありません。");
    }
#endif
    //-1.0 ～ 1.0 が 自機の移動可能範囲とする
    for (int i = 0; i < n; i++) {
//        p[i][0] = p[i][0] * MyShip::_lim_front; //X
//        p[i][1] = p[i][1] * MyShip::_lim_top;   //Y
//        p[i][2] = p[i][2] * MyShip::_lim_zleft; //Z

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
        if (p[i][2] < GgafDx9Universe::_Z_goneFar*0.9) {
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
//
//[CLASS]
//FixedFrameSplineProgram 420 6000
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
//[CLASS]
//スプラインクラスを指定する。構文は以下の２種類のみ
//-------------------------------------------------------------
//FixedFrameSplineProgram <spent_frame> <ang_veloRzRyMv>
//又は
//FixedVelocitySplineProgram <ang_veloRzRyMv>
//-------------------------------------------------------------
//
//FixedFrameSplineProgram ・・・ スプラインの開始点～終了点の移動を、時間(フレーム)固定で移動させる。
//<spent_frame>   ・・・ 費やすフレーム数
//<ang_veloRzRyMv> ・・・ 毎フレーム方向転換可能な最大角(1000 で 1度）
//各キャラが保持している移動速度は無視されます。
//スプライン曲線の点の個数と費やすフレーム数から計算された移動速度が逐一キャラの速度値に上書き設定されます。
//このため、スプライン曲線の点の密度が濃いところはスピードが遅く、点の密度が薄いところはスピードが速い移動となります。
//
//FixedVelocitySplineProgram ・・・ スプラインの開始点～終了点の移動を、速度固定で移動させる。
//<ang_veloRzRyMv> ・・・ 毎フレーム方向転換可能な最大角(1000 で 1度）
//各キャラが保持している移動速度がずっと使用されます。
//スプライン曲線の点の密度がスピードに影響しません。



SplineProgram* SplineSource::makeSplineProgram(GgafDx9GeometricActor* prm_pForWhichActor) {
    SplineProgram* pSpProg = NULL;
    if (_classname.find("FixedFrameSplineProgram") != string::npos) {
        pSpProg = NEW FixedFrameSplineProgram(prm_pForWhichActor, _pSp, _spent_frame, _ang_veloRzRyMv);
    } else if (_classname.find("FixedVelocitySplineProgram") != string::npos) {
        pSpProg = NEW FixedVelocitySplineProgram(prm_pForWhichActor, _pSp, _ang_veloRzRyMv);
    } else {
        throwGgafCriticalException("SplineSource::makeSplineProgram _classname="<<_classname<< "は不明なクラスです");
    }
    return pSpProg;
}

SplineSource::~SplineSource() {
    DELETE_IMPOSSIBLE_NULL(_pSp);
}
