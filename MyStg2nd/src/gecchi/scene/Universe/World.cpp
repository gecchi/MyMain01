#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _TRACE_("World::World");
    pCAM->_pos_camera = 0;
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

    pCAM->_pos_camera = 0;
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
        if (pCAM->_pos_camera == 0) {
            pCAM->_pos_camera = 1;
        } else if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
            if (VB::isBeingPressed(VB_RIGHT)) {
                pCAM->_pos_camera = 3;
            } else if (VB::isBeingPressed(VB_LEFT)) {
                pCAM->_pos_camera = 0;
            } else {
                if (pCAM->_Z > GameGlobal::_pMyShip->_Z) {
                    pCAM->_pos_camera = 3;
                } else {
                    pCAM->_pos_camera = 0;
                }
            }
        } else if (pCAM->_pos_camera == 3) {
            pCAM->_pos_camera = 2;
        }
        _frame_pushdown_zmove = _lifeframe;
    }


    if (VB::isReleasedUp(VB_ZMOVE)) {
        if (_frame_pushdown_zmove + 15 > _lifeframe) {
//            if (pCAM->_pos_camera == 0) {
//                pCAM->_pos_camera = 1;
//            } else if (pCAM->_pos_camera == 1) {
//                pCAM->_pos_camera = 0;
//            } else if (pCAM->_pos_camera == 2) {
//                pCAM->_pos_camera = 3;
//            } else if (pCAM->_pos_camera == 3) {
//                pCAM->_pos_camera = 2;
//            }
        } else {
            if (pCAM->_pos_camera == 0) {
                pCAM->_pos_camera = 0;
            } else if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
                if (VB::isBeingPressed(VB_RIGHT)) {
                    pCAM->_pos_camera = 3;
                } else if (VB::isBeingPressed(VB_LEFT)) {
                    pCAM->_pos_camera = 0;
                } else {
                    if (pCAM->_Z > GameGlobal::_pMyShip->_Z) {
                        pCAM->_pos_camera = 3;
                    } else {
                        pCAM->_pos_camera = 0;
                    }
                }
            } else if (pCAM->_pos_camera == 3) {
                pCAM->_pos_camera = 3;
            }
        }

    }





    //�J�����i�n�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    static int dX_CAM, dY_CAM, dZ_CAM;
    //�r���[�|�C���g�i�I�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    static int dX_VP, dY_VP, dZ_VP;
//    startc int X_MyShip_prev = pMYSHIP->_X;
//    startc int Y_MyShip_prev = pMYSHIP->_Y;
//    startc int Z_MyShip_prev = pMYSHIP->_Z;
    static GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
    static int X_screen_left = (int)(-1 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) * LEN_UNIT / 2);
    static int Y_screen_top = (int)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) * LEN_UNIT / 2);
    //if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
    if ( getSubFirst()->isBehaving() ) {
        if (pCAM->_pos_camera == 0) {
            dZ_CAM = (pMYSHIP->_Z - _dZ_camera_init) - pCAM->_Z;
            dX_CAM = (0 - (_dZ_camera_init / 4)) - pCAM->_X;
            dY_CAM = pMYSHIP->_Y - pCAM->_Y;

            if (pCAM->_Y > _lim_VP_top && dY_CAM > 0) {
                dY_CAM = 0;//pMYSHIP->_Y - _lim_VP_top;
            } else if (pCAM->_Y < _lim_VP_bottom && dY_CAM < 0) {
                dY_CAM = 0;//  pMYSHIP->_Y -_lim_VP_bottom;
            }

            dZ_VP = pMYSHIP->_Z - pCAM->_pViewPoint->_Z;
            dX_VP = 0;
            dY_VP = pMYSHIP->_Y - pVP->_Y;

            if (pVP->_Y > _lim_VP_top && dY_VP > 0) {
                dY_VP = 0;// pMYSHIP->_Y - _lim_VP_top;
            } else if (pVP->_Y < _lim_VP_bottom && dY_VP < 0) {
                dY_VP = 0;// pMYSHIP->_Y -_lim_VP_bottom;
            }
        } else if (pCAM->_pos_camera == 1) {
            dX_CAM = (0 - (_dZ_camera_init / 2)) - pCAM->_X;
            dY_CAM = (pMYSHIP->_Y + _dZ_camera_init) - pCAM->_Y;
            dZ_CAM = (pMYSHIP->_Z - (_dZ_camera_init / 128)) - pCAM->_Z;

            if (pCAM->_Z > _lim_VP_zleft && dZ_CAM > 0) {
                dZ_CAM = 0;//pCAM->_Z - _lim_VP_zleft;
            } else if (pCAM->_Z < _lim_VP_zright && dZ_CAM < 0) {
                dZ_CAM = 0;//pCAM->_Z - _lim_VP_zright;
            }

            dX_VP = 0;
            dY_VP = pMYSHIP->_Y - pVP->_Y;
            dZ_VP = pMYSHIP->_Z - pVP->_Z;

            if (pVP->_Z > _lim_VP_zleft && dZ_VP > 0) {
                dZ_VP = 0;//pVP->_Z - _lim_VP_zleft;
            } else if (pVP->_Z < _lim_VP_zright && dZ_VP < 0) {
                dZ_VP = 0;//pVP->_Z - _lim_VP_zright;
            } else {

            }

        } else if (pCAM->_pos_camera == 2) {

            dX_CAM = (0 - (_dZ_camera_init / 2)) - pCAM->_X;
            dY_CAM = (pMYSHIP->_Y + _dZ_camera_init) - pCAM->_Y;
            dZ_CAM = (pMYSHIP->_Z + (_dZ_camera_init / 128)) - pCAM->_Z;

            if (pCAM->_Z > _lim_VP_zleft && dZ_CAM > 0) {
                dZ_CAM = 0;//pCAM->_Z- _lim_VP_zleft;
            } else if (pCAM->_Z < _lim_VP_zright && dZ_CAM < 0) {
                dZ_CAM = 0;//pCAM->_Z - _lim_VP_zright;
            } else {

            }

            dX_VP = 0;
            dY_VP = pMYSHIP->_Y - pVP->_Y;
            dZ_VP = pMYSHIP->_Z - pVP->_Z;

            if (pVP->_Z > _lim_VP_zleft && dZ_VP > 0) {
                dZ_VP = 0;//pVP->_Z - _lim_VP_zleft;
            } else if (pVP->_Z < _lim_VP_zright && dZ_VP < 0) {
                dZ_VP = 0;//pVP->_Z - _lim_VP_zright;
            }

        } else if (pCAM->_pos_camera == 3) {
            dZ_CAM = (pMYSHIP->_Z + _dZ_camera_init) - pCAM->_Z;
            dX_CAM = (0 - (_dZ_camera_init / 4)) - pCAM->_X;
            dY_CAM = pMYSHIP->_Y - pCAM->_Y;

            if (pCAM->_Y > _lim_VP_top && dY_CAM > 0) {
                dY_CAM = 0;//pCAM->_Y - _lim_VP_top;
            } else if (pCAM->_Y < _lim_VP_bottom && dY_CAM < 0) {
                dY_CAM = 0;//pCAM->_Y - _lim_VP_bottom;
            }

            dZ_VP = pMYSHIP->_Z - pVP->_Z;
            dX_VP = 0;
            dY_VP = pMYSHIP->_Y - pVP->_Y;
            if (pVP->_Y > _lim_VP_top && dY_VP > 0) {
                dY_VP = 0;//pVP->_Y - _lim_VP_top;
            } else if (pVP->_Y < _lim_VP_bottom && dY_VP < 0) {
                dY_VP = 0;//pVP->_Y - _lim_VP_bottom;
            } else {

            }
        }



        static int slow_reng_CAM = 30000;
        int speed = (pMYSHIP->_iMoveSpeed + pMYSHIP->_pMover->_veloMove)* 0.99;
        pCAM->_pMover->setVxMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVyMoveVeloRenge(-speed, speed);
        pCAM->_pMover->setVzMoveVeloRenge(-speed, speed);


        if (-slow_reng_CAM < dZ_CAM && dZ_CAM < slow_reng_CAM) {
            pCAM->_pMover->_veloVzMove *= 0.8;
            pCAM->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɉ�鎞
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/1000.0);
            } else {                                                //���ɉ��Ƃ�
                pCAM->_pMover->setVzMoveVeloAcceleration(dZ_CAM/100.0);
            }
        }
        if (-slow_reng_CAM < dX_CAM && dX_CAM < slow_reng_CAM) {
            pCAM->_pMover->_veloVxMove *= 0.9;
            pCAM->_pMover->setVxMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɂɉ�鎞
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/100.0);
            } else {                                                //���ɉ��Ƃ�
                pCAM->_pMover->setVxMoveVeloAcceleration(dX_CAM/1000.0);
            }
        }

        if (-slow_reng_CAM < dY_CAM && dY_CAM < slow_reng_CAM) {
            pCAM->_pMover->_veloVyMove *= 0.9;
            pCAM->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɂɉ�鎞
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/100.0);
            } else {                                                //���ɉ��Ƃ�
                pCAM->_pMover->setVyMoveVeloAcceleration(dY_CAM/1000.0);
            }
        }

//        pCAM->_pMover->setVxMoveVeloRenge(-(dX_CAM - pCAM->_X), dX_CAM - pCAM->_X);
//        pCAM->_pMover->setVyMoveVeloRenge(-(dY_CAM - pCAM->_Y), dY_CAM - pCAM->_Y);
//        pCAM->_pMover->setVzMoveVeloRenge(-(dZ_CAM - pCAM->_Z), dZ_CAM - pCAM->_Z);
        pVP->_pMover->setVxMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVyMoveVeloRenge(-speed, speed);
        pVP->_pMover->setVzMoveVeloRenge(-speed, speed);

        static int slow_reng_VP = 50000;

        if (-slow_reng_VP < dZ_VP && dZ_VP < slow_reng_VP) {
            pVP->_pMover->_veloVzMove *= 0.9;
            pVP->_pMover->setVzMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɉ�鎞
                pVP->_pMover->setVzMoveVeloAcceleration(dZ_VP/1000.0);
            } else {                                                //���ɉ��Ƃ�
                pVP->_pMover->setVzMoveVeloAcceleration(dZ_VP/1000.0);
            }
        }
        if (-slow_reng_VP < dX_VP && dX_VP < slow_reng_VP) {
            pVP->_pMover->_veloVxMove *= 0.9;
            pVP->_pMover->setVxMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɂɉ�鎞
                pVP->_pMover->setVxMoveVeloAcceleration(dX_VP/1000.0);
            } else {                                                //���ɉ��Ƃ�
                pVP->_pMover->setVxMoveVeloAcceleration(dX_VP/1000.0);
            }
        }


        if (-slow_reng_VP < dY_VP && dY_VP < slow_reng_VP) {
            pVP->_pMover->_veloVyMove *= 0.9;
            pVP->_pMover->setVyMoveVeloAcceleration(0);
        } else {
            if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) { //��ɂɉ�鎞
                pVP->_pMover->setVyMoveVeloAcceleration(dY_VP/1000.0);
            } else {                                                //���ɉ��Ƃ�
                pVP->_pMover->setVyMoveVeloAcceleration(dY_VP/1000.0);
            }
        }

        //pCAM->setViewPoint(0, 0, GameGlobal::_pMyShip->_Z);//
        //GameGlobal::_pMyShip->_Z��������Ƃ�����΂����͂�
        //pCAM->setViewPoint(0, 0, 0);//


//        if (pCAM->_pos_camera == 0 || pCAM->_pos_camera == 3) {
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

    //}


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
