#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
namespace GgafDx9Core {

#define sgn(X) (GgafDx9Core::GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Core::GgafDx9Util::max3(A,B,C))

/**
 * ���[�e�B���e�B�N���X .
 * �ÓI�ȍ��W�v�Z�֘A�֐��̓R�R�ɏW�񂵂Ă������B
 */
class GgafDx9Util: public GgafCore::GgafUtil {

    struct AngleSet {
        angle RZ[S_ANG360+1];
        angle RY[S_ANG360+1];
    };

public:

    static float PARABORA[];
    /**
     * cos�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ S_ANG360
     * angle�l r �� cos�́ACOS_UNITLEN[r/ANGLE_RATE]
     */
    static float COS[];
    /**
     * sin�e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ S_ANG360
     * angle�l r �� sin �́ASIN_UNITLEN[r/ANGLE_RATE]
     */
    static float SIN[];
    /**
     * �ʓx�@�ϊ��e�[�u�� .
     * �v�f�ԍ��͈́F0 ~ S_ANG360
     * angle�l r �̃��f�B�A���́ARAD_UNITLEN[r/ANGLE_RATE]
     */
    static float RAD[];

    static angle SLANT2ANG[];
    static angle PROJANG_XY_XZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];
    static angle PROJANG_XY_XZ_TO_ROTANG_Y_REV[S_ANG90+1][S_ANG90+1];
    static angle PROJANG_ZY_ZX_TO_ROTANG_X_REV[S_ANG90+1][S_ANG90+1];
    static angle PROJANG_ZY_ZX_TO_ROTANG_Y[S_ANG90+1][S_ANG90+1];

    static AngleSet ROTY_ANGLE[S_ANG360+1];

    static GgafDx9SphereRadiusVectors _srv;

    static bool _was_inited_flg;

    static void init();

    template<typename T>
    static angle getAngle2D(T prm_vx, T prm_vy) {
        if (prm_vx == 0) {
            if (prm_vy > 0) {
                return ANGLE90;
            } else if (prm_vy < 0) {
                return ANGLE270;
            } else {
                //���_�ł���A�s��B
                return 0;
            }
        }
        if (prm_vy == 0) {
            if (prm_vx > 0) {
                return 0;
            } else if (prm_vx < 0) {
                return ANGLE180;
            } else {
                //���_�ł���A�s��B
                return 0;
            }
        }
        if (prm_vx >= 0 && prm_vy >= 0) { //��1�ی�
            if (prm_vx >= prm_vy) {
                return ANGLE0  + SLANT2ANG[(int)(1.0*prm_vy/prm_vx*100000)];
            } else {
                return ANGLE90 - SLANT2ANG[(int)(1.0*prm_vx/prm_vy*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //��2�ی�
            if (-prm_vx <= prm_vy) {
                return ANGLE90 + SLANT2ANG[(int)(1.0*-prm_vx/prm_vy*100000)];
            } else {
                return ANGLE180 - SLANT2ANG[(int)(1.0*prm_vy/-prm_vx*100000)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //��3�ی�
            if (-prm_vx >= -prm_vy) {
                return ANGLE180 + SLANT2ANG[(int)(1.0*-prm_vy/-prm_vx*100000)];
            } else {
                return ANGLE270 - SLANT2ANG[(int)(1.0*-prm_vx/-prm_vy*100000)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //��4�ی�
            if (prm_vx <= -prm_vy) {
                return ANGLE270 + SLANT2ANG[(int)(1.0*prm_vx/-prm_vy*100000)];
            } else {
                return ANGLE360 - SLANT2ANG[(int)(1.0*-prm_vy/prm_vx*100000)];
            }
        }
        return 0;
    }

    /**
     * �߂��ق��̃A���O���l�̍������
     * @param angFrom
     * @param angTo
     * @return �A���O���l�̍��i��������)
     */
    static angle getDiffAng(angle angFrom, angle angTo) {
            if (0 <= angFrom && angFrom < ANGLE180) {
                if (0 <= angTo && angTo < angFrom) {
                    return -1 * (angFrom - angTo);
                } else if (angTo == angFrom) {
                    //�d�Ȃ��Ă�ꍇ
                    return 0;
                } else if (angFrom < angTo && angTo < angFrom + ANGLE180) {
                    return angTo - angFrom;
                } else if (angTo == angFrom + ANGLE180) {
                    //�����΂������Ă���i�������͓������j
                    //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -ANGLE180 or ANGLE180)
                    return ANGLE180;
                } else if (angFrom + ANGLE180 < angTo && angTo <= ANGLE360) {
                    return -1 * (angFrom + (ANGLE360 - angTo));
                } else {
                    //��������
                    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
                    throwGgafCriticalException("GgafDx9Util::getDiffAngle �A���O���l���͈͊O�ł�(1)�B");
                }
            } else if (ANGLE180 <= angFrom && angFrom <= ANGLE360) {
                if (0 <= angTo && angTo < angFrom - ANGLE180) {
                    return ANGLE360 - angFrom + angTo;
                } else if (angTo == angFrom - ANGLE180) {
                    //�����΂������Ă���i�������͓������j
                    //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -ANGLE180 or ANGLE180)
                    return ANGLE180;
                } else if (angFrom - ANGLE180 < angTo && angTo < angFrom) {
                    return -1 * (angFrom - angTo);
                } else if (angFrom == angTo) {
                    //�d�Ȃ��Ă�ꍇ
                    return 0;
                } else if (angFrom < angTo && angTo <= ANGLE360) {
                    return angTo - angFrom;
                } else {
                    //��������
                    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
                    throwGgafCriticalException("GgafDx9Util::getDiffAngle �A���O���l���͈͊O�ł�(2)�B");
                }
            }

        _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
        throwGgafCriticalException("GgafDx9Util::getDiffAngle  ���̂�����p�̋��������߂�܂���B(1)");
    }


    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̃A���O���l���擾 .
     * @param prm_vx_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��X�v�f
     * @param prm_vy_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��Y�v�f
     * @param prm_nWay	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_nWay,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * ���ʏ�ɂ����āA'N'way�e(N=����)�̃A���O���l�̔z����擾 .
     * @param prm_angCenter	[in]'N'way�e�̑S�̂Ƃ��Č����Ă�������̃A���O���l
     * @param prm_nWay	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle);

    static void convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz);

//    static void getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                           int prm_nWay, angle prm_angClearance,
//                                           angle* out_paAngleRz, angle* out_paAngleRy);

//    static void getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                        angle& out_angFaceZ, angle* out_paAngRotY);


    /**
     * ���ʏ�ɂ����āA�~�̕��ˏ�S������'N'way�e(N=����)�̃A���O���l��z��Ŏ擾 .
     * �e�ƒe�Ƃ̐����p�� �ϓ��ɂȂ�B�Ⴆ�ΑS����4way�e�̏ꍇ�A�e�ƒe�Ƃ̐����p�͒��p�ł���B
     * @param prm_angStart	���ˏ�̑S����'N'way�e�̂P�ڂ̒e�̃A���O���l
     * @param prm_nWay	[in] 'N'way�e�� N�B
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle);

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
    static void rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y);

    /**
     *
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @return
     */
    static int getDistance(int x1, int y1, int x2, int y2);

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
    static void getRzRyAng(int x,
                              int y,
                              int z,
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
    static void getRzRyAng(int x, int y, int z, angle& out_angFaceZ, angle& out_angFaceY);

    /**
     * ���_����p�����[�^���W�����������x�N�g��(�P�ʃx�N�g��)�ɑΉ�����uZ����]�̃A���O���l�v�ƁuY����]�̃A���O���l�v���擾 .
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h���̂P<BR>
     * �����x�N�g�� -> Z��Y����]���p �̕ϊ�<BR>
     * �������ŁA�����x�N�g���̐��K�����s��Ȃ��̂� <BR>
     * getRzRyAng(int, int, int , angle&, angle&);
     * ����⍂���B�P�ʃx�N�g�������܂��Ă���Ƃ��͂�������g�p���܂��傤�B<BR>
     * @param nvx [in]�P�ʃx�N�g��X�v�f
     * @param nvy [in]�P�ʃx�N�g��Y�v�f
     * @param nvz [in]�P�ʃx�N�g��Z�v�f
     * @param out_angFaceZ [out]Z����]�A���O���l
     * @param out_angFaceY [out]Y����]�A���O���l
     */
    static void getRzRyAng(float nvx, float nvy, float nvz, angle& out_angFaceZ, angle& out_angFaceY);


    /**
     * Z����]+Y����]�l����P�ʕ����x�N�g�����擾
     * �{�N���X�̒��j�Ƃ������ׂ����\�b�h����2<BR>
     * Z��Y����]���p -> �����x�N�g�� �̕ϊ�<BR>
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

    static void getNormalizeVector(int x,
                                   int y,
                                   int z,
                                   float& out_nvx,
                                   float& out_nvy,
                                   float& out_nvz);

    /**
     * ������ς����AZ����]+Y����]�̍��v���������Ȃ�悤�ɍœK�������݂�B
     * @param rz1
     * @param ry1
     */
    static void anotherRzRy(angle& rz1, angle& ry1) {
        int rz2 = 0;
        int ry2 = 0;
        if (0 <= rz1 && rz1 < ANGLE90) {
            rz2 = ANGLE180 - rz1;

            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE90 <= rz1 && rz1 < ANGLE180) {
            rz2 = ANGLE180 - rz1;
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE180 <= rz1 && rz1 < ANGLE270) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        } else if (ANGLE270 <= rz1 && rz1 <= ANGLE360) {
            rz2 = ANGLE180 + (ANGLE360 - rz1);
            if (0 <= ry1 && ry1 < ANGLE180) {
                ry2 = ry1 + ANGLE180;
            } else {
                ry2 = ry1 - ANGLE180;
            }
        }
        rz1 = rz2;
        ry1 = ry2;
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
    static bool chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22);



    /**
     * world�ϊ��s��ݒ� .
     * �g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);




    static void setWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��XYZ�̏��łȂ����Ƃɒ���<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * X����] �~ Y����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * ��Y����]������܂���B_RY���Q��ڂ�X����]�ƂȂ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

    /**
     * world�ϊ��s��ݒ� .
     * �r���{�[�hX����] �~ �r���{�[�hY����] �~ �r���{�[�hZ����]  �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬���f�o�C�X�ɐݒ� <BR>
     * @param prm_pActor [in]�ΏۃA�N�^�[
     * @param out_matWorld [out]world�ϊ��s��
     */
    static void setWorldMatrix_BxyzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScRzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);


    static void mulWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld);



    static void setWorldMatrix_RxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
    static void setWorldMatrix_RzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);

};

}
#endif /*GGAFDX9UTIL_H_*/

