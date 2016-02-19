#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"

using namespace GgafCore;
using namespace GgafDxCore;

//DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
DWORD GgafDxMeshModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
                                    D3DFVF_TEXCOORDSIZE2(0) | // real texture coord
                                    D3DFVF_TEXCOORDSIZE3(1) | // tangent
                                    D3DFVF_TEXCOORDSIZE3(2)   // binormal
                                    );
GgafDxMeshModel::GgafDxMeshModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxMeshModel::GgafDxMeshModel(" << _model_name << ")");
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;

    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paVtxBuffer_org = nullptr;
    _paIdxBuffer_org = nullptr;
    _paIndexParam = nullptr;
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    _material_list_grp_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _obj_model |= Obj_GgafDxMeshModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreMeshModel(GgafDxMeshModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxMeshModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    //GgafDxMeshActor* pTargetActor = (GgafDxMeshActor*)prm_pActor_target;
    const GgafDxFigureActor* const pTargetActor = prm_pActor_target;
    //対象MeshActorのエフェクトラッパ
    GgafDxMeshEffect* const pMeshEffect = (GgafDxMeshEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshEffect->_pID3DXEffect;

    HRESULT hr;
    UINT material_no;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxMeshModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    for (UINT i = 0; i < _material_list_grp_num; i++) {
        const INDEXPARAM& idxparam = _paIndexParam[i];
        material_no = idxparam.MaterialNo;
        if (GgafDxModelManager::_pModelLastDraw != this || _material_list_grp_num != 1) {
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxMeshModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
        }
        hr = pID3DXEffect->SetValue(pMeshEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[material_no].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if ((pEffect_active != pMeshEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique) && i == 0) {
            //本モデル描画初回
            if (pEffect_active) {
                _TRACE4_("前回_pEffect_active != pMeshEffect (" <<(pEffect_active->_effect_name)<<"!="<<(pMeshEffect->_effect_name)<<")");
                _TRACE4_("EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
                hr = pEffect_active->_pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() EndPass() に失敗しました。");
                hr = pEffect_active->_pID3DXEffect->End();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() End() に失敗しました。");
                if (pEffect_active->_obj_effect & Obj_GgafDxMassMeshEffect) {
                    pDevice->SetStreamSourceFreq( 0, 1 );
                    pDevice->SetStreamSourceFreq( 1, 1 );
                }
#ifdef MY_DEBUG
                if (pEffect_active->_begin == false) {
                    throwGgafCriticalException("begin していません "<<(pEffect_active==nullptr?"nullptr":pEffect_active->_effect_name)<<"");
                } else {
                    pEffect_active->_begin = false;
                }
#endif
            }
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "GgafDxMeshModel::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name<<"("<<pMeshEffect<<")");
            hr = pID3DXEffect->Begin( &_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() BeginPass(0) に失敗しました。");
#ifdef MY_DEBUG
            if (pMeshEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshEffect->_begin = true;
            }
#endif

        } else {
            //前回描画と同じモデル
            hr = pID3DXEffect->CommitChanges(); //マテリアルをコミットしなければいけない。
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshEffect->_effect_name);
        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() １パス目 EndPass() に失敗しました。");
            for (UINT pass = 1; pass < _num_pass; pass++) {
                hr = pID3DXEffect->BeginPass(pass);
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"パス目 BeginPass("<<pass<<") に失敗しました。");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() "<<pass+1<<"パス目 EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "GgafDxMeshModel::draw() １パス目 BeginPass(0) に失敗しました。");
        }
        GgafGod::_num_drawing++;
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshModel::restore() {
    _TRACE3_("GgafDxMeshModel::restore() " << _model_name << " start");
    //【GgafDxMeshModel再構築（＝初期化）処理概要】
    //１）頂点バッファ、頂点インデックスバッファ を new
    //２）Xファイルから、独自に次の情報を読み込み、頂点バッファ、頂点インデックスバッファ に流し込む。
    //３）２）を行なう過程で、同時に GgafDxMeshModel に次のメンバを作成。
    //      ・頂点バッファの写し
    //      ・頂点インデックスバッファの写し
    //      ・マテリアル配列(要素数＝マテリアル数)
    //      ・テクスチャ配列(要素数＝マテリアル数)
    //      ・DrawIndexedPrimitive用引数配列(要素数＝マテリアルリストが変化した数)


    std::string xfile_name = GgafDxModelManager::getMeshFileName(_model_name);
    if (xfile_name == "") {
        throwGgafCriticalException("GgafDxModelManager::restoreMeshModel メッシュファイル(*.x)が見つかりません。_model_name="<<_model_name);
    }
    HRESULT hr;

    //流し込む頂点バッファデータ作成
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = nullptr;
    Frm::Mesh*    model_pMeshesFront = nullptr;

    GgafDxMeshModel::INDEXPARAM* model_paIndexParam = nullptr;
    GgafDxMeshModel::VERTEX*     model_paVtxBuffer_org = nullptr;
    WORD*                        model_paIdxBuffer_org = nullptr;
    D3DMATERIAL9*                model_paMaterial = nullptr;
    GgafDxTextureConnection**    model_papTextureConnection = nullptr;
    int nVertices = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;

    if (_pModel3D == nullptr) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMeshModel] Xファイルの読込み失敗。対象="<<xfile_name);
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
        nVertices = model_pMeshesFront->_nVertices; //メッシュ連結後の総頂点数
        nFaces = model_pMeshesFront->_nFaces;       //メッシュ連結後の総面数
//        nFaceNormals = model_pMeshesFront->_nFaceNormals; //メッシュ連結後の総法線数
        model_paVtxBuffer_org = NEW GgafDxMeshModel::VERTEX[nVertices];
        _size_vertices = sizeof(GgafDxMeshModel::VERTEX) * nVertices;
        _size_vertex_unit = sizeof(GgafDxMeshModel::VERTEX);
        int nTextureCoords = model_pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            _TRACE3_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE3_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<xfile_name);
        }

        //頂点バッファ作成開始！
        //法線以外設定
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            model_paVtxBuffer_org[i].x = model_pMeshesFront->_Vertices[i].data[0];
            model_paVtxBuffer_org[i].y = model_pMeshesFront->_Vertices[i].data[1];
            model_paVtxBuffer_org[i].z = model_pMeshesFront->_Vertices[i].data[2];
            model_paVtxBuffer_org[i].nx = 0.0f;
            model_paVtxBuffer_org[i].ny = 0.0f;
            model_paVtxBuffer_org[i].nz = 0.0f;
            model_paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラーは今の所使っていない
            if (i < nTextureCoords) {
                model_paVtxBuffer_org[i].tu = model_pMeshesFront->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                model_paVtxBuffer_org[i].tv = model_pMeshesFront->_TextureCoords[i].data[1];
            } else {
                model_paVtxBuffer_org[i].tu = 0.0f;
                model_paVtxBuffer_org[i].tv = 0.0f;
            }
            model_paVtxBuffer_org[i].tan_x = 0.0f;
            model_paVtxBuffer_org[i].tan_y = 0.0f;
            model_paVtxBuffer_org[i].tan_z = 0.0f;
            model_paVtxBuffer_org[i].bin_x = 0.0f;
            model_paVtxBuffer_org[i].bin_y = 0.0f;
            model_paVtxBuffer_org[i].bin_z = 0.0f;


            //距離
            model_bounding_sphere_radius = (FLOAT)(sqrt(model_paVtxBuffer_org[i].x * model_paVtxBuffer_org[i].x +
                                                        model_paVtxBuffer_org[i].y * model_paVtxBuffer_org[i].y +
                                                        model_paVtxBuffer_org[i].z * model_paVtxBuffer_org[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //頂点バッファ作成
        prepareVtx((void*)model_paVtxBuffer_org, _size_vertex_unit,
                    model_pModel3D, paNumVertices);

        GGAF_DELETE(paNumVertices);

        //インデックスバッファ登録
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //描画時（DrawIndexedPrimitive）のパラメータリスト作成
        GgafDxMeshModel::INDEXPARAM* paParam = NEW GgafDxMeshModel::INDEXPARAM[nFaces]; //最高にマテリアルがバラバラだった場合nFaces必要

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = model_pMeshesFront->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //_TRACE3_("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = UINT_MAX; //次回ブレイク時に設定、必ずブレイクしたいため変な値にしとく
                paParam[paramno].NumVertices = UINT_MAX; //次回ブレイク時に設定
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = UINT_MAX; //次回ブレイク時に設定

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //リセット
                    max_num_vertices = 0;
                    min_num_vertices = UINT_MAX;
                }
                paramno++;
            }

            if (max_num_vertices <  model_paIdxBuffer_org[faceNoCnt*3 + 0]) {
                max_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  model_paIdxBuffer_org[faceNoCnt*3 + 1]) {
                max_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  model_paIdxBuffer_org[faceNoCnt*3 + 2]) {
                max_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  model_paIdxBuffer_org[faceNoCnt*3 + 0]) {
                min_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  model_paIdxBuffer_org[faceNoCnt*3 + 1]) {
                min_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  model_paIdxBuffer_org[faceNoCnt*3 + 2]) {
                min_num_vertices = model_paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        model_paIndexParam = NEW GgafDxMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            model_paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            model_paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            model_paIndexParam[i].MinIndex = paParam[i].MinIndex;
            model_paIndexParam[i].NumVertices = paParam[i].NumVertices;
            model_paIndexParam[i].StartIndex = paParam[i].StartIndex;
            model_paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        _material_list_grp_num = paramno;

        delete[] paParam;
    }

    if (_pVertexBuffer == nullptr) {

        //頂点バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));

        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] 頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pVertexBuffer, model_paVtxBuffer_org, _size_vertices); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
    }


    //インデックスバッファデータ作成
    if (_pIndexBuffer == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));
        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , model_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
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
    _paVtxBuffer_org = model_paVtxBuffer_org;
    _paIndexParam = model_paIndexParam;
    _paMaterial_default = model_paMaterial;
    _papTextureConnection = model_papTextureConnection;
    _num_materials = model_nMaterials;


//        //デバッグ
//        _TRACE_("#頂点バッファ nVertices="<<nVertices);
//        float x,y,z,nx,ny,nz,tu,tv,tan_x,tan_y,tan_z,bin_x,bin_y,bin_z;
//        for (int i = 0; i < nVertices; i++) {
//            x = model_paVtxBuffer_org[i].x;
//            y = model_paVtxBuffer_org[i].y;
//            z = model_paVtxBuffer_org[i].z;
//            nx = model_paVtxBuffer_org[i].nx;
//            ny = model_paVtxBuffer_org[i].ny;
//            nz = model_paVtxBuffer_org[i].nz;
//            tu = model_paVtxBuffer_org[i].tu;
//            tv = model_paVtxBuffer_org[i].tv;
//            tan_x = model_paVtxBuffer_org[i].tan_x;
//            tan_y = model_paVtxBuffer_org[i].tan_y;
//            tan_z = model_paVtxBuffer_org[i].tan_z;
//            bin_x = model_paVtxBuffer_org[i].bin_x;
//            bin_y = model_paVtxBuffer_org[i].bin_y;
//            bin_z = model_paVtxBuffer_org[i].bin_z;
//            //デバッグ
//            //_TRACE_("頂点["<<i<<"] pos("<<x<<","<<y<<","<<z<<")\tuv("<<tu<<","<<tv<<")\tn("<<nx<<","<<ny<<","<<nz<<")\tt("<<tan_x<<","<<tan_y<<","<<tan_z<<")\tb("<<bin_x<<","<<bin_y<<","<<bin_z<<")");
//        }


//    {
//        //デバッグ
//        _TRACE_("#頂点バッファ nVertices="<<nVertices);
//        float x,y,z,nx,ny,nz,tu,tv;
//        for (int i = 0; i < nVertices; i++) {
//            x = model_paVtxBuffer_org[i].x;
//            y = model_paVtxBuffer_org[i].y;
//            z = model_paVtxBuffer_org[i].z;
//            nx = model_paVtxBuffer_org[i].nx;
//            ny = model_paVtxBuffer_org[i].ny;
//            nz = model_paVtxBuffer_org[i].nz;
//            tu = model_paVtxBuffer_org[i].tu;
//            tv = model_paVtxBuffer_org[i].tv;
//
//            _TRACE_("頂点["<<i<<"] "<<x<<";"<<y<<";"<<z<<";,\t"<<nx<<";"<<ny<<";"<<nz<<";,\t"<<tu<<";"<<tv<<";,");
//        }
//
//
//        _TRACE_("#インデックスバッファ nFaces="<<nFaces);
//        WORD vtx1,vtx2,vtx3;
//        for (int face = 0; face < nFaces; face++) {
//            vtx1 = model_paIdxBuffer_org[face*3 + 0];
//            vtx2 = model_paIdxBuffer_org[face*3 + 1];
//            vtx3 = model_paIdxBuffer_org[face*3 + 2];
//            _TRACE_("面["<<face<<"] 3;"<<vtx1<<","<<vtx2<<","<<vtx3<<";,");
//        }
//
//        _TRACE_("マテリアル  model_nMaterials="<<model_nMaterials);
//        float a,r,g,b;
//        for (int i = 0; i < model_nMaterials; i++) {
//            a = model_paMaterial[i].Diffuse.a;
//            r = model_paMaterial[i].Diffuse.r;
//            g = model_paMaterial[i].Diffuse.g;
//            b = model_paMaterial[i].Diffuse.b;
//            _TRACE_("nMaterial["<<i<<"] Diffuse(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//            a = model_paMaterial[i].Ambient.a;
//            r = model_paMaterial[i].Ambient.r;
//            g = model_paMaterial[i].Ambient.g;
//            b = model_paMaterial[i].Ambient.b;
//            _TRACE_("nMaterial["<<i<<"] Ambient(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//        }
//
//        _TRACE_("#マテリアルリスト _material_list_grp_num="<< _material_list_grp_num);
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            int material_no = _paIndexParam[i].MaterialNo;
//            _TRACE_("MaterialGrp["<<i<<"] "<<material_no<<",");
//        }
//
//        _TRACE_("#IndexParam  _material_list_grp_num="<< _material_list_grp_num);
//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//        for (UINT i = 0; i < _material_list_grp_num; i++) {
//            MaterialNo = model_paIndexParam[i].MaterialNo;
//            BaseVertexIndex = model_paIndexParam[i].BaseVertexIndex;
//            MinIndex = model_paIndexParam[i].MinIndex;
//            NumVertices = model_paIndexParam[i].NumVertices;
//            StartIndex = model_paIndexParam[i].StartIndex;
//            PrimitiveCount = model_paIndexParam[i].PrimitiveCount;
//            _TRACE_("MaterialGrp["<<i<<"] MaterialNo="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] BaseVertexIndex="<<BaseVertexIndex);
//            _TRACE_("MaterialGrp["<<i<<"] MinIndex="<<MinIndex);
//            _TRACE_("MaterialGrp["<<i<<"] NumVertices="<<MaterialNo);
//            _TRACE_("MaterialGrp["<<i<<"] StartIndex="<<StartIndex);
//            _TRACE_("MaterialGrp["<<i<<"] PrimitiveCount="<<PrimitiveCount);
//        }
//    }
    _TRACE3_("GgafDxMeshModel::restore() " << _model_name << " end");
}

void GgafDxMeshModel::onDeviceLost() {
    _TRACE3_("GgafDxMeshModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxMeshModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxMeshModel::release() {
    _TRACE3_("GgafDxMeshModel::release() " << _model_name << " start");

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

    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);

    GGAF_DELETEARR(_paVtxBuffer_org);
    GGAF_DELETEARR(_paIdxBuffer_org);
    GGAF_DELETE(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;
    GGAF_DELETEARR(_paIndexParam);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);


    _TRACE3_("GgafDxMeshModel::release() " << _model_name << " end");

}
GgafDxMeshModel::~GgafDxMeshModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}


