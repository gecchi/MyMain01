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
const angvelo MyBunshinBase::ANGVELO_TURN = PX_C(3); //���g�̌����̊p���x
const angvelo MyBunshinBase::ANGVELO_EXPANSE = PX_C(3); //���g�L�����]�p���x
//MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
//  GgafDxGeometricActor(prm_name, nullptr, nullptr) {

MyBunshinBase::MyBunshinBase(const char* prm_name, int prm_no) :
        DefaultMeshActor(prm_name, "myvic") {

    trace_offset_.set(0,0,0);
    no_ = prm_no; //�P�`

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
        case PROG_BUNSHIN_NOMAL_TRACE: { //�ʏ�g���[�X
            if (GgafDxInput::isPushedDownKey(DIK_SPACE)) {
                EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
                if (pTurbo002) {
                    pTurbo002->positionAs(pBunshin_);
                }
                pProg->change(PROG_BUNSHIN_FREE_MOVE);
            }

            break;
        }

        case PROG_BUNSHIN_FREE_IGNITED: { //���g�t���[���[�h�A�_�΁I
            if (pProg->hasJustChanged()) {
            }

            if (pVbPlay->isReleasedUp(VB_TURBO)) { //VB_OPTION�����ƃ��Z�b�g
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }


            if (pProg->getFrame() >= (MyBunshinBase::MAX_BUNSHIN_NUM - (no_-1) )*10) { //�ŏ��̃I�v�V�����قǃJ�E���g�������K�v
                //���˓_��OK���̏���
                //�_��OK�̎��� VB_OPTION + VB_TURBO�����Ŕ���
                if (pVbPlay->isReleasedUp(VB_TURBO)) {
                    //pBunshin_�Ȃɂ��A�N�V����


                    //�_��OK�̎��� VB_OPTION + VB_TURBO�����Ŕ���
//                    ignited_bushin_cnt_mode_ = false; //VB_TURBON�����ƃ��Z�b�g
//                    ignite_bushin_cnt_ = 0;
//                    if (pVbPlay->isBeingPressed(VB_OPTION) && was_ignited_bushin_) { //�_��OK������
//                        was_ignited_bushin_ = false;
//
//                        is_free_from_myship_mode_ = true;
//                        is_handle_move_mode_ = true;
//                        pAxsMver_->setZeroVxyzMvVelo();
//                        pAxsMver_->setZeroVxyzMvAcce();
//                        if (pOption_->isActive()) {
//                            EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
//                            if (pTurbo002) {
//                                pTurbo002->positionAs(pOption_);
//                            }
//                        }
//                    }


                }
            }


            //�_��OK�̎��� VB_OPTION + VB_TURBO�����Ŕ���
            if (pVbPlay->isReleasedUp(VB_TURBO)) {

            }
            break;
        }
        case PROG_BUNSHIN_FREE_MOVE: { //���g�t���[���[�h�A����ړ����I
            if (pProg->hasJustChanged()) {
            }
            if (GgafDxInput::isReleasedUpKey(DIK_SPACE)) {
                pProg->change(PROG_BUNSHIN_FREE_WAIT);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_WAIT: { //���g�t���[���[�h�A�ҋ@���I
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        case PROG_BUNSHIN_RETURN_DEFAULT_POS_BEGIN: { //���g�A���̈ʒu�锭��
            EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->positionAs(pBunshin_);
            }
            //���S�Ƀf�t�H���g��ԂɌ��ɖ߂��߂ɁA�Œ���K�v�ȃt���[������l
            return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * MyBunshinBase::MAX_BUNSHIN_NUM;
            //�y�䂪�̌��������ɖ߂�i�O���Ɍ����j�w��
            pKuroko->turnRzRyFaceAngTo(D0ANG, D0ANG,
                                       D_ANG(2), 0,
                                       TURN_CLOSE_TO,
                                       false );
            //���g�̊p�x�ʒu�����ɖ߂�w��
            int angvelo_sgn = SGN(bunshin_default_angvelo_mv_);
            pKuroko->asstB()->rollFaceAngByDtTo(
                                  bunshin_default_ang_position_,
                                  angvelo_sgn > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                                  return_default_pos_frames_,
                                  0.3, 0.7,
                                  bunshin_default_angvelo_mv_,
                                  true
                               );
            //���g�̔��a�ʒu�����ɖ߂�w��
            bunshin_radius_pos_ = bunshin_default_radius_position_;
            pBunshin_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_);
            //���g�̌��������ɖ߂�i�O���Ɍ����j�w��
            pBunshin_->turnExpanse(D_ANG(0), return_default_pos_frames_);

            pProg->change(PROG_BUNSHIN_RETURNING_DEFAULT_POS);
            break;
        }
        case PROG_BUNSHIN_RETURNING_DEFAULT_POS: { //���g�A���̈ʒu�ɖ߂蒆
            trace_mode_ = TRACE_TWINBEE; //�g���[�X�������ɖ߂�
            if (pProg->hasArrivedAt(return_default_pos_frames_+2)) {
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        default :
            break;
    }





    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        //���g�����̈ʒu�ɖ߂�
        pProg->change(PROG_BUNSHIN_RETURN_DEFAULT_POS_BEGIN);
    } else if (pVbPlay->isBeingPressed(VB_OPTION)) {
        //���g����
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //���g�L����Ɣ��a�ʒu����
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

            bunshin_radius_pos_ = pBunshin_->getRadiusPosition(); //�W�����a�ʒu

        } else {  //if ( pVbPlay->isBeingPressed(VB_TURBO) )  �� else
            //���g�̌�������
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
    //�I�v�V�����t���[���[�h�ւ̔��f
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBO�_�u���v�b�V��
            pProg->change(PROG_BUNSHIN_FREE_IGNITED);
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
    Pos* pPos = pPosTrace->getNext(); //��Ȃ̂�getNext()���������W���B
    coord tx = pPos->x;
    coord ty = pPos->y;
    coord tz = pPos->z;
    position(tx,ty,tz);
}



MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace);
}

