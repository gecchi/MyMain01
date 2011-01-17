#ifndef GGAFDX9AAPRISMACTOR_H_
#define GGAFDX9AAPRISMACTOR_H_

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
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃v���Y����ǂݍ��܂��Ă��������B
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
