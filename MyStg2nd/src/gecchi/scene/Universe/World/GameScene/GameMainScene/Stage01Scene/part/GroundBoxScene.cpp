#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxScene::GroundBoxScene(const char* prm_name) : DefaultScene(prm_name) {

    ifstream ifs("../MyStg2nd/stage_data.txt");
    ifs >> _area_len >> _area_height >> _area_width;

    int r_data;
    _paBoxInfoLen = NEW int[_area_len];
    for (int i = 0; i < _area_len; i++) {
        ifs >> r_data;
        _paBoxInfoLen[i] = r_data;
    }

    _papaBoxInfo = NEW BoxInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _TRACE_("GroundBoxScene read..."<<i);
        _papaBoxInfo[i] = NEW BoxInfo[_paBoxInfoLen[i]];
        for (int j = 0; j < _paBoxInfoLen[i]; j++) {
            ifs >> _papaBoxInfo[i][j]._Y >>
                   _papaBoxInfo[i][j]._Z >>
                   _papaBoxInfo[i][j]._box_draw_face >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[0] >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[1] >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[2] >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[3] >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[4] >>
                   _papaBoxInfo[i][j]._aColliBoxStretch[5];
        }
    }
    ifs.close();

    _ground_speed = 16000;

    _box_dep = 1600000;
    _box_width = 400000;
    _box_height = 400000;
    _frame_of_launch_interval = (frame)(_box_dep /_ground_speed);

    _box_stock = 3000;
    _pDispatcher_Box = NEW GgafActorDispatcher("Dp_Box");
    for (int i = 0; i < _box_stock; i++) {
        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox","g_box001",
                                                              _box_dep, _box_width, _box_height);
        pGroundBoxActor->_ground_speed = _ground_speed;
        pGroundBoxActor->inactivateTreeImmediately();
        _pDispatcher_Box->addSubLast(pGroundBoxActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Box);
}

void GroundBoxScene::initialize() {
//    for (int i = 0; i < _area_len; i++) {
//        for (int j = 0; j < _paBoxInfoLen[i]; j++) {
//            _TRACE_("_papaBoxInfo["<<i<<"]["<<j<<"]:--------------");
//            _TRACE_("{"<<_papaBoxInfo[i][j]._Y <<","<<_papaBoxInfo[i][j]._Z<<","<<_papaBoxInfo[i][j]._box_draw_face<<","<<
//                    "{"<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[0]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[1]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[2]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[3]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[4]<<","<<
//                    _papaBoxInfo[i][j]._aColliBoxStretch[5]<<""<<
//                    "}"<<
//                    "}");
//
//        }
//    }
}

void GroundBoxScene::onActive() {
    _cnt_area_len = 0;
}


void GroundBoxScene::processBehavior() {

    if (_cnt_area_len < _area_len && getActivePartFrame() % _frame_of_launch_interval == 0) {
        for (int n = 0; n < _paBoxInfoLen[_cnt_area_len]; n++) {
            GroundBoxActor* pBox = (GroundBoxActor*)_pDispatcher_Box->employ();
            if (pBox) {
                pBox->config(_papaBoxInfo[_cnt_area_len][n]._box_draw_face,
                             _papaBoxInfo[_cnt_area_len][n]._aColliBoxStretch);
                pBox->setGeometry(10000000,
                                  ((-_area_height/2) + _papaBoxInfo[_cnt_area_len][n]._Y) * _box_height,
                                  ((-_area_width/2) + _papaBoxInfo[_cnt_area_len][n]._Z) * _box_width);
                pBox->activate();
            }
        }
        _cnt_area_len++;
    }
}

void GroundBoxScene::processFinal() {
}

GroundBoxScene::~GroundBoxScene() {
    for (int i = 0; i < _area_len; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papaBoxInfo[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papaBoxInfo);
    DELETEARR_IMPOSSIBLE_NULL(_paBoxInfoLen);

}
