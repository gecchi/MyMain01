#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


WalledSectionScene::WalledSectionScene(const char* prm_name, const char* prm_data_filename,  ScrolledScene* prm_pScrolledScene) : DefaultScene(prm_name) {
//ruby tool/script/make_stage_data.rb > scene/stage_data.txt

    _TRACE_("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" begin");
    _class_name = "WalledSectionScene";
    _pTarget_FrontAlpha = NULL;
	_pTarget_FrontAlpha = NULL;
    _pScrolledScene = prm_pScrolledScene;
    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    _loop_num = 1;
    _cnt_loop = 0;
    _is_loop_end = false;
    string data_filename = CFG_PROPERTY(DIR_SCENE_DATA) + string(prm_data_filename);
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" が開けません");
    }
    ifs >> _loop_num;


    ifs >> _area_len >>
           _area_height >>
           _area_width;
    if (ifs.fail()) {
        throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその１");
    }
    int r_data;
    _paWallInfoLen = NEW int[_area_len];
    for (int i = 0; i < _area_len; i++) {
        ifs >> r_data;
        _paWallInfoLen[i] = r_data;
        if (ifs.fail()) {
            throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその２ i="<<i<<" _area_len="<<_area_len);
        }
    }

    _papaWallInfo = NEW WallInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _TRACE_("WalledSectionScene read..."<<i);
        _papaWallInfo[i] = NEW WallInfo[_paWallInfoLen[i]];
        for (int j = 0; j < _paWallInfoLen[i]; j++) {
            ifs >> _papaWallInfo[i][j]._pos_prism >>
                   _papaWallInfo[i][j]._Y >>
                   _papaWallInfo[i][j]._Z >>
                   _papaWallInfo[i][j]._wall_draw_face >>
                   _papaWallInfo[i][j]._aColliBoxStretch[0] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[1] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[2] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[3] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[4] >>
                   _papaWallInfo[i][j]._aColliBoxStretch[5];
            if (ifs.fail()) {
                throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" フォーマットエラーその３ i="<<i<<"/j="<<j<<"/_area_len="<<_area_len<<"/_paWallInfoLen[i]="<<_paWallInfoLen[i]);
            }
        }

    }
    ifs.close();
    _pWallPartsLast = NULL;;
    _wall_start_X = 0;
    _pDepo_WallAAB = NULL;
    _pDepo_WallAAPrism = NULL;
    _TRACE_("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" done");
}
void WalledSectionScene::config(
        GgafActorDepository* prm_pDepo_WallAAB,
        GgafActorDepository* prm_pDepo_WallAAPrism,
        int prm_wall_dep, int prm_wall_width, int prm_wall_height) {
    _pDepo_WallAAB = prm_pDepo_WallAAB;
    _pDepo_WallAAPrism = prm_pDepo_WallAAPrism;
    _wall_dep = prm_wall_dep;
    _wall_width = prm_wall_width;
    _wall_height = prm_wall_height;
}

void WalledSectionScene::initialize() {
    if (_pDepo_WallAAB == NULL) {
        throwGgafCriticalException("WalledSectionScene::initialize()   GgafActorDepository* _pDepo_WallAAB をセットして下さい。")
    }
}

void WalledSectionScene::onActive() {
    _frame_of_launch_next = (frame)(_wall_dep /_pScrolledScene->getScroolSpeed());
    _cnt_area_len = 0;
    _cnt_loop = 0;
    _is_loop_end = false;
    _wall_start_X = GgafDxUniverse::_X_goneRight - _wall_dep;
}

void WalledSectionScene::processBehavior() {
    if (!_is_loop_end) {

        velo parent_scroll_speed =_pScrolledScene->getScroolSpeed();
        if (_pWallPartsLast == NULL || (_wall_start_X - _pWallPartsLast->_X) >= _wall_dep) {
            if (_cnt_area_len >= _area_len && _cnt_loop+1 >= _loop_num) {
                //終了
                _is_loop_end = true;
                return;
            } else {
                if (_cnt_area_len >= _area_len) {
                    _cnt_area_len = 0;
                    _cnt_loop++;
                }
            }

            WallPartsActor* pWallParts = NULL;
            for (int n = 0; n < _paWallInfoLen[_cnt_area_len]; n++) {
                if (_papaWallInfo[_cnt_area_len][n]._pos_prism == 0) {
                    pWallParts = (WallPartsActor*)_pDepo_WallAAB->dispatchForce();
                } else {
                    if (_pDepo_WallAAPrism) {
                        pWallParts = (WallPartsActor*)_pDepo_WallAAPrism->dispatchForce();
                    } else {
                        continue;
                    }
                }
                if (pWallParts->isActiveActor()) {
                    pWallParts->inactivateImmediately();
                    pWallParts->onInactive();
                }

                pWallParts->config(this,
                              _papaWallInfo[_cnt_area_len][n]._pos_prism,
                              _papaWallInfo[_cnt_area_len][n]._wall_draw_face,
                              _papaWallInfo[_cnt_area_len][n]._aColliBoxStretch);
                pWallParts->locate(_pWallPartsLast==NULL ? _wall_start_X : _pWallPartsLast->_X + _wall_dep - parent_scroll_speed,
                                  ((-_area_height/2) + _papaWallInfo[_cnt_area_len][n]._Y) * _wall_height,
                                  ((-_area_width/2) + _papaWallInfo[_cnt_area_len][n]._Z) * _wall_width);
                pWallParts->activate();
            }
            _pWallPartsLast = pWallParts;
            _frame_of_launch_next = (frame)(_wall_dep / parent_scroll_speed);
            _cnt_area_len++;

        }
    } else {
        //終了
        //
    }
}

void WalledSectionScene::processFinal() {
}


WallPartsActor* WalledSectionScene::getLastWallParts() {
    return _pWallPartsLast;
}

WalledSectionScene::~WalledSectionScene() {
    for (int i = 0; i < _area_len; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo);
    DELETEARR_IMPOSSIBLE_NULL(_paWallInfoLen);

}
