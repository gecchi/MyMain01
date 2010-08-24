#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define ORDER_ID_CREATESTAGE01SCENE 11
#define ORDER_ID_CREATESTAGE02SCENE 12
#define ORDER_ID_CREATESTAGE03SCENE 13
#define ORDER_ID_CREATESTAGE04SCENE 14
#define ORDER_ID_CREATESTAGE05SCENE 15
GameMainScene* GameMainScene::_pGameMainScene = NULL;

GameMainScene::GameMainScene(const char* prm_name) : DefaultScene(prm_name) {
    _pos_camera = 0;
    _frame_pushdown_zmove = 0;


    _pFont16_SCORE = NEW LabelGecchi16Font("SCORE");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_SCORE);
    _pFont16_RANK = NEW LabelGecchi16Font("RANK");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_RANK);
    _pFont16_STAMINA = NEW LabelGecchi16Font("STAMINA");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont16_STAMINA);
    _pFont1601 = NEW LabelGecchi16Font("STR01");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont1601);
    _pFont1602 = NEW LabelGecchi16Font("STR02");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont1602);
    _pFont8_JIKI_X = NEW LabelGecchi8Font("JIKI_X");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_X);
    _pFont8_JIKI_Y = NEW LabelGecchi8Font("JIKI_Y");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_Y);
    _pFont8_JIKI_Z = NEW LabelGecchi8Font("JIKI_Z");
    getLordActor()->addSubGroup(KIND_EFFECT, _pFont8_JIKI_Z);
    _pScene_Stage01 = NULL;
    _pScene_Stage02 = NULL;
    _pScene_Stage03 = NULL;
    _pScene_Stage04 = NULL;
    _pScene_Stage05 = NULL;

    _pSceneMainCannnel = NULL;
    setProgress(GAMEMAIN_PROG_INIT);

    GameMainScene::_pGameMainScene = this;
}
void GameMainScene::reset() {
    setProgress(GAMEMAIN_PROG_INIT);
}
void GameMainScene::ready(int prm_stage) {
    _stage = prm_stage;
    _is_ready_stage = true;
    _frame_ready_stage = 0;
    switch (prm_stage) {
        case 1:
            orderSceneToFactory(11, Stage01Scene, "Stage01");
            break;
        case 2:
            orderSceneToFactory(11, Stage02Scene, "Stage02");
            break;
        case 3:
            orderSceneToFactory(11, Stage03Scene, "Stage03");
            break;
        case 4:
            orderSceneToFactory(11, Stage04Scene, "Stage04");
            break;
        case 5:
            orderSceneToFactory(11, Stage05Scene, "Stage05");
            break;
        default:
            break;
    }
}

void GameMainScene::initialize() {
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

    _stop_renge = 60000;
    _angXY_nowCamUp = ANGLE90;
}


void GameMainScene::processBehavior() {
    if (getProgress() == GAMEMAIN_PROG_INIT) {
        setProgress(GAMEMAIN_PROG_BEGIN);
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_BEGIN)) {
        _pFont1601->update(300, 300, "GAME_MAIN_SCENE BEGIN");
        _pFont1602->update(300, 350, "DESTOROY ALL THEM!!");
        GgafScene* pCommonScene = GameGlobal::_pSceneCommon->extract();
		if (_pSceneMainCannnel) {
			//2面目以降はこのタイミングで前ステージをend
			_TRACE_("_pSceneMainCannnel="<<_pSceneMainCannnel->getName()<<" end()");
			_pSceneMainCannnel->end(30*60);
		}
		_pSceneMainCannnel = (StageScene*)obtainSceneFromFactory(11);
		addSubLast(_pSceneMainCannnel); //ステージシーン追加
        _pSceneMainCannnel->addSubLast(pCommonScene);         // 共通シーンを配下に移動
        _is_ready_stage = false;
        _frame_Begin = 0;


    } else if (getProgress() == GAMEMAIN_PROG_BEGIN) {
        //活動ループ
        _frame_Begin++;

        if (_frame_Begin == 180) {
            setProgress(GAMEMAIN_PROG_PLAY); //
        }
    }

    if (onChangeProgressAt(GAMEMAIN_PROG_PLAY)) {
        _pFont1601->update(300, 300, "");
        _pFont1602->update(300, 350, "");

    } else if (getProgress() == GAMEMAIN_PROG_PLAY) {
        //活動ループ
        if (_is_ready_stage) {
            _frame_ready_stage++;
            if (_frame_ready_stage == 20*60) {
                _TRACE_("新ステージCOMEING!!");
                setProgress(GAMEMAIN_PROG_BEGIN);
            }
        }

    }

    //SCORE表示
    sprintf(_buf, "SCORE %07u", _SCORE_);
    _pFont16_SCORE->update(550, 1, _buf);
    sprintf(_buf, "RANK %.7f", _RANK_);
    _pFont16_RANK->update(550, 20, _buf);
    sprintf(_buf, "STAMINA %7d", pMYSHIP->_pStatus->get(STAT_Stamina));
    _pFont16_STAMINA->update(550, 40, _buf);

    sprintf(_buf, "X:%8d", pMYSHIP->_X);
    _pFont8_JIKI_X->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*3-1, _buf);
    sprintf(_buf, "Y:%8d", pMYSHIP->_Y);
    _pFont8_JIKI_Y->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*2-1, _buf);
    sprintf(_buf, "Z:%8d", pMYSHIP->_Z);
    _pFont8_JIKI_Z->update(1, GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) - 8*1-1, _buf);
    //カメラワーク関連

    if (getProgress() == GAMEMAIN_PROG_PLAY) {

        //一時停止
        if (VB_PLAY->isReleasedUp(VB_PAUSE)) {
            _TRACE_("PAUSE!");
            pGOD->setVB(VB_UI);  //入力はＵＩに切り替え
            pause();     //自身配下を一時停止する
                         //一時停止解除はGameSceneで行われる
        }

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

                move_target_X_CAM = -Dx + (-pMYSHIP->_X-180000)*2; //-180000 はカメラ移動位置、*2はパン具合。調整を繰り返せ
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = pMYSHIP->_Y;
                move_target_Z_CAM = pMYSHIP->_Z - _dZ_camera_init;
                move_target_X_VP = Dx - (-pMYSHIP->_X-180000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = pMYSHIP->_Y;
                move_target_Z_VP = pMYSHIP->_Z;

                move_target_XY_CAM_UP = ANGLE90;
            } else if (_pos_camera == CAM_POS_LEFT) {
                move_target_X_CAM = -Dx + (-pMYSHIP->_X-180000)*2;
                if (-Dx > move_target_X_CAM) {
                    move_target_X_CAM = -Dx;
                } else if (move_target_X_CAM > Dx/2) {
                    move_target_X_CAM = Dx/2;
                }
                move_target_Y_CAM = pMYSHIP->_Y;
                move_target_Z_CAM = pMYSHIP->_Z + _dZ_camera_init;
                move_target_X_VP = Dx - (-pMYSHIP->_X-180000)*2;
                if (Dx < move_target_X_VP) {
                    move_target_X_VP = Dx;
                } else if ( move_target_X_VP < -Dx/2) {
                    move_target_X_VP = -Dx/2;
                }
                move_target_Y_VP = pMYSHIP->_Y;
                move_target_Z_VP = pMYSHIP->_Z;
                move_target_XY_CAM_UP = ANGLE90;
            } else if (_pos_camera == CAM_POS_TOP) {
                move_target_X_CAM = -Dx - Ddx_hw + (-pMYSHIP->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = pMYSHIP->_Y + _dZ_camera_init + Ddx_hw;
                move_target_Z_CAM = pMYSHIP->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-pMYSHIP->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = pMYSHIP->_Y;
                move_target_Z_VP = pMYSHIP->_Z;
                if (pCAM->_X < pVP->_X) {
                    move_target_XY_CAM_UP = ANGLE45;
                } else {
                    move_target_XY_CAM_UP = ANGLE315;
                }
            } else if (_pos_camera == CAM_POS_BOTTOM) {
                move_target_X_CAM = -Dx - Ddx_hw + (-pMYSHIP->_X-125000)*2;
                if ((-Dx - Ddx_hw) > move_target_X_CAM) {
                    move_target_X_CAM = -Dx - Ddx_hw;
                } else if (move_target_X_CAM > (Dx + Ddx_hw)/2) {
                    move_target_X_CAM = (Dx + Ddx_hw)/2;
                }
                move_target_Y_CAM = pMYSHIP->_Y - _dZ_camera_init - Ddx_hw;
                move_target_Z_CAM = pMYSHIP->_Z;
                move_target_X_VP = Dx + Ddx_hw - (-pMYSHIP->_X-125000)*2;
                if (Dx + Ddx_hw < move_target_X_VP) {
                    move_target_X_VP = Dx + Ddx_hw;
                } else if ( move_target_X_VP < -(Dx + Ddx_hw)/2) {
                    move_target_X_VP = -(Dx + Ddx_hw)/2;
                }
                move_target_Y_VP = pMYSHIP->_Y;
                move_target_Z_VP = pMYSHIP->_Z;
                if (pCAM->_X < pVP->_X) {
                    move_target_XY_CAM_UP = ANGLE135;
                } else {
                    move_target_XY_CAM_UP = ANGLE225;
                }


            }
        } else if (_pos_camera > CAM_POS_TO_BEHIND) {
            move_target_X_CAM = pMYSHIP->_X - (_dZ_camera_init*0.6);
            move_target_Y_CAM = pMYSHIP->_Y;
            move_target_Z_CAM = pMYSHIP->_Z;
            move_target_X_VP = pMYSHIP->_X + (_dZ_camera_init*6);
            move_target_Y_VP = pMYSHIP->_Y;
            move_target_Z_VP = pMYSHIP->_Z;
            move_target_XY_CAM_UP = ANGLE90;
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
            throwGgafCriticalException("World::processBehavior() 不正な_pos_camera="<<_pos_camera);
        }
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
        pCAM->_pMover->forceVxMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);
        pCAM->_pMover->forceVyMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);
        pCAM->_pMover->forceVzMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);
        pVP->_pMover->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
        pVP->_pMover->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
        pVP->_pMover->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
        pVP->_pMover->forceVxMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);
        pVP->_pMover->forceVyMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);
        pVP->_pMover->forceVzMvAcceRange(-cam_velo_renge / 40, cam_velo_renge / 40);

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


        //目標地点までの各軸距離
        //速度＊３を加算するのは、ぶるんぶるんしなようにするため
        dX_CAM = move_target_X_CAM - (pCAM->_X + pCAM->_pMover->_veloVxMv*3);
        dY_CAM = move_target_Y_CAM - (pCAM->_Y + pCAM->_pMover->_veloVyMv*3);
        dZ_CAM = move_target_Z_CAM - (pCAM->_Z + pCAM->_pMover->_veloVzMv*3);
        dX_VP = move_target_X_VP - (pVP->_X + pVP->_pMover->_veloVxMv*3);
        dY_VP = move_target_Y_VP - (pVP->_Y + pVP->_pMover->_veloVyMv*3);
        dZ_VP = move_target_Z_VP - (pVP->_Z + pVP->_pMover->_veloVzMv*3);

        if ( getSubFirst()->canBehave() ) {
            if (_pos_camera == CAM_POS_RIGHT || _pos_camera == CAM_POS_LEFT ||
                _pos_camera == CAM_POS_TOP   || _pos_camera == CAM_POS_BOTTOM  ) {
                //背後視点以外は前後（X軸）は遊びを少なくする
                if (-_stop_renge/4 < dX_CAM && dX_CAM < _stop_renge/4) {
                    pCAM->_pMover->setVxMvAcce(0);
                    pCAM->_pMover->setVxMvVelo(pCAM->_pMover->_veloVxMv * 0.6);
                } else {
                    pCAM->_pMover->setVxMvAcce(dX_CAM);
                }
                if (-_stop_renge/4 < dX_VP && dX_VP < _stop_renge/4) {
                    pVP->_pMover->setVxMvAcce(0);
                    pVP->_pMover->setVxMvVelo(pVP->_pMover->_veloVxMv * 0.6);
                } else {
                    pVP->_pMover->setVxMvAcce(dX_VP);
                }
            } else {
                if (-_stop_renge < dX_CAM && dX_CAM < _stop_renge) {
                    pCAM->_pMover->setVxMvAcce(0);
                    pCAM->_pMover->setVxMvVelo(pCAM->_pMover->_veloVxMv * 0.8);
                } else {
                    pCAM->_pMover->setVxMvAcce(dX_CAM);
                }
                if (-_stop_renge < dX_VP && dX_VP < _stop_renge) {
                    pVP->_pMover->setVxMvAcce(0);
                    pVP->_pMover->setVxMvVelo(pVP->_pMover->_veloVxMv * 0.8);
                } else {
                    pVP->_pMover->setVxMvAcce(dX_VP);
                }
            }



            if (_pos_camera == CAM_POS_TOP   || _pos_camera == CAM_POS_BOTTOM) {
                //TOP,BOTTOM視点の場合は上下（Y軸）は遊びを少なくする
                if (-_stop_renge/4 < dY_CAM && dY_CAM < _stop_renge/4) {
                    pCAM->_pMover->setVyMvAcce(0);
                    pCAM->_pMover->setVyMvVelo(pCAM->_pMover->_veloVyMv * 0.6);
                } else {
                    pCAM->_pMover->setVyMvAcce(dY_CAM);
                }
                if (-_stop_renge/4 < dY_VP && dY_VP < _stop_renge/4) {
                    pVP->_pMover->setVyMvAcce(0);
                    pVP->_pMover->setVyMvVelo(pVP->_pMover->_veloVyMv * 0.6);
                } else {
                    pVP->_pMover->setVyMvAcce(dY_VP);
                }
            } else {
                if (-_stop_renge < dY_CAM && dY_CAM < _stop_renge) {
                    pCAM->_pMover->setVyMvAcce(0);
                    pCAM->_pMover->setVyMvVelo(pCAM->_pMover->_veloVyMv * 0.8);
                } else {
                    pCAM->_pMover->setVyMvAcce(dY_CAM);
                }
                if (-_stop_renge < dY_VP && dY_VP < _stop_renge) {
                    pVP->_pMover->setVyMvAcce(0);
                    pVP->_pMover->setVyMvVelo(pVP->_pMover->_veloVyMv * 0.8);
                } else {
                    pVP->_pMover->setVyMvAcce(dY_VP);
                }
            }

            if (_pos_camera == CAM_POS_RIGHT || _pos_camera == CAM_POS_LEFT) {
                //横視点の場合は奥行（Z軸）は遊びを少なくする
                if (-_stop_renge/4 < dZ_CAM && dZ_CAM < _stop_renge/4) {
                    pCAM->_pMover->setVzMvAcce(0);
                    pCAM->_pMover->setVzMvVelo(pCAM->_pMover->_veloVzMv * 0.6);
                } else {
                    pCAM->_pMover->setVzMvAcce(dZ_CAM);
                }
                if (-_stop_renge/4 < dZ_VP && dZ_VP < _stop_renge/4) {
                    pVP->_pMover->setVzMvAcce(0);
                    pVP->_pMover->setVzMvVelo(pVP->_pMover->_veloVzMv * 0.6);
                } else {
                    pVP->_pMover->setVzMvAcce(dZ_VP);
                }
            } else {
                if (-_stop_renge < dZ_CAM && dZ_CAM < _stop_renge) {
                    pCAM->_pMover->setVzMvAcce(0);
                    pCAM->_pMover->setVzMvVelo(pCAM->_pMover->_veloVzMv * 0.8);
                } else {
                    pCAM->_pMover->setVzMvAcce(dZ_CAM);
                }
                if (-_stop_renge/4 < dZ_VP && dZ_VP < _stop_renge/4) {
                    pVP->_pMover->setVzMvAcce(0);
                    pVP->_pMover->setVzMvVelo(pVP->_pMover->_veloVzMv * 0.8);
                } else {
                    pVP->_pMover->setVzMvAcce(dZ_VP);
                }
            }

            //自機通常移動に吸着
            if (pMYSHIP->_iMoveVelo != 0) {
                //カメラがブルブル震えるので、震えない差分を加えている。
                //TODO:もっと良い方法があるかもしれない。後で考えよう。
                int kyuchaku = pMYSHIP->_iMoveVelo/2; //吸着範囲
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

            //カメラのUPを計算
            if (_angXY_nowCamUp != move_target_XY_CAM_UP) {
                //_TRACE_("_angXY_nowCamUp="<<_angXY_nowCamUp<<" / move_target_XY_CAM_UP="<<move_target_XY_CAM_UP);
                angle da = GgafDx9Util::getDiffAng(_angXY_nowCamUp, move_target_XY_CAM_UP);
                if (-1000 < da && da < 1000) {
                    _angXY_nowCamUp = move_target_XY_CAM_UP;
                } else {
                    _angXY_nowCamUp += (1000 * sgn(da));
                }
                _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
                pCAM->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
                pCAM->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
                pCAM->_pVecCamUp->z = 0.0f;
            }

            pCAM->_pMover->behave();
            pVP->_pMover->behave();
        }

    } // if (getProgress() == GAMEMAIN_PROG_PLAY)
}
void GameMainScene::catchEvent(UINT32 prm_no, void* prm_pSource) {
    if (prm_no == READY_NEXT_STAGE) {
        _TRACE_("GameMainScene::catchEvent() READY_NEXT_STAGE準備きた");
        if (_stage < 5) {
            _stage++;
            ready(_stage);

        } else {
            //TODO:エデニング？
        }
    }
}
void GameMainScene::processFinal() {
}

GameMainScene::~GameMainScene() {
}

