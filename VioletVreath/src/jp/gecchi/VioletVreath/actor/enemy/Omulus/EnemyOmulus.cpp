#include "EnemyOmulus.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyOmulus::EnemyOmulus(const char* prm_name) :
        DefaultMassMorphMeshActor(prm_name, "Omulus_1", STATUS(EnemyOmulus)) {
    _class_name = "EnemyOmulus";
    pScaler_ = NEW GgafDxScaler(this);
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_ = 120;

    pDepo_Fired_ = nullptr;
    pConn_depo_ = connectToDepositoryManager("Talante");
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSe->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyOmulus::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOmulus::initialize() {
    setHitAble(true);
    getKuroko()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 200000);
    setScale(1000);
    pScaler_->setRange(1000, 1200);
    pScaler_->beat(30, 5, 0, 20, -1);
    pDepo_Fired_ = pConn_depo_->peek();
}

void EnemyOmulus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    getProgress()->reset(PROG_HATCH_CLOSE);
}

void EnemyOmulus::processBehavior() {
    //ローカルで計算を行う
    changeGeoLocal();

    //ボーンにあたるアクターのメモ
    //_x, _y, _z, _rx, _ry, _rz について２つの座標系セットを切り替えが必要な仕様です。
    //それぞれローカル座標、最終（絶対）座標と呼ぶことにします。
    //・最終（絶対）座標 ・・・ 普通のワールド座標系の事です。
    //・ローカル座標     ・・・ 親アクターの基点(0,0,0)からの相対的な座標系を意味します。
    //                          座標計算はこちらで行って下さい。
    //＜方針＞
    //  ①座標計算は主にローカル座標系の計算である。GgafDxKuroko でローカル座標系の操作を行うこととする。
    //    しかし、八分木登録や、当たり判定や、ターゲット座標など、他のオブジェクトからワールド座標を参照する等、
    //    基本状態は最終（絶対）座標系。
    //    processBehavior()開始時は 最終（絶対）座標系(changeGeoFinal())の状態となっている。
    //  ②processBehavior()内で必要に応じて changeGeoLocal() でメンバー _x, _y, _z, _rx, _ry, _rz をローカル座標系に
    //    切り替えることが可能。移動等の座標計算を行う。
    //  ③但し processBehavior() を抜ける際には必ず最終座標(changeGeoFinal())の状態に戻しておく事。
    //  ④最終（絶対）座標と、ローカル座標は互いに独立し、干渉はしないが、
    //    表示時のワールド変換行列作成時、行列積で合成され、最終的な表示位置が決定する。

    //＜changeGeoLocal(); 実行時＞
    //ローカル座標系に切替えます。
    //・_x, _y, _z     ・・・ は、ローカル座標を意味するようになります。
    //                        changeGeoLocal(); を実行すると自動的に_x, _y, _z に
    //                        ローカル座標値に切り替わります。
    //・_rx, _ry, _rz  ・・・ は、ローカル座標での軸回転値を意味するようになります。
    //                        changeGeoLocal(); を実行すると自動的に_rx, _ry, _rzに
    //                        ローカル座標軸回転値に切り替わります。

    //＜changeGeoFinal(); 実行時＞
    //最終（絶対）座標系に切り替えます。
    //・_x, _y, _z    ・・・ 毎フレーム GgafDxGeometricActor::processSettlementBehavior() で計算され自動更新されてます。
    //                       processBehavior() で changeGeoFinal() を行うと、１フレーム前の_x, _y, _zに切り替わる事になります。
    //                       _x, _y, _z は参照専用。値を代入しても意味が有りません
    //・_rx, _ry, _rz ・・・ 毎フレーム GgafDxGeometricActor::processSettlementBehavior() 自動代入されません！
    //                       changeGeoFinal(); を実行しても、_rx, _ry, _rz は以前の最終（絶対）座標系の値が
    //                       入りっぱなしで変化しません。
    //                       他のオブジェクトから、ボーンにあたるアクターを参照するとき、_rx, _ry, _rzは全く信用できません。

    //＜注意＞
    //・GgafDxKuroko(getKuroko())の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDxKuroko(getKuroko())の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    pKuroko->behave();
    //    changeGeoFinal();
    //TODO:混在感をもっとなくす。
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                pKuroko->setRollFaceAngVelo(-3000);
            }

            //次へ
            if (pProg->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pKuroko->setRollFaceAngVelo(0);
            }
            //processJudgement()でショット発射
            if (pProg->getFrame() >= frame_of_open_interval_+ frame_of_morph_interval_) {
                pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }

//    if (getActiveFrame() % 10U == 0                   && 1 == 2) {
//        //自機へ方向を向ける
//        //考え方：ローカル座標系で予めどの方向に向いておけば、最終的に自機に向くことになるかを求める
//        //
//        //自機への向くための変換前状態でのターゲット位置を(tvx, tvy, tvz) とおき、
//        //「土台まで」の行列の積（_pActor_base->_matWorldRotMv) を b_mat_xx とする。
//        //現在の最終座標から自機への向きのベクトルを、(mvx, mvy, mvz) とすると、
//        //
//        //                | b_mat_11 b_mat_12 b_mat_13 |
//        //| tvx tvy tvz | | b_mat_21 b_mat_22 b_mat_23 | = | mvx mvy mvz |
//        //                | b_mat_31 b_mat_32 b_mat_33 |
//        //
//        //となる。ローカル座標で(tvx, tvy, tvz) の方向を向けると、
//        //最終的に自機に向くことになる。
//        //逆行列を掛けて(tvx, tvy, tvz) を求めれば良い
//        //
//        //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
//        // | tvx tvy tvz | = | mvx mvy mvz | | b_mat_21 b_mat_22 b_mat_23 |
//        //                                   | b_mat_31 b_mat_32 b_mat_33 |
//        //
//
//        //mvx mvy mvz を求める
//        int mvx = P_MYSHIP->_x - _x;
//        int mvy = P_MYSHIP->_y - _y;
//        int mvz = P_MYSHIP->_z - _z;
//        //逆行列取得
//        D3DXMATRIX* pBaseInvMatRM = getBaseActor()->getInvMatWorldRotMv();
//        //ローカル座標でのターゲットとなる方向ベクトル計算
//        int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz * pBaseInvMatRM->_31;
//        int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz * pBaseInvMatRM->_32;
//        int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz * pBaseInvMatRM->_33;
//        //自動方向向きシークエンス開始
//        angle rz_target, ry_target;
//        UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target);
//        pKuroko->turnRzRyMvAngTo(rz_target, ry_target,
//                                   1000, 0,
//                                   TURN_CLOSE_TO, false);
//    }

    pScaler_->behave();
    getMorpher()->behave();

    pKuroko->behave();
    changeGeoFinal();
}

void EnemyOmulus::processChangeGeoFinal() {
    //絶対座標が更新されてから～
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_HATCH_OPEN: {
            //オープン時敵出現処理
            if (getMorphWeight(MORPHTARGET_HATCH_OPEN) > 0.5) { //モーションが半分以上まで到達したなら
                if (pProg->getFrame() % (frame)(RF_EnemyOmulus_ShotInterval(G_RANK)) == 0) { //出現間隔
                    if (pDepo_Fired_) {
                        GgafDxFigureActor* pActor = (GgafDxFigureActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
                            pActor->getKuroko()->setRzRyMvAng(_rz, _ry); //絶対座標系での向き
                            pActor->position(_x, _y, _z);
                            pActor->reset();
                        }
                    }
                }
            }
            break;
        }
        default :
            break;
    }
}

void EnemyOmulus::processJudgement() {
    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_base->_pFunc_calc_rot_mv_world_matrix))(_pActor_base, _matWorld);
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }


//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyOmulus::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyOmulus::onInactive() {
    sayonara();
}

EnemyOmulus::~EnemyOmulus() {
    pConn_depo_->close();
    GGAF_DELETE(pScaler_);
}
