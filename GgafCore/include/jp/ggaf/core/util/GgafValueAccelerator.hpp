#ifndef GGAFCORE_GGAFVALUEACCELERATOR_H_
#define GGAFCORE_GGAFVALUEACCELERATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * �����̒l�̉����� .
 * �����̒l���ȈՓI�Ƀk�����Ɗ��炩�ɕω�������B
 * @tparam VAL_TYPE �J�ڒl�̃f�[�^�^
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class GgafValueAccelerator : public GgafObject {

private:
    enum {
        ACCELERATE_ZERO_END = -9,        /** ������ 0 �̏ꍇ�̐i���萔�B                                                     */
        ACCELERATE_RECOVERY_BEGIN = 0,   /** �񕜃t�F�[�Y Ts �֌����Ẳ����x�ݒ�                                            */
        ACCELERATE_RECOVERING_to_Ts = 1, /** �񕜒�  �` Ts                                                                   */
        ACCELERATE_on_Ts = 2,            /** Ts�`T1 �� 0 �Ȃ�� ACCELERATE_T1_to_T2 �ցA�����łȂ���� ACCELERATE_acc_for_T1 */
        ACCELERATE_acc_for_T1 = 3,       /** T1 �֌����Ẳ����x�ݒ�                                                         */
        ACCELERATE_Ts_to_T1 = 4,         /** ������ Ts�`T1 �AT1�ɓ��B����΁AT2�֌����Ă̓����x�ݒ�                          */
        ACCELERATE_T1_to_T2 = 5,         /** ������ T1�`T2 �AT2�ɓ��B����΁ATe�֌����Ă̌����x�ݒ�                          */
        ACCELERATE_T2_to_Te = 6,         /** ������ T2�`Te �ATe�ɓ��B����ΏI���B���邢�͕␳�łP�t���[���ǉ�                */
        ACCELERATE_BACCHIRI = 7,         /** �c�����o�b�`�����킹�i�P�t���[���j                                              */
        ACCELERATE_DONE = -1,            /** �������������S�ɏI���������̐i���萔                                            */
    };

    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s����true */
    bool _is_accelerating;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
    bool _zero_acc_end_flg;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�g�b�v�X�s�[�h�i�����ړ������x�j */
    VAL_TYPE _top_velo;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�I�����̑��x */
    VAL_TYPE _end_velo;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ʒu���B�܂łɕK�v�Ȏ����̈ړ������i���̂݁B���̈ړ������Z�����ꍇ�̂�d�ۂ��������a�j */
    VAL_TYPE _target_distance;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ʒu�܂ł̒��������i�����L��j */
    VAL_TYPE _target_distance2;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ō��܂łɎ����ړ������ړ��������v�i���܂ł̈ړ����x�̐�Βl�̉��Z���v�j */
    VAL_TYPE _moved;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ō��܂ł̈ړ������̘a�i���܂ł̈ړ����x�i�������̂܂܂̉��Z���v�j */
    VAL_TYPE _moved2;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ňړ����x�����𔽓]����܂ł̐ݒ肳�ꂽ�񕜎������x */
    VAL_TYPE _acce_a0;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ړ������̐��� */
    int _target_sgn;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW���� */
    int  _frame_of_target;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̌o�ߎ��� */
    int  _spent_frames;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�p���x�̐������؂�ւ��|�C���g */
    double  _p0;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    double  _p1;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
    double  _p2;
    /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�̐i���� */
    int  _progress;

public:
    /** �����̒l */
    VAL_TYPE _t_value;
    /** �����̒l�̑��x */
    VAL_TYPE _t_velo;
    /** �����̒l�̉����x */
    VAL_TYPE _t_acce;

public:
    GgafValueAccelerator() {
        _is_accelerating = false;
        _zero_acc_end_flg = true;
        _top_velo = 0;
        _end_velo = 0;
        _target_distance = 0;
        _target_distance2 = 0;
        _moved = 0;
        _moved2 = 0;
        _acce_a0 = 0;
        _target_sgn = 1;
        _frame_of_target = 0;
        _spent_frames = 0;
        _p0 = 0;
        _p1 = 0;
        _p2 = 0;
        _progress = ACCELERATE_DONE;

        _t_value = 0;
        _t_velo = 0;
        _t_acce = 0;
    }

    void accelerateByDt(VAL_TYPE prm_target_value_distance,
                        frame prm_frame_of_target,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_zero_acc_end_flg) {
        //�ڕW���Ԏw��̏ꍇ
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_t_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //������0�Ȃ̂ŁA_frame_of_target ��~���ďI��
            _is_accelerating = true;
            _target_distance = 0;
            _target_distance2 = 0;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _p1 = 0;
            _p2 = 0;
            _top_velo = 0;
            _end_velo = prm_end_velo;
            _frame_of_target = prm_frame_of_target;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_ZERO_END; //�����Ȃ�I��
            return;
        }
        //_TRACE_(FUNC_NAME<<" COME!");
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance);
        //_TRACE_("prm_frame_of_target="<<prm_frame_of_target);
        //_TRACE_("prm_p1="<<prm_p1);
        //_TRACE_("prm_p2="<<prm_p2);
        //_TRACE_("prm_end_velo="<<prm_end_velo);
        //_TRACE_("prm_zero_acc_end_flg="<<prm_zero_acc_end_flg);

        if (sgn_W0 == 0 || s_d == sgn_W0) {  //��������v
            //���g�b�v�X�s�[�h(Vt) ���v�Z��
            //
            //    ���x(v)
            //     ^
            //     |                          D:�ڕW�ړ�����
            //     |                         V0:�����_�̑��x
            //     |                         Vt:�g�b�v�X�s�[�h
            //     |                         Ve:�ŏI���x
            //   Vt|....�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
            //     |   /:         :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
            //   Ve|../.:.........:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
            //     | /  :         :    |        (0.0 < p1 < p2 < 1.0)
            //     |/   :         :    |
            //   V0|    :    D    :    |
            //     |    :         :    |
            //   --+----+---------+----+-----> ����(t:�t���[��)
            //   0 |    T1        T2   Te
            //
            // �ړ�����D�́A���̑�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
            // D = (1/2)*(V0+Vt)*T1 + Vt*(T2-T1)  +  (1/2)*(Ve+Vt)*(Te-T2);
            // �����Vt�ɂ��ĉ���
            // Vt=-(T1*V0-Ve*T2-2*D+Te*Ve)/(T2-T1+Te)
            const double V0 = _t_velo;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double T1 = prm_frame_of_target*prm_p1;
            const double T2 = prm_frame_of_target*prm_p2;
            const double Te = prm_frame_of_target;
            const double D  = prm_target_value_distance;
            const double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);

            _is_accelerating = true;
            _target_distance = ABS(D);
            _target_distance2 = D;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _p1 = T1;
            _p2 = T2;
            _top_velo = Vt;
            _end_velo = Ve;
            _frame_of_target = Te;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_acc_for_T1;

        } else {
            //        ���x(v)
            //         ^
            //         |                                   D2-D1:�ڕW�ړ�����
            //         |                                      V0:�����_�̑��x
            //         |                                      Vt:�g�b�v�X�s�[�h
            //         |                                      Ve:�ŏI���x
            //       Vt|................�Q�Q�Q�Q�Q�Q          Te:�ڕW���ԁi�t���[�����j
            //         |               /:  |       :�_        p1:�g�b�v�X�s�[�h�ɒB���鎞���ƂȂ�悤�ȁATe�ɑ΂��銄��
            //       Ve|............../.:..|.......:..�_      p2:�������J�n�����ƂȂ�悤�ȁATe�ɑ΂��銄��
            //         |             /  :  |       :    |        (0.0 < p1 < p2 < 1.0)
            //         |         a  /   :  |       :    |
            //         |           /    s  |  D    :    |
            //         |          /     :  |       :    |
            //       --+---------/------+--+-------+----+-----> ����(t:�t���[��)
            //       0 |        /Ts    T1         T2   Te
            //         |   -s  /
            //         |      /
            //         |     /
            //         |    /
            //         |   /
            //         |  /
            //         | /
            //       V0|/
            //         |
            //
            //    ���� t �� 0 �` T1 ���̊p���x�� w �Ƃ����
            //    ���� V = a*t + V0 ���
            //    t = T1 �̎�  V = Vt  �ł���̂�
            //    Vt = a*T1 + V0
            //    a = -(V0-Vt)/T1 �E�E�E(1)
            //
            //    t = Ts �̎�  V = 0  �ł���̂�
            //    0 = a*Ts + V0  �E�E�E(2)
            //    (1)��(2)�֑��
            //    0 = (-(V0-Vt)/T1)*Ts + V0
            //    Ts = (T1*V0)/(V0-Vt) �E�E�E(3)
            //
            //    �����s��
            //    s = (1/2)*Ts*-V0
            //    (3)����
            //    s = (1/2)*( (T1*V0)/(V0-Vt) )*-V0
            //    s = -(T1*V0^2)/(2*(V0-Vt))  �E�E�E(4)
            //
            //    Vt�����߂�
            //    D+s = ���̎O�p�`�{�����̒����`�{�E�̑�` �̖ʐςł���A
            //    D+s =  ( (1/2)*(T1-Ts)*Vt )  +  ( (T2-T1) * Vt )  +  ( (1/2)*(Vt+Ve)*(Te-T2) )   �E�E�E(5)
            //    (3)(4)��(5)�֑��
            //    D+(-(T1*V0^2)/(2*(V0-Vt))) =  ( (1/2)*(T1-((T1*V0)/(V0-Vt)))*Vt )  +  ( (T2-T1) * Vt )  +  ( (1/2)*(Vt+Ve)*(Te-T2) )
            //    Vt�ɂ��ĉ���
            //    Vt=-(T1*V0-Ve*T2-2*D+Te*Ve)/(T2-T1+Te)
            const double V0 = _t_velo;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double T1 = prm_frame_of_target*prm_p1;
            const double T2 = prm_frame_of_target*prm_p2;
            const double Te = prm_frame_of_target;
            const double D = prm_target_value_distance;
            const double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);
            const double Ts = (T1*V0)/(V0-Vt);
            const double s = (1.0/2.0)*Ts*-V0;

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);
            //_TRACE_("Ts="<<Ts);
            //_TRACE_("s="<<s);
            _is_accelerating = true;
            _p0 = Ts;
            _p1 = T1;
            _p2 = T2;
            _target_distance = ABS(s)+ ABS(s) + ABS(D);
            _target_distance2 = D;
            _target_sgn = s_d;
            _moved = 0;
            _moved2 = 0;
            _top_velo = Vt;
            _end_velo = Ve;
            _frame_of_target = Te;
            _spent_frames = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_acc_for_T1;
        }


        //_TRACE_("_is_accelerating ="<<_is_accelerating);
        //_TRACE_("_p0 ="<<_p0);
        //_TRACE_("_p1 ="<<_p1);
        //_TRACE_("_p2 ="<<_p2);
        //_TRACE_("_target_distance ="<<_target_distance);
        //_TRACE_("_target_distance2 ="<<_target_distance2);
        //_TRACE_("_target_sgn ="<<_target_sgn);
        //_TRACE_("_moved ="<<_moved);
        //_TRACE_("_moved2 ="<<_moved2);
        //_TRACE_("_top_velo ="<<_top_velo);
        //_TRACE_("_end_velo ="<<_end_velo);
        //_TRACE_("_frame_of_target ="<<_frame_of_target);
        //_TRACE_("_spent_frames ="<<_spent_frames);
        //_TRACE_("_progress ="<<_progress);
    }

    void accelerateByVd(VAL_TYPE prm_top_velo,
                        VAL_TYPE prm_target_value_distance,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_zero_acc_end_flg) {
        //�ڕWTOP�X�s�[�h�w��̏ꍇ
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance<<" _t_velo="<<_t_velo);
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_t_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //������0�Ȃ̂ő����I��
            _is_accelerating = true;
            _top_velo = 0;
            _end_velo = prm_end_velo;
            _target_distance = 0;
            _target_distance2 = 0;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _frame_of_target = -1; //���Ԗ��g�p
            _spent_frames = 0;
            _p0 = 0;
            _p1 = 0;
            _p2 = 0;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_ZERO_END; //�����Ȃ肨���܂�
            return;
        }
        //_TRACE_("s_d="<<s_d<<" sgn_W0="<<sgn_W0);
        if (sgn_W0 == 0 || s_d == sgn_W0) {  //��������v
            //
            //        �p���x(V)                        V0:�����_�̑��x     (_velo_mv)
            //         ^                               Vt:�g�b�v�X�s�[�h   (prm_top_angvelo)
            //         |                               Ve:�ŏI���x         (prm_end_angvelo)
            //         |                                D:�ڕW��]�����pD  (D1+D2+D3)                     �E�E�E �v�Z���ċ��߂�
            //         |                               p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(D)�ɑ΂��銄��
            //         |       D=D1+D2+D3                   �܂�    D1 = D*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
            //       Vt|....___________                p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
            //         |   /|         |�_                   �܂� D1+D2 = D*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
            //       Ve|../.|.........|..�_            T1: D1    = D*p1 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
            //         | /  |         |    |           T2: D1+D2 = D*p2 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
            //         |/   |         |    |           Te:��₳���K�v���ԃt���[����                     �E�E�E �v�Z���ċ��߂�
            //       V0| D1 |    D2   | D3 |
            //         |    |         |    |
            //       --+----+---------+----+-----> ����(t:�t���[��)
            //       0 |    T1        T2   Te
            const double V0 = _t_velo;
            const double Vt = ABS(prm_top_velo) * s_d;
            const double Ve = ABS(prm_end_velo) * s_d;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            _is_accelerating = true;
            _top_velo = Vt;
            _end_velo = Ve;
            _target_distance = ABS(prm_target_value_distance);
            _target_distance2 = prm_target_value_distance;
            _moved = 0;
            _moved2 = 0;
            _target_sgn = s_d;
            _frame_of_target = -1; //���Ԗ��g�p
            _spent_frames = 0;
            _p0 = 0; //���g�p
            _p1 = ABS(_target_distance) * prm_p1;
            _p2 = ABS(_target_distance) * prm_p2;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_on_Ts; //�񕜃t�F�[�Y���΂�
        } else {
            //                                                       V0:�����_�̑��x      (_velo_mv)
            //        ���x(v)                                        Vt:�g�b�v�X�s�[�h    (prm_top_angvelo)
            //        ^                                              Ve:�ŏI���x          (prm_end_angvelo)
            //        |                                               D:�X�^�[�g���_�̊p�x����̖ڕW��]�����p                     �E�E�E �v�Z���ċ��߂�
            //        |                                              Dp:�p���x�O�ɂȂ��Ă���̖ڕW��]�����p(Dp1 + Dp2 + Dp3)   �E�E�E �v�Z���ċ��߂�
            //        |                                               s:�p���x�O�ɂȂ�܂ł̋t��]����                             �E�E�E �v�Z���ċ��߂�
            //        |                                              p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(D)�ɑ΂��銄��
            //        |           D  = (Dp1-s) + Dp2 + Dp3                 �܂� Dp1 = Dp*p1 �ƂȂ�悤�� p1 (0.0�`1.0)    ����
            //        |           Dp = Dp1 + Dp2 + Dp3               p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
            //      Vt|...............___________                          �܂� Dp1+Dp2 = Dp*p2 �ƂȂ�悤�� p2 (0.0�`1.0)  ����
            //        |            A /|         |�_B                 T0: �p���x�O�ɂȂ�܂łɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
            //        |             / |         |  �_                T1: Dp1     = Dp*p1 �ɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
            //        |            /  |         |    �_              T2: Dp1+Dp2 = Dp*p2 �ɔ�₳���K�v���ԃt���[����  �E�E�E �v�Z���ċ��߂�
            //        |           /   |         |      �_            Te:��₳���K�v���ԃt���[����                        �E�E�E �v�Z���ċ��߂�
            //        |          / Dp1|    Dp2  |  Dp3   �_
            //        |         /:    |         |          �_
            //      Ve|......../.:....|.........|............�_  C
            //        |       /  :    |         |             |
            //        |      / s :    |         |             |
            //   -----+-----+----+----+---------+-------------+----------> ����(t:�t���[��)
            //      0 | s�^ Ts       T1        T2            Te
            //        |�^
            //      V0| ^    <-s-><------------D-------------->
            //        | |
            //        | |    <---------------Dp--------------->
            //        | |
            //        | |    <---Dp1--><---Dp2--><-----Dp3---->
            //        | |
            //        | �����񕜊p�����x(a0)�Œ�
            //
            //        ���� t �� 0 �` Ts ���̊p���x�� V �Ƃ����
            //        ���� V = a0*t + V0 ���    (�������񕜊p�����x(a0)�͒萔)
            //        t = Ts �̎�  V = 0  �ł���̂�
            //        0 = a0*Ts + V0
            //        Ts = -V0/a0  �E�E�E(1)
            //        �܂�
            //        s = (1/2) * Ts * -V0       (��O�p�`�̖ʐ�)
            //        �����(1)����
            //        s = (1/2) * (-V0/a0) * -V0
            //        s = V0^2/(2*a0)  �E�E�E(2)
            //        �܂�
            //
            //        D + s =  Dp = (Dp1 + Dp2 + Dp3) �E�E�E(3)
            //        ���
            //        Dp = D + (V0^2/(2*a0))  �E�E�E(4)
            const double V0 = _t_velo;
            const double Vt = ABS(prm_top_velo) * s_d;
            const double Ve = ABS(prm_end_velo) * s_d;
            const double a0 = ABS(prm_top_velo)*0.05 * -sgn_W0;
            const double s  = (V0*V0)/(2.0*a0);
            const double Dp = s + prm_target_value_distance;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            //_TRACE_("a0 = "<<a0);
            //_TRACE_("s  = "<<s );
            //_TRACE_("Dp = "<<Dp);

            _is_accelerating = true;
            _top_velo = Vt;
            _end_velo = Ve;
            _target_distance = ABS(s) + ABS(Dp);
            _target_distance2 = prm_target_value_distance;
            _moved = 0;
            _moved2 = 0;
            _acce_a0 = a0;
            _target_sgn = s_d;
            _frame_of_target = -1; //���Ԗ��g�p
            _spent_frames = 0;
            _p0 = ABS(s);
            _p1 = prm_p1;
            _p2 = prm_p2;
            _zero_acc_end_flg = prm_zero_acc_end_flg;
            _progress = ACCELERATE_RECOVERY_BEGIN; //�񕜃t�F�[�Y����
        }

        //_TRACE_("_is_accelerating ="<<_is_accelerating);
        //_TRACE_("_p0 ="<<_p0);
        //_TRACE_("_p1 ="<<_p1);
        //_TRACE_("_p2 ="<<_p2);
        //_TRACE_("_target_distance ="<<_target_distance);
        //_TRACE_("_target_distance2 ="<<_target_distance2);
        //_TRACE_("_target_sgn ="<<_target_sgn);
        //_TRACE_("_moved ="<<_moved);
        //_TRACE_("_moved2 ="<<_moved2);
        //_TRACE_("_top_velo ="<<_top_velo);
        //_TRACE_("_end_velo ="<<_end_velo);
        //_TRACE_("_frame_of_target ="<<_frame_of_target);
        //_TRACE_("_spent_frames ="<<_spent_frames);
        //_TRACE_("_progress ="<<_progress);
    }

    /**
     * ���݉����������ł��邩�ۂ� .
     * @return true:����������/false:��~��
     */
    inline bool isAccelerating() const {
        return _progress == ACCELERATE_DONE ? false : true;
    }

    /**
     * ���x���������������������ǂ������ׂ� .
     * �������������������̂� true �ƂȂ�B
     * ���̌�� behave() �� false �ƂȂ�B
     * @return true:���x��������������/false:���݉������������A�����͈ȑO�����~��
     */
    inline bool hasJustFinishedAccelerating() {
        if (_progress != ACCELERATE_DONE && _is_accelerating == false) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �����������������I�� .
     */
    inline void stopAccelerating() {
        _is_accelerating = false;
    }

    void behave() {
        //�Ȃ߂炩�ړ��V�[�N�G���X�N����
        if (_is_accelerating) {
            //_TRACE_(_frame_of_target<<":_progress="<<_progress);
            //_TRACE_(_frame_of_target<<":before _t_value="<<_t_value<<" _t_velo="<<_t_velo<<" _t_acce="<<_t_acce<<" _moved="<<_moved<<" _moved2="<<_moved2<<"");
            if (_progress == ACCELERATE_ZERO_END) {
                //�����Ȃ�I�����̏����i�������O�A�����́A���Ԃ��O�j
                _t_velo = (VAL_TYPE)0.0; //��~
                _t_acce = (VAL_TYPE)0.0;
                if (_frame_of_target < 0) {
                    _t_velo = _end_velo;
                    _t_acce = (VAL_TYPE)0.0; //_zero_acc_end_flg �֌W�Ȃ�
                    _is_accelerating = false; //�����܂�
                } else {
                    //�ڕW�����w��̏ꍇ
                    if (_spent_frames >= _frame_of_target) { //���Ԃ܂ŉ��������ɔS��
                        _t_velo = _end_velo;
                        _t_acce = (VAL_TYPE)0.0; //_zero_acc_end_flg �֌W�Ȃ�
                        _is_accelerating = false; //�����܂�
                    }
                }

            } else {

                if (_frame_of_target < 0) {
                    //�ڕWTOP�X�s�[�h�w��̏ꍇ
                    if (_progress == ACCELERATE_RECOVERY_BEGIN) {
                        //�񕜃t�F�[�Y
                        _t_acce = _acce_a0;
                        _progress = ACCELERATE_RECOVERING_to_Ts;
                    }
                    if (_progress == ACCELERATE_RECOVERING_to_Ts) {
                        //�񕜒�
                        if (_moved >= _p0) {
                            //�����ݒ�
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = (VAL_TYPE)0.0;
                            //�Đݒ�
                            _target_distance = _target_distance - _moved;
                            _moved = (VAL_TYPE)0.0;
                            _p1 = _target_distance * _p1;
                            _p2 = _target_distance * _p2;
                            _progress = ACCELERATE_on_Ts;
                        }
                    }
                    if (_progress == ACCELERATE_on_Ts) {
                        if (!ZEROd_EQ(_p1)) {
                            _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _top_velo, _p1*_target_sgn));
                            VAL_TYPE a = ABS(_t_acce);
                            if (a > ABS(_target_distance2)) {
                                _t_acce = _target_distance2;
                            } else if (a > ABS(_top_velo)) {
                                _t_acce = _top_velo;
                            }
                            _progress = ACCELERATE_acc_for_T1; //T1 �֌����Ẳ����x�ݒ�
                        } else {
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            _progress = ACCELERATE_T1_to_T2; //�����X�L�b�v
                        }
                    }
                    if (_progress == ACCELERATE_acc_for_T1) {
                        //������
                        if (_moved >= _p1) {
                            //p1 �ɓ��B����� ������
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                            if (ABS(_t_velo) > ABS(diff_to_end)) {
                                _t_velo = diff_to_end;
                            }
                            _progress = ACCELERATE_T1_to_T2;
                        }
                    }
                    if (_progress == ACCELERATE_T1_to_T2) {
                        //_TRACE_("������");
                        //������
                        if (_moved >= _p2) {
                            //p2 �ɓ��B����� ����t���[�����猸����
                            //_TRACE_("p2 �ɓ��B����� ����t���[�����猸����");
                            const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                            if (!ZEROd_EQ(diff_to_end)) {
                                //_TRACE_("diff_to_end="<<diff_to_end<<" ���������x�����߂��");
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _end_velo, diff_to_end));
                                //_TRACE_("���������x _t_acce="<<acc<<" ????");
                                if (ABS(_t_velo)+ABS(_t_acce) > ABS(diff_to_end)) {
                                    _t_acce = diff_to_end-_t_velo;
                                }
                                //_TRACE_("���������x �␳ _t_acce="<<acc<<" ????");
                            }
                            _progress = ACCELERATE_T2_to_Te;
                        }
                    }
                    if (_progress == ACCELERATE_T2_to_Te) {
                         //_TRACE_("������");
                        //������
                        const VAL_TYPE diff_to_end = _target_distance2 - _moved2;
                        //Te=(2*D)/(V0+Vt)

                        //double t = (2.0*diff_to_end)/(_t_velo+_end_velo); //�c�t���[����    //�����������R�����g
                        //_TRACE_("double t = (2.0*diff_to_end)/(_t_velo+_end_velo); //�c�t���[����");
                        //_TRACE_("double t = (2.0*"<<diff_to_end<<")/("<<_t_velo<<"+"<<_end_velo<<"); //�c�t���[����");
                        //_TRACE_("double t = ("<<2.0*diff_to_end<<")/("<<_t_velo+_end_velo<<"); //�c�t���[����");
                        //_TRACE_("�c�t���[�� t="<<t<<" �H");
                        //_TRACE_("ABS(_t_velo) < 2.0*ABS(_t_acce) = "<<ABS(_t_velo)<<" < "<<2.0*ABS(_t_acce));
                        if (ABS(_t_velo) < 2.0*ABS(_t_acce)) {
                            //_TRACE_("�␳���Ȃ� �i_velo�����܂�ɂ����������߁At ����������B�������̉����x���ݒ肳��Ă��܂����߁j");
                            //t = 1;
                            //�␳���Ȃ�(_velo�����܂�ɂ����������߁At ����������)
                        } else {
                            if ((_spent_frames & 1) == 0) { //2���1��
        //                      if (t > 3 && ABS(diff_to_end) > ABS(_top_velo)*0.0001 && _spent_frames % 4U == 0) {
                                //_TRACE_("t="<<t<<" ���������ĂȂ��̂ŁA�␳�E�␳�E�␳");
                                //�␳�E�␳�E�␳
                                if (!ZEROd_EQ(diff_to_end)) {
                                    _t_acce = (VAL_TYPE)(UTIL::getAcceByVd(_t_velo, _end_velo, diff_to_end));
                                    //_TRACE_("���������x�Đݒ� _t_acce="<<acc<<" ????");
                                    if (ABS(_t_velo)+ABS(_t_acce) > ABS(diff_to_end)) {
                                        _t_acce = diff_to_end-_t_velo;
                                    }
                                    //_TRACE_("���������x�Đݒ� �␳ _t_acce="<<acc<<" ????");
                                }
                            }
                        }
                        const VAL_TYPE end_velo = _end_velo;

                        if ( ZEROd_EQ(diff_to_end)  ||
                             ABS(diff_to_end) <=  ABS(_top_velo)*0.0001 ||
                             (ZEROd_EQ(_top_velo)  || (_top_velo > 0 && diff_to_end <= 0) || (_top_velo < 0  && diff_to_end >= 0) ) || //�ʂ�z������
                             (ZEROd_EQ(_t_velo+end_velo)  || (_t_velo+end_velo > 0 && _t_velo+end_velo+_t_acce < 0 ) || (_t_velo+end_velo <  0 && _t_velo+end_velo+_t_acce > 0) ) //�͂������]������
                        ) {
                            //�ڕW�����֓��B
                            //_TRACE_("�ڕW�����֓��B");
                            //_TRACE_("ABS(_target_distance2 - _moved2) <=  ABS(_top_velo)*0.00001");
                            //_TRACE_(""<<ABS(_target_distance2 - _moved2)<<" <= "<<ABS(_top_velo)*0.00001<<" ??");
                            //_TRACE_("(ZEROd_EQ(_top_velo)  || (_top_velo > 0  && diff_to_end <= 0) || (_top_velo < 0  && diff_to_end >= 0) ) || //�ʂ�z������");
                            //_TRACE_("_top_velo="<<_top_velo<<" diff_to_end="<<diff_to_end<<"");
                            //_TRACE_("(ZEROd_EQ(_t_velo+end_velo)  || (_t_velo+end_velo  >  0 && _t_velo +end_velo + _t_acce < 0 ) || (_t_velo+end_velo  <  0 && _t_velo +end_velo+_t_acce > 0) ) //�͂������]������");
                            //_TRACE_("_t_velo="<<_t_velo<<" end_velo="<<end_velo<<" _t_velo+end_velo="<<_t_velo+end_velo<<" _t_acce="<<_t_acce<<" _t_velo +end_velo+_t_acce="<<_t_velo +end_velo + _t_acce <<"");
                            //_TRACE_("�����܂��ȕ��͋C");
                            _t_velo = _end_velo;
                            if (_zero_acc_end_flg) {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(end_velo)) {
                                //�ŏI���x��0�̏ꍇ�A�o�b�`�����킹�����݂�B
                                if (ZEROd_EQ(diff_to_end)) {
                                    //���Ƀo�b�`�������Ă��܂���
                                    //_TRACE_("���Ƀo�b�`�������Ă��܂���");
                                    //_TRACE_("�����܂�11���I!!");
                                    _t_velo = (VAL_TYPE)0.0;
                                    _is_accelerating = false; //�����܂�
                                } else {
                                    //����Ă�̂ł����P�t���[���撣���ăo�b�`�����킹��
                                    _t_velo = diff_to_end;   //�o�b�`�����킹��
                                    //_TRACE_("�o�b�`�����킹��������_velo="<<_target_distance2<<"-"<<_moved2<<"="<<_t_velo);
                                    _progress = ACCELERATE_BACCHIRI; //�����P�t���[��
                                }
                            } else {
                                //�ŏI���x��0�ł͂Ȃ��B���̂܂܏I��
                                //_TRACE_("�����܂�22");
                                _is_accelerating = false; //�����܂�
                            }
                        }
                    } else if (_progress == ACCELERATE_BACCHIRI) {
                        //_TRACE_("�悵�o�b�`�����킹�Ă����܂�");
                        _t_velo = (VAL_TYPE)0.0;
                        _is_accelerating = false; //�����܂�
                    }
                } else {
                    //�ڕW���Ԏw��̏ꍇ
                    if (_progress == ACCELERATE_acc_for_T1) {
                        if (ZEROd_EQ(_p1)) {
                            _t_acce = 0;
                        } else {
                            //�����ݒ�
                            _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(_p1, _t_velo, _top_velo));
                        }
                        _progress = ACCELERATE_Ts_to_T1;
                    }
                    if (_progress == ACCELERATE_Ts_to_T1) {
                        //������
                        if (_spent_frames >= (int)(_p1)) {
                            //p1 �ɓ��B����� ������
                            _t_acce = (VAL_TYPE)0.0;
                            _t_velo = _top_velo;
                            _progress = ACCELERATE_T1_to_T2;
                        }
                    }
                    if (_progress == ACCELERATE_T1_to_T2) {
                        //_TRACE_("������ _spent_frames="<<_spent_frames<<" _p2="<<_p2);
                        //������
                        if (_spent_frames >= (int)(_p2)) {
                            //_TRACE_("p2 �ɓ��B����� ����t���[�����猸���� _spent_frames="<<_spent_frames<<" _p2="<<_p2);
                            //p2 �ɓ��B����� ����t���[�����猸����
                            const double Ve = _end_velo;
                            const double Te = _frame_of_target - _spent_frames;
                            if (Te > 0) {
                                //�����ݒ�
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(Te, _t_velo, Ve));
                                //_TRACE_("���������x _t_acce="<<_t_acce);
                            } else {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            _progress = ACCELERATE_T2_to_Te;
                        }
                    }
                    if (_progress == ACCELERATE_T2_to_Te) {
                        //������
                        //_TRACE_("������");
                        if ((_spent_frames & 1) == 0) { //2���1��
                            //_TRACE_("�␳�E�␳�E�␳");
                            //�␳�E�␳�E�␳
                            //�Ō�̑�`�␳
                            //D = (1/2)*(V+Ve)*Te
                            const double Ve = _end_velo;
                            const double Te = _frame_of_target - _spent_frames;
                            //_TRACE_("Ve = "<<Ve);
                            //_TRACE_("Te = "<<Te);
                            if (Te > 0) {
                                const double D = _target_distance2 - _moved2;
                                const double V = (2.0*D-Te*Ve)/Te;
                                //_TRACE_("D = "<<D);
                                //_TRACE_("V = "<<V);
                                _t_velo = V;
                                //_TRACE_("���x _t_velo = "<<_t_velo<<" �ɕ␳");
                                _t_acce = (VAL_TYPE)(UTIL::getAcceByTv(Te, _t_velo, Ve));
                                //_TRACE_("�����x _t_acce = "<<_t_acce<<" �ɕ␳");
                            }
                        }
                        //_TRACE_("_spent_frames="<<_spent_frames<< " _frame_of_target="<<_frame_of_target);
                        if (_spent_frames >= _frame_of_target) {
                            //_TRACE_("_spent_frames >= _frame_of_target �����A�����܂��ȕ��͋C");
                            _t_velo = _end_velo;
                            if (_zero_acc_end_flg) {
                                _t_acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(_end_velo)) {
                                //�ŏI���x��0�̏ꍇ�A�o�b�`�����킹�����݂�B
                                if (ZEROd_EQ(_target_distance2 - _moved2)) {
                                    //���Ƀo�b�`�������Ă��܂���
                                    //_TRACE_("���Ƀo�b�`�������Ă��܂���");
                                    //_TRACE_("�����܂�1���I");
                                    _t_velo = (VAL_TYPE)0.0;
                                    _is_accelerating = false; //�����܂�
                                } else {
                                    //����Ă�B�o�b�`�����킹�邽�߁A�����P�t���[��
                                    _t_velo = (_target_distance2 - _moved2); //���̓o�b�`��0�ɂȂ�
                                    //_TRACE_("�o�b�`�����킹��������_velo="<<_target_distance2<<"-"<<_moved2<<"="<<_t_velo);
                                    _progress = ACCELERATE_BACCHIRI;
                                }
                            } else {
                                //�ŏI���x��0�ł͂Ȃ��B���̂܂܏I��
                                //_TRACE_("�����܂�2");
                                _is_accelerating = false; //�����܂�
                            }
                        }
                    } else if (_progress == ACCELERATE_BACCHIRI) {
                        //_TRACE_("�o�b�`�����킹�Ă����܂�");
                        _t_velo = (VAL_TYPE)0.0;
                        _is_accelerating = false; //�����܂�
                    }
                }
            }

            _t_velo += _t_acce;
            _t_value += _t_velo;

            _moved += ABS(_t_velo);
            _moved2 += _t_velo;

            //_TRACE_(_frame_of_target<<":after _t_value="<<_t_value<<" _t_velo="<<_t_velo<<" _t_acce="<<_t_acce<<" _moved="<<_moved<<" _moved2="<<_moved2<<"");
            _spent_frames++;
        } else {
            _progress = ACCELERATE_DONE;
        }
#ifdef MY_DEBUG
        if (_spent_frames > 60*60*10) {
            throwGgafCriticalException("10���ȏ㊊����ςȂ��Ȃ�ł����I");
        }
#endif
    }

    virtual ~GgafValueAccelerator() {
    }
};

}
#endif /*GGAFCORE_GGAFVALUEACCELERATOR_H_*/

