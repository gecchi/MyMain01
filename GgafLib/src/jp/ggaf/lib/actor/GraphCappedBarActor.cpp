#include "stdafx.h"
#include "jp/ggaf/lib/actor/GraphCappedBarActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

GraphCappedBarActor::GraphCappedBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity)
      : GraphBarActor(prm_name, prm_model, prm_pPxQuantity) {
    _class_name = "GraphCappedBarActor";
}

GraphCappedBarActor::GraphCappedBarActor(const char* prm_name, const char* prm_model)
      : GraphBarActor(prm_name, prm_model) {
    _class_name = "GraphCappedBarActor";
}

void GraphCappedBarActor::processDraw() {
    float bar_width = (float)(_pPxQuantity->getPx());
    if (bar_width == 0.0f) { //I know float
        return;
    }
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    float left_x = (float)(C_PX(_X));
    float top_y = (float)(C_PX(_Y));
    HRESULT hr;
#ifdef MY_DEBUG
    if (_align != ALIGN_LEFT) {
        throwGgafCriticalException("GraphCappedBarActor::processDraw() X���W�A���C�����g�� ALIGN_LEFT �ȊO�o���܂���Bname="<<getName()<<" this="<<this);
    }
#endif
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, (float)(-_pBoardModel->_fSize_BoardModelHeightPx*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_Y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_local_left_top_Y) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_Rz, ANG_RAD(_RZ));
    checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_Rz) �Ɏ��s���܂����B");
    if (bar_width > 0.0f) {
        //_pUvFlipper->_pattno_uvflip_now �� <=> �� "<" �̔ԍ��ɍ��킹�邱�ƁI
        if (bar_width > _chip_width*2) {
            // <=> �̐^�� = ��\��
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + (_chip_width * SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedY) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_local_left_top_X) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_Z)));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_alpha) �Ɏ��s���܂����B");
            float sx = (bar_width * _rate_org_chip_width) -  2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̍����i < ��\��
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, 1.0f * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + ((bar_width - _chip_width)*SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2 ; //���Ƃɖ߂�
        } else {

            // <=> �̍����i < ��\��
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedY) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_local_left_top_X) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_Z)));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_alpha) �Ɏ��s���܂����B");

            float sx = (bar_width * _rate_org_chip_width) * 0.5f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, sx * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x + ((_chip_width*sx)*SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //���Ƃɖ߂�
        }
    } else {
        //���̒����̏ꍇ
        if (bar_width < -_chip_width*2) {
            // <=> �̐^�� = �𔽓]�\��
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x - (_chip_width * SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedY) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_local_left_top_X) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_Z)));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_alpha) �Ɏ��s���܂����B");
            float sx = (-bar_width * _rate_org_chip_width) - 2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, -sx * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̍����i < �𔽓]�\�����ĉE���i > ��\��
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, -1.0f * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > �𔽓]�\�����č����i < ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x - (((-bar_width) - _chip_width)*SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //���Ƃɖ߂�

        } else {
            float sx = (-bar_width * _rate_org_chip_width) * 0.5f;

            // <=> �̍����i < �𔽓]�\�����ĉE���i > ��\��
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, top_y);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedY) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_X, 0.0f);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_local_left_top_X) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, (float)(C_PX(_Z)));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hDepthZ) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_h_alpha) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, -sx * SC_R(_SX));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, SC_R(_SY));
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > �𔽓]�\�����č����i < ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, left_x - ((_chip_width*sx)*SC_R(_SX)) );
            checkDxException(hr, D3D_OK, "GraphCappedBarActor::processDraw() SetFloat(_hTransformedX) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);
            _pUvFlipper->_pattno_uvflip_now -= 2; //���Ƃɖ߂�
        }
    }
}

GraphCappedBarActor::~GraphCappedBarActor() {
    if (_is_new_PxQuantity) {
        GGAF_DELETE(_pPxQuantity);
    }
}
