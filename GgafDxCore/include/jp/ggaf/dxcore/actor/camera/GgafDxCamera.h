#ifndef GGAFDXCORE_GGAFDXCAMERAACTOR_H_
#define GGAFDXCORE_GGAFDXCAMERAACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * �J�����A�N�^�[.
 * GgafDxGeometricActor ���p�����A�J������\�����A�N�^�[�ł��B<BR>
 * �{�N���X�͐_(GgafDxGod)�ƘA���Ă��܂��B�����o�𑀍삷��ƁA���̒ʂ�ɃJ�����̈ʒu�ƒ����_������ł��܂��B<BR>
 * processPreDraw ���\�b�h����������Ă���A���̒��Ő_(GgafDxGod)�̃J�����ɍ��W�����㏑�����܂��B<BR>
 * <BR>
 * _x,_y,_z             �E�E�E �J�����̈ʒu <BR>
 * <BR>
 * ���g������<BR>
 * �p�����AprocessBehavior() ���� �I�[�o�[���C�h���čD���ɍ��W�𓮂������悢<BR>
 * <BR>
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class GgafDxCamera : public GgafDxGeometricActor {
    friend GgafDxGod;
    friend GgafDxUtil;
    friend GgafDxGeometricActor;
    friend GgafDxSeTransmitterForActor;

private:
    D3DVIEWPORT9 _viewport;

    // �������6�̖ʂ̒��_���W
    /** [r]������ʁA��O�̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecNear[4];
    /** [r]������ʁA���̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecFar[4];

    D3DXVECTOR3 _vecVerticalCenter[4];

    // �������6�̖�
    /** [r]������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnTop;
    /** [r]������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnBottom;
    /** [r]������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnLeft;
    /** [r]������ʁA�E(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnRight;
    /** [r]������ʁA��O(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnFront;
    /** [r]������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnBack;
    /** [r]����������E�ɕ������鐂���ʁA���E�̌��ʉ��̃p���Ɏg�p(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnVerticalCenter;

    /** [r]DirectX�ˉe�ϊ��s�� */
    D3DXMATRIX _matProj;
    /** [r]DirectX���ˉe�ϊ��s�� */
    D3DXMATRIX _vMatrixOrthoProj;

    /** [r]DirectX�J�����̈ʒu(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** [r]DirectX�J�����̒����_(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** [r]DirectX�J�����̏�x�N�g��(�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamUp;
    /** [r]DirectXVIEW�ϊ��s��(�t���[�����X�V) */
    D3DXMATRIX _matView;

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
    /** [r]�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0 */
    const dxcoord _zn;
    /** [r]�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
    const dxcoord _zf;
    const coord _x_buffer_left;
    const coord _x_buffer_right;
    const coord _y_buffer_top;
    const coord _y_buffer_bottom;




    /** [r/w]�����_�i���W�� _pVecCamLookatPoint �ƘA���j **/
    GgafDxCameraViewPoint* _pCameraViewPoint;
    GgafDxCameraUpVector* _pCameraUpVector;

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
    GgafDxCamera(const char* prm_name, double prm_rad_fovX, double prm_dep);

    virtual void initialize() override;

    /**
     * ������ʏ����X�V����B
     */
    virtual void processBehavior() override;


    virtual void processSettlementBehavior() override {
        _fX = C_DX(_x);
        _fY = C_DX(_y);
        _fZ = C_DX(_z);
    }

    /**
     * DirectX�̃J�����֔��f .
     * ���g�̍��W�� _pVecCamFromPoint �փR�s�[
     * _pCameraViewPoint �̍��W�� _pVecCamLookatPoint �փR�s�[�B
     * _pCameraUpVector �̈ʒu�x�N�g���� _pVecCamUp �w�R�s�[�B
     * _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp ��
     * D3DXMatrixLookAtLH() �����s�B
     */
    virtual void processJudgement() override;


    virtual void setDefaultPosition();

    /**
     * ���_�p�A�N�^�[���擾 .
     * �����ς݂̎��_�p�A�N�^�[���擾���܂��B
     * �A���A���߂ČĂяo�����ꍇ�AcreateCameraViewPoint() ���Ăяo����
     * �C���X�^���X���쐬����܂��B
     * @return �����ςݎ��_�p�A�N�^�[
     */
    virtual GgafDxCameraViewPoint* getCameraViewPoint();

    /**
     * ���_�p�A�N�^�[�̃C���X�^���X�𐶐� .
     * �Ǝ��̃C���X�^���X�𐶐��������ꍇ�́A�I�[�o�[���C�h���Ă��������B
     * @return �������ꂽ���_�p�A�N�^�[
     */
    virtual GgafDxCameraViewPoint* createCameraViewPoint() = 0;

    virtual GgafDxCameraUpVector* getCameraUpVector();

    virtual GgafDxCameraUpVector* createCameraUpVector() = 0;

    bool isMoving();

    inline dxcoord getZFar() const {
        return _zf;
    }

    inline dxcoord getZNear() const {
        return _zn;
    }

    inline D3DXMATRIX* getProjectionMatrix()  {
        return &_matProj;
    }

    inline D3DXMATRIX* getViewMatrix() {
        return &_matView;
    }

    inline D3DXVECTOR3* getVecCamFromPoint() const {
        return _pVecCamFromPoint;
    }

    inline D3DXVECTOR3* getVecCamLookatPoint() const {
        return _pVecCamLookatPoint;
    }

    inline dxcoord getZOrigin() const {
        return _cameraZ_org;
    }

    void setCamUpVecByFaceNo(face26 prm_face_no);


    virtual ~GgafDxCamera(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXCAMERAACTOR_H_*/
