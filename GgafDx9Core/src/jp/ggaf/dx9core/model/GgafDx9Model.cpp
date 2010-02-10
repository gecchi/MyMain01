#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


GgafDx9Model::GgafDx9Model(char* prm_model_name) : GgafObject() {
    TRACE3("GgafDx9Model::GgafDx9Model(" << prm_model_name << ")");
    _id = GgafDx9ModelManager::getNextId();
    _model_name = NEW char[51];
    strcpy(_model_name, prm_model_name);
    _paD3DMaterial9_default = NULL;
    _dwNumMaterials = 0;
    _papTextureCon = NULL;
    _bounding_sphere_radius = 0;
    _fPowerBlink = -1.0f;
    _fBlinkThreshold = 1.1f;
    _frame_blinker = 0;
    _pTextureBlinker = NEW GgafDx9TextureBlinker(this);
    _is_init_model = false;
    TRACE3("GgafDx9Model::GgafDx9Model(" << prm_model_name << ") _id="<<_id);
}

GgafDx9Model::~GgafDx9Model() {
    TRACE3("GgafDx9Model::~GgafDx9Model() " << _model_name << " start-->");
    DELETEARR_POSSIBLE_NULL(_model_name);
    DELETEARR_POSSIBLE_NULL(_paD3DMaterial9_default);
    DELETE_IMPOSSIBLE_NULL(_pTextureBlinker);
}

