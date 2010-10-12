#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

GroundBoxScene::GroundBoxScene(const char* prm_name) : DefaultScene(prm_name) {
    _area_len = 2;//23;
    _area_height = 24;
    _area_width = 32;


    BoxInfo a[2][24*32] = {
                    { {1,2,4,{0,11,0,0,0,0}}, {2,4,44,{0,0,21,0,0,0}} },
                    { {3,5,34,{11,22,33,44,55,66}}, {4,4,44,{99,91,92,93,94,0}} }
    };
    _papaBoxInfo = NEW BoxInfo*[_area_len];
    for (int i = 0; i < _area_len; i++) {
        _papaBoxInfo[i] = NEW BoxInfo[_area_height*_area_width];
    }

    for (int i = 0; i < _area_len; i++) {
        for (int j = 0; j < 2; i++) {

            _papaBoxInfo[i][j] = a[i][j]; //ƒRƒs[
        }
    }




    _box_stock = 200;


    _pDispatcher_Box = NEW GgafActorDispatcher("Dp_Box");
    for (int i = 0; i < _box_stock; i++) {
        GroundBoxActor* pGroundBoxActor =  NEW GroundBoxActor("GroundBox","boxmodel");
        pGroundBoxActor->inactivateTreeImmediately();
        _pDispatcher_Box->addSubLast(pGroundBoxActor);
    }
    getLordActor()->addSubGroup(_pDispatcher_Box);




}

void GroundBoxScene::initialize() {
    for (int i = 0; i < _area_len; i++) {
        for (int j = 0; j < 2; i++) {
            _TRACE_("_papaBoxInfo["<<i<<"]["<<j<<"]:--------------");
            _TRACE_("{"<<_papaBoxInfo[i][j]._Y <<","<<_papaBoxInfo[i][j]._Z<<","<<_papaBoxInfo[i][j]._box_draw_face<<","<<
                    "{"<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[0]<<","<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[1]<<","<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[2]<<","<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[3]<<","<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[4]<<","<<
                    _papaBoxInfo[i][j]._aColliBoxStretch[5]<<""<<
                    "}"<<
                    "}");

        }
    }
}

void GroundBoxScene::processBehavior() {

}

void GroundBoxScene::processFinal() {
}

GroundBoxScene::~GroundBoxScene() {

}
