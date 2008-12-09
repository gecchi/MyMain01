#include "stdafx.h"

FontPlateActor::FontPlateActor(string prm_name, string prm_model) : DefaultPlateActor(prm_name, prm_model) {
	_class_name = "FontPlateActor";
	_draw_string = "";
	_iStrLen = (int)_draw_string.size();
}

void FontPlateActor::setString(float prm_x, float prm_y, string prm_draw_string) {
	_draw_string = prm_draw_string;
	_iStrLen = (int)_draw_string.size();
	_x = prm_x;
	_y = prm_y;
}

void FontPlateActor::setString(float prm_x, float prm_y, char* prm_paCString) {
	_draw_string = string(prm_paCString);
	_iStrLen = (int)_draw_string.size();
	_x = prm_x;
	_y = prm_y;
}

void FontPlateActor::setString(float prm_x, float prm_y, float prm_z, string prm_draw_string) {
	_draw_string = prm_draw_string;
	_iStrLen = (int)_draw_string.size();
	_x = prm_x;
	_y = prm_y;
	_z = prm_z;
}
void FontPlateActor::setString(float prm_x, float prm_y, float prm_z, char* prm_paCString) {
	_draw_string = string(prm_paCString);
	_iStrLen = (int)_draw_string.size();
	_x = prm_x;
	_y = prm_y;
	_z = prm_z;
}

void FontPlateActor::setString(string prm_draw_string) {
	_draw_string = prm_draw_string;
	_iStrLen = (int)_draw_string.size();
}

void FontPlateActor::setString(char* prm_paCString) {
	_draw_string = string(prm_paCString);
	_iStrLen = (int)_draw_string.size();
}

void FontPlateActor::processDrawMain() {
	if (_iStrLen == 0) {
		return;
	}
	_paVertex[0].z = _z;
	_paVertex[1].z = _z;
	_paVertex[2].z = _z;
	_paVertex[3].z = _z;

	float x_beginning = _x;
	float x = _x;
	float y = _y;
	const char* paChar = _draw_string.c_str();
	for (int i = 0; i < _iStrLen; i++) {
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

