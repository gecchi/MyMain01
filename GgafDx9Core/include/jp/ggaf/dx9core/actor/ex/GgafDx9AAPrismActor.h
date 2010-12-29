#ifndef GGAFDX9AAPRISMACTOR_H_
#define GGAFDX9AAPRISMACTOR_H_

                                  //   XYZxx
#define POS_PRISM_XY_nn   (0x18)  //0b 11000
#define POS_PRISM_XY_np   (0x19)  //0b 11001
#define POS_PRISM_XY_pn   (0x1a)  //0b 11010
#define POS_PRISM_XY_pp   (0x1b)  //0b 11011
#define POS_PRISM_YZ_nn   (0xc)   //0b 01100
#define POS_PRISM_YZ_np   (0xd)   //0b 01101
#define POS_PRISM_YZ_pn   (0xe)   //0b 01110
#define POS_PRISM_YZ_pp   (0xf)   //0b 01111
#define POS_PRISM_ZX_nn   (0x14)  //0b 10100
#define POS_PRISM_ZX_np   (0x15)  //0b 10101
#define POS_PRISM_ZX_pn   (0x16)  //0b 10110
#define POS_PRISM_ZX_pp   (0x17)  //0b 10111

#define POS_PRISM_nn      (0x0)    //0b 00000
#define POS_PRISM_np      (0x1)    //0b 00001
#define POS_PRISM_pn      (0x2)    //0b 00010
#define POS_PRISM_pp      (0x3)    //0b 00011
#define POS_PRISM_XY      (0x18)   //0b 11000
#define POS_PRISM_YZ      (0xc)    //0b 01100
#define POS_PRISM_ZX      (0x14)   //0b 10100

//�⑫
//�v���Y���ʒu��\���萔�͈ȉ��̂悤�ɂȂ��Ă���
//"POS_PRISM_" + �ǂ̕��ʂɃX���C�X�����邩 + "_" + �X���C�X�̎d��
//[�ǂ̕��ʂɃX���C�X�����邩]
//XY �E�E�E AAB��XY���ʂɐ����ɃX���C�X
//YZ �E�E�E AAB��YZ���ʂɐ����ɃX���C�X
//ZX �E�E�E AAB��ZX���ʂɐ����ɃX���C�X
//[�X���C�X�̎d��]
// n(negative)�͕������Ap(positive)�͐������A�Ƃ����Ӗ����������Ă���
//nn �E�E�E ���p�O�p�`�̒��p�̕�������̕��ʍ��W�n�� (������, ������) �ƌ����Ӗ�
//np �E�E�E ���p�O�p�`�̒��p�̕�������̕��ʍ��W�n�� (������, ������) �ƌ����Ӗ�
//pn �E�E�E ���p�O�p�`�̒��p�̕�������̕��ʍ��W�n�� (������, ������) �ƌ����Ӗ�
//pp �E�E�E ���p�O�p�`�̒��p�̕�������̕��ʍ��W�n�� (������, ������) �ƌ����Ӗ�

namespace GgafDx9Core {

/**
 * AA�v���Y��.
 * GgafDx9GeometricActor ���p�����A�v���Y����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class GgafDx9AAPrismActor : public GgafDx9MeshActor {
public:
    class RotPosPrism : public GgafCore::GgafObject {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
        RotPosPrism() {}
        RotPosPrism(angle rx, angle rz, angle ry) : GgafCore::GgafObject(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };


    static boolean init;
    static _MAP_<int, GgafDx9AAPrismActor::RotPosPrism> pos2r;

    GgafDx9AAPrismActor(const char* prm_name,
                        GgafDx9Checker* prm_pChecker);

///**
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processDraw();
//
    void drawPrism(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int pos_prism);

    virtual ~GgafDx9AAPrismActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDX9BOXACTOR_H_*/
