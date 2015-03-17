#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

CappedGraphBarActor::CappedGraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQty)
      : GraphBarActor(prm_name, prm_model, prm_pPxQty) {
    _class_name = "CappedGraphBarActor";
}

CappedGraphBarActor::CappedGraphBarActor(const char* prm_name, const char* prm_model)
      : GraphBarActor(prm_name, prm_model) {
    _class_name = "CappedGraphBarActor";
}

void CappedGraphBarActor::processDraw() {
    float bar_width = (float)(_pPxQty->getPx());
    if (bar_width == 0.0f) { //I know float ==
        return;
    }
    ID3DXEffect* const pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    float left_x = (float)(C_PX(_x));
    float top_y = (float)(C_PX(_y));
    HRESULT hr;
#ifdef MY_DEBUG
    if (_align != ALIGN_LEFT) {
        throwGgafCriticalException("CappedGraphBarActor::processDraw() X座標アライメントは ALIGN_LEFT 以外出来ません。this="<<NODE_INFO);
    }
#endif
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_y) に失敗しました。");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_depth_z, (float)(C_PX(_z)));
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_depth_z) に失敗しました。");
//    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_alpha) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::draw() SetValue(_h_colMaterialDiffuse) に失敗しました。");

    if (bar_width > 0.0f) {
        //_pUvFlipper->_pattno_uvflip_now は <=> の "<" の番号に合わせること！
        if (bar_width > _chip_width*2) {
            // <=> の真ん中 = を表示
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + (_chip_width * SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) に失敗しました。3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) に失敗しました。");

            float sx = (bar_width * _rate_org_chip_width) -  2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の左部品 < を表示
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, 1.0f * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の右部品 > を表示
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + ((bar_width - _chip_width)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2 ; //もとに戻す
        } else {

            // <=> の左部品 < を表示
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) に失敗しました。3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) に失敗しました。");

            float sx = (bar_width * _rate_org_chip_width) * 0.5f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の右部品 > を表示
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + ((_chip_width*sx)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //もとに戻す
        }
    } else {
        //負の長さの場合
        if (bar_width < -_chip_width*2) {
            // <=> の真ん中 = を反転表示
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - (_chip_width * SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) に失敗しました。3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) に失敗しました。");

            float sx = (-bar_width * _rate_org_chip_width) - 2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の左部品 < を反転表示して右部品 > を表示
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -1.0f * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の右部品 > を反転表示して左部品 < を表示
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - (((-bar_width) - _chip_width)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //もとに戻す

        } else {
            float sx = (-bar_width * _rate_org_chip_width) * 0.5f;

            // <=> の左部品 < を反転表示して右部品 > を表示
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) に失敗しました。3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) に失敗しました。");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) に失敗しました。");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) に失敗しました。");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> の右部品 > を反転表示して左部品 < を表示
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - ((_chip_width*sx)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) に失敗しました。3");
            _pBoardModel->GgafDxBoardModel::draw(this);
            _pUvFlipper->_pattno_uvflip_now -= 2; //もとに戻す
        }
    }
}

CappedGraphBarActor::~CappedGraphBarActor() {
}
