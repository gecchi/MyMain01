#include "stdafx.h"
#include "jp/ggaf/lib/actor/GraphBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/lib/util/AmountGraph.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

GraphBarActor::GraphBarActor(const char* prm_name, const char* prm_model, AmountGraph* prm_pAmount)
      : DefaultBoardActor(prm_name, prm_model) {
    _class_name = "GraphBarActor";
    pAmount_ = prm_pAmount;
    chip_width_ = _pBoardModel->_fSize_BoardModelWidthPx;
    rate_org_chip_width_ = 1.0 / chip_width_;
}

void GraphBarActor::processBehavior() {
//    _SX = R_SC(pAmount_->getPx() * rate_org_width_); //横方向に倍率で伸ばす
    _pUvFlipper->behave();
}

void GraphBarActor::processDraw() {
    float bar_width = (float)(pAmount_->getPx());
    if (bar_width <= 0.0f) {
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    float left_x = (float)(C_PX(_X));
    float top_y = (float)(C_PX(_Y));
    HRESULT hr;
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_Y) に失敗しました。");
    if (bar_width > chip_width_*2) {
        // <=> の真ん中 = を表示
        _pUvFlipper->_pattno_uvflip_now++;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (chip_width_ * SC_R(_SX)) );
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) に失敗しました。3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) に失敗しました。");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) に失敗しました。");
        float sx = (bar_width * rate_org_chip_width_) -  2.0f;
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
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, 1.0f * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) に失敗しました。");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> の右部品 > を表示
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + ((bar_width - chip_width_)*SC_R(_SX)) );
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now -=2 ; //もとに戻す
    } else {

        // <=> の左部品 < を表示
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) に失敗しました。3");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_local_left_top_X) に失敗しました。");

        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(C_PX(_Z)));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_alpha) に失敗しました。");

//        float sx = bar_width / (chip_width_*2.0f);
        float sx = (bar_width * rate_org_chip_width_) * 0.5f;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, 0.0f);
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_h_Rz) に失敗しました。");
        _pBoardModel->GgafDxBoardModel::draw(this);

        // <=> の右部品 > を表示
        _pUvFlipper->_pattno_uvflip_now += 2;
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + ((chip_width_*sx)*SC_R(_SX)) );
        checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) に失敗しました。3");
        _pBoardModel->GgafDxBoardModel::draw(this);

        _pUvFlipper->_pattno_uvflip_now -=2; //もとに戻す
    }
}

GraphBarActor::~GraphBarActor() {
}
