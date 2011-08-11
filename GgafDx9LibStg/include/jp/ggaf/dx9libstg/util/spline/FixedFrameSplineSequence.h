#ifndef FIXEDFRAMESPLINESEQUENCE_H_
#define FIXEDFRAMESPLINESEQUENCE_H_
namespace GgafDx9LibStg {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��B .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineSequence : public SplineSequence {

public:

    FixedFrameSplineManufacture* _pFixedFrameSplineManufacture;

    //�v�Z�p�萔
    float _SIN_RzMv_begin;
    float _COS_RzMv_begin;
    float _SIN_RyMv_begin;
    float _COS_RyMv_begin;

    FixedFrameSplineSequence(SplineManufacture* prm_pManufacture,
                             GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA);

    FixedFrameSplineSequence(GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA,
                             Spline3D* prmpSpl,
                             frame prm_spent_frame,
                             ang_velo prm_ang_veloRzRyMv);
    /**
     * �X�v���C���Ȑ����p�̃t���[�����w��ړ��v���O�����J�n
     * @param prm_option �I�v�V���� 0:��΍��W�ړ��^1:�n�_��Actor�̌����W�Ƃ݂Ȃ��A��������̑��΍��W�ړ�
     */
    void exec(int prm_option = 0) override;

    /**
     * �ړ����s���\�b�h .
     * �ړ��̂��߂ɖ��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    void behave() override;

    virtual ~FixedFrameSplineSequence();
};

}
#endif /*FIXEDFRAMESPLINESEQUENCE_H_*/
