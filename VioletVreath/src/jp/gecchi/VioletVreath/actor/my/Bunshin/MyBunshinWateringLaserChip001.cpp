#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(160); //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 20; //この値を大きくすると、カーブが緩くなる
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //計算簡素化用
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;

MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyBunshinWateringLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
    lockon_st_ = 0;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
    pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pAxsMver_->forceVxyzMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);

    WateringLaserChip::onActive();

    //ロックオン情報の引き継ぎ
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (getInfrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (getInfrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    if (getActiveFrame() > 7) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree() && getActiveFrame() < 30)  {
                aimChip(pMainLockOnTarget->_x,
                        pMainLockOnTarget->_y,
                        pMainLockOnTarget->_z );
            } else {
                lockon_st_ = 2;
            }
        }
        if (lockon_st_ == 2) {
            if (_pLeader == this) {
                aimChip(_x + pAxsMver_->_velo_vx_mv*11+1,
                        _y + pAxsMver_->_velo_vy_mv*10+1,
                        _z + pAxsMver_->_velo_vz_mv*10+1 );
            } else {
                aimChip(_pLeader->_x, _pLeader->_y, _pLeader->_z);
            }
        }
    }
    pAxsMver_->behave();
    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //分身はFKなので、絶対座標の確定が processSettlementBehavior() 以降となるため、ここで初期設定が必要
    if (hasJustChangedToActive()) {
        //活動開始初回フレーム、チップの速度と向きの初期設定
        setFaceAngAs(pOrg_);
        positionAs(pOrg_);
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100)); //初速はここで
        pAxsMver_->setZeroVxyzMvAcce();
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pOrg_pLockonCtrler_pRingTarget_ = pOrg_->pLockonCtrler_->pRingTarget_;
}

void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //    |                            vVT 仮的                        |
    //    |                                ^ ┌                        |
    //    |                 |仮的| > 5*vM /    ＼  vVP 仮自→仮的      |      仮的
    //    |                 となるような /       ＼                    |       ↑
    //    |                 vVTを設定   /         ┐                   |      仮自
    //    |                            /        ／vVM  仮自            |       ↑
    //    |                           /       ／  (vVMx,vVMy,vVMz)     |       ｜
    //    |                          /      ／                         |       ｜
    //    |                         /     ／                           |       ｜
    //    |                        /    ／ |仮自| = lVM * 5            |       ｜
    //    |                   vT 的   ／                               |       的
    //    |             ┌       ^  ／                                 |       ↑
    //    |               ＼    / ┐vM 現在の移動方向ベクトル          |       ｜
    //    | vVP 仮自→仮的  ＼ /／ (veloVxMv_,veloVyMv_,veloVzMv_)     |       ｜
    //    |                   自                                       |       自
    // ---+------------------------------------------               ---+---------------------------
    //    |                                                            |
    //
    // vVP が動きたい方向。vVPを求める！

    //自→的
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //自→仮自。
    const int vVMx = pAxsMver_->_velo_vx_mv;
    const int vVMy = pAxsMver_->_velo_vy_mv;
    const int vVMz = pAxsMver_->_velo_vz_mv;
    //|仮自| = lVM * 5
    const int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //仮自ベクトル大きさ簡易版
    //|的|
    const int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    const double r = (lVM*5 * 1.5) / lT;
    //* 1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    const double accX = ((vTx * r) - vVMx*5) * RR_MAX_ACCE;
    const double accY = ((vTy * r) - vVMy*5) * RR_MAX_ACCE;
    const double accZ = ((vTz * r) - vVMz*5) * RR_MAX_ACCE;

    if (_pLeader == this) {
        //先頭はやや速めに。SGN(accX)*5 を加算するのは、加速度を0にしないため
        pAxsMver_->setVxyzMvAcce(accX + SGN(accX)*5.0,
                                 accY + SGN(accY)*5.0,
                                 accZ + SGN(accZ)*5.0);
    } else {
        pAxsMver_->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                 accY + SGN(accY)*3.0,
                                 accZ + SGN(accZ)*3.0);
    }
    static const coord min_velo = MyBunshinWateringLaserChip001::MAX_VELO_RENGE/3;
    if (lVM < min_velo) {
        if (pAxsMver_->_velo_vx_mv == 0 && pAxsMver_->_velo_vy_mv == 0 && pAxsMver_->_velo_vz_mv == 0) {
            GgafDxKuroko* pOrg_Kuroko = pOrg_->getKuroko();
            pAxsMver_->setVxyzMvVelo(pOrg_Kuroko->_vX*min_velo,
                                     pOrg_Kuroko->_vY*min_velo,
                                     pOrg_Kuroko->_vZ*min_velo );
        } else {
            double vx = (double)(pAxsMver_->_velo_vx_mv);
            double vy = (double)(pAxsMver_->_velo_vy_mv);
            double vz = (double)(pAxsMver_->_velo_vz_mv);
            double t = (1.0 / sqrt(vx*vx + vy*vy + vz*vz)) * min_velo;
            pAxsMver_->setVxyzMvVelo(vx*t, vy*t, vz*t);
        }
    }
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (getInfrontChip() && getInfrontChip()->getInfrontChip() == nullptr) {
                    //中間先頭チップがヒットした場合、先端にも伝える(先端は当たり判定ないため中間先頭と同値にする)
                    ((MyBunshinWateringLaserChip001*)getInfrontChip())->lockon_st_ = 2;
                }
            } else {
                //オプションのロックオン以外のアクターに命中した場合
            }
        } else {
            //オプション非ロックオン中に命中した場合
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
    pOrg_ = nullptr;
    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
}

void MyBunshinWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinWateringLaserChip001::pModel_) {
        MyBunshinWateringLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinWateringLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    GGAF_DELETE(pAxsMver_);
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

