#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;



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



bool GgafDxUtil::_was_inited_flg = false;

float GgafDxUtil::PARABORA[D360SANG+1];
float GgafDxUtil::COS[D360SANG+1];
float GgafDxUtil::SIN[D360SANG+1];
float GgafDxUtil::RAD[D360SANG+1];

float GgafDxUtil::ROOT_1_MINUS_XX[1000];


angle GgafDxUtil::SLANT2ANG[100000 + 1];

//����Ȃ񂢂�̂ł́I
//angle GgafDxUtil::PROJANG_XY_ZX_YZ_TO_ROTANG_Z[D90SANG+1][D90SANG+1];


angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_Z[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_Y_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_X_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_Y[D90SANG+1][D90SANG+1];


UINT32 GgafDxUtil::BITNUM[33];
GgafDxSphereRadiusVectors GgafDxUtil::_srv = GgafDxSphereRadiusVectors();

void GgafDxUtil::init() {
    if (_was_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < D360SANG+1; ang++) {
        double rad = (PI * 2.0 * ang) / D360SANG;


        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        PARABORA[ang] = (float)((double)((ang-(D360SANG/2))*(ang-(D360SANG/2))) /  (double)(-1.0*(D360SANG/2)*(D360SANG/2)) + 1.0);
        //PARABORA[0] = 0 , PARABORA[D180SANG] = 1,  PARABORA[D360SANG-1] = 0 �� y = -x^2  �������̒l���Ƃ�
    }

    COS[D0SANG]   =  1;
    COS[D90SANG]  =  0;
    COS[D180SANG] = -1;
    COS[D270SANG] =  0;
    COS[D360SANG] =  1;
    SIN[D0SANG]   =  0;
    SIN[D90SANG]  =  1;
    SIN[D180SANG] =  0;
    SIN[D270SANG] = -1;
    SIN[D360SANG] =  0;
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
        rad = (PI * 2.0 * ang) / 360000;
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
        SLANT2ANG[i] = (angle)( (45000-1) + (1.0*d)/(1.0*d_index_slant) );
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
    for (s_ang prj_ang_xy = 0; prj_ang_xy <= D90SANG; prj_ang_xy++) {
        prj_rad_xy = (PI * 2.0 * prj_ang_xy) / (1.0*D360SANG);
        vy = tan(prj_rad_xy);

        for (s_ang prj_ang_xz = 0; prj_ang_xz <= D90SANG; prj_ang_xz++) {
            prj_rad_xz = (PI * 2.0 * prj_ang_xz) / (1.0*D360SANG);
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
            PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz] = rz*SANG_RATE;
            PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*SANG_RATE;


           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }



    vz = 1.0;
    for (s_ang prj_ang_zy = 0; prj_ang_zy <= D90SANG; prj_ang_zy++) {
        prj_rad_zy = (PI * 2.0 * prj_ang_zy) / (1.0*D360SANG);
        vy = tan(prj_rad_zy);

        for (s_ang prj_ang_zx = 0; prj_ang_zx <= D90SANG; prj_ang_zx++) {
            prj_rad_zx = (PI * 2.0 * prj_ang_zx) / (1.0*D360SANG);
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
            //����͏�ŋ��߂�ry_rev��D90ANG����������l�ł���B
            PROJANG_ZY_ZX_TO_ROTANG_X_REV[prj_ang_zy][prj_ang_zx] = rx_rev*SANG_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx] = D90ANG - ry_rev*SANG_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_Y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = D90ANG - "<<ry_rev<<"*SANG_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_Y[prj_ang_zy][prj_ang_zx]);

           //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_Z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_Y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }

    //ROOT_1_MINUS_XX�̐ݒ�
    for (int i = 0; i < 1000; i++) {
        ROOT_1_MINUS_XX[i] = sqrt(1.0 - ((double)i/1000.0) * ((double)i/1000.0));
    }

    BITNUM[ 0] = 0;
    BITNUM[ 1] = (0x1);            //0b 00000000 00000000 00000000 00000001
    BITNUM[ 2] = (0x2);            //0b 00000000 00000000 00000000 00000010
    BITNUM[ 3] = (0x4);            //0b 00000000 00000000 00000000 00000100
    BITNUM[ 4] = (0x8);            //0b 00000000 00000000 00000000 00001000
    BITNUM[ 5] = (0x10);           //0b 00000000 00000000 00000000 00010000
    BITNUM[ 6] = (0x20);           //0b 00000000 00000000 00000000 00100000
    BITNUM[ 7] = (0x40);           //0b 00000000 00000000 00000000 01000000
    BITNUM[ 8] = (0x80);           //0b 00000000 00000000 00000000 10000000
    BITNUM[ 9] = (0x100);          //0b 00000000 00000000 00000001 00000000
    BITNUM[10] = (0x200);          //0b 00000000 00000000 00000010 00000000
    BITNUM[11] = (0x400);          //0b 00000000 00000000 00000100 00000000
    BITNUM[12] = (0x800);          //0b 00000000 00000000 00001000 00000000
    BITNUM[13] = (0x1000);         //0b 00000000 00000000 00010000 00000000
    BITNUM[14] = (0x2000);         //0b 00000000 00000000 00100000 00000000
    BITNUM[15] = (0x4000);         //0b 00000000 00000000 01000000 00000000
    BITNUM[16] = (0x8000);         //0b 00000000 00000000 10000000 00000000
    BITNUM[17] = (0x10000);        //0b 00000000 00000001 00000000 00000000
    BITNUM[18] = (0x20000);        //0b 00000000 00000010 00000000 00000000
    BITNUM[19] = (0x40000);        //0b 00000000 00000100 00000000 00000000
    BITNUM[20] = (0x80000);        //0b 00000000 00001000 00000000 00000000
    BITNUM[21] = (0x100000);       //0b 00000000 00010000 00000000 00000000
    BITNUM[22] = (0x200000);       //0b 00000000 00100000 00000000 00000000
    BITNUM[23] = (0x400000);       //0b 00000000 01000000 00000000 00000000
    BITNUM[24] = (0x800000);       //0b 00000000 10000000 00000000 00000000
    BITNUM[25] = (0x1000000);      //0b 00000001 00000000 00000000 00000000
    BITNUM[26] = (0x2000000);      //0b 00000010 00000000 00000000 00000000
    BITNUM[27] = (0x4000000);      //0b 00000100 00000000 00000000 00000000
    BITNUM[28] = (0x8000000);      //0b 00001000 00000000 00000000 00000000
    BITNUM[29] = (0x10000000);     //0b 00010000 00000000 00000000 00000000
    BITNUM[30] = (0x20000000);     //0b 00100000 00000000 00000000 00000000
    BITNUM[31] = (0x40000000);     //0b 01000000 00000000 00000000 00000000
    BITNUM[32] = (0x80000000);     //0b 10000000 00000000 00000000 00000000
}



void GgafDxUtil::getWayAngle2D(int prm_vx_Center,
                               int prm_vy_Center,
                               int prm_nWay,
                               angle prm_angClearance,
                               angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_nWay, prm_angClearance, out_paAngle);
}

void GgafDxUtil::getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle) {
    int angstart = addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(angstart, prm_angClearance * i);
    }
}

void GgafDxUtil::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = addAng(prm_angStart, (angle)(1.0f * D360ANG / prm_nWay * i));
    }
}

void GgafDxUtil::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    getNormalizeVectorZY(prm_Rz, prm_Ry , vx, vy, vz);
    getRzRyAng(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-�X�O�xX����]RzRy����ւ�
    out_Rz = D360ANG-out_Rz; //Y����Z���l���邽�߁A�������ς�遁�t��]��360�������
}



//void GgafDxUtil::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
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

//void GgafDxUtil::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tX, coord prm_tY, coord prm_tZ,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    getRzRyAng(prm_tX, prm_tY, prm_tZ, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDxUtil::addAng(angle prm_angNow, angle prm_angOffset) {
    static angle angAdd;
    angAdd = prm_angNow + prm_angOffset;
    while (angAdd >= D360ANG) {
        angAdd -= D360ANG;
    }
    while (angAdd < 0) {
        angAdd += D360ANG;
    }
    return angAdd;
}

angle GgafDxUtil::getAngDiff(angle angFrom, angle angTo, int prm_way) {
    if (prm_way == TURN_CLOSE_TO) {
        if (0 <= angFrom && angFrom < D180ANG) {
            if (0 <= angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angTo == angFrom) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (angFrom < angTo && angTo < angFrom + D180ANG) {
                return angTo - angFrom;
            } else if (angTo == angFrom + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (angFrom + D180ANG < angTo && angTo <= D360ANG) {
                return -1 * (angFrom + (D360ANG - angTo));
            } else {
                //��������
                _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDxUtil::getDiffAngle �A���O���l���͈͊O�ł�(1)�B\n"<<
                                           "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= angFrom && angFrom <= D360ANG) {
            if (0 <= angTo && angTo < angFrom - D180ANG) {
                return D360ANG - angFrom + angTo;
            } else if (angTo == angFrom - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (angFrom - D180ANG < angTo && angTo < angFrom) {
                return -1 * (angFrom - angTo);
            } else if (angFrom == angTo) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (angFrom < angTo && angTo <= D360ANG) {
                return angTo - angFrom;
            } else {
                //��������
                _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
                throwGgafCriticalException("GgafDxUtil::getDiffAngle �A���O���l���͈͊O�ł�(2)�B\n"<<
                                           "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (angFrom <= angTo) {
            return angTo - angFrom;
        } else {
            return (D360ANG - angFrom) + angTo;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (angFrom >= angTo) {
            return -(angFrom - angTo);
        } else {
            return -(angFrom + (D360ANG - angTo));
        }
    } else {
        _TRACE_("GgafDxUtil::getAngDiff bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
        throwGgafCriticalException("GgafDxUtil::getDiffAngle  prm_way = TURN_CLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE �ȊO���w�肳��Ă��܂��B");
    }

    _TRACE_("bad angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
    throwGgafCriticalException("GgafDxUtil::getDiffAngle  ���̂�����p�̋��������߂�܂���B(1) \n"<<
                               "angFrom=" << angFrom << "/angTo=" << angTo<<"/prm_way="<<prm_way);
}

void GgafDxUtil::rotXY(int prm_X, int prm_Y, angle prm_ang, int& out_X, int& out_Y) {
    out_X = (int)(floor((prm_X * GgafDxUtil::COS[prm_ang/SANG_RATE]) - (prm_Y * GgafDxUtil::SIN[prm_ang/SANG_RATE])));
    out_Y = (int)(floor((prm_X * GgafDxUtil::SIN[prm_ang/SANG_RATE]) + (prm_Y * GgafDxUtil::COS[prm_ang/SANG_RATE])));
}

// �����̓����蔻�� (x11,y11)-(x12,y12) �~ (x21,y21)-(x22,y22)
bool GgafDxUtil::chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22) {

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

int GgafDxUtil::getDistance(int x1, int y1, int x2, int y2) {
    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}
//int GgafDxUtil::getDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
//    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))) + (((double)(z2 - z1)) * ((double)(z2 - z1))));
//}


void GgafDxUtil::getRzRyAng(coord vx,
                            coord vy,
                            coord vz,
                            angle& out_angRZ,
                            angle& out_angRY ) {

    if (vz == 0) {
        out_angRZ = getAngle2D(vx, vy);
        out_angRY = 0;
        return;
    }



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

    angle rotZ, rotY_rev;
    if (0 <= prj_rXZ && prj_rXZ <= D45ANG) {
        rotZ = PROJANG_XY_XZ_TO_ROTANG_Z[(int)(prj_rXY/100)][(int)(prj_rXZ/100)];
        rotY_rev = PROJANG_XY_XZ_TO_ROTANG_Y_REV[(int)(prj_rXY/100)][(int)(prj_rXZ/100)];
    } else if (D45ANG <= prj_rXZ && prj_rXZ <= D90ANG) {
        rotZ = PROJANG_ZY_ZX_TO_ROTANG_X_REV[(int)(prj_rZY/100)][(int)(prj_rZX/100)];
        rotY_rev = D90ANG - PROJANG_ZY_ZX_TO_ROTANG_Y[(int)(prj_rZY/100)][(int)(prj_rZX/100)];
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng �͈͂��j�����Ă܂��Bprj_rXZ="<<prj_rXZ);
    }
#if MY_DEBUG
    if (0 <= prj_rXY && prj_rXY < D45ANG) {
        //OK
    } else if (D45ANG <= prj_rXY && prj_rXY <= D90ANG) {
        //OK
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng �͈͂��j�����Ă܂��Bprj_rXY="<<prj_rXY<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
#endif
    //�ی��ɂ���ĉ�]�p��␳
    if (vx >= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angRZ = rotZ;
        out_angRY = (D360ANG - rotY_rev);
    } else if (vx <= 0 && vy >= 0 && vz >= 0) { //���ی�
        out_angRZ = rotZ;
        out_angRY = (D180ANG + rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz >= 0) { //��O�ی�
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D180ANG + rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz >= 0) { //��l�ی�
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D360ANG - rotY_rev);
    } else if (vx >= 0 && vy >= 0 && vz <= 0) { //��܏ی�
        out_angRZ = rotZ;
        out_angRY = rotY_rev;
    } else if (vx <= 0 && vy >= 0 && vz <= 0) { //��Z�ی�
        out_angRZ = rotZ;
        out_angRY = (D180ANG - rotY_rev);
    } else if (vx <= 0 && vy <= 0 && vz <= 0) { //�掵�ی�
        out_angRZ = (D360ANG - rotZ);
        out_angRY = (D180ANG - rotY_rev);
    } else if (vx >= 0 && vy <= 0 && vz <= 0) { //�攪�ی�
        out_angRZ = (D360ANG - rotZ);
        out_angRY = rotY_rev;
    } else {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng ���肦�܂���Bvx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }

#if MY_DEBUG
    if (D360ANG < out_angRZ || 0 > out_angRZ || D360ANG < out_angRY || 0 > out_angRY) {
        throwGgafCriticalException("GgafDxUtil::getRzRyAng �͈͊O�ł��v�����B\n out_angRZ,out_angRY="<<out_angRZ<<","<<out_angRY<<" vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
#endif
//    out_angRZ = simplifyAng(out_angRZ);
//    out_angRY = simplifyAng(out_angRY);
}


void GgafDxUtil::getRzRyAng(coord vx,
                            coord vy,
                            coord vz,
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



void GgafDxUtil::getNormalizeVector(coord x,
                                    coord y,
                                    coord z,
                                    float& out_nvx,
                                    float& out_nvy,
                                    float& out_nvz) {
    dxcoord vx = C_DX(x);
    dxcoord vy = C_DX(y);
    dxcoord vz = C_DX(z);
    double t = 1.0 / sqrt_fast(vx * vx + vy * vy + vz * vz);
    out_nvx = t * vx;
    out_nvy = t * vy;
    out_nvz = t * vz;
}



void GgafDxUtil::getNormalizeVectorZY(angle prm_angFaceZ,
                                      angle prm_angFaceY,
                                      float& out_nvx,
                                      float& out_nvy,
                                      float& out_nvz) {
    //void GgafDxSphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angFaceZ, unsigned __int16& out_x, unsigned __int16& out_y, unsigned __int16& out_z) {
    //��]�p�ɂ���ďی����l�����AgetVectorClosely�̃p�����[�^�p(< 900)���o��
    int Xsign, Ysign, Zsign;
    s_ang rZ, rY_rev;

    if (0 <= prm_angFaceZ && prm_angFaceZ < D90ANG) {
        rZ = (prm_angFaceZ - D0ANG) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //��܏ی�
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //��Z�ی�
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //���ی�
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //���ی�
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: �Ȃ񂩂��������ł���(1) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else if (D90ANG <= prm_angFaceZ && prm_angFaceZ < D180ANG) {
        rZ = (D180ANG - prm_angFaceZ) / SANG_RATE;

        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //���ی�
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = 1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //���ی�
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = 1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //��܏ی�
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = 1;
            Ysign = 1;
            Zsign = -1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //��Z�ی�
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = 1;
            Zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: �Ȃ񂩂��������ł���(2) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }

    } else if (D180ANG <= prm_angFaceZ && prm_angFaceZ < D270ANG) {
        rZ = (prm_angFaceZ - D180ANG) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //��O�ی�
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //��l�ی�
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //�攪�ی�
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //�掵�ی�
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: �Ȃ񂩂��������ł���(3) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else if (D270ANG <= prm_angFaceZ && prm_angFaceZ <= D360ANG) {
        rZ = (D360ANG - prm_angFaceZ) / SANG_RATE;
        if (0 <= prm_angFaceY && prm_angFaceY < D90ANG) { //�攪�ی�
            rY_rev = prm_angFaceY / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = -1;
        } else if (D90ANG <= prm_angFaceY && prm_angFaceY < D180ANG) { //�掵�ی�
            rY_rev = (D180ANG - prm_angFaceY) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = -1;
        } else if (D180ANG <= prm_angFaceY && prm_angFaceY < D270ANG) { //��O�ی�
            rY_rev = (prm_angFaceY - D180ANG) / SANG_RATE;
            Xsign = -1;
            Ysign = -1;
            Zsign = 1;
        } else if (D270ANG <= prm_angFaceY && prm_angFaceY <= D360ANG) { //��l�ی�
            rY_rev = (D360ANG - prm_angFaceY) / SANG_RATE;
            Xsign = 1;
            Ysign = -1;
            Zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizeVectorZY: �Ȃ񂩂��������ł���(4) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
        }
    } else {
        throwGgafCriticalException("getNormalizeVectorZY: �Ȃ񂩂��������ł���(5) prm_angFaceZ="<<prm_angFaceZ<<" prm_angFaceY="<<prm_angFaceY);
    }
    UINT32 vx, vy, vz;
    _srv.getVectorClosely(rY_rev, rZ, vx, vy, vz);
    out_nvx = Xsign * (int)vx / 1000000.0;
    out_nvy = Ysign * (int)vy / 1000000.0;
    out_nvz = Zsign * (int)vz / 1000000.0;
}




void GgafDxUtil::setWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 =  Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 =  Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //�O�̂���
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDxUtil::RAD_UNITLEN[s_RX]/LEN_UNIT);
     D3DXMatrixRotationX(&matrixRotY, GgafDxUtil::RAD_UNITLEN[s_RY]/LEN_UNIT);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDxUtil::RAD_UNITLEN[s_RZ]/LEN_UNIT);
     D3DXMatrixTranslation(&matrixTrans, _X/LEN_UNIT, _Y/LEN_UNIT, _Z/LEN_UNIT);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void GgafDxUtil::setWorldMatrix_RzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy;
    out_matWorld._22 = cosRz;
    out_matWorld._23 = -sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RzRy(angle prm_Rz, angle prm_Ry, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    float sinRy = ANG_SIN(prm_Ry);
    float cosRy = ANG_COS(prm_Ry);
    float sinRz = ANG_SIN(prm_Rz);
    float cosRz = ANG_COS(prm_Rz);

    out_matWorld._11 = cosRz*cosRy;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy;
    out_matWorld._22 = cosRz;
    out_matWorld._23 = -sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = 0.0f;
    out_matWorld._42 = 0.0f;
    out_matWorld._43 = 0.0f;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_RxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

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

void GgafDxUtil::setWorldMatrix_RxRzRy(angle prm_RX, angle prm_RZ, angle prm_RY, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    float sinRx = ANG_SIN(prm_RX);
    float cosRx = ANG_COS(prm_RX);
    float sinRy = ANG_SIN(prm_RY);
    float cosRy = ANG_COS(prm_RY);
    float sinRz = ANG_SIN(prm_RZ);
    float cosRz = ANG_COS(prm_RZ);

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


void GgafDxUtil::setWorldMatrix_ScRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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



void GgafDxUtil::mulWorldMatrix_RzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*Sx  sinRz*Sy   cosRz*-sinRy*Sz   0 |
    //    | -sinRz*cosRy*Sx  cosRz*Sy  -sinRz*-sinRy*Sz   0 |
    //    |  sinRy*Sx        0          cosRy*Sz          0 |
    //    |  dx              dy         dz                1 |
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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

void GgafDxUtil::setWorldMatrix_RxRzRyScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy*Sx,          sinRz*Sy,                         cosRz*-sinRy*Sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*Sx,    cosRx*cosRz*Sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*Sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*Sx,   -sinRx*cosRz*Sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*Sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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


void GgafDxUtil::setWorldMatrix_RxRyRzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //    |                           cosRy*cosRz*Sx,                        cosRy*sinRz*Sy  ,      -sinRy*Sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*Sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*Sy), sinRx*cosRy*Sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*Sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*Sy), cosRx*cosRy*Sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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



void GgafDxUtil::setWorldMatrix_RxRzRxScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬.
    //��Y����]������܂���BRY�͂Q��ڂ�X����]�ƂȂ�
    //|         cosRz*Sx,                          sinRz*cosRy*Sy ,                          sinRz*sinRy*Sz, 0 |
    //|  cosRx*-sinRz*Sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*Sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*Sz), 0 |
    //| -sinRx*-sinRz*Sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*Sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*Sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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


void GgafDxUtil::setWorldMatrix_RzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    out_matWorld._11 = cosRz;
    out_matWorld._12 = sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz;
    out_matWorld._22 = cosRz;
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



void GgafDxUtil::setWorldMatrix_ScRzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |Sx*cosZ , Sx*sinZ , 0    , 0  |
    // |Sy*-sinZ, Sy*cosZ , 0    , 0  |
    // |0       , 0       , Sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx * cosRz;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy * -sinRz;
    out_matWorld._22 = Sy * cosRz;
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


void GgafDxUtil::setWorldMatrix_ScMvRxRzRy(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);
    dxcoord dx = prm_pActor->_fX;
    dxcoord dy = prm_pActor->_fY;
    dxcoord dz = prm_pActor->_fZ;

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




void GgafDxUtil::updateWorldMatrix_Mv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}







void GgafDxUtil::setWorldMatrix_BxyzScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;

    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = pCam->_matView._11 * Sx;
    out_matWorld._12 = pCam->_matView._21 * Sy;
    out_matWorld._13 = pCam->_matView._31 * Sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = pCam->_matView._12 * Sx;
    out_matWorld._22 = pCam->_matView._22 * Sy;
    out_matWorld._23 = pCam->_matView._32 * Sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_matView._13 * Sx;
    out_matWorld._32 = pCam->_matView._23 * Sy;
    out_matWorld._33 = pCam->_matView._33 * Sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}






void GgafDxUtil::setWorldMatrix_ScRzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;

    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

    out_matWorld._11 = Sx*cosRz*pCam->_matView._11 + Sx*sinRz*pCam->_matView._12;
    out_matWorld._12 = Sx*cosRz*pCam->_matView._21 + Sx*sinRz*pCam->_matView._22;
    out_matWorld._13 = Sx*cosRz*pCam->_matView._31 + Sx*sinRz*pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = Sy*-sinRz*pCam->_matView._11 + Sy*cosRz*pCam->_matView._12;
    out_matWorld._22 = Sy*-sinRz*pCam->_matView._21 + Sy*cosRz*pCam->_matView._22;
    out_matWorld._23 = Sy*-sinRz*pCam->_matView._31 + Sy*cosRz*pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = Sz*pCam->_matView._13;
    out_matWorld._32 = Sz*pCam->_matView._32;
    out_matWorld._33 = Sz*pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::mulWorldMatrix_ScRxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | Sx*cosRz*cosRy                           , Sx*sinRz       , Sx*cosRz*-sinRy                           , 0|
    // | (Sy* cosRx*-sinRz*cosRy + Sy*sinRx*sinRy), Sy*cosRx*cosRz , (Sy* cosRx*-sinRz*-sinRy + Sy*sinRx*cosRy), 0|
    // | (Sz*-sinRx*-sinRz*cosRy + Sz*cosRx*sinRy), Sz*-sinRx*cosRz, (Sz*-sinRx*-sinRz*-sinRy + Sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    D3DXMATRIX matScRxRzRyMv;
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);
    float Sx = SC_R(prm_pActor->_SX);
    float Sy = SC_R(prm_pActor->_SY);
    float Sz = SC_R(prm_pActor->_SZ);

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
}


void GgafDxUtil::setWorldMatrix_RxRzRyMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | cosRz*cosRy                        , sinRz       , cosRz*-sinRy                        , 0 |
    // | (cosRx*-sinRz*cosRy + sinRx*sinRy) , cosRx*cosRz , (cosRx*-sinRz*-sinRy + sinRx*cosRy) , 0 |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy), -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy), 0 |
    // | dx                                 , dy          , dz                                  , 1 |
    float sinRx = ANG_SIN(prm_pActor->_RX);
    float cosRx = ANG_COS(prm_pActor->_RX);
    float sinRy = ANG_SIN(prm_pActor->_RY);
    float cosRy = ANG_COS(prm_pActor->_RY);
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

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

void GgafDxUtil::setWorldMatrix_RzBxyzMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    GgafDxCamera* pCam = P_CAM;
    float sinRz = ANG_SIN(prm_pActor->_RZ);
    float cosRz = ANG_COS(prm_pActor->_RZ);

    out_matWorld._11 = cosRz*pCam->_matView._11 + sinRz*pCam->_matView._12;
    out_matWorld._12 = cosRz*pCam->_matView._21 + sinRz*pCam->_matView._22;
    out_matWorld._13 = cosRz*pCam->_matView._31 + sinRz*pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*pCam->_matView._11 + cosRz*pCam->_matView._12;
    out_matWorld._22 = -sinRz*pCam->_matView._21 + cosRz*pCam->_matView._22;
    out_matWorld._23 = -sinRz*pCam->_matView._31 + cosRz*pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = pCam->_matView._13;
    out_matWorld._32 = pCam->_matView._32;
    out_matWorld._33 = pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDxUtil::setWorldMatrix_ScMv(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._11 = SC_R(prm_pActor->_SX);
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = SC_R(prm_pActor->_SY);
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = SC_R(prm_pActor->_SZ);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
//UINT32 GgafDxUtil::max3(UINT32 a, UINT32 b, UINT32 c) {
//  if (a > b) {
//      if (a > c) {
//          return a;
//      } else {
//          return c;
//      }
//  } else {
//      if (b > c) {
//          return b;
//      } else {
//          return c;
//      }
//  }
//}

