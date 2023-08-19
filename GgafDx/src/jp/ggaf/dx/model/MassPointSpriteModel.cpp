#include "jp/ggaf/dx/model/MassPointSpriteModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MassPointSpriteActor.h"
#include "jp/ggaf/dx/effect/MassPointSpriteEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;
//TODO:現在使えません。ビデオカード依存が高い為。

MassPointSpriteModel::MassPointSpriteModel(const char* prm_model_id) : MassModel(prm_model_id) {
    _TRACE3_("_model_id="<<_model_id);
    _obj_class |= Obj_GgafDx_MassPointSpriteModel;

    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
    _paVtxBuffer_data_model = nullptr;
//    _paIndexBuffer_data = nullptr;
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    registerCallback_VertexModelInfo(MassPointSpriteModel::createVertexModel); //頂点レイアウト情報作成コールバック関数
    _TRACE_("MassPointSpriteModel::MassPointSpriteModel(" << _model_id << ") End");
}

void MassPointSpriteModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
    int element_num = 4;
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
    //float psize;      // ポイントサイズ
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT1;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_PSIZE;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*1;
    //DWORD color;     // : COLOR0  頂点カラー
    out_info->paElement[2].Stream = 0;
    out_info->paElement[2].Offset = st0_offset_next;
    out_info->paElement[2].Type   = D3DDECLTYPE_D3DCOLOR;
    out_info->paElement[2].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[2].Usage  = D3DDECLUSAGE_COLOR;
    out_info->paElement[2].UsageIndex = 0;
    st0_offset_next += sizeof(DWORD);
    //float tu, tv;    // : TEXCOORD0  テクスチャ座標
    out_info->paElement[3].Stream = 0;
    out_info->paElement[3].Offset = st0_offset_next;
    out_info->paElement[3].Type   = D3DDECLTYPE_FLOAT2;
    out_info->paElement[3].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[3].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[3].UsageIndex = 0;
    st0_offset_next += sizeof(float)*2;

    out_info->element_num = element_num;
}

void MassPointSpriteModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    ModelManager* pModelManager = pCARETAKER->_pModelManager;
    HRESULT hr;
    if (!_paVtxBuffer_data_model) {

        ModelManager::ModelXFileFmt xdata;
        loadMetaModelInfo(&xdata);
        std::string psprx_filepath = getPointSpriteXFilePath(xdata.XFileNames[0]);

        ModelManager::PointSpriteXFileFmt xdata_pspr;
        pModelManager->obtainPointSpriteModelInfo(&xdata_pspr, psprx_filepath);
        //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
//        _num_materials = 1; //setMaterial();で実行済み
        setMaterial();
//        _pa_texture_filenames = NEW std::string[1]; //setMaterial();で実行済み
        _pa_texture_filenames[0] = std::string(xdata_pspr.TextureFile);

        //デバイスにテクスチャ作成 (下にも同じ処理があるが、下はデバイスロスト時実行)
        //頂点バッファのpsizeの算出に、テクスチャの長さが必要なため、ここで一旦求めている
        if (!_papTextureConnection) {
            _papTextureConnection = NEW TextureConnection*[1];
            _papTextureConnection[0] = connectToTextureManager(_pa_texture_filenames[0].c_str());
            Texture* pTex = _papTextureConnection[0]->peek();
            float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
            float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
            if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
                throwCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
            }
            _texture_size_px = tex_width;
        }
        _square_size_px = xdata_pspr.SquareSize;
        _texture_split_rowcol = xdata_pspr.TextureSplitRowCol;
        _inv_texture_split_rowcol = 1.0f / _texture_split_rowcol;
        _nVertices = xdata_pspr.VerticesNum;
        _draw_set_num = xdata_pspr.DrawSetNum;
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MassPointSpriteModel::restore() "<<_model_id<<" の同時描画セット数は、最大の "<<_max_draw_set_num<<" に再定義されました。理由：_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MassPointSpriteModel::restore() "<<_model_id<<" の同時描画セット数は "<<_draw_set_num<<" です。");
        }
        _nFaces = 0; //_nFacesは使用しない
        _paVtxBuffer_data_model = NEW MassPointSpriteModel::VERTEX_model[_nVertices*_draw_set_num];
        _size_vertex_unit_model = sizeof(MassPointSpriteModel::VERTEX_model);
        _size_vertices_model = sizeof(MassPointSpriteModel::VERTEX_model) * _nVertices*_draw_set_num;


        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data_model[i].x = xdata_pspr.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data_model[i].y = xdata_pspr.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data_model[i].z = xdata_pspr.paD3DVECTOR_Vertices[i].z;
            _paVtxBuffer_data_model[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata_pspr.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
                                                                                                    //シェーダーで拡大縮小ピクセルを計算
            _paVtxBuffer_data_model[i].color = D3DCOLOR_COLORVALUE(xdata_pspr.paD3DVECTOR_VertexColors[i].r,
                                                                   xdata_pspr.paD3DVECTOR_VertexColors[i].g,
                                                                   xdata_pspr.paD3DVECTOR_VertexColors[i].b,
                                                                   xdata_pspr.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data_model[i].tu = (float)(xdata_pspr.paInt_InitUvPtnNo[i]);
            _paVtxBuffer_data_model[i].tv = 0;


        }
        transformPosVtx(_paVtxBuffer_data_model, _size_vertex_unit_model, _nVertices);

        //距離
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                        _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                        _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );

            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        for (int n = 1; n < _draw_set_num; n++) {
            int os = n*_nVertices;
            for (UINT i = 0; i < _nVertices; i++) {
                _paVtxBuffer_data_model[os+i].x = _paVtxBuffer_data_model[i].x;
                _paVtxBuffer_data_model[os+i].y = _paVtxBuffer_data_model[i].y;
                _paVtxBuffer_data_model[os+i].z = _paVtxBuffer_data_model[i].z;
                _paVtxBuffer_data_model[os+i].color = _paVtxBuffer_data_model[i].color;
                _paVtxBuffer_data_model[os+i].tu = _paVtxBuffer_data_model[i].tu;
                _paVtxBuffer_data_model[os+i].tv = _paVtxBuffer_data_model[i].tv;
            }
        }
    }

    //デバイスに頂点バッファ作成(モデル)
    if (_paVertexBuffer_model == nullptr) {
        hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
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

    //デバイスにテクスチャ作成
    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[1];
        _papTextureConnection[0] = connectToTextureManager(_pa_texture_filenames[0].c_str());
        Texture* pTex = _papTextureConnection[0]->peek();
    }

    //インデックスバッファは使わない
    _paIndexBuffer = nullptr;

    MassModel::restore(); //上位を呼び出す
    _TRACE3_("_model_id=" << _model_id << " end");
}

HRESULT MassPointSpriteModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("MassPointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
//    if (_paVertexBuffer_instancedata == nullptr) {
//        createVertexElements(); //デバイスロスト復帰時に呼び出される
//    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _draw_set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_id<<" の描画セット数オーバー。_draw_set_num="<<_draw_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif

    IDirect3DDevice9* pDevice = pCARETAKER->_pID3DDevice9;

    //対象アクター
    const MassPointSpriteActor* pTargetActor = (MassPointSpriteActor*)prm_pActor_target;
    //対象MassPointSpriteActorのエフェクトラッパ
    MassPointSpriteEffect* pMassPointSpriteEffect = (MassPointSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassPointSpriteEffect->_pID3DXEffect;

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
    if (pModelLastDraw != this) {
//        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
//        hr = pDevice->SetStreamSourceFreq( 1, prm_draw_set_num );
// hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
        hr = pDevice->SetStreamSourceFreq( 1, _nVertices );
//        hr = pDevice->SetStreamSourceFreq( 1, 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _paVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _paVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(nullptr);
        checkDxException(hr, D3D_OK, "SetIndices に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pMassPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_hInvTextureSplitRowcol, _inv_texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hInvTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) に失敗しました。");

        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassPointSpriteModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            hr = pDevice->SetTexture(0, nullptr);
        }
        checkDxException(hr, D3D_OK, "SetTexture に失敗しました");
    }
//    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    hr = pDevice->SetStreamSourceFreq(0, 1);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 に失敗しました。prm_draw_set_num="<<prm_draw_set_num);

    Effect* pEffect_active = EffectManager::_pEffect_active;
    if (FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassPointSpriteEffect->_effect_name<<"("<<pMassPointSpriteEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassPointSpriteEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassPointSpriteEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassPointSpriteEffect->_effect_name);
    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
    checkDxException(hr, D3D_OK, " pass=1 に失敗しました。");
#ifdef MY_DEBUG
    GgafCore::Caretaker::_num_draw++;
#endif
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
            hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
            checkDxException(hr, D3D_OK, " pass="<<(i+1)<<" に失敗しました。");
#ifdef MY_DEBUG
            GgafCore::Caretaker::_num_draw++;
#endif
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMassPointSpriteEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

MassPointSpriteModel::~MassPointSpriteModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
}

