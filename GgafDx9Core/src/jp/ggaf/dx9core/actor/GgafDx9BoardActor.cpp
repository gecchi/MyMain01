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

    _class_name = "GgafDx9BoardActor";

    _pBoardModel = (GgafDx9BoardModel*)_pGgafDx9Model;
    _pBoardEffect = (GgafDx9BoardEffect*)_pGgafDx9Effect;

    _fAlpha = 1.0f;

    _pattno_top = 0;
    _pattno_bottom = _pBoardModel->_pattno_max;
    _patteno_now = 0;

    _isTransformed = true;
    _pFunc_calcWorldMatrix = NULL;
}

void GgafDx9BoardActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, _x);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, _y);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, _z);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) に失敗しました。");

    _pBoardModel->draw(this);
}

void GgafDx9BoardActor::setPatternNo(int prm_pattno) {
    if (_pattno_top <= prm_pattno && prm_pattno <= _pattno_bottom) {
        _patteno_now = prm_pattno;
    } else if (prm_pattno < _pattno_top) {
        _patteno_now = _pattno_top;
    } else if (prm_pattno > _pattno_bottom) {
        _patteno_now = _pattno_bottom;
    }
}

GgafDx9BoardActor::~GgafDx9BoardActor() {
//    DELETEARR_IMPOSSIBLE_NULL(_technique);
//    _pModelCon->close();
//    _pEffectCon->close();
//
//    DELETEARR_POSSIBLE_NULL(_paD3DMaterial9);
    //GgafDx9BoardActorはマテリアルを使わないので_paD3DMaterial9はNULLのままである
}
