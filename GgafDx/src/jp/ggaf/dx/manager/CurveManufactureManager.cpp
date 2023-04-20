#include "jp/ggaf/dx/manager/CurveManufactureManager.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"
#include "jp/ggaf/dx/util/curve/FixedVelocityCurveManufacture.h"
#include "jp/ggaf/dx/util/curve/SteppedCoordCurveManufacture.h"

using namespace GgafDx;

CurveManufactureManager::CurveManufactureManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<CurveManufacture> (prm_manager_name) {
}

CurveManufacture* CurveManufactureManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    _TRACE_(FUNC_NAME<<" prm_idstr="<<prm_idstr<<"");

    frame spent_frame = 0;
    angvelo angvelo_rzry_mv = 0;
    std::string classname = "";
    int turn_way = -1;
    bool turn_optimize = true;
    double rate_x = 1.0f;
    double rate_y = 1.0f;
    double rate_z = 1.0f;

    std::string id_str = std::string(prm_idstr);
        _TRACE_(FUNC_NAME<<" id_str="<<id_str<<"");
    std::vector<std::string> curve_id = UTIL::split(id_str, ","); // "FormationUrydike001,3"�̂悤�ɃX���b�V����؂肪���邩


    std::string spl_file="";
    std::string ldr_filename = CONFIG::DIR_CURVE + curve_id[0] + ".ldr";
    GgafCore::Properties propCurve = GgafCore::Properties(ldr_filename);

    if (propCurve.isExistKey("SPLINE")) {
        if (curve_id.size() == 1) {
            //prm_idstr = "FormationUrydike001"
            std::string ldr_data_file_csv = propCurve.getStr("SPLINE");
            std::vector<std::string> vecCurveData = UTIL::split(ldr_data_file_csv, ",");
#ifdef MY_DEBUG
            if (1 < vecCurveData.size()) {
                _TRACE_("�y�x���z CurveManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] �̓J���}��؂�̔z��ł����A�Ăяo�����̓C���f�b�N�X�w�肵�Ă��܂���B�Ӑ}���Ă��܂����H ldr_data_file_csv="<<ldr_data_file_csv);
            }
#endif
            spl_file = vecCurveData[0];
        } else {
            //prm_idstr = "FormationUrydike001,3"
            //�̂悤�ɁA��؂肪����ꍇ�A
            //ldr�t�@�C���� SPLINE��
            //SPLINE=mobius1.spl,mobius2.spl,mobius3.spl,mobius4.spl
            //�̂悤��CSV�ŕ����w�肵�Ă��āA�X���b�V���̌�̐��l���C���f�b�N�X(0�`)�Ƃ���B
            std::string ldr_data_file_csv = propCurve.getStr("SPLINE");
            std::vector<std::string> vecCurveData = UTIL::split(ldr_data_file_csv, ",");
            int i = STOI(curve_id[1]);
#ifdef MY_DEBUG
            if (i+1 > vecCurveData.size()) {
                throwCriticalException(prm_idstr<<" [SPLINE] �̔z��v�f����"<<(vecCurveData.size())<<"�ł����A�w��C���f�b�N�X��"<<i<<"�ׁ̈A�͈͊O�ł��B(���e�͈�=0�`"<<(vecCurveData.size()-1)<<")");
            }
            if (vecCurveData.size() == 1) {
                _TRACE_("�y�x���z CurveManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE]�̓J���}��؂�̔z��ł͂���܂��񂪁A�Ăяo������0�Ԗڂ̃C���f�b�N�X�w��ł��B�Ӑ}���Ă��܂����H");
            }
#endif
            spl_file = vecCurveData[i];
        }
    } else {
        throwCriticalException(prm_idstr<<" [SPLINE] �͕K�{�ł��B");
    }
    if (spl_file.length() == 0) {
        throwCriticalException(prm_idstr<<" [SPLINE] ���w�肳��Ă܂���B");
    }

    if (propCurve.isExistKey("MAG_X")) {
        rate_x = propCurve.getDouble("MAG_X");
    } else {
        rate_x = 1.0;
    }
    if (propCurve.isExistKey("MAG_Y")) {
        rate_y = propCurve.getDouble("MAG_Y");
    } else {
        rate_y = 1.0;
    }
    if (propCurve.isExistKey("MAG_Z")) {
        rate_z = propCurve.getDouble("MAG_Z");
    } else {
        rate_z = 1.0;
    }

    if (propCurve.isExistKey("CLASS")) {
        classname = propCurve.getStr("CLASS");
        if (classname.length() == 0) {
            throwCriticalException(prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
        }
    } else {
        throwCriticalException(prm_idstr<<" [CLASS] ���w�肳��Ă܂���B");
    }
    CurveManufacture::MoveMethod move_method;
    CurveManufacture::MoveDriver move_driver;

    if (classname.find("FixedVelocityCurveCoordVehicleLeader") != std::string::npos) {
        //���쐬
        move_method = CurveManufacture::MoveMethod::FixedVelocity;
        move_driver = CurveManufacture::MoveDriver::CoordVehicle;
    } else if (classname.find("FixedVelocityCurveLocoVehicleLeader") != std::string::npos) {
        move_method = CurveManufacture::MoveMethod::FixedVelocity;
        move_driver = CurveManufacture::MoveDriver::LocoVehicle;
    } else if (classname.find("FixedFrameCurveCoordVehicleLeader") != std::string::npos) {
        move_method = CurveManufacture::MoveMethod::FixedFrame;
        move_driver = CurveManufacture::MoveDriver::CoordVehicle;
    } else if (classname.find("FixedFrameCurveLocoVehicleLeader") != std::string::npos) {
        move_method = CurveManufacture::MoveMethod::FixedFrame;
        move_driver = CurveManufacture::MoveDriver::LocoVehicle;
    } else if (classname.find("SteppedCoordCurveCoordVehicleLeader") != std::string::npos) {
        //���쐬
        move_method = CurveManufacture::MoveMethod::SteppedCoord;
        move_driver = CurveManufacture::MoveDriver::CoordVehicle;
    } else if (classname.find("SteppedCoordCurveLocoVehicleLeader") != std::string::npos) {
        move_method = CurveManufacture::MoveMethod::SteppedCoord;
        move_driver = CurveManufacture::MoveDriver::LocoVehicle;
    } else {
        throwCriticalException(prm_idstr<<" : "
                "[CLASS]="<<classname<<" �͎w��o���܂���B�\�ȃN���X�� FixedVelocityCurveLocoVehicleLeader/FixedFrameCurveCoordVehicleLeader/FixedFrameCurveLocoVehicleLeader/CLASS_SteppedCoordCurveLocoVehicleLeader �݂̂ł��B");
    }


    //SPENT_FRAME
    if (propCurve.isExistKey("SPENT_FRAME")) {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame) {
            spent_frame = (frame)propCurve.getUInt("SPENT_FRAME");
            if (spent_frame == 0) {
                throwCriticalException(prm_idstr<<" : "
                        "[SPENT_FRAME] �� 0 �͎w��o���܂���B");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[SPENT_FRAME] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[SPENT_FRAME] �̎w�肪�K�{�ł��B");
        }
    }

    //ANGLE_VELOCITY
    if (propCurve.isExistKey("ANGLE_VELOCITY")) {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            angvelo_rzry_mv = (angvelo)propCurve.getInt("ANGLE_VELOCITY");
            if (angvelo_rzry_mv == 0) {
                _TRACE_("�y�x���z CurveManufactureManager::processCreateResource "<<prm_idstr<<" : "
                        "[ANGLE_VELOCITY] �� 0 �ł��B�Ӑ}���Ă܂����H");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[ANGLE_VELOCITY] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[ANGLE_VELOCITY] �̎w�肪�K�{�ł��B");
        }
    }

    //TURN_WAY
    if (propCurve.isExistKey("TURN_WAY")) {
        std::string turn_way_val = propCurve.getStr("TURN_WAY");
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            if (turn_way_val == "TURN_CLOSE_TO") {
                turn_way = TURN_CLOSE_TO;
            } else if (turn_way_val == "TURN_ANTICLOSE_TO") {
                turn_way = TURN_ANTICLOSE_TO;
            } else if (turn_way_val == "TURN_CLOCKWISE") {
                turn_way = TURN_CLOCKWISE;
            } else if (turn_way_val == "TURN_COUNTERCLOCKWISE") {
                turn_way = TURN_COUNTERCLOCKWISE;
            } else {
                throwCriticalException(prm_idstr<<" : "
                        "[TURN_WAY] �̒l('"<<turn_way<<"')���s���ł��B\n"
                         "TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE �̉��ꂩ���w�肵�Ă�������");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_WAY] �̎w��͕s�ł��B");
        }
    } else {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_WAY] �̎w�肪�K�{�ł��B");
        }
    }

    //TURN_OPTIMIZE
    if (propCurve.isExistKey("TURN_OPTIMIZE")) {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            turn_optimize = propCurve.getBool("TURN_OPTIMIZE");
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_OPTIMIZE] �̎w��͕s�ł��B(�R�����g���ɂ��ď������ĉ�����)");
        }
    } else {
        if (move_method == CurveManufacture::MoveMethod::FixedFrame || move_method == CurveManufacture::MoveMethod::FixedVelocity) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" �̏ꍇ�́A[TURN_OPTIMIZE] �̎w�肪�K�{�ł��B");
        }
    }

    //CurveManufacture�쐬
    CurveManufacture* pCurveManuf = nullptr;
    if (move_method == CurveManufacture::MoveMethod::FixedFrame) {
        pCurveManuf = NEW FixedFrameCurveManufacture(spl_file.c_str(),
                                                    spent_frame,
                                                    angvelo_rzry_mv,
                                                    turn_way,
                                                    turn_optimize);
    } else if (move_method == CurveManufacture::MoveMethod::FixedVelocity) {
        pCurveManuf = NEW FixedVelocityCurveManufacture(spl_file.c_str(),
                                                       angvelo_rzry_mv,
                                                       turn_way,
                                                       turn_optimize);
    } else if (move_method == CurveManufacture::MoveMethod::SteppedCoord) {
        pCurveManuf = NEW SteppedCoordCurveManufacture(spl_file.c_str());
    } else {
        throwCriticalException("_classname="<<classname<< "�͕s���ȃN���X�ł�");
    }

    pCurveManuf->_move_method = move_method;
    pCurveManuf->_move_driver = move_driver;

    pCurveManuf->adjustAxisRate(rate_x, rate_y, rate_z); //�g��k��
    pCurveManuf->calculate(); //�v�Z�I

    return pCurveManuf;
}

GgafCore::ResourceConnection<CurveManufacture>* CurveManufactureManager::processCreateConnection(const char* prm_idstr, CurveManufacture* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    CurveManufactureConnection* pConne = NEW CurveManufactureConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}

