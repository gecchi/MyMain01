#include "MyBunshinBase.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinBase::MAX_BUNSHIN_NUM = 9;
const frame MyBunshinBase::BUNSHIN_D = 15;
const angvelo MyBunshinBase::ANGVELO_TURN = PX_C(3); //分身の向きの角速度
const angvelo MyBunshinBase::ANGVELO_EXPANSE = PX_C(3); //分身広がり回転角速度
//MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
//  GgafDxGeometricActor(prm_name, nullptr, nullptr) {

MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
        DefaultMeshActor(prm_name, "myvic") {

    trace_offset_.set(0,0,0);
    no_ = prm_no; //１～

    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->addSubGroupAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_no);
    trace_mode_ = TRACE_GRADIUS;
    return_default_pos_frames_ = 0;


    pAxsMver_ = NEW GgafDxAxesMover(this);
    renge_ = PX_C(80);
    pAxsMver_->forceVxyzMvVeloRange(-renge_, renge_);
    pAxsMver_->forceVxyzMvAcceRange(-renge_ / 30, renge_ / 30);
    velo_bunshin_free_mv_ = PX_C(20);
}

void MyBunshinBase::config(
        coord prm_radius_position,
        angle prm_ang_position,
        angle prm_expanse,
        angvelo prm_angvelo_mv)
{
    bunshin_default_radius_position_ = prm_radius_position;
    bunshin_default_ang_position_  = prm_ang_position;
    bunshin_default_expanse_ = prm_expanse;
    bunshin_default_angvelo_mv_ = prm_angvelo_mv;
    bunshin_velo_mv_radius_pos_ = 3000 * (bunshin_default_radius_position_/60000);

    bunshin_radius_pos_ = bunshin_default_radius_position_;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    setAlpha(0.7);
    useProgress(PROG_BANPEI);

}

void MyBunshinBase::onReset() {
    pBunshin_->setRadiusPosition(bunshin_default_radius_position_);
    bunshin_radius_pos_ = bunshin_default_radius_position_;

    setRollFaceAng(bunshin_default_ang_position_);
    getKuroko()->setRollFaceAngVelo(bunshin_default_angvelo_mv_);
    getProgress()->reset(PROG_INIT);
    trace_mode_ = TRACE_GRADIUS;
}

void MyBunshinBase::onActive() {
}

void MyBunshinBase::processBehavior() {

    const MyShip* pMyShip = P_MYSHIP;
    const VirtualButton* pVbPlay = VB_PLAY;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            break;
        }
        case PROG_BUNSHIN_NOMAL_TRACE: { //通常トレース
            trace_mode_ = TRACE_GRADIUS;
            break;
        }

        case PROG_BUNSHIN_FREE_IGNITED: { //分身フリーモード、点火待ち！
            if (pProg->hasJustChanged()) {
            }
            if (pVbPlay->isBeingPressed(VB_OPTION | VB_TURBO) ) {
                if (pProg->getFrame() >= (MyBunshinBase::MAX_BUNSHIN_NUM - (no_-1) )*10) { //最初のオプションほどカウントが多く必要
                    //点火完了。次へ
                    pProg->change(PROG_BUNSHIN_FREE_READY);
                }
            } else {
                //分身フリーモード、リセット
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_READY: { //分身フリーモード発射準備OK
            if (pVbPlay->isBeingPressed(VB_OPTION)) {
                if(pVbPlay->isReleasedUp(VB_TURBO)) { //VB_OPTIONだけ離すと発射。
                    //発射！！
                    pProg->change(PROG_BUNSHIN_FREE_MOVE);
                } else {
                    //発射待ち・・・
                }
            } else {
                //分身フリーモード、リセット
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MOVE: { //分身フリーモード、操作移動！
            if (pProg->hasJustChanged()) {
                //移動開始
                pAxsMver_->setZeroVxyzMvVelo();
                pAxsMver_->setZeroVxyzMvAcce();
                EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
                if (pTurbo002) {
                    pTurbo002->positionAs(pBunshin_);
                }
            }
            if (pVbPlay->isBeingPressed(VB_OPTION)) {
                //オプションの広がり角より、MyBunshinBaseの移動速度と、MyBunshin旋回半径増加速度にベクトル分解。
                angvelo bunshin_angvelo_expance = pBunshin_->getExpanse();
                pKuroko->setMvVelo(ANG_COS(bunshin_angvelo_expance) * velo_bunshin_free_mv_); //MyBunshinBase
                pBunshin_->addRadiusPosition(ANG_SIN(bunshin_angvelo_expance) * velo_bunshin_free_mv_);
                //こここここ
            } else {
                //分身フリーモード、リセット
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_WAIT: { //分身フリーモード、待機中！
            if (pProg->hasJustChanged()) {
            }

            break;
        }
        default :
            break;
    }

    //オプションフリーモードへの判断
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBOダブルプッシュ
            //分身フリーモード、点火！
            pProg->change(PROG_BUNSHIN_FREE_IGNITED);
        }
    }


    if (return_default_pos_frames_ > 0) {
        //分身が元の位置に戻る継続中
        trace_mode_ = TRACE_TWINBEE;
        return_default_pos_frames_ --;
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        //完全にデフォルト状態に元に戻ために、最低限必要なフレーム数基準値
        trace_mode_ = TRACE_TWINBEE;
        return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * (MyBunshinBase::MAX_BUNSHIN_NUM+1);
        //エフェクト
        EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
        if (pTurbo002) {
            pTurbo002->positionAs(pBunshin_);
        }
        //土台がの向きが元に戻る（前方に向く）指示
        pKuroko->turnRzRyFaceAngTo(D0ANG, D0ANG,
                                   D_ANG(2), 0,
                                   TURN_CLOSE_TO,
                                   false );
        //分身の角度位置が元に戻る指示
        int angvelo_sgn = SGN(bunshin_default_angvelo_mv_);
        pKuroko->asstB()->rollFaceAngByDtTo(
                              bunshin_default_ang_position_,
                              angvelo_sgn > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                              return_default_pos_frames_/2,
                              0.3, 0.7,
                              bunshin_default_angvelo_mv_,
                              true
                           );
        //分身の半径位置が元に戻る指示
        bunshin_radius_pos_ = bunshin_default_radius_position_;
        pBunshin_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_);
        //分身の向きが元に戻る（前方に向く）指示
        pBunshin_->turnExpanse(
                       D_ANG(0),
                       return_default_pos_frames_*RCNV(1,MyBunshinBase::MAX_BUNSHIN_NUM,no_,0.5,1.0)
                   );
        //後はreturn_default_pos_frames_ が0になるまで
        //trace_mode_ = TRACE_TWINBEE;
        //が行われる
    } else if (pVbPlay->isBeingPressed(VB_OPTION)) {
        //分身操作
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //分身広がりと半径位置制御
            trace_mode_ = TRACE_FREEZE;
            const int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            }
            bunshin_radius_pos_ = pBunshin_->getRadiusPosition(); //標準半径位置を更新
        } else {  //if ( pVbPlay->isBeingPressed(VB_TURBO) )  の else
            //分身の向き操作
            trace_mode_ = TRACE_FREEZE;
            if (pVbPlay->isBeingPressed(VB_UP)) {
                addRzFaceAng(MyBunshinBase::ANGVELO_TURN);
            } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                addRzFaceAng(-MyBunshinBase::ANGVELO_TURN);
            }
            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                addRyFaceAng(MyBunshinBase::ANGVELO_TURN);
            } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                addRyFaceAng(-MyBunshinBase::ANGVELO_TURN);
            }
        }
    }






    if (trace_mode_ == TRACE_GRADIUS) {
        if (pMyShip->is_move_) {
            pPosTrace->next()->set(pMyShip);
        }
    } else if (trace_mode_ == TRACE_TWINBEE) {
        pPosTrace->next()->set(pMyShip);
    } else if (trace_mode_ == TRACE_FREEZE) {
        if (pMyShip->is_move_) {
            int l = pPosTrace->_num;
            coord dx = pMyShip->mv_offset_x_;
            coord dy = pMyShip->mv_offset_y_;
            coord dz = pMyShip->mv_offset_z_;
            Pos* p = pPosTrace->_paPos;
            for (int i = 0; i < l; i++) {
                p[i].add(dx, dy, dz);
            }
        }
    }











    pKuroko->behave();
    Pos* pPos = pPosTrace->getNext(); //環状なのでgetNext()が末尾座標情報。
    coord tx = pPos->x;
    coord ty = pPos->y;
    coord tz = pPos->z;
    position(tx,ty,tz);
}



MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace);
}

