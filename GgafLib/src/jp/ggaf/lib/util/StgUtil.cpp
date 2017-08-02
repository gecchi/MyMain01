#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

bool StgUtil::_was_StgUtil_inited_flg = false;
float StgUtil::ROOT_1_MINUS_XX[1000];
uint32_t StgUtil::BITNUM[33];

void StgUtil::init() {
    GgafDxUtil::init();
    if (StgUtil::_was_StgUtil_inited_flg) {
        return;
    }

    //ROOT_1_MINUS_XX�̐ݒ�
    for (int i = 0; i < 1000; i++) {
        StgUtil::ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }


    StgUtil::BITNUM[ 0] = 0;
    StgUtil::BITNUM[ 1] = (0x1);            //0b 00000000 00000000 00000000 00000001
    StgUtil::BITNUM[ 2] = (0x2);            //0b 00000000 00000000 00000000 00000010
    StgUtil::BITNUM[ 3] = (0x4);            //0b 00000000 00000000 00000000 00000100
    StgUtil::BITNUM[ 4] = (0x8);            //0b 00000000 00000000 00000000 00001000
    StgUtil::BITNUM[ 5] = (0x10);           //0b 00000000 00000000 00000000 00010000
    StgUtil::BITNUM[ 6] = (0x20);           //0b 00000000 00000000 00000000 00100000
    StgUtil::BITNUM[ 7] = (0x40);           //0b 00000000 00000000 00000000 01000000
    StgUtil::BITNUM[ 8] = (0x80);           //0b 00000000 00000000 00000000 10000000
    StgUtil::BITNUM[ 9] = (0x100);          //0b 00000000 00000000 00000001 00000000
    StgUtil::BITNUM[10] = (0x200);          //0b 00000000 00000000 00000010 00000000
    StgUtil::BITNUM[11] = (0x400);          //0b 00000000 00000000 00000100 00000000
    StgUtil::BITNUM[12] = (0x800);          //0b 00000000 00000000 00001000 00000000
    StgUtil::BITNUM[13] = (0x1000);         //0b 00000000 00000000 00010000 00000000
    StgUtil::BITNUM[14] = (0x2000);         //0b 00000000 00000000 00100000 00000000
    StgUtil::BITNUM[15] = (0x4000);         //0b 00000000 00000000 01000000 00000000
    StgUtil::BITNUM[16] = (0x8000);         //0b 00000000 00000000 10000000 00000000
    StgUtil::BITNUM[17] = (0x10000);        //0b 00000000 00000001 00000000 00000000
    StgUtil::BITNUM[18] = (0x20000);        //0b 00000000 00000010 00000000 00000000
    StgUtil::BITNUM[19] = (0x40000);        //0b 00000000 00000100 00000000 00000000
    StgUtil::BITNUM[20] = (0x80000);        //0b 00000000 00001000 00000000 00000000
    StgUtil::BITNUM[21] = (0x100000);       //0b 00000000 00010000 00000000 00000000
    StgUtil::BITNUM[22] = (0x200000);       //0b 00000000 00100000 00000000 00000000
    StgUtil::BITNUM[23] = (0x400000);       //0b 00000000 01000000 00000000 00000000
    StgUtil::BITNUM[24] = (0x800000);       //0b 00000000 10000000 00000000 00000000
    StgUtil::BITNUM[25] = (0x1000000);      //0b 00000001 00000000 00000000 00000000
    StgUtil::BITNUM[26] = (0x2000000);      //0b 00000010 00000000 00000000 00000000
    StgUtil::BITNUM[27] = (0x4000000);      //0b 00000100 00000000 00000000 00000000
    StgUtil::BITNUM[28] = (0x8000000);      //0b 00001000 00000000 00000000 00000000
    StgUtil::BITNUM[29] = (0x10000000);     //0b 00010000 00000000 00000000 00000000
    StgUtil::BITNUM[30] = (0x20000000);     //0b 00100000 00000000 00000000 00000000
    StgUtil::BITNUM[31] = (0x40000000);     //0b 01000000 00000000 00000000 00000000
    StgUtil::BITNUM[32] = (0x80000000);     //0b 10000000 00000000 00000000 00000000

    StgUtil::_was_StgUtil_inited_flg = true;
}

GgafDxChecker* StgUtil::createChecker(GgafDxGeometricActor* prm_pActor) {
    return PROPERTY::IS_HIT_CHECK_3D  ?  NEW CollisionChecker3D(prm_pActor) : NEW CollisionChecker3D(prm_pActor); //TODO:CollisionChecker2D
}

bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //���� �� ����
    //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
    //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    double d2 = (double)((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) * ((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) +
                (double)((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) * ((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) +
                (double)((pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz)) * ((pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz));
    if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}



bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* pActor01, const ColliAABox*  pAABox01,
                    const GgafDxCore::GgafDxGeometricActor* pActor02, const ColliSphere* pSphere02) {
    //��AAB �� ����
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord bx1 = pActor01->_x + pAABox01->_x1;
    const coord bx2 = pActor01->_x + pAABox01->_x2;
    const coord by1 = pActor01->_y + pAABox01->_y1;
    const coord by2 = pActor01->_y + pAABox01->_y2;
    const coord bz1 = pActor01->_z + pAABox01->_z1;
    const coord bz2 = pActor01->_z + pAABox01->_z2;

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
    //���̔��肪�S�ăn�Y���āAsquare_length == 0 �Ȃ�΁A
    //���̒��S���ABOX���ɂ���Ƃ����Ӗ��ɂȂ�B

    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length <= pSphere02->_rr) {
        return true;
    } else {
        return false;
    }
}


 bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                     const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliAABox*   const pAABox02     ) {
    //���v���Y�� �� AAB��
    const int aX1 = pActor01->_x + pAAPrism01->_x1;
    const int aY1 = pActor01->_y + pAAPrism01->_y1;
    const int aZ1 = pActor01->_z + pAAPrism01->_z1;
    const int aX2 = pActor01->_x + pAAPrism01->_x2;
    const int aY2 = pActor01->_y + pAAPrism01->_y2;
    const int aZ2 = pActor01->_z + pAAPrism01->_z2;

    const int bX1 = pActor02->_x + pAABox02->_x1;
    const int bY1 = pActor02->_y + pAABox02->_y1;
    const int bZ1 = pActor02->_z + pAABox02->_z1;
    const int bX2 = pActor02->_x + pAABox02->_x2;
    const int bY2 = pActor02->_y + pAABox02->_y2;
    const int bZ2 = pActor02->_z + pAABox02->_z2;

    if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
            //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
            const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

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



bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //���v���Y�� �� ����
    //MEMO:�����ȓ����蔻��v�Z�͍s���Ă��܂���B


    //AAB �� ���ł܂����肷��
    if (isHit(pActor01, (ColliAABox*)pAAPrism01,
              pActor02, pSphere02             ) ) {
        //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���
        const int aX1 = pActor01->_x + pAAPrism01->_x1;
        const int aY1 = pActor01->_y + pAAPrism01->_y1;
        const int aZ1 = pActor01->_z + pAAPrism01->_z1;
        const int aX2 = pActor01->_x + pAAPrism01->_x2;
        const int aY2 = pActor01->_y + pAAPrism01->_y2;
        const int aZ2 = pActor01->_z + pAAPrism01->_z2;
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY) { //XY���ʃX���C�X�̃v���Y��
            //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
            const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

            int oppX, oppY;
            const int bZc = pActor02->_z + pSphere02->_cz; //���̒��SZ���W
            if (aZ1 < bZc && bZc < aZ2) {
                //���̒��SZ���W���v���Y����Z���͈͓��Ȃ�΁A�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
                //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else if (bZc >= aZ2) {
                //���̒��SZ���W���v���Y����Z���͈͊O�̏ꍇ
                //����鋗���ɉ����āA�����̔��a(pSphere02->_r)�����������č������v�Z
                //���������銄���� ROOT_1_MINUS_XX (1/4�~�̉��̃e�[�u���z��j���g�p�B
                //                 |
                //                 �_
                //        ���������� `��
                // z- ��  ��      ��  �� z+
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * r;
            } else { //if (aZ1 >= bZc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_x * r;
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_y * r;
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
            const int b = ((pActor01->_z+pAAPrism01->_cz) - pAAPrism01->_a * (pActor01->_y+pAAPrism01->_cy)) + pAAPrism01->_b;
            int oppY, oppZ;

            const int bXc = pActor02->_x + pSphere02->_cx;
            if (aX1 < bXc && bXc < aX2) {
                oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else {
                if (bXc >= aX2) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                    oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * r;
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * r;
                } else if (aX1 >= bXc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                    oppY = (pActor02->_y + pSphere02->_cy) + pAAPrism01->_vIH_x * r;
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_y * r;
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
            const int b = ((pActor01->_x+pAAPrism01->_cx) - pAAPrism01->_a * (pActor01->_z+pAAPrism01->_cz)) + pAAPrism01->_b;
            int oppZ,oppX;
            const int bYc = pActor02->_y + pSphere02->_cy;
            if (aY1 < bYc && bYc < aY2) {
                oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * pSphere02->_r;
                oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * pSphere02->_r;
            } else {
                if (bYc >= aY2) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * r;
                    oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * r;
                } else if (aY1 >= bYc) {
                    int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                    oppZ = (pActor02->_z + pSphere02->_cz) + pAAPrism01->_vIH_x * r;
                    oppX = (pActor02->_x + pSphere02->_cx) + pAAPrism01->_vIH_y * r;
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


bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliAABox*     const pAABox02     ) {
    //�s���~�b�h��BOX
    const int aX1 = pActor01->_x + pAAPyramid01->_x1;
    const int aY1 = pActor01->_y + pAAPyramid01->_y1;
    const int aZ1 = pActor01->_z + pAAPyramid01->_z1;
    const int aX2 = pActor01->_x + pAAPyramid01->_x2;
    const int aY2 = pActor01->_y + pAAPyramid01->_y2;
    const int aZ2 = pActor01->_z + pAAPyramid01->_z2;

    const int bX1 = pActor02->_x + pAABox02->_x1;
    const int bY1 = pActor02->_y + pAABox02->_y1;
    const int bZ1 = pActor02->_z + pAABox02->_z1;
    const int bX2 = pActor02->_x + pAABox02->_x2;
    const int bY2 = pActor02->_y + pAABox02->_y2;
    const int bZ2 = pActor02->_z + pAABox02->_z2;

    if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g

        //�s���~�b�h�Ζʂɑ΂��ăs���~�b�h����BOX�̈���ŁA����BOX�̍ŋߖT�_�����߂�
        //
        const int pos_pyramid = pAAPyramid01->_pos_pyramid;

        int nnx, nny, nnz; //�ŋߖT�_
        if (pos_pyramid & POS_PYRAMID_p__) {
            //bX2�ɋ���������
            if (aX1 <= bX2 && bX2 <= aX2) {
                //bX2 �����ɂ���
                nnx = bX2;
            } else { //if (aX2 < bX2) {
                //bX2 ���O�ɂ���
                nnx = aX2;
            }
        } else {
            //bX1�ɋ���������
            if (aX1 <= bX1 && bX1 <= aX2) {
                //bX1 �����ɂ���
                nnx = bX1;
            } else { // if (aX1 > bX1) {
                //bX1 ���O�ɂ���
                nnx = aX1;
            }
        }

        if (pos_pyramid & POS_PYRAMID__p_) {
            //bY2�ɋ���������
            if (aY1 <= bY2 && bY2 <= aY2) {
                //bY2 �����ɂ���
                nny = bY2;
            } else { //if (aY2 < bY2) {
                //bY2 ���O�ɂ���
                nny = aY2;
            }
        } else {
            //bY1�ɋ���������
            if (aY1 <= bY1 && bY1 <= aY2) {
                //by1 �����ɂ���
                nny = bY1;
            } else { //if (aY1 > bY1) {
                //bx1 ���O�ɂ���
                nny = aY1;
            }
        }

        if (pos_pyramid & POS_PYRAMID___p) {
            //bZ2�ɋ���������
            if (aZ1 <= bZ2 && bZ2 <= aZ2) {
                //bZ2 �����ɂ���
                nnz = bZ2;
            } else if (aZ2 < bZ2) {
                //bZ2 ���O�ɂ���
                nnz = aZ2;
            } else {
                //���肦�Ȃ��H
            }
        } else {
            //bZ1�ɋ���������
            if (aZ1 <= bZ1 && bZ1 <= aZ2) {
                //bz1 �����ɂ���
                nnz = bZ1;
            } else if (aZ1 > bZ1) {
                //bx1 ���O�ɂ���
                nnz = aZ1;
            } else {
                //�q�b�g���ĂȂ��H
            }
        }
        //(nnx,nny,nnz) ���ߖT�_
        float a_xy = pAAPyramid01->_a_xy;
        float b_xy_z1 = pAAPyramid01->_b_xy_z1;
        float b_xy_z2 = pAAPyramid01->_b_xy_z2;
        float b_xy = RCNV(bZ1, bZ2, nnz, b_xy_z1, b_xy_z2);

        //XY�ŃX���C�X�����ꍇ�̐ؕЂ� MAX�ؕЁ`MIN�ؕ� �̊Ԋ����� bZ1�`bZ2 �̕ω������ŋ��߂�
        //XY���ʂɃX���C�X�������p�O�p�`�̓����i�O�p�`�Εӂ̒������������E�̎O�p�`�������̈�j
        //�ɋߖT�_������΃q�b�g

        // y = ax + b
        // y = a_xy * x + b_xy ��
        // X����pActor01_x�AY����pActor01_y���s�ړ�����������
        // y-pActor01_y = a_xy * (x-pActor01_x) + b_xy
        // y = a_xy * (x-pActor01_x) + b_xy + pActor01_y
        //
        // ���̒�����(nnx,nny)�̓_�̈ʒu�͈̔͂𒲂ׂ�

        if (pos_pyramid & POS_PYRAMID__p_) {
            if (nny >= a_xy * (nnx-pActor01->_x) + b_xy + pActor01->_y) {
                return true;
            }
        } else {
            if (nny <= a_xy * (nnx-pActor01->_x) + b_xy + pActor01->_y) {
                return true;
            }
        }
    }
    return false;
}

bool StgUtil::isHit(const GgafDxCore::GgafDxGeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                    const GgafDxCore::GgafDxGeometricActor* const pActor02, const ColliSphere*    const pSphere02  ) {

    //�܂�BOX�Ƌ��œ����蔻����s��
    //��AAB �� ����
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord o_r = pSphere02->_r;
    const coord b_x1 = pActor01->_x + pAAPyramid01->_x1;
    const coord b_x2 = pActor01->_x + pAAPyramid01->_x2;
    const coord b_y1 = pActor01->_y + pAAPyramid01->_y1;
    const coord b_y2 = pActor01->_y + pAAPyramid01->_y2;
    const coord b_z1 = pActor01->_z + pAAPyramid01->_z1;
    const coord b_z2 = pActor01->_z + pAAPyramid01->_z2;

    double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
    int sgn_x_spos, sgn_y_spos, sgn_z_spos;
    if(o_scx < b_x1) {
        square_length += (double)(o_scx - b_x1) * (o_scx - b_x1);
        sgn_x_spos = -1;
    } else if(o_scx > b_x2) {
        square_length += (double)(o_scx - b_x2) * (o_scx - b_x2);
        sgn_x_spos = +1;
    } else {
        sgn_x_spos = 0;
    }

    if(o_scy < b_y1) {
        square_length += (double)(o_scy - b_y1) * (o_scy - b_y1);
        sgn_y_spos = -1;
    } else if(o_scy > b_y2) {
        square_length += (double)(o_scy - b_y2) * (o_scy - b_y2);
        sgn_y_spos = +1;
    } else {
        sgn_y_spos = 0;
    }

    if(o_scz < b_z1) {
        square_length += (double)(o_scz - b_z1) * (o_scz - b_z1);
        sgn_z_spos = -1;
    } else if(o_scz > b_z2) {
        square_length += (double)(o_scz - b_z2) * (o_scz - b_z2);
        sgn_z_spos = +1;
    } else {
        sgn_z_spos = 0;

    }
    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length <= pSphere02->_rr) {
        //OK�A�܂�BOX�Ƌ��Ńq�b�g�A�������N���A
        //����
    } else {
        return false;
    }

    const int pos_pyramid = pAAPyramid01->_pos_pyramid;
    switch (pos_pyramid) {
        case POS_PYRAMID_nnn: {
//                if (sgn_x_spos == -1 && sgn_y_spos == -1) {
//                    return true;
//                }
//                if (sgn_y_spos == -1 && sgn_z_spos == -1) {
//                    return true;
//                }
//                if (sgn_z_spos == -1 && sgn_x_spos == -1) {
//                    return true;
//                }
            if (sgn_x_spos == -1) {
                if (sgn_y_spos == -1 || sgn_z_spos == -1) {
                    return true;
                } else if (sgn_y_spos == -1 && sgn_z_spos == -1) {
                    return true;
                }
            }

//            if (o_r < pAAPyramid01->_d_c2vtx && sgn_x_spos == 1 && sgn_y_spos == 1 && sgn_x_spos == 1) {
//                return false;
//            }
//                //�v�Z���y�ɂ��邽�ߒ��p�O�p���̂R���p�����_�ɕ��s�ړ����čl����
////                const coord b0_x1 = 0;
//                const coord b0_x2 = pAAPyramid01->_dx;
////                const coord b0_y1 = 0;
//                const coord b0_y2 = pAAPyramid01->_dy;
////                const coord b0_z1 = 0;
//                const coord b0_z2 = pAAPyramid01->_dz;
//
//                const coord o0_scx = o_scx - pAAPyramid01->_x1;
//                const coord o0_scy = o_scy - pAAPyramid01->_y1;
//                const coord o0_scz = o_scz - pAAPyramid01->_z1;


            //���S�ƎΖʂ̋��������a��肿��������΃q�b�g
            //���� a*x + b*y + c*z + d = 0
            //�_D(x0,y0,z0)
            //���� �� abs(a*x0+b*y0+c*z0+d) / sqrt(a^2+b^2+c^2)
            double d = ABS(pAAPyramid01->_s_nvx*o_scx + pAAPyramid01->_s_nvy*o_scy + pAAPyramid01->_s_nvz*o_scz + pAAPyramid01->_s_d) / pAAPyramid01->_d_nv;
            if (d <= o_r) {
                return true;
            }


            //���̒��S���L���[�u���ł���
            //Z���X���C�X���p�O�p�`�����ɂ���΃q�b�g
            if (sgn_x_spos == 0 && sgn_y_spos == 0 && sgn_z_spos == 0) {
                float a_xy = pAAPyramid01->_a_xy;
                float b_xy_z1 = pAAPyramid01->_b_xy_z1;
                float b_xy_z2 = pAAPyramid01->_b_xy_z2;
                float b_xy = RCNV(b_z1, b_z2, o_scz, b_xy_z1, b_xy_z2);
                //XY�ŃX���C�X�����ꍇ�̐ؕЂ� MAX�ؕЁ`MIN�ؕ� �̊Ԋ����� bZ1�`bZ2 �̕ω������ŋ��߂�
                //XY���ʂɃX���C�X�������p�O�p�`�̓����i�O�p�`�Εӂ̒������������E�̎O�p�`�������̈�j
                //�ɋߖT�_������΃q�b�g

                if (pos_pyramid & POS_PYRAMID__p_) {
                    if (o_scy >= a_xy * (o_scx-pActor01->_x) + b_xy + pActor01->_y) {
                        return true;
                    }
                } else {
                    if (o_scy <= a_xy * (o_scx-pActor01->_x) + b_xy + pActor01->_y) {
                        return true;
                    }
                }
            }
            break;
        }
        case POS_PYRAMID_nnp: {
            break;
        }
        case POS_PYRAMID_npn: {
            break;
        }
        case POS_PYRAMID_npp: {
            break;
        }
        case POS_PYRAMID_pnn: {
            break;
        }
        case POS_PYRAMID_pnp: {
            break;
        }
        case POS_PYRAMID_ppn: {
            break;
        }
        case POS_PYRAMID_ppp: {
            break;
        }
        default: {
            break;
        }
    }



    return false;
}


GgafDxFigureActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    if (prm_set_num <= 0) {  return nullptr;  }
    float vx, vy, vz;
    GgafDxUtil::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord x = vx * prm_r;
    coord y = vy * prm_r;
    coord z = vz * prm_r;
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
        if (pActor_shot) {
            dispatch_num++;
            pActor_shot->setPosition(prm_x + x,
                                     prm_y + y,
                                     prm_z + z);
            pActor_shot->getKuroko()->setRzRyMvAng(prm_rz, prm_ry);
            pActor_shot->getKuroko()->setMvVelo(now_velo);
            pActor_shot->getKuroko()->setMvAcce(now_acce);
            if (pFunc_call_back_dispatched) {
                pFunc_call_back_dispatched(pActor_shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_shot;
}

GgafDxFigureActor* StgUtil::shotWay001(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxFigureActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int)) {
    angle rz,ry;
    GgafDxUtil::convVectorToRzRy(prm_to_x - prm_from_x,
                                 prm_to_y - prm_from_y,
                                 prm_to_z - prm_from_z,
                                 rz, ry);
    return shotWay001(prm_from_x, prm_from_y, prm_from_z,
                      rz, ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxFigureActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way_N,
                                       angle prm_ang_clearance_N,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    if (prm_way_N <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    for (int i = 0; i < prm_way_N; i++) {
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        ry = D0ANG;
        GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDxCore::GgafDxFigureActor* StgUtil::shotWay002(const GgafDxCore::GgafDxGeometricActor* prm_pFrom,
                                                   GgafCore::GgafActorDepository* prm_pDepo_shot,
                                                   coord prm_r,
                                                   int prm_way_N,
                                                   angle prm_ang_clearance_N,
                                                   velo prm_velo_first, acce prm_acce,
                                                   int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                   void (*pFunc_call_back_dispatched)(GgafDxCore::GgafDxFigureActor*, int, int, int)) {
    return shotWay002(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way_N,
                      prm_ang_clearance_N,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDxFigureActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int, int, int)) {
    if (prm_way_N <= 0 || prm_way_M <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDxUtil::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDxUtil::getWayAngle2D(0, prm_way_M, prm_ang_clearance_M, paAng_way_M);
    GgafDxGeoElem** papaGeo = NEW GgafDxGeoElem*[prm_way_N];
    float vx, vy, vz;
    float tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    uint32_t dot1,dot2,dot3;
    for (int i = 0; i < prm_way_N; i++) {
        dot1 = prm_paUint32_dotmat1 ? prm_paUint32_dotmat1[i] : 0;
        dot2 = prm_paUint32_dotmat2 ? prm_paUint32_dotmat2[i] : 0;
        dot3 = prm_paUint32_dotmat3 ? prm_paUint32_dotmat3[i] : 0;
        paUint32_dotmat[i] = dot1 | dot2 | dot3;
        if (paUint32_dotmat[i] == 0) {
            papaGeo[i] = nullptr;
            continue;
        }
        rz = GgafDxUtil::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDxGeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                ry = GgafDxUtil::simplifyAng(paAng_way_M[j]);
                GgafDxUtil::convRzRyToVector(rz, ry, vx, vy, vz);
                tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
                ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
                tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
                papaGeo[i][j].x = (coord)(tx * prm_r);
                papaGeo[i][j].y = (coord)(ty * prm_r);
                papaGeo[i][j].z = (coord)(tz * prm_r);
                GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                             papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    int depo_no = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            if (paUint32_dotmat[i] == 0) {
                continue;
            }
            for (int j = 0; j < prm_way_M; j++) {
                if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                    if (prm_paUint32_dotmat1 && (prm_paUint32_dotmat1[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot3->dispatch(n*prm_interval_frames+1);
                        depo_no = 3;
                    } else {
                        pActor_shot = nullptr;
                        depo_no = 0;
                    }
                } else {
                    pActor_shot = nullptr;
                    depo_no = 0;
                }
                if (pActor_shot) {
                    dispatch_num++;
                    pActor_shot->setPosition(prm_x + papaGeo[i][j].x,
                                             prm_y + papaGeo[i][j].y,
                                             prm_z + papaGeo[i][j].z);
                    pActor_shot->getKuroko()->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_shot->getKuroko()->setMvVelo(now_velo);
                    pActor_shot->getKuroko()->setMvAcce(now_acce);
                    if (pFunc_call_back_dispatched) {
                        pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, depo_no, i, j);
                    }
                }
            }
        }
        now_velo *= prm_attenuated;
    }

    GGAF_DELETEARR(paAng_way_N);
    GGAF_DELETEARR(paAng_way_M);
    GGAF_DELETEARR(paUint32_dotmat);
    for (int i = 0; i < prm_way_N; i++) {
        if (papaGeo[i]) {
            GGAF_DELETEARR(papaGeo[i]);
        }
    }
    GGAF_DELETEARR(papaGeo);

    return pActor_shot;
}


GgafDxFigureActor* StgUtil::shotWay003(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int, int, int)) {
    return shotWay003(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rx, prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot1, prm_paUint32_dotmat1,
                      prm_pDepo_shot2, prm_paUint32_dotmat2,
                      prm_pDepo_shot3, prm_paUint32_dotmat3,
                      prm_r,
                      prm_way_N, prm_way_M,
                      prm_ang_clearance_N, prm_ang_clearance_M,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}


GgafDxFigureActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_radial_way_num, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    if (prm_radial_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way = NEW angle[prm_radial_way_num];
    GgafDxUtil::getRadialAngle2D(0, prm_radial_way_num, paAng_way);
    GgafDxGeoElem* paGeo = NEW GgafDxGeoElem[prm_radial_way_num];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDxUtil::setWorldMatrix_RzRy(GgafDxUtil::simplifyAng(prm_rz-D90ANG), prm_ry, matWorldRot);

    float vx, vy, vz;
    float tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    for (int i = 0; i < prm_radial_way_num; i++) {
        GgafDxUtil::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDxUtil::convVectorToRzRy(tx, ty, tz,
                                     paGeo[i].rz, paGeo[i].ry);
    }
    GgafDxFigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_radial_way_num; i++) {
            pActor_shot = (GgafDxFigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getKuroko()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getKuroko()->setMvVelo(now_velo);
                pActor_shot->getKuroko()->setMvAcce(now_acce);
//                pActor_shot->_rz = Rz;
//                pActor_shot->_ry = Ry;
                if (pFunc_call_back_dispatched) {
                    pFunc_call_back_dispatched(pActor_shot, dispatch_num, n, i);
                }
            }
        }
        now_velo *= prm_attenuated;
    }
    GGAF_DELETEARR(paAng_way);
    GGAF_DELETEARR(paGeo);
    return pActor_shot;
}

GgafDxFigureActor* StgUtil::shotWay004(const GgafDxGeometricActor* prm_pFrom,
                                       GgafActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDxFigureActor*, int, int, int)) {
    return shotWay004(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_way, prm_expanse_angle,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}





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
