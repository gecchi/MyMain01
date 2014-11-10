#include "jp/ggaf/dxcore/model/GgafDxModel.h"

#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxModel::GgafDxModel(char* prm_model_name) : GgafObject(),
_pTexBlinker(new GgafDxTextureBlinker(this)) {
    _TRACE3_("GgafDxModel::GgafDxModel(" << prm_model_name << ")");
    _id = GgafDxModelManager::getNextId();
    _model_name = NEW char[51];
    strcpy(_model_name, prm_model_name);
    _paMaterial_default = nullptr;
    _num_materials = 0;
    _papTextureConnection = nullptr;
    _bounding_sphere_radius = 0;
    _power_blink = 1.0f;
    _blink_threshold = 1.000001f;
    _blinker_frames = 0;
    _is_init_model = false;
    _set_num = 1; //デフォルト最大同描画数１
    _specular = 0.0f;
    _specular_power = 0.0f;
    _num_pass = 1;
    _obj_model = 0;
    _TRACE3_("GgafDxModel::GgafDxModel(" << prm_model_name << ") _id="<<_id);
}

//void GgafDxModel::setMaterialTexture(int prm_material_no, const char* prm_texture) {
//    GgafDxTextureManager* pModelTextureManager = P_GOD->_pModelManager->_pModelTextureManager;
//    GgafDxTextureConnection* pTexCon = (GgafDxTextureConnection*)pModelTextureManager->connect(prm_texture, this);
//    _papTextureConnection[prm_material_no]->close();
//    _papTextureConnection[prm_material_no] = pTexCon;
//}

//GgafDxTextureConnection* GgafDxModel::setMaterialTexture(int prm_material_no, GgafDxTextureConnection* prm_pTexCon) {
//    if (prm_material_no > _num_materials) {
//        throwGgafCriticalException("GgafDxModel::setMaterialTexture マテリアルINDEXが範囲外です。_model_name="<<_model_name<<" _num_materials="<<_num_materials<<" prm_material_no="<<prm_material_no)
//    } else {
//        GgafDxTextureConnection* r = _papTextureConnection[prm_material_no];
//        _papTextureConnection[prm_material_no] = prm_pTexCon;
//        return r;
//    }
//}
void GgafDxModel::swapTopTextureOrder(const char* prm_texture0) {
    int idx = -1;
    for (DWORD i = 0; i < _num_materials; i++) {
        if (UTIL::strcmp_ascii(_papTextureConnection[i]->peek()->getName(), prm_texture0) == 0) {
            if (i == 0) {
                return; //swap不要すでにTop
            } else {
                idx = i;
                break;
            }
        }
    }
    if (idx < 0) {
        throwGgafCriticalException("GgafDxModel::swapTextureOrder 指定テクスチャは見つかりません。prm_texture0="<<prm_texture0);
    }
    GgafDxTextureConnection* top = _papTextureConnection[idx];
    for (int i = _num_materials-1; i >= 1; i--) {
        if (i <= idx) {
            _papTextureConnection[i] = _papTextureConnection[i-1];
        }
    }
    _papTextureConnection[0] = top;
}

GgafDxModel::~GgafDxModel() {
    _TRACE_("GgafDxModel::~GgafDxModel() " << _model_name << " ");
    GGAF_DELETEARR_NULLABLE(_model_name);
    GGAF_DELETEARR_NULLABLE(_paMaterial_default);
    delete _pTexBlinker;
}

