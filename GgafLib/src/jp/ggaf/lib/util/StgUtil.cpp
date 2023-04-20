#include "jp/ggaf/lib/util/StgUtil.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/lib/util/StgUtil.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker2D.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker3D.h"
#include "jp/ggaf/lib/util/ColliSphere.h"
#include "jp/ggaf/lib/util/ColliAAPrism.h"
#include "jp/ggaf/lib/util/ColliAAPyramid.h"



using namespace GgafLib;

bool StgUtil::_was_StgUtil_inited_flg = false;
float StgUtil::ROOT_1_MINUS_XX[1000];
uint32_t StgUtil::BITNUM[33];
std::map<pos_t,pos_t> StgUtil::POS_R_TRIANGLE_inv_X;
std::map<pos_t,pos_t> StgUtil::POS_R_TRIANGLE_inv_Y;


#define C_INT64(X)  ( (int_fast64_t)((X) * (1.0 / LEN_UNIT)) )


void StgUtil::init() {
    GgafDx::Util::init();
    if (StgUtil::_was_StgUtil_inited_flg) {
        return;
    }

    //ROOT_1_MINUS_XX�̐ݒ�
    for (int i = 0; i < 1000; i++) {
        StgUtil::ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }

    BITNUM[0] = (uint32_t)0;
    for (int i = 1; i < 33; i++) {
        BITNUM[i] = ((uint32_t)1 << (i-1));
    }

    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_NN] = POS_R_TRIANGLE_PN;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_NP] = POS_R_TRIANGLE_PP;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_PN] = POS_R_TRIANGLE_NN;
    StgUtil::POS_R_TRIANGLE_inv_X[POS_R_TRIANGLE_PP] = POS_R_TRIANGLE_NP;

    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_NN] = POS_R_TRIANGLE_NP;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_NP] = POS_R_TRIANGLE_NN;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_PN] = POS_R_TRIANGLE_PP;
    StgUtil::POS_R_TRIANGLE_inv_Y[POS_R_TRIANGLE_PP] = POS_R_TRIANGLE_PN;

    StgUtil::_was_StgUtil_inited_flg = true;
}

GgafDx::CollisionChecker* StgUtil::createCollisionChecker(GgafDx::GeometricActor* prm_pActor) {
    if (CONFIG::ENABLE_WORLD_HIT_CHECK_2D) {
        return NEW WorldCollisionChecker2D(prm_pActor);
    } else {
        return NEW WorldCollisionChecker3D(prm_pActor);
    }
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //���� �� ����
    //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
    //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
    //(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
    double dx = (double)( (pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx) );
    double dy = (double)( (pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy) );
    double dz = (double)( (pActor02->_z+pSphere02->_cz) - (pActor01->_z+pSphere01->_cz) );
    double dd = dx*dx + dy*dy + dz*dz;
    if (dd <= (double)(pSphere02->_r + pSphere01->_r) * (double)(pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02) {
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

    double square_length = 0; //���̒��S��AAB�̍ŒZ����(����)�����l
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
    if (square_length <= pSphere02->_rr) { //�����蔻��Ȃ̂ŁA���[�g���Ƃ炸���̂܂܂̔�r�ł悢
        return true;
    } else {
        return false;
    }
}


bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02     ) {
    //���v���Y�� �� AAB��
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord aZ = pActor01->_z;
    const coord aX1 = aX + pAAPrism01->_x1;
    const coord aY1 = aY + pAAPrism01->_y1;
    const coord aZ1 = aZ + pAAPrism01->_z1;
    const coord aX2 = aX + pAAPrism01->_x2;
    const coord aY2 = aY + pAAPrism01->_y2;
    const coord aZ2 = aZ + pAAPrism01->_z2;
    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bZ1 = pActor02->_z + pAABox02->_z1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;
    const coord bZ2 = pActor02->_z + pAABox02->_z2;

    if (aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        if (pos & POS_PRISM_XY_xx) { //XY���ʃX���C�X�̃v���Y��
            //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
            const double b = ((aY+pAAPrism01->_cy) - pAAPrism01->_a * (aX+pAAPrism01->_cx)) + pAAPrism01->_b;

            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { // �̂���� POS_PRISM_xx_NN �݂̂ł���
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
        } else if (pos & POS_PRISM_YZ_xx) {//YZ���ʃX���C�X�̃v���Y��
            //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = z - ay
            int b = ((aZ+pAAPrism01->_cz) - pAAPrism01->_a * (aY+pAAPrism01->_cy)) + pAAPrism01->_b;
            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { //�̂���� POS_PRISM_xx_NN �݂̂ł���
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

        } else if (pos & POS_PRISM_ZX_xx) {
            //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = x - az
            int b = ((aX+pAAPrism01->_cx) - pAAPrism01->_a * (aZ+pAAPrism01->_cz)) + pAAPrism01->_b;
            if (pos & POS_PRISM_xx_PP) {
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

            } else if (pos & POS_PRISM_xx_NP) {
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

            } else if (pos & POS_PRISM_xx_PN) {
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

            } else { //�c��� POS_PRISM_xx_NN �݂̂ł���
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


bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //���v���Y�� �� ����
    //MEMO:�����ȓ����蔻��v�Z�͍s���Ă��܂���B
    //�܂��A�� �� AAB �̔�����s��
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord aZ = pActor01->_z;
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord o_scz = pActor02->_z + pSphere02->_cz;
    const coord aX1 = aX + pAAPrism01->_x1;
    const coord aY1 = aY + pAAPrism01->_y1;
    const coord aZ1 = aZ + pAAPrism01->_z1;
    const coord aX2 = aX + pAAPrism01->_x2;
    const coord aY2 = aY + pAAPrism01->_y2;
    const coord aZ2 = aZ + pAAPrism01->_z2;
    double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
    if(o_scx < aX1) {
        square_length += (double)(o_scx - aX1) * (o_scx - aX1);
    }
    if(o_scx > aX2) {
        square_length += (double)(o_scx - aX2) * (o_scx - aX2);
    }
    if(o_scy < aY1) {
        square_length += (double)(o_scy - aY1) * (o_scy - aY1);
    }
    if(o_scy > aY2) {
        square_length += (double)(o_scy - aY2) * (o_scy - aY2);
    }
    if(o_scz < aZ1) {
        square_length += (double)(o_scz - aZ1) * (o_scz - aZ1);
    }
    if(o_scz > aZ2) {
        square_length += (double)(o_scz - aZ2) * (o_scz - aZ2);
    }
    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length > pSphere02->_rr) {
        return false;
    }
    //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���

    const int pos = pAAPrism01->_pos_info;
    const double a = pAAPrism01->_a;
    if (pos & POS_PRISM_XY_xx) { //XY���ʃX���C�X�̃v���Y��
        //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
        const double b = ((aY+pAAPrism01->_cy) - pAAPrism01->_a * (aX+pAAPrism01->_cx)) + pAAPrism01->_b;

        int oppX, oppY;
        const int bZc = o_scz; //���̒��SZ���W
        if (aZ1 < bZc && bZc < aZ2) {
            //���̒��SZ���W���v���Y����Z���͈͓��Ȃ�΁A�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
            //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
            oppX = o_scx + pAAPrism01->_vIH_x * pSphere02->_r;
            oppY = o_scy + pAAPrism01->_vIH_y * pSphere02->_r;
        } else if (bZc >= aZ2) {
            //���̒��SZ���W���v���Y����Z���͈͊O�̏ꍇ
            //����鋗���ɉ����āA�����̔��a(pSphere02->_r)�����������č������v�Z
            //���������銄���� ROOT_1_MINUS_XX (1/4�~�̉��̃e�[�u���z��j���g�p�B
            //                 |
            //                 �_
            //        ���������� `��
            // z- ��  ��      ��  �� z+
            int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bZc - aZ2) / pSphere02->_r)*1000)];
            oppX = o_scx + pAAPrism01->_vIH_x * r;
            oppY = o_scy + pAAPrism01->_vIH_y * r;
        } else { //if (aZ1 >= bZc) {
            int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aZ1 - bZc) / pSphere02->_r)*1000)];
            oppX = o_scx + pAAPrism01->_vIH_x * r;
            oppY = o_scy + pAAPrism01->_vIH_y * r;
        }

        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { // �̂���� POS_PRISM_xx_NN �݂̂ł���
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
    } else if (pos & POS_PRISM_YZ_xx) {//YZ���ʃX���C�X�̃v���Y��
        //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = z - ay
        const int b = ((aZ+pAAPrism01->_cz) - pAAPrism01->_a * (aY+pAAPrism01->_cy)) + pAAPrism01->_b;
        int oppY, oppZ;

        const int bXc = o_scx;
        if (aX1 < bXc && bXc < aX2) {
            oppY = o_scy + pAAPrism01->_vIH_x * pSphere02->_r;
            oppZ = o_scz + pAAPrism01->_vIH_y * pSphere02->_r;
        } else {
            if (bXc >= aX2) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bXc - aX2) / pSphere02->_r)*1000)];
                oppY = o_scy + pAAPrism01->_vIH_x * r;
                oppZ = o_scz + pAAPrism01->_vIH_y * r;
            } else if (aX1 >= bXc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aX1 - bXc) / pSphere02->_r)*1000)];
                oppY = o_scy + pAAPrism01->_vIH_x * r;
                oppZ = o_scz + pAAPrism01->_vIH_y * r;
            }
        }
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { //�̂���� POS_PRISM_xx_NN �݂̂ł���
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

    } else if (pos & POS_PRISM_ZX_xx) {
        //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = x - az
        const int b = ((aX+pAAPrism01->_cx) - pAAPrism01->_a * (aZ+pAAPrism01->_cz)) + pAAPrism01->_b;
        int oppZ,oppX;
        const int bYc = o_scy;
        if (aY1 < bYc && bYc < aY2) {
            oppZ = o_scz + pAAPrism01->_vIH_x * pSphere02->_r;
            oppX = o_scx + pAAPrism01->_vIH_y * pSphere02->_r;
        } else {
            if (bYc >= aY2) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(bYc - aY2) / pSphere02->_r)*1000)];
                oppZ = o_scz + pAAPrism01->_vIH_x * r;
                oppX = o_scx + pAAPrism01->_vIH_y * r;
            } else if (aY1 >= bYc) {
                int r = pSphere02->_r * UTIL::ROOT_1_MINUS_XX[(int)((1.0*(aY1 - bYc) / pSphere02->_r)*1000)];
                oppZ = o_scz + pAAPrism01->_vIH_x * r;
                oppX = o_scx + pAAPrism01->_vIH_y * r;
            }
        }
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { //�c��� POS_PRISM_xx_NN �݂̂ł���
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
    return false;
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*     const pAABox02     ) {
    //�s���~�b�h��BOX
    const coord aX1 = pActor01->_x + pAAPyramid01->_x1;
    const coord aY1 = pActor01->_y + pAAPyramid01->_y1;
    const coord aZ1 = pActor01->_z + pAAPyramid01->_z1;
    const coord aX2 = pActor01->_x + pAAPyramid01->_x2;
    const coord aY2 = pActor01->_y + pAAPyramid01->_y2;
    const coord aZ2 = pActor01->_z + pAAPyramid01->_z2;
    //�Ζʂ̖@��
    float a = pAAPyramid01->_s_nvx;
    float b = pAAPyramid01->_s_nvy;
    float c = pAAPyramid01->_s_nvz;
    //�ΖʂƑΊp���̌�_
    const coord px = pActor01->_x + pAAPyramid01->_l_px;
    const coord py = pActor01->_y + pAAPyramid01->_l_py;
    const coord pz = pActor01->_z + pAAPyramid01->_l_pz;

    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bZ1 = pActor02->_z + pAABox02->_z1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;
    const coord bZ2 = pActor02->_z + pAABox02->_z2;


    if (aX2 >= bX1 && aX1 <= bX2 && aZ2 >= bZ1 && aZ1 <= bZ2 && aY2 >= bY1 && aY1 <= bY2) {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g

        //�s���~�b�h�Ζʂɑ΂��ăs���~�b�h����BOX�̈���ŁA����BOX�̍ŋߖT�_�����߂�
        const pos_t pos_info = pAAPyramid01->_pos_info;
        coord nnx, nny, nnz; //BOX���ŋߖT�_
        if (pos_info & POS_PYRAMID_Pxx) {
            //bX2�ɋ���������
            if (/* aX1 <= bX2 && */ bX2 <= aX2) {
                //bX2 �����ɂ���
                nnx = bX2;
            } else { //if (aX2 < bX2) {
                //bX2 ���O�ɂ���
                nnx = aX2;
            }
        } else {
            //bX1�ɋ���������
            if (aX1 <= bX1 /* && bX1 <= aX2*/ ) {
                //bX1 �����ɂ���
                nnx = bX1;
            } else { // if (aX1 > bX1) {
                //bX1 ���O�ɂ���
                nnx = aX1;
            }
        }
        if (pos_info & POS_PYRAMID_xPx) {
            //bY2�ɋ���������
            if (/* aY1 <= bY2 &&*/ bY2 <= aY2) {
                //bY2 �����ɂ���
                nny = bY2;
            } else { //if (aY2 < bY2) {
                //bY2 ���O�ɂ���
                nny = aY2;
            }
        } else {
            //bY1�ɋ���������
            if (aY1 <= bY1 /*&& bY1 <= aY2*/) {
                //by1 �����ɂ���
                nny = bY1;
            } else { //if (aY1 > bY1) {
                //bx1 ���O�ɂ���
                nny = aY1;
            }
        }

        if (pos_info & POS_PYRAMID_xxP) {
            //bZ2�ɋ���������
            if (/*aZ1 <= bZ2 &&*/ bZ2 <= aZ2) {
                //bZ2 �����ɂ���
                nnz = bZ2;
            } else { //if (aZ2 < bZ2) {
                //bZ2 ���O�ɂ���
                nnz = aZ2;
            }
        } else {
            //bZ1�ɋ���������
            if (aZ1 <= bZ1 /* && bZ1 <= aZ2*/) {
                //bz1 �����ɂ���
                nnz = bZ1;
            } else { //if (aZ1 > bZ1) {
                //bx1 ���O�ɂ���
                nnz = aZ1;
            }
        }
        //(nnx,nny,nnz) ��BOX���ߖT�_
        //�Ζʂ̖@���x�N�g�� (a, b, c)
        //�Ζʏ�̓_(px, py, pz) ���� �ߖT�_(nnx,nny,nnz) �̃x�N�g��
        // (nnx-px, nny-py, nnz-pz) �̓��ς� �� �Ȃ�΋ߖT�_ (nnx,nny,nnz) ���s���~�b�h�̒��ɂ���
        double d = a*(nnx-px) + b*(nny-py) + c*(nnz-pz);
        if (d < 0) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool StgUtil::isHit3D(const GgafDx::GeometricActor* const pActor01, const ColliAAPyramid* const pAAPyramid01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*    const pSphere02  ) {
    //�O���p�O�p���̎O���p���_�̍��W�����_(0,0,0)�ɂ����A
    //A(ex,0,0), B(0,ey,0), C(0,0,ez) �̎O���p�O�p���œ����蔻����l�������̂ŁA
    //���̈ʒu(o_cx, o_cy, o_cz)�����W�ϊ�����B

    const int_fast64_t ex = C_INT64(pAAPyramid01->_dx); //�������̂܂ܒ��_A��X�����W�ƂȂ�
    const int_fast64_t ey = C_INT64(pAAPyramid01->_dy); //���������̂܂ܒ��_B��Y�����W�ƂȂ�
    const int_fast64_t ez = C_INT64(pAAPyramid01->_dz); //���s���������̂܂ܒ��_C��Z�����W�ƂȂ�
    const int_fast64_t o_r  = C_INT64(pSphere02->_r);   //���̔��a�͍��W�ϊ��ɖ��e���Ȃ̂ł��̂܂�
    const int_fast64_t o_rr = o_r*o_r;

    //�{���̋��̈ʒu
    int_fast64_t o_cx = C_INT64(pActor02->_x + pSphere02->_cx);
    int_fast64_t o_cy = C_INT64(pActor02->_y + pSphere02->_cy);
    int_fast64_t o_cz = C_INT64(pActor02->_z + pSphere02->_cz);
    const pos_t pos_info = pAAPyramid01->_pos_info; //�O���p�O�p���̎p�����
    if (pos_info & POS_PYRAMID_Pxx) {
        //���̎O���p�O�p���̒��_��X���͐��̕���
        o_cx -= C_INT64(pActor01->_x + pAAPyramid01->_x2);
        o_cx = -o_cx; //x�����]
    } else {
        //���̎O���p�O�p���̒��_��X���͕��̕���
        o_cx -= C_INT64(pActor01->_x + pAAPyramid01->_x1);
    }
    if (pos_info & POS_PYRAMID_xPx) {
        //���̎O���p�O�p���̒��_��Y���͐��̕���
        o_cy -= C_INT64(pActor01->_y + pAAPyramid01->_y2);
        o_cy = -o_cy; //y�����]
    } else {
        //���̎O���p�O�p���̒��_��Y���͕��̕���
        o_cy -= C_INT64(pActor01->_y + pAAPyramid01->_y1);
    }

    if (pos_info & POS_PYRAMID_xxP) {
        //���̎O���p�O�p���̒��_��Z���͐��̕���
        o_cz -= C_INT64(pActor01->_z + pAAPyramid01->_z2);
        o_cz = -o_cz; //z�����]
    } else {
        //���̎O���p�O�p���̒��_��Z���͕��̕���
        o_cz -= C_INT64(pActor01->_z + pAAPyramid01->_z1);
    }
    //���̈ʒu�ϊ������A�������瓖���蔻�胍�W�b�N

    //xy���ʂ���(���T����)��
    const bool xy = (o_cz > 0);
    //yz���ʂ���(���T����)��
    const bool yz = (o_cx > 0);
    //zx���ʂ���(���T����)��
    const bool zx = (o_cy > 0);
    //xy���ʂɕ��s�ȓ_C��ʂ镽��(true:���_��)
    const bool xy_C = (o_cz < ez);
    //yz���ʂɕ��s�ȓ_A��ʂ镽��(true:���_��)
    const bool yz_A = (o_cx < ex);
    //zx���ʂɕ��s�ȓ_B��ʂ镽��(true:���_��)
    const bool zx_B = (o_cy < ey);

    //����BOX�̓����蔻����܂��s��
    const int_fast64_t o_cx2 = o_cx*o_cx;
    const int_fast64_t o_cy2 = o_cy*o_cy;
    const int_fast64_t o_cz2 = o_cz*o_cz;
    const int_fast64_t o_cx_MINUS_ex2 = (o_cx - ex)*(o_cx - ex);
    const int_fast64_t o_cy_MINUS_ey2 = (o_cy - ey)*(o_cy - ey);
    const int_fast64_t o_cz_MINUS_ez2 = (o_cz - ez)*(o_cz - ez);
    int_fast64_t slength = 0; //���̒��S��AAB�̍ŒZ�������悵���l
    if (!yz) {
        slength += o_cx2;
    }
    if (!yz_A) {
        slength += o_cx_MINUS_ex2;
    }
    if (!zx) {
        slength += o_cy2;
    }
    if (!zx_B) {
        slength += o_cy_MINUS_ey2;
    }
    if (!xy) {
        slength += o_cz2;
    }
    if (!xy_C) {
        slength += o_cz_MINUS_ez2;
    }
    if (slength > o_rr) {
        //square_length �����̔��a�i�̓��j�����������BOX�Ƃ���Փ˂��Ă��Ȃ��B
        return false;
    }
    //��������ȍ~�́A�� �� BOX �ŏՓ˂��Ă��邱�ƂɂȂ�B
    //�O���p�O�p���̂ǂ̕����i���_�A�ӁA�ʁj�Ƃ̋����Ŕ��肷��΂悢��
    //�ꍇ�킯�ōl����

    if (!xy && !yz && !zx) {
        //���_�Ƃ̋����Ŕ���
        //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
        return true;
    }

    if (xy) {
        if (!yz) {
            if (!zx) {
                if (xy_C) {
                    //��OC�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }
            }
        }
    } else {
        if (yz) {
            if (!zx) {
                if (yz_A) {
                    //��OA�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }
            }
        } else {
            if (zx) {
                if (zx_B) {
                    //��OB�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }
            }
        }
    }

    const int_fast64_t exey = ex*ey;
    const int_fast64_t eyez = ey*ez;
    const int_fast64_t ezex = ez*ex;
    // A(ex,0,0), B(0,ey,0) ���܂�xy���ʂɐ����Ȗʂ����i���_�����鑤�j
    const bool vxy_AB = (-ey*o_cx - ex*o_cy           + exey > 0);
    // B(0,ey,0), C(0,0,ez) ���܂�yz���ʂɐ����Ȗʂ����i���_�����鑤�j
    const bool vyz_BC = (          -ez*o_cy - ey*o_cz + eyez > 0);
    // C(0,0,ez), A(ex,0,0) ���܂�zx���ʂɐ����Ȗʂ����i���_�����鑤�j
    const bool vzx_CA = (-ez*o_cx           - ex*o_cz + ezex > 0);
    if (xy) {
        if (yz) {
            if (!zx) {
                if (vzx_CA) {
                    //��OCA�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }

            }
        } else {
            if (zx) {
                if (vyz_BC) {
                    //��OBC�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }
            }
        }
    } else {
        if (yz) {
            if (zx) {
                if (vxy_AB) {
                    //��OAB�Ƃ̋����Ŕ���
                    //�� �� BOX �ŏՓ˂��Ă���̂Ńq�b�g
                    return true;
                }
            }
        }
    }

    const int_fast64_t ex2 = ex*ex;
    const int_fast64_t ey2 = ey*ey;
    const int_fast64_t ez2 = ez*ez;
    //�_A�ƕ�AB�̋��E��(true:���_��)
    const bool bo_A_AB = ( ezex * o_cx - eyez * o_cy               - ex2*ez > 0);
    //�_A�ƕ�AC�̋��E��(true:���_��)
    const bool bo_A_AC = ( exey * o_cx               - eyez * o_cz - ey*ex2 > 0);
    //�Ȃ������Ȃ�̂��́A�u���ƃs���~�b�h�i���_�ƕӂ̋��E�ʁj�v�Q��
    if (!yz_A && bo_A_AB && bo_A_AC) {
        //���_A�Ƃ̋����Ŕ���
        int_fast64_t length = o_cx_MINUS_ex2 + o_cy2 + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //�_B�ƕ�BA�̋��E��(true:���_��)
    const bool bo_B_BA = (-ezex * o_cx + eyez * o_cy               - ey2*ez > 0);
    //�_B�ƕ�BC�̋��E��(true:���_��)
    const bool bo_B_BC = (               exey * o_cy - ezex * o_cz - ey2*ex > 0);
    if (!zx_B && bo_B_BA && bo_B_BC) {
        //���_B�Ƃ̋����Ŕ���
        int_fast64_t length = o_cx2 + o_cy_MINUS_ey2 + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }
    //�_C�ƕ�CA�̋��E��(true:���_��)
    const bool bo_C_CA = (-exey * o_cx               + eyez * o_cz - ey*ez2 > 0);
    //�_C�ƕ�CB�̋��E��
    const bool bo_C_CB = (              -exey * o_cy + ezex * o_cz - ex*ez2 > 0);
    if (!xy_C && bo_C_CA && bo_C_CB) {
        //���_C�Ƃ̋����Ŕ���
        int_fast64_t length = o_cx2 + o_cy2 + o_cz_MINUS_ez2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //A(ex,0,0), B(0,ey,0) ���܂ގΖʂɐ����Ȗʂ����i���_�����鑤�j
    bool vramp_AB = ((-ex*ey2)*o_cx      + (-ex2*ey)*o_cy      + (ez*(ex2+ey2))*o_cz + (ex2*ey2) > 0);
    //�Ȃ������Ȃ�̂��́A�u���ƃs���~�b�h�i�ΖʂƂ̋����Ŕ��肷��͈́j�v�Q��
    if (!vxy_AB && !bo_A_AB && !bo_B_BA && !vramp_AB) {
        //��AB�Ƃ̋����Ŕ���
        // A(ex,0,0), B(0,ey,0)  ���
        // ��AB�̒����̎���
        //
        // �_P(o_cx, o_cy, o_cz) ��
        // AB��ʂ钼��l (x,y,z) = (ex,0,0) + t(-ex, ey, 0)�̋������l����B
        // �_P���璼��l�ɐ����ɍ~�낵�����̌�_�� H �Ƃ���ƁA�_H�͒���l��Ȃ̂�
        // �_H(ex-t*ex, t*ey, 0) �ł���킳���
        //
        // |PH|^2 = ((ex-t*ex)-o_cx)^2 + (t*ey - o_cy)^2 + (0-o_cz)^2
        //
        // �Ƃ���ŁAAB��PH�͐����Ȃ̂�
        // (-ex, ey, 0)�E((ex-t*ex)-o_cx, t*ey-o_cy, -o_cz) = 0
        //
        // (-ex*((ex-t*ex)-o_cx)) + (ey*(t*ey-o_cy)) + (0) = 0
        // t=(ey*o_cy-ex*o_cx+ex^2)/(ey^2+ex^2)
        double t = (ey*o_cy - ex*o_cx + ex2) / double(ey2+ex2);
        int_fast64_t length = ((ex-t*ex)-o_cx)*((ex-t*ex)-o_cx) + (t*ey - o_cy)*(t*ey - o_cy) + o_cz2;
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //B(0,ey,0) C(0,0,ez)  ���܂ގΖʂɐ����Ȗʂ����i���_�����鑤�j
    bool vramp_BC = ((ex*(ey2+ez2))*o_cx + (-ey*ez2)*o_cy      + (-ey2*ez)*o_cz      + (ey2*ez2) > 0);
    if (!vyz_BC && !bo_B_BC && !bo_C_CB && !vramp_BC) {
        //��BC�Ƃ̋����Ŕ���
        double t = (ez*o_cz - ey*o_cy + ey2) / double(ez2+ey2);
        int_fast64_t length = o_cx2 + ((ey-t*ey) - o_cy)*((ey-t*ey) - o_cy) + (t*ez - o_cz)*(t*ez - o_cz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //C(0,0,ez) A(ex,0,0)  ���܂ގΖʂɐ����Ȗʂ����i���_�����鑤�j
    bool vramp_CA = ((-ez2*ex)*o_cx      + (ey*(ez2+ex2))*o_cy + (-ez*ex2)*o_cz      + (ez2*ex2) > 0);
    if (!vzx_CA && !bo_A_AC && !bo_C_CA && !vramp_CA) {
        //��CA�Ƃ̋����Ŕ���
        double t = (ex*o_cx - ez*o_cz + ez2) / double(ez2+ex2);
        int_fast64_t length = (t*ex-o_cx)*(t*ex-o_cx) + o_cy2 + ((ez-t*ez) - o_cz)*((ez-t*ez) - o_cz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    //�Ζʂ��O���i���_�̖������j
    int_fast64_t ramp_value = eyez*o_cx + ezex*o_cy + exey*o_cz - ex*ey*ez;
    bool ramp = (ramp_value > 0);
    if (vramp_AB && vramp_BC && vramp_CA && ramp) {
        //��ABC�Ƃ̋����Ŕ���
        //�~�̒��S����Ζʂɍ~�낵�������̌�_(lx,ly,lz)�����߂�
        //�Ζʂ�
        //a*x + b*y + c*z - ex*ey*ez = 0
        //�����̕�������
        //(x,y,z) = (o_cx,o_cy,o_cz) + t(a,b,c)
        // x = o_cx + t*a
        // y = o_cy + t*b
        // z = o_cz + t*c
        // t�����߂�
        // a*(o_cx + t*a) + b*(o_cy + t*b) + c*(o_cz + t*c) - ex*ey*ez = 0
        // t=-(c*o_cz+b*o_cy+a*o_cx-ex*ey*ez)/(c^2+b^2+a^2)
        //�Ζʂ̕������̗v�f

        //�Ζʂ̖@��(a,b,c)
        //int_fast64_t a = eyez;
        //int_fast64_t b = ezex;
        //int_fast64_t c = exey;
        //double d = -(ex*ex*ez);
        //double t =-(a*o_cx + b*o_cy +c*o_cz - ex*ey*ez) / double(a*a + b*b + c*c);
        double t = -ramp_value / double(eyez*eyez + ezex*ezex + exey*exey);
        //��_��
        int_fast64_t lx = o_cx + t*eyez;
        int_fast64_t ly = o_cy + t*ezex;
        int_fast64_t lz = o_cz + t*exey;
        //�~�̒��S����A�Ζʂɐ��������낵���Ƃ��̌�_�Ƃ̋���(�̂Q��)
        int_fast64_t length = (o_cx-lx)*(o_cx-lx) + (o_cy-ly)*(o_cy-ly) + (o_cz-lz)*(o_cz-lz);
        if (length < o_rr) {
            return true;
        } else {
            return false;
        }
    }

    if (xy && yz && zx && !ramp) {
        //�O�p������
        return true;
    } else {
        _TRACE_("�y�x���zStgUtil::isHit3D() ���l�͈͂��I�[�o�[�t���[���āA���������肳��Ă��܂���B");
    }

    return false;
}

bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliSphere* const pSphere01 ,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* const pSphere02 ) {
    //���� �� ����
    //��1 �F ���S�_�̍��WP1(x1, y1, z1), ���ar1
    //��2 �F ���S�_�̍��WP2(x2, y2, z2), ���ar2
    //(x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
    double d2 = (double)((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) * ((pActor02->_x+pSphere02->_cx) - (pActor01->_x+pSphere01->_cx)) +
                (double)((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy)) * ((pActor02->_y+pSphere02->_cy) - (pActor01->_y+pSphere01->_cy));
    if (d2 <= (double)(pSphere02->_r + pSphere01->_r) * (pSphere02->_r + pSphere01->_r)
    ) {
        return true;
    } else {
        return false;
    }
}


bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAABox*  pAABox01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere* pSphere02) {
    //��AAB �� ����
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord bx1 = pActor01->_x + pAABox01->_x1;
    const coord bx2 = pActor01->_x + pAABox01->_x2;
    const coord by1 = pActor01->_y + pAABox01->_y1;
    const coord by2 = pActor01->_y + pAABox01->_y2;

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
    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length <= pSphere02->_rr) {
        return true;
    } else {
        return false;
    }
}
bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAABox*   const pAABox02   ) {
    const coord aX1 = pActor01->_x + pAAPrism01->_x1;
    const coord aY1 = pActor01->_y + pAAPrism01->_y1;
    const coord aX2 = pActor01->_x + pAAPrism01->_x2;
    const coord aY2 = pActor01->_y + pAAPrism01->_y2;
    const coord bX1 = pActor02->_x + pAABox02->_x1;
    const coord bY1 = pActor02->_y + pAABox02->_y1;
    const coord bX2 = pActor02->_x + pAABox02->_x2;
    const coord bY2 = pActor02->_y + pAABox02->_y2;

    if (aY2 >= bY1 && aY1 <= bY2 && aX2 >= bX1 && aX1 <= bX2) {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
        const int pos = pAAPrism01->_pos_info;
        const double a = pAAPrism01->_a;
        const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;
        if (pos & POS_PRISM_xx_PP) {
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

        } else if (pos & POS_PRISM_xx_NP) {
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

        } else if (pos & POS_PRISM_xx_PN) {
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

        } else { // �̂���� POS_PRISM_xx_NN �݂̂ł���
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
    }
    return false;
}
bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliSphere*  const pSphere02  ) {
    //���v���Y�� �� ����
    //MEMO:�����ȓ����蔻��v�Z�͍s���Ă��܂���B

    //�܂��A�� �� AAB �̔�����s��
    const coord o_scx = pActor02->_x + pSphere02->_cx;
    const coord o_scy = pActor02->_y + pSphere02->_cy;
    const coord aX1 = pActor01->_x + pAAPrism01->_x1;
    const coord aY1 = pActor01->_y + pAAPrism01->_y1;
    const coord aX2 = pActor01->_x + pAAPrism01->_x2;
    const coord aY2 = pActor01->_y + pAAPrism01->_y2;
    double square_length = 0; //���̒��S��AAB�̍ŒZ�������悵���l
    if(o_scx < aX1) {
        square_length += (double)(o_scx - aX1) * (o_scx - aX1);
    }
    if(o_scx > aX2) {
        square_length += (double)(o_scx - aX2) * (o_scx - aX2);
    }
    if(o_scy < aY1) {
        square_length += (double)(o_scy - aY1) * (o_scy - aY1);
    }
    if(o_scy > aY2) {
        square_length += (double)(o_scy - aY2) * (o_scy - aY2);
    }
    //square_length�����̔��a�i�̓��j�����Z����ΏՓ˂��Ă���
    if (square_length > pSphere02->_rr) {
        return false;
    }
    //���̎��_��AAB �� ���Ńq�b�g�B��������v���Y���ł��q�b�g�����؂���

    const int pos = pAAPrism01->_pos_info;
    const double a = pAAPrism01->_a;
    //���[���h���W�ł̃v���Y�����E���̐ؕЂ����߂� b = y - ax
    const double b = ((pActor01->_y+pAAPrism01->_cy) - pAAPrism01->_a * (pActor01->_x+pAAPrism01->_cx)) + pAAPrism01->_b;

    //�\�ߕێ����Ă���_vIH_x,_vIH_y���g�p����
    //�v���Y���ΕӂƍŒZ�����̉~�����XY���W�����߂�
    int oppX = o_scx + pAAPrism01->_vIH_x * pSphere02->_r;
    int oppY = o_scy + pAAPrism01->_vIH_y * pSphere02->_r;
    if (pos & POS_PRISM_xx_PP) {
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

    } else if (pos & POS_PRISM_xx_NP) {
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

    } else if (pos & POS_PRISM_xx_PN) {
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

    } else { // �̂���� POS_PRISM_xx_NN �݂̂ł���
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
    return false;
}

bool StgUtil::isHit2D(const GgafDx::GeometricActor* const pActor01, const ColliAAPrism* const pAAPrism01,
                      const GgafDx::GeometricActor* const pActor02, const ColliAAPrism* const pAAPrism02  ) {
    const coord aX = pActor01->_x;
    const coord aY = pActor01->_y;
    const coord bX = pActor02->_x;
    const coord bY = pActor02->_y;

    coord bX1 = bX + pAAPrism02->_x1;
    coord bY1 = bY + pAAPrism02->_y1;
    coord bX2 = bX + pAAPrism02->_x2;
    coord bY2 = bY + pAAPrism02->_y2;
    if (aY + pAAPrism01->_y2 >= bY1 && aY + pAAPrism01->_y1 <= bY2 &&
        aX + pAAPrism01->_x2 >= bX1 && aX + pAAPrism01->_x1 <= bX2)
    {
        //���̎��_��AAB �� AAB �Ȃ�΃q�b�g
    } else {
        //���̎��_��AAB �� AAB ���Ƃ��Ă��q�b�g���ĂȂ�
        return false;
    }
    int pos1 = pAAPrism01->_pos_info; //�����̎O�p�`�̒��p���_�̈ʒu
    double aA = pAAPrism01->_a;       //�����̎O�p�`�̎Εӂ̌X��
    coord aB = aY + pAAPrism01->_b;   //�����̎O�p�`�̎Εӂ̐ؕ�
    float aNx = -pAAPrism01->_vIH_x;  //�����̎O�p�`�̎Εӂ̖@���x�N�g��X�v�f
    float aNy = -pAAPrism01->_vIH_y;  //�����̎O�p�`�̎Εӂ̖@���x�N�g��Y�v�f

    int pos2 = pAAPrism02->_pos_info; //�����̎O�p�`�̒��p���_�̈ʒu
    double bA = pAAPrism02->_a;       //�����̎O�p�`�̎Εӂ̌X��
    coord bB = bY + pAAPrism02->_b;   //�����̎O�p�`�̎Εӂ̐ؕ�
    float bNx = -pAAPrism02->_vIH_x;  //�����̎O�p�`�̎Εӂ̖@���x�N�g��X�v�f
    float bNy = -pAAPrism02->_vIH_y;  //�����̎O�p�`�̎Εӂ̖@���x�N�g��Y�v�f

    //�����̒��p�O�p�`�ɂ��āA���p���_��(0, 0) �ɂ����A�c��̒��_�� A(aEx,0), B(0,aEy) �Ƃ���
    //���p�O�p�`�ł̓����蔻����l�������iPOS_R_TRIANGLE_NN �ɌŒ肵�����j
    const coord aEx = pAAPrism01->_dx;
    const coord aEy = pAAPrism01->_dy;
    const coord aCX = aEx / 2; //�����̎O�p�`�̎Εӏ�̓_��X�v�f
    const coord aCY = aEy / 2; //�����̎O�p�`�̎Εӏ�̓_��Y�v�f
    //�����ŁA�����Ƒ���̒��p�O�p�`�̈ʒu�֌W���_�C�i�~�b�N�ɕϊ��I
    if (pos1 & POS_R_TRIANGLE_Px) {
        //���蒼�p�O�p�`���W�́AX�����s�ړ��EX���W���](Y�����])
        const coord aX2 = aX + pAAPrism01->_x2;
        const coord tmp_bX2 = bX2;
        bX2 = aX2 - bX1;
        bX1 = aX2 - tmp_bX2;
        //aB bB �ؕЂ͂��̂܂�
        //���蒼�p�O�p�`�v�f�́AX���W���](Y�����])
        aA = -aA;
        bA = -bA;
        aNx = -aNx;
        bNx = -bNx;
        pos2 = StgUtil::POS_R_TRIANGLE_inv_X[pos2];
    } else {
        //X�����s�ړ�
        const coord aX1 = aX + pAAPrism01->_x1;
        bX1 -= aX1;
        bX2 -= aX1;
    }

    if (pos1 & POS_R_TRIANGLE_xP) {
        //���蒼�p�O�p�`���W�́AY�����s�ړ��EY���W���](X�����])
        const coord aY2 = aY + pAAPrism01->_y2;
        const coord tmp_bY2 = bY2;
        bY2 = aY2 - bY1;
        bY1 = aY2 - tmp_bY2;
        aB  = aY2 - aB;
        bB  = aY2 - bB;
        //���蒼�p�O�p�`�v�f�́AY���W���](X�����])
        aA = -aA;
        bA = -bA;
        aNy = -aNy;
        bNy = -bNy;
        pos2 = StgUtil::POS_R_TRIANGLE_inv_Y[pos2];
    } else {
        //Y�����s�ړ�
        const coord aY1 = aY + pAAPrism01->_y1;
        bY1 -= aY1;
        bY2 -= aY1;
        aB  -= aY1;
        bB  -= aY1;
    }
    coord bCX = bX1 + (pAAPrism02->_dx / 2); //����̎O�p�`�̎Εӏ�̓_��X�v�f
    coord bCY = bY1 + (pAAPrism02->_dy / 2); //����̎O�p�`�̎Εӏ�̓_��Y�v�f

    //�����̒��_��(0,0)�� POS_R_TRIANGLE_NN �Œ�
    //����̒��p�O�p�`�́A����ɔ����ʒu�֌W���ϊ����ꂽ���
    if (pos2 == POS_R_TRIANGLE_NN) {
        //����̒��p���_�� (bX1, bY1)
        if (bX1 <= 0) {
            if (bY1 <= 0) {
                //�ʒu1
                //���g�̒��p���_���A�ߖT�_(0, 0)
                //����̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (bNx, bNy) ��
                //����̒��p�O�p�`�̎Εӂ̓_ (bCX, bCY) ����  �ߖT�_(0, 0) �̃x�N�g��(-bCX, -bCY)��
                //���ς��� �Ȃ�΋ߖT�_(0, 0) ������̒��p�O�p�`�̒��ɂ���
                //(bNx, bNy)�E(-bCX, -bCY) = bNx*(-bCX) + bNy*(bCY)
                if ((bNx*(-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //�ʒu4
                if (bX2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu7
                return false;
            }
        } else if (bX1 <= aEx) {
            if (bY1 <= 0) {
                //�ʒu2
                if (bY2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //�ʒu5
                //����̒��p���_���A�ߖT�_(bX1, bY1)
                //���g�̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (aNx, aNy) ��
                //���g�̒��p�O�p�`�̎Εӂ̓_ (aCX, aCY) ����  �ߖT�_(bX1, bY1) �̃x�N�g��(bX1-aCX, bY1-aCY)��
                //���ς��� �Ȃ�΋ߖT�_(bX1, bY1) �����p�O�p�`�̒��ɂ���
                //(aNx, aNy)�E(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu8
                return false;
            }
        } else {
            //�ʒu3 or 6 or 9
            return false;
        }
    } //pos2 == POS_R_TRIANGLE_NN

    if (pos2 == POS_R_TRIANGLE_NP) {
        //����̒��p���_�� (bX1, bY2)
        if (bX1 <= 0) {
            if (bY2 <= 0) {
                //�ʒu1
                return false;
            } else if (bY2 <= aEy) {
                //�ʒu4
                if (bX2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu7
                //���g�̒��_�ߖT�_(0, aEy)
                //����̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (bNx, bNy) ��
                //����̒��p�O�p�`�̎Εӂ̓_ (bCX, bCY) ����  �ߖT�_(0, aEy) �̃x�N�g��(-bCX, aEy-bCY)��
                //���ς��� �Ȃ�΋ߖT�_(0, aEy) ������̒��p�O�p�`�̒��ɂ���
                //(bNx, bNy)�E(-bCX, aEy-bCY) = bNx*(-bCX) + bNy*(aEy-bCY)
                if ((bNx*(-bCX) + bNy*(aEy-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            }
        } else if (bX1 <= aEx) {
            if (bY2 <= 0) {
                //�ʒu2
                return false;
            } else if (bY2 <= aEy) {
                //�ʒu5
                //����̒��_�ߖT�_(bX1, bY1)
                //���g�̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (aNx, aNy) ��
                //���g�̒��p�O�p�`�̎Εӂ̓_ (aCX, aCY) ����  �ߖT�_(bX1, bY1) �̃x�N�g��(bX1-aCX, bY1-aCY)��
                //���ς��� �Ȃ�΋ߖT�_(bX1, bY1) �����p�O�p�`�̒��ɂ���
                //(aNx, aNy)�E(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu8
                //�ʒu5�Ɠ���
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            //�ʒu3 or 6or 9
            return false;
        }
    } //pos2 == POS_R_TRIANGLE_NP

    if (pos2 == POS_R_TRIANGLE_PN) {
        //����̒��p���_�� (bX2, bY1)
        if (bX2 <= 0) {
            return false;
        } else if (bX2 <= aEx) {
            if (bY1 <= 0) {
                //�ʒu2
                if (bY2 > 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //�ʒu5
                //����̒��_�ߖT�_(bX1, bY1)
                //���g�̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (aNx, aNy) ��
                //���g�̒��p�O�p�`�̎Εӂ̓_ (aCX, aCY) ����  �ߖT�_(bX1, bY1) �̃x�N�g��(bX1-aCX, bY1-aCY)��
                //���ς��� �Ȃ�΋ߖT�_(bX1, bY1) �����p�O�p�`�̒��ɂ���
                //(aNx, aNy)�E(bX1-aCX, bY1-aCY) = aNx*(bX1-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu8
                return false;
            }
        } else {
            if (bY1 <= 0) {
                //�ʒu3
                //���g�̒��_�ߖT�_(aEx, 0)
                //����̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (bNx, bNy) ��
                //����̒��p�O�p�`�̎Εӂ̓_ (bCX, bCY) ����  �ߖT�_(aEx, 0) �̃x�N�g��(aEx-bCX, -bCY)��
                //���ς��� �Ȃ�΋ߖT�_(aEx, 0) ������̒��p�O�p�`�̒��ɂ���
                //(bNx, bNy)�E(aEx-bCX, -bCY) = bNx*(aEx-bCX) + bNy*(-bCY)
                if ((bNx*(aEx-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if (bY1 <= aEy) {
                //�ʒu6
                //�ʒu5�Ɠ���
                if ((aNx*(bX1-aCX) + aNy*(bY1-aCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //�ʒu9
                return false;
            }
        }
    } //pos2 == POS_R_TRIANGLE_PN

    if (pos2 == POS_R_TRIANGLE_PP) {
        //����̒��p���_�� (bX2, bY2)
        if (bX2 <= 0) {
            //�ʒu1 or 4 or 7
            return false;
        } else if (bX2 <= aEx) {
            if (bY2 <= 0) {
                //�ʒu2
                return false;
            } else {
                //�ʒu5 or 8
            }
        } else {
            if (bY2 <= 0) {
                //�ʒu3
                return false;
            } else if (bY2 <= aEy) {
                //�ʒu6 or 9
            }
        }

        //�ʒu5 or 6 or 8 or 9
        //�܂��X���������r
        // aA < bA �̏ꍇ�A����O�p�`�̒��_(bX1,bY2) �̈ʒu�ɒ���
        // aA > bA �̏ꍇ�A����O�p�`�̒��_(bX2,bY1) �̈ʒu�ɒ���
        // aA = bA �̏ꍇ�A�Εӂ����s�Ȃ̂łǂ����ł�����
        // ���ڂ̒��_�ɂ��āA
        // A(aEx,0) ���܂ގΕӂ̖@���ɕ��s�Ȑ���
        // B(0,aEy) ���܂ގΕӂ̖@���ɕ��s�Ȑ��Ƃ̊Ԃ͈̔�(�͈�R�Ƃ���)
        // �̓����ɑ���̒��_�����邩�������ŏꍇ�킯
        //
        //A(aEx,0) ���܂ގΕӂ̖@���ɕ��s�Ȑ��́A
        //�����̖@�� ��AB=(-aEx, aEy) �Ɍ��������̂�
        //-aEx * x + aEy * y + c = 0
        //���ꂪ�AA(aEx,0)��ʂ�̂�
        //-aEx * aEx + c = 0
        //c = aEx^2
        //�����
        //-aEx * x + aEy * y + aEx^2 > 0
        //
        //B(0,aEy) ���܂ގΕӂ̖@���ɕ��s�Ȑ��́A
        //�����̖@�� ��BA=(aEx, -aEy) �Ɍ��������̂�
        //aEx * x - aEy * y + c = 0
        //���ꂪ�AB(0,aEy) ��ʂ�̂�
        //- aEy * aEy + c = 0
        //c = aEy^2
        //�����
        //aEx * x - aEy * y + aEy^2 > 0

        //�̈�R��
        //-aEx * x + aEy * y + aEx^2 > 0
        //aEx * x - aEy * y + aEy^2 > 0
        //�͈̔�

        const double ex = aEx;
        const double ey = aEy;
        if (aA < bA) {
            //�Εӂ̌X���i���j���A����O�p�`�̕�����萅���ɋ߂�

            //����O�p�`�̒��_(bX1,bY2) �̈ʒu�ɒ���
            if ((-ex*bX1 + ey*bY2 + ex*ex) < 0) {
                //���ڂ̒��_(bX1,bY2)��A(ex,0) ���܂ގΕӂ̖@���ɕ��s�Ȑ��̊O��
                return false;
            } else if ((ex*bX1 - ey*bY2 + ey*ey) < 0) {
                //���ڂ̒��_(bX1,bY2)��B(0,ey) ���܂ގΕӂ̖@���ɕ��s�Ȑ��̊O��

                //���g�̒��_�ߖT�_(0, aEy)
                //����̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (bNx, bNy) ��
                //����̒��p�O�p�`�̎Εӂ̓_ (bCX, bCY) ����  �ߖT�_(0, aEy) �̃x�N�g��(-bCX, aEy-bCY)��
                //���ς��� �Ȃ�΋ߖT�_(0, aEy) ������̒��p�O�p�`�̒��ɂ���
                //(bNx, bNy)�E(-bCX, aEy-bCY) = bNx*(-bCX) + bNy*(aEy-bCY)
                if ((bNx*(-bCX) + bNy*(aEy-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else {
                //���ڂ̒��_(bX1,bY2)���͈�R�͈͓̔��̏ꍇ

                //����̒��_�ߖT�_(bX1,bY2)
                //���g�̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (aNx, aNy) ��
                //���g�̒��p�O�p�`�̎Εӂ̓_ (aCX, aCY) ����  �ߖT�_(bX1,bY2) �̃x�N�g��(bX1-aCX, bY2-aCY)��
                //���ς��� �Ȃ�΋ߖT�_(bX1, bY2) �����p�O�p�`�̒��ɂ���
                //(aNx, aNy)�E(bX1-aCX, bY2-aCY) = aNx*(bX1-aCX) + aNy*(bY2-aCY)
                if ((aNx*(bX1-aCX) + aNy*(bY2-aCY)) < 0)  {
                    return true;
                } else {
                    return false;
                }
            }

        } else {
            //�Εӂ̌X���i���j���A����O�p�`�̕�����萂���ɋ߂�
            //����O�p�`�̒��_(bX2,bY1) �̈ʒu�ɒ���
            if ((-ex*bX2 + ey*bY1 + ex*ex) < 0) {
                //���ڂ̒��_(bX2,bY1)��A(ex,0) ���܂ގΕӂ̖@���ɕ��s�Ȑ��̊O��

                //���g�̒��_�ߖT�_(aEx, 0)
                //����̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (bNx, bNy) ��
                //����̒��p�O�p�`�̎Εӂ̓_ (bCX, bCY) ����  �ߖT�_(aEx, 0) �̃x�N�g��(aEx-bCX, -bCY)��
                //���ς��� �Ȃ�΋ߖT�_(aX2, 0) ������̒��p�O�p�`�̒��ɂ���
                //(bNx, bNy)�E(aEx-bCX, -bCY) = bNx*(aEx-bCX) + bNy*(-bCY)
                if ((bNx*(aEx-bCX) + bNy*(-bCY)) < 0) {
                    return true;
                } else {
                    return false;
                }
            } else if ((ex*bX2 - ey*bY1 + ey*ey) < 0) {
                //���ڂ̒��_(bX2,bY1)��B(0,ey) ���܂ގΕӂ̖@���ɕ��s�Ȑ��̊O��

                return false;
            } else {
                //���ڂ̒��_(bX2,bY1)���͈�R�͈͓̔��̏ꍇ

                //����̒��_�ߖT�_(bX2,bY1)
                //���g�̒��p�O�p�`�̎Εӂ̖@���x�N�g�� (aNx, aNy) ��
                //���g�̒��p�O�p�`�̎Εӂ̓_ (aCX, aCY) ����  �ߖT�_(bX2,bY1) �̃x�N�g��(bX2-aCX, bY1-aCY)��
                //���ς��� �Ȃ�΋ߖT�_(bX2, bY1) �����p�O�p�`�̒��ɂ���
                //(aNx, aNy)�E(bX2-aCX, bY1-aCY) = aNx*(bX2-aCX) + aNy*(bY1-aCY)
                if ((aNx*(bX2-aCX) + aNy*(bY1-aCY)) < 0)  {
                    return true;
                } else {
                    return false;
                }
            }

        }
    } //pos2 == POS_R_TRIANGLE_PP

    return false;
}

GgafDx::FigureActor* StgUtil::shotWay001(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    if (prm_set_num <= 0) {  return nullptr;  }
    double vx, vy, vz;
    GgafDx::Util::convRzRyToVector(prm_rz, prm_ry, vx, vy, vz);
    coord x = vx * prm_r;
    coord y = vy * prm_r;
    coord z = vz * prm_r;
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
        if (pActor_shot) {
            dispatch_num++;
            pActor_shot->setPosition(prm_x + x,
                                     prm_y + y,
                                     prm_z + z);
            pActor_shot->getLocoVehicle()->setRzRyMvAng(prm_rz, prm_ry);
            pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
            pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
            if (pFunc_call_back_dispatched) {
                pFunc_call_back_dispatched(pActor_shot, dispatch_num, n);
            }
        }
        now_velo *= prm_attenuated;
    }
    return pActor_shot;
}

GgafDx::FigureActor* StgUtil::shotWay001(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    return shotWay001(prm_pFrom->_x, prm_pFrom->_y, prm_pFrom->_z,
                      prm_pFrom->_rz, prm_pFrom->_ry,
                      prm_pDepo_shot,
                      prm_r,
                      prm_velo_first, prm_acce,
                      prm_set_num, prm_interval_frames, prm_attenuated,
                      pFunc_call_back_dispatched);
}

GgafDx::FigureActor* StgUtil::shotWay001(coord prm_from_x, coord prm_from_y, coord prm_from_z,
                                       coord prm_to_x, coord prm_to_y, coord prm_to_z,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int)) {
    angle rz,ry;
    GgafDx::Util::convVectorToRzRy(prm_to_x - prm_from_x,
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

GgafDx::FigureActor* StgUtil::shotWay002(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way_N,
                                       angle prm_ang_clearance_N,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_way_N <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    GgafDx::Util::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_way_N];
    double vx, vy, vz;
    double tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
    for (int i = 0; i < prm_way_N; i++) {
        rz = GgafDx::Util::simplifyAng(paAng_way_N[i]);
        ry = D0ANG;
        GgafDx::Util::convRzRyToVector(rz, ry, vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                       paGeo[i].rz, paGeo[i].ry);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_way_N; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getLocoVehicle()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
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

GgafDx::FigureActor* StgUtil::shotWay002(const GgafDx::GeometricActor* prm_pFrom,
                                                   GgafCore::ActorDepository* prm_pDepo_shot,
                                                   coord prm_r,
                                                   int prm_way_N,
                                                   angle prm_ang_clearance_N,
                                                   velo prm_velo_first, acce prm_acce,
                                                   int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                                   void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
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

GgafDx::FigureActor* StgUtil::shotWay003(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rx, angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int)) {
    if (prm_way_N <= 0 || prm_way_M <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way_N = NEW angle[prm_way_N];
    angle* paAng_way_M = NEW angle[prm_way_M];
    uint32_t* paUint32_dotmat = NEW uint32_t[prm_way_N];
    GgafDx::Util::getWayAngle2D(0, prm_way_N, prm_ang_clearance_N, paAng_way_N);
    GgafDx::Util::getWayAngle2D(0, prm_way_M, prm_ang_clearance_M, paAng_way_M);
    GgafDx::GeoElem** papaGeo = NEW GgafDx::GeoElem*[prm_way_N];
    double vx, vy, vz;
    double tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    angle rz,ry;
    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RxRzRy(prm_rx, prm_rz, prm_ry, matWorldRot);
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
        rz = GgafDx::Util::simplifyAng(paAng_way_N[i]);
        papaGeo[i] = NEW GgafDx::GeoElem[prm_way_M];
        for (int j = 0; j < prm_way_M; j++) {
            if (paUint32_dotmat[i] & UTIL::BITNUM[prm_way_M-j]) {
                ry = GgafDx::Util::simplifyAng(paAng_way_M[j]);
                GgafDx::Util::convRzRyToVector(rz, ry, vx, vy, vz);
                tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
                ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
                tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
                papaGeo[i][j].x = (coord)(tx * prm_r);
                papaGeo[i][j].y = (coord)(ty * prm_r);
                papaGeo[i][j].z = (coord)(tz * prm_r);
                GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                               papaGeo[i][j].rz, papaGeo[i][j].ry);
            }
        }
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
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
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot1->dispatch(n*prm_interval_frames+1);
                        depo_no = 1;
                    } else if (prm_paUint32_dotmat2 && (prm_paUint32_dotmat2[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot2->dispatch(n*prm_interval_frames+1);
                        depo_no = 2;
                    } else if (prm_paUint32_dotmat3 && (prm_paUint32_dotmat3[i] & UTIL::BITNUM[prm_way_M-j])) {
                        pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot3->dispatch(n*prm_interval_frames+1);
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
                    pActor_shot->getLocoVehicle()->setRzRyMvAng(papaGeo[i][j].rz, papaGeo[i][j].ry);
                    pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                    pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
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


GgafDx::FigureActor* StgUtil::shotWay003(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot1, uint32_t* prm_paUint32_dotmat1,
                                       GgafCore::ActorDepository* prm_pDepo_shot2, uint32_t* prm_paUint32_dotmat2,
                                       GgafCore::ActorDepository* prm_pDepo_shot3, uint32_t* prm_paUint32_dotmat3,
                                       coord prm_r,
                                       int prm_way_N, int prm_way_M,
                                       angle prm_ang_clearance_N, angle prm_ang_clearance_M,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int, int, int)) {
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


GgafDx::FigureActor* StgUtil::shotWay004(coord prm_x, coord prm_y, coord prm_z,
                                       angle prm_rz, angle prm_ry,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_radial_way_num, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
    if (prm_radial_way_num <= 0 || prm_set_num <= 0) {  return nullptr;  }
    angle* paAng_way = NEW angle[prm_radial_way_num];
    GgafDx::Util::getRadialAngle2D(0, prm_radial_way_num, paAng_way);
    GgafDx::GeoElem* paGeo = NEW GgafDx::GeoElem[prm_radial_way_num];
    angle expanse_rz = (D180ANG - prm_expanse_angle)/2;

    D3DXMATRIX matWorldRot;
    GgafDx::Util::setWorldMatrix_RzRy(GgafDx::Util::simplifyAng(prm_rz-D90ANG), prm_ry, matWorldRot);

    double vx, vy, vz;
    double tx, ty, tz; //�ŏI�����̐�΍��W�̒P�ʃx�N�g��
    for (int i = 0; i < prm_radial_way_num; i++) {
        GgafDx::Util::convRzRyToVector(expanse_rz, paAng_way[i], vx, vy, vz);
        tx = vx*matWorldRot._11 + vy*matWorldRot._21 + vz*matWorldRot._31;
        ty = vx*matWorldRot._12 + vy*matWorldRot._22 + vz*matWorldRot._32;
        tz = vx*matWorldRot._13 + vy*matWorldRot._23 + vz*matWorldRot._33;
        paGeo[i].x = (coord)(tx * prm_r);
        paGeo[i].y = (coord)(ty * prm_r);
        paGeo[i].z = (coord)(tz * prm_r);
        GgafDx::Util::convVectorToRzRy(tx, ty, tz,
                                       paGeo[i].rz, paGeo[i].ry);
    }
    GgafDx::FigureActor* pActor_shot = nullptr;
    velo now_velo = prm_velo_first;
    acce now_acce = prm_acce;
    int dispatch_num = 0;
    for (int n = 0; n < prm_set_num; n++) {
        for (int i = 0; i < prm_radial_way_num; i++) {
            pActor_shot = (GgafDx::FigureActor*)prm_pDepo_shot->dispatch(n*prm_interval_frames+1);
            if (pActor_shot) {
                dispatch_num++;
                pActor_shot->setPosition(prm_x + paGeo[i].x,
                                         prm_y + paGeo[i].y,
                                         prm_z + paGeo[i].z);
                pActor_shot->getLocoVehicle()->setRzRyMvAng(paGeo[i].rz, paGeo[i].ry);
                pActor_shot->getLocoVehicle()->setMvVelo(now_velo);
                pActor_shot->getLocoVehicle()->setMvAcce(now_acce);
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

GgafDx::FigureActor* StgUtil::shotWay004(const GgafDx::GeometricActor* prm_pFrom,
                                       GgafCore::ActorDepository* prm_pDepo_shot,
                                       coord prm_r,
                                       int prm_way, angle prm_expanse_angle,
                                       velo prm_velo_first, acce prm_acce,
                                       int prm_set_num, frame prm_interval_frames, float prm_attenuated,
                                       void (*pFunc_call_back_dispatched)(GgafDx::FigureActor*, int, int, int)) {
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


//�_AB��ʂ钼���Ɠ_D�̋���
//�_ A(a,b,c) B(d,e,f) ��ʂ钼����
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
//�Ȃ񂶂Ⴑ��E�E�E


// ���ƃs���~�b�h�i�ΖʂƂ̋����Ŕ��肷��͈́j
//    (1) (a, b, c) �����ʂ̖@���x�N�g���ł��B
//
//    (2) |d|/|(a, b, c)| �� "���ʂƌ��_�̋���" �ɂȂ�܂��B�܂�A���_���畽�ʂɐ������~�낵�����́A�����̒����ł��B
//    �@�A���A|(a, b, c)| = ��(a^2+b^2+c^2) (�@���x�N�g���̒���) �ł��B
//    �@�@���x�N�g�� (a,b,c) �����ɋK�i������Ă���ꍇ (|(a,b,c)|=1 �̏ꍇ) �́A�P�� |d| �� "���ʂƌ��_�̋���" �ł��B
//
//    (3) d �̕����́A���_�����ʂ̕\���ɂ��邩�����ɂ��邩�ɑΉ����Ă��܂��B
//    �@d �����̎��́A���_�͕��ʂ̕\��(���ʂ��猩�Ė@���x�N�g���̕���)�ɂ���܂��B
//    �@d �����̎��́A���_�͕��ʂ̗���(�@���x�N�g���Ƌt�̕���)�ɂ���܂��B
//    a��=(ax,ay,az),
//    b��=(bx,by,bz)
//
//    ����
//    ����-1�j�F�X�J���[�l |a��||b��|cos�� �̂���
//    �i����-2�j�F�X�J���[�l ax bx + ay by + az bz �̂��ƁB
//
//    �O��
//    ������ |a��||b��|sin�� �� a�� �� b�� �ɐ����ȃx�N�g���̂���
//    �i�O��-2�j�F(ay bz - az by, az bx - ax bz, ax by - ay bx)�Ƃ��������ŕ\�����x�N�g���̂��ƁB
//
//
//    ���_�ɎO���p���_�������AA(ex,0,0), B(0,ey,0), C(0,0,ez) �̎O���p�O�p�����l�� (ex>0, ey>0, ez>0)
//    �Ζʂ��ʂƂ����O�p���i���������j�͈̔͂��l����
//
//    �Ζʂ̕�����
//    AB�� = (-ex, ey, 0 )
//    AC�� = (-ex, 0 , ez)
//    AB����AC�� = (a,b,c)
//
//    a = ey*ez
//    b = ex*ez
//    c = ey*ex
//
//    ey ez x + ex ez y + ey ex z + d = 0
//    ���ꂪ�AA(ex,0,0)���Ƃ���̂ŁA
//
//    d = -ex*ey*ez
//
//    �Ζʂ̕�����
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez = 0
//    �@�� (ey*ez, ex*ez, ey*ex)
//
//    ----------------------------------------------------------
//    A(ex,0,0), B(0,ey,0) ���܂ގΖʂɐ����Ȗʂ����߂�
//
//    ���߂�ʂ�
//    va*x + vb*y + vc*z + vd = 0 �Ƃ���
//    ---------------------------------
//    ���O�ςŋ��߂遄
//
//    ���߂�ʂ̖@����(va, vb, vc)
//    ���߂�ʂ̖@���� (ey*ez, ex*ez, ey*ex)�ɐ����ł��AAB��(-ex, ey, 0 )�Ƃ������Ȃ̂�
//    (ey*ez, ex*ez, ey*ex) �� (-ex, ey, 0 ) = (va, vb, vc)
//
//    (va, vb, vc) =
//    ( - (ey*ex)* ey, (ey*ex)*(-ex) , (ey*ez)*ey - (ex*ez)*(-ex))
//    ( -ex*ey^2, -ex^2*ey , (ey^2+ex^2)*ez)
//
//    -------------
//
//    �����ς�0�ŋ��߂遄
//
//    ���߂�ʂ̖@���� (ey*ez, ex*ez, ey*ex)�ɐ����Ȃ̂�
//    (ey*ez, ex*ez, ey*ex)�E(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        �E�E�E�@
//
//    ���߂�ʂ̖@����AB��(-ex, ey, 0 )�Ƃ������Ȃ̂�
//    (-ex, ey, 0 )�E(va, vb, vc) = 0
//    -ex*va + ey*vb = 0 �E�E�E�A
//
//    ������ �@���x�N�g��(va, vb, vc) z���� vc=1 �iz�����@���͂����Ƃ����̂��}���킩�����̂Łj�Ƃ����
//
//    ey*ez*va + ex*ez*vb + ey*ex = 0  �E�E�E�@�f
//    -ex*va + ey*vb = 0               �E�E�E�A
//
//    va=(ey*vb)/ex ���@�f��
//
//    ey*ez*((ey*vb)/ex) + ex*ez*vb + ey*ex = 0
//
//    vb=-(ex^2*ey)/((ey^2+ex^2)*ez)
//    �A�֑��
//
//    -ex*va + ey*(-(ex^2*ey)/((ey^2+ex^2)*ez)) = 0
//    va=-(ex*ey^2)/((ey^2+ex^2)*ez)
//
//    ����Ė@��(va, vb, vc) =
//     (-(ex*ey^2)/((ey^2+ex^2)*ez), -(ex^2*ey)/((ey^2+ex^2)*ez), 1)
//
//    ((ey^2+ex^2)*ez)���|���Đ���
//    (-ex*ey^2, -ex^2*ey, (ey^2+ex^2)*ez)
//
//
//    -----------------------------------------------------
//
//    (-ex*ey^2)*x + (-ex^2*ey)*y + ((ey^2+ex^2)*ez)*z + vd = 0
//    �� A(ex,0,0) ��ʂ�̂�
//    (-ex*ey^2)*ex + vd = 0
//    vd=ex^2*ey^2
//
//    ����ċ��߂������ʂ�
//    (-ex*ey^2)*x + (-ex^2*ey)*y + ((ey^2+ex^2)*ez)*z + (ex^2*ey^2) = 0
//

//    ���l�ɂ��āA
//
//    B(0,ey,0) C(0,0,ez) ���܂ގΖʂɐ����Ȗʂ����߂�
//
//    ���߂�ʂ�
//    va*x + vb*y + vc*z + vd = 0 �Ƃ���
//
//    ���߂�ʂ̖@���� (ey*ez, ex*ez, ey*ex)�ɐ����Ȃ̂�
//    (ey*ez, ex*ez, ey*ex)�E(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        �E�E�E�@
//
//
//    ���߂�ʂ̖@����BC��(0, -ey, ez)�Ƃ������Ȃ̂�
//    (0, -ey, ez)�E(va, vb, vc) = 0
//    -ey*vb + ez*vc = 0 �E�E�E�A
//
//    ������ �@���x�N�g��(va, vb, vc) x���� va=1 �ix�����@���͐��Ƃ����̂��}���킩�����̂Łj�Ƃ����
//
//    ey*ez + ex*ez*vb + ey*ex*vc = 0     �E�E�E�@�f
//    -ey*vb + ez*vc = 0                  �E�E�E�A�f
//
//    vb=(ez*vc)/ey �� �@�f�֑��
//
//    ey*ez + ex*ez*((ez*vc)/ey) + ey*ex*vc = 0
//
//    vc=-(ey^2*ez)/(ex*ez^2+ex*ey^2)
//    �A�f�֑��
//    -ey*vb + ez*(-(ey^2*ez)/(ex*ez^2+ex*ey^2)) = 0
//
//    vb=-(ey*ez^2)/(ex*ez^2+ex*ey^2)
//
//    ����Ė@��(va, vb, vc) =
//    (1, -(ey*ez^2)/(ex*ez^2+ex*ey^2), -(ey^2*ez)/(ex*ez^2+ex*ey^2))
//
//    (ex*ez^2+ex*ey^2) ���|���Đ���
//
//    (ex*(ez^2+ey^2), -ey*ez^2, -ey^2*ez)
//    -----------------------------------------------------
//
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (-ey^2*ez)*z + vd = 0
//    ��B(0,ey,0) ��ʂ�̂ŁA
//    (-ey*ez^2)*ey + vd = 0
//    vd=ey^2*ez^2
//
//    ����ċ��߂������ʂ�
//
//    (ex*(ez^2+ey^2))*x + (-ey*ez^2)*y + (-ey^2*ez)*z + (ey^2*ez^2) = 0


//    ���l�ɂ���
//    C(0,0,ez) A(ex,0,0) ���܂ގΖʂɐ����Ȗʂ����߂�
//
//    ���߂�ʂ�
//    va*x + vb*y + vc*z + vd = 0 �Ƃ���
//
//    ���߂�ʂ̖@���� (ey*ez, ex*ez, ey*ex)�ɐ����Ȃ̂�
//    (ey*ez, ex*ez, ey*ex)�E(va, vb, vc) = 0
//    ey*ez*va + ex*ez*vb + ey*ex*vc = 0        �E�E�E�@
//
//    ���߂�ʂ̖@����CA��(ex, 0, -ez)�Ƃ������Ȃ̂�
//    (ex, 0, -ez)�E(va, vb, vc) = 0
//    ex*va - ez*vc = 0 �E�E�E�A
//
//    ������ �@���x�N�g��(va, vb, vc) y���� vb=1 �iy�����@���͐��Ƃ����̂��}���킩�����̂Łj�Ƃ����
//
//    ey*ez*va + ex*ez + ey*ex*vc = 0        �E�E�E�@�f
//    ex*va - ez*vc = 0                      �E�E�E�A
//
//    va=(ez*vc)/ex  ���@�f�֑��
//
//    ey*ez*((ez*vc)/ex) + ex*ez + ey*ex*vc = 0
//    vc=-(ex^2*ez)/(ey*ez^2+ex^2*ey)
//    �A�֑��
//    ex*va - ez*(-(ex^2*ez)/(ey*ez^2+ex^2*ey)) = 0
//    va=-(ex*ez^2)/(ey*ez^2+ex^2*ey)
//
//
//    ����Ė@��(va, vb, vc) =
//    (-(ex*ez^2)/(ey*ez^2+ex^2*ey), 1, -(ex^2*ez)/(ey*ez^2+ex^2*ey))
//
//    (ey*ez^2+ex^2*ey) ���|���Đ���
//
//    (-ex*ez^2, ey*(ez^2+ex^2), -ex^2*ez)
//
//    -----------------------------------------------------
//    (-ex*ez^2)*x + (ey*(ez^2+ex^2))*y + (-ex^2*ez)*z + vd = 0
//    �� C(0,0,ez) ��ʂ�̂ŁA
//    (-ex^2*ez)*ez + vd = 0
//    vd=ex^2*ez^2
//
//    ����ċ��߂������ʂ�
//
//    (-ex*ez^2)*x + (ey*(ez^2+ex^2))*y + (-ex^2*ez)*z + ex^2*ez^2 = 0
//   ����ĎΖʂ��ʂƂ����O�p���i���������j�͈̔͂�
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez > 0      �Ζ�
//    (-ex*ey^2)*x       + (-ex^2*ey)*y       + (ez*(ex^2+ey^2))*z + (ex^2*ey^2) > 0
//    (ex*(ey^2+ez^2))*x + (-ey*ez^2)*y       + (ey^2*ez)*z        + (ey^2*ez^2) > 0
//    (-ez^2*ex)*x       + (ey*(ez^2+ex^2))*y + (-ez*ex^2)*z       + (ez^2*ex^2) > 0

//���ƃs���~�b�h�u���_�ƕӂ̋��E�ʁv
//    �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
//        ���_�ɎO���p���_�������AA(ex,0,0), B(0,ey,0), C(0,0,ez) �̎O���p�O�p�����l�� (ex>0, ey>0, ez>0)
//        A(ex,0,0), B(0,ey,0) ���܂�xy���ʂɐ����Ȗʂ����߂�
//        ���߂�ʂ�
//        va*x + vb*y + vc*z + vd = 0 �Ƃ���
//
//        �@��(va, vb, vc) = (-ey, -ex, 0)  �Ȃ̂�
//        -ey*x -ex*y + vd = 0   �ƂȂ�A���ꂪA(ex,0,0)��ʂ�̂�
//        -ey*ex + vd = 0
//        vd = ex*ey
//
//        ����ċ��߂�ʂ�
//        -ey*x - ex*y + ex*ey = 0
//
//    -----------
//        B(0,ey,0), C(0,0,ez) ���܂�yz���ʂɐ����Ȗʂ����߂�
//        va*x + vb*y + vc*z + vd = 0 �Ƃ���
//
//        �@��(va, vb, vc) = (0, -ez, -ey)  �Ȃ̂�
//        -ez*y - ey*z + vd = 0   �ƂȂ�A���ꂪB(0,ey,0)��ʂ�̂�
//        -ez*ey + vd = 0
//        vd = ey*ez
//
//        ����ċ��߂�ʂ�
//        -ez*y - ey*z + ey*ez = 0
//
//    ------------------------
//        C(0,0,ez), A(ex,0,0) ���܂�zx���ʂɐ����Ȗʂ����߂�
//        va*x + vb*y + vc*z + vd = 0 �Ƃ���
//
//        �@��(va, vb, vc) = (-ez, 0, -ex)  �Ȃ̂�
//        -ez*x - ex*z + vd = 0 �ƂȂ�A���ꂪC(0,0,ez)��ʂ�̂�
//        -ex*ez + vd = 0
//        vd=ez*ex
//
//        ����ċ��߂�ʂ�
//       -ez*x - ex*z + ez*ex = 0
//    ------------------------

//�O�σ���
//     a��=(ax,ay,az),
//     b��=(bx,by,bz)
//    (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)

//    A(ex,0,0), B(0,ey,0), C(0,0,ez)
//
//    ���_B�ƕ�BA�̋��E�ʁ�
//    �Ζʂ̕�����
//    (ey*ez)*x + (ex*ez)*y + (ey*ex)*z - ex*ey*ez = 0
//    ���A
//
//    B(0,ey,0)��ʂ�Ζʖ@�� (ey*ez, ex*ez, ey*ex) �ɕ��s�Ȑ��ł���̂ŁA
//    (x,y,z) = (0,ey,0) + t(ey*ez, ex*ez, ey*ex)  �E�E�E�@
//
//    A(ex,0,0)��ʂ��zx �ɕ��s�ȁi���E�́j�����̂P��
//    (x,y,z) = (0,ey,0) + t(0, 0, -1)  �E�E�E�A
//
//    �@�A���܂ޖʂ����߂�
//    ���̖ʂ̖@����(a,b,c) �Ƃ����
//    �O�ς͐������
//    (ey*ez, ex*ez, ey*ex)��(0, 0, -1) = (-ex*ez, ey*ez, 0)
//
//    -ex*ez * x + ey*ez * y + d = 0
//    ���ꂪ�_B(0,ey,0)��ʂ�̂�
//    d = -ey^2*ez
//
//    ���߂�ʂ�
//    -ex*ez * x + ey*ez * y - ey^2*ez = 0    �E�E�E�_B�ƕ�BA�̋��E��
//    ------------------------------------------------
//    ���_B�ƕ�BC�̋��E�ʁ�
//    (x,y,z) = (ex,0,0) + t(ey*ez, ex*ez, ey*ex)  �E�E�E�@
//    B(0,ey,0)��ʂ��zx �ɕ��s�ȁi���E�́j�����̂Q��
//    (x,y,z) = (ex,0,0) + t(-1, 0, 0)  �E�E�E�A
//    �@�A���܂ޖʂ����߂�
//    ���̖ʂ̖@����(a,b,c) �Ƃ����
//    �O�ς͐������
//    (-1, 0, 0)��(ey*ez, ex*ez, ey*ex) = (0, ey*ex, -ex*ez)
//
//    ey*ex * y - ex*ez * z + d = 0
//
//    ���ꂪ�_B(0,ey,0)��ʂ�̂�
//    d = -ey^2*ex
//
//    ���߂�ʂ�
//    ey*ex * y - ex*ez * z - ey^2*ex = 0   �E�E�E�_B�ƕ�BC�̋��E��
//
//
//    ------------------------------------------------
//    ���_A�ƕ�AB�̋��E�ʁ�
//    �O�ς͐�����肱�̖ʂ̖@���x�N�g����
//    (0, 0, -1)��(ey*ez, ex*ez, ey*ex) =  (ex*ez, -ey*ez, 0)
//
//    ex*ez * x - ey*ez * y + d = 0
//    ���ꂪ�_A(ex,0,0)��ʂ�̂�
//    d = -ex^2*ez
//
//    ���߂�ʂ�
//    ex*ez * x - ey*ez * y - ex^2*ez = 0   �E�E�E�_A�ƕ�AB�̋��E��
//    ------------------------------------------------
//    ���_A�ƕ�AC�̋��E�ʁ�
//    �O�ς͐�����肱�̖ʂ̖@���x�N�g����
//    (ey*ez, ex*ez, ey*ex)��(0, -1, 0) = (ey*ex, 0, -ey*ez)
//
//    ey*ex * x - ey*ez * z + d = 0
//    ���ꂪ�_A(ex,0,0)��ʂ�̂�
//    d = -ey*ex^2
//
//    ���߂�ʂ�
//    ey*ex * x - ey*ez * z - ey*ex^2 = 0   �E�E�E�_A�ƕ�AC�̋��E��
//
//
//    ------------------------------------------------
//    ���_C�ƕ�CA�̋��E�ʁ�
//    �O�ς͐�����肱�̖ʂ̖@���x�N�g����
//    (0, -1, 0)��(ey*ez, ex*ez, ey*ex) = (-ey*ex, 0, ey*ez)
//    -ey*ex * x + ey*ez * z + d = 0
//    ���ꂪ�_ C(0,0,ez) ��ʂ�̂�
//    d = -ey*ez^2
//    ���߂�ʂ�
//    -ey*ex * x + ey*ez * z -ey*ez^2 = 0  �E�E�E�_C�ƕ�CA�̋��E��
//    ------------------------------------------------
//    ���_C�ƕ�CB�̋��E�ʁ�
//    �O�ς͐�����肱�̖ʂ̖@���x�N�g����
//    (ey*ez, ex*ez, ey*ex)��(-1, 0, 0) = (0, -ey*ex, ex*ez)
//    -ey*ex * y + ex*ez * z + d = 0
//    ���ꂪ�_ C(0,0,ez) ��ʂ�̂�
//    d = -ex*ez^2
//    ���߂�ʂ�
//    -ey*ex * y + ex*ez * z - ex*ez^2 = 0    �E�E�E�_C�ƕ�CB�̋��E��
//
//    ex*ez * x - ey*ez * y             - ex^2*ez = 0   �E�E�E�_A�ƕ�AB�̋��E��
//    ey*ex * x             - ey*ez * z - ey*ex^2 = 0   �E�E�E�_A�ƕ�AC�̋��E��
//
//   -ex*ez * x + ey*ez * y             - ey^2*ez = 0    �E�E�E�_B�ƕ�BA�̋��E��
//                ey*ex * y - ex*ez * z - ey^2*ex = 0    �E�E�E�_B�ƕ�BC�̋��E��
//
//   -ey*ex * x             + ey*ez * z - ey*ez^2 = 0    �E�E�E�_C�ƕ�CA�̋��E��
//               -ey*ex * y + ex*ez * z - ex*ez^2 = 0    �E�E�E�_C�ƕ�CB�̋��E��
