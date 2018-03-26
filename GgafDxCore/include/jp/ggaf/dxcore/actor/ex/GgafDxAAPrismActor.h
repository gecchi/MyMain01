#ifndef GGAFDXCORE_GGAFDXAAPRISMACTOR_H_
#define GGAFDXCORE_GGAFDXAAPRISMACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * AA�v���Y��.
 * GgafDxGeometricActor ���p�����A�v���Y����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃v���Y����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/12/29
 * @author Masatoshi Tsuge
 */
class GgafDxAAPrismActor : public GgafDxMeshActor {
public:
    class RotPosPrism : public GgafCore::GgafObject {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPrism() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPrism(angle rx, angle rz, angle ry) :
            GgafCore::GgafObject(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    static std::map<int, GgafDxAAPrismActor::RotPosPrism> pos2r;

public:
    GgafDxAAPrismActor(const char* prm_name,
                        GgafCore::GgafStatus* prm_pStat,
                        GgafDxChecker* prm_pChecker);

    static bool initStatic();

    void drawPrism(coord prm_x1, coord prm_y1, coord prm_z1,
                   coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~GgafDxAAPrismActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXBOXACTOR_H_*/

//�⑫
//�v���Y���ʒu(pos_info)���A�\���萔(GgafDxCommonHeader.h�Œ�`)�͈ȉ��̂悤�Ȗ������Ȃ���Ă���B
//���၄
//POS_PRISM_YZ_NN
//���Ӗ���
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
