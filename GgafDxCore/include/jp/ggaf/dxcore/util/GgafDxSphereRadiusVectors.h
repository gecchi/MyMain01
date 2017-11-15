#ifndef GGAFDXCORE_GGAFDXSPHERERADIUSVECTORS_H_
#define GGAFDXCORE_GGAFDXSPHERERADIUSVECTORS_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �P�ʋ��ƁA�P�ʃx�N�g���̍��W�̊֌W��ێ�����N���X�ł��B .
 * �����x�N�g������Z����]�p��Y����]�p�A�t��Z����]�p��Y����]�p��������x�N�g���̑��ݕϊ����\�Ƃ��邽�߂ɐ݌v�B<BR>
 * �A���ێ�����Ă���͈͂͒P�ʋ��́Ax��0 y��0 z��0 �͈̔͂̕����x�N�g�������ł��B�i1/8�����̂݁j<BR>
 * �y�⑫�z<BR>
 * �ێ����Ă���x�N�g���̊e�v(X,Y,Z)�̒P��(uint16_t)�́A����1 �� 10000 �ɑ������鐮���ɂȂ��Ă��܂��B<BR>
 * �p�x�̒P�ʁis_ang�j�́A1�x �� 10 �ɑ������܂��B���p�� 900 �ɂȂ�܂��Bangle�l(1�x��1000)�ƍ��݂��Ȃ��悤�ɒ���<BR>
 */
class GgafDxSphereRadiusVectors : public GgafCore::GgafObject {
public:
    /**
     * �\�[�g�\�����x�N�g���N���X.
     * SR_VECTOR(�����x�N�g��)�ɑ召�̒l�����A��r���\�ɂ��������o�����N���X�B<BR>
     * �召�̒l�̋����́Ay�v�f �� z�v�f �� x�v�f �̏��ł��B<BR>
     */
    class COMPARE_ABLE_SR_VECTOR : public GgafCore::GgafObject {
    public:
        /**
         * COMPARE_ABLE_SR_VECTOR�p�̕����x�N�g���\����.
         * �e�v�f�̒P�ʂ́A1000000�{�̐����ŕێ�����܂��B<BR>
         * ���၄<BR>
         * �P�ʃx�N�g��(0.658301, 0.1132, 0.744) ��<BR>
         * SR_VECTOR�ł́A(658301, 113200, 744000) �ł�<BR>
         */
        struct SR_VECTOR {
            uint32_t x;
            uint32_t z;
            uint32_t y;
        };


        uint64_t num_yzx;
        SR_VECTOR vec;
    public:
        COMPARE_ABLE_SR_VECTOR() : GgafObject() , num_yzx(0) {
        }
        /**
         * �P�ʃx�N�g����ݒ肷��B<BR>
         * @param prm_x �P�ʕ����x�N�g��X�v�f�i����1 �� 1000000)
         * @param prm_y �P�ʕ����x�N�g��Y�v�f�i����1 �� 1000000)
         * @param prm_z �P�ʕ����x�N�g��Z�v�f�i����1 �� 1000000)
         */
        void set(uint32_t prm_x, uint32_t prm_y, uint32_t prm_z) {
            vec.x = prm_x;
            vec.y = prm_y;
            vec.z = prm_z;
            num_yzx = (prm_y * 1000000LL * 1000000LL ) +
            (prm_z * 1000000LL ) +
            (prm_x );

            //_TRACE_(prm_x<<","<<prm_y<<","<<prm_z<<"  num_yzx="<<(num_yzx));
            //1048575LL = &b11111111111111111111 (20bit)
        }
    };

    /** �쐬�ړI�� 1/8�����̃\�[�g�\�����x�N�g���z��(�v�f����900*900) */
    COMPARE_ABLE_SR_VECTOR _sr[(D90SANG + 1) * (D90SANG + 1)];

public:
    GgafDxSphereRadiusVectors();

    /**
     * ������X,Y,Z�����x�N�g������A��������Z����]��Y����]�̋ߎ������߂�B
     * �A���AX,Y,Z �͑S�Đ��łȂ��Ă͂Ȃ�Ȃ�
     * @param prm_x �P�ʕ����x�N�g��X�v�f�i����1 �� 1000000) > 0
     * @param prm_y �P�ʕ����x�N�g��Y�v�f�i����1 �� 1000000) > 0
     * @param prm_z �P�ʕ����x�N�g��Z�v�f�i����1 �� 1000000) > 0
     * @param out_faceZ Z����]�l�i ��]�l0�́A�����x�N�g��(1,0,0)�B�����x�N�g��(0,0,1)�������Ĕ����v���B�j�i�P��s_ang�j
     * @param out_faceY_rev ���v����Y����]�l�i��]�l0�́A�����������x�N�g��(1,0,0)�B�����x�N�g��(0,1,0)�������Ď��v���j�i�P��s_ang�j
     * @param s �v�Z�񐔁i���x�j�B�񐔂������قǐ��m�ɂȂ�B
     */
    void getFaceAngClosely(uint32_t prm_x,
                           uint32_t prm_y,
                           uint32_t prm_z,
                           s_ang& out_faceZ,
                           s_ang& out_faceY_rev,
                           int s = 25);

    /**
     * ������Z����]��Y����]�̒l����A��������P�ʕ����x�N�g���̋ߎ������߂� .
     * �A���A���ʂ̕����x�N�g���̊e�v�f(X,Y,Z)�����̒l�ɂȂ�悤�Ȉ��������󂯕t���Ȃ��B<BR>
     * �߂�l��uint32_t�ŕ��������̂��߁Aint�Ɖ��Z���鎞�͋C������<BR>
     * @param prm_faceY_rev Z����]�l�i ��]�l0�́A�����x�N�g��(1,0,0)�B�����x�N�g��(0,0,1)�������Ĕ����v���B�j�i�P��s_ang�j
     * @param prm_faceZ ���v����Y����]�l�i��]�l0�́A�����������x�N�g��(1,0,0)�B�����x�N�g��(0,1,0)�������Ď��v���j�i�P��s_ang�j
     * @param out_x �P�ʕ����x�N�g��X�v�f�i����1 �� 1000000) > 0
     * @param out_y �P�ʕ����x�N�g��Y�v�f�i����1 �� 1000000) > 0
     * @param out_z �P�ʕ����x�N�g��Z�v�f�i����1 �� 1000000) > 0
     */
    inline void getVectorClosely(s_ang prm_faceY_rev,
                                 s_ang prm_faceZ,
                                 uint32_t& out_x,
                                 uint32_t& out_y,
                                 uint32_t& out_z ) {
        COMPARE_ABLE_SR_VECTOR::SR_VECTOR& V = _sr[(int)(prm_faceZ*(D90SANG+1)+prm_faceY_rev)].vec;
        out_x = V.x;
        out_y = V.y;
        out_z = V.z;
    }


    virtual ~GgafDxSphereRadiusVectors();
};




}
#endif /*GGAFDXCORE_GGAFDXSPHERERADIUSVECTORS_H_*/

