#include "stdafx.h"
#include "jp/ggaf/lib/actor/GraphBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQty)
      : DefaultBoardActor(prm_name, prm_model) ,
_chip_width(_pBoardModel->_model_width_px),
_rate_org_chip_width(1.0 / _chip_width) {
    _class_name = "GraphBarActor";
    _pPxQty = prm_pPxQty;
    _is_new_PxQuantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model)
      : DefaultBoardActor(prm_name, prm_model) ,
_chip_width(_pBoardModel->_model_width_px),
_rate_org_chip_width(1.0 / _chip_width) {
    _class_name = "GraphBarActor";
    _pPxQty = NEW PxQuantity();
    _is_new_PxQuantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void GraphBarActor::linkQty(PxQuantity* prm_pPxQty) {
    if (_pPxQty) {
        if (_is_new_PxQuantity) {
            GGAF_DELETE(_pPxQty);
        }
    }
    _pPxQty = prm_pPxQty;
    _is_new_PxQuantity = false;
}

void GraphBarActor::linkVariable(int* prm_pVariable) {
    _pPxQty->link(prm_pVariable);
}

void GraphBarActor::processDraw() {
    float bar_width = (float)(_pPxQty->getPx());
    if (bar_width == 0.0f) { //I know float ==
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
#ifdef MY_DEBUG
    if (_align != ALIGN_LEFT) {
        throwGgafCriticalException("GraphBarActor::processDraw() X座標アライメントは ALIGN_LEFT 以外出来ません。name="<<getName()<<" this="<<this);
    }
#endif
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_local_left_top_y) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_Rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, (float)(C_PX(_x)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hTransformedX) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, (float)(C_PX(_y)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hTransformedY) に失敗しました。3");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_local_left_top_x) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_z)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "GraphBarActor::draw() SetValue(_h_colMaterialDiffuse) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_alpha) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, bar_width * _rate_org_chip_width * SC_R(_sx));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_sy));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
    _pBoardModel->GgafDxBoardModel::draw(this);
}

GraphBarActor::~GraphBarActor() {
    if (_is_new_PxQuantity) {
        GGAF_DELETE(_pPxQty);
    }
}
