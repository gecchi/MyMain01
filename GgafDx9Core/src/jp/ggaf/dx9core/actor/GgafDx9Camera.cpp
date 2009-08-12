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
            500.0 //zf:�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn
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
//    float x1_ = _pVecCamFromPoint->x;
//    float y1_ = _pVecCamFromPoint->y;
//    float z1_ = _pVecCamFromPoint->z;
//    float x2_ = _pVecCamLookatPoint->x;
//    float y2_ = _pVecCamLookatPoint->y;
//    float z2_ = _pVecCamLookatPoint->z;
//    _view_slant_XZ = (z2_-z1_)/(x2_-x1_);
//    _view_slant_ZY = (y2_-y1_)/(z2_-z1_);

//    _view_rad_XZ = atan(_view_slant_XZ);
//    _view_rad_ZY = atan(_view_slant_ZY);

//    _view_border_rad1_XZ =  _view_rad_XZ + _rad_half_fovX; //����1.3�͓K��
//    _view_border_rad2_XZ =  _view_rad_XZ - _rad_half_fovX;
//    _view_border_rad1_ZY =  _view_rad_ZY + _rad_half_fovY;
//    _view_border_rad2_ZY =  _view_rad_ZY - _rad_half_fovY;

//    _view_border_slant1_XZ = tan(_view_border_rad1_XZ);
//    _view_border_slant2_XZ = tan(_view_border_rad2_XZ);
//    _view_border_slant1_ZY = tan(_view_border_rad1_ZY);
//    _view_border_slant2_ZY = tan(_view_border_rad2_ZY);

//    _view_border_intercept1_XZ = _Z - (_view_border_slant1_XZ*_X);
//    _view_border_intercept2_XZ = _Z - (_view_border_slant2_XZ*_X);
//    _view_border_intercept1_ZY = _Y - (_view_border_slant1_ZY*_Z);
//    _view_border_intercept2_ZY = _Y - (_view_border_slant2_ZY*_Z);



//    D3DXMatrixOrthoLH(
//        &_vMatrixOrthoProj,
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w �r���[ �{�����[���̕�
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h �r���[ �{�����[���̍���
//        1.0,    //zn �r���[ �{�����[���̍ŏ� z �l (z �߂Ƃ�����)
//        2000.0  //zf �r���[ �{�����[���̍ő� z �l (z ���Ƃ�����)
//    );








    HRESULT hr;
    D3DVIEWPORT9 viewport;       //�N���C�A���g�̈�S�̂̕ێ�
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
     D3DXMATRIX mat_world;
     D3DXMatrixIdentity( &mat_world );
     D3DVIEWPORT9 *pViewport = const_cast<D3DVIEWPORT9*>(&viewport);
     // ���[���h �� �r���[ �� �ˉe �� �X�N���[���ϊ� �̋t���s��
     for( int i = 0; i < 4; ++i )
     {
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

}



void GgafDx9Camera::processJudgement() {
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    _pVecCamLookatPoint->x = (1.0 * _gazeX) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0 * _gazeY) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0 * _gazeZ) / LEN_UNIT / PX_UNIT;


    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}



//bool GgafDx9Camera::isInTheViewports_old(int prm_X, int prm_Y, int prm_Z) {
//    //���x�D��̂��ߊȈՎ����䔻��
//    //fovX*1.3  fovY*1.3 �͂�1.3�́A ����p�ɂ���ĕς��Ȃ���΂����܂���B���̂����肪�K���ł��B
//    //�J�������^��t�߂���^���t�߂�����ꍇ�A����сA�^���t�߂���^��t�߂�����ꍇ��
//    //����������ł��܂���B
//
//    if ( _Z - 10000000 < prm_Z && prm_Z < _Z + 10000000) {
//        //XZ���ʎ��_
//        if (_view_border_slant1_XZ >= 0 && _view_border_slant2_XZ >= 0) {
//            if (_X < _gazeX && _Z < _gazeZ) {
//                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else if (_X > _gazeX && _Z > _gazeZ) {
//                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else {
//                return false;
//            }
//
//        } else if (_view_border_slant1_XZ >= 0 && _view_border_slant2_XZ < 0) {
//            if (_X < _gazeX) {
//                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                }else {
//                    return false;
//                }
//            } else if (_X > _gazeX) {
//                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                }else {
//                    return false;
//                }
//            } else {
//                return false;
//            }
//
//        } else if (_view_border_slant1_XZ < 0 && _view_border_slant2_XZ < 0) {
//            if (_X < _gazeX && _Z > _gazeZ) {
//                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else if (_X > _gazeX && _Z < _gazeZ) {
//                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else {
//                return false;
//            }
//        } else if (_view_border_slant1_XZ < 0 && _view_border_slant2_XZ > 0) {
//            if (_Z < _gazeZ) {
//
//                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//
//            } else if (_Z > _gazeZ) {
//                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
//                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
//                        //XZ����OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else {
//                return false;
//            }
//        } else {
//            return false;
//        }
//
//        //ZY���ʎ��_
//        if (_view_border_slant1_ZY >= 0 && _view_border_slant2_ZY >= 0) {
//            if (_Z < _gazeZ && _Y < _gazeY) {
//                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true; //OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else if (_Z > _gazeZ && _Y > _gazeY) {
//                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true; //OK
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//
//            } else {
//                return false;
//            }
//        } else if (_view_border_slant1_ZY >= 0 && _view_border_slant2_ZY < 0) {
//            if (_Z < _gazeZ) {
//                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true; //ok
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else if (_Y > _gazeY) {
//                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true; //ok
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//
//            } else {
//                return false;
//            }
//        } else if (_view_border_slant1_ZY < 0 && _view_border_slant2_ZY < 0) {
//            if (_Z < _gazeZ && _Y > _gazeY) {
//                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true;
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            } else if (_Z > _gazeZ && _Y < _gazeY) {
//                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true;
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//
//            } else {
//                return false;
//            }
//        } else if (_view_border_slant1_ZY < 0 && _view_border_slant2_ZY > 0) {
//            if (_Z > _gazeZ) {
//                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true;
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//
//            } else if (_Z < _gazeZ) {
//                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
//                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
//                        return true;
//                    } else {
//                        return false;
//                    }
//                } else {
//                    return false;
//                }
//            }else {
//                return false;
//            }
//        } else {
//            return false;
//        }
//    } else {
//        return false;
//    }
//
//}


//test
//int GgafDx9Camera::canView(GgafDx9GeometricActor* pActor, FLOAT radius) {
//    D3DXVECTOR3 pos;
//    pos.x = (float)(1.0 * pActor->_X / LEN_UNIT / PX_UNIT);
//    pos.y = (float)(1.0 * pActor->_Y / LEN_UNIT / PX_UNIT);
//    pos.z = (float)(1.0 * pActor->_Z / LEN_UNIT / PX_UNIT);
//
//    if ( _plnTop.a*pos.x + _plnTop.b*pos.y + _plnTop.c * pos.z + _plnTop.d <= radius) {
//        if ( _plnBottom.a*pos.x + _plnBottom.b*pos.y + _plnBottom.c * pos.z + _plnBottom.d <= radius) {
//            if ( _plnLeft.a*pos.x + _plnLeft.b*pos.y + _plnLeft.c * pos.z + _plnLeft.d <= radius) {
//                if ( _plnRight.a*pos.x + _plnRight.b*pos.y + _plnRight.c * pos.z + _plnRight.d <= radius) {
//                    if ( _plnFront.a*pos.x + _plnFront.b*pos.y + _plnFront.c * pos.z + _plnFront.d <= radius) {
//                        if ( _plnBack.a*pos.x + _plnBack.b*pos.y + _plnBack.c * pos.z + _plnBack.d <= radius) {
//                            //Viewport�͈͓�
//                            return 0;
//                        } else {
//                            //�����ʂ�艜�Ŕ͈͊O
//                            return 6;
//                        }
//                    } else {
//                        //��O���ʂ���O�Ŕ͈͊O
//                        return 5;
//                    }
//                } else {
//                    //�E���ʂ��E�Ŕ͈͊O
//                    return 4;
//                }
//            } else {
//                //�����ʂ�荶�Ŕ͈͊O
//                return 3;
//            }
//        } else {
//            //�����ʂ�艺�Ŕ͈͊O
//            return 2;
//        }
//    } else {
//        //�㕽�ʂ���Ŕ͈͊O
//        return 1;
//    }
//
////     return ( _plnTop.a*pos.x + _plnTop.b*pos.y + _plnTop.c * pos.z + _plnTop.d <= radius)
////         && ( _plnBottom.a*pos.x + _plnBottom.b*pos.y + _plnBottom.c * pos.z + _plnBottom.d <= radius)
////         && ( _plnLeft.a*pos.x + _plnLeft.b*pos.y + _plnLeft.c * pos.z + _plnLeft.d <= radius)
////         && ( _plnRight.a*pos.x + _plnRight.b*pos.y + _plnRight.c * pos.z + _plnRight.d <= radius)
////         && ( _plnFront.a*pos.x + _plnFront.b*pos.y + _plnFront.c * pos.z + _plnFront.d <= radius)
////         && ( _plnBack.a*pos.x + _plnBack.b*pos.y + _plnBack.c * pos.z + _plnBack.d <= radius);
//
//}


GgafDx9Camera::~GgafDx9Camera() {
    //���낢����
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
