#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9StringBoardActor::GgafDx9StringBoardActor(const char* prm_name, const char* prm_model)
  : GgafDx9BoardActor(prm_name, prm_model, "B/DefaultBoardEffect", "DefaultBoardTechnique") {
    _class_name = "GgafDx9StringBoardActor";
    _draw_string = NULL;
    _len = 0;
    _buf = NEW char[50];
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, const char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, float prm_z, const char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    //_paVertex[0].z = _z;
    //_paVertex[1].z = _z;
    //_paVertex[2].z = _z;
    //_paVertex[3].z = _z;
}

void GgafDx9StringBoardActor::update(float prm_x, float prm_y, float prm_z, char* prm_str) {
    update(prm_str);
    _x = prm_x;
    _y = prm_y;
    _z = prm_z;
    //_paVertex[0].z = _z;
    //_paVertex[1].z = _z;
    //_paVertex[2].z = _z;
    //_paVertex[3].z = _z;

}

void GgafDx9StringBoardActor::update(const char* prm_str) {
    _draw_string = (char*)prm_str;
    _len = strlen(prm_str);
}

void GgafDx9StringBoardActor::update(char* prm_str) {
    _draw_string = _buf;
    strcpy(_draw_string, prm_str);
    _len = strlen(prm_str);
}

void GgafDx9StringBoardActor::processDrawMain() {
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
        } else if (_draw_string[i] == '\0') {
            break;
        } else {
            if (_draw_string[i] - ' ' < 0) {
                setPatternNo('?' - ' '); //”ÍˆÍŠO‚Í"?"
            } else {
                setPatternNo(_draw_string[i] - ' '); //’Êí•¶Žš—ñ
            }
        }
        GgafDx9BoardActor::processDrawMain();

        _x += _pBoardModel->_fSize_BoardModelWidthPx;
    }
    _x = x_beginning;
    _y = y_beginning;
}

GgafDx9StringBoardActor::~GgafDx9StringBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_buf);
}

