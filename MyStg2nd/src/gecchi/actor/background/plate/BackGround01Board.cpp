#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGround01Board::BackGround01Board(const char* prm_name, const char* prm_dummy) : GgafDx9TransformedActor(prm_name) {
    _class_name = "BackGround01Board";

    _papChipBoard = NEW BackGroundChipBoard*[4];
	_papChipBoard[0] = NEW BackGroundChipBoard("Bg01_Chip01", "B/background01");
    _papChipBoard[1] = NEW BackGroundChipBoard("Bg01_Chip02", "B/background02");
    _papChipBoard[2] = NEW BackGroundChipBoard("Bg01_Chip03", "B/background03");
    _papChipBoard[3] = NEW BackGroundChipBoard("Bg01_Chip04", "B/background04");
    inactImmediately();
}

void BackGround01Board::initialize() {

    _x = 0;
    _y = -216;
    _z = 0.999;//たぶん最背面 （0 <= _z < 1.0）Z=(0～+1)
    //_z = 0.001;//たぶん最全面 （0 <= _z < 1.0）
    for (int i = 0; i < 4; i++) {
        _papChipBoard[i]->setAlpha(0);
        _papChipBoard[i]->_z = _z;
    }
}

void BackGround01Board::processBehavior() {
    //フェードイン
    //	if (0 < _dwFrame && _dwFrame <= 255) {
    //		for (int i = 0; i < 4; i++) {
    //			for (int j = 0; j < 4; j++) {
    //				_papChipBoard[i]->_paVertex[j].color = D3DCOLOR_ARGB(_dwFrame,255,255,255);
    //			}
    //		}
    //	}
    //フェードイン
    if (0 < _dwFrame && _dwFrame <= 255) {
        for (int i = 0; i < 4; i++) {
            _papChipBoard[i]->setAlpha(float(_dwFrame / 255.0));
        }
    }

    if (_x < -1024) {
        _x += 1024;
    } else {
        _x -= 1;
    }

}

void BackGround01Board::processDrawMain() {
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

BackGround01Board::~BackGround01Board() {
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[0]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[1]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[2]);
    DELETE_IMPOSSIBLE_NULL(_papChipBoard[3]);
    DELETEARR_IMPOSSIBLE_NULL(_papChipBoard);
}
