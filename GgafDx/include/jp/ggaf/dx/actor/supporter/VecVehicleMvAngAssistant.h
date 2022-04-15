#ifndef GGAF_DX_VECVEHICLEMVANGASSISTANT_H_
#define GGAF_DX_VECVEHICLEMVANGASSISTANT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"

namespace GgafDx {

/**
 * �͎Ԃ̏���C .
 * �t��(�͎�)�̈ړ����p�p���x�̕⍲���s���܂��B
 * @version 1.00
 * @since 2013/12/10
 * @author Masatoshi Tsuge
 */
class VecVehicleMvAngAssistant : public GgafCore::Object {
    friend class VecVehicle;

private:

    struct Pendulum {
        int count;
        int target_num;
        angle target[10];
        int loop_num;
        int way;
        frame target_frames;
        double p1;
        double p2;
        angvelo end_angvelo;
        bool zero_acc_end_flg;
    };

    /** �U��q��� */
    Pendulum _pnd_rz;
    Pendulum _pnd_ry;
    /** [r]�t�� */
    VecVehicle* const _pMaster;
    GgafCore::TrapezoidalVeloValue<int> _smthMvRzAng;
    GgafCore::TrapezoidalVeloValue<int> _smthMvRyAng;

    /**
     * �͎Ԃ̏��肪�U�镑�� .
     * �t�����U�镑��(behave())���ɁA�����ŌĂяo�����̂ŋC�ɂ��Ȃ��ł悢�ł��B
     */
     virtual void behave();

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pMaster  �t��
     */
    explicit VecVehicleMvAngAssistant(VecVehicle* prm_pMaster);


    /**
     * �ړ����p�����炩�ɉ�]����V�[�N�G���X�����s(�p�����w��A���Ԏw��A�p���x�ϓ�) .
     * �p��]�ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�Ȋp���x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̊p���x����g�b�v�p���x�܂ŉ�]���x������<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����p���x�œ�����]<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�p���x�։�]���x������<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    �p���x(��)
     *     ^
     *     |                         ��:�ڕW�ړ��p�i�����j    �E�E�E���� prm_distance
     *     |                        ��0:�����_�̊p���x        �E�E�E_pMaster->_angvelo_rz_mv
     *     |                        ��t:�g�b�v�p���x          �E�E�E�ϓ��A�v�Z�����
     *     |                        ��e:�ŏI���x              �E�E�E���� prm_end_angvelo
     *  ��t|....___________          Te:�ڕW���ԁi�t���[�����j�E�E�E���� prm_target_frames
     *     |   /:         :�_        p1:�g�b�v�p���x�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄���E�E�E���� prm_p1
     *  ��e|../.:.........:..�_      p2:��]�̌������J�n���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄���E�E�E���� prm_p2
     *     | /  :         :    |
     *     |/   :         :    |
     *  ��0|    :    ��   :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * @param prm_distance �ڕW�p����(��)�i�����ɂ���]�����L��B���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzByDt(angle prm_distance, int prm_target_frames,
                    float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                    bool prm_zero_acc_end_flg);

    void turnRyByDt(angle prm_distance, int prm_target_frames,
                    float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                    bool prm_zero_acc_end_flg);
    /**
     * �ڕW�̈ړ����p(Z��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_rz_target ���B�ڕW��Z�ړ����p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzByDtTo(angle prm_rz_target, int prm_way, int prm_target_frames,
                      float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                      bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̈ړ����p(Y��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_ry_target ���B�ڕW��Y�ړ����p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRyByDtTo(angle prm_ang_ry_target, int prm_way, int prm_target_frames,
                      float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                      bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̈ړ����p�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_rz_target �ڕWZ�ړ����p
     * @param prm_ry_target �ڕWY�ړ����p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_rz_target, prm_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _rz_mv, _ry_mv ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_rz_target, prm_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzRyByDtTo(
            angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̍��W�Ɍ����悤�ɁA���炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnByDtTwd(
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̃A�N�^�[�̍��W�Ɍ����悤�ɁA���炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_pActor_target �ڕW�A�N�^�[
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e)
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnByDtTwd(
            GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̈ړ����p(Z��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���x�E�����w��A���ԕϓ�) .
     * �ړ�������3�̃Z�N�V����(��1,��2,��3)�ɕ����A���̂悤�Ȋp���x����������I�ɍs���B<BR>
     * �E�����p 0       �` �����p ��1         �܂� �E�E�E ���݂̃Ƒ��x����g�b�v�X�s�[�h�܂Ŋp����(or����)��]<BR>
     * �E�����p ��1     �` �����p ��1+��2     �܂� �E�E�E �g�b�v�X�s�[�h�œ����p��]<BR>
     * �E�����p ��1+��2 �` �����p ��1+��2+��3 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֊p����(or����)��]<BR>
     * �����}�Q��<BR>
     * <pre>
     *    �p���x(��)
     *     ^
     *     |                        ��0:�����_�̊p���x
     *     |                        ��t:�g�b�v�p���x
     *     |                        ��e:�ŏI�p���x
     *     |       ��=��1+��2+��3    ��:�ڕW��]�����p
     *  ��t|....___________          p1:�g�b�v�p���x�ɒB����p�����ƂȂ�悤�ȁA�Ƃɑ΂��銄��
     *     |   /|         |�_            �܂�     ��1 = ��*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
     *  ��e|../.|.........|..�_      p2:�������J�n�����ƂȂ�悤�ȁA�Ƒ΂��銄��
     *     | /  |         |    |         �܂� ��1+��2 = ��*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
     *     |/   |         |    |     Te:��₳���K�v���ԁi�t���[�����j
     *  ��0|��1 |   ��2   |��3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> ����(t:�t���[��)
     *   0 |                  Te
     *
     * </pre>
     * �g�b�v�X�s�[�h(��t)�A�ŏI�X�s�[�h(��e)�A�ڕW��]�����p(��)�A�y�� p1, p2 ���w�肷��B<BR>
     * ��₳��鎞��(Te)�͓����Ŏ����v�����肳���B<BR>
     * <BR>
     * @param prm_axis ��]���p��(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_top_angvelo �g�b�v�p���x(��t)
     * @param prm_distance �ڕW�p����(��)�i�����ɂ���]�����L��B���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA��]�����p(��)�ɑ΂��銄���B(��1 = ��*prm_p1)
     * @param prm_p2 �p��]�̌������J�n�p�ƂȂ�悤�ȁA��]�����p(��)�ɑ΂��銄�� (��1+��2 = ��*p2)
     * @param prm_end_angvelo �ŏI�p���x(��e)
     * @param prm_zero_acc_end_flg true:�ڕW���ԂɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzByVd(
            angvelo prm_top_angvelo, angle prm_distance,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnRyByVd(
            angvelo prm_top_angvelo, angle prm_distance,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnRzByVdTo(
            angvelo prm_top_angvelo, angle prm_rz_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnRyByVdTo(
            angvelo prm_top_angvelo, angle prm_ry_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnRzRyByVdTo(
            angvelo prm_top_angvelo,
            angle prm_rz_target, angle prm_ry_target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnByVdTwd(
            angvelo prm_top_angvelo,
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);

    void turnByVdTwd(
            angvelo prm_top_angvelo,
            GeometricActor* prm_pActor_target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_zero_acc_end_flg);



    void turnRzPendulum(coord prm_target_rz1, coord prm_target_rz2,
                        int prm_twist_num,
                        int prm_first_way, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg);

    void turnRyPendulum(coord prm_target_ry1, coord prm_target_ry2,
                        int prm_twist_num,
                        int prm_first_way, int prm_target_frames,
                        float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                        bool prm_zero_acc_end_flg);


    inline bool isTurning() const {
        return (_smthMvRzAng.isTransitioning() || _smthMvRyAng.isTransitioning()) ? true : false;
    }

    inline void stopTurning() {
        _smthMvRzAng.stopTransitioning();
        _smthMvRyAng.stopTransitioning();
    }

    virtual ~VecVehicleMvAngAssistant();
};

}
#endif /*GGAF_DX_VECVEHICLEMVANGASSISTANT_H_*/

