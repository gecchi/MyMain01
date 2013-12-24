#include "stdafx.h"
#include "VvvCamWorker.h"

#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "VvvGod.h"
#include "actor/VvvCamera.h"
#include "scene/VvvUniverse.h"
#include "actor/VvvViewPoint.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamWorker::VvvCamWorker(const char* prm_name) : DefaultGeometricActor(prm_name) {
    _class_name = "VvvCamWorker";
    t_x_VP_ =  0;
    t_y_VP_ =  0;
    t_z_VP_ =  0;
    t_x_CAM_ =  0;
    t_y_CAM_ =  0;
    t_z_CAM_ =  0;
    frame_of_behaving_since_onSwitch_ = 0;
    pCam_ = nullptr;
    pVp_ = nullptr;
    t_cam_up_face_ = 2;

    cd_ = 0;
    mdz_flg_ = false;
    mdz_vx_ = mdz_vy_ = mdz_vz_ = mdz_t_ = 0.0;
    //���ӁFCamera�͂܂���������Ă��Ȃ����߂�����P_CAM�͎g�p�s��
}

void VvvCamWorker::initialize() {
    pCam_ = P_CAM;
    pVp_ = (VvvViewPoint*)(pCam_->getViewPoint());
    t_x_VP_ = pVp_->_x;
    t_y_VP_ = pVp_->_y;
    t_z_VP_ = pVp_->_z;
    t_x_CAM_ = pCam_->_x;
    t_y_CAM_ = pCam_->_y;
    t_z_CAM_ = pCam_->_z;
    t_cam_up_face_ = pCam_->up_face_;

}
void VvvCamWorker::onActive() {
    //���݂̃^�[�Q�b�g���ă^�[�Q�b�g
    slideMvCamTo(t_x_CAM_, t_y_CAM_, t_z_CAM_, 60);
    slideMvVpTo(t_x_VP_, t_y_VP_, t_z_VP_, 60);
}

void VvvCamWorker::slideMvCamTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvCamTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void VvvCamWorker::slideMvVpTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t) {
    slideMvVpTo(pTarget->_x, pTarget->_y, pTarget->_z, t);
}
void VvvCamWorker::slideMvCamTo(coord tx, coord ty, coord tz, frame t) {
    t_x_CAM_ = tx;
    t_y_CAM_ = ty;
    t_z_CAM_ = tz;
    pCam_->slideMvTo(tx, ty, tz, t);
}
void VvvCamWorker::slideMvVpTo(coord tx, coord ty, coord tz, frame t) {
    t_x_VP_ = tx;
    t_y_VP_ = ty;
    t_z_VP_ = tz;
    pVp_->slideMvTo(tx, ty, tz, t);
}

void VvvCamWorker::processBehavior() {
    GgafDxInput::updateMouseState();

    //TODO:���x���グ��A�C�f�B�A
    //�}�E�X�|�C���g�̗��������Amdx,mdy,mdz�́A�R�t���[���قǉߋ��Ƃ̍��ɂ���Ɖ�]�������肷�邾�낤

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
        D3DXMatrixInverse( &InvView, nullptr, &pCam_->_matView);
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
            double x = t_x_CAM_ - t_x_VP_;
            double y = t_y_CAM_ - t_y_VP_;
            double z = t_z_CAM_ - t_z_VP_;

            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            slideMvCamTo(Q._x + t_x_VP_, Q._y + t_y_VP_, Q._z + t_z_VP_, 60);
        }
        //�J�����𒆐S�Ɏ��_����]�ړ�
        if (GgafDxInput::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //�J���������_ �̕����x�N�g��(x,y,z)
            double x = t_x_VP_ - t_x_CAM_;
            double y = t_y_VP_ - t_y_CAM_;
            double z = t_z_VP_ - t_z_CAM_;
            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            slideMvVpTo(Q._x + t_x_CAM_, Q._y + t_y_CAM_, Q._z + t_z_CAM_, 60);
        }
        //�J�������Ǝ��_�����s�ړ�
        if (GgafDxInput::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //��]���������p�x
            double cosHalf = cos(ang/2);
            double x = t_x_VP_ - t_x_CAM_;
            double y = t_y_VP_ - t_y_CAM_;
            double z = t_z_VP_ - t_z_CAM_;
            //���K��
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            double r = ((d/cd_) * PX_C(PROPERTY::GAME_BUFFER_WIDTH*2));
            slideMvCamTo(t_x_CAM_ + (Q._x*r),
                         t_y_CAM_ + (Q._y*r),
                         t_z_CAM_ + (Q._z*r) , 60);
            slideMvVpTo(t_x_VP_ + (Q._x*r),
                        t_y_VP_ + (Q._y*r),
                        t_z_VP_ + (Q._z*r) , 60);
        }

    } else if (mdz != 0 || (GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
        if (mdz_flg_ == false) {
            //�z�C�[�������i���������j�ŏ��̃t���[��
            mdz_total_ = 0;
            //�J���� �� ���_ �̕����x�N�g��
            double vx = pVp_->_x - pCam_->_x;
            double vy = pVp_->_y - pCam_->_y;
            double vz = pVp_->_z - pCam_->_z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            mdz_vx_ = t * vx;
            mdz_vy_ = t * vy;
            mdz_vz_ = t * vz;
        }
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/cd_) * PROPERTY::GAME_BUFFER_WIDTH*2)*LEN_UNIT;
        }
        if (mdx != 0 || mdy != 0 || mdz != 0) {
            slideMvCamTo(t_x_CAM_ + mdz_vx_*r,
                         t_y_CAM_ + mdz_vy_*r,
                         t_z_CAM_ + mdz_vz_*r , 60);
            slideMvVpTo(t_x_VP_ + mdz_vx_*r,
                        t_y_VP_ + mdz_vy_*r,
                        t_z_VP_ + mdz_vz_*r , 60);
        }
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }


}

VvvCamWorker::~VvvCamWorker() {
}
