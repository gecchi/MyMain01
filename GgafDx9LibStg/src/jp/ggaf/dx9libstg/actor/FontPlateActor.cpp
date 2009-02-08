#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FontPlateActor::FontPlateActor(const char* prm_name, const char* prm_model) : DefaultPlateActor(prm_name, prm_model) {
    _class_name = "FontPlateActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[50];
}

void FontPlateActor::setString(float prm_x, float prm_y, const char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void FontPlateActor::setString(float prm_x, float prm_y, char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void FontPlateActor::setString(float prm_x, float prm_y, float prm_z, const char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    _paVertex[0].z = _z;
    _paVertex[1].z = _z;
    _paVertex[2].z = _z;
    _paVertex[3].z = _z;
}

void FontPlateActor::setString(float prm_x, float prm_y, float prm_z, char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    _paVertex[0].z = _z;
    _paVertex[1].z = _z;
    _paVertex[2].z = _z;
    _paVertex[3].z = _z;

}

void FontPlateActor::setString(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
}

void FontPlateActor::setString(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
}

void FontPlateActor::processDrawMain() {
    if (_len == 0) {
        return;
    }

    static float x_beginning, x, y;
    x_beginning = _x;
    x = _x;
    y = _y;
    for (int i = 0; i < _len; i++) {
        if (_draw_string[i] == '\n') {
            x = x_beginning;
            y += _pPlateModel->_fSize_PlateModelHeight;
            continue;
        } else {
            if (_draw_string[i] - ' ' < 0) {
                setPatternNo('?' - ' '); //”ÍˆÍŠO‚Í"?"
            } else {
                setPatternNo(_draw_string[i] - ' '); //’Êí•¶Žš—ñ
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
    DELETE_IMPOSSIBLE_NULL(_buf);
}

