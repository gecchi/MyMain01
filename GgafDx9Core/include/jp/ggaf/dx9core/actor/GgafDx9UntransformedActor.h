#ifndef GGAFDX9UNTRANSFORMEDACTOR_H_
#define GGAFDX9UNTRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * ���ϊ����W�̃A�N�^�[.
 * ���ϊ�3�������W�i���[���h/�r���[/�ˉe�ϊ������Ă��Ȃ����W�j�������A<BR>
 * ���W�ϊ����\�b�h��������A�N�^�[�ł��B<BR>
 */
class GgafDx9UntransformedActor : public GgafDx9BaseActor {

private:

public:

    /** �� (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    /** ���[���hX���W */
    int _X;
    /** ���[���hY���W */
    int _Y;
    /** ���[���hZ���W */
    int _Z;
    /** ���[���hX����]�p */
    angle _RX;
    /** ���[���hY����]�p */
    angle _RY;
    /** ���[���hZ����]�p */
    angle _RZ;
    /** ���[���hX�������{�� */
    int _SX;
    /** ���[���hY�������{�� */
    int _SY;
    /** ���[���hZ�������{�� */
    int _SZ;

    //�⑫
    //�y_X, _Y, _Z �̒P�ʂɂ��āz
    //�@�̂蓾��l�� DirectX���[���h���W(float)�� 1000�{�̐����l�ł���B
    //�@�`��̒��O�� 1000 �ŏ��Z���ꃏ�[���h�ϊ��Ɏg�p�����B
    //�@�Ȃ�ł��Ƃ����Ɛ����ō��W�v�Z���ď����ł������������������߁B
    //�@�̂͗ǂ��g������@�����Afloat�ł������̂ŁA�悩�����̂��ǂ��������B
    //�y_RX, _RY, _RZ �̒P�ʂɂ��āz
    //�@�Ǝ��P�ʂ́u�A���O���l�v���̂�B�u�A���O���l�v�Ƃ� 0~360000 �̒l�ŁA1000�{�̐��x�̊p�x�l�ł���B
    //�@�~���p�Ɠ�����3���̕�����0�Ƃ��A�����v���ɃA���O���l�͑�������̂Ƃ���B���p�̒l��90000�A������180000�ł���B
    //�y_SX, _SY, _SZ �̒P�ʂɂ��āz
    //�@�`��̒��O�� 1000 �ŏ��Z����A�g��k���̕ϊ��Ɏg�p�����B
    //�@1000���P�{�̃X�P�[���Ӗ�����B���������ăf�t�H���g��1000�ɂȂ��Ă���B


    GgafDx9GeometryMover* _pGeoMover;

    GgafDx9GeometryChecker* _pGeoChecker;

    const int _X_OffScreenLeft;
    const int _X_OffScreenRight;
    const int _Y_OffScreenTop;
    const int _Y_OffScreenBottom;

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_name ���ʖ�
     */
    GgafDx9UntransformedActor(const char* prm_name,
                              GgafDx9GeometryMover* prm_pGeoMover,
                              GgafDx9GeometryChecker* prm_pGeoChecker);

    virtual GgafDx9UntransformedActor* getPrev() {
        return (GgafDx9UntransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9UntransformedActor* getNext() {
        return (GgafDx9UntransformedActor*)GgafActor::getNext();
    }

    virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent);

    virtual bool isOffScreen();

    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    virtual void setGeometry(GgafDx9UntransformedActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    /**
     * _Z�̒l�ɂ��A��܂��Ƀ����_�����O������ݒ肷��B
     * �C�ӂ̗D�揇�ʂŃ����_�����O�������ꍇ�́A���̃��\�b�h���I�[�o�[���C�h��
     * GgafUniverse::_apAlphaActorList_DrawDepthLevel[n] �̍D���� n �� addSubLast(this) ���s���ĉ������B
     * �A�� 0 �� n �� MAX_DRAW_DEPTH_LEVEL
     * TODO:private virtual �ɂ���ׂ����ۂ��H�Bfainal ���~����
     */
    virtual void processDrawPrior();

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }

    /**
     * world�ϊ��s��ݒ� .
     * �g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_ScRxRzRyMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);


    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRzRyScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRyRzScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��Y����]������܂���B_RY���Q��ڂ�X����]�ƂȂ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRzRxScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_ScRzMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �r���{�[�hX����] �~ �r���{�[�hY����] �~ �r���{�[�hZ����]  �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ� <BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_BillBoardXYZ_ScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void getWorldMatrix_BillBoardX_RzRyScMv(GgafDx9UntransformedActor* prm_pActor, D3DXMATRIX& out_matWorld);

    virtual ~GgafDx9UntransformedActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9UNTRANSFORMEDACTOR_H_*/
