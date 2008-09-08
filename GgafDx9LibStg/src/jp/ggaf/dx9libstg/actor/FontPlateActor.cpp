#include "stdafx.h"

FontPlateActor::FontPlateActor(string prm_name, string prm_xname) : DefaultPlateActor(prm_name, prm_xname) {
	_class_name = "FontPlateActor";
	_draw_string = "empty";
}

void FontPlateActor::setStringPlate(float prm_x, float prm_y, string prm_draw_string) {
	_draw_string = prm_draw_string;
	_x = prm_x;
	_y = prm_y;
}

void FontPlateActor::processDrawMain() {
	_paVertex[0].z = _z;
	_paVertex[1].z = _z;
	_paVertex[2].z = _z;
	_paVertex[3].z = _z;

	int iStrLen = (int)_draw_string.size();
	float x_beginning = _x;
	float x = _x;
	float y = _y;
	const char* paChar = _draw_string.c_str();
	for (int i = 0; i < iStrLen; i++) {
		if (paChar[i] == '\n') {
			x = x_beginning;
			y += _pPlateModel->_fSize_PlateModelHeight;
			continue;
		} else {
			if (paChar[i] - ' ' < 0) {
				setPatternNo('?' - ' '); //”ÍˆÍŠO‚Í"?"
			} else {
				setPatternNo(paChar[i] - ' '); //’Êí•¶Žš—ñ
			}
		}
		_paVertex[0].x = x;
		_paVertex[1].x = x + _pPlateModel->_fSize_PlateModelWidth;
		_paVertex[2].x = x;
		_paVertex[3].x = x + _pPlateModel->_fSize_PlateModelWidth;
		_paVertex[0].y = y;
		_paVertex[1].y = y;
		_paVertex[2].y = y + _pPlateModel->_fSize_PlateModelHeight;
		_paVertex[3].y = y + _pPlateModel->_fSize_PlateModelHeight;

		_pPlateModel->draw(this);

		x += _pPlateModel->_fSize_PlateModelWidth;
	}
}

FontPlateActor::~FontPlateActor() {
}

