#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9ModelManager::GgafDx9ModelManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Model> (prm_manager_name) {

    //テクスチャマネジャー
    _pTextureManager = NEW GgafDx9TextureManager("GgafDx9TextureManager");
    //板ポリゴン定義ファイル読込み
    DirectXFileCreate( &_pIDirectXFile );
    char* paChar_SpriteModelineTemplate = GgafUtil::getFileText(GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_spritemodel_define.x");
    if (paChar_SpriteModelineTemplate == NULL) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] スプライト情報読込みテンプレート\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\" が開けません。");
    }
    HRESULT hr = _pIDirectXFile->RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] RegisterTemplatesに失敗しました。\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\"を確認して下さい。");
    }
    DELETE_IMPOSSIBLE_NULL(paChar_SpriteModelineTemplate);
    _id_lastdraw = -1;
    _id_max = 0;

}

GgafDx9Model* GgafDx9ModelManager::processCreateResource(char* prm_idstr) {
    //振り分け
    char model_type = *prm_idstr; //頭一文字
    char* model_name = prm_idstr + 2; //３文字目以降
    GgafDx9Model* model;
    switch (model_type) {
        case 'M':
            //MeshModel
            model = createMeshModel(model_name, D3DXMESH_SYSTEMMEM);
            break;
        case 'm':
            //DynaMeshModel
            model = createMeshModel(model_name, D3DXMESH_DYNAMIC);
            break;
        case 'S':
            //SpriteModel
            model = createSpriteModel(model_name);
            break;
        case 'P':
            //SpriteModel
            model = createPlateModel(model_name);
            break;
        case 'C':
            //cubeModel
            model = createMeshModel("cube", D3DXMESH_SYSTEMMEM);
            break;
        case 'Q':
            //SquareModel
            model = createSquareModel(model_name);
            break;
        default:
            TRACE("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") そんな種別はありません");
            throwGgafCriticalException("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") そんなモデル種別は知りません");
            model = NULL;
            break;
    }
    return model;
}

GgafDx9MeshModel* GgafDx9ModelManager::createMeshModel(char* prm_model_name, DWORD prm_dwOptions) {
    GgafDx9MeshModel* pMeshModel_New = NEW GgafDx9MeshModel(prm_model_name, prm_dwOptions);
    restoreMeshModel(pMeshModel_New);
    return pMeshModel_New;
}

GgafDx9SpriteModel* GgafDx9ModelManager::createSpriteModel(char* prm_model_name) {

    GgafDx9SpriteModel* pSpriteModel_New = NEW GgafDx9SpriteModel(prm_model_name);
    restoreSpriteModel(pSpriteModel_New);
    return pSpriteModel_New;
}

GgafDx9PlateModel* GgafDx9ModelManager::createPlateModel(char* prm_model_name) {
    GgafDx9PlateModel* pPlateModel_New = NEW GgafDx9PlateModel(prm_model_name);
    restorePlateModel(pPlateModel_New);
    return pPlateModel_New;
}

GgafDx9SquareModel* GgafDx9ModelManager::createSquareModel(char* prm_model_name) {
    GgafDx9SquareModel* pSquareModel_New = NEW GgafDx9SquareModel(prm_model_name);
    restoreSquareModel(pSquareModel_New);
    return pSquareModel_New;
}

GgafDx9PrimitiveModel* GgafDx9ModelManager::createPrimitiveModel(char* prm_model_name) {
    GgafDx9PrimitiveModel* pPrimitiveModel_New = NEW GgafDx9PrimitiveModel(prm_model_name);
    restorePrimitiveModel(pPrimitiveModel_New);
    return pPrimitiveModel_New;
}


void GgafDx9ModelManager::restorePrimitiveModel(GgafDx9PrimitiveModel* prm_pPrimModel) {
    TRACE("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //１）頂点バッファ、インデックス頂点バッファ を作成
    //２）Xファイルから、独自に次の情報を読み込み、頂点バッファ、インデックス頂点バッファ に流し込む。
    //３）２）を行なう過程で、同時に GgafDx9PrimitiveModel に次のメンバを作成。
    //　　　　・頂点バッファの写し
    //　　　　・インデックス頂点バッファの写し
    //　　　　・マテリアル配列(要素数＝マテリアル数)
    //　　　　・テクスチャ配列(要素数＝マテリアル数)
    //　　　　・DrawIndexedPrimitive用引数配列(要素数＝マテリアルリストが変化した数)
    //＜留意＞
    //
    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pPrimModel->_model_name) + ".x";
    HRESULT hr;
//    LPDIRECT3DVERTEXBUFFER9 pIDirect3DVertexBuffer9;
//    LPDIRECT3DINDEXBUFFER9 pIDirect3DIndexBuffer9;
//    D3DMATERIAL9* paD3DMaterial9;

    //流し込む頂点バッファデータ作成
    if (prm_pPrimModel->_pModel3D == NULL) {
        prm_pPrimModel->_pModel3D = NEW Frm::Model3D();
        ToolBox::IO_Model_X iox;
        bool r = iox.Load(xfile_name, prm_pPrimModel->_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDx9ModelManager::restorePrimitiveModel] Xファイルの読込み失敗。対象="<<xfile_name);
        }
        prm_pPrimModel->_pModel3D->ConcatenateMeshes();
        prm_pPrimModel->_pMeshesFront = prm_pPrimModel->_pModel3D->_Meshes.front();

        int nVertices = prm_pPrimModel->_pMeshesFront->_nVertices;
        int nFaces = prm_pPrimModel->_pMeshesFront->_nFaces;

    //    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //    //テクスチャの参照を保持させる。
    //    prm_pSpriteModel->_pTextureCon = pTextureCon;


        prm_pPrimModel->_paVtxBuffer_org = NEW GgafDx9PrimitiveModel::VERTEX[nVertices];
        prm_pPrimModel->_size_vertecs = sizeof(GgafDx9PrimitiveModel::VERTEX)*nVertices;
        prm_pPrimModel->_size_vertec_unit = sizeof(GgafDx9PrimitiveModel::VERTEX);

        //設定
        for (int i = 0; i < nVertices; i++) {
            prm_pPrimModel->_paVtxBuffer_org[i].x = prm_pPrimModel->_pMeshesFront->_Vertices[i].data[0];
            prm_pPrimModel->_paVtxBuffer_org[i].y = prm_pPrimModel->_pMeshesFront->_Vertices[i].data[1];
            prm_pPrimModel->_paVtxBuffer_org[i].z = prm_pPrimModel->_pMeshesFront->_Vertices[i].data[2];
            prm_pPrimModel->_paVtxBuffer_org[i].nx = 0.0f;
            prm_pPrimModel->_paVtxBuffer_org[i].ny = 0.0f;
            prm_pPrimModel->_paVtxBuffer_org[i].nz = 0.0f;
            prm_pPrimModel->_paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255);
            prm_pPrimModel->_paVtxBuffer_org[i].tu = 0.0f;
            prm_pPrimModel->_paVtxBuffer_org[i].tv = 0.0f;
        }

        //出来る限りUV座標設定
        int nTextureCoords = prm_pPrimModel->_pMeshesFront->_nTextureCoords;
        for (int i = 0; i < nTextureCoords; i++) {
            if (nVertices < i) {
                _TRACE_("UV座標数が、頂点バッファ数を越えてます。対象="<<xfile_name);
                break;
            } else {
                prm_pPrimModel->_paVtxBuffer_org[i].tu = prm_pPrimModel->_pMeshesFront->_TextureCoords[i].data[0];
                prm_pPrimModel->_paVtxBuffer_org[i].tv = prm_pPrimModel->_pMeshesFront->_TextureCoords[i].data[1];
            }
        }
        //法線設定
        unsigned short indexVertices[3];
        unsigned short indexNormals[3];
        float nx, ny, nz;
        for (int i = 0; i < nFaces; i++) {
            indexVertices[0] = prm_pPrimModel->_Faces[i].data[0];
            indexVertices[1] = prm_pPrimModel->_Faces[i].data[1];
            indexVertices[2] = prm_pPrimModel->_Faces[i].data[2];
            indexNormals[0] = prm_pPrimModel->_FaceNormals[i].data[0];
            indexNormals[1] = prm_pPrimModel->_FaceNormals[i].data[1];
            indexNormals[2] = prm_pPrimModel->_FaceNormals[i].data[2];
            for (int j = 0; j < 3; j++) {
                nx = prm_pPrimModel->_Normals[indexNormals[j]].x;
                ny = prm_pPrimModel->_Normals[indexNormals[j]].y;
                nz = prm_pPrimModel->_Normals[indexNormals[j]].z;
                prm_pPrimModel->_paVtxBuffer_org[indexVertices[j]].nx = nx;
                prm_pPrimModel->_paVtxBuffer_org[indexVertices[j]].ny = ny;
                prm_pPrimModel->_paVtxBuffer_org[indexVertices[j]].nz = nz;
            }
        }

        //マテリアルリスト
        prm_pPrimModel->_pFaceMaterials = NEW UINT[nFaces];
        for (int i = 0; i < nFaces; i++) {
            prm_pPrimModel->_pFaceMaterials[i] =  prm_pPrimModel->_pMeshesFront->_pFaceMaterials[i];
        }

        //パラメータリスト作成
        GgafDx9PrimitiveModel::INDEXPARAM param  = GgafDx9PrimitiveModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int prev_paramno = 0;
        int paramno = 0;
        for (int i = 0; i < nFaces; i++) {
            materialno = prm_pPrimModel->_pMeshesFront->_pFaceMaterials[i];
            if (prev_mno != materialno) {
                param[next_paramno].MaterialNo = prev_mno;
                param[next_paramno].BaseVertexIndex = 0;
                param[next_paramno].MinIndex = nFaces;
                param[next_paramno].NumVertices = 0; //次回へ
                param[next_paramno].StartIndex =
                param[next_paramno].PrimitiveCount =
            }
        }

//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//        DrawIndexedPrimitiveを使って描画する。
//        第一引数には プリミティブタイプ、
//        第二引数には 頂点バッファの何番目から使用するかを指定する
//        第三引数には インデックス番号の最小値を指定する
//        第四引数には 頂点バッファ内の使用する頂点数を指定する
//        第五引数には インデックスバッファの何番目から使用するかを指定する
//        第六引数には プリミティブタイプで指定した形の描画する総数である
//
//
//
//
//            // サンプル　下の図参照
//                lpD3DDEV->DrawIndexedPrimitive(
//                            D3DPT_TRIANGLELIST,
//                            2,        // オフセット値
//                            0,        // 最小インデックス値
//                            4,        // 頂点数
//                            0,        // インデックスバッファ
//                            2 );
//
//






        //インデックスバッファ登録
        prm_pPrimModel->_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            prm_pPrimModel->_paIdxBuffer_org[i*3 + 0] = prm_pPrimModel->_pMeshesFront->_Faces[i].data[0];
            prm_pPrimModel->_paIdxBuffer_org[i*3 + 1] = prm_pPrimModel->_pMeshesFront->_Faces[i].data[1];
            prm_pPrimModel->_paIdxBuffer_org[i*3 + 2] = prm_pPrimModel->_pMeshesFront->_Faces[i].data[2];
        }




    }


    if (prm_pPrimModel->_pIDirect3DVertexBuffer9 == NULL) {

        //頂点バッファ作成
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pPrimModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9PrimitiveModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pPrimModel->_pIDirect3DVertexBuffer9),
                NULL);
        if(hr != D3D_OK) {
            throwGgafDx9CriticalException("[GgafDx9ModelManager::restorePrimitiveModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(prm_pPrimModel->_model_name), hr);
        }
        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = prm_pPrimModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pPrimModel->_size_vertecs, (void**)&pVertexBuffer, 0);
        if(hr != D3D_OK) {
            throwGgafDx9CriticalException("[GgafDx9ModelManager::restorePrimitiveModel] 頂点バッファのロック取得に失敗 model="<<prm_pPrimModel->_model_name, hr);
        }
        memcpy(pVertexBuffer, prm_pPrimModel->_paVtxBuffer_org, prm_pPrimModel->_size_vertecs); //pVertexBuffer ← paVertex
        prm_pPrimModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //流し込むインデックスバッファデータ作成
    if (prm_pPrimModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = prm_pPrimModel->_pMeshesFront->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_MANAGED,
                                &(prm_pPrimModel->_pIDirect3DIndexBuffer9),
                                NULL);
        if (hr != D3D_OK) {
             throwGgafDx9CriticalException("[GgafDx9ModelManager::restorePrimitiveModel] _pID3DDevice9->CreateIndexBuffer 失敗 model="<<(prm_pPrimModel->_model_name), hr);
        }
        void* pIndexBuffer;
        prm_pPrimModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , prm_pPrimModel->_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pPrimModel->_pIDirect3DIndexBuffer9->Unlock();
    }


    int nMaterials = prm_pPrimModel->_pMeshesFront->_nMaterials;
    prm_pPrimModel->_dwNumMaterials = nMaterials;
    prm_pPrimModel->_paD3DMaterial9_default = NEW D3DMATERIAL9[nMaterials];
    prm_pPrimModel->_paIndexParam = NEW GgafDx9PrimitiveModel::INDEXPARAM[nMaterials];
    prm_pPrimModel->_papTextureCon = NEW GgafDx9TextureConnection*[nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = prm_pPrimModel->_pMeshesFront->_Materials.begin(); material != prm_pPrimModel->_pMeshesFront->_Materials.end(); material++) {
        prm_pPrimModel->_paD3DMaterial9_default[n].Diffuse.r = (*material)->_FaceColor.data[0];
        prm_pPrimModel->_paD3DMaterial9_default[n].Diffuse.g = (*material)->_FaceColor.data[1];
        prm_pPrimModel->_paD3DMaterial9_default[n].Diffuse.b = (*material)->_FaceColor.data[2];
        prm_pPrimModel->_paD3DMaterial9_default[n].Diffuse.a = (*material)->_FaceColor.data[3];

        prm_pPrimModel->_paD3DMaterial9_default[n].Ambient.r = (*material)->_FaceColor.data[0];
        prm_pPrimModel->_paD3DMaterial9_default[n].Ambient.g = (*material)->_FaceColor.data[1];
        prm_pPrimModel->_paD3DMaterial9_default[n].Ambient.b = (*material)->_FaceColor.data[2];
        prm_pPrimModel->_paD3DMaterial9_default[n].Ambient.a = (*material)->_FaceColor.data[3];

        prm_pPrimModel->_paD3DMaterial9_default[n].Specular.r = (*material)->_SpecularColor.data[0];
        prm_pPrimModel->_paD3DMaterial9_default[n].Specular.g = (*material)->_SpecularColor.data[1];
        prm_pPrimModel->_paD3DMaterial9_default[n].Specular.b = (*material)->_SpecularColor.data[2];
        prm_pPrimModel->_paD3DMaterial9_default[n].Specular.a = 1.000000;
        prm_pPrimModel->_paD3DMaterial9_default[n].Power =  (*material)->_power;

        prm_pPrimModel->_paD3DMaterial9_default[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        prm_pPrimModel->_paD3DMaterial9_default[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        prm_pPrimModel->_paD3DMaterial9_default[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        prm_pPrimModel->_paD3DMaterial9_default[n].Emissive.a = 1.000000;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            prm_pPrimModel->_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //テクスチャ無し
            prm_pPrimModel->_papTextureCon[n] = NULL;
        }


    }


}

void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel) {
    TRACE("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //Xファイルのロードして必要な内容をGgafDx9MeshModelメンバに設定しインスタンスとして完成させたい
    //以下の string xfile_name まではGgafDx9MeshModelメンバ設定のための受け取り変数。
    LPD3DXMESH pID3DXMesh; //メッシュ(ID3DXMeshインターフェイスへのポインタ）
    D3DMATERIAL9* paD3DMaterial9; //マテリアル(D3DXMATERIAL構造体の配列の先頭要素を指すポインタ）
    GgafDx9TextureConnection** papTextureCon; //テクスチャ配列(IDirect3DTexture9インターフェイスへのポインタを保持するオブジェクト）
    DWORD dwNumMaterials;
    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshModel->_model_name) + ".x";

    LPD3DXBUFFER pID3DXBuffer; //受け取り用バッファ（マテリアル用）
    HRESULT hr;
    //Xファイルのファイルロード
    hr = D3DXLoadMeshFromX(
           xfile_name.c_str(),         //[in]  LPCTSTR pFilename
           prm_pMeshModel->_dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
           GgafDx9God::_pID3DDevice9,  //[in]  LPDIRECT3DDEVICE9 pDevice
           NULL,                       //[out] LPD3DXBUFFER* ppAdjacency
           &pID3DXBuffer,              //[out] LPD3DXBUFFER* ppMaterials
           NULL,                       //[out] LPD3DXBUFFER* ppEffectInstances
           &dwNumMaterials,            //[out] DWORD* pNumMaterials
           &pID3DXMesh                 //[out] LPD3DXMESH* pMesh
         );
    if (hr != D3D_OK) {
        throwGgafDx9CriticalException("[GgafDx9ModelManager::restoreMeshModel] D3DXLoadMeshFromXによるロードが失敗。対象="<<xfile_name, hr);
    }

    //TODO メッシュのOptimizeを試せ！
    //    !   メッシュの面及び頂点の順番を変更し，最適化したメッシュオブジェクトを取得する。
    //        call XOptimize(lpMesh,D3DXMESHOPT_ATTRSORT,NULL,NULL,NULL,NULL,LOC(lpMeshOpt),iRes)

    //マテリアルを取り出す
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //＜2008/02/02 の脳みそ＞
    // やっていることメモ
    // GetBufferPointer()で取得できる D3DXMATERIAL構造体配列のメンバのMatD3D (D3DMATERIAL9構造体) が欲しい。
    //（∵GgafDx9MeshModelのメンバー持ちにしたいため）。 pID3DXBuffer_tmp の方はさっさと解放(Release())しようとした。
    // だが解放すると D3DXMATERIAL構造体配列もどうやら消えるようだ、すぐには消えないかもしれんが…（ここでハマる；）。
    // そこでしかたないので、paD3DMaterial9_tmp の構造体を物理コピーをして保存することにしましょ～、あ～そ～しましょう。
    paD3DMaterial9 = NEW D3DMATERIAL9[dwNumMaterials];
    for( DWORD i = 0; i < dwNumMaterials; i++){
        paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //マテリアルのDiffuse反射をAmbient反射にコピーする
    //理由：Ambientライトを使用したかった。そのためには当然Ambient反射値をマテリアルに設定しなければいけないが
    //xファイル（MatD3D）にはDiffuse反射値しか設定されていない、そこでDiffuse反射の値で
    //Ambient反射値を代用することにする。とりあえず。
    //TODO:本当にこれでいいのか？
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        paD3DMaterial9[i].Ambient = paD3DMaterial9[i].Diffuse;
    }

    //テクスチャを取り出す
    papTextureCon = NEW GgafDx9TextureConnection*[dwNumMaterials];
    char* texture_filename;
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //テクスチャ無し
            papTextureCon[i] = NULL;
        }
    }
    RELEASE_IMPOSSIBLE_NULL(pID3DXBuffer);//テクスチャファイル名はもういらないのでバッファ解放

    //Xファイルに法線がない場合、法線を設定。
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = NULL;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           GgafDx9God::_pID3DDevice9,            // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        if(hr != D3D_OK) {
            throwGgafDx9CriticalException("[GgafDx9ModelManager::restoreMeshModel]  pID3DXMesh->CloneMeshFVF()失敗。対象="<<xfile_name, hr);
        }
        D3DXComputeNormals(pID3DXMesh_tmp, NULL); //法線計算
        RELEASE_IMPOSSIBLE_NULL(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //メッシュ、マテリアル、テクスチャの参照、マテリアル数をモデルオブジェクトに保持させる
    prm_pMeshModel->_pID3DXMesh = pID3DXMesh;
    prm_pMeshModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pMeshModel->_papTextureCon = papTextureCon;
    prm_pMeshModel->_dwNumMaterials = dwNumMaterials;
}

void GgafDx9ModelManager::restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel) {
    TRACE("GgafDx9ModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");

    prm_pSpriteModel->_pTextureCon = NULL;
    prm_pSpriteModel->_paRectUV = NULL;

    prm_pSpriteModel->_pD3DMaterial9_default = NEW D3DMATERIAL9;
    ZeroMemory(prm_pSpriteModel->_pD3DMaterial9_default, sizeof(D3DMATERIAL9) );
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.r = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.g = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.b = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Diffuse.a = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.r = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.g = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.b = 1.0f;
    prm_pSpriteModel->_pD3DMaterial9_default->Ambient.a = 1.0f;

    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteModel->_model_name) + ".x";

    //スプライト情報読込みテンプレートの登録(初回実行時のみ)

    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    if(hr != DXFILE_OK) {
        throwGgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<"のCreateEnumObjectに失敗しました。", hr);
    }

    //TODO
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_SpriteModelWidth;
    float* pFloat_Size_SpriteModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1セットだけ読込み
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" の読込みに失敗しました。項目名を見直して");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        // PersonIDテンプレートデータを取得
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_SpriteModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_SpriteModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        prm_pSpriteModel->_fSize_SpriteModelWidthPx = *pFloat_Size_SpriteModelWidth;
        prm_pSpriteModel->_fSize_SpriteModelHeightPx = *pFloat_Size_SpriteModelHeight;
        prm_pSpriteModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pSpriteModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" のGUIDが一致しません。");
    }

    //テクスチャ取得しモデルに保持させる
    //string texture_filename = GGAFDX9_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //テクスチャの参照を保持させる。
    prm_pSpriteModel->_pTextureCon = pTextureCon;

    GgafDx9SpriteModel::VERTEX* paVertex = NEW GgafDx9SpriteModel::VERTEX[4];
    prm_pSpriteModel->_size_vertecs = sizeof(GgafDx9SpriteModel::VERTEX)*4;
    prm_pSpriteModel->_size_vertec_unit = sizeof(GgafDx9SpriteModel::VERTEX);

    //頂点配列情報をモデルに保持させる
    paVertex[0].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[0].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = 0.0f;
    paVertex[0].tv = 0.0f;

    paVertex[1].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[1].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = 1.0f;
    paVertex[1].tv = 0.0f;

    paVertex[2].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[2].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = 0.0f;
    paVertex[2].tv = 1.0f;

    paVertex[3].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[3].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = 1.0f;
    paVertex[3].tv = 1.0f;

    //バッファ作成
    if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9SpriteModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
                NULL);
        if(hr != D3D_OK) {
            throwGgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(prm_pSpriteModel->_model_name), hr);
        }
    }
    //頂点バッファ作成
    //頂点情報をビデオカード頂点バッファへロード
    void *pVertexBuffer;
    hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSpriteModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    if(hr != D3D_OK) {
        throwGgafDx9CriticalException("[GgafDx9ModelManager::restoreSpriteModel] 頂点バッファのロック取得に失敗 model="<<prm_pSpriteModel->_model_name, hr);
    }
    memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_size_vertecs); //pVertexBuffer ← paVertex
    prm_pSpriteModel->_pIDirect3DVertexBuffer9->Unlock();

    //全パターンのUV情報の配列作成しモデルに保持させる
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_ani = row*(*pInt_ColNum_TextureSplit)+col;
            paRectUV[pattno_ani]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

            paRectUV[pattno_ani]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pSpriteModel->_paRectUV = paRectUV;
    prm_pSpriteModel->_pattno_ani_Max=pattnum-1;

    //後始末
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restorePlateModel(GgafDx9PlateModel* prm_pPlateModel) {
    TRACE("GgafDx9ModelManager::restorePlateModel(" << prm_pPlateModel->_model_name << ")");

    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pPlateModel->_model_name) + ".x";

    //	prm_pPlateModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
    //	ZeroMemory( prm_pPlateModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.r = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.g = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.b = 1.0f;
    //	prm_pPlateModel->_pD3DMaterial9->Diffuse.a = 0.2f;
    //	prm_pPlateModel->_pD3DMaterial9->Ambient = prm_pPlateModel->_pD3DMaterial9->Diffuse;
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    if (hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"のCreateEnumObjectに失敗しました。");
    }

    //TODO
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_PlateModelWidth;
    float* pFloat_Size_PlateModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1セットだけ読込み
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if (hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"の読込みに失敗しました。項目名を見直して");
    }

    const GUID *pGuid;
    pIDirectXFileData->GetType(&pGuid);
    //if( *pGuid == PersonID_GUID ) {

    if (true) {
        DWORD Size;
        // PersonIDテンプレートデータを取得
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_PlateModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_PlateModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        //データはコピーしなければいけません。
        prm_pPlateModel->_fSize_PlateModelWidth  = *pFloat_Size_PlateModelWidth;
        prm_pPlateModel->_fSize_PlateModelHeight = *pFloat_Size_PlateModelHeight;
        prm_pPlateModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pPlateModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePlateModel] "<<xfile_name<<"のGUIDが一致しません。");
    }

    //頂点配列情報をモデルに保持させる
    //string texture_filename = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);

    prm_pPlateModel->_pTextureCon = pTextureCon;

    // テクスチャーのサイズを取得
    /*
     D3DSURFACE_DESC d3dsurface_desc;
     pIDirect3DTexture9->GetLevelDesc(0, &d3dsurface_desc);
     UINT ulTextureWidth  = d3dsurface_desc.Width;  //幅（テクセル）
     UINT ulTextureHeight = d3dsurface_desc.Height; //テクスチャ高さ（ピクセル）
     */

    //全パターンのUV分割座標を求めて保持
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
	for (int row = 0; row < *pInt_RowNum_TextureSplit; row++){
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno = row*(*pInt_ColNum_TextureSplit)+col;

            paRectUV[pattno]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

            paRectUV[pattno]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pPlateModel->_paRectUV = paRectUV;
    prm_pPlateModel->_pattno_max=pattnum-1;

    //後始末
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel) {
    TRACE("GgafDx9ModelManager::restoreSquareModel(" << prm_pSquareModel->_model_name << ")");

    //頂点情報も設定し直し。
    prm_pSquareModel->_pD3DMaterial9 = NEW D3DMATERIAL9;
    ZeroMemory(prm_pSquareModel->_pD3DMaterial9, sizeof(D3DMATERIAL9) );
    prm_pSquareModel    ->_pD3DMaterial9->Diffuse.r = prm_pSquareModel->_pD3DMaterial9->Ambient.r = 1.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.g = prm_pSquareModel->_pD3DMaterial9->Ambient.g = 0.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.b = prm_pSquareModel->_pD3DMaterial9->Ambient.b = 0.0f;
    prm_pSquareModel->_pD3DMaterial9->Diffuse.a = prm_pSquareModel->_pD3DMaterial9->Ambient.a = 1.0f;

    GgafDx9SquareModel::VERTEX* paVertex = NEW GgafDx9SquareModel::VERTEX[12];
    prm_pSquareModel->_size_vertecs = sizeof(GgafDx9SquareModel::VERTEX)*4;
    prm_pSquareModel->_size_vertec_unit = sizeof(GgafDx9SquareModel::VERTEX);
    paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);
    paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);

    //頂点配列情報をモデルに保持させる
    paVertex[0].x = -0.5/PX_UNIT;
    paVertex[0].y = 0.5/PX_UNIT;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[1].x = 0.5/PX_UNIT;
    paVertex[1].y = 0.5/PX_UNIT;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[2].x = -0.5/PX_UNIT;
    paVertex[2].y = -0.5/PX_UNIT;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,0,0);

    paVertex[3].x = 0.5/PX_UNIT;
    paVertex[3].y = -0.5/PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,0,0);

    HRESULT hr;
    //頂点バッファ作成
    if (prm_pSquareModel->_pIDirect3DVertexBuffer9 == NULL) {
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                                          prm_pSquareModel->_size_vertecs,
                                          D3DUSAGE_WRITEONLY,
                                          GgafDx9SquareModel::FVF,
                                          D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                                          &(prm_pSquareModel->_pIDirect3DVertexBuffer9),
                                          NULL
                                        );
        if(hr != D3D_OK) {
            throwGgafDx9CriticalException("[GgafDx9SquareModelManager::restoreSquareModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<prm_pSquareModel->_model_name, hr);
        }
    }

    //頂点情報をビデオカード頂点バッファへロード
    void *pVertexBuffer;
    hr = prm_pSquareModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSquareModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    if(hr != D3D_OK) {
        throwGgafDx9CriticalException("[GgafDx9SquareModelManager::restoreSquareModel] 頂点バッファのロック取得に失敗 model="<<prm_pSquareModel->_model_name, hr);
    }
    memcpy(pVertexBuffer, paVertex, prm_pSquareModel->_size_vertecs);
    prm_pSquareModel->_pIDirect3DVertexBuffer9->Unlock();

    //後始末
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
}

GgafResourceConnection<GgafDx9Model>* GgafDx9ModelManager::processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource) {
    TRACE(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    GgafDx9ModelConnection* p = NEW GgafDx9ModelConnection(prm_idstr, prm_pResource);
    TRACE(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return p;
}

GgafDx9ModelManager::~GgafDx9ModelManager() {
    TRACE("GgafDx9ModelManager::~GgafDx9ModelManager() start-->");
    RELEASE_IMPOSSIBLE_NULL(_pIDirectXFile);
    _pTextureManager->dump();
    DELETE_IMPOSSIBLE_NULL(_pTextureManager);
    TRACE("GgafDx9ModelManager::releaseAll() するけども、ここでは既に何も開放するものがないはずです");
    releaseAll();
    TRACE("GgafDx9ModelManager::~GgafDx9ModelManager() end<--");

}

void GgafDx9ModelManager::restoreAll() {
    TRACE("GgafDx9ModelManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    TRACE("restoreAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->restore();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::restoreAll() end<--");
}

void GgafDx9ModelManager::onDeviceLostAll() {
    TRACE("GgafDx9ModelManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    TRACE("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->onDeviceLost();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::onDeviceLostAll() end<--");
}

void GgafDx9ModelManager::releaseAll() {
    TRACE("GgafDx9ModelManager::releaseAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pTop;
    while (pCurrent != NULL) {
        pCurrent->view()->release();
        pCurrent = pCurrent->_pNext;
    }
    TRACE("GgafDx9ModelManager::releaseAll() end<--");
}

