#include "EnemyOmulus.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

enum {
    PHASE_INIT       ,
    PHASE_HATCH_CLOSE,
    PHASE_HATCH_OPEN ,
    PHASE_BANPEI,
};

EnemyOmulus::EnemyOmulus(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Omulus", StatusReset(EnemyOmulus)) {
    _class_name = "EnemyOmulus";
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_ = 120;

    pDepo_Fired_ = nullptr;
    pConn_depo_ = connectToDepositoryManager("Talante");
}

void EnemyOmulus::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOmulus::initialize() {
    setHitAble(true);
    getLocusVehicle()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 200000);
    setScale(1000);
    getScaler()->setRange(1000, 1200);
    getScaler()->beat(30, 5, 0, 20, -1);
    pDepo_Fired_ = pConn_depo_->peek();
}

void EnemyOmulus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    getPhase()->reset(PHASE_HATCH_CLOSE);
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
    //  ①座標計算は主にローカル座標系の計算である。GgafDx::LocusVehicle でローカル座標系の操作を行うこととする。
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
    //・_x, _y, _z    ・・・ 毎フレーム GgafDx::GeometricActor::processSettlementBehavior() で計算され自動更新されてます。
    //                       processBehavior() で changeGeoFinal() を行うと、１フレーム前の_x, _y, _zに切り替わる事になります。
    //                       _x, _y, _z は参照専用。値を代入しても意味が有りません
    //・_rx, _ry, _rz ・・・ 毎フレーム GgafDx::GeometricActor::processSettlementBehavior() 自動代入されません！
    //                       changeGeoFinal(); を実行しても、_rx, _ry, _rz は以前の最終（絶対）座標系の値が
    //                       入りっぱなしで変化しません。
    //                       他のオブジェクトから、ボーンにあたるアクターを参照するとき、_rx, _ry, _rzは全く信用できません。

    //＜注意＞
    //・GgafDx::LocusVehicle(getLocusVehicle())の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDx::LocusVehicle(getLocusVehicle())の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    pLocusVehicle->behave();
    //    changeGeoFinal();
    //TODO:混在感をもっとなくす。
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_HATCH_CLOSE);
            break;
        }
        case PHASE_HATCH_CLOSE: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                pLocusVehicle->setRollFaceAngVelo(-3000);
            }

            //次へ
            if (pPhase->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_OPEN);
            }
            break;
        }
        case PHASE_HATCH_OPEN: {
            if (pPhase->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pLocusVehicle->setRollFaceAngVelo(0);
            }
            //processJudgement()でショット発射
            if (pPhase->getFrame() >= frame_of_open_interval_+ frame_of_morph_interval_) {
                pPhase->change(PHASE_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }

    getScaler()->behave();
    getMorpher()->behave();

    pLocusVehicle->behave();
    changeGeoFinal();
}

void EnemyOmulus::processChangeGeoFinal() {
    //絶対座標が更新されてから～
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_HATCH_OPEN: {
            //オープン時敵出現処理
            if (getMorphWeight(MORPHTARGET_HATCH_OPEN) > 0.5) { //モーションが半分以上まで到達したなら
                if (pPhase->getFrame() % (frame)(RF_EnemyOmulus_ShotInterval(G_RANK)) == 0) { //出現間隔
                    if (pDepo_Fired_) {
                        GgafDx::FigureActor* pActor = (GgafDx::FigureActor*)pDepo_Fired_->dispatch();
                        if (pActor) {
                            pActor->getLocusVehicle()->setRzRyMvAng(_rz, _ry); //絶対座標系での向き
                            pActor->setPosition(_x, _y, _z);
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

void EnemyOmulus::onInactive() {
    sayonara();
}

EnemyOmulus::~EnemyOmulus() {
    pConn_depo_->close();
}
