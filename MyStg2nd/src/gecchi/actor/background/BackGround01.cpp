#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGround01::BackGround01(const char* prm_name, const char* prm_dummy) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "BackGround01";

    _papChipBoard = NEW BackGroundChipBoard*[4];
    _papChipBoard[0] = NEW BackGroundChipBoard("Bg01_Chip01", "B/background01");
    _papChipBoard[1] = NEW BackGroundChipBoard("Bg01_Chip02", "B/background02");
    _papChipBoard[2] = NEW BackGroundChipBoard("Bg01_Chip03", "B/background03");
    _papChipBoard[3] = NEW BackGroundChipBoard("Bg01_Chip04", "B/background04");

//    _papBackGroundStar001 = NEW BackGroundStar001*[4];
//    _papBackGroundStar001[0] = NEW BackGroundStar001("star01");
//    _papBackGroundStar001[1] = NEW BackGroundStar001("star02");
//    _papBackGroundStar001[2] = NEW BackGroundStar001("star03");
//    _papBackGroundStar001[3] = NEW BackGroundStar001("star04");

    inactivateImmediately();
}

void BackGround01::initialize() {

    _x = 0;
    _y = -216;
    _z = 0.999;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.001;//たぶん最全面 （0 <= _z < 1.0）
    for (int i = 0; i < 4; i++) {
        _papChipBoard[i]->setAlpha(0);
        _papChipBoard[i]->_z = _z;
    }
}

void BackGround01::processBehavior() {
    //フェードイン
    //	if (0 < _lifeframe && _lifeframe <= 255) {
    //		for (int i = 0; i < 4; i++) {
    //			for (int j = 0; j < 4; j++) {
    //				_papChipBoard[i]->_paVertex[j].color = D3DCOLOR_ARGB(_lifeframe,255,255,255);
    //			}
    //		}
    //	}
    //フェードイン
    if (0 < _lifeframe && _lifeframe <= 255) {
        for (int i = 0; i < 4; i++) {
            _papChipBoard[i]->setAlpha(float(_lifeframe / 255.0));
        }
    }

    if (_x < -1024) {
        _x += 1024;
    } else {
        _x -= 0.1;
    }

}

void BackGround01::processDrawPrior() {
    if (_is_active_flg && _can_live_flg) {
        for (int i = 0; i < 4; i++) {
           GgafDx9Universe::setDrawDepthMaxLevel(_papChipBoard[i]);

           //自分自身が this が段階レンダに登録され無いとprocessDrawMainがよばれん！
        }
    }
}


void BackGround01::processDrawMain() {
    _papChipBoard[0]->_x = _x;
    _papChipBoard[0]->_y = _y;
    _papChipBoard[1]->_x = _x + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelWidthPx;
    _papChipBoard[1]->_y = _y;
    _papChipBoard[2]->_x = _x;
    _papChipBoard[2]->_y = _y + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelHeightPx;
    _papChipBoard[3]->_x = _x + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelWidthPx;
    _papChipBoard[3]->_y = _y + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelHeightPx;
    for (int i = 0; i < 4; i++) {
        _papChipBoard[i]->processDrawMain();
    }

    _papChipBoard[0]->_x = _x + 1024;
    _papChipBoard[0]->_y = _y;
    _papChipBoard[1]->_x = _x + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelWidthPx + 1024;
    _papChipBoard[1]->_y = _y;
    _papChipBoard[2]->_x = _x + 1024;
    _papChipBoard[2]->_y = _y + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelHeightPx;
    _papChipBoard[3]->_x = _x + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelWidthPx + 1024;
    _papChipBoard[3]->_y = _y + _papChipBoard[0]->_pBoardModel->_fSize_BoardModelHeightPx;
    for (int i = 0; i < 4; i++) {
        _papChipBoard[i]->processDrawMain();
    }

}

BackGround01::~BackGround01() {
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[0]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[1]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[2]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[3]);
    DELETEARR_IMPOSSIBLE_NULL(_papChipBoard);

//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[0]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[1]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[2]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[3]);
//    DELETEARR_IMPOSSIBLE_NULL(_papBackGroundStar001);
}
