#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_
namespace GgafDx9Core {

// (2009/2/12 �̔]�݂�)
// �Q�`�R�� new ���āA�P�J���A�Q�J���݂����Ȑ؂�ւ����삪�ł�����ǂ�������


/**
 * �J�����A�N�^�[.
 * GgafDx9UntransformedActor ���p�����A�J������\�����A�N�^�[�ł��B<BR>
 * �{�N���X�͐_(GgafDx9God)�ƘA���Ă��܂��B�����o�𑀍삷��ƁA���̒ʂ�ɃJ�����̈ʒu�ƒ����_������ł��܂��B<BR>
 * processDrawPrior ���\�b�h����������Ă���A���̒��Ő_(GgafDx9God)�̃J�����ɍ��W�����㏑�����܂��B<BR>
 * <BR>
 * _X,_Y,_Z             �E�E�E �J�����̈ʒu <BR>
 * _gazeX,_gazeY,_gazeZ �E�E�E �J����������������W <BR>
 * <BR>
 * ���g������<BR>
 * �p�����AprocessBehavior() ���� �I�[�o�[���C�h���čD���ɍ��W�𓮂��������ŗǂ�<BR>
 * <BR>
 */
class GgafDx9Camera : public GgafDx9UntransformedActor {
private:

public:
    /** �ˉe�ϊ�������� */
    D3DXMATRIX _vMatrixProj;
    /** ���ˉe�ϊ�������� */
    D3DXMATRIX _vMatrixOrthoProj;

    /** �J�����̈ʒu */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** �J�����̒����_ */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** �J�����̏�x�N�g��(�ǂݍ��ݐ�p) */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW�ϊ��s��(�ǂݍ��ݐ�p) */
    D3DXMATRIX _vMatrixView;
    /** ����pX(�ǂݍ��ݐ�p) */
    float _rad_fovX;
    /** ����pY(�ǂݍ��ݐ�p) */
    float _rad_fovY;
    /** �J������Z���W(�ǂݍ��ݐ�p) */
    float _cameraZ;
    /** �J������Z���W�����ʒu(�ǂݍ��ݐ�p) */
    float _cameraZ_org;
    /** �A�X�y�N�g�� */
    float _screen_aspect;

    float _tan_half_fovY;
    float _tan_half_fovX;
    float _dCamHarfXfovTan;
    float _view_border_slant1_XZ;
    float _view_border_slant2_XZ;

    /** �����_�i�ǂݏ�����) */
    int _gazeX, _gazeY, _gazeZ;

    GgafDx9Camera(const char* prm_name);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement() {
    }

    /**
     * �J�����̍X�V
     */
    virtual void processDrawPrior();

    virtual void processDrawMain() {
    }

    virtual void processDrawTerminate() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    /**
     * �J�����̒����_��ݒ� .
     * @param prm_tX �����_X���W
     * @param prm_tY �����_Y���W
     * @param prm_tZ �����_Z���W
     */
    void setGaze(int prm_tX, int prm_tY, int prm_tZ) {
        _gazeX = prm_tX;
        _gazeY = prm_tY;
        _gazeZ = prm_tZ;
    }

    /**
     * �J�����̒����_��ݒ� .
     * �����̃A�N�^�[��XYZ���W(_X, _Y, _Z)��setGaze����邾���ł��B
     * @param prm_pActor ��������A�N�^�[
     */
    void setGaze(GgafDx9UntransformedActor* prm_pActor) {
        _gazeX = prm_pActor->_X;
        _gazeY = prm_pActor->_Y;
        _gazeZ = prm_pActor->_Z;
    }

    virtual ~GgafDx9Camera(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
