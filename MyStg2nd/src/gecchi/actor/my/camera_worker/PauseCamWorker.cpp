#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
    _cd = 0;
    _mdz_flg = false;
    _pVPGuide = NULL;
}
void PauseCamWorker::initialize() {
    _pVPGuide = NEW ViewPointGuide("VPGuide");
    _pVPGuide->inactivateImmediately();
    P_WORLD->getLordActor()->addSubGroup(_pVPGuide);
}


void PauseCamWorker::processBehavior() {
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9GeometricActor* pVP = P_CAM->_pViewPoint;
    GgafDx9Input::updateMouseState();

    long mx,my,mz,mdx,mdy,mdz;
    GgafDx9Input::getMousePointer(&mx, &my, &mz);
    GgafDx9Input::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Y�̓C���o�[�Y

    if (GgafDx9Input::isBeingPressedMouseButton(0) || GgafDx9Input::isBeingPressedMouseButton(1) || GgafDx9Input::isBeingPressedMouseButton(2) || mdz != 0) {
        if (!_pVPGuide->isActiveActor()) {
            _pVPGuide->activate();
        }

    } else {
        if (_pVPGuide->isActiveActor()) {
            _pVPGuide->inactivate();
        }

    }


    if ((GgafDx9Input::isBeingPressedMouseButton(0) || GgafDx9Input::isBeingPressedMouseButton(1) || GgafDx9Input::isBeingPressedMouseButton(2))) {

        if (GgafDx9Input::isPushedDownMouseButton(0) || GgafDx9Input::isPushedDownMouseButton(1) || GgafDx9Input::isPushedDownMouseButton(2)) {
            RECT cRect; // �N���C�A���g�̈�̋�`
            int cw, ch; // �N���C�A���g�̈�̕��A����
            // �N���C�A���g�̈�̕��E�������v�Z
            GetClientRect(GgafDx9God::_hWnd, &cRect);
            cw = cRect.right - cRect.left;
            ch = cRect.bottom - cRect.top;
            if (cw > ch) {
                _cd = ch;
            } else {
                _cd = cw;
            }

            _move_target_X_CAM = pCam->_X;
            _move_target_Y_CAM = pCam->_Y;
            _move_target_Z_CAM = pCam->_Z;
            //���m��VP�ɍĐݒ�
            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
            _move_target_X_VP = pVP->_X;
            _move_target_Y_VP = pVP->_Y;
            _move_target_Z_VP = pVP->_Z;
            _pVPGuide->activate();
        }

    //�v�Z

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
        D3DXMatrixInverse( &InvView, NULL, &pCam->_vMatrixView );
        //(vx,vy,vz) * InvView
        // _11, _12, _13, _14
        // _21, _22, _23, _24
        // _31, _32, _33, _34
        // vx*_11 + vy*_21 + vz*_31 + _41, vx*_12 + vy*_22 + vz*_32 + _42, vx*_13 + vy*_23 + vz*_33 + _43, vx*_14 + vy*_24 + vz*_34 + _44
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
        if (GgafDx9Input::isBeingPressedMouseButton(0) && (mdx != 0 || mdy != 0)) {
            _stop_renge = 60000;
            //���_���J���� �̕����x�N�g��(x,y,z)
            double x = _move_target_X_CAM - _move_target_X_VP;
            double y = _move_target_Y_CAM - _move_target_Y_VP;
            double z = _move_target_Z_CAM - _move_target_Z_VP;

            angle rz1 = GgafDx9Util::getAngle2D(x, y);

            //��]���������p�x
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);

            //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
            if (abs(mdy) > abs(mdx)) {
                _move_target_XY_CAM_UP += GgafDx9Util::getAngDiff(rz1, rz2);
                _move_target_XY_CAM_UP = GgafDx9Util::simplifyAng(_move_target_XY_CAM_UP);
            }
            _move_target_X_CAM = Q._x + _move_target_X_VP;
            _move_target_Y_CAM = Q._y + _move_target_Y_VP;
            _move_target_Z_CAM = Q._z + _move_target_Z_VP;
        }
        //�J�����𒆐S�Ɏ��_����]�ړ�
        if (GgafDx9Input::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            _stop_renge = 60000;
            //�J���������_ �̕����x�N�g��(x,y,z)
            double x = _move_target_X_VP - _move_target_X_CAM;
            double y = _move_target_Y_VP - _move_target_Y_CAM;
            double z = _move_target_Z_VP - _move_target_Z_CAM;
            angle rz1 = GgafDx9Util::getAngle2D(x, y);
            //��]���������p�x
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);
            if (abs(mdy) > abs(mdx)) {
                _move_target_XY_CAM_UP += GgafDx9Util::getAngDiff(rz1, rz2);
                _move_target_XY_CAM_UP = GgafDx9Util::simplifyAng(_move_target_XY_CAM_UP);
            }
            //Q._x, Q._y, Q._z ����]��̍��W�ƂȂ�
            _move_target_X_VP = Q._x + _move_target_X_CAM;
            _move_target_Y_VP = Q._y + _move_target_Y_CAM;
            _move_target_Z_VP = Q._z + _move_target_Z_CAM;
        }
        //�J�������Ǝ��_�����s�ړ�
        if (GgafDx9Input::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            _stop_renge = 60000;
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //��]���������p�x
            double cosHalf = cos(ang/2);

            double x = _move_target_X_VP - _move_target_X_CAM;
            double y = _move_target_Y_VP - _move_target_Y_CAM;
            double z = _move_target_Z_VP - _move_target_Z_CAM;

            //���K��
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;


            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P ��]�������݂̐i�s�����x�N�g���ƂȂ�
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q

            double r = ((d/_cd)*GgafDx9Properties::GAME_BUFFER_WIDTH*2)*LEN_UNIT;

            _move_target_X_CAM += (Q._x*r);
            _move_target_Y_CAM += (Q._y*r);
            _move_target_Z_CAM += (Q._z*r);

            _move_target_X_VP += (Q._x*r);
            _move_target_Y_VP += (Q._y*r);
            _move_target_Z_VP += (Q._z*r);
        }
    } else {
    }


    //�}�E�X�z�C�[����]��
    if (mdz != 0) {
        _stop_renge = 60000;
        if (_mdz_flg == false) {
            _mdz_total = 0;
            _move_target_X_CAM = pCam->_X;
            _move_target_Y_CAM = pCam->_Y;
            _move_target_Z_CAM = pCam->_Z;
            //���m��VP�ɍĐݒ�
            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
            _move_target_X_VP = pVP->_X;
            _move_target_Y_VP = pVP->_Y;
            _move_target_Z_VP = pVP->_Z;

            _cam_X = pCam->_X;
            _cam_Y = pCam->_Y;
            _cam_Z = pCam->_Z;
            _vp_X = pVP->_X;
            _vp_Y = pVP->_Y;
            _vp_Z = pVP->_Z;
            //�J���� �� ���_ �̕����x�N�g��
            double vx = pVP->_X - pCam->_X;
            double vy = pVP->_Y - pCam->_Y;
            double vz = pVP->_Z - pCam->_Z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            _mdz_vx = t * vx;
            _mdz_vy = t * vy;
            _mdz_vz = t * vz;
        }
        _mdz_total += mdz; //�A���z�C�[����]���A���Z
        double r = (_mdz_total*PX_UNIT*LEN_UNIT/10.0);
        _move_target_X_CAM = _cam_X + _mdz_vx*r;
        _move_target_Y_CAM = _cam_Y + _mdz_vy*r;
        _move_target_Z_CAM = _cam_Z + _mdz_vz*r;
        _move_target_X_VP  = _vp_X  + _mdz_vx*r;
        _move_target_Y_VP  = _vp_Y  + _mdz_vy*r;
        _move_target_Z_VP  = _vp_Z  + _mdz_vz*r;
        _mdz_flg = true;
    } else {
        _mdz_flg = false;
    }


//    //�}�E�X�z�C�[����]��
//    if (mdz != 0) {
//        _stop_renge = 60000;
//        if (_mdz_flg == false) {
//            _mdz_total = 0;
//            _move_target_X_CAM = pCam->_X;
//            _move_target_Y_CAM = pCam->_Y;
//            _move_target_Z_CAM = pCam->_Z;
//            //���m��VP�ɍĐݒ�
//            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
//            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
//            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
//            _move_target_X_VP = pVP->_X;
//            _move_target_Y_VP = pVP->_Y;
//            _move_target_Z_VP = pVP->_Z;
////
////            _cam_X = pCam->_X;
////            _cam_Y = pCam->_Y;
////            _cam_Z = pCam->_Z;
////            _vp_X = pVP->_X;
////            _vp_Y = pVP->_Y;
////            _vp_Z = pVP->_Z;
//            //�J���� �� ���_ �̕����x�N�g��
//            if (mdz > 0) {
//                pCam->_pKuroko->setMvAng(pVP->_X - pCam->_X,
//                                         pVP->_Y - pCam->_Y,
//                                         pVP->_Z - pCam->_Z);
//                pVP->_pKuroko->setMvAng(pVP->_X - pCam->_X,
//                                        pVP->_Y - pCam->_Y,
//                                        pVP->_Z - pCam->_Z);
//            } else if (mdz < 0) {
//                pCam->_pKuroko->setMvAng(-(pVP->_X - pCam->_X),
//                                         -(pVP->_Y - pCam->_Y),
//                                         -(pVP->_Z - pCam->_Z));
//                pVP->_pKuroko->setMvAng(-(pVP->_X - pCam->_X),
//                                        -(pVP->_Y - pCam->_Y),
//                                        -(pVP->_Z - pCam->_Z));
//            }
//            pCam->_pKuroko->forceMvVeloRange(0,_cam_velo_renge);
//            pVP->_pKuroko->forceMvVeloRange(0,_cam_velo_renge);
//            pCam->_pKuroko->setMvAcce(-100);
//            pVP->_pKuroko->setMvAcce(-100);
//
////
////            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
////            _mdz_vx = t * vx;
////            _mdz_vy = t * vy;
////            _mdz_vz = t * vz;
//        }
//        _mdz_total = mdz; //�A���z�C�[����]���A���Z
//        int r = (_mdz_total*LEN_UNIT*10);
//        pCam->_pKuroko->addMvVelo(r);
//        pVP->_pKuroko->addMvVelo(r);
//
////
////        _move_target_X_CAM = _cam_X + _mdz_vx*r;
////        _move_target_Y_CAM = _cam_Y + _mdz_vy*r;
////        _move_target_Z_CAM = _cam_Z + _mdz_vz*r;
////        _move_target_X_VP  = _vp_X  + _mdz_vx*r;
////        _move_target_Y_VP  = _vp_Y  + _mdz_vy*r;
////        _move_target_Z_VP  = _vp_Z  + _mdz_vz*r;
//        _mdz_flg = true;
//    } else {
////        pCam->_pKuroko->setMvVelo(0);
////        pVP->_pKuroko->setMvVelo(0);
//       // pCam->_pKuroko->setMvAcce(0);
//       // pVP->_pKuroko->setMvAcce(0);
//        _mdz_flg = false;
//    }


    //�R�}����
    if (VB_UI->isPushedDown(VB_BUTTON7)) {
        P_GAME_SCENE->_is_frame_advance = true;
    }


    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        //V�{�����Œ����_����
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            pVP->_Y += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            pVP->_Y -= 1000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            pVP->_X += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            pVP->_X -= 1000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            pVP->_Z += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            pVP->_Z -= 1000;
        } else {
        }
    } else if (GgafDx9Input::isBeingPressedKey(DIK_C)) {
        //C�{�����ŃJ��������
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            P_CAM->_Y += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            P_CAM->_Y -= 1000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            P_CAM->_X += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            P_CAM->_X -= 1000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            P_CAM->_Z += 1000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            P_CAM->_Z -= 1000;
        } else {
        }
    }
    CameraWorker::processBehavior();
}
PauseCamWorker::~PauseCamWorker() {
}
