#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    _pos_camera = 0;
    _frame_pushdown_zmove = 0;

    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
        _TRACE_("World::initialize()");
    GameScene* pGameScene = NEW GameScene("Game");
    addSubLast(pGameScene);
#ifdef OREDEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "moji");
    getLordActor()->accept(KIND_EFFECT, pDispFpsActor);
#endif
    //�����J�����ʒu
    int speed = pMYSHIP->_iMoveSpeed * 0.99;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    _lim_CAM_top     = GameGlobal::_lim_MyShip_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT / 2);
    _lim_CAM_bottom  = GameGlobal::_lim_MyShip_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT / 2);
    _lim_CAM_front   = GameGlobal::_lim_MyShip_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_CAM_behaind = GameGlobal::_lim_MyShip_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_CAM_zleft   = GameGlobal::_lim_MyShip_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_CAM_zright  = GameGlobal::_lim_MyShip_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);

    _lim_VP_top     = GameGlobal::_lim_MyShip_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT / 2);
    _lim_VP_bottom  = GameGlobal::_lim_MyShip_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT / 2);
    _lim_VP_front   = GameGlobal::_lim_MyShip_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_VP_behaind = GameGlobal::_lim_MyShip_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_VP_zleft   = GameGlobal::_lim_MyShip_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);
    _lim_VP_zright  = GameGlobal::_lim_MyShip_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT / 2);

    _pos_camera = CAM_POS_RIGHT;
    _pos_camera_prev = CAM_POS_RIGHT;

    pCAM->_X = _dZ_camera_init / 10; //�����΂߂߂��猩�Ă�
    pCAM->_Y = 0; //�S�T�x�΂߂��猩��
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMoveAngle(0,0,0);


    pCAM->_pMover->setVxMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVxMoveVelocity(0);
    pCAM->_pMover->setVxMoveVeloAcceleration(0);

    pCAM->_pMover->setVyMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVyMoveVelocity(0);
    pCAM->_pMover->setVyMoveVeloAcceleration(0);

    pCAM->_pMover->setVzMoveVeloRenge(-speed, speed);
    pCAM->_pMover->setVzMoveVelocity(0);
    pCAM->_pMover->setVzMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_X = 0;
    pCAM->_pViewPoint->_Y = 0;
    pCAM->_pViewPoint->_Z = pMYSHIP->_Z;


    pCAM->_pViewPoint->_pMover->setMoveAngle(0,0,0);

    pCAM->_pViewPoint->_pMover->setVxMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVxMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVxMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVyMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVyMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVyMoveVeloAcceleration(0);

    pCAM->_pViewPoint->_pMover->setVzMoveVeloRenge(-speed, speed);
    pCAM->_pViewPoint->_pMover->setVzMoveVelocity(0);
    pCAM->_pViewPoint->_pMover->setVzMoveVeloAcceleration(0);


}



void World::processBehavior() {
    VB::update(); //���͏��X�V


    //TODO:�~�߂Ă�frame�͐i�ށQ�H
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->isBehaving()) {
            _TRACE_("PAUSE!");
//            //�J�������������ݒ�
//            pCAM->_pMover->setMoveAngle(
//                                pCAM->_gazeX,
//                                pCAM->_gazeY,
//                                pCAM->_gazeZ
//                           );

            getSubFirst()->pause();     //�ꎞ��~
        } else {
            _TRACE_("UNPAUSE!");
            getSubFirst()->unpause();   //�ꎞ��~����
        }
    }

    //�J�����ʒu���s�����藈����
    if (VB::isPushedDown(VB_ZMOVE)) {
        int temp_pos_camera_prev = _pos_camera_prev;
        _pos_camera_prev = _pos_camera;
        if (_pos_camera < CAM_POS_TO_BEHIND) { //�w�ʎ��_�ł͂Ȃ��ꍇ�A
            _pos_camera += CAM_POS_TO_BEHIND;  //���ꂼ��̑Ή��w�ʎ��_��
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {//�w�ʎ��_�̏ꍇ
            if (VB::isBeingPressed(VB_RIGHT)) {
                _pos_camera = CAM_POS_RIGHT;
            } else if (VB::isBeingPressed(VB_LEFT)) {
                _pos_camera = CAM_POS_LEFT;
            } else if (VB::isBeingPressed(VB_UP)) {
                _pos_camera = CAM_POS_TOP;
            } else if (VB::isBeingPressed(VB_DOWN)) {
                _pos_camera = CAM_POS_BOTTOM;
            } else {
                _pos_camera = temp_pos_camera_prev;
            }
        }

    }

    static GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;

    //�J�����̈ړ��ڕW�_
    int move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //�J�����̒����_�̈ړ��ڕW�_
    int move_target_X_VP, move_target_Y_VP, move_target_Z_VP;
    //�J�����i�n�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    int dX_CAM, dY_CAM, dZ_CAM;
    //�r���[�|�C���g�i�I�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    int dX_VP, dY_VP, dZ_VP;

    static int Dx = (int)(_dZ_camera_init / 4);
    static int Dd = (int)(_dZ_camera_init / 128);
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    static int Y_screen_top = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
    static int slow_range_CAM = 30000;
    static int slow_range_VP = 50000;

    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
            move_target_X_CAM = -Dx;
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z - _dZ_camera_init;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_LEFT) {
            move_target_X_CAM = -Dx;
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z + _dZ_camera_init;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_TOP) {
            move_target_X_CAM = -Dx * pCAM->_screen_aspect;
            move_target_Y_CAM = pMYSHIP->_Y + _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            move_target_X_CAM = -Dx * pCAM->_screen_aspect;
            move_target_Y_CAM = pMYSHIP->_Y - _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        move_target_X_CAM = X_screen_left - Dx;
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = Dx;
        move_target_Y_VP = pMYSHIP->_Y;
        move_target_Z_VP = pMYSHIP->_Z;
        if (_pos_camera == CAM_POS_BEHIND_RIGHT) {
            move_target_Z_CAM -= Dd;
        } else if (_pos_camera == CAM_POS_BEHIND_LEFT) {
            move_target_Z_CAM += Dd;
        } else if (_pos_camera == CAM_POS_BEHIND_TOP) {
            move_target_Y_CAM -= Dd;
        } else if (_pos_camera > CAM_POS_BEHIND_BOTTOM) {
            move_target_Y_CAM += Dd;
        }
    }
    //�ڕW�n�_�܂ł̊e������
    dX_CAM = move_target_X_CAM - pCAM->_X;
    dY_CAM = move_target_Y_CAM - pCAM->_Y;
    dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    dX_VP = move_target_X_VP - pVP->_X;
    dY_VP = move_target_Y_VP - pVP->_Y;
    dZ_VP = move_target_Z_VP - pVP->_Z;

    if ( getSubFirst()->isBehaving() ) {

        int speed = (pMYSHIP->_iMoveSpeed + pMYSHIP->_pMover->_veloMove)* 0.99;
        pCAM->_pMover->setVxMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVyMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVzMoveVeloRenge(-speed, speed);
        if (-slow_range_CAM < dX_CAM && dX_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVxMove *= 0.8;
            pCAM->_pMover->setVxMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/100.0);//�w��ɉ�鎞
            } else {
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/1000.0);
            }
        }
        if (-slow_range_CAM < dY_CAM && dY_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVyMove *= 0.8;
            pCAM->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/1000.0);//�w��ɉ�鎞
            } else {
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/100.0);
            }
        }
        if (-slow_range_CAM < dZ_CAM && dZ_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVzMove *= 0.8;
            pCAM->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/1000.0);//�w��ɉ�鎞
            } else {
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/100.0);
            }
        }
        pVP->_pMover->setVxMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVyMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVzMoveVeloRenge(-speed, speed);


        if (-slow_range_VP < dX_VP && dX_VP < slow_range_VP) {
            pVP->_pMover->_veloVxMove *= 0.8;
            pVP->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVxMoveVeloAcceleration(dX_VP/1000.0);
        }
        if (-slow_range_VP < dY_VP && dY_VP < slow_range_VP) {
            pVP->_pMover->_veloVyMove *= 0.8;
            pVP->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVyMoveVeloAcceleration(dY_VP/1000.0);
        }
        if (-slow_range_VP < dZ_VP && dZ_VP < slow_range_VP) {
            pVP->_pMover->_veloVzMove *= 0.8;
            pVP->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            pVP->_pMover->setVzMoveVeloAcceleration(dZ_VP/1000.0);
        }

        //        if (_pos_camera == 0 || _pos_camera == 3) {
        //            if (pVP->_Y > _lim_VP_top) {
        //                pVP->_Y = _lim_VP_top;
        //            }
        //            if (pVP->_Y < _lim_VP_bottom ) {
        //                pVP->_Y = _lim_VP_bottom;
        //            }
        //            if (pCAM->_Y > _lim_VP_top) {
        //                pCAM->_Y = _lim_VP_top;
        //            }
        //            if (pCAM->_Y < _lim_VP_bottom ) {
        //                pCAM->_Y = _lim_VP_bottom;
        //            }
        //        } else {
        //            if (pCAM->_Z > _lim_VP_zleft) {
        //                pCAM->_Z = _lim_VP_zleft;
        //            }
        //            if (pCAM->_Z < _lim_VP_zright) {
        //                pCAM->_Z = _lim_VP_zright;
        //            }
        //            if (pVP->_Z > _lim_VP_zleft) {
        //                pVP->_Z = _lim_VP_zleft;
        //            }
        //            if (pVP->_Z < _lim_VP_zright) {
        //                pVP->_Z = _lim_VP_zright;
        //            }
        //        }

        pCAM->_pMover->behave();
        pVP->_pMover->behave();
    }

    //�T�u�V�[�����ꎞ��~���Ă���΁A�J��������ł���B
    if ( getSubFirst()->isBehaving() ) {
        //�X���[
    } else {
        pCAM->_pMover->_move_angle_rz_target_flg = true;
        pCAM->_pMover->_move_angle_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                pCAM->_Y += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                pCAM->_Y -= 2000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                pCAM->_X += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                pCAM->_X -= 2000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                pCAM->_Z += 2000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                pCAM->_Z -= 2000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_T)) {
                pCAM->_pMover->addRzMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_G)) {
                pCAM->_pMover->addRzMoveAngle(-2000);
            } else {
                pCAM->_pMover->addRzMoveAngle(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_H)) {
                pCAM->_pMover->addRyMoveAngle(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_F)) {
                pCAM->_pMover->addRyMoveAngle(-2000);
            } else {
                pCAM->_pMover->addRyMoveAngle(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_U)) {
                pCAM->_pMover->setMoveVelocity(2000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_J)) {
                pCAM->_pMover->setMoveVelocity(-2000);
            } else {
                pCAM->_pMover->setMoveVelocity(0);
            }
        }
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
        pCAM->_pMover->setMoveAngle(0,0,0);
        _TRACE_("GgafDx9Universe Camera=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<")");
    }

//    if ( getSubFirst()->isBehaving() ) {
//        //�X���[
//    } else {
//        //�J�������������ݒ�
//        pCAM->setViewPoint (
//                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
//                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
//                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
//                  );
//        pCAM->_pMover->setMoveAngle(0,0,0);
//    }

}

void World::processJudgement() {
}

World::~World() {
}
