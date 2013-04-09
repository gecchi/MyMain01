#ifndef GGAFDXGEOMETRICACTOR_H_
#define GGAFDXGEOMETRICACTOR_H_

namespace GgafDxCore {

/**
 * ���W�A��]�A�X�P�[�������������A�N�^�[.
 * ���[���h���W�A�����͕ϊ��ςݍ��W�̉��ꂩ�������A<BR>
 * ���W�֘A���\�b�h��������A�N�^�[�ł��B<BR>
 * (��GgafDxUntranceformedActor ��GgafDxTranceformedActor �𓝍�)
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxGeometricActor : public GgafDxBaseActor {

private:
    /**
     * ���ʂŎg�p�֎~ .
     */
    void processFinal() override {
    }

public:
    /** [r] �ϊ��ςݍ��W�ł��邩(true:�{�A�N�^�[�͕ϊ��ςݍ��W/false:�{�A�N�^�[�̓��[���h���W) */
    bool _is_2D;
    /** [r] ��ʊO��ʁBisOutOfView()�������Ŏg�p�B���v�Z���� -1 */
    int _offscreen_kind;

    /** [r/w]���[���hX���W( _X : DirectX��X���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _X;
    /** [r/w]���[���hY���W( _Y : DirectX��Y���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _Y;
    /** [r/w]���[���hZ���W( _Z : DirectX��Z���W : �����J�����ʒu�ł̉�ʏ�s�N�Z�� = 1000 : 0.1 : �� 1px  ) */
    coord _Z;
    /** [r/w]���[���hX����]�p(_RX : Degree = 1000 : 1�x) */
    angle _RX;
    /** [r/w]���[���hY����]�p(_RY : Degree = 1000 : 1�x) */
    angle _RY;
    /** [r/w]���[���hZ����]�p(_RZ : Degree = 1000 : 1�x) */
    angle _RZ;
    /** [r/w]���[���hX�������X�P�[��(_SX : �{�� = 1000 : 1.0�{) */
    scale _SX;
    /** [r/w]���[���hY�������X�P�[��(_SY : �{�� = 1000 : 1.0�{) */
    scale _SY;
    /** [r/w]���[���hZ�������X�P�[��(_SZ : �{�� = 1000 : 1.0�{) */
    scale _SZ;
    /** [r]����A */
    GgafDxKurokoA* _pKurokoA;
    /** [r]����B */
    GgafDxKurokoB* _pKurokoB;
    /** [r]�`�F�b�J�[ */
    GgafDxChecker* _pChecker;
    /** [r]���ʉ������Ǘ��I�u�W�F�N�g */
    GgafDxSeTransmitterForActor* _pSeTx;

    /** [r]���E���̔��a(DirectX�̒P��)�B��ʊO����Ɏg�p����� */
    dxcoord _bounding_sphere_radius;
    /** [r]���f���̋��E�����a�{�� */
    dxcoord _rate_of_bounding_sphere_radius;
    /** [r]������ _X ����v�Z�����DirectX�̃��[���hX���W(_X : _fX = 1000 : 0.1) */
    dxcoord _fX;
    /** [r]������ _Y ����v�Z�����DirectY�̃��[���hY���W(_Y : _fY = 1000 : 0.1) */
    dxcoord _fY;
    /** [r]������ _Z ����v�Z�����DirectZ�̃��[���hZ���W(_Z : _fZ = 1000 : 0.1) */
    dxcoord _fZ;
    /** [r]�������ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_top;
    /** [r]�����䉺�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_bottom;
    /** [r]�����䍶�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_left;
    /** [r]������E�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_right;
    /** [r]�������O�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_front;
    /** [r]�����䉜�ʂ��王��O�Ɍ������Ă̎��g�̍��W�܂ł�DirectX�̋����A������̋����͕��̒l�ɂȂ� */
    dxcoord _dest_from_vppln_back;
    /** [r/w]WORLD�ϊ�(��]�~�ړ�)�s��v�Z�֐� */
    void (*_pFunc_calcRotMvWorldMatrix)(GgafDxGeometricActor*, D3DXMATRIX&);
    /** [r]���g�̌��݂�World�ϊ��s��(�ʏ�́u�g��k���~��]�~�ړ��v)�B�y�䂪����ꍇ�́A���̓y��ƍs��̐ςɂȂ��Ă���B */
    D3DXMATRIX _matWorld;
    /** [r]���g�̌��݂�World�ϊ��s��́u��]�~�ړ��v�̂݁B�y�䂪����ꍇ�́A���̓y��ƍs��̐ςɂȂ��Ă���B */
    D3DXMATRIX _matWorldRotMv;
    /** [r]���g�̌��݂�World�ϊ��s��́u��]�~�ړ��v�̋t�s��(��]�~�ړ��̃C���o�[�X) */
    D3DXMATRIX _matInvWorldRotMv;
    /** [r]�J�����g�t���[���Ŏ��g�̌��݂�World�ϊ��s��̋t�s��(_matInvWorldRotMv)���v�Z���ċ��߂����ǂ����̃t���O�B */
    bool _was_calculated_matInvWorldRotMv;

    /** [r]�y��ƂȂ�A�N�^�[�A�y�䂪�����ꍇ��nullptr�iIK�p�j */
    GgafDxCore::GgafDxGeometricActor* _pActor_Base;
    /** [r]�y��A�N�^�[��ł̃��[���hX���W */
    coord _X_local;
    /** [r]�y��A�N�^�[��ł̃��[���hY���W */
    coord _Y_local;
    /** [r]�y��A�N�^�[��ł̃��[���hZ���W */
    coord _Z_local;
    /** [r]�y��A�N�^�[��ł̃��[���hX����]�p */
    angle _RX_local;
    /** [r]�y��A�N�^�[��ł̃��[���hY����]�p */
    angle _RY_local;
    /** [r]�y��A�N�^�[��ł̃��[���hZ����]�p */
    angle _RZ_local;

    coord _X_final;
    coord _Y_final;
    coord _Z_final;
    angle _RX_final;
    angle _RY_final;
    angle _RZ_final;

    bool _is_local;

    //�⑫����
    //�y_X, _Y, _Z �̒P�ʂɂ��āz
    //�@���W�l _X, _Y, _Z �͓Ǝ��̒P�ʂł���B
    //�@DirectX���W(float)�n�̒l�̂P.0�ɑ������� X, _Y, _Z���W�l�́ALEN_UNIT(=1000)�{��PX_UNIT(=10)�{�̐����l�ł���B
    //�@�܂�10000�{�BDirectX���W�P�ʂ̂P.0�́A�Q�[����ʏ��10px�����̑傫���ɂȂ�i�悤�ɃJ�����������Ă���j�B
    //�@�Ⴆ�΁A_X = 5000 �́A��ʂŏ����J�����ʒu�� 5px �̕��Ɍ����ADirectX���W�ł�0.5�ɂȂ�i�悤�ɐ݌v���Ă���j�B
    //�@_X,_Y,_Z     �� �s�N�Z�� �̕ϊ��B    �E�E�E _X,_Y,_Z �� LEN_UNIT(=1000)�Ŋ���B
    //�@DirectX���W  �� �s�N�Z�� �̕ϊ��B    �E�E�E DirectX���W���APX_UNIT(=10)���|���Z����B
    //�@_X,_Y,_Z     �� DirectX���W �̕ϊ��B �E�E�E _X,_Y,_Z �� LEN_UNIT*PX_UNIT(=10000)�Ŋ���B
    //�@���́A�`��̒��O��_X,_Y,_Z ����͂Ƃ��āA LEN_UNIT*PX_UNIT ���Z���A���[���h�ϊ��s��̒l�Ɏg�p����Ă���B
    //�@�킴�킴����Ȃ��Ƃ����Ă���̂́A�Q�[�����̍��W�v�Z�͑S�Đ����ōs���A�����ł����x���グ�����������߁B
    //�@��(�����;)�͂悭�g���Ă�����@�Ǝv���̂����A���݂ł� �œK������Ă��� float �� double �ł����Ȃ葬���̂ŁA
    //�@�{���ɂ��̐݌v�ł悩�����̂��낤���c�A����A�����Ȃ��Ă�ƐM����B
    //
    //�y_RX, _RY, _RZ �̒P�ʂɂ��āz
    //�@�Ǝ��P�ʂ́u�A���O���l�v���̂�B
    //�@�u�A���O���l�v�Ƃ� 0~3600000 �̒l�ŁA�����ڂł� �p�x�l(Degree)�� 1000�{�̐��x�̒l�ł���B
    //�@(�A���A���ۂ͓����ł� Degree �� 10�{�̐��x�ł���B3600�����̒P�ʕ����x�N�g���e�[�u���ƑΉ�������݌v)
    //�@1�x��1000�A0.5�x��500�B���p�̒l��90000�A������180000�ł���B
    //�@���S�p�Ɠ�����3���̕�����0�Ƃ��A���̐������������Ĕ����v���ɃA���O���l�͑�������̂Ƃ���B
    //
    //�y_SX, _SY, _SZ �̒P�ʂɂ��āz
    //�@1000���P�{�̃X�P�[���Ӗ�����B���������ăf�t�H���g��1000�ɂȂ��Ă���B
    //�@�`��̒��O�� 1000 �ŏ��Z����A�g��k�����ɕϊ����g�p����B


public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �A�N�^�[��
     * @param prm_pStat �X�e�[�^�X(�g�p���Ȃ��� nullptr)
     * @param prm_pChecker �`�F�b�J�[(�g�p���Ȃ��� nullptr)
     * @return
     */
    GgafDxGeometricActor(const char* prm_name,
                          GgafCore::GgafStatus* prm_pStat,
                          GgafDxChecker* prm_pChecker);

    /**
     * ���̃A�N�^�[���擾
     * @return ���̃A�N�^�[
     */
    virtual GgafDxGeometricActor* getPrev() override {
        return (GgafDxGeometricActor*)GgafActor::getPrev();
    }

    /**
     * �O�̃A�N�^�[���擾
     * @return �O�̃A�N�^�[
     */
    virtual GgafDxGeometricActor* getNext() override {
        return (GgafDxGeometricActor*)GgafActor::getNext();
    }

    /**
     * ���菈�����O���� .
     * processBehavior() ��A���W�v�Z���㏈���Ƃ��Ď��̏������s�� <BR>
     * �@���g�̍��W���(_X,_Y,_Z)����ȉ��̃����o�̍X�V���s���B <BR>
     *     _fX <BR>
     *     _fY <BR>
     *     _fZ <BR>
     *     _dest_from_vppln_top <BR>
     *     _dest_from_vppln_bottom <BR>
     *     _dest_from_vppln_left <BR>
     *     _dest_from_vppln_right <BR>
     *     _dest_from_vppln_front <BR>
     *     _dest_from_vppln_back <BR>
     * �A ���g�̍��W��񂩂烏�[���h�ϊ��s����쐬��_matWorld�ɕێ�
     * �B processJudgement() ���Ăяo���̂��ߏ��������Ƃ��āA <BR>
     *    ���g�̍��W��񂩂���`�W���ؔz��ւ̓o�^���s���B <BR>
     * �C ���g���t�H�[���[�V���������̏ꍇ�A
     *    ���g���S�~���֑�����ۂɁA�t�H�[���[�V���������ێ����鎩�g�ւ̃|�C���^���N���A
     * �{���\�b�h�̓I�[�o�[���C�h�\�Ƃ��邪�A�t���[�����[�N�̕`��┻��Ɋւ��
     * �d�v�Ȏ��O�����̂��߁A�I�[�o�[���C�h�͐����ł��Ȃ��B<BR>
     * �ǂ����Ă��I�[�o�[���C�h���K�v�ȏꍇ�́A�I�[�o�[���C�h��ŁA <BR>
     * GgafDxGeometricActor::processSettlementBehavior() ���Ăяo�����A <BR>
     * ��L�@�A�B�Ɠ����̏������s���悤�ɂ��ׂ��ł���B
     * �t�Ɍ��ʃG�t�F�N�g�ȂǁA��L�̍l�����s�v�ȃA�N�^�[�̏ꍇ�́A�{���\�b�h���I�[�o�[���C�h���A
     * _fX,_fY,_fZ�̂ݍX�V�����������邱�Ƃɂ��A�p�t�H�[�}���X�����コ���邱�Ƃ��ł���B <BR>
     */
    virtual void processSettlementBehavior() override;

    /**
     * �����蔻�胍�W�b�N .
     * �����蔻�胍�W�b�N���������Ă���B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g������ꍇ�A<BR>
     * GgafDxChecker::isHit() �Ŕ��肷��B<BR>
     * �`�F�b�J�[�I�u�W�F�N�g�������ꍇ�A<BR>
     * �q�b�g���Ă��Ȃ����ƂƂ���B<BR>
     * @param prm_pOtherActor ����̃A�N�^�[
     * @return true�F�q�b�g���Ă���^false�F�q�b�g���Ă��Ȃ�
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override;

    /**
     * ��ʓ��ɕ\������Ă��邩���� .
     * @return 0(false):Viewport�͈͓�
     *         1       :Viewport������̏㕽�ʂ���Ŕ͈͊O
     *         2       :Viewport������̉����ʂ�艺�Ŕ͈͊O
     *         3       :Viewport������̍����ʂ�荶�Ŕ͈͊O
     *         4       :Viewport������̉E���ʂ��E�Ŕ͈͊O
     *         5       :Viewport������̎�O���ʂ���O�Ŕ͈͊O
     *         6       :Viewport������̉����ʂ�艜�Ŕ͈͊O
     *         ������D�揇�ʏ��ɕ���ł��܂��B�i��F1 ���� 4 �� 1 ���Ԃ�܂��j
     */
    virtual int isOutOfView();

    /**
     * ���݂̍��W���Q�[�������͈͓����ǂ������� .
     * ��ʓ��A��ʊO�Ƃ͖��֌W
     * @return true:�����͈͊O/false:�����͈͓�
     */
    virtual bool isOutOfUniverse();

    /**
     * ���[���h���W��ݒ� .
     * @param X
     * @param Y
     * @param Z
     */
    virtual void locate(coord X, coord Y, coord Z) {
        _X = X;
        _Y = Y;
        _Z = Z;
    }

    /**
     * ���[���h���W��ݒ� .
     * @param X
     * @param Y
     */
    virtual void locate(coord X, coord Y) {
        _X = X;
        _Y = Y;
    }

    /**
     * X��Y��Z���e���X�P�[��(_SX, _SY, _SZ)�𓯂��l�Őݒ�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���B
     * @param S �X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale S) {
        _SX = S;
        _SY = S;
        _SZ = S;
        setBoundingSphereRadiusRate(SC_R(S));
    }

    /**
     * X��Y��Z���X�P�[��(_SX, _SY, _SZ)�����ꂼ��l�Őݒ�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param SX X���X�P�[���l(1000 �� 1.0�{)
     * @param SY Y���X�P�[���l(1000 �� 1.0�{)
     * @param SZ Z���X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale SX, scale SY, scale SZ) {
        _SX = SX;
        _SY = SY;
        _SZ = SZ;
        setBoundingSphereRadiusRate(SC_R(MAX3(_SX,_SY,_SZ)));
    }

    /**
     * X��Y���X�P�[��(_SX, _SY)�݂̂�l�Őݒ�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param SX X���X�P�[���l(1000 �� 1.0�{)
     * @param SY Y���X�P�[���l(1000 �� 1.0�{)
     */
    virtual void setScale(scale SX, scale SY) {
        _SX = SX;
        _SY = SY;
        setBoundingSphereRadiusRate(SC_R(MAX3(_SX,_SY,_SZ)));
    }

    /**
     * X��Y��Z���S�Ă̎��X�P�[���������Őݒ�B
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_rate �{��
     */
    virtual void setScaleR(float prm_rate) {
        _SX = R_SC(prm_rate);
        _SY = R_SC(prm_rate);
        _SZ = R_SC(prm_rate);
        setBoundingSphereRadiusRate(prm_rate);
    }

    /**
     * X��Y��Z���e���X�P�[���������Őݒ�B
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_x_rate X���{��
     * @param prm_y_rate Y���{��
     * @param prm_z_rate Z���{��
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) {
        _SX = R_SC(prm_x_rate);
        _SY = R_SC(prm_y_rate);
        _SZ = R_SC(prm_z_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, prm_z_rate));
    }

    /**
     * X��Y���̂݃X�P�[���������Őݒ�B
     * 1.0 �� ���̃��f���̑傫������1.0�{�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param prm_x_rate X���{��
     * @param prm_y_rate Y���{��
     */
    virtual void setScaleR(float prm_x_rate, float prm_y_rate) {
        _SX = R_SC(prm_x_rate);
        _SY = R_SC(prm_y_rate);
        setBoundingSphereRadiusRate(MAX3(prm_x_rate, prm_y_rate, SC_R(_SZ)));
    }

    /**
     * X��Y��Z���e���X�P�[��(_SX, _SY, _SZ)�𓯂��l�ŉ��Z�B
     * �y���Ӂz
     * _pScaler->behave(); �����݂���Ə㏑������܂���I�B
     * @param dS ���Z����X�P�[���l
     */
    virtual void addScale(scale dS) {
        _SX += dS;
        _SY += dS;
        _SZ += dS;
        setBoundingSphereRadiusRate(SC_R(MAX3(_SX,_SY,_SZ)));
    }

    /**
     * ���W(_X, _Y, _Z)���R�s�[���Đݒ� .
     * @param prm_pActor �R�s�[���A�N�^�[
     */
    virtual void locateAs(GgafDxGeometricActor* prm_pActor) {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
        _Z = prm_pActor->_Z;
    }

    /**
     * ���W(_X, _Y, _Z)���R�s�[���Đݒ� .
     * @param prm_pGeoElem ���W�I�u�W�F�N�g
     */
    virtual void locateAs(GgafDxGeoElem* prm_pGeoElem);

    /**
     * ��]�p�x(_RX, _RY, _RZ)���R�s�[���Đݒ� .
     * @param prm_pActor �R�s�[���A�N�^�[
     */
    virtual void rotateAs(GgafDxGeometricActor* prm_pActor);

    /**
     * ��]�p�x(_RX, _RY, _RZ)���R�s�[���Đݒ� .
     * @param prm_pGeoElem ���W�I�u�W�F�N�g
     */
    virtual void rotateAs(GgafDxGeoElem* prm_pGeoElem);

    /**
     * X��Y��Z���X�P�[��(_SX, _SY, _SZ)���R�s�[���Đݒ� .
     * @param prm_pActor �R�s�[���A�N�^�[
     */
    virtual void scaleAs(GgafDxGeometricActor* prm_pActor);

    /**
     * ���g�̓������[���h�ϊ�(_matWorldRotMv) �̋t�s��𖢌v�Z�Ȃ�v�Z���A�v�Z�ς݂Ȃ炻�̂܂ܕԂ� .
     * @return _matInvWorldRotMv
     */
    D3DXMATRIX* getInvMatWorldRotMv() {
        if (_was_calculated_matInvWorldRotMv) {
            return &_matInvWorldRotMv;
        } else {
            D3DXMatrixInverse(&_matInvWorldRotMv, nullptr, &_matWorldRotMv);
            _was_calculated_matInvWorldRotMv = true;
            return &_matInvWorldRotMv;
        }
    }

    /**
     * �����̃A�N�^�[���A���g�̃T�u�A�N�^�[�Ƃ��Ēǉ����A�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷��B
     * �����̏]���A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _X,_Y,_Z,_RX,_RY,_RZ �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _X,_Y,_Z,_RX,_RY,_RZ ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * ����A(_pKurokoA) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_kind     ���
     * @param prm_pGeoActor �]��������A�N�^�[
     * @param prm_X_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_Y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_Z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_RX_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_RY_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_RZ_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     * @return ��ʃg�b�v�̒c��
     */
    virtual GgafCore::GgafGroupHead* addSubGroupAsFk(actorkind prm_kind,
                                                     GgafDxGeometricActor* prm_pGeoActor,
                                                     int prm_X_init_local,
                                                     int prm_Y_init_local,
                                                     int prm_Z_init_local,
                                                     int prm_RX_init_local,
                                                     int prm_RY_init_local,
                                                     int prm_RZ_init_local);

    /**
     * �����̃A�N�^�[���A���g�̃T�u�A�N�^�[�Ƃ��Ēǉ����A�p�����t�H���[�h�L�l�}�e�B�N�X�Őݒ肷��B
     * �����̏]���A�N�^�[�́A���̂Q�̃��\�b�h�̎g�p���\�ƂȂ�܂��B <BR>
     * _X,_Y,_Z,_RX,_RY,_RZ �����[�J���ithis����̑��΁j�ɐ؂�ւ���E�E�EchangeGeoLocal()<BR>
     * _X,_Y,_Z,_RX,_RY,_RZ ��΍��W�ɐ؂�ւ���                    �E�E�EchangeGeoFinal()<BR>
     * �y���Ӂz<BR>
     * ����A(_pKurokoA) �́A���[�J�����W�n�ł̂ݎg�p�\�ƂȂ�܂��B<BR>
     * �]���A�N�^�[processBehavior() �̏����𔲂���O�ɂ́AchangeGeoFinal() �Ő�΍��W�ɖ߂��Ă����K�v������܂��B<BR>
     * @param prm_pGeoActor �]��������A�N�^�[
     * @param prm_X_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����X���W�ʒu
     * @param prm_Y_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Y���W�ʒu
     * @param prm_Z_init_local  �]���A�N�^�[�̃��[�J��(this)�ʒu�����Z���W�ʒu
     * @param prm_RX_init_local �]���A�N�^�[�̃��[�J��(this)��]�����X����]�l
     * @param prm_RY_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Y����]�l
     * @param prm_RZ_init_local �]���A�N�^�[�̃��[�J��(this)��]�����Z����]�l
     * @return ��ʃg�b�v�̒c��
     */
    virtual GgafCore::GgafGroupHead* addSubGroupAsFk(GgafDxGeometricActor* prm_pGeoActor,
                                                     int prm_X_init_local,
                                                     int prm_Y_init_local,
                                                     int prm_Z_init_local,
                                                     int prm_RX_init_local,
                                                     int prm_RY_init_local,
                                                     int prm_RZ_init_local);

    /**
     * ���W�n(_X,_Y,_Z,_RX,_RY,_RZ )�����[�J�����W(�y�䂩��̑��΍��W)�ɕϊ� .
     */
    virtual void changeGeoLocal() {
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

    /**
     * ���W�n(_X,_Y,_Z,_RX,_RY,_RZ)��ޔ����Ă�����΍��W�ɖ߂� .
     * ���[�J�����W�̕ύX�ɔ�����΍��W�̍X�V�́A������<BR>
     * processSettlementBehavior()<BR>
     * �ōs������ɂȂ��Ă���B<BR>
     * ���������āAchangeGeoFinal() �ō��W�X�V�����킯�ł͂Ȃ��̂Œ��ӁB<BR>
     */
    virtual void changeGeoFinal() {
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
    void defineRotMvWorldMatrix(void (*prm_pFunc)(GgafDxGeometricActor*, D3DXMATRIX&)) {
        _pFunc_calcRotMvWorldMatrix = prm_pFunc;
    }

    /**
     * ���f���̋��E�����a�̔{���ݒ�B
     * ���E�����a�Ƃ́A���[�J�����W�̌��_����S���_�̋����ōő�̒����ŁA
     * ���̒l�́A��ʊO����ɗ��p����Ă邽�߁A���f���\�����ɓƎ��Ɋg����s�����ꍇ�B
     * ���̒l���X�V���Ȃ��Ɖ�ʊO���肪�������s���Ȃ��B<BR>
     * �Ⴆ�΁A�\�����ɂT�{�̊g��ŕ\�������ꍇ�A�{���\�b�h��<BR>
     * <BR>
     * setBoundingSphereRadiusRate(5.0)<BR>
     * <BR>
     * �Ƃ���ƁA��ʊO���肪�������Ȃ�B<BR>
     * ��ʊO���肪�������Ȃ�Ƃ́A��̓I�ɂ́AisOutOfView() �̔���v�Z���ɉe����^����
     * �Ƃ����Ӗ��ł���B<BR>
     * @param prm_rate �g�嗦
     */
    virtual void setBoundingSphereRadiusRate(FLOAT prm_rate) {
        _rate_of_bounding_sphere_radius = prm_rate;
    }

    virtual void onEnd() override;

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDxGeometricActor();

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
#endif /*GGAFDXGEOMETRICACTOR_H_*/
