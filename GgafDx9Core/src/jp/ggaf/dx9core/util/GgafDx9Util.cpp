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
//�L���������� angle�l�� 0 �` 360,000 �� �x���@��1000�{�̐��x�����B�ꉞ���ꂪ��{�B
//s_ang �͌v�Z�p�A�e�[�u���C���f�b�N�X�p�ɐ��x�𗎂Ƃ���  0 �` 3600 �̒P�ʌn������
//
//���Ɏ���]�ƕ��ʂ̒��S�p�̕\����ʂɂ���
//������]�̊p�x�̕ϐ����\����
//����]�� rot �܂��� r �ŏ����悤�ɂ���B angFace �Ƃ��A�Ƃɂ��� R ���ϐ����ɓ����Ă�
//���၄
//angRx angFaceX rotX rX Rx rX radRx ��� X����]angle�l
//angRy angFaceY rotY rY Ry rY radRy ��� Y����]angle�l
//angRz angFaceZ rotZ rX Rz rZ radRz ��� Z����]angle�l
//���������̎��X�ɂ�萸�x���ς���Ă��邩������Ȃ��B
//�܂�����n(X���͉E�֍s���Ɛ��AY���͏�ɍs���Ɛ��AZ���͉��֍s���Ɛ��j��O��Ƃ��Ă��邽�߁A
//�����̎���]angle�l�̐��̒l�Ƃ͎��������Ĕ����v���̕�����\���B
//X����]�l ��� X���̐��̕����������č���肪���̉�]�p�x
//Y����]�l ��� Y���̐��̕����������č���肪���̉�]�p�x
//Z����]�l ��� Z���̐��̕����������č���肪���̉�]�p�x
//
//�����ʂ̒��S�p�A�܂��͒����̐����p�x�̕ϐ����\����
//���镽�ʌn�ɑ΂��Ă̒��S�p�͂ǂ̕��ʂ��������悤�ɂ���B
//
//angXY ���XY���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� X���̐��̕������E�AY���̐��̕�������A�R���̕��� (x,y)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//angXZ ���XZ���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� X���̐��̕������E�AZ���̐��̕�������A�R���̕��� (x,z)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//angZX ���ZX���ʂł̒��S�p�̒l�B���̊p�x�Ƃ� Z���̐��̕������E�AX���̐��̕�������A�R���̕��� (z,x)=(1,0)���p�x0���Ƃ��A���_�𒆐S�ɔ����v���
//         angXZ �Ƃ͊p�x�̐������t�ɂȂ�܂��B
//
//�����ʂ̒��S�p�A�܂��͒����̐����p�x���A����]�Ƃ݂Ȃ��Čv�Z����ꍇ�̕ϐ����\����
//angXY �� �R������Ԃ� Z=0 ��XY���ʏ�Ɍ���AangRz �Ƃ݂Ȃ����Ƃ��o���܂��B
//���̂悤�ɂ��Čv�Z���s���Ă���ӏ�������A
//�u���ʂ̒��S�p�A�܂��͒����̐����p�x �Ƃ��Ēl�����߂����ǂ��A����]�Ƃ��ēǂݑւ����A�����́A�g�����������v
//�Ƃ����ꍇ�� rotXY �Ƃ����ϐ��ɂ��Ă��܂��B
//angXY -> angRz �͊p�x0���̈ʒu(�����x�N�g��(x,y,z)=(1,0,0))�A���̉�]��������v����̂ł킩��₷���ł����A
//
//�܂� rotXY = angXY or angRz
//�u�߂��v
//angXZ -> angRy �̓ǂݑւ��͐��̉�]������ angXZ �� angRy �ŋt�ɂȂ��Ă��܂��܂��B
//angZX -> angRy �̏ꍇ�͐��̉�]�����͈�v���܂����A�p�x0���̈ʒu��(x,y,z)=(1,0,0) �ł͂Ȃ��Ȃ��Ă��܂����߁A�L�����̎���]�ɂ͌����܂���
//
//������
//rotXZ = angXZ or angRy_rev
//�̂悤�� "rev" �u�t����ł���v�Ə����悤�ɂ����B














bool GgafDx9Util::_was_inited_flg = false;
int GgafDx9Util::COS_UNITLEN[S_ANG360];
int GgafDx9Util::SIN_UNITLEN[S_ANG360];
int GgafDx9Util::TAN_UNITLEN[S_ANG360];
int GgafDx9Util::RAD_UNITLEN[S_ANG360];
float GgafDx9Util::PARABORA[S_ANG360];
float GgafDx9Util::COS[S_ANG360];
float GgafDx9Util::SIN[S_ANG360];
float GgafDx9Util::RAD[S_ANG360];

angle GgafDx9Util::SLANT2ANG[10000 + 1];
angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Z[S_ANG90+1][S_ANG90+1];
angle GgafDx9Util::PROJANG_XY_XZ_TO_ROTANG_Y_REV[S_ANG90+1][S_ANG90+1];

GgafDx9SphereRadiusVectors GgafDx9Util::_srv = GgafDx9SphereRadiusVectors();

void GgafDx9Util::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < S_ANG360; ang++) {
        double rad = (PI * 2.0f * ang) / S_ANG360;
        COS_UNITLEN[ang] = (int)(cos(rad) * LEN_UNIT);
        SIN_UNITLEN[ang] = (int)(sin(rad) * LEN_UNIT);
        TAN_UNITLEN[ang] = (int)(tan(rad) * LEN_UNIT);
        RAD_UNITLEN[ang] = (int)(rad * LEN_UNIT);

        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        PARABORA[ang] = (float)((double)((ang-(S_ANG360/2))*(ang-(S_ANG360/2))) /  (double)(-1.0*(S_ANG360/2)*(S_ANG360/2)) + 1.0);
        //PARABORA[0] = 0 , PARABORA[S_ANG180] = 1,  PARABORA[S_ANG360-1] = 0 �� y = -x^2  �������̒l���Ƃ�
    }

    COS_UNITLEN[0] = 1 * LEN_UNIT;
    COS_UNITLEN[S_ANG90] = 0;
    COS_UNITLEN[S_ANG180] = -1 * LEN_UNIT;
    COS_UNITLEN[S_ANG270] = 0;

    SIN_UNITLEN[0] = 0;
    SIN_UNITLEN[S_ANG90] = 1 * LEN_UNIT;
    SIN_UNITLEN[S_ANG180] = 0;
    SIN_UNITLEN[S_ANG270] = -1 * LEN_UNIT;

    TAN_UNITLEN[0] = 0;
    TAN_UNITLEN[S_ANG90] = LONG_MAX;
    TAN_UNITLEN[S_ANG180] = 0;
    TAN_UNITLEN[S_ANG270] = -1 * LONG_MAX;
    //TAN_UNITLEN[ANGLE360] = 0;

    COS[0] = 1;
    COS[S_ANG90] = 0;
    COS[S_ANG180] = -1;
    COS[S_ANG270] = 0;

    SIN[0] = 0;
    SIN[S_ANG90] = 1;
    SIN[S_ANG180] = 0;
    SIN[S_ANG270] = -1;

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
    for (int ang = 0; ang <= 4500; ang++) {
        rad = (PI * 2.0f * ang) / 36000;
        vx = cos(rad);
        vy = sin(rad);
        if (vx == 0) {
            slant = 0.0f;
        } else {
            slant = (float)(vy / vx);
        }
        index_slant = (int)(slant * 10000);
        d_index_slant = index_slant - index_slant_prev;
        for (int i = index_slant_prev+1, d = 1; i <= index_slant; i++, d++) {
            if (i > 10000) {
                _TRACE_("���x�����z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(ang*10));
            }
            //��������i�������A�o�E�g�̂��Ɓj
            SLANT2ANG[i] = (angle)( ((ang-1) + (1.0*d)/(1.0*d_index_slant))*10.0 );
        }
        index_slant_prev = index_slant;
    }
    d_index_slant = 10000 - index_slant_prev;
    for (int i = index_slant_prev+1, d = 1; i <= 10000; i++, d++) {
        if (i > 10000) {
            _TRACE_("���x�����z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(45000));
        }
        SLANT2ANG[i] = (angle)( (4500-1) + (1.0*d)/(1.0*d_index_slant) );
    }

    //<PROJ_ANG2ROT_ANG> �i2009/10/20 �o�܁E�E�E�������邽�߂Ȃ牽�ł�����Ă݂悤�j
    //��������x�N�g������AXY���ʁAZY���ʂɓ��e�������ɂł��鎲�Ƃ̊p�i���ꂼ��XY�ˉe�p�AZY�ˉe�p�ƌĂԂ��ƂƂ���j�ƁA
    //���̕����x�N�g���̒P�ʃx�N�g�����w���P�ʋ��̈ܓx�ƌo�x�iZ����]�p�AY����]�p�j��R���邱�Ƃ�ړI�Ƃ���B
    //�܂�AXY�ˉe�p�AZY�ˉe�p �� Z����]�p�AY����]�p �̓ǂݑւ��������ɍs������
    //XY�ˉe�p90�x�� * ZY�ˉe�p90�x�� ��z��v�f�A�l��Z����]�p�AY����]�p��l�Ƃ���z����\�z�B




    double nvx,nvy,nvz;
    double prj_rad_xy,prj_rad_xz;
    s_ang rz, ry_rev;

    vx = 1.0;
    for (s_ang prj_ang_xy = 0; prj_ang_xy <= S_ANG90; prj_ang_xy++) {
        prj_rad_xy = (PI * 2.0 * prj_ang_xy) / (1.0*S_ANG360);
        vy = tan(prj_rad_xy);

        for (s_ang prj_ang_xz = 0; prj_ang_xz <= S_ANG90; prj_ang_xz++) {
            prj_rad_xz = (PI * 2.0 * prj_ang_xz) / (1.0*S_ANG360);
            //�����x�N�g�����쐬
            //vx�������G�C���ƌ��߂�


            vz = tan(prj_rad_xz);

            //vx,vy,vz �𐳋K������B
            //���߂�P�ʃx�N�g���� (X,Y,Z) �Ƃ���� (X,Y,Z) = t(vx,vy,vz)
            //�֌W��   X=t*vx; Y=t*vy; Z=t*vz; ��� (1) �𓾂�
            //�P�ʋ��� X^2 + Y^2 + Z^2 = 1 ���(2)
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
                    (unsigned __int16) (nvx*10000),
                    (unsigned __int16) (nvy*10000),
                    (unsigned __int16) (nvz*10000),
                    rz,
                    ry_rev,
                    50
            );
            PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz] = rz*ANGLE_RATE;
            PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*ANGLE_RATE;


           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
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

void GgafDx9Util::getRadiationAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
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

//_TRACE_("GgafDx9Util::getRzRyAng "<<vx<<","<<vy<<","<<vz);
    angle prj_rXY = getAngle2D(abs(vx), abs(vy));
    angle prj_rXZ = getAngle2D(abs(vx), abs(vz)); //ZX���ʂ���Ȃ���XZ���ʂ�I��]������Y����]�Ƌt��I
//_TRACE_("prj_rXY,prj_rXZ="<<prj_rXY<<","<<prj_rXZ);
    angle rotZ     = PROJANG_XY_XZ_TO_ROTANG_Z[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
    angle rotY_rev = PROJANG_XY_XZ_TO_ROTANG_Y_REV[(int)(prj_rXY/100.0)][(int)(prj_rXZ/100.0)];
//_TRACE_("rotZ,rotY_rev="<<rotZ<<","<<rotY_rev);
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
        _TRACE_("���������ł���getRzRyAngle_new");
    }
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

void GgafDx9Util::getRzRyAng(float nvx, float nvy, float nvz, angle& out_angFaceZ, angle& out_angFaceY) {
    getRzRyAng((int)(nvx*LEN_UNIT*PX_UNIT*100),
                      (int)(nvy*LEN_UNIT*PX_UNIT),
                      (int)(nvz*LEN_UNIT*PX_UNIT),
                      out_angFaceZ,
                      out_angFaceY );


}


//���ݖ��g�p�B��荂����getRzRyAngle���g�p���Ă���B
void GgafDx9Util::getRzRyAngle_old(int x,
                                int y,
                                int z,
                                float& out_nvx,
                                float& out_nvy,
                                float& out_nvz,
                                angle& out_angFaceZ,
                                angle& out_angFaceY ) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    //vx,vy,vz �𐳋K������B
    //���߂�P�ʃx�N�g���� (X,Y,Z) �Ƃ���� (X,Y,Z) = t(vx,vy,vz)
    //�֌W��   X=t*vx; Y=t*vy; Z=t*vz; ��� (1) �𓾂�
    //�P�ʋ��� X^2 + Y^2 + Z^2 = 1 ���(2)
    //(1)(2)��A�������āAt �ɂ��ĉ����B
    //t = 1 / sqrt(vx^2 + vy^2 + vz^2)
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    //���߂� t �� (1) �ɑ���� (X,Y,Z) �����߂�B
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;

    //GgafDx9SphereRadiusVectors ���g���ĒP�ʃx�N�g�������]�p�����Ƃ߂�
    //�A�� GgafDx9SphereRadiusVectors �̃x�N�g�����x�� 10000���悶�������ł���B(LEN_UNIT*10)
    //����ɁA�����̃x�N�g���v�f�͑S�Đ��̒l�i1/8 �̋����j�����Ȃ̂ł��B����āA���낢��ꍇ�킯����B

    static s_ang rZ, rY;
    _srv.getFaceAngClosely(
            (unsigned __int16) abs(out_nvx*10000),
            (unsigned __int16) abs(out_nvy*10000),
            (unsigned __int16) abs(out_nvz*10000),
            rZ,
            rY
    );

    //x > 0; y > 0; z > 0 �̗̈����ی��Ƃ���
    //x < 0; y > 0; z > 0 �̗̈����ی��Ƃ���
    //x < 0; y < 0; z > 0 �̗̈���O�ی��Ƃ���
    //x > 0; y < 0; z > 0 �̗̈���l�ی��Ƃ���
    //x > 0; y > 0; z < 0 �̗̈���܏ی��Ƃ���
    //x < 0; y > 0; z < 0 �̗̈���Z�ی��Ƃ���
    //x < 0; y < 0; z < 0 �̗̈��掵�ی��Ƃ���
    //x > 0; y < 0; z < 0 �̗̈��攪�ی��Ƃ���
    //�ی��ɂ���ĉ�]�p��␳
    if (vx >= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //��O�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //��l�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //��܏ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //��Z�ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //�掵�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //�攪�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else {
        _TRACE_("���������ł���");
    }

    //_TRACE_("(x,y,z)=("<<x<<","<<y<<","<<z<<") (out_nvx,nvy,nvz)=("<<out_nvx<<","<<out_nvy<<","<<out_nvz<<") RZ="<<out_angFaceZ<<" RY="<<out_angFaceY);
}

//���ݖ��g�p�B��荂����getRzRyAngle���g�p���Ă���B
void GgafDx9Util::getRzRyAngle_old(int x, int y, int z, angle& out_angFaceZ, angle& out_angFaceY, int s) {
    static float vx, vy, vz, t;
    vx = ((float)x) / LEN_UNIT;
    vy = ((float)y) / LEN_UNIT;
    vz = ((float)z) / LEN_UNIT;
    t = 1 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    static s_ang rZ, rY;

    _srv.getFaceAngClosely(
            (unsigned __int16) abs(t*vx*10000),
            (unsigned __int16) abs(t*vy*10000),
            (unsigned __int16) abs(t*vz*10000),
            rZ,
            rY,
            s
    );
    if (vx >= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //��O�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //��l�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //��܏ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //��Z�ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //�掵�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //�攪�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else {
        _TRACE_("���������ł���");
    }
}

//���ݖ��g�p�B��荂����getRzRyAngle���g�p���Ă���B
void GgafDx9Util::getRzRyAngle_old(float vx, float vy, float vz, angle& out_angFaceZ, angle& out_angFaceY, int s) {
    static s_ang rZ, rY;
    _srv.getFaceAngClosely(
            (unsigned __int16) abs(vx*10000),
            (unsigned __int16) abs(vy*10000),
            (unsigned __int16) abs(vz*10000),
            rZ,
            rY,
            s
    );
    if (vx >= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //��O�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 + rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //��l�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG360 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //��܏ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //��Z�ی�
        out_angFaceZ = rZ * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //�掵�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = (S_ANG180 - rY) * ANGLE_RATE;
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //�攪�ی�
        out_angFaceZ = (S_ANG360 - rZ) * ANGLE_RATE;
        out_angFaceY = rY * ANGLE_RATE;
    } else {
        _TRACE_("���������ł���");
    }
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
    static int Xsign, Ysign, Zsign;
    static s_ang rZ, rY_rev;

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
    static unsigned __int16 vx, vy, vz;
    //  _TRACE_("prm_angFaceZ="<<prm_angFaceZ<<"/prm_angFaceY="<<prm_angFaceY<<" rY="<<rY<<"/rZ="<<rZ<<")");
    //  _TRACE_("("<<Xsign<<","<<Ysign<<","<<Zsign<<")");
    _srv.getVectorClosely(rY_rev, rZ, vx, vy, vz);
    out_nvx = Xsign * vx / 10000.0f;
    out_nvy = Ysign * vy / 10000.0f;
    out_nvz = Zsign * vz / 10000.0f;
}




void GgafDx9Util::setWorldMatrix_ScRxRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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





void GgafDx9Util::setWorldMatrix_ScRzRyMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    //sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    //cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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





void GgafDx9Util::setWorldMatrix_RxRzRyScMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy*Sx,          sinRz*Sy,                         cosRz*-sinRy*Sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*Sx,    cosRx*cosRz*Sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*Sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*Sx,   -sinRx*cosRz*Sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*Sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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

    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;

    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;

    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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
    static s_ang s_RZ;
    s_RZ = prm_pActor->_RZ / ANGLE_RATE;

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
    static s_ang s_RZ;
    static float Sx, Sy, Sz;

    s_RZ = prm_pActor->_RZ / ANGLE_RATE;
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    static float dx, dy, dz;

    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;
    dx = prm_pActor->_fX;
    dy = prm_pActor->_fY;
    dz = prm_pActor->_fZ;

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
    static float Sx, Sy, Sz;
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = pCAM->_vMatrixView._11 * Sx;
    out_matWorld._12 = pCAM->_vMatrixView._21 * Sy;
    out_matWorld._13 = pCAM->_vMatrixView._31 * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCAM->_vMatrixView._12 * Sx;
    out_matWorld._22 = pCAM->_vMatrixView._22 * Sy;
    out_matWorld._23 = pCAM->_vMatrixView._32 * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCAM->_vMatrixView._13 * Sx;
    out_matWorld._32 = pCAM->_vMatrixView._23 * Sy;
    out_matWorld._33 = pCAM->_vMatrixView._33 * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}






void GgafDx9Util::setWorldMatrix_ScRzBxyzMv(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    static float fRateScale = 1.0f * LEN_UNIT;
    static float sinRz, cosRz, Sx, Sy, Sz;
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

    out_matWorld._11 = Sx*cosRz*pCAM->_vMatrixView._11 + Sx*sinRz*pCAM->_vMatrixView._12;
    out_matWorld._12 = Sx*cosRz*pCAM->_vMatrixView._21 + Sx*sinRz*pCAM->_vMatrixView._22;
    out_matWorld._13 = Sx*cosRz*pCAM->_vMatrixView._31 + Sx*sinRz*pCAM->_vMatrixView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*pCAM->_vMatrixView._11 + Sy*cosRz*pCAM->_vMatrixView._12;
    out_matWorld._22 = Sy*-sinRz*pCAM->_vMatrixView._21 + Sy*cosRz*pCAM->_vMatrixView._22;
    out_matWorld._23 = Sy*-sinRz*pCAM->_vMatrixView._31 + Sy*cosRz*pCAM->_vMatrixView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*pCAM->_vMatrixView._13;
    out_matWorld._32 = Sz*pCAM->_vMatrixView._32;
    out_matWorld._33 = Sz*pCAM->_vMatrixView._33;
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
    static float sinRx, cosRx, sinRy, cosRy, sinRz, cosRz;
    static float fRateScale = 1.0f * LEN_UNIT;
    static float Sx, Sy, Sz;
    D3DXMATRIX matScRxRzRyMv;
    sinRx = GgafDx9Util::SIN[prm_pActor->_RX / ANGLE_RATE];
    cosRx = GgafDx9Util::COS[prm_pActor->_RX / ANGLE_RATE];
    sinRy = GgafDx9Util::SIN[prm_pActor->_RY / ANGLE_RATE];
    cosRy = GgafDx9Util::COS[prm_pActor->_RY / ANGLE_RATE];
    sinRz = GgafDx9Util::SIN[prm_pActor->_RZ / ANGLE_RATE];
    cosRz = GgafDx9Util::COS[prm_pActor->_RZ / ANGLE_RATE];
    Sx = prm_pActor->_SX / fRateScale;
    Sy = prm_pActor->_SY / fRateScale;
    Sz = prm_pActor->_SZ / fRateScale;

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





//DWORD GgafDx9Util::max3(DWORD a, DWORD b, DWORD c) {
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

