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
    _obj_class |= Obj_GgafDx9BoardActor;
    _class_name = "GgafDx9BoardActor";

    _pBoardModel = (GgafDx9BoardModel*)_pGgafDx9Model;
    _pBoardEffect = (GgafDx9BoardEffect*)_pGgafDx9Effect;
    _pUvFlipper = NEW GgafDx9UvFlipper(_pBoardModel->_papTextureCon[0]->refer());
    _pUvFlipper->setRotation(_pBoardModel->_col_texture_split,
                             _pBoardModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    _fAlpha = 1.0f;
    _is2DActor = true;
    _pFunc_calcRotMvWorldMatrix = NULL;
    _Z = 0;
}

void GgafDx9BoardActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, float(cnvCoordApp2Pix(_X)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, float(cnvCoordApp2Pix(_Y)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(cnvCoordApp2Pix(_Z)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, float(cnvScaleApp2Rate(_SX)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_sx) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, float(cnvScaleApp2Rate(_SY)));
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_sy) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pBoardModel->draw(this);
}

GgafDx9BoardActor::~GgafDx9BoardActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
