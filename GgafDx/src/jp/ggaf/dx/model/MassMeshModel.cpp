#include "jp/ggaf/dx/model/MassMeshModel.h"

#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MassMeshActor.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

MassMeshModel::MassMeshModel(const char* prm_model_name) : MassModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDx_MassMeshModel;

    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;
    registerCallback_VertexModelInfo(MassMeshModel::createVertexModel); //頂点レイアウト情報作成コールバック関数
    _TRACE_("MassMeshModel::MassMeshModel(" << _model_name << ") End");
}

void MassMeshModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
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
    //float nx, ny, nz; // :NORMAL0 法線
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_NORMAL;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*3;
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
    //st0_offset_next += sizeof(float)*2;

    out_info->element_num = element_num;
}

void MassMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    if (_paVtxBuffer_data_model == nullptr) {
        HRESULT hr;
        ModelManager* pModelManager = pGOD->_pModelManager;
        // _model_name には "xxxxxx" or "8,xxxxx" が、渡ってくる。
        // 同時描画セット数が8という意味です。
        // モデル名から同時描画セット数指定があれば取り出す
        std::vector<std::string> names = UTIL::split(std::string(_model_name), ",");
        std::string xfile_name = ""; //読み込むXファイル名
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" の最大同時描画オブジェクト数は、デフォルトの"<<GGAFDXMASS_MAX_INSTANCE_NUM<<" が設定されました。");
            _set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
            xfile_name = ModelManager::getMeshFileName(names[0]);
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);
            xfile_name = ModelManager::getMeshFileName(names[1]);
        } else {
            throwCriticalException("_model_name には \"xxxxxx\" or \"8,xxxxx\" 形式を指定してください。 \n"
                    "実際は、_model_name="<<_model_name<<" でした。");
        }
        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTANCE_NUM) {
            throwCriticalException(_model_name<<"の最大同時描画オブジェクト数が不正。範囲は 1〜"<<GGAFDXMASS_MAX_INSTANCE_NUM<<"セットです。_set_num="<<_set_num);
        }
        if (xfile_name == "") {
            throwCriticalException("メッシュファイル(*.x)が見つかりません。model_name="<<(_model_name));
        }

        //流し込む頂点バッファデータ作成
        ToolBox::IO_Model_X iox;
        Frm::Model3D* pModel3D = NEW Frm::Model3D();
        bool r = iox.Load(xfile_name, pModel3D);
        if (r == false) {
            throwCriticalException("Xファイルの読込み失敗。対象="<<xfile_name);
        }

        //メッシュを結合する前に、情報を確保しておく
        int nMesh = (int)pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = pModel3D->_Meshes.begin();
                iteMeshes != pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        pModel3D->ConcatenateMeshes(); //メッシュを繋げる

        Frm::Mesh* pMeshesFront = pModel3D->_Meshes.front();
        _nVertices = pMeshesFront->_nVertices;
        _nFaces = pMeshesFront->_nFaces;
        if (_nVertices > 65535) {
            throwCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  _nVertices:"<<_nVertices);
        }
        UINT nTextureCoords = pMeshesFront->_nTextureCoords;
//        nFaceNormals = pMeshesFront->_nFaceNormals;
        _paVtxBuffer_data_model = NEW MassMeshModel::VERTEX_model[_nVertices];
        _size_vertex_unit_model = sizeof(MassMeshModel::VERTEX_model);
        _size_vertices_model = sizeof(MassMeshModel::VERTEX_model) * _nVertices;
        //法線以外設定
        FLOAT model_bounding_sphere_radius;
        for (UINT i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data_model[i].x = pMeshesFront->_Vertices[i].data[0];
            _paVtxBuffer_data_model[i].y = pMeshesFront->_Vertices[i].data[1];
            _paVtxBuffer_data_model[i].z = pMeshesFront->_Vertices[i].data[2];
            _paVtxBuffer_data_model[i].nx = 0.0f;
            _paVtxBuffer_data_model[i].ny = 0.0f;
            _paVtxBuffer_data_model[i].nz = 0.0f;
            _paVtxBuffer_data_model[i].color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラーは今の所使っていない
            if (i < nTextureCoords) {
                _paVtxBuffer_data_model[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                _paVtxBuffer_data_model[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                _paVtxBuffer_data_model[i].tu = 0;
                _paVtxBuffer_data_model[i].tv = 0;
            }

            //距離
            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                        _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                        _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        if (_nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
            _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<xfile_name);
        }
        //法線設定とFrameTransformMatrix適用
        prepareVtx((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                                        pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //インデックスバッファ構築
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (UINT i = 0; i < _nFaces; i++) {
            _paIndexBuffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            _paIndexBuffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            _paIndexBuffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }
        //マテリアル設定
        setMaterial(pMeshesFront);
        GGAF_DELETE(pModel3D);
    }

    //デバイスに頂点バッファ作成(モデル)
    if (_pVertexBuffer_model == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //バッファへ作成済み頂点データを流し込む
        void* pDeviceMemory = 0;
        hr = _pVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
        hr = _pVertexBuffer_model->Unlock();
        checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_name);
    }

    //デバイスにインデックスバッファ作成
    if (_pIndexBuffer == nullptr) {
        HRESULT hr;
        hr = God::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<_model_name);
        void* pDeviceMemory = 0;
        hr = _pIndexBuffer->Lock(0, 0, (void**)&pDeviceMemory,0);
        checkDxException(hr, D3D_OK, "インデックスバッファのロック取得に失敗 model="<<_model_name);
        memcpy(pDeviceMemory, _paIndexBuffer_data, sizeof(WORD)*_nFaces*3);
        hr = _pIndexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "インデックスバッファのアンロック取得に失敗 model="<<_model_name);
    }

    //デバイスにテクスチャ作成
    if (_papTextureConnection == nullptr) {
        ModelManager* pModelManager = pGOD->_pModelManager;
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (TextureConnection*)(pModelManager->_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
    _TRACE3_("_model_name=" << _model_name << " end");
}

HRESULT MassMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    if (_pVertexBuffer_instancedata == nullptr) {
        createVertexElements(); //デバイスロスト復帰時に呼び出される
    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwCriticalException(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = God::_pID3DDevice9;
    //対象アクター
    const MassMeshActor* pTargetActor = (MassMeshActor*)prm_pActor_target;
    //対象MassMeshActorのエフェクトラッパ
    MassMeshEffect* pMassMeshEffect = (MassMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;
    //頂点バッファ(インスタンスデータ)書き換え
    UINT update_vertex_instancedata_size = _size_vertex_unit_instancedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm は臨時のテンポラリインスタンスデータ
    void* pDeviceMemory = 0;
    hr = _pVertexBuffer_instancedata->Lock(0, update_vertex_instancedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instancedata_size);
    hr = _pVertexBuffer_instancedata->Unlock();
    checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_name);

    //モデルが同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "SetIndices に失敗しました。");

        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            hr = pDevice->SetTexture(0, nullptr);
        }
        checkDxException(hr, D3D_OK, "SetTexture に失敗しました");
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
    //checkDxException(hr, D3D_OK, " pass=1 に失敗しました。");
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                               0,
                                               0,
                                               _nVertices,
                                               0,
                                               _nFaces);
            checkDxException(hr, D3D_OK, " pass="<<(i+1)<<" に失敗しました。");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }
#ifdef MY_DEBUG
        GgafCore::God::_num_drawing++;
#endif
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMassMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

MassMeshModel::~MassMeshModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

