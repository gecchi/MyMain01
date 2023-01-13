#ifndef MYSHIP_H_
#define MYSHIP_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultD3DXMeshActor.h"

#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

//#define MY_SHIP_VREATH_COST (500)
//���ċz�� 1000000/500/60 = ��33.3�b�Ŏ���

/** ���t���[������Vreath */
#define MY_SHIP_VREATH_COST (5)
//���ċz�� 10000/5/60 = ��33.3�b�Ŏ���

/** �ő�MP */
#define MY_SHIP_MAX_MP   (500000)
/** ����MP */
#define MY_SHIP_START_MP (500000)
/** ���@�̈ړ�����~���Ă��A�g���[�X�ȏ�Ԃ��ێ��ł���t���[���� */
#define TRACE_DELAY_WAIT_FRAME (0x7fffffff)

#define MYSHIP_SHOT_MATRIX (7)
/** �ő啪�g�� */
#define MAX_BUNSHIN_NUM (10)
/** �P�I�v�V����������̍ő�\���b�N�I���� */
#define MAX_LOCKON_NUM (8)
/**
 * ���@�N���X
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
class MyShip : public VvMyActor<GgafLib::DefaultD3DXMeshActor> {
//class MyShip : public GgafLib::DefaultMeshActor {
//class MyShip : public GgafLib::CubeMapMeshActor {
//class MyShip : public GgafLib::DefaultD3DXAniMeshActor {
public:
    enum Switch {
        SW_ADD = 1,
        SW_NOP = 0,
        SW_SUB = -1
    };
public:
    /** �ړ�Y���W��� */
    static coord lim_y_top_;
    /** �ړ�Y���W���� */
    static coord lim_y_bottom_;
    /** �ړ�X���W��� */
    static coord lim_x_infront_;
    /** �ړ�X���W���� */
    static coord lim_x_behaind_;
    /** �ړ�Z���W��� */
    static coord lim_z_left_;
    /** �ړ�Z���W���� */
    static coord lim_z_right_;

    static uint32_t shot2_matrix_[4][MYSHIP_SHOT_MATRIX];
    static uint32_t shot3_matrix_[2][MYSHIP_SHOT_MATRIX];

    angle senakai_[3*3*3];
    angle* pSenakai_;

    /** [r]���b�N�I���R���g���[���[ */
    MyLockonController* pLockonCtrler_;
    /** [r]�����R���g���[���[ */
    MyTorpedoController* pTorpedoCtrler_;

    /** ���݈ړ����p */
    dir26 mv_way_;
    /** ���݈ړ����p��X������ */
    int mv_way_sgn_x_;
    /** ���݈ړ����p��Y������ */
    int mv_way_sgn_y_;
    /** ���݈ړ����p��Z������ */
    int mv_way_sgn_z_;
    /** �O��ړ����p */
    dir26 prev_way_;
    /** �ړ����p�ɕω����������ꍇ true �ƂȂ� */
    bool is_just_change_mv_way_;

    /** �ړ��X�s�[�h���x���ɑ�������ړ��X�s�[�h */
    velo mv_speed_;

    velo veloTurboTop_;
    velo veloTurboBottom_;

    /** Turbo�ړ��J�n���̈ړ����x�̏����x */
    velo veloBeginMT_; //Move Velo when I Begin To Move with Turbo
    //Z�������ޏꍇ�A���܂����̒l����v�Z���悤�iZ���̈ړ����x�͐����ŊǗ����Ă邽�߁j

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ��J�n����X����]�p���x�̏����x */
    angvelo angRxVelo_BeginMZ_; //Rotation axisX angle Velo when I Begin To Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�ړ�����X����]�p���x�̊p�����x */
    angacce angRxAcce_MZ_; //Rotation axisX angle Acce while I Move Z
    //���̏ꍇ�͐��A��O�̏ꍇ�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�ֈړ�����X����]�p���x�̏���p���x */
    angvelo angRxTopVelo_MZ_; //Rotation axisX Top angle Velo while I Move Z
    //�����p���x�͂���� -1 ���悸��

    /** ��(+Z)���͎�O(-Z)�֒ʏ�Z�ړ�����X����]�p�̒�~�p�x */
    angle angRxStop_MZ_; //Rotation axisX Stop angle while I Move Z


    /** ��(+Y)���͉�(-Y)��Turbo�ړ��J�n����Z����]�p���x�̏����x */
    angvelo angRxVelo_BeginMZT_; //Rotation axisX angle Velo when I Begin To Move Z with Turbo
    //��̏ꍇ�͐��A���̏ꍇ�͂���� -1 ���悸��

    GgafCore::ActorDepository* pDepo_MyShots001_;
    GgafCore::ActorDepository* pDepo_MySnipeShots001_;
    GgafLib::LaserChipDepository* pLaserChipDepo_;

    EffectTurbo001* pEffectTurbo001_;
    MyMagicEnergyCore* pMyMagicEnergyCore_;
//    //debug ---->
//    GgafCore::ActorDepository* pDepo_TestGuShot_;
//    GgafCore::ActorDepository* pDepo_TestChokiShot_;
//    GgafCore::ActorDepository* pDepo_TestPaShot_;
//    GgafCore::ActorDepository* pDepo_TestNomalShot_;
//    //<---- debug


    /** �\�t�g�A�˔������ł��邩�ۂ� */
    bool is_being_soft_rapidshot_;

    /** �\�t�g�A�˂������J�n���Ă���̔��ː��J�E���g���v */
    uint32_t soft_rapidshot_shot_count_;
    /** �\�t�g�A�˂������J�n���Ă���̃v�b�V���J�E���g */
    int soft_rapidshot_push_cnt_;

    /** �P�v�b�V�����̃\�t�g�A�ˊJ�n����̌o�߃t���[���� */
    frame soft_rapidshot_frames_in_one_push;
    /** �P�v�b�V�����̃\�t�g�A�ˊJ�n����̔��ː��J�E���g */
    int soft_rapidshot_shot_count_in_one_push_;

    /** �V���b�g�����������t���[���̂� true �ɂȂ� */
    bool is_just_shot_;
    /** �V���b�g���擪�̈ꔭ�ڂ̃X�i�C�v�V���b�g���ۂ��A�X�i�C�v�V���b�g�̎��̂� true �ɂȂ� */
    bool is_snipe_shot_;

    /** ���[�U�[���˒����ǂ��� */
    bool is_shooting_laser_;
    /** ���[�U�[���ˉ\���ǂ��� */
    bool can_shoot_laser_;
    /** SHOT�{�^���������ςȂ��o�߃t���[�����i���[�U�[���ˊJ�n����̂��߁j */
    frame frame_shot_pressed_;
    /** �V�[���˓������ǂ��� */
    bool is_diving_;

    /** ����� */
    bool can_control_;

    /** �������X���� */
    int blown_veloX_;
    /** �������Y���� */
    int blown_veloY_;
    /** �������Z���� */
    int blown_veloZ_;

    /** ������ь����� */
    double r_blown_velo_decay_;

    /** MP */
    int mp_;

    int invincible_frames_;

    /** ���@���[�^�[ */
    MagicMeter* pMagicMeter_;
    /** �I�v�V�����g���[�X�����@��~�̍ۂɁA�����I�ɃI�v�V�����������߂�܂ł̗P�\�ɂ���~��true */
    bool is_trace_waiting_;
    /** is_trace_waiting_�̃t���O��؂�ւ��邽�߂̎��ԃJ�E���^ */
    frame trace_delay_count_;


    int shot_level_;

    /** SHOT1+SHOT2���������̕���̃J�E���^�[ */
    int center_wepon_launch_count_;


    coord prev_x_;
    coord prev_y_;
    coord prev_z_;
    coord mv_offset_x_;
    coord mv_offset_y_;
    coord mv_offset_z_;
    bool is_move_;

public:
    MyShip(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;
    void onInactive() override;
    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    /**
     * �ړ������̏�Ԃ��X�V .
     * ���͕����ɉ����� mv_way_, mv_way_sgn_x_, mv_way_sgn_y_, mv_way_sgn_z_,is_just_change_mv_way_�̏�Ԃ��X�V���܂� .
     */
    void updateMoveWay();
    dir26 getMoveWay() {
        return mv_way_;
    }

    void setMoveSpeed(velo prm_speed_velo);

    void moveNomal();

    void moveTurbo();


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    /**
     * ���@������� .
     * @param prm_blown_veloX X����������ё��x
     * @param prm_blown_veloY Y����������ё��x
     * @param prm_blown_veloZ Z����������ё��x
     * @param prm_r_blown_velo_attenuate ������ь�����
     */
    void setBlownVelo(velo prm_blown_veloX, velo prm_blown_veloY, velo prm_blown_veloZ, double prm_r_blown_velo_attenuate);
    /**
     * ���@���G�ݒ� .
     * @param prm_frames ���G����(�t���[��)
     */
    void setInvincibleFrames(int prm_frames);

    /**
     * ���@������\�ȏ�Ԃ��ǂ��� �B
     * @return
     */
    inline bool canControl() {
        return can_control_;
    }

    virtual ~MyShip();

};

}
#endif /*MYSHIP_H_*/

