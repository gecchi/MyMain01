#ifndef GGAFLIB_STGUTIL_H_
#define GGAFLIB_STGUTIL_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

#include "jp/ggaf/lib/util/ColliAAB.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

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
class StgUtil: public GgafDxCore::GgafDxUtil {
public:
    struct Pos {
        coord X;
        coord Y;
        coord Z;
    };

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAB* pAAB01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliAAB* pAAB02 ) {
        //��AAB �� AAB��
        //������v���Ȃ��m�����������ȏ���(X>Z>Y)�ɔ���
        if (pActor01->_x + pAAB01->_x2 >= pActor02->_x + pAAB02->_x1) {
            if (pActor01->_x + pAAB01->_x1 <= pActor02->_x + pAAB02->_x2) {
                if (pActor01->_z + pAAB01->_z2 >= pActor02->_z + pAAB02->_z1) {
                    if (pActor01->_z + pAAB01->_z1 <= pActor02->_z + pAAB02->_z2) {
                        if (pActor01->_y + pAAB01->_y2 >= pActor02->_y + pAAB02->_y1) {
                            if (pActor01->_y + pAAB01->_y1 <= pActor02->_y + pAAB02->_y2) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliSphere* pSphere01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere* pSphere02 ) {
        //���� �� ����
        //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
        //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
        //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
        double d2 = (double)((pActor02->_x+pSphere02->_x) - (pActor01->_x+pSphere01->_x)) * ((pActor02->_x+pSphere02->_x) - (pActor01->_x+pSphere01->_x)) +
                    (double)((pActor02->_y+pSphere02->_y) - (pActor01->_y+pSphere01->_y)) * ((pActor02->_y+pSphere02->_y) - (pActor01->_y+pSphere01->_y)) +
                    (double)((pActor02->_z+pSphere02->_z) - (pActor01->_z+pSphere01->_z)) * ((pActor02->_z+pSphere02->_z) - (pActor01->_z+pSphere01->_z));
        if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
        ) {
            return true;
        } else {
            return false;
        }
    }

    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAB*    pAAB01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere* pSphere02) {
        //��AAB �� ����
        coord o_scx = pActor02->_x + pSphere02->_cx;
        coord o_scy = pActor02->_y + pSphere02->_cy;
        coord o_scz = pActor02->_z + pSphere02->_cz;
        coord bx1 = pActor01->_x + pAAB01->_x1;
        coord bx2 = pActor01->_x + pAAB01->_x2;
        coord by1 = pActor01->_y + pAAB01->_y1;
        coord by2 = pActor01->_y + pAAB01->_y2;
        coord bz1 = pActor01->_z + pAAB01->_z1;
        coord bz2 = pActor01->_z + pAAB01->_z2;
        double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
        if(o_scx < bx1) {
            square_length += (double)(o_scx - bx1) * (o_scx - bx1);
        }
        if(o_scx > bx2) {
            square_length += (double)(o_scx - bx2) * (o_scx - bx2);
        }
        if(o_scy < by1) {
            square_length += (double)(o_scy - by1) * (o_scy - by1);
        }
        if(o_scy > by2) {
            square_length += (double)(o_scy - by2) * (o_scy - by2);
        }
        if(o_scz < bz1) {
            square_length += (double)(o_scz - bz1) * (o_scz - bz1);
        }
        if(o_scz > bz2) {
            square_length += (double)(o_scz - bz2) * (o_scz - bz2);
        }
        //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
        if (square_length <= pSphere02->_rr) {
            return true;
        } else {
            return false;
        }
    }


    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliAAB*     pAAB02     ) {
        //���v���Y�� �� AAB��
        int aX1 = pActor01->_x + pAAPrism01->_x1;
        int aY1 = pActor01->_y + pAAPrism01->_y1;
        int aZ1 = pActor01->_z + pAAPrism01->_z1;
        int aX2 = pActor01->_x + pAAPrism01->_x2;
        int aY2 = pActor01->_y + pAAPrism01->_y2;
        int aZ2 = pActor01->_z + pAAPrism01->_z2;

        int bX1 = pActor02->_x + pAAB02->_x1;
        int bY1 = pActor02->_y + pAAB02->_y1;
        int bZ1 = pActor02->_z + pAAB02->_z1;
        int bX2 = pActor02->_x + pAAB02->_x2;
        int bY2 = pActor02->_y + pAAB02->_y2;
        int bZ2 = pActor02->_z + pAAB02->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

                if (pos & POS_PRISM_pp) {
                    //            �� y+
                    //
                    //        ����������
                    //        ���_������
                    // x- ��  ���@�_�焠  �� x+
                    //      �������@�_��
                    //      ������������
                    //      ������
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX2, bY2)�A�Ƃ̈ʒu�֌W���l����
                    //y > ax + b �ł���΃q�b�g
                    if (bY2 > a * bX2 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� y+
                    //
                    //        ����������
                    //        �������^��
                    // x- ��  ����^�@��  �� x+
                    //        ���^�@������
                    //        ������������Opp
                    //              ������
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX1, bY2)�A�Ƃ̈ʒu�֌W���l����
                    //y > ax + b �ł���΃q�b�g
                    if (bY2 > a * bX1 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� y+
                    //      ������
                    //      ������������
                    //      �������@�^��
                    // x- ��  ���@�^����  �� x+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX2, bY1)�A�Ƃ̈ʒu�֌W���l����
                    //y < ax + b �ł���΃q�b�g
                    if (bY1 < a * bX2 +  b) {
                        return true;
                    }

                } else { // �̂���� POS_PRISM_nn �݂̂ł���
                    //            �� y+
                    //              ������
                    //        ������������Opp
                    //        ���_�@������
                    // x- ��  �����_�@��  �� x+
                    //        ������_��
                    //        ����������
                    //
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX1, bY1)�A�Ƃ̈ʒu�֌W���l����
                    //y < ax + b �ł���΃q�b�g
                    if (bY1 < a * bX1 +  b) {
                        return true;
                    }


                }
            } else if (pos & POS_PRISM_YZ) {//YZ���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = z - ay
                int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
                if (pos & POS_PRISM_pp) {
                    //            �� z+
                    //
                    //        ����������
                    //        ���_������
                    // y- ��  ���@�_�焠  �� y+
                    //      �������@�_��
                    //      ������������
                    //      ������
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY2, bZ2)�A�Ƃ̈ʒu�֌W���l����
                    //z > ay + b �ł���΃q�b�g
                    if (bZ2 > a * bY2 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� z+
                    //
                    //        ����������
                    //        �������^��
                    // y- ��  ����^�@��  �� y+
                    //        ���^�@������
                    //        ������������Opp
                    //              ������
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY1, bZ2)�A�Ƃ̈ʒu�֌W���l����
                    //z > ay + b �ł���΃q�b�g
                    if (bZ2 > a * bY1 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� z+
                    //      ������
                    //      ������������
                    //      �������@�^��
                    // y- ��  ���@�^����  �� y+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY2, bZ1)�A�Ƃ̈ʒu�֌W���l����
                    //z < ay + b �ł���΃q�b�g
                    if (bZ1 < a * bY2 +  b) {
                        return true;
                    }

                } else { //�̂���� POS_PRISM_nn �݂̂ł���
                    //            �� z+
                    //              ������
                    //        ������������Opp
                    //        ���_�@������
                    // y- ��  �����_�@��  �� y+
                    //        ������_��
                    //        ����������
                    //
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY1, bZ1)�A�Ƃ̈ʒu�֌W���l����
                    //z < ay + b �ł���΃q�b�g
                    if (bZ1 < a * bY1 +  b) {
                        return true;
                    }
                }

            } else if (pos & POS_PRISM_ZX) {
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = x - az
                int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
                if (pos & POS_PRISM_pp) {
                    //            �� x+
                    //
                    //        ����������
                    //        ���_������
                    // z- ��  ���@�_�焠  �� z+
                    //      �������@�_��
                    //      ������������
                    //      ������
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ2, bX2)�A�Ƃ̈ʒu�֌W���l����
                    //x > az + b �ł���΃q�b�g
                    if (bX2 > a * bZ2 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� x+
                    //
                    //        ����������
                    //        �������^��
                    // z- ��  ����^�@��  �� z+
                    //        ���^�@������
                    //        ������������Opp
                    //              ������
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ1, bX2)�A�Ƃ̈ʒu�֌W���l����
                    //x > az + b �ł���΃q�b�g
                    if (bX2 > a * bZ1 +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� x+
                    //      ������
                    //      ������������
                    //      �������@�^��
                    // z- ��  ���@�^����  �� z+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ2, bX1)�A�Ƃ̈ʒu�֌W���l����
                    //x < az + b �ł���΃q�b�g
                    if (bX1 < a * bZ2 +  b) {
                        return true;
                    }

                } else { //�c��� POS_PRISM_nn �݂̂ł���
                    //            �� x+
                    //              ������
                    //        ������������Opp
                    //        ���_�@������
                    // z- ��  �����_�@��  �� z+
                    //        ������_��
                    //        ����������
                    //
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ1, bX1)�A�Ƃ̈ʒu�֌W���l����
                    //x < az + b �ł���΃q�b�g
                    if (bX1 < a * bZ1 +  b) {
                        return true;
                    }
                }
            }
        }
        return false;
    }



    static inline bool isHit(GgafDxCore::GgafDxGeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             GgafDxCore::GgafDxGeometricActor* pActor02, ColliSphere*  pSphere02  ) {
        //���v���Y�� �� ����
        //MEMO:�����ȓ����蔻��v�Z�͍s���Ă��܂���B
        int aX1 = pActor01->_x + pAAPrism01->_x1;
        int aY1 = pActor01->_y + pAAPrism01->_y1;
        int aZ1 = pActor01->_z + pAAPrism01->_z1;
        int aX2 = pActor01->_x + pAAPrism01->_x2;
        int aY2 = pActor01->_y + pAAPrism01->_y2;
        int aZ2 = pActor01->_z + pAAPrism01->_z2;

        //AAB �� ���ł܂����肷��
        if (isHit(pActor01, (ColliAAB*)pAAPrism01,
                  pActor02, pSphere02             ) ) {
            //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

                int oppX, oppY;
                int bZc = pActor02->_z + pSphere02->_cz; //���̒��SZ���W
                if (aZ1 < bZc && bZc < aZ2) {
                    //���̒��SZ���W���v���Y����Z���͈͓��Ȃ�΁A�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
                    //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else if (bZc >= aZ2) {
                    //���̒��SZ���W���v���Y����Z���͈͊O�̏ꍇ
                    //����鋗���ɉ����āA�����̔��a(pSphere02->_r)�����������č������v�Z
                    //���������銄���� ROOT_1_MINUS_XX (1/4�~�̉��̃e�[�u���z��j���g�p�B
                    //                 |
                    //                 �_
                    //        ���������� `��
                    // z- ��  ��      ��  �� z+
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
                } else { //if (aZ1 >= bZc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
                }

                if (pos & POS_PRISM_pp) {
                    //            �� y+
                    //
                    //        ����������
                    //        ���_������
                    // x- ��  ���@�_�焠  �� x+
                    //       ,�����@�_��
                    //      ������������
                    //       `��'
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX2, bY2)�A�Ƃ̈ʒu�֌W���l����
                    //y > ax + b �ł���΃q�b�g
                    if (oppY > a * oppX +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� y+
                    //
                    //        ����������
                    //        �������^��
                    // x- ��  ����^�@��  �� x+
                    //        ���^�@�����A
                    //        ������������Opp
                    //               `��'
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX1, bY2)�A�Ƃ̈ʒu�֌W���l����
                    //y > ax + b �ł���΃q�b�g
                    if (oppY > a * oppX +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� y+
                    //       ,���A
                    //      ������������
                    //       `�����@�^��
                    // x- ��  ���@�^����  �� x+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX2, bY1)�A�Ƃ̈ʒu�֌W���l����
                    //y < ax + b �ł���΃q�b�g
                    if (oppY < a * oppX +  b) {
                        return true;
                    }

                } else { // �̂���� POS_PRISM_nn �݂̂ł���
                    //            �� y+
                    //               ,���A
                    //        ������������Opp
                    //        ���_�@����'
                    // x- ��  �����_�@��  �� x+
                    //        ������_��
                    //        ����������
                    //
                    //            �� y-
                    //
                    //�v���Y�����E�� y = ax + b ��
                    //���̍��W(bX1, bY1)�A�Ƃ̈ʒu�֌W���l����
                    //y < ax + b �ł���΃q�b�g
                    if (oppY < a * oppX +  b) {
                        return true;
                    }


                }
            } else if (pos & POS_PRISM_YZ) {//YZ���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = z - ay
                int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
                int oppY, oppZ;

                int bXc = pActor02->_x + pSphere02->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
                    }
                }
                if (pos & POS_PRISM_pp) {
                    //            �� z+
                    //
                    //        ����������
                    //        ���_������
                    // y- ��  ���@�_�焠  �� y+
                    //       ,�����@�_��
                    //      ������������
                    //       `��'
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY2, bZ2)�A�Ƃ̈ʒu�֌W���l����
                    //z > ay + b �ł���΃q�b�g
                    if (oppZ > a * oppY +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� z+
                    //
                    //        ����������
                    //        �������^��
                    // y- ��  ����^�@��  �� y+
                    //        ���^�@�����A
                    //        ������������Opp
                    //               `��'
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY1, bZ2)�A�Ƃ̈ʒu�֌W���l����
                    //z > ay + b �ł���΃q�b�g
                    if (oppZ > a * oppY +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� z+
                    //       ,���A
                    //      ������������
                    //       `�����@�^��
                    // y- ��  ���@�^����  �� y+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY2, bZ1)�A�Ƃ̈ʒu�֌W���l����
                    //z < ay + b �ł���΃q�b�g
                    if (oppZ < a * oppY +  b) {
                        return true;
                    }

                } else { //�̂���� POS_PRISM_nn �݂̂ł���
                    //            �� z+
                    //               ,���A
                    //        ������������Opp
                    //        ���_�@����'
                    // y- ��  �����_�@��  �� y+
                    //        ������_��
                    //        ����������
                    //
                    //            �� z-
                    //
                    //�v���Y�����E�� z = ay + b ��
                    //���̍��W(bY1, bZ1)�A�Ƃ̈ʒu�֌W���l����
                    //z < ay + b �ł���΃q�b�g
                    if (oppZ < a * oppY +  b) {
                        return true;
                    }
                }

            } else if (pos & POS_PRISM_ZX) {
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = x - az
                int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
                int oppZ,oppX;
                int bYc = pActor02->_y + pSphere02->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_x + pSphere02->_x) + pAAPrism01->_vIH_y * r;
                    }
                }
                if (pos & POS_PRISM_pp) {
                    //            �� x+
                    //
                    //        ����������
                    //        ���_������
                    // z- ��  ���@�_�焠  �� z+
                    //       ,�����@�_��
                    //      ������������
                    //       `��'
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ2, bX2)�A�Ƃ̈ʒu�֌W���l����
                    //x > az + b �ł���΃q�b�g
                    if (oppX > a * oppZ +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_np) {
                    //            �� x+
                    //
                    //        ����������
                    //        �������^��
                    // z- ��  ����^�@��  �� z+
                    //        ���^�@�����A
                    //        ������������Opp
                    //               `��'
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ1, bX2)�A�Ƃ̈ʒu�֌W���l����
                    //x > az + b �ł���΃q�b�g
                    if (oppX > a * oppZ +  b) {
                        return true;
                    }

                } else if (pos & POS_PRISM_pn) {
                    //            �� x+
                    //       ,���A
                    //      ������������
                    //       `�����@�^��
                    // z- ��  ���@�^����  �� z+
                    //        ���^���焠
                    //        ����������
                    //
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ2, bX1)�A�Ƃ̈ʒu�֌W���l����
                    //x < az + b �ł���΃q�b�g
                    if (oppX < a * oppZ +  b) {
                        return true;
                    }

                } else { //�c��� POS_PRISM_nn �݂̂ł���
                    //            �� x+
                    //               ,���A
                    //        ������������Opp
                    //        ���_�@����'
                    // z- ��  �����_�@��  �� z+
                    //        ������_��
                    //        ����������
                    //
                    //            �� x-
                    //
                    //�v���Y�����E�� x = az + b ��
                    //���̍��W(bZ1, bX1)�A�Ƃ̈ʒu�֌W���l����
                    //x < az + b �ł���΃q�b�g
                    if (oppX < a * oppZ +  b) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    /**
     * �e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
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
     * @param prm_attenuated      ���e�ȍ~�̃V���b�g�������x�E�����x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched �e���f�|�W�g������ dispach() ���ꂽ���ɌĂяo���R�[���o�b�N�B
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������� �e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
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
     * @param prm_attenuated      ���e�ȍ~�̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������� �e�𕡐����� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_velo_first      ���e�̃V���b�g�������x�B���e�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �V���b�g���������x
     * @param prm_set_num         ���e�̍��v��
     * @param prm_interval_frames �e�ƒe�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�e��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�ȍ~�̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay001(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int) = nullptr);


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
     * @param prm_ang_clearance_N   N-Way�̊Ԋu�p�x
     * @param prm_velo_first       N-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce             N-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num          ���˂��� N-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames  �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̊e�Z�b�g���̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_way_N,
                                                       angle prm_ang_clearance_N,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rx, _rz > _ry�jN-Way�e�iRz�ω��j�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom                  ���ˌ�
     * @param prm_pDepo_shot             ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r                      ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_N                  N-Way���iRz�ω��j
     * @param prm_ang_clearance_N         N-Way�̊Ԋu�p�x
     * @param prm_velo_first             N-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce                   N-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num                ���˂��� N-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames        �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated             ���e�Z�b�g�ȍ~�̊e�Z�b�g���̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay002(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_way_N,
                                                       angle prm_ang_clearance_N,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * N*M-Way�e�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
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
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̊e�Z�b�g���̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                       coord prm_r,
                                                       int prm_way_N, int prm_way_M,
                                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int, int, int) = nullptr);


    /**
     * ���ˌ��������Ă�������i_rx > _rz > _ry�j�Ɍ������� N*M-Way�e�𕡐��Z�b�g���� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
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
     * @param prm_ang_clearance_N   N-Way�̊Ԋu�p�x
     * @param prm_ang_clearance_M   M-Way�̊Ԋu�p�x
     * @param prm_velo_first       N*M-Way�e���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce             N*M-Way�e�e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num          ���˂��� N*M-Way�e�Z�b�g�̍��v�Z�b�g��
     * @param prm_interval_frames  �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated       ���e�Z�b�g�ȍ~�̊e�Z�b�g���̃V���b�g�������x�̌�����(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay003(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                                       coord prm_r,
                                                       int prm_way_N, int prm_way_M,
                                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int, int, int) = nullptr);



    /**
     * �g�U���˒e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x               ���ˌ�X���W
     * @param prm_y               ���ˌ�Y���W
     * @param prm_z               ���ˌ�Z���W
     * @param prm_rz              ���˕���Rz
     * @param prm_ry              ���˕���Ry
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_radial_way_num  �P�Z�b�g����Way��
     * @param prm_expanse_angle   ���˒e�̏Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         ������WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x������(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched �f�|�W�g��(prm_pDepo_shot)���� dispatch() ����āA
     *                                 �ړ������A�������x�A�����x���ݒ肳�ꂽ��ɃR�[���o�b�N�����֐���ݒ�B
     *                                 �����ɂ͎��̒l�������n�����B
     *                                 void f(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()���ꂽ�e�̃A�N�^�[
     *                                 prm_dispatch_num   ����ڂ� dispatch() �̒e��  (1�`)
     *                                 prm_set_index      ����WAY�e���Z�b�g�ڂł��邩 (0�`)
     *                                 prm_way_index      ��WAY�ڂ̒e�ł��邩         (0�`)
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                                       angle prm_rz, angle prm_ry,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_radial_way_num, angle prm_expanse_angle,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������Ċg�U���˒e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_radial_way_num  �P�Z�b�g����Way��
     * @param prm_expanse_angle   ���˒e�̏Ǝ˒��S�p(0 �` D180ANG�B�����d���̌��̍L����̐����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x
     * @param prm_acce            ���e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         ������WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x�E�����x�̌�����(> 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched �f�|�W�g��(prm_pDepo_shot)���� dispatch() ����āA
     *                                 �ړ������A�������x�A�����x���ݒ肳�ꂽ��ɃR�[���o�b�N�����֐���ݒ�B
     *                                 �����ɂ͎��̒l�������n�����B
     *                                 void f(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index)
     *                                 prm_pActor         dispatch()���ꂽ�e�̃A�N�^�[
     *                                 prm_dispatch_num   ����ڂ� dispatch() �̒e��  (1�`)
     *                                 prm_set_index      ����WAY�e���Z�b�g�ڂł��邩 (0�`)
     *                                 prm_way_index      ��WAY�ڂ̒e�ł��邩         (0�`)
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWay004(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                       GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                       coord prm_r,
                                                       int prm_radial_way_num, angle prm_expanse_angle,
                                                       velo prm_velo_first, acce prm_acce,
                                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                       void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * �����p�g�U���˒e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_x               ���ˌ�X���W
     * @param prm_y               ���ˌ�Y���W
     * @param prm_z               ���ˌ�Z���W
     * @param prm_rz              ���˕���Rz
     * @param prm_ry              ���˕���Ry
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_num         �P�Z�b�g���ː�(1�`999)
     * @param prm_first_expanse_angle   ���˒e�̏����Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_inc_expanse_angle     1�e���ɉ��Z����Ǝˊp����(0 �` D180ANG)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         ������WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x������(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWayGoldenAng(coord prm_x, coord prm_y, coord prm_z,
                                                             angle prm_rz, angle prm_ry,
                                                             GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                             coord prm_r,
                                                             int prm_way_num,
                                                             angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                             velo prm_velo_first, acce prm_acce,
                                                             int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                             void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);

    /**
     * ���ˌ��������Ă�������i_rz > _ry�j�Ɍ������ĉ����p�g�U���˒e�𕡐��Z�b�g�����Ɍ��� .
     * ���˂���V���b�g�ɁA���̍��ڂ��ݒ肳��܂��B<BR>
     * �E�V���b�g�� _x, _y, _z ���W <BR>
     * �E�V���b�g�� GgafDxKuroko �̈ړ������A�ړ����x�A�����x<BR>
     * @param prm_pFrom           ���ˌ�
     * @param prm_pDepo_shot      ���˂���V���b�g�̃f�|�W�g��
     * @param prm_r               ���ˌ��Ɣ��˂���V���b�g�̏����\���ʒu����(���ˌ�����̔��a)�B0���傫���l�̕K�v�L��B
     * @param prm_way_num         �P�Z�b�g���ː�(1�`999)
     * @param prm_first_expanse_angle   ���˒e�̏����Ǝˊp(0 �` D180ANG�B�����d���̌��̍L����p�̂悤�ȃC���[�W�B�������ƒe�̊Ԋu������)
     * @param prm_inc_expanse_angle     1�e���ɉ��Z����Ǝˊp����(0 �` D180ANG)
     * @param prm_velo_first      ���e�Z�b�g�̃V���b�g�������x�B���e�Z�b�g�ȍ~�̏������x�� prm_attenuated ���悶�Ă����B
     * @param prm_acce            �e�Z�b�g�̃V���b�g���������x
     * @param prm_set_num         ������WAY�e�̍��v�Z�b�g��
     * @param prm_interval_frames �e�Z�b�g�ƒe�Z�b�g�̏o���t���[���Ԋu�B(0���傫���ݒ�l�ŁA���ԍ��ł��Ԃ��̂悤�ȉ��o�ɂȂ�B0 �w��͑S�Z�b�g��Ĕ��ˁB�j
     * @param prm_attenuated      ���e�Z�b�g�ȍ~�̃Z�b�g���̃V���b�g�������x������(< 1.0)�A�����͑�����(>1.0)
     * @param pFunc_call_back_dispatched
     * @return �Ō�̔��˒e�̃A�N�^�[(���ĂȂ������ꍇ�� nullptr)
     */
    static GgafDxCore::GgafDxDrawableActor* shotWayGoldenAng(GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                             GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                             coord prm_r,
                                                             int prm_way_num,
                                                             angle prm_first_expanse_angle, angle prm_inc_expanse_angle,
                                                             velo prm_velo_first, acce prm_acce,
                                                             int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                             void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxDrawableActor*, int, int, int) = nullptr);


};

}
#endif /*GGAFLIB_STGUTIL_H_*/
