#include "stdafx.h"
#include "MyOptionWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



GgafDxCore::GgafDxModel* MyOptionWateringLaserChip001::pModel_  = nullptr;
char MyOptionWateringLaserChip001::aaTextureName[3][51];
int MyOptionWateringLaserChip001::tex_no_ = 0;


MyOptionWateringLaserChip001::MyOptionWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyOptionWateringLaserChip001", STATUS(MyOptionWateringLaserChip001)) {
    _class_name = "MyOptionWateringLaserChip001";
    default_stamina_ = _pStatus->get(STAT_Stamina);
    pOrg_ = nullptr;
    lockon_st_ = 0;
    is_lockon_ = false;
    max_acce_renge_ = 0;
    max_velo_renge_ = 160000; //この値を大きくすると、最高速度が早くなる。
    r_max_acce_ = 20; //この値を大きくすると、カーブが緩くなる
    rr_max_acce_ = 1.0 / r_max_acce_; //計算簡素化用
    if (!MyOptionWateringLaserChip001::pModel_) {
        if (_pModel->_num_materials != 3) {
            throwGgafCriticalException("MyOptionWateringLaserChip001::onCreateModel() MyOptionWateringLaserChip001モデルは、マテリアが３つ必要です。");
        }
        for (DWORD i = 0; i < _pModel->_num_materials; i ++) {
            strcpy(MyOptionWateringLaserChip001::aaTextureName[i], _pModel->_papTextureConnection[i]->peek()->getName());
        }
        MyOptionWateringLaserChip001::pModel_ = _pModel;
    }
}

void MyOptionWateringLaserChip001::initialize() {
    _pKurokoA->relateFaceWithMvAng(true);
    registerHitAreaCube_AutoGenMidColli(80000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void MyOptionWateringLaserChip001::onCreateModel() {

}

void MyOptionWateringLaserChip001::onActive() {
    _pStatus->reset();
    default_stamina_ = _pStatus->get(STAT_Stamina);
    WateringLaserChip::onActive();
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
        if (_pChip_front == nullptr) {
            //先端チップ
            lockon_st_ = 1;
        } else {
            //先端以外
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    } else {
        if (_pChip_front == nullptr) {
            //先端チップ
            lockon_st_ = 0;
        } else {
            //先端以外
            MyOptionWateringLaserChip001* pF = (MyOptionWateringLaserChip001*) _pChip_front;
            lockon_st_ = pF->lockon_st_;//一つ前のロックオン情報を引き継ぐ
        }
    }
    _pKurokoB->setZeroVxyzMvAcce(); //加速度リセット
    //Vxyzの速度はオプション側で設定される


    _pKurokoB->forceVxyzMvVeloRange(-max_velo_renge_, max_velo_renge_);
    max_acce_renge_ = max_velo_renge_/r_max_acce_;
    _pKurokoB->forceVxyzMvAcceRange(-max_acce_renge_, max_acce_renge_);
}

void MyOptionWateringLaserChip001::processBehavior() {
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    if (getActiveFrame() > 6) {
        if (lockon_st_ == 1) {
            if (pMainLockOnTarget && pMainLockOnTarget->isActiveInTheTree()) {
                moveChip(pMainLockOnTarget->_x,
                         pMainLockOnTarget->_y,
                         pMainLockOnTarget->_z );
            } else {
                //_pKurokoB->setZeroVxyzMvAcce();
                lockon_st_ = 2;
            }
        }

        if (lockon_st_ == 2) {
            if (_pLeader) {
                if (_pLeader == this) {
                    moveChip(_x + _pKurokoB->_veloVxMv*4+1,
                             _y + _pKurokoB->_veloVyMv*2+1,
                             _z + _pKurokoB->_veloVzMv*2+1 );
                } else {
                    moveChip(_pLeader->_x, _pLeader->_y, _pLeader->_z);
                }
            }
        }
    }

    WateringLaserChip::processBehavior();//座標を移動させてから呼び出すこと
    //根元からレーザー表示のため強制的に座標補正
    if (onChangeToActive()) {
        positionAs(pOrg_);
        _tmpX = _x;
        _tmpY = _y;
        _tmpZ = _z;
    }

}

void MyOptionWateringLaserChip001::moveChip(int tX, int tY, int tZ) {
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
    int vTx = tX - _x;
    int vTy = tY - _y;
    int vTz = tZ - _z;

    //自→仮自。上図の |仮自| = 5*vM
    int vVMx = _pKurokoB->_veloVxMv*5;
    int vVMy = _pKurokoB->_veloVyMv*5;
    int vVMz = _pKurokoB->_veloVzMv*5;

    //|仮自|
    int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //仮自ベクトル大きさ簡易版
    //|的|
    int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    double r = (lVM*1.5) / lT;
    //* 2は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    double accX = ((vTx * r) - vVMx) * rr_max_acce_;
    double accY = ((vTy * r) - vVMy) * rr_max_acce_;
    double accZ = ((vTz * r) - vVMz) * rr_max_acce_;

    if (_pChip_front == nullptr) {
        //先頭はやや速めに。SGN(accX)*5 を加算するのは、加速度を0にしないため
        _pKurokoB->setVxyzMvAcce(accX + SGN(accX)*5.0,
                                 accY + SGN(accY)*5.0,
                                 accZ + SGN(accZ)*5.0);
    } else {
        _pKurokoB->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                 accY + SGN(accY)*3.0,
                                 accZ + SGN(accZ)*3.0);
    }
    //ネジレ描画が汚くならないように回転を制限
    if (lVM > max_velo_renge_/2) {
        angle rz_temp, ry_temp;
        UTIL::convVectorToRzRy(vVMx, vVMy, vVMz, rz_temp, ry_temp);
        angle angDRZ = UTIL::getAngDiff(rz_temp, _rz);
        angle angDRY = UTIL::getAngDiff(ry_temp, _ry);
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

void MyOptionWateringLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void MyOptionWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    GgafDxGeometricActor* pMainLockOnTarget = pOrg_->pLockonCtrler_->pRingTarget_->getCurrent();
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        if (pMainLockOnTarget) { //既にオプションはロックオン中
            if (pOther == pMainLockOnTarget) {
                //オプションのロックオンに見事命中した場合

                lockon_st_ = 2; //ロックオンをやめる。非ロックオン（ロックオン→非ロックオン）
                if (_pChip_front && _pChip_front->_pChip_front == nullptr) {
                    //中間先頭チップがヒットした場合、先端にも伝える(先端は当たり判定ないため中間先頭と同値にする)
                    ((MyOptionWateringLaserChip001*)_pChip_front)->lockon_st_ = 2;
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
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            _pStatus->set(STAT_Stamina, default_stamina_);
            //ロックオン可能アクターならロックオン
            if (pOther->_pStatus->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }
    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyOptionWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
    lockon_st_ = 0;
}

void MyOptionWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyOptionWateringLaserChip001::pModel_) {
        MyOptionWateringLaserChip001::tex_no_ = prm_tex_no;
        MyOptionWateringLaserChip001::pModel_->swapTopTextureOrder(aaTextureName[prm_tex_no]);
    }
}

MyOptionWateringLaserChip001::~MyOptionWateringLaserChip001() {
    MyOptionWateringLaserChip001::pModel_ = nullptr;
}

