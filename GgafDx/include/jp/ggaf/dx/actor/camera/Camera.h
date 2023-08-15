#ifndef GGAF_DX_CAMERAACTOR_H_
#define GGAF_DX_CAMERAACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �J�����A�N�^�[.
 * �J������\�����A�N�^�[�ł��B<BR>
 * �{�N���X�͊Ǘ���(Caretaker)�ƘA�����Ă��܂��B�����o�𑀍삷��ƁA���̒ʂ�ɃJ�����̈ʒu�ƒ����_������ł��܂��B<BR>
 * processPreDraw ���\�b�h����������Ă���A���̒��ŊǗ���(Caretaker)�̃J�����ɍ��W�����㏑�����܂��B<BR>
 * <BR>
 * _x,_y,_z  �E�E�E �J�����̈ʒu <BR>
 * <BR>
 * ���g������<BR>
 * �p�����AprocessBehavior() ���� �I�[�o�[���C�h���čD���ɍ��W�𓮂������悢<BR>
 * <BR>
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class Camera : public GeometricActor {
    friend Caretaker;
    friend Util;
    friend GeometricActor;
    friend SeTransmitterForActor;

public:
    /** [r]�������ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnTop;
    /** [r]�����䉺�ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnBottom;
    /** [r]�����䍶�ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnLeft;
    /** [r]������E�ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnRight;
    /** [r]�������O�ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnInfront;
    /** [r]�����䉜�ʁA�@���͎�����̓�����O�Ɍ����Ă���(���t���[���X�V) */
    D3DXPLANE _plnBack;
    /** [r]����������E�ɕ������鐂���ʁA���E�̌��ʉ��̃p���Ɏg�p(���t���[���X�V) */
    D3DXPLANE _plnVerticalCenter;

    /** [r]�J�����̃r���[�|�[�g��� */
    D3DVIEWPORT9 _viewport;
    /** [r]DirectX�r���[�|�[�g�ϊ��s�� */
    D3DXMATRIX _matViewPort;
    /** [r]DirectX�r���[�|�[�g�ϊ��t�s�� */
    D3DXMATRIX _matInvViewPort;
    /** [r]DirectX�ˉe�ϊ��s��i���݂̃J�����̎ˉe�ϊ��s��j */
    D3DXMATRIX _matProj;
    /** [r]DirectX�ˉe�ϊ��t�s�� */
    D3DXMATRIX _matInvProj;
    /** [r]DirectX���ˉe�ϊ��s�� */
    D3DXMATRIX _matProjOrtho;

    /** [r]DirectX�J�����̈ʒu(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** [r]DirectX�J�����̒����_(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** [r]DirectX�J�����̏�x�N�g��(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamUp;
    /** [r]DirectX�r���[�ϊ��s��(�t���[�����X�V) */
    D3DXMATRIX _matView;
    /** [r]DirectX�r���[�ϊ��t�s��(�t���[�����X�V) */
    D3DXMATRIX _matInvView;
    /** [r]������v�Z�p(�t���[�����X�V) */
    D3DXMATRIX _matInvViewPort_Proj_View;
    /** [r]����pX���W�A�� */
    const double _rad_fovX;
    /** [r]�[���i_cameraZ_org�̉��{��)  */
    const double _dep;
    /** [r]����pX���W�A���̔��� */
    const double _rad_half_fovX;
    /** [r]�A�X�y�N�g�� */
    const double _screen_aspect;
    /** [r]����pY���W�A�� */
    const double _rad_fovY;
    /** [r]����pY���W�A���̔��� */
    const double _rad_half_fovY;
    /** [r]����pX�^���W�F���g�̔��� */
    const double _tan_half_fovX;
    /** [r]����pY�^���W�F���g�̔��� */
    const double _tan_half_fovY;
    /** [r]�J������Z���W�����ʒu */
    const dxcoord _cameraZ_org;
    /** [r]�\���ΏۊJ�n�́A�J��������ŋߖT�N���b�v�ʂ܂ŋ���(�ǂ�����̋������\���Ώۂ��j��0 */
    const dxcoord _zn;
    /** [r]�\���ΏۏI���́A�J��������ŉ��N���b�v�ʂ܂ŋ���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
    const dxcoord _zf;

    /** [r/w]�J�����̒����_�i���g����̕����� _pVecCamLookatPoint �ƘA���j */
    CameraViewPoint* _pCameraViewPoint;
    /** [r/w]�J�����̏�����i���g����̕����� _pVecCamUp �ƘA���j */
    CameraUpVector* _pCameraUpVector;

    /** [r]��O�̍��W */
    coord _x_prev, _y_prev, _z_prev;

public:
    /**
     * �R���X�g���N�^ .
     * ����p�ƕ\���[����ݒ肷��B
     * ����p�ɂ���āA�J�����̏���Z�ʒu�����肷��B
     * ���̃J�����̏���Z�ʒu�́A���_�t�߂�DirectX�̒���1�i�̃I�u�W�F�N�g�j��
     * ��ʏ�10�s�N�Z�������ŕ\������ʒu�փJ�����������悤�Ɏ����v�Z�����B�i_cameraZ_org�ɕێ�)
     * ���̌��_����A�����̃J����Z�ʒu�܂ł�1.0�Ƃ��āA�\���͈͂̐[���̔{�������� prm_dep �Őݒ肷��B
     * prm_dep=1.0�Ƃ����ꍇ�B�\���͈͂� ���_�𒆐S�Ƃ��A���a�������J����Z�ʒu�̋����̋��ƂȂ�B
     * �܂��A�\���͈́{�����A�A�N�^�[�B�̃Q�[�����ł̉��͈͂ƂȂ�悤�ɐ݌v���Ă��邽�߁A�J�����̏����ݒ�l��
     * ���ɏd�v�ł���B
     * �ʏ펋��p�����߂�΃Y�[���A�b�v�̌��ʂ������邪�A�{���C�u�����ł́A
     * ��L�̏���Z�ʒu�܂ŃJ�����������ň������߁A����p��ύX���Ă��A�N�^�[�̕\���̑傫���͉�ʏ�ς��Ȃ��B
     * ����������p����������΁A�����̃J�����������������L�т邱�ƂɂȂ�A���ʂƂ���
     * ���E�̕\���͈͂��g�傷����ʂ����邱�Ƃ��ł���B
     * �t�Ɏ���p���L����΁A�J�����̏���Z�ʒu�͌��_�ɋ߂��Ȃ�A���͐��E�̕\���͈͂͋����Ȃ�B
     *
     * @param prm_name ���O(�f�o�b�N�ŕ\���B���ł��悢)
     * @param prm_rad_fovX ���E�̎���p�i���W�A���j
     * @param prm_dep �[���i_cameraZ_org�̉��{��)
     * @return
     */
    Camera(const char* prm_name, double prm_rad_fovX, double prm_dep);

    /**
     * �����F�J�����̒����_�A�J�����̏�����A�N�^�[�̐��� .
     */
    virtual void initialize() override;

    /**
     * ������ʂ̍��W�����X�V����B
     */
    virtual void processBehavior() override;

    /**
     * DirectX�̃J�����֔��f .
     * ���g�̍��W�� _pVecCamFromPoint �փR�s�[
     * _pCameraViewPoint �̍��W�� _pVecCamLookatPoint �փR�s�[�B
     * _pCameraUpVector �̈ʒu�x�N�g���� _pVecCamUp �w�R�s�[�B
     * _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp ��
     * D3DXMatrixLookAtLH() �����s�B
     */
    virtual void processSettlementBehavior() override;

    /**
     * �J�����������ݒ�ɖ߂� .
     * �J�����������ʒu�ݒ肵�A���_�͌��_�𒍎����A��������J������Y���^������x�N�g���Ƃ��܂��B
     */
    virtual void setDefaultPosition();

    /**
     * �J��������̎��_�|�C���g�Ɉʒu����A�N�^�[���擾 .
     * �����ς݂̎��_�p�A�N�^�[���擾���܂��B
     * �A���A���߂ČĂяo�����ꍇ�AcreateCameraViewPoint() ���Ăяo����
     * �C���X�^���X���쐬����܂��B
     * @return ���_�|�C���g�A�N�^�[
     */
    virtual CameraViewPoint* getCameraViewPoint();

    /**
     * �J��������̎��_�|�C���g�̃A�N�^�[�C���X�^���X�𐶐� .
     * �I�[�o�[���C�h���Ă��������B
     * @return ���_�|�C���g�A�N�^�[
     */
    virtual CameraViewPoint* createCameraViewPoint() = 0;

    /**
     * �J�����̏�����x�N�g���̃|�C���g��\���A�N�^�[���擾 .
     * �����ς݂̃A�N�^�[���擾���܂��B
     * �A���A���߂ČĂяo�����ꍇ�AcreateCameraUpVector() ���Ăяo����
     * �C���X�^���X���쐬����܂��B
     * @return �J�����̏�����x�N�g���̃|�C���g�A�N�^�[
     */
    virtual CameraUpVector* getCameraUpVector();

    /**
     * �J�����̏�����x�N�g���̃|�C���g�̃A�N�^�[�C���X�^���X�𐶐� .
     * �I�[�o�[���C�h���Ă��������B
     * @return ������|�C���g�A�N�^�[
     */
    virtual CameraUpVector* createCameraUpVector() = 0;

    /**
     * �J�������ړ��������肵�܂��B
     * ���ӁF�����_�A������̈ړ����͔���Ɋ܂܂�܂���B
     * @return true:�ړ����i��O�̃t���[���ƍ��W���Ⴄ�j�^false:��~���i��O�̃t���[���ƍ��W�������j
     */
    bool isMoving();

    /**
     * �\���ΏۏI���́A�J��������ŉ��N���b�v�ʂ܂ŋ������擾 .
     * @return  �\���ΏۏI���́A�J��������ŉ��N���b�v�ʂ܂ŋ���
     */
    inline dxcoord getZFar() const {
        return _zf;
    }

    /**
     * �\���ΏۊJ�n�́A�J��������ŋߖT�N���b�v�ʂ܂ŋ������擾 .
     * @return �\���ΏۊJ�n�́A�J��������ŋߖT�N���b�v�ʂ܂ŋ���
     */
    inline dxcoord getZNear() const {
        return _zn;
    }

    /**
     * �J�����̉e�ϊ��s����擾 .
     * @return �J�����̉e�ϊ��s��
     */
    inline D3DXMATRIX* getProjectionMatrix()  {
        return &_matProj;
    }

    /**
     * �J�����̉e�ϊ��̋t�s����擾 .
     * @return �J�����̉e�ϊ��̋t�s��
     */
    inline D3DXMATRIX* getInvProjectionMatrix()  {
        return &_matInvProj;
    }

    /**
     * ���݂̃J�����̃r���[�ϊ��s��(���t���[���X�V)���擾 .
     * @return �J�����̃r���[�ϊ��s��
     */
    inline D3DXMATRIX* getViewMatrix() {
        return &_matView;
    }

    /**
     * �J�����̈ʒu�x�N�g�����擾 .
     * @return �J�����̈ʒu�x�N�g��
     */
    inline D3DXVECTOR3* getVecCamFromPoint() const {
        return _pVecCamFromPoint;
    }

    /**
     * �J�����̒����_�ʒu�x�N�g�����擾 .
     * @return �J�����̒����_�ʒu�x�N�g��
     */
    inline D3DXVECTOR3* getVecCamLookatPoint() const {
        return _pVecCamLookatPoint;
    }

    /**
     * �J�����̏��\���n�_�̈ʒu�x�N�g�����擾 .
     * @return �J�����̏��\���n�_�̈ʒu�x�N�g��
     */
    inline D3DXVECTOR3* getVecCamUp() const {
        return _pVecCamUp;
    }

    /**
     * �J�����̏����ʒu��Z���W���擾 .
     * @return �J�����̏����ʒu��Z���W���擾
     */
    inline dxcoord getZOrigin() const {
        return _cameraZ_org;
    }

    /**
     * �J�����̕\���̐[���i_cameraZ_org�̉��{��) ���擾 .
     * @return �J�����̕\���̐[��
     */
    inline double getDep() {
        return _dep;
    }

    virtual ~Camera();
};

}
#endif /*GGAF_DX_CAMERAACTOR_H_*/
