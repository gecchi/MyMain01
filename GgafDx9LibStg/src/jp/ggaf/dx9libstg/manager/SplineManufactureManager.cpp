#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManufactureManager::SplineManufactureManager(const char* prm_manager_name) :
    GgafResourceManager<SplineManufacture> (prm_manager_name) {
}

SplineManufacture* SplineManufactureManager::processCreateResource(char* prm_idstr, void* prm_p) {
    frame spent_frame = 1;
    angle ang_veloRzRyMv = 0;
    string classname = "";
    float rate_X = 1.0f;
    float rate_Y = 1.0f;
    float rate_Z = 1.0f;

    string spl_data_file="";
    string spl_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";
    ifstream ifs(spl_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<spl_filename<<" が開けません");
    }
    string line;
    while( getline(ifs,line) ) {
        if (line.size() == 0 ) continue;
        if (line.c_str()[0] == '#') continue;

        LOOP_SPLFILE:

        if (line.find("[SPLINE]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> spl_data_file;
            }
        }
        if (line.find("[MAGNIFICATION]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> rate_X;
                iss >> rate_Y;
                iss >> rate_Z;
            }
        }

        if (line.find("[CLASS]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> classname;
                if (classname == "FixedFrameSpline") {
                    iss >> spent_frame;
                    iss >> ang_veloRzRyMv;
                } else if (classname == "FixedVelocitySpline") {
                    iss >> ang_veloRzRyMv;
                    spent_frame = 0;
                } else {
                    throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] の四手が不正です。\n"<<
                                               "'FixedFrameSpline' or 'FixedVelocitySpline' を指定してください。入力データは '" << classname<< "' でした。");
                }
            }
        }
    }
    if (classname.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] が指定されてません。");
    }
    if (spl_data_file.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] が指定されてません。");
    }

    SplineManufacture* pSplManufacture = NULL;
    if (classname.find("FixedFrameSpline") != string::npos) {
        pSplManufacture = NEW FixedFrameSplineManufacture(spl_data_file.c_str(), spent_frame, ang_veloRzRyMv);
        pSplManufacture->adjustAxisRate(rate_X, rate_Y, rate_Z); //拡大縮小
        pSplManufacture->calculate();
    } else if (classname.find("FixedVelocitySpline") != string::npos) {
        pSplManufacture = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(), ang_veloRzRyMv);
        pSplManufacture->adjustAxisRate(rate_X, rate_Y, rate_Z); //拡大縮小
        pSplManufacture->calculate();
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource _classname="<<classname<< "は不明なクラスです");
    }
    return pSplManufacture;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) {
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineManufactureConnection* pConnection = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConnection;
}

