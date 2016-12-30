#include "jp/ggaf/dxcore/model/GgafDxPointSpriteSetModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteSetActor.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteSetEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxMassModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteSetModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1  );
//LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer = nullptr;

GgafDxPointSpriteSetModel::GgafDxPointSpriteSetModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _set_num = 0;
    _pVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _size_vertex_unit= 0;
    _nVertices = 0;
    _obj_model |= Obj_GgafDxPointSpriteSetModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどのメンバー初期化は
    //void GgafDxModelManager::restorePointSpriteSetModel(GgafDxPointSpriteSetModel*)
    //で行うようにした。要参照。
    _TRACE_("GgafDxPointSpriteSetModel::GgafDxPointSpriteSetModel(" << _model_name << ") End");
}

//描画
HRESULT GgafDxPointSpriteSetModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxPointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        _TRACE_(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //対象アクター
    const GgafDxPointSpriteSetActor* pTargetActor = (GgafDxPointSpriteSetActor*)prm_pActor_target;
    //対象PointSpriteSetActorのエフェクトラッパ
    GgafDxPointSpriteSetEffect* pPointSpriteSetEffect = (GgafDxPointSpriteSetEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pPointSpriteSetEffect->_pID3DXEffect;

    HRESULT hr;
    //モデルが同じでかつ、セット数も同じならば頂点バッファ、インデックスバッファの設定はスキップできる
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        if (pModelLastDraw && (pModelLastDraw->_obj_model & Obj_GgafDxMassModel)) {
            ((GgafDxMassModel*)pModelLastDraw)->resetStreamSourceFreq();
        }
        //頂点バッファとインデックスバッファを設定
        pDevice->SetStreamSource(0, _pVertexBuffer,  0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxPointSpriteSetModel::FVF);
        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxPointSpriteSetModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            hr = pDevice->SetTexture(0, nullptr);
        }
        pDevice->SetIndices(nullptr);

        hr = pID3DXEffect->SetFloat(pPointSpriteSetEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteSetEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");
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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name<<"("<<pPointSpriteSetEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteSetEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteSetEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteSetEffect->_effect_name);
    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices*prm_draw_set_num);
    checkDxException(hr, D3D_OK, " pass=1 に失敗しました。");
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pPointSpriteSetEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

void GgafDxPointSpriteSetModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    if (!_paVtxBuffer_data) {

        //静的な情報設定
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xfile_name = ""; //読み込むXファイル名
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" の最大同時描画オブジェクト数は、デフォルトの15が設定されました。");
            _set_num = 15;
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[0]);
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[1]);
        } else {
            throwGgafCriticalException("_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                    "実際は、_model_name="<<_model_name<<" でした。");
        }
//        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTANCE_NUM) {
//            throwGgafCriticalException(_model_name<<"の最大同時描画オブジェクト数が不正。範囲は 1～"<<GGAFDXMASS_MAX_INSTANCE_NUM<<"セットです。_set_num="<<_set_num);
//        }
//        if (xfile_name == "") {
//            throwGgafCriticalException("ポイントスプライト定義ファイル(*.psprx)が見つかりません。model_name="<<(_model_name));
//        }
        GgafDxModelManager::PointSpriteXFileFmt xdata;
        GgafDxModelManager::obtainPointSpriteInfo(&xdata, xfile_name);

        //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
        setMaterial();
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);

        //デバイスにテクスチャ作成 (下にも同じ処理があるが、下はデバイスロスト時実行)
        //頂点バッファのpsizeの算出に、テクスチャの長さが必要なため、ここで一旦求めている
        if (!_papTextureConnection) {
            _papTextureConnection = NEW GgafDxTextureConnection*[1];
            _papTextureConnection[0] =
                (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
            GgafDxTexture* pTex = _papTextureConnection[0]->peek();
            float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
            float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
            if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
                throwGgafCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
            }
            _texture_size_px = tex_width;
        }
        _square_size_px = xdata.SquareSize;
        _texture_split_rowcol = xdata.TextureSplitRowCol;

        _nVertices = xdata.VerticesNum;
        if (_nVertices*_set_num > 65535) {
            throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  _nVertices*_set_num:"<<_nVertices*_set_num);
        }
//        _nFaces = 0; //_nFacesは使用しない
        _paVtxBuffer_data = NEW GgafDxPointSpriteSetModel::VERTEX[_nVertices*_set_num];
        _size_vertex_unit = sizeof(GgafDxPointSpriteSetModel::VERTEX);
        _size_vertices = sizeof(GgafDxPointSpriteSetModel::VERTEX) * _nVertices*_set_num;

        FLOAT model_bounding_sphere_radius;


        for (int i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data[i].x = xdata.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data[i].y = xdata.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data[i].z = xdata.paD3DVECTOR_Vertices[i].z;

            _paVtxBuffer_data[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
            //シェーダーで拡大縮小ピクセルを計算
            _paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(xdata.paD3DVECTOR_VertexColors[i].r,
                                                                   xdata.paD3DVECTOR_VertexColors[i].g,
                                                                   xdata.paD3DVECTOR_VertexColors[i].b,
                                                                   xdata.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data[i].ini_ptn_no = (float)(xdata.paInt_InitUvPtnNo[i]); //頂点スプライトのUVパターン番号
            _paVtxBuffer_data[i].index = 0; //頂点番号（むりやり埋め込み）

            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data[i].x * _paVtxBuffer_data[i].x +
                                                        _paVtxBuffer_data[i].y * _paVtxBuffer_data[i].y +
                                                        _paVtxBuffer_data[i].z * _paVtxBuffer_data[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );

            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        for (int n = 1; n < _set_num; n++) {
            int os = n*_nVertices;
            for (int i = 0; i < _nVertices; i++) {
                _paVtxBuffer_data[os+i].x = _paVtxBuffer_data[i].x;
                _paVtxBuffer_data[os+i].y = _paVtxBuffer_data[i].y;
                _paVtxBuffer_data[os+i].z = _paVtxBuffer_data[i].z;
                _paVtxBuffer_data[os+i].psize = _paVtxBuffer_data[i].psize;
                _paVtxBuffer_data[os+i].color = _paVtxBuffer_data[i].color;
                _paVtxBuffer_data[os+i].ini_ptn_no = _paVtxBuffer_data[i].ini_ptn_no;
                _paVtxBuffer_data[os+i].index = n; //頂点番号（むりやり埋め込み）
            }
        }

    }

    //デバイスに頂点バッファ作成(モデル)
    if (_pVertexBuffer == nullptr) {

        //頂点バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                _size_vertices,
                D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
                GgafDxPointSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "_pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));
        //バッファへ作成済み頂点データを流し込む
        void* pDeviceMemory = 0;
        hr = _pVertexBuffer->Lock(0, _size_vertices, (void**)&pDeviceMemory, 0);
        checkDxException(hr, D3D_OK, "頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pDeviceMemory, _paVtxBuffer_data, _size_vertices);
        hr = _pVertexBuffer->Unlock();
        checkDxException(hr, D3D_OK, "頂点バッファのアンロック取得に失敗 model="<<_model_name);
    }

    //デバイスにテクスチャ作成
    if (!_papTextureConnection) {
        _num_materials = 1;
        _papTextureConnection = NEW GgafDxTextureConnection*[1];
        _papTextureConnection[0] =
            (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(_pa_texture_filenames[0].c_str(), this));
        GgafDxTexture* pTex = _papTextureConnection[0]->peek();
        float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
        float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
        if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
            throwGgafCriticalException("ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
        }
        _texture_size_px = tex_width;
    }

//    //インデックスバッファは使わない
//    _pIndexBuffer = nullptr;

    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteSetModel::onDeviceLost() {
    _TRACE3_("_model_name=" << _model_name << " start");
    release();
    _TRACE3_("_model_name=" << _model_name << " end");
}

void GgafDxPointSpriteSetModel::release() {
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
    GGAF_DELETEARR(_paVtxBuffer_data);

    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("_model_name=" << _model_name << " end");

}
GgafDxPointSpriteSetModel::~GgafDxPointSpriteSetModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

