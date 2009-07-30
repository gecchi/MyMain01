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
    _view_border_rad1_XZ =  _view_rad_XZ + _rad_half_fovX; //����1.3�͓K��
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



//    D3DXMatrixOrthoLH(
//        &_vMatrixOrthoProj,
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w �r���[ �{�����[���̕�
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h �r���[ �{�����[���̍���
//        1.0,    //zn �r���[ �{�����[���̍ŏ� z �l (z �߂Ƃ�����)
//        2000.0  //zf �r���[ �{�����[���̍ő� z �l (z ���Ƃ�����)
//    );

}

void GgafDx9Camera::processJudgement() {
    _pVecCamFromPoint->x = (1.0 * _X) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->y = (1.0 * _Y) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->z = (1.0 * _Z) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->x = (1.0 * _gazeX) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0 * _gazeY) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0 * _gazeZ) / LEN_UNIT / PX_UNIT;


    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}



bool GgafDx9Camera::isInTheViewports(int prm_X, int prm_Y, int prm_Z) {
    //���x�D��̂��ߊȈՎ����䔻��
    //fovX*1.3  fovY*1.3 �͂�1.3�́A ����p�ɂ���ĕς��Ȃ���΂����܂���B���̂����肪�K���ł��B
    //�J�������^��t�߂���^���t�߂�����ꍇ�A����сA�^���t�߂���^��t�߂�����ꍇ��
    //����������ł��܂���B

    if ( _Z - 10000000 < prm_Z && prm_Z < _Z + 10000000) {
        //XZ���ʎ��_
        if (_view_border_slant1_XZ >= 0 && _view_border_slant2_XZ >= 0) {
            if (_X < _gazeX && _Z < _gazeZ) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_X > _gazeX && _Z > _gazeZ) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }

        } else if (_view_border_slant1_XZ >= 0 && _view_border_slant2_XZ < 0) {
            if (_X < _gazeX) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                }else {
                    return false;
                }
            } else if (_X > _gazeX) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                }else {
                    return false;
                }
            } else {
                return false;
            }

        } else if (_view_border_slant1_XZ < 0 && _view_border_slant2_XZ < 0) {
            if (_X < _gazeX && _Z > _gazeZ) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_X > _gazeX && _Z < _gazeZ) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (_view_border_slant1_XZ < 0 && _view_border_slant2_XZ > 0) {
            if (_Z < _gazeZ) {

                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else if (_Z > _gazeZ) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ����OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }

        //ZY���ʎ��_
        if (_view_border_slant1_ZY >= 0 && _view_border_slant2_ZY >= 0) {
            if (_Z < _gazeZ && _Y < _gazeY) {
                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true; //OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_Z > _gazeZ && _Y > _gazeY) {
                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true; //OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else if (_view_border_slant1_ZY >= 0 && _view_border_slant2_ZY < 0) {
            if (_Z < _gazeZ) {
                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true; //ok
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_Y > _gazeY) {
                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true; //ok
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else if (_view_border_slant1_ZY < 0 && _view_border_slant2_ZY < 0) {
            if (_Z < _gazeZ && _Y > _gazeY) {
                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_Z > _gazeZ && _Y < _gazeY) {
                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else if (_view_border_slant1_ZY < 0 && _view_border_slant2_ZY > 0) {
            if (_Z > _gazeZ) {
                if (prm_Y < _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y < _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else if (_Z < _gazeZ) {
                if (prm_Y > _view_border_slant1_ZY*prm_Z + _view_border_intercept1_ZY) {
                    if (prm_Y > _view_border_slant2_ZY*prm_Z + _view_border_intercept2_ZY) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }else {
                return false;
            }
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
