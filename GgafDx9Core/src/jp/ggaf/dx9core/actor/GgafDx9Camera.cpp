#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Camera::GgafDx9Camera(const char* prm_name, float prm_rad_fovX) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "GgafDx9Camera";
    _pMover = NEW GgafDx9GeometryMover(this);
    //全ての基準はfovXから考える
    _rad_fovX = prm_rad_fovX;
    //半分を保持
    _rad_half_fovX = _rad_fovX / 2.0;
    //画面アスペクト比(w/h)
    _screen_aspect = (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    //fovXとアスペクト比からfovYを計算して求める
    double xzRatio = tan( _rad_fovX/2 );
    double yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0;
    //半分を保持
    _rad_half_fovY = _rad_fovY / 2.0;
    //tan値も保持
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //初期カメラ位置は視点(0,0,Z)、注視点(0,0,0)
    //Zは、キャラがZ=0のXY平面で丁度キャラが値ピクセル幅と一致するような所にカメラを引く
    _cameraZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("カメラの位置(0,0,"<<_cameraZ<<")");
//    _view_border_slant1_XZ = sin((PI - _rad_fovX) / 2) / cos((PI - _rad_fovX) / 2);
//    _view_border_slant2_XZ = -_view_border_slant1_XZ;
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ); //位置
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向

    // VIEW変換行列作成
    D3DXMatrixLookAtLH(
       &_vMatrixView,         // pOut [in, out] 演算結果である D3DXMATRIX 構造体へのポインタ。
        _pVecCamFromPoint,    // pEye [in] 視点を定義する D3DXVECTOR3 構造体へのポインタ。この値は、平行移動に使用される。
        _pVecCamLookatPoint,  // pAt  [in] カメラの注視対象を定義する D3DXVECTOR3 構造体へのポインタ。
        _pVecCamUp            // pUp  [in] カレント ワールドの上方、一般には [0, 1, 0] を定義する D3DXVECTOR3 構造体へのポインタ。
    );

    // 射影変換行列作成（３Ｄ→平面）
    D3DXMatrixPerspectiveFovLH(
            &_vMatrixProj,
            _rad_fovY, //y方向視野角ラディアン(0～π)
            _screen_aspect, //アスペクト比  640×480 の場合  640/480
            1.0, //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            2000.0 //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
            //(FLOAT)(-1.0*dCam*4)
            //(-1.0*fCam)-30,
            //(-1.0*fCam)+30
    );
    /*
     //左手座標系正射影
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
    //傾き (y2-y1)/(x2-x1)   = tanθ
    //切片 (x2y1-x1y2)/(x2-x1)

    //ZY
    //傾き (y2-y1)/(z2-z1)   = tanθ
    //切片 (z2y1-z1y2)/(z2-z1)

    //XZ
    //傾き (z2-z1)/(x2-x1)   = tanθ
    //切片 (x2z1-x1z2)/(x2-x1)
    //クリップボーダー計算
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
    _view_border_rad1_XZ =  _view_rad_XZ + _rad_half_fovX; //この1.3は適当
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
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w ビュー ボリュームの幅
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h ビュー ボリュームの高さ
//        1.0,    //zn ビュー ボリュームの最小 z 値 (z 近ともいう)
//        2000.0  //zf ビュー ボリュームの最大 z 値 (z 遠ともいう)
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
    //速度優先のため簡易視錐台判定
    //fovX*1.3  fovY*1.3 はの1.3は、 視野角によって変えなければいけません。このあたりが適当です。
    //カメラが真上付近から真下付近を見る場合、および、真下付近から真上付近を見る場合は
    //正しく判定できません。

    if ( _Z - 10000000 < prm_Z && prm_Z < _Z + 10000000) {
        //XZ平面視点
        if (_view_border_slant1_XZ >= 0 && _view_border_slant2_XZ >= 0) {
            if (_X < _gazeX && _Z < _gazeZ) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z > _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ平面OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_X > _gazeX && _Z > _gazeZ) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ平面OK
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
                        //XZ平面OK
                    } else {
                        return false;
                    }
                }else {
                    return false;
                }
            } else if (_X > _gazeX) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ平面OK
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
                        //XZ平面OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (_X > _gazeX && _Z < _gazeZ) {
                if (prm_Z > _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ平面OK
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
                        //XZ平面OK
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }

            } else if (_Z > _gazeZ) {
                if (prm_Z < _view_border_slant1_XZ*prm_X + _view_border_intercept1_XZ) {
                    if (prm_Z < _view_border_slant2_XZ*prm_X + _view_border_intercept2_XZ) {
                        //XZ平面OK
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

        //ZY平面視点
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
    //いろいろ解放
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
