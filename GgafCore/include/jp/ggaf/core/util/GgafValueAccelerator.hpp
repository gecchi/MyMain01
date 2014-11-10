#ifndef GGAFCORE_GGAFVALUEACCELERATOR_H_
#define GGAFCORE_GGAFVALUEACCELERATOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/core/util/GgafUtil.h"

namespace GgafCore {

/**
 * �l�̉����� .
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
template<class VAL_TYPE>
class GgafValueAccelerator : public GgafObject {
public:


    class SmoothPrm {
     public:
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s����true */
         bool _flg;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
         bool _endacc_flg;
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
         int  _target_frames;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ɊJ�n���猻�݂܂ł̌o�ߎ��� */
         int  _frame_of_spent;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�p���x�̐������؂�ւ��|�C���g */
         double  _p0;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
         double  _p1;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�����`�����֐؂�ւ��ʒu */
         double  _p2;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�̐i���� */
         int  _progress;
     public:
         SmoothPrm() {
             _flg = false;
             _endacc_flg = true;
             _top_velo = 0;
             _end_velo = 0;
             _target_distance = 0;
             _target_distance2 = 0;
             _moved = 0;
             _moved2 = 0;
             _acce_a0 = 0;
             _target_sgn = 1;
             _target_frames = 0;
             _frame_of_spent = 0;
             _p0 = 0;
             _p1 = 0;
             _p2 = 0;
             _progress = -1;
         }
    };
    VAL_TYPE _value;
    VAL_TYPE _velo;
    VAL_TYPE _acce;
    SmoothPrm _prm;
public:
    GgafValueAccelerator() {
        _value = 0;
        _velo = 0;
        _acce = 0;
    }

    void accelerateByDt(VAL_TYPE prm_target_value_distance,
                        frame prm_target_frames,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_endacc_flg) {
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //������0�Ȃ̂ő����I��
            _velo = ABS(prm_end_velo) * s_d;
            if (prm_endacc_flg) {
                _acce = (VAL_TYPE)0.0;
            }
            _prm._progress = -9;
            _prm._endacc_flg = false;
            return;
        }
        //_TRACE_("GgafValueAccelerator::accelerateByDt COME!");
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance);
        //_TRACE_("prm_target_frames="<<prm_target_frames);
        //_TRACE_("prm_p1="<<prm_p1);
        //_TRACE_("prm_p2="<<prm_p2);
        //_TRACE_("prm_end_velo="<<prm_end_velo);
        //_TRACE_("prm_endacc_flg="<<prm_endacc_flg);

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
            double V0 = _velo;
            double Ve = ABS(prm_end_velo) * s_d;
            double T1 = prm_target_frames*prm_p1;
            double T2 = prm_target_frames*prm_p2;
            double Te = prm_target_frames;
            double D  = prm_target_value_distance;
            double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);


            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);

            _prm._flg = true;
            _prm._target_distance = ABS(D);
            _prm._target_distance2 = D;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._target_sgn = s_d;
            _prm._p1 = T1;
            _prm._p2 = T2;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_frames = Te;
            _prm._frame_of_spent = 0;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0;


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
            double V0 = _velo;
            double Ve = ABS(prm_end_velo) * s_d;
            double T1 = prm_target_frames*prm_p1;
            double T2 = prm_target_frames*prm_p2;
            double Te = prm_target_frames;
            double D = prm_target_value_distance;
            double Vt = -(T1*V0-Ve*T2-2.0*D+Te*Ve)/(T2-T1+Te);
            double Ts = (T1*V0)/(V0-Vt);
            double s = (1.0/2.0)*Ts*-V0;

            //_TRACE_("V0="<<V0);
            //_TRACE_("Ve="<<Ve);
            //_TRACE_("T1="<<T1);
            //_TRACE_("T2="<<T2);
            //_TRACE_("Te="<<Te);
            //_TRACE_("D="<<D);
            //_TRACE_("Vt="<<Vt);
            //_TRACE_("Ts="<<Ts);
            //_TRACE_("s="<<s);
            _prm._flg = true;
            _prm._p0 = Ts;
            _prm._p1 = T1;
            _prm._p2 = T2;
            _prm._target_distance = ABS(s)+ ABS(s) + ABS(D);
            _prm._target_distance2 = D;
            _prm._target_sgn = s_d;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_frames = Te;
            _prm._frame_of_spent = 0;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0;
        }


        //_TRACE_("_prm._flg ="<<_prm._flg);
        //_TRACE_("_prm._p0 ="<<_prm._p0);
        //_TRACE_("_prm._p1 ="<<_prm._p1);
        //_TRACE_("_prm._p2 ="<<_prm._p2);
        //_TRACE_("_prm._target_distance ="<<_prm._target_distance);
        //_TRACE_("_prm._target_distance2 ="<<_prm._target_distance2);
        //_TRACE_("_prm._target_sgn ="<<_prm._target_sgn);
        //_TRACE_("_prm._moved ="<<_prm._moved);
        //_TRACE_("_prm._moved2 ="<<_prm._moved2);
        //_TRACE_("_prm._top_velo ="<<_prm._top_velo);
        //_TRACE_("_prm._end_velo ="<<_prm._end_velo);
        //_TRACE_("_prm._target_frames ="<<_prm._target_frames);
        //_TRACE_("_prm._frame_of_spent ="<<_prm._frame_of_spent);
        //_TRACE_("_prm._progress ="<<_prm._progress);

    }

    void accelerateByVd(VAL_TYPE prm_top_velo,
                        VAL_TYPE prm_target_value_distance,
                        double prm_p1, double prm_p2, VAL_TYPE prm_end_velo,
                        bool prm_endacc_flg) {
        //_TRACE_("prm_target_value_distance="<<prm_target_value_distance<<" _velo="<<_velo);
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            //������0�Ȃ̂ő����I��
            _velo = ABS(prm_end_velo) * s_d;
            if (prm_endacc_flg) {
                _acce = (VAL_TYPE)0.0;
            }
            _prm._progress = -9;
            _prm._endacc_flg = false;
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
            double V0 = _velo;
            double Vt = ABS(prm_top_velo) * s_d;
            double Ve = ABS(prm_end_velo) * s_d;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            _prm._flg = true;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_distance = ABS(prm_target_value_distance);
            _prm._target_distance2 = prm_target_value_distance;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._target_sgn = s_d;
            _prm._target_frames = -1; //���Ԗ��g�p
            _prm._frame_of_spent = 0;
            _prm._p0 = 0; //���g�p
            _prm._p1 = ABS(_prm._target_distance) * prm_p1;
            _prm._p2 = ABS(_prm._target_distance) * prm_p2;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 2; //�񕜃t�F�[�Y���΂�
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
            double V0 = _velo;
            double Vt = ABS(prm_top_velo) * s_d;
            double Ve = ABS(prm_end_velo) * s_d;
            double a0 = ABS(prm_top_velo)*0.05 * -sgn_W0;
            double s  = (V0*V0)/(2.0*a0);
            double Dp = s + prm_target_value_distance;
            //_TRACE_("V0 = "<<V0);
            //_TRACE_("Vt = "<<Vt);
            //_TRACE_("Ve = "<<Ve);
            //_TRACE_("a0 = "<<a0);
            //_TRACE_("s  = "<<s );
            //_TRACE_("Dp = "<<Dp);

            _prm._flg = true;
            _prm._top_velo = Vt;
            _prm._end_velo = Ve;
            _prm._target_distance = ABS(s) + ABS(Dp);
            _prm._target_distance2 = prm_target_value_distance;
            _prm._moved = 0;
            _prm._moved2 = 0;
            _prm._acce_a0 = a0;
            _prm._target_sgn = s_d;
            _prm._target_frames = -1; //���Ԗ��g�p
            _prm._frame_of_spent = 0;
            _prm._p0 = ABS(s);
            _prm._p1 = prm_p1;
            _prm._p2 = prm_p2;
            _prm._endacc_flg = prm_endacc_flg;
            _prm._progress = 0; //�񕜃t�F�[�Y����

        }


        //_TRACE_("_prm._flg ="<<_prm._flg);
        //_TRACE_("_prm._p0 ="<<_prm._p0);
        //_TRACE_("_prm._p1 ="<<_prm._p1);
        //_TRACE_("_prm._p2 ="<<_prm._p2);
        //_TRACE_("_prm._target_distance ="<<_prm._target_distance);
        //_TRACE_("_prm._target_distance2 ="<<_prm._target_distance2);
        //_TRACE_("_prm._target_sgn ="<<_prm._target_sgn);
        //_TRACE_("_prm._moved ="<<_prm._moved);
        //_TRACE_("_prm._moved2 ="<<_prm._moved2);
        //_TRACE_("_prm._top_velo ="<<_prm._top_velo);
        //_TRACE_("_prm._end_velo ="<<_prm._end_velo);
        //_TRACE_("_prm._target_frames ="<<_prm._target_frames);
        //_TRACE_("_prm._frame_of_spent ="<<_prm._frame_of_spent);
        //_TRACE_("_prm._progress ="<<_prm._progress);
    }

    bool isAcce() {
        return _prm._flg;
    }

    void behave() {
        //�Ȃ߂炩�ړ��V�[�N�G���X�N����
        if (_prm._flg) {
            //_TRACE_(_prm._target_frames<<":_prm._progress="<<_prm._progress);
            //_TRACE_(_prm._target_frames<<":before _value="<<_value<<" _velo="<<_velo<<" _acce="<<_acce<<" _prm._moved="<<_prm._moved<<" _prm._moved2="<<_prm._moved2<<"");
            if (_prm._progress == -9) {
                _prm._flg = false; //�����܂�
            } else {

                if (_prm._target_frames < 0) {
                    //�ڕW�����w��̏ꍇ
                    if (_prm._progress == 0) {
                        //�񕜃t�F�[�Y
                        _acce = _prm._acce_a0;
                        _prm._progress++;
                    }
                    if (_prm._progress == 1) {
                        //�񕜒�
                        if (_prm._moved >= _prm._p0) {
                            //�����ݒ�
                            _acce = 0.0;
                            _velo = 0.0;
                            //�Đݒ�
                            _prm._target_distance = _prm._target_distance - _prm._moved;
                            _prm._moved = 0.0;
                            _prm._p1 = _prm._target_distance * _prm._p1;
                            _prm._p2 = _prm._target_distance * _prm._p2;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 2) {
                        if (!ZEROd_EQ(_prm._p1)) {
                            VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._top_velo, _prm._p1*_prm._target_sgn);
                            _acce = acc;
                            if (ABS(_acce) > ABS(_prm._target_distance2)) {
                                _acce = _prm._target_distance2;
                            } else if (ABS(_acce) > ABS(_prm._top_velo)) {
                                _acce = _prm._top_velo;
                            }
                            _prm._progress++;
                        } else {
                            _acce = 0;
                            _velo = _prm._top_velo;
                            _prm._progress+=2; //�����X�L�b�v
                        }
                    }
                    if (_prm._progress == 3) {
                        //������
                        if (_prm._moved >= _prm._p1) {
                            //p1 �ɓ��B����� ������
                            _acce = 0;
                            _velo = _prm._top_velo;
                            VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                            if (ABS(_velo) > ABS(diff_to_end)) {
                                _velo = diff_to_end;
                            }
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 4) {
                        //_TRACE_("������");
                        //������
                        if (_prm._moved >= _prm._p2) {
                            //p2 �ɓ��B����� ����t���[�����猸����
                            //_TRACE_("p2 �ɓ��B����� ����t���[�����猸����");
                            VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                            if (!ZEROd_EQ(diff_to_end)) {
                                //_TRACE_("diff_to_end="<<diff_to_end<<" ���������x�����߂��");
                                VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                                _acce = acc;
                                //_TRACE_("���������x _acce="<<acc<<" ????");
                                if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                    _acce = diff_to_end-_velo;
                                }
                                //_TRACE_("���������x �␳ _acce="<<acc<<" ????");
                            }
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 5) {
                         //_TRACE_("������");
                        //������
                        VAL_TYPE diff_to_end = _prm._target_distance2 - _prm._moved2;
                        //Te=(2*D)/(V0+Vt)

                        //double t = (2.0*diff_to_end)/(_velo+_prm._end_velo); //�c�t���[����    //�����������R�����g
                        //_TRACE_("double t = (2.0*diff_to_end)/(_velo+_prm._end_velo); //�c�t���[����");
                        //_TRACE_("double t = (2.0*"<<diff_to_end<<")/("<<_velo<<"+"<<_prm._end_velo<<"); //�c�t���[����");
                        //_TRACE_("double t = ("<<2.0*diff_to_end<<")/("<<_velo+_prm._end_velo<<"); //�c�t���[����");
                        //_TRACE_("�c�t���[�� t="<<t<<" �H");
                        //_TRACE_("ABS(_velo) < 2.0*ABS(_acce) = "<<ABS(_velo)<<" < "<<2.0*ABS(_acce));
                        if (ABS(_velo) < 2.0*ABS(_acce)) {
                            //_TRACE_("�␳���Ȃ� �i_velo�����܂�ɂ����������߁At ����������B�������̉����x���ݒ肳��Ă��܂����߁j");
                            //t = 1;
                            //�␳���Ȃ�(_velo�����܂�ɂ����������߁At ����������)
                        } else {
                            if (_prm._frame_of_spent & 1) { //2���1��
        //                      if (t > 3 && ABS(diff_to_end) > ABS(_prm._top_velo)*0.0001 && _prm._frame_of_spent % 4U == 0) {
                                //_TRACE_("t="<<t<<" ���������ĂȂ��̂ŁA�␳�E�␳�E�␳");
                                //�␳�E�␳�E�␳
                                if (!ZEROd_EQ(diff_to_end)) {
                                    VAL_TYPE acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                                    _acce = acc;
                                    //_TRACE_("���������x�Đݒ� _acce="<<acc<<" ????");
                                    if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                        _acce = diff_to_end-_velo;
                                    }
                                    //_TRACE_("���������x�Đݒ� �␳ _acce="<<acc<<" ????");
                                }
                            }
                        }
                        VAL_TYPE end_velo = _prm._end_velo;

                        if ( ZEROd_EQ(diff_to_end)  ||
                             ABS(diff_to_end) <=  ABS(_prm._top_velo)*0.0001 ||
                             (ZEROd_EQ(_prm._top_velo)  || (_prm._top_velo > 0 && diff_to_end <= 0) || (_prm._top_velo < 0  && diff_to_end >= 0) ) || //�ʂ�z������
                             (ZEROd_EQ(_velo+end_velo)  || (_velo+end_velo > 0 && _velo+end_velo+_acce < 0 ) || (_velo+end_velo <  0 && _velo+end_velo+_acce > 0) ) //�͂������]������
                        ) {
                            //�ڕW�����֓��B
                            //_TRACE_("�ڕW�����֓��B");
                            //_TRACE_("ABS(_prm._target_distance2 - _prm._moved2) <=  ABS(_prm._top_velo)*0.00001");
                            //_TRACE_(""<<ABS(_prm._target_distance2 - _prm._moved2)<<" <= "<<ABS(_prm._top_velo)*0.00001<<" ??");
                            //_TRACE_("(ZEROd_EQ(_prm._top_velo)  || (_prm._top_velo > 0  && diff_to_end <= 0) || (_prm._top_velo < 0  && diff_to_end >= 0) ) || //�ʂ�z������");
                            //_TRACE_("_prm._top_velo="<<_prm._top_velo<<" diff_to_end="<<diff_to_end<<"");
                            //_TRACE_("(ZEROd_EQ(_velo+end_velo)  || (_velo+end_velo  >  0 && _velo +end_velo + _acce < 0 ) || (_velo+end_velo  <  0 && _velo +end_velo+_acce > 0) ) //�͂������]������");
                            //_TRACE_("_velo="<<_velo<<" end_velo="<<end_velo<<" _velo+end_velo="<<_velo+end_velo<<" _acce="<<_acce<<" _velo +end_velo+_acce="<<_velo +end_velo + _acce <<"");
                            //_TRACE_("�����܂��ȕ��͋C");
                            _velo = _prm._end_velo;
                            if (_prm._endacc_flg) {
                                _acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(end_velo)) {
                                //�ŏI���x��0�̏ꍇ�A�o�b�`�����킹�����݂�B
                                if (ZEROd_EQ(diff_to_end)) {
                                    //���Ƀo�b�`�������Ă��܂���
                                    //_TRACE_("���Ƀo�b�`�������Ă��܂���");
                                    //_TRACE_("�����܂�11���I!!");
                                    _velo = (VAL_TYPE)0.0;
                                    _prm._flg = false; //�����܂�
                                } else {
                                    //����Ă�̂ł����P�t���[���撣���ăo�b�`�����킹��
                                    _velo = diff_to_end;   //�o�b�`�����킹��
                                    //_TRACE_("�o�b�`�����킹��������_velo="<<_prm._target_distance2<<"-"<<_prm._moved2<<"="<<_velo);
                                    _prm._progress++; //�����P�t���[��
                                }
                            } else {
                                //�ŏI���x��0�ł͂Ȃ��B���̂܂܏I��
                                //_TRACE_("�����܂�22");
                                _prm._flg = false; //�����܂�
                            }
                        }
                    } else if (_prm._progress == 6) {
                        //_TRACE_("�悵�o�b�`�����킹�Ă����܂�");
                        _velo = (VAL_TYPE)0.0;
                        _prm._flg = false; //�����܂�
                    }
                } else {
                    //�ڕW���Ԏw��̏ꍇ
                    if (_prm._progress == 0) {
                        if (ZEROd_EQ(_prm._p1)) {
                            _acce = 0;
                            _prm._progress++;
                        } else {
                            //�����ݒ�
                            VAL_TYPE acc = UTIL::getAcceByTv(_prm._p1, _velo, _prm._top_velo);
                            _acce = acc;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 1) {
                        //������
                        if (_prm._frame_of_spent >= (int)(_prm._p1)) {
                            //p1 �ɓ��B����� ������
                            _acce = 0;
                            _velo = _prm._top_velo;
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 2) {
                        //_TRACE_("������ _prm._frame_of_spent="<<_prm._frame_of_spent<<" _prm._p2="<<_prm._p2);
                        //������
                        if (_prm._frame_of_spent >= (int)(_prm._p2)) {
                            //_TRACE_("p2 �ɓ��B����� ����t���[�����猸���� _prm._frame_of_spent="<<_prm._frame_of_spent<<" _prm._p2="<<_prm._p2);
                            //p2 �ɓ��B����� ����t���[�����猸����
                            VAL_TYPE acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                            _acce = acc;
                            //_TRACE_("���������x _acce="<<_acce);
                            _prm._progress++;
                        }
                    }
                    if (_prm._progress == 3) {
                        //������
                        //_TRACE_("������");
                        if (_prm._frame_of_spent & 1 == 0) { //2���1��
                            //_TRACE_("�␳�E�␳�E�␳");
                            //�␳�E�␳�E�␳
                            //�Ō�̑�`�␳
                            //D = (1/2)*(V+Ve)*Te
                            double Ve = _prm._end_velo;
                            double Te = _prm._target_frames - _prm._frame_of_spent;
                            //_TRACE_("Ve = "<<Ve);
                            //_TRACE_("Te = "<<Te);
                            if (Te > 0) {
                                double D = _prm._target_distance2 - _prm._moved2;
                                double V =(2.0*D-Te*Ve)/Te;
                                //_TRACE_("D = "<<D);
                                //_TRACE_("V = "<<V);
                                _velo = V;
                                //_TRACE_("���x _velo = "<<_velo<<" �ɕ␳");
                                VAL_TYPE acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                                _acce = acc;
                                //_TRACE_("�����x _acce = "<<_acce<<" �ɕ␳");
                            }
                        }
                        //_TRACE_("_prm._frame_of_spent="<<_prm._frame_of_spent<< " _prm._target_frames="<<_prm._target_frames);
                        if (_prm._frame_of_spent >= _prm._target_frames) {
                            //_TRACE_("_prm._frame_of_spent >= _prm._target_frames �����A�����܂��ȕ��͋C");
                            _velo = _prm._end_velo;
                            if (_prm._endacc_flg) {
                                _acce = (VAL_TYPE)0.0;
                            }
                            if (ZEROd_EQ(_prm._end_velo)) {
                                //�ŏI���x��0�̏ꍇ�A�o�b�`�����킹�����݂�B
                                if (ZEROd_EQ(_prm._target_distance2 - _prm._moved2)) {
                                    //���Ƀo�b�`�������Ă��܂���
                                    //_TRACE_("���Ƀo�b�`�������Ă��܂���");
                                    //_TRACE_("�����܂�1���I");
                                    _velo = (VAL_TYPE)0.0;
                                    _prm._flg = false; //�����܂�
                                } else {
                                    //����Ă�B
                                    _velo = (_prm._target_distance2 - _prm._moved2); //�o�b�`�����킹��āA�����P�t���[��
                                    //_TRACE_("�o�b�`�����킹��������_velo="<<_prm._target_distance2<<"-"<<_prm._moved2<<"="<<_velo);
                                    _prm._progress++;
                                }
                            } else {
                                //�ŏI���x��0�ł͂Ȃ��B���̂܂܏I��
                                //_TRACE_("�����܂�2");
                                _prm._flg = false; //�����܂�
                            }
                        }
                    } else if (_prm._progress == 4) {
                        //_TRACE_("�o�b�`�����킹�Ă����܂�");
                        _velo = (VAL_TYPE)0.0;
                        _prm._flg = false; //�����܂�
                    }
                }
            }

            _velo += _acce;
            _value += _velo;

            _prm._moved += ABS(_velo);
            _prm._moved2 += _velo;

            //_TRACE_(_prm._target_frames<<":after _value="<<_value<<" _velo="<<_velo<<" _acce="<<_acce<<" _prm._moved="<<_prm._moved<<" _prm._moved2="<<_prm._moved2<<"");
            _prm._frame_of_spent++;
        } else {
            _prm._progress = -1;
        }
#ifdef MY_DEBUG
        if (_prm._frame_of_spent > 60*60*10) {
            throwGgafCriticalException("GgafValueAccelerator::behave() 10���ȏ㊊����ςȂ��Ȃ�ł����I");
        }
#endif

    }

    virtual ~GgafValueAccelerator() {
    }
};

}
#endif /*GGAFCORE_GGAFVALUEACCELERATOR_H_*/

