#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


WalledScene::WalledScene(const char* prm_name,
                            const char* prm_data_filename,
                            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
                            int prm_ground_speed) : DefaultScene(prm_name) {
//gecchi@dv9200-xp ~/workspace/MyStg2nd (520)$ ruby tool/script/make_stage_data.rb > stage_data.txt
    _wall_dep = prm_wall_dep;
    _wall_width = prm_wall_width;
    _wall_height = prm_wall_height;
    _ground_speed = prm_ground_speed;
    ifstream ifs(prm_data_filename);
    ifs >> _area_len >>
           _area_height >>
           _area_width;

    int r_data;
    _paWallInfoLen = NEW int[_area_len];
    for (int i = 0; i < _area_len; i++) {
        ifs >> r_data;
        _paWallInfoLen[i] = r_data;
    }

    _papaWallInfo = NEW WallInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _TRACE_("WalledScene read..."<<i);
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
        }
    }
    ifs.close();



//
//    _wall_stock = 4000;
//    _pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Box");
//    for (int i = 0; i < _wall_stock; i++) {
//        WallActor* pWallActor =  NEW WallActor("GroundBox","g_box001",
//                                                              _wall_dep, _wall_width, _wall_height);
//        pWallActor->_ground_speed = _ground_speed;
//        pWallActor->inactivateTreeImmediately();
//        _pDispatcher_Wall->addSubLast(pWallActor);
//    }
    _pDispatcher_Wall = NEW GgafActorDispatcher("Dp_Wall");
    getLordActor()->addSubGroup(_pDispatcher_Wall);
}

void WalledScene::initialize() {
    if (_pDispatcher_Wall->getSubFirst() == NULL) {
        throwGgafCriticalException("WalledScene::initialize() 実装クラスのコンストラクタで _pDispatcher_Wallに壁オブジェクトをセットして下さい。")
    }
//    for (int i = 0; i < _area_len; i++) {
//        for (int j = 0; j < _paWallInfoLen[i]; j++) {
//            _TRACE_("_papaWallInfo["<<i<<"]["<<j<<"]:--------------");
//            _TRACE_("{"<<_papaWallInfo[i][j]._Y <<","<<_papaWallInfo[i][j]._Z<<","<<_papaWallInfo[i][j]._wall_draw_face<<","<<
//                    "{"<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[0]<<","<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[1]<<","<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[2]<<","<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[3]<<","<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[4]<<","<<
//                    _papaWallInfo[i][j]._aColliBoxStretch[5]<<""<<
//                    "}"<<
//                    "}");
//
//        }
//    }
}

void WalledScene::onActive() {
    _frame_of_launch_interval = (frame)(_wall_dep /_ground_speed);
    _cnt_area_len = 0;
}


void WalledScene::processBehavior() {

    if (_cnt_area_len < _area_len && getActivePartFrame() % _frame_of_launch_interval == 0) {
        for (int n = 0; n < _paWallInfoLen[_cnt_area_len]; n++) {
            WallActor* pWall = (WallActor*)_pDispatcher_Wall->employ();
            if (pWall) {
                pWall->config(_papaWallInfo[_cnt_area_len][n]._wall_draw_face,
                             _papaWallInfo[_cnt_area_len][n]._aColliBoxStretch);
                pWall->setGeometry(10000000,
                                  ((-_area_height/2) + _papaWallInfo[_cnt_area_len][n]._Y) * _wall_height,
                                  ((-_area_width/2) + _papaWallInfo[_cnt_area_len][n]._Z) * _wall_width);
                pWall->activate();
            }
        }
        _cnt_area_len++;
    }
}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {


     //void creatNewWall() =  6)


    for (int i = 0; i < _area_len; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaWallInfo);
    DELETEARR_IMPOSSIBLE_NULL(_paWallInfoLen);

}
