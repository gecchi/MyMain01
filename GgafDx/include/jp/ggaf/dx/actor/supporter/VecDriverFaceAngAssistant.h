#ifndef GGAF_DX_VECDRIVERFACEANGASSISTANT_H_
#define GGAF_DX_VECDRIVERFACEANGASSISTANT_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/AccelerationValue.hpp"

namespace GgafDx {

/**
 * �͎Ԃ̏���B .
 * �t��(�͎�)�̎���]���p�p���x�̕⍲���s���܂��B
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class VecDriverFaceAngAssistant : public GgafCore::Object {
    friend class VecDriver;

private:
    struct Twist {
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

    /** [r]�t�� */
    VecDriver* const _pMaster;
    GgafCore::AccelerationValue<int> _smthFaceAng[3];
    /** �c�C�X�g��� */
    Twist _tw[3];

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
    explicit VecDriverFaceAngAssistant(VecDriver* prm_pMaster);


    /**
     * ����]���p�����炩�ɉ�]����V�[�N�G���X�����s(�p�����w��A���Ԏw��A�p���x�ϓ�) .
     * �p��]�ړ��ɔ�₳��鎞��(Te)��3�̃Z�N�V�����ɕ����A���̂悤�Ȋp���x����������I�ɍs���B<BR>
     * �E���� 0     �` ���� p1*Te �܂� �E�E�E ���݂̊p���x����g�b�v�p���x�܂ŉ�]���x������<BR>
     * �E���� p1*Te �` ���� p2*Te �܂� �E�E�E �g�b�v�X�s�[�h�œ����p���x�œ�����]<BR>
     * �E���� p2*Te �` ���� Te    �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�p���x�։�]���x������<BR>
     * �����}�Q��<BR>
     * <pre>
     *
     *    �p���x(��)
     *     ^
     *     |                         ��:�ڕW�ړ��p�i�����j    �E�E�E�����Fprm_distance
     *     |                        ��0:�����_�̊p���x        �E�E�E�����o�[�F_angvelo_face[prm_axis]
     *     |                        ��t:�g�b�v�p���x          �E�E�E�ϓ��A�v�Z�����
     *     |                        ��e:�ŏI���x              �E�E�E�����Fprm_end_angvelo
     *  ��t|....___________          Te:�ڕW���ԁi�t���[�����j�E�E�E�����Fprm_target_frames
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
     * @param prm_axis ��]���p��(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_distance �ڕW�p����(��)�i�����ɂ���]�����L��B���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnByDt(axis prm_axis,
                  angle prm_distance, int prm_target_frames,
                  float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                  bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̎���]���p(Z��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_rz_target ���B�ڕW��Z����]���p
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
     * �ڕW�̎���]���p(Y��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_ry_target ���B�ڕW��Y����]���p
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
     * �ڕW�̎���]���p(X��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_ry_target ���B�ڕW��X����]���p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void rollFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                           float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                           bool prm_zero_acc_end_flg);

    /**
     * �ڕW�̎���]���p�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_rz_target �ڕWZ����]���p
     * @param prm_ry_target �ڕWY����]���p
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
     * �ڕW�̎���]���p(Z��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���x�E�����w��A���ԕϓ�) .
     * �ړ�������3�̃Z�N�V����(��1,��2,��3)�ɕ����A���̂悤�Ȋp���x����������I�ɍs���B<BR>
     * �E�����p 0       �` �����p ��1         �܂� �E�E�E ���݂̃Ƒ��x����g�b�v�X�s�[�h�܂Ŋp����(or����)��]<BR>
     * �E�����p ��1     �` �����p ��1+��2     �܂� �E�E�E �g�b�v�X�s�[�h�œ����p��]<BR>
     * �E�����p ��1+��2 �` �����p ��1+��2+��3 �܂� �E�E�E �g�b�v�X�s�[�h����ŏI�X�s�[�h�֊p����(or����)��]<BR>
     * �����}�Q��<BR>
     * <pre>
     *    �p���x(��)
     *     ^
     *     |                        ��0:�����_�̊p���x        �E�E�E�����o�[�F_angvelo_face[prm_axis]
     *     |                        ��t:�g�b�v�p���x          �E�E�E�����Fprm_top_angvelo
     *     |                        ��e:�ŏI�p���x            �E�E�E�����Fprm_end_angvelo
     *     |       ��=��1+��2+��3    ��:�ڕW�ړ��p�i�����j    �E�E�E�����Fprm_distance
     *  ��t|....___________          p1:�g�b�v�p���x�ɒB����p�����ƂȂ�悤�ȁA�Ƃɑ΂��銄��
     *     |   /|         |�_            �܂�     ��1 = ��*p1 �ƂȂ�悤�� p1 (0.0�`1.0)    �E�E�E���� prm_p1
     *  ��e|../.|.........|..�_      p2:�������J�n�����ƂȂ�悤�ȁA�Ƒ΂��銄��
     *     | /  |         |    |         �܂� ��1+��2 = ��*p2 �ƂȂ�悤�� p2 (0.0�`1.0)    �E�E�E���� prm_p2
     *     |/   |         |    |     Te:��₳���K�v���ԁi�t���[�����j �E�E�E�ϓ��A�v�Z�����
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
    void turnByVd(
            axis prm_axis,
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

    void rollByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
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

    /**
     * ����]�̃c�C�X�g(���Ԏw��A�p���x�ϓ�) .
     * ������ turnByDt() ���J��Ԃ����s���A�c�C�X�g�̂悤�ȓ������s���B
     *
     * @param prm_axis �c�C�X�g��]���p��(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_ang_target1 �c�C�X�g���B�ڕW�P�̃A���O���l
     * @param prm_ang_target2 �c�C�X�g���B�ڕW�Q�̃A���O���p�l
     * @param prm_twist_num �c�C�X�g�񐔁i-1 �Ŗ����c�C�X�g�j
     * @param prm_first_way �c�C�X�g���B�ڕW�P���ŏ��Ƀ^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��A�ȍ~�̃c�C�X�g�͔��Ύ���ɉ�]���J��Ԃ��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames �c�C�X�g1��ɔ�₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_distance�̐����ɍ��킹����j
     * @param prm_zero_acc_end_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void twist(axis prm_axis, angle prm_ang_target1, angle prm_ang_target2, int prm_twist_num,
               int prm_first_way, int prm_target_frames,
               float prm_p1, float prm_p2, angvelo prm_end_angvelo,
               bool prm_zero_acc_end_flg);

    inline bool isTurning() const {
        if (_smthFaceAng[AXIS_X].isAccelerating() || _smthFaceAng[AXIS_Y].isAccelerating() || _smthFaceAng[AXIS_Z].isAccelerating()) {
            return true;
        } else {
            return false;
        }
    }

    inline void stopTurn() {
        _smthFaceAng[AXIS_X].stopAccelerating();
        _smthFaceAng[AXIS_Y].stopAccelerating();
        _smthFaceAng[AXIS_Z].stopAccelerating();
        _tw[AXIS_X].target_num = 0;
        _tw[AXIS_Y].target_num = 0;
        _tw[AXIS_Z].target_num = 0;
    }

    virtual ~VecDriverFaceAngAssistant();
};

}
#endif /*GGAF_DX_VECDRIVERFACEANGASSISTANT_H_*/

