#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

ColliAAPrism::ColliAAPrism() : ColliAAB() {
    _pos_prism = 0;
    _shape_kind = COLLI_AAPRISM;
}

void ColliAAPrism::set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ) {
    ColliAAB::set(x1, y1, z1, x2, y2, z2, rotX, rotY, rotZ);

    //   y  = ax + b
    //   a  = (y2-y1)/(x2-x1)
    //   b  = (x1y2-x2y1) / (x1-x2)

    //   y  = {(y2-y1)/(x2-x1)} (x-x1) + y1

    _pos_prism = pos_prism;
    if (_pos_prism & POS_PRISM_XY) {
        _a = 1.0*(_y2 - _y1) / (_x2 - _x1);
        _b = (_x1*_y2 - _x2*_y1) / (_x1 - _x2);


    } else if (_pos_prism & POS_PRISM_YZ) {
        _a = 1.0*(_z2 - _z1) / (_y2 - _y1);
        _b = (_y1*_z2 - _y2*_z1) / (_y1 - _y2);

    } else if (_pos_prism & POS_PRISM_ZX) {
        _a = 1.0*(_x2 - _x1) / (_z2 - _z1);
        _b = (_z1*_x2 - _z2*_x1) / (_z1 - _z2);
    }
   if (_pos_prism & POS_PRISM_pp) {
        //            �� y+
        //
        //        ����������
        //        ���_������
        // x- ��  ���@�_�焠  �� x+
        //        ���@�@�_��
        //        ����������
        //
        //            �� y-
        _a = -1.0*_a; //�X���͉E������ɂȂ邽��
    } else if (_pos_prism & POS_PRISM_np) {
        //            �� y+
        //
        //        ����������
        //        �������^��
        // x- ��  ����^�@��  �� x+
        //        ���^�@�@��
        //        ����������
        //
        //            �� y-
        
    } else if (_pos_prism & POS_PRISM_pn) {
        //            �� y+
        //
        //        ����������
        //        ���@�@�^��
        // x- ��  ���@�^����  �� x+
        //        ���^���焠
        //        ����������
        //
        //            �� y-

    } else { // �̂���� POS_PRISM_nn
        //            �� y+
        //
        //        ����������
        //        ���_�@�@��
        // x- ��  �����_�@��  �� x+
        //        ������_��
        //        ����������
        //
        //            �� y-
        _a = -1.0*_a; //�X���͉E������ɂȂ邽��
    } 
}


ColliAAPrism::~ColliAAPrism() {
    TRACE("ColliAAPrism::~ColliAAPrism()");
}
