#include "jp/ggaf/dx/util/Util.h"

#include "jp/ggaf/dx/exception/CriticalException.h"


using namespace GgafDx;

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
//ry rot_y ry Ry ry radRy �E�E�E Y����]�Ɋ֘A���Ă���ϐ���
//rz rot_z rx Rz rz radRz �E�E�E Z����]�Ɋ֘A���Ă���ϐ���
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
//angXY �� �R������Ԃ� Z=0 ��XY���ʏ�Ɍ���Arz �Ƃ݂Ȃ����Ƃ��o���܂��B
//���̂悤�ɂ��Čv�Z���s���Ă���ӏ�������A
//�u���ʂ̒��S�p�A�܂��͒����̐����p�x �Ƃ��Ēl�����߂����ǂ��A����]�Ƃ��ēǂݑւ����A�����́A�g�����������v
//�Ƃ����ꍇ�� rotxy �Ƃ����ϐ��ɂ��Ă��܂��B
//�܂� rotxy = angXY or rz
//angXY -> rz �͊p�x0���̈ʒu(�����x�N�g��(x,y,z)=(1,0,0))�A���̉�]��������v����̂ł킩��₷���ł��B

//�u�߂��v
//angXZ -> ry �̓ǂݑւ��͐��̉�]������ angXZ �� ry �ŋt�ɂȂ��Ă��܂��܂��B
//angZX -> ry �̏ꍇ�͐��̉�]�����͈�v���܂����A�p�x0���̈ʒu��(x,y,z)=(1,0,0) �ł͂Ȃ��Ȃ��Ă��܂����߁A�L�����̎���]�ɂ͌����܂���
//
//������
//rot_xZ = angXZ or ry_rev
//�̂悤�� "rev" �u�t����ł���v�Ə����悤�ɂ����B�p�x0���̈ʒu��D�悵�����ʁA����Ȃ�₱�������ƂɂȂ��Ă���I



bool Util::_was_GgafDx_Util_inited_flg = false;

//float Util::PARABORA[D360SANG+1];
double Util::COS[36000+1];
double Util::SIN[36000+1];
double Util::RAD[36000+1];

angle Util::SLANT2ANG[100000 + 1];

//����Ȃ񂢂�̂ł́I
//angle Util::PROJANG_XY_ZX_YZ_TO_ROTANG_z[D90SANG+1][D90SANG+1];


angle Util::PROJANG_XY_XZ_TO_ROTANG_z[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
angle Util::PROJANG_XY_XZ_TO_ROTANG_y_REV[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
angle Util::PROJANG_ZY_ZX_TO_ROTANG_x_REV[D90SANG*SR_AC+1][D90SANG*SR_AC+1];
angle Util::PROJANG_ZY_ZX_TO_ROTANG_y[D90SANG*SR_AC+1][D90SANG*SR_AC+1];

double Util::RND_CIRCLE_X[10000];
double Util::RND_CIRCLE_Y[10000];
double Util::RND_SPHERE_X[10000];
double Util::RND_SPHERE_Y[10000];
double Util::RND_SPHERE_Z[10000];
SphereRadiusVectors Util::_srv = SphereRadiusVectors();
Camera* Util::_pCam = nullptr; //Spacetime::Spacetime() �Őݒ肳���

void Util::init() {
    if (Util::_was_GgafDx_Util_inited_flg) {
        return;
    }
    // ang���x 0 �` 36000 �ɕύX
    for (s_ang ang = 0; ang < 36000+1; ang++) {
        double rad = (PI2 * ang) / 36000;
        Util::COS[ang] = cos(rad);
        Util::SIN[ang] = sin(rad);
        Util::RAD[ang] = rad;
        //PARABORA[ang] = (float)((double)((ang-(D360SANG/2))*(ang-(D360SANG/2))) /  (double)(-1.0*(D360SANG/2)*(D360SANG/2)) + 1.0);
        ////PARABORA[0] = 0 , PARABORA[D180SANG] = 1,  PARABORA[D360SANG-1] = 0 �� y = -x^2  �������̒l���Ƃ�
    }
    Sleep(100);
    Util::COS[0]     =  1;
    Util::COS[9000]  =  0;
    Util::COS[18000] = -1;
    Util::COS[27000] =  0;
    Util::COS[36000] =  1;
    Util::SIN[0]     =  0;
    Util::SIN[9000]  =  1;
    Util::SIN[18000] =  0;
    Util::SIN[27000] = -1;
    Util::SIN[36000] =  0;
    Sleep(1);
    //<SLANT2ANG>
    {
        double rad;
        double vx,vy,vz;
        double slant;
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
            if (ZEROd_EQ(vx)) {
                slant = 0.0;
            } else {
                slant = vy / vx;
            }
            index_slant = (int)(slant * 100000);
            d_index_slant = index_slant - index_slant_prev;
            for (int i = index_slant_prev+1, d = 1; i <= index_slant; i++, d++) {
                if (i > 100000) {
                    _TRACE_("�y�x���z�z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(ang*10));
                }
                //��������i�������A�o�E�g�̂��Ɓj
                Util::SLANT2ANG[i] = (angle)( ((ang-1) + (1.0*d)/(1.0*d_index_slant))*1.0);
            }
            index_slant_prev = index_slant;
        }
        Sleep(10);
        d_index_slant = 100000 - index_slant_prev;
        for (int i = index_slant_prev+1, d = 1; i <= 100000; i++, d++) {
            if (i > 100000) {
                _TRACE_("�y�x���z�z��͈͈ȏ�̌X���z��INDEX��ݒ�B���������j�󂳂�܂��BSLANT2ANG["<<i<<"]<="<<(450000));
            }
            Util::SLANT2ANG[i] = (angle)( (45000-1) + (1.0*d)/(1.0*d_index_slant) );
        }
        Sleep(10);
    }
//    //<PROJ_ANG2ROT_ANG> �i2009/10/20 �o�܁E�E�E�������邽�߂Ȃ牽�ł�����Ă݂悤�j
//    //��������x�N�g������AXY���ʁAZY���ʂɓ��e�������ɂł��鎲�Ƃ̊p�i���ꂼ��XY�ˉe�p�AZY�ˉe�p�ƌĂԂ��ƂƂ���j�ƁA
//    //���̕����x�N�g���̒P�ʃx�N�g�����w���P�ʋ��̈ܓx�ƌo�x�iZ����]�p�AY����]�p�j��R���邱�Ƃ�ړI�Ƃ���B
//    //�܂�AXY�ˉe�p�AZY�ˉe�p �� Z����]�p�AY����]�p �̓ǂݑւ��������ɍs������
//    //XY�ˉe�p90�x�� * ZY�ˉe�p90�x�� ��z��v�f�A�l��Z����]�p�AY����]�p��l�Ƃ���z����\�z�B
//
    {
//        double vx,vy,vz;
        double vx1 = 1.0;
        double vz2 = 1.0;

        for (s_ang prj_s_ang = 0; prj_s_ang <= D90SANG*SR_AC; prj_s_ang++) {

            double prj_rad_xy = (PI * 2.0 * prj_s_ang) / (1.0*D360SANG*SR_AC);
            double vy1 = tan(prj_rad_xy);

            s_ang prj_s_ang_xy = prj_s_ang;
            for (s_ang prj_s_ang_xz = 0; prj_s_ang_xz <= D90SANG*SR_AC; prj_s_ang_xz++) {
                double prj_rad_xz = (PI * 2.0 * prj_s_ang_xz) / (1.0*D360SANG*SR_AC);
                double vz1 = tan(prj_rad_xz);

                //�����x�N�g�����쐬
                //vx,vy,vz �𐳋K������B
                double t = 1.0 / sqrt(vx1 * vx1 + vy1 * vy1 + vz1 * vz1);
                double nvx = t * vx1;
                double nvy = t * vy1;
                double nvz = t * vz1;
                //�P�ʃx�N�g������RzRy(�t��])�����߂�
                angle rz, ry_rev;
                Util::_srv.getFaceAngClosely(
                        (uint32_t)(nvx*10000000),
                        (uint32_t)(nvy*10000000),
                        (uint32_t)(nvz*10000000),
                        rz,
                        ry_rev
                );
                Util::PROJANG_XY_XZ_TO_ROTANG_z[prj_s_ang_xy][prj_s_ang_xz] = rz;
                Util::PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_s_ang_xy][prj_s_ang_xz] = ry_rev;
            }
//            prj_rad_zy = (PI * 2.0 * prj_ang_zy) / (1.0*D360SANG);
//            vy2 = tan(prj_rad_zy);
            s_ang prj_s_ang_zy = prj_s_ang;
            double vy2 = vy1;
            for (s_ang prj_s_ang_zx = 0; prj_s_ang_zx <= D90SANG*SR_AC; prj_s_ang_zx++) {
                double prj_rad_zx = (PI * 2.0 * prj_s_ang_zx) / (1.0*D360SANG*SR_AC);
                //�����x�N�g�����쐬
                double vx2 = tan(prj_rad_zx);

                double t2 = 1.0 / sqrt(vx2 * vx2 + vy2 * vy2 + vz2 * vz2);
                double nvx2 = t2 * vx2;
                double nvy2 = t2 * vy2;
                double nvz2 = t2 * vz2;
                //�P�ʃx�N�g������RzRy(�t��])�����߂�
                angle rz, ry_rev;
                Util::_srv.getFaceAngClosely(
                        (uint32_t)(nvx2*10000000),
                        (uint32_t)(nvy2*10000000),
                        (uint32_t)(nvz2*10000000),
                        rz,
                        ry_rev
                );

                //(0,0,1.0)��0���Ƃ�X���̐��̕��������Ď��v���𐳂̊p(rx_rev)���l����
                //����͏�ŋ��߂�rz�Ɠ������Ȃ�B
                angle rx_rev = rz;
                //(0,0,1.0)��0���Ƃ�Y���̐��̕��������Ĕ����v���𐳂̊p(ry)���l����
                //����͏�ŋ��߂�ry_rev��D90ANG����������l�ł���B
                Util::PROJANG_ZY_ZX_TO_ROTANG_x_REV[prj_s_ang_zy][prj_s_ang_zx] = rx_rev;
                Util::PROJANG_ZY_ZX_TO_ROTANG_y[prj_s_ang_zy][prj_s_ang_zx] = D90ANG - ry_rev;
            }
        }
    }

    Sleep(10);
    //�~���A�����Ɉ�l�ɕ��z���郉���_���ȓ_�𐶐�
    for (int i = 0; i < 10000; i++) {
        const double r = dRND(0.0, 1.0);
        const double z = dRND(-1.0, 1.0);
        const double phi = dRND(0.0, 2.0*PI);

        const double cos_phi = cos(phi);
        const double sin_phi = sin(phi);
        const double wk1 = sqrt(1 - z * z);
        const double wk2 = GgafCore::Util::_cbrt_(r);
        Util::RND_SPHERE_X[i] = wk2 * wk1 * cos_phi;
        Util::RND_SPHERE_Y[i] = wk2 * wk1 * sin_phi;
        Util::RND_SPHERE_Z[i] = wk2 * z;

        const double wk3 = sqrt(r);
        Util::RND_CIRCLE_X[i] = wk3 * cos_phi;
        Util::RND_CIRCLE_Y[i] = wk3 * sin_phi;
    }
    Util::_was_GgafDx_Util_inited_flg = true;

}

void Util::calcVecToAng(double prm_x,
                        double prm_y,
                        double prm_z,
                        s_ang& out_faceZ,
                        s_ang& out_faceY_rev) {
    double out_x, out_y, out_z;
    Util::getIntersectionSphereAndVec<double>(prm_x, prm_y, prm_z ,out_x, out_y, out_z);

    //TODO:
}

void Util::getWayAngle2D(int prm_vx_Center,
                               int prm_vy_Center,
                               int prm_ways,
                               angle prm_clearance,
                               angle* out_paAngle) {
    return Util::getWayAngle2D(Util::getAngle2D(prm_vx_Center, prm_vy_Center), prm_ways, prm_clearance, out_paAngle);
}

void Util::getWayAngle2D(angle prm_center, int prm_ways, angle prm_clearance, angle* out_paAngle) {
    int angstart = Util::addAng(prm_center, ((prm_ways - 1) * prm_clearance) / -2);

    for (int i = 0; i < prm_ways; i++) {
        out_paAngle[i] = Util::addAng(angstart, prm_clearance * i);
    }
}

void Util::getRadialAngle2D(angle prm_start, int prm_ways, angle* out_paAngle) {
    for (int i = 0; i < prm_ways; i++) {
        out_paAngle[i] = Util::addAng(prm_start, (angle)(1.0 * D360ANG / prm_ways * i));
    }
}

void Util::convRzRyToRyRz(angle prm_rz, angle prm_ry, angle& out_ry, angle& out_rz) {
    double vx,vy,vz;
    Util::convRzRyToVector(prm_rz, prm_ry , vx, vy, vz);
    Util::convVectorToRzRy(vx, vz, -1.0f*vy, out_ry, out_rz ); //-�X�O�xX����]RzRy����ւ�
    out_rz = D360ANG-out_rz; //Y����Z���l���邽�߁A�������ς�遁�t��]��360�������
}



//void Util::getWayAngle_LinedRzLongitude(angle prm_ang_center_rz, angle prm_ang_center_ry,
//                                              int prm_ways, angle prm_clearance,
//                                              angle* out_paAngleRz, angle* out_paAngleRy) {
//    float vx,vy,vz;
//    convRzRyToVector(prm_ang_center_rz, prm_ang_center_ry, vx, vy, vz);
//    float vx2,vy2,vz2;
//    //X���X�O�x��]
//    vx2 = vx;
//    vy2 = -vz;
//    vz2 = vy;
//
//    getWayAngle2D(prm_ang_center_rz, prm_ways, prm_clearance, out_paAngleRz);
//
//}

//void Util::getMoveRzRyWayShot3D_XZ(int prm_ways, angle prm_clearance, coord prm_tx, coord prm_ty, coord prm_tz,
//                                          angle& out_faceZ, angle* out_paAngRotY) {
//    angle tRz, tRy;
//    convVectorToRzRy(prm_tx, prm_ty, prm_tz, tRy, tRy);
//
//    angle angStart = addAng(tRy, ((prm_ways - 1) * prm_clearance) / -2);
//    for (int i = 0; i < prm_ways; i++) {
//        out_paAngRotY[i] = addAng(angstart, prm_clearance * i);
//    }
//}

angle Util::addAng(angle prm_ang, angle prm_offset) {
    return UTIL::simplifyAng(prm_ang + prm_offset);
}

angle Util::getAngDiff(angle prm_from, angle prm_to, int prm_way) {
    const angle from = UTIL::simplifyAng(prm_from);
    const angle to = UTIL::simplifyAng(prm_to);
    if (prm_way == TURN_CLOSE_TO) {
        if (0 <= from && from < D180ANG) {
            if (0 <= to && to < from) {
                return -1 * (from - to);
            } else if (to == from) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (from < to && to < from + D180ANG) {
                return to - from;
            } else if (to == from + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂Ő��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (from + D180ANG < to && to <= D360ANG) {
                return -1 * (from + (D360ANG - to));
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
                throwCriticalException("�A���O���l���͈͊O�ł�(1)�B\n"
                                           "from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= from && from <= D360ANG) {
            if (0 <= to && to < from - D180ANG) {
                return D360ANG - from + to;
            } else if (to == from - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return D180ANG;
            } else if (from - D180ANG < to && to < from) {
                return -1 * (from - to);
            } else if (from == to) {
                //�d�Ȃ��Ă�ꍇ
                return 0;
            } else if (from < to && to <= D360ANG) {
                return to - from;
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
                throwCriticalException("�A���O���l���͈͊O�ł�(2)�B\n"
                                           "from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_ANTICLOSE_TO) {
        if (0 <= from && from < D180ANG) {
            if (0 <= to && to < from) {
                return (D360ANG - from) + to;
            } else if (to == from) {
                //�d�Ȃ��Ă�ꍇ
                return -1 * D360ANG;
            } else if (from < to && to < from + D180ANG) {
                return -1 * (from + (D360ANG - to));
            } else if (to == from + D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return -1 * D180ANG;
            } else if (from + D180ANG < to && to <= D360ANG) {
                return to - from;
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
                throwCriticalException("�A���O���l���͈͊O�ł�(3)�B\n"
                                           "from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
            }
        } else if (D180ANG <= from && from <= D360ANG) {
            if (0 <= to && to < from - D180ANG) {
                return -1 * (from - to);
            } else if (to == from - D180ANG) {
                //�����΂������Ă���i�������͓������j
                //�d���Ȃ��̂ŕ��̒l�Ƃ���B(���m�ɂ� -D180ANG or D180ANG)
                return -1 * D180ANG;
            } else if (from - D180ANG < to && to < from) {
                return (D360ANG - from) + to;
            } else if (from == to) {
                //�d�Ȃ��Ă�ꍇ
                return -1 * D360ANG;
            } else if (from < to && to <= D360ANG) {
                return -1 * (from + (D360ANG - to));
            } else {
                //��������
                _TRACE_(FUNC_NAME<<" bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
                throwCriticalException("�A���O���l���͈͊O�ł�(4)�B\n"
                                           "from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
            }
        }
    } else if (prm_way == TURN_COUNTERCLOCKWISE) {
        if (from <= to) {
            return to - from;
        } else {
            return (D360ANG - from) + to;
        }
    } else if (prm_way == TURN_CLOCKWISE) {
        if (from >= to) {
            return -(from - to);
        } else {
            return -(from + (D360ANG - to));
        }
    } else {
        _TRACE_(FUNC_NAME<<" bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
        throwCriticalException("prm_way = TURN_CLOSE_TO/TURN_ANTICLOSE_TO/TURN_COUNTERCLOCKWISE/TURN_CLOCKWISE �ȊO���w�肳��Ă��܂��B");
    }

    _TRACE_("bad from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
    throwCriticalException("���̂�����p�̋��������߂�܂���B(1) \n"
                               "from=" << from << "/to=" << to<<"/prm_way="<<prm_way);
}

void Util::rotxy(int prm_x, int prm_y, angle prm_ang, int& out_x, int& out_y) {
    out_x = (int)(floor((prm_x * ANG_COS(prm_ang)) - (prm_y * ANG_SIN(prm_ang))));
    out_y = (int)(floor((prm_x * ANG_SIN(prm_ang)) + (prm_y * ANG_COS(prm_ang))));
}

// �����̓����蔻�� (x11,y11)-(x12,y12) �~ (x21,y21)-(x22,y22)
bool Util::chk2DLineCrossing(coord x11, coord y11, coord x12, coord y12, coord x21, coord y21, coord x22, coord y22) {

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

coord Util::getDistance(coord x1, coord y1, coord x2, coord y2) {
    return (coord)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))));
}
//int Util::getDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
//    return (int)sqrt((((double)(x2 - x1)) * ((double)(x2 - x1))) + (((double)(y2 - y1)) * ((double)(y2 - y1))) + (((double)(z2 - z1)) * ((double)(z2 - z1))));
//}


//void Util::convVectorToRzRy2(coord vx,
//                            coord vy,
//                            coord vz,
//                            angle& out_rz,
//                            angle& out_ry ) {
//    double dx = ABS(vx);
//    double dy = ABS(vy);
//    double dz = ABS(vz);
//    double out_nvx, out_nvy, out_nvz;
//    double t = 1.0 / sqrt(dx * dx + dy * dy + dz * dz);
//    out_nvx = t * dx;
//    out_nvy = t * dy;
//    out_nvz = t * dz;
//    //�P�ʃx�N�g������RzRy(�t��])�����߂�
//    s_ang rz, ry_rev;
//    Util::_srv.getFaceAngClosely(
//            (uint32_t)(out_nvx*10000000),
//            (uint32_t)(out_nvy*10000000),
//            (uint32_t)(out_nvz*10000000),
//            rz,
//            ry_rev
//    );
//    angle rot_z = rz * SANG_RATE;
//    angle rot_y_rev = ry_rev * SANG_RATE;
//    //�T���ɂ���ĉ�]�p��␳
//    if (vx >= 0) {
//        if (vy >= 0) {
//            if (vz >= 0) {
//                //���T��
//                out_rz = rot_z;
//                out_ry = (D360ANG - rot_y_rev);
//            } else { //vz < 0
//                //��܌T��
//                out_rz = rot_z;
//                out_ry = rot_y_rev;
//            }
//        } else { //vy < 0
//            if (vz >= 0) {
//                //��l�T��
//                out_rz = (D360ANG - rot_z);
//                out_ry = (D360ANG - rot_y_rev);
//            } else { //vz < 0
//                //�攪�T��
//                out_rz = (D360ANG - rot_z);
//                out_ry = rot_y_rev;
//            }
//        }
//    } else { //vx < 0
//        if (vy >= 0) {
//            if (vz >= 0) {
//                //���T��
//                out_rz = rot_z;
//                out_ry = (D180ANG + rot_y_rev);
//            } else { //vz < 0
//                //��Z�T��
//                out_rz = rot_z;
//                out_ry = (D180ANG - rot_y_rev);
//            }
//        } else { //vy < 0
//            if (vz >= 0) {
//                //��O�T��
//                out_rz = (D360ANG - rot_z);
//                out_ry = (D180ANG + rot_y_rev);
//            } else { //vz < 0
//                //�掵�T��
//                out_rz = (D360ANG - rot_z);
//                out_ry = (D180ANG - rot_y_rev);
//            }
//        }
//    }
//}

void Util::convVectorToRzRy(coord vx,
                            coord vy,
                            coord vz,
                            angle& out_rz,
                            angle& out_ry ) {
    if (vz == 0) {
        out_rz = Util::getAngle2D(vx, vy);
        out_ry = 0;
        return;
    }

    //���ꂩ�̗v�f��0�̏ꍇ�AgetAngle2D�̌��ʂ��傫������Ă��܂��B
    //�Ƃ肠�����P��ݒ肵�ċߎ������Ă������B
    //TODO:0 �����Ă����v�ɂ���B
    vx = (vx == 0 ? 1 : vx);
    vy = (vy == 0 ? 1 : vy);
//    vz = (vz == 0 ? 1 : vz);
    coord dx = ABS(vx);
    coord dy = ABS(vy);
    coord dz = ABS(vz);

    const angle prj_rXZ = Util::getAngle2D_first_quadrant(dx, dz);
    const angle prj_rXY = Util::getAngle2D_first_quadrant(dx, dy); //Rz
    angle rot_z, rot_y_rev;
    const double rate = ((1.0/SANG_RATE)*SR_AC);
    if (0 <= prj_rXZ && prj_rXZ <= D45ANG) {
        s_ang prj_s_ang_rXY = (s_ang)(prj_rXY*rate);
        s_ang prj_s_ang_rXZ = (s_ang)(prj_rXZ*rate);
        rot_z = Util::PROJANG_XY_XZ_TO_ROTANG_z[prj_s_ang_rXY][prj_s_ang_rXZ];
        rot_y_rev = Util::PROJANG_XY_XZ_TO_ROTANG_y_REV[prj_s_ang_rXY][prj_s_ang_rXZ];
    } else if (prj_rXZ <= D90ANG) {
        const angle prj_rZY = Util::getAngle2D_first_quadrant(dz, dy); //Rz
        const angle prj_rZX = Util::getAngle2D_first_quadrant(dz, dx);
        s_ang prj_s_ang_rZY = (s_ang)(prj_rZY*rate);
        s_ang prj_s_ang_rZX = (s_ang)(prj_rZX*rate);
        rot_z = Util::PROJANG_ZY_ZX_TO_ROTANG_x_REV[prj_s_ang_rZY][prj_s_ang_rZX];
        rot_y_rev = D90ANG - Util::PROJANG_ZY_ZX_TO_ROTANG_y[prj_s_ang_rZY][prj_s_ang_rZX];
    } else {
        throwCriticalException("�͈͂��j�]���Ă܂��Bprj_rXZ="<<prj_rXZ<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
#ifdef MY_DEBUG
    if (0 <= prj_rXY && prj_rXY < D45ANG) {
        //OK
    } else if (D45ANG <= prj_rXY && prj_rXY <= D90ANG) {
        //OK
    } else {
        throwCriticalException("�͈͂��j�]���Ă܂��Bprj_rXY="<<prj_rXY<<" ����:"<<vx<<","<<vy<<","<<vz);
    }
#endif
    //�T���ɂ���ĉ�]�p��␳
    if (vx >= 0) {
        if (vy >= 0) {
            if (vz >= 0) {
                //���T��
                out_rz = rot_z;
                out_ry = (D360ANG - rot_y_rev);
            } else { //vz < 0
                //��܌T��
                out_rz = rot_z;
                out_ry = rot_y_rev;
            }
        } else { //vy < 0
            if (vz >= 0) {
                //��l�T��
                out_rz = (D360ANG - rot_z);
                out_ry = (D360ANG - rot_y_rev);
            } else { //vz < 0
                //�攪�T��
                out_rz = (D360ANG - rot_z);
                out_ry = rot_y_rev;
            }
        }
    } else { //vx < 0
        if (vy >= 0) {
            if (vz >= 0) {
                //���T��
                out_rz = rot_z;
                out_ry = (D180ANG + rot_y_rev);
            } else { //vz < 0
                //��Z�T��
                out_rz = rot_z;
                out_ry = (D180ANG - rot_y_rev);
            }
        } else { //vy < 0
            if (vz >= 0) {
                //��O�T��
                out_rz = (D360ANG - rot_z);
                out_ry = (D180ANG + rot_y_rev);
            } else { //vz < 0
                //�掵�T��
                out_rz = (D360ANG - rot_z);
                out_ry = (D180ANG - rot_y_rev);
            }
        }
    }

#ifdef MY_DEBUG
    if (D360ANG < out_rz || 0 > out_rz || D360ANG < out_ry || 0 > out_ry) {
        throwCriticalException("�͈͊O�ł��v�����B\n out_rz,out_ry="<<out_rz<<","<<out_ry<<" vx,vy,vz="<<vx<<","<<vy<<","<<vz);
    }
#endif
//    out_rz = simplifyAng(out_rz);
//    out_ry = simplifyAng(out_ry);
}

void Util::convRzRyToVector(angle prm_rz,
                            angle prm_ry,
                            double& out_nvx,
                            double& out_nvy,
                            double& out_nvz) {
    //void SphereRadiusVectors::getVectorClosely(int out_faceY, int prm_angZ, uint16_t& out_x, uint16_t& out_y, uint16_t& out_z) {
    //��]�p�ɂ���ČT�����l�����AgetVectorClosely�̃p�����[�^�p(< 900)���o��
    int xsign, ysign, zsign;
    angle rz, ry_rev;

    if (0 <= prm_rz && prm_rz < D90ANG) {
        rz = (prm_rz - D0ANG);
        if (0 <= prm_ry && prm_ry < D90ANG) { //��܌T��
            ry_rev = prm_ry;
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (prm_ry < D180ANG) { //��Z�T��
            ry_rev = (D180ANG - prm_ry);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else if (prm_ry < D270ANG) { //���T��
            ry_rev = (prm_ry - D180ANG);
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (prm_ry <= D360ANG) { //���T��
            ry_rev = (D360ANG - prm_ry);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else {
            throwCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(1) prm_rz="<<prm_rz<<" prm_ry="<<prm_ry);
        }
    } else if (prm_rz < D180ANG) {
        rz = (D180ANG - prm_rz);

        if (0 <= prm_ry && prm_ry < D90ANG) { //���T��
            ry_rev = prm_ry;
            xsign = -1;
            ysign = 1;
            zsign = 1;
        } else if (prm_ry < D180ANG) { //���T��
            ry_rev = (D180ANG - prm_ry);
            xsign = 1;
            ysign = 1;
            zsign = 1;
        } else if (prm_ry < D270ANG) { //��܌T��
            ry_rev = (prm_ry - D180ANG);
            xsign = 1;
            ysign = 1;
            zsign = -1;
        } else if (prm_ry <= D360ANG) { //��Z�T��
            ry_rev = (D360ANG - prm_ry);
            xsign = -1;
            ysign = 1;
            zsign = -1;
        } else {
            throwCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(2) prm_rz="<<prm_rz<<" prm_ry="<<prm_ry);
        }

    } else if (prm_rz < D270ANG) {
        rz = (prm_rz - D180ANG);
        if (0 <= prm_ry && prm_ry < D90ANG) { //��O�T��
            ry_rev = prm_ry;
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (prm_ry < D180ANG) { //��l�T��
            ry_rev = (D180ANG - prm_ry);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else if (prm_ry < D270ANG) { //�攪�T��
            ry_rev = (prm_ry - D180ANG);
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (prm_ry <= D360ANG) { //�掵�T��
            ry_rev = (D360ANG - prm_ry);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else {
            throwCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(3) prm_rz="<<prm_rz<<" prm_ry="<<prm_ry);
        }
    } else if (prm_rz <= D360ANG) {
        rz = (D360ANG - prm_rz);
        if (0 <= prm_ry && prm_ry < D90ANG) { //�攪�T��
            ry_rev = prm_ry;
            xsign = 1;
            ysign = -1;
            zsign = -1;
        } else if (prm_ry < D180ANG) { //�掵�T��
            ry_rev = (D180ANG - prm_ry);
            xsign = -1;
            ysign = -1;
            zsign = -1;
        } else if (prm_ry < D270ANG) { //��O�T��
            ry_rev = (prm_ry - D180ANG);
            xsign = -1;
            ysign = -1;
            zsign = 1;
        } else if (prm_ry <= D360ANG) { //��l�T��
            ry_rev = (D360ANG - prm_ry);
            xsign = 1;
            ysign = -1;
            zsign = 1;
        } else {
            throwCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(4) prm_rz="<<prm_rz<<" prm_ry="<<prm_ry);
        }
    } else {
        throwCriticalException("getNormalizedVectorZY: �Ȃ񂩂��������ł���(5) prm_rz="<<prm_rz<<" prm_ry="<<prm_ry);
    }
    uint32_t vx, vy, vz;
    Util::_srv.getVectorClosely(rz, ry_rev, vx, vy, vz);
    out_nvx = xsign * (int)vx * (1.0 / 10000000.0);
    out_nvy = ysign * (int)vy * (1.0 / 10000000.0);
    out_nvz = zsign * (int)vz * (1.0 / 10000000.0);
}

void Util::getPlaneNomalVec(float p1x, float p1y, float p1z,
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

void Util::setWorldMatrix_ScRxRzRyMv(const GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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
     D3DXMatrixRotationY(&matrixRotX, Util::RAD_UNITLEN[s_rx]/LEN_UNIT);
     D3DXMatrixRotationX(&matrixRotY, Util::RAD_UNITLEN[s_ry]/LEN_UNIT);
     D3DXMatrixRotationZ(&matrixRotZ, Util::RAD_UNITLEN[s_rz]/LEN_UNIT);
     D3DXMatrixTranslation(&matrixTrans, _x/LEN_UNIT, _y/LEN_UNIT, _z/LEN_UNIT);
     D3DXMATRIX matrixWorld = matrixRotX * matrixRotY * matrixRotZ * matrixTrans;
     */
}

void Util::setWorldMatrix_RzRy(const GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);

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


void Util::setWorldMatrix_RzRy(angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |  cosRz*cosRy, sinRz,  cosRz*-sinRy,   0  |
    // | -sinRz*cosRy, cosRz, -sinRz*-sinRy,   0  |
    // |        sinRy,     0,         cosRy,   0  |
    // |            0,     0,             0,   1  |
    const float sinRy = (float)ANG_SIN(prm_ry);
    const float cosRy = (float)ANG_COS(prm_ry);
    const float sinRz = (float)ANG_SIN(prm_rz);
    const float cosRz = (float)ANG_COS(prm_rz);

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

void Util::setWorldMatrix_RxRzRy(const GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);

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

void Util::setWorldMatrix_RxRzRy(angle prm_rx, angle prm_rz, angle prm_ry, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy,          sinRz,                         cosRz*-sinRy,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy),    cosRx*cosRz, ( cosRx*-sinRz*-sinRy + sinRx*cosRy),   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy),   -sinRx*cosRz, (-sinRx*-sinRz*-sinRy + cosRx*cosRy),   0  |
    // |                                   0,              0,                                    0,   1  |
    const float sinRx = (float)ANG_SIN(prm_rx);
    const float cosRx = (float)ANG_COS(prm_rx);
    const float sinRy = (float)ANG_SIN(prm_ry);
    const float cosRy = (float)ANG_COS(prm_ry);
    const float sinRz = (float)ANG_SIN(prm_rz);
    const float cosRz = (float)ANG_COS(prm_rz);

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


void Util::setWorldMatrix_ScRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
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


void Util::mulWorldMatrix_RzRyScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //    |  cosRz*cosRy*sx  sinRz*sy   cosRz*-sinRy*sz   0 |
    //    | -sinRz*cosRy*sx  cosRz*sy  -sinRz*-sinRy*sz   0 |
    //    |  sinRy*sx        0          cosRy*sz          0 |
    //    |  dx              dy         dz                1 |
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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

void Util::setWorldMatrix_RxRzRyScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ Y����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s����쐬
    //��XYZ�̏��łȂ����Ƃɒ���
    // |                         cosRz*cosRy*sx,          sinRz*sy,                         cosRz*-sinRy*sz,   0  |
    // | ( cosRx*-sinRz*cosRy + sinRx*sinRy)*sx,    cosRx*cosRz*sy, ( cosRx*-sinRz*-sinRy + sinRx*cosRy)*sz,   0  |
    // | (-sinRx*-sinRz*cosRy + cosRx*sinRy)*sx,   -sinRx*cosRz*sy, (-sinRx*-sinRz*-sinRy + cosRx*cosRy)*sz,   0  |
    // |                                     dx,                dy,                                      dz,   1  |
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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


void Util::setWorldMatrix_RxRyRzScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Y����] �~ Z����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s����쐬
    //    |                           cosRy*cosRz*sx,                        cosRy*sinRz*sy  ,      -sinRy*sz,  0 |
    //    | ((sinRx*sinRy*cosRz +  cosRx*-sinRz)*sx), ((sinRx*sinRy*sinRz +  cosRx*cosRz)*sy), sinRx*cosRy*sz,  0 |
    //    | ((cosRx*sinRy*cosRz + -sinRx*-sinRz)*sx), ((cosRx*sinRy*sinRz + -sinRx*cosRz)*sy), cosRx*cosRy*sz,  0 |
    //    |                                       dx,                                      dy,             dz,  1 |

    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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


void Util::setWorldMatrix_RxRzRxScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ X����] �~ Z����] �~ X����] �~ �g��k�� �~ ���s�ړ� �̕ϊ��s����쐬.
    //��Y����]������܂���BRY�͂Q��ڂ�X����]�ƂȂ�
    //|         cosRz*sx,                          sinRz*cosRy*sy ,                          sinRz*sinRy*sz, 0 |
    //|  cosRx*-sinRz*sx, (( cosRx*cosRz*cosRy + sinRx*-sinRy)*sy), (( cosRx*cosRz*sinRy + sinRx*cosRy)*sz), 0 |
    //| -sinRx*-sinRz*sx, ((-sinRx*cosRz*cosRy + cosRx*-sinRy)*sy), ((-sinRx*cosRz*sinRy + cosRx*cosRy)*sz), 0 |
    //|               dx,                                       dy,                                      dz, 1 |
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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


void Util::setWorldMatrix_RzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ Z����] �~ ���s�ړ� �̕ϊ��s����쐬
    // |cosZ  , sinZ , 0  , 0  |
    // |-sinZ , cosZ , 0  , 0  |
    // |0     , 0    , 1  , 0  |
    // |dx    , dy   , dz , 1  |
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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


void Util::setWorldMatrix_ScRzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    //World�ϊ�
    //�P�ʍs�� �~ �g��k�� �~ Z����] �~ ���s�ړ� �̕ϊ��s����쐬
    // |sx*cosZ , sx*sinZ , 0    , 0  |
    // |sy*-sinZ, sy*cosZ , 0    , 0  |
    // |0       , 0       , sz   , 0  |
    // |dx      , dy      , dz   , 1  |
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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

void Util::setWorldMatrix_ScMvRxRzRy(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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

void Util::updateWorldMatrix_Mv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}

void Util::setWorldMatrix_BxyzScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
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

void Util::setWorldMatrix_BxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {

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



void Util::setWorldMatrix_ScRzBxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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


void Util::mulWorldMatrix_ScRxRzRyMv(const GeometricActor* const prm_pActor, D3DXMATRIX& inout_matWorld) {
    //World�ϊ�
    //�g��k�� �~ X����] �~ Z����] �~ Y����] �~ ���s�ړ� �̕ϊ��s���ݒ�<BR>
    //��XYZ�̏��łȂ����Ƃɒ���
    // | sx*cosRz*cosRy                           , sx*sinRz       , sx*cosRz*-sinRy                           , 0|
    // | (sy* cosRx*-sinRz*cosRy + sy*sinRx*sinRy), sy*cosRx*cosRz , (sy* cosRx*-sinRz*-sinRy + sy*sinRx*cosRy), 0|
    // | (sz*-sinRx*-sinRz*cosRy + sz*cosRx*sinRy), sz*-sinRx*cosRz, (sz*-sinRx*-sinRz*-sinRy + sz*cosRx*cosRy), 0|
    // | dx                                       , dy             , dz                                        , 1|
    const float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    const float cosRx = (float)ANG_COS(prm_pActor->_rx);
    const float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    const float cosRy = (float)ANG_COS(prm_pActor->_ry);
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);
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



void Util::setWorldMatrix_RzBxyzMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
    const D3DXMATRIX& matView = _pCam->_matView;
    const float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    const float cosRz = (float)ANG_COS(prm_pActor->_rz);

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
void Util::setWorldMatrix_ScMv(const GeometricActor* const prm_pActor, D3DXMATRIX& out_matWorld) {
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

