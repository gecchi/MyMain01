#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGround01::BackGround01(const char* prm_name, const char* prm_dummy) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "BackGround01";
    _x = 0;
    _y = 0;
    _z = 0.999;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)

    _papapChipBoard = NEW BackGroundChipBoard**[4];
    for (int i = 0; i < 4; i++) {
        _papapChipBoard[i] = NEW BackGroundChipBoard*[4];
        _papapChipBoard[i][0] = NEW BackGroundChipBoard("Bg01_Chip01", "background01");
        _papapChipBoard[i][1] = NEW BackGroundChipBoard("Bg01_Chip02", "background02");
        _papapChipBoard[i][2] = NEW BackGroundChipBoard("Bg01_Chip03", "background03");
        _papapChipBoard[i][3] = NEW BackGroundChipBoard("Bg01_Chip04", "background04");
    }


    _chip_width  = _papapChipBoard[0][0]->_pBoardSetModel->_fSize_BoardSetModelWidthPx;
    _chip_height = _papapChipBoard[0][0]->_pBoardSetModel->_fSize_BoardSetModelHeightPx;

//    _papapChipBoard[0] = NEW BackGroundChipBoard("Bg01_Chip01", "background01");
//    _papapChipBoard[1] = NEW BackGroundChipBoard("Bg01_Chip02", "background02");
//    _papapChipBoard[2] = NEW BackGroundChipBoard("Bg01_Chip03", "background03");
//    _papapChipBoard[3] = NEW BackGroundChipBoard("Bg01_Chip04", "background04");

//    _papBackGroundStar001 = NEW BackGroundStar001*[4];
//    _papBackGroundStar001[0] = NEW BackGroundStar001("star01");
//    _papBackGroundStar001[1] = NEW BackGroundStar001("star02");
//    _papBackGroundStar001[2] = NEW BackGroundStar001("star03");
//    _papBackGroundStar001[3] = NEW BackGroundStar001("star04");

    inactivateImmediately();
}

void BackGround01::initialize() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            addSubLast(_papapChipBoard[j][i]); //[j][i]にすることにより同モデルが４つでグルーピング表示をさせる。
        }
    }


    for (int i = 0; i < 4; i++) {
        baseがななめってる
        float base_x = i * (_chip_width + _chip_width);
        float base_y = i * (_chip_height + _chip_height);
        _papapChipBoard[i][0]->_x = base_x + _x;
        _papapChipBoard[i][0]->_y = base_y + _y;
        _papapChipBoard[i][0]->_z = _z;
        _papapChipBoard[i][1]->_x = base_x + _x + _chip_width;
        _papapChipBoard[i][1]->_y = base_y + _y;
        _papapChipBoard[i][1]->_z = _z;
        _papapChipBoard[i][2]->_x = base_x + _x;
        _papapChipBoard[i][2]->_y = base_y + _y + _chip_height;
        _papapChipBoard[i][2]->_z = _z;
        _papapChipBoard[i][3]->_x = base_x + _x + _chip_width;
        _papapChipBoard[i][3]->_y = base_y + _y + _chip_height;
        _papapChipBoard[i][3]->_z = _z;
   }
//    //GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)
//
//    _x = 0;
//    _y = -216;
//    _z = 0.999;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
//    //_z = 0.001;//たぶん最全面 （0 <= _z < 1.0）
//    for (int i = 0; i < 4; i++) {
//        _papapChipBoard[i]->setAlpha(0);
//        _papapChipBoard[i]->_z = _z;
//    }
}

void BackGround01::processBehavior() {
    //フェードイン
    //	if (0 < _lifeframe && _lifeframe <= 255) {
    //		for (int i = 0; i < 4; i++) {
    //			for (int j = 0; j < 4; j++) {
    //				_papapChipBoard[i]->_paVertex[j].color = D3DCOLOR_ARGB(_lifeframe,255,255,255);
    //			}
    //		}
    //	}
    //フェードイン
//    if (0 < _lifeframe && _lifeframe <= 255) {
//        for (int i = 0; i < 4; i++) {
//            _papapChipBoard[i]->setAlpha(float(_lifeframe / 255.0));
//        }
//    }

    if (_x < -1 * (_chip_width + _chip_width) ) {
        _x += (_chip_width + _chip_width);
    } else {
        _x -= 0.1;
    }

    for (int i = 0; i < 4; i++) {
        float base_x = i * (_chip_width + _chip_width);
        float base_y = i * (_chip_height + _chip_height);
        _papapChipBoard[i][0]->_x = base_x + _x;
        _papapChipBoard[i][0]->_y = base_y + _y;
        _papapChipBoard[i][1]->_x = base_x + _x + _chip_width;
        _papapChipBoard[i][1]->_y = base_y + _y;
        _papapChipBoard[i][2]->_x = base_x + _x;
        _papapChipBoard[i][2]->_y = base_y + _y + _chip_height;
        _papapChipBoard[i][3]->_x = base_x + _x + _chip_width;
        _papapChipBoard[i][3]->_y = base_y + _y + _chip_height;
   }

}

void BackGround01::processDrawPrior() {
//    if (_is_active_flg && _can_live_flg) {
//        for (int i = 0; i < 4; i++) {
//           GgafDx9Universe::setDrawDepthMaxLevel(_papapChipBoard[i]);
//
//           //自分自身が this が段階レンダに登録され無いとprocessDrawMainがよばれん！
//        }
//    }
}


void BackGround01::processDrawMain() {
//    _papapChipBoard[0]->_x = _x;
//    _papapChipBoard[0]->_y = _y;
//    _papapChipBoard[1]->_x = _x + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelWidthPx;
//    _papapChipBoard[1]->_y = _y;
//    _papapChipBoard[2]->_x = _x;
//    _papapChipBoard[2]->_y = _y + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelHeightPx;
//    _papapChipBoard[3]->_x = _x + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelWidthPx;
//    _papapChipBoard[3]->_y = _y + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelHeightPx;
//    for (int i = 0; i < 4; i++) {
//        _papapChipBoard[i]->processDrawMain();
//    }
//
//    _papapChipBoard[0]->_x = _x + 1024;
//    _papapChipBoard[0]->_y = _y;
//    _papapChipBoard[1]->_x = _x + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelWidthPx + 1024;
//    _papapChipBoard[1]->_y = _y;
//    _papapChipBoard[2]->_x = _x + 1024;
//    _papapChipBoard[2]->_y = _y + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelHeightPx;
//    _papapChipBoard[3]->_x = _x + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelWidthPx + 1024;
//    _papapChipBoard[3]->_y = _y + _papapChipBoard[0]->_pBoardSetModel->_fSize_BoardSetModelHeightPx;
//    for (int i = 0; i < 4; i++) {
//        _papapChipBoard[i]->processDrawMain();
//    }

}

BackGround01::~BackGround01() {
    for (int i = 0; i < 4; i++) {
        DELETEARR_IMPOSSIBLE_NULL(_papapChipBoard[i]);
    }
    DELETEARR_IMPOSSIBLE_NULL(_papapChipBoard);

//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[0]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[1]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[2]);
//    DELETE_IMPOSSIBLE_NULL(_papBackGroundStar001[3]);
//    DELETEARR_IMPOSSIBLE_NULL(_papBackGroundStar001);
}
