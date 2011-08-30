#ifndef GGAFDX9SPHEREACTOR_H_
#define GGAFDX9SPHEREACTOR_H_
namespace GgafDx9Core {

/**
 * ���A�N�^�[.
 * GgafDx9GeometricActor ���p�����A����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A���a�Ppx�����̋�(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class GgafDx9SphereActor : public GgafDx9MeshActor {

public:
    GgafDx9SphereActor(const char* prm_name,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDx9Checker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r);

    virtual ~GgafDx9SphereActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9SPHEREACTOR_H_*/
