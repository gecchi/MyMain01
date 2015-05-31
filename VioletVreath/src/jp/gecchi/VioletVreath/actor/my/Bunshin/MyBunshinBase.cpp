#include "MyBunshinBase.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoFaceAngAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAngAssistant.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinBase::MAX_BUNSHIN_NUM = 9;
const frame MyBunshinBase::BUNSHIN_D = 16;
const angvelo MyBunshinBase::ANGVELO_TURN = PX_C(2);        //���g�̌����̊p���x
const angvelo MyBunshinBase::ANGVELO_EXPANSE = PX_C(2);     //���g�L�����]�p���x
const int MyBunshinBase::RENGE = PX_C(70);                  //���g���߂��Ă��鎞��MAX����
const velo MyBunshinBase::VELO_BUNSHIN_FREE_MV = PX_C(20);  //���g�t���[�ړ����̕��g�̈ړ����x

int MyBunshinBase::now_bunshin_num_ = 0;

MyBunshinBase::MyBunshinBase(const char* prm_name, unsigned int prm_no) :
        DefaultGeometricActor(prm_name) {

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActor��FK�x�[�X�ɂȂ邽�߂ɕK�v

    trace_offset_.set(0,0,0);
    no_ = prm_no; //�P�`
    delay_r_ = RCNV(1,MyBunshinBase::MAX_BUNSHIN_NUM,no_,0.5,1.0);
    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->addSubGroupAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace_ = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_no);
    trace_mode_ = TRACE_GRADIUS;
    return_default_pos_frames_ = 0;

    pAxsMver_ = NEW GgafDxAxesMover(this);
    pAxsMver_->forceVxyzMvVeloRange(-MyBunshinBase::RENGE, MyBunshinBase::RENGE);
    pAxsMver_->forceVxyzMvAcceRange(-MyBunshinBase::RENGE / 30, MyBunshinBase::RENGE / 30);

    is_free_mode_ = false;
    is_isolate_mode_ = true;
    moving_frames_since_default_pos_ = 0;

    bunshin_default_radius_position_ = 0;
    bunshin_default_ang_position_  = 0;
    bunshin_default_expanse_ = 0;
    bunshin_default_angvelo_mv_ = 0;
    bunshin_velo_mv_radius_pos_ = 0;

}

void MyBunshinBase::config(
        coord prm_radius_position,
        angle prm_ang_position,
        angle prm_expanse,
        angvelo prm_angvelo_mv)
{
    bunshin_default_radius_position_ = prm_radius_position;
    bunshin_default_ang_position_  = UTIL::simplifyAng(prm_ang_position);
    bunshin_default_expanse_ =  UTIL::simplifyAng(prm_expanse);;
    bunshin_default_angvelo_mv_ = prm_angvelo_mv;
    bunshin_velo_mv_radius_pos_ = 3000 * (bunshin_default_radius_position_/60000);
    bunshin_radius_pos_ = bunshin_default_radius_position_;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    getKuroko()->linkFaceAngByMvAng(true);
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
    is_free_mode_ = true;
    position(P_MYSHIP->_x,P_MYSHIP->_y,P_MYSHIP->_z);

    int len = pPosTrace_->_num;
    Pos* p = pPosTrace_->_paPos;
    for (int i = 0; i < len; i++) {
        p[i].set(P_MYSHIP);
    }
    pBunshin_->setRadiusPosition(0);
    resetBunshin(0);
}

void MyBunshinBase::processBehavior() {
    GgafDxKuroko* pKuroko = getKuroko();
    if (is_isolate_mode_) {
        pKuroko->behave();
        pAxsMver_->behave();
        return;
    }
    const MyShip* pMyShip = P_MYSHIP;
    const VirtualButton* pVbPlay = VB_PLAY;
    GgafProgress* const pProg = getProgress();

    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            break;
        }
        case PROG_BUNSHIN_NOMAL_TRACE: { //�ʏ�g���[�X
            if (pProg->hasJustChanged()) {
                is_free_mode_ = false;
            }
            //�����ʒu����Q�O�t���[���ȓ��̓����́ATRACE_TWINBEE�ɂ���ď����ʒu���ێ�������
            if (pMyShip->is_move_) {
                moving_frames_since_default_pos_++;
            } else {
                if (moving_frames_since_default_pos_ <= 20) {
                    moving_frames_since_default_pos_ = 0;
                }
            }
            trace_mode_ = moving_frames_since_default_pos_ > 20 ? TRACE_GRADIUS : TRACE_TWINBEE;
            break;
        }
        case PROG_BUNSHIN_FREE_MODE_IGNITED: { //���g�t���[���[�h�A�_�Α҂��I
            if (pProg->hasJustChanged()) {
                pBunshin_->effectFreeModeIgnited(); //�_�΃G�t�F�N�g
            }
            if (pVbPlay->isBeingPressed(VB_OPTION | VB_TURBO) == (VB_OPTION | VB_TURBO)) {
                if (pProg->getFrame() >= (((MyBunshinBase::now_bunshin_num_ - (no_-1) )*5) + 10) ) { //������̃I�v�V��������
                    pProg->change(PROG_BUNSHIN_FREE_MODE_READY);
                }
            } else {
                //���g�t���[���[�h�A���Z�b�g
                if (is_free_mode_) {
                    pProg->change(PROG_BUNSHIN_FREE_MODE_STOP);
                } else {
                    pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
                }
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MODE_READY: { //���g�t���[���[�h���ˏ���OK
            if (pProg->hasJustChanged()) {
                pBunshin_->effectFreeModeReady(); //���ˏ���OK�G�t�F�N�g
            }
            if ( pProg->getFrame() >= ((no_-1)*5) + 10 ) { //�Ō�̕��g�����ˏ���OK�ɂȂ�������+10
                //��������
                pProg->change(PROG_BUNSHIN_FREE_MODE_MOVE);
            } else {
                if (pVbPlay->isBeingPressed(VB_OPTION)) {
                    if(pVbPlay->isReleasedUp(VB_TURBO)) { //VB_TURBO���������Ƒ����ˁB
                        //�n�[�t���ˁI�I
                        pProg->change(PROG_BUNSHIN_FREE_MODE_MOVE);
                    } else {
                        //���ˑ҂��E�E�E
                    }
                } else {
                    //VB_OPTION �𗣂��ƃ��Z�b�g�B
                    //���Z�b�g
                    if (is_free_mode_) {
                        pProg->change(PROG_BUNSHIN_FREE_MODE_STOP);
                    } else {
                        pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
                    }
                }
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MODE_MOVE: { //���g�t���[���[�h�A����ړ��I
            if (pProg->hasJustChanged()) {
                //���g�t���[���[�h�ړ��J�n
                pBunshin_->effectFreeModeLaunch(); //���˃G�t�F�N�g
                is_free_mode_ = true;
                pAxsMver_->setZeroVxyzMvVelo();
                pAxsMver_->setZeroVxyzMvAcce();
            }
            if (pVbPlay->isBeingPressed(VB_OPTION)) {
                //���g�t���[���[�h�ňړ���
                //�I�v�V�����̍L����p���AMyBunshinBase�̈ړ����x�ƁAMyBunshin���񔼌a�������x�Ƀx�N�g�������B
                angvelo bunshin_angvelo_expance = pBunshin_->getExpanse();
                pKuroko->setMvVelo(ANG_COS(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV); //MyBunshinBase
                pBunshin_->addRadiusPosition(ANG_SIN(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV);
                // VB_OPTION �𗣂��܂ő҂E�E�E
            } else {
                //���g�t���[���[�h�A���f�ҋ@
                pKuroko->setMvVelo(0);
                pProg->change(PROG_BUNSHIN_FREE_MODE_STOP);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MODE_STOP: { //���g�t���[���[�h�A��~���I
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS: { //���g���̏ꏊ�ɖ߂�I
            if (pProg->hasJustChanged()) {
            }
            const Pos* pTargetPos = pPosTrace_->getNext(); //�ʏ펞�̖{���̕��g�̍��W�ʒu��ڕW�ɂ���
            const coord tx = pTargetPos->x;
            const coord ty = pTargetPos->y;
            const coord tz = pTargetPos->z;
            if (pProg->getFrame() == 3*(no_-1)) { //�΂����

                // (0,1,0) �~ RxRzRy �� ( (cosRx*-sinRz*cosRy + sinRx*sinRy),  cosRx*cosRz, (cosRx*-sinRz*-sinRy + sinRx*cosRy) )
                const float sinRx = ANG_SIN(_rx);
                const float cosRx = ANG_COS(_rx);
                const float sinRy = ANG_SIN(_ry);
                const float cosRy = ANG_COS(_ry);
                const float sinRz = ANG_SIN(_rz);
                const float cosRz = ANG_COS(_rz);
                pAxsMver_->setVxyzMvVelo((cosRx*-sinRz*cosRy + sinRx*sinRy)  * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                         (cosRx*cosRz)                       * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                         (cosRx*-sinRz*-sinRy + sinRx*cosRy) * MyBunshinBase::VELO_BUNSHIN_FREE_MV );
            } else if (pProg->getFrame() > 3*(no_-1)) { //�΂����
                pAxsMver_->setVxyzMvAcce( (tx - (_x + pAxsMver_->_velo_vx_mv*6)),
                                          (ty - (_y + pAxsMver_->_velo_vy_mv*6)),
                                          (tz - (_z + pAxsMver_->_velo_vz_mv*6)) );
            }
            if (ABS(_x - tx) < 10000 &&
                ABS(_y - ty) < 10000 &&
                ABS(_z - tz) < 10000 &&
                ABS(pAxsMver_->_velo_vx_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxsMver_->_velo_vy_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxsMver_->_velo_vz_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV)
            {
                //���ǂ����I
                pAxsMver_->setZeroVxyzMvVelo();
                pAxsMver_->setZeroVxyzMvAcce();
                position(tx, ty, tz);
                moving_frames_since_default_pos_ = 0;
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }

        default :
            break;
    }

    //�I�v�V�����t���[���[�h�ւ̔��f
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBO�_�u���v�b�V��
            //���g�t���[���[�h�A�_�΁I
            pProg->change(PROG_BUNSHIN_FREE_MODE_IGNITED);
        }
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        if (pVbPlay->isBeingPressed(VB_TURBO)) {
            //VB_OPTION �_�u���v�b�V�� + VB_TURBO�������ςȂ��̏ꍇ
            //�I�[�����Z�b�g
            resetBunshin(0);
        } else {
            //VB_OPTION �_�u���v�b�V���AVB_TURBO�������Ă��Ȃ��ƁA
            //�`���b�g���Z�b�g
            //�t���[���[�h�ێ��A���a�ʒu���ێ��A
            resetBunshin(1);
        }
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
            bunshin_radius_pos_ = pBunshin_->getRadiusPosition(); //�W�����a�ʒu���X�V
        } else {  //if ( pVbPlay->isBeingPressed(VB_TURBO) )  �� else
            //���g�̌���(this�y��̌���)����
            trace_mode_ = TRACE_FREEZE;
            if (pVbPlay->isBeingPressed(VB_UP)) {
                pKuroko->addRzMvAng(MyBunshinBase::ANGVELO_TURN);
            } else if (pVbPlay->isBeingPressed(VB_DOWN)) {
                pKuroko->addRzMvAng(-MyBunshinBase::ANGVELO_TURN);
            }
            if (pVbPlay->isBeingPressed(VB_RIGHT)) {
                pKuroko->addRyMvAng(MyBunshinBase::ANGVELO_TURN);
            } else if (pVbPlay->isBeingPressed(VB_LEFT)) {
                pKuroko->addRyMvAng(-MyBunshinBase::ANGVELO_TURN);
            }
        }
    }

    if (return_default_pos_frames_ > 0) {
        //���g�����̈ʒu�ɖ߂�p����
        trace_mode_ = TRACE_TWINBEE; //�߂��Ă�Œ��̓c�C���r�[�g���[�X
        return_default_pos_frames_ --;
    }

    if (trace_mode_ == TRACE_GRADIUS) {
        if (pMyShip->is_move_) {
            pPosTrace_->next()->set(pMyShip);
        }
    } else if (trace_mode_ == TRACE_TWINBEE) {
        pPosTrace_->next()->set(pMyShip);
    } else if (trace_mode_ == TRACE_FREEZE) {
        if (pMyShip->is_move_) {
            int l = pPosTrace_->_num;
            coord dx = pMyShip->mv_offset_x_;
            coord dy = pMyShip->mv_offset_y_;
            coord dz = pMyShip->mv_offset_z_;
            Pos* p = pPosTrace_->_paPos;
            for (int i = 0; i < l; i++) {
                p[i].add(dx, dy, dz);
            }
        }
    }

    if (is_free_mode_) {
        //�t���[���[�h���̓t���[�Y�̓���
        if (pMyShip->is_move_) {
            position(_x + pMyShip->mv_offset_x_,
                     _y + pMyShip->mv_offset_y_,
                     _z + pMyShip->mv_offset_z_ );
        }
    } else {
        //�ʏ펞�� trace_mode_ �̓���
        positionAs(pPosTrace_->getNext()); //��Ȃ̂�getNext()���������W���B
        if (trace_mode_ == TRACE_GRADIUS) {
            //TRACE_GRADIUS �� �y�䂪�ړ�����Ȃ�΁A���a�ʒu��y��̒��S�Ɋ񂹂�
            Pos* p = pPosTrace_->get2Next();
            if (!(p->x == _x && p->y == _y && p->z == _z)) {
                pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
        }
    }
    pKuroko->behave();
    pAxsMver_->behave();
}

void MyBunshinBase::resetBunshin(int prm_mode) {
    //prm_mode = 0 �I�[�����Z�b�g
    //prm_mode = 1 �n�[�t���Z�b�g
    is_isolate_mode_ = false;
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    //���S�Ƀf�t�H���g��ԂɌ��ɖ߂��߂ɁA�Œ���K�v�ȃt���[������l
    return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * (MyBunshinBase::MAX_BUNSHIN_NUM+1); //�����΂�����鉉�o
    //�G�t�F�N�g

    //�y�䂪�̌��������ɖ߂�i�O���Ɍ����j�w��
    pKuroko->asstMvAng()->turnRzRyByDtTo(D0ANG, D0ANG,
                                         TURN_CLOSE_TO,
                                         false,
                                         return_default_pos_frames_ * delay_r_,
                                         0.3, 0.5,
                                         0,
                                         true);
    //���g�̌��������ɖ߂�i�O���Ɍ����j�w��
    pBunshin_->turnExpanse(
                   D_ANG(0),
                   return_default_pos_frames_ * delay_r_
               );
    //���g�̊p�x�ʒu�����ɖ߂�w��
    pKuroko->asstFaceAng()->rollFaceAngByDtTo(
                          bunshin_default_ang_position_,
                          SGN(bunshin_default_angvelo_mv_) > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                          return_default_pos_frames_/2, //�΂������ƃY����̂�  * delay_r_ ���܂���
                          0.3, 0.5,
                          bunshin_default_angvelo_mv_,
                          true
                       );
    if (prm_mode == 0) {
        //VB_OPTION �_�u���v�b�V�� + VB_TURBO�������ςȂ��̏ꍇ
        //�I�[�����Z�b�g
        EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
        if (pTurbo002) {
            pTurbo002->positionAs(pBunshin_);
        }
        //���g�̔��a�ʒu�����ɖ߂�w��
        bunshin_radius_pos_ = bunshin_default_radius_position_;
        pBunshin_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_ * delay_r_ );
        //���return_default_pos_frames_ ��0�ɂȂ�܂�
        //trace_mode_ = TRACE_TWINBEE;
        //���s����
        pProg->change(PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS); //���g���ɖ߂�
    } else {
        //VB_OPTION �_�u���v�b�V���AVB_TURBO�������Ă��Ȃ��ƁA
        //�`���b�g���Z�b�g
        //�t���[���[�h�ێ��A���a�ʒu���ێ��A
        return_default_pos_frames_ = 0;
    }
}

MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace_);
    GGAF_DELETE(pAxsMver_);
}

void MyBunshinBase::setBunshinNum(int prm_num) {
    MyBunshinBase::now_bunshin_num_ = prm_num;
    MyBunshinBase** papBase = P_MYSHIP_SCENE->papBunshinBase_;
    for (int i = 0; i < MyBunshinBase::MAX_BUNSHIN_NUM; i++) {
        MyBunshinBase* p = papBase[i];
        if (i+1 <= prm_num) {
            if (!(p->isActive())) {
                p->activate();
            }
        } else {
            if (p->isActive()) {
                p->inactivate();
            }
        }
    }

    switch (MyBunshinBase::now_bunshin_num_) {
        case 1: {
            papBase[0]->config(60000, D0ANG, 0, 1000);
            break;
        }
        case 2: {
            papBase[0]->config(60000, D0ANG  , 0, 1000);
            papBase[1]->config(60000, D180ANG, 0, 1000);
            break;
        }
        case 3: {
            papBase[0]->config(60000, D_ANG(120*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(120*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(120*2), 0, 1000);
            break;
        }
        case 4: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            break;
        }
        case 5: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            papBase[4]->config(120000, D0ANG, 0, -1500);
            break;
        }
        case 6: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            papBase[4]->config(120000, D0ANG  , 0, -1500);
            papBase[5]->config(120000, D180ANG, 0, -1500);
            break;
        }
        case 7: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            papBase[4]->config(120000, D_ANG(120* 0), 0, -1500);
            papBase[5]->config(120000, D_ANG(120*-1), 0, -1500);
            papBase[6]->config(120000, D_ANG(120*-2), 0, -1500);
            break;
        }
        case 8: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            papBase[4]->config(120000, D_ANG(90* 0), 0, -1500);
            papBase[5]->config(120000, D_ANG(90*-1), 0, -1500);
            papBase[6]->config(120000, D_ANG(90*-2), 0, -1500);
            papBase[7]->config(120000, D_ANG(90*-3), 0, -1500);
            break;
        }
        case 9: {
            papBase[0]->config(60000, D_ANG(90*0), 0, 1000);
            papBase[1]->config(60000, D_ANG(90*1), 0, 1000);
            papBase[2]->config(60000, D_ANG(90*2), 0, 1000);
            papBase[3]->config(60000, D_ANG(90*3), 0, 1000);
            papBase[4]->config(120000, D_ANG(72* 0), 0, -1500);
            papBase[5]->config(120000, D_ANG(72*-1), 0, -1500);
            papBase[6]->config(120000, D_ANG(72*-2), 0, -1500);
            papBase[7]->config(120000, D_ANG(72*-3), 0, -1500);
            papBase[8]->config(120000, D_ANG(72*-4), 0, -1500);
            break;
        }
        default :
            break;
    }
}

