#ifndef GGAFDX9CAMERAACTOR_H_
#define GGAFDX9CAMERAACTOR_H_
namespace GgafDx9Core {

// (2009/2/12 �̔]�݂�)
// �Q�`�R�� new ���āA�P�J���A�Q�J���݂����Ȑ؂�ւ����삪�ł�����ǂ�������


/**
 * �J�����A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�J������\�����A�N�^�[�ł��B<BR>
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
class GgafDx9Camera : public GgafDx9GeometricActor {
private:

public:



    // �������6�̖ʂ̒��_���W
    /** ������ʁA��O�̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecNear[4];
    /** ������ʁA���̎l�p�`�̒��_(�ǂݍ��ݐ�p�A���t���[���X�V) */
    D3DXVECTOR3 _vecFar[4];

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







    /** ���W�ړ��x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;


    /** �ˉe�ϊ�������� */
    D3DXMATRIX _vMatrixProj;
    /** ���ˉe�ϊ�������� */
    D3DXMATRIX _vMatrixOrthoProj;

    /** �J�����̈ʒu(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamFromPoint;
    /** �J�����̒����_(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXVECTOR3* _pVecCamLookatPoint;
    /** �J�����̏�x�N�g��(�ǂݍ��ݐ�p�A������s��) */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW�ϊ��s��(�ǂݍ��ݐ�p�A�t���[�����X�V) */
    D3DXMATRIX _vMatrixView;
    /** ����pX(�ǂݍ��ݐ�p�A������s��) */
    float _rad_fovX;
    /** ����pX�̔���(�ǂݍ��ݐ�p�A������s��) */
    float _rad_half_fovX;
    /** ����pY(�ǂݍ��ݐ�p�A������s��) */
    float _rad_fovY;
    /** ����pY�̔���(�ǂݍ��ݐ�p�A������s��) */
    float _rad_half_fovY;
    /** �J������Z���W(�ǂݍ��ݐ�p) */
    float _cameraZ;
    /** �J������Z���W�����ʒu(�ǂݍ��ݐ�p�A������s��) */
    float _cameraZ_org;
    /** �A�X�y�N�g��(�ǂݍ��ݐ�p�A������s��) */
    float _screen_aspect;

    float _tan_half_fovY;
    float _tan_half_fovX;
    float _dCamHarfXfovTan;

//    /** XY���ʍ��W�̎��_���璍���_�����Ԓ����̌X�� */
//    float _view_slant_XZ;
//    /** XY���ʍ��W�̎��_���璍���_�����Ԓ����̌X�� */
//    float _view_slant_ZY;

//    float _view_rad_XZ;
//    float _view_rad_ZY;

//    float _view_border_rad1_XZ;
//    float _view_border_rad2_XZ;
//    float _view_border_rad1_ZY;
//    float _view_border_rad2_ZY;

//    float _view_border_slant1_XZ;
//    float _view_border_slant2_XZ;
//    float _view_border_slant1_ZY;
//    float _view_border_slant2_ZY;
    //�ؕ�
//    int _view_border_intercept1_XZ;
//    int _view_border_intercept2_XZ;
//    int _view_border_intercept1_ZY;
//    int _view_border_intercept2_ZY;

    /** �����_�i�ǂݏ�����) */
    int _gazeX, _gazeY, _gazeZ;

    /**
     * �R���X�g���N�^
     * @param prm_name ���O(�f�o�b�N�ŕ\���B���ł��悢)
     * @param prm_rad_fovX ���E�̎���p�i���W�A���j
     * @return
     */
    GgafDx9Camera(const char* prm_name, float prm_rad_fovX);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void processDrawPrior() {
    }

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

//    virtual int canView(GgafDx9GeometricActor* pActor) {
//        return canView(pActor, pActor->_max_radius);
//    }
//
//
//    virtual int canView(GgafDx9GeometricActor* pActor, FLOAT radius);


//    virtual bool isInTheViewports_old(int prm_X, int prm_Y, int prm_Z);
//
//    virtual bool isInTheViewports_old(GgafDx9GeometricActor* prm_pActor) {
//        return isInTheViewports_old(prm_pActor->_X, prm_pActor->_Y, prm_pActor->_Z);
//    }

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
    void setGaze(GgafDx9GeometricActor* prm_pActor) {
        _gazeX = prm_pActor->_X;
        _gazeY = prm_pActor->_Y;
        _gazeZ = prm_pActor->_Z;
    }

    virtual ~GgafDx9Camera(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
