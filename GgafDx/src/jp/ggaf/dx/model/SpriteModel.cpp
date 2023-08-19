#include "jp/ggaf/dx/model/SpriteModel.h"

#include "jp/ggaf/dx/Caretaker.h"
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

SpriteModel::SpriteModel(const char* prm_model_id) : Model(prm_model_id), IPlaneModel() {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_SpriteModel | Obj_GgafDx_IPlaneModel;
    _paVertexBuffer = nullptr;
    _paVertexBuffer_data = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _nVertices = 4;
    _max_draw_set_num = 1;
}

HRESULT SpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
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
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        pDevice->SetStreamSource(0, _paVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(SpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pSpriteEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteEffect->_effect_name<<"("<<pSpriteEffect<<")");
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
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
#ifdef MY_DEBUG
    GgafCore::Caretaker::_num_draw++;
#endif
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
#ifdef MY_DEBUG
            GgafCore::Caretaker::_num_draw++;
#endif
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
    return D3D_OK;
}

void SpriteModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVertexBuffer_data == nullptr) {
        _papTextureConnection = nullptr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        loadMetaModelInfo(&xdata);
        if (_draw_set_num != 1) {
             _TRACE_("SpriteModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
             _draw_set_num = 1;
        }
        std::string sprx_filepath = getSpriteXFilePath(xdata.XFileNames[0]);
        ModelManager::SpriteXFileFmt xdata_spr;
        pModelManager->obtainSpriteModelInfo(&xdata_spr, sprx_filepath);

        _model_width_px = xdata_spr.Width;
        _model_height_px =  xdata_spr.Height;
        _row_texture_split = xdata_spr.TextureSplitRows;
        _col_texture_split = xdata_spr.TextureSplitCols;
        _paVertexBuffer_data = NEW SpriteModel::VERTEX[4];
        _size_vertices = sizeof(SpriteModel::VERTEX)*4;
        _size_vertex_unit = sizeof(SpriteModel::VERTEX);
        _nVertices = 4;
        _pa_texture_filenames = NEW std::string[1];
        _pa_texture_filenames[0] = std::string(xdata_spr.TextureFile);

        if (_draw_set_num != 1) {
            _TRACE_("SpriteModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
            _draw_set_num = 1;
        }
        //左上
        _paVertexBuffer_data[0].x = PX_DX(xdata_spr.Width)  / -2.0;
        _paVertexBuffer_data[0].y = PX_DX(xdata_spr.Height) /  2.0;
        _paVertexBuffer_data[0].z = 0.0f;
        _paVertexBuffer_data[0].nx = 0.0f;
        _paVertexBuffer_data[0].ny = 0.0f;
        _paVertexBuffer_data[0].nz = -1.0f;
        _paVertexBuffer_data[0].color = D3DCOLOR_ARGB(255,255,255,255);
        _paVertexBuffer_data[0].tu = 0.0f;
        _paVertexBuffer_data[0].tv = 0.0f;
        //右上
        _paVertexBuffer_data[1].x = PX_DX(xdata_spr.Width)  /  2.0;
        _paVertexBuffer_data[1].y = PX_DX(xdata_spr.Height) /  2.0;
        _paVertexBuffer_data[1].z = 0.0f;
        _paVertexBuffer_data[1].nx = 0.0f;
        _paVertexBuffer_data[1].ny = 0.0f;
        _paVertexBuffer_data[1].nz = -1.0f;
        _paVertexBuffer_data[1].color = D3DCOLOR_ARGB(255,255,255,255);
        _paVertexBuffer_data[1].tu = (float)(1.0 / xdata_spr.TextureSplitCols);
        _paVertexBuffer_data[1].tv = 0.0f;
        //左下
        _paVertexBuffer_data[2].x = PX_DX(xdata_spr.Width)  / -2.0;
        _paVertexBuffer_data[2].y = PX_DX(xdata_spr.Height) / -2.0;
        _paVertexBuffer_data[2].z = 0.0f;
        _paVertexBuffer_data[2].nx = 0.0f;
        _paVertexBuffer_data[2].ny = 0.0f;
        _paVertexBuffer_data[2].nz = -1.0f;
        _paVertexBuffer_data[2].color = D3DCOLOR_ARGB(255,255,255,255);
        _paVertexBuffer_data[2].tu = 0.0f;
        _paVertexBuffer_data[2].tv = (float)(1.0 / xdata_spr.TextureSplitRows);
        //右下
        _paVertexBuffer_data[3].x = PX_DX(xdata_spr.Width)  /  2.0;
        _paVertexBuffer_data[3].y = PX_DX(xdata_spr.Height) / -2.0;
        _paVertexBuffer_data[3].z = 0.0f;
        _paVertexBuffer_data[3].nx = 0.0f;
        _paVertexBuffer_data[3].ny = 0.0f;
        _paVertexBuffer_data[3].nz = -1.0f;
        _paVertexBuffer_data[3].color = D3DCOLOR_ARGB(255,255,255,255);
        _paVertexBuffer_data[3].tu = (float)(1.0 / xdata_spr.TextureSplitCols);
        _paVertexBuffer_data[3].tv = (float)(1.0 / xdata_spr.TextureSplitRows);


        transformPosVtx(_paVertexBuffer_data, _size_vertex_unit, _nVertices);

        //距離
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(_paVertexBuffer_data[0].x * _paVertexBuffer_data[0].x +
                                                          _paVertexBuffer_data[0].y * _paVertexBuffer_data[0].y +
                                                          _paVertexBuffer_data[0].z * _paVertexBuffer_data[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;

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
    }

    //バッファ作成
    if (_paVertexBuffer == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                SpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_paVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void *paVertexBuffer;
        hr = _paVertexBuffer->Lock(0, _size_vertices, (void**)&paVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(paVertexBuffer, _paVertexBuffer_data, _size_vertices); //paVertexBuffer ← _paVertexBuffer_data
        _paVertexBuffer->Unlock();
    }
    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = connectToTextureManager(_pa_texture_filenames[0].c_str());
    }

    _TRACE3_("_model_id=" << _model_id << " end");
}

void SpriteModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void SpriteModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    GGAF_RELEASE(_paVertexBuffer);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    _TRACE3_("_model_id=" << _model_id << " end");
}

SpriteModel::~SpriteModel() {
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    GGAF_DELETEARR(_paVertexBuffer_data);
}

