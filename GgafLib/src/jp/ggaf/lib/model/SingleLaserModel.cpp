#include "jp/ggaf/lib/model/SingleLaserModel.h"

using namespace GgafLib;

SingleLaserModel::SingleLaserModel(const char* prm_model_id) : MeshSetModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _max_draw_set_num = 26;
    _TRACE_("SingleLaserModel::SingleLaserModel() "<<_model_id<<" �̍ő哯���`��Z�b�g���� "<<_max_draw_set_num<<" �ɋ����㏑������܂����B");
}

SingleLaserModel::~SingleLaserModel() {
}

