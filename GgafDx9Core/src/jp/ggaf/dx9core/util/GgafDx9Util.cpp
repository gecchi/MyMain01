#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;



//�p�x�̎�ނ̕ϐ����̖����B�Y��Ȃ��悤����(2009/10/21)
//
//�ϐ����Ǝ��
//
//��{�I�ɓx���@�i0���`360���j���g�p���Ă���B
//ang �܂��� angle �ƕϐ����ɂ���ꍇ�A���W�A���ł͂Ȃ��ēx���@�ł̊p�x���l������B
//�i���W�A���̏ꍇ��rad�Ə����悤�ɂ��Ă���j
//�A�����x���ꍇ�ɂ���Ă܂��܂��ł���B
//�L���������� angle�l�� 0 �` 360,000 �� �l�̏�ł͓x���@��1000�{�̐��x�����B�ꉞ���ꂪ��{�B
//s_ang �͌v�Z�p�A�e�[�u���C���f�b�N�X�p�ɐ��x�𗎂Ƃ����߁Aangle�l��100�Ŋ�����  0 �` 3600 �ɂ����P�ʌn�B
//
//���Ɏ���]�ƕ��ʂ̒��S�p�̕\����ʂɂ���
//������]�̊p�x�̕ϐ����\����
//����]�� rot �܂��� r �ŏ����悤�ɂ���B angRx �Ƃ��A�Ƃɂ��� "R" �� "r" ���ϐ����ɓ����Ă�
//���၄
//angRx rotX rX Rx rX radRx �E�E�E X����]�Ɋ֘A���Ă���ϐ���
//angRy rotY rY Ry rY radRy �E�E�E Y����]�Ɋ֘A���Ă���ϐ���
//angRz rotZ rX Rz rZ radRz �E�E�E Z����]�Ɋ֘A���Ă���ϐ���
//���������̎��X�ɂ�萸�x���ς���Ă��邩������Ȃ��B
//�܂�����n(X���͉E�֍s���Ɛ��AY���͏�ɍs���Ɛ��AZ���͉��֍s���Ɛ��j��O��Ƃ��Ă��邽�߁A
//�����̎���]angle�l�̐��̒l�Ƃ͒ʏ�́A���������Ĕ����v���̕�����\���B
//X����]�l �E�E�E X���̐��̕����������č���肪���̉�]�p�x
//Y����]�l �E�E�E Y���̐��̕����������č���肪���̉�]�p�x
//Z����]�l �E�E�E Z���̐��̕����������č���肪���̉�]�p�x
//
//�����ʂ̒��S�p�A�܂��͒����̐����p�x�̕ϐ����\����
//���镽�ʌn�ɑ΂��Ă̒��S�p�͂ǂ̕��ʂ��������悤�ɂ���B
//
//angXY �E�E�EXY���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� X���̐��̕������E�AY���̐��̕�������ɂ����Q�������ʂŁA�R���̕��� (x,y)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//angXZ �E�E�EXZ���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� X���̐��̕������E�AZ���̐��̕�������ɂ����Q�������ʂŁA�R���̕��� (x,z)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//angZX �E�E�EZX���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� Z���̐��̕������E�AX���̐��̕�������ɂ����Q�������ʂŁA�R���̕��� (z,x)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//�����Œ��ӂ́A
//angXY �� Z����]�l
//angZX �� Y����]�l
//�Ɠǂݑւ���邪�AangXZ��Y����]�l�̐������t�ɂȂ邱�ƁA�ǂ̂悤�Ɂu���ʂƌ���v���p�����Ⴄ���߁B
//
//�����ʂ̒��S�p�A�܂��͒����̐����p�x���A����]�Ƃ݂Ȃ��Čv�Z����ꍇ�̕ϐ����\����
//angXY �� �R������Ԃ� Z=0 ��XY���ʏ�Ɍ���AangRz �Ƃ݂Ȃ����Ƃ��o���܂��B
//���̂悤�ɂ��Čv�Z���s���Ă���ӏ�������A
//�u���ʂ̒��S�p�A�܂��͒����̐����p�x �Ƃ��Ēl�����߂����ǂ��A����]�Ƃ��ēǂݑւ����A�����́A�g�����������v
//�Ƃ����ꍇ�� rotXY �Ƃ����ϐ��ɂ��Ă��܂��B
//�܂� rotXY = angXY or angRz
//angXY -> angRz �͊p�x0���̈ʒu(�����x�N�g��(x,y,z)=(1,0,0))�A���̉�]��������v����̂ł킩��₷���ł��B

//�u�߂��v
//angXZ -> angRy �̓ǂݑւ��͐��̉�]������ angXZ �� angRy �ŋt�ɂȂ��Ă��܂��܂��B
//angZX -> angRy �̏ꍇ�͐��̉�]�����͈�v���܂����A�p�x0���̈ʒu��(x,y,z)=(1,0,0) �ł͂Ȃ��Ȃ��Ă��܂����߁A�L�����̎���]�ɂ͌����܂���
//
//������
//rotXZ = angXZ or angRy_rev
//�̂悤�� "rev" �u�t����ł���v�Ə����悤�ɂ����B�p�x0���̈ʒu��D�悵�����ʁA����Ȃ�₱�������ƂɂȂ��Ă���I



bool GgafDx9Util::_was_inited_flg = false;

float GgafDx9Util::PARABORA[S_ANG360+1];
float GgafDx9Util::COS[S_ANG360+1];
float GgafDx9Util::SIN[S_ANG360+1];
float GgafDx9Util::RAD[S_ANG360+1];

float GgafDx9Util::ROOT_1_MINUS_XX[1000];


angle GgafDx9Util::SLANT2ANG[100000 + 1];

//����Ȃ񂢂�̂ł́I
//angle GgafDx9Util::PROJANG_XY_ZX_YZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];


angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Y_REV[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_ZY_ZX_TO_ROTANG_X_REV[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_ZY_ZX_TO_ROTANG_Y[S_ANG90+1][S_ANG90+1];

GgafDx9SphereRadiusVectors GgafDx9Util::_srv = GgafDx9SphereRadiusVectors();

void GgafDx9Util::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < S_ANG360+1; ang++) {
        double rad = (PI * 2.0f * ang) / S_ANG360;


        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        PARABORA[ang] = (float)((double)((ang-(S_ANG360/2))*(ang-(S_ANG360/2))) /  (double)(-1.0*(S_ANG360/2)*(S_ANG360/2)) + 1.0);
        //PARABORA[0] = 0 , PARABORA[S_ANG180] = 1,  PARABORA[S_ANG360-1] = 0 �� y = -x^2  �������̒l���Ƃ�
    }

    COS[S_ANG0]   =  1;
    COS[S_ANG90]  =  0;
    COS[S_ANG180] = -1;
    COS[S_ANG270] =  0;
    COS[S_ANG360] =  1;
    SIN[S_ANG0]   =  0;
    SIN[S_ANG90]  =  1;
    SIN[S_ANG180] =  0;
    SIN[S_ANG270] = -1;
    SIN[S_ANG360] =  0;
    //<SLANT2ANG>
    double rad;
    double vx,vy,vz;
    float slant;
    int index_slant;
    int index_slant_prev = -1;
    int d_index_slant = 0;
    //�X�� 0.0 �` 1.0 �� �p�x�����ߔz��Ɏ��߂�B���߂�p�x��100�{�̐����B
    //�v�f�ԍ��́A�X��*10000

    //ang=0  slant=0 vx,vy=1,0
    //ang=1  slant=0.000174533   vx,vy=1,0.000174533
    //ang=2  slant=0.000349066   vx,vy=1,0.000349066
    //ang=3  slant=0.000523599   vx,vy=1,0.000523599
    //ang=4  slant=0.000698132   vx,vy=1,0.000698132
    //ang=5  slant=0.000872665   vx,vy=1,0.000872665

    // SLANT2ANG[0]      = 0
    // SLANT2ANG[1(.7)]�` = 1000�`
    // SLANT2ANG[3(.4)]�` = 2000�`
    // SLANT2ANG[5(.2)]  = 3000�`
    // SLANT2ANG[6(.9)]  = 4000�`
    // SLANT2ANG[8(.7)]  = 5000�` �Ƃ�������ɂȂ�悤�ɒ���

    //ang=4493   slant=0.99756   vx,vy=0.70797,0.706242
    //ang=4494   slant=0.997908  vx,vy=0.707847,0.706366
    //ang=4495   slant=0.998256  vx,vy=0.707724,0.706489
    //ang=4496   slant=0.998605  vx,vy=0.7076,0.706613
    //ang=4497   slant=0.998953  vx,vy=0.707477,0.706736
    //ang=4498   slant=0.999302  vx,vy=0.707354,0.70686
    //ang=4499   slant=0.999651  vx,vy=0.70723,0.706983
    //ang=4500   slant=1 vx,vy=0.707107,0.707107         <--���̂�����܂ŋ��߂�
    //ang=4501   slant=1.00035   vx,vy=0.706983,0.70723
    //ang=4502   slant=1.0007    vx,vy=0.70686,0.707354

    //2010/03/09 SLANT2ANG�̐��x10�{�ɃA�b�v
    //���݂͗v�f�ԍ��́A�X��*100000
    for (int ang = 0; ang <= 45000; ang++) {
        rad = (PI * 2.0f * ang) / 360000;
        vx = cos(rad);
        vy = sin(rad);
        if (vx == 0) {
            slant = 0.0f;
        } else {
            slant = (float)(vy / vx);
        }
        index_slant = (int)(slant * 100000);
        d_index_slant = index_slant - index_slant_prev;
        for (int i = index_slant_prev+1, d = 1; i <= index_slant; i++, d++) {
            if (i > 100000) {
                _TRACE_("���x�����z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(ang*10));
            }
            //��������i�������A�o�E�g�̂��Ɓj
            SLANT2ANG[i] = (angle)( ((ang-1) + (1.0*d)/(1.0*d_index_slant))*1.0);
        }
        index_slant_prev = index_slant;
    }
    d_index_slant = 100000 - index_slant_prev;
    for (int i = index_slant_prev+1, d = 1; i <= 100000; i++, d++) {
        if (i > 100000) {
            _TRACE_("���x�����z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(450000));
        }
        SLANT2ANG[i] = (angle)( (450000-1) + (1.0*d)/(1.0*d_index_slant) );
    }

    //<PROJ_ANG2ROT_ANG> �i2009/10/20 �o�܁E�E�E�������邽�߂Ȃ牽�ł�����Ă݂悤�j
    //��������x�N�g������AXY���ʁAZY���ʂɓ��e�������ɂł��鎲�Ƃ̊p�i���ꂼ��XY�ˉe�p�AZY�ˉe�p�ƌĂԂ��ƂƂ���j�ƁA
    //���̕����x�N�g���̒P�ʃx�N�g�����w���P�ʋ��̈ܓx�ƌo�x�iZ����]�p�AY����]�p�j��R���邱�Ƃ�ړI�Ƃ���B
    //�܂�AXY�ˉe�p�AZY�ˉe�p �� Z����]�p�AY����]�p �̓ǂݑւ��������ɍs������
    //XY�ˉe�p90�x�� * ZY�ˉe�p90�x�� ��z��v�f�A�l��Z����]�p�AY����]�p��l�Ƃ���z����\�z�B

    double nvx,nvy,nvz;
    double prj_rad_xy,prj_rad_xz, prj_rad_zy, prj_rad_zx;
    s_ang rz, ry_rev;

    vx = 1.0;
    for (s_ang prj_ang_xy = 0; prj_ang_xy <= S_ANG90; prj_ang_xy++) {
        prj_rad_xy = (PI * 2.0 * prj_ang_xy) / (1.0*S_ANG360);
        vy = tan(prj_rad_xy);

        for (s_ang prj_ang_xz = 0; prj_ang_xz <= S_ANG90; prj_ang_xz++) {
            prj_rad_xz = (PI * 2.0 * prj_ang_xz) / (1.0*S_ANG360);
            vz = tan(prj_rad_xz);

            //�����x�N�g�����쐬
            //vx,vy,vz �𐳋K������B
            //���߂�P�ʃx�N�g���� (X,Y,Z) �Ƃ���� (X,Y,Z) = t(vx,vy,vz)
            //�֌W��   X=t*vx; Y=t*vy; Z=t*vz; �E�E�E (1) �𓾂�
            //�P�ʋ��� X^2 + Y^2 + Z^2 = 1 �E�E�E(2)
            //(1)(2)��A�������āAt �ɂ��ĉ����B
            //t = 1 / sqrt(vx^2 + vy^2 + vz^2)
            double t = 1 / sqrt(vx * vx + vy * vy + vz * vz);
            //���߂� t �� (1) �ɑ���� (X,Y,Z) �����߂�B
            nvx = t * vx;
            nvy = t * vy;
            nvz = t * vz;
            //getRzRyAng((float)nvx,(float)nvy,(float)nvz,rZ,rY,30);
//
//            //�P�ʃx�N�g������RxRy�����߂�
            _srv.getFaceAngClosely(
                    (UINT32)(nvx*1000000),
                    (UINT32)(nvy*1000000),
                    (UINT32)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );
            PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz] = rz*ANGLE_RATE;
            PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*ANGLE_RATE;


           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }



    vz = 1.0;
    for (s_ang prj_ang_zy = 0; prj_ang_zy <= S_ANG90; prj_ang_zy++) {
        prj_rad_zy = (PI * 2.0 * prj_ang_zy) / (1.0*S_ANG360);
        vy = tan(prj_rad_zy);

        for (s_ang prj_ang_zx = 0; prj_ang_zx <= S_ANG90; prj_ang_zx++) {
            prj_rad_zx = (PI * 2.0 * prj_ang_zx) / (1.0*S_ANG360);
            //�����x�N�g�����쐬
            vx = tan(prj_rad_zx);

            double t = 1 / sqrt(vx * vx + vy * vy + vz * vz);
            nvx = t * vx;
            nvy = t * vy;
            nvz = t * vz;
            //getRzRyAng((float)nvx,(float)nvy,(float)nvz,rZ,rY,30);
//
//            //�P�ʃx�N�g������RxRy�����߂�
            _srv.getFaceAngClosely(
                    (UINT32)(nvx*1000000),
                    (UINT32)(nvy*1000000),
                    (UINT32)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );

            //(0,0,1.0)��0���Ƃ�X���̐��̕��������Ď��v���𐳂̊p(rx_rev)���l����
            //����͏�ŋ��߂�rz�Ɠ������Ȃ�B
            int rx_rev = rz;
            //(0,0,1.0)��0���Ƃ�Y���̐��̕��������Ĕ����v���𐳂̊p(ry)���l����
            //����͏�ŋ��߂�ry_rev��ANGLE90����������l�ł���B
            PROJANG_ZY_ZX_TO_ROTANG_X_REV[prj_ang_zy][prj_ang_zx] = rx_rev*ANGLE_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx] = ANGLE90 - ry_rev*ANGLE_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_Y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = ANGLE90 - "<<ry_rev<<"*ANGLE_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx]);

           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }

    //ROOT_1_MINUS_XX�̐ݒ�
    for (int i = 0; i < 1000; i++) {
        ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }
}



void GgafDx9Util::getWayAngle2D(int prm_vx_Center,
                                int prm_vy_Center,
                                int prm_nWay,
                                angle prm_angClearance,
                                angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_nWay, prm_angClearance, out_paAngle);
}

void GgafDx9Util::getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle) {
    int angstart = addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(angstart, prm_angClearance * i);
    }
}

void GgafDx9Util::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(prm_angStart, (angle)(1.0f * ANGLE360 / prm_nWay * i));
    }
}

void GgafDx9Util::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    getNormalizeVectorZY(prm_Rz, prm_Ry , vx, vy, vz);
    getRzRyAng(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-�X�O�xX����]RzRy����ւ�
    out_Rz = ANGLE360-out_Rz; //Y����Z���l���邽�߁A�������ς�遁�t��]��360�������
}



//void GgafDx9Util::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                              int prm_nWay, angle prm_angClearance,
//                                              angle* out_paAngleRz, angle* out_paAngleRy) {
//    float vx,vy,vz;
//    getNormalizeVectorZY(prm_angCenterRz, prm_angCenterRy, vx, vy, vz);
//    float vx2,vy2,vz2;
//    //X���X�O�x��]
//    vx2 = vx;
//    vy2 = -vz;
//    vz2 = vy;
//
//    getWayAngle2D(prm_angCenterRz, prm_nWay, prm_angClearance, out_paAngleRz);
//
//}

//void GgafDx9Util::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, int prm_tX, int prm_tY, int prm_tZ,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    getRzRyAng(prm_tX, prm_tY, prm_tZ, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDx9Util::addAng(angle prm_angNow, angle prm_angOffset) {
    static angle angAdd;
    angAdd = prm_angNow + prm_angOffset;
    while (angAdd >= ANGLE360) {
        angAdd -= ANGLE360;
    }
    while (angAdd < 0) {
        angAdd += ANGLE360;
    }
    return angAdd;
}

angle GgafDx9Util::getAngDiff(angle angFrom, angle angTo, int prm_way) {
    if (prm_way == TURN_CLOSE_TO) {
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
                _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
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
                _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDx9Util::getDiffAngle �A���O���l���͈͊O�ł�(2)�B");
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (angFrom <= angTo) {
            return angTo - angFrom;
        } else {
            return (ANGLE360 - angFrom) + angTo;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (angFrom >= angTo) {
            return -(angFrom - angTo);
        } else {
            return -(angFrom + (ANGLE360 - angTo));
        }
    } else {
        _TRACE_("GgafDx9Util::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
        throwGgafCriticalException("GgafDx9Util::getDiffAngle  prm_way = TURN_CLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE �ȊO���w�肳��Ă��܂��B");
    }

    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
    throwGgafCriticalException("GgafDx9Util::getDiffAngle  ���̂�����p�̋��������߂�܂���B(1)");
}

void GgafDx9Util::rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y) {
    out_X = (int)(floor((prm_X * GgafDx9Util::COS[prm_ang / ANGLE_RATE]) - (prm_Y * GgafDx9Util::SIN[prm_ang
            / ANGLE_RATE])));
    out_Y = (int)(floor((prm_X * GgafDx9Util::SIN[prm_ang / ANGLE_RATE]) + (prm_Y * GgafDx9Util::COS[prm_ang
            / ANGLE_RATE])));
}

// �����̓����蔻�� (x11,y11)-(x12,y12) �~ (x21,y21)-(x22,y22)
bool GgafDx9Util::chk2DLineCrossing(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {

    //x���W�ɂ��`�F�b�N
    if (x11 >= x12) {
        if ((x11 < x21 && x11 < x22) || (x12 > x21 && x12 > x22)) {
            return false;
        }
    } else {
        if ((x12 < x21 && x12 < x22) || (x11 > x21 && x11 > x22)) {
            return false;
        }
    }
    //y���W�ɂ��`�F�b�N
    if (y11 >= y12) {
        if ((y11 < y21 && y11 < y22) || (y12 > y21 && y12 > y22)) {
            return false;
        }
    } else {
        if ((y12 < y21 && y12 < y22) || (y11 > y21 && y11 > y22)) {
            return false;
        }
    }
    if (((x11 - x12) * (y21 - y11) + (y11 - y12) * (x11 - x21)) * ((x11 - x12) * (y22 - y11) + (y11 - y12)
            * (x11 - x22)) > 0) {
        return false;
    }
    if (((x21 - x22) * (y11 - y21) + (y21 - y22) * (x21 - x11)) * ((x21 - x22) * (y12 - y21) + (y21 - y22)
            * (x21 - x12)) > 0) {
        return false;
    }
    return true;
}

int GgafDx9Util::getDistance(int x1, int y1, int x2, int y2) {
    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}

void GgafDx9Util::getRzRyAng(int vx,
                             int vy,
                             int vz,
                             angle& out_angFaceZ,
                             angle& out_angFaceY ) {
    //���ꂩ�̗v�f��0�̏ꍇ�AgetAngle2D�̌��ʂ��傫������Ă��܂��B
    //�Ƃ肠�����P��ݒ肵�ċߎ������Ă������B
    //TODO:0 �����Ă����v�ɂ���B
    vx = (vx == 0 ? 1 : vx);
    vy = (vy == 0 ? 1 : vy);
    vz = (vz == 0 ? 1 : vz);

    angle prj_rXY = getAngle2D(abs(vx), abs(vy)); //Rz
    angle prj_rXZ = getAngle2D(abs(vx), abs(vz));
    angle prj_rZY = getAngle2D(abs(vz), abs(vy)); //Rz
    angle prj_rZX = getAngle2D(abs(vz), abs(vx));

    angle rotZ, rotY_rev, rotY;
    if (0 <= prj_rXZ && prj_rXZ <= ANGLE45) {
        rotZ = PROJANG_XY_XZ_TO_ROTANG_Z[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
        rotY_rev = PROJANG_XY_XZ_TO_ROTANG_Y_REV[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
    } else if (ANGLE45 <= prj_rXZ && prj_rXZ <= ANGLE90) {
        rotZ = PROJANG_ZY_ZX_TO_ROTANG_X_REV[(int)(prj_rZY/100.0)][(int)(prj_rZX/100.0)];
        rotY = PROJANG_ZY_ZX_TO_ROTANG_Y[(int)(prj_rZY/100.0)][(int)(prj_rZX/100.0)];
        rotY_rev = ANGLE90 - rotY;
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng �͈͂��j�����Ă܂��Bprj_rXZ="<<prj_rXZ);
    }

    if (0 <= prj_rXY && prj_rXY < ANGLE45) {
        //OK
    } else if (ANGLE45 <= prj_rXY && prj_rXY <= ANGLE90) {
        //OK
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng �͈͂��j�����Ă܂��Bprj_rXY="<<prj_rXY<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
    //�ی��ɂ���ĉ�]�p��␳
    if (vx >= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE360 - rotY_rev);
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE180 + rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //��O�ی�
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE180 + rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //��l�ی�
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE360 - rotY_rev);
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //��܏ی�
        out_angFaceZ = rotZ;
        out_angFaceY = rotY_rev;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //��Z�ی�
        out_angFaceZ = rotZ;
        out_angFaceY = (ANGLE180 - rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //�掵�ی�
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = (ANGLE180 - rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //�攪�ی�
        out_angFaceZ = (ANGLE360 - rotZ);
        out_angFaceY = rotY_rev;
    } else {
        throwGgafCriticalException("GgafDx9Util::getRzRyAng ���肦�܂���Bvx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
    out_angFaceZ = simplifyAng(out_angFaceZ);
    out_angFaceY = simplifyAng(out_angFaceY);
}


void GgafDx9Util::getRzRyAng(int vx,
                          int vy,
                          int vz,
                          float& out_nvx,
                          float& out_nvy,
                          float& out_nvz,
                          angle& out_angFaceZ,
                          angle& out_angFaceY) {

    getRzRyAng(vx,
               vy,
               vz,
               out_angFaceZ,
               out_angFaceY );

    getNormalizeVectorZY(out_angFaceZ,
                         out_angFaceY,
                         out_nvx,
                         out_nvy,
                         out_nvz);

}



void GgafDx9Util::getNormalizeVector(int x,
                                     int y,
                                     int z,
                                     float& out_nvx,
                                     float& out_nvy,
                                     float& out_nvz) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;
}


void GgafDx9Util::getNormalizeVectorZY(angle prm_angFaceZ,
                                       angle prm_angFaceY,
                                       float& out_nvx,
                                       float& out_nvy,
                                       float& out_nvz) {
    //void GgafDx9SphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angFaceZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
    //��]�p�ɂ���ďی����l�����AgetVectorClosely�̃p�����[�^�p(< 900)���o��
    int Xsign, Ysign, Zsign;
    s_ang rZ, rY_rev;

    if (0 <= prm_angFaceZ && prm_angFaceZ < ANGLE90) {
        rZ = (prm_angFaceZ - ANGLE0) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //��܏ی�
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //��Z�ی�
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //���ی�
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //���ی�
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        }
    } else if (ANGLE90 <= prm_angFaceZ && prm_angFaceZ < ANGLE180) {
        rZ = (ANGLE180 - prm_angFaceZ) / ANGLE_RATE;

        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //���ی�
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //���ی�
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //��܏ی�
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //��Z�ی�
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        }

    } else if (ANGLE180 <= prm_angFaceZ && prm_angFaceZ < ANGLE270) {
        rZ = (prm_angFaceZ - ANGLE180) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //��O�ی�
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //��l�ی�
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //�攪�ی�
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //�掵�ی�
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        }
    } else if (ANGLE270 <= prm_angFaceZ && prm_angFaceZ <= ANGLE360) {
        rZ = (ANGLE360 - prm_angFaceZ) / ANGLE_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < ANGLE90) { //�攪�ی�
            rY_rev = prm_angFaceY / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE90 <= prm_angFaceY && prm_angFaceY < ANGLE180) { //�掵�ی�
            rY_rev = (ANGLE180 - prm_angFaceY) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (ANGLE180 <= prm_angFaceY && prm_angFaceY < ANGLE270) { //��O�ی�
            rY_rev = (prm_angFaceY - ANGLE180) / ANGLE_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (ANGLE270 <= prm_angFaceY && prm_angFaceY <= ANGLE360) { //��l�ی�
            rY_rev = (ANGLE360 - prm_angFaceY) / ANGLE_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        }
    } else {
        _TRACE_("getNormalizeVectorZY: �Ȃ񂩂��������ł��� prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
    }
    UINT32 vx, vy, vz;
    //  _TRACE_("prm_angFaceZ="<<prm_angFaceZ<<"/prm_angFaceY="<<prm_angFaceY<<" rY="<<rY<<"/rZ="<<rZ<<")");
    //  _TRACE_("("<<Xsign<<","<<Ysign<<","<<Zsign<<")");
    _srv.getVectorClosely(rY_rev, rZ, vx, vy, vz);
    out_nvx = Xsign * (int)vx / 1000000.0f;
    out_nvy = Ysign * (int)vy / 1000000.0f;
    out_nvz = Zsign * (int)vz / 1000000.0f;
}




void GgafDx9Util::setWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 = Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 = Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //�O�̂���
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void GgafDx9Util::setWorldMatrix_RxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz * cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (cosRx * -sinRz * cosRy) + (sinRx * sinRy);
    out_matWorld._22 = cosRx * cosRz;
    out_matWorld._23 = (cosRx * -sinRz * -sinRy) + (sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (-sinRx * -sinRz * cosRy) + (cosRx * sinRy);
    out_matWorld._32 = -sinRx * cosRz;
    out_matWorld._33 = (-sinRx * -sinRz * -sinRy) + (cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}




void GgafDx9Util::setWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];

    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx*cosRz*cosRy;
    out_matWorld._12 = Sx*sinRz;
    out_matWorld._13 = Sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*cosRy;
    out_matWorld._22 = Sy*cosRz;
    out_matWorld._23 = Sy*-sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = Sz*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::mulWorldMatrix_RzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*Sx  sinRz*Sy   cosRz*-sinRy*Sz   0 |
    //    | -sinRz*cosRy*Sx  cosRz*Sy  -sinRz*-sinRy*Sz   0 |
    //    |  sinRy*Sx        0          cosRy*Sz          0 |
    //    |  dx              dy         dz                1 |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz*cosRy*Sx;
    out_matWorld._12 = sinRz*Sy;
    out_matWorld._13 = cosRz*-sinRy*Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy*Sx;
    out_matWorld._22 = cosRz*Sy;
    out_matWorld._23 = -sinRz*-sinRy*Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy*Sx;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy*Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDx9Util::setWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy*Sx,          sinRz*Sy,                         cosRz*-sinRy*Sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*Sx,    cosRx*cosRz*Sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*Sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*Sx,   -sinRx*cosRz*Sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*Sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz * cosRy * Sx;
    out_matWorld._12 = sinRz * Sy;
    out_matWorld._13 = cosRz * -sinRy * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((cosRx * -sinRz * cosRy) + (sinRx * sinRy)) * Sx;
    out_matWorld._22 = cosRx * cosRz * Sy;
    out_matWorld._23 = ((cosRx * -sinRz * -sinRy) + (sinRx * cosRy)) * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((-sinRx * -sinRz * cosRy) + (cosRx * sinRy)) * Sx;
    out_matWorld._32 = -sinRx * cosRz * Sy;
    out_matWorld._33 = ((-sinRx * -sinRz * -sinRy) + (cosRx * cosRy)) * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_RxRyRzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //    |                           cosRy*cosRz*Sx,                        cosRy*sinRz*Sy  ,      -sinRy*Sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*Sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*Sy), sinRx*cosRy*Sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*Sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*Sy), cosRx*cosRy*Sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    static float fRateScale = 1.0f * LEN_UNIT;

    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRy*cosRz*Sx;
    out_matWorld._12 = cosRy*sinRz*Sy;
    out_matWorld._13 = -sinRy*Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((sinRx*sinRy*cosRz) + (cosRx*-sinRz))*Sx;
    out_matWorld._22 = ((sinRx*sinRy*sinRz) + (cosRx*cosRz))*Sy;
    out_matWorld._23 = sinRx*cosRy*Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((cosRx*sinRy*cosRz) + (-sinRx*-sinRz))*Sx;
    out_matWorld._32 = ((cosRx*sinRy*sinRz) + (-sinRx* cosRz))*Sy;
    out_matWorld._33 = cosRx*cosRy*Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::setWorldMatrix_RxRzRxScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬.
    //��Y����]������܂���BRY�͂Q��ڂ�X����]�ƂȂ�
    //|         cosRz*Sx,                          sinRz*cosRy*Sy ,                          sinRz*sinRy*Sz, 0 |
    //|  cosRx*-sinRz*Sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*Sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*Sz), 0 |
    //| -sinRx*-sinRz*Sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*Sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*Sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    static float fRateScale = 1.0f * LEN_UNIT;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = cosRz * Sx;
    out_matWorld._12 = sinRz * cosRy * Sy;
    out_matWorld._13 = sinRz * sinRy * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = cosRx * -sinRz * Sx;
    out_matWorld._22 = (( cosRx * cosRz * cosRy) + (sinRx * -sinRy)) * Sy;
    out_matWorld._23 = (( cosRx * cosRz * sinRy) + (sinRx *  cosRy)) * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = -sinRx * -sinRz * Sx;
    out_matWorld._32 = ((-sinRx * cosRz * cosRy) + (cosRx * -sinRy)) * Sy;
    out_matWorld._33 = ((-sinRx * cosRz * sinRy) + (cosRx *  cosRy)) * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_RzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    s_ang s_RZ = prm_pActor->_RZ / ANGLE_RATE;

    out_matWorld._11 = GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (float)(-1.0f * GgafDx9Util::SIN[s_RZ]);
    out_matWorld._22 = GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = 1.0f;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDx9Util::setWorldMatrix_ScRzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |Sx*cosZ , Sx*sinZ , 0    , 0  |
    // |Sy*-sinZ, Sy*cosZ , 0    , 0  |
    // |0       , 0       , Sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    static float fRateScale = 1.0f * LEN_UNIT;

    s_ang s_RZ = prm_pActor->_RZ / ANGLE_RATE;
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx * GgafDx9Util::COS[s_RZ];
    out_matWorld._12 = Sx * GgafDx9Util::SIN[s_RZ];
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy * -1.0f * GgafDx9Util::SIN[s_RZ];
    out_matWorld._22 = Sy * GgafDx9Util::COS[s_RZ];
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::setWorldMatrix_ScMvRxRzRy(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;

    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;
    float dx = prm_pActor->_fX;
    float dy = prm_pActor->_fY;
    float dz = prm_pActor->_fZ;

    out_matWorld._11 = Sx*cosRz*cosRy;
    out_matWorld._12 = Sx*sinRz;
    out_matWorld._13 = Sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*cosRx*-sinRz*cosRy + Sy*sinRx*sinRy;
    out_matWorld._22 = Sy*cosRx*cosRz;
    out_matWorld._23 = Sy*cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy;
    out_matWorld._32 = Sz*-sinRx*cosRz;
    out_matWorld._33 = Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*cosRy + ((dy*sinRx + dz*cosRx))*sinRy;
    out_matWorld._42 = (dx*sinRz + (dy*cosRx + dz*-sinRx)*cosRz);
    out_matWorld._43 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*-sinRy + ((dy*sinRx + dz*cosRx))*cosRy;
    out_matWorld._44 = 1.0f;

}




void GgafDx9Util::updateWorldMatrix_Mv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}







void GgafDx9Util::setWorldMatrix_BxyzScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    GgafDx9Camera* pCam = P_CAM;

    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCam->_vMatrixView._11 * Sx;
    out_matWorld._12 = pCam->_vMatrixView._21 * Sy;
    out_matWorld._13 = pCam->_vMatrixView._31 * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCam->_vMatrixView._12 * Sx;
    out_matWorld._22 = pCam->_vMatrixView._22 * Sy;
    out_matWorld._23 = pCam->_vMatrixView._32 * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_vMatrixView._13 * Sx;
    out_matWorld._32 = pCam->_vMatrixView._23 * Sy;
    out_matWorld._33 = pCam->_vMatrixView._33 * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}






void GgafDx9Util::setWorldMatrix_ScRzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    GgafDx9Camera* pCam = P_CAM;

    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx*cosRz*pCam->_vMatrixView._11 + Sx*sinRz*pCam->_vMatrixView._12;
    out_matWorld._12 = Sx*cosRz*pCam->_vMatrixView._21 + Sx*sinRz*pCam->_vMatrixView._22;
    out_matWorld._13 = Sx*cosRz*pCam->_vMatrixView._31 + Sx*sinRz*pCam->_vMatrixView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*pCam->_vMatrixView._11 + Sy*cosRz*pCam->_vMatrixView._12;
    out_matWorld._22 = Sy*-sinRz*pCam->_vMatrixView._21 + Sy*cosRz*pCam->_vMatrixView._22;
    out_matWorld._23 = Sy*-sinRz*pCam->_vMatrixView._31 + Sy*cosRz*pCam->_vMatrixView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*pCam->_vMatrixView._13;
    out_matWorld._32 = Sz*pCam->_vMatrixView._32;
    out_matWorld._33 = Sz*pCam->_vMatrixView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDx9Util::mulWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float fRateScale = 1.0f * LEN_UNIT;
    D3DXMATRIX matScRxRzRyMv;
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    float Sx = prm_pActor->_SX / fRateScale;
    float Sy = prm_pActor->_SY / fRateScale;
    float Sz = prm_pActor->_SZ / fRateScale;

    matScRxRzRyMv._11 = Sx * cosRz *cosRy;
    matScRxRzRyMv._12 = Sx * sinRz;
    matScRxRzRyMv._13 = Sx * cosRz * -sinRy;
    matScRxRzRyMv._14 = 0.0f;

    matScRxRzRyMv._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    matScRxRzRyMv._22 = Sy * cosRx *  cosRz;
    matScRxRzRyMv._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    matScRxRzRyMv._24 = 0.0f;

    matScRxRzRyMv._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    matScRxRzRyMv._32 = Sz * -sinRx *  cosRz;
    matScRxRzRyMv._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    matScRxRzRyMv._34 = 0.0f;

    matScRxRzRyMv._41 = prm_pActor->_fX;
    matScRxRzRyMv._42 = prm_pActor->_fY;
    matScRxRzRyMv._43 = prm_pActor->_fZ;
    matScRxRzRyMv._44 = 1.0f;

    D3DXMatrixMultiply(&inout_matWorld, &inout_matWorld, &matScRxRzRyMv);
    /*
     //�O�̂���
     float fRateScale = LEN_UNIT;
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDx9Util::RAD_UNITLEN[s_RX]/fRateScale);
     D3DXMatrixRotationX(&matrixRotY, GgafDx9Util::RAD_UNITLEN[s_RY]/fRateScale);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDx9Util::RAD_UNITLEN[s_RZ]/fRateScale);
     D3DXMatrixTranslation(&matrixTrans, _X/fRateScale, _Y/fRateScale, _Z/fRateScale);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}


void GgafDx9Util::setWorldMatrix_RxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
    // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
    // | dx                                 , dy          , dz                                  , 1 |
    float sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    float cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    float sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    float cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (cosRx*-sinRz*cosRy + sinRx*sinRy);
    out_matWorld._22 = cosRx*cosRz;
    out_matWorld._23 = (cosRx*-sinRz*-sinRy + sinRx*cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (-sinRx*-sinRz*cosRy + cosRx*sinRy);
    out_matWorld._32 = -sinRx*cosRz;
    out_matWorld._33 = (-sinRx*-sinRz*-sinRy + cosRx*cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDx9Util::setWorldMatrix_RzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDx9Camera* pCam = P_CAM;
    float sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    float cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];

    out_matWorld._11 = cosRz*pCam->_vMatrixView._11 + sinRz*pCam->_vMatrixView._12;
    out_matWorld._12 = cosRz*pCam->_vMatrixView._21 + sinRz*pCam->_vMatrixView._22;
    out_matWorld._13 = cosRz*pCam->_vMatrixView._31 + sinRz*pCam->_vMatrixView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*pCam->_vMatrixView._11 + cosRz*pCam->_vMatrixView._12;
    out_matWorld._22 = -sinRz*pCam->_vMatrixView._21 + cosRz*pCam->_vMatrixView._22;
    out_matWorld._23 = -sinRz*pCam->_vMatrixView._31 + cosRz*pCam->_vMatrixView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_vMatrixView._13;
    out_matWorld._32 = pCam->_vMatrixView._32;
    out_matWorld._33 = pCam->_vMatrixView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDx9Util::setWorldMatrix_ScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;

    out_matWorld._11 = prm_pActor->_SX / fRateScale;
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = prm_pActor->_SY / fRateScale;
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = prm_pActor->_SZ / fRateScale;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
//UINT32 GgafDx9Util::max3(UINT32 a, UINT32 b, UINT32 c) {
//	if (a > b) {
//		if (a > c) {
//			return a;
//		} else {
//			return c;
//		}
//	} else {
//		if (b > c) {
//			return b;
//		} else {
//			return c;
//		}
//	}
//}

