#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model)
  : DefaultBoardActor(prm_name, prm_model, "DefaultBoardTechnique") {
    _class_name = "FontBoardActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[50];
}

void FontBoardActor::setString(float prm_x, float prm_y, const char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void FontBoardActor::setString(float prm_x, float prm_y, char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void FontBoardActor::setString(float prm_x, float prm_y, float prm_z, const char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    //_paVertex[0].z = _z;
    //_paVertex[1].z = _z;
    //_paVertex[2].z = _z;
    //_paVertex[3].z = _z;
}

void FontBoardActor::setString(float prm_x, float prm_y, float prm_z, char* prm_str) {
    setString(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    //_paVertex[0].z = _z;
    //_paVertex[1].z = _z;
    //_paVertex[2].z = _z;
    //_paVertex[3].z = _z;

}

void FontBoardActor::setString(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
}

void FontBoardActor::setString(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
}

void FontBoardActor::processDrawMain() {
    if (_len == 0) {
        return;
    }
    static float x_beginning, y_beginning;
    x_beginning = _x;
    y_beginning = _y;
    for (int i = 0; i < _len; i++) {
        if (_draw_string[i] == '\n') {
            _x = x_beginning;
            _y += _pBoardModel->_fSize_BoardModelHeightPx;
            continue;
        } else {
            if (_draw_string[i] - ' ' < 0) {
                setPatternNo('?' - ' '); //”ÍˆÍŠO‚Í"?"
            } else {
                setPatternNo(_draw_string[i] - ' '); //’Êí•¶Žš—ñ
            }
        }
        DefaultBoardActor::processDrawMain();
        _pBoardModel->draw(this);

        _x += _pBoardModel->_fSize_BoardModelWidthPx;
    }
    _x = x_beginning;
    _y = y_beginning;
}

FontBoardActor::~FontBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}

