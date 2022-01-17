#include "jp/ggaf/lib/model/SingleLaserModel.h"

using namespace GgafLib;

SingleLaserModel::SingleLaserModel(const char* prm_model_id) : MeshSetModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _max_draw_set_num = 26;
    _TRACE_("SingleLaserModel::SingleLaserModel() "<<_model_id<<" の最大同時描画セット数は "<<_max_draw_set_num<<" に強制上書きされました。");
}

SingleLaserModel::~SingleLaserModel() {
}

