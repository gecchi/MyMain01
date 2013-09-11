#include "stdafx.h"
#include "GraphBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/lib/util/AmountGraph.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

GraphBar::GraphBar(const char* prm_name, const char* prm_model, AmountGraph* prm_pAmount)
      : DefaultBoardActor(prm_name, prm_model) {
    _class_name = "GraphBar";
    pAmount_ = prm_pAmount;
    org_width_ = _pBoardModel->_fSize_BoardModelWidthPx;
    rate_org_width_ = 1.0 / org_width_;
}

void GraphBar::processBehavior() {
//    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //横方向に倍率で伸ばす
    _pUvFlipper->behave();
}

void GraphBar::processDraw() {
    float bar_width = (float)(pAmount_->getPx());
    if (bar_width <= 0.0f) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    float bar_chip_width = org_width_;
    float left_x = (float)(C_PX(_X));
    float top_y = (float)(C_PX(_Y));
    HRESULT hr;

    if (bar_width > bar_chip_width*2) {
        // <=> の真ん中 = を表示
        _pUvFlipper->_pattno_uvflip_now++;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (bar_chip_width*0.5f));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) に失敗しました。3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) に失敗しました。");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) に失敗しました。");

        float sx = (bar_width - bar_chip_width*2) / bar_width;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) に失敗しました。");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> の左部品 < を表示
        _pUvFlipper->_pattno_uvflip_now--;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, 1.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) に失敗しました。");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> の右部品 > を表示
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + bar_width - bar_chip_width);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now --; //もとに戻す
    } else {

        float sx = (bar_width*0.5) / bar_chip_width;
        // <=> の左部品 < を表示
        _pUvFlipper->_pattno_uvflip_now--;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) に失敗しました。3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) に失敗しました。");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) に失敗しました。");

        sx = (bar_width - bar_chip_width*2) / bar_width;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) に失敗しました。");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> の右部品 > を表示
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (bar_chip_width*sx));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now --; //もとに戻す
    }
}

GraphBar::~GraphBar() {
}
