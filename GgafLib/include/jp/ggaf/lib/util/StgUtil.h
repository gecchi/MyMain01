#ifndef GGAF_LIB_STGUTIL_H_
#define GGAF_LIB_STGUTIL_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/util/Util.h"

#include "jp/ggaf/lib/util/ColliAABox.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

#ifdef UTIL
    #undef UTIL
#endif
#define UTIL GgafLib::StgUtil

namespace GgafLib {

/**
 * ���[�e�B���e�B .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StgUtil: public GgafDx::Util {
public:

    static bool _was_StgUtil_inited_flg;

    static void init();

    /**
     * ���a 1000 �� 1/4 �~�̉��e�[�u�� .
     * <pre><code>
     *      ______________
     * y = ��(1000^2-x^2)
     * </code></pre>
     * �� �v�f[x] �ɑ΂��� y
     */
    static float ROOT_1_MINUS_XX[1000];

    static uint32_t BITNUM[];
    /** POS_R_TRIANGLE �� X�v�f���]�e�[�u�� */
    static std::map<pos_t,pos_t> POS_R_TRIANGLE_inv_X;
    /** POS_R_TRIANGLE �� Y�v�f���]�e�[�u�� */
    static std::map<pos_t,pos_t> POS_R_TRIANGLE_inv_Y;

    static GgafDx::Checker* createChecker(GgafDx::GeometricActor* prm_pActor);

    /**
     * AAB �� AAB �����蔻�� .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static inline bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox* const pAABox01,
                               const GgafDx::GeometricActor* const pActor02, const ColliAABox* const pAABox02 ) {
        //��AAB �� AAB��
        //������v���Ȃ��m�����������ȏ���(X>Z>Y)�ɔ���
//        if (pActor01->_x + pAABox01->_x2 >= pActor02->_x + pAABox02->_x1) {
//            if (pActor01->_x + pAABox01->_x1 <= pActor02->_x + pAABox02->_x2) {
//                if (pActor01->_z + pAABox01->_z2 >= pActor02->_z + pAABox02->_z1) {
//                    if (pActor01->_z + pAABox01->_z1 <= pActor02->_z + pAABox02->_z2) {
//                        if (pActor01->_y + pAABox01->_y2 >= pActor02->_y + pAABox02->_y1) {
//                            if (pActor01->_y + pAABox01->_y1 <= pActor02->_y + pAABox02->_y2) {
//                                return true;
//                            }
//                        }
//                    }
//                }
//            }
//        }

//        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
//        if (ABS(pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx)) < max_dx) ) {
//        }
//    	��ό`�B

        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
        if ((ucoord)( (pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx) + max_dx ) < (ucoord)(2*max_dx)) {
            //�����ӌv�Z��0��菬�����ꍇ unsigned �L���X�g�ɂ�萳�̑傫�Ȑ��ɂȂ�̂ŏ����������Ȃ����𗘗p���AABS�̔������������Ă�B
            coord max_dz = pAABox01->_hdz + pAABox02->_hdz;
            if ((ucoord)( (pActor02->_z + pAABox02->_cz) - (pActor01->_z + pAABox01->_cz) + max_dz ) < (ucoord)(2*max_dz)) {
                coord max_dy = pAABox01->_hdy + pAABox02->_hdy;
                if ((ucoord)( (pActor02->_y + pAABox02->_cy) - (pActor01->_y + pAABox01->_cy) + max_dy ) < (ucoord)(2*max_dy)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * �� �� �� �����蔻�� .
     * @param pActor01
     * @param pSphere01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 );

    /**
     * AAB �� �� �����蔻�� .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02);

    /**
     * AA�v���Y�� �� AAB �����蔻�� .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   );

    /**
     * AA�v���Y�� �� �� �����蔻�� .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  );

    /**
     * AA�s���~�b�h �� AAB �����蔻�� .
     * @param pActor01
     * @param pAAPyramid01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*     const pAABox02     );

    /**
     * AA�s���~�b�h �� �� �����蔻�� .
     * @param pActor01
     * @param pAAPyramid01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*    const pSphere02    );


    /**
     * 2D �����` �� �����` �����蔻�� .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static inline bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox* const pAABox01,
                               const GgafDx::GeometricActor* const pActor02, const ColliAABox* const pAABox02 ) {
        //��AAB �� AAB��
//        //������v���Ȃ��m�����������ȏ���(X>Y)�ɔ���
//        if (pActor01->_x + pAABox01->_x2 >= pActor02->_x + pAABox02->_x1) {
//            if (pActor01->_x + pAABox01->_x1 <= pActor02->_x + pAABox02->_x2) {
//                if (pActor01->_y + pAABox01->_y2 >= pActor02->_y + pAABox02->_y1) {
//                    if (pActor01->_y + pAABox01->_y1 <= pActor02->_y + pAABox02->_y2) {
//                        return true;
//                    }
//                }
//            }
//        }

        coord max_dx = pAABox01->_hdx + pAABox02->_hdx;
        if ((ucoord)( (pActor02->_x + pAABox02->_cx) - (pActor01->_x + pAABox01->_cx) + max_dx ) < (ucoord)(2*max_dx)) {
            coord max_dy = pAABox01->_hdy + pAABox02->_hdy;
            if ((ucoord)( (pActor02->_y + pAABox02->_cy) - (pActor01->_y + pAABox01->_cy) + max_dy ) < (ucoord)(2*max_dy)) {
                return true;
            }
        }

        return false;
    }

    /**
     * 2D �~ �� �~ �����蔻�� .
     * @param pActor01
     * @param pSphere01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 );

    /**
     * 2D �����` �� �~ �����蔻�� .
     * @param pActor01
     * @param pAABox01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02);

    /**
     * 2D ���p�O�p�` �� �����` �����蔻�� .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAABox02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   );

    /**
     * 2D ���p�O�p�` �� �~ �����蔻�� .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pSphere02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  );
    /**
     * 2D ���p�O�p�` �� �~ ���p�O�p�` .
     * @param pActor01
     * @param pAAPrism01
     * @param pActor02
     * @param pAAPrism02
     * @return
     */
    static bool isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                        const GgafDx::GeometricActor* const pActor02, const ColliAAPrism* const pAAPrism02  );

    /**
     * �P���e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x               ���ˌ�X���W
     * @param prm_y               ���ˌ�Y���W
     * @param prm_z               ���ˌ�Z���W
     * @param prm_rz              ���˕���Rz
     * @param prm_ry              ���˕���Ry
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_velo_first      ���e�̃V���b�g�������x
     * @param prm_acce            ���e�̃V���b�g���������x
     * @param prm_set_num         ���e�̍��v��
     * @param prm_interval_frames �e�ƒe�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�e��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched �e���f�|�W�g������ dispach() ���ꂽ���ɌĂяo���R�[���o�b�N�B
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                                     angle prm_rz, angle prm_ry,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������� �P���e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_from_x          ���ˌ�X���W
     * @param prm_from_y          ���ˌ�Y���W
     * @param prm_from_z          ���ˌ�Z���W
     * @param prm_to_x            �ڕWX���W
     * @param prm_to_y            �ڕWY���W
     * @param prm_to_z            �ڕWZ���W
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_velo_first      ���e�̃V���b�g�������x�B���e�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �V���b�g���������x
     * @param prm_set_num         ���e�̍��v��
     * @param prm_interval_frames �e�ƒe�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�e��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                                     coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������� �P���e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_velo_first      ���e�̃V���b�g�������x�B���e�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �V���b�g���������x
     * @param prm_set_num         ���e�̍��v��
     * @param prm_interval_frames �e�ƒe�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�e��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay001(const GgafDx::GeometricActor* prm_pFrom,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int) = nullptr);


    /**
     * N-Way�e�iRz�ω��j�𕡐��Z�b�g���� .
     * prm_rx, prm_rz, prm_ry = (0,0,0) �ŁAXY���ʏ��Rz�ω��� N-Way�e ������܂��B
     * @param prm_x                ���ˌ�X���W
     * @param prm_y                ���ˌ�Y���W
     * @param prm_z                ���ˌ�Z���W
     * @param prm_rx               N Way�̉�]�p
     * @param prm_rz               ���˕���Rz
     * @param prm_ry               ���˕���Ry
     * @param prm_pDepo_shot       ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r                ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_N            N-Way���iRz�ω��j
     * @param prm_ang_clearance_N  N-Way�̊Ԋu�p�x
     * @param prm_velo_first       N-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce             N-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num          ���˂��� N-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames  �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                                     angle prm_rx, angle prm_rz, angle prm_ry,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     int prm_way_N,
                                                     angle prm_ang_clearance_N,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rx, _rz > _ry�jN-Way�e�iRz�ω��j�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom                  ���ˌ�
     * @param prm_pDepo_shot             ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r                      ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_N                  N-Way���iRz�ω��j
     * @param prm_ang_clearance_N        N-Way�̊Ԋu�p�x
     * @param prm_velo_first             N-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce                   N-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num                ���˂��� N-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames        �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated             ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay002(const GgafDx::GeometricActor* prm_pFrom,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     int prm_way_N,
                                                     angle prm_ang_clearance_N,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * N*M-Way�e�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x                ���ˌ�X���W
     * @param prm_y                ���ˌ�Y���W
     * @param prm_z                ���ˌ�Z���W
     * @param prm_rx               N*M �����`�̉�]�p
     * @param prm_rz               ���˕���Rz
     * @param prm_ry               ���˕���Ry
     * @param prm_pDepo_shot1      ���˂���V���b�g�̃f�|�W�g�����̂P
     * @param prm_paUint32_dotmat1 �V���b�g���̂P���g�p����h�b�g�}�g���b�N�X
     * @param prm_pDepo_shot2      ���˂���V���b�g�̃f�|�W�g�����̂Q
     * @param prm_paUint32_dotmat2 �V���b�g���̂Q���g�p����h�b�g�}�g���b�N�X
     * @param prm_pDepo_shot3      ���˂���V���b�g�̃f�|�W�g�����̂R
     * @param prm_paUint32_dotmat3 �V���b�g���̂R���g�p����h�b�g�}�g���b�N�X
     * @param prm_r                ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_N            N-Way���iRz�ω��j
     * @param prm_way_M            M-Way���iRy�ω��j
     * @param prm_ang_clearance_N   N-Way�̊Ԋu�p�x
     * @param prm_ang_clearance_M   M-Way�̊Ԋu�p�x
     * @param prm_velo_first       N*M-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce             N*M-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num          ���˂��� N*M-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames  �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                                     angle prm_rx, angle prm_rz, angle prm_ry,
                                                     GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                     GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                     GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                     coord prm_r,
                                                     int prm_way_N, int prm_way_M,
                                                     angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int) = nullptr);


    /**
     * ���ˌ��������Ă�������i_rx > _rz > _ry�j�Ɍ������� N*M-Way�e�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom            ���ˌ�
     * @param prm_pDepo_shot1      ���˂���V���b�g�̃f�|�W�g�����̂P
     * @param prm_paUint32_dotmat1 �V���b�g���̂P���g�p����h�b�g�}�g���b�N�X
     * @param prm_pDepo_shot2      ���˂���V���b�g�̃f�|�W�g�����̂Q
     * @param prm_paUint32_dotmat2 �V���b�g���̂Q���g�p����h�b�g�}�g���b�N�X
     * @param prm_pDepo_shot3      ���˂���V���b�g�̃f�|�W�g�����̂R
     * @param prm_paUint32_dotmat3 �V���b�g���̂R���g�p����h�b�g�}�g���b�N�X
     * @param prm_r                ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_N            N-Way���iRz�ω��j
     * @param prm_way_M            M-Way���iRy�ω��j
     * @param prm_ang_clearance_N  N-Way�̊Ԋu�p�x
     * @param prm_ang_clearance_M  M-Way�̊Ԋu�p�x
     * @param prm_velo_first       N*M-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce             N*M-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num          ���˂��� N*M-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames  �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay003(const GgafDx::GeometricActor* prm_pFrom,
                                                     GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                     GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                     GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                     coord prm_r,
                                                     int prm_way_N, int prm_way_M,
                                                     angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int) = nullptr);

    /**
     * �g�U���ˏ�e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x               ���ˌ�X���W
     * @param prm_y               ���ˌ�Y���W
     * @param prm_z               ���ˌ�Z���W
     * @param prm_rz              ���˕���Rz
     * @param prm_ry              ���˕���Ry
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_radial_way_num  �P�Z�b�g���ˏ�Way��
     * @param prm_expanse_angle   ���˕����ւ̕��ˏ�e�̏Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         �����ˏ�WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched �f�|�W�g��(prm_pDepo_shot)���� dispatch() ����āA
     *                                 �ړ������A�������x�A�����x���ݒ肳�ꂽ��ɃR�[���o�b�N�����֐���ݒ�B
     *                                 �����ɂ͎��̒l�������n�����B
     *                                 void f(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()���ꂽ�e�̃A�N�^�[
     *                                 prm_dispatch_num   ����ڂ� dispatch() �̒e��  (1�`)
     *                                 prm_set_index      ���ˏ�WAY�e���Z�b�g�ڂł��邩 (0�`)
     *                                 prm_way_index      ��WAY�ڂ̒e�ł��邩         (0�`)
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                                     angle prm_rz, angle prm_ry,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     int prm_radial_way_num, angle prm_expanse_angle,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������Ċg�U���ˏ�e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDx::Rikisha �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_radial_way_num  �P�Z�b�g���ˏ�Way��
     * @param prm_expanse_angle   ���˕����ւ̕��ˏ�e�̏Ǝ˒��S�p(0 �` D180ANG�B�����d���̌��̍L����̐����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x
     * @param prm_acce            ���e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         �����ˏ�WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�֏旦�B���x����(< 1.0)�����͑��x����(>1.0)�B1.0�͑S�Z�b�g���x�������B
     * @param pFunc_call_back_dispatched �f�|�W�g��(prm_pDepo_shot)���� dispatch() ����āA
     *                                 �ړ������A�������x�A�����x���ݒ肳�ꂽ��ɃR�[���o�b�N�����֐���ݒ�B
     *                                 �����ɂ͎��̒l�������n�����B
     *                                 void f(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()���ꂽ�e�̃A�N�^�[
     *                                 prm_dispatch_num   ����ڂ� dispatch() �̒e��  (1�`)
     *                                 prm_set_index      ���ˏ�WAY�e���Z�b�g�ڂł��邩 (0�`)
     *                                 prm_way_index      ��WAY�ڂ̒e�ł��邩         (0�`)
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDx::FigureActor* shotWay004(const GgafDx::GeometricActor* prm_pFrom,
                                                     GgafCore::ActorDepository* prm_pDepo_shot,
                                                     coord prm_r,
                                                     int prm_radial_way_num, angle prm_expanse_angle,
                                                     velo prm_velo_first, acce prm_acce,
                                                     int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                     void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int) = nullptr);


};

}
#endif /*GGAF_LIB_STGUTIL_H_*/



//�s���~�b�h�Ƌ�
//  ���� a*x + b*y + c*z + d = 0
//  �_D(x0,y0,z0)
//  �_���畽�ʂɉ��낵�����̍�����_H(x,y,z) �Ƃ����
//
//  �x�N�g�� HD=(x0-x ,y0-y, z0-z) = t(a,b,c)  (t�͎���)  �E�E�E�@
//
//  �@���
//  x0 - x = t*a
//  y0 - y = t*b
//  z0 - z = t*c
//  �Ȃ̂�
//  x = x0 - t*a
//  y = y0 - t*b
//  z = z0 - t*c
//
//  �𕽖ʂ̎��֑��
//  a*(x0-t*a) + b*(y0-t*b) + c*(z0-t*c) + d = 0
//
//  �����t�ɂ��ĉ�����
//  t = (a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2)  �E�E�E�A
//
//  �����
//  x =  x0 - t*a
//    =  x0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*a
//
//  y = y0 - t*b
//    = y0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*b
//
//  z = z0 - t*c
//    = z0 - ((a*x0+b*y0+c*z0+d)/(a^2+b^2+c^2))*c
//
//  �܂��AHD�̋�����
//  |HD|= |t(a,b,c)| = |t|*|(a,b,c)| = abs(t)*sqrt(a^2+b^2+c^2)  �E�E�E�B
//
//  �A��t���B�֑��
//
//  |HD| = abs((c*z0+b*y0+a*x0+d)/(c^2+b^2+a^2))*sqrt(a^2+b^2+c^2)
//
//  |HD| = abs(a*x0+b*y0+c*z0+d) / sqrt(a^2+b^2+c^2)






//// ����̓_(a,b,c)��ʂ�A�����x�N�g����(p,q,r)�̒����́B
//(x,y,z) = (a,b,c) + t(p,q,r)  (t�͔}��ϐ�)
//
//x = a + t*p �E�E�E �@
//y = b + t*q �E�E�E �A
//z = c + t*r �E�E�E �B
//
//t = (x-a) /p = (y-b)/q = (z-c)/r
//
//
//�_D(x0,y0,z0)
//�_���璼���ɉ��낵�����̍�����_H(x,y,z) �Ƃ����
//�x�N�g�� HD = (x0-x,y0-y, z0-z)
//    = (x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))  �E�E�E�C
//
//���ꂪ�A(p,q,r) �ƒ�������̂ŁA����=0
//(x0-(a+t*p), y0-(b+t*q), z0-(c+t*r))�E(p,q,r) = 0
//p*(x0-(a+t*p)) + q*(y0-(b+t*q)) + r*(z0-(c+t*r)) = 0
//
//t�ɂ��ĉ�����
//
//t=(r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2)
//
//�C��t �ɑ�����A���������� HD ��
//HD = ( x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p),
//y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q),
//z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r)    )
//
//|HD| = sqrt( (x0-(a+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*p))^2 +
//     (y0-(b+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*q))^2 +
//     (z0-(c+( (r*z0+q*y0+p*x0-c*r-b*q-a*p)/(r^2+q^2+p^2) )*r))^2   )
//
//|HD| = sqrt((q^2+p^2)*z0^2+(-2*q*r*y0-2*p*r*x0+(2*b*q+2*a*p)*r-2*c*q^2-2*c*p^2)*z0+(r^2+p^2)*y0^2+
//(-2*p*q*x0-2*b*r^2+2*c*q*r+2*a*p*q-2*b*p^2)*y0+(r^2+q^2)*x0^2+(-2*a*r^2+2*c*p*r-2*a*q^2+2*b*p*q)*x0+(b^2+a^2)*r^2+
//(-2*b*c*q-2*a*c*p)*r+(c^2+a^2)*q^2-2*a*b*p*q+(c^2+b^2)*p^2)/(sqrt(r^2+q^2+p^2))





//// �_ A(a,b,c) B(d,e,f) ��ʂ钼����
//AB = (d-a, e-b, f-c)
//(x,y,z) = (a,b,c) + t(d-a, e-b, f-c)  (t�͔}��ϐ�)
//
//x = a + t*(d-a) �E�E�E �@
//y = b + t*(e-b) �E�E�E �A
//z = c + t*(f-c) �E�E�E �B
//
//�_D(x0,y0,z0)
//�_���璼���ɉ��낵�����̍�����_H(x,y,z) �Ƃ����
//�x�N�g�� HD = (x0-x,y0-y, z0-z)
//            = (x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))  �E�E�E�C
//
//
//���ꂪ�AAB=(d-a, e-b, f-c) �ƒ�������̂ŁA����=0
//(x0-(a+t*(d-a)), y0-(b+t*(e-b)), z0-(c+t*(f-c)))�E(d-a, e-b, f-c) = 0
//�Ȃ̂�
//(x0-(a+t*(d-a)))*(d-a) + (y0-(b+t*(e-b)))*(e-b) + (z0-(c+t*(f-c)))*(f-c) = 0
//
//t�ɂ��ĉ�����
//
//t = ((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2)
//
//�C�� t �ɑ�����A���������� HD ��
//HD = ( x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)) ,
//       y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)) ,
//       z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c))   )
//
//|HD| = sqrt( (x0-(a+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(d-a)))^2 +
//             (y0-(b+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(e-b)))^2 +
//             (z0-(c+(((f-c)*z0+(e-b)*y0+(d-a)*x0-c*f-b*e-a*d+c^2+b^2+a^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))*(f-c)))^2    )
//
//=sqrt(((e^2-2*b*e+d^2-2*a*d+b^2+a^2)*z0^2+(((2*b-2*e)*f+2*c*e-2*b*c)*y0+((2*a-2*d)*f+2*c*d-2*a*c)*x0+
//(2*b*e+2*a*d-2*b^2-2*a^2)*f-2*c*e^2+2*b*c*e-2*c*d^2+2*a*c*d)*z0+(f^2-2*c*f+d^2-2*a*d+c^2+a^2)*y0^2+
//(((2*a-2*d)*e+2*b*d-2*a*b)*x0-2*b*f^2+(2*c*e+2*b*c)*f+(2*a*d-2*c^2-2*a^2)*e-2*b*d^2+2*a*b*d)*y0+
//(f^2-2*c*f+e^2-2*b*e+c^2+b^2)*x0^2+(-2*a*f^2+(2*c*d+2*a*c)*f-2*a*e^2+(2*b*d+2*a*b)*e+(-2*c^2-2*b^2)*d)*x0+(b^2+a^2)*
//f^2+(-2*b*c*e-2*a*c*d)*f+(c^2+a^2)*e^2-2*a*b*d*e+(c^2+b^2)*d^2)/(f^2-2*c*f+e^2-2*b*e+d^2-2*a*d+c^2+b^2+a^2))












//�_ A(x1,y2,z1) B(x2,y1,z1) ��ʂ钼���Ɠ_D(o_scx,o_scy,o_scz)�̋���
//
//(x1,y2,z1) (x2,y1,z1)     (o_scx,o_scy,o_scz)
//
//sqrt(((y1^2-2*y2*y1+x2^2-2*x1*x2+y2^2+x1^2)*o_scz^2+(((2*y2-2*y1)*z1+2*z1*y1-2*y2*z1)*o_scy+((2*x1-2*x2)*z1+2*z1*x2-2*x1*z1)*o_scx+
//(2*y2*y1+2*x1*x2-2*y2^2-2*x1^2)*z1-2*z1*y1^2+2*y2*z1*y1-2*z1*x2^2+2*x1*z1*x2)*o_scz+(z1^2-2*z1*z1+x2^2-2*x1*x2+z1^2+x1^2)*o_scy^2+
//(((2*x1-2*x2)*y1+2*y2*x2-2*x1*y2)*o_scx-2*y2*z1^2+(2*z1*y1+2*y2*z1)*z1+(2*x1*x2-2*z1^2-2*x1^2)*y1-2*y2*x2^2+2*x1*y2*x2)*o_scy+
//(z1^2-2*z1*z1+y1^2-2*y2*y1+z1^2+y2^2)*o_scx^2+(-2*x1*z1^2+(2*z1*x2+2*x1*z1)*z1-2*x1*y1^2+(2*y2*x2+2*x1*y2)*y1+(-2*z1^2-2*y2^2)*x2)*o_scx+(y2^2+x1^2)*
//z1^2+(-2*y2*z1*y1-2*x1*z1*x2)*z1+(z1^2+x1^2)*y1^2-2*x1*y2*x2*y1+(z1^2+y2^2)*x2^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2))
//
//
//sqrt(((y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)*z1^2+(-2*o_scz*y2^2+4*o_scz*y1*y2-2*o_scz*y1^2-2*o_scz*x2^2+4*o_scz*x1*x2-2*o_scz*x1^2)*z1+
//(x2^2-2*o_scx*x2+o_scz^2+o_scx^2)*y2^2+
//(((2*o_scx-2*x1)*x2+2*o_scx*x1-2*o_scz^2-2*o_scx^2)*y1-2*o_scy*x2^2+(2*o_scy*x1+2*o_scx*o_scy)*x2-2*o_scx*o_scy*x1)*y2+
//(x1^2-2*o_scx*x1+o_scz^2+o_scx^2)*y1^2+((2*o_scy*x1-2*o_scx*o_scy)*x2-2*o_scy*x1^2+2*o_scx*o_scy*x1)*y1+(o_scz^2+o_scy^2)*x2^2+(-2*o_scz^2-2*o_scy^2)*x1*
//x2+(o_scz^2+o_scy^2)*x1^2)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2))
//
//
//
//
//t=((z1-z1)*z0+(y1-y2)*y0+(x2-x1)*x0-z1*z1-y2*y1-x1*x2+z1^2+y2^2+x1^2)/(z1^2-2*z1*z1+y1^2-2*y2*y1+x2^2-2*x1*x2+z1^2+y2^2+x1^2)
//
//t=(y2^2+(-y1-y0)*y2+y0*y1+(x0-x1)*x2+x1^2-x0*x1)/(y2^2-2*y1*y2+y1^2+x2^2-2*x1*x2+x1^2)
