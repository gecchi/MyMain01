#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxBoardSetActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxBoardSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_TEX1);
GgafDxBoardSetModel::GgafDxBoardSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxBoardSetModel::GgafDxBoardSetModel(" << _model_name << ")");

    _model_width_px = 32.0f;
    _model_height_px = 32.0f;
    _row_texture_split = 1;
    _col_texture_split = 1;
    _pVertexBuffer = nullptr;
    _pIndexBuffer = nullptr;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _paIndexParam = nullptr;
    _obj_model |= Obj_GgafDxBoardSetModel;



    std::string model_name = std::string(prm_model_name);
    std::vector<std::string> names = UTIL::split(model_name, "/", 1);
    if (names.size() > 2) {
        throwGgafCriticalException("GgafDxBoardSetModel::GgafDxBoardSetModel "<<
                "prm_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                "実際の引数は、prm_idstr="<<prm_model_name);
    }
    if (names.size() == 2) {
        _set_num = STOI(names[0]);
        if (_set_num > 28) {
            _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") の同時描画セット数オーバー。最大の28がセットですが、それ以上のセット数です。意図していますか？_set_num="<<_set_num);
        }
    } else {
        _TRACE_("GgafDxBoardSetModel("<<prm_model_name<<") の同時描画セット数省略のため、最大の28がセットされます。");
        _set_num = 28;
    }

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restoreBoardSetModel(GgafDxBoardSetModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxBoardSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    _TRACE4_("GgafDxBoardSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_("GgafDxBoardSetModel::draw() "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    //対象Actor
    const GgafDxBoardSetActor* const pTargetActor = (GgafDxBoardSetActor*)prm_pActor_target;
    //対象BoardSetActorのエフェクトラッパ
    GgafDxBoardSetEffect* const pBoardSetEffect = (GgafDxBoardSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pBoardSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じならば頂点バッファ等、の設定はスキップできる
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxBoardSetModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        pDevice->SetIndices(_pIndexBuffer);

        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pBoardSetEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pBoardSetEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
           _TRACE4_("GgafDxBoardSetModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() End() に失敗しました。");
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
        _TRACE4_("GgafDxBoardSetModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxBoardSetActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("GgafDxBoardSetModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name<<"("<<pBoardSetEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxBoardSetActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pBoardSetEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pBoardSetEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxBoardSetModel::draw() CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pBoardSetEffect->_effect_name);
    const INDEXPARAM& idxparam = _paIndexParam[prm_draw_set_num-1];
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
                                  idxparam.BaseVertexIndex,
                                  idxparam.MinIndex,
                                  idxparam.NumVertices,
                                  idxparam.StartIndex,
                                  idxparam.PrimitiveCount);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pBoardSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_drawing++;
    return D3D_OK;
}

void GgafDxBoardSetModel::restore() {
    _TRACE3_("GgafDxBoardSetModel::restore() " << _model_name << " start");

    if (4*_set_num > 65535) {
        throwGgafCriticalException("[GgafDxModelManager::restoreBoardSetModel] 頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  nVertices:4  セット数:"<<(_set_num));
    }

    _papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name; //読み込むスプライト定義ファイル名（Xファイル形式）
    //"12/Moji" or "8/Moji" or "Moji" から "Moji" だけ取とりだしてフルパス名取得。
    //TODO:数値3桁("123/Moji"とか)が来たら困る。
    if (*(_model_name + 1) == '/') {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name + 2));
    } else if (*(_model_name + 2) == '/') {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name + 3));
    } else {
        xfile_name = GgafDxModelManager::getSpriteFileName(std::string(_model_name));
    }
    GgafDxModelManager::SpriteXFileFmt xdata;
    GgafDxModelManager::obtainSpriteInfo(&xdata, xfile_name);
    _model_width_px  = xdata.width;
    _model_height_px = xdata.height;
    _row_texture_split = xdata.row_texture_split;
    _col_texture_split = xdata.col_texture_split;

    //テクスチャ取得しモデルに保持させる
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(xdata.texture_file, this));
    //テクスチャの参照を保持させる。
    _papTextureConnection = NEW GgafDxTextureConnection*[1];
    _papTextureConnection[0] = model_pTextureConnection;

    if (_pVertexBuffer == nullptr) {

        _size_vertices = sizeof(GgafDxBoardSetModel::VERTEX)*4;
        _size_vertex_unit = sizeof(GgafDxBoardSetModel::VERTEX);
        GgafDxBoardSetModel::VERTEX* paVertex = NEW GgafDxBoardSetModel::VERTEX[4 * _set_num];

        //1pxあたりのuvの大きさを求める
//        float tex_width  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
//        float tex_height = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)
        double du = 0.0; //1.0 / tex_width  / 100000.0; //テクスチャの幅1pxの10000分の1px
        double dv = 0.0; //1.0 / tex_height / 100000.0; //テクスチャの高さ1pxの10000分の1px
        for (int i = 0; i < _set_num; i++) {
            //左上
            paVertex[i*4 + 0].x = 0.0f;
            paVertex[i*4 + 0].y = 0.0f;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].tu = du;
            paVertex[i*4 + 0].tv = dv;
            paVertex[i*4 + 0].index = (float)i;
            //右上
            paVertex[i*4 + 1].x = xdata.width;
            paVertex[i*4 + 1].y = 0.0f;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].tu = (1.0 / xdata.col_texture_split) - du;
            paVertex[i*4 + 1].tv = dv;
            paVertex[i*4 + 1].index = (float)i;
            //左下
            paVertex[i*4 + 2].x = 0.0f;
            paVertex[i*4 + 2].y = xdata.height;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].tu = du;
            paVertex[i*4 + 2].tv = (1.0 / xdata.row_texture_split) - dv;
            paVertex[i*4 + 2].index = (float)i;
            //右下
            paVertex[i*4 + 3].x = xdata.width;
            paVertex[i*4 + 3].y = xdata.height;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].tu = (1.0 / xdata.col_texture_split) - du;
            paVertex[i*4 + 3].tv = (1.0 / xdata.row_texture_split) - dv;
            paVertex[i*4 + 3].index = (float)i;
         }

        //バッファ作成

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices * _set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxBoardSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //頂点バッファ作成
        //頂点情報をビデオカード頂点バッファへロード
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(
                                 0,
                                 _size_vertices * _set_num,
                                 (void**)&pVertexBuffer,
                                 0
                               );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] 頂点バッファのロック取得に失敗 model="<<_model_name);

        memcpy(
          pVertexBuffer,
          paVertex,
          _size_vertices * _set_num
        ); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();

        GGAF_DELETEARR(paVertex);
    }


    //インデックスバッファ作成
    if (_pIndexBuffer == nullptr) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * _set_num];
        for (int i = 0; i < _set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * _set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(_pIndexBuffer),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] _pID3DDevice9->CreateIndexBuffer 失敗 model="<<(_model_name));

        void* pIndexBuffer;
        _pIndexBuffer->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * _set_num
        );
        _pIndexBuffer->Unlock();
        GGAF_DELETEARR(unit_paIdxBuffer);
        GGAF_DELETEARR(paIdxBufferSet);

        //描画時パラメーター
        GgafDxBoardSetModel::INDEXPARAM* paIndexParam = NEW GgafDxBoardSetModel::INDEXPARAM[_set_num];
        for (int i = 0; i < _set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        _paIndexParam = paIndexParam;
    }

    _num_materials = 1;
    D3DMATERIAL9* paMaterial = NEW D3DMATERIAL9[_num_materials];
    for( DWORD i = 0; i < _num_materials; i++){
        //paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        paMaterial[i].Diffuse.r = 1.0f;
        paMaterial[i].Diffuse.g = 1.0f;
        paMaterial[i].Diffuse.b = 1.0f;
        paMaterial[i].Diffuse.a = 1.0f;
        paMaterial[i].Ambient.r = 1.0f;
        paMaterial[i].Ambient.g = 1.0f;
        paMaterial[i].Ambient.b = 1.0f;
        paMaterial[i].Ambient.a = 1.0f;
    }
    _paMaterial_default = paMaterial;
}

void GgafDxBoardSetModel::onDeviceLost() {
    _TRACE3_("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxBoardSetModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxBoardSetModel::release() {
    _TRACE3_("GgafDxBoardSetModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_RELEASE(_pIndexBuffer);
    //テクスチャを解放
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    GGAF_DELETEARR(_paIndexParam);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR(_pa_texture_filenames);
    _TRACE3_("GgafDxBoardSetModel::release() " << _model_name << " end");
}

GgafDxBoardSetModel::~GgafDxBoardSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

