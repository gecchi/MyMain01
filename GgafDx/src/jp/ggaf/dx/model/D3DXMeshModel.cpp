#include "jp/ggaf/dx/model/D3DXMeshModel.h"

#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/D3DXMeshActor.h"
#include "jp/ggaf/dx/effect/MeshEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/MassModel.h"
#include "jp/ggaf/dx/texture/Texture.h"

using namespace GgafDx;

D3DXMeshModel::D3DXMeshModel(const char* prm_model_id, DWORD prm_dwOptions) : Model(prm_model_id) {
    _obj_class |= Obj_GgafDx_D3DXMeshModel;
    _pID3DXMesh = nullptr;
    _num_materials = 0L;
    _dwOptions = prm_dwOptions;
    _max_draw_set_num = 1;
}

HRESULT D3DXMeshModel::draw(FigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("D3DXMeshModel::draw("<<prm_pActor_target->getName()<<")");
    IDirect3DDevice9* const pDevice = pCARETAKER->_pID3DDevice9;
    //対象アクター
    const D3DXMeshActor* const pTargetActor = (D3DXMeshActor*)prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    MeshEffect* const pMeshEffect = (MeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    pDevice->SetFVF(D3DXMeshActor::FVF);
    HRESULT hr;
    Model* pModelLastDraw = ModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_class & Obj_GgafDx_MassModel)) {
            ((MassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
    }
    for (DWORD i = 0; i < _num_materials; i++) {
        if (ModelManager::_pModelLastDraw != this || _num_materials != 1) {
            if (_papTextureConnection[i]) {
                if (i == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[i]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("D3DXMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(CONFIG::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
            //マテリアルのセット
            hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[i].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
            checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
            checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
            checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
            checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
        }

        //描画
        Effect* pEffect_active = EffectManager::_pEffect_active;
        if ((FigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            UINT numPass;
            hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwCriticalException("End していません "<<(EffectManager::_pEffect_active==nullptr?"nullptr":EffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawSubset: /actor="<<pTargetActor->getName()<<"/model="<<_model_id<<" effect="<<pMeshEffect->_effect_name);
        hr = _pID3DXMesh->DrawSubset(i);  //なんて便利なメソッド。
#ifdef MY_DEBUG
        GgafCore::Caretaker::_num_drawing++;
#endif
    }
    //前回描画モデル名反映
    ModelManager::_pModelLastDraw = this;
    EffectManager::_pEffect_active = pMeshEffect;
    FigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;

    return D3D_OK;
}

//シェーダー実装前
//        if (pTargetActor->_sx == LEN_UNIT &&
//            pTargetActor->_sy == LEN_UNIT &&
//            pTargetActor->_sz == LEN_UNIT)
//        {
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//        } else {
//            //拡大縮小がなされているため、カメラ空間にトランスフォームされた後で頂点法線の正規化するように設定（負荷高）
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//            hr = _pID3DXMesh->DrawSubset(i); //なんて便利なメソッド！
//            pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
//        }


void D3DXMeshModel::restore() {
    _TRACE3_("_model_id=" << _model_id << " start");
    ModelManager* pModelManager = pCARETAKER->_pModelManager;
    //【restoreD3DXMeshModel再構築（＝初期化）処理概要】
    //1)D3DXLoadMeshFromXを使用してXファイルを読み込む
    //2)D3DXMeshModelのメンバにセット

    ModelManager::MeshXFileFmt xdata;
    std::string model_def_file = std::string(_model_id) + ".meshx";
    std::string model_def_filepath = Model::getModelDefineFilePath(model_def_file);
    pModelManager->obtainMeshModelInfo(&xdata, model_def_filepath);
    _matBaseTransformMatrix = xdata.BaseTransformMatrix;
    _draw_set_num = xdata.DrawSetNum;
    if (_draw_set_num != 1) {
        _TRACE_("D3DXMeshModel::restore() 本モデルの "<<_model_id<<" の同時描画セット数は 1 に上書きされました。（_draw_set_num="<<_draw_set_num<<" は無視されました。）");
        _draw_set_num = 1;
    }
    std::string xfilepath = Model::getXFilePath(xdata.XFileNames[0]);

    //Xファイルのロードして必要な内容をD3DXMeshModelメンバに設定しインスタンスとして完成させたい
    LPD3DXMESH pID3DXMesh; //メッシュ(ID3DXMeshインターフェイスへのポインタ）
    D3DMATERIAL9* paMaterial; //マテリアル(D3DXMATERIAL構造体の配列の先頭要素を指すポインタ）
    TextureConnection** papTextureConnection; //テクスチャ配列(IDirect3DTexture9インターフェイスへのポインタを保持するオブジェクト）
    DWORD num_materials;

//    std::string xfile_name = Model::getModelDefineFilePath(_model_id, "meshx");
//    if (xfile_name == "") {
//         throwCriticalException("メッシュファイル(*.x)が見つかりません。model_id="<<(_model_id));
//    }

    LPD3DXBUFFER pID3DXBuffer; //受け取り用バッファ（マテリアル用）
    HRESULT hr;
    //Xファイルのファイルロード
    hr = D3DXLoadMeshFromX(
            xfilepath.c_str(),             //[in]  LPCTSTR pFilename
            _dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
            pCARETAKER->_pID3DDevice9,       //[in]  LPDIRECT3DDEVICE9 pDevice
            nullptr,                        //[out] LPD3DXBUFFER* ppAdjacency
            &pID3DXBuffer,                  //[out] LPD3DXBUFFER* ppMaterials
            nullptr,                        //[out] LPD3DXBUFFER* ppEffectInstances
            &num_materials,                //[out] DWORD* pNumMaterials
            &pID3DXMesh                     //[out] LPD3DXMESH* pMesh
         );
    checkDxException(hr, D3D_OK, "D3DXLoadMeshFromXによるロードが失敗。対象="<<xfilepath);

    IDirect3DVertexBuffer9* pVb_load;
    pID3DXMesh->GetVertexBuffer(&pVb_load);
    DWORD size_vertex_unit = pID3DXMesh->GetNumBytesPerVertex(); // 1つの頂点のサイズ
    void* paVertexBuffer;
    int nVertices = (int)(pID3DXMesh->GetNumVertices()); //メッシュコンテナの頂点数
    pVb_load->Lock(0, nVertices*size_vertex_unit, (void**)&paVertexBuffer, 0);
//    for (int vi = 0; vi < nVertices; vi++) {
//        Model::VERTEX_POS* pVtx = (Model::VERTEX_POS*)pVb_load + (size_vertex_unit*vi);  //読み込む1頂点の開始アドレス
//    }
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        //Xファイルに法線がない場合
        transformPosVtx(paVertexBuffer, size_vertex_unit, nVertices);
    } else {
        transformPosNomalVtx(paVertexBuffer, size_vertex_unit, nVertices);
    }
    pVb_load->Unlock();
    pVb_load->Release();

    //最適化
    DWORD *pAdjacency = NEW DWORD [ pID3DXMesh->GetNumFaces() * 3 ];
    hr = pID3DXMesh->GenerateAdjacency( 1e-6f, pAdjacency );
    checkDxException(hr, D3D_OK, "GenerateAdjacencyがつくれません。対象="<<xfilepath);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "D3DXMESHOPT_ATTRSORTできません。対象="<<xfilepath);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "D3DXMESHOPT_VERTEXCACHEできません。対象="<<xfilepath);
    GGAF_DELETEARR(pAdjacency);

    //マテリアルを取り出す
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //＜2008/02/02 の脳みそ＞
    // やっていることメモ
    // GetBufferPointer()で取得できる D3DXMATERIAL構造体配列のメンバのMatD3D (D3DMATERIAL9構造体) が欲しい。
    //構造体を物理コピーをして保存することにしましょ～、とりあえずそ～しましょう。
    paMaterial = NEW D3DMATERIAL9[num_materials];
    for ( DWORD i = 0; i < num_materials; i++) {
        paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //マテリアルのDiffuse反射をAmbient反射にコピーする
    //理由：Ambientライトを使用したかった。そのためには当然Ambient反射値をマテリアルに設定しなければいけないが
    //エクスポートされたxファイルのマテリアルにAmbient反射値が設定されてない（生成ツールのせい？）。
    //まぁほとんどDiffuse=Ambientで問題ないハズと考えた。
    //そこでデフォルトで、Diffuse反射値でAmbient反射値を設定することにする、とりあえず。
    //＜2009/3/13＞
    //固定パイプラインはもう使わなくなった。それに伴いマテリアルDiffuseはシェーダーのパラメータのみで利用している。
    //TODO:現在マテリアルAmbientは参照されない。今後もそうする？
    for ( DWORD i = 0; i < num_materials; i++) {
        paMaterial[i].Ambient = paMaterial[i].Diffuse;
    }

    //テクスチャを取り出す
    papTextureConnection = NEW TextureConnection*[num_materials];
    char* texture_filename;
    for ( DWORD i = 0; i < num_materials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
            papTextureConnection[i] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(texture_filename, this));
        } else {
            //テクスチャ無し
            papTextureConnection[i] = (TextureConnection*)(pModelManager->_pModelTextureManager->connect(CONFIG::WHITE_TEXTURE.c_str(), this));
        }
    }
    GGAF_RELEASE(pID3DXBuffer);//テクスチャファイル名はもういらないのでバッファ解放

    //Xファイルに法線がない場合、FVFに法線を追加し、法線を計算してを設定。
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = nullptr;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           pCARETAKER->_pID3DDevice9,             // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        checkDxException(hr, D3D_OK, " pID3DXMesh->CloneMeshFVF()失敗。対象="<<xfilepath);
        D3DXComputeNormals(pID3DXMesh_tmp, nullptr); //法線計算（Faceの表裏どっちに法線向けるか、どうやって判定しているのだろうか・・・）
        GGAF_RELEASE(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //メッシュ、マテリアル、テクスチャの参照、マテリアル数をモデルオブジェクトに保持させる
    _pID3DXMesh             = pID3DXMesh;
    _paMaterial_default     = paMaterial;
    _papTextureConnection   = papTextureConnection;
    _num_materials          = num_materials;
    _bounding_sphere_radius = 10.0f; //TODO:境界球半径大きさとりあえず100px
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXMeshModel::onDeviceLost() {
    _TRACE3_("_model_id=" << _model_id << " start");
    //デバイスロスト時は解放します。
    release();
    _TRACE3_("_model_id=" << _model_id << " end");
}

void D3DXMeshModel::release() {
    _TRACE3_("_model_id=" << _model_id << " start");
    if (_pID3DXMesh == nullptr) {
        _TRACE_("【警告】 [D3DXMeshModel::release()]  "<<_model_id<<" の _pID3DXMeshが オブジェクトになっていないため release できません！");
    }
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
    GGAF_RELEASE(_pID3DXMesh);
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_id=" << _model_id << " end");
}

D3DXMeshModel::~D3DXMeshModel() {
    //release();
    //はModelConnection::processReleaseResource(Model* prm_pResource) で呼び出される
}
