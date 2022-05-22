#ifndef GGAF_DX_SPHERERADIUSVECTORS_H_
#define GGAF_DX_SPHERERADIUSVECTORS_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>

namespace GgafDx {

/**
 * �P�ʋ��ƁA�P�ʃx�N�g���̍��W�̃}�b�s���O .
 * �����x�N�g������Z����]�p��Y����]�p�A�t��Z����]�p��Y����]�p��������x�N�g���̑��ݕϊ����\�Ƃ��邽�߂ɐ݌v�B<BR>
 * �A���ێ�����Ă���͈͂͒P�ʋ��́Ax��0 y��0 z��0 �͈̔͂̕����x�N�g�������ł��B�i1/8�����̂݁j<BR>
 * �y�⑫�z<BR>
 * �ێ����Ă���x�N�g���̊e�v(X,Y,Z)�̒P��(uint32_t)�́A����1 �� 10000000 �ɑ������鐮���ɂȂ��Ă��܂��B<BR>
 * �p�x�̒P�ʁis_ang�j�́A�ʓx�@ 1�x �� 10 �ɑ������܂��B���p�� 900 �ɂȂ�܂��B
 * angle�l(�ʓx�@1�x��1000)�ƍ��݂��Ȃ��悤�ɒ���<BR>
 */
class SphereRadiusVectors : public GgafCore::Object {
public:
    struct SrVec {
        uint32_t x;
        uint32_t z;
        uint32_t y;
    };

    struct RzRy {
        s_ang rz;
        s_ang ry;
    };

    SrVec _sr_vec[(D90SANG + 1)][(D90SANG+1)];
    std::map<uint32_t, std::map<uint32_t, RzRy> > _vy_vz_2_rz_ry_rev;

public:
    SphereRadiusVectors();

    /**
     * ������X,Y,Z�����x�N�g������A��������Z����]��Y����]�̋ߎ������߂�B
     * �A���AX,Y,Z �͑S�Đ��łȂ��Ă͂Ȃ�Ȃ�
     * @param prm_x �P�ʕ����x�N�g��X�v�f�i���� 1 �� 10000000) > 0
     * @param prm_y �P�ʕ����x�N�g��Y�v�f�i���� 1 �� 10000000) > 0
     * @param prm_z �P�ʕ����x�N�g��Z�v�f�i���� 1 �� 10000000) > 0
     * @param out_faceZ Z����]�l�i ��]�l0�́A�����x�N�g��(1,0,0)�B�����x�N�g��(0,0,1)�������Ĕ����v���B�j�i�P��s_ang�j
     * @param out_faceY_rev ���v����Y����]�l�i��]�l0�́A�����������x�N�g��(1,0,0)�B�����x�N�g��(0,1,0)�������Ď��v���j�i�P��s_ang�j
     */
    void getFaceAngClosely(uint32_t prm_x,
                           uint32_t prm_y,
                           uint32_t prm_z,
                           s_ang& out_faceZ,
                           s_ang& out_faceY_rev);

    /**
     * ������Z����]��Y����]�̒l����A��������P�ʕ����x�N�g���̋ߎ������߂� .
     * �A���A���ʂ̕����x�N�g���̊e�v�f(X,Y,Z)�����̒l�ɂȂ�悤�Ȉ��������󂯕t���Ȃ��B<BR>
     * �߂�l��uint32_t�ŕ��������̂��߁Aint�Ɖ��Z���鎞�͋C������<BR>
     * @param prm_faceZ Z����]�l�i ��]�l0�́A�����x�N�g��(1,0,0)�B�����x�N�g��(0,0,1)�������Ĕ����v���B�j�i�P��s_ang�j
     * @param prm_faceY_rev ���v����Y����]�l�i��]�l0�́A�����������x�N�g��(1,0,0)�B�����x�N�g��(0,1,0)�������Ď��v���j�i�P��s_ang�j
     * @param out_x �P�ʕ����x�N�g��X�v�f�i���� 1 �� 10000000) > 0
     * @param out_y �P�ʕ����x�N�g��Y�v�f�i���� 1 �� 10000000) > 0
     * @param out_z �P�ʕ����x�N�g��Z�v�f�i���� 1 �� 10000000) > 0
     */
    inline void getVectorClosely(s_ang prm_faceZ,
                                 s_ang prm_faceY_rev,
                                 uint32_t& out_x,
                                 uint32_t& out_y,
                                 uint32_t& out_z ) {
        SrVec* pV = &(_sr_vec[prm_faceZ][prm_faceY_rev]);
        out_x = pV->x;
        out_y = pV->y;
        out_z = pV->z;
    }

    virtual ~SphereRadiusVectors();
};

}
#endif /*GGAF_DX_SPHERERADIUSVECTORS_H_*/

