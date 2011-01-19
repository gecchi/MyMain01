#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

//    /**
//     * AAB �� AAB �̃q�b�g�`�F�b�N���s�� .
//     * @param pActor
//     * @param pAAB
//     * @param pOppActor
//     * @param pOppAAB
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);
//
//    /**
//     *  �� �� �� �̃q�b�g�`�F�b�N���s�� .
//     * @param pActor
//     * @param pSphere
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);
//
//    /**
//     * AAB �� �� �̃q�b�g�`�F�b�N���s�� .
//     * @param pActor
//     * @param pAAB
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere);
//
//    /**
//     * �v���Y�� �� AAB �̃q�b�g�`�F�b�N���s�� .
//     * @param pActor
//     * @param pAAPrism
//     * @param pOppActor
//     * @param pOppAAB
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB);
//
//    /**
//     * �v���Y�� �� �� �̃q�b�g�`�F�b�N���s�� .
//     * @param pActor
//     * @param pAAPrism
//     * @param pOppActor
//     * @param pOppSphere
//     * @return
//     */
//    static boolean isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
//                         GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere);



    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB* pAAB,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB) {
        //��AAB �� AAB��
        //������v���Ȃ��m�����������ȏ���(Z>Y>X)�ɔ���
        if (pActor->_Z + pAAB->_z2 >= pOppActor->_Z + pOppAAB->_z1) {
            if (pActor->_Z + pAAB->_z1 <= pOppActor->_Z + pOppAAB->_z2) {
                if (pActor->_Y + pAAB->_y2 >= pOppActor->_Y + pOppAAB->_y1) {
                    if (pActor->_Y + pAAB->_y1 <= pOppActor->_Y + pOppAAB->_y2) {
                        if (pActor->_X + pAAB->_x2 >= pOppActor->_X + pOppAAB->_x1) {
                            if (pActor->_X + pAAB->_x1 <= pOppActor->_X + pOppAAB->_x2) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliSphere* pSphere,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
        //���� �� ����
        //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
        //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
        //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
        if (
            (double)((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) * ((pOppActor->_X+pOppSphere->_x) - (pActor->_X+pSphere->_x)) +
            (double)((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) * ((pOppActor->_Y+pOppSphere->_y) - (pActor->_Y+pSphere->_y)) +
            (double)((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z)) * ((pOppActor->_Z+pOppSphere->_z) - (pActor->_Z+pSphere->_z))
              <=
            (double)(pOppSphere->_r + pSphere->_r) * (pOppSphere->_r + pSphere->_r)
        ) {
            return true;
        } else {
            return false;
        }
    }

    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAB*    pAAB,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere* pOppSphere) {
        //��AAB �� ����
        int o_scx =  pOppActor->_X+pOppSphere->_cx;
        int o_scy =  pOppActor->_Y+pOppSphere->_cy;
        int o_scz =  pOppActor->_Z+pOppSphere->_cz;
        int bx1 = pActor->_X+pAAB->_x1;
        int bx2 = pActor->_X+pAAB->_x2;
        int by1 = pActor->_Y+pAAB->_y1;
        int by2 = pActor->_Y+pAAB->_y2;
        int bz1 = pActor->_Z+pAAB->_z1;
        int bz2 = pActor->_Z+pAAB->_z2;
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
        if (square_length <= (double)pOppSphere->_r * pOppSphere->_r) {
            return true;
        } else {
            return false;
        }
    }


    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliAAB* pOppAAB) {
        //���v���Y�� �� AAB��
        int aX1 = pActor->_X + pAAPrism->_x1;
        int aY1 = pActor->_Y + pAAPrism->_y1;
        int aZ1 = pActor->_Z + pAAPrism->_z1;
        int aX2 = pActor->_X + pAAPrism->_x2;
        int aY2 = pActor->_Y + pAAPrism->_y2;
        int aZ2 = pActor->_Z + pAAPrism->_z2;

        int bX1 = pOppActor->_X + pOppAAB->_x1;
        int bY1 = pOppActor->_Y + pOppAAB->_y1;
        int bZ1 = pOppActor->_Z + pOppAAB->_z1;
        int bX2 = pOppActor->_X + pOppAAB->_x2;
        int bY2 = pOppActor->_Y + pOppAAB->_y2;
        int bZ2 = pOppActor->_Z + pOppAAB->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
            int pos = pAAPrism->_pos_prism;
            double a = pAAPrism->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor->_Y+pAAPrism->_cy) - pAAPrism->_a * (pActor->_X+pAAPrism->_cx)) + pAAPrism->_b;

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
                int b = ((pActor->_Z+pAAPrism->_cz) - pAAPrism->_a * (pActor->_Y+pAAPrism->_cy)) + pAAPrism->_b;
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
                int b = ((pActor->_X+pAAPrism->_cx) - pAAPrism->_a * (pActor->_Z+pAAPrism->_cz)) + pAAPrism->_b;
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



    static inline bool isHit(GgafDx9Core::GgafDx9GeometricActor* pActor   , ColliAAPrism* pAAPrism,
                           GgafDx9Core::GgafDx9GeometricActor* pOppActor, ColliSphere*  pOppSphere) {
        //���v���Y�� �� ����
        int aX1 = pActor->_X + pAAPrism->_x1;
        int aY1 = pActor->_Y + pAAPrism->_y1;
        int aZ1 = pActor->_Z + pAAPrism->_z1;
        int aX2 = pActor->_X + pAAPrism->_x2;
        int aY2 = pActor->_Y + pAAPrism->_y2;
        int aZ2 = pActor->_Z + pAAPrism->_z2;

        //AAB �� ���ł܂����肷��
        if (isHit(pActor, (ColliAAB*)pAAPrism, pOppActor, pOppSphere)) {
            //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���
            int pos = pAAPrism->_pos_prism;
            double a = pAAPrism->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor->_Y+pAAPrism->_cy) - pAAPrism->_a * (pActor->_X+pAAPrism->_cx)) + pAAPrism->_b;

                int oppX, oppY;
                int bZc = pOppActor->_Z + pOppSphere->_cz; //���̒��SZ���W
                if (aZ1 < bZc && bZc < aZ2) {
                    //���̒��SZ���W���v���Y����Z���͈͓��Ȃ�΁A�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
                    //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
                    oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bZc >= aZ2) {
                        //���̒��SZ���W���v���Y����Z���͈͊O�̏ꍇ
                        //����鋗���ɉ����āA�����̔��a(pOppSphere->_r)�����������č������v�Z
                        //���������銄���� ROOT_1_MINUS_XX (1/4�~�̉��̔z��j���g�p�B
                        //                 |
                        //                 �_
                        //        ���������� `��
                        // z- ��  ��      ��  �� z+
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pOppSphere->_r)*1000)];
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * r;
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * r;
                    } else if (aZ1 >= bZc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pOppSphere->_r)*1000)];
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_x * r;
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_y * r;
                    }
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
                int b = ((pActor->_Z+pAAPrism->_cz) - pAAPrism->_a * (pActor->_Y+pAAPrism->_cy)) + pAAPrism->_b;
                int oppY, oppZ;

                int bXc = pOppActor->_X + pOppSphere->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pOppSphere->_r)*1000)];
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * r;
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pOppSphere->_r)*1000)];
                        oppY = (pOppActor->_Y + pOppSphere->_y) + pAAPrism->_vIH_x * r;
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_y * r;
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
                int b = ((pActor->_X+pAAPrism->_cx) - pAAPrism->_a * (pActor->_Z+pAAPrism->_cz)) + pAAPrism->_b;
                int oppZ,oppX;
                int bYc = pOppActor->_Y + pOppSphere->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * pOppSphere->_r;
                    oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * pOppSphere->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pOppSphere->_r)*1000)];
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * r;
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pOppSphere->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pOppSphere->_r)*1000)];
                        oppZ = (pOppActor->_Z + pOppSphere->_z) + pAAPrism->_vIH_x * r;
                        oppX = (pOppActor->_X + pOppSphere->_x) + pAAPrism->_vIH_y * r;
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
     * Rz�ω��ɂ�� nWay�e������ .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way Way��
     * @param prm_angClearance Way�̊Ԋu
     * @param prm_velo �������x
     * @param prm_acce �����x
     */
    static void shotWay001(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angClearance,
                           velo prm_velo, acce prm_acce);
    /**
     * Rz�ω��ɂ�� nWay�e�𕡐��Z�b�g�����Ɍ��� .
     * @param prm_pFrom        ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget      �ڕW
     * @param prm_way          Way��
     * @param prm_angClearance Way�̊Ԋu
     * @param prm_velo_top     ���eWAY�̏������x
     * @param prm_acce_top     ���eWAY�̉����x
     * @param prm_num          ����WAY�e�̃Z�b�g��
     * @param prm_attenuated   ����WAY�e�̏������x�����x�̌�����
     */
    static void shotWay001v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angClearance,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);


    /**
     * Ry �͖ڕW�ւ̌����{ANGLE90�ŁARz�ω��ɂ�� nWay���˒e��ł� .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way ����Way��
     * @param prm_angBegin ���ˊJ�n�A���O��
     * @param prm_velo �������x
     * @param prm_acce �����x
     */
    static void shotWay002(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                           GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                           GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                           int prm_way, angle prm_angBegin,
                           velo prm_velo, acce prm_acce);

    /**
     * shotWay002�e�𕡐��Z�b�g�����Ɍ��� .
     * @param prm_pFrom ���ˌ�
     * @param prm_pDispatcher_Shot ���˂���V���b�g�̃f�B�X�p�b�`���[
     * @param prm_pTarget �ڕW
     * @param prm_way ����Way��
     * @param prm_angBegin ���ˊJ�n�A���O��
     * @param prm_velo_top ���e����WAY�̏������x
     * @param prm_acce_top ���e����WAY�̉����x
     * @param prm_num      ������WAY�e�̃Z�b�g��
     * @param prm_attenuated ����WAY�e�̏������x�����x�̌�����
     */
    static void shotWay002v2(GgafDx9Core::GgafDx9GeometricActor* prm_pFrom,
                             GgafCore::GgafActorDispatcher*      prm_pDispatcher_Shot,
                             GgafDx9Core::GgafDx9GeometricActor* prm_pTarget,
                             int prm_way, angle prm_angBegin,
                             velo prm_velo_top, acce prm_acce_top,
                             int prm_num, float prm_attenuated);

};

}
#endif /*STGUTIL_H_*/
