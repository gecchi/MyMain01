#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

CommonScene::CommonScene(const char* prm_name) : DefaultScene(prm_name) {
    GameGlobal::_pSceneCommon = this;

    { //MyShip
        _pMyShip = NEW MyShip("MYSHIP");
        _pMyShip->inactivateImmediately(); //配下に仮登録のアクター発送者とかあるし
        getLordActor()->addSubGroup(KIND_MY_BODY_NOMAL, _pMyShip);
    }


    { //EnemyShot001
        _pDispatcher_EnemyShots001 = NEW GgafActorDispatcher("TAMAS001");
        EnemyCeresShot001* pEnemyShot;
        for (int i = 0; i < 36*7; i++) { //ストック256個
            pEnemyShot = NEW EnemyCeresShot001("EnemyCeresShot001");
            pEnemyShot->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EnemyShots001->addSubLast(pEnemyShot);
        }
        getLordActor()->addSubGroup(_pDispatcher_EnemyShots001);
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion001 = NEW GgafActorDispatcher("RotExplo001");
        EffectExplosion001* pEffectExplosion;
        for (int i = 0; i < 256; i++) { //ストック100個
            pEffectExplosion = NEW EffectExplosion001("EffectExplosion001");
            pEffectExplosion->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectExplosion001->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion001);
    }

    { //Effect EffectExplosion001
        _pDispatcher_EffectExplosion003 = NEW GgafActorDispatcher("RotExplo003");
        EffectExplosion003* pEffectExplosion;
        for (int i = 0; i < 50; i++) { //ストック100個
            pEffectExplosion = NEW EffectExplosion003("EffectExplosion003");
            pEffectExplosion->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectExplosion003->addSubLast(pEffectExplosion);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectExplosion003);
    }



    { //Effect EffectTurbo002 ターボ噴射
        _pDispatcher_EffectTurbo002 = NEW GgafActorDispatcher("RotExplo002");
        EffectTurbo002* pEffectTurbo;
        for (int i = 0; i < 10; i++) { //ストック100個
            pEffectTurbo = NEW EffectTurbo002("EffectTurbo002");
            pEffectTurbo->inactivateTreeImmediately(); //最初非表示
            _pDispatcher_EffectTurbo002->addSubLast(pEffectTurbo);
        }
        getLordActor()->addSubGroup(_pDispatcher_EffectTurbo002);
    }

    {
        _pDispatcher_LaserChipDispatcher = NEW GgafActorDispatcher("LCDD");
        LaserChipDispatcher* pLaserChipDispatcher;
        EnemyAstraeaLaserChip002* pChip;
        for (int nLaser = 0; nLaser < 27; nLaser++) {
            stringstream name;
            name <<  "LaserChipDispatcher["<<nLaser<<"]";
            pLaserChipDispatcher = NEW LaserChipDispatcher(name.str().c_str());
            for (int nChip = 0; nChip < 50; nChip++) {
                stringstream name;
                name <<  "EnemyAstraeaLaserChip002["<<nLaser<<"]["<<nChip<<"]";
                pChip = NEW EnemyAstraeaLaserChip002(name.str().c_str());
                pChip->inactivateImmediately();
                pLaserChipDispatcher->addSubLast(pChip);
            }
            pLaserChipDispatcher->inactivateImmediately();
            _pDispatcher_LaserChipDispatcher->addSubLast(pLaserChipDispatcher);
        }
        getLordActor()->addSubGroup(_pDispatcher_LaserChipDispatcher);
    }


}

void CommonScene::initialize() {
    //初期カメラZ位置
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
    //初期カメラ移動範囲制限
    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
    _lim_CAM_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_CAM_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_CAM_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;

    _lim_VP_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_VP_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_VP_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)*revise;
    //画面背後用範囲差分
    //背後のZ座標は_dZ_camera_init/2
    _correction_width = 0;//(GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)/4;
    _correction_height = 0;//(GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2)/4;

    _pos_camera = CAM_POS_RIGHT;
    _frame_pushdown_zmove = 0;
    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    pCAM->_X = 0;
    pCAM->_Y = 0;
    pCAM->_Z = 0;
    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMvAng(0,0,0);

    _cam_velo_renge = 30000;
    pCAM->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCAM->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pCAM->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
//    pCAM->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
//    pCAM->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
//    pCAM->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);

    pVP->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
//    pVP->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
//    pVP->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
//    pVP->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);

    _stop_renge = 100000;
    _angXY_nowCamUp = ANGLE90;
    _stop_dZ = 0;
    _stop_dY = 0;
}

void CommonScene::processBehavior() {

    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    //カメラ位置を行ったり来たり
    if (VB_PLAY->isPushedDown(VB_VIEW)) {
        _TRACE_("VB_VIEW!! now _pos_camera="<<_pos_camera);
        if (_pos_camera < CAM_POS_TO_BEHIND) { //背面視点ではない場合、
            _pos_camera += CAM_POS_TO_BEHIND;  //それぞれの対応背面視点へ
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {//背面視点の場合
            //方向入力により新たな視点へ
            if (VB_PLAY->isBeingPressed(VB_RIGHT)) {
                _pos_camera = CAM_POS_LEFT;
            } else if (VB_PLAY->isBeingPressed(VB_LEFT)) {
                _pos_camera = CAM_POS_RIGHT;
            } else if (VB_PLAY->isBeingPressed(VB_UP)) {
                _pos_camera = CAM_POS_BOTTOM;
            } else if (VB_PLAY->isBeingPressed(VB_DOWN)) {
                _pos_camera = CAM_POS_TOP;
            } else {
                //方向未入力の場合、元の視点へ
                _pos_camera -= CAM_POS_TO_BEHIND;
            }
        }
        _TRACE_("VB_VIEW!!  -> _pos_camera="<<_pos_camera);
    }

    //カメラの移動目標点
    int move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //カメラの注視点の移動目標点
    int move_target_X_VP, move_target_Y_VP, move_target_Z_VP;

    angle move_target_XY_CAM_UP;
    //カメラ（始点）の目標地点までの距離（座標差分）
    int dX_CAM, dY_CAM, dZ_CAM;
    //ビューポイント（終点）の目標地点までの距離（座標差分）
    int dX_VP, dY_VP, dZ_VP;

    static int Dx = (int)((GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)/4*2);
    static int Ddx_hw = (int)((GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2) - (GGAFDX9_PROPERTY(GAME_SPACE_HEIGHT)*LEN_UNIT/2));
    static int Dd = 30000;
    //int Dx = (int)((GGAFDX9_PROPERTY(GAME_SPACE_WIDTH)*LEN_UNIT/2)/2);

    //カメラと視点の移動目標設定
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
//            move_target_X_CAM = 0;
//            move_target_Y_CAM = 0;
//            move_target_Z_CAM = -_dZ_camera_init;
//            move_target_X_VP = 0;
//            move_target_Y_VP = 0;
//            move_target_Z_VP = 0;

            move_target_X_CAM = -Dx + (-_pMyShip->_X-180000)*2; //-180000 はカメラ移動位置、*2はパン具合。調整を繰り返せ
            if (-Dx > move_target_X_CAM) {
                move_target_X_CAM = -Dx;
            } else if (move_target_X_CAM > Dx/2) {
                move_target_X_CAM = Dx/2;
            }
            move_target_Y_CAM = _pMyShip->_Y;
            move_target_Z_CAM = _pMyShip->_Z - _dZ_camera_init;
            move_target_X_VP = Dx - (-_pMyShip->_X-180000)*2;
            if (Dx < move_target_X_VP) {
                move_target_X_VP = Dx;
            } else if ( move_target_X_VP < -Dx/2) {
                move_target_X_VP = -Dx/2;
            }
            move_target_Y_VP = _pMyShip->_Y;
            move_target_Z_VP = _pMyShip->_Z;

            move_target_XY_CAM_UP = ANGLE90;
        } else if (_pos_camera == CAM_POS_LEFT) {
            move_target_X_CAM = -Dx + (-_pMyShip->_X-180000)*2;
            if (-Dx > move_target_X_CAM) {
                move_target_X_CAM = -Dx;
            } else if (move_target_X_CAM > Dx/2) {
                move_target_X_CAM = Dx/2;
            }
            move_target_Y_CAM = _pMyShip->_Y;
            move_target_Z_CAM = _pMyShip->_Z + _dZ_camera_init;
            move_target_X_VP = Dx - (-_pMyShip->_X-180000)*2;
            if (Dx < move_target_X_VP) {
                move_target_X_VP = Dx;
            } else if ( move_target_X_VP < -Dx/2) {
                move_target_X_VP = -Dx/2;
            }
            move_target_Y_VP = _pMyShip->_Y;
            move_target_Z_VP = _pMyShip->_Z;
            move_target_XY_CAM_UP = ANGLE90;
        } else if (_pos_camera == CAM_POS_TOP) {
            move_target_X_CAM = -Dx - Ddx_hw + (-_pMyShip->_X-125000)*2;
            if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                move_target_X_CAM = -Dx - Ddx_hw;
            } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                move_target_X_CAM = (Dx + Ddx_hw)/2;
            }
            move_target_Y_CAM = _pMyShip->_Y + _dZ_camera_init + Ddx_hw;
            move_target_Z_CAM = _pMyShip->_Z;
            move_target_X_VP = Dx + Ddx_hw - (-_pMyShip->_X-125000)*2;
            if (Dx + Ddx_hw < move_target_X_VP) {
                move_target_X_VP = Dx + Ddx_hw;
            } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                move_target_X_VP = -(Dx + Ddx_hw)/2;
            }
            move_target_Y_VP = _pMyShip->_Y;
            move_target_Z_VP = _pMyShip->_Z;
            if (pCAM->_X < pVP->_X) {
                move_target_XY_CAM_UP = ANGLE45;
            } else {
                move_target_XY_CAM_UP = ANGLE315;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            move_target_X_CAM = -Dx - Ddx_hw + (-_pMyShip->_X-125000)*2;
            if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                move_target_X_CAM = -Dx - Ddx_hw;
            } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                move_target_X_CAM = (Dx + Ddx_hw)/2;
            }
            move_target_Y_CAM = _pMyShip->_Y - _dZ_camera_init - Ddx_hw;
            move_target_Z_CAM = _pMyShip->_Z;
            move_target_X_VP = Dx + Ddx_hw - (-_pMyShip->_X-125000)*2;
            if (Dx + Ddx_hw < move_target_X_VP) {
                move_target_X_VP = Dx + Ddx_hw;
            } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                move_target_X_VP = -(Dx + Ddx_hw)/2;
            }
            move_target_Y_VP = _pMyShip->_Y;
            move_target_Z_VP = _pMyShip->_Z;
            if (pCAM->_X < pVP->_X) {
                move_target_XY_CAM_UP = ANGLE135;
            } else {
                move_target_XY_CAM_UP = ANGLE225;
            }


        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        move_target_X_CAM = _pMyShip->_X - (_dZ_camera_init*0.6);
        move_target_Y_CAM = _pMyShip->_Y;
        move_target_Z_CAM = _pMyShip->_Z;
        move_target_X_VP = _pMyShip->_X + (_dZ_camera_init*6);
        move_target_Y_VP = _pMyShip->_Y;
        move_target_Z_VP = _pMyShip->_Z;
        move_target_XY_CAM_UP = ANGLE90;
//        if (_pos_camera == CAM_POS_BEHIND_RIGHT) {
//            move_target_Z_CAM -= Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_LEFT) {
//            move_target_Z_CAM += Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_TOP) {
//            move_target_Y_CAM += Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_BOTTOM) {
//            move_target_Y_CAM -= Dd;
//        }
    } else {
        throwGgafCriticalException("World::processBehavior() 不正な_pos_camera="<<_pos_camera);
    }
    GeoElement* pGeoMyShip = _pMyShip->_pRing_GeoHistory->get();
    GeoElement* pGeoMyShip_prev= _pMyShip->_pRing_GeoHistory->getPrev();
    _stop_dZ += (pGeoMyShip_prev->_Z - pGeoMyShip->_Z)*0.1;
    _stop_dY += (pGeoMyShip_prev->_Y - pGeoMyShip->_Y)*0.1;
    move_target_Z_CAM += _stop_dZ;
    move_target_Y_CAM += _stop_dY;

    //各軸最大速度
    int cam_velo_renge;

    if (VB_PLAY->isBeingPressed(VB_VIEW)) {
        cam_velo_renge = _cam_velo_renge / 100; //おしっぱはゆっくり
    } else {
        cam_velo_renge = _cam_velo_renge;
    }
    //離した場合
    if (VB_PLAY->isReleasedUp(VB_VIEW)) {
        if (VB_PLAY->isPushedUp(VB_VIEW, 20)) {
            //チョン押しの場合
        } else {
            //長押し
            if (_pos_camera < CAM_POS_TO_BEHIND) { //背面視点ではない場合、
                _pos_camera += CAM_POS_TO_BEHIND;  //それぞれの対応背面視点へ
            } else if (_pos_camera > CAM_POS_TO_BEHIND) {//背面視点の場合
                _pos_camera -= CAM_POS_TO_BEHIND;
            }

        }
    }


    pCAM->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCAM->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCAM->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラと視点の移動目標を自機移動範囲を考慮して制限
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == CAM_POS_LEFT) {
            if (move_target_Y_CAM > _lim_CAM_top) {
                move_target_Y_CAM = _lim_CAM_top;
            }
            if (move_target_Y_CAM < _lim_CAM_bottom ) {
                move_target_Y_CAM = _lim_CAM_bottom;
            }
        } else if (_pos_camera == CAM_POS_TOP) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            if (move_target_Z_CAM > _lim_CAM_zleft) {
                move_target_Z_CAM = _lim_CAM_zleft;
            }
            if (move_target_Z_CAM < _lim_CAM_zright) {
                move_target_Z_CAM = _lim_CAM_zright;
            }
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        if (move_target_Y_CAM > _lim_CAM_top - _correction_height) {
            move_target_Y_CAM = _lim_CAM_top - _correction_height;
        }
        if (move_target_Y_CAM < _lim_CAM_bottom + _correction_height) {
            move_target_Y_CAM = _lim_CAM_bottom + _correction_height;
        }
        if (move_target_Z_CAM > _lim_CAM_zleft - _correction_width) {
            move_target_Z_CAM = _lim_CAM_zleft - _correction_width;
        }
        if (move_target_Z_CAM < _lim_CAM_zright + _correction_width) {
            move_target_Z_CAM = _lim_CAM_zright + _correction_width;
        }
    }
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == CAM_POS_LEFT) {
            if (move_target_Y_VP > _lim_VP_top) {
                move_target_Y_VP = _lim_VP_top;
            }
            if (move_target_Y_VP < _lim_VP_bottom ) {
                move_target_Y_VP = _lim_VP_bottom;
            }
        } else if (_pos_camera == CAM_POS_TOP) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            if (move_target_Z_VP > _lim_VP_zleft) {
                move_target_Z_VP = _lim_VP_zleft;
            }
            if (move_target_Z_VP < _lim_VP_zright) {
                move_target_Z_VP = _lim_VP_zright;
            }
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        if (move_target_Y_VP > _lim_VP_top - _correction_height) {
            move_target_Y_VP = _lim_VP_top - _correction_height;
        }
        if (move_target_Y_VP < _lim_VP_bottom + _correction_height) {
            move_target_Y_VP = _lim_VP_bottom + _correction_height;
        }
        if (move_target_Z_VP > _lim_VP_zleft - _correction_width) {
            move_target_Z_VP = _lim_VP_zleft - _correction_width;
        }
        if (move_target_Z_VP < _lim_VP_zright + _correction_width) {
            move_target_Z_VP = _lim_VP_zright + _correction_width;
        }
    }
    dX_CAM = move_target_X_CAM - pCAM->_X;
    dY_CAM = move_target_Y_CAM - pCAM->_Y;
    dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    dX_VP = move_target_X_VP - pVP->_X;
    dY_VP = move_target_Y_VP - pVP->_Y;
    dZ_VP = move_target_Z_VP - pVP->_Z;
    //if ( getSubFirst()->canBehave() ) {
        velo veloVxRenge = 3000;
        velo veloVyRenge = 3000;
        velo veloVzRenge = 3000;
        if (_pos_camera == CAM_POS_BEHIND_RIGHT || _pos_camera == CAM_POS_BEHIND_LEFT) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.5;
        } else if (_pos_camera == CAM_POS_BEHIND_TOP || _pos_camera == CAM_POS_BEHIND_BOTTOM) {
            //ややX軸移動を早くする
            veloVxRenge *= 1.5;
        } else if (_pos_camera == CAM_POS_RIGHT || _pos_camera == CAM_POS_LEFT) {
            ////ややX軸移動を早くする
            //veloVxRenge *= 1.5;
        } else if (_pos_camera == CAM_POS_TOP || _pos_camera == CAM_POS_BOTTOM) {
            ////ややY軸移動を早くする
            //veloVyRenge *= 1.5;
        }
        velo last_CAM_veloVxMv = pCAM->_pMover->_veloVxMv;
        velo  new_CAM_veloVxMv = _pMyShip->_iMoveSpeed*(dX_CAM*1.0 / _stop_renge);
        if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
            pCAM->_pMover->setVxMvVelo(new_CAM_veloVxMv);
        } else {
            if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
                pCAM->_pMover->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
            } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
                pCAM->_pMover->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
            }
        }
        velo last_VP_veloVxMv = pVP->_pMover->_veloVxMv;
        velo  new_VP_veloVxMv = _pMyShip->_iMoveSpeed*(dX_VP*1.0 / _stop_renge);
        if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
            pVP->_pMover->setVxMvVelo(new_VP_veloVxMv);
        } else {
            if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
                pVP->_pMover->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
            } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
                pVP->_pMover->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
            }
        }

        velo last_CAM_veloVyMv = pCAM->_pMover->_veloVyMv;
        velo  new_CAM_veloVyMv = _pMyShip->_iMoveSpeed*(dY_CAM*1.0 / _stop_renge);
        if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
            pCAM->_pMover->setVyMvVelo(new_CAM_veloVyMv);
        } else {
            if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
                pCAM->_pMover->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
            } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
                pCAM->_pMover->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
            }
        }
        velo last_VP_veloVyMv = pVP->_pMover->_veloVyMv;
        velo  new_VP_veloVyMv = _pMyShip->_iMoveSpeed*(dY_VP*1.0 / _stop_renge);
        if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
            pVP->_pMover->setVyMvVelo(new_VP_veloVyMv);
        } else {
            if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
                pVP->_pMover->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
            } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
                pVP->_pMover->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
            }
        }

        velo last_CAM_veloVzMv = pCAM->_pMover->_veloVzMv;
        velo  new_CAM_veloVzMv = _pMyShip->_iMoveSpeed*(dZ_CAM*1.0 / _stop_renge);
        if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
            pCAM->_pMover->setVzMvVelo(new_CAM_veloVzMv);
        } else {
            if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
                pCAM->_pMover->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
            } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
                pCAM->_pMover->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
            }
        }
        velo last_VP_veloVzMv = pVP->_pMover->_veloVzMv;
        velo  new_VP_veloVzMv = _pMyShip->_iMoveSpeed*(dZ_VP*1.0 / _stop_renge);
        if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
            pVP->_pMover->setVzMvVelo(new_VP_veloVzMv);
        } else {
            if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
                pVP->_pMover->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
            } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
                pVP->_pMover->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
            }
        }

        //カメラのUPを計算
        if (_angXY_nowCamUp != move_target_XY_CAM_UP) {
            //_TRACE_("_angXY_nowCamUp="<<_angXY_nowCamUp<<" / move_target_XY_CAM_UP="<<move_target_XY_CAM_UP);
            angle da = GgafDx9Util::getDiffAng(_angXY_nowCamUp, move_target_XY_CAM_UP);
            if (-1000 < da && da < 1000) {
                _angXY_nowCamUp = move_target_XY_CAM_UP;
            } else {
                _angXY_nowCamUp += (2000 * sgn(da));
            }
            _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
            pCAM->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
            pCAM->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
            pCAM->_pVecCamUp->z = 0.0f;
        }

        pCAM->_pMover->behave();
        pVP->_pMover->behave();
    //}
}

CommonScene::~CommonScene() {
}
