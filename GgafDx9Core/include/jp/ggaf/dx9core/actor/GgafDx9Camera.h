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
    /** �J�����̏�x�N�g�� */
    D3DXVECTOR3* _pVecCamUp;
    /** VIEW�ϊ��s�� */
    D3DXMATRIX _vMatrixView;




    /** �J������Z���W�����ʒu */
    double _cameraZ_org;

    /** �J������Z���W */
    double _cameraZ;


    double _rad_fovY;
    double _rad_fovX;

    double _tan_half_fovY;
    double _tan_half_fovX;
    double _dCamHarfXfovTan;
    double _screen_aspect;
    double _border1_XZ;
    double _border2_XZ;



    //int _iPxDep = 0;

    /** �����_ */
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

    void setGaze(int prm_tX, int prm_tY, int prm_tZ) {
        _gazeX = prm_tX;
        _gazeY = prm_tY;
        _gazeZ = prm_tZ;
    }

    void setGaze(GgafDx9UntransformedActor* prm_pActor) {
        _gazeX = prm_pActor->_X;
        _gazeY = prm_pActor->_Y;
        _gazeZ = prm_pActor->_Z;
    }

    virtual ~GgafDx9Camera(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CAMERAACTOR_H_*/
