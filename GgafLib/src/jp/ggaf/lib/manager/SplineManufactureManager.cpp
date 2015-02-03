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

    std::string id_str = std::string(prm_idstr);
    std::vector<std::string> spline_id = UTIL::split(id_str, "/"); // "FormationUrydike001/3"�̂悤�ɃX���b�V����؂肪���邩


    std::string spl_data_file="";
    std::string spl_filename = PROPERTY::DIR_SPLINE + spline_id[0] + ".spl";

    GgafStrMap mapSplPropperties;
    UTIL::readProperties(spl_filename, &mapSplPropperties);

    if (spline_id.size() == 1) {
        //prm_idstr = "FormationUrydike001"
        if (UTIL::isExistKey("SPLINE", &mapSplPropperties)) {
            spl_data_file = mapSplPropperties["SPLINE"];
        } else {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B(1)");
        }
    } else {
        //prm_idstr = "FormationUrydike001/3"
        //�̂悤�ɁA��؂肪����ꍇ�A
        //spl�t�@�C���� SPLINE��
        //SPLINE=mobius1.dat,mobius2.dat,mobius3.dat,mobius4.dat
        //�̂悤��CSV�ŕ����w�肵�Ă��āA�X���b�V���̌�̐��l���C���f�b�N�X�Ƃ���B
        if (UTIL::isExistKey("SPLINE", &mapSplPropperties)) {
            std::string spl_data_file_csv = mapSplPropperties["SPLINE"];
            std::vector<std::string> vecSplineData = UTIL::split(spl_data_file_csv, ",");
            int i = STOI(spline_id[1]);
            spl_data_file = vecSplineData[i];
        } else {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B(2)");
        }
    }


    if (UTIL::isExistKey("MAG_X", &mapSplPropperties)) {
        rate_x = atof(mapSplPropperties["MAG_X"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_X] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("MAG_Y", &mapSplPropperties)) {
        rate_y = atof(mapSplPropperties["MAG_Y"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Y] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("MAG_Z", &mapSplPropperties)) {
        rate_z = atof(mapSplPropperties["MAG_Z"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [MAG_Z] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("CLASS", &mapSplPropperties)) {
        classname = mapSplPropperties["CLASS"];
        if (classname.length() == 0) {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
        }
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("ANGLE_VELOCITY", &mapSplPropperties)) {
        angveloRzRyMv = (angvelo)atoi(mapSplPropperties["ANGLE_VELOCITY"].c_str());
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
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
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_WAY] �̒l('"<<mapSplPropperties["TURN_WAY"]<<"')���s���ł��B\n" <<
                                       "TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE �̉��ꂩ���w�肵�Ă�������");
        }
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_WAY] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("TURN_OPTIMIZE", &mapSplPropperties)) {
        turn_optimize = UTIL::cnvBool(mapSplPropperties["TURN_OPTIMIZE"]);
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [TURN_OPTIMIZE] ���w�肳��Ă܂���B");
    }


    if (spl_data_file.length() == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B");
    }

    SplineManufacture* pSplManuf = nullptr;
    if (classname.find("FixedFrameSpline") != std::string::npos) {
        if (UTIL::isExistKey("SPENT_FRAME", &mapSplPropperties)) {
            spent_frame = (frame)atoi(mapSplPropperties["SPENT_FRAME"].c_str());
        } else {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [CLASS] �� FixedFrameSpline�̏ꍇ�́ASPENT_FRAME ���K�v�ł��B");
        }

        if (spent_frame == 0) {
            throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPENT_FRAME] ��0�ł��B");
        }
        pSplManuf = NEW FixedFrameSplineManufacture(spl_data_file.c_str(), spent_frame,
                                                    angveloRzRyMv,
                                                    turn_way,
                                                    turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //�g��k��
        pSplManuf->calculate();
    } else if (classname.find("FixedVelocitySpline") != std::string::npos) {
        pSplManuf = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(),
                                                       angveloRzRyMv,
                                                       turn_way,
                                                       turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //�g��k��
        pSplManuf->calculate();
    } else if (classname.find("SteppedCoordSpline") != std::string::npos) {
        pSplManuf = NEW SteppedCoordSplineManufacture(spl_data_file.c_str(),
                                                      // angveloRzRyMv,
                                                      turn_way,
                                                      turn_optimize);
        pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //�g��k��
        pSplManuf->calculate();
    } else {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource _classname="<<classname<< "�͕s���ȃN���X�ł�");
    }
    if (angveloRzRyMv == 0) {
        throwGgafCriticalException("SplineManufactureManager::processCreateResource "<<prm_idstr<<" [ANGLE_VELOCITY] ���w�肳��Ă܂���B");
    }
    return pSplManuf;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(char* prm_idstr, SplineManufacture* prm_pResource) {
    _TRACE3_(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    SplineManufactureConnection* pConne = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    _TRACE3_(" SplineManufactureManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}

