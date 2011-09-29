#ifndef GGAFDXBOXACTOR_H_
#define GGAFDXBOXACTOR_H_
namespace GgafDxCore {

/**
 * �L���[�u�A�N�^�[.
 * GgafDxGeometricActor ���p�����A�L���[�u�i�����́j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class GgafDxAABActor : public GgafDxMeshActor {

public:
    GgafDxAABActor(const char* prm_name,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~GgafDxAABActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXBOXACTOR_H_*/
