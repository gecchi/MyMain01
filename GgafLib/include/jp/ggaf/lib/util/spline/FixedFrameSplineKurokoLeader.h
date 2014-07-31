#ifndef GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#define GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�A����(GgafDxCore::GgafDxKuroko)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoLeader : public SplineKurokoLeader {
private:
    void restart();

public:
    /** [r]�X�v���C�����Z�b�g(spl�t�@�C���̏��ɑ���) */
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //�v�Z�p�萔
    float _sinRzMv_begin;
    float _cosRzMv_begin;
    float _sinRyMv_begin;
    float _cosRyMv_begin;
    frame _hosei_frames;
    /** �O���_point_index */
    int _prev_point_index;

public:
    /**
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKuroko
     */
    FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    FixedFrameSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                 SplineLine* prm_pSpl,
                                 frame prm_spent_frame,
                                 angvelo prm_angveloRzRyMv);
    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� ABSOLUTE_COORD:��΍��W�ړ�
     *                              RELATIVE_COORD:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     *                              RELATIVE_DIRECTION:�n�_��Actor�̌����W�Ƃ݂Ȃ��A
     *                                                 �A�N�^�[�̌��݌����i_pKuroko �� _ang_rz_mv, _ang_ry_mv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     * @param prm_max_loop �J��Ԃ��񐔁B0�ȉ��Ŗ������[�v
     */
    void start(SplinTraceOption prm_option, int prm_max_loop = 1) override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
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

    virtual ~FixedFrameSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEKUROKOLEADER_H_*/
