#ifndef GGAFDXCORE_GGAFDXKUROKOASSISTANT_H_
#define GGAFDXCORE_GGAFDXKUROKOASSISTANT_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/core/util/GgafValueAccelerator.hpp"

namespace GgafDxCore {

/**
 * ���߂̏���A .
 * �t��(����)�̈ړ����x�̕⍲���s���܂��B
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoAssistantA : public GgafCore::GgafObject {

public:
    /** [r]�t�� */
    GgafDxKuroko* const _pMaster;
    GgafCore::GgafValueAccelerator<int> _smthMv;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pMaster  �t��
     */
    explicit GgafDxKurokoAssistantA(GgafDxKuroko* prm_pMaster);


    /**
     * �Ȃ߂炩�Ȉړ����x��ω�������V�[�N�G���X�����s(���ԁE�����w��A���x�ϓ�) .
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
    void slideMvByDt(coord prm_target_distance, int prm_target_frames,
                     float prm_p1, float prm_p2, velo prm_end_velo,
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
     * @param prm_top_velo �g�b�v�X�s�[�h(Vt) (>=0)
     * @param prm_target_distance �ڕW�����ړ�����(D)
     * @param prm_p1 �g�b�v�X�s�[�h�ɒB���鋗���ƂȂ�悤�ȁA����(D)�ɑ΂��銄���B(d1 = D*prm_p1)
     * @param prm_p2 �������J�n�����ƂȂ�悤�ȁA����(D)�ɑ΂��銄�� (d1+d2 = D*p2)
     * @param prm_end_velo �ŏI�X�s�[�h(Ve) (>=0)
     * @param prm_zero_acc_end_flg true:�ڕW���ԂɒB�����ۂɉ����x���O�ɋ����ݒ�/false:�����x�͂��̂܂܂ɂ��Ă���
     */
    void slideMvByVd(velo prm_top_velo, coord prm_target_distance,
                     float prm_p1, float prm_p2, velo prm_end_velo,
                     bool prm_zero_acc_end_flg);

    bool isSlidingMv() {
        return _smthMv.isAccelerating();
    }

    void stopSlidingMv() {
        _smthMv.stopAccelerating();
    }

    bool hasJustFinishedSlidingMv() {
        return _smthMv.hasJustFinishedAccelerating();
    }
   /**
     * ���߂̏��肪�U�镑�� .
     * ���肪�A�t���ɂ��낢��ݒ���s���܂��̂ŁA�t�����U�镑��(behave())�O�Ɏ��s���܂��傤�B
     */
    virtual void behave();

    virtual ~GgafDxKurokoAssistantA();
};

}
#endif /*GGAFDXCORE_GGAFDXKUROKOASSISTANT_H_*/

