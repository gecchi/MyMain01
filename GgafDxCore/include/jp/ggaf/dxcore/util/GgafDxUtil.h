#ifndef GGAFDXUTIL_H_
#define GGAFDXUTIL_H_
namespace GgafDxCore {


/**
 * ���[�e�B���e�B�N���X .
 * �ÓI�ȍ��W�v�Z�֘A�֐��̓R�R�ɏW�񂵂Ă������B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class GgafDxUtil: public GgafCore::GgafUtil {

    struct AngleSet {
        angle RZ[D360SANG+1];
        angle RY[D360SANG+1];
    };

public:

    static float PARABORA[];
    /**
     * cos�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ D360SANG
     * angle�l r �� cos�́ACOS[r/SANG_RATE]
     */
    static float COS[];
    /**
     * sin�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ D360SANG
     * angle�l r �� sin �́ASIN[r/SANG_RATE]
     */
    static float SIN[];
    /**
     * �ʓx�@�ϊ��e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ D360SANG
     * angle�l r �̃��f�B�A���́ARAD[r/SANG_RATE]
     */
    static float RAD[];
    /**
     * [�X��] �� angle�l�ϊ��e�[�u��
     * �v�f�ԍ��͈́F���� y = ax �X�� a �� 10000 �{�̐������x���v�f�ԍ��ƂȂ�B
     * ���� y = ax �̐����p�̃A���O���l�� SLANT2ANG[(int)a*10000] �ƂȂ�B
     */
    static angle SLANT2ANG[];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����1-1) .
     * �����x�N�g�����A[XY���ʂ֎ˉe�������̂Ȃ��p][XZ���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Z����]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_Z[D90SANG+1][D90SANG+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����1-2) .
     * �����x�N�g�����A[XY���ʂ֎ˉe�������̂Ȃ��p][XZ���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Y��(�t)��]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_XY_XZ_TO_ROTANG_Y_REV[D90SANG+1][D90SANG+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����2-1) .
     * �����x�N�g�����A[ZY���ʂ֎ˉe�������̂Ȃ��p][ZX���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����X��(�t)��]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_X_REV[D90SANG+1][D90SANG+1];
    /**
     * ���ʎˉe���ɂł���Ȃ��p �� 2���̉�]�p  �̕ϊ��e�[�u��(����2-2) .
     * �����x�N�g�����A[ZY���ʂ֎ˉe�������̂Ȃ��p][ZX���ʂ֎ˉe�������̂Ȃ��p] �� ���̕����x�N�g����Y����]�p �̕ϊ��e�[�u��
     */
    static angle PROJANG_ZY_ZX_TO_ROTANG_Y[D90SANG+1][D90SANG+1];


//    static MoveWay Against[2^(6+8)+];
    //static AngleSet ROTY_ANGLE[D360SANG+1];


    /**
     * ���a 1000 �� 1/4 �~�̉��e�[�u�� .
     *      ______________
     * y = ��(1000^2-x^2)
     * �� �v�f[x] �ɑ΂��� y
     */
    static float ROOT_1_MINUS_XX[1000];


    static GgafDxSphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static void init();

    /**
     * ���ʏ�̃x�N�g��(vx, vy) ����錴�_�̂Ȃ��p��Ԃ� .
     * @param prm_vx �x�N�g�� x �v�f
     * @param prm_vy �x�N�g�� y �v�f
     * @return �Ȃ��p�̃A���O���l (0 �` 360000)
     */
    template<typename T>
    static angle getAngle2D(T prm_vx, T prm_vy) {
        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return D90ANG;
            } else if (prm_vy < 0) {
                return D270ANG;
            } else {
                //���_�ł���A�s��B
                return 0;
            }
        }
        if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return D180ANG;
            } else {
                //���_�ł���A�s��B
                return 0;
            }
        }
        if (prm_vx >= 0 && prm_vy >= 0) { //��1�ی�
            if (prm_vx >= prm_vy) {
                return D0ANG  + SLANT2ANG[(int)(1.0*prm_vy/prm_vx*100000)];
            } else {
                return D90ANG - SLANT2ANG[(int)(1.0*prm_vx/prm_vy*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //��2�ی�
            if (-prm_vx <= prm_vy) {
                return D90ANG + SLANT2ANG[(int)(1.0*-prm_vx/prm_vy*100000)];
            } else {
                return D180ANG - SLANT2ANG[(int)(1.0*prm_vy/-prm_vx*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //��3�ی�
            if (-prm_vx >= -prm_vy) {
                return D180ANG + SLANT2ANG[(int)(1.0*-prm_vy/-prm_vx*100000)];
            } else {
                return D270ANG - SLANT2ANG[(int)(1.0*-prm_vx/-prm_vy*100000)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //��4�ی�
            if (prm_vx <= -prm_vy) {
                return D270ANG + SLANT2ANG[(int)(1.0*prm_vx/-prm_vy*100000)];
            } else {
                return D360ANG - SLANT2ANG[(int)(1.0*-prm_vy/prm_vx*100000)];
            }
        }
        return 0;
    }

    /**
     * �A���O���l�̍������ .
     * TURN_COUNTERCLOCKWISE �E�E�E ��]�����������ō��يp�擾�A���̒l�ŕԂ�B<BR>
     * TURN_CLOCKWISE        �E�E�E ��]�������E���ō��يp�擾�A���̒l�ŕԂ�B<BR>
     * TURN_CLOSE_TO         �E�E�E �^�[�Q�b�g�̉�]�p�Ƌ������߂����̉�]�����Ŏ擾�A�����͕��̒l�ɂȂ�B<BR>
     * @param angFrom
     * @param angTo
     * @param prm_way TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE/TURN_CLOSE_TO
     * @return �A���O���l�̍��i���ʂ� �����v����͐��A���v���͕�)
     */
    static angle getAngDiff(angle angFrom, angle angTo, int prm_way=TURN_CLOSE_TO);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̎ˏo�A���O���l���Z�b�g(�z��)�Ŏ擾 .
     * @param prm_vx_Center     [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��X�v�f
     * @param prm_vy_Center     [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��Y�v�f
     * @param prm_nWay	        [in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	    [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_nWay,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̎ˏo�A���O���l���Z�b�g(�z��)�Ŏ擾 .
     * @param prm_angCenter	    [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������̃A���O���l
     * @param prm_nWay	        [in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	    [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle);

    /**
     * ���ʏ�ɂ����āA���ˏ�S������'N'way�e(N=����)�̃A���O���l��z��Ŏ擾 .
     * �e�ƒe�Ƃ̐����p�� �ϓ��ɂȂ邱�ƂƂ���B
     * �Ⴆ�ΑS����4way�e�̏ꍇ�A�e�ƒe�Ƃ̐����p�͒��p(90000)�ɂȂ�B
     * @param prm_angStart  ���ˏ�̑S����'N'way�e�̂P�ڂ̒e�̃A���O���l
     * @param prm_nWay  [in] 'N'way�e�� N�B
     * @param out_paAngle   [out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle);

    static void convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz);

//    static void getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                           int prm_nWay, angle prm_angClearance,
//                                           angle* out_paAngleRz, angle* out_paAngleRy);

//    static void getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tX, coord prm_tY, coord prm_tZ,
//                                        angle& out_angFaceZ, angle* out_paAngRotY);


    /**
     *
     * @param prm_angNow
     * @param prm_angOffset
     * @return
     */
    static angle addAng(angle prm_angNow, angle prm_angOffset);

    /**
     *
     * @param prm_X
     * @param prm_Y
     * @param prm_ang
     * @param out_X
     * @param out_Y
     */
    static void rotXY(coord prm_X, coord prm_Y, angle prm_ang, coord& out_X, coord& out_Y);

    /**
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(coord x1, coord y1, coord x2, coord y2);

    /**
     * �����v�Z .
     * @param x1
     * @param y1
     * @param z1
     * @param x2
     * @param y2
     * @param z2
     * @return
     */
    template<typename T>
    static T getDistance(T x1, T y1, T z1, T x2, T y2, T z2) {
        return (T)( sqrt(
                      (
                        ((double)(x2 - x1)) * ((double)(x2 - x1))
                      ) + (
                        ((double)(y2 - y1)) * ((double)(y2 - y1))
                      ) + (
                        ((double)(z2 - z1)) * ((double)(z2 - z1))
                      )
                    )
                 );
    }


    static double getDistance(GgafDxCore::GgafDxGeometricActor* pA1, GgafDxCore::GgafDxGeometricActor* pA2) {
        return sqrt(
                      (
                        ((double)(pA2->_X - pA1->_X)) * ((double)(pA2->_X - pA1->_X))
                      ) + (
                        ((double)(pA2->_Y - pA1->_Y)) * ((double)(pA2->_Y - pA1->_Y))
                      ) + (
                        ((double)(pA2->_Z - pA1->_Z)) * ((double)(pA2->_Z - pA1->_Z))
                      )
                    );
    }


    /**
     * ���_����p�����[�^���W�����������x�N�g���́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * ���܂��ŒP�ʕ����x�N�g�����Q�b�g�ł���B<BR>
     * Z����]�A���O���l��Y����]�A���O���l���擾����ߒ��ŁA<BR>
     * �����x�N�g���̐��K�����s�Ȃ�Ȃ���΂Ȃ�Ȃ����߁A���������Ȃ��̂Ŗ߂�l�ɁB<BR>
     * @param x [in]X���W
     * @param y [in]Y���W
     * @param z [in]Z���W
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     * @param out_angFaceZ [out]Z����]�A���O���l
     * @param out_angFaceY [out]Y����]�A���O���l
     */
    static void getRzRyAng(coord x,
                           coord y,
                           coord z,
                           float& out_nvx,
                           float& out_nvy,
                           float& out_nvz,
                           angle& out_angFaceZ,
                           angle& out_angFaceY);

    /**
     * ���_����p�����[�^���W�����������x�N�g���ɑΉ�����uZ����]�̃A���O���l�v�ƁuY����]�̃A���O���l�v���擾 .
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h���̂P<BR>
     * �����x�N�g�� -> Z��Y����]���p �̕ϊ�<BR>
     * @param x [in]X���W
     * @param y [in]Y���W
     * @param z [in]Z���W
     * @param out_angFaceZ [out]Z����]�A���O���l
     * @param out_angFaceY [out]Y����]�A���O���l
     */
    static void getRzRyAng(coord x, coord y, coord z, angle& out_angFaceZ, angle& out_angFaceY);

    /**
     * ���_����p�����[�^���W�����������x�N�g��(�P�ʃx�N�g��)�ɑΉ�����uZ����]�̃A���O���l�v�ƁuY����]�̃A���O���l�v���擾 .
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h���̂P<BR>
     * �����x�N�g�� -> Z��Y����]���p �̕ϊ��B<BR>
     * �v�Z�����Ƀe�[�u���Q�Ƃō����ɍs���B<BR>
     * �������ŁA�����x�N�g���̐��K�����s��Ȃ��̂� <BR>
     * getRzRyAng(int, int, int , angle&, angle&);
     * ����⍂���B�P�ʃx�N�g�������܂��Ă���Ƃ��͂�������g�p���܂��傤�B<BR>
     * @param nvx [in]�P�ʃx�N�g��X�v�f
     * @param nvy [in]�P�ʃx�N�g��Y�v�f
     * @param nvz [in]�P�ʃx�N�g��Z�v�f
     * @param out_angFaceZ [out]Z����]�A���O���l
     * @param out_angFaceY [out]Y����]�A���O���l
     */
    static void getRzRyAng(double nvx, double nvy, double nvz, angle& out_angFaceZ, angle& out_angFaceY) {
        getRzRyAng((int)(nvx*LEN_UNIT*PX_UNIT),
                   (int)(nvy*LEN_UNIT*PX_UNIT),
                   (int)(nvz*LEN_UNIT*PX_UNIT),
                   out_angFaceZ,
                   out_angFaceY );
    }

    static void getRzRyAng(float nvx, float nvy, float nvz, angle& out_angFaceZ, angle& out_angFaceY) {
        getRzRyAng((int)(nvx*LEN_UNIT*PX_UNIT),
                   (int)(nvy*LEN_UNIT*PX_UNIT),
                   (int)(nvz*LEN_UNIT*PX_UNIT),
                   out_angFaceZ,
                   out_angFaceY );


    }


    /**
     * Z����]+Y����]�l����P�ʕ����x�N�g�����擾
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h����2<BR>
     * Z��Y����]���p -> �����x�N�g�� �̕ϊ�<BR>
     * �v�Z�����Ƀe�[�u���Q�Ƃō����ɍs���B<BR>
     * @param prm_angFaceZ [in]Z����]�A���O���l
     * @param prm_angFaceY [in]Y����]�A���O���l
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     */
    static void getNormalizeVectorZY(angle prm_angFaceZ,
                                     angle prm_angFaceY,
                                     float& out_nvx,
                                     float& out_nvy,
                                     float& out_nvz);

    static void getNormalizeVector(coord x,
                                   coord y,
                                   coord z,
                                   float& out_nvx,
                                   float& out_nvy,
                                   float& out_nvz);

    /**
     * ������ς����AZ����]+Y����]������̑g�ݍ��킹��Ԃ��B
     * @param rz1
     * @param ry1
     */
    static void anotherRzRy(angle& rz1, angle& ry1) {
        int rz2 = 0;
        int ry2 = 0;
        if (0 <= rz1 && rz1 < D90ANG) {
            rz2 = D180ANG - rz1;

            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D90ANG <= rz1 && rz1 < D180ANG) {
            rz2 = D180ANG - rz1;
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D180ANG <= rz1 && rz1 < D270ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D270ANG <= rz1 && rz1 <= D360ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
    }

    /**
     * RzRy�̍œK�������݂�B
     * ������ς����AZ����]+Y����]������̑g�ݍ��킹�Ɣ�r���B
     * @param rz1
     * @param ry1
     */
    static void optimizeRzRy(angle& rz1, angle& ry1) {
        int rz2 = 0;
        int ry2 = 0;
        if (0 <= rz1 && rz1 < D90ANG) {
            rz2 = D180ANG - rz1;

            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D90ANG <= rz1 && rz1 < D180ANG) {
            rz2 = D180ANG - rz1;
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D180ANG <= rz1 && rz1 < D270ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        } else if (D270ANG <= rz1 && rz1 <= D360ANG) {
            rz2 = D180ANG + (D360ANG - rz1);
            if (0 <= ry1 && ry1 < D180ANG) {
                ry2 = ry1 + D180ANG;
            } else {
                ry2 = ry1 - D180ANG;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
    }


    static angle simplifyAng(angle prm_ang) {
        angle angSimple = prm_ang;
        while (angSimple >= D360ANG) {
            angSimple -= D360ANG;
        }
        while (angSimple < 0) {
            angSimple += D360ANG;
        }
        return angSimple;
    }



    /**
     * �����̓����蔻��<BR>
     * @param x11
     * @param y11
     * @param x12
     * @param y12
     * @param x21
     * @param y21
     * @param x22
     * @param y22
     * @return true:�q�b�g/false:�q�b�g���ĂȂ�
     */
    static bool chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22);



    /**
     * world�ϊ��s��ݒ� .
     * �g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_RxRzRy(angle prm_RX, angle prm_RZ, angle prm_RY, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzRy(angle prm_Rz, angle prm_Ry, D3DXMATRIX& out_matWorld);


    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRyRzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��Y����]������܂���B_RY�͂Q��ڂ�X����]�ƂȂ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRxScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �r���{�[�hX����] �~ �r���{�[�hY����] �~ �r���{�[�hZ����]  �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ� <BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_BxyzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);

    static void mulWorldMatrix_RzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);

    static void setWorldMatrix_RxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    static void setWorldMatrix_ScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

};

}
#endif /*GGAFDXUTIL_H_*/

