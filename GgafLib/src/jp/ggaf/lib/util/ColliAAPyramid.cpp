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

//    (x1,y1) (x2,y2) �� �ʂ钼��
//    y = ax + b
//    a = (y2-y1) / (x2-x1)
//    b = (x2*y1 - x1*y2) / (x2-x1)


    // (a,b) (c,d) ��ʂ钼��
    //�X�� = (d-b) / (c-a);
    //�ؕ� = (c*b - a*d) / (c-a);

    //y = ax + b ���
    //b = y - ax

    //�@���x�N�g����\�ߋ��߂ĕێ�
    float x1 = PX_DX(_x1);
    float y1 = PX_DX(_y1);
    float z1 = PX_DX(_z1);
    float x2 = PX_DX(_x2);
    float y2 = PX_DX(_y2);
    float z2 = PX_DX(_z2);
    float hdx = PX_DX(_hdx);
    float hdy = PX_DX(_hdy);
    float hdz = PX_DX(_hdz);

    switch (_pos_pyramid) {
        case POS_PYRAMID_nnn: {
            UTIL::getPlaneNomalVec(x2, y1, z1,
                                   x1, y2, z1,
                                   x1, y1, z2,
                                   _s_nvx, _s_nvy, _s_nvz, _s_d);
            // (x1,y2), (x2,y1) ��ʂ钼���̌X���Ɛؕ�
            _a_xy = (y1-y2) / (x2-x1);
            _b_xy_z1 = (x2*y2 - x1*y1) / (x2-x1);
            //���́AZ�� = z1 XY���� �̒l�ɂȂ�B
            //Z�� = z2 XY���� (x1,y1) ��ʂ�A�X���͂��̂܂܂̏ꍇ�̐ؕЂ����߂�
            //y = ax + b ���
            //b = y - ax
            _b_xy_z2 = y1 - _a_xy*x1;

//             //XY���� : (x1,y2), (x1+hdx, y1) ��ʂ钼��
//             _a_xy[0] = (y1-y2) / ((x1+hdx)-x1);
//             _b_xy[0] = ((x1+hdx)*y2 - x1*y1) / ((x1+hdx)-x1);
//             //XY���� : (x2,y1), (x1, y1+hdy) ��ʂ钼��
//             _a_xy[1] = ((y1+hdy)-y1) / (x1-x2);
//             _b_xy[1] = (x1*y1 - x2*(y1+hdy)) / (x1-x2);
//
//             //YZ���� : (y1,z2), (y1+hdy,z1) ��ʂ钼��
//             _a_yz[0] = (z1-z2) / ((y1+hdy)-y1);
//             _b_yz[0] = ((y1+hdy)*z2 - y1*z1) / ((y1+hdy)-y1);
//             //YZ���� : (y2,z1), (y1,z1+hdz) ��ʂ钼��
//             _a_yz[1] = ((z1+hdz)-z1) / (y1-y2);
//             _b_yz[1] = (y1*z1 - y2*(z1+hdz)) / (y1-y2);
//
//             //ZX���� : (z1,x2), (z1+hdz,x1) ��ʂ钼��
//             _a_zx[0] = (x1-x2) / ((z1+hdz)-z1);
//             _b_zx[0] = ((z1+hdz)*x2 - z1*x1) / ((z1+hdz)-z1);
//             //ZX���� : (z2,x1), (z1,x1+hdx) ��ʂ钼��
//             _a_zx[1] = ((x1+hdx)-x1) / (z1-z2);
//             _b_zx[1] = (z1*x1 - z2*(x1+hdx)) / (z1-z2);

             break;
         }
         case POS_PYRAMID_nnp: {
             UTIL::getPlaneNomalVec(x1, y1, z1,
                                    x1, y2, z2,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_npn: {
             UTIL::getPlaneNomalVec(x2, y2, z1,
                                    x1, y2, z2,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_npp: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y1, z2,
                                    x1, y2, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_pnn: {
             UTIL::getPlaneNomalVec(x2, y1, z2,
                                    x2, y2, z1,
                                    x1, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_pnp: {
             UTIL::getPlaneNomalVec(x1, y1, z2,
                                    x2, y2, z2,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_ppn: {
             UTIL::getPlaneNomalVec(x2, y2, z2,
                                    x1, y2, z1,
                                    x2, y1, z1,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         case POS_PYRAMID_ppp: {
             UTIL::getPlaneNomalVec(x1, y2, z2,
                                    x2, y2, z1,
                                    x2, y1, z2,
                                    _s_nvx, _s_nvy, _s_nvz, _s_d);
             break;
         }
         default: {
             break;
         }
     }
    _d_nv = sqrt((_s_nvz*_s_nvz) + (_s_nvy*_s_nvy) + (_s_nvx*_s_nvx));
    _d_c2vtx = UTIL::getDistance(_cx, _cy, _cz, _x1, _y1, _z1);
}


ColliAAPyramid::~ColliAAPyramid() {
}
