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
    int cam_MvVeloRange = pMYSHIP->_iMoveSpeed * 0.99;
    _dZ_camera_init = -1 * pCAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
    //�����J�����ړ��͈͐���
    float revise = 0.8; //�΂߂��猩��̂ŕ␳�l���|����B1.0�̏ꍇ�͌��_����Ńh���s�V���B����͔��������J��Ԃ���
    _lim_CAM_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_CAM_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_CAM_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_CAM_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;

    _lim_VP_top     = MyShip::_lim_top     - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_VP_bottom  = MyShip::_lim_bottom  + (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)*revise;
    _lim_VP_front   = MyShip::_lim_front   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_behaind = MyShip::_lim_behaind + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_zleft   = MyShip::_lim_zleft   - (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;
    _lim_VP_zright  = MyShip::_lim_zright  + (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)*revise;

    _correction_width = (GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/2;
    _correction_height = (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2)/2;

    _pos_camera = CAM_POS_RIGHT;

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
    pCAM->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
    pCAM->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
    pCAM->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);

    pVP->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
    pVP->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
    pVP->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
    pVP->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);

    _stop_renge = 70000;
}



void World::processBehavior() {
    VB::update(); //���͏��X�V

    GgafDx9CameraViewPoint* pVP = pCAM->_pViewPoint;
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

    static int Dx = (int)((GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/5*2);
    static int Ddx_hw = (int)((GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2) - (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)*LEN_UNIT/2));
    //int Dx = (int)((GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)*LEN_UNIT/2)/2);

    //�J�����Ǝ��_�̈ړ��ڕW�ݒ�
    if (_pos_camera < CAM_POS_TO_BEHIND) {
        if (_pos_camera == CAM_POS_RIGHT) {
//            move_target_X_CAM = 0;
//            move_target_Y_CAM = 0;
//            move_target_Z_CAM = -_dZ_camera_init;
//            move_target_X_VP = 0;
//            move_target_Y_VP = 0;
//            move_target_Z_VP = 0;

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
            move_target_X_CAM = -Dx - Ddx_hw;
            move_target_Y_CAM = pMYSHIP->_Y + _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx - Ddx_hw;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        } else if (_pos_camera == CAM_POS_BOTTOM) {
            move_target_X_CAM = -Dx - Ddx_hw;
            move_target_Y_CAM = pMYSHIP->_Y - _dZ_camera_init;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = Dx - Ddx_hw;
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
        }
    } else if (_pos_camera > CAM_POS_TO_BEHIND) {
        move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init/2);
        move_target_Y_CAM = pMYSHIP->_Y;
        move_target_Z_CAM = pMYSHIP->_Z;
        move_target_X_VP = pMYSHIP->_X + (_dZ_camera_init*5);
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
    } else {
        throwGgafCriticalException("World::processBehavior() �s����_pos_camera="<<_pos_camera);
    }
    if (VB::isBeingPressed(VB_ZMOVE)) {
        int cam_slow_velo_renge = _cam_velo_renge / 100;
        pCAM->_pMover->forceVxMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pCAM->_pMover->forceVyMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pCAM->_pMover->forceVzMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pCAM->_pMover->forceVxMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
        pCAM->_pMover->forceVyMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
        pCAM->_pMover->forceVzMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
        pVP->_pMover->forceVxMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pVP->_pMover->forceVyMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pVP->_pMover->forceVzMvVeloRange(-cam_slow_velo_renge, cam_slow_velo_renge);
        pVP->_pMover->forceVxMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
        pVP->_pMover->forceVyMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
        pVP->_pMover->forceVzMvAcceRange(-cam_slow_velo_renge / 50, cam_slow_velo_renge / 50);
    } else {
        pCAM->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pCAM->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pCAM->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pCAM->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
        pCAM->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
        pCAM->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
        pVP->_pMover->forceVxMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pVP->_pMover->forceVyMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pVP->_pMover->forceVzMvVeloRange(-_cam_velo_renge, _cam_velo_renge);
        pVP->_pMover->forceVxMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
        pVP->_pMover->forceVyMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
        pVP->_pMover->forceVzMvAcceRange(-_cam_velo_renge / 50, _cam_velo_renge / 50);
    }
    //�J�����Ǝ��_�̈ړ��ڕW�����@�ړ��͈͂��l�����Đ���
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
    //���x���R�����Z����̂́A�Ԃ��Ԃ�񂵂Ȃ悤�ɂ��邽��
    dX_CAM = move_target_X_CAM - (pCAM->_X + pCAM->_pMover->_veloVxMv*3);
    dY_CAM = move_target_Y_CAM - (pCAM->_Y + pCAM->_pMover->_veloVyMv*3);
    dZ_CAM = move_target_Z_CAM - (pCAM->_Z + pCAM->_pMover->_veloVzMv*3);
    dX_VP = move_target_X_VP - (pVP->_X + pVP->_pMover->_veloVxMv*3);
    dY_VP = move_target_Y_VP - (pVP->_Y + pVP->_pMover->_veloVyMv*3);
    dZ_VP = move_target_Z_VP - (pVP->_Z + pVP->_pMover->_veloVzMv*3);

    if ( getSubFirst()->canBehave() ) {
        if (-_stop_renge < dX_CAM && dX_CAM < _stop_renge) {
            pCAM->_pMover->setVxMvAcce(0);
            pCAM->_pMover->setVxMvVelo(pCAM->_pMover->_veloVxMv * 0.8);
        } else {
            pCAM->_pMover->setVxMvAcce(dX_CAM);
        }
        if (-_stop_renge < dY_CAM && dY_CAM < _stop_renge) {
            pCAM->_pMover->setVyMvAcce(0);
            pCAM->_pMover->setVyMvVelo(pCAM->_pMover->_veloVyMv * 0.8);
        } else {
            pCAM->_pMover->setVyMvAcce(dY_CAM);
        }
        if (-_stop_renge < dZ_CAM && dZ_CAM < _stop_renge) {
            pCAM->_pMover->setVzMvAcce(0);
            pCAM->_pMover->setVzMvVelo(pCAM->_pMover->_veloVzMv * 0.8);
        } else {
            pCAM->_pMover->setVzMvAcce(dZ_CAM);
        }
        if (-_stop_renge < dX_VP && dX_VP < _stop_renge) {
            pVP->_pMover->setVxMvAcce(0);
            pVP->_pMover->setVxMvVelo(pVP->_pMover->_veloVxMv * 0.8);
        } else {
            pVP->_pMover->setVxMvAcce(dX_VP);
        }
        if (-_stop_renge < dY_VP && dY_VP < _stop_renge) {
            pVP->_pMover->setVyMvAcce(0);
            pVP->_pMover->setVyMvVelo(pVP->_pMover->_veloVyMv * 0.8);
        } else {
            pVP->_pMover->setVyMvAcce(dY_VP);
        }
        if (-_stop_renge < dZ_VP && dZ_VP < _stop_renge) {
            pVP->_pMover->setVzMvAcce(0);
            pVP->_pMover->setVzMvVelo(pVP->_pMover->_veloVzMv * 0.8);
        } else {
            pVP->_pMover->setVzMvAcce(dZ_VP);
        }

        //���@�ʏ�ړ��ɋz��
        if (pMYSHIP->_iMoveVelo != 0) {
            //�J�������u���u���k����̂ŁA�k���Ȃ������������Ă���B
            //TODO:�����Ɨǂ����@�����邩������Ȃ��B��ōl���悤�B
            int kyuchaku = pMYSHIP->_iMoveVelo/2; //�z���͈�
            int camveloX = pCAM->_pMover->_veloVxMv;
            int vpveloX = pVP->_pMover->_veloVxMv;
            if (camveloX > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= camveloX && camveloX < pMYSHIP->_iMoveVelo+kyuchaku) {
                pCAM->_X += ((pCAM->_X + pMYSHIP->_iMoveVelo) - (pCAM->_X + camveloX + pCAM->_pMover->_acceVxMv));
            } else if (camveloX < 0 &&  -(pMYSHIP->_iMoveVelo)-kyuchaku <= camveloX && camveloX < -(pMYSHIP->_iMoveVelo)+kyuchaku) {
                pCAM->_X += ((pCAM->_X - pMYSHIP->_iMoveVelo) - (pCAM->_X + camveloX + pCAM->_pMover->_acceVxMv));
            }
            if (vpveloX > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= vpveloX && vpveloX < pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_X += ((pVP->_X + pMYSHIP->_iMoveVelo) - (pVP->_X + vpveloX + pVP->_pMover->_acceVxMv));
            } else if (vpveloX < 0 && -pMYSHIP->_iMoveVelo-kyuchaku <= vpveloX && vpveloX < -pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_X += ((pVP->_X - pMYSHIP->_iMoveVelo) - (pVP->_X + vpveloX + pVP->_pMover->_acceVxMv));
            }

            int camveloY = pCAM->_pMover->_veloVyMv;
            int vpveloY = pVP->_pMover->_veloVyMv;
            if (camveloY > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= camveloY && camveloY < pMYSHIP->_iMoveVelo+kyuchaku) {
                pCAM->_Y += ((pCAM->_Y + pMYSHIP->_iMoveVelo) - (pCAM->_Y + camveloY + pCAM->_pMover->_acceVyMv));
            } else if (camveloY < 0 &&  -(pMYSHIP->_iMoveVelo)-kyuchaku <= camveloY && camveloY < -(pMYSHIP->_iMoveVelo)+kyuchaku) {
                pCAM->_Y += ((pCAM->_Y - pMYSHIP->_iMoveVelo) - (pCAM->_Y + camveloY + pCAM->_pMover->_acceVyMv));
            }
            if (vpveloY > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= vpveloY && vpveloY < pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_Y += ((pVP->_Y + pMYSHIP->_iMoveVelo) - (pVP->_Y + vpveloY + pVP->_pMover->_acceVyMv));
            } else if (vpveloY < 0 && -pMYSHIP->_iMoveVelo-kyuchaku <= vpveloY && vpveloY < -pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_Y += ((pVP->_Y - pMYSHIP->_iMoveVelo) - (pVP->_Y + vpveloY + pVP->_pMover->_acceVyMv));
            }

            int camveloZ = pCAM->_pMover->_veloVzMv;
            int vpveloZ = pVP->_pMover->_veloVzMv;
            if (camveloZ > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= camveloZ && camveloZ < pMYSHIP->_iMoveVelo+kyuchaku) {
                pCAM->_Z += ((pCAM->_Z + pMYSHIP->_iMoveVelo) - (pCAM->_Z + camveloZ + pCAM->_pMover->_acceVzMv));
            } else if (camveloZ < 0 &&  -(pMYSHIP->_iMoveVelo)-kyuchaku <= camveloZ && camveloZ < -(pMYSHIP->_iMoveVelo)+kyuchaku) {
                pCAM->_Z += ((pCAM->_Z - pMYSHIP->_iMoveVelo) - (pCAM->_Z + camveloZ + pCAM->_pMover->_acceVzMv));
            }
            if (vpveloZ > 0 && pMYSHIP->_iMoveVelo-kyuchaku <= vpveloZ && vpveloZ < pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_Z += ((pVP->_Z + pMYSHIP->_iMoveVelo) - (pVP->_Z + vpveloZ + pVP->_pMover->_acceVzMv));
            } else if (vpveloZ < 0 && -pMYSHIP->_iMoveVelo-kyuchaku <= vpveloZ && vpveloZ < -pMYSHIP->_iMoveVelo+kyuchaku) {
                pVP->_Z += ((pVP->_Z - pMYSHIP->_iMoveVelo) - (pVP->_Z + vpveloZ + pVP->_pMover->_acceVzMv));
            }
        }


        pCAM->_pMover->behave();
        pVP->_pMover->behave();
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



