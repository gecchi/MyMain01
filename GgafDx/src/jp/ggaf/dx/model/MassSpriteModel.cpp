#include "jp/ggaf/dx/model/MassSpriteModel.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/effect/MassSpriteEffect.h"
#include "jp/ggaf/dx/actor/MassSpriteActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/TextureManager.h"

using namespace GgafDx;

MassSpriteModel::MassSpriteModel(const char* prm_model_id) : MassModel(prm_model_id), IPlaneModel() {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_MassSpriteModel | Obj_GgafDx_IPlaneModel;
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;
    _model_half_width_px = _model_width_px/2;
    _model_half_height_px = _model_height_px/2;
    _papTextureConnection = nullptr;
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    registerCallback_VertexModelInfo(MassSpriteModel::createVertexModel); //頂点レイアウト情報作成コールバック関数
}

void MassSpriteModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
    int element_num = 3;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    WORD  st0_offset_next = 0;
    //float x, y, z;    // :POSITION0 頂点座標
    out_info->paElement[0].Stream = 0;
    out_info->paElement[0].Offset = st0_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_POSITION;
    out_info->paElement[0].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //float nx, ny, nz; // :NORMAL0 法線
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_NORMAL;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
    //float tu, tv;    // : TEXCOORD0  テクスチャ座標
    out_info->paElement[2].Stream = 0;
    out_info->paElement[2].Offset = st0_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[2].UsageIndex = 0;
    //st0_offset_next += sizeof(float)*2;
    out_info->element_num = element_num;
}

HRESULT MassSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("MassSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
//    if (_paVertexBuffer_instancedata == nullptr) {
//        createVertexElements(); //デバイスロスト復帰時に呼び出される
//    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(_model_id<<" の描画セット数オーバー。_draw_set_num="<<_draw_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //対象Actor
    const MassSpriteActor* const pTargetActor = (MassSpriteActor*)prm_pActor_target;
    //対象MassSpriteActorのエフェクトラッパ
    MassSpriteEffect* const pMassSpriteEffect = (MassSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassSpriteEffect->_pID3DXEffect;

    HRESULT hr;
    //頂点バッファ(インスタンスデータ)書き換え
    UINT update_vertex_instancedata_size = _size_vertex_unit_instancedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm は臨時のテンポラリインスタンスデータ
    void* pDeviceMemory = 0;
    hr = _paVertexBuffer_instancedata->Lock(0, update_vertex_instancedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instancedata_size);
    hr = _paVertexBuffer_instancedata->Unlock();
    checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_id);

    //モデルが同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _paVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _paVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(_paIndexBuffer);
        checkDxException(hr, D3D_OK, "SetIndices に失敗しました。");

        hr = pID3DXEffect->SetFloat(pMassSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");

        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassSpriteActor::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            pDevice->SetTexture(0, nullptr);
        }
    }

    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 に失敗しました。prm_draw_set_num="<<prm_draw_set_num);

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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassSpriteEffect->_effect_name<<"("<<pMassSpriteEffect<<")");
        hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassSpriteEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassSpriteEffect->_effect_name);
    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
#ifdef MY_DEBUG
    GgafCore::Caretaker::_num_draw++;
#endif
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");

        for (UINT pass = 1; pass < _num_pass; pass++) {
            hr = pID3DXEffect->BeginPass(pass);
            checkDxException(hr, D3D_OK, pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                               0,
                                               0,
                                               _nVertices,
                                               0,
                                               _nFaces);
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
    EffectManager::_pEffect_active = pMassSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void MassSpriteModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");

    if (_paVtxBuffer_data_model == nullptr) {
        HRESULT hr;
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::SpriteXFileFmt xdata;
        std::string model_def_file = std::string(_model_id) + ".sprx";
        std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
        if (model_def_filepath == "") {
            throwCriticalException("MassSpriteModel::restore() "+model_def_file+" が見つかりません");
        }
        pModelManager->obtainSpriteModelInfo(&xdata, model_def_filepath);
        _model_width_px  = xdata.Width;
        _model_height_px = xdata.Height;
        _model_half_width_px = _model_width_px/2;
        _model_half_height_px = _model_height_px/2;
        _row_texture_split = xdata.TextureSplitRows;
        _col_texture_split = xdata.TextureSplitCols;

        _draw_set_num = xdata.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MassSpriteModel::restore() "<<_model_id<<" の同時描画セット数は、最大の "<<_max_draw_set_num<<" に再定義されました。理由：_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MassSpriteModel::restore() "<<_model_id<<" の同時描画セット数は "<<_draw_set_num<<" です。");
        }

        _nVertices = 4;
        _nFaces = 2;
        _paVtxBuffer_data_model = NEW MassSpriteModel::VERTEX_model[_nVertices];
        _size_vertex_unit_model = sizeof(MassSpriteModel::VERTEX_model);
        _size_vertices_model = sizeof(MassSpriteModel::VERTEX_model) * _nVertices;

//        float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
//        float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)
        double du = 0.0;
        double dv = 0.0;
        //左上
        _paVtxBuffer_data_model[0].x = PX_DX(xdata.Width)  / -2.0;
        _paVtxBuffer_data_model[0].y = PX_DX(xdata.Height) /  2.0;
        _paVtxBuffer_data_model[0].z = 0.0f;
        _paVtxBuffer_data_model[0].nx = 0.0f;
        _paVtxBuffer_data_model[0].ny = 0.0f;
        _paVtxBuffer_data_model[0].nz = -1.0f;
        _paVtxBuffer_data_model[0].tu = du;
        _paVtxBuffer_data_model[0].tv = dv;
        //右上
        _paVtxBuffer_data_model[1].x = PX_DX(xdata.Width)  / 2.0;
        _paVtxBuffer_data_model[1].y = PX_DX(xdata.Height) / 2.0;
        _paVtxBuffer_data_model[1].z = 0.0f;
        _paVtxBuffer_data_model[1].nx = 0.0f;
        _paVtxBuffer_data_model[1].ny = 0.0f;
        _paVtxBuffer_data_model[1].nz = -1.0f;
        _paVtxBuffer_data_model[1].tu = (1.0/xdata.TextureSplitCols) - du;
        _paVtxBuffer_data_model[1].tv = dv;
        //左下
        _paVtxBuffer_data_model[2].x = PX_DX(xdata.Width)  / -2.0;
        _paVtxBuffer_data_model[2].y = PX_DX(xdata.Height) / -2.0;
        _paVtxBuffer_data_model[2].z = 0.0f;
        _paVtxBuffer_data_model[2].nx = 0.0f;
        _paVtxBuffer_data_model[2].ny = 0.0f;
        _paVtxBuffer_data_model[2].nz = -1.0f;
        _paVtxBuffer_data_model[2].tu = du;
        _paVtxBuffer_data_model[2].tv = (1.0/xdata.TextureSplitRows) - dv;
        //右下
        _paVtxBuffer_data_model[3].x = PX_DX(xdata.Width)  /  2.0;
        _paVtxBuffer_data_model[3].y = PX_DX(xdata.Height) / -2.0;
        _paVtxBuffer_data_model[3].z = 0.0f;
        _paVtxBuffer_data_model[3].nx = 0.0f;
        _paVtxBuffer_data_model[3].ny = 0.0f;
        _paVtxBuffer_data_model[3].nz = -1.0f;
        _paVtxBuffer_data_model[3].tu = 1.0/xdata.TextureSplitCols;
        _paVtxBuffer_data_model[3].tv = 1.0/xdata.TextureSplitRows;

        _paIndexBuffer_data = NEW WORD[(_nFaces*3)];
        _paIndexBuffer_data[0] = 0;
        _paIndexBuffer_data[1] = 1;
        _paIndexBuffer_data[2] = 2;

        _paIndexBuffer_data[3] = 1;
        _paIndexBuffer_data[4] = 3;
        _paIndexBuffer_data[5] = 2;

        //距離
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[0].x * _paVtxBuffer_data_model[0].x +
                                                          _paVtxBuffer_data_model[0].y * _paVtxBuffer_data_model[0].y +
                                                          _paVtxBuffer_data_model[0].z * _paVtxBuffer_data_model[0].z));
        _bounding_sphere_radius = model_bounding_sphere_radius;

        setMaterial();
//        _pa_texture_filenames = NEW std::string[1]; ////setMaterial();で実行済み
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);
    }

    //デバイスに頂点バッファ作成(モデル)
    if (_paVertexBuffer_model == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_paVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_id));
        //バッファへ作成済み頂点データを流し込む
        void* pDeviceMemory = 0;
        hr = _paVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_id);
        memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
        hr = _paVertexBuffer_model->Unlock();
        checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_id);
    }

    //デバイスにインデックスバッファ作成
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_paIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<_model_id);
        void* pDeviceMemory = 0;
        hr = _paIndexBuffer->Lock(0, 0, (void**)&pDeviceMemory,0);
        checkDxException(hr, D3D_OK, "インデックスバッファのロック取得に失敗 model="<<_model_id);
        memcpy(pDeviceMemory, _paIndexBuffer_data, sizeof(WORD)*_nFaces*3);
        hr = _paIndexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "インデックスバッファのアンロック取得に失敗 model="<<_model_id);
    }
    //デバイスにテクスチャ作成
    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    MassModel::restore(); //上位を呼び出す
    _TRACE3_("_model_id=" << _model_id << " end");
}

MassSpriteModel::~MassSpriteModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

