#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Camera::GgafDx9Camera(const char* prm_name, float prm_rad_fovX) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "GgafDx9Camera";
    _pMover = NEW GgafDx9GeometryMover(this);
    //�S�Ă̊��fovX����l����
    _rad_fovX = prm_rad_fovX;
    //������ێ�
    _rad_half_fovX = _rad_fovX / 2.0;
    //��ʃA�X�y�N�g��(w/h)
    _screen_aspect = (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    //fovX�ƃA�X�y�N�g�䂩��fovY���v�Z���ċ��߂�
    double xzRatio = tan( _rad_fovX/2 );
    double yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0;
    //������ێ�
    _rad_half_fovY = _rad_fovY / 2.0;
    //tan�l���ێ�
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //�����J�����ʒu�͎��_(0,0,Z)�A�����_(0,0,0)
    //Z�́A�L������Z=0��XY���ʂŒ��x�L�������l�s�N�Z�����ƈ�v����悤�ȏ��ɃJ����������
    _cameraZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("�J�����̈ʒu(0,0,"<<_cameraZ<<")");
//    _view_border_slant1_XZ = sin((PI - _rad_fovX) / 2) / cos((PI - _rad_fovX) / 2);
//    _view_border_slant2_XZ = -_view_border_slant1_XZ;
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ); //�ʒu
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //�����������
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //�����

    // VIEW�ϊ��s��쐬
    D3DXMatrixLookAtLH(
       &_vMatrixView,         // pOut [in, out] ���Z���ʂł��� D3DXMATRIX �\���̂ւ̃|�C���^�B
        _pVecCamFromPoint,    // pEye [in] ���_���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B���̒l�́A���s�ړ��Ɏg�p�����B
        _pVecCamLookatPoint,  // pAt  [in] �J�����̒����Ώۂ��`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
        _pVecCamUp            // pUp  [in] �J�����g ���[���h�̏���A��ʂɂ� [0, 1, 0] ���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
    );

    // �ˉe�ϊ��s��쐬�i�R�c�����ʁj
    D3DXMatrixPerspectiveFovLH(
            &_vMatrixProj,
            _rad_fovY, //y��������p���f�B�A��(0�`��)
            _screen_aspect, //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
            1.0, //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
            2000.0 //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
            //(FLOAT)(-1.0*dCam*4)
            //(-1.0*fCam)-30,
            //(-1.0*fCam)+30
    );
    /*
     //������W�n���ˉe
     D3DXMatrixOrthoLH(
     &_vMatrixProj,
     GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH),
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT),
     1.0f,
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)
     );
     */


    _gazeX = _pVecCamLookatPoint->x * LEN_UNIT * PX_UNIT;
    _gazeY = _pVecCamLookatPoint->y * LEN_UNIT * PX_UNIT;
    _gazeZ = _pVecCamLookatPoint->z * LEN_UNIT * PX_UNIT;
    _X = _pVecCamFromPoint->x * LEN_UNIT * PX_UNIT;
    _Y = _pVecCamFromPoint->y * LEN_UNIT * PX_UNIT;
    _Z = _pVecCamFromPoint->z * LEN_UNIT * PX_UNIT;

    _pMover->setMoveAngle(0,0,0);
    _pMover->setMoveVelocity(0);
    _pMover->setRzMoveAngleVelocity(0);
    _pMover->setRyMoveAngleVelocity(0);
    _pMover->_move_angle_rz_target_flg = true;
    _pMover->_move_angle_ry_target_flg = true;

    _pMover->setVxMoveVelocityRenge(-5000, 5000);
    _pMover->setVxMoveVelocity(0);
    _pMover->setVxMoveAcceleration(0);

    _pMover->setVyMoveVelocityRenge(-5000, 5000);
    _pMover->setVyMoveVelocity(0);
    _pMover->setVyMoveAcceleration(0);

    _pMover->setVzMoveVelocityRenge(-5000, 5000);
    _pMover->setVzMoveVelocity(0);
    _pMover->setVzMoveAcceleration(0);


    setBumpable(false);
}

void GgafDx9Camera::initialize() {

}




void GgafDx9Camera::processBehavior() {
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
    //XY
    //�X�� (y2-y1)/(x2-x1)   = tan��
    //�ؕ� (x2y1-x1y2)/(x2-x1)

    //ZY
    //�X�� (y2-y1)/(z2-z1)   = tan��
    //�ؕ� (z2y1-z1y2)/(z2-z1)

    //XZ
    //�X�� (z2-z1)/(x2-x1)   = tan��
    //�ؕ� (x2z1-x1z2)/(x2-x1)
    //�N���b�v�{�[�_�[�v�Z
    float x1 = _pVecCamFromPoint->x;
    float y1 = _pVecCamFromPoint->y;
    float z1 = _pVecCamFromPoint->z;
    float x2 = _pVecCamLookatPoint->x;
    float y2 = _pVecCamLookatPoint->y;
    float z2 = _pVecCamLookatPoint->z;
    _view_slant_XZ = (z2-z1)/(x2-x1);
    _view_slant_ZY = (y2-y1)/(z2-z1);
    _view_rad_XZ = atan(_view_slant_XZ);
    _view_rad_ZY = atan(_view_slant_ZY);
    _view_border_rad1_XZ =  _view_rad_XZ + _rad_half_fovX;
    _view_border_rad2_XZ =  _view_rad_XZ - _rad_half_fovX;
    _view_border_rad1_ZY =  _view_rad_ZY + _rad_half_fovY;
    _view_border_rad2_ZY =  _view_rad_ZY - _rad_half_fovY;

    _view_border_slant1_XZ = tan(_view_border_rad1_XZ);
    _view_border_slant2_XZ = tan(_view_border_rad2_XZ);
    _view_border_slant1_ZY = tan(_view_border_rad1_ZY);
    _view_border_slant2_ZY = tan(_view_border_rad2_ZY);

    _view_border_intercept1_XZ = _Z - (_view_border_slant1_XZ*_X);
    _view_border_intercept2_XZ = _Z - (_view_border_slant2_XZ*_X);
    _view_border_intercept1_ZY = _Y - (_view_border_slant1_ZY*_Z);
    _view_border_intercept2_ZY = _Y - (_view_border_slant2_ZY*_Z);


    _pMover->behave();
//    D3DXMatrixOrthoLH(
//        &_vMatrixOrthoProj,
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w �r���[ �{�����[���̕�
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h �r���[ �{�����[���̍���
//        1.0,    //zn �r���[ �{�����[���̍ŏ� z �l (z �߂Ƃ�����)
//        2000.0  //zf �r���[ �{�����[���̍ő� z �l (z ���Ƃ�����)
//    );

}

void GgafDx9Camera::processDrawPrior() {
    _pVecCamFromPoint->x = (1.0 * _X) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->y = (1.0 * _Y) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->z = (1.0 * _Z) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->x = (1.0 * _gazeX) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0 * _gazeY) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0 * _gazeZ) / LEN_UNIT / PX_UNIT;
}



bool GgafDx9Camera::isInTheViewports(int prm_X, int prm_Y, int prm_Z) {
    //y < (a*n)x+b
    //y > (a*(1/n))x+b
    //y = ax + b �́A�J�����̎��_�ƒ����_�����Ԓ����B
    //n�͌X���͈�

    float a1 = _view_border_slant1_XZ;
    int   b1 = _view_border_intercept1_XZ;
    float a2 = _view_border_slant2_XZ;
    int   b2 = _view_border_intercept2_XZ;

    float a3 = _view_border_slant1_ZY;
    int   b3 = _view_border_intercept1_ZY;
    float a4 = _view_border_slant2_ZY;
    int   b4 = _view_border_intercept2_ZY;

    if ( _Z < prm_Z && prm_Z < _Z + 3000000) {

        if (a1 >= 0 && a2 >= 0) {
            if (prm_Z < a1*prm_X + b1) {
                if (prm_Z > a2*prm_X + b2) {
                    //return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (a1 >= 0 && a2 < 0) {
            return false;
    //        if (prm_Z < a1*prm_X + b1) {
    //            if (prm_Z > a2*prm_X + b2) {
    //                return true;
    //            }
    //        }
        } else if (a1 < 0 && a2 < 0) {
            if (prm_Z > a1*prm_X + b1) {
                if (prm_Z < a2*prm_X + b2) {
                    //return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (a1 < 0 && a2 > 0) {
            if (prm_Z > a1*prm_X + b1) {
                if (prm_Z > a2*prm_X + b2) {
                    //return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }

        if (a3 >= 0 && a4 >= 0) {
            if (prm_Y < a3*prm_Z + b3) {
                if (prm_Y > a4*prm_Z + b4) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (a3 >= 0 && a4 < 0) {
            if (prm_Y < a3*prm_Z + b3) {
                if (prm_Y > a4*prm_Z + b4) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (a3 < 0 && a4 < 0) {
            if (prm_Y < a3*prm_Z + b3) {
                if (prm_Y > a4*prm_Z + b4) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (a3 < 0 && a4 > 0) {
            return false;
    //        if (prm_Y > a3*prm_Z + b1) {
    //            if (prm_Y > a4*prm_Z + b2) {
    //                //return true;
    //            } else {
    //                return false;
    //            }
    //        } else {
    //            return false;
    //        }
        } else {
            return false;
        }
    } else {
        return false;
    }

}


GgafDx9Camera::~GgafDx9Camera() {
    //���낢����
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
