#include "stdafx.h"
#include "EnemyHisbe.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbe::EnemyHisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hisbe", STATUS(EnemyHisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/HisbeCM", STATUS(EnemyHisbe)) {

    _class_name = "EnemyHisbe";
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

//    //リフレクション------>
//    GgafActorDepository* pDepoEffect = NEW GgafActorDepository("HisbeLaser");
//    EffectLaserRefraction001* pEffect;
//    for (int i = 0; i < 100; i++) {
//        std::string name = "EffectLaserRefraction001["+XTOS(i)+"]";
//        pEffect = NEW EffectLaserRefraction001(name.c_str());
//        pDepoEffect->addSubLast(pEffect);
//    }
//    addSubGroup(pDepoEffect);
//
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Hisbeは弾切れフレームを1にしないとパクパクしちゃいます。
//    for (int i = 0; i < 100; i++) { //レーザーストック
//        std::string name = "EnemyHisbeLaserChip002["+XTOS(i)+"]";
//        EnemyHisbeLaserChip002* pChip = NEW EnemyHisbeLaserChip002(name.c_str());
//        int num_refraction = pChip->pKurokoLeader_->getPointNum();
//        pChip->config(num_refraction, 1, 1, false, pDepoEffect);
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //ホーミング------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(300, 1, nullptr); //Hisbeは弾切れフレームを1にしないとパクパクしちゃいます。
//    for (int i = 0; i < 300; i++) { //レーザーストック
//        std::string name = "EnemyHisbeLaserChip001["+XTOS(i)+"]";
//        EnemyHisbeLaserChip001* pChip = NEW EnemyHisbeLaserChip001(name.c_str());
//        pChip->_is_fix_begin_pos = false;
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------

//    //水------>
//    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
//    pLaserChipDepo_->config(100, 1, nullptr); //Hisbeは弾切れフレームを1にしないとパクパクしちゃいます。
//    for (int i = 0; i < 100; i++) { //レーザーストック
//        std::string name = "EnemyHisbeLaserChip003["+XTOS(i)+"]";
//        EnemyHisbeLaserChip003* pChip = NEW EnemyHisbeLaserChip003(name.c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }
//    addSubGroup(pLaserChipDepo_);
//    //<---------------------


    //ホーミング(リポジトリ)------>
//    pConn_LaserChipDepoStore_ = connect_DepositoryManager("EnemyHisbeLaserChip001DepoStore");
//    pLaserChipDepo_ = nullptr;
    //<---------------------

    //リフレクション(リポジトリ)------>
    pConn_LaserChipDepoStore_ = connect_DepositoryManager("EnemyHisbeLaserChip002DepoStore");
    pLaserChipDepo_ = nullptr;


    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
}

void EnemyHisbe::onCreateModel() {
}

void EnemyHisbe::initialize() {
    _pKuroko->relateFaceWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 40000);

//    if (pConn_LaserChipDepoStore_->chkFirstConnectionIs(this)) {
//        _TRACE_("pConn_LaserChipDepoStore_は、ワシ("<<this<<")が育てたエヘン！")
//        getPlatformScene()->getSceneDirector()->addSubGroup(
//                pConn_LaserChipDepoStore_->peek()->extract()
//                );
//    }
}

void EnemyHisbe::onActive() {
    _pStatus->reset();
    _pMorpher->reset();
    _pProg->reset(PROG_WAIT);
}

void EnemyHisbe::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_) {
                if (pLaserChipDepo_->_num_chip_active == 0) {
                    pLaserChipDepo_ = nullptr;
                }
            } else {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->morphLinerUntil(1, 1.0, 120);
            }
            if (!_pMorpher->isMorphing()) {
                //完全に開いたら
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pConn_LaserChipDepoStore_->peek()->dispatch()); //レーザーセット一本借ります。
            }
            if (pLaserChipDepo_) {
                LaserChip* pLaser = pLaserChipDepo_->dispatch();
                if (pLaser) {
                    pLaser->positionAs(this);
                    pLaser->_pKuroko->setRzRyMvAng(_pKuroko->_angFace[AXIS_Z], _pKuroko->_angFace[AXIS_Y]);
                                       //レーザーのスプラインがRELATIVE_DIRECTIONのためMvAngの設定が必要。
                    if (pLaser->_pChip_front == nullptr) {
                        _pSeTx->play3D(SE_FIRE);
                    }
                } else {
                    _pProg->changeNext();
                }
            } else {
                //借りれなかった！
                _pProg->changeNext();
            }
            break;
        }

        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->morphLinerUntil(1, 0.0, 120); //閉じる
            if (!_pMorpher->isMorphing()) {
                //完全に閉じたら
                _pProg->change(PROG_WAIT);
            }
            break;
        }

        default:
            break;
    }
    _pKuroko->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyHisbe::processJudgement() {
    if (isOutOfUniverse()) {
        if (_x >= GgafDxUniverse::_x_gone_right) {
            //WALL内実験
        } else {
            sayonara();
        }
    }
}

void EnemyHisbe::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe::onInactive() {
    //sayonara();
}

EnemyHisbe::~EnemyHisbe() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
        pConn_LaserChipDepoStore_->close();
    //pConn_RefractionEffectDepository_->close();
}
