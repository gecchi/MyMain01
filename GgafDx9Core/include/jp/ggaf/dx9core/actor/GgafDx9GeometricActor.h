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
    /** ��ʊO��ʁBisOffscreen()�������Ŏg�p�B���v�Z���� -1 */
    int _offscreenkind;

public:
    /** [r] �ϊ��ςݍ��W�ł��邩(true:�{�A�N�^�[�͕ϊ��ςݍ��W/false:�{�A�N�^�[�̓��[���h���W) */
    bool _isTransformed;
    /** [r/w]���[���hX���W(��ʃs�N�Z�� : _X  = 1px : 1000) */
    int _X;
    /** [r/w]���[���hY���W(��ʃs�N�Z�� : _Y  = 1px : 1000) */
    int _Y;
    /** [r/w]���[���hZ���W(��ʃs�N�Z�� : _Z  = 1px : 1000) */
    int _Z;
    /** [r/w]���[���hX����]�p(Degree : _RX = 1�x : 1000) */
    angle _RX;
    /** [r/w]���[���hY����]�p(Degree : _RY = 1�x : 1000) */
    angle _RY;
    /** [r/w]���[���hZ����]�p(Degree : _RZ = 1�x : 1000) */
    angle _RZ;
    /** [r/w]���[���hX�������X�P�[��(�{�� : _SX = 1.0�{ : 1000) */
    int _SX;
    /** [r/w]���[���hY�������X�P�[��(�{�� : _SY = 1.0�{ : 1000) */
    int _SY;
    /** [r/w]���[���hZ�������X�P�[��(�{�� : _SZ = 1.0�{ : 1000) */
    int _SZ;
    /** [r]���[���h���W�v�Z�x���I�u�W�F�N�g */
    GgafDx9GeometryMover* _pMover;
    /** [r]�`�F�b�J�[�I�u�W�F�N�g */
    GgafDx9Checker* _pChecker;
    /** [r/w]���E���̔��a(DirectX��t�P��)�B��ʊO����Ɏg�p����� */
    FLOAT _fBoundingSphereRadius;
    /** [r]DirectX�̃��[���hX���W(_fX : _X = 0.1 : 1000) */
    FLOAT _fX;
    /** [r]DirectY�̃��[���hY���W(_fY : _Y = 0.1 : 1000) */
    FLOAT _fY;
    /** [r]DirectZ�̃��[���hZ���W(_fZ : _Z = 0.1 : 1000) */
    FLOAT _fZ;
    /** [r]����O�̎��g�̍��W���王�����ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnTop;
    /** [r]����O�̎��g�̍��W���王���䉺�ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnBottom;
    /** [r]����O�̎��g�̍��W���王���䍶�ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnLeft;
    /** [r]����O�̎��g�̍��W���王����E�ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnRight;
    /** [r]����O�̎��g�̍��W���王�����O�ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnFront;
    /** [r]����O�̎��g�̍��W���王���䉜�ʂ܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    FLOAT _fDist_VpPlnBack;
    /** [r/w]WORLD�ϊ��s��v�Z�֐� */
    void (*_pFunc_calcWorldMatrix)(GgafDx9GeometricActor*, D3DXMATRIX&);

    /** [r/w]���g�̌��݂�World�ϊ��s��(��]�ƈړ��̂�) */
    D3DXMATRIX _matWorld_RM;
    /** [r/w]���g�̌��݂�World�ϊ��s�� */
    D3DXMATRIX _matWorld;
    /** �y��ƂȂ�A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_Foundation;
    int _X_local;
    int _Y_local;
    int _Z_local;
    angle _RX_local;
    angle _RY_local;
    angle _RZ_local;
    int _X_final;
    int _Y_final;
    int _Z_final;
    angle _RX_final;
    angle _RY_final;
    angle _RZ_final;

    int _X_offset;
    int _Y_offset;
    int _Z_offset;
    angle _RX_offset;
    angle _RY_offset;
    angle _RZ_offset;


    bool _is_local;

    /** [r/w]�ϊ��ς݂̏ꍇ��X���W(-1.0 <= _x < 1.0) */
    float _x;
    /** [r/w]�ϊ��ς݂̏ꍇ��Y���W(-1.0 <= _y < 1.0) */
    float _y;
    /** [r/w]�ϊ��ς݂̏ꍇ�̐[�x (0.0 <= _z < 1.0) */
    float _z;

    //�⑫
    //�y_X, _Y, _Z �̒P�ʂɂ��āz
    //�@�̂蓾��l�� DirectX���W(float)�� LEN_UNIT(=1000)�{��PX_UNIT(=10)�{�̐����l�ł���B�܂�10000�{�B
    //�@DirectX���W�P�ʂ�1�́A�Q�[����ʏ��10px�����̑傫���ɂȂ�i�悤�ɃJ�����������Ă���j�B
    //�@�Ⴆ�΁A_X = 5000 �́A��ʂł�5px�̈ʒu�ADirectX���W�ł�50�ɂȂ�i�悤�ɐ݌v�j�B
    //�@_X,_Y,_Z ���s�N�Z���ōl�������ꍇ�́ALEN_UNIT(=1000)�Ŋ���B
    //�@DirectX���W�P�ʂ��s�N�Z���ōl�������ꍇ�́APX_UNIT(=10)���|���Z����B
    //�@�`��̒��O��_X,_Y,_Z �� (LEN_UNIT*PX_UNIT) �ŏ��Z���ꃏ�[���h�ϊ��Ɏg�p�����B
    //�@�Ȃ�����Ȃ�₱�������Ƃ����邩�Ƃ����ƁA���W�v�Z�����ׂĐ����ōs���A�����ł����������������B
    //�@float�̂܂܂��ƁA�|���Z����Z�̎��ɁA�u�����A��������double�ɂ���ł������̂Ɂv�Ɩ���v���̂��A�̂Ɉ����E�E�E�B
    //�@�S�������Ōv�Z���Ă�낤�A�Ƃ����̂����[�B
    //�@��(BASIC�̎�)�͗ǂ��g������@�Ȃ̂����A���͂�float�ł����Ȃ葬���̂ŁA�ǂ��̂��ǂ��������B
    //�y_RX, _RY, _RZ �̒P�ʂɂ��āz
    //�@�Ǝ��P�ʂ́u�A���O���l�v���̂�B�u�A���O���l�v�Ƃ� 0~3600000 �̒l�ŁA1000�{�̐��x�̊p�x�l�ł���B
    //�@1�x��1000�A0.5�x��500�B���p�̒l��90000�A������180000�ł���B
    //�@���S�p�Ɠ�����3���̕�����0�Ƃ��A�����v���ɃA���O���l�͑�������̂Ƃ���B
    //�y_SX, _SY, _SZ �̒P�ʂɂ��āz
    //�@1000���P�{�̃X�P�[���Ӗ�����B���������ăf�t�H���g��1000�ɂȂ��Ă���B
    //�@�`��̒��O�� 1000 �ŏ��Z����A�g��k���̕ϊ��Ɏg�p�����B

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[��
     * @param prm_pChecker �`�F�b�J�[(�g�p���Ȃ��� NULL)
     * @return
     */
    GgafDx9GeometricActor(const char* prm_name,
                              GgafDx9Checker* prm_pChecker);

    /**
     * ���̃A�N�^�[���擾
     * @return ���̃A�N�^�[
     */
    virtual GgafDx9GeometricActor* getPrev() override {
        return (GgafDx9GeometricActor*)GgafActor::getPrev();
    }

    /**
     * �O�̃A�N�^�[���擾
     * @return �O�̃A�N�^�[
     */
    virtual GgafDx9GeometricActor* getNext() override {
        return (GgafDx9GeometricActor*)GgafActor::getNext();
    }

    /**
     * ���菈�����O���� .
     * �@ processBehavior() ��A���W�v�Z���㏈���Ƃ��� <BR>
     *    �ȉ��̃����o�̍X�V���s���B <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     *     _fDist_VpPlnTop <BR>
     *     _fDist_VpPlnBottom <BR>
     *     _fDist_VpPlnLeft <BR>
     *     _fDist_VpPlnRight <BR>
     *     _fDist_VpPlnFront <BR>
     *     _fDist_VpPlnBack <BR>
     * �A ���[���h�ϊ��s����쐬��_matWorld�ɕێ�
     * �B processJudgement() ���Ăяo���̂��ߏ��������Ƃ��āA <BR>
     *    �A�N�^�[�̐��`�W���ؔz��ւ̓o�^���s���B <BR>
     *
     * <B>[����]</B> <BR>
     * �{���\�b�h�̓I�[�o�[���C�h�\�Ƃ��邪�A�t���[�����[�N�̕`��┻��Ɋւ��
     * �d�v�Ȏ��O�����̂��߁A�I�[�o�[���C�h�͐����ł��Ȃ��B<BR>
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�I�[�o�[���C�h��ŁA <BR>
     * GgafDx9GeometricActor::processPreJudgement() ���Ăяo�����A <BR>
     * �����̏������s���悤�ɂ��ׂ��ł���B <BR>
     */
    virtual void processPreJudgement() override;

    /**
     * �����蔻�胍�W�b�N .
     * �����蔻�胍�W�b�N���������Ă���B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g������ꍇ�A<BR>
     * GgafDx9Checker::isHit() �Ŕ��肷��B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g�������ꍇ�A<BR>
     * �q�b�g���Ă��Ȃ����ƂƂ���B<BR>
     * @param prm_pOtherActor ����̃A�N�^�[
     * @return true�F�q�b�g���Ă���^false�F�q�b�g���Ă��Ȃ�
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override;

    /**
     * ��ʓ��ɕ\������Ă��邩���� .
     * @return 0:Viewport�͈͓�
     *         6:Viewport������̉����ʂ�艜�Ŕ͈͊O
     *         5:Viewport������̎�O���ʂ���O�Ŕ͈͊O
     *         4:Viewport������̉E���ʂ��E�Ŕ͈͊O
     *         3:Viewport������̍����ʂ�荶�Ŕ͈͊O
     *         2:Viewport������̉����ʂ�艺�Ŕ͈͊O
     *         1:Viewport������̏㕽�ʂ���Ŕ͈͊O
     */
    virtual int isOffscreen();

    /**
     * ���݂̍��W���Q�[�������͈͓����ǂ������� .
     * ��ʓ��A��ʊO�Ƃ͖��֌W
     * @return true:�����͈͊O/false:�����͈͓�
     */
    virtual bool isOutOfGameSpace();

    /**
     * ���ϊ����[���h���W��ݒ� .
     * @param X
     * @param Y
     * @param Z
     */
    virtual void setGeometry(int X, int Y, int Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    /**
     * ���ϊ����W���R�s�[���Đݒ� .
     * @param prm_pActor �R�s�[���A�N�^�[
     */
    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    virtual void chengeGeoLocal() {
        if (_is_local) {
            return;
        } else {
            _X_final  = _X;
            _Y_final  = _Y;
            _Z_final  = _Z;
            _RX_final = _RX;
            _RY_final = _RY;
            _RZ_final = _RZ;
            _X  = _X_local;
            _Y  = _Y_local;
            _Z  = _Z_local;
            _RX = _RX_local;
            _RY = _RY_local;
            _RZ = _RZ_local;
            _is_local = true;
        }
    }
    virtual void chengeGeoFinal() {
        if (_is_local) {
            _X_local = _X;
            _Y_local = _Y;
            _Z_local = _Z;
            _RX_local = _RX;
            _RY_local = _RY;
            _RZ_local = _RZ;
            _X  = _X_final;
            _Y  = _Y_final;
            _Z  = _Z_final;
            _RX = _RX_final;
            _RY = _RY_final;
            _RZ = _RZ_final;
			_is_local = false;
        } else {
            return;

        }
    }





    /**
     * ���[���h�ϊ��s����v�Z����֐����` .
     * @param prm_pFunc �֐��ւ̃|�C���^
     */
    void defineWorldMatrix(void (*prm_pFunc)(GgafDx9GeometricActor*, D3DXMATRIX&)) {
        _pFunc_calcWorldMatrix = prm_pFunc;
    }

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDx9GeometricActor();

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
