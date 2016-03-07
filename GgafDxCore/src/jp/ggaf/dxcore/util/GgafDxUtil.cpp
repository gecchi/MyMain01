#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

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
//angRx rot_x rx Rx rx radRx �E�E�E X����]�Ɋ֘A���Ă���ϐ���
//angRy rot_y ry Ry ry radRy �E�E�E Y����]�Ɋ֘A���Ă���ϐ���
//angRz rot_z rx Rz rz radRz �E�E�E Z����]�Ɋ֘A���Ă���ϐ���
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
//�Ƃ����ꍇ�� rotxy �Ƃ����ϐ��ɂ��Ă��܂��B
//�܂� rotxy = angXY or angRz
//angXY -> angRz �͊p�x0���̈ʒu(�����x�N�g��(x,y,z)=(1,0,0))�A���̉�]��������v����̂ł킩��₷���ł��B

//�u�߂��v
//angXZ -> angRy �̓ǂݑւ��͐��̉�]������ angXZ �� angRy �ŋt�ɂȂ��Ă��܂��܂��B
//angZX -> angRy �̏ꍇ�͐��̉�]�����͈�v���܂����A�p�x0���̈ʒu��(x,y,z)=(1,0,0) �ł͂Ȃ��Ȃ��Ă��܂����߁A�L�����̎���]�ɂ͌����܂���
//
//������
//rot_xZ = angXZ or angRy_rev
//�̂悤�� "rev" �u�t����ł���v�Ə����悤�ɂ����B�p�x0���̈ʒu��D�悵�����ʁA����Ȃ�₱�������ƂɂȂ��Ă���I



bool GgafDxUtil::_was_GgafDxUtil_inited_flg = false;

//float GgafDxUtil::PARABORA[D360SANG+1];
float GgafDxUtil::COS[D360SANG+1];
float GgafDxUtil::SIN[D360SANG+1];
float GgafDxUtil::RAD[D360SANG+1];

angle GgafDxUtil::SLANT2ANG[100000 + 1];

//����Ȃ񂢂�̂ł́I
//angle GgafDxUtil::PROJANG_XY_ZX_YZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];


angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_y_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_x_REV[D90SANG+1][D90SANG+1];
angle GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_y[D90SANG+1][D90SANG+1];

GgafDxSphereRadiusVectors GgafDxUtil::_srv = GgafDxSphereRadiusVectors();
GgafDxCamera* GgafDxUtil::_pCam = nullptr; //GgafDxSpacetime::GgafDxSpacetime() �Őݒ肳���

void GgafDxUtil::init() {
    if (GgafDxUtil::_was_GgafDxUtil_inited_flg) {
        return;
    }

    for (s_ang ang = 0; ang < D360SANG+1; ang++) {
        double rad = (PI * 2.0 * ang) / D360SANG;

        COS[ang] = (float)(cos(rad));
        SIN[ang] = (float)(sin(rad));
        RAD[ang] = (float)rad;
        //PARABORA[ang] = (float)((double)((ang-(D360SANG/2))*(ang-(D360SANG/2))) /  (double)(-1.0*(D360SANG/2)*(D360SANG/2)) + 1.0);
        ////PARABORA[0] = 0 , PARABORA[D180SANG] = 1,  PARABORA[D360SANG-1] = 0 �� y = -x^2  �������̒l���Ƃ�
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
    Sleep(1);
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
        if (ZEROf_EQ(vx)) {
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
    Sleep(1);
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
            //convVectorToRzRy((float)nvx,(float)nvy,(float)nvz,rz,ry,30);
            //�P�ʃx�N�g������RxRy�����߂�
            _srv.getFaceAngClosely(
                    (uint32_t)(nvx*1000000),
                    (uint32_t)(nvy*1000000),
                    (uint32_t)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );
            PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz] = rz*SANG_RATE;
            PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz] = ry_rev*SANG_RATE;
            //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz]<<")");

        }
    }
    Sleep(1);
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
            //convVectorToRzRy((float)nvx,(float)nvy,(float)nvz,rz,ry,30);
            //�P�ʃx�N�g������RxRy�����߂�
            _srv.getFaceAngClosely(
                    (uint32_t)(nvx*1000000),
                    (uint32_t)(nvy*1000000),
                    (uint32_t)(nvz*1000000),
                    rz,
                    ry_rev,
                    9999
            );

            //(0,0,1.0)��0���Ƃ�X���̐��̕��������Ď��v���𐳂̊p(rx_rev)���l����
            //����͏�ŋ��߂�rz�Ɠ������Ȃ�B
            int rx_rev = rz;
            //(0,0,1.0)��0���Ƃ�Y���̐��̕��������Ĕ����v���𐳂̊p(ry)���l����
            //����͏�ŋ��߂�ry_rev��D90ANG����������l�ł���B
            PROJANG_ZY_ZX_TO_ROTANG_x_REV[prj_ang_zy][prj_ang_zx] = rx_rev*SANG_RATE;
            PROJANG_ZY_ZX_TO_ROTANG_y[prj_ang_zy][prj_ang_zx] = D90ANG - ry_rev*SANG_RATE;
            //_TRACE_("PROJANG_ZY_ZX_TO_ROTANG_y["<<prj_ang_zy<<"]["<<prj_ang_zx<<"] = D90ANG - "<<ry_rev<<"*SANG_RATE = "<<PROJANG_ZY_ZX_TO_ROTANG_y[prj_ang_zy][prj_ang_zx]);
            //_TRACE_("["<<prj_ang_xy<<"]["<<prj_ang_xz<<"]=("<<PROJANG_XY_XZ_TO_ROTANG_z[prj_ang_xy][prj_ang_xz]<<","<<PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_ang_xy][prj_ang_xz]<<")");
        }
    }


    GgafDxUtil::_was_GgafDxUtil_inited_flg = true;
}



void GgafDxUtil::getWayAngle2D(int prm_vx_Center,
                               int prm_vy_Center,
                               int prm_nWay,
                               angle prm_angClearance,
                               angle* out_paAngle) {
    return getWayAngle2D(getAngle2D(prm_vx_Center, prm_vy_Center), prm_nWay, prm_angClearance, out_paAngle);
}

void GgafDxUtil::getWayAngle2D(angle prm_angCenter, int prm_nWay, angle prm_angClearance, angle* out_paAngle) {
    int angstart = GgafDxUtil::addAng(prm_angCenter, ((prm_nWay - 1) * prm_angClearance) / -2);

    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = GgafDxUtil::addAng(angstart, prm_angClearance * i);
    }
}

void GgafDxUtil::getRadialAngle2D(angle prm_angStart, int prm_nWay, angle* out_paAngle) {
    for (int i = 0; i < prm_nWay; i++) {
        out_paAngle[i] = GgafDxUtil::addAng(prm_angStart, (angle)(1.0 * D360ANG / prm_nWay * i));
    }
}

void GgafDxUtil::convRzRyToRyRz(angle prm_Rz, angle prm_Ry, angle& out_Ry, angle& out_Rz) {
    float vx,vy,vz;
    GgafDxUtil::convRzRyToVector(prm_Rz, prm_Ry , vx, vy, vz);
    GgafDxUtil::convVectorToRzRy(vx, vz, -1.0f*vy, out_Ry, out_Rz ); //-�X�O�xX����]RzRy����ւ�
    out_Rz = D360ANG-out_Rz; //Y����Z���l���邽�߁A�������ς�遁�t��]��360�������
}



//void GgafDxUtil::getWayAngle_LinedRzLongitude(angle prm_angCenterRz, angle prm_angCenterRy,
//                                              int prm_nWay, angle prm_angClearance,
//                                              angle* out_paAngleRz, angle* out_paAngleRy) {
//    float vx,vy,vz;
//    convRzRyToVector(prm_angCenterRz, prm_angCenterRy, vx, vy, vz);
//    float vx2,vy2,vz2;
//    //X���X�O�x��]
//    vx2 = vx;
//    vy2 = -vz;
//    vz2 = vy;
//
//    getWayAngle2D(prm_angCenterRz, prm_nWay, prm_angClearance, out_paAngleRz);
//
//}

//void GgafDxUtil::getMoveRzRyWayShot3D_XZ(int prm_nWay, angle prm_angClearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                          angle& out_angFaceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    convVectorToRzRy(prm_tx, prm_ty, prm_tz, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_nWay - 1) * prm_angClearance) / -2);
//    for (int i = 0; i < prm_nWay; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_angClearance * i);
//    }
//}

angle GgafDxUtil::addAng(angle prm_angNow, angle prm_angOffset) {
    angle angAdd = prm_angNow + prm_angOffset;
    while (angAdd >= D360ANG) {
        angAdd -= D360ANG;
    }
    while (angAdd < 0) {
        angAdd += D360ANG;
    }
    return angAdd;
}

angle GgafDxUtil::getAngDiff(angle prm_ang_from, angle prm_ang_to, int prm_way) {
    const angle ang_from = UTIL::simplifyAng(prm_ang_from);
    const angle ang_to = UTIL::simplifyAng(prm_ang_to);
    if (prm_way == TURN_CLOSE_TO) {
        if (0 <= ang_from && ang_from < D180ANG) {
            if (0 <= ang_to && ang_to < ang_from) {
                return -1 * (ang_from - ang_to);
            } else if (ang_to == ang_from) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (ang_from < ang_to && ang_to < ang_from + D180ANG) {
                return ang_to - ang_from;
            } else if (ang_to == ang_from + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (ang_from + D180ANG < ang_to && ang_to <= D360ANG) {
                return -1 * (ang_from + (D360ANG - ang_to));
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
                throwGgafCriticalException("�A���O���l���͈͊O�ł�(1)�B\n"<<
                                           "ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= ang_from && ang_from <= D360ANG) {
            if (0 <= ang_to && ang_to < ang_from - D180ANG) {
                return D360ANG - ang_from + ang_to;
            } else if (ang_to == ang_from - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (ang_from - D180ANG < ang_to && ang_to < ang_from) {
                return -1 * (ang_from - ang_to);
            } else if (ang_from == ang_to) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (ang_from < ang_to && ang_to <= D360ANG) {
                return ang_to - ang_from;
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
                throwGgafCriticalException("�A���O���l���͈͊O�ł�(2)�B\n"<<
                                           "ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) {
        if (0 <= ang_from && ang_from < D180ANG) {
            if (0 <= ang_to && ang_to < ang_from) {
                return (D360ANG - ang_from) + ang_to;
            } else if (ang_to == ang_from) {
                //�d�Ȃ��Ă�ꍇ
                return -1 * D360ANG;
            } else if (ang_from < ang_to && ang_to < ang_from + D180ANG) {
                return -1 * (ang_from + (D360ANG - ang_to));
            } else if (ang_to == ang_from + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return -1 * D180ANG;
            } else if (ang_from + D180ANG < ang_to && ang_to <= D360ANG) {
                return ang_to - ang_from;
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
                throwGgafCriticalException("�A���O���l���͈͊O�ł�(3)�B\n"<<
                                           "ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= ang_from && ang_from <= D360ANG) {
            if (0 <= ang_to && ang_to < ang_from - D180ANG) {
                return -1 * (ang_from - ang_to);
            } else if (ang_to == ang_from - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return -1 * D180ANG;
            } else if (ang_from - D180ANG < ang_to && ang_to < ang_from) {
                return (D360ANG - ang_from) + ang_to;
            } else if (ang_from == ang_to) {
                //�d�Ȃ��Ă�ꍇ
                return -1 * D360ANG;
            } else if (ang_from < ang_to && ang_to <= D360ANG) {
                return -1 * (ang_from + (D360ANG - ang_to));
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
                throwGgafCriticalException("�A���O���l���͈͊O�ł�(4)�B\n"<<
                                           "ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (ang_from <= ang_to) {
            return ang_to - ang_from;
        } else {
            return (D360ANG - ang_from) + ang_to;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (ang_from >= ang_to) {
            return -(ang_from - ang_to);
        } else {
            return -(ang_from + (D360ANG - ang_to));
        }
    } else {
        _TRACE_(FUNC_NAME<<" bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
        throwGgafCriticalException("prm_way = TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE �ȊO���w�肳��Ă��܂��B");
    }

    _TRACE_("bad ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
    throwGgafCriticalException("���̂�����p�̋��������߂�܂���B(1) \n"<<
                               "ang_from=" << ang_from << "/ang_to=" << ang_to<<"/prm_way="<<prm_way);
}

void GgafDxUtil::rotxy(int prm_x, int prm_y, angle prm_ang, int& out_x, int& out_y) {
    out_x = (int)(floor((prm_x * GgafDxUtil::COS[prm_ang/SANG_RATE]) - (prm_y * GgafDxUtil::SIN[prm_ang/SANG_RATE])));
    out_y = (int)(floor((prm_x * GgafDxUtil::SIN[prm_ang/SANG_RATE]) + (prm_y * GgafDxUtil::COS[prm_ang/SANG_RATE])));
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

coord GgafDxUtil::getDistance(coord x1, coord y1, coord x2, coord y2) {
    return (coord)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}
//int GgafDxUtil::getDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
//    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))) + (((double)(z2 - z1)) * ((double)(z2 - z1))));
//}


void GgafDxUtil::convVectorToRzRy(coord vx,
                                  coord vy,
                                  coord vz,
                                  angle& out_angRz,
                                  angle& out_angRy ) {
    if (vz == 0) {
        out_angRz = GgafDxUtil::getAngle2D(vx, vy);
        out_angRy = 0;
        return;
    }

    //���ꂩ�̗v�f��0�̏ꍇ�AgetAngle2D�̌��ʂ��傫������Ă��܂��B
    //�Ƃ肠�����P��ݒ肵�ċߎ������Ă������B
    //TODO:0 �����Ă����v�ɂ���B
    vx = (vx == 0 ? 1 : vx);
    vy = (vy == 0 ? 1 : vy);
    vz = (vz == 0 ? 1 : vz);

    const angle prj_rXY = GgafDxUtil::getAngle2D(ABS(vx), ABS(vy)); //Rz
    const angle prj_rXZ = GgafDxUtil::getAngle2D(ABS(vx), ABS(vz));
    const angle prj_rZY = GgafDxUtil::getAngle2D(ABS(vz), ABS(vy)); //Rz
    const angle prj_rZX = GgafDxUtil::getAngle2D(ABS(vz), ABS(vx));

    angle rot_z, rot_y_rev;
    if (0 <= prj_rXZ && prj_rXZ <= D45ANG) {
        rot_z = GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_z[(int)(prj_rXY*0.01)][(int)(prj_rXZ*0.01)];
        rot_y_rev = GgafDxUtil::PROJANG_XY_XZ_TO_ROTANG_y_REV[(int)(prj_rXY*0.01)][(int)(prj_rXZ*0.01)];
    } else if (D45ANG <= prj_rXZ && prj_rXZ <= D90ANG) {
        rot_z = GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_x_REV[(int)(prj_rZY*0.01)][(int)(prj_rZX*0.01)];
        rot_y_rev = D90ANG - GgafDxUtil::PROJANG_ZY_ZX_TO_ROTANG_y[(int)(prj_rZY*0.01)][(int)(prj_rZX*0.01)];
    } else {
        throwGgafCriticalException("�͈͂��j�]���Ă܂��Bprj_rXZ="<<prj_rXZ<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
#if MY_DEBUG
    if (0 <= prj_rXY && prj_rXY < D45ANG) {
        //OK
    } else if (D45ANG <= prj_rXY && prj_rXY <= D90ANG) {
        //OK
    } else {
        throwGgafCriticalException("�͈͂��j�]���Ă܂��Bprj_rXY="<<prj_rXY<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
#endif
    //�ی��ɂ���ĉ�]�p��␳
    if (vx >= 0) {
        if (vy >= 0) {
            if (vz >= 0) {
                //���ی�
                out_angRz = rot_z;
                out_angRy = (D360ANG - rot_y_rev);
            } else { //vz < 0
                //��܏ی�
                out_angRz = rot_z;
                out_angRy = rot_y_rev;
            }
        } else { //vy < 0
            if (vz >= 0) {
                //��l�ی�
                out_angRz = (D360ANG - rot_z);
                out_angRy = (D360ANG - rot_y_rev);
            } else { //vz < 0
                //�攪�ی�
                out_angRz = (D360ANG - rot_z);
                out_angRy = rot_y_rev;
            }
        }
    } else { //vx < 0
        if (vy >= 0) {
            if (vz >= 0) {
                //���ی�
                out_angRz = rot_z;
                out_angRy = (D180ANG + rot_y_rev);
            } else { //vz < 0
                //��Z�ی�
                out_angRz = rot_z;
                out_angRy = (D180ANG - rot_y_rev);
            }
        } else { //vy < 0
            if (vz >= 0) {
                //��O�ی�
                out_angRz = (D360ANG - rot_z);
                out_angRy = (D180ANG + rot_y_rev);
            } else { //vz < 0
                //�掵�ی�
                out_angRz = (D360ANG - rot_z);
                out_angRy = (D180ANG - rot_y_rev);
            }
        }
    }

#if MY_DEBUG
    if (D360ANG < out_angRz || 0 > out_angRz || D360ANG < out_angRy || 0 > out_angRy) {
        throwGgafCriticalException("�͈͊O�ł��v�����B\n out_angRz,out_angRy="<<out_angRz<<","<<out_angRy<<" vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
#endif
//    out_angRz = simplifyAng(out_angRz);
//    out_angRy = simplifyAng(out_angRy);
}


void GgafDxUtil::convVectorToRzRy(coord vx,
                                  coord vy,
                                  coord vz,
                                  float& out_nvx,
                                  float& out_nvy,
                                  float& out_nvz,
                                  angle& out_angRz,
                                  angle& out_angRy) {

    GgafDxUtil::convVectorToRzRy(vx, vy, vz,
                                 out_angRz, out_angRy );

    GgafDxUtil::convRzRyToVector(out_angRz, out_angRy,
                                 out_nvx, out_nvy, out_nvz);

}


void GgafDxUtil::convRzRyToVector(angle prm_ang_rz,
                                  angle prm_ang_ry,
                                  float& out_nvx,
                                  float& out_nvy,
                                  float& out_nvz) {
    //void GgafDxSphereRadiusVectors::getVectorClosely(int out_angFaceY, int prm_angZ, uint16_t& out_x, uint16_t& out_y, uint16_t& out_z) {
    //��]�p�ɂ���ďی����l�����AgetVectorClosely�̃p�����[�^�p(< 900)���o��
    int xsign, ysign, zsign;
    s_ang rz, ry_rev;

    if (0 <= prm_ang_rz && prm_ang_rz < D90ANG) {
        rz = (prm_ang_rz - D0ANG) * (1.0 / SANG_RATE);
        if (0 <= prm_ang_ry && prm_ang_ry < D90ANG) { //��܏ی�
            ry_rev = prm_ang_ry * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (D90ANG <= prm_ang_ry && prm_ang_ry < D180ANG) { //��Z�ی�
            ry_rev = (D180ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else if (D180ANG <= prm_ang_ry && prm_ang_ry < D270ANG) { //���ی�
            ry_rev = (prm_ang_ry - D180ANG) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (D270ANG <= prm_ang_ry && prm_ang_ry <= D360ANG) { //���ی�
            ry_rev = (D360ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(1) prm_ang_rz="<<prm_ang_rz<<" prm_ang_ry="<<prm_ang_ry);
        }
    } else if (D90ANG <= prm_ang_rz && prm_ang_rz < D180ANG) {
        rz = (D180ANG - prm_ang_rz) * (1.0 / SANG_RATE);

        if (0 <= prm_ang_ry && prm_ang_ry < D90ANG) { //���ی�
            ry_rev = prm_ang_ry * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (D90ANG <= prm_ang_ry && prm_ang_ry < D180ANG) { //���ی�
            ry_rev = (D180ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else if (D180ANG <= prm_ang_ry && prm_ang_ry < D270ANG) { //��܏ی�
            ry_rev = (prm_ang_ry - D180ANG) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (D270ANG <= prm_ang_ry && prm_ang_ry <= D360ANG) { //��Z�ی�
            ry_rev = (D360ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(2) prm_ang_rz="<<prm_ang_rz<<" prm_ang_ry="<<prm_ang_ry);
        }

    } else if (D180ANG <= prm_ang_rz && prm_ang_rz < D270ANG) {
        rz = (prm_ang_rz - D180ANG) * (1.0 / SANG_RATE);
        if (0 <= prm_ang_ry && prm_ang_ry < D90ANG) { //��O�ی�
            ry_rev = prm_ang_ry * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (D90ANG <= prm_ang_ry && prm_ang_ry < D180ANG) { //��l�ی�
            ry_rev = (D180ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else if (D180ANG <= prm_ang_ry && prm_ang_ry < D270ANG) { //�攪�ی�
            ry_rev = (prm_ang_ry - D180ANG) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (D270ANG <= prm_ang_ry && prm_ang_ry <= D360ANG) { //�掵�ی�
            ry_rev = (D360ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else {
            throwGgafCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(3) prm_ang_rz="<<prm_ang_rz<<" prm_ang_ry="<<prm_ang_ry);
        }
    } else if (D270ANG <= prm_ang_rz && prm_ang_rz <= D360ANG) {
        rz = (D360ANG - prm_ang_rz) * (1.0 / SANG_RATE);
        if (0 <= prm_ang_ry && prm_ang_ry < D90ANG) { //�攪�ی�
            ry_rev = prm_ang_ry * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (D90ANG <= prm_ang_ry && prm_ang_ry < D180ANG) { //�掵�ی�
            ry_rev = (D180ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else if (D180ANG <= prm_ang_ry && prm_ang_ry < D270ANG) { //��O�ی�
            ry_rev = (prm_ang_ry - D180ANG) * (1.0 / SANG_RATE);
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (D270ANG <= prm_ang_ry && prm_ang_ry <= D360ANG) { //��l�ی�
            ry_rev = (D360ANG - prm_ang_ry) * (1.0 / SANG_RATE);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else {
            throwGgafCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(4) prm_ang_rz="<<prm_ang_rz<<" prm_ang_ry="<<prm_ang_ry);
        }
    } else {
        throwGgafCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(5) prm_ang_rz="<<prm_ang_rz<<" prm_ang_ry="<<prm_ang_ry);
    }
    uint32_t vx, vy, vz;
    GgafDxUtil::_srv.getVectorClosely(ry_rev, rz, vx, vy, vz);
    out_nvx = xsign * (int)vx * (1.0 / 1000000.0);
    out_nvy = ysign * (int)vy * (1.0 / 1000000.0);
    out_nvz = zsign * (int)vz * (1.0 / 1000000.0);
}

void GgafDxUtil::getPlaneNomalVec(float p1x, float p1y, float p1z,
                                  float p2x, float p2y, float p2z,
                                  float p3x, float p3y, float p3z,
                                  float& out_nvx, float& out_nvy, float& out_nvz, float& out_d) {
    //�ʂ̒��_�R��
    D3DXVECTOR3 v1 = D3DXVECTOR3(p1x, p1y, p1z);
    D3DXVECTOR3 v2 = D3DXVECTOR3(p2x, p2y, p2z);
    D3DXVECTOR3 v3 = D3DXVECTOR3(p3x, p3y, p3z);
    D3DXPLANE plane;
    // 3 �̓_���畽�ʂ��쐬
    D3DXPlaneFromPoints(&plane, &v1, &v2, &v3);
    //���K����������(�@��)���Z�o
    D3DXPlaneNormalize(&plane, &plane);
    //a x + b y + c z + d w = 0 �ƂȂ�悤�ɓK�p�����B
    out_nvx = plane.a;
    out_nvy = plane.b;
    out_nvz = plane.c;
    out_d = plane.d;
}

void GgafDxUtil::setWorldMatrix_ScRxRzRyMv(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx * cosRz *cosRy;
    out_matWorld._12 = sx * sinRz;
    out_matWorld._13 = sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (sy * cosRx * -sinRz *  cosRy) + (sy * sinRx * sinRy);
    out_matWorld._22 =  sy * cosRx *  cosRz;
    out_matWorld._23 = (sy * cosRx * -sinRz * -sinRy) + (sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (sz * -sinRx * -sinRz *  cosRy) + (sz * cosRx * sinRy);
    out_matWorld._32 =  sz * -sinRx *  cosRz;
    out_matWorld._33 = (sz * -sinRx * -sinRz * -sinRy) + (sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
    /*
     //�O�̂���
     D3DXMATRIX matrixRotX, matrixRotY, matrixRotZ, matrixTrans;
     D3DXMatrixRotationY(&matrixRotX, GgafDxUtil::RAD_UNITLEN[s_rx]/LEN_UNIT);
     D3DXMatrixRotationX(&matrixRotY, GgafDxUtil::RAD_UNITLEN[s_ry]/LEN_UNIT);
     D3DXMatrixRotationZ(&matrixRotZ, GgafDxUtil::RAD_UNITLEN[s_rz]/LEN_UNIT);
     D3DXMatrixTranslation(&matrixTrans, _x/LEN_UNIT, _y/LEN_UNIT, _z/LEN_UNIT);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void GgafDxUtil::setWorldMatrix_RzRy(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);

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
    const float sinRy = ANG_SIN(prm_Ry);
    const float cosRy = ANG_COS(prm_Ry);
    const float sinRz = ANG_SIN(prm_Rz);
    const float cosRz = ANG_COS(prm_Rz);

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

void GgafDxUtil::setWorldMatrix_RxRzRy(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);

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

void GgafDxUtil::setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    const float sinRx = ANG_SIN(prm_rx);
    const float cosRx = ANG_COS(prm_rx);
    const float sinRy = ANG_SIN(prm_ry);
    const float cosRy = ANG_COS(prm_ry);
    const float sinRz = ANG_SIN(prm_rz);
    const float cosRz = ANG_COS(prm_rz);

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


void GgafDxUtil::setWorldMatrix_ScRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx*cosRz*cosRy;
    out_matWorld._12 = sx*sinRz;
    out_matWorld._13 = sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*-sinRz*cosRy;
    out_matWorld._22 = sy*cosRz;
    out_matWorld._23 = sy*-sinRz*-sinRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*sinRy;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDxUtil::mulWorldMatrix_RzRyScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*sx  sinRz*sy   cosRz*-sinRy*sz   0 |
    //    | -sinRz*cosRy*sx  cosRz*sy  -sinRz*-sinRy*sz   0 |
    //    |  sinRy*sx        0          cosRy*sz          0 |
    //    |  dx              dy         dz                1 |
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz*cosRy*sx;
    out_matWorld._12 = sinRz*sy;
    out_matWorld._13 = cosRz*-sinRy*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*cosRy*sx;
    out_matWorld._22 = cosRz*sy;
    out_matWorld._23 = -sinRz*-sinRy*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sinRy*sx;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = cosRy*sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_RxRzRyScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy*sx,          sinRz*sy,                         cosRz*-sinRy*sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*sx,    cosRx*cosRz*sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*sx,   -sinRx*cosRz*sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz * cosRy * sx;
    out_matWorld._12 = sinRz * sy;
    out_matWorld._13 = cosRz * -sinRy * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((cosRx * -sinRz * cosRy) + (sinRx * sinRy)) * sx;
    out_matWorld._22 = cosRx * cosRz * sy;
    out_matWorld._23 = ((cosRx * -sinRz * -sinRy) + (sinRx * cosRy)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((-sinRx * -sinRz * cosRy) + (cosRx * sinRy)) * sx;
    out_matWorld._32 = -sinRx * cosRz * sy;
    out_matWorld._33 = ((-sinRx * -sinRz * -sinRy) + (cosRx * cosRy)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RxRyRzScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬
    //    |                           cosRy*cosRz*sx,                        cosRy*sinRz*sy  ,      -sinRy*sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*sy), sinRx*cosRy*sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*sy), cosRx*cosRy*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRy*cosRz*sx;
    out_matWorld._12 = cosRy*sinRz*sy;
    out_matWorld._13 = -sinRy*sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = ((sinRx*sinRy*cosRz) + (cosRx*-sinRz))*sx;
    out_matWorld._22 = ((sinRx*sinRy*sinRz) + (cosRx*cosRz))*sy;
    out_matWorld._23 = sinRx*cosRy*sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = ((cosRx*sinRy*cosRz) + (-sinRx*-sinRz))*sx;
    out_matWorld._32 = ((cosRx*sinRy*sinRz) + (-sinRx* cosRz))*sy;
    out_matWorld._33 = cosRx*cosRy*sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RxRzRxScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ��@�̕ϊ��s����쐬.
    //��Y����]������܂���BRY�͂Q��ڂ�X����]�ƂȂ�
    //|         cosRz*sx,                          sinRz*cosRy*sy ,                          sinRz*sinRy*sz, 0 |
    //|  cosRx*-sinRz*sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*sz), 0 |
    //| -sinRx*-sinRz*sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = cosRz * sx;
    out_matWorld._12 = sinRz * cosRy * sy;
    out_matWorld._13 = sinRz * sinRy * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = cosRx * -sinRz * sx;
    out_matWorld._22 = (( cosRx * cosRz * cosRy) + (sinRx * -sinRy)) * sy;
    out_matWorld._23 = (( cosRx * cosRz * sinRy) + (sinRx *  cosRy)) * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = -sinRx * -sinRz * sx;
    out_matWorld._32 = ((-sinRx * cosRz * cosRy) + (cosRx * -sinRy)) * sy;
    out_matWorld._33 = ((-sinRx * cosRz * sinRy) + (cosRx *  cosRy)) * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::setWorldMatrix_RzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
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


void GgafDxUtil::setWorldMatrix_ScRzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ��@�̕ϊ��s����쐬
    // |sx*cosZ , sx*sinZ , 0    , 0  |
    // |sy*-sinZ, sy*cosZ , 0    , 0  |
    // |0       , 0       , sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx * cosRz;
    out_matWorld._12 = sx * sinRz;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy * -sinRz;
    out_matWorld._22 = sy * cosRz;
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_ScMvRxRzRy(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);
    const dxcoord dx = prm_pActor->_fX;
    const dxcoord dy = prm_pActor->_fY;
    const dxcoord dz = prm_pActor->_fZ;

    out_matWorld._11 = sx*cosRz*cosRy;
    out_matWorld._12 = sx*sinRz;
    out_matWorld._13 = sx*cosRz*-sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*cosRx*-sinRz*cosRy + sy*sinRx*sinRy;
    out_matWorld._22 = sy*cosRx*cosRz;
    out_matWorld._23 = sy*cosRx*-sinRz*-sinRy + sy*sinRx*cosRy;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy;
    out_matWorld._32 = sz*-sinRx*cosRz;
    out_matWorld._33 = sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*cosRy + ((dy*sinRx + dz*cosRx))*sinRy;
    out_matWorld._42 = (dx*sinRz + (dy*cosRx + dz*-sinRx)*cosRz);
    out_matWorld._43 = (dx*cosRz + (dy*cosRx + dz*-sinRx)*-sinRz)*-sinRy + ((dy*sinRx + dz*cosRx))*cosRy;
    out_matWorld._44 = 1.0f;

}

void GgafDxUtil::updateWorldMatrix_Mv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_BxyzScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = _pCam->_matView._11 * sx;
    out_matWorld._12 = _pCam->_matView._21 * sy;
    out_matWorld._13 = _pCam->_matView._31 * sz;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = _pCam->_matView._12 * sx;
    out_matWorld._22 = _pCam->_matView._22 * sy;
    out_matWorld._23 = _pCam->_matView._32 * sz;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = _pCam->_matView._13 * sx;
    out_matWorld._32 = _pCam->_matView._23 * sy;
    out_matWorld._33 = _pCam->_matView._33 * sz;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void GgafDxUtil::setWorldMatrix_BxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {

    out_matWorld._11 = _pCam->_matView._11;
    out_matWorld._12 = _pCam->_matView._21;
    out_matWorld._13 = _pCam->_matView._31;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = _pCam->_matView._12;
    out_matWorld._22 = _pCam->_matView._22;
    out_matWorld._23 = _pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = _pCam->_matView._13;
    out_matWorld._32 = _pCam->_matView._23;
    out_matWorld._33 = _pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}



void GgafDxUtil::setWorldMatrix_ScRzBxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx*cosRz*_pCam->_matView._11 + sx*sinRz*_pCam->_matView._12;
    out_matWorld._12 = sx*cosRz*_pCam->_matView._21 + sx*sinRz*_pCam->_matView._22;
    out_matWorld._13 = sx*cosRz*_pCam->_matView._31 + sx*sinRz*_pCam->_matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = sy*-sinRz*_pCam->_matView._11 + sy*cosRz*_pCam->_matView._12;
    out_matWorld._22 = sy*-sinRz*_pCam->_matView._21 + sy*cosRz*_pCam->_matView._22;
    out_matWorld._23 = sy*-sinRz*_pCam->_matView._31 + sy*cosRz*_pCam->_matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = sz*_pCam->_matView._13;
    out_matWorld._32 = sz*_pCam->_matView._32;
    out_matWorld._33 = sz*_pCam->_matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}


void GgafDxUtil::mulWorldMatrix_ScRxRzRyMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    const float sinRx = ANG_SIN(prm_pActor->_rx);
    const float cosRx = ANG_COS(prm_pActor->_rx);
    const float sinRy = ANG_SIN(prm_pActor->_ry);
    const float cosRy = ANG_COS(prm_pActor->_ry);
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);
    const float sx = SC_R(prm_pActor->_sx);
    const float sy = SC_R(prm_pActor->_sy);
    const float sz = SC_R(prm_pActor->_sz);
    const D3DXMATRIX matScRxRzRyMv(
            sx * cosRz *cosRy,
            sx * sinRz,
            sx * cosRz * -sinRy,
            0.0f,

            (sy * cosRx * -sinRz *  cosRy) + (sy * sinRx * sinRy),
            sy * cosRx *  cosRz,
            (sy * cosRx * -sinRz * -sinRy) + (sy * sinRx * cosRy),
            0.0f,

            (sz * -sinRx * -sinRz *  cosRy) + (sz * cosRx * sinRy),
            sz * -sinRx *  cosRz,
            (sz * -sinRx * -sinRz * -sinRy) + (sz * cosRx * cosRy),
            0.0f,

            prm_pActor->_fX,
            prm_pActor->_fY,
            prm_pActor->_fZ,
            1.0f
        );
    D3DXMatrixMultiply(&inout_matWorld, &inout_matWorld, &matScRxRzRyMv);
}



void GgafDxUtil::setWorldMatrix_RzBxyzMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const D3DXMATRIX& matView = _pCam->_matView;
    const float sinRz = ANG_SIN(prm_pActor->_rz);
    const float cosRz = ANG_COS(prm_pActor->_rz);

    out_matWorld._11 = cosRz*matView._11 + sinRz*matView._12;
    out_matWorld._12 = cosRz*matView._21 + sinRz*matView._22;
    out_matWorld._13 = cosRz*matView._31 + sinRz*matView._32;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = -sinRz*matView._11 + cosRz*matView._12;
    out_matWorld._22 = -sinRz*matView._21 + cosRz*matView._22;
    out_matWorld._23 = -sinRz*matView._31 + cosRz*matView._32;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = matView._13;
    out_matWorld._32 = matView._32;
    out_matWorld._33 = matView._33;
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
void GgafDxUtil::setWorldMatrix_ScMv(const GgafDxGeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._11 = SC_R(prm_pActor->_sx);
    out_matWorld._12 = 0.0f;
    out_matWorld._13 = 0.0f;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = 0.0f;
    out_matWorld._22 = SC_R(prm_pActor->_sy);
    out_matWorld._23 = 0.0f;
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = 0.0f;
    out_matWorld._32 = 0.0f;
    out_matWorld._33 = SC_R(prm_pActor->_sz);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

