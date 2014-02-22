#ifndef GGAFDXCORE_GGAFDXKUROKOHELPERB_H_
#define GGAFDXCORE_GGAFDXKUROKOHELPERB_H_
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"

namespace GgafDxCore {

/**
 * ���߂̏���B .
 * �t��(����)�̎���]���p�p���x�̕⍲���s���܂��B
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoHelperB : public GgafCore::GgafObject {

public:
    /** [r]�t�� */
    GgafDxKuroko* _pMaster;
    GgafCore::GgafValueAccelerator<int> _smthFaceAng[3];
public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pMaster  �t��
     */
    GgafDxKurokoHelperB(GgafDxKuroko* prm_pMaster);


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
     *     |                         ��:�ڕW�ړ��p�i�����j    �E�E�E���� prm_angular_distance
     *     |                        ��0:�����_�̊p���x        �E�E�E_angveloFace[prm_axis]
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
     * @param prm_axis ��]���p��(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_angular_distance �ڕW�p����(��)�i�����ɂ���]�����L��B���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_angular_distance�̐����ɍ��킹����j
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnFaceAngByDt(axis prm_axis,
                             angle prm_angular_distance, int prm_target_frames,
                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                             bool prm_endacc_flg);

    /**
     * �ڕW�̎���]���p(Z��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_rz_target ���B�ڕW��Z����]���p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_angular_distance�̐����ɍ��킹����j
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzFaceAngByDtTo(angle prm_ang_rz_target, int prm_way, int prm_target_frames,
                                 float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                 bool prm_endacc_flg);

    /**
     * �ڕW�̎���]���p(Y��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_rt_target ���B�ڕW��Y����]���p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_angular_distance�̐����ɍ��킹����j
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRyFaceAngByDtTo(angle prm_ang_rt_target, int prm_way, int prm_target_frames,
                             float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                             bool prm_endacc_flg);
    /**
     * �ڕW�̎���]���p(X��)�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_rt_target ���B�ڕW��X����]���p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e) �i�����Ő�����prm_angular_distance�̐����ɍ��킹����j
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void spinRxFaceAngByDtTo(angle prm_ang_rx_target, int prm_way, int prm_target_frames,
                                     float prm_p1, float prm_p2, angvelo prm_end_angvelo,
                                     bool prm_endacc_flg);

    /**
     * �ڕW�̎���]���p�֊��炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_ang_rz_target �ڕWZ����]���p
     * @param prm_ang_ry_target �ڕWY����]���p
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     *                         true: ������ prm_ang_rz_target, prm_ang_ry_target �܂ł̋����ƁA<BR>
     *                               �����������Ӗ����������g�� RzRy �܂ł̋���������o���A<BR>
     *                               ���B�t���[�����̏��Ȃ����� RzRy �̑g�ݍ��킹�������̗p����B<BR>
     *                               ���]�̕����ɍŒZ�t���[���Ń^�[�Q�b�g���邪�A������ _angMvRz, _angMvRy ��<BR>
     *                               �����̃^�[�Q�b�g�A���O���l�ƈ�v���Ȃ���������Ȃ��B(�p�����قȂ�\���L��)<BR>
     *                               (���ӁF�ɒnY����]�����邽�߁A�ŒZ�t���[���͕K�������ŒZ�����ɂ��炸)<BR>
     *                         false:������ prm_ang_rz_target, prm_ang_ry_target �����̂܂܃^�[�Q�[�g�Ƃ���B<BR>
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e)
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnRzRyFaceAngByDtTo(
            angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

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
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnFaceAngByDtTwd(
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    /**
     * �ڕW�̃A�N�^�[�̍��W�Ɍ����悤�ɁA���炩�ɉ�]����V�[�N�G���X�����s(���Ԏw��A�p���x�ϓ�) .
     * @param prm_pActor_Target �ڕW�A�N�^�[
     * @param prm_way �^�[�Q�b�g���邽�߂́A��]�����w���B���̂����ꂩ���w��B<BR>
     *                TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO/TURN_ANTICLOSE_TO
     * @param prm_optimize_ang �^�[�Q�b�g�A���O�����œK�����邩�ǂ������w��B<BR>
     * @param prm_target_frames ��₷����(Te)(�t���[�������w��A���̐��͕s��)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��(p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��(p2)
     * @param prm_end_angvelo �ڕW���B���̍ŏI�p���x(��e)
     * @param prm_endacc_flg true:�ڕW�ړ������ɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnFaceAngByDtTwd(
            GgafDxGeometricActor* prm_pActor_Target, int prm_way, bool prm_optimize_ang,
            int prm_target_frames,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

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
     * @param prm_angular_distance �ڕW�p����(��)�i�����ɂ���]�����L��B���FTURN_COUNTERCLOCKWISE�A���FTURN_CLOCKWISE�j
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA��]�����p(��)�ɑ΂��銄���B(��1 = ��*prm_p1)
     * @param prm_p2 �p��]�̌������J�n�p�ƂȂ�悤�ȁA��]�����p(��)�ɑ΂��銄�� (��1+��2 = ��*p2)
     * @param prm_end_angvelo �ŏI�p���x(��e)
     * @param prm_endacc_flg true:�ڕW���ԂɒB�����ۂɊp�����x���O�ɋ����ݒ�/false:�p�����x�͂��̂܂܂ɂ��Ă���
     */
    void turnFaceAngByVd(
            axis prm_axis,
            angvelo prm_top_angvelo, angle prm_angular_distance,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnRzFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_rz_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnRyFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_ry_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void spinRxFaceAngByVdTo(
            angvelo prm_top_angvelo, angle prm_ang_rx_target, int prm_way,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);


    void turnRzRyFaceAngByVdTo(
            angvelo prm_top_angvelo,
            angle prm_ang_rz_target, angle prm_ang_ry_target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnFaceAngByVdTwd(
            angvelo prm_top_angvelo,
            coord prm_tx, coord prm_ty, coord prm_tz, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    void turnFaceAngByVdTwd(
            angvelo prm_top_angvelo,
            GgafDxGeometricActor* prm_pActor_Target, int prm_way, bool prm_optimize_ang,
            float prm_p1, float prm_p2, angvelo prm_end_angvelo,
            bool prm_endacc_flg);

    inline bool isTurningFaceAng() {
        if (_smthFaceAng[AXIS_X]._prm._flg || _smthFaceAng[AXIS_Y]._prm._flg || _smthFaceAng[AXIS_Z]._prm._flg) {
            return true;
        } else {
            return false;
        }
    }

    inline void stopTurnFaceAng() {
        _smthFaceAng[AXIS_X]._prm._flg = false;
        _smthFaceAng[AXIS_Y]._prm._flg = false;
        _smthFaceAng[AXIS_Z]._prm._flg = false;
    }

    /**
     * ���߂̏��肪�U�镑�� .
     * ���肪�A�t���ɂ��낢��ݒ���s���܂��̂ŁA�t�����U�镑��(behave())�O�Ɏ��s���܂��傤�B
     */
    virtual void behave();

    virtual ~GgafDxKurokoHelperB();
};

}
#endif /*GGAFDXCORE_GGAFDXKUROKOHELPERB_H_*/

