#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

SplineManufactureManager::SplineManufactureManager(const char* prm_manager_name) :
    GgafResourceManager<SplineManufacture> (prm_manager_name) {
}

SplineManufacture* SplineManufactureManager::processCreateResource(char* prm_idstr, void* prm_p) {
    frame spent_frame = 0;
    angle ang_veloRzRyMv = 0;
    string classname = "";
    int turn_way = -1;
    float rate_X = 1.0f;
    float rate_Y = 1.0f;
    float rate_Z = 1.0f;

    string spl_data_file="";
    string spl_filename = CFG_PROPERTY(DIR_SPLINE_DATA) + string(prm_idstr) + ".spl";


//    GgafStrMap mapSplPropperties;
//
//    GgafUtil::read(spl_filename, &mapSplPropperties);
//
//    if (GgafUtil::isExistKey("SPLINE", &mapSplPropperties)) {
//        spl_data_file = mapSplPropperties["SPLINE"];
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B");
//    }
//
//    if (GgafUtil::isExistKey("MAG_X", &mapSplPropperties)) {
//        rate_X = (float)atof(mapSplPropperties["MAG_X"].c_str());
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_X] ���w�肳��Ă܂���B");
//    }
//
//    if (GgafUtil::isExistKey("MAG_Y", &mapSplPropperties)) {
//        rate_Y = (float)atof(mapSplPropperties["MAG_Y"].c_str());
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Y] ���w�肳��Ă܂���B");
//    }
//
//    if (GgafUtil::isExistKey("MAG_Z", &mapSplPropperties)) {
//        rate_Z = (float)atof(mapSplPropperties["MAG_Z"].c_str());
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Z] ���w�肳��Ă܂���B");
//    }
//
//    if (GgafUtil::isExistKey("CLASS", &mapSplPropperties)) {
//        classname = mapSplPropperties["CLASS"];
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
//    }
//
//    if (GgafUtil::isExistKey("CLASS", &mapSplPropperties)) {
//        classname = mapSplPropperties["CLASS"];
//    } else {
//        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
//    }


    ifstream ifs(spl_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<spl_filename<<" ���J���܂���");
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
            }
        }
        if (line.find("[ANGLE_VELOCITY]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> ang_veloRzRyMv;
            }
        }
        if (line.find("[SPENT_FRAME]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> spent_frame;
            }
        }
        if (line.find("[TURN_WAY]") != string::npos) {
            while( getline(ifs,line) ) {
                if (line.size() == 0 ) break;
                if (line.c_str()[0] == '#') continue;
                if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                istringstream iss(line);
                iss >> turn_way;
            }
        }
        if (line.find("[OPTIMAIZE]") != string::npos) {
             while( getline(ifs,line) ) {
                 if (line.size() == 0 ) break;
                 if (line.c_str()[0] == '#') continue;
                 if (line.c_str()[0] == '[') goto LOOP_SPLFILE;
                 istringstream iss(line);
//                 iss >> OPTIMAIZE;
             }
         }
    }
    if (classname.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
    }
    if (spl_data_file.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B");
    }

    SplineManufacture* pSplManuf = NULL;
    if (classname.find("FixedFrameSpline") != string::npos) {
        if (spent_frame == 0) {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" FixedFrameSpline �̏ꍇ�� [SPENT_FRAME] ���K�v�ł��B");
        }
        pSplManuf = NEW FixedFrameSplineManufacture(spl_data_file.c_str(), spent_frame, ang_veloRzRyMv);
        pSplManuf->adjustAxisRate(rate_X, rate_Y, rate_Z); //�g��k��
        pSplManuf->calculate();
    } else if (classname.find("FixedVelocitySpline") != string::npos) {
        pSplManuf = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(), ang_veloRzRyMv);
        pSplManuf->adjustAxisRate(rate_X, rate_Y, rate_Z); //�g��k��
        pSplManuf->calculate();
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource _classname="<<classname<< "�͕s���ȃN���X�ł�");
    }
    if (ang_veloRzRyMv == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [ANGLE_VELOCITY] ���w�肳��Ă܂���B");
    }
    return pSplManuf;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) {
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    SplineManufactureConnection* pConnection = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    TRACE3(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}

