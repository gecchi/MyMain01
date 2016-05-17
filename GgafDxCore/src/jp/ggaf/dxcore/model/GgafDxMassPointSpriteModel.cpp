#include "jp/ggaf/dxcore/model/GgafDxMassPointSpriteModel.h"

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassPointSpriteEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassPointSpriteActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxMassPointSpriteModel::GgafDxMassPointSpriteModel(const char* prm_model_name) : GgafDxMassModel(prm_model_name) {
    _TRACE3_("_model_name="<<_model_name);
    _obj_model |= Obj_GgafDxMassPointSpriteModel;

    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;

    _paVtxBuffer_data_model = nullptr;
//    _paIndexBuffer_data = nullptr;

    registerCallback_VertexModelInfo(GgafDxMassPointSpriteModel::createVertexModel); //頂点レイアウト情報作成コールバック関数
    _TRACE_("GgafDxMassPointSpriteModel::GgafDxMassPointSpriteModel(" << _model_name << ") End");
}

void GgafDxMassPointSpriteModel::createVertexModel(void* prm, GgafDxMassModel::VertexModelInfo* out_info) {
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
    //float psize;      // ポイントサイズ
    out_info->paElement[1].Stream = 0;
    out_info->paElement[1].Offset = st0_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT1;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_PSIZE;
    out_info->paElement[1].UsageIndex = 0;
    st0_offset_next += sizeof(float)*1;
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

void GgafDxMassPointSpriteModel::restore() {
    _TRACE3_("_model_name=" << _model_name << " start");
    HRESULT hr;
    if (!_paVtxBuffer_data_model) {






        //静的な情報設定
        std::vector<std::string> names = UTIL::split(std::string(_model_name), "/");
        std::string xfile_name = ""; //読み込むXファイル名
        if (names.size() == 1) {
            _TRACE_(FUNC_NAME<<" "<<_model_name<<" の最大同時描画オブジェクト数は、デフォルトの"<<GGAFDXMASS_MAX_INSTACE_NUM<<" が設定されました。");
            _set_num = GGAFDXMASS_MAX_INSTACE_NUM;
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[0]);
        } else if (names.size() == 2) {
            _set_num = STOI(names[0]);
            xfile_name = GgafDxModelManager::getPointSpriteFileName(names[1]);
        } else {
            throwGgafCriticalException("_model_name には \"xxxxxx\" or \"8/xxxxx\" 形式を指定してください。 \n"<<
                    "実際は、_model_name="<<_model_name<<" でした。");
        }
        if (_set_num < 1 || _set_num > GGAFDXMASS_MAX_INSTACE_NUM) {
            throwGgafCriticalException(_model_name<<"の最大同時描画オブジェクト数が不正。範囲は 1～"<<GGAFDXMASS_MAX_INSTACE_NUM<<"セットです。_set_num="<<_set_num);
        }
        if (xfile_name == "") {
            throwGgafCriticalException("ポイントスプライト定義ファイル(*.psprx)が見つかりません。model_name="<<(_model_name));
        }
        GgafDxModelManager::PointSpriteXFileFmt xdata;
        GgafDxModelManager::obtainPointSpriteInfo(&xdata, xfile_name);


        //マテリアル定義が１つも無いので、描画のために無理やり１つマテリアルを作成。
        _num_materials = 1;
        _paMaterial_default  = NEW D3DMATERIAL9[1];
        _pa_texture_filenames = NEW std::string[1];
        _paMaterial_default[0].Diffuse.r = 1.0f;
        _paMaterial_default[0].Diffuse.g = 1.0f;
        _paMaterial_default[0].Diffuse.b = 1.0f;
        _paMaterial_default[0].Diffuse.a = 1.0f;
        _paMaterial_default[0].Ambient.r = 1.0f;
        _paMaterial_default[0].Ambient.g = 1.0f;
        _paMaterial_default[0].Ambient.b = 1.0f;
        _paMaterial_default[0].Ambient.a = 1.0f;
        _paMaterial_default[0].Specular.r = 1.0f;
        _paMaterial_default[0].Specular.g = 1.0f;
        _paMaterial_default[0].Specular.b = 1.0f;
        _paMaterial_default[0].Specular.a = 1.0f;
        _paMaterial_default[0].Power = 0.0f;
        _paMaterial_default[0].Emissive.r = 1.0f;
        _paMaterial_default[0].Emissive.g = 1.0f;
        _paMaterial_default[0].Emissive.b = 1.0f;
        _paMaterial_default[0].Emissive.a = 1.0f;
        _pa_texture_filenames[0] = std::string(xdata.TextureFile);

        //デバイスにテクスチャ作成 (下にも同じ処理があるが、下はデバイスロスト時実行)
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



        //退避
        _square_size_px = xdata.SquareSize;
        _texture_split_rowcol = xdata.TextureSplitRowCol;

        _nVertices = xdata.VerticesNum;
        if (_nVertices > 65535) {
            throwGgafCriticalException("頂点が 65535を超えたかもしれません。\n対象Model："<<getName()<<"  _nVertices:"<<_nVertices);
        }
        _nFaces = 0; //_nFacesは使用しない
        _paVtxBuffer_data_model = NEW VERTEX_model[_nVertices];
        _size_vertex_unit_model = sizeof(VERTEX_model);
        _size_vertices_model = sizeof(VERTEX_model) * _nVertices;

        FLOAT model_bounding_sphere_radius;
        float dis;
        for (int i = 0; i < _nVertices; i++) {
            _paVtxBuffer_data_model[i].x = xdata.paD3DVECTOR_Vertices[i].x;
            _paVtxBuffer_data_model[i].y = xdata.paD3DVECTOR_Vertices[i].y;
            _paVtxBuffer_data_model[i].z = xdata.paD3DVECTOR_Vertices[i].z;
            _paVtxBuffer_data_model[i].psize = (_square_size_px*_texture_split_rowcol / _texture_size_px) * xdata.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
                                                                                                    //シェーダーで拡大縮小ピクセルを計算
            _paVtxBuffer_data_model[i].color = D3DCOLOR_COLORVALUE(xdata.paD3DVECTOR_VertexColors[i].r,
                                                            xdata.paD3DVECTOR_VertexColors[i].g,
                                                            xdata.paD3DVECTOR_VertexColors[i].b,
                                                            xdata.paD3DVECTOR_VertexColors[i].a );
            _paVtxBuffer_data_model[i].tu = (float)(xdata.paInt_InitUvPtnNo[i]);
            _paVtxBuffer_data_model[i].tv = 0;

            model_bounding_sphere_radius = (FLOAT)(sqrt(_paVtxBuffer_data_model[i].x * _paVtxBuffer_data_model[i].x +
                                                        _paVtxBuffer_data_model[i].y * _paVtxBuffer_data_model[i].y +
                                                        _paVtxBuffer_data_model[i].z * _paVtxBuffer_data_model[i].z  )
                                                   + (((_square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                                                 );

            if (_bounding_sphere_radius < model_bounding_sphere_radius) {
                _bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }


    }

    //デバイスに頂点バッファ作成(モデル)
    if (_pVertexBuffer_model == nullptr) {
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

    //インデックスバッファは使わない
    _pIndexBuffer = nullptr;

    _TRACE3_("_model_name=" << _model_name << " end");
}

HRESULT GgafDxMassPointSpriteModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num, void* prm_pPrm) {
    _TRACE4_("GgafDxMassPointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());
    if (_pVertexBuffer_instacedata == nullptr) {
        createVertexElements(); //デバイスロスト復帰時に呼び出される
    }
#ifdef MY_DEBUG
    if (prm_draw_set_num > _set_num) {
        throwGgafCriticalException(FUNC_NAME<<" "<<_model_name<<" の描画セット数オーバー。_set_num="<<_set_num<<" に対し、prm_draw_set_num="<<prm_draw_set_num<<"でした。");
    }
#endif
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;

    pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE); //ポイントスプライトON！

    //対象アクター
    const GgafDxMassPointSpriteActor* pTargetActor = (GgafDxMassPointSpriteActor*)prm_pActor_target;
    //対象MassPointSpriteActorのエフェクトラッパ
    GgafDxMassPointSpriteEffect* pMassPointSpriteEffect = (GgafDxMassPointSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pMassPointSpriteEffect->_pID3DXEffect;

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
    GgafDxModel* pModelLastDraw = GgafDxModelManager::_pModelLastDraw;
    if (pModelLastDraw != this) {
        hr = pDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1 );
        checkDxException(hr, D3D_OK, "SetStreamSourceFreq 1 に失敗しました。");
        //頂点バッファとインデックスバッファを設定
        hr = pDevice->SetVertexDeclaration(_pVertexDeclaration); //頂点フォーマット
        checkDxException(hr, D3D_OK, "SetVertexDeclaration に失敗しました。");
        hr = pDevice->SetStreamSource(0, _pVertexBuffer_model      , 0, _size_vertex_unit_model);
        checkDxException(hr, D3D_OK, "SetStreamSource 0 に失敗しました。");
        hr = pDevice->SetStreamSource(1, _pVertexBuffer_instacedata, 0, _size_vertex_unit_instacedata);
        checkDxException(hr, D3D_OK, "SetStreamSource 1 に失敗しました。");
        hr = pDevice->SetIndices(_pIndexBuffer);
        checkDxException(hr, D3D_OK, "SetIndices に失敗しました。");

        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pMassPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pMassPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "SetInt(_hTextureSplitRowcol) に失敗しました。");


        if (_papTextureConnection[0]) {
            hr = pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);
        } else {
            _TRACE_("GgafDxMassPointSpriteModel::draw("<<prm_pActor_target->getName()<<") テクスチャがありません。"<<(PROPERTY::WHITE_TEXTURE)<<"が設定されるべきです。おかしいです");
            //無ければテクスチャ無し
            hr = pDevice->SetTexture(0, nullptr);
        }
        checkDxException(hr, D3D_OK, "SetTexture に失敗しました");
    }
    hr = pDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | prm_draw_set_num);
    checkDxException(hr, D3D_OK, "SetStreamSourceFreq 0 に失敗しました。prm_draw_set_num="<<prm_draw_set_num);

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
        _TRACE4_("SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassPointSpriteEffect->_effect_name<<"("<<pMassPointSpriteEffect<<")");
        //UINT numPass;
        hr = pID3DXEffect->Begin(&_num_pass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pMassPointSpriteEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pMassPointSpriteEffect->_begin = true;
        }
#endif
    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawIndexedPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pMassPointSpriteEffect->_effect_name);

    hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices);
    checkDxException(hr, D3D_OK, " pass=1 に失敗しました。");
    if (_num_pass >= 2) { //２パス目以降が存在
        hr = pID3DXEffect->EndPass();
        checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        for (UINT i = 1; i < _num_pass; i++) {
            hr = pID3DXEffect->BeginPass(i);
            checkDxException(hr, D3D_OK, i+1<<"パス目 BeginPass("<<i<<") に失敗しました。");
            hr = pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _nVertices);
            checkDxException(hr, D3D_OK, " pass="<<(i+1)<<" に失敗しました。");
            hr = pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "EndPass() に失敗しました。");
        }
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "１パス目 BeginPass(0) に失敗しました。");
    }
#ifdef MY_DEBUG
        GgafGod::_num_drawing++;
#endif

    pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE); //ポイントスプライトOFF

    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pMassPointSpriteEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    return D3D_OK;
}

GgafDxMassPointSpriteModel::~GgafDxMassPointSpriteModel() {
    GGAF_DELETEARR(_paVtxBuffer_data_model);
}

