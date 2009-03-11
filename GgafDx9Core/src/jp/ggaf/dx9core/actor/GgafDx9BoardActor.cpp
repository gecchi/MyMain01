#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardActor::GgafDx9BoardActor(const char* prm_name, const char* prm_model_name, const char* prm_technique) : GgafDx9TransformedActor(prm_name) {
_TRACE_("GgafDx9BoardActor::GgafDx9BoardActor("<<prm_name<<","<<prm_model_name<<","<<prm_technique<<")");
    _class_name = "GgafDx9BoardActor";
    _technique = NEW char[51];
    strcpy(_technique, prm_technique);

    _pModelCon = (GgafDx9ModelConnection*)GgafDx9God::_pModelManager->getConnection(prm_model_name);
    _pBoardModel = (GgafDx9BoardModel*)_pModelCon->view();
    //モデルのマテリアルをコピーして保持
    _paD3DMaterial9 = NEW D3DMATERIAL9[1];
    _paD3DMaterial9[0] = *(_pBoardModel->_pD3DMaterial9_default);
    //エフェクト取得
    _pEffectCon = (GgafDx9EffectConnection*)GgafDx9God::_pEffectManager->getConnection("B/GgafDx9BoardEffect");
    _pBoardEffect = (GgafDx9BoardEffect*)_pEffectCon->view();

    _pattno_top = 0;
    _pattno_bottom = _pBoardModel->_pattno_max;
    _patteno_now = 0;


    _fAlpha = 1.0f;

}

void GgafDx9BoardActor::processDrawMain() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetTechnique(_technique);
    whetherGgafDx9CriticalException(hr, S_OK, "GgafDx9BoardActor::GgafDx9MeshActor SetTechnique() に失敗しました。");

    UINT numPass;
    hr = pID3DXEffect->Begin( &numPass, 0 );
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain Begin() に失敗しました。");
    for (UINT pass = 0; pass < numPass; pass++) {
        hr = pID3DXEffect->BeginPass(pass);
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardActor::draw BeginPass(0) に失敗しました。");
        _pBoardModel->draw(this);
        hr = pID3DXEffect->EndPass();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardActor::draw EndPass() に失敗しました。");
    }
    hr = pID3DXEffect->End();
    whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9BoardActor::processDrawMain End() に失敗しました。");


}

void GgafDx9BoardActor::setPatternNo(int prm_pattno) {
//    if (_patteno_now == prm_pattno) {
//        return;
//    } else {
//        _patteno_now = prm_pattno;
//        static GgafDx9RectUV* pRectUV_Active;
//        pRectUV_Active = (_pBoardModel->_paRectUV) + prm_pattno;
//        _paVertex[0].tu = pRectUV_Active->_aUV[0].tu;
//        _paVertex[0].tv = pRectUV_Active->_aUV[0].tv;
//        _paVertex[1].tu = pRectUV_Active->_aUV[1].tu;
//        _paVertex[1].tv = pRectUV_Active->_aUV[1].tv;
//        _paVertex[2].tu = pRectUV_Active->_aUV[2].tu;
//        _paVertex[2].tv = pRectUV_Active->_aUV[2].tv;
//        _paVertex[3].tu = pRectUV_Active->_aUV[3].tu;
//        _paVertex[3].tv = pRectUV_Active->_aUV[3].tv;
//    }
}

GgafDx9BoardActor::~GgafDx9BoardActor() {
    DELETEARR_IMPOSSIBLE_NULL(_technique);
    _pModelCon->close();
    _pEffectCon->close();
    DELETEARR_IMPOSSIBLE_NULL(_paD3DMaterial9);
}
