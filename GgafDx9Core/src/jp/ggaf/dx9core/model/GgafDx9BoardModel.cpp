#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

DWORD GgafDx9BoardModel::FVF = (D3DFVF_XYZ | D3DFVF_TEX1);

GgafDx9BoardModel::GgafDx9BoardModel(char* prm_platemodel_name) :
    GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9BoardModel::GgafDx9BoardModel(" << _model_name << ")");
    _fSize_BoardModelWidth = 32.0f;
    _fSize_BoardModelHeight = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pattno_max = 1;
    _pTextureCon = NULL;
    _paRectUV = NULL;
    _pRectUV_drawlast = NULL;
}

//描画

HRESULT GgafDx9BoardModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
    TRACE("GgafDx9BoardModel::draw("<<prm_pActor_Target->getName()<<")");
    //GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
    static GgafDx9BoardActor* pBoardActor_Target;
    pBoardActor_Target = (GgafDx9BoardActor*)prm_pActor_Target;

    //α設定（効かないのでコメント）
    //	_pD3DMaterial9->Diffuse.a = pBoardActor_Target->_fAlpha;
    //	_pD3DMaterial9->Ambient.a = pBoardActor_Target->_fAlpha;
    //	GgafDx9God::_pID3DDevice9->SetMaterial(_pD3DMaterial9);

    if (GgafDx9ModelManager::_id_lastdraw != _id) {
        GgafDx9God::_pID3DDevice9->SetTexture(0, _pTextureCon->view());
        //ここらへんで　this が 0x0h になる
        GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9BoardModel::FVF);

    } else {
        //ちょっとだけ早いのかどうか
    }
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
    GgafDx9God::_pID3DDevice9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pBoardActor_Target->_paVertex,
                                               pBoardActor_Target->_size_vertec_unit);
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);

    //↑＜2008/10/24 の脳みそ＞
    //GgafDx9God::_pID3DDevice9->SetMaterial で色をマテリアルで変更できると思っていた。
    //だがしかし、いろいろやってもできなかった。 トランスフォーム済み（FVF に D3DFVF_XYZRHW 付）はマテリアルが適用されない（αができない）・・・
    //というか、マテリアル適用は固定パイプラインの工程内ということなのか、よくわからない。
    //しかし頂点カラーは適用される、これはどこで行われるのか。レンダの最後らへんで頂点カラーは適用されるということなのか？
    //
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_MATERIAL); //マテリアル情報元をマテリアルにする
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1); //マテリアル情報元を頂点カラーにする
    //
    //とかあるので、マテリアルも頂点カラーも最後のレンダリング時に設定できるものと思ってた。違うのか、正しいのか、設定が足りないのか･･･。
    //TODO:とりあえずα（マテリアル）は後回し。

    GgafDx9ModelManager::_id_lastdraw = _id; //前回描画モデル名保存
    //GgafGod::_num_actor_playing++;
    return D3D_OK;
}

void GgafDx9BoardModel::restore() {
    _TRACE_("GgafDx9BoardModel::restore() " << _model_name << " start");
    GgafDx9God::_pModelManager->restoreBoardModel(this);
    _TRACE_("GgafDx9BoardModel::restore() " << _model_name << " end");
}

void GgafDx9BoardModel::release() {
    _TRACE_("GgafDx9BoardModel::release() " << _model_name << " start");
    //GgafDx9ModelManager::_pTextureManager->releaseResourceConnection(_pTextureCon);
    if (_pTextureCon != NULL) {
        _pTextureCon->close();
    }
    DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
    _TRACE_("GgafDx9BoardModel::release() " << _model_name << " end");

}

void GgafDx9BoardModel::onDeviceLost() {
    _TRACE_("GgafDx9BoardModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9BoardModel::onDeviceLost() " << _model_name << " end");
}

GgafDx9BoardModel::~GgafDx9BoardModel() {
    _TRACE_("GgafDx9BoardModel::~GgafDx9BoardModel() " << _model_name << " start");
    release();
    _TRACE_("GgafDx9BoardModel::~GgafDx9BoardModel() " << _model_name << " end");
}
