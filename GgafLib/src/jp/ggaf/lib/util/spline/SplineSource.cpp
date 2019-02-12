#include "jp/ggaf/lib/util/spline/SplineSource.h"

#include <fstream>
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/util/StgUtil.h"



using namespace GgafLib;

SplineSource::SplineSource() : GgafCore::Object() {
    _x_basepoint = nullptr;
    _y_basepoint = nullptr;
    _z_basepoint = nullptr;
    _num_basepoint = 0;
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    _rnum = 0;
    _accuracy = 1.0;
    _coord_data_file = NEW char[13+1];
    strcpy(_coord_data_file, "nothing_idstr");
    _coord_data_file[13] = '\0';
}

SplineSource::SplineSource(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) : GgafCore::Object() {
    _coord_data_file = NEW char[13+1];
    strcpy(_coord_data_file, "nothing_idstr");
    _coord_data_file[13] = '\0';
    init(prm_paaEstablish, prm_num, prm_accuracy);
}

SplineSource::SplineSource(double prm_paaEstablish[][3], int prm_num, double prm_accuracy, RotMat& prm_rotmat) : GgafCore::Object() {
    _coord_data_file = NEW char[13+1];
    strcpy(_coord_data_file, "nothing_idstr");
    _coord_data_file[13] = '\0';
    _rotmat = prm_rotmat;
    init(prm_paaEstablish, prm_num, prm_accuracy);
}

SplineSource::SplineSource(const char* prm_coord_data_file) : GgafCore::Object() {
    int len = strlen(prm_coord_data_file);
    _coord_data_file = NEW char[len+1];
    strcpy(_coord_data_file, prm_coord_data_file);

    double accuracy = 1.0;
    std::string data_filename = CONFIG::DIR_SPLINE + _coord_data_file;// + ".spls";
    std::ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwCriticalException(data_filename<<" が開けません");
    }
    double p[MaxSplineSize][3];
    std::string line;
    int n = 0;
    int d = 0;
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
                if (iss.fail()) {
                    throwCriticalException(_coord_data_file<<" [BASEPOINT]不正な数値データです line=["<<line<<"]");
                }
                n++;
                if (n >= MaxSplineSize) {
                    throwCriticalException(_coord_data_file<<" ポイントが"<<MaxSplineSize<<"を超えました。");
                }
            }
        }
        if (line.find("[ACCURACY]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                iss >> accuracy;
                if (iss.fail()) {
                    throwCriticalException(_coord_data_file<<" [ACCURACY]不正な数値データです line=["<<line<<"]");
                }
            }
        }
        if (line.find("[ADJUST_MAT]") != std::string::npos) {
            while( getline(ifs,line) ) {
                if (UTIL::trim(line).size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                std::istringstream iss(line);
                if (d == 0) {
                    iss >> _rotmat._11; iss >> _rotmat._12; iss >> _rotmat._13; iss >> _rotmat._14;
                } else if (d == 1) {
                    iss >> _rotmat._21; iss >> _rotmat._22; iss >> _rotmat._23; iss >> _rotmat._24;
                } else if (d == 2) {
                    iss >> _rotmat._31; iss >> _rotmat._32; iss >> _rotmat._33; iss >> _rotmat._34;
                } else if (d == 3) {
                    iss >> _rotmat._41; iss >> _rotmat._42; iss >> _rotmat._43; iss >> _rotmat._44;
                } else {
                    throwCriticalException(_coord_data_file<<" [ADJUST_MAT] のデータ数が多いです。４列４行の行列を設定してください。");
                }
                if (iss.fail()) {
                    throwCriticalException(_coord_data_file<<" [ADJUST_MAT] 不正な数値データです line=["<<line<<"]");
                }
                d++;
            }
        }
    }
    if (int(accuracy*100000000) == 0) {
        throwCriticalException(_coord_data_file<<" [ACCURACY] が指定されてません。");
    }
    if (n == 0) {
        throwCriticalException(_coord_data_file<<" [BASEPOINT] に座標がありません。");
    }
    if (d != 0 && d != 4) {
        throwCriticalException(_coord_data_file<<" [ADJUST_MAT] のデータ数が中途半端です。４列４行の行列を設定してください。");
    }
    init(p, n, accuracy);
}



void SplineSource::init(double prm_paaEstablish[][3], int prm_num, double prm_accuracy) {
    _num_basepoint = prm_num;
    _accuracy = prm_accuracy;
    _x_basepoint = NEW double[prm_num];
    _y_basepoint = NEW double[prm_num];
    _z_basepoint = NEW double[prm_num];
    double x,y,z;
    for (int i = 0; i < prm_num; i++) {
        //x*_11 + y*_21 + z*_31 + _41 , x*_12 + y*_22 + z*_32 + _42, x*_13 + y*_23 + z*_33 + _43
        x = prm_paaEstablish[i][0];
        y = prm_paaEstablish[i][1];
        z = prm_paaEstablish[i][2];
        _x_basepoint[i] = x*_rotmat._11 + y*_rotmat._21 + z*_rotmat._31 + _rotmat._41;
        _y_basepoint[i] = x*_rotmat._12 + y*_rotmat._22 + z*_rotmat._32 + _rotmat._42;
        _z_basepoint[i] = x*_rotmat._13 + y*_rotmat._23 + z*_rotmat._33 + _rotmat._43;
    }
    _xs.init(_x_basepoint, prm_num);
    _ys.init(_y_basepoint, prm_num);
    _zs.init(_z_basepoint, prm_num);
    _x_compute = nullptr;
    _y_compute = nullptr;
    _z_compute = nullptr;
    compute();
}

void SplineSource::compute() {
    _rnum = _num_basepoint/_accuracy;
    if (_x_compute) {
        GGAF_DELETEARR(_x_compute);
        GGAF_DELETEARR(_y_compute);
        GGAF_DELETEARR(_z_compute);
    }
    _x_compute = NEW double[_rnum];
    _y_compute = NEW double[_rnum];
    _z_compute = NEW double[_rnum];

    int index = 0;
    for (double t = 0.0; t <= (_num_basepoint+0.000001) - 1.0; t += _accuracy) { //0.000001 は最後を成立させるため
#ifdef MY_DEBUG
        if (_rnum < index+1) {
            throwCriticalException("補間点配列の要素数の範囲外指定です。_rnum="<<_rnum<<" index="<<index<<" t="<<t);
        }
#endif
        _x_compute[index] = _xs.compute(t);
        _y_compute[index] = _ys.compute(t);
        _z_compute[index] = _zs.compute(t);
        index++;
    }
    _rnum = index;
}

void SplineSource::rotation(angle prm_rx, angle prm_ry, angle prm_rz) {
    const double sinRx = ANG_SIN(prm_rx);
    const double cosRx = ANG_COS(prm_rx);
    const double sinRy = ANG_SIN(prm_ry);
    const double cosRy = ANG_COS(prm_ry);
    const double sinRz = ANG_SIN(prm_rz);
    const double cosRz = ANG_COS(prm_rz);
    for (int t = 0; t < _rnum; t ++) {
        double x = _x_compute[t];
        double y = _y_compute[t];
        double z = _z_compute[t];
        _x_compute[t] = x*cosRz*cosRy + y*(cosRx*-sinRz*cosRy + sinRx*sinRy) + z*(-sinRx*-sinRz*cosRy + cosRx*sinRy);
        _y_compute[t] = x*sinRz + y*cosRx*cosRz + z*-sinRx*cosRz;
        _z_compute[t] = x*cosRz*-sinRy + y*(cosRx*-sinRz*-sinRy + sinRx*cosRy) + z*(-sinRx*-sinRz*-sinRy + cosRx*cosRy);
    }
}

SplineSource::~SplineSource() {
    _TRACE_("SplineSource::~SplineSource() ");
    GGAF_DELETEARR(_coord_data_file);
    GGAF_DELETEARR(_x_basepoint);
    GGAF_DELETEARR(_y_basepoint);
    GGAF_DELETEARR(_z_basepoint);
    //イニシャライズされる前に解放されるかもしれない
    GGAF_DELETEARR_NULLABLE(_x_compute);
    GGAF_DELETEARR_NULLABLE(_y_compute);
    GGAF_DELETEARR_NULLABLE(_z_compute);
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
//[ADJUST_MAT]
//変換行列(4x4)を設定し、BASEPOINT座標情報の補正が可能です。
//例では 元のBASEPOINTの座標に、X軸に5.0移動→90度Y軸回 を行う補正の変換行列です。
//
//0		0		-1		0
//0		1		0		0
//1		0		0		0
//0		0		-5.0	1
//
//もし ADJUST_MAT 省略した場合は、次の単位行列が設定されたものとします。
//
//1		0		0		0
//0		1		0		0
//0		0		1		0
//0		0		0		1
