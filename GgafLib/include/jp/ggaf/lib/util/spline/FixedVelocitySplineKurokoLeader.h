#ifndef GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * �����ړ��X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA�����X�s�[�h�ňړ����܂��B<BR>
 * ���̕⊮�_�܂ł̋����𑪂�A���݂̈ړ����x����A���������������Z���u�c��ړ������v�����߂�B
 * �c��ړ�������0�ɂȂ�΁A���̕⊮�_�Ɍ�����ς��Ȃ���܂������𑪂�E�E�E���J��Ԃ��܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���ł��Z���Ƃ���ł��ړ����x�ɉe���͂���܂���B<BR>
 * ���̂悤�ɓ��삷��悤�A����(GgafDxCore::GgafDxKuroko)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineKurokoLeader : public SplineLeader {


public:
    GgafDxCore::GgafDxKuroko* _pKuroko_target;
    /** [r]�X�v���C�����Z�b�g(spl�t�@�C���̏��ɑ���)  */
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _leadning_float_frames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_leadning_fFrames */
    float _float_frame_of_next;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     */
    FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture, GgafDxCore::GgafDxKuroko* prm_pKuroko_target);

    virtual void restart() override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedVelocitySplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
