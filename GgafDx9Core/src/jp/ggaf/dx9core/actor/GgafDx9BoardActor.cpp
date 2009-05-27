#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardActor::GgafDx9BoardActor(const char* prm_name,
                                     const char* prm_model_name,
                                     const char* prm_effect,
                                     const char* prm_technique) : GgafDx9TransformedActor(prm_name) {
    _class_name = "GgafDx9BoardActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model_name);
    _pBoardModel = (GgafDx9BoardModel*)_pModelCon->view();
    //モデルのマテリアルをコピーして保持(2009/3/10 現在マテリアル未使用。将来使うかも。)
    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
    _paD3DMaterial9[0] = *(_pBoardModel->_pD3DMaterial9_default);
    _fAlpha = 1.0;
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection(prm_effect);
    _pBoardEffect = (GgafDx9BoardEffect*)_pEffectCon->view();
    _pattno_top = 0;
    _pattno_bottom = _pBoardModel->_pattno_max;
    _patteno_now = 0;
}

void GgafDx9BoardActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedX, _x);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedX) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hTransformedY, _y);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hTransformedY) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hDepthZ, _z);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hDepthZ) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pBoardEffect->_hAlpha, _fAlpha);
    mightDx9Exception(hr, D3D_OK, "GgafDx9BoardModel::draw SetFloat(_hAlpha) に失敗しました。");

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
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
