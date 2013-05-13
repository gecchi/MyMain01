#ifndef FIXEDFRAMESPLINEKUROKOLEADER_H_
#define FIXEDFRAMESPLINEKUROKOLEADER_H_
namespace GgafLib {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�A����A(GgafDxCore::GgafDxKurokoA)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineKurokoLeader : public SplineKurokoLeader {

public:
    /** [r]�X�v���C�����Z�b�g(spl�t�@�C���̏��ɑ���) */
    FixedFrameSplineManufacture* _pFixedFrameSplManuf;

    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;
    frame _hosei_frames;
    /** �O���_point_index */
    int _prev_point_index;

public:
    /**
     *
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKurokoA
     */
    FixedFrameSplineKurokoLeader(SplineManufacture* prm_pManufacture,
                                 GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

    FixedFrameSplineKurokoLeader(GgafDxCore::GgafDxKurokoA* prm_pKurokoA,
                                 SplineLine* prmpSpl,
                                 frame prm_spent_frame,
                                 angvelo prm_angveloRzRyMv);
    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void start(SplinTraceOption prm_option = ABSOLUTE_COORD) override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    void behave() override;

    /**
     * �⊮�_�̍��W���擾���� .
     * @param prm_point_index �⊮�_�̃C���f�b�N�X (0�`)
     * @param out_X �Ή�����X���W(�߂�l)
     * @param out_Y �Ή�����Y���W(�߂�l)
     * @param out_Z �Ή�����Z���W(�߂�l)
     */
    void getPointCoord(int prm_point_index, coord& out_X, coord& out_Y, coord& out_Z) override;

    virtual ~FixedFrameSplineKurokoLeader();
};

}
#endif /*FIXEDFRAMESPLINEKUROKOLEADER_H_*/
