#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

int GgafDxCamera::_X_ScreenLeft   = 0;
int GgafDxCamera::_X_ScreenRight  = 0;
int GgafDxCamera::_Y_ScreenTop    = 0;
int GgafDxCamera::_Y_ScreenBottom = 0;



GgafDxCamera::GgafDxCamera(const char* prm_name, float prm_rad_fovX, float prm_dep) : GgafDxGeometricActor(prm_name, NULL, NULL) {
    _class_name = "GgafDxCamera";

    //�S�Ă̊��fovX����l����
    _rad_fovX = prm_rad_fovX;
    //������ێ�
    _rad_half_fovX = _rad_fovX / 2.0f;
    //��ʃA�X�y�N�g��(w/h)
    _screen_aspect = (FLOAT)(1.0f * CFG_PROPERTY(GAME_BUFFER_WIDTH) / CFG_PROPERTY(GAME_BUFFER_HEIGHT));
    //fovX�ƃA�X�y�N�g�䂩��fovY���v�Z���ċ��߂�
    float xzRatio = tan( _rad_fovX/2 );
    float yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0f;
    _TRACE_("GgafDxCamera::GgafDxCamera ��ʃA�X�y�N�g�F"<<_screen_aspect);
    _TRACE_("GgafDxCamera::GgafDxCamera FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);

    //������ێ�
    _rad_half_fovY = _rad_fovY / 2.0f;
    //tan�l���ێ�
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //�����J�����ʒu�͎��_(0,0,Z)�A�����_(0,0,0)
    //Z�́A�L������Z=0��XY���ʂŒ��x�L�������l�s�N�Z�����ƈ�v����悤�ȏ��ɃJ����������
    _cameraZ = -1.0f * ((CFG_PROPERTY(GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0f) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("GgafDxCamera::GgafDxCamera �J�����̈ʒu(0,0,"<<_cameraZ<<")");
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ); //�ʒu
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //�����������
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //�����

    // VIEW�ϊ��s��쐬
    D3DXMatrixLookAtLH(
       &_matView,         // pOut [in, out] ���Z���ʂł��� D3DXMATRIX �\���̂ւ̃|�C���^�B
        _pVecCamFromPoint,    // pEye [in] ���_���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B���̒l�́A���s�ړ��Ɏg�p�����B
        _pVecCamLookatPoint,  // pAt  [in] �J�����̒����Ώۂ��`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
        _pVecCamUp            // pUp  [in] �J�����g ���[���h�̏���A��ʂɂ� [0, 1, 0] ���`���� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
    );

    // �ˉe�ϊ��s��쐬�i�R�c�����ʁj
    _dep = prm_dep;
    _zn = 0.1f;
    _zf = -_cameraZ_org*(_dep+1.0f);
    _TRACE_("GgafDxCamera::GgafDxCamera �͈� ["<<_zn<<" ~ "<<_zf<<"]");
    D3DXMatrixPerspectiveFovLH(
            &_matProj,
            _rad_fovY,        //y��������p���f�B�A��(0�`��)
            _screen_aspect,   //�A�X�y�N�g��  640�~480 �̏ꍇ  640/480
            _zn,             //zn:�J��������߂��̃N���b�v�ʂ܂ł̋���(�ǂ�����̋������\���Ώۂ��j��0
            _zf              //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
            //(FLOAT)(-1.0f*dCam*4)
            //(-1.0f*fCam)-30,
            //(-1.0f*fCam)+30
    );
    /*
     //������W�n���ˉe
     D3DXMatrixOrthoLH(
     &_matProj,
     CFG_PROPERTY(GAME_BUFFER_WIDTH),
     CFG_PROPERTY(GAME_BUFFER_HEIGHT),
     1.0f,
     CFG_PROPERTY(GAME_BUFFER_HEIGHT)
     );
     */
    locate(0, 0, Dx2Co(_cameraZ));
    _pKurokoA->setMvAng(0,0,0);
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setRzMvAngVelo(0);
    _pKurokoA->setRyMvAngVelo(0);
    _pKurokoA->_mv_ang_rz_target_flg = true;
    _pKurokoA->_mv_ang_ry_target_flg = true;
    setHitAble(false);

    _pViewPoint = NEW GgafDxCameraViewPoint();
    _pViewPoint->locate(0, 0, 0);

    _X_ScreenLeft   = Px2Co(CFG_PROPERTY(GAME_BUFFER_WIDTH)) / -2;
    _X_ScreenRight  = Px2Co(CFG_PROPERTY(GAME_BUFFER_WIDTH)) / 2;
    _Y_ScreenTop    = Px2Co(CFG_PROPERTY(GAME_BUFFER_HEIGHT)) / 2;
    _Y_ScreenBottom = Px2Co(CFG_PROPERTY(GAME_BUFFER_HEIGHT)) / -2;
    GgafDxGod::_pID3DDevice9->GetViewport(&_viewport);
}

void GgafDxCamera::initialize() {
    addSubLast(_pViewPoint);
}

void GgafDxCamera::processBehavior() {
    //if (_frame_of_behaving % 2 == 0) { //10�t���[���ɂP�񂾂��v�Z
    //�X�N���[���S�̂̃N���C�A���g�̈��ێ��B

    // _viewport.MinZ / MaxZ �́A�ʏ킻�ꂼ�� 0 / 1
    dxcoord x1 = dxcoord(_viewport.X);
    dxcoord y1 = dxcoord(_viewport.Y);
    dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
    dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);

    // ������̂W�_���i�[�����C���X�^���X
    _vecNear[0] = D3DXVECTOR3( x1, y1, _viewport.MinZ ); // ���� (�ϊ���)
    _vecNear[1] = D3DXVECTOR3( x2, y1, _viewport.MinZ ); // �E�� (�ϊ���)
    _vecNear[2] = D3DXVECTOR3( x1, y2, _viewport.MinZ ); // ���� (�ϊ���)
    _vecNear[3] = D3DXVECTOR3( x2, y2, _viewport.MinZ ); // �E�� (�ϊ���)

    _vecFar[0]  = D3DXVECTOR3( x1, y1, _viewport.MaxZ ); // ���� (�ϊ���)
    _vecFar[1]  = D3DXVECTOR3( x2, y1, _viewport.MaxZ ); // �E�� (�ϊ���)
    _vecFar[2]  = D3DXVECTOR3( x1, y2, _viewport.MaxZ ); // ���� (�ϊ���)
    _vecFar[3]  = D3DXVECTOR3( x2, y2, _viewport.MaxZ ); // �E�� (�ϊ���)

    // ������̂W�_�̌v�Z
    static D3DXMATRIX mat_world;
    D3DXMatrixIdentity( &mat_world );
    // ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
    for( int i = 0; i < 4; ++i ) {
        D3DXVec3Unproject(
            &_vecNear[i],   //D3DXVECTOR3 *pOut,              [in, out] ���Z���ʂł��� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
            &_vecNear[i],   //CONST D3DXVECTOR3 *pV,          [in] �����̊�ɂȂ� D3DXVECTOR3 �\���̂ւ̃|�C���^�B
            &_viewport,      //CONST D3DVIEWPORT9 *pViewport,[in] �r���[�|�[�g��\�� D3DVIEWPORT9 �\���̂ւ̃|�C���^�B
            &_matProj,  //CONST D3DXMATRIX *pProjection,  [in] �ˉe�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
            &_matView,  //CONST D3DXMATRIX *pView,        [in] �r���[�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
            &mat_world      //CONST D3DXMATRIX *pWorld        [in] ���[���h�s���\�� D3DXMATRIX �\���̂ւ̃|�C���^�B
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

    // ���S������ �i�{�����[���p���Ŏg�p�j
    _vecVerticalCenter[0] = D3DXVECTOR3( (_vecFar[1].x + _vecFar[0].x)/2.0,
                                         (_vecFar[1].y + _vecFar[0].y)/2.0,
                                         (_vecFar[1].z + _vecFar[0].z)/2.0
                                       );
    _vecVerticalCenter[1] = D3DXVECTOR3( (_vecNear[3].x + _vecNear[2].x)/2.0,
                                         (_vecNear[3].y + _vecNear[2].y)/2.0,
                                         (_vecNear[3].z + _vecNear[2].z)/2.0
                                       );
    _vecVerticalCenter[2] = D3DXVECTOR3( (_vecNear[1].x + _vecNear[0].x)/2.0,
                                         (_vecNear[1].y + _vecNear[0].y)/2.0,
                                         (_vecNear[1].z + _vecNear[0].z)/2.0
                                       );
    D3DXPlaneNormalize(
        &_plnVerticalCenter,
        D3DXPlaneFromPoints(&_plnVerticalCenter, &(_vecVerticalCenter[0]),
                                                 &(_vecVerticalCenter[1]),
                                                 &(_vecVerticalCenter[2])
                            )
    );

    //}

//    xaxis.x           yaxis.x           zaxis.x          0
//    xaxis.y           yaxis.y           zaxis.y          0
//    xaxis.z           yaxis.z           zaxis.z          0
//   -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1


    //_TRACE_(_matView._14<<","<<_matView._24<<","<<_matView._34);

}



void GgafDxCamera::processJudgement() {
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    _pVecCamLookatPoint->x = Co2Dx(_pViewPoint->_X);
    _pVecCamLookatPoint->y = Co2Dx(_pViewPoint->_Y);
    _pVecCamLookatPoint->z = Co2Dx(_pViewPoint->_Z);
    D3DXMatrixLookAtLH(&_matView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

void GgafDxCamera::setViewPoint(coord prm_tX, coord prm_tY, coord prm_tZ) {
    _pViewPoint->_X = prm_tX;
    _pViewPoint->_Y = prm_tY;
    _pViewPoint->_Z = prm_tZ;
}

void GgafDxCamera::setViewPoint(GgafDxGeometricActor* prm_pActor) {
    _pViewPoint->locateAs(prm_pActor);
}


void GgafDxCamera::setDefaultPosition() {
    _X = 0;
    _Y = 0;
    _Z = Dx2Co(_cameraZ_org);
    _pViewPoint->_X = 0;
    _pViewPoint->_Y = 0;
    _pViewPoint->_Z = 0;
    _pVecCamUp->x = 0.0f;
    _pVecCamUp->y = 1.0f;
    _pVecCamUp->z = 0.0f;
}


GgafDxCamera::~GgafDxCamera() {
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);
}
