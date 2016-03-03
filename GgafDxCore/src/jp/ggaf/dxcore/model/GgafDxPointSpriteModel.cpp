#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"

#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
using namespace GgafCore;
using namespace GgafDxCore;

DWORD GgafDxPointSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE | D3DFVF_TEX1);

GgafDxPointSpriteModel::GgafDxPointSpriteModel(const char* prm_model_name) : GgafDxModel(prm_model_name) {
    _TRACE3_("GgafDxPointSpriteModel::GgafDxPointSpriteModel(" << _model_name << ")");
    _pVertexBuffer = nullptr;
    _paVtxBuffer_data = nullptr;
    _vertices_num = 0;
    _size_vertices = 0;
    _size_vertex_unit = 0;
    _square_size_px = 0.0f;
    _texture_size_px = 0.0f;
    _texture_split_rowcol = 1;
    _obj_model |= Obj_GgafDxPointSpriteModel;

    //デバイイスロスト対応と共通にするため、テクスチャ、頂点、マテリアルなどの初期化は
    //void GgafDxModelManager::restorePointSpriteModel(GgafDxPointSpriteModel*)
    //で行うようにした。要参照。
}

//描画
HRESULT GgafDxPointSpriteModel::draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num) {
    IDirect3DDevice9* const pDevice = GgafDxGod::_pID3DDevice9;
    _TRACE4_("GgafDxPointSpriteModel::draw("<<prm_pActor_target->getName()<<") this="<<getName());

    //対象Actor
    const GgafDxPointSpriteActor* const pTargetActor = (GgafDxPointSpriteActor*)prm_pActor_target;
    //対象PointSpriteActorのエフェクトラッパ
    GgafDxPointSpriteEffect* const pPointSpriteEffect = (GgafDxPointSpriteEffect*)prm_pActor_target->getEffect();
    //対象エフェクト
    ID3DXEffect* const pID3DXEffect = pPointSpriteEffect->_pID3DXEffect;

    //今回描画のUV
    HRESULT hr;
    if (GgafDxModelManager::_pModelLastDraw != this) {
        pDevice->SetStreamSource(0, _pVertexBuffer, 0, _size_vertex_unit);
        pDevice->SetFVF(GgafDxPointSpriteModel::FVF);
        pDevice->SetTexture(0, getDefaultTextureConnection()->peek()->_pIDirect3DBaseTexture9);

        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_power, _power_blink);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_power) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_h_tex_blink_threshold, _blink_threshold);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_h_tex_blink_threshold) に失敗しました。");
        hr = pID3DXEffect->SetFloat(pPointSpriteEffect->_hTexSize, _texture_size_px);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetFloat(_hTexSize) に失敗しました。");
        hr = pID3DXEffect->SetInt(pPointSpriteEffect->_hTextureSplitRowcol, _texture_split_rowcol);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetInt(_hTextureSplitRowcol) に失敗しました。");
        hr = pID3DXEffect->SetValue(pPointSpriteEffect->_h_colMaterialDiffuse, &(pTargetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() SetValue(g_colMaterialDiffuse) に失敗しました。");
    }
    GgafDxEffect* pEffect_active = GgafDxEffectManager::_pEffect_active;
    if (pEffect_active != pPointSpriteEffect || GgafDxFigureActor::_hash_technique_last_draw != prm_pActor_target->_hash_technique)  {
        if (pEffect_active) {
            _TRACE4_("GgafDxPointSpriteModel::draw() EndPass("<<pEffect_active->_pID3DXEffect<<"): /_pEffect_active="<<pEffect_active->_effect_name<<"("<<pEffect_active<<")");
            hr = pEffect_active->_pID3DXEffect->EndPass();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() EndPass() に失敗しました。");
            hr = pEffect_active->_pID3DXEffect->End();
            checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() End() に失敗しました。");
            if (pEffect_active->_obj_effect & Obj_GgafDxMassEffect) {
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
        _TRACE4_("GgafDxPointSpriteModel::draw() SetTechnique("<<pTargetActor->_technique<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
        hr = pID3DXEffect->SetTechnique(pTargetActor->_technique);
        checkDxException(hr, S_OK, "GgafDxPointSpriteActor::draw() SetTechnique("<<pTargetActor->_technique<<") に失敗しました。");

        _TRACE4_("GgafDxPointSpriteModel::draw() BeginPass("<<pID3DXEffect<<"): /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name<<"("<<pPointSpriteEffect<<")");
        UINT numPass;
        hr = pID3DXEffect->Begin( &numPass, D3DXFX_DONOTSAVESTATE );
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() Begin() に失敗しました。");
        hr = pID3DXEffect->BeginPass(0);
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::draw() BeginPass(0) に失敗しました。");

#ifdef MY_DEBUG
        if (pPointSpriteEffect->_begin) {
            throwGgafCriticalException("End していません "<<(GgafDxEffectManager::_pEffect_active==nullptr?"nullptr":GgafDxEffectManager::_pEffect_active->_effect_name)<<"");
        } else {
            pPointSpriteEffect->_begin = true;
        }
#endif

    } else {
        hr = pID3DXEffect->CommitChanges();
        checkDxException(hr, D3D_OK, "GgafDxPointSpriteModel::draw() CommitChanges() に失敗しました。");
    }
    _TRACE4_("DrawPrimitive: /actor="<<pTargetActor->getName()<<"/model="<<_model_name<<" effect="<<pPointSpriteEffect->_effect_name);
    pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, _vertices_num);

    //前回描画モデル保持
    GgafDxModelManager::_pModelLastDraw = this;
    GgafDxEffectManager::_pEffect_active = pPointSpriteEffect;
    GgafDxFigureActor::_hash_technique_last_draw = prm_pActor_target->_hash_technique;
    GgafGod::_num_drawing++;
    return D3D_OK;
}

void GgafDxPointSpriteModel::restore() {
    _TRACE3_("GgafDxPointSpriteModel::restore() " << _model_name << " start");

    _TRACE3_("GgafDxModelManager::restorePointSpriteModel(" << _model_name << ")");

    _papTextureConnection = nullptr;
    HRESULT hr;
//    std::string xfile_name = PROPERTY::DIR_SPRITE_MODEL[0] + std::string(_model_name) + ".psprx";
    std::string xfile_name = GgafDxModelManager::getPointSpriteFileName(_model_name);
//    //スプライト情報読込みテンプレートの登録(初回実行時のみ)
//    ID3DXFileEnumObject* pID3DXFileEnumObject;
//    ID3DXFileData* pID3DXFileData;
//    hr = GgafDxModelManager::_pID3DXFile_psprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
//    checkDxException(hr, S_OK, "[GgafDxModelManager::restorePointSpriteModel] '"<<xfile_name<<"' のCreateEnumObjectに失敗しました。ファイルの存在を確認して下さい。");
//
//    //TODO:GUIDなんとかする。今は完全無視。
//    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
//    SIZE_T nChildren;
//    pID3DXFileEnumObject->GetChildren(&nChildren);
//    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
//        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
//    }
//
////    "template PointSpriteDef { "
////    "  <E4EECE4C-E106-11DC-9B62-346D55D89593> "
////    "  FLOAT  SquareSize; "
////    "  STRING TextureFile; "
////    "  DWORD  TextureSplitRowCol; "
////    "  DWORD  VerticesNum; "
////    "  array  Vector    Vertices[VerticesNum]; "
////    "  array  ColorRGBA VertexColors[VerticesNum]; "
////    "  array  DWORD     InitUvPtnNo[VerticesNum]; "
////    "  array  FLOAT     InitScale[VerticesNum]; "
////    "} "
////
//    struct XFILE_FMT_HD {
//        float SquareSize;
//        char TextureFile[256];
//        int TextureSplitRowCol;
//        int VerticesNum;
//    };
//    SIZE_T xsize = 0;
//    char* pXData = nullptr;
//    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
//    if (pXData == nullptr) {
//        throwGgafCriticalException("[GgafDxModelManager::restorePointSpriteModel] "<<xfile_name<<" のフォーマットエラー。");
//    }
//    //    GUID* pGuid;
//    //    pID3DXFileData->GetType(pGuid);
//    XFILE_FMT_HD xDataHd;
//    //"  FLOAT  SquareSize;\n"
//    memcpy(&(xDataHd.SquareSize), pXData, sizeof(float));
//    pXData += sizeof(float);
//    //"  STRING TextureFile;\n"
//    strcpy(xDataHd.TextureFile, pXData);
//    pXData += (sizeof(char) * (strlen(xDataHd.TextureFile)+1));
//    //"  DWORD  TextureSplitRowCol;\n"
//    memcpy(&(xDataHd.TextureSplitRowCol), pXData, sizeof(int));
//    pXData += sizeof(int);
//    //"  DWORD  VerticesNum;\n"
//    memcpy(&(xDataHd.VerticesNum), pXData, sizeof(int));
//    pXData += sizeof(int);
//    //"  array  Vector    Vertices[VerticesNum];\n"
//    D3DVECTOR* paD3DVECTOR_Vertices = NEW D3DVECTOR[xDataHd.VerticesNum];
//    memcpy(paD3DVECTOR_Vertices, pXData, sizeof(D3DVECTOR)*xDataHd.VerticesNum);
//    pXData += sizeof(D3DVECTOR)*xDataHd.VerticesNum;
//    //"  array  ColorRGBA VertexColors[VerticesNum];\n"
//    D3DCOLORVALUE* paD3DVECTOR_VertexColors = NEW D3DCOLORVALUE[xDataHd.VerticesNum];
//    memcpy(paD3DVECTOR_VertexColors, pXData, sizeof(D3DCOLORVALUE)*xDataHd.VerticesNum);
//    pXData += sizeof(D3DCOLORVALUE)*xDataHd.VerticesNum;
//    //"  array  DWORD     InitUvPtnNo[VerticesNum];\n"
//    int* paInt_InitUvPtnNo = NEW int[xDataHd.VerticesNum];
//    memcpy(paInt_InitUvPtnNo, pXData, sizeof(int)*xDataHd.VerticesNum);
//    pXData += sizeof(int)*xDataHd.VerticesNum;
//    //"  array  FLOAT     InitScale[VerticesNum];\n"
//    float* paFLOAT_InitScale = NEW float[xDataHd.VerticesNum];
//    memcpy(paFLOAT_InitScale, pXData, sizeof(float)*xDataHd.VerticesNum);
//    pXData += sizeof(float)*xDataHd.VerticesNum;
    GgafDxModelManager::PointSpriteXFileFmt pointsprite_info;
    GgafDxModelManager::obtainPointSpriteInfo(&pointsprite_info, xfile_name);
    //退避
    float square_size_px = pointsprite_info.SquareSize;
    int texture_split_rowcol = pointsprite_info.TextureSplitRowCol;
    int vertices_num = pointsprite_info.VerticesNum;
    _TRACE3_("GgafDxModelManager::restorePointSpriteModel vertices_num="<<vertices_num);
    UINT size_vertices = sizeof(GgafDxPointSpriteModel::VERTEX)*vertices_num;
    UINT size_vertex_unit = sizeof(GgafDxPointSpriteModel::VERTEX);

    //テクスチャ取得しモデルに保持させる
    GgafDxTextureConnection** papTextureConnection = NEW GgafDxTextureConnection*[1];
    papTextureConnection[0] = (GgafDxTextureConnection*)(GgafDxModelManager::_pModelTextureManager->connect(pointsprite_info.TextureFile , this));
    GgafDxTexture* pTex = papTextureConnection[0]->peek();

    float tex_width  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //テクスチャの幅(px)
    float tex_height = (float)(pTex->_pD3DXIMAGE_INFO->Height); //テクスチャの高さ(px)幅と同じになる
    if ((int)(tex_width*100000) != (int)(tex_height*100000)) {
        throwGgafCriticalException("[GgafDxModelManager::restorePointSpriteModel] ポイントスプライト用テクスチャ["<<pTex->getName()<<"]("<<tex_width<<"x"<<tex_height<<")は、正方形である必要があります。");
    }
    FLOAT bounding_sphere_radius = 0;

    //頂点バッファ作成
    GgafDxPointSpriteModel::VERTEX* paVtxBuffer_data = NEW GgafDxPointSpriteModel::VERTEX[vertices_num];

    float dis;
    for (int i = 0; i < vertices_num; i++) {
        paVtxBuffer_data[i].x = pointsprite_info.paD3DVECTOR_Vertices[i].x;
        paVtxBuffer_data[i].y = pointsprite_info.paD3DVECTOR_Vertices[i].y;
        paVtxBuffer_data[i].z = pointsprite_info.paD3DVECTOR_Vertices[i].z;
        paVtxBuffer_data[i].psize = (square_size_px*texture_split_rowcol / tex_width) * pointsprite_info.paFLOAT_InitScale[i]; //PSIZEにはピクセルサイズではなく倍率を埋め込む。
                                                                                                //シェーダーで拡大縮小ピクセルを計算
        paVtxBuffer_data[i].color = D3DCOLOR_COLORVALUE(pointsprite_info.paD3DVECTOR_VertexColors[i].r,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].g,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].b,
                                                        pointsprite_info.paD3DVECTOR_VertexColors[i].a );
        paVtxBuffer_data[i].tu = (float)(pointsprite_info.paInt_InitUvPtnNo[i]);
        paVtxBuffer_data[i].tv = 0;

        dis = (FLOAT)(sqrt(paVtxBuffer_data[i].x * paVtxBuffer_data[i].x +
                           paVtxBuffer_data[i].y * paVtxBuffer_data[i].y +
                           paVtxBuffer_data[i].z * paVtxBuffer_data[i].z  )
                       + (((square_size_px/PX_UNIT) * 1.41421356 ) / 2.0)
                     );

         if (bounding_sphere_radius < dis) {
             bounding_sphere_radius = dis;
         }
    }

    D3DMATERIAL9*   paMaterial = nullptr;
    if (_pVertexBuffer == nullptr) {

        //頂点バッファ作成
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxPointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(_pVertexBuffer),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restorePointSpriteModel] _pID3DDevice9->CreateVertexBuffer 失敗 model="<<(_model_name));

        //バッファへ作成済み頂点データを流し込む
        void *pVertexBuffer;
        hr = _pVertexBuffer->Lock(0, size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restorePointSpriteModel] 頂点バッファのロック取得に失敗 model="<<_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_data, size_vertices); //pVertexBuffer ← paVertex
        _pVertexBuffer->Unlock();
    }

    paMaterial = NEW D3DMATERIAL9[1];
    paMaterial[0].Diffuse.r = 1.0f;
    paMaterial[0].Diffuse.g = 1.0f;
    paMaterial[0].Diffuse.b = 1.0f;
    paMaterial[0].Diffuse.a = 1.0f;

    //モデルに保持させる
    _paMaterial_default     = paMaterial;
    _papTextureConnection   = papTextureConnection;
    _num_materials          = 1;
    _square_size_px         = square_size_px;
    _texture_size_px        = tex_width;
    _texture_split_rowcol   = texture_split_rowcol;
    _vertices_num           = vertices_num;
    _size_vertices          = size_vertices;
    _size_vertex_unit       = size_vertex_unit;
    _paVtxBuffer_data        = paVtxBuffer_data;
    _bounding_sphere_radius = bounding_sphere_radius;
//    pID3DXFileData->Unlock();
//    GGAF_DELETEARR(paD3DVECTOR_Vertices);
//    GGAF_DELETEARR(paD3DVECTOR_VertexColors);
//    GGAF_DELETEARR(paInt_InitUvPtnNo);
//    GGAF_DELETEARR(paFLOAT_InitScale);
//
//    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
//    GGAF_RELEASE(pID3DXFileEnumObject);
    _TRACE3_("GgafDxPointSpriteModel::restore() " << _model_name << " end");
}

void GgafDxPointSpriteModel::onDeviceLost() {
    _TRACE3_("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " start");
    release();
    _TRACE3_("GgafDxPointSpriteModel::onDeviceLost() " << _model_name << " end");
}

void GgafDxPointSpriteModel::release() {
    _TRACE3_("GgafDxPointSpriteModel::release() " << _model_name << " start");
    GGAF_RELEASE(_pVertexBuffer);
    GGAF_DELETEARR(_paVtxBuffer_data);
    if (_papTextureConnection) {
        for (int i = 0; i < (int)_num_materials; i++) {
            if (_papTextureConnection[i]) {
                _papTextureConnection[i]->close();
            }
        }
    }
    GGAF_DELETEARR(_papTextureConnection);
    //TODO:親クラスメンバをDELETEするのはややきたないか
    GGAF_DELETEARR(_paMaterial_default);
    GGAF_DELETEARR_NULLABLE(_pa_texture_filenames);
    _TRACE3_("GgafDxPointSpriteModel::release() " << _model_name << " end");
}

GgafDxPointSpriteModel::~GgafDxPointSpriteModel() {
    //release();
    //はGgafDxModelConnection::processReleaseResource(GgafDxModel* prm_pResource) で呼び出される
}

