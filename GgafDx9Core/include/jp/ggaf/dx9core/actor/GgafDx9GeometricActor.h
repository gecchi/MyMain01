#ifndef GGAFDX9GEOMETRICACTOR_H_
#define GGAFDX9GEOMETRICACTOR_H_
namespace GgafDx9Core {

/**
 * ���W���������̃A�N�^�[.
 * ���[���h���W�A�����͕ϊ��ςݍ��W�̉��ꂩ�������A<BR>
 * ���W�֘A���\�b�h��������A�N�^�[�ł��B<BR>
 */
class GgafDx9GeometricActor : public GgafDx9BaseActor {

private:

public:

    /** �ϊ��ςݍ��W�ł��邩 */
    bool _isTransformed;

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

    D3DXMATRIX _matWorld; //���g�̌��݂�World�ϊ��s��
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


    /** �ϊ��ς݉��X���W */
    float _x;
    /** �ϊ��ς݉��Y���W */
    float _y;
    /** �[�x (0.0 <= _z < 1.0) */
    float _z;


    GgafDx9Checker* _pChecker;

    const int _X_OffScreenLeft;
    const int _X_OffScreenRight;
    const int _Y_OffScreenTop;
    const int _Y_OffScreenBottom;

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_name ���ʖ�
     */
    GgafDx9GeometricActor(const char* prm_name,
                              GgafDx9Checker* prm_pChecker);

    virtual GgafDx9GeometricActor* getPrev() {
        return (GgafDx9GeometricActor*)GgafActor::getPrev();
    }

    virtual GgafDx9GeometricActor* getNext() {
        return (GgafDx9GeometricActor*)GgafActor::getNext();
    }

    virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent);

    virtual bool isOffScreen();

    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    /**
     * world�ϊ��s��ݒ� .
     * �g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��Y����]������܂���B_RY���Q��ڂ�X����]�ƂȂ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �r���{�[�hX����] �~ �r���{�[�hY����] �~ �r���{�[�hZ����]  �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ� <BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void getWorldMatrix_BillBoardXYZ_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void getWorldMatrix_BillBoardX_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    virtual ~GgafDx9GeometricActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9GEOMETRICACTOR_H_*/
