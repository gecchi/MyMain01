#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

int GgafDx9Camera::_X_ScreenLeft   = 0;
int GgafDx9Camera::_X_ScreenRight  = 0;
int GgafDx9Camera::_Y_ScreenTop    = 0;
int GgafDx9Camera::_Y_ScreenBottom = 0;



GgafDx9Camera::GgafDx9Camera(const char* prm_name, float prm_rad_fovX) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "GgafDx9Camera";

    //�S�Ă̊��fovX����l����
    _rad_fovX = prm_rad_fovX;
    //������ێ�
    _rad_half_fovX = _rad_fovX / 2.0f;
    //��ʃA�X�y�N�g��(w/h)
    _screen_aspect = (FLOAT)(1.0f * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    //fovX�ƃA�X�y�N�g�䂩��fovY���v�Z���ċ��߂�
    float xzRatio = tan( _rad_fovX/2 );
    float yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0f;
    //������ێ�
    _rad_half_fovY = _rad_fovY / 2.0f;
    //tan�l���ێ�
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //�����J�����ʒu�͎��_(0,0,Z)�A�����_(0,0,0)
    //Z�́A�L������Z=0��XY���ʂŒ��x�L�������l�s�N�Z�����ƈ�v����悤�ȏ��ɃJ����������
    _cameraZ = -1.0f * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0f) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("�J�����̈ʒu(0,0,"<<_cameraZ<<")");
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
            _rad_fovY,        //y��������p���f�B�A��(0�`��)
            _screen_aspect,   //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
            0.01,             //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
            -_cameraZ_org*20.0 //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn (20.0�͓K��)
            //(FLOAT)(-1.0f*dCam*4)
            //(-1.0f*fCam)-30,
            //(-1.0f*fCam)+30
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

    _pViewPoint = NEW GgafDx9CameraViewPoint();
    _pViewPoint->_X = _pVecCamLookatPoint->x * LEN_UNIT * PX_UNIT;
    _pViewPoint->_Y = _pVecCamLookatPoint->y * LEN_UNIT * PX_UNIT;
    _pViewPoint->_Z = _pVecCamLookatPoint->z * LEN_UNIT * PX_UNIT;

    _X_ScreenLeft   = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    _X_ScreenRight  = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    _Y_ScreenTop    = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
    _Y_ScreenBottom = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
}

void GgafDx9Camera::initialize() {
    addSubLast(_pViewPoint);
}

void GgafDx9Camera::processBehavior() {
    //if (_lifeframe % 2 == 0) { //10�t���[���ɂP�񂾂��v�Z
    HRESULT hr;
    static D3DVIEWPORT9 viewport;       //�N���C�A���g�̈�S�̂̕ێ�
    //�X�N���[���S�̂̃N���C�A���g�̈��ێ��B
    hr = GgafDx9God::_pID3DDevice9->GetViewport(&viewport);

    // viewport.MinZ / MaxZ �́A�ʏ킻�ꂼ�� 0 / 1
    float x1 = (float)viewport.X;
    float y1 = (float)viewport.Y;
    float x2 = (float)viewport.X + (float)viewport.Width;
    float y2 = (float)viewport.Y + (float)viewport.Height;

    // ������̂W�_���i�[�����C���X�^���X
    _vecNear[0] = D3DXVECTOR3( x1, y1, viewport.MinZ ); // ���� (�ϊ���)
    _vecNear[1] = D3DXVECTOR3( x2, y1, viewport.MinZ ); // �E�� (�ϊ���)
    _vecNear[2] = D3DXVECTOR3( x1, y2, viewport.MinZ ); // ���� (�ϊ���)
    _vecNear[3] = D3DXVECTOR3( x2, y2, viewport.MinZ ); // �E�� (�ϊ���)

    _vecFar[0]  = D3DXVECTOR3( x1, y1, viewport.MaxZ ); // ���� (�ϊ���)
    _vecFar[1]  = D3DXVECTOR3( x2, y1, viewport.MaxZ ); // �E�� (�ϊ���)
    _vecFar[2]  = D3DXVECTOR3( x1, y2, viewport.MaxZ ); // ���� (�ϊ���)
    _vecFar[3]  = D3DXVECTOR3( x2, y2, viewport.MaxZ ); // �E�� (�ϊ���)

    // ������̂W�_�̌v�Z
    static D3DXMATRIX mat_world;
    D3DXMatrixIdentity( &mat_world );
    D3DVIEWPORT9* pViewport = (D3DVIEWPORT9*)(&viewport);
    // ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
    for( int i = 0; i < 4; ++i ) {
        D3DXVec3Unproject(
            &_vecNear[i],   //D3DXVECTOR3 *pOut,              [in, out] ���Z���ʂł��� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
            &_vecNear[i],   //CONST D3DXVECTOR3 *pV,          [in] �����̊�ɂȂ� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
            pViewport,      //CONST D3DVIEWPORT9 *pViewport,  [in] �r���[�|�[�g��\�� D3DVIEWPORT9 �\���̂ւ̃|�C���^�B
            &_vMatrixProj,  //CONST D3DXMATRIX *pProjection,  [in] �ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
            &_vMatrixView,  //CONST D3DXMATRIX *pView,        [in] �r���[�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
            &mat_world      //CONST D3DXMATRIX *pWorld        [in] ���[���h�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
        );
        D3DXVec3Unproject(
            &_vecFar[i],
            &_vecFar[i],
            pViewport,
            &_vMatrixProj,
            &_vMatrixView,
            &mat_world
        );
    }
    //-------------------------------------------------
    //  ���ʕ������Fax+by+cz+d
    //  ���ʂ̖@���x�N�g���Fn = (a, b, c)
    //  ���ʏ��1�_���Ap = (x0, y0, z0) �Ƃ���ƁA
    //  ���ʂ̖@���x�N�g���ƕ��ʏ��1�_�̓��ρFd = n*p
    //
    //  �\�����������Ƃ��́A�_ p = (x0, y0, z0)���A
    //  p = (x0, y0, z0, 1) �Ƃ݂Ȃ��A
    //  ���ʂƂ̓��ρFa*x0 + b*y0 + c*z0 + d*1 = ans
    //  ans > 0 �Ȃ�\�Aans < 0 �Ȃ痠�Aans == 0 �Ȃ�ʏ�A�ƂȂ�B
    //  DXPlaneDotCoord() �́A���̏������s���Ă���
    //
    //  �܂��Ap = (x0, y0, z0, 0) �Ƃ݂Ȃ��ē��ς̌v�Z���s���ƁA
    //  �p�x�̊֌W�𒲂ׂ邱�Ƃ��ł���B
    //  �� D3DXPlaneDotNormal()
    //-------------------------------------------------


     // �� ( F����AN����AN�E�� )
    D3DXPlaneNormalize(
        &_plnTop,
        D3DXPlaneFromPoints(&_plnTop, &(_vecFar[2]), &(_vecNear[2]), &(_vecNear[3]))
    );
    // �� ( F�����AN�E���AN���� )
    D3DXPlaneNormalize(
        &_plnBottom,
        D3DXPlaneFromPoints(&_plnBottom, &(_vecFar[0]), &(_vecNear[1]), &(_vecNear[0]))
    );
    // �� ( F�����AN�����AN���� )
    D3DXPlaneNormalize(
        &_plnLeft,
        D3DXPlaneFromPoints(&_plnLeft, &(_vecFar[0]), &(_vecNear[0]), &(_vecNear[2]))
    );
    // �E ( F�E���AN�E��AN�E�� )
    D3DXPlaneNormalize(
        &_plnRight,
        D3DXPlaneFromPoints(&_plnRight, &(_vecFar[1]), &(_vecNear[3]), &(_vecNear[1]))
    );
    // ��O ( N����AN�����AN�E��)
    D3DXPlaneNormalize(
        &_plnFront,
        D3DXPlaneFromPoints(&_plnFront, &(_vecNear[2]), &(_vecNear[0]), &(_vecNear[3]))
    );
    // �� ( F�E��AF�����AF����)
    D3DXPlaneNormalize(
        &_plnBack,
        D3DXPlaneFromPoints(&_plnBack, &(_vecFar[3]), &(_vecFar[0]), &(_vecFar[2]))
    );

    //}

}



void GgafDx9Camera::processJudgement() {
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    _pVecCamLookatPoint->x = (1.0f * _pViewPoint->_X ) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0f * _pViewPoint->_Y ) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0f * _pViewPoint->_Z ) / LEN_UNIT / PX_UNIT;
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

void GgafDx9Camera::setViewPoint(int prm_tX, int prm_tY, int prm_tZ) {
    _pViewPoint->_X = prm_tX;
    _pViewPoint->_Y = prm_tY;
    _pViewPoint->_Z = prm_tZ;
}

void GgafDx9Camera::setViewPoint(GgafDx9GeometricActor* prm_pActor) {
    _pViewPoint->setGeometry(prm_pActor);
}
GgafDx9Camera::~GgafDx9Camera() {
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);
}
