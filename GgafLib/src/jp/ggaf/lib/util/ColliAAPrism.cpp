#include "jp/ggaf/lib/util/ColliAAPrism.h"

#include "jp/ggaf/lib/util/StgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPrism::ColliAAPrism() : ColliAABox() {
    _shape_kind = COLLI_AAPRISM;
    _a = 0;
    _b = 0;
    _vIH_x = 0;
    _vIH_y = 0;
}

void ColliAAPrism::set(int x1, int y1, int z1, int x2, int y2, int z2, pos_t pos_info, bool rot_x, bool rot_y, bool rot_z) {
#ifdef MY_DEBUG
    if (rot_x || rot_y || rot_z) {
        //TODO:�Ђ܂Ȃ�v���Y���v�f�͉�]���s�ړ�����
        throwGgafCriticalException("�����蔻��̃v���Y���v�f�͉�]���s�ړ��͖��Ή��ł��B");
    }
#endif

    ColliAABox::set(x1, y1, z1, x2, y2, z2, rot_x, rot_y, rot_z);

    //   y  = ax + b
    //   a  = (y2-y1)/(x2-x1)
    //   b  = (x1y2-x2y1) / (x1-x2)

    //   y  = {(y2-y1)/(x2-x1)} (x-x1) + y1
    //+90�x�Ŗ@���ōs����
    int x1_s=0, y1_s=0, x2_e=0, y2_e=0;
    _pos_info = pos_info;
    if (_pos_info & POS_PRISM_XY_xx) {
        if (_pos_info & POS_PRISM_xx_PP) {
            //            �� y+
            // (_x1,_y2)      (_x2,_y2)
            //        ����������
            //        ���_������
            // x- ��  ��  �_�焠  �� x+
            //        ��    �_��
            //        ����������
            // (_x1,_y1)      (_x2,_y1)
            //            �� y-
            x1_s = _x2;
            y1_s = _y1;
            x2_e = _x1;
            y2_e = _y2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            �� y+
            // (_x1,_y2)      (_x2,_y2)
            //        ����������
            //        �������^��
            // x- ��  ����^  ��  �� x+
            //        ���^    ��
            //        ����������
            // (_x1,_y1)      (_x2,_y1)
            //            �� y-
            x1_s = _x2;
            y1_s = _y2;
            x2_e = _x1;
            y2_e = _y1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            �� y+
            // (_x1,_y2)      (_x2,_y2)
            //        ����������
            //        ��    �^��
            // x- ��  ��  �^����  �� x+
            //        ���^���焠
            //        ����������
            // (_x1,_y1)      (_x2,_y1)
            //            �� y-
            x1_s = _x1;
            y1_s = _y1;
            x2_e = _x2;
            y2_e = _y2;
        } else { // �̂���� POS_PRISM_xx_NN
            //            �� y+
            // (_x1,_y2)      (_x2,_y2)
            //        ����������
            //        ���_    ��
            // x- ��  �����_  ��  �� x+
            //        ������_��
            //        ����������
            // (_x1,_y1)      (_x2,_y1)
            //            �� y-
            x1_s = _x1;
            y1_s = _y2;
            x2_e = _x2;
            y2_e = _y1;
        }


    } else if (_pos_info & POS_PRISM_YZ_xx) {

        if (_pos_info & POS_PRISM_xx_PP) {
            //            �� z+
            // (_y1,_z2)      (_y2,_z2)
            //        ����������
            //        ���_������
            // y- ��  ��  �_�焠  �� y+
            //        ��    �_��
            //        ����������
            // (_y1,_z1)      (_y2,_z1)
            //            �� z-
            x1_s = _y2;
            y1_s = _z1;
            x2_e = _y1;
            y2_e = _z2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            �� z+
            // (_y1,_z2)      (_y2,_z2)
            //        ����������
            //        �������^��
            // y- ��  ����^  ��  �� y+
            //        ���^    ��
            //        ����������
            // (_y1,_z1)      (_y2,_z1)
            //            �� z-
            x1_s = _y2;
            y1_s = _z2;
            x2_e = _y1;
            y2_e = _z1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            �� z+
            // (_y1,_z2)      (_y2,_z2)
            //        ����������
            //        ��    �^��
            // y- ��  ��  �^����  �� y+
            //        ���^���焠
            //        ����������
            // (_y1,_z1)      (_y2,_z1)
            //            �� z-
            x1_s = _y1;
            y1_s = _z1;
            x2_e = _y2;
            y2_e = _z2;
        } else { // �̂���� POS_PRISM_xx_NN
            //            �� z+
            // (_y1,_z2)      (_y2,_z2)
            //        ����������
            //        ���_    ��
            // y- ��  �����_  ��  �� y+
            //        ������_��
            //        ����������
            // (_y1,_z1)      (_y2,_z1)
            //            �� z-
            x1_s = _y1;
            y1_s = _z2;
            x2_e = _y2;
            y2_e = _z1;
        }

    } else if (_pos_info & POS_PRISM_ZX_xx) {
        if (_pos_info & POS_PRISM_xx_PP) {
            //            �� x+
            // (_z1,_x2)      (_z2,_x2)
            //        ����������
            //        ���_������
            // z- ��  ��  �_�焠  �� z+
            //        ��    �_��
            //        ����������
            // (_z1,_x1)      (_z2,_x1)
            //            �� x-
            x1_s = _z2;
            y1_s = _x1;
            x2_e = _z1;
            y2_e = _x2;
        } else if (_pos_info & POS_PRISM_xx_NP) {
            //            �� x+
            // (_z1,_x2)      (_z2,_x2)
            //        ����������
            //        �������^��
            // z- ��  ����^  ��  �� z+
            //        ���^    ��
            //        ����������
            // (_z1,_x1)      (_z2,_x1)
            //            �� x-
            x1_s = _z2;
            y1_s = _x2;
            x2_e = _z1;
            y2_e = _x1;
        } else if (_pos_info & POS_PRISM_xx_PN) {
            //            �� x+
            // (_z1,_x2)      (_z2,_x2)
            //        ����������
            //        ��    �^��
            // z- ��  ��  �^����  �� z+
            //        ���^���焠
            //        ����������
            // (_z1,_x1)      (_z2,_x1)
            //            �� x-
            x1_s = _z1;
            y1_s = _x1;
            x2_e = _z2;
            y2_e = _x2;
        } else { // �̂���� POS_PRISM_xx_NN
            //            �� x+
            // (_z1,_x2)      (_z2,_x2)
            //        ����������
            //        ���_    ��
            // z- ��  �����_  ��  �� z+
            //        ������_��
            //        ����������
            // (_z1,_x1)      (_z2,_x1)
            //            �� x-
            x1_s = _z1;
            y1_s = _x2;
            x2_e = _z2;
            y2_e = _x1;
        }
    } else {
        //memo WallAAPrismActor �� ��new���̓v���Y���ʒu 0 �ɂ��邱�ƂƂ����̂ŁA
        //�ȉ��̃G���[�̓X���[����悤�ɕύX�����B

        //throwGgafCriticalException("�������ȃv���Y���ʒu _pos_info="<<_pos_info)
    }

    //�����蔻�莞�Ɏg�p����v�Z�p�̒l��\�ߋ��߂Ă����B
    if (x2_e == x1_s) {
        _a = 0;
        _b = 0;
    } else {
        //�v���Y���Εӂ̋��E���X��
        _a = 1.0*(y2_e - y1_s) / (x2_e - x1_s);
        //�v���Y���Εӂ̋��E���̐ؕ�
        _b = (x1_s*y2_e - x2_e*y1_s) / (x1_s - x2_e);
    }
    //���ƂŌv�Z���y�ɂȂ邽�߁A
    //�v���Y���ΕӖʂ̖@���x�N�g���̋t�����̃x�N�g�� _vIH_x, _vIH_y�����߂Ă���
    //�ΕӃx�N�g��(x2_e-x1_s, y2_e-y1_s)��90�x�������
    //�ΕӖʂ̖@���x�N�g���ƂȂ�悤�ɂ��Ă���B
    //�����ŕێ����Ă��������̂�-90�x(+270�x)�̃x�N�g���ł���
    angle angIH = UTIL::simplifyAng(
        UTIL::getAngle2D(x2_e-x1_s, y2_e-y1_s)
        + D270ANG
        );
    _vIH_x = UTIL::COS[angIH/SANG_RATE];
    _vIH_y = UTIL::SIN[angIH/SANG_RATE];

}


ColliAAPrism::~ColliAAPrism() {
}
