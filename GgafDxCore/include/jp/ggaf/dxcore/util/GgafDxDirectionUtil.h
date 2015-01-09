#ifndef GGAFDXCORE_GGAFDXDIRECTIONUTIL_H_
#define GGAFDXCORE_GGAFDXDIRECTIONUTIL_H_
#include "GgafDxCommonHeader.h"

//Ternary numeral -1,0,1 ��3����3�i�@ �� �z��v�f�̂��ߐ���10�i���ɕϊ�����}�N��(-13�`+13)
#define TN(X,Y,Z) (((3*3)*(X)) + (3*(Y)) + (Z))

namespace GgafDxCore {

/**
 * �Ε��������ʑ̂Q�U�������[�e�B���e�B .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class GgafDxDirectionUtil {
private:
    struct FaceVec {
        float vx;
        float vy;
        float vz;
    };

    struct FaceSgn {
        int sgn_x;
        int sgn_y;
        int sgn_z;
    };

    /** �ʔԍ�(�����ԍ�)�ƃx�N�g���̃e�[�u�� */
    static FaceVec _vec[3*3*3];
    /** �ʔԍ�(�����ԍ�)�Ɗe���̐����̃e�[�u�� */
    static FaceSgn _sgn[3*3*3];

public:
    /**
     * ���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�萔 .
     */
    enum {
        FACE_NNN = TN(-1,-1,-1),     //-13
        FACE_NNZ = TN(-1,-1, 0),     //-12
        FACE_NNP = TN(-1,-1, 1),     //-11
        FACE_NZN = TN(-1, 0,-1),     //-10
        FACE_NZZ = TN(-1, 0, 0),     //-9
        FACE_NZP = TN(-1, 0, 1),     //-8
        FACE_NPN = TN(-1, 1,-1),     //-7
        FACE_NPZ = TN(-1, 1, 0),     //-6
        FACE_NPP = TN(-1, 1, 1),     //-5
        FACE_ZNN = TN( 0,-1,-1),     //-4
        FACE_ZNZ = TN( 0,-1, 0),     //-3
        FACE_ZNP = TN( 0,-1, 1),     //-2
        FACE_ZZN = TN( 0, 0,-1),     //-1
        FACE_ZZZ = TN( 0, 0, 0),     // 0   // ���ʂȕ����������Ƃ��������B
        FACE_ZZP = TN( 0, 0, 1),     // 1
        FACE_ZPN = TN( 0, 1,-1),     // 2
        FACE_ZPZ = TN( 0, 1, 0),     // 3
        FACE_ZPP = TN( 0, 1, 1),     // 4
        FACE_PNN = TN( 1,-1,-1),     // 5
        FACE_PNZ = TN( 1,-1, 0),     // 6
        FACE_PNP = TN( 1,-1, 1),     // 7
        FACE_PZN = TN( 1, 0,-1),     // 8
        FACE_PZZ = TN( 1, 0, 0),     // 9
        FACE_PZP = TN( 1, 0, 1),     // 10
        FACE_PPN = TN( 1, 1,-1),     // 11
        FACE_PPZ = TN( 1, 1, 0),     // 12
        FACE_PPP = TN( 1, 1, 1),     // 13
        FACE_XXX = 666,
    };

    static FaceVec* _face2vec;

    static FaceSgn* _face2sgn;


    /** �������p */
    static bool is_init;

    static void init();

    /**
     * �����x�N�g�����A���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ɕϊ� .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param prm_vz �����x�N�g��Z�v�f
     * @return ���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�AFACE_NNN �` FACE_PPP or FACE_XXX
     */
    static face26 cnvVec2FaceNo(float prm_vx, float prm_vy, float prm_vz);

    /**
     * �����x�N�g�����A���߂̂Q�U�����ɕϊ������ꍇ�́AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param prm_vz �����x�N�g��Z�v�f
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_z Z���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    /**
     * ���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)����A�����x�N�g���i���K���ς݁j���擾 .
     * @param prm_face_no �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�AFACE_NNN �` FACE_PPP
     * @param out_vx �����x�N�g��X�v�f
     * @param out_vy �����x�N�g��Y�v�f
     * @param out_vz �����x�N�g��Z�v�f
     */
    static void cnvFaceNo2Vec(face26 prm_face_no, float& out_vx, float& out_vy, float& out_vz);

    /**
     * ���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)����AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_face_no �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�AFACE_NNN �` FACE_PPP
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_z Z���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvFaceNo2Sgn(face26 prm_face_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

};

}
#endif /*GGAFDXCORE_GGAFDXDIRECTIONUTIL_H_*/
