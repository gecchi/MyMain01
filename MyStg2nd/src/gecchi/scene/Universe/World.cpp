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


    pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVxMvVelo(0);
    pCAM->_pMover->setVxMvAcce(0);

    pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVyMvVelo(0);
    pCAM->_pMover->setVyMvAcce(0);

    pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pMover->setVzMvVelo(0);
    pCAM->_pMover->setVzMvAcce(0);

    pCAM->_pViewPoint->_X = 0;
    pCAM->_pViewPoint->_Y = 0;
    pCAM->_pViewPoint->_Z = pMYSHIP->_Z;


    pCAM->_pViewPoint->_pMover->setMvAng(0,0,0);

    pCAM->_pViewPoint->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVxMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVxMvAcce(0);

    pCAM->_pViewPoint->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVyMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVyMvAcce(0);

    pCAM->_pViewPoint->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
    pCAM->_pViewPoint->_pMover->setVzMvVelo(0);
    pCAM->_pViewPoint->_pMover->setVzMvAcce(0);


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

    static int Dx = (int)(_dZ_camera_init / 2);
    static int Dd = (int)(_dZ_camera_init / 100);
    static int slow_range_CAM = 50000;
    static int slow_range02_CAM = slow_range_CAM * 1.1;
    static int slow_range_VP = 50000;
    static int slow_range02_VP = slow_range_VP * 1.1;
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
        if (move_target_Y_CAM > _lim_CAM_top + _correction_height) {
            //(_lim_CAM_top/2) ��
            //move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init/2);
            //�ɂ��߂Â�������
            move_target_Y_CAM = _lim_CAM_top + _correction_height;
        }
        if (move_target_Y_CAM < _lim_CAM_bottom - _correction_height) {
            move_target_Y_CAM = _lim_CAM_bottom - _correction_height;
        }
        if (move_target_Z_CAM > _lim_CAM_zleft + _correction_width) {
            move_target_Z_CAM = _lim_CAM_zleft + _correction_width;
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
        if (move_target_Y_VP > _lim_VP_top + _correction_height) {
            move_target_Y_VP = _lim_VP_top + _correction_height;
        }
        if (move_target_Y_VP < _lim_VP_bottom - _correction_height) {
            move_target_Y_VP = _lim_VP_bottom - _correction_height;
        }
        if (move_target_Z_VP > _lim_VP_zleft + _correction_width) {
            move_target_Z_VP = _lim_VP_zleft + _correction_width;
        }
        if (move_target_Z_VP < _lim_VP_zright + _correction_width) {
            move_target_Z_VP = _lim_VP_zright + _correction_width;
        }
    }


    //�ڕW�n�_�܂ł̊e������
    dX_CAM = move_target_X_CAM - pCAM->_X;
    dY_CAM = move_target_Y_CAM - pCAM->_Y;
    dZ_CAM = move_target_Z_CAM - pCAM->_Z;
    dX_VP = move_target_X_VP - pVP->_X;
    dY_VP = move_target_Y_VP - pVP->_Y;
    dZ_VP = move_target_Z_VP - pVP->_Z;

    if ( getSubFirst()->canBehave() ) {

        int cam_MvVeloRenge;//�J�����ړ��X�s�[�h
        int moveway_num = 0; //���@�ړ�������
        if (VB::isBeingPressed(VB_LEFT)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_UP)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_RIGHT)) {
            moveway_num++;
        }
        if (VB::isBeingPressed(VB_DOWN)) {
            moveway_num++;
        }
        if (moveway_num >= 2) {
            cam_MvVeloRenge = pMYSHIP->_iMoveSpeed*NANAME +
                                  ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
                                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
                                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)*1.5  ); //�J�����ړ��X�s�[�h�i���@�΂߈ړ����j

        } else {
            cam_MvVeloRenge = pMYSHIP->_iMoveSpeed +
                                    ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
                                      GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
                                      GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)*1.5  ); //�J�����ړ��X�s�[�h�i�W���j
        }

//                +
//                  ( GgafDx9Util::abs(pMYSHIP->_pMover->_veloVxMv) +
//                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVyMv) +
//                    GgafDx9Util::abs(pMYSHIP->_pMover->_veloVzMv)
//                  )
//                 ) * 0.7;//�ǂ����邩????0.7; //0.7�̈Ӗ��� 1/��2 ���킸���ɏ�����
                          //����͎��@���΂߈ړ����J�������킸���ɒǂ����Ȃ��悤�ɂ��邽��
//        if (GgafDx9Util::abs(dX_CAM) > slow_range_CAM*1.2 ||
//            GgafDx9Util::abs(dY_CAM) > slow_range_CAM*1.2 ||
//            GgafDx9Util::abs(dZ_CAM) > slow_range_CAM*1.2) {
//            cam_MvVeloRenge = cam_MvVeloRenge * 2;
//        }


        //�J�������X���[�͈́i������ƍL�߁j���Ƃ����łȂ����̏���
        if (-slow_range02_CAM > dX_CAM && dX_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_CAM > dY_CAM && dY_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_CAM > dZ_CAM && dZ_CAM > slow_range02_CAM) {
            pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pCAM->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }


        //�J�������X���[�͈͎��Ƃ����łȂ����̏���
        static double acc_rate = 500.0;
        if (-slow_range_CAM < dX_CAM && dX_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVxMv *= 0.9;
            pCAM->_pMover->setVxMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVxMvAcce(dX_CAM/acc_rate);//�w��ɉ�鎞
            } else {
                pCAM->_pMover->setVxMvAcce(dX_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dY_CAM && dY_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVyMv *= 0.9;
            pCAM->_pMover->setVyMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVyMvAcce(dY_CAM/acc_rate);//�w��ɉ�鎞
            } else {
                pCAM->_pMover->setVyMvAcce(dY_CAM/acc_rate);
            }
        }
        if (-slow_range_CAM < dZ_CAM && dZ_CAM < slow_range_CAM) {
            pCAM->_pMover->_veloVzMv *= 0.9;
            pCAM->_pMover->setVzMvAcce(0);
        } else {
            if (_pos_camera > CAM_POS_TO_BEHIND) {
                pCAM->_pMover->setVzMvAcce(dZ_CAM/acc_rate);//�w��ɉ�鎞
            } else {

                pCAM->_pMover->setVzMvAcce(dZ_CAM/acc_rate);
            }
        }






        if (-slow_range02_VP > dX_VP && dX_VP > slow_range02_VP) {
            pVP->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVxMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_VP > dY_VP && dY_VP > slow_range02_VP) {
            pVP->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVyMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }
        if (-slow_range02_VP > dZ_VP && dZ_VP > slow_range02_VP) {
            pVP->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge*10, cam_MvVeloRenge*10);
        } else {
            pVP->_pMover->setVzMvVeloRenge(-cam_MvVeloRenge, cam_MvVeloRenge);
        }

        if (-slow_range_VP < dX_VP && dX_VP < slow_range_VP) {
            pVP->_pMover->_veloVxMv *= 0.9;
            pVP->_pMover->setVxMvAcce(0);
        } else {
            pVP->_pMover->setVxMvAcce(dX_VP/acc_rate);
        }
        if (-slow_range_VP < dY_VP && dY_VP < slow_range_VP) {
            pVP->_pMover->_veloVyMv *= 0.9;
            pVP->_pMover->setVyMvAcce(0);
        } else {
            pVP->_pMover->setVyMvAcce(dY_VP/acc_rate);
        }
        if (-slow_range_VP < dZ_VP && dZ_VP < slow_range_VP) {
            pVP->_pMover->_veloVzMv *= 0.9;
            pVP->_pMover->setVzMvAcce(0);
        } else {
            pVP->_pMover->setVzMvAcce(dZ_VP/acc_rate);
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



