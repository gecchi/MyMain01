#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


DWORD GgafDx9PlateModel::FVF =  (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);

GgafDx9PlateModel::GgafDx9PlateModel(char* prm_platemodel_name) : GgafDx9Model(prm_platemodel_name) {
    TRACE("GgafDx9PlateModel::GgafDx9PlateModel(" <<  _model_name << ")");
	_fSize_PlateModelWidth  = 32.0f;
	_fSize_PlateModelHeight = 32.0f;
	_iRowNum_TextureSplit    = 1;
	_iColNum_TextureSplit    = 1;
	_iPatternNo_Max = 1;
	_pTexture = NULL;
	_paRectUV = NULL;
	_pRectUV_drawlast = NULL;
}



//描画

HRESULT GgafDx9PlateModel::draw(GgafDx9BaseActor* prm_pActor_Target) {
	TRACE("GgafDx9PlateModel::draw("<<prm_pActor_Target->getName()<<")");
	//GgafDx9God::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0x000000, 1.0, 0);
	GgafDx9PlateActor* pPlateActor_Target = (GgafDx9PlateActor*)prm_pActor_Target;


	//α設定（効かないのでコメント）
//	_pD3DMaterial9->Diffuse.a = pPlateActor_Target->_fAlpha;
//	_pD3DMaterial9->Ambient.a = pPlateActor_Target->_fAlpha;
//	GgafDx9God::_pID3DDevice9->SetMaterial(_pD3DMaterial9);

	if (GgafDx9God::_pModelManager->_id_lastdraw != _id) {
		GgafDx9God::_pID3DDevice9->SetTexture( 0, _pTexture->getResource() );
		//ここらへんで　this が 0x0h になる
		GgafDx9God::_pID3DDevice9->SetFVF(GgafDx9PlateModel::FVF);

	} else {
		//ちょっとだけ早いのよ！
	}
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE); //ライトオフ
	GgafDx9God::_pID3DDevice9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pPlateActor_Target->_paVertex, pPlateActor_Target->_iSize_Vertec_unit);
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

	GgafDx9God::_pModelManager->_id_lastdraw = _id; //前回描画モデル名保存
	//GgafGod::_iNumPlayingActor++;
	return D3D_OK;
}


void GgafDx9PlateModel::restore() {
	_TRACE_("GgafDx9PlateModel::restore() " <<  _model_name << " start");
	GgafDx9God::_pModelManager->restorePlateModel(this);
	_TRACE_("GgafDx9PlateModel::restore() " <<  _model_name << " end");
}

void GgafDx9PlateModel::release() {
	_TRACE_("GgafDx9PlateModel::release() " <<  _model_name << " start");
	//GgafDx9ModelManager::_pTextureManager->releaseResourceLead(_pTexture);
	RELEASE_SAFETY(_pTexture);
	DELETEARR_IMPOSSIBLE_NULL(_paRectUV);
	_TRACE_("GgafDx9PlateModel::release() " <<  _model_name << " end");


}

void GgafDx9PlateModel::onDeviceLost() {
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " start");
	release();
	_TRACE_("GgafDx9PlateModel::onDeviceLost() " <<  _model_name << " end");
}

GgafDx9PlateModel::~GgafDx9PlateModel() {
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " start");
    release();
    _TRACE_("GgafDx9PlateModel::~GgafDx9PlateModel() " <<  _model_name << " end");
}
