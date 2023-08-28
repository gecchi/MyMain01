#include "EnemyRatislavia.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion004.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT      ,
    PHASE_FLOAT_MOVE,
    PHASE_EXPLOSION ,
    PHASE_NOTHING   ,
    PHASE_BANPEI,
};

EnemyRatislavia::EnemyRatislavia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2) :
        VvChikeiActor<CubeMapMeshActor>(prm_name, prm_model, StatusReset(EnemyRatislavia)) {
    _class_name = "EnemyRatislavia";
    setCubeMap("BkSky_cubemap.dds", 0.4);
    r1_ = prm_r1;
    r2_ = prm_r2;
    colli_part_num_ = 16; //当たり判定球の数
}

void EnemyRatislavia::appendGroupChildAsFkOnSurface(GgafDx::GeometricActor* prm_pGeoActor, angle prm_ang1, angle prm_ang2) {
    //トーラスモデルはZY平面に円
    //位置を求める
    //平行移動( +r2_, +0, +0) > ang2のY軸回転 > 平行移動( +0, +0, -r1_) > ang1のX軸回転 変換行列の dx, dy, dz が欲しい
    //
    //    | COS[ang2]    , -SIN[ang2]*-SIN[ang1]             , -SIN[ang2]*COS[ang1]             , 0 |
    //    | 0            ,  COS[ang1]                        ,  SIN[ang1]                       , 0 |
    //    | SIN[ang2]    ,  COS[ang2]*-SIN[ang1]             ,  COS[ang2]*COS[ans]              , 0 |
    //    | r2_*COS[ang2], (r2_*-SIN[ang2] + -r1_)*-SIN[ang1], (r2_*-SIN[ang2] + -r1_)*COS[ang1], 1 |
    //より
    double X = r2_*ANG_COS(prm_ang2);
    double Y = (r2_*-ANG_SIN(prm_ang2) - r1_) * -ANG_SIN(prm_ang1);
    double Z = (r2_*-ANG_SIN(prm_ang2) - r1_) *  ANG_COS(prm_ang1);

    //向きを求める
    //平行移動( +0, +0, -r1_) > ang1のX軸回転 変換行列の dx, dy, dz を使用
    //    | 1, 0              , 0             , 0 |
    //    | 0, COS[ang1]      , SIN[ang1]     , 0 |
    //    | 0, -SIN[ang1]     , COS[ang1]     , 0 |
    //    | 0, -r1_*-SIN[ang1], -r1_*COS[ang1], 1 |
    //より
    double X2 = 0;
    double Y2 = -r1_*-ANG_SIN(prm_ang1);
    double Z2 = -r1_*ANG_COS(prm_ang1);
    angle rz, ry;
    UTIL::convVectorToRzRy((int)(X - X2), (int)(Y - Y2), (int)(Z - Z2),
                            rz, ry);
    //ボーンとして追加
    this->appendGroupChildAsFk(prm_pGeoActor, X, Y, Z, D0ANG, ry, rz);
}

void EnemyRatislavia::addCollisionAreaArea(int prm_nSphere) {
    angle* paAngRadial = NEW angle[prm_nSphere];
    UTIL::getRadialAngleArr(0, prm_nSphere, paAngRadial);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(prm_nSphere);
    for (int i = 0; i < prm_nSphere; i++) {
        pChecker->setColliSphere(
                    i,
                    0 , ANG_SIN(paAngRadial[i]) * r1_, ANG_COS(paAngRadial[i]) * r1_,
                    r2_,
                    false, true, true
                    );
    }
    setSpecialRenderDepthIndex(RENDER_DEPTH_FAR_INDEX-2);
    GGAF_DELETE(paAngRadial);
}

void EnemyRatislavia::onCreateModel() {
}

void EnemyRatislavia::initialize() {
    addCollisionAreaArea(colli_part_num_);
    setHitAble(true);
}

void EnemyRatislavia::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyRatislavia::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setAlpha(0);
            getAlphaFader()->transitionLinearUntil(1.0, 30*60);
            pPhase->change(PHASE_FLOAT_MOVE);
            break;
        }

        case PHASE_FLOAT_MOVE: {
            //イベント待ち
            break;
        }

        case PHASE_EXPLOSION: {
            if (pPhase->hasJustChanged()) {
                _TRACE_(FUNC_NAME<<" _pPhase=PHASE_EXPLOSION きたわ～");
            }
            if (pPhase->getFrame() % 16U == 0) {
                //沸々爆発
                //当たり判定球付近に爆発エフェクトを散乱させる
                GgafDx::CollisionPart* pPart;
                GgafDx::FigureActor* pE;
                WorldCollisionChecker* pChecker = getWorldCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getCollisionArea()->getPart(j);
                    pE = CommonScene_dispatchDelay(EffectExplosion004, RND(1,10));
                    if (pE) {
                        pE->setPosition(_x + pPart->_cx + RND(-r2_, +r2_),
                                        _y + pPart->_cy + RND(-r2_, +r2_),
                                        _z + pPart->_cz + RND(-r2_, +r2_));
                    }
                }
            }


            if (pPhase->hasArrivedFrameAt(480)) {
                //ここで大きい爆発
                //当たり判定球付近に爆発エフェクトを散乱させる
                GgafDx::CollisionPart* pPart;
                GgafDx::FigureActor* pE;
                WorldCollisionChecker* pChecker = getWorldCollisionChecker();
                for (int j = 0; j < colli_part_num_; j++) {
                    pPart = pChecker->getCollisionArea()->getPart(j);
                    pE = CommonScene_dispatch(EffectExplosion004);
                    if (pE) {
                        pE->setPosition(_x + pPart->_cx,
                                     _y + pPart->_cy,
                                     _z + pPart->_cz);
                    }
                }
                sayonara();
                pPhase->change(PHASE_NOTHING);
            }
            break;
        }
        case PHASE_NOTHING: {
            //死を松の実
            break;
        }
    }

    pLocoVehicle->behave();
    getAlphaFader()->behave();
}

void EnemyRatislavia::processJudgement() {
    if (wasDeclaredEnd() == false && isOutOfSpacetime()) {
        sayonara(600);
    }
}

void EnemyRatislavia::onHit(const GgafCore::Actor* prm_pOtherActor) {

}

void EnemyRatislavia::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if (prm_event_val == RATISLAVIA_EXPLOSION) {
        _TRACE_(FUNC_NAME<<" RATISLAVIA_EXPLOSION キャッチ");
        setHitAble(false);
        getPhase()->change(PHASE_EXPLOSION);
    }
}

int EnemyRatislavia::isOutOfView() {
    //視野外判定無し
    return 0;
}

bool EnemyRatislavia::isOutOfSpacetime() const {
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    if (pSpacetime->_x_bound_left <= _x) {
        return false;
    } else {
        return true;
    }
}

EnemyRatislavia::~EnemyRatislavia() {
}
