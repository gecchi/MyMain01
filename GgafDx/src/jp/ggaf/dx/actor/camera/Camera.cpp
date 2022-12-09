#include "jp/ggaf/dx/actor/camera/Camera.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dx/actor/camera/CameraUpVector.h"
#include "jp/ggaf/dx/Caretaker.h"


using namespace GgafDx;

Camera::Camera(const char* prm_name, double prm_rad_fovX, double prm_dep) :
        GeometricActor(prm_name, nullptr),
_rad_fovX(prm_rad_fovX),      //�S�Ă̊��fovX����l����
_dep(prm_dep),
_rad_half_fovX(_rad_fovX / 2.0),
_screen_aspect(1.0 * (CONFIG::GAME_BUFFER_WIDTH) / (CONFIG::GAME_BUFFER_HEIGHT)),
_rad_fovY(atan( ( (tan(_rad_fovX/2.0)) / _screen_aspect) )*2.0),
_rad_half_fovY(_rad_fovY / 2.0),
_tan_half_fovX(tan(_rad_fovX/2.0)),
_tan_half_fovY(tan(_rad_fovY/2.0)),
_cameraZ_org(-1.0 * ((1.0 * (CONFIG::GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0) / _tan_half_fovY),
_zn(0.1f),
_zf(-_cameraZ_org*(_dep+1.0)-_zn),
_x_buffer_left(PX_C(CONFIG::GAME_BUFFER_WIDTH) / -2),
_x_buffer_right(PX_C(CONFIG::GAME_BUFFER_WIDTH) / 2),
_y_buffer_top(PX_C(CONFIG::GAME_BUFFER_HEIGHT) / 2),
_y_buffer_bottom(PX_C(CONFIG::GAME_BUFFER_HEIGHT) / -2)
{
    _class_name = "Camera";
    //fovX�ƃA�X�y�N�g�䂩��fovY���v�Z���ċ��߂�
    _TRACE_(FUNC_NAME<<" ��ʃA�X�y�N�g�F"<<_screen_aspect);
    _TRACE_(FUNC_NAME<<" FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);


    //�����J�����ʒu�͎��_(0,0,Z)�A�����_(0,0,0)
    //Z�́A�L������Z=0��XY���ʂŒ��x�L�������l�s�N�Z�����ƈ�v����悤�ȏ��ɃJ����������
    _TRACE_(FUNC_NAME<<" �J�����̈ʒu(0,0,"<<_cameraZ_org<<") dxcoord");
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ_org); //�ʒu
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //�����������
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //�����

    // VIEW�ϊ��s��쐬
    D3DXMatrixLookAtLH(
       &_matView,             // pOut [in, out] ���Z���ʂł��� D3DXMATRIX �\���̂ւ̃|�C���^�B
        _pVecCamFromPoint,    // pEye [in] ���_���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B���̒l�́A���s�ړ��Ɏg�p�����B
        _pVecCamLookatPoint,  // pAt  [in] �J�����̒����Ώۂ��`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
        _pVecCamUp            // pUp  [in] �J�����g ���[���h�̏���A��ʂɂ� [0, 1, 0] ���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
    );

    // �ˉe�ϊ��s��쐬
    _TRACE_(FUNC_NAME<<" _cameraZ_org="<<_cameraZ_org<<" dxcoord");
    _TRACE_(FUNC_NAME<<" _dep="<<_dep<<"");
    _TRACE_(FUNC_NAME<<" _zn=" << _zn << " dxcoord");
    _TRACE_(FUNC_NAME<<" _zf=("<<-_cameraZ_org<<"*("<<_dep<<"+1.0)-"<<_zn<<")=" << _zf << " dxcoord");
    _TRACE_(FUNC_NAME<<" �J�����̕\�������͈� ["<<_zn<<" ~ "<<_zf<<"] dxcoord");

    if (CONFIG::PRJ_2D_MODE) {
        //2D���[�h�F���ˉe�ϊ�
        D3DXMatrixOrthoLH(
            &_matProj,
            PX_DX(CONFIG::GAME_BUFFER_WIDTH),
            PX_DX(CONFIG::GAME_BUFFER_HEIGHT),
            _zn,
            _zf
        );
    } else {
        //3D���[�h�F�ʏ�̎ˉe�ϊ�
        D3DXMatrixPerspectiveFovLH(
            &_matProj,
            _rad_fovY,       //y��������p���f�B�A��(0�`��)
            _screen_aspect,  //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
            _zn,             //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
            _zf              //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
        );
    }
    //�ˉe�ϊ��t�s��
    D3DXMatrixInverse(&_matInvProj, nullptr, &_matProj);

    setPosition(0, 0, DX_C(_cameraZ_org));
    setFaceAngTwd(0,0,0);
    getVecVehicle()->setMvAngTwd(0,0,0);
    setHitAble(false);

    pCARETAKER->_pID3DDevice9->GetViewport(&_viewport);
    _TRACE_("_viewport.X="<<_viewport.X);
    _TRACE_("_viewport.Y="<<_viewport.Y);
    _TRACE_("_viewport.Width="<<_viewport.Width);
    _TRACE_("_viewport.Height="<<_viewport.Height);
    _TRACE_("_viewport.MinZ="<<_viewport.MinZ);
    _TRACE_("_viewport.MaxZ="<<_viewport.MaxZ);
    //�r���[�|�[�g�s��
    // |   W/2,     0,         0, 0 |
    // |     0,  -H/2,         0, 0 |
    // |     0,     0, MaxZ-MinZ, 0 |
    // | X+W/2, H/2+Y,      MinZ, 1 |
    D3DXMatrixIdentity(&_matViewPort);
    _matViewPort._11 =  _viewport.Width  / 2.0f;
    _matViewPort._22 = -1 * (_viewport.Height / 2.0f);
    _matViewPort._33 = _viewport.MaxZ - _viewport.MinZ;
    _matViewPort._41 = _viewport.X + (_viewport.Width / 2.0f);
    _matViewPort._42 = (_viewport.Height / 2.0f) + _viewport.Y;
    _matViewPort._43 = _viewport.MinZ;
    _matViewPort._44 = 1.0f;
    //�r���[�|�[�g�t�s��
    D3DXMatrixInverse(&_matInvViewPort, nullptr, &_matViewPort);

    _x_prev = 0;
    _y_prev = 0;
    _z_prev = 0;

    _pCameraViewPoint = nullptr;
    _pCameraUpVector = nullptr;

    //�r���[�|�[�g�s��
    // | W/2,    0, 0, 0 |
    // |   0, -H/2, 0, 0 |
    // |   0,    0, 1, 0 |
    // | W/2,  H/2, 0, 1 |
    //
    //W :�X�N���[����(�s�N�Z��)
    //H :�X�N���[������(�s�N�Z��)

}

void Camera::initialize() {
    getCameraViewPoint();
    getCameraUpVector();
}

void Camera::processBehavior() {
    const dxcoord x1 = dxcoord(_viewport.X);
    const dxcoord y1 = dxcoord(_viewport.Y);
    const dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
    const dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);
    // _viewport.MinZ / MaxZ �́A�ʏ킻�ꂼ�� 0 / 1
    const float MinZ = 0;
    const float MaxZ = 1;
    //(x1,y1)   -------->
    //    +--------------------+
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  v |                    |
    //    +--------------------+
    //                         (x2,y2)
    // _11,  _12,  _13,  _14,   // �� ������W
    // _21,  _22,  _23,  _24,   // �� �E����W
    // _31,  _32,  _33,  _34,   // �� �������W
    // _41,  _42,  _43,  _44    // �� �E�����W
    // �������āA�S�_��x��
    //���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��

    //�������O�S���_�����߂�
    D3DXMATRIX matScreenNear = D3DXMATRIX(
        x1, y1, MinZ, 1.0f,  // ��O����X�N���[�����W
        x2, y1, MinZ, 1.0f,  // ��O�E��X�N���[�����W
        x1, y2, MinZ, 1.0f,  // ��O�����X�N���[�����W
        x2, y2, MinZ, 1.0f   // ��O�E���X�N���[�����W
    );
    D3DXMATRIX matNear = matScreenNear * _matInvViewPort_Proj_View;
    const float near0_W = matNear._14;
    const float near1_W = matNear._24;
    const float near2_W = matNear._34;
    const float near3_W = matNear._44;
    D3DXVECTOR3 vecNear0 = D3DXVECTOR3(matNear._11/near0_W, matNear._12/near0_W, matNear._13/near0_W); //��O���ハ�[���h���W
    D3DXVECTOR3 vecNear1 = D3DXVECTOR3(matNear._21/near1_W, matNear._22/near1_W, matNear._23/near1_W); //��O�E�ハ�[���h���W
    D3DXVECTOR3 vecNear2 = D3DXVECTOR3(matNear._31/near2_W, matNear._32/near2_W, matNear._33/near2_W); //��O�������[���h���W
    D3DXVECTOR3 vecNear3 = D3DXVECTOR3(matNear._41/near3_W, matNear._42/near3_W, matNear._43/near3_W); //��O�E�����[���h���W

    //�����䉜�S���_�����߂�
    D3DXMATRIX matScreeFar = D3DXMATRIX(
        x1, y1, MaxZ, 1.0f,  // ����X�N���[�����W
        x2, y1, MaxZ, 1.0f,  // �E��X�N���[�����W
        x1, y2, MaxZ, 1.0f,  // �����X�N���[�����W
        x2, y2, MaxZ, 1.0f   // �E���X�N���[�����W
    );
    D3DXMATRIX matFar = matScreeFar * _matInvViewPort_Proj_View;
    const float far0_W = matFar._14;
    const float far1_W = matFar._24;
    const float far2_W = matFar._34;
    const float far3_W = matFar._44;
    D3DXVECTOR3 vecFar0 = D3DXVECTOR3(matFar._11/far0_W, matFar._12/far0_W, matFar._13/far0_W);  //�����ハ�[���h���W
    D3DXVECTOR3 vecFar1 = D3DXVECTOR3(matFar._21/far1_W, matFar._22/far1_W, matFar._23/far1_W);  //���E�ハ�[���h���W
    D3DXVECTOR3 vecFar2 = D3DXVECTOR3(matFar._31/far2_W, matFar._32/far2_W, matFar._33/far2_W);  //���������[���h���W
    D3DXVECTOR3 vecFar3 = D3DXVECTOR3(matFar._41/far3_W, matFar._42/far3_W, matFar._43/far3_W);  //���E�����[���h���W

    // ������̖ʂ�@�����K�����Đݒ�
    // �� ( F����AN�E��AN���� )
    D3DXPlaneNormalize(
        &_plnTop,
        D3DXPlaneFromPoints(&_plnTop, &(vecFar0), &(vecNear1), &(vecNear0))
    );

    // �� ( F�����AN�����AN�E�� )
   D3DXPlaneNormalize(
       &_plnBottom,
       D3DXPlaneFromPoints(&_plnBottom, &(vecFar2), &(vecNear2), &(vecNear3))
   );

   // �� ( F����AN����AN���� )
   D3DXPlaneNormalize(
       &_plnLeft,
       D3DXPlaneFromPoints(&_plnLeft, &(vecFar0), &(vecNear0), &(vecNear2))
   );
   // �E ( F�E��AN�E���AN�E�� )
   D3DXPlaneNormalize(
       &_plnRight,
       D3DXPlaneFromPoints(&_plnRight, &(vecFar1), &(vecNear3), &(vecNear1))
   );
   // ��O ( N�����AN����AN�E��)
   D3DXPlaneNormalize(
       &_plnInfront,
       D3DXPlaneFromPoints(&_plnInfront, &(vecNear2), &(vecNear0), &(vecNear3))
   );
   // �� ( F�E���AF����AF����)
   D3DXPlaneNormalize(
       &_plnBack,
       D3DXPlaneFromPoints(&_plnBack, &(vecFar3), &(vecFar0), &(vecFar2))
   );

   // ���S������ �i�{�����[���p���Ŏg�p�j
   D3DXVECTOR3 vecVerticalCenter0 =
           D3DXVECTOR3(
               (vecFar1.x + vecFar0.x)*0.5f,
               (vecFar1.y + vecFar0.y)*0.5f,
               (vecFar1.z + vecFar0.z)*0.5f
           );
   D3DXVECTOR3 vecVerticalCenter1 =
           D3DXVECTOR3(
               (vecNear3.x + vecNear2.x)*0.5f,
               (vecNear3.y + vecNear2.y)*0.5f,
               (vecNear3.z + vecNear2.z)*0.5f
           );
   D3DXVECTOR3 vecVerticalCenter2 =
           D3DXVECTOR3(
               (vecNear1.x + vecNear0.x)*0.5f,
               (vecNear1.y + vecNear0.y)*0.5f,
               (vecNear1.z + vecNear0.z)*0.5f
           );
    D3DXPlaneNormalize(
        &_plnVerticalCenter,
        D3DXPlaneFromPoints(&_plnVerticalCenter, &(vecVerticalCenter0),
                                                 &(vecVerticalCenter1),
                                                 &(vecVerticalCenter2)
                            )
    );

    //�̂̂�������
    //    _vecNear[0].x = x1;  _vecNear[0].y = y1;  _vecNear[0].z = _viewport.MinZ;   // ���� (�ϊ���)
    //    _vecNear[1].x = x2;  _vecNear[1].y = y1;  _vecNear[1].z = _viewport.MinZ;   // �E�� (�ϊ���)
    //    _vecNear[2].x = x1;  _vecNear[2].y = y2;  _vecNear[2].z = _viewport.MinZ;   // ���� (�ϊ���)
    //    _vecNear[3].x = x2;  _vecNear[3].y = y2;  _vecNear[3].z = _viewport.MinZ;   // �E�� (�ϊ���)
    //
    //    _vecFar[0].x  = x1;  _vecFar[0].y  = y1;  _vecFar[0].z  = _viewport.MaxZ;   // ���� (�ϊ���)
    //    _vecFar[1].x  = x2;  _vecFar[1].y  = y1;  _vecFar[1].z  = _viewport.MaxZ;   // �E�� (�ϊ���)
    //    _vecFar[2].x  = x1;  _vecFar[2].y  = y2;  _vecFar[2].z  = _viewport.MaxZ;   // ���� (�ϊ���)
    //    _vecFar[3].x  = x2;  _vecFar[3].y  = y2;  _vecFar[3].z  = _viewport.MaxZ;   // �E�� (�ϊ���)
    //
    //    // ������̂W�_�̌v�Z
    //    const D3DXMATRIX mat_world = D3DXMATRIX(
    //        1.0f,  0.0f,  0.0f,  0.0f,
    //        0.0f,  1.0f,  0.0f,  0.0f,
    //        0.0f,  0.0f,  1.0f,  0.0f,
    //        0.0f,  0.0f,  0.0f,  1.0f
    //    );
    //    // ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
    //    for ( int i = 0; i < 4; i++ ) {
    //        D3DXVec3Unproject(
    //            &_vecNear[i], //D3DXVECTOR3 *pOut,              [in, out] ���Z���ʂł��� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
    //            &_vecNear[i], //CONST D3DXVECTOR3 *pV,          [in] �����̊�ɂȂ� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
    //            &_viewport,   //CONST D3DVIEWPORT9 *pViewport,  [in] �r���[�|�[�g��\�� D3DVIEWPORT9 �\���̂ւ̃|�C���^�B
    //            &_matProj,    //CONST D3DXMATRIX *pProjection,  [in] �ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
    //            &_matView,    //CONST D3DXMATRIX *pView,        [in] �r���[�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
    //            &mat_world    //CONST D3DXMATRIX *pWorld        [in] ���[���h�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
    //        );
    //        D3DXVec3Unproject(
    //            &_vecFar[i],
    //            &_vecFar[i],
    //            &_viewport,
    //            &_matProj,
    //            &_matView,
    //            &mat_world
    //        );
    //    }
}

void Camera::processSettlementBehavior() {
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);

    _x_prev = _x;
    _y_prev = _y;
    _z_prev = _z;
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    CameraViewPoint* pVp = getCameraViewPoint();
    _pVecCamLookatPoint->x = pVp->_fX;
    _pVecCamLookatPoint->y = pVp->_fY;
    _pVecCamLookatPoint->z = pVp->_fZ;
    CameraUpVector* pUpv = getCameraUpVector();
    _pVecCamUp->x = pUpv->_fX;
    _pVecCamUp->y = pUpv->_fY;
    _pVecCamUp->z = pUpv->_fZ;
    // VIEW�ϊ��s��X�V
    D3DXMatrixLookAtLH(&_matView,
                       _pVecCamFromPoint,
                       _pVecCamLookatPoint,
                       _pVecCamUp);
    D3DXMatrixInverse(&_matInvView, nullptr, &_matView);
    _matInvViewPort_Proj_View = _matInvViewPort * _matInvProj * _matInvView;

}

CameraViewPoint* Camera::getCameraViewPoint() {
    if (_pCameraViewPoint) {
        return _pCameraViewPoint;
    } else {
        _pCameraViewPoint = createCameraViewPoint();
        _pCameraViewPoint->setPosition(0, 0, 0);
        appendGroupChild(_pCameraViewPoint);
        return _pCameraViewPoint;
    }
}

CameraUpVector* Camera::getCameraUpVector() {
    if (_pCameraUpVector) {
        return _pCameraUpVector;
    } else {
        _pCameraUpVector = createCameraUpVector();
        _pCameraUpVector->setPosition(0, DX_C(1), 0);
        appendGroupChild(_pCameraUpVector);
        return _pCameraUpVector;
    }
}

void Camera::setDefaultPosition() {
    _x = 0;
    _y = 0;
    _z = DX_C(_cameraZ_org);
    CameraViewPoint* pVp = getCameraViewPoint();
    pVp->setPosition(0, 0, 0);
    CameraUpVector* pUpv = getCameraUpVector();
    pUpv->setPosition(0, DX_C(1), 0);
}

bool Camera::isMoving() {
    if (_x_prev == _x && _y_prev == _y && _z_prev == _z) {
        return false;
    } else {
        return true;
    }
}

Camera::~Camera() {
    GGAF_DELETE(_pVecCamFromPoint);
    GGAF_DELETE(_pVecCamLookatPoint);
    GGAF_DELETE(_pVecCamUp);
}
