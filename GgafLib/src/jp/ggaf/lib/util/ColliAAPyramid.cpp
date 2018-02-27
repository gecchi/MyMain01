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
    //�Ίp���x�N�g��
    float dg_vx,dg_vy,dg_vz;
    //�Ίp��
//    float a,b,c,d;
    switch (_pos_pyramid) {
        case POS_PYRAMID_nnn: {
            UTIL::getPlaneNomalVec(x2, y1, z1,
                                   x1, y2, z1,
                                   x1, y1, z2,
                                   _s_nvx, _s_nvy, _s_nvz, _s_d);
            //�Ίp���x�N�g��
            dg_vx = x2-x1;
            dg_vy = y2-y1;
            dg_vz = z2-z1;

            float x0, y0, z0;//�ʂ�_
            x0 = x1;
            y0 = y1;
            z0 = z1;
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
            _l_px = x0 + t*dg_vx;
            _l_py = y0 + t*dg_vy;
            _l_pz = z0 + t*dg_vz;
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
//    _d_c2vtx = UTIL::getDistance(_cx, _cy, _cz, _x1, _y1, _z1);
}


ColliAAPyramid::~ColliAAPyramid() {
}
