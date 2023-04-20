#ifndef GGAF_DX_COORDVEHICLEASSISTANT_H_
#define GGAF_DX_COORDVEHICLEASSISTANT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * ����(���s�ړ��x��) �̏���A .
 * �t��(����(���s�ړ��x��) )�̕⍲���s���܂��B
 * @version 1.00
 * @since 2013/12/16
 * @author Masatoshi Tsuge
 */
class CoordVehicleAssistantA : public GgafCore::Object {
    friend class CoordVehicle;

private:
    /** [r]�t�� */
    CoordVehicle* _pMaster;
    /** X�������������u */
    GgafCore::TrapezoidalVeloValue<coord> _smthVxMv;
    /** Y�������������u */
    GgafCore::TrapezoidalVeloValue<coord> _smthVyMv;
    /** Z�������������u */
    GgafCore::TrapezoidalVeloValue<coord> _smthVzMv;

    virtual void behave();

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pMaster  �t��
     */
    explicit CoordVehicleAssistantA(CoordVehicle* prm_pMaster);

    /**
     * X�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * �ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    ���x(v)
     *     ^
     *     |
     *     |                         V0:�����_�̑��x
     *     |                         Ve:�ŏI���x
     *     |                          D:�ڕW�ړ�����
     *   Vt|....___________          Te:�ڕW���ԁi�t���[�����j
     *     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(0.0�`1.0)
     *     | /  :         :    |     Vt:�����E���Ԃ��瓱���������g�b�v�X�s�[�h
     *     |/   :         :    |
     *   V0|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * �ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A���B�ڕW����(Te)�A�y�� p1, p2 ���w�肷��B<BR>
     * �g�b�v�X�s�[�h(Vt)�͓����Ŏ����v�Z�����肳���B<BR>
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * Y�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * slideVxMvByDt() �̐����Q�ƁB
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVyMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * Z�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * slideVxMvByDt() �̐����Q�ƁB
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVzMvByDt(coord prm_target_distance, int prm_target_frames,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    /**
     * X,Y,Z�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * ������ slideVxMvByDt(), slideVyMvByDt(), slideVzMvByDt() �����s����B
     * �����̈��������ς��Ăق��̈����͋��ʁB
     * @param prm_x_target_distance X�������ڕW�ړ�����(Dx)
     * @param prm_y_target_distance Y�������ڕW�ړ�����(Dy)
     * @param prm_z_target_distance Z�������ڕW�ړ�����(Dz)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxyzMvByDt(coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         int prm_target_frames,
                         double prm_p1, double prm_p2, velo prm_end_velo,
                         bool prm_zero_acc_end_flg) {
        slideVxMvByDt(prm_x_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
        slideVyMvByDt(prm_y_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
        slideVzMvByDt(prm_z_target_distance, prm_target_frames,
                      prm_p1, prm_p2, prm_end_velo,
                      prm_zero_acc_end_flg);
    }

    /**
     * X,Y,Z�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
     * ������ slideVxMvByDt(), slideVyMvByDt(), slideVzMvByDt() �����s����B
     * ��₷����(prm_target_frames),prm_zero_acc_end_flg�̂݋��ʁB
     * @param prm_x_target_distance X�������ڕW�ړ�����(Dx)
     * @param prm_y_target_distance Y�������ڕW�ړ�����(Dy)
     * @param prm_z_target_distance Z�������ڕW�ړ�����(Dz)
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_x_p1 X�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_x_p2 X�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_x_end_velo X�������ŏI�X�s�[�h(Ve)
     * @param prm_y_p1 Y�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_y_p2 Y�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_y_end_velo Y�������ŏI�X�s�[�h(Ve)
     * @param prm_z_p1 Z�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_z_p2 Z�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_z_end_velo Z�������ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxyzMvByDt(coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         int prm_target_frames,
                         double prm_x_p1, double prm_x_p2, velo prm_x_end_velo,
                         double prm_y_p1, double prm_y_p2, velo prm_y_end_velo,
                         double prm_z_p1, double prm_z_p2, velo prm_z_end_velo,
                         bool prm_zero_acc_end_flg) {
        slideVxMvByDt(prm_x_target_distance, prm_target_frames,
                      prm_x_p1, prm_x_p2, prm_x_end_velo,
                      prm_zero_acc_end_flg);
        slideVyMvByDt(prm_y_target_distance, prm_target_frames,
                      prm_y_p1, prm_y_p2, prm_y_end_velo,
                      prm_zero_acc_end_flg);
        slideVzMvByDt(prm_z_target_distance, prm_target_frames,
                      prm_z_p1, prm_z_p2, prm_z_end_velo,
                      prm_zero_acc_end_flg);


    }

    /**
     * X,Y,Z�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE����(�ڕW���W)�w��A���x�ϓ�) .
     * �ڕW���W���w��B�ړ������͓����v�Z�B���̑���slideVxyzMvByDt() �̐����Q�ƁB
     * @param prm_x_target X���������B�ڕW���W�l
     * @param prm_y_target Y���������B�ڕW���W�l
     * @param prm_z_target Z���������B�ڕW���W�l
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           int prm_target_frames,
                           double prm_p1, double prm_p2, velo prm_end_velo,
                           bool prm_zero_acc_end_flg);

    /**
     * X,Y,Z�������łȂ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE����(�ڕW���W)�w��A���x�ϓ�) .
     * �ڕW���W���w��B�ړ������͓����v�Z�B���̑���slideVxyzMvByDt() �̐����Q�ƁB
     * @param prm_x_target X���������B�ڕW���W�l
     * @param prm_y_target Y���������B�ڕW���W�l
     * @param prm_z_target Z���������B�ڕW���W�l
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_x_p1 X�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_x_p2 X�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_x_end_velo X�������ŏI�X�s�[�h(Ve)
     * @param prm_y_p1 Y�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_y_p2 Y�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_y_end_velo Y�������ŏI�X�s�[�h(Ve)
     * @param prm_z_p1 Z�������g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_z_p2 Z�������������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_z_end_velo Z�������ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxyzMvByDtTo(coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           int prm_target_frames,
                           double prm_x_p1, double prm_x_p2, velo prm_x_end_velo,
                           double prm_y_p1, double prm_y_p2, velo prm_y_end_velo,
                           double prm_z_p1, double prm_z_p2, velo prm_z_end_velo,
                           bool prm_zero_acc_end_flg);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���x�E�����w��A���ԕϓ�) .
     * �ړ�������3�̃Z�N�V����(d1,d2,d3)�ɕ����A���̂悤�ȑ��x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� d1       �܂� �E�E�E ���݂̑��x����g�b�v�X�s�[�h�܂ŉ���(or����)�ړ�<BR>
     * �E���� d1    �` ���� d1+d2    �܂� �E�E�E �g�b�v�X�s�[�h�œ����ړ�<BR>
     * �E���� d1+d2 �` ���� d1+d2+d3 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֌���(or����)�ړ�<BR>
     * �����}�Q��<BR>
     * <pre>
     *    ���x(v)
     *     ^
     *     |                         V0:�����_�̑��x
     *     |                         Vt:�g�b�v�X�s�[�h
     *     |                         Ve:�ŏI���x
     *     |         D=d1+d2+d3       D:�ڕW�ړ�����(D=d1+d2+d3)
     *   Vt|....___________          p1:�g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     |   /|         |�_            �܂�    d1 = D*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
     *   Ve|../.|.........|..�_      p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
     *     | /  |         |    |         �܂� d1+d2 = D*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
     *     |/   |         |    |     Te:��₳���K�v���ԁi�t���[�����j
     *   V0| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |                  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(Vt)�A�ŏI�X�s�[�h(Ve)�A�ڕW�ړ�����(D)�A�y�� p1, p2 ���w�肷��B<BR>
     * ��₳��鎞��(Te)�͓����Ŏ����v�����肳���B<BR>
     * <BR>
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄���B(d1 = D*prm_p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄�� (d1+d2 = D*p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve)
     * @param prm_zero_acc_end_flg true:�ڕW���ԂɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideVxMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVyMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVzMvByVd(velo prm_top_velo, coord prm_target_distance,
                       double prm_p1, double prm_p2, velo prm_end_velo,
                       bool prm_zero_acc_end_flg);

    void slideVxyzMvByVd(velo prm_top_velo,
                         coord prm_x_target_distance, coord prm_y_target_distance, coord prm_z_target_distance,
                         double prm_p1, double prm_p2, velo prm_end_velo,
                         bool prm_zero_acc_end_flg);

    void slideVxyzMvByVdTo(velo prm_top_velo,
                           coord prm_x_target, coord prm_y_target, coord prm_z_target,
                           double prm_p1, double prm_p2, velo prm_end_velo,
                           bool prm_zero_acc_end_flg);

    /**
     * �Ȃ߂炩�Ȉړ��V�[�N�G���X���쓮�����i���ӁF�ړ����Ă��邩�ۂ��ł͂Ȃ��j.
     * @return true:�쓮�� / false:�쓮���ł͂Ȃ�
     */
    bool isSliding() {
        if (_smthVxMv.isTransitioning() || _smthVyMv.isTransitioning() || _smthVzMv.isTransitioning()) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �Ȃ߂炩�Ȉړ��V�[�N�G���X���~�i���ӁF�ړ��i���x�j���~������Ƃ������͍s���Ă��Ȃ��j.
     */
    void stopSliding() {
        _smthVxMv.stopTransitioning();
        _smthVyMv.stopTransitioning();
        _smthVzMv.stopTransitioning();
    }

    virtual ~CoordVehicleAssistantA();
};

}
#endif /*GGAF_DX_COORDVEHICLEASSISTANT_H_*/

