#include "MyBunshinBase.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/AxisVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/lib/util/Direction26Util.h"



using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinBase::MAX_BUNSHIN_NUM = 10;              //�ő啪�g��
const frame MyBunshinBase::BUNSHIN_D = 16;                  //�g���[�X���̕��g�ƕ��g�̊Ԋu
const angvelo MyBunshinBase::ANGVELO_TURN = D_ANG(2.7);     //���g�̌����̊p���x
const angvelo MyBunshinBase::ANGVELO_EXPANSE = D_ANG(2.7);  //���g�L�����]�p���x
const int MyBunshinBase::RENGE = PX_C(70);                  //���g���߂��Ă��鎞��MAX����
const velo MyBunshinBase::VELO_BUNSHIN_FREE_MV = PX_C(20);  //���g�t���[�ړ����̕��g�̈ړ����x
int MyBunshinBase::now_bunshin_num_ = 0;

enum {
    TRACE_TWINBEE,   //�c�C���r�[�̕��g�̂悤�ȃg���[�X
    TRACE_GRADIUS,   //�O���f�B�E�X�̃I�v�V�����̂悤�ȃg���[�X
    TRACE_FREEZE,    //�O���f�B�E�XV��Type1�̃I�v�V�����t���[�Y�̂悤�ȓ���
};
enum {
    PHASE_INIT,
    PHASE_BUNSHIN_NOMAL_TRACE,
    PHASE_BUNSHIN_FREE_MODE_IGNITED,
    PHASE_BUNSHIN_FREE_MODE_READY,
    PHASE_BUNSHIN_FREE_MODE_MOVE,
    PHASE_BUNSHIN_FREE_MODE_STOP,
    PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS,
    PHASE_BANPEI,
};

MyBunshinBase::MyBunshinBase(const char* prm_name, unsigned int prm_no) :
        DefaultGeometricActor(prm_name) {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActor��FK�x�[�X�ɂȂ邽�߂ɕK�v

    trace_offset_.set(0,0,0);
    no_ = prm_no; //�P�`
    delay_r_ = RCNV(1,MyBunshinBase::MAX_BUNSHIN_NUM,no_,0.4,1.0);
    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->appendGroupChildAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace_ = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_no);
    trace_mode_ = TRACE_GRADIUS;
    return_default_pos_frames_ = 0;
    GgafDx::AxisVehicle* const pAxisVehicle = getAxisVehicle();
    pAxisVehicle->forceVeloXYZRange(-MyBunshinBase::RENGE, MyBunshinBase::RENGE);
    pAxisVehicle->forceAcceXYZRange(-MyBunshinBase::RENGE / 30, MyBunshinBase::RENGE / 30);

    is_free_mode_ = false;
    is_isolate_mode_ = true;
    moving_frames_since_default_pos_ = 0;

    bunshin_default_radius_pos_ = 0;
    bunshin_default_ang_pos_  = 0;
    bunshin_default_expanse_ = 0;
    bunshin_default_angvelo_mv_ = 0;
    bunshin_velo_mv_radius_pos_ = 0;
    bunshin_radius_pos_ = 0;
    c_ax_x_ = 0.0f;
    c_ax_y_ = 0.0f;
    c_ax_z_ = 0.0f;
}

void MyBunshinBase::config(
        coord prm_radius_pos,
        angle prm_ang_pos,
        angle prm_expanse,
        angvelo prm_angvelo_mv)
{
    bunshin_default_radius_pos_ = prm_radius_pos;
    bunshin_default_ang_pos_    = UTIL::simplifyAng(prm_ang_pos);
    bunshin_default_expanse_    = UTIL::simplifyAng(prm_expanse);
    bunshin_default_angvelo_mv_ = prm_angvelo_mv;
    bunshin_velo_mv_radius_pos_ = (velo)(3000.0 * (bunshin_default_radius_pos_/60000.0));
    bunshin_radius_pos_         = bunshin_default_radius_pos_;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    getVecVehicle()->linkFaceAngByMvAng(true);
}

void MyBunshinBase::onReset() {
    pBunshin_->setRadiusPosition(bunshin_default_radius_pos_);
    bunshin_radius_pos_ = bunshin_default_radius_pos_;

    setRollFaceAng(bunshin_default_ang_pos_);
    getVecVehicle()->setRollFaceAngVelo(bunshin_default_angvelo_mv_);
    getPhase()->reset(PHASE_INIT);
    trace_mode_ = TRACE_GRADIUS;
}

void MyBunshinBase::onActive() {
    is_free_mode_ = true;
    setPosition(pMYSHIP->_x,pMYSHIP->_y,pMYSHIP->_z);

    int len = pPosTrace_->_num;
    Pos* p = pPosTrace_->_paPos;
    for (int i = 0; i < len; i++) {
        p[i].set(pMYSHIP);
    }
    pBunshin_->setRadiusPosition(0);
    resetBunshin(0);
    //MyBunshinBase�́AactivateTree() �ł͂Ȃ��Aactivate() ����邽��
    //���g��onActive();���蓮�ŌĂяo��
    pBunshin_->onActive();
}

void MyBunshinBase::onInactive() {
    //MyBunshinBase�́AinactivateTree() �ł͂Ȃ��Ainactivate() ����邽��
    //���g��onInactive();���蓮�ŌĂяo��
    pBunshin_->onInactive();
}

void MyBunshinBase::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafDx::AxisVehicle* const pAxisVehicle = getAxisVehicle();

    if (is_isolate_mode_) {
        pVecVehicle->behave();
        pAxisVehicle->behave();
        return;
    }
    MyShip* pMyShip = pMYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;
    const bool is_pressed_VB_OPTION = pVbPlay->isPressed(VB_OPTION);
    const bool is_pressed_VB_TURBO  = pVbPlay->isPressed(VB_TURBO);
    const bool is_released_up_VB_TURBO = pVbPlay->isReleasedUp(VB_TURBO);
    GgafCore::Phase* pPhase = getPhase();

    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
            break;
        }
        case PHASE_BUNSHIN_NOMAL_TRACE: { //�ʏ�g���[�X
            if (pPhase->hasJustChanged()) {
                is_free_mode_ = false;
            }
            //�����ʒu����Q�O�t���[���ȓ��̓����́ATRACE_TWINBEE�ɂ���ď����ʒu���ێ�������
            if (pMyShip->is_move_) {
                if (is_pressed_VB_OPTION) {
                    moving_frames_since_default_pos_ = 0;
                } else {
                    moving_frames_since_default_pos_++;
                }
            } else {
                if (moving_frames_since_default_pos_ <= 20) {
                    moving_frames_since_default_pos_ = 0;
                }
            }
            trace_mode_ = moving_frames_since_default_pos_ > 20 ? TRACE_GRADIUS : TRACE_TWINBEE;
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_IGNITED: { //���g�t���[���[�h�A�_�Α҂��I
            if (pPhase->hasJustChanged()) {
                pBunshin_->effectFreeModeIgnited(); //�_�΃G�t�F�N�g
            }
            if (is_pressed_VB_OPTION && is_pressed_VB_TURBO) {
                if (pPhase->getFrame() >= (((MyBunshinBase::now_bunshin_num_ - (no_-1) )*5) + 10) ) { //������̃I�v�V��������
                    pPhase->change(PHASE_BUNSHIN_FREE_MODE_READY);
                }
            } else {
                //���g�t���[���[�h�A���Z�b�g
                if (is_free_mode_) {
                    pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
                } else {
                    pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
                }
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_READY: { //���g�t���[���[�h���ˏ���OK
            if (pPhase->hasJustChanged()) {
                pBunshin_->effectFreeModeReady(); //���ˏ���OK�G�t�F�N�g
            }
            if ( pPhase->getFrame() >= ((no_-1)*5) + 10 ) { //�Ō�̕��g�����ˏ���OK�ɂȂ�������+10
                //��������
                pPhase->change(PHASE_BUNSHIN_FREE_MODE_MOVE);
            } else {
                if (is_pressed_VB_OPTION) {
                    if(is_released_up_VB_TURBO) { //VB_TURBO���������Ƒ����ˁB
                        //�n�[�t���ˁI�I
                        pPhase->change(PHASE_BUNSHIN_FREE_MODE_MOVE);
                    } else {
                        //���ˑ҂��E�E�E
                    }
                } else {
                    //VB_OPTION �𗣂��ƃ��Z�b�g�B
                    //���Z�b�g
                    if (is_free_mode_) {
                        pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
                    } else {
                        pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
                    }
                }
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_MOVE: { //���g�t���[���[�h�A����ړ��I
            if (pPhase->hasJustChanged()) {
                //���g�t���[���[�h�ړ��J�n
                pBunshin_->effectFreeModeLaunch(); //���˃G�t�F�N�g
                is_free_mode_ = true;
                pAxisVehicle->setXYZZero();
                pAxisVehicle->setAcceXYZZero();
            }
            if (is_pressed_VB_OPTION) {
                //���g�t���[���[�h�ňړ���
                //�I�v�V�����̍L����p���AMyBunshinBase�̈ړ����x�ƁAMyBunshin���񔼌a�������x�Ƀx�N�g�������B
                angvelo bunshin_angvelo_expance = pBunshin_->getExpanse();
                pVecVehicle->setMvVelo(ANG_COS(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV); //MyBunshinBase
                pBunshin_->addRadiusPosition(ANG_SIN(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV);
                // VB_OPTION �𗣂��܂ő҂E�E�E
            } else {
                //���g�t���[���[�h�A���f�ҋ@
                pVecVehicle->setMvVelo(0);
                pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_STOP: { //���g�t���[���[�h�A��~���I
            if (pPhase->hasJustChanged()) {
                pBunshin_->effectFreeModePause();
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS: { //���g���̏ꏊ�ɖ߂�I
            if (pPhase->hasJustChanged()) {
            }
            const Pos* pTargetPos = pPosTrace_->getNext(); //�ʏ펞�̖{���̕��g�̍��W�ʒu��ڕW�ɂ���
            const coord tx = pTargetPos->x;
            const coord ty = pTargetPos->y;
            const coord tz = pTargetPos->z;
            if (pPhase->getFrame() == 3*(no_-1)) { //�΂����

                // (0,1,0) �~ RxRzRy �� ( (cosRx*-sinRz*cosRy + sinRx*sinRy),  cosRx*cosRz, (cosRx*-sinRz*-sinRy + sinRx*cosRy) )
                const float sinRx = ANG_SIN(_rx);
                const float cosRx = ANG_COS(_rx);
                const float sinRy = ANG_SIN(_ry);
                const float cosRy = ANG_COS(_ry);
                const float sinRz = ANG_SIN(_rz);
                const float cosRz = ANG_COS(_rz);
                pAxisVehicle->setVeloXYZ( (cosRx*-sinRz*cosRy + sinRx*sinRy)  * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                         (cosRx*cosRz)                       * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                         (cosRx*-sinRz*-sinRy + sinRx*cosRy) * MyBunshinBase::VELO_BUNSHIN_FREE_MV );
            } else if (pPhase->getFrame() > 3*(no_-1)) { //�΂����
                pAxisVehicle->setAcceXYZ( (tx - (_x + pAxisVehicle->_velo_x*6)),
                                         (ty - (_y + pAxisVehicle->_velo_y*6)),
                                         (tz - (_z + pAxisVehicle->_velo_z*6)) );
            }
            if (ABS(_x - tx) < 10000 &&
                ABS(_y - ty) < 10000 &&
                ABS(_z - tz) < 10000 &&
                ABS(pAxisVehicle->_velo_x) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxisVehicle->_velo_y) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxisVehicle->_velo_z) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV)
            {
                //���ǂ����I
                pAxisVehicle->setXYZZero();
                pAxisVehicle->setAcceXYZZero();
                setPosition(tx, ty, tz);
                moving_frames_since_default_pos_ = 0;
                pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }

        default :
            break;
    }

    //�I�v�V�����t���[���[�h�ւ̔��f
    if (is_pressed_VB_OPTION) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBO�_�u���v�b�V��
            //���g�t���[���[�h�A�_�΁I
            pPhase->change(PHASE_BUNSHIN_FREE_MODE_IGNITED);
        }
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION, 8, 8)) {
        if (is_pressed_VB_TURBO) {
            //VB_OPTION �_�u���v�b�V�� + VB_TURBO�������ςȂ��̏ꍇ
            //�n�[�t�Z�b�g
            //�t���[���[�h�ێ��A���a�ʒu���ێ��A
            resetBunshin(1);
        } else {
            //VB_OPTION �_�u���v�b�V���AVB_TURBO�������Ă��Ȃ��ƁA
            //�I�[�����Z�b�g
            resetBunshin(0);
        }
    } else if (is_pressed_VB_OPTION) {
        //���g����
        if (is_pressed_VB_TURBO) {
            trace_mode_ = TRACE_FREEZE;
            dir26 mv_way_sgn_x_MyShip = pMyShip->mv_way_sgn_x_;
            dir26 mv_way_sgn_y_MyShip = pMyShip->mv_way_sgn_y_;
            dir26 mv_way_sgn_z_MyShip = pMyShip->mv_way_sgn_z_;
            //���g�L����
            if (mv_way_sgn_x_MyShip == 1) {
                pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
            } else if (mv_way_sgn_x_MyShip == -1) {
                pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
            } else {
                if (mv_way_sgn_z_MyShip == 1) {
                    pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (mv_way_sgn_z_MyShip == -1) {
                    pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
            }
            //���a�ʒu����
            if (mv_way_sgn_y_MyShip == 1) {
                pBunshin_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
            } else if (mv_way_sgn_y_MyShip == -1) {
                pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
            bunshin_radius_pos_ = pBunshin_->getRadiusPosition(); //�W�����a�ʒu���X�V
        } else {  //if ( pVbPlay->isPressed(VB_TURBO) )  �� else
            //���g�̌���(this�y��̌���)����
            trace_mode_ = TRACE_FREEZE;
            //�J�����ʒu�ɂ���ď㉺���E�̑��슄����ς���
            const dir26 pos_up = pVAM->getPosUp();
            const float vX = pVecVehicle->_vX;
            const float vY = pVecVehicle->_vY;
            const float vZ = pVecVehicle->_vZ;
            bool update_updown_rot_axis_timing = (pVecVehicle->isTurningMvAng() || pVbPlay->isPushedDown(VB_OPTION) || pVAM->isJustChangedPosCam());

            //LEFT RIGHT ��]�� = pos_up = (up_sgn_x, up_sgn_y, up_sgn_z)
            float up_vx, up_vy, up_vz;
            Direction26Util::cnvDirNo2Vec(pos_up, up_vx, up_vy, up_vz);
            //b = (vX, vY, vZ)
            //a�~b = (up_sgn_y*vZ-up_sgn_z*vY, up_sgn_z*vX-up_sgn_x*vZ, up_sgn_x*vY-up_sgn_y*vX)
            //�� (a1,a2,a3)�~(b1,b2,b3)=(a2*b3-a3*b2, a3*b1-a1*b3, a1*b2-a2*b1)
            if (update_updown_rot_axis_timing) {
                // UP DOWN ��]��
                float c_vx = up_vy*vZ-up_vz*vY;
                float c_vy = up_vz*vX-up_vx*vZ;
                float c_vz = up_vx*vY-up_vy*vX;
                if ( !(ZEROf_EQ(c_vx) && ZEROf_EQ(c_vy) && ZEROf_EQ(c_vz)) ) {
                    UTIL::getNormalizedVector(c_vx, c_vy, c_vz,
                                              c_ax_x_, c_ax_y_, c_ax_z_);
                }
            }
            if (pos_up == VAM_POS_UP) {
                //����
                if (pVbPlay->isPressed(VB_LEFT)) {
                    pVecVehicle->addRyMvAng(-MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(VB_RIGHT)) {
                    pVecVehicle->addRyMvAng(MyBunshinBase::ANGVELO_TURN);
                }
                if (pVbPlay->isPressed(VB_UP)) {
                    pVecVehicle->addRzMvAng(MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(VB_DOWN)) {
                    pVecVehicle->addRzMvAng(-MyBunshinBase::ANGVELO_TURN);
                }

//TODO:��ȊO���΂߂łȂ���΍����ł�����̂ł́H
            } else {
                //�d�����d���Ȃ�
                if (pVbPlay->isPressed(VB_LEFT)) {
                    addTurnAngleAroundAx2( up_vx,  up_vy,  up_vz);
                } else if (pVbPlay->isPressed(VB_RIGHT)) {
                    addTurnAngleAroundAx2(-up_vx, -up_vy, -up_vz);
                }
                if (pVbPlay->isPressed(VB_UP)) {
                    addTurnAngleAroundAx1( c_ax_x_,  c_ax_y_,  c_ax_z_);
                } else if (pVbPlay->isPressed(VB_DOWN)) {
                    addTurnAngleAroundAx1(-c_ax_x_, -c_ax_y_, -c_ax_z_);
                }
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
            setPosition(_x + pMyShip->mv_offset_x_,
                        _y + pMyShip->mv_offset_y_,
                        _z + pMyShip->mv_offset_z_ );
        }
    } else {
        //�ʏ펞�� trace_mode_ �̓���
        setPosAt(pPosTrace_->getNext()); //��Ȃ̂�getNext()���������W���B
        if (trace_mode_ == TRACE_GRADIUS) {
            //TRACE_GRADIUS �� �y�䂪�ړ�����Ȃ�΁A���a�ʒu��y��̒��S�Ɋ񂹂�
            Pos* p = pPosTrace_->get2Next();
            if (!(p->x == _x && p->y == _y && p->z == _z)) {
                pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
        }
    }
    pVecVehicle->behave();
    pAxisVehicle->behave();
}

void MyBunshinBase::resetBunshin(int prm_mode) {
    //prm_mode = 0 �I�[�����Z�b�g
    //prm_mode = 1 �n�[�t���Z�b�g

    EffectTurbo002* pTurbo002 = CommonScene_dispatch(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->setPositionAt(pBunshin_);
    }

    is_isolate_mode_ = false;
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    //���S�Ƀf�t�H���g��ԂɌ��ɖ߂��߂ɁA�Œ���K�v�ȃt���[������l
    return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * (MyBunshinBase::MAX_BUNSHIN_NUM+1); //�����΂�����鉉�o
    //�G�t�F�N�g

    //�y�䂪�̌��������ɖ߂�i�O���Ɍ����j�w��
    pVecVehicle->asstMvAng()->turnRzRyByDtTo(D0ANG, D0ANG,
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
    pVecVehicle->asstFaceAng()->rollFaceAngByDtTo(
                          bunshin_default_ang_pos_,
                          SGN(bunshin_default_angvelo_mv_) > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                          return_default_pos_frames_/2, //�΂������ƃY����̂�  * delay_r_ ���܂���
                          0.3, 0.5,
                          bunshin_default_angvelo_mv_,
                          true
                       );
    if (prm_mode == 0) {
        //VB_OPTION �_�u���v�b�V�� + VB_TURBO�������ςȂ��̏ꍇ
        //�I�[�����Z�b�g
        //���g�̔��a�ʒu�����ɖ߂�w��
        bunshin_radius_pos_ = bunshin_default_radius_pos_;
        pBunshin_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_ * delay_r_ );
        //���return_default_pos_frames_ ��0�ɂȂ�܂�
        //trace_mode_ = TRACE_TWINBEE;
        //���s����
        pPhase->change(PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS); //���g���ɖ߂�
    } else {
        //VB_OPTION �_�u���v�b�V���AVB_TURBO�������Ă��Ȃ��ƁA
        //�`���b�g���Z�b�g
        //�t���[���[�h�ێ��A���a�ʒu���ێ��A
        return_default_pos_frames_ = 0;
    }
}
void MyBunshinBase::addTurnAngleAroundAx1(float prm_ax_x, float prm_ax_y, float prm_ax_z) {
    //������W(x, y, z)�ɂ����āA��]�̎��� v=(��, ��, ��) (�A��|v|=1) �ŁA�Ɖ񂷉�]���������ꍇ�B
    //P = (0; x, y, z)
    //Q = (cos(��/2); �� sin(��/2), �� sin(��/2), �� sin(��/2))
    //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
    //�Ƃ��āA�����v�Z����B
    //R P Q = (0; x2, y2, z2)
    //�Ɖ�]������̍��W�� (x2, y2, z2)
    static const float p_sin_h = ANG_SIN(MyBunshinBase::ANGVELO_TURN/2);  //ANGVELO_TURN=��]���������p�x
    static const float p_cos_h = ANG_COS(MyBunshinBase::ANGVELO_TURN/2);

    float a = prm_ax_x*p_sin_h;
    float b = prm_ax_y*p_sin_h;
    float c = prm_ax_z*p_sin_h;

    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    Quaternion<float> H(p_cos_h, -a, -b, -c); //R
    H.mul(0, pVecVehicle->_vX, pVecVehicle->_vY, pVecVehicle->_vZ); //R*P
    H.mul(p_cos_h, a, b, c);                               //R*P*Q
    pVecVehicle->setRzRyMvAng(H.i, H.j, H.k, false);
}

void MyBunshinBase::addTurnAngleAroundAx2(float prm_ax_x, float prm_ax_y, float prm_ax_z) {
    static const float p_sin_h = ANG_SIN(MyBunshinBase::ANGVELO_TURN/2);  //ANGVELO_TURN=��]���������p�x
    static const float p_cos_h = ANG_COS(MyBunshinBase::ANGVELO_TURN/2);

    float a = prm_ax_x*p_sin_h;
    float b = prm_ax_y*p_sin_h;
    float c = prm_ax_z*p_sin_h;

    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    Quaternion<float> H(p_cos_h, -a, -b, -c); //R
    Quaternion<float> H2 = H;
    H.mul(0, pVecVehicle->_vX, pVecVehicle->_vY, pVecVehicle->_vZ); //R*P
    H.mul(p_cos_h, a, b, c);                               //R*P*Q
    pVecVehicle->setRzRyMvAng(H.i, H.j, H.k, false);

    //�㉺���͎��̉�]������]������
    H2.mul(0, c_ax_x_, c_ax_y_, c_ax_z_); //R*P
    H2.mul(p_cos_h, a, b, c);             //R*P*Q
    c_ax_x_ = H2.i;
    c_ax_y_ = H2.j;
    c_ax_z_ = H2.k;
}

MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace_);
}

void MyBunshinBase::setBunshinNum(int prm_num) {
    MyBunshinBase::now_bunshin_num_ = prm_num;
    MyBunshinBase** papBase = pMYSHIP_SCENE->papBunshinBase_;
    for (int i = 0; i < MyBunshinBase::MAX_BUNSHIN_NUM; i++) {
        MyBunshinBase* p = papBase[i];
        if (i+1 <= prm_num) {
            //�������Ė����ꍇ����������B�������������牽�����Ȃ��B
            if (!(p->isActive())) {
                p->activate();
            }
        } else {
            //�����𒴂��镪�g�͔񊈓�
            if (p->isActive()) {
                p->inactivate();
            }
        }
    }

    const angvelo INNER_ROT = D_ANG(0.5);   //���g�����邮����񂵂Ă��鑬�x
    const angvelo OUTER_ROT = -D_ANG(1);
    const coord INNER_RADIUS = PX_C(50);  //�������g�̒��S����̋���
    const coord OUTER_RADIUS = PX_C(120); //�O�����g�̒��S����̋���
    switch (MyBunshinBase::now_bunshin_num_) {
        case 1: {
            papBase[0]->config(INNER_RADIUS, D0ANG, 0, INNER_ROT);
            break;
        }
        case 2: {
            papBase[0]->config(INNER_RADIUS, D0ANG  , 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D180ANG, 0, INNER_ROT);
            break;
        }
        case 3: {
            papBase[0]->config(INNER_RADIUS, D_ANG(120*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(120*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(120*2), 0, INNER_ROT);
            break;
        }
        case 4: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            break;
        }
        case 5: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG, 0, OUTER_ROT);
            break;
        }
        case 6: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG  , 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D180ANG, 0, OUTER_ROT);
            break;
        }
        case 7: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(120* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(120*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(120*-2), 0, OUTER_ROT);
            break;
        }
        case 8: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(90* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(90*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(90*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(90*-3), 0, OUTER_ROT);
            break;
        }
        case 9: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(72* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(72*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(72*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(72*-3), 0, OUTER_ROT);
            papBase[8]->config(OUTER_RADIUS, D_ANG(72*-4), 0, OUTER_ROT);
            break;
        }
        case 10: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(60* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(60*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(60*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(60*-3), 0, OUTER_ROT);
            papBase[8]->config(OUTER_RADIUS, D_ANG(60*-4), 0, OUTER_ROT);
            papBase[9]->config(OUTER_RADIUS, D_ANG(60*-5), 0, OUTER_ROT);
            break;
        }
        default :
            break;
    }
}


