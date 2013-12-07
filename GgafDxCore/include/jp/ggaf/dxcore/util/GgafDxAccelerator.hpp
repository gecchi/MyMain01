#ifndef GGAFDXCORE_GGAFDXACCELERATOR_H_
#define GGAFDXCORE_GGAFDXACCELERATOR_H_
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafUtil.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using GgafDxCore::GgafDxUtil;

namespace GgafDxCore {

/**
 * �l�̉����� .
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
template<class T>
class GgafDxAccelerator : public GgafCore::GgafObject {
public:


    class SmoothPrm {
     public:
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s����true */
         bool _flg;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�����s�������̉����x�ݒ�itrue�F�����x0�ɐݒ�^false:�����x�����̂܂܂ɂ��Ă����j */
         bool _endacc_flg;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�g�b�v�X�s�[�h�i�����ړ������x�j */
         T _top_velo;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�I�����̑��x */
         T _end_velo;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ʒu���B�܂łɕK�v�Ȏ����̈ړ������i�����ړ��������܂ށj */
         T _target_distance;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�Őݒ肳�ꂽ�ڕW�ʒu�܂ł̒������� */
         T _target_distance2;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ō��܂łɈړ������ړ��������v�i�����ړ��������܂ށj */
         T _moved;
         T _moved2;
         /** [r]�Ȃ߂炩�ړ��V�[�N�G���X�ňړ����x�����𔽓]����܂ł̐ݒ肳�ꂽ�񕜎������x */
         T _acce_a0;
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
    T _value;
    T _velo;
    T _acce;
    SmoothPrm _prm;
public:
    GgafDxAccelerator() {
        _value = 0;
        _velo = 0;
        _acce = 0;
    }

    void accelerateByDt(T prm_target_value_distance,
                       frame prm_target_frames,
                       double prm_p1, double prm_p2, T prm_end_velo,
                       bool prm_endacc_flg = true) {
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            return;
        }
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
            _prm._progress = 0;
        } else {
            //        ���x(v)
            //         ^
            //         |                           D2-D1:�ڕW�ړ�����
            //         |                              V0:�����_�̑��x
            //         |                              Vt:�g�b�v�X�s�[�h
            //         |                              Ve:�ŏI���x
            //       Vt|................�Q�Q�Q�Q�Q�Q           Te:�ڕW���ԁi�t���[�����j
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
            _prm._progress = 0;
        }

    }

    void accelerateByVd(T prm_top_velo,
                       T prm_target_value_distance,
                       double prm_p1, double prm_p2, T prm_end_velo,
                       bool prm_endacc_flg = true) {
        int s_d = SGN(prm_target_value_distance);
        int sgn_W0 = SGN(_velo);
        if (ZEROd_EQ(prm_target_value_distance)) {
            return;
        }
        if (sgn_W0 == 0 || s_d == sgn_W0) {  //��������v
            //
            //        �p���x(V)                        V0:�����_�̑��x     (_veloMv)
            //         ^                               Vt:�g�b�v�X�s�[�h   (prm_top_angvelo)
            //         |                               Ve:�ŏI���x         (prm_end_angvelo)
            //         |                                D:�ڕW��]�����pD  (D1+D2+D3)                     �E�E�E �v�Z���ċ��߂�
            //         |                               p1:�g�b�v�X�s�[�h�ɒB����p�����ƂȂ�悤�ȁA�p����(D)�ɑ΂��銄��
            //         |       D=D1+D2+D3                  �܂�     D1 = D*p1 �ƂȂ�悤�� p1 (0.0�`1.0)
            //       Vt|....___________                p2:�������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄��
            //         |   /|         |�_                   �܂� D1+D2 = D*p2 �ƂȂ�悤�� p2 (0.0�`1.0)
            //       Ve|../.|.........|..�_            T1: D1     = D*p1 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
            //         | /  |         |    |           T2: D1+D2 = D*p2 �ɔ�₳���K�v���ԃt���[����     �E�E�E �v�Z���ċ��߂�
            //         |/   |         |    |           Te:��₳���K�v���ԃt���[����                        �E�E�E �v�Z���ċ��߂�
            //       V0| D1 |    D2   | D3 |
            //         |    |         |    |
            //       --+----+---------+----+-----> ����(t:�t���[��)
            //       0 |    T1        T2   Te
            double V0 = _velo;
            double Vt = ABS(prm_top_velo) * s_d;
            double Ve = ABS(prm_end_velo) * s_d;
            _prm._flg = true;
            _prm._endacc_flg = prm_endacc_flg;
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
            _prm._progress = 2; //�񕜃t�F�[�Y���΂�
        } else {
            //                                                       V0:�����_�̑��x      (_veloMv)
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
            //        |
            //
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
            double s = (V0*V0)/(2.0*a0);
            double Dp = s + prm_target_value_distance;
            _prm._flg = true;
            _prm._endacc_flg = prm_endacc_flg;
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
            _prm._progress = 0; //�񕜃t�F�[�Y����
        }
    }

    bool isAcce() {
        return _prm._flg;
    }

    void behave() {
        //�Ȃ߂炩�ړ��V�[�N�G���X�N����
        if (_prm._flg) {
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
                    T acc = UTIL::getAcceByVd(_velo, _prm._top_velo, _prm._p1*_prm._target_sgn);
                    _acce = acc;
                    if (ABS(_acce) > ABS(_prm._target_distance2)) {
                        _acce = _prm._target_distance2;
                    } else if (ABS(_acce) > ABS(_prm._top_velo)) {
                        _acce = _prm._top_velo;
                    }
                    _prm._progress++;
                }
                if (_prm._progress == 3) {
                    //������
                    if (_prm._moved >= _prm._p1) {
                        //p1 �ɓ��B����� ������
                        _acce = 0;
                        _velo = _prm._top_velo;
                        T diff_to_end = _prm._target_distance2 - _prm._moved2;
                        if (ABS(_velo) > ABS(diff_to_end)) {
                            _velo = diff_to_end;
                        }
                        _prm._progress++;
                    }
                }
                if (_prm._progress == 4) {
                    //������
                    if (_prm._moved >= _prm._p2) {
                        T diff_to_end = _prm._target_distance2 - _prm._moved2;
                        if (!ZEROd_EQ(diff_to_end)) {
                            //p2 �ɓ��B����� ����t���[�����猸����
                            T acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                            _acce = acc;
                            if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                _acce = diff_to_end-_velo;
                            }
                        }
                        _prm._progress++;
                    }
                }
                if (_prm._progress == 5) {
                    //������
                    T diff_to_end = _prm._target_distance2 - _prm._moved2;
                    //t=(2*D)/V
                    double t = (2.0*diff_to_end)/_velo; //�c�t���[����
                    if (t > 1 && _prm._frame_of_spent % 4U == 0) {
                        //�␳�E�␳�E�␳
                        if (!ZEROd_EQ(diff_to_end)) {
                            T acc = UTIL::getAcceByVd(_velo, _prm._end_velo, diff_to_end);
                            _acce = acc;
                            if (ABS(_velo)+ABS(acc) > ABS(diff_to_end)) {
                                _acce = diff_to_end-_velo;
                            }
                        }
                    }
                    T end_velo = _prm._end_velo;

                    if ( ABS(_prm._target_distance2 - _prm._moved2) <=  ABS(_prm._top_velo)*0.00001 ||
                         (ZEROd_EQ(_prm._top_velo)  || (_prm._top_velo > 0  && diff_to_end <= 0) || (_prm._top_velo < 0  && diff_to_end >= 0) ) || //�ʂ�z������
                         (ZEROd_EQ(_velo+end_velo)  || (_velo+end_velo  >  0 && _velo +end_velo + _acce < 0 ) || (_velo+end_velo  <  0 && _velo +end_velo+_acce > 0) ) //�͂������]������
                    ) {
                        //�ڕW�����֓��B
                        if (ZEROd_EQ(end_velo)) {
                            _velo =(_prm._target_distance2 - _prm._moved2);   //�o�b�`�����킹��
                        } else {
                            _velo = _prm._end_velo;
                        }
                        if (_prm._endacc_flg) {
                            _acce = 0.0;
                        }
                        _prm._progress++;
                    }
                } else if (_prm._progress == 6) {
                    _velo = _prm._end_velo;
                    _prm._flg = false; //�����܂�
                }
            } else {
                //�ڕW���Ԏw��̏ꍇ
                if (_prm._progress == 0) {
                    //�����ݒ�
                    T acc = UTIL::getAcceByTv(_prm._p1, _velo, _prm._top_velo);
                    _acce = acc;
                    _prm._progress++;
                }
                if (_prm._progress == 1) {
                    //������
                    if (_prm._frame_of_spent >= _prm._p1) {
                        //p1 �ɓ��B����� ������
                        _acce = 0;
                        _velo = _prm._top_velo;
                        _prm._progress++;
                    }
                }
                if (_prm._progress == 2) {
                    //������
                    if (_prm._frame_of_spent >= _prm._p2) {
                        //p2 �ɓ��B����� ����t���[�����猸����
                        T acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                        _acce = acc;
                        _prm._progress++;
                    }
                }
                if (_prm._progress == 3) {
                    //������
                    if (_prm._frame_of_spent % 4U == 0) {
                        //�␳�E�␳�E�␳
                        //�Ō�̑�`�␳
                        //D = (1/2)*(V+Ve)*Te
                        double Ve = _prm._end_velo;
                        double Te = _prm._target_frames - _prm._frame_of_spent;
                        if (Te > 0) {
                            double D = _prm._target_distance2 - _prm._moved2;
                            double V =(2.0*D-Te*Ve)/Te;
                            _velo = V;
                            T acc = UTIL::getAcceByTv(_prm._target_frames - _prm._frame_of_spent, _velo, _prm._end_velo);
                            _acce = acc;
                        }
                    }
                    if (_prm._frame_of_spent > _prm._target_frames) {
                        if (ZEROd_EQ(_prm._end_velo)) {
                            _velo = (_prm._target_distance2 - _prm._moved2); //�o�b�`�����킹��
                        } else {
                            _velo = _prm._end_velo;
                        }
                        if (_prm._endacc_flg) {
                            _acce = 0;
                        }
                        _prm._progress++;
                    }
                } else if (_prm._progress == 4) {
                    _velo = _prm._end_velo;
                    _prm._flg = false; //�����܂�
                }
            }

            _velo += _acce;
            _value += _velo;

            _prm._moved += ABS(_velo);
            _prm._moved2 += _velo;

            _prm._frame_of_spent++;
        } else {
            _prm._progress = -1;
        }

    }

    virtual ~GgafDxAccelerator() {
    }
};

}
#endif /*GGAFDXCORE_GGAFDXACCELERATOR_H_*/

