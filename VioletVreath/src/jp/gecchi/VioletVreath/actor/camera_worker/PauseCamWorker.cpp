#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
    cd_ = 0;
    mdz_flg_ = false;
    pVPGuide_ = NULL;
    mdz_vx_ = mdz_vy_ = mdz_vz_ = mdz_t_ = 0.0;
//    orderActorToFactory(UTIL::easy_hash("VPGuide"), ViewPointGuide, "VPGuide");
//    pVPGuide_ = (ViewPointGuide*)(obtainActorFromFactory(UTIL::easy_hash("VPGuide")));
    pVPGuide_ = createInFactory(ViewPointGuide, "VPGuide");
}

void PauseCamWorker::initialize() {
    pVPGuide_->inactivateImmed();
    P_WORLD->getDirector()->addSubGroup(pVPGuide_);
}


void PauseCamWorker::processBehavior() {
    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = P_CAM->_pViewPoint;
    GgafDxInput::updateMouseState();

    long mx,my,mz,mdx,mdy,mdz;
    GgafDxInput::getMousePointer(&mx, &my, &mz);
    GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Y�̓C���o�[�Y

//    if (GgafDxInput::isPushedDownMouseButton(0) || GgafDxInput::isPushedDownMouseButton(1) || GgafDxInput::isPushedDownMouseButton(2)) {
//        pVPGuide_->activate(); //�K�C�hON
//    } else if(GgafDxInput::isReleasedUpMouseButton(0) || GgafDxInput::isReleasedUpMouseButton(1) || GgafDxInput::isReleasedUpMouseButton(2)) {
//        pVPGuide_->inactivate(); //�K�C�hOFF
//    }

    if (GgafDxInput::isPushedDownMouseButton(0) || GgafDxInput::isPushedDownMouseButton(1) || GgafDxInput::isPushedDownMouseButton(2)) {
        RECT cRect; // �N���C�A���g�̈�̋�`
        int cw, ch; // �N���C�A���g�̈�̕��A����
        // �N���C�A���g�̈�̕��E�������v�Z
        GetClientRect(GgafDxGod::_pHWndPrimary, &cRect);
        cw = cRect.right - cRect.left;
        ch = cRect.bottom - cRect.top;
        if (cw > ch) {
            cd_ = ch;
        } else {
            cd_ = cw;
        }
        if (!pCam->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
            move_target_X_CAM_ = pCam->_X;
            move_target_Y_CAM_ = pCam->_Y;
            move_target_Z_CAM_ = pCam->_Z;
        }
        if (!pVP->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
            //���m��VP�ɍĐݒ�
            pVP->_X = DX_C(pCam->_pVecCamLookatPoint->x);
            pVP->_Y = DX_C(pCam->_pVecCamLookatPoint->y);
            pVP->_Z = DX_C(pCam->_pVecCamLookatPoint->z);
            move_target_X_VP_ = pVP->_X;
            move_target_Y_VP_ = pVP->_Y;
            move_target_Z_VP_ = pVP->_Z;
        }
    }

    if ( !(GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1)) &&
         (GgafDxInput::isBeingPressedMouseButton(0) || GgafDxInput::isBeingPressedMouseButton(1) || GgafDxInput::isBeingPressedMouseButton(2))
    ) {


        //���_�𒆐S�ɃJ��������]�ړ�
        //�J�����𒆐S�Ɏ��_����]�ړ�
        //�J�������Ǝ��_�����s�ړ�
        //���ʂ̌v�Z

        //���[���h��]�������x�N�g���A(vX_axis, vY_axis, vZ_axis) ���v�Z begin =======>

        //���ʉ�]��(vx,vy)�����߂�
        //double a = asin(1.0*dx/dy); //a XY���ʂ̂Ȃ��p 90�x��] x��y y��-x
        double vx = mdy;
        double vy = -mdx;
        double vz = 0;
        double d = sqrt(vx * vx + vy * vy); //�|�C���^�ړ��s�N�Z������

        double t = 1.0 / d;
        vx = t * vx;
        vy = t * vy;
        vz = 0;
        //���ʉ�]��(vx,vy)��VP�̃��[���h��Ԏ��ɕϊ�
        //VP��CAM�̃��[���h��ԕ����x�N�g����@���Ƃ��镽�ʏ�ɉ�]���x�N�g���͑��݂���

        D3DXMATRIX InvView;
        D3DXMatrixInverse( &InvView, NULL, &pCam->_matView);
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //�����x�N�g��(0,0,0)->(vx,vy,vz) ���t�r���[�ϊ�
        //�ϊ�������x�N�g�� = (vx,vy,vz)�ϊ�����W - (0,0,0)�ϊ�����W
        //               <------------  (vx,vy,vz)�ϊ�����W-------------------------->    <-- (0,0,0)�ϊ�����W -->
        double vX_axis = vx*InvView._11 + vy*InvView._21 + vz*InvView._31 + InvView._41  -    InvView._41;
        double vY_axis = vx*InvView._12 + vy*InvView._22 + vz*InvView._32 + InvView._42  -    InvView._42;
        double vZ_axis = vx*InvView._13 + vy*InvView._23 + vz*InvView._33 + InvView._43  -    InvView._43;
        //���K��
        double d2 = sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
        double t2 = 1.0 / d2;
        vX_axis = t2 * vX_axis;
        vY_axis = t2 * vY_axis;
        vZ_axis = t2 * vZ_axis;
        //<==========  ���[���h��]�������x�N�g���A(vX_axis, vY_axis, vZ_axis) ���v�Z end


        //������W(x, y, z)�ɂ����āA��]�̎���(��, ��, ��)�ŁA�Ɖ񂷉�]
        //P = (0; x, y, z)
        //Q = (cos(��/2); �� sin(��/2), �� sin(��/2), �� sin(��/2))
        //R = (cos(��/2); -�� sin(��/2), -�� sin(��/2), -�� sin(��/2))
        //R P Q = (0; ����)
        //(��, ��, ��) = (vX_axis,vY_axis,vY_axis);
        //(x, y, z) �� CAM �� VP

        //���_�𒆐S�ɃJ��������]�ړ�
        if (GgafDxInput::isBeingPressedMouseButton(0) && (mdx != 0 || mdy != 0)) {
            //���_���J���� �̕����x�N�g��(x,y,z)
            double x = move_target_X_CAM_ - move_target_X_VP_;
            double y = move_target_Y_CAM_ - move_target_Y_VP_;
            double z = move_target_Z_CAM_ - move_target_Z_VP_;

            angle rz1 = UTIL::getAngle2D(x, y);

            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = UTIL::getAngle2D(Q._x,Q._y);

            //Q.x_, Q.y_, Q.z_ ����]��̍��W�ƂȂ�
            if (ABS(mdy) > ABS(mdx)/2) { //�㉺�u���␳
                move_target_XY_CAM_UP_ += UTIL::getAngDiff(rz1, rz2);
                move_target_XY_CAM_UP_ = UTIL::simplifyAng(move_target_XY_CAM_UP_);
            }
            move_target_X_CAM_ = Q._x + move_target_X_VP_;
            move_target_Y_CAM_ = Q._y + move_target_Y_VP_;
            move_target_Z_CAM_ = Q._z + move_target_Z_VP_;
        }
        //�J�����𒆐S�Ɏ��_����]�ړ�
        if (GgafDxInput::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //�J���������_ �̕����x�N�g��(x,y,z)
            double x = move_target_X_VP_ - move_target_X_CAM_;
            double y = move_target_Y_VP_ - move_target_Y_CAM_;
            double z = move_target_Z_VP_ - move_target_Z_CAM_;
            angle rz1 = UTIL::getAngle2D(x, y);
            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = UTIL::getAngle2D(Q._x,Q._y);
            if (ABS(mdy) > ABS(mdx)/2) { //�㉺�u���␳
                move_target_XY_CAM_UP_ += UTIL::getAngDiff(rz1, rz2);
                move_target_XY_CAM_UP_ = UTIL::simplifyAng(move_target_XY_CAM_UP_);
            }
            //Q.x_, Q.y_, Q.z_ ����]��̍��W�ƂȂ�
            move_target_X_VP_ = Q._x + move_target_X_CAM_;
            move_target_Y_VP_ = Q._y + move_target_Y_CAM_;
            move_target_Z_VP_ = Q._z + move_target_Z_CAM_;
        }
        //�J�������Ǝ��_�����s�ړ�
        if (GgafDxInput::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            stop_renge_ = 60000;
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //��]���������p�x
            double cosHalf = cos(ang/2);

            double x = move_target_X_VP_ - move_target_X_CAM_;
            double y = move_target_Y_VP_ - move_target_Y_CAM_;
            double z = move_target_Z_VP_ - move_target_Z_CAM_;

            //���K��
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q

            double r = ((d/cd_) * PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2));

            move_target_X_CAM_ += (Q._x*r);
            move_target_Y_CAM_ += (Q._y*r);
            move_target_Z_CAM_ += (Q._z*r);

            move_target_X_VP_ += (Q._x*r);
            move_target_Y_VP_ += (Q._y*r);
            move_target_Z_VP_ += (Q._z*r);
        }

    } else if (mdz != 0 || (GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
        stop_renge_ = 60000;
        if (mdz_flg_ == false) {
            mdz_total_ = 0;
            if (!pCam->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
                move_target_X_CAM_ = pCam->_X;
                move_target_Y_CAM_ = pCam->_Y;
                move_target_Z_CAM_ = pCam->_Z;
            }
            if (!pVP->_pKurokoA->isRunnigSmoothMvVeloSequence()) {
                pVP->_X = DX_C(pCam->_pVecCamLookatPoint->x);
                pVP->_Y = DX_C(pCam->_pVecCamLookatPoint->y);
                pVP->_Z = DX_C(pCam->_pVecCamLookatPoint->z);
                move_target_X_VP_ = pVP->_X;
                move_target_Y_VP_ = pVP->_Y;
                move_target_Z_VP_ = pVP->_Z;
            }
            cam_X_ = pCam->_X;
            cam_Y_ = pCam->_Y;
            cam_Z_ = pCam->_Z;
            vp_X_ = pVP->_X;
            vp_Y_ = pVP->_Y;
            vp_Z_ = pVP->_Z;
            //�J���� �� ���_ �̕����x�N�g��
            double vx = pVP->_X - pCam->_X;
            double vy = pVP->_Y - pCam->_Y;
            double vz = pVP->_Z - pCam->_Z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            mdz_vx_ = t * vx;
            mdz_vy_ = t * vy;
            mdz_vz_ = t * vz;
        }
//        mdz_total_ += mdz; //�A���z�C�[����]���A���Z
//        double r = (mdz_total_*PX_UNIT*LEN_UNIT/10.0);
//        move_target_X_CAM_ = cam_X_ + mdz_vx_*r;
//        move_target_Y_CAM_ = cam_Y_ + mdz_vy_*r;
//        move_target_Z_CAM_ = cam_Z_ + mdz_vz_*r;
//        move_target_X_VP_  = vp_X_ + mdz_vx_*r;
//        move_target_Y_VP_  = vp_Y_ + mdz_vy_*r;
//        move_target_Z_VP_  = vp_Z_ + mdz_vz_*r;
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/cd_) * GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2)*LEN_UNIT;
        }
        move_target_X_CAM_ += mdz_vx_*r;
        move_target_Y_CAM_ += mdz_vy_*r;
        move_target_Z_CAM_ += mdz_vz_*r;
        move_target_X_VP_  += mdz_vx_*r;
        move_target_Y_VP_  += mdz_vy_*r;
        move_target_Z_VP_  += mdz_vz_*r;
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }

    if (ABS(move_target_X_CAM_ - pCam->_X) < 10 && ABS(move_target_Y_CAM_ - pCam->_Y) < 10 && ABS(move_target_Z_CAM_ - pCam->_Z) < 10) {
        //OK
    } else {
        pCam->_pKurokoA->setMvAng(move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_);

        int td1 = UTIL::getDistance(pCam->_X, pCam->_Y, pCam->_Z,
                                           move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_);
        if (ABS(td1) > 10) {
            pCam->_pKurokoA->execSmoothMvVeloSequence(0, td1, 20, 0.4, 0.6);
        }
    }
    if (ABS(move_target_X_VP_ - pVP->_X) < 10 && ABS(move_target_Y_VP_ - pVP->_Y) < 10 && ABS(move_target_Z_VP_ - pVP->_Z) < 10) {
        //OK
    } else {
        pVP->_pKurokoA->setMvAng(move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_);
        int td2 = UTIL::getDistance(pVP->_X, pVP->_Y, pVP->_Z,
                                           move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_);
        if (ABS(td2) > 10) {
            pVP->_pKurokoA->execSmoothMvVeloSequence(0, td2, 20, 0.4, 0.6);
        }
    }


    //�J������UP���v�Z
    angvelo angvelo_cam_up = 30000 / 20;
    if (angXY_nowCamUp_ != move_target_XY_CAM_UP_) {
        angle da = UTIL::getAngDiff(angXY_nowCamUp_, move_target_XY_CAM_UP_);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            angXY_nowCamUp_ = move_target_XY_CAM_UP_;
        } else {
            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
        }
        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
        pCam->_pVecCamUp->x = ANG_COS(angXY_nowCamUp_);
        pCam->_pVecCamUp->y = ANG_SIN(angXY_nowCamUp_);
        pCam->_pVecCamUp->z = 0.0f;
    }


    pCam->_pKurokoA->behave();
    pVP->_pKurokoA->behave();

}

PauseCamWorker::~PauseCamWorker() {
}
