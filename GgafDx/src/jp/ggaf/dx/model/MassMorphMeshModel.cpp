#include "jp/ggaf/dx/model/MassMorphMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/MassMorphMeshActor.h"
#include "jp/ggaf/dx/effect/MassMorphMeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

MassMorphMeshModel::MassMorphMeshModel(const char* prm_model_id) : MassModel(prm_model_id) {
    _obj_class |= Obj_GgafDx_MassMorphMeshModel;
    _paVtxBuffer_data_model = nullptr;
    _paIndex16Buffer_data = nullptr;
    _paIndex32Buffer_data = nullptr;
    _paVertexBuffer_model_morph = nullptr;
    _papaVtxBuffer_data_morph_model = nullptr;
    _size_vertices_morph_model = 0;
    _size_vertex_unit_morph_model = 0;
    _morph_target_num = 0;
    _max_draw_set_num = GGAFDXMASS_MAX_INSTANCE_NUM;
    _is_65535 = false;
    registerCallback_VertexModelInfo(MassMorphMeshModel::createVertexModel); //頂点レイアウト情報作成コールバック関数
}

void MassMorphMeshModel::createVertexModel(void* prm, MassModel::VertexModelInfo* out_info) {
    MassMorphMeshModel* pModel = (MassMorphMeshModel*)prm;
    int morph_target_num =  pModel->_morph_target_num;
    int element_num = 4+(2*morph_target_num);
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
    st0_offset_next += sizeof(float)*2;
    //モーフターゲットメッシュ部頂点フォーマット
    int s = 1;
    int POSITION_idx = 1;
    int NORMAL_idx = 1;
    int n = 4;
    for (int i = 1; i <= morph_target_num; i++) {
        //float x, y, z; // 頂点座標   POSITION1 ～ POSITIONX
        out_info->paElement[n].Stream = s;
        out_info->paElement[n].Offset = 0;
        out_info->paElement[n].Type   = D3DDECLTYPE_FLOAT3;
        out_info->paElement[n].Method = D3DDECLMETHOD_DEFAULT;
        out_info->paElement[n].Usage  = D3DDECLUSAGE_POSITION;
        out_info->paElement[n].UsageIndex = POSITION_idx;    POSITION_idx++;
        n++;
        //float nx, ny, nz; // 法線    NORMAL1 ～ NORMALX
        out_info->paElement[n].Stream = s;
        out_info->paElement[n].Offset = sizeof(float)*3;
        out_info->paElement[n].Type   = D3DDECLTYPE_FLOAT3;
        out_info->paElement[n].Method = D3DDECLMETHOD_DEFAULT;
        out_info->paElement[n].Usage  = D3DDECLUSAGE_NORMAL;
        out_info->paElement[n].UsageIndex = NORMAL_idx;       NORMAL_idx++;
        n++;

        s++;
    }
    out_info->element_num = element_num; //D3DVERTEXELEMENT9 構造体の配列要素数;
}

void MassMorphMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_paVtxBuffer_data_model == nullptr) {
        ModelManager* pModelManager = pCARETAKER->_pModelManager;
        ModelManager::ModelXFileFmt xdata;
        obtainMetaModelInfo(&xdata);
        if (_draw_set_num == 0 || _draw_set_num > _max_draw_set_num) {
            _TRACE_("MassMorphMeshModel::restore() "<<_model_id<<" の同時描画セット数は、最大の "<<_max_draw_set_num<<" に再定義されました。理由：_draw_set_num="<<_draw_set_num);
            _draw_set_num = _max_draw_set_num;
        } else {
            _TRACE_("MassMorphMeshModel::restore() "<<_model_id<<" の同時描画セット数は "<<_draw_set_num<<" です。");
        }
        _morph_target_num = xdata.XFileNum - 1;
        int morph_target_num = _morph_target_num;
        std::string* paXfilepath = NEW std::string[morph_target_num+1];
        for (int i = 0; i < morph_target_num+1; i++) {
            paXfilepath[i] = Model::getMeshXFilePath(xdata.XFileNames[i]);
        }
        //流し込む頂点バッファデータ作成
        ToolBox::IO_Model_X iox;
        Frm::Model3D** papModel3D = NEW Frm::Model3D*[_morph_target_num+1];
        Frm::Mesh** papMeshesFront = NEW Frm::Mesh*[_morph_target_num+1];
        _papaVtxBuffer_data_morph_model = NEW MassMorphMeshModel::VERTEX_model_morph*[_morph_target_num];

        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = iox.Load(paXfilepath[pattern], papModel3D[pattern]);
            if (r == false) {
                throwCriticalException("Xファイルの読込み失敗。対象="<<paXfilepath[pattern]);
            }
            //メッシュを結合する前に、情報を確保しておく
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint32_t* paNumVertices = NEW uint32_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            papModel3D[pattern]->ConcatenateMeshes(); //メッシュを繋げる
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();
            _nVertices = papMeshesFront[pattern]->_nVertices;
            uint32_t nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            _nFaces = papMeshesFront[pattern]->_nFaces;
    //            nFaceNormals = papMeshesFront[pattern]->_nFaceNormals;
            if (_nFaces*3 > 65535) {
                _is_65535 = true;
                _TRACE_("【警告】頂点インデックスが 65535 を超えたかもしれません。しらんけど。\n対象Model："<<getName()<<" インデックス:3*"<<_nFaces<<"(faces) _nVertices:"<<_nVertices);
            }

            if (pattern == 0) {
                //プライマリメッシュ
                _paVtxBuffer_data_model = NEW MassMorphMeshModel::VERTEX_model_primary[_nVertices];
                _size_vertex_unit_model = sizeof(MassMorphMeshModel::VERTEX_model_primary);
                _size_vertices_model = sizeof(MassMorphMeshModel::VERTEX_model_primary) * _nVertices;
                //法線以外設定
                for (UINT i = 0; i < _nVertices; i++) {
                    _paVtxBuffer_data_model[i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    _paVtxBuffer_data_model[i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    _paVtxBuffer_data_model[i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    _paVtxBuffer_data_model[i].nx = 0.0f;
                    _paVtxBuffer_data_model[i].ny = 0.0f;
                    _paVtxBuffer_data_model[i].nz = 0.0f;
                    _paVtxBuffer_data_model[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    if (i < nTextureCoords) {
                        _paVtxBuffer_data_model[i].tu = papMeshesFront[pattern]->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                        _paVtxBuffer_data_model[i].tv = papMeshesFront[pattern]->_TextureCoords[i].data[1];
                    } else {
                        _paVtxBuffer_data_model[i].tu = 0.0f;
                        _paVtxBuffer_data_model[i].tv = 0.0f;
                    }

                }
            } else {
                //モーフターゲットメッシュ
                _papaVtxBuffer_data_morph_model[pattern-1] = NEW MassMorphMeshModel::VERTEX_model_morph[_nVertices];
                _size_vertex_unit_morph_model = sizeof(MassMorphMeshModel::VERTEX_model_morph);
                _size_vertices_morph_model = sizeof(MassMorphMeshModel::VERTEX_model_morph) * _nVertices;
                //法線以外設定
                for (UINT i = 0; i < _nVertices; i++) {
                    _papaVtxBuffer_data_morph_model[pattern-1][i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    _papaVtxBuffer_data_morph_model[pattern-1][i].nx = 0.0f;
                    _papaVtxBuffer_data_morph_model[pattern-1][i].ny = 0.0f;
                    _papaVtxBuffer_data_morph_model[pattern-1][i].nz = 0.0f;
                }
            }

            if (_nVertices < nTextureCoords) {
                _TRACE_("nTextureCoords="<<nTextureCoords<<"/_nVertices="<<_nVertices);
                _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<paXfilepath[pattern]);
            }

            //法線設定とFrameTransformMatrix適用
            if (pattern == 0) { //プライマリメッシュ
                prepareVtx3D((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                           papModel3D[pattern], paNumVertices);
                //距離
                FLOAT model_bounding_sphere_radius;
                for (UINT i = 0; i < _nVertices; i++) {
                    model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                                _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                                _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {            //ターゲットメッシュ
                prepareVtx3D((void*)(_papaVtxBuffer_data_morph_model[pattern-1]), _size_vertex_unit_morph_model,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);
        }   // プライマリ＆モーフターゲットループEND... for (int pattern = 0; pattern < _morph_target_num+1; pattern++)

        //インデックスバッファ取得
        if (_is_65535) {
            _paIndex32Buffer_data = NEW uint32_t[_nFaces*3];
            for (UINT i = 0; i < _nFaces; i++) {
                _paIndex32Buffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
                _paIndex32Buffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
                _paIndex32Buffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
            }
        } else {
            _paIndex16Buffer_data = NEW uint16_t[_nFaces*3];
            for (UINT i = 0; i < _nFaces; i++) {
                _paIndex16Buffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
                _paIndex16Buffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
                _paIndex16Buffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
            }
        }

        //マテリアル設定
        setMaterial(papMeshesFront[0]);

        //後片付け
        for (int pattern = 0; pattern <= _morph_target_num; pattern++) {
            if (papModel3D) {
                Frm::Model3D* p = papModel3D[pattern];
                GGAF_DELETE(p);
            }
        }
        GGAF_DELETEARR(paXfilepath);
        GGAF_DELETEARR(papMeshesFront);
        GGAF_DELETEARR(papModel3D);
    }
    //頂点バッファ作成
    if (_paVertexBuffer_model == nullptr) {
        HRESULT hr;
        //デバイスに頂点バッファ作成(モデル)
        _paVertexBuffer_model_morph = NEW LPDIRECT3DVERTEXBUFFER9[_morph_target_num];
        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            if (pattern == 0) {
                //プライマリ頂点バッファ
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
            } else {
                //モーフターゲット頂点バッファ
                hr = pCARETAKER->_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_paVertexBuffer_model_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（モーフ:"<<pattern-1<<"） model="<<(_model_id));
                //バッファへ作成済み頂点データを流し込む
                void* pDeviceMemory = 0;
                hr = _paVertexBuffer_model_morph[pattern-1]->Lock(0, _size_vertices_morph_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_id);
                memcpy(pDeviceMemory, _papaVtxBuffer_data_morph_model[pattern-1], _size_vertices_morph_model); //paVertexBuffer ← paVertex
                hr = _paVertexBuffer_model_morph[pattern-1]->Unlock();
                checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_id);
            }
        }
    }


    //インデックスバッファデータ作成（プライマリ、モーフターゲット共に同じ）
    if (_paIndexBuffer == nullptr) {
        HRESULT hr;
        if (_is_65535) {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                    sizeof(uint32_t) * _nFaces * 3,
                                    D3DUSAGE_WRITEONLY,
                                    D3DFMT_INDEX32,
                                    D3DPOOL_DEFAULT,
                                    &(_paIndexBuffer),
                                    nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* pDeviceMemory = 0;
            _paIndexBuffer->Lock(0,0,(void**)&pDeviceMemory,0);
            memcpy(pDeviceMemory , _paIndex32Buffer_data , sizeof(uint32_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        } else {
            hr = pCARETAKER->_pID3DDevice9->CreateIndexBuffer(
                                    sizeof(uint16_t) * _nFaces * 3,
                                    D3DUSAGE_WRITEONLY,
                                    D3DFMT_INDEX16,
                                    D3DPOOL_DEFAULT,
                                    &(_paIndexBuffer),
                                    nullptr);
            checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_id));
            void* pDeviceMemory = 0;
            _paIndexBuffer->Lock(0,0,(void**)&pDeviceMemory,0);
            memcpy(pDeviceMemory , _paIndex16Buffer_data , sizeof(uint16_t) * _nFaces * 3);
            _paIndexBuffer->Unlock();
        }
    }

    if (_papTextureConnection == nullptr) {
        _papTextureConnection = NEW TextureConnection*[_num_materials];
        for (DWORD n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] = connectToTextureManager(_pa_texture_filenames[n].c_str());
        }
    }
    MassModel::restore(); //上位を呼び出す
    _TRACE3_("_model_id=" << _model_id << " end");
}

HRESULT MassMorphMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
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
    const MassMorphMeshActor* const pTargetActor = (MassMorphMeshActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    MassMorphMeshEffect* const pMassMorphMeshEffect = (MassMorphMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassMorphMeshEffect->_pID3DXEffect;

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
    //頂点バッファ設定
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq(_morph_target_num+1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<_morph_target_num+1<<" D3DSTREAMSOURCE_INSTANCEDATA に失敗しました。");
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _paVertexBuffer_model, 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        for (int i = 1; i <= _morph_target_num; i++) {
            hr = pDevice->SetStreamSource(i, _paVertexBuffer_model_morph[i-1], 0, _size_vertex_unit_morph_model);
            checkDxException(hr, D3D_OK, "SetStreamSource "<<i<<" に失敗しました。");
        }
        hr = pDevice->SetStreamSource(_morph_target_num+1, _paVertexBuffer_instancedata, 0, _size_vertex_unit_instancedata);
        checkDxException(hr, D3D_OK, "SetStreamSource "<<_morph_target_num+1<<" に失敗しました。");
        //インデックスバッファ設定
        pDevice->SetIndices(_paIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_fog_starts_far_rate, _fog_starts_far_rate);
        checkDxException(hr, D3D_OK, "SetFloat(_h_fog_starts_far_rate) に失敗しました。");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("MassMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            pDevice->SetTexture(0, nullptr);
        }
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 に失敗しました。D3DSTREAMSOURCE_INDEXEDDATA prm_draw_set_num="<<prm_draw_set_num);
    for (int i = 1; i <= _morph_target_num; i++) {
        hr = pDevice->SetStreamSourceFreq( i, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<i<<" に失敗しました。D3DSTREAMSOURCE_INDEXEDDATA prm_draw_set_num="<<prm_draw_set_num);
    }


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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name<<"("<<pMassMorphMeshEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        //モーフターゲットの数により pass を切り替えている
        //プリマリメッシュのみ                             = pass0
        //プライマリメッシュ＋モーフターゲットメッシュ１つ = pass1
        //プライマリメッシュ＋モーフターゲットメッシュ２つ = pass2
        //以下最大９まで
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassMorphMeshEffect->_begin) {
            throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMorphMeshEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }

    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMassMorphMeshEffect->_effect_name);
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
    EffectManager::_pEffect_active = pMassMorphMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void MassMorphMeshModel::resetStreamSourceFreq() {
    pCARETAKER->_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    for (int i = 1; i <= _morph_target_num; i++) {
        pCARETAKER->_pID3DDevice9->SetStreamSourceFreq( i, 1 );
    }
    pCARETAKER->_pID3DDevice9->SetStreamSourceFreq( _morph_target_num+1, 1 );
}

void MassMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void MassMorphMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_RELEASE(_paVertexBuffer_model_morph[pattern-1]);
    }
    GGAF_DELETEARR(_paVertexBuffer_model_morph);
    _TRACE3_("_model_id=" << _model_id << " end");
    MassModel::release();
}

MassMorphMeshModel::~MassMorphMeshModel() {
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_DELETEARR(_papaVtxBuffer_data_morph_model[pattern-1]);
    }
    GGAF_DELETEARR(_papaVtxBuffer_data_morph_model);
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR_NULLABLE(_paIndex16Buffer_data);
    GGAF_DELETEARR_NULLABLE(_paIndex32Buffer_data);
}

