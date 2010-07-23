#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardActor::GgafDx9BoardActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique) :
                                         GgafDx9DrawableActor(prm_name,
                                                              prm_model_id,
                                                              "B",
                                                              prm_effect_id,
                                                              "B",
                                                              prm_technique,
                                                              NULL) {
    _actor_class |= Obj_GgafDx9BoardActor;
    _class_name = "GgafDx9BoardActor";

    _pBoardModel = (GgafDx9BoardModel*)_pGgafDx9Model;
    _pBoardEffect = (GgafDx9BoardEffect*)_pGgafDx9Effect;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forcePtnNoRange(0, _pBoardModel->_pattno_max);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    _fAlpha = 1.0f;

    _isTransformed = true;
    _pFunc_calcRotMvWorldMatrix = NULL;
    _sx = 1.0f;
    _sy = 1.0f;
}

void GgafDx9BoardActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, _x);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, _y);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, _z);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, _sx);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_sx) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, _sy);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_sy) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pBoardModel->draw(this);
}

GgafDx9BoardActor::~GgafDx9BoardActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
