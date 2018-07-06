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
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinBase::MAX_BUNSHIN_NUM = 9;
const frame MyBunshinBase::BUNSHIN_D = 16;
const angvelo MyBunshinBase::ANGVELO_TURN = D_ANG(2.7);        //���g�̌����̊p���x
const angvelo MyBunshinBase::ANGVELO_EXPANSE = D_ANG(2.7);     //���g�L�����]�p���x
const int MyBunshinBase::RENGE = PX_C(70);                  //���g���߂��Ă��鎞��MAX����
const velo MyBunshinBase::VELO_BUNSHIN_FREE_MV = PX_C(20);  //���g�t���[�ړ����̕��g�̈ړ����x
int MyBunshinBase::now_bunshin_num_ = 0;

enum {
    TRACE_TWINBEE,   //�c�C���r�[�̕��g�̂悤�ȃg���[�X
    TRACE_GRADIUS,   //�O���f�B�E�X�̃I�v�V�����̂悤�ȃg���[�X
    TRACE_FREEZE,    //�O���f�B�E�XV��Type1�̃I�v�V�����t���[�Y�̂悤�ȓ���
};
enum {
    PROG_INIT,
    PROG_BUNSHIN_NOMAL_TRACE,
    PROG_BUNSHIN_FREE_MODE_IGNITED,
    PROG_BUNSHIN_FREE_MODE_READY,
    PROG_BUNSHIN_FREE_MODE_MOVE,
    PROG_BUNSHIN_FREE_MODE_STOP,
    PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS,
    PROG_BANPEI,
};

MyBunshinBase::MyBunshinBase(const char* prm_name, unsigned int prm_no) :
        DefaultGeometricActor(prm_name) {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActor��FK�x�[�X�ɂȂ邽�߂ɕK�v

    trace_offset_.set(0,0,0);
    no_ = prm_no; //�P�`
    delay_r_ = RCNV(1,MyBunshinBase::MAX_BUNSHIN_NUM,no_,0.4,1.0);
    std::string bunshin_name = "Bunshin" + XTOS(no_);
    pBunshin_ = NEW MyBunshin(bunshin_name.c_str(), this);
    this->addSubGroupAsFk(pBunshin_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace_ = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_no);
    trace_mode_ = TRACE_GRADIUS;
    return_default_pos_frames_ = 0;
    GgafDxAxesMover* const pAxesMover = getAxesMover();
    pAxesMover->forceVxyzMvVeloRange(-MyBunshinBase::RENGE, MyBunshinBase::RENGE);
    pAxesMover->forceVxyzMvAcceRange(-MyBunshinBase::RENGE / 30, MyBunshinBase::RENGE / 30);

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
    bunshin_velo_mv_radius_pos_ = 3000 * (bunshin_default_radius_pos_/60000);
    bunshin_radius_pos_         = bunshin_default_radius_pos_;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    getKuroko()->linkFaceAngByMvAng(true);
    useProgress(PROG_BANPEI);
}

void MyBunshinBase::onReset() {
    pBunshin_->setRadiusPosition(bunshin_default_radius_pos_);
    bunshin_radius_pos_ = bunshin_default_radius_pos_;

    setRollFaceAng(bunshin_default_ang_pos_);
    getKuroko()->setRollFaceAngVelo(bunshin_default_angvelo_mv_);
    getProgress()->reset(PROG_INIT);
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
    GgafDxKuroko* pKuroko = getKuroko();
    GgafDxAxesMover* const pAxesMover = getAxesMover();

    if (is_isolate_mode_) {
        pKuroko->behave();
        pAxesMover->behave();
        return;
    }
    MyShip* pMyShip = pMYSHIP;
    VirtualButton* pVbPlay = VB_PLAY;
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
            if (pVbPlay->isPressed(VB_OPTION | VB_TURBO) == (VB_OPTION | VB_TURBO)) {
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
                if (pVbPlay->isPressed(VB_OPTION)) {
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
                pAxesMover->setZeroVxyzMvVelo();
                pAxesMover->setZeroVxyzMvAcce();
            }
            if (pVbPlay->isPressed(VB_OPTION)) {
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
                pBunshin_->effectFreeModePause();
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
                pAxesMover->setVxyzMvVelo((cosRx*-sinRz*cosRy + sinRx*sinRy)  * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                          (cosRx*cosRz)                       * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                          (cosRx*-sinRz*-sinRy + sinRx*cosRy) * MyBunshinBase::VELO_BUNSHIN_FREE_MV );
            } else if (pProg->getFrame() > 3*(no_-1)) { //�΂����
                pAxesMover->setVxyzMvAcce( (tx - (_x + pAxesMover->_velo_vx_mv*6)),
                                           (ty - (_y + pAxesMover->_velo_vy_mv*6)),
                                           (tz - (_z + pAxesMover->_velo_vz_mv*6)) );
            }
            if (ABS(_x - tx) < 10000 &&
                ABS(_y - ty) < 10000 &&
                ABS(_z - tz) < 10000 &&
                ABS(pAxesMover->_velo_vx_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxesMover->_velo_vy_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pAxesMover->_velo_vz_mv) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV)
            {
                //���ǂ����I
                pAxesMover->setZeroVxyzMvVelo();
                pAxesMover->setZeroVxyzMvAcce();
                setPosition(tx, ty, tz);
                moving_frames_since_default_pos_ = 0;
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }

        default :
            break;
    }

    //�I�v�V�����t���[���[�h�ւ̔��f
    if (pVbPlay->isPressed(VB_OPTION)) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBO�_�u���v�b�V��
            //���g�t���[���[�h�A�_�΁I
            pProg->change(PROG_BUNSHIN_FREE_MODE_IGNITED);
        }
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        if (pVbPlay->isPressed(VB_TURBO)) {
            //VB_OPTION �_�u���v�b�V�� + VB_TURBO�������ςȂ��̏ꍇ
            //�n�[�t�Z�b�g
            //�t���[���[�h�ێ��A���a�ʒu���ێ��A
            resetBunshin(1);
        } else {
            //VB_OPTION �_�u���v�b�V���AVB_TURBO�������Ă��Ȃ��ƁA
            //�I�[�����Z�b�g
            resetBunshin(0);
        }
    } else if (pVbPlay->isPressed(VB_OPTION)) {
        //���g����
        if (pVbPlay->isPressed(VB_TURBO)) {
            trace_mode_ = TRACE_FREEZE;
            dir26 mv_way_MyShip = pMyShip->mv_way_;
            dir26 mv_way_sgn_x_MyShip = pMyShip->mv_way_sgn_x_;
            dir26 mv_way_sgn_y_MyShip = pMyShip->mv_way_sgn_y_;
            dir26 mv_way_sgn_z_MyShip = pMyShip->mv_way_sgn_z_;
            //���g�L����
            if (mv_way_sgn_x_MyShip == 1 || mv_way_sgn_z_MyShip == 1) {
                pBunshin_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
            } else if (mv_way_sgn_x_MyShip == -1 || mv_way_sgn_z_MyShip == -1) {
                pBunshin_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
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
            const dir26 pos_camera = pVAM->getPosCam();
            const dir26 pos_up = pVAM->getPosUp();
            const float vX = pKuroko->_vX;
            const float vY = pKuroko->_vY;
            const float vZ = pKuroko->_vZ;
            static const float ONE_OVER_ROOT2 = 1.0 / sqrt(2.0);
            bool update_updown_rot_axis_timing = (pKuroko->isTurningMvAng() || pVbPlay->isPushedDown(VB_OPTION) || pVAM->isJustChangedPosCam());

            //LEFT RIGHT ��]�� = pos_up = (up_sgn_x, up_sgn_y, up_sgn_z)
            float up_vx, up_vy, up_vz;
            GgafDx26DirectionUtil::cnvDirNo2Vec(pos_up, up_vx, up_vy, up_vz);
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
                    pKuroko->addRyMvAng(-MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(VB_RIGHT)) {
                    pKuroko->addRyMvAng(MyBunshinBase::ANGVELO_TURN);
                }
                if (pVbPlay->isPressed(VB_UP)) {
                    pKuroko->addRzMvAng(MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(VB_DOWN)) {
                    pKuroko->addRzMvAng(-MyBunshinBase::ANGVELO_TURN);
                }
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
        setPositionAt(pPosTrace_->getNext()); //��Ȃ̂�getNext()���������W���B
        if (trace_mode_ == TRACE_GRADIUS) {
            //TRACE_GRADIUS �� �y�䂪�ړ�����Ȃ�΁A���a�ʒu��y��̒��S�Ɋ񂹂�
            Pos* p = pPosTrace_->get2Next();
            if (!(p->x == _x && p->y == _y && p->z == _z)) {
                pBunshin_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
        }
    }

    pKuroko->behave();
    pAxesMover->behave();
}

void MyBunshinBase::resetBunshin(int prm_mode) {
    //prm_mode = 0 �I�[�����Z�b�g
    //prm_mode = 1 �n�[�t���Z�b�g

    EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->setPositionAt(pBunshin_);
    }

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
        pProg->change(PROG_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS); //���g���ɖ߂�
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
    GgafDxKuroko* pKuroko = getKuroko();
    GgafDxQuaternion H(p_cos_h, -prm_ax_x*p_sin_h, -prm_ax_y*p_sin_h, -prm_ax_z*p_sin_h); //R
    H.mul(0, pKuroko->_vX, pKuroko->_vY, pKuroko->_vZ);                                   //R*P
    H.mul(p_cos_h, prm_ax_x*p_sin_h, prm_ax_y*p_sin_h, prm_ax_z*p_sin_h);                 //R*P*Q
    pKuroko->setRzRyMvAng(H.i, H.j, H.k, true);
}

void MyBunshinBase::addTurnAngleAroundAx2(float prm_ax_x, float prm_ax_y, float prm_ax_z) {
    static const float p_sin_h = ANG_SIN(MyBunshinBase::ANGVELO_TURN/2);  //ANGVELO_TURN=��]���������p�x
    static const float p_cos_h = ANG_COS(MyBunshinBase::ANGVELO_TURN/2);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafDxQuaternion H(p_cos_h, -prm_ax_x*p_sin_h, -prm_ax_y*p_sin_h, -prm_ax_z*p_sin_h); //R
    GgafDxQuaternion H2 = H;
    H.mul(0, pKuroko->_vX, pKuroko->_vY, pKuroko->_vZ);                                   //R*P
    H.mul(p_cos_h, prm_ax_x*p_sin_h, prm_ax_y*p_sin_h, prm_ax_z*p_sin_h);                 //R*P*Q
    pKuroko->setRzRyMvAng(H.i, H.j, H.k, true);

    //�㉺���͎��̉�]������]������
    H2.mul(0, c_ax_x_, c_ax_y_, c_ax_z_);                                                 //R*P
    H2.mul(p_cos_h, prm_ax_x*p_sin_h, prm_ax_y*p_sin_h, prm_ax_z*p_sin_h);                //R*P*Q
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
            if (!(p->isActive())) {
                p->activate();
            }
        } else {
            if (p->isActive()) {
                p->inactivate();
            }
        }
    }

    const angvelo ROT = D_ANG(0.5);
    const coord INNER_RADIUS = PX_C(60);
    const coord OUTER_RADIUS = PX_C(120);
    switch (MyBunshinBase::now_bunshin_num_) {
        case 1: {
            papBase[0]->config(INNER_RADIUS, D0ANG, 0, ROT);
            break;
        }
        case 2: {
            papBase[0]->config(INNER_RADIUS, D0ANG  , 0, ROT);
            papBase[1]->config(INNER_RADIUS, D180ANG, 0, ROT);
            break;
        }
        case 3: {
            papBase[0]->config(INNER_RADIUS, D_ANG(120*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(120*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(120*2), 0, ROT);
            break;
        }
        case 4: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            break;
        }
        case 5: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG, 0, -ROT);
            break;
        }
        case 6: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG  , 0, -ROT);
            papBase[5]->config(OUTER_RADIUS, D180ANG, 0, -ROT);
            break;
        }
        case 7: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(120* 0), 0, -ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(120*-1), 0, -ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(120*-2), 0, -ROT);
            break;
        }
        case 8: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(90* 0), 0, -ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(90*-1), 0, -ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(90*-2), 0, -ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(90*-3), 0, -ROT);
            break;
        }
        case 9: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(72* 0), 0, -ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(72*-1), 0, -ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(72*-2), 0, -ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(72*-3), 0, -ROT);
            papBase[8]->config(OUTER_RADIUS, D_ANG(72*-4), 0, -ROT);
            break;
        }
        default :
            break;
    }
}


