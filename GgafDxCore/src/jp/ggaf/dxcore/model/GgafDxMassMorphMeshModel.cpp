#include "jp/ggaf/dxcore/model/GgafDxMassMorphMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMorphMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMorphMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassMorphMeshModel::GgafDxMassMorphMeshModel(const char* prm_model_name) : GgafDxMassModel(prm_model_name) {
    _paVtxBuffer_data_model = nullptr;
    _paIndexBuffer_data = nullptr;

    _pVertexBuffer_model_morph = nullptr;
    _papaVtxBuffer_data_morph_model = nullptr;
    _size_vertices_morph_model = 0;
    _size_vertex_unit_morph_model = 0;

    _obj_model |= Obj_GgafDxMassMorphMeshModel;


    registerCallback_VertexModelInfo(GgafDxMassMorphMeshModel::createVertexModel); //頂点レイアウト情報作成コールバック関数

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreMassMorphMeshModel(GgafDxMassMorphMeshModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMassMorphMeshModel::GgafDxMassMorphMeshModel(" << _model_name << ") End");
}

void GgafDxMassMorphMeshModel::createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info) {
    GgafDxMassMorphMeshModel* pModel = (GgafDxMassMorphMeshModel*)prm;
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

void GgafDxMassMorphMeshModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");

    if (!_paVtxBuffer_data_model) {
        // _model_name には "8/xxx_4" or "xxx_4" という文字列が渡ってくる。 (/と_は区切り文字)
        // 8   ：同時描画セット数(省略時 GGAFDXMASS_MAX_INSTACE_NUM)
        // xxx ：モデル名
        // 4   ：モーフターゲット数
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xname = "";
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" の最大同時描画オブジェクト数は、デフォルトの"<<GGAFDXMASS_MAX_INSTACE_NUM<<" が設定されました。");
            _set_num = GGAFDXMASS_MAX_INSTACE_NUM;
            xname = names[0];
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);  // "8/xxx_4" の 8 が入る
            xname = names[1];            // "8/xxx_4" の xxx_4 が入る
        } else {
            throwGgafCriticalException("_model_name には \"8/xxx_4\" or \"xxx_4\" 形式を指定してください。 \n"<<
                    "実際は、_model_name="<<_model_name<<" でした。");
        }
        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTACE_NUM) {
            throwGgafCriticalException(_model_name<<"の最大同時描画オブジェクト数が不正。範囲は 1～"<<GGAFDXMASS_MAX_INSTACE_NUM<<"セットです。_set_num="<<_set_num);
        }

        std::string::size_type pos = xname.find_last_of('_');
        if (pos == std::string::npos) {
            throwGgafCriticalException("_model_name には \"8/xxx_4\" or \"xxx_4\" 形式を指定してください。 \n"<<
                    "実際は、_model_name="<<_model_name<<" でした。(2)");
        }
        std::string str_model = xname.substr(0, pos);  // "8/xxx_4" の xxx が入る
        std::string str_t_num = xname.substr(pos + 1); // "8/xxx_4" の 4 が入る
        _morph_target_num = STOI(str_t_num);

        std::string* xfile_names = NEW std::string[_morph_target_num+1];

        for(int i = 0; i < _morph_target_num+1; i++) {
            xfile_names[i] = GgafDxModelManager::getMeshFileName(str_model + "_" + XTOS(i));
        }
        HRESULT hr;
        D3DMATERIAL9*                         paMaterial = nullptr;

        GgafDxTextureConnection** model_papTextureConnection = nullptr;

        //流し込む頂点バッファデータ作成
        ToolBox::IO_Model_X iox;
        Frm::Model3D** papModel3D = NEW Frm::Model3D*[_morph_target_num+1];
        Frm::Mesh** papMeshesFront = NEW Frm::Mesh*[_morph_target_num+1];
        _papaVtxBuffer_data_morph_model = NEW GgafDxMassMorphMeshModel::VERTEX_model_morph*[_morph_target_num];

        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = iox.Load(xfile_names[pattern], papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("Xファイルの読込み失敗。2/ とか忘れてませんか？ 対象="<<xfile_names[pattern]);
            }
            //メッシュを結合する前に、情報を確保しておく
            int nMesh = (int)papModel3D[pattern]->_Meshes.size();
            uint16_t* paNumVertices = NEW uint16_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            papModel3D[pattern]->ConcatenateMeshes(); //メッシュを繋げる
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();
            _nVertices = papMeshesFront[pattern]->_nVertices;
            uint16_t nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            _nFaces = papMeshesFront[pattern]->_nFaces;
    //            nFaceNormals = papMeshesFront[pattern]->_nFaceNormals;

            if (_nVertices > 65535) {
                throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  _nVertices:"<<_nVertices);
            }

            if (pattern == 0) {
                //プライマリメッシュ
                _paVtxBuffer_data_model = NEW VERTEX_model_primary[_nVertices];
                _size_vertex_unit_model = sizeof(VERTEX_model_primary);
                _size_vertices_model = sizeof(VERTEX_model_primary) * _nVertices;
                //法線以外設定
                FLOAT model_bounding_sphere_radius;
                for (int i = 0; i < _nVertices; i++) {
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

                    //距離
                    model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                                _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                                _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z));
                    if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                        _bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {
                //モーフターゲットメッシュ
                _papaVtxBuffer_data_morph_model[pattern-1] = NEW VERTEX_model_morph[_nVertices];
                _size_vertex_unit_morph_model = sizeof(VERTEX_model_morph);
                _size_vertices_morph_model = sizeof(VERTEX_model_morph) * _nVertices;
                //法線以外設定
                for (int i = 0; i < _nVertices; i++) {
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
                _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<xfile_names[pattern]);
            }

            //法線設定とFrameTransformMatrix適用
            if (pattern == 0) { //プライマリメッシュ
                prepareVtx((void*)_paVtxBuffer_data_model, _size_vertex_unit_model,
                           papModel3D[pattern], paNumVertices);
            } else {            //ターゲットメッシュ
                prepareVtx((void*)(_papaVtxBuffer_data_morph_model[pattern-1]), _size_vertex_unit_morph_model,
                           papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);
        }   // プライマリ＆モーフターゲットループEND... for (int pattern = 0; pattern < _morph_target_num+1; pattern++)

        //インデックスバッファ取得
        _paIndexBuffer_data = NEW WORD[_nFaces*3];
        for (int i = 0; i < _nFaces; i++) {
            _paIndexBuffer_data[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
            _paIndexBuffer_data[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
            _paIndexBuffer_data[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
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
        GGAF_DELETEARR(xfile_names);
        GGAF_DELETEARR(papMeshesFront);
        GGAF_DELETEARR(papModel3D);
    }



    //頂点バッファ作成
    HRESULT hr;
    if (_pVertexBuffer_model == nullptr) {
        //デバイスに頂点バッファ作成(モデル)
        _pVertexBuffer_model_morph = NEW LPDIRECT3DVERTEXBUFFER9[_morph_target_num];
        for (int pattern = 0; pattern < _morph_target_num+1; pattern++) {
            if (pattern == 0) {
                //プライマリ頂点バッファ
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_pVertexBuffer_model),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
                //バッファへ作成済み頂点データを流し込む
                void *pDeviceMemory;
                hr = _pVertexBuffer_model->Lock(0, _size_vertices_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
                memcpy(pDeviceMemory, _paVtxBuffer_data_model, _size_vertices_model);
                hr = _pVertexBuffer_model->Unlock();
                checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_name);
            } else {
                //モーフターゲット頂点バッファ
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        _size_vertices_morph_model,
                        D3DUSAGE_WRITEONLY,
                        0,
                        D3DPOOL_DEFAULT,
                        &(_pVertexBuffer_model_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗（モーフ:"<<pattern-1<<"） model="<<(_model_name));
                //バッファへ作成済み頂点データを流し込む
                void *pDeviceMemory;
                hr = _pVertexBuffer_model_morph[pattern-1]->Lock(0, _size_vertices_morph_model, (void**)&pDeviceMemory, 0);
                checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_name);
                memcpy(pDeviceMemory, _papaVtxBuffer_data_morph_model[pattern-1], _size_vertices_morph_model); //pVertexBuffer ← paVertex
                hr = _pVertexBuffer_model_morph[pattern-1]->Unlock();
                checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗（モーフ:"<<pattern-1<<"） model="<<_model_name);
            }
        }
    }


    //インデックスバッファデータ作成（プライマリ、モーフターゲット共に同じ）
    if (_pIndexBuffer == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * _nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));
        void* pDeviceMemory;
        _pIndexBuffer->Lock(0,0,(void**)&pDeviceMemory,0);
        memcpy(pDeviceMemory , _paIndexBuffer_data , sizeof(WORD) * _nFaces * 3);
        _pIndexBuffer->Unlock();
    }

    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (int n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }
    _TRACE3_("_model_name=" << _model_name << " end");
}

HRESULT GgafDxMassMorphMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    if (_pVertexBuffer_instacedata == nullptr) {
        createVertexElements(); //デバイスロスト復帰時に呼び出される
    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxMassMorphMeshActor* const pTargetActor = (GgafDxMassMorphMeshActor*)prm_pActor_target;
    //対象アクターのエフェクトラッパ
    GgafDxMassMorphMeshEffect* const pMassMorphMeshEffect = (GgafDxMassMorphMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassMorphMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //頂点バッファ(インスタンスデータ)書き換え
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pInstancedata = prm_pPrm ? prm_pPrm : this->_pInstancedata; //prm_pPrm は臨時のテンポラリインスタンスデータ
    void* pDeviceMemory;
    hr = _pVertexBuffer_instacedata->Lock(0, update_vertex_instacedata_size, (void**)&pDeviceMemory, D3DLOCK_DISCARD);
    checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
    memcpy(pDeviceMemory, pInstancedata, update_vertex_instacedata_size);
    hr = _pVertexBuffer_instacedata->Unlock();
    checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_name);

    //モデルが同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    //頂点バッファ設定
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq(_morph_target_num+1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq "<<_morph_target_num+1<<" D3DSTREAMSOURCE_INSTANCEDATA に失敗しました。");
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model, 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        for (int i = 1; i <= _morph_target_num; i++) {
            hr = pDevice->SetStreamSource(i, _pVertexBuffer_model_morph[i-1], 0, _size_vertex_unit_morph_model);
            checkDxException(hr, D3D_OK, "SetStreamSource "<<i<<" に失敗しました。");
        }
        hr = pDevice->SetStreamSource(_morph_target_num+1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "SetStreamSource "<<_morph_target_num+1<<" に失敗しました。");
        //インデックスバッファ設定
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMorphMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
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


    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
           _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");


        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name<<"("<<pMassMorphMeshEffect<<")");
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
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMorphMeshEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }

    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMorphMeshEffect->_effect_name);
    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                       0,
                                       0,
                                       _nVertices,
                                       0,
                                       _nFaces);
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
    ++GgafGod::_num_drawing;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMorphMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMassMorphMeshModel::resetStreamSourceFreq() {
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( 0, 1 );
    for (int i = 1; i <= _morph_target_num; i++) {
        GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( i, 1 );
    }
    GgafDxGod::_pID3DDevice9->SetStreamSourceFreq( _morph_target_num+1, 1 );
}

void GgafDxMassMorphMeshModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMassMorphMeshModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_RELEASE(_pVertexBuffer_model_morph[pattern-1]);
    }
    GGAF_DELETEARR(_pVertexBuffer_model_morph);
    _TRACE3_("_model_name=" << _model_name << " end");
    GgafDxMassModel::release();
}

GgafDxMassMorphMeshModel::~GgafDxMassMorphMeshModel() {
    for (int pattern = 1; pattern <= _morph_target_num; pattern++) {
        GGAF_DELETEARR(_papaVtxBuffer_data_morph_model[pattern-1]);
    }
    GGAF_DELETEARR(_papaVtxBuffer_data_morph_model);
    GGAF_DELETEARR(_paVtxBuffer_data_model);
    GGAF_DELETEARR(_paIndexBuffer_data);
}

