#ifndef STGUTIL_H_
#define STGUTIL_H_
namespace GgafDx9LibStg {

class StgUtil: public GgafDx9Core::GgafDx9Util {
public:

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAB* pAAB01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliAAB* pAAB02) {
        //��AAB �� AAB��
        //������v���Ȃ��m�����������ȏ���(Z>Y>X)�ɔ���
        if (pActor01->_Z + pAAB01->_z2 >= pActor02->_Z + pAAB02->_z1) {
            if (pActor01->_Z + pAAB01->_z1 <= pActor02->_Z + pAAB02->_z2) {
                if (pActor01->_Y + pAAB01->_y2 >= pActor02->_Y + pAAB02->_y1) {
                    if (pActor01->_Y + pAAB01->_y1 <= pActor02->_Y + pAAB02->_y2) {
                        if (pActor01->_X + pAAB01->_x2 >= pActor02->_X + pAAB02->_x1) {
                            if (pActor01->_X + pAAB01->_x1 <= pActor02->_X + pAAB02->_x2) {
//                                if (pCChecker01->_is_blown || pCChecker02->_is_blown) {
                                    //�q�b�g���Ă���ꍇ�A
                                    //������ѕ�����ݒ�
                                    if (pActor01->_Z + pAAB01->_z1 < pActor02->_Z + pAAB02->_z1) {
                                        pCChecker01->_blown_sgn_vZ -= 1;
                                    }
                                    if (pActor01->_Z + pAAB01->_z2 > pActor02->_Z + pAAB02->_z2) {
                                        pCChecker01->_blown_sgn_vZ += 1;
                                    }
                                    if (pActor01->_Y + pAAB01->_y1 < pActor02->_Y + pAAB02->_y1) {
                                        pCChecker01->_blown_sgn_vY -= 1;
                                    }
                                    if (pActor01->_Y + pAAB01->_y2 > pActor02->_Y + pAAB02->_y2) {
                                        pCChecker01->_blown_sgn_vY += 1;
                                    }
                                    if (pActor01->_X + pAAB01->_x1 < pActor02->_X + pAAB02->_x1) {
                                        pCChecker01->_blown_sgn_vX -= 1;
                                    }
                                    if (pActor01->_X + pAAB01->_x2 > pActor02->_X + pAAB02->_x2) {
                                        pCChecker01->_blown_sgn_vX += 1;
                                    }
//                                }
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliSphere* pSphere01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere* pSphere02) {
        //���� �� ����
        //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
        //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
        //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
        double d2 = (double)((pActor02->_X+pSphere02->_x) - (pActor01->_X+pSphere01->_x)) * ((pActor02->_X+pSphere02->_x) - (pActor01->_X+pSphere01->_x)) +
                    (double)((pActor02->_Y+pSphere02->_y) - (pActor01->_Y+pSphere01->_y)) * ((pActor02->_Y+pSphere02->_y) - (pActor01->_Y+pSphere01->_y)) +
                    (double)((pActor02->_Z+pSphere02->_z) - (pActor01->_Z+pSphere01->_z)) * ((pActor02->_Z+pSphere02->_z) - (pActor01->_Z+pSphere01->_z));
        if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
        ) {
            //�q�b�g
            //todo:�u���΋�������ъȈՌv�Z�A�C�f�B�A�v
            //���ڐ��W�p�`���l���݂��̒��a�̕��ς��Ƃ�A���̕��ϒ��a�ɐ^���ʂ̊������v�Z���|����͈͂������������
            if (pActor01->_Z + pSphere01->_aab_z1 < pActor02->_Z + pSphere02->_aab_z1) {
                pCChecker01->_blown_sgn_vZ -= 1;
            }
            if (pActor01->_Z + pSphere01->_aab_z2 > pActor02->_Z + pSphere02->_aab_z2) {
                pCChecker01->_blown_sgn_vZ += 1;
            }
            if (pActor01->_Y + pSphere01->_aab_y1 < pActor02->_Y + pSphere02->_aab_y1) {
                pCChecker01->_blown_sgn_vY -= 1;
            }
            if (pActor01->_Y + pSphere01->_aab_y2 > pActor02->_Y + pSphere02->_aab_y2) {
                pCChecker01->_blown_sgn_vY += 1;
            }
            if (pActor01->_X + pSphere01->_aab_x1 < pActor02->_X + pSphere02->_aab_x1) {
                pCChecker01->_blown_sgn_vX -= 1;
            }
            if (pActor01->_X + pSphere01->_aab_x2 > pActor02->_X + pSphere02->_aab_x2) {
                pCChecker01->_blown_sgn_vX += 1;
            }
            return true;
        } else {
            return false;
        }
    }

    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAB*    pAAB01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere* pSphere02) {
        //��AAB �� ����
        int o_scx = pActor02->_X+pSphere02->_cx;
        int o_scy = pActor02->_Y+pSphere02->_cy;
        int o_scz = pActor02->_Z+pSphere02->_cz;
        int bx1 = pActor01->_X+pAAB01->_x1;
        int bx2 = pActor01->_X+pAAB01->_x2;
        int by1 = pActor01->_Y+pAAB01->_y1;
        int by2 = pActor01->_Y+pAAB01->_y2;
        int bz1 = pActor01->_Z+pAAB01->_z1;
        int bz2 = pActor01->_Z+pAAB01->_z2;
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
            //�q�b�g
            //������������l��
            if (pActor01->_Z + pAAB01->_aab_z1 < pActor02->_Z + pSphere02->_aab_z1) {
                pCChecker01->_blown_sgn_vZ -= 1;
            }
            if (pActor01->_Z + pAAB01->_aab_z2 > pActor02->_Z + pSphere02->_aab_z2) {
                pCChecker01->_blown_sgn_vZ += 1;
            }
            if (pActor01->_Y + pAAB01->_aab_y1 < pActor02->_Y + pSphere02->_aab_y1) {
                pCChecker01->_blown_sgn_vY -= 1;
            }
            if (pActor01->_Y + pAAB01->_aab_y2 > pActor02->_Y + pSphere02->_aab_y2) {
                pCChecker01->_blown_sgn_vY += 1;
            }
            if (pActor01->_X + pAAB01->_aab_x1 < pActor02->_X + pSphere02->_aab_x1) {
                pCChecker01->_blown_sgn_vX -= 1;
            }
            if (pActor01->_X + pAAB01->_aab_x2 > pActor02->_X + pSphere02->_aab_x2) {
                pCChecker01->_blown_sgn_vX += 1;
            }
            return true;
        } else {
            return false;
        }
    }


    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliAAB*     pAAB02) {
        //���v���Y�� �� AAB��
        int aX1 = pActor01->_X + pAAPrism01->_x1;
        int aY1 = pActor01->_Y + pAAPrism01->_y1;
        int aZ1 = pActor01->_Z + pAAPrism01->_z1;
        int aX2 = pActor01->_X + pAAPrism01->_x2;
        int aY2 = pActor01->_Y + pAAPrism01->_y2;
        int aZ2 = pActor01->_Z + pAAPrism01->_z2;

        int bX1 = pActor02->_X + pAAB02->_x1;
        int bY1 = pActor02->_Y + pAAB02->_y1;
        int bZ1 = pActor02->_Z + pAAB02->_z1;
        int bX2 = pActor02->_X + pAAB02->_x2;
        int bY2 = pActor02->_Y + pAAB02->_y2;
        int bZ2 = pActor02->_Z + pAAB02->_z2;

        if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
            //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor01->_Y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_X+pAAPrism01->_cx)) + pAAPrism01->_b;

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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vX += 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vY += 1;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vY -= 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vY -= 1;
                        return true;
                    }


                }
            } else if (pos & POS_PRISM_YZ) {//YZ���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = z - ay
                int b = ((pActor01->_Z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_Y+pAAPrism01->_cy)) + pAAPrism01->_b;
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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vY -= 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vY += 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
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
                        pCChecker01->_blown_sgn_vY -= 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
                        return true;
                    }
                }

            } else if (pos & POS_PRISM_ZX) {
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = x - az
                int b = ((pActor01->_X+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_Z+pAAPrism01->_cz)) + pAAPrism01->_b;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vX += 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vZ += 1;
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
                        pCChecker01->_blown_sgn_vX -= 1;
                        pCChecker01->_blown_sgn_vZ -= 1;
                        return true;
                    }
                }
            }
        }
        return false;
    }



    static inline bool isHit(CollisionChecker* pCChecker01, GgafDx9Core::GgafDx9GeometricActor* pActor01, ColliAAPrism* pAAPrism01,
                             CollisionChecker* pCChecker02, GgafDx9Core::GgafDx9GeometricActor* pActor02, ColliSphere*  pSphere02) {
        //���v���Y�� �� ����
        int aX1 = pActor01->_X + pAAPrism01->_x1;
        int aY1 = pActor01->_Y + pAAPrism01->_y1;
        int aZ1 = pActor01->_Z + pAAPrism01->_z1;
        int aX2 = pActor01->_X + pAAPrism01->_x2;
        int aY2 = pActor01->_Y + pAAPrism01->_y2;
        int aZ2 = pActor01->_Z + pAAPrism01->_z2;

        //AAB �� ���ł܂����肷��
        if (isHit(pCChecker01   , pActor01   , (ColliAAB*)pAAPrism01,
                  pCChecker02, pActor02, pSphere02)          ) {
            //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���
            int pos = pAAPrism01->_pos_prism;
            double a = pAAPrism01->_a;
            if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
                //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
                double b = ((pActor01->_Y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_X+pAAPrism01->_cx)) + pAAPrism01->_b;

                int oppX, oppY;
                int bZc = pActor02->_Z + pSphere02->_cz; //���̒��SZ���W
                if (aZ1 < bZc && bZc < aZ2) {
                    //���̒��SZ���W���v���Y����Z���͈͓��Ȃ�΁A�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
                    //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
                    oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bZc >= aZ2) {
                        //���̒��SZ���W���v���Y����Z���͈͊O�̏ꍇ
                        //����鋗���ɉ����āA�����̔��a(pSphere02->_r)�����������č������v�Z
                        //���������銄���� ROOT_1_MINUS_XX (1/4�~�̉��̃e�[�u���z��j���g�p�B
                        //                 |
                        //                 �_
                        //        ���������� `��
                        // z- ��  ��      ��  �� z+
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
                    } else if (aZ1 >= bZc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_x * r;
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_Z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_Y+pAAPrism01->_cy)) + pAAPrism01->_b;
                int oppY, oppZ;

                int bXc = pActor02->_X + pSphere02->_cx;
                if (aX1 < bXc && bXc < aX2) {
                    oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bXc >= aX2) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
                    } else if (aX1 >= bXc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                        oppY = (pActor02->_Y + pSphere02->_y) + pAAPrism01->_vIH_x * r;
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_y * r;
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
                int b = ((pActor01->_X+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_Z+pAAPrism01->_cz)) + pAAPrism01->_b;
                int oppZ,oppX;
                int bYc = pActor02->_Y + pSphere02->_cy;
                if (aY1 < bYc && bYc < aY2) {
                    oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * pSphere02->_r;
                    oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * pSphere02->_r;
                } else {
                    if (bYc >= aY2) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * r;
                    } else if (aY1 >= bYc) {
                        int r = pSphere02->_r * GgafDx9Util::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                        oppZ = (pActor02->_Z + pSphere02->_z) + pAAPrism01->_vIH_x * r;
                        oppX = (pActor02->_X + pSphere02->_x) + pAAPrism01->_vIH_y * r;
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
