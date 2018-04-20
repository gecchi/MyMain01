#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/GgafLibConfig.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

AroundViewCamWorker::AroundViewCamWorker(const char* prm_name, DefaultCamera* prm_pCamera) : CameraWorker(prm_name, prm_pCamera) {
    _class_name = "AroundViewCamWorker";
    cd_ = 0;
    mdz_flg_ = false;
    mdz_vx_ = mdz_vy_ = mdz_vz_ = mdz_t_ = 0.0;
    mdz_total_ = 0;
}

void AroundViewCamWorker::initialize() {
    CameraWorker::initialize();
}

void AroundViewCamWorker::onActive() {
    CameraWorker::onActive();
    //CameraWorker::onActive(); ���㏑�����āA
    //���̏���W���^�[�Q�b�g���W�ɏ㏑��
    slideMvCamTo(pCam_->_x, pCam_->_y, pCam_->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvVpTo(pVp_->_x, pVp_->_y, pVp_->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvUpVecTo(pUp_->_x, pUp_->_y, pUp_->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
}

void AroundViewCamWorker::processBehavior() {
    //TODO:���x���グ��A�C�f�B�A
    //�}�E�X�|�C���g�̗��������Amdx,mdy,mdz�́A�R�t���[���قǉߋ��Ƃ̍��ɂ���Ɖ�]�������肷�邾�낤
    long mx,my,mz,mdx,mdy,mdz;
    GgafDxInput::getMousePointer(&mx, &my, &mz);
    GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Y�̓C���o�[�Y
    bool isPressedMouseButton0 = GgafDxInput::isPressedMouseButton(0);
    bool isPressedMouseButton1 = GgafDxInput::isPressedMouseButton(1);
    bool isPressedMouseButton2 = GgafDxInput::isPressedMouseButton(2);
    bool isPushedMouseButton0 = GgafDxInput::isPushedDownMouseButton(0);
    bool isPushedMouseButton1 = GgafDxInput::isPushedDownMouseButton(1);
    bool isPushedMouseButton2 = GgafDxInput::isPushedDownMouseButton(2);


//    if (isPushedMouseButton0 || isPushedMouseButton1 || isPushedMouseButton2) {
//        pVPGuide_->activate(); //�K�C�hON
//    } else if(GgafDxInput::isReleasedUpMouseButton(0) || GgafDxInput::isReleasedUpMouseButton(1) || GgafDxInput::isReleasedUpMouseButton(2)) {
//        pVPGuide_->inactivate(); //�K�C�hOFF
//    }

    if (isPushedMouseButton0 || isPushedMouseButton1 || isPushedMouseButton2) {
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

    static const coord game_width = PX_C(CONFIG::GAME_BUFFER_WIDTH*2);

    if ( !(isPressedMouseButton0 && isPressedMouseButton1) &&
         (isPressedMouseButton0 || isPressedMouseButton1 || isPressedMouseButton2)
    ) {
        //���_�𒆐S�ɃJ��������]�ړ�
        //�J�����𒆐S�Ɏ��_����]�ړ�
        //�J�������Ǝ��_�����s�ړ�
        //���ʂ̌v�Z

        //���[���h��]�������x�N�g���A(vX_axis, vY_axis, vZ_axis) ���v�Z begin =======>

        //���ʉ�]��(vx, vy)�����߂�
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
        D3DXMatrixInverse( &InvView, nullptr, pCam_->getViewMatrix());
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
        double t2 = 1.0 / sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
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
        //(x, y, z) �� CAM �� VP �� UP

        //���_�𒆐S�ɃJ��������]�ړ�
        if (isPressedMouseButton0 && (mdx != 0 || mdy != 0)) {
            //�����_���J���� �̕����x�N�g��(vx, vy, vz)
            double vx_eye = t_x_CAM_ - t_x_VP_;
            double vy_eye = t_y_CAM_ - t_y_VP_;
            double vz_eye = t_z_CAM_ - t_z_VP_;
            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            GgafDxQuaternion qu2 = qu;
            GgafDxQuaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
            qu.mul(0, vx_eye, vy_eye, vz_eye); //R*P
            qu.mul(Q); //R*P*Q
            slideMvCamTo(qu.i + t_x_VP_, qu.j + t_y_VP_, qu.k + t_z_VP_, DEFAULT_CAMERA_SLIDE_FRAMES);
            //UP���܂킷
            {
                qu2.mul(0, t_x_UP_, t_y_UP_, t_z_UP_);//R*P
                qu2.mul(Q); //R*P*Q
                slideMvUpVecTo(qu2.i, qu2.j, qu2.k, DEFAULT_CAMERA_SLIDE_FRAMES);
            }
        }
        //�J�����𒆐S�Ɏ��_����]�ړ�
        if (isPressedMouseButton1 && (mdx != 0 || mdy != 0)) {
            //�J�����������_ �̕����x�N�g��(vx, vy, vz)
            double vx_cam = t_x_VP_ - t_x_CAM_;
            double vy_cam = t_y_VP_ - t_y_CAM_;
            double vz_cam = t_z_VP_ - t_z_CAM_;
            //��]���������p�x
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            GgafDxQuaternion qu2 = qu;
            GgafDxQuaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
            qu.mul(0, vx_cam, vy_cam, vz_cam);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            qu.mul(Q); //R*P*Q
            slideMvVpTo(qu.i + t_x_CAM_, qu.j + t_y_CAM_, qu.k + t_z_CAM_, DEFAULT_CAMERA_SLIDE_FRAMES);
            //UP���܂킷
            {
                qu2.mul(0, t_x_UP_, t_y_UP_, t_z_UP_); //R*P
                qu2.mul(Q);  //R*P*Q
                slideMvUpVecTo(qu2.i, qu2.j, qu2.k, DEFAULT_CAMERA_SLIDE_FRAMES);
            }
        }
        //�J�������Ǝ��_�����s�ړ�
        if (isPressedMouseButton2 && (mdx != 0 || mdy != 0)) {
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //��]���������p�x
            double cosHalf = cos(ang/2);
            //�J�����������_ �̕����x�N�g��(vx, vy, vz)
            double vx_cam = t_x_VP_ - t_x_CAM_;
            double vy_cam = t_y_VP_ - t_y_CAM_;
            double vz_cam = t_z_VP_ - t_z_CAM_;
            //���K��
            double t3 = 1.0 / sqrt(vx_cam * vx_cam + vy_cam * vy_cam + vz_cam * vz_cam);
            vx_cam = t3 * vx_cam;
            vy_cam = t3 * vy_cam;
            vz_cam = t3 * vz_cam;
            GgafDxQuaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            qu.mul(0, vx_cam, vy_cam, vz_cam); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            qu.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            double r = (d/cd_) * game_width;
            slideMvCamTo(t_x_CAM_ + (qu.i*r),
                         t_y_CAM_ + (qu.j*r),
                         t_z_CAM_ + (qu.k*r) , DEFAULT_CAMERA_SLIDE_FRAMES);
            slideMvVpTo(t_x_VP_ + (qu.i*r),
                        t_y_VP_ + (qu.j*r),
                        t_z_VP_ + (qu.k*r) , DEFAULT_CAMERA_SLIDE_FRAMES);
        }

    } else if (mdz != 0 || (isPressedMouseButton0 && isPressedMouseButton1)) {
        //�E�H�[�N�X���[
        if (mdz_flg_ == false) {
            //�z�C�[�������i���������j�ŏ��̃t���[��
            mdz_total_ = 0;
            //�J���� �� �����_ �̕����x�N�g��
            double vx_cam = pVp_->_x - pCam_->_x;
            double vy_cam = pVp_->_y - pCam_->_y;
            double vz_cam = pVp_->_z - pCam_->_z;
            double t = 1.0 / sqrt(vx_cam * vx_cam + vy_cam * vy_cam + vz_cam * vz_cam);
            mdz_vx_ = t * vx_cam;
            mdz_vy_ = t * vy_cam;
            mdz_vz_ = t * vz_cam;
        }
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((isPressedMouseButton0 && isPressedMouseButton1)) {
            r = (1.0*mdy/cd_) * game_width;
        }
        if (mdx != 0 || mdy != 0 || mdz != 0) {
            slideMvCamTo(t_x_CAM_ + mdz_vx_*r,
                         t_y_CAM_ + mdz_vy_*r,
                         t_z_CAM_ + mdz_vz_*r , DEFAULT_CAMERA_SLIDE_FRAMES);
            slideMvVpTo(t_x_VP_ + mdz_vx_*r,
                        t_y_VP_ + mdz_vy_*r,
                        t_z_VP_ + mdz_vz_*r , DEFAULT_CAMERA_SLIDE_FRAMES);
        }
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }
}

AroundViewCamWorker::~AroundViewCamWorker() {
}
