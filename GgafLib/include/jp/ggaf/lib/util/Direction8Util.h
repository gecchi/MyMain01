#ifndef GGAF_LIB_DIRECTION8UTIL_H_
#define GGAF_LIB_DIRECTION8UTIL_H_
#include "GgafLibCommonHeader.h"

//-1,0,1 ��3����3�i�@ �� �z��v�f�̂��ߐ���10�i���ɕϊ�����}�N��(-4�`+4)
#define DIR8(X,Y) ((3*(X)) + (Y))
#define DIR8_NULL (999)

namespace GgafLib {

/**
 * ���������[�e�B���e�B .
 * @version 1.00
 * @since 2015/09/16
 * @author Masatoshi Tsuge
 */
class Direction8Util {
private:
    struct FaceVec {
        float vx;
        float vy;
    };

    struct FaceSgn {
        int sgn_x;
        int sgn_y;
    };

    /** �ʔԍ�(�����ԍ�)�ƃx�N�g���̃e�[�u�� */
    static const FaceVec _vec[3*3];
    /** �ʔԍ�(�����ԍ�)�Ɗe���̐����̃e�[�u�� */
    static const FaceSgn _sgn[3*3];
    static const angle _angle[3*3];
public:
    static const FaceVec* _dir2vec;

    static const FaceSgn* _dir2sgn;

    static const angle* _dir2angle;

    /** �������p */
    static bool is_init;

    static void init();

    /**
     * ���S����̕����x�N�g�����A���߂̔������ԍ�( DIR8(X,Y) )�ɕϊ� .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @return ���߂̔������ԍ�( DIR8(X,Y) )�Aor DIR8_NULL
     */
    static dir8 cnvVec2DirNo(float prm_vx, float prm_vy);

    /**
     * �����x�N�g�����A���߂̂W�����ɕϊ������ꍇ�́AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvVec2Sgn(float prm_vx, float prm_vy,
                           int& out_sgn_x, int& out_sgn_y);

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy,
                           int& out_sgn_x, int& out_sgn_y) {
        Direction8Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy),
                                         out_sgn_x, out_sgn_y);
    }

    /**
     * �������ԍ�( DIR8(X,Y) )����A�����x�N�g���i���K���ς݁j���擾 .
     * @param prm_dir_no �������ԍ�( DIR8(X,Y) )
     * @param out_vx �����x�N�g��X�v�f
     * @param out_vy �����x�N�g��Y�v�f
     */
    static void cnvDirNo2Vec(dir8 prm_dir_no, float& out_vx, float& out_vy);

    /**
     * �������ԍ�( DIR8(X,Y) )����AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_dir_no �������ԍ�( DIR8(X,Y) )�ADIR_NNN �` DIR_PPP
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvDirNo2Sgn(dir8 prm_dir_no, int& out_sgn_x, int& out_sgn_y);

    /**
     * �������ԍ�( DIR8(X,Y) )����ARzRy�̂Q���A���O���l���擾 .
     * @param prm_dir_no �������ԍ�( DIR8(X,Y) )
     * @param out_rz
     * @param out_ry
     */
    static angle cnvDirNo2RzRy(dir8 prm_dir_no);

    static dir8 cnvAng2DirNo(angle prm_angle);

    static void cnvAng2Sgn(angle prm_angle, int& out_sgn_x, int& out_sgn_y);
};

}
#endif /*GGAF_LIB_DIRECTION26UTIL_H_*/
