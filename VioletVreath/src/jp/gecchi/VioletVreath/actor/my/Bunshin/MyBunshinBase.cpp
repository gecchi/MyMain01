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
    no_ = prm_no;

    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->addSubGroupAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_no);
    trace_mode_ = TRACE_GRADIUS;
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
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    setAlpha(0.7);
    useProgress(PROG_BANPEI);

}

void MyBunshinBase::onReset() {
    setBunshinRadiusPosition(bunshin_default_radius_position_);
    setBunshinExpanse(bunshin_default_expanse_);

    setRollFaceAng(bunshin_default_ang_position_);
    getKuroko()->setRollFaceAngVelo(bunshin_default_angvelo_mv_);
    getProgress()->reset(PROG_INIT);
}

void MyBunshinBase::onActive() {
}

void MyBunshinBase::processBehavior() {

    const MyShip* pMyShip = P_MYSHIP;
    const VirtualButton* pVbPlay = VB_PLAY;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    trace_mode_ = TRACE_GRADIUS;

    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            break;
        }
        case PROG_BUNSHIN_NOMAL_TRACE: { //通常トレース
            if (GgafDxInput::isPushedDownKey(DIK_SPACE)) {
                EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
                if (pTurbo002) {
                    pTurbo002->positionAs(pBunshin_);
                }
                pProg->change(PROG_BUNSHIN_FREE_MOVE);
            }

            break;
        }
        case PROG_BUNSHIN_FREE_MOVE: { //分身フリーモード、操作移動中！
            if (pProg->hasJustChanged()) {
            }
            if (GgafDxInput::isReleasedUpKey(DIK_SPACE)) {
                pProg->change(PROG_BUNSHIN_FREE_WAIT);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_WAIT: { //分身フリーモード、待機中！
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        case PROG_BUNSHIN_RETURN_DEFAULT_POS_BEGIN: { //分身、元の位置に戻り中
            EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->positionAs(pBunshin_);
            }
            //元に戻るのに必要なフレーム数基準値
            return_default_pos_frames_ = 60;
            //土台が前に向く。
            pKuroko->turnRzRyFaceAngTo(D0ANG, D0ANG,
                                       D_ANG(2), 0,
                                       TURN_CLOSE_TO,
                                       false );
            //分身の初期の角度位置までの角距離
            int angvelo_sgn = SGN(bunshin_default_angvelo_mv_);
            angle ang_diff = UTIL::getAngDiff(_rx, bunshin_default_ang_position_, angvelo_sgn);
            int way;
            if (angvelo_sgn > 0) {
                //正の角速度の回転＝反時計回り
                if (ABS(ang_diff) > D_ANG(350)) {
                    //逆に回る
                    way = TURN_CLOCKWISE;
                } else {
                    way = TURN_COUNTERCLOCKWISE;
                }
            } else {
                //負の角速度の回転＝時計回り
                if (ABS(ang_diff) > D_ANG(350)) {
                    //逆に回る
                    way = TURN_COUNTERCLOCKWISE;
                } else {
                    way = TURN_CLOCKWISE;
                }
            }
            //滑らかに元の位置に戻ろう。
            pKuroko->asstB()->rollFaceAngByDtTo(bunshin_default_ang_position_, way, return_default_pos_frames_,
                                                0.3, 0.7, bunshin_default_angvelo_mv_, true );
            pProg->change(PROG_BUNSHIN_RETURNING_DEFAULT_POS);
            break;
        }
        case PROG_BUNSHIN_RETURNING_DEFAULT_POS: { //分身、元の位置に戻り中

            if (pProg->hasArrivedAt(return_default_pos_frames_)) {
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        default :
            break;
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        //分身が元の位置に戻る
        pProg->change(PROG_BUNSHIN_RETURN_DEFAULT_POS_BEGIN);
    } else if (pVbPlay->isBeingPressed(VB_OPTION)) {
        //分身操作
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //分身広がりと半径位置制御
            trace_mode_ = TRACE_FREEZE;
            const int pos_camera = P_VAM->pos_camera_;
            if (pos_camera == VAM_POS_RIGHT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addBunshinExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addBunshinExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addBunshinRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addBunshinRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            } else if (pos_camera == VAM_POS_LEFT) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addBunshinExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addBunshinExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addBunshinRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addBunshinRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            } else if (pos_camera == VAM_POS_TOP) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addBunshinRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addBunshinRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addBunshinExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addBunshinExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
            } else if (pos_camera == VAM_POS_BOTTOM) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addBunshinRadiusPosition(-bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addBunshinRadiusPosition(+bunshin_velo_mv_radius_pos_);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addBunshinExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addBunshinExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                }
            } else if (pos_camera > VAM_POS_TO_BEHIND) {
                if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                    addBunshinExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                    addBunshinExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
                if (pVbPlay->isBeingPressed(VB_UP)) {
                    addBunshinRadiusPosition(+bunshin_velo_mv_radius_pos_);
                } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                    addBunshinRadiusPosition(-bunshin_velo_mv_radius_pos_);
                }
            }
        } else {  //if ( pVbPlay->isBeingPressed(VB_TURBO) )  の else
            //分身の向き操作
            trace_mode_ = TRACE_FREEZE;
            if (pVbPlay->isBeingPressed(VB_UP)) {
                addRzFaceAng(MyBunshinBase::ANGVELO_TURN);
            }
            if (pVbPlay->isBeingPressed(VB_DOWN)) {
                addRzFaceAng(-MyBunshinBase::ANGVELO_TURN);
            }
            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                addRyFaceAng(MyBunshinBase::ANGVELO_TURN);
            }
            if (pVbPlay->isBeingPressed(VB_LEFT)) {
                addRyFaceAng(-MyBunshinBase::ANGVELO_TURN);
            }
        }
    }

    if (trace_mode_ == TRACE_GRADIUS) {
        if (pMyShip->is_move_) {
            pPosTrace->next()->set(pMyShip);
        }
    } else if (trace_mode_ == TRACE_TWINBEE) {
        if (pMyShip->is_move_) {
            pPosTrace->next()->set(pMyShip);
        }
    } else if (trace_mode_ == TRACE_FREEZE) {
        if (pMyShip->is_move_) {
            int l = pPosTrace->_num;
            coord dx = pMyShip->mv_offset_x_;
            coord dy = pMyShip->mv_offset_y_;
            coord dz = pMyShip->mv_offset_z_;
            for (int i = 0; i < l; i++) {
                pPosTrace->_paPos[i].add(dx, dy, dz);
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



void MyBunshinBase::setBunshinRadiusPosition(coord prm_radius_position) {
    pBunshin_->_y_local = prm_radius_position;
}
void MyBunshinBase::addBunshinRadiusPosition(coord prm_radius_position) {
    pBunshin_->_y_local += prm_radius_position;
}
coord MyBunshinBase::getBunshinRadiusPosition() {
    return pBunshin_->_y_local;
}

void MyBunshinBase::setBunshinExpanse(angvelo prm_ang_expanse) {
    pBunshin_->_rz_local = UTIL::simplifyAng(prm_ang_expanse);
}
void MyBunshinBase::addBunshinExpanse(angvelo prm_ang_expanse) {
    pBunshin_->_rz_local += UTIL::simplifyAng(prm_ang_expanse);
}
angvelo MyBunshinBase::getBunshinExpanse() {
    return  pBunshin_->_rz_local;
}
MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace);
}

