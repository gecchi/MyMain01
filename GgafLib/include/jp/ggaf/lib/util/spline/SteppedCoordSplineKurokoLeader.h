#ifndef GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#define GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * TODO:�쐬���I�g���܂���I
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineKurokoLeader : public SplineKurokoLeader {

    void restart();

public:
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _leadning_fFrames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_leadning_fFrames */
    float _fFrame_of_next;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;

    //�v�Z�p
    float _sinRzMv_begin;
    float _cosRzMv_begin;
    float _sinRyMv_begin;
    float _cosRyMv_begin;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     */
    SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    SteppedCoordSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp,
                                    angvelo prm_angveloRzRyMv);


    void start(SplinTraceOption prm_option, int prm_max_loop = 1) override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;


    virtual ~SteppedCoordSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
