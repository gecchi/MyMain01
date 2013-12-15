#include "stdafx.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperC.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxAccelerator.hpp"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"


using namespace GgafCore;
using namespace GgafDxCore;

GgafDxKurokoHelperC::GgafDxKurokoHelperC(GgafDxKuroko* prm_pMaster) : GgafObject(),
        _pMaster(prm_pMaster) {
    _smthMvRzAng._velo = _pMaster->_angveloRzMv;
    _smthMvRzAng._acce = _pMaster->_angacceRzMv;
    _smthMvRyAng._velo = _pMaster->_angveloRyMv;
    _smthMvRyAng._acce = _pMaster->_angacceRyMv;
}

void GgafDxKurokoHelperC::behave() {
    bool flg = _smthMvRzAng._prm._flg;
    _smthMvRzAng.behave();
    if (flg) {
        _pMaster->setRzMvAngVelo(_smthMvRzAng._velo - _smthMvRzAng._acce); //‚±‚¤‚µ‚È‚¢‚Æ•ˆß‚Ìbehave‚Å‚Q‰ñ_acce‘«‚µž‚Ü‚ê‚é‚µ
        _pMaster->setRzMvAngAcce(_smthMvRzAng._acce);
    }
    flg = _smthMvRyAng._prm._flg;
    _smthMvRyAng.behave();
    if (flg) {
        _pMaster->setRyMvAngVelo(_smthMvRyAng._velo - _smthMvRyAng._acce); //‚±‚¤‚µ‚È‚¢‚Æ•ˆß‚Ìbehave‚Å‚Q‰ñ_acce‘«‚µž‚Ü‚ê‚é‚µ
        _pMaster->setRyMvAngAcce(_smthMvRyAng._acce);
    }
}

void GgafDxKurokoHelperC::turnRzMvAngByDt(
                        angle prm_angular_distance, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_endacc_flg ) {

    _smthMvRzAng._value = 0;
    _smthMvRzAng._velo = _pMaster->_angveloRzMv;
    _smthMvRzAng._acce = _pMaster->_angacceRzMv;
    _smthMvRzAng.accelerateByDt(prm_angular_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_endacc_flg);
}
void GgafDxKurokoHelperC::turnRyMvAngByDt(
                        angle prm_angular_distance, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_endacc_flg ) {

    _smthMvRyAng._value = 0;
    _smthMvRyAng._velo = _pMaster->_angveloRyMv;
    _smthMvRyAng._acce = _pMaster->_angacceRyMv;
    _smthMvRyAng.accelerateByDt(prm_angular_distance, prm_target_frames,
                           prm_p1,prm_p2,prm_end_angvelo,
                           prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnRzMvAngByVd(
        angvelo prm_top_angvelo, angle prm_angular_distance,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    _smthMvRzAng._value = 0;
    _smthMvRzAng._velo = _pMaster->_angveloRzMv;
    _smthMvRzAng._acce = _pMaster->_angacceRzMv;
    _smthMvRzAng.accelerateByVd(prm_top_angvelo, prm_angular_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_endacc_flg);
}
void GgafDxKurokoHelperC::turnRyMvAngByVd(
        angvelo prm_top_angvelo, angle prm_angular_distance,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    _smthMvRyAng._value = 0;
    _smthMvRyAng._velo = _pMaster->_angveloRyMv;
    _smthMvRyAng._acce = _pMaster->_angacceRyMv;
    _smthMvRyAng.accelerateByVd(prm_top_angvelo, prm_angular_distance,
                                prm_p1,prm_p2, prm_end_angvelo,
                                prm_endacc_flg);
}


void GgafDxKurokoHelperC::turnRzMvAngByDtTo(angle prm_ang_rz_target, int prm_way, int prm_target_frames,
                                              float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                              bool prm_endacc_flg) {
    angle angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
    turnRzMvAngByDt(angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
}
void GgafDxKurokoHelperC::turnRyMvAngByDtTo(angle prm_ang_ry_target, int prm_way, int prm_target_frames,
                                              float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                              bool prm_endacc_flg) {
    angle angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    turnRyMvAngByDt(angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnRzRyMvAngByDtTo(
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {

    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                          out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }

    turnRzMvAngByDt(out_rz_angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    turnRyMvAngByDt(out_ry_angular_distance, prm_target_frames,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnMvAngByDtTwd(
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        int prm_target_frames,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pMaster->_pActor->_x,
                           prm_ty - _pMaster->_pActor->_y,
                           prm_tz - _pMaster->_pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);
    turnRzRyMvAngByDtTo(
            out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);

}

void GgafDxKurokoHelperC::turnMvAngByDtTwd(
                    GgafDxGeometricActor* prm_pActor_Target, int prm_way, bool prm_optimize_ang,
                    int prm_target_frames,
                    float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                    bool prm_endacc_flg) {
    turnMvAngByDtTwd(
            prm_pActor_Target->_x, prm_pActor_Target->_y, prm_pActor_Target->_z, prm_way, prm_optimize_ang,
            prm_target_frames,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);
}


void GgafDxKurokoHelperC::turnRzMvAngByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_rz_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
        angle angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
        turnRzMvAngByVd(prm_top_angvelo, angular_distance,
                            prm_p1, prm_p2, prm_end_angvelo,
                            prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnRyMvAngByVdTo(
        angvelo prm_top_angvelo, angle prm_ang_ry_target, int prm_way,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
        angle angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
        turnRyMvAngByVd(
                prm_top_angvelo, angular_distance,
                prm_p1, prm_p2, prm_end_angvelo,
                prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnRzRyMvAngByVdTo(
        angvelo prm_top_angvelo,
        angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    angle out_rz_angular_distance;
    angle out_ry_angular_distance;
    if (prm_optimize_ang) {
        _pMaster->getRzRyMvAngDistanceTwd(prm_ang_rz_target, prm_ang_ry_target, prm_way,
                                         out_rz_angular_distance, out_ry_angular_distance);
    } else {
        out_rz_angular_distance = _pMaster->getRzMvAngDistance(prm_ang_rz_target, prm_way);
        out_ry_angular_distance = _pMaster->getRyMvAngDistance(prm_ang_ry_target, prm_way);
    }
    double drz = ABS(out_rz_angular_distance);
    double dry = ABS(out_ry_angular_distance);
    if (drz > dry) {
        double drr = dry / drz;
        turnRzMvAngByVd(prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnRyMvAngByVd(prm_top_angvelo*drr, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    } else if (drz < dry) {
        double drr = drz / dry;
        turnRzMvAngByVd(prm_top_angvelo*drr, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnRyMvAngByVd(prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    } else {
        turnRzMvAngByVd(prm_top_angvelo, out_rz_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
        turnRyMvAngByVd(prm_top_angvelo, out_ry_angular_distance,
                        prm_p1, prm_p2, prm_end_angvelo,
                        prm_endacc_flg);
    }
}

void GgafDxKurokoHelperC::turnMvAngByVdTwd(
        angvelo prm_top_angvelo,
        coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {
    angle out_angRz_Target;
    angle out_angRy_Target;
    UTIL::convVectorToRzRy(prm_tx - _pMaster->_pActor->_x,
                           prm_ty - _pMaster->_pActor->_y,
                           prm_tz - _pMaster->_pActor->_z,
                           out_angRz_Target,
                           out_angRy_Target);
    turnRzRyMvAngByVdTo(
            prm_top_angvelo,
            out_angRz_Target, out_angRy_Target, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);
}

void GgafDxKurokoHelperC::turnMvAngByVdTwd(
        angvelo prm_top_angvelo,
        GgafDxGeometricActor* prm_pActor_Target, int prm_way, bool prm_optimize_ang,
        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
        bool prm_endacc_flg) {

    turnMvAngByVdTwd(
            prm_top_angvelo,
            prm_pActor_Target->_x, prm_pActor_Target->_y, prm_pActor_Target->_z, prm_way, prm_optimize_ang,
            prm_p1, prm_p2, prm_end_angvelo,
            prm_endacc_flg);
}

GgafDxKurokoHelperC::~GgafDxKurokoHelperC() {
}


