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
    _angveloRzRyMv = 0;
    _classname = "";
    string data_filename = STG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
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
                if (_classname == "GgafDx9FixedFrameSplineProgram") {
                    iss >> _spent_frame;
                    iss >> _angveloRzRyMv;
                } else if (_classname == "GgafDx9FixedVelocitySplineProgram") {
                    iss >> _angveloRzRyMv;
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
        p[i][0] = p[i][0] * MyShip::_lim_front; //X
        p[i][1] = p[i][1] * MyShip::_lim_top;   //Y
        p[i][2] = p[i][2] * MyShip::_lim_zleft; //Z
    }
    _pSp = NEW GgafDx9Spline3D(p, n, _accuracy);

}


GgafDx9SplineProgram* SplineSource::makeSplineProgram(GgafDx9GeometricActor* prm_pActor) {
    GgafDx9SplineProgram* pSpProg = NULL;
    if (_classname.find("GgafDx9FixedFrameSplineProgram") != string::npos) {
        pSpProg = NEW GgafDx9FixedFrameSplineProgram(prm_pActor, _pSp, _spent_frame, _angveloRzRyMv);
        //_TRACE_("pSpProg = NEW GgafDx9FixedFrameSplineProgram("<<prm_pActor->getName()<<", _pSp, "<<_accuracy<<", "<<_spent_frame<<", "<<_angveloRzRyMv<<");");
    } else if (_classname.find("GgafDx9FixedVelocitySplineProgram") != string::npos) {
        pSpProg = NEW GgafDx9FixedVelocitySplineProgram(prm_pActor, _pSp, _angveloRzRyMv);
        //_TRACE_("pSpProg = NEW GgafDx9FixedVelocitySplineProgram("<<prm_pActor->getName()<<", _pSp, "<<_accuracy<<", "<<_angveloRzRyMv<<");");
    } else {
        throwGgafCriticalException("SplineSource::makeSplineProgram _classname="<<_classname<< "は不明なクラスです");
    }
    return pSpProg;
}

SplineSource::~SplineSource() {
    DELETE_IMPOSSIBLE_NULL(_pSp);
}
