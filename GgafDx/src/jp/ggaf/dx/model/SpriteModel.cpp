#include "jp/ggaf/dx/model/SpriteModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/actor/SpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/SpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

DWORD SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

SpriteModel::SpriteModel(const char* prm_model_name) : Model(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDx_SpriteModel;
}

HRESULT SpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = God::_pID3DDevice9;
    _TRACE4_("SpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    //対象Actor
    const SpriteActor* const pTargetActor = (SpriteActor*)prm_pActor_target;
    //対象SpriteActorのエフェクトラッパ
    SpriteEffect* const pSpriteEffect = (SpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    float u,v;
    pTargetActor->_pUvFlipper->getUV(u,v);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(SpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name<<"("<<pSpriteEffect<<")");
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pSpriteEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }

        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }

    //前回描画モデル保持
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    return D3D_OK;
}

void SpriteModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    ModelManager* pModelManager = pGOD->_pModelManager;
    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = ModelManager::getSpriteFileName(_model_name, "sprx");
    ModelManager::SpriteXFileFmt xdata;
    pModelManager->obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px = xdata.width;
    _model_height_px =  xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //テクスチャ取得しモデルに保持させる
    TextureConnection* model_pTextureConnection = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(xdata.texture_file, this));

    //テクスチャの参照を保持させる。
    _papTextureConnection = NEW TextureConnection*[1];
    _papTextureConnection[0] = model_pTextureConnection;

    SpriteModel::VERTEX* paVertex = NEW SpriteModel::VERTEX[4];
    _size_vertices = sizeof(SpriteModel::VERTEX)*4;
    _size_vertex_unit = sizeof(SpriteModel::VERTEX);

    //頂点配列情報をモデルに保持させる
    //UVは左上の１つ分（アニメパターン０）をデフォルトで設定する。
    //シェーダーが描画時にアニメパターン番号をみてUV座標をずらす仕様としよっと。
    //x,y の ÷2 とは、モデル中心をローカル座標の原点中心としたいため
//    float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
//    float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)
    double du = 0.0;
    double dv = 0.0;
    //左上
    paVertex[0].x = PX_DX(xdata.width)  / -2.0;
    paVertex[0].y = PX_DX(xdata.height) /  2.0;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = (float)du;
    paVertex[0].tv = (float)dv;
    //右上
    paVertex[1].x = PX_DX(xdata.width)  /  2.0;
    paVertex[1].y = PX_DX(xdata.height) /  2.0;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = (float)((1.0 / xdata.col_texture_split) - du);
    paVertex[1].tv = (float)dv;
    //左下
    paVertex[2].x = PX_DX(xdata.width)  / -2.0;
    paVertex[2].y = PX_DX(xdata.height) / -2.0;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = (float)du;
    paVertex[2].tv = (float)((1.0 / xdata.row_texture_split) - dv);

    //右下
    paVertex[3].x = PX_DX(xdata.width)  /  2.0;
    paVertex[3].y = PX_DX(xdata.height) / -2.0;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = (float)((1.0 / xdata.col_texture_split) - du);
    paVertex[3].tv = (float)((1.0 / xdata.row_texture_split) - dv);

    //距離
    FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(paVertex[0].x * paVertex[0].x +
                                                      paVertex[0].y * paVertex[0].y +
                                                      paVertex[0].z * paVertex[0].z));
    _bounding_sphere_radius = model_bounding_sphere_radius;


    //バッファ作成
    if (_pVertexBuffer == nullptr) {

        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                SpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
    }
    //頂点バッファ作成
    //頂点情報をビデオカード頂点バッファへロード
    void *pVertexBuffer;
    hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);

    memcpy(pVertexBuffer, paVertex, _size_vertices); //pVertexBuffer ← paVertex
    _pVertexBuffer->Unlock();

    _num_materials = 1;
    D3DMATERIAL9* paMaterial;
    paMaterial = NEW D3DMATERIAL9[_num_materials];
    for ( DWORD i = 0; i < _num_materials; i++) {
        //paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        paMaterial[i].Diffuse.r = 1.0f;
        paMaterial[i].Diffuse.g = 1.0f;
        paMaterial[i].Diffuse.b = 1.0f;
        paMaterial[i].Diffuse.a = 1.0f;
        paMaterial[i].Ambient.r = 1.0f;
        paMaterial[i].Ambient.g = 1.0f;
        paMaterial[i].Ambient.b = 1.0f;
        paMaterial[i].Ambient.a = 1.0f;
    }
    _paMaterial_default = paMaterial;
    //後始末
    GGAF_DELETEARR(paVertex);
    _TRACE3_("_model_name=" << _model_name << " end");
}

void SpriteModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void SpriteModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");
}

SpriteModel::~SpriteModel() {
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}

