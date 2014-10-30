#include "jp/ggaf/lib/manager/SplineManufactureManager.h"

#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/util/spline/FixedFrameSplineManufacture.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/ggaf/lib/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

SplineManufactureManager::SplineManufactureManager(const char* prm_manager_name) :
    GgafResourceManager<SplineManufacture> (prm_manager_name) {
}

SplineManufacture* SplineManufactureManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    frame spent_frame = 0;
    angvelo angveloRzRyMv = 0;
    std::string classname = "";
    int turn_way = -1;
    bool turn_optimize = true;
    double rate_x = 1.0f;
    double rate_y = 1.0f;
    double rate_z = 1.0f;

    std::string spl_data_file="";
    std::string spl_filename = PROPERTY::DIR_SPLINE + std::string(prm_idstr) + ".spl";


    GgafStrMap mapSplPropperties;

    UTIL::readProperties(spl_filename, &mapSplPropperties);

    if (UTIL::isExistKey("SPLINE", &mapSplPropperties)) {
        spl_data_file = mapSplPropperties["SPLINE"];
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] が指定されてません。");
    }

    if (UTIL::isExistKey("MAG_X", &mapSplPropperties)) {
        rate_x = atof(mapSplPropperties["MAG_X"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_X] が指定されてません。");
    }

    if (UTIL::isExistKey("MAG_Y", &mapSplPropperties)) {
        rate_y = atof(mapSplPropperties["MAG_Y"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Y] が指定されてません。");
    }

    if (UTIL::isExistKey("MAG_Z", &mapSplPropperties)) {
        rate_z = atof(mapSplPropperties["MAG_Z"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Z] が指定されてません。");
    }

    if (UTIL::isExistKey("CLASS", &mapSplPropperties)) {
        classname = mapSplPropperties["CLASS"];
        if (classname.length() == 0) {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] が指定されてません。");
        }
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] が指定されてません。");
    }

    if (UTIL::isExistKey("ANGLE_VELOCITY", &mapSplPropperties)) {
        angveloRzRyMv = (angvelo)atoi(mapSplPropperties["ANGLE_VELOCITY"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] が指定されてません。");
    }

    if (UTIL::isExistKey("TURN_WAY", &mapSplPropperties)) {
        if (mapSplPropperties["TURN_WAY"] == "TURN_CLOSE_TO") {
            turn_way = TURN_CLOSE_TO;
        } else if (mapSplPropperties["TURN_WAY"] == "TURN_ANTICLOSE_TO") {
            turn_way = TURN_ANTICLOSE_TO;
        } else if (mapSplPropperties["TURN_WAY"] == "TURN_CLOCKWISE") {
            turn_way = TURN_CLOCKWISE;
        } else if (mapSplPropperties["TURN_WAY"] == "TURN_COUNTERCLOCKWISE") {
            turn_way = TURN_COUNTERCLOCKWISE;
        } else {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_WAY] の値('"<<mapSplPropperties["TURN_WAY"]<<"')が不正です。\n" <<
                                       "TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE の何れかを指定してください");
        }
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_WAY] が指定されてません。");
    }

    if (UTIL::isExistKey("TURN_OPTIMIZE", &mapSplPropperties)) {
        turn_optimize = UTIL::cnvBool(mapSplPropperties["TURN_OPTIMIZE"]);
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_OPTIMIZE] が指定されてません。");
    }


    if (spl_data_file.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] が指定されてません。");
    }

    SplineManufacture* pSplManuf = nullptr;
    if (classname.find("FixedFrameSpline") != std::string::npos) {
        if (UTIL::isExistKey("SPENT_FRAME", &mapSplPropperties)) {
            spent_frame = (frame)atoi(mapSplPropperties["SPENT_FRAME"].c_str());
        } else {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] が FixedFrameSplineの場合は、SPENT_FRAME が必要です。");
        }

        if (spent_frame == 0) {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPENT_FRAME] が0です。");
        }
        pSplManuf = NEW FixedFrameSplineManufacture(spl_data_file.c_str(), spent_frame,
                                                    angveloRzRyMv,
                                                    turn_way,
                                                    turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //拡大縮小
        pSplManuf->calculate();
    } else if (classname.find("FixedVelocitySpline") != std::string::npos) {
        pSplManuf = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(),
                                                       angveloRzRyMv,
                                                       turn_way,
                                                       turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //拡大縮小
        pSplManuf->calculate();
    } else if (classname.find("SteppedCoordSpline") != std::string::npos) {
        pSplManuf = NEW SteppedCoordSplineManufacture(spl_data_file.c_str(),
                                                      // angveloRzRyMv,
                                                      turn_way,
                                                      turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //拡大縮小
        pSplManuf->calculate();
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource _classname="<<classname<< "は不明なクラスです");
    }
    if (angveloRzRyMv == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [ANGLE_VELOCITY] が指定されてません。");
    }
    return pSplManuf;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) {
    _DTRACE3_(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    SplineManufactureConnection* pConne = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    _DTRACE3_(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}

