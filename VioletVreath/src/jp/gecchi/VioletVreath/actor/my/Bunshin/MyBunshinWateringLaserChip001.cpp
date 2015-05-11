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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinWateringLaserChip001::max_velo_renge_ = 160000; //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::r_max_acce_ = 20; //この値を大きくすると、カーブが緩くなる
const double MyBunshinWateringLaserChip001::rr_max_acce_ = 1.0 / r_max_acce_; //計算簡素化用
const float MyBunshinWateringLaserChip001::max_acce_renge_ = max_velo_renge_/r_max_acce_;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
char MyBunshinWateringLaserChip001::aaTextureName[3][51];
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
        if (pModel->_num_materials != 3) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001モデルは、マテリアが３つ必要です。");
        }
        for (DWORD i = 0; i < pModel->_num_materials; i ++) {
            strcpy(MyBunshinWateringLaserChip001::aaTextureName[i], pModel->_papTextureConnection[i]->peek()->getName());
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
    pAxsMver_->forceVxyzMvVeloRange(-max_velo_renge_, max_velo_renge_);
    pAxsMver_->forceVxyzMvAcceRange(-max_acce_renge_, max_acce_renge_);
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
        if (getFrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getFrontChip();
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (getFrontChip() == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getFrontChip();
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    if (getActiveFrame() > 7) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                aimChip(pMainLockOnTarget->_x,
                        pMainLockOnTarget->_y,
                        pMainLockOnTarget->_z );
            } else {
                lockon_st_ = 2;
            }
        }
        if (lockon_st_ == 2) {
            if (_pLeader == this) {
                aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                        _y + pAxsMver_->_velo_vy_mv*2+1,
                        _z + pAxsMver_->_velo_vz_mv*2+1 );
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
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100));
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
    //    |                        /    ／ |仮自| = 5*vM = lVM         |       ｜
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

    //自→仮自。上図の |仮自| = 5*vM
    const int vVMx = pAxsMver_->_velo_vx_mv*5;
    const int vVMy = pAxsMver_->_velo_vy_mv*5;
    const int vVMz = pAxsMver_->_velo_vz_mv*5;

    //|仮自|
    const int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //仮自ベクトル大きさ簡易版
    //|的|
    const int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    const double r = (lVM*1.5) / lT;
    //* 1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    const double accX = ((vTx * r) - vVMx) * rr_max_acce_;
    const double accY = ((vTy * r) - vVMy) * rr_max_acce_;
    const double accZ = ((vTz * r) - vVMz) * rr_max_acce_;

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
    //ネジレ描画が汚くならないように回転を制限
    if (lVM > max_velo_renge_/2) {
        angle rz_temp, ry_temp;
        UTIL::convVectorToRzRy(vVMx, vVMy, vVMz, rz_temp, ry_temp);
        const angle angDRZ = UTIL::getAngDiff(rz_temp, _rz);
        const angle angDRY = UTIL::getAngDiff(ry_temp, _ry);
        if (-4000 <= angDRZ) {
            _rz -= 4000;
        } else if (angDRZ <= 4000) {
            _rz += 4000;
        } else {
            _rz += angDRZ;
        }
        if (-4000 <= angDRY) {
            _ry -= 4000;
        } else if (angDRY <= 4000) {
            _ry += 4000;
        } else {
            _ry += angDRY;
        }
        if (_rz >= D360ANG) {
            _rz -= D360ANG;
        }
        if (_rz < 0) {
            _rz += D360ANG;
        }
        if (_ry >= D360ANG) {
            _ry -= D360ANG;
        }
        if (_ry < 0) {
            _ry += D360ANG;
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
                if (getFrontChip() && getFrontChip()->getFrontChip() == nullptr) {
                    //中間先頭チップがヒットした場合、先端にも伝える(先端は当たり判定ないため中間先頭と同値にする)
                    ((MyBunshinWateringLaserChip001*)getFrontChip())->lockon_st_ = 2;
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
        MyBunshinWateringLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    GGAF_DELETE(pAxsMver_);
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

