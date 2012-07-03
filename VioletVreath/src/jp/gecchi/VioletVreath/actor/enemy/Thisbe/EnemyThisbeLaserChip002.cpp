#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbeLaserChip002::EnemyThisbeLaserChip002(const char* prm_name) :
        RefractionLaserChip(prm_name, "ThisbeLaserChip001", STATUS(EnemyThisbeLaserChip001)) {
    _class_name = "EnemyThisbeLaserChip002";
    pSplManufCon_ = connectSplineManufactureManager("Hilbert"); //ヒルベルト曲線
    pSplSeq_ = pSplManufCon_->fetch()->createSplineSequence(_pKurokoA);
    rnum_ = pSplSeq_->_pManufacture->_sp->_rnum;
}

void EnemyThisbeLaserChip002::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyThisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //ステータスリセット
    _pStatus->reset();

    //_pKurokoA->setMvAcce(300);
    //_pKurokoA->forceRyMvAngVeloRange(-90000, 90000);
    _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[1]);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyThisbeLaserChip002::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}


void EnemyThisbeLaserChip002::onRefractionBegin(int prm_num_refraction)  {

}

void EnemyThisbeLaserChip002::onRefractionFinish(int prm_num_refraction)  {
    _TRACE_("f:["<<getActivePartFrame() <<"] rnum="<<(pSplSeq_->_pManufacture->_sp->_rnum)<<"prm_num_refraction="<<prm_num_refraction);
    _TRACE_("f:["<<getActivePartFrame() <<"] befor xyz="<<_X<<","<<_Y<<","<<_Z);
    if (prm_num_refraction == 0) {
        return;
    }
    if (getActivePartFrame() == 3) {

        pSplSeq_->exec(RELATIVE_DIRECTION); //向いた方向にワールド変換
    }
    if (getActivePartFrame() >= 3) {
        if (rnum_ > prm_num_refraction) {


            SplineLine* sp = pSplSeq_->_pManufacture->_sp;
            _TRACE_("f:["<<getActivePartFrame() <<"] sp="<<sp->_X_compute[prm_num_refraction-1]<<","<<sp->_Y_compute[prm_num_refraction-1]<<","<<sp->_Z_compute[prm_num_refraction-1]);
            _TRACE_("f:["<<getActivePartFrame() <<"] _paDistace_to["<<prm_num_refraction-1<<"]="<<(pSplSeq_->_pManufacture->_paDistace_to[prm_num_refraction-1]));

            _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[prm_num_refraction-1]);
        } else {
            SplineLine* sp = pSplSeq_->_pManufacture->_sp;
            _TRACE_("LAST!");
            _TRACE_("f:["<<getActivePartFrame() <<"] sp="<<sp->_X_compute[rnum_ -1]<<","<<sp->_Y_compute[rnum_ -1]<<","<<sp->_Z_compute[rnum_ -1]);
            _TRACE_("f:["<<getActivePartFrame() <<"] _paDistace_to["<<rnum_ -1<<"]="<<(pSplSeq_->_pManufacture->_paDistace_to[rnum_ -1]));

            _pKurokoA->setMvVelo(pSplSeq_->_pManufacture->_paDistace_to[rnum_ -1]);
        }
        pSplSeq_->behave();
        _pKurokoA->behave();
    }
    _TRACE_("f:["<<getActivePartFrame() <<"] after xyz="<<_X<<","<<_Y<<","<<_Z);

//        SplineManufacture* pSpManuf = pSplManufCon_->fetch();
//        SplineSource* pSpSource = pSpManuf->_pSplSrc;
//        SplineLine* pSp = pSpSource->_pSp;
//        angle out_angRz_Target;
//        angle out_angRy_Target;
//        angle out_d_angRz;
//        angle out_d_angRy;
//        UTIL::getRzRyAng(P_MYSHIP->_X - _X,
//                         P_MYSHIP->_Y - _Y,
//                         P_MYSHIP->_Z - _Z,
//                         out_angRz_Target,
//                         out_angRy_Target);
//        out_d_angRz = _pKurokoA->getRzMvAngDistance(out_angRz_Target, TURN_CLOSE_TO);
//        out_d_angRy = _pKurokoA->getRyMvAngDistance(out_angRy_Target, TURN_CLOSE_TO);
//        _pKurokoA->addRzMvAng(SGN(out_d_angRz)*20000);
//        _pKurokoA->addRyMvAng(SGN(out_d_angRy)*30000);
////        _pKurokoA->execTurnMvAngSequence(
////                        P_MYSHIP,
////                        90000, 0,
////                        TURN_CLOSE_TO, false);
//
////        _pKurokoA->setMvAng(P_MYSHIP);
}

void EnemyThisbeLaserChip002::onHit(GgafActor* prm_pOtherActor) {
//    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
//    //ヒット時
//
//    //体力計算
//    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
//        //ヒットして消滅時
//        sayonara();
//    } else {
//        //ヒットして生存時
//    }
}

EnemyThisbeLaserChip002::~EnemyThisbeLaserChip002() {
    DELETE_IMPOSSIBLE_NULL(pSplSeq_);
    pSplManufCon_->close();
}

