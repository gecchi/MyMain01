#ifndef GGAF_DX_AAPYRAMIDACTOR_H_
#define GGAF_DX_AAPYRAMIDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * AA�s���~�b�h.
 * MeshActor ���p�����A�s���~�b�h��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�ŁA
 * (-0.5, -0.5, -0.5) ���R���p�̒��_�ƂȂ钼�p�O�p����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2016/01/15
 * @author Masatoshi Tsuge
 */
class AAPyramidActor : public MeshActor {
public:
    class RotPosPyramid : public GgafCore::Object {
    public:
        angle _rx;
        angle _rz;
        angle _ry;
    public:
        RotPosPyramid() : _rx(0), _rz(0), _ry(0) {
        };
        RotPosPyramid(angle rx, angle rz, angle ry) :
            GgafCore::Object(), _rx(rx), _rz(rz), _ry(ry) {
        }
    };

    static std::map<int, AAPyramidActor::RotPosPyramid> pos2r;

public:
    AAPyramidActor(const char* prm_name, Checker* prm_pChecker);

    static bool initStatic();

    void drawPyramid(coord prm_x1, coord prm_y1, coord prm_z1,
                     coord prm_x2, coord prm_y2, coord prm_z2, pos_t pos_info);

    virtual ~AAPyramidActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_AAPYRAMIDACTOR_H_*/

//�⑫
//�s���~�b�h�ʒu(pos_info)���A�\���萔(CommonHeader.h�Œ�`)�͈ȉ��̂悤�Ȗ������Ȃ���Ă���B
//���၄
//POS_PYRAMID_NPN
//
//���Ӗ���
//"POS_PYRAMID_" + �ǂ̒��_���R���p�̒��_��
//�X���C�X�����O�̗����̂����_�ɂ������Ƃ��āA
//�X���C�X����ďo���オ�������p�O�p���̂R���p�̒��_�̈ʒu��\���Ă���B
//n(negative)�͕������Ap(positive)�͐������A�Ƃ����Ӗ����������Ă���
//POS_PYRAMID_NPN �� "npn" �̂R�����̕����́A
//�P�����ڂ�X���̐���,�Q�����ڂ�Y���̐����A�R�����ڂ�Z���̐���
//��\���A��� "npn" �� (x, y, z) = (-, +, -) �̏ی��ɂR���p�̒��_�������
//�Ƃ����Ӗ�
