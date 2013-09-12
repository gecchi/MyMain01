#include "stdafx.h"
#include "GraphBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GraphBar::GraphBar(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity)
      : DefaultBoardActor(prm_name, prm_model) {
    _class_name = "GraphBar";
    pPxQuantity_ = prm_pPxQuantity;
    org_width_ = _pBoardModel->_fSize_BoardModelWidthPx;
    rate_org_width_ = 1.0 / org_width_;
}

void GraphBar::processBehavior() {
//    _SX = R_SC(pPxQuantity_->getPx() * rate_org_width_); //â°ï˚å¸Ç…î{ó¶Ç≈êLÇŒÇ∑
    _pUvFlipper->behave();
}

void GraphBar::processDraw() {
    float bar_width = (float)(pPxQuantity_->getPx());
    if (bar_width <= 0.0f) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    float bar_chip_width = org_width_;
    float left_x = (float)(C_PX(_X));
    float top_y = (float)(C_PX(_Y));
    HRESULT hr;

    if (bar_width > bar_chip_width*2) {
        // <=> ÇÃê^ÇÒíÜ = Çï\é¶
        _pUvFlipper->_pattno_uvflip_now++;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (bar_chip_width*0.5f));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

        float sx = (bar_width - bar_chip_width*2) / bar_width;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> ÇÃç∂ïîïi < Çï\é¶
        _pUvFlipper->_pattno_uvflip_now--;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, 1.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> ÇÃâEïîïi > Çï\é¶
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + bar_width - bar_chip_width);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now --; //Ç‡Ç∆Ç…ñﬂÇ∑
    } else {

        float sx = (bar_width*0.5) / bar_chip_width;
        // <=> ÇÃç∂ïîïi < Çï\é¶
        _pUvFlipper->_pattno_uvflip_now--;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");

        sx = (bar_width - bar_chip_width*2) / bar_width;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> ÇÃâEïîïi > Çï\é¶
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (bar_chip_width*sx));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) Ç…é∏îsÇµÇ‹ÇµÇΩÅB3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now --; //Ç‡Ç∆Ç…ñﬂÇ∑
    }
}

GraphBar::~GraphBar() {
}
