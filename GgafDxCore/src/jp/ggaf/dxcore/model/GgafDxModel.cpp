#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxModel::GgafDxModel(char* prm_model_name) : GgafObject() {
    TRACE3("GgafDxModel::GgafDxModel(" << prm_model_name << ")");
    _id = GgafDxModelManager::getNextId();
    _model_name = NEW char[51];
    strcpy(_model_name, prm_model_name);
    _paMaterial_default = NULL;
    _num_materials = 0;
    _papTextureCon = NULL;
    _bounding_sphere_radius = 0;
    _power_blink = -1.0f;
    _blink_threshold = 1.1f;
    _blinker_frames = 0;
    _pTextureBlinker = NEW GgafDxTextureBlinker(this);
    _is_init_model = false;
    _set_num = 1; //ƒfƒtƒHƒ‹ƒgÅ‘å“¯•`‰æ”‚P
    _specular = 0.0f;
    _specular_power = 0.0f;
    _numPass = 1;
    TRACE3("GgafDxModel::GgafDxModel(" << prm_model_name << ") _id="<<_id);
}

GgafDxModel::~GgafDxModel() {
    _TRACE_("GgafDxModel::~GgafDxModel() " << _model_name << " ");
    DELETEARR_POSSIBLE_NULL(_model_name);
    DELETEARR_POSSIBLE_NULL(_paMaterial_default);
    DELETE_IMPOSSIBLE_NULL(_pTextureBlinker);
}

