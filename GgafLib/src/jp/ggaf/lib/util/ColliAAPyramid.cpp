#include "jp/ggaf/lib/util/ColliAAPyramid.h"

#include "jp/ggaf/lib/util/StgUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

ColliAAPyramid::ColliAAPyramid() : ColliAABox() {
    _pos_pyramid = -1;
    _shape_kind = COLLI_AAPYRAMID;
}

void ColliAAPyramid::set(int prm_x1, int prm_y1, int prm_z1, int prm_x2, int prm_y2, int prm_z2, int prm_pos_pyramid, bool prm_rot_x, bool prm_rot_y, bool prm_rot_z) {
#ifdef MY_DEBUG
    if (prm_rot_x || prm_rot_y || prm_rot_z) {
        //TODO:�Ђ܂Ȃ����
        throwGgafCriticalException("�����蔻��̒��p�O�p���v�f�͉�]���s�ړ��͖��Ή��ł��B");
    }
#endif
    ColliAABox::set(prm_x1, prm_y1, prm_z1, prm_x2, prm_y2, prm_z2, prm_rot_x, prm_rot_y, prm_rot_z);
    _pos_pyramid = prm_pos_pyramid;
    //�@���x�N�g����\�ߋ��߂ĕێ�
    float x1 = C_DX(_x1);
    float y1 = C_DX(_y1);
    float z1 = C_DX(_z1);
    float x2 = C_DX(_x2);
    float y2 = C_DX(_y2);
    float z2 = C_DX(_z2);

    float dg_vx, dg_vy, dg_vz; //�Ίp�������x�N�g��
    float x0, y0, z0;          //�R���p�̒��_�i�Ίp�����ʂ�_�j
    switch (_pos_pyramid) {
        case POS_PYRAMID_nnn: {
            UTIL::getPlaneNomalVec(x2, y1, z1,
                                   x1, y2, z1,
                                   x1, y1, z2,
                                   _s_nvx, _s_nvy, _s_nvz, _s_d);
            x0 = x1;
            y0 = y1;
            z0 = z1;
            dg_vx = x2-x1;
            dg_vy = y2-y1;
            dg_vz = z2-z1;
            break;
         }
         case POS_PYRAMID_nnp: {
             UTIL::getPlaneNomalVec(x1, y1, z1,
                                    x1, y2, z2,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y1;
             z0 = z2;
             dg_vx = x2-x1;
             dg_vy = y2-y1;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_npn: {
             UTIL::getPlaneNomalVec(x2, y2, z1,
                                    x1, y2, z2,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y2;
             z0 = z1;
             dg_vx = x2-x1;
             dg_vy = y1-y2;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_npp: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y1, z2,
                                    x1, y2, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x1;
             y0 = y2;
             z0 = z2;
             dg_vx = x2-x1;
             dg_vy = y1-y2;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_pnn: {
             UTIL::getPlaneNomalVec(x2, y1, z2,
                                    x2, y2, z1,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y1;
             z0 = z1;
             dg_vx = x1-x2;
             dg_vy = y2-y1;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_pnp: {
             UTIL::getPlaneNomalVec(x1, y1, z2,
                                    x2, y2, z2,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y1;
             z0 = z2;
             dg_vx = x1-x2;
             dg_vy = y2-y1;
             dg_vz = z1-z2;
             break;
         }
         case POS_PYRAMID_ppn: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y2, z1,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y2;
             z0 = z1;
             dg_vx = x1-x2;
             dg_vy = y1-y2;
             dg_vz = z2-z1;
             break;
         }
         case POS_PYRAMID_ppp: {
             UTIL::getPlaneNomalVec(x1, y2, z2,
                                    x2, y2, z1,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             x0 = x2;
             y0 = y2;
             z0 = z2;
             dg_vx = x1-x2;
             dg_vy = y1-y2;
             dg_vz = z1-z2;
             break;
         }
         default: {
             throwGgafCriticalException("ColliAAPyramid::set() prm_pos_pyramid ���s���ł��Bprm_pos_pyramid="<<prm_pos_pyramid);
             break;
         }
     }

    //�Ίp���ƎΖʂ̌�_�����߂�
    //
    //���ꂪ�Ax0, y0, z0 ��ʂ�̂őΊp���̕�������
    // (x-x0/dg_vx) = (y-y0/dg_vy) = (z-z0/dg_vz)
    // (x,y,z) = (x0,y0,z0) + t(dg_vx,dg_vy,dg_vz)     �E�E�E�@
    //�Ζ� _s_nvx*x + _s_nvy*y + _s_nvz*z + _s_d = 0   �E�E�E�A
    //�@���A�ɑ�����āA�������߂�
    // _s_nvx*(x0+t*dg_vx) + _s_nvy*(y0+t*dg_vy) + _s_nvz*(z0+t*dg_vz) + _s_d = 0
    // t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx)
    //������@�֑��
    float t=-(_s_nvz*z0+_s_nvy*y0+_s_nvx*x0+_s_d)/(_s_nvz*dg_vz+_s_nvy*dg_vy+_s_nvx*dg_vx);
    //��_��
    _l_px = DX_C(x0 + t*dg_vx);
    _l_py = DX_C(y0 + t*dg_vy);
    _l_pz = DX_C(z0 + t*dg_vz);


    // 2���̋����������̏ꍇ�킯�Őݒ�
    //
    //  a
    //	if(o_scx < b_x1) {
    //		square_length += (double)(o_scx - b_x1) * (o_scx - b_x1);
    //	}

    //	b
    //	if(o_scx > b_x2) {
    //		square_length += (double)(o_scx - b_x2) * (o_scx - b_x2);
    //	}

    //          a         b      c        d      e
    //    -------------><---><---------><---><-----------------
    //              ,���A
    //             ��  ��   ,���A
    //              `��'  _��_ ���@
    //                  |�_ `��'
    //                  |  �_   �_
    //                  |    �_  r�_
    //                  |      �_   �_
    //                  |        �_    ,���A�A
    //                  |          �_ ��| ��
    //                  |            �_`+-'
    //                  ----------------,���A
    //              ,���A              ��  ��
    //             ��  ��               `��'
    //              `��'

    //�ΖʂƋ����ڂ����ꍇ�A���̒��S(cx,cy,cz)���琂�����Ζʂɍ~�낵���_P(x,y,z)���l��
    //��(cx,cy,cz)-(x,y,z) �� XY���ʁAYZ���ʁAZX���ʂ��猩�����ꂼ��́u�Ȃ��p�v�Ƃ����߂�
    //�@ �A�A�̂Ƃ��̑�������2���̋��������߂邽�߂�






    // XY���ʂōl����
    //
    //    (x1,y1) (x2,y2) �� �ʂ钼��
    //    y = ax + b
    //    a = (y2-y1) / (x2-x1)
    //    b = (x2*y1 - x1*y2) / (x2-x1)
    //
    // (a,b) (c,d) ��ʂ钼��
    //�X�� = (d-b) / (c-a);
    //�ؕ� = (c*b - a*d) / (c-a);

    //y = ax + b ���
    //b = y - ax

    // XY���ʂōl����
    // a = (y2-y1) / (x2-x1) ���
    float a_XY = (y2-y1) / (x2-x1);

//    if ((_pos_pyramid & POS_PYRAMID_ppn) ||(_pos_pyramid & POS_PYRAMID_ppp)) {
////    (x1,y2)    (x2,y2)
////        _______
////        �_    |
////          �_  |
////            �_|
////              (x2, y1)�R�R
//        _rad_xy =              UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_npn) ||(_pos_pyramid & POS_PYRAMID_npp)) {
////    (x1,y2)    (x2,y2)�R�R
////        _______
////        |    �^
////        |  �^
////        |�^
////    (x1, y1)
//        _rad_xy = (PI / 2.0) + UTIL::getRad2D(x1-x2,y2-y2 , x1-x2,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_nnn) ||(_pos_pyramid & POS_PYRAMID_nnp)) {
////    (x1,y2)�R�R
////        |�_
////        |  �_
////        |    �_
////        --------
//// (x1, y1)   (x2, y1)
//        _rad_xy = PI + UTIL::getRad2D(x1-x1,y1-y2 , x2-x1,y1-y2);
//    }
//    if ((_pos_pyramid & POS_PYRAMID_pnn) ||(_pos_pyramid & POS_PYRAMID_pnp)) {
////          (x2,y2)�R�R
////        �^|
////      �^  |
////    �^    |
////   --------
//// (x1, y1)   (x2, y1)
//        _rad_xy = ((3.0 * PI) / 2.0) + UTIL::getRad2D(x2-x2,y1-y2 , x1-x2,y1-y2);
//    }
//
////    _rad_xy =              UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);

    _rad_xy = UTIL::getRad2D(x2-x2,y2-y1 , x1-x2,y2-y1);
    _rad_yz = UTIL::getRad2D(y2-y2,z2-z1 , y1-y2,z2-z1);
    _rad_zx = UTIL::getRad2D(z2-z2,x2-x1 , z1-z2,x2-x1);
}


ColliAAPyramid::~ColliAAPyramid() {
}
