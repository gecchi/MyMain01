#include "jp/ggaf/lib/actor/camera/worker/AroundViewCamWorker.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAssistant.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"



using namespace GgafLib;

AroundViewCamWorker::AroundViewCamWorker(const char* prm_name, DefaultCamera* prm_pCamera) : CameraWorker(prm_name, prm_pCamera) {
    _class_name = "AroundViewCamWorker";
    _cd = 0;
    _mdz_flg = false;
    _mdz_vx = _mdz_vy = _mdz_vz = _mdz_t = 0.0;
    _mdz_total = 0;
    _isPressed0 = _isPressed1 =_isPressed2 = false;
    _onScreen = false;
    _hWnd_last = nullptr;
}

void AroundViewCamWorker::initialize() {
    CameraWorker::initialize();
}

void AroundViewCamWorker::onActive() {
    CameraWorker::onActive();
    //CameraWorker::onActive(); ���㏑�����āA
    //���̏���W���^�[�Q�b�g���W�ɏ㏑��
    slideMvCamTo(_pCam->_x, _pCam->_y, _pCam->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvVpTo(_pVp->_x, _pVp->_y, _pVp->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
    slideMvUpVecTo(_pUp->_x, _pUp->_y, _pUp->_z, DEFAULT_CAMERA_SLIDE_FRAMES);
}

void AroundViewCamWorker::processBehavior() {
    //TODO:���x���グ��A�C�f�B�A
    //�}�E�X�|�C���g�̗��������Amdx,mdy,mdz�́A�R�t���[���قǉߋ��Ƃ̍��ɂ���Ɖ�]�������肷�邾�낤
    long mdx,mdy,mdz;
//    GgafDx::Input::getMousePointer(&mx, &my, &mz);
    GgafDx::Input::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Y�̓C���o�[�Y
    bool isPressedMouseButton0 = GgafDx::Input::isPressedMouseButton(0);
    bool isPressedMouseButton1 = GgafDx::Input::isPressedMouseButton(1);
    bool isPressedMouseButton2 = GgafDx::Input::isPressedMouseButton(2);
    bool isPushedMouseButton0 = GgafDx::Input::isPushedDownMouseButton(0);
    bool isPushedMouseButton1 = GgafDx::Input::isPushedDownMouseButton(1);
    bool isPushedMouseButton2 = GgafDx::Input::isPushedDownMouseButton(2);


//    if (isPushedMouseButton0 || isPushedMouseButton1 || isPushedMouseButton2) {
//        pVPGuide_->activate(); //�K�C�hON
//    } else if(GgafDx::Input::isReleasedUpMouseButton(0) || GgafDx::Input::isReleasedUpMouseButton(1) || GgafDx::Input::isReleasedUpMouseButton(2)) {
//        pVPGuide_->inactivate(); //�K�C�hOFF
//    }
    POINT mouse_point;
    //�}�E�X�̍��W���擾
    GetCursorPos(&mouse_point);
    // �J�[�\���ʒu����E�B���h�E�n���h���擾
    HWND hWnd = WindowFromPoint(mouse_point);
//    if (pCARETAKER->_sync_frame_time) {
//        _onScreen = false;
//        _hWnd_last = nullptr;
//        _isPressed0 = false;
//        _isPressed1 = false;
//        _isPressed2 = false;
//    } else {
        if (pCARETAKER->_pHWndPrimary == hWnd) {
            _onScreen = true;
            _hWnd_last = hWnd;
        } else if (pCARETAKER->_pHWndSecondary && pCARETAKER->_pHWndSecondary == hWnd) {
            _onScreen = true;
            _hWnd_last = hWnd;
        } else {
            _onScreen = false;
            _hWnd_last = nullptr;
        }
//    }
    if (_onScreen && (isPushedMouseButton0 || isPushedMouseButton1 || isPushedMouseButton2)) {
        mdx = mdy = mdz = 0;
        RECT cRect; // �N���C�A���g�̈�̋�`
        int cw, ch; // �N���C�A���g�̈�̕��A����
        // �N���C�A���g�̈�̕��E�������v�Z
        GetClientRect(_hWnd_last, &cRect);
        cw = cRect.right - cRect.left;
        ch = cRect.bottom - cRect.top;
        if (cw > ch) {
            _cd = ch;
        } else {
            _cd = cw;
        }
        if (isPushedMouseButton0) {
            _isPressed0 = true;
        }
        if (isPushedMouseButton1) {
            _isPressed1 = true;
        }
        if (isPushedMouseButton2) {
            _isPressed2 = true;
        }
    }
    if (!isPressedMouseButton0) {
        _isPressed0 = false;
    }
    if (!isPressedMouseButton1) {
        _isPressed1 = false;
    }
    if (!isPressedMouseButton2) {
        _isPressed2 = false;
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
        D3DXMatrixInverse( &InvView, nullptr, _pCam->getViewMatrix());
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
        if ((_isPressed0) && (mdx != 0 || mdy != 0)) {
            //�����_���J���� �̕����x�N�g��(vx, vy, vz)
            double vx_eye = (double)(_t_x_CAM - _t_x_VP);
            double vy_eye = (double)(_t_y_CAM - _t_y_VP);
            double vz_eye = (double)(_t_z_CAM - _t_z_VP);
            //��]���������p�x
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            Quaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Quaternion qu2 = qu;
            Quaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
            qu.mul(0, vx_eye, vy_eye, vz_eye); //R*P
            qu.mul(Q); //R*P*Q
            slideMvCamTo(qu.i + _t_x_VP, qu.j + _t_y_VP, qu.k + _t_z_VP, DEFAULT_CAMERA_SLIDE_FRAMES);
            //UP���܂킷
            {
                qu2.mul(0, _t_x_UP, _t_y_UP, _t_z_UP);//R*P
                qu2.mul(Q); //R*P*Q
                slideMvUpVecTo(qu2.i, qu2.j, qu2.k, DEFAULT_CAMERA_SLIDE_FRAMES);
            }
        }
        //�J�����𒆐S�Ɏ��_����]�ړ�
        if (_isPressed1 && (mdx != 0 || mdy != 0)) {
            //�J�����������_ �̕����x�N�g��(vx, vy, vz)
            double vx_cam = (double)(_t_x_VP - _t_x_CAM);
            double vy_cam = (double)(_t_y_VP - _t_y_CAM);
            double vz_cam = (double)(_t_z_VP - _t_z_CAM);
            //��]���������p�x
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            Quaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Quaternion qu2 = qu;
            Quaternion Q(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf);
            qu.mul(0, vx_cam, vy_cam, vz_cam);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            qu.mul(Q); //R*P*Q
            slideMvVpTo(qu.i + _t_x_CAM, qu.j + _t_y_CAM, qu.k + _t_z_CAM, DEFAULT_CAMERA_SLIDE_FRAMES);
            //UP���܂킷
            {
                qu2.mul(0, _t_x_UP, _t_y_UP, _t_z_UP); //R*P
                qu2.mul(Q);  //R*P*Q
                slideMvUpVecTo(qu2.i, qu2.j, qu2.k, DEFAULT_CAMERA_SLIDE_FRAMES);
            }
        }
        //�J�������Ǝ��_�����s�ړ�
        if (_isPressed2 && (mdx != 0 || mdy != 0)) {
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //��]���������p�x
            double cosHalf = cos(ang/2);
            //�J�����������_ �̕����x�N�g��(vx, vy, vz)
            double vx_cam = _t_x_VP - _t_x_CAM;
            double vy_cam = _t_y_VP - _t_y_CAM;
            double vz_cam = _t_z_VP - _t_z_CAM;
            //���K��
            double t3 = 1.0 / sqrt(vx_cam * vx_cam + vy_cam * vy_cam + vz_cam * vz_cam);
            vx_cam = t3 * vx_cam;
            vy_cam = t3 * vy_cam;
            vz_cam = t3 * vz_cam;
            Quaternion qu(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            qu.mul(0, vx_cam, vy_cam, vz_cam); //R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            qu.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            double r = (d/_cd) * game_width;
            slideMvCamTo(_t_x_CAM + (qu.i*r),
                         _t_y_CAM + (qu.j*r),
                         _t_z_CAM + (qu.k*r) , DEFAULT_CAMERA_SLIDE_FRAMES);
            slideMvVpTo(_t_x_VP + (qu.i*r),
                        _t_y_VP + (qu.j*r),
                        _t_z_VP + (qu.k*r) , DEFAULT_CAMERA_SLIDE_FRAMES);
        }

    } else if ((mdz != 0 && _onScreen) || (isPressedMouseButton0 && isPressedMouseButton1)) {
        //�E�H�[�N�X���[
        if (_mdz_flg == false) {
            //�z�C�[�������i���������j�ŏ��̃t���[��
            _mdz_total = 0;
            //�J���� �� �����_ �̕����x�N�g��
            double vx_cam = _pVp->_x - _pCam->_x;
            double vy_cam = _pVp->_y - _pCam->_y;
            double vz_cam = _pVp->_z - _pCam->_z;
            double t = 1.0 / sqrt(vx_cam * vx_cam + vy_cam * vy_cam + vz_cam * vz_cam);
            _mdz_vx = t * vx_cam;
            _mdz_vy = t * vy_cam;
            _mdz_vz = t * vz_cam;
        }
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((isPressedMouseButton0 && isPressedMouseButton1)) {
            r = (1.0*mdy/_cd) * game_width;
        }
        if (mdx != 0 || mdy != 0 || mdz != 0) {
            slideMvCamTo(_t_x_CAM + _mdz_vx*r,
                         _t_y_CAM + _mdz_vy*r,
                         _t_z_CAM + _mdz_vz*r , DEFAULT_CAMERA_SLIDE_FRAMES);
            slideMvVpTo(_t_x_VP + _mdz_vx*r,
                        _t_y_VP + _mdz_vy*r,
                        _t_z_VP + _mdz_vz*r , DEFAULT_CAMERA_SLIDE_FRAMES);
        }
        _mdz_flg = true;
    } else {
        _mdz_flg = false;
    }
}

AroundViewCamWorker::~AroundViewCamWorker() {
}
