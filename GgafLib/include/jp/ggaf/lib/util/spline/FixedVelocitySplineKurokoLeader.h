#ifndef GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

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
class FixedVelocitySplineKurokoLeader : public SplineKurokoLeader {
private:
    void restart();

public:
    /** [r]�X�v���C�����Z�b�g(spl�t�@�C���̏��ɑ���)  */
    FixedVelocitySplineManufacture* _pFixedVeloSplManuf;

    /** [r]����x�ňړ������ꍇ�̃X�v���C���ړ����̌o�߃t���[���� */
    float _leadning_fFrames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_leadning_fFrames */
    float _fFrame_of_next;
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
    FixedVelocitySplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @param prm_angveloRzRyMv 1�t���[��������̐���\�ȉ�]�p�p���x (1000 �� 1�x)
     * @return
     */
    FixedVelocitySplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp,
                                    angvelo prm_angveloRzRyMv);


    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� ABSOLUTE_COORD:��΍��W�ړ�
     *                              RELATIVE_COORD:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     *                              RELATIVE_DIRECTION:�n�_��Actor�̌����W�Ƃ݂Ȃ��A
     *                                                 �A�N�^�[�̌��݌����i_pKuroko �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     * @param prm_max_loop �J��Ԃ��񐔁B0�ȉ��Ŗ������[�v
     */
    void start(SplinTraceOption prm_option, int prm_max_loop = 1) override;



    /**
     * ���t���[���̐U�镑�����\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    void behave() override;

    /**
     * �⊮�_�̍��W���擾���� .
     * @param prm_point_index �⊮�_�̃C���f�b�N�X (0�`)
     * @param out_x �Ή�����X���W(�߂�l)
     * @param out_y �Ή�����Y���W(�߂�l)
     * @param out_z �Ή�����Z���W(�߂�l)
     */
    void getPointCoord(int prm_point_index, coord& out_x, coord& out_y, coord& out_z) override;

    virtual ~FixedVelocitySplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/