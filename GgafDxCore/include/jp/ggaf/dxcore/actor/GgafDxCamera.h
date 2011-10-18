#ifndef GGAFDXCAMERAACTOR_H_
#define GGAFDXCAMERAACTOR_H_


namespace GgafDxCore {

// (2009/2/12 �̔]�݂�)
// �Q�`�R�� new ���āA�P�J���A�Q�J���݂����Ȑ؂�ւ����삪�ł�����ǂ�������


/**
 * �J�����A�N�^�[.
 * GgafDxGeometricActor ���p�����A�J������\�����A�N�^�[�ł��B<BR>
 * �{�N���X�͐_(GgafDxGod)�ƘA���Ă��܂��B�����o�𑀍삷��ƁA���̒ʂ�ɃJ�����̈ʒu�ƒ����_������ł��܂��B<BR>
 * processPreDraw ���\�b�h����������Ă���A���̒��Ő_(GgafDxGod)�̃J�����ɍ��W�����㏑�����܂��B<BR>
 * <BR>
 * _X,_Y,_Z             �E�E�E �J�����̈ʒu <BR>
 * <BR>
 * ���g������<BR>
 * �p�����AprocessBehavior() ���� �I�[�o�[���C�h���čD���ɍ��W�𓮂������悢<BR>
 * <BR>
 * @version 1.00
 * @since 2009/02/12
 * @author Masatoshi Tsuge
 */
class GgafDxCamera : public GgafDxGeometricActor {
private:

public:
    D3DVIEWPORT9 _viewport;

    // �������6�̖ʂ̒��_���W
    /** ������ʁA��O�̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecNear[4];
    /** ������ʁA���̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecFar[4];

    D3DXVECTOR3 _vecVerticalCenter[4];

    // �������6�̖�
    /** ������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnTop;
    /** ������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnBottom;
    /** ������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnLeft;
    /** ������ʁA�E(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnRight;
    /** ������ʁA��O(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnFront;
    /** ������ʁA��(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXPLANE _plnBack;

    D3DXPLANE _plnVerticalCenter;

    /** �ˉe�ϊ�������� */
    D3DXMATRIX _matProj;
    /** ���ˉe�ϊ�������� */
    D3DXMATRIX _vMatrixOrthoProj;

    /** �J�����̈ʒu(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** �J�����̒����_(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** �J�����̏�x�N�g��(�ǂݍ��ݐ�p�A������s��) */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW�ϊ��s��(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXMATRIX _matView;
    /** ����pX(�ǂݍ��ݐ�p�A������s��) */
    float _rad_fovX;
    /** ����pX�̔���(�ǂݍ��ݐ�p�A������s��) */
    float _rad_half_fovX;
    /** ����pY(�ǂݍ��ݐ�p�A������s��) */
    float _rad_fovY;
    /** ����pY�̔���(�ǂݍ��ݐ�p�A������s��) */
    float _rad_half_fovY;
    /** �J������Z���W(�ǂݍ��ݐ�p) */
    dxcoord _cameraZ;
    /** �J������Z���W�����ʒu(�ǂݍ��ݐ�p�A������s��) */
    dxcoord _cameraZ_org;
    /** �A�X�y�N�g��(�ǂݍ��ݐ�p�A������s��) */
    float _screen_aspect;

    float _tan_half_fovY;
    float _tan_half_fovX;
    float _dCamHarfXfovTan;

    /** �J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0 */
    dxcoord _zn;
    /** �J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn  */
    dxcoord _zf;

    float _dep;
    /** �����_ **/
    GgafDxCameraViewPoint* _pViewPoint;


    static coord _X_ScreenLeft;
    static coord _X_ScreenRight;
    static coord _Y_ScreenTop;
    static coord _Y_ScreenBottom;


    /**
     * �R���X�g���N�^ .
     * ����p�ƕ\���[����ݒ肷��B
     * ����p�ɂ���āA�J�����̏���Z�ʒu�����肷��B
     * ���̃J�����̏���Z�ʒu�́A���_�t�߂�DirctX�̒���1�i�̃I�u�W�F�N�g�j��
     * ��ʏ�10�s�N�Z���ŕ\������ʒu�փJ�����������悤�Ɏ����v�Z�����B�i_cameraZ_org�ɕێ�)
     * ���̌��_����A�����̃J����Z�ʒu�܂ł�1.0�Ƃ��āA�\���͈͂̐[���̔{�������� prm_dep �Őݒ肷��B
     * prm_dep=1.0�Ƃ����ꍇ�B�\���͈͂� ���_�𒆐S�Ƃ��A���a�������J����Z�ʒu�̋����̋��ƂȂ�B
     * �܂��A�\���͈́{�����A�A�N�^�[�B�̃Q�[�����ł̉��͈͂ƂȂ�悤�ɐ݌v���Ă��邽�߁A�J�����̏����ݒ�l��
     * ���ɏd�v�ł���B
     * �ʏ펋��p�����߂�΃Y�[���A�b�v�̌��ʂ������邪�A�{���C�u�����ł́A
     * ��L�̏���Z�ʒu�܂ŃJ�����������ň������߁A����p��ύX���Ă��A�N�^�[�̕\���̑傫���͉�ʏ�ς��Ȃ��B
     * ����������p����������΁A�����̃J�����������������L�т邱�ƂɂȂ�A���ʂƂ���
     * �\���͈͂��g�傷����ʂ����邱�Ƃ��ł���B
     * �t�Ɏ���p���L����΁A�J�����̏���Z�ʒu�͌��_�ɋ߂��Ȃ�A���͕\���͈͂͋����Ȃ�B
     *
     * @param prm_name ���O(�f�o�b�N�ŕ\���B���ł��悢)
     * @param prm_rad_fovX ���E�̎���p�i���W�A���j
     * @param prm_dep �[���i_cameraZ_org�̉��{��)
     * @return
     */
    GgafDxCamera(const char* prm_name, float prm_rad_fovX, float prm_dep);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    virtual void setDefaultPosition();

    /**
     * �J�����̒����_��ݒ� .
     * @param prm_tX �����_X���W
     * @param prm_tY �����_Y���W
     * @param prm_tZ �����_Z���W
     */
    virtual void setViewPoint(coord prm_tX, coord prm_tY, coord prm_tZ);

    /**
     * �J�����̒����_��ݒ� .
     * �����̃A�N�^�[��XYZ���W(_X, _Y, _Z)��setViewPoint����邾���ł��B
     * @param prm_pActor ��������A�N�^�[
     */
    virtual void setViewPoint(GgafDxGeometricActor* prm_pActor);

    virtual ~GgafDxCamera(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCAMERAACTOR_H_*/
