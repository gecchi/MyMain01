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
#ifdef MY_DEBUG
    DispFpsActor* pDispFpsActor = NEW DispFpsActor("FPS_STRING", "28/moji");
    getLordActor()->addSubGroup(KIND_EFFECT, pDispFpsActor);
#endif
    //�����J�����ʒu
    int cam_MvVeloRenge = pMYSHIP->_iMoveSpeed * 0.99;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;

    _lim_CAM_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_CAM_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_CAM_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _lim_VP_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2);
    _lim_VP_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);
    _lim_VP_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2);

    _correction_width = (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/2;
    _correction_height = (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)/2;

    _pos_camera = CAM_POS_RIGHT;

    pCAM->_X = _dZ_camera_init / 10; //�����΂߂߂��猩�Ă�
    pCAM->_Y = 0; //�S�T�x�΂߂��猩��
    pCAM->_Z = -_dZ_camera_init;

    pCAM->setViewPoint(0,0,0);
    pCAM->_pMover->setMvAng(0,0,0);

    pVP->_X = 0;
    pVP->_Y = 0;
    pVP->_Z = pMYSHIP->_Z;


    _renge = 80000;
    pCAM->_pMover->setVxMvVeloRenge(-_renge, _renge);
    pCAM->_pMover->setVyMvVeloRenge(-_renge, _renge);
    pCAM->_pMover->setVzMvVeloRenge(-_renge, _renge);
    pCAM->_pMover->setVxMvAcceRenge(-_renge / 40, _renge / 40);
    pCAM->_pMover->setVyMvAcceRenge(-_renge / 40, _renge / 40);
    pCAM->_pMover->setVzMvAcceRenge(-_renge / 40, _renge / 40);

    pVP->_pMover->setVxMvVeloRenge(-_renge, _renge);
    pVP->_pMover->setVyMvVeloRenge(-_renge, _renge);
    pVP->_pMover->setVzMvVeloRenge(-_renge, _renge);
    pVP->_pMover->setVxMvAcceRenge(-_renge / 40, _renge / 40);
    pVP->_pMover->setVyMvAcceRenge(-_renge / 40, _renge / 40);
    pVP->_pMover->setVzMvAcceRenge(-_renge / 40, _renge / 40);

}



void World::processBehavior() {
    VB::update(); //���͏��X�V


    //TODO:�~�߂Ă�frame�͐i�ށQ�H
    if (VB::isPushedDown(VB_PAUSE)) {
        if (getSubFirst()->canBehave()) {
            _TRACE_("PAUSE!");
//            //�J�������������ݒ�
//            pCAM->_pMover->setMvAng(
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
        _TRACE_("VB_ZMOVE!! now _pos_camera="<<_pos_camera);
        if (_pos_camera < CAM_POS_TO_BEHIND) { //�w�ʎ��_�ł͂Ȃ��ꍇ�A
            _pos_camera += CAM_POS_TO_BEHIND;  //���ꂼ��̑Ή��w�ʎ��_��
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {//�w�ʎ��_�̏ꍇ
            //�������͂ɂ��V���Ȏ��_��
            if (VB::isBeingPressed(VB_RIGHT)) {
                _pos_camera = CAM_POS_LEFT;
            } else if (VB::isBeingPressed(VB_LEFT)) {
                _pos_camera = CAM_POS_RIGHT;
            } else if (VB::isBeingPressed(VB_UP)) {
                _pos_camera = CAM_POS_BOTTOM;
            } else if (VB::isBeingPressed(VB_DOWN)) {
                _pos_camera = CAM_POS_TOP;
            } else {
                //���������͂̏ꍇ�A���̎��_��
                _pos_camera -= CAM_POS_TO_BEHIND;
            }
        }
        _TRACE_("VB_ZMOVE!!  -> _pos_camera="<<_pos_camera);

    }

    //�J�����̈ړ��ڕW�_
    int move_target_X_CAM, move_target_Y_CAM, move_target_Z_CAM;
    //�J�����̒����_�̈ړ��ڕW�_
    int move_target_X_VP, move_target_Y_VP, move_target_Z_VP;
    //�J�����i�n�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    int dX_CAM, dY_CAM, dZ_CAM;
    //�r���[�|�C���g�i�I�_�j�̖ڕW�n�_�܂ł̋����i���W�����j
    int dX_VP, dY_VP, dZ_VP;

    static int Dx = (int)((GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/2);
    static int Dd = (int)(_dZ_camera_init / 100);
    //�J�����Ǝ��_�̈ړ��ڕW�ݒ�
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
        move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init/2);
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = pMYSHIP->_X + (_dZ_camera_init);
        move_target_Y_VP = pMYSHIP->_Y;
        move_target_Z_VP = pMYSHIP->_Z;
//        if (_pos_camera == CAM_POS_BEHIND_RIGHT) {
//            move_target_Z_CAM -= Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_LEFT) {
//            move_target_Z_CAM += Dd;
//        } else if (_pos_camera == CAM_POS_BEHIND_TOP) {
//            move_target_Y_CAM -= Dd;
//        } else if (_pos_camera > CAM_POS_BEHIND_BOTTOM) {
//            move_target_Y_CAM += Dd;
//        }
    }
    //�J�����Ǝ��_�̈ړ��ڕW�␳
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


    //�ڕW�n�_�܂ł̊e������
    dX_CAM = move_target_X_CAM - (pCAM->_X + pCAM->_pMover->_veloVxMv*2);
    dY_CAM = move_target_Y_CAM - (pCAM->_Y + pCAM->_pMover->_veloVyMv*2);
    dZ_CAM = move_target_Z_CAM - (pCAM->_Z + pCAM->_pMover->_veloVzMv*2);
    dX_VP = move_target_X_VP - (pVP->_X + pVP->_pMover->_veloVxMv*2);
    dY_VP = move_target_Y_VP - (pVP->_Y + pVP->_pMover->_veloVyMv*2);
    dZ_VP = move_target_Z_VP - (pVP->_Z + pVP->_pMover->_veloVzMv*2);

    //_TRACE_("TARGETXYZ("<<move_target_X_CAM<<","<<move_target_Y_CAM<<","<<move_target_Z_CAM<<")");
    //_TRACE_("dXYZ("<<dX_CAM<<","<<dY_CAM<<","<<dZ_CAM<<")");


    if ( getSubFirst()->canBehave() ) {

        int stop_renge = 30000;
        if (-stop_renge < dX_CAM && dX_CAM < stop_renge) {
            pCAM->_pMover->setVxMvAcce(pCAM->_pMover->_acceVxMv * 0.5);
            pCAM->_pMover->setVxMvVelo(pCAM->_pMover->_veloVxMv * 0.5);
        } else {
            pCAM->_pMover->setVxMvAcce(dX_CAM);
        }


        if (-stop_renge < dY_CAM && dY_CAM < stop_renge) {
            pCAM->_pMover->setVyMvAcce(pCAM->_pMover->_acceVyMv * 0.5);
            pCAM->_pMover->setVyMvVelo(pCAM->_pMover->_veloVyMv * 0.5);
        } else {
            pCAM->_pMover->setVyMvAcce(dY_CAM);
        }

        if (-stop_renge < dZ_CAM && dZ_CAM < stop_renge) {
            pCAM->_pMover->setVzMvAcce(pCAM->_pMover->_acceVzMv * 0.5);
            pCAM->_pMover->setVzMvVelo(pCAM->_pMover->_veloVzMv * 0.5);
        } else {
            pCAM->_pMover->setVzMvAcce(dZ_CAM);
        }




        if (-stop_renge < dX_VP && dX_VP < stop_renge) {
            pVP->_pMover->setVxMvAcce(pVP->_pMover->_acceVxMv * 0.5);
            pVP->_pMover->setVxMvVelo(pVP->_pMover->_veloVxMv * 0.5);
        } else {
            pVP->_pMover->setVxMvAcce(dX_VP);
        }

        if (-stop_renge < dY_VP && dY_VP < stop_renge) {
            pVP->_pMover->setVyMvAcce(pVP->_pMover->_acceVyMv * 0.5);
            pVP->_pMover->setVyMvVelo(pVP->_pMover->_veloVyMv * 0.5);
        } else {
            pVP->_pMover->setVyMvAcce(dY_VP);
        }

        if (-stop_renge < dZ_VP && dZ_VP < stop_renge) {
            pVP->_pMover->setVzMvAcce(pVP->_pMover->_acceVzMv * 0.5);
            pVP->_pMover->setVzMvVelo(pVP->_pMover->_veloVzMv * 0.5);
        } else {
            pVP->_pMover->setVzMvAcce(dZ_VP);
        }
 


		int kyuchaku = pMYSHIP->_iMoveSpeed/4;
        int camveloZ = pCAM->_pMover->_veloVzMv;
        int vpveloZ = pVP->_pMover->_veloVzMv;
		if (pMYSHIP->_iMoveSpeed-kyuchaku < camveloZ && camveloZ < pMYSHIP->_iMoveSpeed+kyuchaku) {
        	pCAM->_pMover->_veloVzMv = pMYSHIP->_iMoveSpeed;
		} else if (-pMYSHIP->_iMoveSpeed-kyuchaku < camveloZ && camveloZ < -pMYSHIP->_iMoveSpeed+kyuchaku) {
			pCAM->_pMover->_veloVzMv = -pMYSHIP->_iMoveSpeed;
		} 
		if (pMYSHIP->_iMoveSpeed-kyuchaku < vpveloZ && vpveloZ < pMYSHIP->_iMoveSpeed+kyuchaku) {
        	pVP->_pMover->_veloVzMv = pMYSHIP->_iMoveSpeed;
		} else if (-pMYSHIP->_iMoveSpeed-kyuchaku < vpveloZ && vpveloZ < -pMYSHIP->_iMoveSpeed+kyuchaku) {
			pVP->_pMover->_veloVzMv = -pMYSHIP->_iMoveSpeed;
		} 


        pCAM->_pMover->behave();
        pVP->_pMover->behave();
        //_TRACE_("XYZ=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<") -> ("<<pVP->_X<<","<<pVP->_Y<<","<<pVP->_Z<<")");
        //_TRACE_("veloXYZ=("<<pCAM->_pMover->_veloVxMv<<","<<pCAM->_pMover->_veloVyMv<<","<<pCAM->_pMover->_veloVzMv<<") -> ("<<pVP->_pMover->_veloVxMv<<","<<pVP->_pMover->_veloVyMv<<","<<pVP->_pMover->_veloVzMv<<")");
        //_TRACE_("acceXYZ=("<<pCAM->_pMover->_acceVxMv<<","<<pCAM->_pMover->_acceVyMv<<","<<pCAM->_pMover->_acceVzMv<<") -> ("<<pVP->_pMover->_acceVxMv<<","<<pVP->_pMover->_acceVyMv<<","<<pVP->_pMover->_acceVzMv<<")");

    }

    //�T�u�V�[�����ꎞ��~���Ă���΁A�J��������ł���B
    if ( getSubFirst()->canBehave() ) {
        //�X���[
    } else {
        pCAM->_pMover->_mv_ang_rz_target_flg = true;
        pCAM->_pMover->_mv_ang_ry_target_flg = true;

        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                pCAM->_Y += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                pCAM->_Y -= 4000;
            } else {

            }

            if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                pCAM->_X += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                pCAM->_X -= 4000;
            } else {
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                pCAM->_Z += 4000;
            } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                pCAM->_Z -= 4000;
            } else {
            }

        } else {
            if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
                pCAM->_pMover->addRzMvAng(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
                pCAM->_pMover->addRzMvAng(-4000);
            } else {
                pCAM->_pMover->addRzMvAng(0);
            }

            if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
                pCAM->_pMover->addRyMvAng(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
                pCAM->_pMover->addRyMvAng(-4000);
            } else {
                pCAM->_pMover->addRyMvAng(0);
            }
            if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
                pCAM->_pMover->setMvVelo(4000);
            } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
                pCAM->_pMover->setMvVelo(-4000);
            } else {
                pCAM->_pMover->setMvVelo(0);
            }
        }
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_O)) {
        pCAM->_pMover->setMvAng(0,0,0);
        _TRACE_("GgafDx9Universe Camera=("<<pCAM->_X<<","<<pCAM->_Y<<","<<pCAM->_Z<<")");
    }

//    if ( getSubFirst()->canBehave() ) {
//        //�X���[
//    } else {
//        //�J�������������ݒ�
//        pCAM->setViewPoint (
//                   pCAM->_X + (pCAM->_pMover->_vX * LEN_UNIT * PX_UNIT),
//                   pCAM->_Y + (pCAM->_pMover->_vY * LEN_UNIT * PX_UNIT),
//                   pCAM->_Z + (pCAM->_pMover->_vZ * LEN_UNIT * PX_UNIT)
//                  );
//        pCAM->_pMover->setMvAng(0,0,0);
//    }

}

void World::processJudgement() {
}

World::~World() {
}



