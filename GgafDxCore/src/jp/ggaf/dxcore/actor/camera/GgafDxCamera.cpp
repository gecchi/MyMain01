#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraUpVector.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCamera::GgafDxCamera(const char* prm_name, double prm_rad_fovX, double prm_dep) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr),
_rad_fovX(prm_rad_fovX),      //�S�Ă̊��fovX����l����
_dep(prm_dep),
_rad_half_fovX(_rad_fovX / 2.0),
_screen_aspect(1.0 * (PROPERTY::GAME_BUFFER_WIDTH) / (PROPERTY::GAME_BUFFER_HEIGHT)),
_rad_fovY(atan( ( (tan(_rad_fovX/2.0)) / _screen_aspect) )*2.0),
_rad_half_fovY(_rad_fovY / 2.0),
_tan_half_fovX(tan(_rad_fovX/2.0)),
_tan_half_fovY(tan(_rad_fovY/2.0)),
_cameraZ_org(-1.0 * ((1.0 * (PROPERTY::GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0) / _tan_half_fovY),
_zn(0.1f),
_zf(-_cameraZ_org*(_dep+1.0)),
_x_buffer_left(PX_C(PROPERTY::GAME_BUFFER_WIDTH) / -2),
_x_buffer_right(PX_C(PROPERTY::GAME_BUFFER_WIDTH) / 2),
_y_buffer_top(PX_C(PROPERTY::GAME_BUFFER_HEIGHT) / 2),
_y_buffer_bottom(PX_C(PROPERTY::GAME_BUFFER_HEIGHT) / -2)
{
    _class_name = "GgafDxCamera";
    //fovX�ƃA�X�y�N�g�䂩��fovY���v�Z���ċ��߂�
    _TRACE_(FUNC_NAME<<" ��ʃA�X�y�N�g�F"<<_screen_aspect);
    _TRACE_(FUNC_NAME<<" FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);


    //�����J�����ʒu�͎��_(0,0,Z)�A�����_(0,0,0)
    //Z�́A�L������Z=0��XY���ʂŒ��x�L�������l�s�N�Z�����ƈ�v����悤�ȏ��ɃJ����������
    _TRACE_(FUNC_NAME<<" �J�����̈ʒu(0,0,"<<_cameraZ_org<<")");
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


    _TRACE_(FUNC_NAME<<" �͈� ["<<_zn<<" ~ "<<_zf<<"]");
    if (PROPERTY::PRJ_2D_MODE) {
        //2D���[�h���ˉe
        D3DXMatrixOrthoLH(
            &_matProj,
            PX_DX(PROPERTY::GAME_BUFFER_WIDTH),
            PX_DX(PROPERTY::GAME_BUFFER_HEIGHT),
            _zn,
            _zf
        );
    } else {
        //3D���[�h�ʏ�ˉe
        D3DXMatrixPerspectiveFovLH(
                &_matProj,
                _rad_fovY,       //y��������p���f�B�A��(0�`��)
                _screen_aspect,  //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
                _zn,             //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
                _zf              //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
        );
    }

    locate(0, 0, DX_C(_cameraZ_org));
    setFaceAngTwd(0,0,0);
    getKuroko()->setMvAngTwd(0,0,0);
    setHitAble(false);

    GgafDxGod::_pID3DDevice9->GetViewport(&_viewport);

    _x_prev = 0;
    _y_prev = 0;
    _z_prev = 0;

    _pCameraViewPoint = nullptr;
    _pCameraUpVector = nullptr;
}

void GgafDxCamera::initialize() {
    getCameraViewPoint();
    getCameraUpVector();
}

void GgafDxCamera::processBehavior() {
    //if (isMoving() || _pCameraViewPoint->isMoving()) {
        //if (_frame_of_behaving % 2 == 0) { //10�t���[���ɂP�񂾂��v�Z
        //�X�N���[���S�̂̃N���C�A���g�̈��ێ��B

        // _viewport.MinZ / MaxZ �́A�ʏ킻�ꂼ�� 0 / 1
        const dxcoord x1 = dxcoord(_viewport.X);
        const dxcoord y1 = dxcoord(_viewport.Y);
        const dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
        const dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);

        // ������̂W�_���i�[�����C���X�^���X
        _vecNear[0].x = x1;  _vecNear[0].y = y1;  _vecNear[0].z = _viewport.MinZ;   // ���� (�ϊ���)
        _vecNear[1].x = x2;  _vecNear[1].y = y1;  _vecNear[1].z = _viewport.MinZ;   // �E�� (�ϊ���)
        _vecNear[2].x = x1;  _vecNear[2].y = y2;  _vecNear[2].z = _viewport.MinZ;   // ���� (�ϊ���)
        _vecNear[3].x = x2;  _vecNear[3].y = y2;  _vecNear[3].z = _viewport.MinZ;   // �E�� (�ϊ���)

        _vecFar[0].x  = x1;  _vecFar[0].y  = y1;  _vecFar[0].z  = _viewport.MaxZ;   // ���� (�ϊ���)
        _vecFar[1].x  = x2;  _vecFar[1].y  = y1;  _vecFar[1].z  = _viewport.MaxZ;   // �E�� (�ϊ���)
        _vecFar[2].x  = x1;  _vecFar[2].y  = y2;  _vecFar[2].z  = _viewport.MaxZ;   // ���� (�ϊ���)
        _vecFar[3].x  = x2;  _vecFar[3].y  = y2;  _vecFar[3].z  = _viewport.MaxZ;   // �E�� (�ϊ���)

        // ������̂W�_�̌v�Z
        const D3DXMATRIX mat_world = D3DXMATRIX(
            1.0f,  0.0f,  0.0f,  0.0f,
            0.0f,  1.0f,  0.0f,  0.0f,
            0.0f,  0.0f,  1.0f,  0.0f,
            0.0f,  0.0f,  0.0f,  1.0f
        );
        // ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
        for( int i = 0; i < 4; i++ ) {
            D3DXVec3Unproject(
                &_vecNear[i], //D3DXVECTOR3 *pOut,              [in, out] ���Z���ʂł��� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
                &_vecNear[i], //CONST D3DXVECTOR3 *pV,          [in] �����̊�ɂȂ� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
                &_viewport,   //CONST D3DVIEWPORT9 *pViewport,  [in] �r���[�|�[�g��\�� D3DVIEWPORT9 �\���̂ւ̃|�C���^�B
                &_matProj,    //CONST D3DXMATRIX *pProjection,  [in] �ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
                &_matView,    //CONST D3DXMATRIX *pView,        [in] �r���[�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
                &mat_world    //CONST D3DXMATRIX *pWorld        [in] ���[���h�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
            );
            D3DXVec3Unproject(
                &_vecFar[i],
                &_vecFar[i],
                &_viewport,
                &_matProj,
                &_matView,
                &mat_world
            );
        }

        // ������̖�
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
            &_plnInfront,
            D3DXPlaneFromPoints(&_plnInfront, &(_vecNear[2]), &(_vecNear[0]), &(_vecNear[3]))
        );
        // �� ( F�E��AF�����AF����)
        D3DXPlaneNormalize(
            &_plnBack,
            D3DXPlaneFromPoints(&_plnBack, &(_vecFar[3]), &(_vecFar[0]), &(_vecFar[2]))
        );

        // ���S������ �i�{�����[���p���Ŏg�p�j
        _vecVerticalCenter[0].x = (_vecFar[1].x + _vecFar[0].x)*0.5f;
        _vecVerticalCenter[0].y = (_vecFar[1].y + _vecFar[0].y)*0.5f;
        _vecVerticalCenter[0].z = (_vecFar[1].z + _vecFar[0].z)*0.5f;

        _vecVerticalCenter[1].x = (_vecNear[3].x + _vecNear[2].x)*0.5f;
        _vecVerticalCenter[1].y = (_vecNear[3].y + _vecNear[2].y)*0.5f;
        _vecVerticalCenter[1].z = (_vecNear[3].z + _vecNear[2].z)*0.5f;

        _vecVerticalCenter[2].x = (_vecNear[1].x + _vecNear[0].x)*0.5f;
        _vecVerticalCenter[2].y = (_vecNear[1].y + _vecNear[0].y)*0.5f;
        _vecVerticalCenter[2].z = (_vecNear[1].z + _vecNear[0].z)*0.5f;

        D3DXPlaneNormalize(
            &_plnVerticalCenter,
            D3DXPlaneFromPoints(&_plnVerticalCenter, &(_vecVerticalCenter[0]),
                                                     &(_vecVerticalCenter[1]),
                                                     &(_vecVerticalCenter[2])
                                )
        );
    //}

}

void GgafDxCamera::processJudgement() {
    _x_prev = _x;
    _y_prev = _y;
    _z_prev = _z;

    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    GgafDxCameraViewPoint* pVp = getCameraViewPoint();
    _pVecCamLookatPoint->x = pVp->_fX;
    _pVecCamLookatPoint->y = pVp->_fY;
    _pVecCamLookatPoint->z = pVp->_fZ;
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    _pVecCamUp->x = pUpv->_fX;
    _pVecCamUp->y = pUpv->_fY;
    _pVecCamUp->z = pUpv->_fZ;
    D3DXMatrixLookAtLH(&_matView,
                       _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

GgafDxCameraViewPoint* GgafDxCamera::getCameraViewPoint() {
    if (_pCameraViewPoint) {
        return _pCameraViewPoint;
    } else {
        _pCameraViewPoint = createCameraViewPoint();
        _pCameraViewPoint->locate(0, 0, 0);
        addSubGroup(_pCameraViewPoint);
        return _pCameraViewPoint;
    }
}

GgafDxCameraUpVector* GgafDxCamera::getCameraUpVector() {
    if (_pCameraUpVector) {
        return _pCameraUpVector;
    } else {
        _pCameraUpVector = createCameraUpVector();
        _pCameraUpVector->locate(0, PX_C(1), 0);
        addSubGroup(_pCameraUpVector);
        return _pCameraUpVector;
    }
}

void GgafDxCamera::setDefaultPosition() {
    _x = 0;
    _y = 0;
    _z = DX_C(_cameraZ_org);
    GgafDxCameraViewPoint* pVp = getCameraViewPoint();
    pVp->locate(0, 0, 0);
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    pUpv->locate(0, PX_C(1), 0);
}

bool GgafDxCamera::isMoving() {
    if (_x_prev == _x && _y_prev == _y && _z_prev == _z) {
        return false;
    } else {
        return true;
    }
}

void GgafDxCamera::setCamUpVecByFaceNo(dir26 prm_face_no) {
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    pUpv->locateByFaceNo(prm_face_no);
}

GgafDxCamera::~GgafDxCamera() {
    GGAF_DELETE(_pVecCamFromPoint);
    GGAF_DELETE(_pVecCamLookatPoint);
    GGAF_DELETE(_pVecCamUp);
}
