#include "jp/ggaf/dx/manager/SplineManufactureManager.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/SplineManufactureConnection.h"
#include "jp/ggaf/dx/util/spline/FixedFrameSplineManufacture.h"
#include "jp/ggaf/dx/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/ggaf/dx/util/spline/SteppedCoordSplineManufacture.h"

using namespace GgafDx;

SplineManufactureManager::SplineManufactureManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<SplineManufacture> (prm_manager_name) {
}

SplineManufacture* SplineManufactureManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    _TRACE_(FUNC_NAME<<" idstr="<<prm_idstr<<"");

    frame spent_frame = 0;
    angvelo angvelo_rzry_mv = 0;
    std::string classname = "";
    int turn_way = -1;
    bool turn_optimize = true;
    double rate_x = 1.0f;
    double rate_y = 1.0f;
    double rate_z = 1.0f;

    std::string id_str = std::string(prm_idstr);
    std::vector<std::string> spline_id = UTIL::split(id_str, ","); // "FormationUrydike001,3"のようにスラッシュ区切りがあるか


    std::string spl_data_file="";
    std::string spl_filename = CONFIG::DIR_SPLINE + spline_id[0] + ".spl";
    GgafCore::Properties propSpl = GgafCore::Properties(spl_filename);

    if (propSpl.isExistKey("SPLINE")) {
        if (spline_id.size() == 1) {
            //prm_idstr = "FormationUrydike001"
            std::string spl_data_file_csv = propSpl.getStr("SPLINE");
            std::vector<std::string> vecSplineData = UTIL::split(spl_data_file_csv, ",");
#ifdef MY_DEBUG
            if (0 < vecSplineData.size()) {
                _TRACE_("＜警告＞ SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE] はカンマ区切りの配列ですが、呼び出し側はインデックス指定していません。意図していますか？");
            }
#endif
            spl_data_file = vecSplineData[0];
        } else {
            //prm_idstr = "FormationUrydike001,3"
            //のように、区切りがある場合、
            //splファイルの SPLINEは
            //SPLINE=mobius1.dat,mobius2.dat,mobius3.dat,mobius4.dat
            //のようにCSVで複数指定していて、スラッシュの後の数値がインデックス(0～)とする。
            std::string spl_data_file_csv = propSpl.getStr("SPLINE");
            std::vector<std::string> vecSplineData = UTIL::split(spl_data_file_csv, ",");
            int i = STOI(spline_id[1]);
#ifdef MY_DEBUG
            if (i+1 > vecSplineData.size()) {
                throwCriticalException(prm_idstr<<" [SPLINE] の配列要素数は"<<(vecSplineData.size())<<"ですが、指定インデックスは"<<i<<"の為、範囲外です。(許容範囲=0～"<<(vecSplineData.size()-1)<<")");
            }
            if (vecSplineData.size() == 1) {
                _TRACE_("＜警告＞ SplineManufactureManager::processCreateResource "<<prm_idstr<<" [SPLINE]はカンマ区切りの配列ではありませんが、呼び出し側は0番目のインデックス指定です。意図していますか？");
            }
#endif
            spl_data_file = vecSplineData[i];
        }
    } else {
        throwCriticalException(prm_idstr<<" [SPLINE] は必須です。");
    }
    if (spl_data_file.length() == 0) {
        throwCriticalException(prm_idstr<<" [SPLINE] が指定されてません。");
    }

    if (propSpl.isExistKey("MAG_X")) {
        rate_x = propSpl.getDouble("MAG_X");
    } else {
        rate_x = 1.0;
    }
    if (propSpl.isExistKey("MAG_Y")) {
        rate_y = propSpl.getDouble("MAG_Y");
    } else {
        rate_y = 1.0;
    }
    if (propSpl.isExistKey("MAG_Z")) {
        rate_z = propSpl.getDouble("MAG_Z");
    } else {
        rate_z = 1.0;
    }

    //CLASS
    enum SplineLeader {
        CLASS_FixedFrameSpline,
        CLASS_FixedVelocitySpline,
        CLASS_SteppedCoordSpline,
    } leader;

    if (propSpl.isExistKey("CLASS")) {
        classname = propSpl.getStr("CLASS");
        if (classname.length() == 0) {
            throwCriticalException(prm_idstr<<" [CLASS] が指定されてません。");
        }
    } else {
        throwCriticalException(prm_idstr<<" [CLASS] が指定されてません。");
    }

    if (classname.find("FixedFrameSpline") != std::string::npos) {
        leader = CLASS_FixedFrameSpline;
    } else if (classname.find("FixedVelocitySpline") != std::string::npos) {
        leader = CLASS_FixedVelocitySpline;
    } else if (classname.find("SteppedCoordSpline") != std::string::npos) {
        leader = CLASS_SteppedCoordSpline;
    } else {
        throwCriticalException(prm_idstr<<" : "
                "[CLASS]="<<classname<<" は指定出来ません。可能なクラスは FixedFrameSpline/FixedVelocitySpline/SteppedCoordSpline のみです。");
    }

    //SPENT_FRAME
    if (propSpl.isExistKey("SPENT_FRAME")) {
        if (leader == CLASS_FixedFrameSpline) {
            spent_frame = (frame)propSpl.getUInt("SPENT_FRAME");
            if (spent_frame == 0) {
                throwCriticalException(prm_idstr<<" : "
                        "[SPENT_FRAME] に 0 は指定出来ません。");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[SPENT_FRAME] の指定は不可です。(コメント等にして除去して下さい)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[SPENT_FRAME] の指定が必須です。");
        }
    }

    //ANGLE_VELOCITY
    if (propSpl.isExistKey("ANGLE_VELOCITY")) {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            angvelo_rzry_mv = (angvelo)propSpl.getInt("ANGLE_VELOCITY");
            if (angvelo_rzry_mv == 0) {
                _TRACE_("＜警告＞ SplineManufactureManager::processCreateResource "<<prm_idstr<<" : "
                        "[ANGLE_VELOCITY] が 0 です。意図してますか？");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[ANGLE_VELOCITY] の指定は不可です。(コメント等にして除去して下さい)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[ANGLE_VELOCITY] の指定が必須です。");
        }
    }

    //TURN_WAY
    if (propSpl.isExistKey("TURN_WAY")) {
        std::string turn_way_val = propSpl.getStr("TURN_WAY");
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
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
                        "[TURN_WAY] の値('"<<turn_way<<"')が不正です。\n"
                         "TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_CLOCKWISE/TURN_COUNTERCLOCKWISE の何れかを指定してください");
            }
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[TURN_WAY] の指定は不可です。");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[TURN_WAY] の指定が必須です。");
        }
    }

    //TURN_OPTIMIZE
    if (propSpl.isExistKey("TURN_OPTIMIZE")) {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            turn_optimize = propSpl.getBool("TURN_OPTIMIZE");
        } else {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[TURN_OPTIMIZE] の指定は不可です。(コメント等にして除去して下さい)");
        }
    } else {
        if (leader == CLASS_FixedFrameSpline || leader == CLASS_FixedVelocitySpline) {
            throwCriticalException(prm_idstr<<" : "
                    "[CLASS]="<<classname<<" の場合は、[TURN_OPTIMIZE] の指定が必須です。");
        }
    }

    //SplineManufacture作成
    SplineManufacture* pSplManuf = nullptr;
    if (leader == CLASS_FixedFrameSpline) {
        pSplManuf = NEW FixedFrameSplineManufacture(spl_data_file.c_str(),
                                                    spent_frame,
                                                    angvelo_rzry_mv,
                                                    turn_way,
                                                    turn_optimize);
    } else if (leader == CLASS_FixedVelocitySpline) {
        pSplManuf = NEW FixedVelocitySplineManufacture(spl_data_file.c_str(),
                                                       angvelo_rzry_mv,
                                                       turn_way,
                                                       turn_optimize);
    } else if (leader == CLASS_SteppedCoordSpline) {
        pSplManuf = NEW SteppedCoordSplineManufacture(spl_data_file.c_str());
    } else {
        throwCriticalException("_classname="<<classname<< "は不明なクラスです");
    }
    pSplManuf->adjustAxisRate(rate_x, rate_y, rate_z); //拡大縮小
    pSplManuf->calculate(); //計算！

    return pSplManuf;
}

GgafCore::ResourceConnection<SplineManufacture>* SplineManufactureManager::processCreateConnection(const char* prm_idstr, SplineManufacture* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    SplineManufactureConnection* pConne = NEW SplineManufactureConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return pConne;
}

