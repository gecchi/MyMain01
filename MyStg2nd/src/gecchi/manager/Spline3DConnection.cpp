#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Spline3DConnection::Spline3DConnection(char* prm_idstr, GgafDx9Core::GgafDx9Spline3D* prm_pResource) :
    GgafResourceConnection<GgafDx9Core::GgafDx9Spline3D> (prm_idstr, prm_pResource) {

    _accuracy = 0.0:
    _spent_frame = 0:
    _angveloRzRyMv = 0;
    _classname = NULL;

    string data_filename = STG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineProgramManager::processCreateResource "<<prm_idstr<<" ‚ªŠJ‚¯‚Ü‚¹‚ñ");
    }

    string line;
    string classname;
    int n = 0;
    while( getline(ifs,line) ) {
        if ( line.size() == 0 ) continue;
        if ( line.c_str()[0] == '#' ) continue;
        if ( line == "[CLASS]") {
            getline(ifs,line);
            istringstream iss(line);
            iss >> classname;
            if ( classname == "GgafDx9FixedFrameSplineProgram") {
                iss >> _spent_frame;
                iss >> _angveloRzRyMv;
            } else if ( classname == "GgafDx9FixedVelocitySplineProgram") {
                iss >> _angveloRzRyMv;
                _spent_frame = 0;
            }
        }
    }
//        else if ( line == "[POINT]") {
//
//            while( getline(ifs,line) ) {
//                if ( line.size() == 0 ) break;
//                if ( line.c_str()[0] == '#' ) continue;
//                istringstream iss(line);
//                iss >> p[n][0];
//                iss >> p[n][1];
//                iss >> p[n][2];
//                n++;
//            }
//        }
//        for (int i = 0; i < n; i++) {
//            //X
//            p[i][0] = p[i][0] * MyShip::_lim_front;
//            //Y
//            p[i][1] = p[i][1] * MyShip::_lim_top;
//            //Z
//            p[i][2] = p[i][2] * MyShip::_lim_zleft;
//
//        }

//        if ( _classname == "GgafDx9FixedFrameSplineProgram") {
//            pResource = NEW GgafDx9FixedFrameSplineProgram(pActor, p, n, accuracy, spent_frame, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedFrameSplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<spent_frame<<", "<<angveloRzRyMv<<");");
//        } else if ( _classname == "GgafDx9FixedVelocitySplineProgram") {
//            pResource = NEW GgafDx9FixedVelocitySplineProgram(pActor, p, n, accuracy, angveloRzRyMv);
//            _TRACE_("pResource = NEW GgafDx9FixedVelocitySplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<angveloRzRyMv<<");");
//        }
}

void Spline3DConnection::processReleaseResource(GgafDx9Core::GgafDx9Spline3D* prm_pResource) {
    _TRACE_("Spline3DConnection::processReleaseResource‚ÅŠJ•ú(‚±‚±‚Å‚Ô‚Á‰ó‚ê‚½‚çclose()˜R‚ê‚Ì‰Â”\«‚ ‚è)");
    DELETE_IMPOSSIBLE_NULL(prm_pResource);
}

GgafDx9SplineProgram* Spline3DConnection::makeSplineProgram() {
    GgafDx9SplineProgram* pSpProg = NULL;
    if ( classname == "GgafDx9FixedFrameSplineProgram") {
        pSpProg = NEW GgafDx9FixedFrameSplineProgram(pActor,refer(), _spent_frame, _angveloRzRyMv);
        _TRACE_("pResource = NEW GgafDx9FixedFrameSplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<spent_frame<<", "<<angveloRzRyMv<<");");
    } else if ( classname == "GgafDx9FixedVelocitySplineProgram") {
        pSpProg = NEW GgafDx9FixedVelocitySplineProgram(pActor, refer(), _angveloRzRyMv);
        _TRACE_("pResource = NEW GgafDx9FixedVelocitySplineProgram("<<pActor->getName()<<", p, "<<n<<", "<<accuracy<<", "<<angveloRzRyMv<<");");
    }

    return pSpProg;
}
