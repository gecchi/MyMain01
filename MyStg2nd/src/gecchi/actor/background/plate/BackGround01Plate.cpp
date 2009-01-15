#include "stdafx.h"
using namespace Ggaf;
using namespace GgafDx9;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

BackGround01Plate::BackGround01Plate(string prm_name, string prm_dummy) : GgafDx9TransformedActor(prm_name) {
	_class_name = "BackGround01Plate";

	_papChipPlate = NEW BackGroundChipPlate*[4];
	_papChipPlate[0] = NEW BackGroundChipPlate("Bg01_Chip01", "background01");
	_papChipPlate[1] = NEW BackGroundChipPlate("Bg01_Chip02", "background02");
	_papChipPlate[2] = NEW BackGroundChipPlate("Bg01_Chip03", "background03");
	_papChipPlate[3] = NEW BackGroundChipPlate("Bg01_Chip04", "background04");
	stopImmediately();
}

void BackGround01Plate::initialize() {

	_x = 0;
	_y = -216;
	_z = 0.999;//たぶん最背面 （0 <= _z < 1.0）
	//_z = 0.001;//たぶん最全面 （0 <= _z < 1.0）
	for (int i = 0; i < 4; i++) {
		_papChipPlate[i]->setAlpha(0);
		_papChipPlate[i]->_z = _z;
	}
}

void BackGround01Plate::processBehavior() {
	//フェードイン
//	if (0 < _dwFrame && _dwFrame <= 255) {
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				_papChipPlate[i]->_paVertex[j].color = D3DCOLOR_ARGB(_dwFrame,255,255,255);
//			}
//		}
//	}
	//フェードイン
	if (0 < _dwFrame && _dwFrame <= 255) {
		for (int i = 0; i < 4; i++) {
			_papChipPlate[i]->setAlpha(float(_dwFrame/255.0));
		}
	}

	if (_x < -1024) {
		_x += 1024;
	} else {
		_x -= 1;
	}

}

void BackGround01Plate::processDrawMain() {
	_papChipPlate[0]->_x = _x;
	_papChipPlate[0]->_y = _y;
	_papChipPlate[1]->_x = _x+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelWidth;
	_papChipPlate[1]->_y = _y;
	_papChipPlate[2]->_x = _x;
	_papChipPlate[2]->_y = _y+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelHeight;
	_papChipPlate[3]->_x = _x+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelWidth;
	_papChipPlate[3]->_y = _y+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelHeight;
	for (int i = 0; i < 4; i++) {
		_papChipPlate[i]->processDrawMain();
	}

	_papChipPlate[0]->_x = _x+1024;
	_papChipPlate[0]->_y = _y;
	_papChipPlate[1]->_x = _x+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelWidth+1024;
	_papChipPlate[1]->_y = _y;
	_papChipPlate[2]->_x = _x+1024;
	_papChipPlate[2]->_y = _y+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelHeight;
	_papChipPlate[3]->_x = _x+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelWidth+1024;
	_papChipPlate[3]->_y = _y+_papChipPlate[0]->_pPlateModel->_fSize_PlateModelHeight;
	for (int i = 0; i < 4; i++) {
		_papChipPlate[i]->processDrawMain();
	}

}

BackGround01Plate::~BackGround01Plate() {
	DELETE_IMPOSSIBLE_NULL(_papChipPlate[0]);
	DELETE_IMPOSSIBLE_NULL(_papChipPlate[1]);
	DELETE_IMPOSSIBLE_NULL(_papChipPlate[2]);
	DELETE_IMPOSSIBLE_NULL(_papChipPlate[3]);
	DELETEARR_IMPOSSIBLE_NULL(_papChipPlate);
}
