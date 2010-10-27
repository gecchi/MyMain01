#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


WalledSectionScene::WalledSectionScene(const char* prm_name, const char* prm_data_filename) : DefaultScene(prm_name) {
//ruby tool/script/make_stage_data.rb > scene/stage_data.txt
    _class_name = "WalledSectionScene";
    _pTarget_FrontAlpha = NULL;
    _wall_dep = 0;
    _wall_width = 0;
    _wall_height = 0;
    ground_speed = 0;
    _loop_num = 1;
    _cnt_loop = 0;
    _pFuncWallMove = WalledSectionScene::moveX;
    string data_filename = STG_PROPERTY(DIR_SCENE_DATA) + string(prm_data_filename);
    ifstream ifs(data_filename.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException("WalledSectionScene::WalledSectionScene "<<prm_data_filename<<" が開けません");
    }

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
            ifs >> _papaWallInfo[i][j]._Y >>
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
    _pWallLast = NULL;;
    _wall_start_X = 0;
    _pDispatcher_Wall = NULL;
}
void WalledSectionScene::config(
        GgafActorDispatcher* prm_pDispatcher_Wall,
        int prm_wall_dep, int prm_wall_width, int prm_wall_height,
        int prm_loop_num) {
    _pDispatcher_Wall = prm_pDispatcher_Wall;
    _wall_dep = prm_wall_dep;
    _wall_width = prm_wall_width;
    _wall_height = prm_wall_height;
    _loop_num = prm_loop_num;
}

void WalledSectionScene::initialize() {
    if (_pDispatcher_Wall == NULL) {
        throwGgafCriticalException("WalledSectionScene::initialize()   GgafActorDispatcher* _pDispatcher_Wall をセットして下さい。")
    }
}

void WalledSectionScene::onActive() {
    _frame_of_launch_interval = (frame)(_wall_dep /ground_speed);
    _cnt_area_len = 0;
    _cnt_loop = 0;
    _wall_start_X = 0;//GgafDx9Universe::_X_goneRight;
}


void WalledSectionScene::processBehavior() {
    int ground_speed =
    if (_cnt_loop < _loop_num) {
        if (_cnt_area_len >= _area_len) {
            _cnt_area_len = 0;
            _cnt_loop++;
        }
        if (getActivePartFrame() % _frame_of_launch_interval == 0) {
            if (_pWallLast) {
                _wall_start_X = _pWallLast->_X + _wall_dep - ground_speed;
            }
            for (int n = 0; n < _paWallInfoLen[_cnt_area_len]; n++) {
                WallActor* pWall = (WallActor*)_pDispatcher_Wall->employ();
                if (pWall) {
                    pWall->config(_papaWallInfo[_cnt_area_len][n]._wall_draw_face,
                                 _papaWallInfo[_cnt_area_len][n]._aColliBoxStretch);
                    pWall->setGeometry(_wall_start_X,
                                      ((-_area_height/2) + _papaWallInfo[_cnt_area_len][n]._Y) * _wall_height,
                                      ((-_area_width/2) + _papaWallInfo[_cnt_area_len][n]._Z) * _wall_width);
                    pWall->activate();
                    _pWallLast = pWall;
                }
            }
            _frame_of_launch_interval = (frame)(_wall_dep /ground_speed);
            _cnt_area_len++;
        }
    } else {
        //終了
        //
    }
}

void WalledSectionScene::processFinal() {
}

WalledSectionScene::~WalledSectionScene() {
    for (int i = 0; i < _area_len; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo);
    DELETEARR_IMPOSSIBLE_NULL(_paWallInfoLen);

}
