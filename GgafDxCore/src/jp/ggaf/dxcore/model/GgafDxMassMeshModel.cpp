#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMassMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMassMeshModel::GgafDxMassMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name には "xxxxxx" or "8/xxxxx" が、渡ってくる。
    // 同時描画セット数が8という意味です。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そうかな。
    // モデル名から同時描画セット数指定があれば取り出す。無ければ8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxMassMeshModel::GgafDxMassMeshModel "<<
                "prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > MAX_INSTACE) {
            _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は"<<MAX_INSTACE<<"セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("GgafDxMassMeshModel("<<prm_model_name<<") のセット数省略のため、標準の最大の"<<MAX_INSTACE<<"セットが設定されます。");
        _set_num = MAX_INSTACE;
    }
    _pVertexBuffer_model = nullptr;
    _pVertexBuffer_instacedata = nullptr;
    _pIndexBuffer = nullptr;
    _pIDirect3DVertexDeclaration9 = nullptr;
    _paVtxBuffer_org_model = nullptr;
    _paIdxBuffer_org = nullptr;
    _size_vertex_unit_instacedata = 0;
    _size_vertex_unit_model = 0;
    _size_vertices_model = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMassMeshModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restoreMassMeshModel(GgafDxMassMeshModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMassMeshModel::GgafDxMassMeshModel(" << _model_name << ") End");
}

void GgafDxMassMeshModel::restore() {
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " start");
//    GgafDxGod::_pModelManager->restoreMassMeshModel(this);

   /////////////////////////////////////////////////////////////////
    _TRACE3_("GgafDxModelManager::restoreMassMeshModel(" << _model_name << ")");
    std::string xfile_name; //読み込むXファイル名
    //"12/Eres" or "8/Celes" or "Celes" から "Celes" だけ取とりだしてフルパス名取得
    //TODO:数値３桁以上の時はだめ
    if (*(_model_name + 1) == '/') {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name + 2));
    } else if (*(_model_name + 2) == '/') {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name + 3));
    } else {
        xfile_name = GgafDxModelManager::getMeshFileName(std::string(_model_name));
    }
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreMassMeshModel メッシュファイル(*.x)が見つかりません。model_name="<<(_model_name));
    }

    HRESULT hr;
    //流し込む頂点バッファデータ作成
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = nullptr;
    Frm::Mesh* model_pMeshesFront = nullptr;

//    GgafDxMassMeshModel::INDEXPARAM** model_papaIndexParam = nullptr;
//    GgafDxMassMeshModel::VERTEX* unit_paVtxBuffer_org = nullptr;
    GgafDxMassMeshModel::VERTEX_model* model_paVtxBuffer_org_model = nullptr;
//    WORD* unit_paIdxBuffer_org = nullptr;
    WORD* model_paIdxBuffer_org = nullptr;
    D3DMATERIAL9* model_paMaterial = nullptr;
    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    int nVertices = 0;
    int nTextureCoords = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;

    if (_pModel3D == nullptr) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMassMeshModel] Xファイルの読込み失敗。対象="<<xfile_name);
        }

        //メッシュを結合する前に、情報を確保しておく
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        model_pModel3D->ConcatenateMeshes(); //メッシュを繋げる

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices;
        nTextureCoords = model_pMeshesFront->_nTextureCoords;
        nFaces = model_pMeshesFront->_nFaces;
//        nFaceNormals = model_pMeshesFront->_nFaceNormals;
        model_paVtxBuffer_org_model = NEW GgafDxMassMeshModel::VERTEX_model[nVertices];

        if (nVertices > 65535) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMassMeshModel] 頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:"<<nVertices);
        }

        _nVertices = nVertices;
        _nFaces = nFaces;
        _size_vertex_unit_model = sizeof(GgafDxMassMeshModel::VERTEX_model);
        _size_vertices_model = sizeof(GgafDxMassMeshModel::VERTEX_model) * nVertices;
        _size_vertex_unit_instacedata = sizeof(GgafDxMassMeshModel::VERTEX_instancedata);

        //法線以外設定
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            model_paVtxBuffer_org_model[i].x = model_pMeshesFront->_Vertices[i].data[0];
            model_paVtxBuffer_org_model[i].y = model_pMeshesFront->_Vertices[i].data[1];
            model_paVtxBuffer_org_model[i].z = model_pMeshesFront->_Vertices[i].data[2];
            model_paVtxBuffer_org_model[i].nx = 0.0f;
            model_paVtxBuffer_org_model[i].ny = 0.0f;
            model_paVtxBuffer_org_model[i].nz = 0.0f;
            model_paVtxBuffer_org_model[i].color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラーは今の所使っていない
            if (i < nTextureCoords) {
                model_paVtxBuffer_org_model[i].tu = model_pMeshesFront->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                model_paVtxBuffer_org_model[i].tv = model_pMeshesFront->_TextureCoords[i].data[1];
            } else {
                model_paVtxBuffer_org_model[i].tu = 0;
                model_paVtxBuffer_org_model[i].tv = 0;
            }

            //距離
            model_bounding_sphere_radius = (FLOAT)(sqrt(model_paVtxBuffer_org_model[i].x * model_paVtxBuffer_org_model[i].x +
                                                        model_paVtxBuffer_org_model[i].y * model_paVtxBuffer_org_model[i].y +
                                                        model_paVtxBuffer_org_model[i].z * model_paVtxBuffer_org_model[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<xfile_name);
        }
        //法線設定とFrameTransformMatrix適用
        prepareVtx((void*)model_paVtxBuffer_org_model, _size_vertex_unit_model,
                                        model_pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //インデックスバッファ構築
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //頂点バッファ作成
        if (_pIDirect3DVertexDeclaration9 == nullptr) {
            D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[10];
            // Stream = 0 ---->
            WORD  st0_offset_next = 0;
            //float x, y, z;    // :POSITION0 頂点座標
            paVtxelem[0].Stream = 0;
            paVtxelem[0].Offset = st0_offset_next;
            paVtxelem[0].Type   = D3DDECLTYPE_FLOAT3;
            paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[0].Usage  = D3DDECLUSAGE_POSITION;
            paVtxelem[0].UsageIndex = 0;
            st0_offset_next += sizeof(float)*3;
            //float nx, ny, nz; // :NORMAL0 法線
            paVtxelem[1].Stream = 0;
            paVtxelem[1].Offset = st0_offset_next;
            paVtxelem[1].Type   = D3DDECLTYPE_FLOAT3;
            paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[1].Usage  = D3DDECLUSAGE_NORMAL;
            paVtxelem[1].UsageIndex = 0;
            st0_offset_next += sizeof(float)*3;
            //DWORD color;     // : COLOR0  頂点カラー
            paVtxelem[2].Stream = 0;
            paVtxelem[2].Offset = st0_offset_next;
            paVtxelem[2].Type   = D3DDECLTYPE_D3DCOLOR;
            paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[2].Usage  = D3DDECLUSAGE_COLOR;
            paVtxelem[2].UsageIndex = 0;
            st0_offset_next += sizeof(DWORD);
            //float tu, tv;    // : TEXCOORD0  テクスチャ座標
            paVtxelem[3].Stream = 0;
            paVtxelem[3].Offset = st0_offset_next;
            paVtxelem[3].Type   = D3DDECLTYPE_FLOAT2;
            paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[3].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[3].UsageIndex = 0;
            st0_offset_next += sizeof(float)*2;
            // <---- Stream = 0

            // Stream = 1 ---->
            WORD st1_offset_next = 0;
            //float _11, _12, _13, _14;   // : TEXCOORD1  World変換行列、１行目
            paVtxelem[4].Stream = 1;
            paVtxelem[4].Offset = st1_offset_next;
            paVtxelem[4].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[4].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[4].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[4].UsageIndex = 1;
            st1_offset_next += sizeof(float)*4;
            //float _21, _22, _23, _24;  // : TEXCOORD2  World変換行列、２行目
            paVtxelem[5].Stream = 1;
            paVtxelem[5].Offset = st1_offset_next;
            paVtxelem[5].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[5].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[5].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[5].UsageIndex = 2;
            st1_offset_next += sizeof(float)*4;
            //float _31, _32, _33, _34;  // : TEXCOORD3  World変換行列、３行目
            paVtxelem[6].Stream = 1;
            paVtxelem[6].Offset = st1_offset_next;
            paVtxelem[6].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[6].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[6].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[6].UsageIndex = 3;
            st1_offset_next += sizeof(float)*4;
            //float _41, _42, _43, _44;  // : TEXCOORD4  World変換行列、４行目
            paVtxelem[7].Stream = 1;
            paVtxelem[7].Offset = st1_offset_next;
            paVtxelem[7].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[7].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[7].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[7].UsageIndex = 4;
            st1_offset_next += sizeof(float)*4;
            //float r, g, b, a;        // : TEXCOORD5  マテリアルカラー
            paVtxelem[8].Stream = 1;
            paVtxelem[8].Offset = st1_offset_next;
            paVtxelem[8].Type   = D3DDECLTYPE_FLOAT4;
            paVtxelem[8].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[8].Usage  = D3DDECLUSAGE_TEXCOORD;
            paVtxelem[8].UsageIndex = 5;
            st1_offset_next += sizeof(float)*4;
            // <---- Stream = 1
            //D3DDECL_END()
            paVtxelem[9].Stream = 0xFF;
            paVtxelem[9].Offset = 0;
            paVtxelem[9].Type = D3DDECLTYPE_UNUSED;
            paVtxelem[9].Method = 0;
            paVtxelem[9].Usage = 0;
            paVtxelem[9].UsageIndex = 0;
            hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(_pIDirect3DVertexDeclaration9) );
            checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] GgafDxGod::_pID3DDevice9->CreateVertexDeclaration 失敗 model="<<(_model_name));
            //ストリーム数取得        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);
            GGAF_DELETEARR(paVtxelem);
        }

    }

    //頂点バッファ作成(モデル)
    if (_pVertexBuffer_model == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices_model,
                D3DUSAGE_WRITEONLY,
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_model),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer_model->Lock(
                                      0,
                                      _size_vertices_model,
                                      (void**)&pVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] 頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(
          pVertexBuffer,
          model_paVtxBuffer_org_model,
          _size_vertices_model
        );
        _pVertexBuffer_model->Unlock();
    }

    //頂点バッファ作成(インスタンス)
    if (_pVertexBuffer_instacedata == nullptr) {
        int size_instancedata = _size_vertex_unit_instacedata * _set_num;//最大同時描画数確保
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                size_instancedata,
                D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,  //毎回書き換える為D3DUSAGE_DYNAMIC
                0,
                D3DPOOL_DEFAULT,
                &(_pVertexBuffer_instacedata),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateVertexBuffer2 失敗 model="<<(_model_name));
        void *pVertexBuffer_instacedata;
        hr = _pVertexBuffer_instacedata->Lock(
                                      0,
                                      size_instancedata,
                                      (void**)&pVertexBuffer_instacedata,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] 頂点バッファのロック取得に失敗2 model="<<_model_name);
        ZeroMemory(pVertexBuffer_instacedata, size_instancedata);
        hr = _pVertexBuffer_instacedata->Unlock();
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] 頂点アンロック取得に失敗2 model="<<_model_name);
    }

    //インデックスバッファデータ作成
    if (_pIndexBuffer == nullptr) {
        nFaces = model_pMeshesFront->_nFaces;
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMassMeshModel] _pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          model_paIdxBuffer_org,
          sizeof(WORD) * nFaces * 3
        );
        _pIndexBuffer->Unlock();
    }


    //マテリアル設定
    int model_nMaterials = 0;
    setMaterial(model_pMeshesFront,
                &model_nMaterials, &model_paMaterial, &model_papTextureConnection);

    //モデルに保持させる
    _pModel3D = model_pModel3D;
    _pMeshesFront = model_pMeshesFront;
    _paIdxBuffer_org = model_paIdxBuffer_org;
    _paVtxBuffer_org_model = model_paVtxBuffer_org_model;
//    _papaIndexParam = model_papaIndexParam;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;
    _TRACE3_("GgafDxMassMeshModel::restore() " << _model_name << " end");
}

//描画
HRESULT GgafDxMassMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxMassMeshModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxMassMeshActor* const pTargetActor = (GgafDxMassMeshActor*)prm_pActor_target;
    //対象MassMeshActorのエフェクトラッパ
    GgafDxMassMeshEffect* const pMassMeshEffect = (GgafDxMassMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassMeshEffect->_pID3DXEffect;

    HRESULT hr;

    //頂点バッファ(インスタンスデータ)書き換え
    UINT update_vertex_instacedata_size = _size_vertex_unit_instacedata * prm_draw_set_num;
    void* pVertexBuffer_instacedata;
    hr = _pVertexBuffer_instacedata->Lock(
                                  0,
                                  update_vertex_instacedata_size,
                                  (void**)&pVertexBuffer_instacedata,
                                  D3DLOCK_DISCARD
                                );
    checkDxException(hr, D3D_OK, "[GgafDxMassMeshModel::draw] 頂点バッファのロック取得に失敗 model="<<_model_name);
    memcpy(
      pVertexBuffer_instacedata,
      _aInstancedata,
      update_vertex_instacedata_size
    );
    _pVertexBuffer_instacedata->Unlock();

    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 0 に失敗しました。prm_draw_set_num="<<prm_draw_set_num);

    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pIDirect3DVertexDeclaration9); //頂点フォーマット
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetIndices に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
        if (_papTextureConnection[0]) {
            pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            pDevice->SetTexture(0, nullptr);
        }
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pMassMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) {
        if (pEffect_active) {
            _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() End() に失敗しました。");
#ifdef MY_DEBUG
            if (pEffect_active->_begin == false) {
                throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
            } else {
                pEffect_active->_begin = false;
            }
#endif
        }
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxMassMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name<<"("<<pMassMeshEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassMeshEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassMeshEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassMeshEffect->_effect_name);

    hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  0,
                                  0,
                                  _nVertices,
                                  0,
                                  _nFaces);
    //checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass=1 に失敗しました。");
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() １パス目 EndPass() に失敗しました。");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
            hr = pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                          0,
                                          0,
                                          _nVertices,
                                          0,
                                          _nFaces);
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() DrawIndexedPrimitive()  pass="<<(i+1)<<" に失敗しました。");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() "<<i+1<<"パス目 EndPass() に失敗しました。");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxMassMeshModel::draw() １パス目 BeginPass(0) に失敗しました。");
    }

//    pDevice->SetStreamSourceFreq( 0, 1 );
//    pDevice->SetStreamSourceFreq( 1, 1 );

    GgafGod::_num_drawing++;
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}


void GgafDxMassMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMassMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMassMeshModel::release() {
    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " start");

    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _TRACE3_("close() _papTextureConnection["<<i<<"]->"<<(_papTextureConnection[i]->getIdStr()));
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection); //テクスチャの配列
    GGAF_RELEASE(_pVertexBuffer_instacedata);
    GGAF_RELEASE(_pVertexBuffer_model);
    GGAF_RELEASE(_pIndexBuffer);
    GGAF_RELEASE(_pIDirect3DVertexDeclaration9);

    GGAF_DELETEARR(_paVtxBuffer_org_model);
    GGAF_DELETEARR(_paIdxBuffer_org);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);

    _TRACE3_("GgafDxMassMeshModel::release() " << _model_name << " end");

}
GgafDxMassMeshModel::~GgafDxMassMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

