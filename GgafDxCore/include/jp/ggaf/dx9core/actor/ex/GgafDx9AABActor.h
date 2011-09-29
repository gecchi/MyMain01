#ifndef GGAFDX9BOXACTOR_H_
#define GGAFDX9BOXACTOR_H_
namespace GgafDx9Core {

/**
 * �L���[�u�A�N�^�[.
 * GgafDx9GeometricActor ���p�����A�L���[�u�i�����́j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDx9AABActor : public GgafDx9MeshActor {

public:
    GgafDx9AABActor(const char* prm_name,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDx9Checker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~GgafDx9AABActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9BOXACTOR_H_*/
