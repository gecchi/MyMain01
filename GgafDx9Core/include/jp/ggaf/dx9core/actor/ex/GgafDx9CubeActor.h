#ifndef GGAFDX9CUBEACTORD_H_
#define GGAFDX9CUBEACTORD_H_
namespace GgafDx9Core {

/**
 * �L���[�u�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�L���[�u�i�����́j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeActor : public GgafDx9MeshActor {

public:
    GgafDx9CubeActor(const char* prm_name,
                     GgafDx9Checker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2);

    virtual ~GgafDx9CubeActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9CUBEACTORD_H_*/
