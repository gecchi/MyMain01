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
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Main.h"

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
    pLockon_ = nullptr;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    aim_status_ = PROG_BANPEI;
    pAimPoint_ = nullptr;
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

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockon_ = pOrg_->pLockonCtrler_->pMainLockonEffect_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    aim_status_ = PROG_AIM_AT_NOTHING;

    WateringLaserChip::onActive();

    //ロックオン情報の引き継ぎ
//    GgafDxGeometricActor* pLockonTarget = pOrg_pLockonCtrler_pRingTarget_->getCurrent();
    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
    if (pF == nullptr) {
        //先端チップ
        GgafDxGeometricActor* pLockonTarget = pLockon_->pTarget_;
        if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
            //ロックオン中
            pAimPoint_ = pOrg_->getAimPoint();
            pAimPoint_->pTarget = pLockonTarget;
            pAimPoint_->target01_x = pLockonTarget->_x;
            pAimPoint_->target01_y = pLockonTarget->_y;
            pAimPoint_->target01_z = pLockonTarget->_z;
            aim_status_ = PROG_AIM_AT_LOCK_ON_TARGET01;
        } else {
            //ロックオンしていない
            pAimPoint_ = pOrg_->getAimPoint();
            pAimPoint_->pTarget = nullptr;
            pAimPoint_->target01_x = pOrg_->_x;
            pAimPoint_->target01_y = pOrg_->_y;
            pAimPoint_->target01_z = pOrg_->_z;
            aim_status_ = PROG_AIM_AT_NOTHING;
        }
    } else {
        //先端以外

        pAimPoint_ = pF->pAimPoint_; //受け継ぐ
        aim_status_ = pF->aim_status_;
    }

}

void MyBunshinWateringLaserChip001::processBehavior() {
    GgafProgress* pProg = getProgress();
    frame active_frame = getActiveFrame();
    MyBunshin::AimPoint* pAimPoint = pAimPoint_;
    if (aim_status_ == PROG_AIM_AT_LOCK_ON_TARGET01) {
        if (pAimPoint->is_enable_target01) { //ロックオンに命中した場合。
            if (_pLeader == this) {
                aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                goto AIM_AT_NOTHING_TARGET01_AFTER;
            } else {
                aim_status_ = PROG_AIM_AT_TARGET01;
                goto AIM_AT_TARGET01;
            }
        } else {
            GgafDxGeometricActor* pAimTarget = pAimPoint->pTarget;
            if (pAimTarget && pAimTarget->isActiveInTheTree() && getActiveFrame() < 120)  {
                if (active_frame > 7 ) {
                    aimChip(pAimTarget->_x,
                            pAimTarget->_y,
                            pAimTarget->_z );
                }
                if (_pLeader == this) {
                    pAimPoint->target01_x = pAimTarget->_x;
                    pAimPoint->target01_y = pAimTarget->_y;
                    pAimPoint->target01_z = pAimTarget->_z;
                      //未だ有効にはしてない。座標更新のみ
                }
            } else {
                aim_status_ = PROG_AIM_AT_TARGET01;
                goto AIM_AT_TARGET01;
            }
        }
    }

    AIM_AT_TARGET01:

    if (aim_status_ == PROG_AIM_AT_TARGET01) {
        static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
        if (_x >= pAimPoint->target01_x - renge) {
            if (_x <= pAimPoint->target01_x + renge) {
                if (_y >= pAimPoint->target01_y - renge) {
                    if (_y <= pAimPoint->target01_y + renge) {
                        if (_z >= pAimPoint->target01_z - renge) {
                            if (_z <= pAimPoint->target01_z + renge) {
                                aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                                goto AIM_AT_NOTHING_TARGET01_AFTER;
                            }
                        }
                    }
                }
            }
        }
        if (active_frame < 120) {
            if (active_frame > 7 ) {
                aimChip(pAimPoint->target01_x,
                        pAimPoint->target01_y,
                        pAimPoint->target01_z );
            }
        } else {
            aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
            goto AIM_AT_NOTHING_TARGET01_AFTER;
        }
    }

    AIM_AT_NOTHING_TARGET01_AFTER:

    if (aim_status_ == PROG_AIM_AT_NOTHING_TARGET01_AFTER) {
        if (pAimPoint->is_enable_target02) {
            aim_status_ = PROG_AIM_AT_TARGET02;
            goto AIM_AT_TARGET02;
        } else {
            if (_pLeader == this) {
                MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                if (pB) {
                    coord dx = _x - pB->_x;
                    coord dy = _y - pB->_y;
                    coord dz = _z - pB->_z;
                    aimChip(_x + dx*2+1,
                            _y + dy*2+1,
                            _z + dz*2+1 );
                } else {
                    aimChip(_x + pAxsMver_->_velo_vx_mv*2+1,
                            _y + pAxsMver_->_velo_vy_mv*2+1,
                            _z + pAxsMver_->_velo_vz_mv*2+1 );
                }
            } else {
                if (_pLeader) {
                    aimChip(_pLeader->_x,
                            _pLeader->_y,
                            _pLeader->_z);
                }
                MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
                if (pF) {
                    if (pF != _pLeader && pF->aim_status_ == PROG_AIM_AT_TARGET01 ) {
                        pF->aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                    }
                }
            }
        }
    }

    AIM_AT_TARGET02:

    if (aim_status_ == PROG_AIM_AT_TARGET02) {
        if (pAimPoint->is_enable_target02) {
            static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
            if (_x >= pAimPoint->target02_x - renge) {
                if (_x <= pAimPoint->target02_x + renge) {
                    if (_y >= pAimPoint->target02_y - renge) {
                        if (_y <= pAimPoint->target02_y + renge) {
                            if (_z >= pAimPoint->target02_z - renge) {
                                if (_z <= pAimPoint->target02_z + renge) {
                                    aim_status_ = PROG_AIM_AT_NOTHING_TARGET02_AFTER;
                                    goto AIM_AT_NOTHING_TARGET02_AFTER;
                                }
                            }
                        }
                    }
                }
            }
            aimChip(pAimPoint->target02_x,
                    pAimPoint->target02_y,
                    pAimPoint->target02_z );
        }
    }

    AIM_AT_NOTHING_TARGET02_AFTER:

    if (aim_status_ == PROG_AIM_AT_NOTHING_TARGET02_AFTER) {
        aimChip(_x + pAxsMver_->_velo_vx_mv*20+1,
                _y + pAxsMver_->_velo_vy_mv*20+1,
                _z + pAxsMver_->_velo_vz_mv*20+1 );
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

    GgafDxAxesMover* pAxsMver = pAxsMver_;

    //自→的
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //自→仮自。
    const int vVMx = pAxsMver->_velo_vx_mv;
    const int vVMy = pAxsMver->_velo_vy_mv;
    const int vVMz = pAxsMver->_velo_vz_mv;
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
        pAxsMver->setVxyzMvAcce(accX*1.5 + SGN(accX)*5.0,
                                accY*1.5 + SGN(accY)*5.0,
                                accZ*1.5 + SGN(accZ)*5.0);
    } else {
        pAxsMver->setVxyzMvAcce(accX + SGN(accX)*3.0,
                                accY + SGN(accY)*3.0,
                                accZ + SGN(accZ)*3.0);
    }
    static const coord min_velo = MyBunshinWateringLaserChip001::MAX_VELO_RENGE/3;
    if (lVM < min_velo) {
        if (vVMx == 0 && vVMy == 0 && vVMz == 0) {
            GgafDxKuroko* pOrg_Kuroko = pOrg_->getKuroko();
            pAxsMver->setVxyzMvVelo(pOrg_Kuroko->_vX*min_velo,
                                    pOrg_Kuroko->_vY*min_velo,
                                    pOrg_Kuroko->_vZ*min_velo );
        } else {
            double t = (1.0 / sqrt(1.0*vVMx*vVMx + 1.0*vVMy*vVMy + 1.0*vVMz*vVMz)) * min_velo;
            pAxsMver->setVxyzMvVelo(vVMx*t, vVMy*t, vVMz*t);
        }
    }
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        if (pF) {
            MyBunshinWateringLaserChip001* pFF = (MyBunshinWateringLaserChip001*)(pF->getInfrontChip());
            if (pFF == nullptr) {
                //先端チップ（先端の次チップが無い）ならば、先端に情報コピー（先端は当たり判定ないので)
                if (pF == _pLeader) {
                    MyBunshin::AimPoint* pF_pAimPoint = pF->pAimPoint_;
                    if (pF_pAimPoint->pTarget == prm_pOtherActor && pF->aim_status_ == PROG_AIM_AT_LOCK_ON_TARGET01) {
                        //目標に見事命中した場合
                        pF_pAimPoint->target01_x = pF_pAimPoint->pTarget->_x;
                        pF_pAimPoint->target01_y = pF_pAimPoint->pTarget->_y;
                        pF_pAimPoint->target01_z = pF_pAimPoint->pTarget->_z;
                        pF_pAimPoint->is_enable_target01 = true;
                        pF->aim_status_ = PROG_AIM_AT_NOTHING_TARGET01_AFTER;
                    }
                }
            }
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }

getStatus()->set(STAT_Stamina, default_stamina_);
//sayonara();
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

    if (_pLeader == this) {
        pAimPoint_->target02_x = _x;
        pAimPoint_->target02_y = _y;
        pAimPoint_->target02_z = _z;
        pAimPoint_->is_enable_target02 = true;
    }
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    WateringLaserChip::onInactive();

//    pOrg_pLockonCtrler_pRingTarget_ = nullptr;
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

