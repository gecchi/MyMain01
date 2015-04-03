#include "MyOptionController.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectMyOption.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

int MyOptionController::max_option_num_ = 9;
int MyOptionController::o2o_ = 15;
int MyOptionController::now_option_num_ = 0;
//MyOptionController::MyOptionController(const char* prm_name, int prm_no) :
//        DefaultMeshSetActor(prm_name, "8/myvic") {

MyOptionController::MyOptionController(const char* prm_name, int prm_no) :
  GgafDxGeometricActor(prm_name, nullptr, nullptr) {
    pAxsMver_ = NEW GgafDxAxesMover(this);
    no_ = prm_no;
    is_handle_move_mode_ = false;
    is_free_from_myship_mode_ = false;
    return_to_default_position_seq_ = false;
    angVelo_Turn_ = 3000;
    veloOptionsMv_ = 20000;
    renge_ = 80000;
    pAxsMver_->forceVxyzMvVeloRange(-renge_, renge_);
    pAxsMver_->forceVxyzMvAcceRange(-renge_ / 30, renge_ / 30);
    std::string name = "MyOption("+XTOS(no_)+")";
    pOption_ = NEW MyOption(name.c_str(), no_, this);
    addSubGroup(pOption_);
    pOption_->inactivate();

//    //�M�Y��
//    pGizmo_ = NEW MyOptionControllerGizmo("MyPGizmo");
//    addSubGroup(pGizmo_);
//    //�����x�N�g��
//    pDirectionVector_ = NEW MyOptionControllerDirectionVector("MyPDirectionVector");
//    addSubGroup(pDirectionVector_);

    //�g���[�X�p����
    pRing_OptCtrlGeoHistory_ = NEW GgafLinkedListRing<GgafDxGeoElem>();
    for (int i = 0; i < max_option_num_*o2o_; i++) {
        pRing_OptCtrlGeoHistory_->addLast(NEW GgafDxGeoElem(this));
    }
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_RESTORE, "WAVE_MY_OPTION_RESTORE_001");
    pSeTx->set(SE_FREE,    "WAVE_MY_OPTION_FREE_001");
    was_ignited_option_ = false;
    ignited_option_cnt_mode_ = false;
    ignite_option_cnt_ = 0;
    frame_of_ignite_option_ = (no_+1)*10;
}

void MyOptionController::initialize() {
}

void MyOptionController::onReset() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(0);
    pKuroko->forceRzRyMvAngVeloRange(-1*angVelo_Turn_, angVelo_Turn_);
    pKuroko->setRzRyMvAng(0,0);
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->behave();
}

void MyOptionController::onActive() {
//    reset();
}

void MyOptionController::processBehavior() {
    MyShip* const pMyShip = P_MYSHIP;
    const VirtualButton* const pVbPlay = VB_PLAY;
    const vb_sta is_double_push_VB_OPTION = pVbPlay->isDoublePushedDown(VB_OPTION,8,8);
    GgafDxKuroko* const pKuroko = getKuroko();
    MyOption* const pOption = pOption_;
    if (is_double_push_VB_OPTION) {
        //���Ƃɖ߂�
        pKuroko->turnRzRyMvAngTo(D0ANG, D0ANG,
                                 D_ANG(20), 0,
                                 TURN_CLOSE_TO,
                                 false );
        is_free_from_myship_mode_ = false;
        is_handle_move_mode_ = false;
        return_to_default_position_seq_ = true;
        MyOptionController::adjustDefaltAngPosition(60);
        pOption->return_to_base_radiusPosition_seq_ = true;
        pOption->return_to_base_angExpanse_seq_= true;
        if (pOption->isActive()) {
            EffectTurbo002* const pTurbo002 = dispatchFromCommon(EffectTurbo002);
            if (pTurbo002) {
                pTurbo002->positionAs(pOption);
            }
        }
    } else if (pVbPlay->isBeingPressed(VB_OPTION) && !pVbPlay->isBeingPressed(VB_TURBO)) {
        //�I�v�V������������
        if (pVbPlay->isBeingPressed(VB_UP)) {
            pKuroko->addRzMvAng(angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_DOWN)) {
            pKuroko->addRzMvAng(-angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_RIGHT)) {
            pKuroko->addRyMvAng(angVelo_Turn_);
        }
        if (pVbPlay->isBeingPressed(VB_LEFT)) {
            pKuroko->addRyMvAng(-angVelo_Turn_);
        }
    }

    //�I�v�V�����t���[���[�h�ւ̔��f
    if (pVbPlay->isBeingPressed(VB_OPTION)) {
        if (pVbPlay->isDoublePushedDown(VB_TURBO)) { //VB_OPTION + VB_TURBO�_�u���v�b�V��
            ignited_option_cnt_mode_ = true; //�I�v�V�������˃J�E���g���[�h����
        }
        if (ignited_option_cnt_mode_) {
            ignite_option_cnt_++; //�I�v�V�������ˉ\�܂ł̃J�E���g�A�b�v
        }
    } else {
        //VB_OPTION�����ƃ��Z�b�g
        ignited_option_cnt_mode_ = false;
        ignite_option_cnt_ = 0;
        was_ignited_option_ = false;
    }

    if ( ignite_option_cnt_ == (10 + (MyOptionController::now_option_num_ - no_)*10) ) { //�ŏ��̃I�v�V�����قǃJ�E���g�������K�v
        //���˓_��OK���̏���
        pOption_->pEffect_->pScaler_->beat(8, 4, 0, 4, 1); //�I�v�V�����Ղ�Ղ�A���˂�����OK�̃G�t�F�N�g
        was_ignited_option_ = true;
        //TODO:������SE?
    }
    //�_��OK�̎��� VB_OPTION + VB_TURBO�����Ŕ���
    if (pVbPlay->isReleasedUp(VB_TURBO)) {
        ignited_option_cnt_mode_ = false; //VB_TURBON�����ƃ��Z�b�g
        ignite_option_cnt_ = 0;
        if (pVbPlay->isBeingPressed(VB_OPTION) && was_ignited_option_) { //�_��OK������
            was_ignited_option_ = false;

            is_free_from_myship_mode_ = true;
            is_handle_move_mode_ = true;
            pAxsMver_->setZeroVxyzMvVelo();
            pAxsMver_->setZeroVxyzMvAcce();
            if (pOption_->isActive()) {
                EffectTurbo002* pTurbo002 = dispatchFromCommon(EffectTurbo002);
                if (pTurbo002) {
                    pTurbo002->positionAs(pOption_);
                }
            }
        }
    }

    if (is_free_from_myship_mode_) {
        if (pVbPlay->isBeingPressed(VB_OPTION)){
            if (is_handle_move_mode_) {
                //�I�v�V�����̍L����p���A�I�v�V�����ړ����x�ƁA���񔼌a�������x�Ƀx�N�g�������B
                //���̂����̃I�v�V�����ړ����x�݂̂�ݒ�B
                pKuroko->setMvVelo(ANG_COS(pOption_->angExpanse_) * veloOptionsMv_);
                //���񔼌a�������x�̏�����MyOption�N���X�ōs���B
            } else {
                //�I�v�V�����t���[���[�h����������Ă�
            }
        } else  {
            is_handle_move_mode_ = false; //VB_OPTION�����Ɖ���
            pKuroko->setMvVelo(0);
            //VB_OPTION �����Ɩ��֌W�� �t���[�Y�I�v�V�����̂�[�Ȋ����ɂȂ�
            const GgafDxGeoElem* const pGeoMyShipPrev = pMyShip->pRing_MyShipGeoHistory2_->getPrev();
            _x += (pMyShip->_x - pGeoMyShipPrev->x);
            _y += (pMyShip->_y - pGeoMyShipPrev->y);
            _z += (pMyShip->_z - pGeoMyShipPrev->z);
        }
    } else {
        const GgafDxGeoElem* const pGeoMyShipTrace = pMyShip->pRing_MyShipGeoHistory4OptCtrler_->getPrev(MyOptionController::o2o_*(no_+1));
        coord tx = pMyShip->_x_local + pGeoMyShipTrace->x;
        coord ty = pMyShip->_y_local + pGeoMyShipTrace->y;
        coord tz = pMyShip->_z_local + pGeoMyShipTrace->z;
        //(tx, ty, tz)�͎��@�̐�΍��W�����ɓ����B
        //VB_OPTION �������́ApRing_MyShipGeoHistory4OptCtrler_ �ɗ����͒ǉ����ꂸ�A
        //(_x_local, _y_local, _z_local) �̂ݍX�V����A�t���[�Y�I�v�V�����̓����ƂȂ�B
        //�Ȃ�ł��Y�ꂽ�� MyShip::processBehavior() ���̃R�����g������

        if (return_to_default_position_seq_) {
            pMyShip->trace_delay_count_ = TRACE_DELAY_WAIT_FRAME; //�g���[�X�ێ�����������
            //���̈ʒu��
            pAxsMver_->setVxyzMvAcce( tx - (_x + pAxsMver_->_velo_vx_mv*6),
                                      ty - (_y + pAxsMver_->_velo_vy_mv*6),
                                      tz - (_z + pAxsMver_->_velo_vz_mv*6) );
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
                return_to_default_position_seq_ = false;
            }

        } else {
            position(tx, ty, tz); //�ʏ�̃c�C���r�[���g�g���[�X
        }
    }

//    //�M�Y��
//    pDirectionVector_->positionAs(this);
//    pDirectionVector_->getKuroko()->setRzRyMvAng(pKuroko->_ang_rz_mv, pKuroko->_ang_ry_mv);

    pKuroko->behave();
    pAxsMver_->behave();

    pRing_OptCtrlGeoHistory_->next()->set(this);
}


void MyOptionController::setNumOption(int prm_num) {
    const MyShipScene* const pMyShipScene = P_MYSHIP_SCENE;
    MyOptionController::now_option_num_ = prm_num;
    for (int i = 0; i < MyOptionController::max_option_num_; i++) {
        if (i >= MyOptionController::now_option_num_) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->inactivate();
        }
        if (i < MyOptionController::now_option_num_) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->activate();
        }
    }
}
void MyOptionController::adjustDefaltAngPosition(frame prm_spent_frame) {
    const MyShipScene* const pMyShipScene = P_MYSHIP_SCENE;
    if (MyOptionController::now_option_num_ <= 4) {
        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/MyOptionController::now_option_num_)*i,prm_spent_frame);
        }
    } else if (MyOptionController::now_option_num_ > 4) {
        for (int i = 0; i < 4; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/4)*i, prm_spent_frame);
        }
        for (int i = 4; i < MyOptionController::now_option_num_; i++) {
            pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/(MyOptionController::now_option_num_-4))*(i-4), prm_spent_frame);
        }
    }
}

void MyOptionController::adjustDefaltAngPosition(frame prm_spent_frame, int prm_start_opt_no, int prm_end_opt_no) {
    const MyShipScene* const pMyShipScene = P_MYSHIP_SCENE;
    if (MyOptionController::now_option_num_ <= 4) {
        for (int i = 0; i < MyOptionController::now_option_num_; i++) {
            if (prm_start_opt_no <= i && i <= prm_end_opt_no) {
                pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/MyOptionController::now_option_num_)*i,prm_spent_frame);
            }
        }
    } else if (MyOptionController::now_option_num_ > 4) {
        for (int i = 0; i < 4; i++) {
            if (prm_start_opt_no <= i && i <= prm_end_opt_no) {
                pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/4)*i, prm_spent_frame);
            }
        }
        for (int i = 4; i < MyOptionController::now_option_num_; i++) {
            if (prm_start_opt_no <= i && i <= prm_end_opt_no) {
                pMyShipScene->papOptionCtrler_[i]->pOption_->adjustAngPosition((D360ANG/(MyOptionController::now_option_num_-4))*(i-4), prm_spent_frame);
            }
        }
    }
}

MyOptionController::~MyOptionController() {
    GGAF_DELETE(pAxsMver_);
    GGAF_DELETE(pRing_OptCtrlGeoHistory_);
}

