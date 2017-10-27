#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshSetActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxMeshSetEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxMeshSetModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxMeshSetModel::GgafDxMeshSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _pModel3D = nullptr;
    _pMeshesFront = nullptr;
    // prm_model_name には "xxxxxx" or "8/xxxxx" が、渡ってくる。
    // 同時描画セット数が8という意味です。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残そうかな。
    // モデル名から同時描画セット数指定があれば取り出す。無ければ8
    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 15) {
            _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大は15セットがですがそれ以上が設定されています。意図していますか？ _set_num="<<_set_num<<"。");
        }
    } else {
        _TRACE_("GgafDxMeshSetModel("<<prm_model_name<<") のセット数省略のため、標準の最大の15セットが設定されます。");
        _set_num = 15;
    }
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _paUint_material_list_grp_num = nullptr;
    _paVtxBuffer_data = nullptr;
    _paIndexBuffer_data = nullptr;
    _papaIndexParam = nullptr;
    _size_vertex_unit= 0;
    _size_vertices = 0;
    _nVertices = 0;
    _nFaces= 0;

    _obj_model |= Obj_GgafDxMeshSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restoreMeshSetModel(GgafDxMeshSetModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxMeshSetModel::GgafDxMeshSetModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDxMeshSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxMeshSetActor* const pTargetActor = (GgafDxMeshSetActor*)prm_pActor_target;
    //対象MeshSetActorのエフェクトラッパ
    GgafDxMeshSetEffect* const pMeshSetEffect = (GgafDxMeshSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxMeshSetModel::FVF);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular, _specular);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMeshSetEffect->_h_specular_power, _specular_power);
        checkDxException(hr, D3D_OK, "SetFloat(_h_specular_power) に失敗しました。");
    }

    //描画
    const UINT material_list_grp_num = _paUint_material_list_grp_num[prm_draw_set_num-1];
    for (UINT material_grp_index = 0; material_grp_index < material_list_grp_num; material_grp_index++) {
        const INDEXPARAM& idxparam = _papaIndexParam[prm_draw_set_num-1][material_grp_index];
        //モデルが同じでかつ、セット数も同じかつ、マテリアルNOが１つしかないならば、テクスチャ設定もスキップできる
        if (GgafDxModelManager::_pModelLastDraw  != this || material_list_grp_num != 1) {
            const UINT material_no = idxparam.MaterialNo;
            if (_papTextureConnection[material_no]) {
                if (material_no == 0) {
                    //マテリアル0番は、特別に規定のテクスチャを設定する仕様
                    pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
                } else {
                    pDevice->SetTexture(0, _papTextureConnection[material_no]->peek()->_pIDirect3DBaseTexture9);
                }
            } else {
                _TRACE_("GgafDxMeshSetModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
                //無ければテクスチャ無し
                pDevice->SetTexture(0, nullptr);
            }
            //MaterialDiffuseはGgafDxMeshSetActor側でマテリアルを設定する。マテリアル色は単色とする。
            //理由はGgafDxMeshSetActorのメモ【GgafDxMeshSetActorのマテリアルカラーについて】を参照
        }
        GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
        if (material_grp_index == 0 && (GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)) {
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
            _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);
            hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
            checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

            _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name<<"("<<pMeshSetEffect<<")");
            //UINT numPass;
            hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
            checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
            if (pMeshSetEffect->_begin) {
                throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
            } else {
                pMeshSetEffect->_begin = true;
            }
#endif
        } else {
            hr = pID3DXEffect->CommitChanges();
            checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
        }
        _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMeshSetEffect->_effect_name);

        pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                      idxparam.BaseVertexIndex,
                                      idxparam.MinIndex,
                                      idxparam.NumVertices,
                                      idxparam.StartIndex,
                                      idxparam.PrimitiveCount);
        if (_num_pass >= 2) { //２パス目以降が存在
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            for (UINT i = 1; i < _num_pass; i++) {
                hr = pID3DXEffect->BeginPass(i);
                checkDxException(hr, D3D_OK, i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
                pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                              idxparam.BaseVertexIndex,
                                              idxparam.MinIndex,
                                              idxparam.NumVertices,
                                              idxparam.StartIndex,
                                              idxparam.PrimitiveCount);
                hr = pID3DXEffect->EndPass();
                checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
            }
            hr = pID3DXEffect->BeginPass(0);
            checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
        }
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif
    }
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMeshSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxMeshSetModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
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
         throwGgafCriticalException("メッシュファイル(*.x)が見つかりません。model_name="<<(_model_name));
    }

    HRESULT hr;
    //流し込む頂点バッファデータ作成
    ToolBox::IO_Model_X iox;

    Frm::Model3D* pModel3D = nullptr;
    Frm::Mesh* pMeshesFront = nullptr;

    GgafDxMeshSetModel::INDEXPARAM** papaIndexParam = nullptr;
    GgafDxMeshSetModel::VERTEX* unit_paVtxBuffer_data = nullptr;
    GgafDxMeshSetModel::VERTEX* paVtxBuffer_data = nullptr;
    WORD* unit_paIndexBuffer_data = nullptr;
    WORD* paIdxBuffer_data = nullptr;
    D3DMATERIAL9* paMaterial = nullptr;

    int nVertices = 0;
    int nTextureCoords = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;

    if (_pModel3D == nullptr) {
        pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, pModel3D);
        if (r == false) {
            throwGgafCriticalException("Xファイルの読込み失敗。対象="<<xfile_name);
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

        pMeshesFront = pModel3D->_Meshes.front();
        nVertices = pMeshesFront->_nVertices;
        nTextureCoords = pMeshesFront->_nTextureCoords;
        nFaces = pMeshesFront->_nFaces;
//        nFaceNormals = pMeshesFront->_nFaceNormals;
        unit_paVtxBuffer_data = NEW GgafDxMeshSetModel::VERTEX[nVertices];

        if (nVertices*_set_num > 65535) {
            throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:"<<nVertices<<"  セット数:"<<(_set_num));
        }

        _nVertices = nVertices;
        _nFaces = nFaces;
        _size_vertices = sizeof(GgafDxMeshSetModel::VERTEX) * nVertices;
        _size_vertex_unit = sizeof(GgafDxMeshSetModel::VERTEX);

        //法線以外設定
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            unit_paVtxBuffer_data[i].x = pMeshesFront->_Vertices[i].data[0];
            unit_paVtxBuffer_data[i].y = pMeshesFront->_Vertices[i].data[1];
            unit_paVtxBuffer_data[i].z = pMeshesFront->_Vertices[i].data[2];
            unit_paVtxBuffer_data[i].nx = 0.0f;
            unit_paVtxBuffer_data[i].ny = 0.0f;
            unit_paVtxBuffer_data[i].nz = 0.0f;
            unit_paVtxBuffer_data[i].color = D3DCOLOR_ARGB(255,255,255,255); //頂点カラーは今の所使っていない
            if (i < nTextureCoords) {
                unit_paVtxBuffer_data[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //出来る限りUV座標設定
                unit_paVtxBuffer_data[i].tv = pMeshesFront->_TextureCoords[i].data[1];
            } else {
                unit_paVtxBuffer_data[i].tu = 0;
                unit_paVtxBuffer_data[i].tv = 0;
            }
            unit_paVtxBuffer_data[i].index = 0; //頂点番号（むりやり埋め込み）

            //距離
            model_bounding_sphere_radius = (FLOAT)(sqrt(unit_paVtxBuffer_data[i].x * unit_paVtxBuffer_data[i].x +
                                                        unit_paVtxBuffer_data[i].y * unit_paVtxBuffer_data[i].y +
                                                        unit_paVtxBuffer_data[i].z * unit_paVtxBuffer_data[i].z));
            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV座標数が、頂点バッファ数を越えてます。頂点数までしか設定されません。対象="<<xfile_name);
        }
        //法線設定とFrameTransformMatrix適用
        prepareVtx((void*)unit_paVtxBuffer_data, _size_vertex_unit,
                   pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //インデックスバッファ登録
        unit_paIndexBuffer_data = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            unit_paIndexBuffer_data[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            unit_paIndexBuffer_data[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            unit_paIndexBuffer_data[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }

        //頂点バッファをセット数分繰り返しコピーで作成
        paVtxBuffer_data = NEW GgafDxMeshSetModel::VERTEX[nVertices * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nVertices; j++) {
                paVtxBuffer_data[(i*nVertices) + j] = unit_paVtxBuffer_data[j];
                paVtxBuffer_data[(i*nVertices) + j].index = (float)i; //+= (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paVtxBuffer_data);

        //インデックスバッファをセット数分繰り返しコピーで作成
        paIdxBuffer_data = NEW WORD[(nFaces*3) * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBuffer_data[((i*nFaces*3)+(j*3)) + 0] = unit_paIndexBuffer_data[j*3 + 0] + (nVertices*i);
                paIdxBuffer_data[((i*nFaces*3)+(j*3)) + 1] = unit_paIndexBuffer_data[j*3 + 1] + (nVertices*i);
                paIdxBuffer_data[((i*nFaces*3)+(j*3)) + 2] = unit_paIndexBuffer_data[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIndexBuffer_data);

        //マテリアルリストをセット数分繰り返しコピーで作成
        uint16_t* paFaceMaterials = NEW uint16_t[nFaces * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paFaceMaterials[(i*nFaces) + j] = pMeshesFront->_FaceMaterials[j];
            }
        }

        //パラメータもをセット数分繰り返しコピーで作成
        papaIndexParam = NEW GgafDxMeshSetModel::INDEXPARAM*[_set_num];
        _paUint_material_list_grp_num = NEW UINT[_set_num];
        for (int set_index = 0; set_index < _set_num; set_index++) {
            GgafDxMeshSetModel::INDEXPARAM* paParam = NEW GgafDxMeshSetModel::INDEXPARAM[nFaces * (set_index+1)];
            int prev_materialno = -1;
            int materialno = 0;
            int paramno = 0;
            int faceNoCnt_break = 0;
            int prev_faceNoCnt_break = -1;
            UINT max_num_vertices = 0;
            UINT min_num_vertices = UINT_MAX;

            int faceNoCnt;
            for (faceNoCnt = 0; faceNoCnt < nFaces * (set_index+1); faceNoCnt++) {
                materialno = paFaceMaterials[faceNoCnt];
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

                if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                    max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
                }
                if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                    max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
                }
                if (max_num_vertices <  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                    max_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
                }
                if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 0]) {
                    min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 0];
                }
                if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 1]) {
                    min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 1];
                }
                if (min_num_vertices >  paIdxBuffer_data[faceNoCnt*3 + 2]) {
                    min_num_vertices = paIdxBuffer_data[faceNoCnt*3 + 2];
                }
                prev_materialno = materialno;
            }
            if (nFaces > 0) {
                paParam[paramno-1].MinIndex = min_num_vertices;
                paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
            }

            papaIndexParam[set_index] = NEW GgafDxMeshSetModel::INDEXPARAM[paramno];
            for (int i = 0; i < paramno; i++) {
                papaIndexParam[set_index][i].MaterialNo = paParam[i].MaterialNo;
                papaIndexParam[set_index][i].BaseVertexIndex = paParam[i].BaseVertexIndex;
                papaIndexParam[set_index][i].MinIndex = paParam[i].MinIndex;
                papaIndexParam[set_index][i].NumVertices = paParam[i].NumVertices;
                papaIndexParam[set_index][i].StartIndex = paParam[i].StartIndex;
                papaIndexParam[set_index][i].PrimitiveCount = paParam[i].PrimitiveCount;
            }

            _paUint_material_list_grp_num[set_index] = paramno;
            delete[] paParam;
        }

        GGAF_DELETEARR(paFaceMaterials);
    }

    if (_pVertexBuffer == nullptr) {
        //頂点バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxMeshSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(
                                      0,
                                      _size_vertices * _set_num,
                                      (void**)&pVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);

        memcpy(
          pVertexBuffer,
          paVtxBuffer_data,
          _size_vertices * _set_num
        ); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
    }


    //流し込むインデックスバッファデータ作成
    if (_pIndexBuffer == nullptr) {

        nFaces = pMeshesFront->_nFaces;

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * _set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBuffer_data,
          sizeof(WORD) * nFaces * 3 * _set_num
        );
        _pIndexBuffer->Unlock();
    }


    //マテリアル設定
    setMaterial(pMeshesFront);

    if (!_papTextureConnection) {
        _papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
        for (int n = 0; n < _num_materials; n++) {
            _papTextureConnection[n] =
                    (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[n].c_str(), this));
        }
    }

    //モデルに保持させる
    _pModel3D = pModel3D;
    _pMeshesFront = pMeshesFront;

    _paIndexBuffer_data = paIdxBuffer_data;
    _paVtxBuffer_data = paVtxBuffer_data;
    _papaIndexParam = papaIndexParam;
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMeshSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxMeshSetModel::release() {
    _TRACE3_("_model_name=" << _model_name << " start");

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

    GGAF_DELETEARR(_paVtxBuffer_data);
    GGAF_DELETEARR(_paIndexBuffer_data);

    GGAF_DELETE(_pModel3D);
    //_pMeshesFront は _pModel3D をDELETEしているのでする必要は無い
    _pMeshesFront = nullptr;
    if (_papaIndexParam) {
        for (int i = 0; i < _set_num; i++) {
            GGAF_DELETEARR(_papaIndexParam[i]);
        }
    }
    GGAF_DELETEARR(_papaIndexParam);
    GGAF_DELETEARR(_paUint_material_list_grp_num);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");

}
GgafDxMeshSetModel::~GgafDxMeshSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

