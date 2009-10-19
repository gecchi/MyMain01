#ifndef GGAFDX9UTIL_H_
#define GGAFDX9UTIL_H_
namespace GgafDx9Core {

#define sgn(X) (GgafDx9Util::sign(X))
#define max3(A,B,C) (GgafDx9Util::max3(A,B,C))

/**
 * ���[�e�B���e�B.
 * �Ɨ������ÓI�ȍ��W�֘A�֐��̓R�R�ɏW��B
 */
class GgafDx9Util: GgafCore::GgafUtil {

public:
    static int COS_UNITLEN[];
    static int SIN_UNITLEN[];
    static int TAN_UNITLEN[];
    static int RAD_UNITLEN[];
    static float PARABORA[];
    static float COS[];
    static float SIN[];
    static float RAD[];

    static int SLANT_ANG_0[];


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
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE0+SLANT_ANG_0["<<(int)(1.0*prm_vy/prm_vx*10000)<<"]="<<(ANGLE0+SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)]));
                return ANGLE0  + SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE90-SLANT_ANG_0["<<(int)(1.0*prm_vy/prm_vx*10000)<<"]="<<(ANGLE90-SLANT_ANG_0[(int)(1.0*prm_vy/prm_vx*10000)]));
                return ANGLE90 - SLANT_ANG_0[(int)(1.0*prm_vx/prm_vy*10000)];
            }
        } else if (prm_vx <= 0 && prm_vy >= 0) { //��2�ی�
            if (-prm_vx <= prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE90+SLANT_ANG_0["<<(int)(1.0*-prm_vx/prm_vy*10000)<<"]="<<(ANGLE90+SLANT_ANG_0[(int)(1.0*-prm_vx/prm_vy*10000)]));
                return ANGLE90 + SLANT_ANG_0[(int)(1.0*-prm_vx/prm_vy*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE180-SLANT_ANG_0["<<(int)(1.0*prm_vy/-prm_vx*10000)<<"]="<<(ANGLE180-SLANT_ANG_0[(int)(1.0*prm_vy/-prm_vx*10000)]));
                return ANGLE180 - SLANT_ANG_0[(int)(1.0*prm_vy/-prm_vx*10000)];
            }
        } else if (prm_vx <= 0 && prm_vy <= 0) { //��3�ی�
            if (-prm_vx >= -prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE180+SLANT_ANG_0["<<(int)(1.0*-prm_vy/-prm_vx*10000)<<"]="<<(ANGLE180+SLANT_ANG_0[(int)(1.0*-prm_vy/-prm_vx*10000)]));
                return ANGLE180 + SLANT_ANG_0[(int)(1.0*-prm_vy/-prm_vx*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE270-SLANT_ANG_0["<<(int)(1.0*-prm_vx/-prm_vy*10000)<<"]="<<(ANGLE270-SLANT_ANG_0[(int)(1.0*-prm_vx/-prm_vy*10000)]));
                return ANGLE270 - SLANT_ANG_0[(int)(1.0*-prm_vx/-prm_vy*10000)];
            }
        } else if (prm_vx >= 0 && prm_vy <= 0) { //��4�ی�
            if (prm_vx <= -prm_vy) {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE270+SLANT_ANG_0["<<(int)(1.0*prm_vx/-prm_vy*10000)<<"]="<<(ANGLE270+SLANT_ANG_0[(int)(1.0*prm_vx/-prm_vy*10000)]));
                return ANGLE270 + SLANT_ANG_0[(int)(1.0*prm_vx/-prm_vy*10000)];
            } else {
                //_TRACE_("prm_vx,prm_vy="<<prm_vx<<","<<prm_vy<<" "<<"ANGLE360-SLANT_ANG_0["<<(int)(1.0*-prm_vy/prm_vx*10000)<<"]="<<(ANGLE360-SLANT_ANG_0[(int)(1.0*-prm_vy/prm_vx*10000)]));
                return ANGLE360 - SLANT_ANG_0[(int)(1.0*-prm_vy/prm_vx*10000)];
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
    static angle getDifferenceAngle(angle angFrom, angle angTo) {
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
                    throwGgafCriticalException("GgafDx9Util::getDifferenceAngle �A���O���l���͈͊O�ł�(1)�B");
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
                    throwGgafCriticalException("GgafDx9Util::getDifferenceAngle �A���O���l���͈͊O�ł�(2)�B");
                }
            }

        _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo);
        throwGgafCriticalException("GgafDx9Util::getDifferenceAngle  ���̂�����p�̋��������߂�܂���B(1)");
    }


    /**
     * XY���W�n�iZ�������j�ɂ����āA�����x�N�g���̐����p���A���O���l�Ŏ擾 .
     * XY���W�n�iZ�������j�ɂ����āA���_(0,0)����(prm_vx,prm_vy)�ɐ��������������A
     * X���Ƃ̊Ԃɏo����p�i�R���̕������甽���v���Ɂj���A���O���l�Ŏ擾 .
     * @param prm_vx	X���W
     * @param prm_vy	Y���W
     * @return �����p
     */
    //static angle getAngle2D(int prm_vx, int prm_vy);

    /**
     * XY���W�n�iZ�������j�ɂ����āA'N'way�e(N=����)�̃A���O���l���擾 .
     * @param prm_vx_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��X�v�f
     * @param prm_vy_Center [in] 'N'way�e�̑S�̂Ƃ��Č����Ă�������́A�����x�N�g��Y�v�f
     * @param prm_way	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(int prm_vx_Center,
                              int prm_vy_Center,
                              int prm_way,
                              angle prm_angClearance,
                              int* out_paAngle);

    /**
     * XY���W�n�iZ�������j�ɂ����āA'N'way�e(N=����)�̃A���O���l�̔z����擾 .
     * @param prm_angCenter	[in]'N'way�e�̑S�̂Ƃ��Č����Ă�������̃A���O���l
     * @param prm_way	[in] 'N'way�e�� N
     * @param prm_angClearance	[in] 'N'way�e�̒e�ƒe�Ƃ̐����p���A���O���l�Ŏw��
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getWayAngle2D(angle prm_angCenter, int prm_way, angle prm_angClearance, angle* out_paAngle);


//    static void getMoveRzRyWayShot3D_XZ(int prm_way, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                        angle& out_angRotZ, angle* out_paAngRotY);


    /**
     * XY���W�n�iZ�������j�ɂ����āA�~�̕��ˏ�S������'N'way�e(N=����)�̃A���O���l��z��Ŏ擾 .
     * �e�ƒe�Ƃ̐����p�� �ϓ��ɂȂ�B�Ⴆ�ΑS����4way�e�̏ꍇ�A�e�ƒe�Ƃ̐����p�͒��p�ł���B
     * @param prm_angStart	���ˏ�̑S����'N'way�e�̂P�ڂ̒e�̃A���O���l
     * @param prm_way	[in] 'N'way�e�� N�B
     * @param out_paAngle	[out] ������'N'way�e �̃A���O���l�z��̃|�C���^
     */
    static void getRadiationAngle2D(angle prm_angStart, int prm_way, angle* out_paAngle);

    /**
     *
     * @param prm_angNow
     * @param prm_angOffset
     * @return
     */
    static angle addAngle(angle prm_angNow, angle prm_angOffset);

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
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(int x,
                              int y,
                              int z,
                              float& out_nvx,
                              float& out_nvy,
                              float& out_nvz,
                              angle& out_angRotZ,
                              angle& out_angRotY);

    /**
     * ���_����p�����[�^���W�����������x�N�g���́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * @param x [in]X���W
     * @param y [in]Y���W
     * @param z [in]Z���W
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(int x, int y, int z, angle& out_angRotZ, angle& out_angRotY);

    /**
     * ���_����p�����[�^�̐��K�����ꂽ�����x�N�g��(�P�ʃx�N�g��)�́AZ����]�A���O���l��Y����]�A���O���l���擾 .
     * �����x�N�g���̐��K���͍s��Ȃ��̂ō����ł��B<BR>
     * @param vx [in]�P�ʃx�N�g��X�v�f
     * @param vy [in]�P�ʃx�N�g��Y�v�f
     * @param vz [in]�P�ʃx�N�g��Z�v�f
     * @param out_angRotZ [out]Z����]�A���O���l
     * @param out_angRotY [out]Y����]�A���O���l
     */
    static void getRotAngleZY(float vx, float vy, float vz, angle& out_angRotZ, angle& out_angRotY);


    /**
     * Z����]+Y����]�l����P�ʕ����x�N�g�����擾
     * @param prm_angRotZ [in]Z����]�A���O���l
     * @param prm_angRotY [in]Y����]�A���O���l
     * @param out_nvx [out]�P�ʃx�N�g��X�v�f
     * @param out_nvy [out]�P�ʃx�N�g��Y�v�f
     * @param out_nvz [out]�P�ʃx�N�g��Z�v�f
     */
    static void getNormalizeVectorZY(angle prm_angRotZ,
                                     angle prm_angRotY,
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
     * ��������.
     * @param x
     * @return
     */
    template<typename T>
    static T sign(T x) {
        if (x < 0) {
            return -1;
        } else if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }

    /**
     * @param x
     * @return
     */
    template<typename T>
    static T abs(T x) {
        if (x < 0) {
            return -1.0* x;
        } else if (x > 0) {
            return x;
        } else {
            return 0.0;
        }
    }

    /**
     * �������̋ߎ������߂� .
     * �W��sqrt�����v�Z���͂₢�ł��傤�B
     * @param a �����������߂����l
     * @param s ���x�i�v�Z���[�v�񐔁j
     * @return ����a�̕�����
     */
    static float sqrt_fast(float a, int s = 11) {
        float ret = 1;
        for (int i = 1; i <= s; i++) {
            ret = 0.5 * (ret + a / ret);
        }
        return ret;
    }
    //static DWORD max3(DWORD a, DWORD b, DWORD c);
};

}
#endif /*GGAFDX9UTIL_H_*/

