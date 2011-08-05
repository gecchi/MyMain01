#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManufactureManager::SplineManufactureManager(const char* prm_manager_name) :
    GgafResourceManager<SplineManufacture> (prm_manager_name) {
}

SplineManufacture* SplineManufactureManager::processCreateResource(char* prm_idstr, void* prm_p) {



//    _accuracy = 1.0;
    frame spent_frame = 1;
    angle ang_veloRzRyMv = 0;
    string classname = "";

    string splinefile="";
    string data_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spm";
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" が開けません");
    }
//    double p[MAX_SP_POINT][3];
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
                iss >> classname;
                if (classname == "FixedFrameSplineProgram") {
                    iss >> spent_frame;
                    iss >> ang_veloRzRyMv;
                } else if (classname == "FixedVelocitySplineProgram") {
                    iss >> ang_veloRzRyMv;
                    spent_frame = 0;
                }
            }
        }
//        if (line.find("[BASEPOINT]") != string::npos) {
//            while( getline(ifs,line) ) {
//                if (line.size() == 0 ) break;
//                if (line.c_str()[0] == '#') continue;
//                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
//                istringstream iss(line);
//                iss >> p[n][0];
//                iss >> p[n][1];
//                iss >> p[n][2];
//                n++;
//#ifdef MY_DEBUG
//                if (n >= MAX_SP_POINT) {
//                    throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ポイントが"<<MAX_SP_POINT<<"を超えました。");
//                }
//#endif
//            }
//        }
        if (line.find("[SPLINE]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> splinefile;
            }
        }
    }
#ifdef MY_DEBUG
    if (classname.length() == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" classname が指定されてません。");
    }
    if (n == 0) {
        throwGgafCriticalException("SplineSource::SplineSource "<<prm_idstr<<" ポイントがありません。");
    }
#endif

    SplineManufacture* pSplineManufacture = NULL;
    if (classname.find("FixedFrameSpline") != string::npos) {
        pSplineManufacture = NEW FixedFrameSplineManufacture(prm_idstr, splinefile.c_str());
    } else if (classname.find("FixedVelocitySpline") != string::npos) {
        pSplineManufacture = NEW FixedVelocitySplineManufacture(prm_idstr, splinefile.c_str());
    } else {
        throwGgafCriticalException("SplineSource::createSplineProgram _classname="<<classname<< "は不明なクラスです");
    }
    return pSplineManufacture;



//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    _pSSCon = (SplineSourceConnection*)((P_GOD)->_pSplineSourceManager->getConnection(splinefile.c_str()));
//
//
//
//    splinefile
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    //-1.0 ～ 1.0 が 自機の移動可能範囲とする
//    for (int i = 0; i < n; i++) {
////        p[i][0] = p[i][0] * MyShip::_lim_front; //X
////        p[i][1] = p[i][1] * MyShip::_lim_top;   //Y
////        p[i][2] = p[i][2] * MyShip::_lim_zleft; //Z
//
//        if (p[i][0] > GgafDx9Universe::_X_goneRight*0.9) {
//            p[i][0] = GgafDx9Universe::_X_goneRight*0.9;
//        }
//        if (p[i][0] < GgafDx9Universe::_X_goneLeft*0.9) {
//            p[i][0] = GgafDx9Universe::_X_goneLeft*0.9;
//        }
//        if (p[i][1] > GgafDx9Universe::_Y_goneTop*0.9) {
//            p[i][1] = GgafDx9Universe::_Y_goneTop*0.9;
//        }
//        if (p[i][1] < GgafDx9Universe::_Y_goneBottom*0.9) {
//            p[i][1] = GgafDx9Universe::_Y_goneBottom*0.9;
//        }
//        if (p[i][2] > GgafDx9Universe::_Z_goneFar*0.9) {
//            p[i][2] = GgafDx9Universe::_Z_goneFar*0.9;
//        }
//        if (p[i][2] < GgafDx9Universe::_Z_goneNear*0.9) {
//            p[i][2] = GgafDx9Universe::_Z_goneNear*0.9;
//        }
//    }
//    _pSp = NEW Spline3D(p, n, _accuracy);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    _pSSCon = (SplineSourceConnection*)((P_GOD)->_pSplineSourceManager->getConnection(prm_idstr));
//    pSSCon->refer();
//    SplineManufacture* pResource = NEW SplineManufacture(prm_idstr);
//
//    return pResource;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) {
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineManufactureConnection* pConnection = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

