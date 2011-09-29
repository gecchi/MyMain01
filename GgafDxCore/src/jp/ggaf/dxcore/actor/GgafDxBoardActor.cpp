#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxBoardActor::GgafDxBoardActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique) :
                                         GgafDxDrawableActor(prm_name,
                                                              prm_model_id,
                                                              "B",
                                                              prm_effect_id,
                                                              "B",
                                                              prm_technique,
                                                              NULL,
                                                              NULL) {
    _obj_class |= Obj_GgafDxBoardActor;
    _class_name = "GgafDxBoardActor";

    _pBoardModel = (GgafDxBoardModel*)_pModel;
    _pBoardEffect = (GgafDxBoardEffect*)_pEffect;
    _pUvFlipper = NEW GgafDxUvFlipper(_pBoardModel->_papTextureCon[0]->use());
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

void GgafDxBoardActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, float(App2Pix(_X)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedX) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, float(App2Pix(_Y)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hTransformedY) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, float(App2Pix(_Z)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hDepthZ) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_hAlpha) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSx, float(cnvScaleApp2Rate(_SX)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sx) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hSy, float(cnvScaleApp2Rate(_SY)));
    checkDxException(hr, D3D_OK, "GgafDxBoardModel::draw SetFloat(_sy) ‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
    _pBoardModel->draw(this);
}
void GgafDxBoardActor::locateAs(GgafDxGeoElem* prm_pGeoElem) {
    _X = prm_pGeoElem->_X;
    _Y = prm_pGeoElem->_Y;
}

GgafDxBoardActor::~GgafDxBoardActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
