#include "jp/ggaf/lib/actor/GraphBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model, Quantity<int, coord>* prm_pQty)
      : DefaultBoardActor(prm_name, prm_model) ,
_chip_width(_pBoardModel->_model_width_px),
_rate_org_chip_width(1.0 / _chip_width) {
    _class_name = "GraphBarActor";
    _pQty = prm_pQty;
    _is_new_Quantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model)
      : DefaultBoardActor(prm_name, prm_model) ,
_chip_width(_pBoardModel->_model_width_px),
_rate_org_chip_width(1.0 / _chip_width) {
    _class_name = "GraphBarActor";
    _pQty = NEW Quantity<int, coord>();
    _is_new_Quantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void GraphBarActor::processDraw() {
    float bar_width = (float)(_pQty->getQty());
    if (bar_width == 0.0f) { //I know float ==
        return;
    }
    ID3DXEffect* const pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
#ifdef MY_DEBUG
    if (_align != ALIGN_LEFT) {
        throwGgafCriticalException("X座標アライメントは ALIGN_LEFT 以外出来ません。this="<<NODE_INFO);
    }
#endif
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_y) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "SetFloat(_h_rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, (float)(C_PX(_x)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_x) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, (float)(C_PX(_y)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_transformed_y) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
    checkDxException(hr, D3D_OK, "SetFloat(_h_local_left_top_x) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_depth_z, (float)(C_PX(_z)));
    checkDxException(hr, D3D_OK, "SetFloat(_h_depth_z) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, bar_width * _rate_org_chip_width * SC_R(_sx));
    checkDxException(hr, D3D_OK, "SetFloat(_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "SetFloat(_sy) に失敗しました。");
    _pBoardModel->GgafDxBoardModel::draw(this);
}

GraphBarActor::~GraphBarActor() {
    if (_is_new_Quantity) {
        GGAF_DELETE(_pQty);
    }
}
