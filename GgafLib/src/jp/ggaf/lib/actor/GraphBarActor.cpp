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

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity)
      : DefaultBoardActor(prm_name, prm_model) ,

_chip_width(_pBoardModel->_fSize_BoardModelWidthPx),
_rate_org_chip_width(1.0 / _chip_width)
{
    _class_name = "GraphBarActor";
    _pPxQuantity = prm_pPxQuantity;
    _is_new_PxQuantity = false;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model)
      : DefaultBoardActor(prm_name, prm_model) ,

_chip_width(_pBoardModel->_fSize_BoardModelWidthPx),
_rate_org_chip_width(1.0 / _chip_width)
{
    _class_name = "GraphBarActor";
    _pPxQuantity = NEW PxQuantity();
    _is_new_PxQuantity = true;
    _min_val = INT_MIN;
    _max_val = INT_MAX;
}

void GraphBarActor::linkQty(PxQuantity* prm_pPxQuantity) {
    if (_pPxQuantity) {
        if (_is_new_PxQuantity) {
            GGAF_DELETE(_pPxQuantity);
        }
    }
    _pPxQuantity = prm_pPxQuantity;
    _is_new_PxQuantity = false;
}

void GraphBarActor::processDraw() {
    float bar_width = (float)(_pPxQuantity->getPx());
    if (bar_width == 0.0f) { //I know float
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
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_local_left_top_Y) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, ANG_RAD(_RZ));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_Rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, (float)(C_PX(_X)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hTransformedX) に失敗しました。3");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, (float)(C_PX(_Y)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hTransformedY) に失敗しました。3");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_local_left_top_X) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_Z)));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_hDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_h_alpha) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, bar_width * _rate_org_chip_width * SC_R(_SX));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
    checkDxException(hr, D3D_OK, "GraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
    _pBoardModel->GgafDxBoardModel::draw(this);
}

GraphBarActor::~GraphBarActor() {
    if (_is_new_PxQuantity) {
        GGAF_DELETE(_pPxQuantity);
    }
}
