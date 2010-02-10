#ifndef GGAFDX9GEOMETRICACTOR_H_
#define GGAFDX9GEOMETRICACTOR_H_
namespace GgafDx9Core {

/**
 * ���W���������̃A�N�^�[.
 * ���[���h���W�A�����͕ϊ��ςݍ��W�̉��ꂩ�������A<BR>
 * ���W�֘A���\�b�h��������A�N�^�[�ł��B<BR>
 * (��GgafDx9UntranceformedActor ��GgafDx9TranceformedActor �𓝍�)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDx9GeometricActor : public GgafDx9BaseActor {

private:

public:

    /** �ϊ��ςݍ��W�ł��邩(true:�{�A�N�^�[�͕ϊ��ςݍ��W/false:�{�A�N�^�[�̓��[���h���W) */
    bool _isTransformed;

    /** ���[���hX���W(_X/LEN_UNIT/PX_UNIT -> DirectX��X���W) */
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

    /** ���E���̔��a�B���̃I�u�W�F�N�g�̃��[�J�����W�̌��_����S���_�̋����ōő�̒����B��ʊO����Ɏg�p����� */
    FLOAT _bounding_sphere_radius;

    /** directX�̃��[���hX���W */
    FLOAT _fX;
    /** directY�̃��[���hY���W */
    FLOAT _fY;
    /** directZ�̃��[���hZ���W */
    FLOAT _fZ;
    /** ����O�̎��g�̍��W���王�����ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnTop;
    /** ����O�̎��g�̍��W���王���䉺�ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnBottom;
    /** ����O�̎��g�̍��W���王���䍶�ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnLeft;
    /** ����O�̎��g�̍��W���王����E�ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnRight;
    /** ����O�̎��g�̍��W���王�����O�ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnFront;
    /** ����O�̎��g�̍��W���王���䉜�ʂ܂ł̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDistance_plnBack;

    int _offscreenkind;
    bool _delete_pChecker;



    //TODO:�N���A�N�^�[�ƋN���A�N�^�[����̃I�t�Z�b�g�󂯎M
    GgafDx9GeometricActor* _pActorOrigin;
    velo _offset_origin_veloMv;
    int _offset_origin_X;
    int _offset_origin_Y;
    int _offset_origin_Z;
    angle _offset_origin_angRxMove;
    angle _offset_origin_angRyMv;
    angle _offset_origin_angFace[3];


    /** ���g�̌��݂�World�ϊ��s�� */
    D3DXMATRIX _matWorld;

    /** �ړ��p���W�v�Z�x���I�u�W�F�N�g */
    GgafDx9GeometryMover* _pMover;

    //�⑫
    //�y_X, _Y, _Z �̒P�ʂɂ��āz
    //�@�̂蓾��l�� DirectX���W(float)�� LEN_UNIT(=1000)�{��PX_UNIT(=10)�{�̐����l�ł���B
    //�@DirectX���W��10�͉�ʏ��1px�����̑傫���ɂȂ�i�悤�ɃJ�����������Ă���j�B
    //�@���������āA_X = 5000 ��5px�����̈ʒu�ƍl���Đ݌v�����B
    //�@�`��̒��O�� LEN_UNIT*PX_UNIT �ŏ��Z���ꃏ�[���h�ϊ��Ɏg�p�����B
    //�@�Ȃ�ł��Ƃ����Ɛ����ō��W�v�Z���ď����ł������������������߁B
    //�@�̂͗ǂ��g������@�����Afloat�ł������̂ŁA�悩�����̂��ǂ��������B
    //�y_RX, _RY, _RZ �̒P�ʂɂ��āz
    //�@�Ǝ��P�ʂ́u�A���O���l�v���̂�B�u�A���O���l�v�Ƃ� 0~360000 �̒l�ŁA1000�{�̐��x�̊p�x�l�ł���B
    //�@���S�p�Ɠ�����3���̕�����0�Ƃ��A�����v���ɃA���O���l�͑�������̂Ƃ���B���p�̒l��90000�A������180000�ł���B
    //�y_SX, _SY, _SZ �̒P�ʂɂ��āz
    //�@�`��̒��O�� 1000 �ŏ��Z����A�g��k���̕ϊ��Ɏg�p�����B
    //�@1000���P�{�̃X�P�[���Ӗ�����B���������ăf�t�H���g��1000�ɂȂ��Ă���B


    /** �ϊ��ς݃I�u�W�F�N�g�̏ꍇ��X���W(-1.0 <= _x < 1.0) */
    float _x;
    /** �ϊ��ς݃I�u�W�F�N�g�̏ꍇ��Y���W(-1.0 <= _y < 1.0) */
    float _y;
    /** �ϊ��ς݃I�u�W�F�N�g�̏ꍇ�̐[�x (0.0 <= _z < 1.0) */
    float _z;
    /** �`�F�b�J�[�I�u�W�F�N�g */
    GgafDx9Checker* _pChecker;

    /** WORLD�ϊ��s��ݒ�p�ÓI�����o�֐� */
    void (*_pFunc_calcWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);

    /**
     *
     * @param prm_name �A�N�^�[��
     * @param prm_pChecker �`�F�b�J�[(���g�p��NULL)
     * @return
     */
    GgafDx9GeometricActor(const char* prm_name,
                              GgafDx9Checker* prm_pChecker);

    virtual GgafDx9GeometricActor* getPrev() override {
        return (GgafDx9GeometricActor*)GgafActor::getPrev();
    }

    virtual GgafDx9GeometricActor* getNext() override {
        return (GgafDx9GeometricActor*)GgafActor::getNext();
    }

    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override;

    /** ���낢��Ȍv�Z���s���Ă��� */
    virtual void processPreJudgement() override;

    /**
     * ��ʓ��ɕ\������Ă��邩����
     * @return 0:Viewport�͈͓�
     */
    virtual int isOffscreen();

    virtual bool isOutOfGameSpace();

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

    void defineWorldMatrix(void (*prm_pFunc)(GgafDx9GeometricActor*, D3DXMATRIX&)) {
        _pFunc_calcWorldMatrix = prm_pFunc;
    }



    static int sign(float x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }

    }

    virtual ~GgafDx9GeometricActor(); //�f�X�g���N�^

    /**
     * �f�o�b�O�p�F�c���[�\����\��<BR>
     */
    virtual void dump();

    /**
     * �f�o�b�O�p�Fdump()����g�p�����<BR>
     */
    virtual void dump(std::string prm_parent);

};

}
#endif /*GGAFDX9GEOMETRICACTOR_H_*/
