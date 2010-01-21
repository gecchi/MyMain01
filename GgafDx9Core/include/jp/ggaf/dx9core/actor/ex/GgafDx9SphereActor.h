#ifndef GGAFDX9SPHEREACTOR_H_
#define GGAFDX9SPHEREACTOR_H_
namespace GgafDx9Core {

/**
 * ���A�N�^�[.
 * GgafDx9GeometricActor ���p�����A����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A���a�P�̋�(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class GgafDx9SphereActor : public GgafDx9MeshActor {

public:
    GgafDx9SphereActor(const char* prm_name,
                     GgafDx9Checker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawSphere(int prm_x, int prm_y, int prm_z, int prm_r);

    virtual ~GgafDx9SphereActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9SPHEREACTOR_H_*/
