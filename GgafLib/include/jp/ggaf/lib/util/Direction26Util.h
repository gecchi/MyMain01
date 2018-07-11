#ifndef GGAFLIB_DIRECTION26UTIL_H_
#define GGAFLIB_DIRECTION26UTIL_H_
#include "GgafLibCommonHeader.h"

//-1,0,1 ��3����3�i�@ �� �z��v�f�̂��ߐ���10�i���ɕϊ�����}�N��(-13�`+13)
#define DIR26(X,Y,Z) (((3*3)*(X)) + (3*(Y)) + (Z))
#define DIR26_NULL (999)

namespace GgafLib {

/**
 * �Ε��������ʑ̖̂ʁi�Q�U�����j���[�e�B���e�B .
 * @version 1.00
 * @since 2014/12/11
 * @author Masatoshi Tsuge
 */
class Direction26Util {
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

    struct RzRy {
        angle rz;
        angle ry;
    };

    /** �ʔԍ�(�����ԍ�)�ƃx�N�g���̃e�[�u�� */
    static const FaceVec _vec[3*3*3];
    /** �ʔԍ�(�����ԍ�)�Ɗe���̐����̃e�[�u�� */
    static const FaceSgn _sgn[3*3*3];
    /** �ʔԍ�(�����ԍ�)��RzRy */
    static const RzRy _rzry[3*3*3];
public:
    static const FaceVec* _dir2vec;

    static const FaceSgn* _dir2sgn;

    static const RzRy* _face2rzry;

    /**
     * ���S����̕����x�N�g�����A���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ɕϊ� .
     * @param prm_vx �����x�N�g��X�v�f
     * @param prm_vy �����x�N�g��Y�v�f
     * @param prm_vz �����x�N�g��Z�v�f
     * @return ���߂̎Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ADIR_NNN �` DIR_PPP or FACE_XXX
     */
    static dir26 cnvVec2DirNo(float prm_vx, float prm_vy, float prm_vz);

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

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy, coord prm_vz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
        Direction26Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy), C_DX(prm_vz),
                                          out_sgn_x, out_sgn_y, out_sgn_z);
    }

    static void cnvVec2Sgn(float prm_vx, float prm_vy, float prm_vz,
                           float& out_nvx, float& out_nvy, float& out_nvz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    static void cnvVec2Sgn(coord prm_vx, coord prm_vy, coord prm_vz,
                           float& out_nvx, float& out_nvy, float& out_nvz,
                           int& out_sgn_x, int& out_sgn_y, int& out_sgn_z) {
        Direction26Util::cnvVec2Sgn(C_DX(prm_vx), C_DX(prm_vy), C_DX(prm_vz),
                                          out_nvx, out_nvy, out_nvz,
                                          out_sgn_x, out_sgn_y, out_sgn_z);
    }
    /**
     * �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)����A�����x�N�g���i���K���ς݁j���擾 .
     * @param prm_dir_no �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ADIR_NNN �` DIR_PPP
     * @param out_vx �����x�N�g��X�v�f
     * @param out_vy �����x�N�g��Y�v�f
     * @param out_vz �����x�N�g��Z�v�f
     */
    static void cnvDirNo2Vec(dir26 prm_dir_no, float& out_vx, float& out_vy, float& out_vz);

    /**
     * �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)����AXYZ���e�v�f�̐����̕������擾 .
     * @param prm_dir_no �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ADIR_NNN �` DIR_PPP
     * @param out_sgn_x X���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_y Y���v�f�̐��� (-1 or 0 or 1)
     * @param out_sgn_z Z���v�f�̐��� (-1 or 0 or 1)
     */
    static void cnvDirNo2Sgn(dir26 prm_dir_no, int& out_sgn_x, int& out_sgn_y, int& out_sgn_z);

    /**
     * �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)����ARzRy�̂Q���A���O���l���擾 .
     * @param prm_dir_no �Ε��������ʑ̖̂ʔԍ�(�Q�U�����ԍ�)�ADIR_NNN �` DIR_PPP
     * @param out_rz
     * @param out_ry
     */
    static void cnvDirNo2RzRy(dir26 prm_dir_no, angle& out_rz, angle& out_ry);


};

}
#endif /*GGAFLIB_DIRECTION26UTIL_H_*/
