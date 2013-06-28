#include "stdafx.h"
#include "EnemySylvia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/util/GgafDxCollisionArea.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion004.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemySylvia::EnemySylvia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        CubeMapMeshActor(prm_name, prm_model, STATUS(EnemySylvia)) {
    _class_name = "EnemySylvia";
    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
    colli_part_num_ = 16; //当たり判定球の数
    useProgress(PROG_NOTHING);
}

void EnemySylvia::addSubGroupAsFkOnSurface(GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2) {
    //トーラスモデルはZY平面に円
    //位置を求める
    //平行移動( +r2_, +0, +0) > angPos2のY軸回転 > 平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz が欲しい
    //
    //    | COS[angPos2]    , -SIN[angPos2]*-SIN[angPos1]             , -SIN[angPos2]*COS[angPos1]             , 0 |
    //    | 0               ,  COS[angPos1]                           ,  SIN[angPos1]                          , 0 |
    //    | SIN[angPos2]    ,  COS[angPos2]*-SIN[angPos1]             ,  COS[angPos2]*COS[angPos]              , 0 |
    //    | r2_*COS[angPos2], (r2_*-SIN[angPos2] + -r1_)*-SIN[angPos1], (r2_*-SIN[angPos2] + -r1_)*COS[angPos1], 1 |
    //より
    double X = r2_*ANG_COS(prm_angPos2);
    double Y = (r2_*-ANG_SIN(prm_angPos2) - r1_) * -ANG_SIN(prm_angPos1);
    double Z = (r2_*-ANG_SIN(prm_angPos2) - r1_) *  ANG_COS(prm_angPos1);

    //向きを求める
    //平行移動( +0, +0, -r1_) > angPos1のX軸回転 変換行列の dx, dy, dz を使用
    //    | 1, 0                 , 0                , 0 |
    //    | 0, COS[angPos1]      , SIN[angPos1]     , 0 |
    //    | 0, -SIN[angPos1]     , COS[angPos1]     , 0 |
    //    | 0, -r1_*-SIN[angPos1], -r1_*COS[angPos1], 1 |
    //より
    double X2 = 0;
    double Y2 = -r1_*-ANG_SIN(prm_angPos1);
    double Z2 = -r1_*ANG_COS(prm_angPos1);
    angle angRz, angRy;
    UTIL::convVectorToRzRy((int)(X - X2), (int)(Y - Y2), (int)(Z - Z2),
                           angRz, angRy);
    //ボーンとして追加
    this->addSubGroupAsFk(prm_pGeoActor, X, Y, Z, D0ANG, angRy, angRz);
}

void EnemySylvia::makeCollisionArea(int prm_nSphere){
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngle2D(0, prm_nSphere, paAngRadial);
    _pColliChecker->makeCollision(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        _pColliChecker->setColliSphere(
                i,
                0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                r2_,
                false, true, true
                );
    }
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_BIGOBJ-2);
    GGAF_DELETE(paAngRadial);
}

void EnemySylvia::onCreateModel() {
//    _pModel->_pTexBlinker->setBlinkableRange(0.7, 0.2, 3.0);
//    _pModel->_pTexBlinker->setPower(0.5);
//    _pModel->_pTexBlinker->beat(60*20, 60*9, 60*3, -1);
}

void EnemySylvia::initialize() {
    makeCollisionArea(colli_part_num_);
    setHitAble(true);
    setAlpha(1.00);
}

void EnemySylvia::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemySylvia::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_FLOAT_MOVE);
            break;
        }

        case PROG_FLOAT_MOVE: {
            //イベント待ち
            break;
        }

        case PROG_EXPLOSION: {
            if (_pProg->isJustChanged()) {
                _TRACE_("EnemySylvia::processBehavior() _pProg=PROG_EXPLOSION きたわ～");
            }
            if (_pProg->getFrameInProgress() % 16 == 0) {
                //沸々爆発
                //当たり判定球付近に爆発エフェクトを散乱させる
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = _pColliChecker->_pCollisionArea->_papColliPart[j];
                    pE = dispatchDelayFromCommon(EffectExplosion004, RND(1,10));
                    if (pE) {
                        pE->position(_X + pPart->_cx + RND(-r2_, +r2_),
                                   _Y + pPart->_cy + RND(-r2_, +r2_),
                                   _Z + pPart->_cz + RND(-r2_, +r2_));
                    }
                }
            }


            if (_pProg->getFrameInProgress() == 480) {
                //ここで大きい爆発
                //当たり判定球付近に爆発エフェクトを散乱させる
                GgafDxCollisionPart* pPart;
                GgafDxDrawableActor* pE;
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = _pColliChecker->_pCollisionArea->_papColliPart[j];
                    pE = dispatchFromCommon(EffectExplosion004);
                    if (pE) {
                        pE->position(_X + pPart->_cx,
                                   _Y + pPart->_cy,
                                   _Z + pPart->_cz);
                    }
                }
                sayonara();
                _pProg->change(PROG_NOTHING);
            }
            break;
        }
        case PROG_NOTHING: {
            //死を松の実
            break;
        }
    }

    _pKurokoA->behave();
}

void EnemySylvia::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfUniverse()) {
        sayonara(600);
    }
}

void EnemySylvia::onHit(GgafActor* prm_pOtherActor) {

}

void EnemySylvia::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if (prm_no == SYLVIA_EXPLOSION) {
        _TRACE_("EnemySylvia::onCatchEvent SYLVIA_EXPLOSION キャッチ");
        setHitAble(false);
        _pProg->change(PROG_EXPLOSION);
    }

}

int EnemySylvia::isOutOfView() {
    //視野外判定無し
    return 0;
}

bool EnemySylvia::isOutOfUniverse() {
    if (GgafDxCore::GgafDxUniverse::_X_gone_left < _X) {
        return false;
    } else {
        return true;
    }
}

EnemySylvia::~EnemySylvia() {
}
