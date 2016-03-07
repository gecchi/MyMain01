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

SplineManufacture* SplineManufactureManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    _TRACE_(FUNC_NAME<<" idstr="<<prm_idstr<<"");

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
    UTIL::readProperties(spl_filename, mapSplPropperties);

    if (UTIL::isExistKey("SPLINE", mapSplPropperties)) {
        if (spline_id.size() == 1) {
            //prm_idstr = "FormationUrydike001"
            std::string spl_data_file_csv = mapSplPropperties["SPLINE"];
            std::vector<std::string> vecSplineData = UTIL::split(spl_data_file_csv, ",");
#ifdef MY_DEBUG
            if (0 < vecSplineData.size()) {
                _TRACE_("���x���� SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] �̓J���}��؂�̔z��ł����A�Ăяo�����̓C���f�b�N�X�w�肵�Ă��܂���B�Ӑ}���Ă��܂����H");
            }
#endif
            spl_data_file = vecSplineData[0];
        } else {
            //prm_idstr = "FormationUrydike001/3"
            //�̂悤�ɁA��؂肪����ꍇ�A
            //spl�t�@�C���� SPLINE��
            //SPLINE=mobius1.dat,mobius2.dat,mobius3.dat,mobius4.dat
            //�̂悤��CSV�ŕ����w�肵�Ă��āA�X���b�V���̌�̐��l���C���f�b�N�X�Ƃ���B
            std::string spl_data_file_csv = mapSplPropperties["SPLINE"];
            std::vector<std::string> vecSplineData = UTIL::split(spl_data_file_csv, ",");
            int i = STOI(spline_id[1]);
#ifdef MY_DEBUG
            if (i+1 > vecSplineData.size()) {
                throwGgafCriticalException(prm_idstr<<" [SPLINE] �̔z��v�f����"<<(vecSplineData.size())<<"�ł����A�w��C���f�b�N�X��"<<i<<"�ׁ̈A�͈͊O�ł��B(���e�͈�=0�`"<<(vecSplineData.size()-1)<<")");
            }
            if (vecSplineData.size() == 1) {
                _TRACE_("���x���� SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE]�̓J���}��؂�̔z��ł͂���܂��񂪁A�Ăяo������0�Ԗڂ̃C���f�b�N�X�w��ł��B�Ӑ}���Ă��܂����H");
            }
#endif
            spl_data_file = vecSplineData[i];
        }
    } else {
        throwGgafCriticalException(prm_idstr<<" [SPLINE] �͕K�{�ł��B");
    }
    if (spl_data_file.length() == 0) {
        throwGgafCriticalException(prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B");
    }

    if (UTIL::isExistKey("MAG_X", mapSplPropperties)) {
        rate_x = atof(mapSplPropperties["MAG_X"].c_str());
    } else {
        rate_x = 1.0;
    }
    if (UTIL::isExistKey("MAG_Y", mapSplPropperties)) {
        rate_y = atof(mapSplPropperties["MAG_Y"].c_str());
    } else {
        rate_y = 1.0;
    }
    if (UTIL::isExistKey("MAG_Z", mapSplPropperties)) {
        rate_z = atof(mapSplPropperties["MAG_Z"].c_str());
    } else {
        rate_z = 1.0;
    }

    //CLASS
    enum SplineLeader {
        CLASS_FixedFrameSpline,
        CLASS_FixedVelocitySpline,
        CLASS_SteppedCoordSpline,
    } leader;

    if (UTIL::isExistKey("CLASS", mapSplPropperties)) {
        classname = mapSplPropperties["CLASS"];
        if (classname.length() == 0) {
            throwGgafCriticalException(prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
        }
    } else {
        throwGgafCriticalException(prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
    }

    if (classname.find("FixedFrameSpline") != std::string::npos) {
        leader = CLASS_FixedFrameSpline;
    } else if (classname.find("FixedVelocitySpline") != std::string::npos) {
        leader = CLASS_FixedVelocitySpline;
    } else if (classname.find("SteppedCoordSpline") != std::string::npos) {
        leader = CLASS_SteppedCoordSpline;
    } else {
        throwGgafCriticalException(prm_idstr<<" : "<<
                "[CLASS]="<<classname<<" �͎w��o���܂���B�\�ȃN���X�� FixedFrameSpline/FixedVelocitySpline/SteppedCoordSpline �݂̂ł��B");
    }

    //SPENT_FRAME
    if (UTIL::isExistKey("SPENT_FRAME", mapSplPropperties)) {
        if (leader == CLASS_FixedFrameSpline) {
            spent_frame = (frame)atoi(mapSplPropperties["SPENT_FRAME"].c_str());
            if (spent_frame == 0) {
                throwGgafCriticalException(prm_idstr<<" : "<<
                        "[SPENT_FRAME] �� 0 �͎w��o���܂���B");
            }
        } else {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[SPENT_FRAME] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline) {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[SPENT_FRAME] �̎w�肪�K�{�ł��B");
        }
    }

    //ANGLE_VELOCITY
    if (UTIL::isExistKey("ANGLE_VELOCITY", mapSplPropperties)) {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            angveloRzRyMv = (angvelo)atoi(mapSplPropperties["ANGLE_VELOCITY"].c_str());
            if (angveloRzRyMv == 0) {
                _TRACE_("���x���� SplineManufactureManager::processCreateResource "<<prm_idstr<<" : "<<
                        "[ANGLE_VELOCITY] �� 0 �ł��B�Ӑ}���Ă܂����H");
            }
        } else {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[ANGLE_VELOCITY] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[ANGLE_VELOCITY] �̎w�肪�K�{�ł��B");
        }
    }

    //TURN_WAY
    if (UTIL::isExistKey("TURN_WAY", mapSplPropperties)) {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            if (mapSplPropperties["TURN_WAY"] == "TURN_CLOSE_TO") {
                turn_way = TURN_CLOSE_TO;
            } else if (mapSplPropperties["TURN_WAY"] == "TURN_ANTICLOSE_TO") {
                turn_way = TURN_ANTICLOSE_TO;
            } else if (mapSplPropperties["TURN_WAY"] == "TURN_CLOCKWISE") {
                turn_way = TURN_CLOCKWISE;
            } else if (mapSplPropperties["TURN_WAY"] == "TURN_COUNTERCLOCKWISE") {
                turn_way = TURN_COUNTERCLOCKWISE;
            } else {
                throwGgafCriticalException(prm_idstr<<" : "<<
                        "[TURN_WAY] �̒l('"<<mapSplPropperties["TURN_WAY"]<<"')���s���ł��B\n" <<
                                           "TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE �̉��ꂩ���w�肵�Ă�������");
            }
        } else {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_WAY] �̎w��͕s�ł��B");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_WAY] �̎w�肪�K�{�ł��B");
        }
    }

    //TURN_OPTIMIZE
    if (UTIL::isExistKey("TURN_OPTIMIZE", mapSplPropperties)) {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            turn_optimize = UTIL::cnvBool(mapSplPropperties["TURN_OPTIMIZE"]);
        } else {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_OPTIMIZE] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwGgafCriticalException(prm_idstr<<" : "<<
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_OPTIMIZE] �̎w�肪�K�{�ł��B");
        }
    }

    //SplineManufacture�쐬
    SplineManufacture* pSplManuf = nullptr;
    if (leader == CLASS_FixedFrameSpline) {
        pSplManuf = NEW FixedFrameSplineManufacture(spl_data_file.c_str(),
                                                    spent_frame,
                                                    angveloRzRyMv,
                                                    turn_way,
                                                    turn_optimize);
    } else if (leader == CLASS_FixedVelocitySpline) {
        pSplManuf = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(),
                                                       angveloRzRyMv,
                                                       turn_way,
                                                       turn_optimize);
    } else if (leader == CLASS_SteppedCoordSpline) {
        pSplManuf = NEW SteppedCoordSplineManufacture(spl_data_file.c_str());
    } else {
        throwGgafCriticalException("_classname="<<classname<< "�͕s���ȃN���X�ł�");
    }
    pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //�g��k��
    pSplManuf->calculate(); //�v�Z�I

    return pSplManuf;
}

GgafResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(const char* prm_idstr, SplineManufacture* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    SplineManufactureConnection* pConne = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}

