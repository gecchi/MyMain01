#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


SplineSource::SplineSource(char* prm_idstr)  : GgafObject() {
    _accuracy = 1.0;


    string data_filename = STG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ‚ªŠJ‚¯‚Ü‚¹‚ñ");
    }
    double p[1000][3];
    string line;
    int n = 0;
    while( getline(ifs,line) ) {
        _TRACE_("1line="<<line);
        if ( line.size() == 0 ) { continue; }
        if ( line.c_str()[0] == '#' ) { continue; }
        if ( line == "[CLASS]") {
                    _TRACE_("2line="<<line);
            getline(ifs,line);
            istringstream iss(line);
            iss >> _classname;
            if ( _classname == "GgafDx9FixedFrameSplineProgram") {
                iss >> _spent_frame;
                iss >> _angveloRzRyMv;
            } else if ( _classname == "GgafDx9FixedVelocitySplineProgram") {
                iss >> _angveloRzRyMv;
                _spent_frame = 0;
            }
        } else if ( line == "[POINT]") {
            while( getline(ifs,line) ) {
                        _TRACE_("3line="<<line);
                if ( line.size() == 0 ) break;
                if ( line.c_str()[0] == '#' ) continue;
                istringstream iss(line);
                iss >> p[n][0];
                iss >> p[n][1];
                iss >> p[n][2];
                n++;
            }
        } else if ( line == "[ACCURACY]") {
            while( getline(ifs,line) ) {
                _TRACE_("4line="<<line);
                if ( line.size() == 0 ) break;
                if ( line.c_str()[0] == '#' ) continue;
                istringstream iss(line);
                iss >> _accuracy;
            }
        }
    }


    for (int i = 0; i < n; i++) {
        //X
        p[i][0] = p[i][0] * MyShip::_lim_front;
        //Y
        p[i][1] = p[i][1] * MyShip::_lim_top;
        //Z
        p[i][2] = p[i][2] * MyShip::_lim_zleft;
    }

    _TRACE_("_classname="<<_classname);
    _TRACE_("_spent_frame="<<_spent_frame);
    _TRACE_("_angveloRzRyMv="<<_angveloRzRyMv);
    for (int i = 0; i < n; i++) {
        _TRACE_("X,Y,Z ["<<i<<"]="<<p[i][0]<<","<<p[i][1]<<","<<p[i][2]);
    }
    _TRACE_("n="<<n);
    _TRACE_("_accuracy="<<_accuracy);
    _pSp = NEW GgafDx9Spline3D(p, n, _accuracy);

}


GgafDx9SplineProgram* SplineSource::makeSplineProgram(GgafDx9GeometricActor* prm_pActor) {
    GgafDx9SplineProgram* pSpProg = NULL;
    if ( _classname == "GgafDx9FixedFrameSplineProgram") {
        pSpProg = NEW GgafDx9FixedFrameSplineProgram(prm_pActor, _pSp, _spent_frame, _angveloRzRyMv);
        _TRACE_("pSpProg = NEW GgafDx9FixedFrameSplineProgram("<<prm_pActor->getName()<<", _pSp, "<<_accuracy<<", "<<_spent_frame<<", "<<_angveloRzRyMv<<");");
    } else if ( _classname == "GgafDx9FixedVelocitySplineProgram") {
        pSpProg = NEW GgafDx9FixedVelocitySplineProgram(prm_pActor, _pSp, _angveloRzRyMv);
        _TRACE_("pSpProg = NEW GgafDx9FixedVelocitySplineProgram("<<prm_pActor->getName()<<", _pSp, "<<_accuracy<<", "<<_angveloRzRyMv<<");");
    }
    return pSpProg;
}

SplineSource::~SplineSource() {
    DELETE_IMPOSSIBLE_NULL(_pSp);
}
