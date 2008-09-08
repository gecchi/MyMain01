#include "stdafx.h"

BackGround01Plate::BackGround01Plate(string prm_name) : GgafDx9TransformedActor(prm_name) {
	_papChipPlate = NEW DefaultPlateActor*[4];
	_papChipPlate[0] = NEW DefaultPlateActor("Bg01_Chip01", "background01");
	_papChipPlate[1] = NEW DefaultPlateActor("Bg01_Chip02", "background02");
	_papChipPlate[2] = NEW DefaultPlateActor("Bg01_Chip03", "background03");
	_papChipPlate[3] = NEW DefaultPlateActor("Bg01_Chip04", "background04");
	stopImmediately();
}

void BackGround01Plate::initialize() {

	_x = 0;
	_y = -216;
	_z = 0.999;//たぶん最背面 （0 < _z < 1.0）

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			_papChipPlate[i]->_paVertex[j].color = D3DCOLOR_ARGB(0 ,255,255,255);
		}
		_papChipPlate[i]->_z = _z;
	}

}

void BackGround01Plate::processBehavior() {
	//フェードイン
	if (0 < _dwFrame && _dwFrame <= 255) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				_papChipPlate[i]->_paVertex[j].color = D3DCOLOR_ARGB(_dwFrame,255,255,255);
			}
		}
	}

	if (_x < -1024) {
		_x += 1024;
	} else {
		_x -= 0.3;
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
		_papChipPlate[i]->drawMain();
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
		_papChipPlate[i]->drawMain();
	}

}

BackGround01Plate::~BackGround01Plate() {
	delete _papChipPlate[0];
	delete _papChipPlate[1];
	delete _papChipPlate[2];
	delete _papChipPlate[3];
	delete [] _papChipPlate;
}
