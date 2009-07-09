#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Camera::GgafDx9Camera(const char* prm_name) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "GgafDx9Camera";
    _pMover = NEW GgafDx9GeometryMover(this);
    //FOVX����ɍl����
    //����p80�x
    _rad_fovX = PI * 4.0 / 9.0 ;

    //_iPxDep = abs(_cameraZ_org * PX_UNIT * 2);
    //�A�X�y�N�g��(w/h)
    _screen_aspect = (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    //FovX�ƃA�X�y�N�g�䂩��FovY�����߂�
    double xzRatio = tan( _rad_fovX/2 );
    double yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2;
    _tan_half_fovY = tan(_rad_fovY/2);
    _tan_half_fovX = tan(_rad_fovX/2);
    //�����J�����ʒu��Z=0��XY���ʂŒ��x�s�N�Z�����ƈ�v����悤�ȏ�
    _cameraZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("�J�����̈ʒu(0,0,"<<_cameraZ<<")");
    _view_border_slant1_XZ = sin((PI - _rad_fovX) / 2) / cos((PI - _rad_fovX) / 2);
    _view_border_slant2_XZ = -_view_border_slant1_XZ;
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

    setBumpable(false);
}

void GgafDx9Camera::initialize() {

}




void GgafDx9Camera::processBehavior() {
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
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

GgafDx9Camera::~GgafDx9Camera() {
    //���낢����
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
