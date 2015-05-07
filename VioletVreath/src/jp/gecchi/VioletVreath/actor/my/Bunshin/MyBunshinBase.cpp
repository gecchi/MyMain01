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

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantC.h"
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
        DefaultMeshActor(prm_name, "Nothing") {

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
    renge_ = PX_C(80); //���g���߂��Ă��鎞��MAX����
    pAxsMver_->forceVxyzMvVeloRange(-renge_, renge_);
    pAxsMver_->forceVxyzMvAcceRange(-renge_ / 30, renge_ / 30);

    velo_bunshin_free_mv_ = PX_C(20);
    is_free_mode_ = false;
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
        case PROG_BUNSHIN_NOMAL_TRACE: { //�ʏ�g���[�X
            if (pProg->hasJustChanged()) {
                is_free_mode_ = false;
            }
            trace_mode_ = TRACE_GRADIUS;
            break;
        }

        case PROG_BUNSHIN_FREE_IGNITED: { //���g�t���[���[�h�A�_�Α҂��I
            if (pProg->hasJustChanged()) {
            }
            if (pVbPlay->isBeingPressed(VB_OPTION | VB_TURBO) == (VB_OPTION | VB_TURBO)) {
                if (pProg->getFrame() >= (MyBunshinBase::MAX_BUNSHIN_NUM - (no_-1) )*10) { //�ŏ��̃I�v�V�����قǃJ�E���g�������K�v
                    //�_�Ί����B����
                    pBunshin_->effectIgnited();
                    pProg->change(PROG_BUNSHIN_FREE_READY);
                }
            } else {
                //���g�t���[���[�h�A���Z�b�g
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_READY: { //���g�t���[���[�h���ˏ���OK
            if (pVbPlay->isBeingPressed(VB_OPTION)) {
                if(pVbPlay->isReleasedUp(VB_TURBO)) { //VB_OPTION���������Ɣ��ˁB
                    //���ˁI�I
                    pProg->change(PROG_BUNSHIN_FREE_MOVE);
                } else {
                    //���ˑ҂��E�E�E
                }
            } else {
                //���g�t���[���[�h�A���Z�b�g
                pProg->change(PROG_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_MOVE: { //���g�t���[���[�h�A����ړ��I
            if (pProg->hasJustChanged()) {
                //���g�t���[���[�h�ړ��J�n
                is_free_mode_ = true;
                pAxsMver_->setZeroVxyzMvVelo();
                pAxsMver_->setZeroVxyzMvAcce();
                EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
                if (pTurbo002) {
                    pTurbo002->positionAs(pBunshin_);
                }
            }
            if (pVbPlay->isBeingPressed(VB_OPTION)) {
                //���g�t���[���[�h�ňړ���
                //�I�v�V�����̍L����p���AMyBunshinBase�̈ړ����x�ƁAMyBunshin���񔼌a�������x�Ƀx�N�g�������B
                angvelo bunshin_angvelo_expance = pBunshin_->getExpanse();
                pKuroko->setMvVelo(ANG_COS(bunshin_angvelo_expance) * velo_bunshin_free_mv_); //MyBunshinBase
                pBunshin_->addRadiusPosition(ANG_SIN(bunshin_angvelo_expance) * velo_bunshin_free_mv_);
            } else {
                //���g�t���[���[�h�A���f�ҋ@
                pKuroko->setMvVelo(0);
                pProg->change(PROG_BUNSHIN_FREE_WAIT);
            }
            break;
        }
        case PROG_BUNSHIN_FREE_WAIT: { //���g�t���[���[�h�A�ҋ@���I
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        case PROG_BUNSHIN_FREE_RETURN_DEFAULT_POS: { //���g�߂�I
            if (pProg->hasJustChanged()) {
            }
            Pos* pTargetPos = pPosTrace_->getNext(); //�ʏ펞�̖{���̕��g�̍��W�ʒu��ڕW
            coord tx = pTargetPos->x;
            coord ty = pTargetPos->y;
            coord tz = pTargetPos->z;
            pAxsMver_->setVxyzMvAcce( (tx - (_x + pAxsMver_->_velo_vx_mv*6))*delay_r_,
                                      (ty - (_y + pAxsMver_->_velo_vy_mv*6))*delay_r_,
                                      (tz - (_z + pAxsMver_->_velo_vz_mv*6))*delay_r_ );
            if (ABS(_x - tx) < 10000 &&
                ABS(_y - ty) < 10000 &&
                ABS(_z - tz) < 10000 &&
                ABS(pAxsMver_->_velo_vx_mv) < 20000 &&
                ABS(pAxsMver_->_velo_vy_mv) < 20000 &&
                ABS(pAxsMver_->_velo_vz_mv) < 20000)
            {
                //���ǂ����I
                pAxsMver_->setZeroVxyzMvVelo();
                pAxsMver_->setZeroVxyzMvAcce();
                position(tx, ty, tz);
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
            pProg->change(PROG_BUNSHIN_FREE_IGNITED);
        }
    }


    if (return_default_pos_frames_ > 0) {
        //���g�����̈ʒu�ɖ߂�p����
        trace_mode_ = TRACE_TWINBEE; //�߂��Ă�Œ��̓c�C���r�[�g���[�X
        return_default_pos_frames_ --;
    }

    if (pVbPlay->isDoublePushedDown(VB_OPTION,8,8)) {
        //���S�Ƀf�t�H���g��ԂɌ��ɖ߂��߂ɁA�Œ���K�v�ȃt���[������l
        trace_mode_ = TRACE_TWINBEE;
        return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * (MyBunshinBase::MAX_BUNSHIN_NUM+1); //�����΂�����鉉�o
        //�G�t�F�N�g
        EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
        if (pTurbo002) {
            pTurbo002->positionAs(pBunshin_);
        }
        //�y�䂪�̌��������ɖ߂�i�O���Ɍ����j�w��
        pKuroko->asstC()->turnRzRyMvAngByDtTo(D0ANG, D0ANG,
                                              TURN_CLOSE_TO,
                                              false,
                                              return_default_pos_frames_ * delay_r_,
                                              0.3, 0.7,
                                              0,
                                              true);
        //���g�̊p�x�ʒu�����ɖ߂�w��
        int angvelo_sgn = SGN(bunshin_default_angvelo_mv_);
        pKuroko->asstB()->rollFaceAngByDtTo(
                              bunshin_default_ang_position_,
                              angvelo_sgn > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                              return_default_pos_frames_, //�΂������ƃY����̂�  * delay_r_ ���܂���
                              0.3, 0.7,
                              bunshin_default_angvelo_mv_,
                              true
                           );
        //���g�̔��a�ʒu�����ɖ߂�w��
        bunshin_radius_pos_ = bunshin_default_radius_position_;
        pBunshin_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_ * delay_r_ );
        //���g�̌��������ɖ߂�i�O���Ɍ����j�w��
        pBunshin_->turnExpanse(
                       D_ANG(0),
                       return_default_pos_frames_ * delay_r_
                   );
        //���return_default_pos_frames_ ��0�ɂȂ�܂�
        //trace_mode_ = TRACE_TWINBEE;
        //���s����
        pProg->change(PROG_BUNSHIN_FREE_RETURN_DEFAULT_POS); //���g���ɖ߂�
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



MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace_);
    GGAF_DELETE(pAxsMver_);
}

