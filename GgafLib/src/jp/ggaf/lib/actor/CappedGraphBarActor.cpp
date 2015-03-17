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
        throwGgafCriticalException("CappedGraphBarActor::processDraw() X���W�A���C�����g�� ALIGN_LEFT �ȊO�o���܂���Bthis="<<NODE_INFO);
    }
#endif
    if (_valign == VALIGN_BOTTOM) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px));
    } else if (_valign == VALIGN_MIDDLE) {
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, (float)(-_pBoardModel->_model_height_px*0.5));
    } else { //VALIGN_TOP
        hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_y, 0.0f);
    }
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_y) �Ɏ��s���܂����B");

    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_rz, ANG_RAD(_rz));
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_rz) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_depth_z, (float)(C_PX(_z)));
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_depth_z) �Ɏ��s���܂����B");
//    hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_alpha, _alpha);
//    checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_alpha) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetValue(_pBoardEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "CappedGraphBarActor::draw() SetValue(_h_colMaterialDiffuse) �Ɏ��s���܂����B");

    if (bar_width > 0.0f) {
        //_pUvFlipper->_pattno_uvflip_now �� <=> �� "<" �̔ԍ��ɍ��킹�邱�ƁI
        if (bar_width > _chip_width*2) {
            // <=> �̐^�� = ��\��
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + (_chip_width * SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) �Ɏ��s���܂����B");

            float sx = (bar_width * _rate_org_chip_width) -  2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̍����i < ��\��
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, 1.0f * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + ((bar_width - _chip_width)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2 ; //���Ƃɖ߂�
        } else {

            // <=> �̍����i < ��\��
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) �Ɏ��s���܂����B");

            float sx = (bar_width * _rate_org_chip_width) * 0.5f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x + ((_chip_width*sx)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //���Ƃɖ߂�
        }
    } else {
        //���̒����̏ꍇ
        if (bar_width < -_chip_width*2) {
            // <=> �̐^�� = �𔽓]�\��
            _pUvFlipper->_pattno_uvflip_now++;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - (_chip_width * SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) �Ɏ��s���܂����B");

            float sx = (-bar_width * _rate_org_chip_width) - 2.0f;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̍����i < �𔽓]�\�����ĉE���i > ��\��
            _pUvFlipper->_pattno_uvflip_now--;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -1.0f * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > �𔽓]�\�����č����i < ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - (((-bar_width) - _chip_width)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);

            _pUvFlipper->_pattno_uvflip_now -=2; //���Ƃɖ߂�

        } else {
            float sx = (-bar_width * _rate_org_chip_width) * 0.5f;

            // <=> �̍����i < �𔽓]�\�����ĉE���i > ��\��
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_y, top_y);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_y) �Ɏ��s���܂����B3");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_local_left_top_x, 0.0f);
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_local_left_top_x) �Ɏ��s���܂����B");

            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sx, -sx * SC_R(_sx));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sx) �Ɏ��s���܂����B");
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_sy, SC_R(_sy));
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_sy) �Ɏ��s���܂����B");
            _pBoardModel->GgafDxBoardModel::draw(this);

            // <=> �̉E���i > �𔽓]�\�����č����i < ��\��
            _pUvFlipper->_pattno_uvflip_now += 2;
            hr = pID3DXEffect->SetFloat(_pBoardEffect->_h_transformed_x, left_x - ((_chip_width*sx)*SC_R(_sx)) );
            checkDxException(hr, D3D_OK, "CappedGraphBarActor::processDraw() SetFloat(_h_transformed_x) �Ɏ��s���܂����B3");
            _pBoardModel->GgafDxBoardModel::draw(this);
            _pUvFlipper->_pattno_uvflip_now -= 2; //���Ƃɖ߂�
        }
    }
}

CappedGraphBarActor::~CappedGraphBarActor() {
}
