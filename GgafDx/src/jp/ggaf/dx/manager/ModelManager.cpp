
// 本プログラムは Paul Coppens さんの作成された、Xファイルを読み込むサンプル
// を元に、独自に改良修正（やデバッグ）したクラスを使用しています。
// ありがとう Paulさん。
//
// 【対象】
// Frm 名前空間のクラス
//
// 【Loading and displaying .X files without DirectX 】
// http://www.gamedev.net/reference/programming/features/xfilepc/
//
//                                         2009/03/06 Masatoshi Tsuge

#include "jp/ggaf/dx/manager/ModelManager.h"

#include <d3dx9xof.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/model/D3DXMeshModel.h"
#include "jp/ggaf/dx/model/D3DXAniMeshModel.h"
#include "jp/ggaf/dx/model/SpriteModel.h"
#include "jp/ggaf/dx/model/SpriteSetModel.h"
#include "jp/ggaf/dx/model/MassSpriteModel.h"
#include "jp/ggaf/dx/model/MeshModel.h"
#include "jp/ggaf/dx/model/MeshSetModel.h"
#include "jp/ggaf/dx/model/MassMeshModel.h"
#include "jp/ggaf/dx/model/MorphMeshModel.h"
#include "jp/ggaf/dx/model/MassMorphMeshModel.h"
#include "jp/ggaf/dx/model/BoardModel.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/dx/model/MassBoardModel.h"
#include "jp/ggaf/dx/model/PointSpriteModel.h"
#include "jp/ggaf/dx/model/MassPointSpriteModel.h"
#include "jp/ggaf/dx/model/PointSpriteSetModel.h"
#include "jp/ggaf/dx/model/FramedBoardModel.h"
#include "jp/ggaf/dx/model/FramedSpriteModel.h"
#include "jp/ggaf/dx/model/RegularPolygonSpriteModel.h"
#include "jp/ggaf/dx/model/RegularPolygonBoardModel.h"
#include "jp/ggaf/dx/model/BoneAniMeshModel.h"
#include "jp/ggaf/dx/model/SkinAniMeshModel.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshModel.h"
#include "jp/ggaf/dx/model/ex/CubeMapMeshSetModel.h"
#include "jp/ggaf/dx/model/ex/CubeMapMorphMeshModel.h"
#include "jp/ggaf/dx/model/ex/WorldBoundModel.h"
#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/manager/ModelConnection.h"

using namespace GgafDx;

Model* ModelManager::_pModelLastDraw = nullptr;
std::map<char, std::string> ModelManager::type_ext;

ModelManager::ModelManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Model> (prm_manager_name) {

    static volatile bool is_init = ModelManager::initStatic(); //静的メンバ初期化
    //テクスチャマネジャー
    _pModelTextureManager = NEW TextureManager("TextureManager");
    HRESULT hr;

    D3DXFileCreate( &_pID3DXFile_modelx );

    static const char* modelx_template =
        "xof 0303txt 0032 \n" \
        "template MetaModelInfo { " \
        "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
        "   DWORD XFileNum; " \
        "   array STRING XFileNames[XFileNum]; " \
        "   DWORD DrawSetNum; " \
        "   array FLOAT BaseTransformMatrix[16]; " \
        "}\n";
    hr = _pID3DXFile_modelx->RegisterTemplates(modelx_template, (DWORD)(strlen(modelx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplatesに失敗しました。modelx_template を確認して下さい。");
    }
#endif

//
//    D3DXFileCreate( &_pID3DXFile_meshx );
//
//    static const char* meshx_template =
//        "xof 0303txt 0032 \n" \
//        "template MeshModelDef { " \
//        "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
//        "   DWORD XFileNum; " \
//        "   array STRING XFileNames[XFileNum]; " \
//        "   DWORD DrawSetNum; " \
//        "   array FLOAT BaseTransformMatrix[16]; " \
//        "}\n";
//    hr = _pID3DXFile_meshx->RegisterTemplates(meshx_template, (DWORD)(strlen(meshx_template)));
//#ifdef MY_DEBUG
//    if(hr != S_OK) {
//        throwCriticalException("RegisterTemplatesに失敗しました。meshx_template を確認して下さい。");
//    }
//#endif

    //板ポリゴンモデル定義ファイル(拡張子sprx)のフォーマット定義
    D3DXFileCreate( &_pID3DXFile_sprx );
    static const char* sprx_template =
        "xof 0303txt 0032 \n" \
        "template SpriteModelDef {" \
        "   <E4EECE4C-E106-11DC-9B62-346D55D89599>" \
        "   FLOAT  Width;" \
        "   FLOAT  Height;" \
        "   STRING TextureFile;" \
        "   DWORD  TextureSplitRows;" \
        "   DWORD  TextureSplitCols;" \
        "}\n";
    hr = _pID3DXFile_sprx->RegisterTemplates(sprx_template, (DWORD)(strlen(sprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplatesに失敗しました。sprx_template を確認して下さい。");
    }
#endif

    //枠ありスプライト定義ファイル(拡張子rsprx)のフォーマット定義
    D3DXFileCreate( &_pID3DXFile_fsprx );
    static const char* fsprx_template =
        "xof 0303txt 0032 \n" \
        "template FramedSpriteModelDef {" \
        "   <E2A64EB2-5F1B-42B4-B05A-19DF9EB9CD72>" \
        "   FLOAT  Width;" \
        "   FLOAT  Height;" \
        "   STRING TextureFile;" \
        "   DWORD  TextureSplitRows;" \
        "   DWORD  TextureSplitCols;" \
        "\n" \
        "   FLOAT  FrameWidth;" \
        "   FLOAT  FrameHeight;" \
        "   STRING FrameTextureFile;" \
        "   DWORD  FrameTextureSplitRows;" \
        "   DWORD  FrameTextureSplitCols;" \
        "}\n";
    hr = _pID3DXFile_fsprx->RegisterTemplates(fsprx_template, (DWORD)(strlen(fsprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplatesに失敗しました。fsprx_template を確認して下さい。");
    }
#endif

    //多角形スプライト定義ファイル(拡張子rsprx)のフォーマット定義
    D3DXFileCreate( &_pID3DXFile_rsprx );
    static const char* rsprx_template =
        "xof 0303txt 0032 \n" \
        "template RegularPolygonModelDef {" \
        "   <964A6FAF-9C35-460C-920F-4A87D713BCA6>" \
        "   FLOAT  Width;" \
        "   FLOAT  Height;" \
        "   STRING TextureFile;" \
        "   DWORD  TextureSplitRows;" \
        "   DWORD  TextureSplitCols;" \
        "   DWORD  FanNum;" \
        "   DWORD  IsCW;" \
        "}\n";
    hr = _pID3DXFile_rsprx->RegisterTemplates(rsprx_template, (DWORD)(strlen(rsprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplatesに失敗しました。rsprx_template を確認して下さい。");
    }
#endif

    //ポイントスプライト定義ファイル(拡張子psprx)のフォーマット定義
    D3DXFileCreate( &_pID3DXFile_psprx );

    static const char* psprx_template =
            "xof 0303txt 0032\n" \
            "template Vector {\n" \
            "  <3d82ab5e-62da-11cf-ab39-0020af71e433>\n" \
            "  FLOAT x;\n" \
            "  FLOAT y;\n" \
            "  FLOAT z;\n" \
            "}\n" \
            "template ColorRGBA {\n" \
            "  <35ff44e0-6c7c-11cf-8f52-0040333594a3>\n" \
            "  FLOAT red;\n" \
            "  FLOAT green;\n" \
            "  FLOAT blue;\n" \
            "  FLOAT alpha;\n" \
            "}\n" \
            "template PointSpriteModelDef {\n" \
            "  <2A355D47-C0C6-4979-92D0-3FCE3090C49A>\n" \
            "  FLOAT  SquareSize;\n" \
            "  STRING TextureFile;\n" \
            "  DWORD  TextureSplitRowCol;\n" \
            "  DWORD  VerticesNum;\n" \
            "  array  Vector    Vertices[VerticesNum];\n" \
            "  array  ColorRGBA VertexColors[VerticesNum];\n" \
            "  array  DWORD     InitUvPtnNo[VerticesNum];\n" \
            "  array  FLOAT     InitScale[VerticesNum];\n" \
            "}\n" \
            "\n";
    hr = _pID3DXFile_psprx->RegisterTemplates(psprx_template, (DWORD)(strlen(psprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplatesに失敗しました。psprx_template を確認して下さい。");
    }
#endif
}

bool ModelManager::initStatic() {
    ModelManager::type_ext[TYPE_UNKNOWN_MODEL              ] = "x";
    ModelManager::type_ext[TYPE_D3DXMESH_MODEL             ] = "x";
    ModelManager::type_ext[TYPE_DYNAD3DXMESH_MODEL         ] = "x";
    ModelManager::type_ext[TYPE_D3DXANIMESH_MODEL          ] = "x";
    ModelManager::type_ext[TYPE_MESH_MODEL                 ] = "x";
    ModelManager::type_ext[TYPE_MESHSET_MODEL              ] = "x";
    ModelManager::type_ext[TYPE_MASSMESH_MODEL             ] = "x";
    ModelManager::type_ext[TYPE_CUBEMAPMESH_MODEL          ] = "x";
    ModelManager::type_ext[TYPE_CUBEMAPMESHSET_MODEL       ] = "x";
    ModelManager::type_ext[TYPE_MORPHMESH_MODEL            ] = "x";
    ModelManager::type_ext[TYPE_MASSMORPHMESH_MODEL        ] = "x";
    ModelManager::type_ext[TYPE_CUBEMAPMORPHMESH_MODEL     ] = "x";
    ModelManager::type_ext[TYPE_WORLDBOUND_MODEL           ] = "x";
    ModelManager::type_ext[TYPE_SPRITE_MODEL               ] = "sprx";
    ModelManager::type_ext[TYPE_SPRITESET_MODEL            ] = "sprx";
    ModelManager::type_ext[TYPE_MASSSPRITE_MODEL           ] = "sprx";
    ModelManager::type_ext[TYPE_BOARD_MODEL                ] = "sprx";
    ModelManager::type_ext[TYPE_BOARDSET_MODEL             ] = "sprx";
    ModelManager::type_ext[TYPE_MASSBOARD_MODEL            ] = "sprx";
    ModelManager::type_ext[TYPE_POINTSPRITE_MODEL          ] = "psprx";
    ModelManager::type_ext[TYPE_MASSPOINTSPRITE_MODEL      ] = "psprx";
    ModelManager::type_ext[TYPE_POINTSPRITESET_MODEL       ] = "psprx";
    ModelManager::type_ext[TYPE_FRAMEDBOARD_MODEL          ] = "fsprx";
    ModelManager::type_ext[TYPE_FRAMEDSPRITE_MODEL         ] = "fsprx";
    ModelManager::type_ext[TYPE_REGULARPOLYGONSPRITE_MODEL ] = "rsprx";
    ModelManager::type_ext[TYPE_REGULARPOLYGONBOARD_MODEL  ] = "rsprx";
    ModelManager::type_ext[TYPE_BONEANIMESH_MODEL          ] = "x";
    ModelManager::type_ext[TYPE_SKINANIMESH_MODEL          ] = "x";
    return true;
}

Model* ModelManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //最初のスラッシュで分割
    if (names.size() != 2) {
        throwCriticalException("引数は、主に次の形式で与えてください。『モデルタイプ1文字  + \",\" + モデル定義名(拡張子 .x を除いたもの)』\n"
                "実際の引数は、prm_idstr="<<prm_idstr);
    }
    char model_type = (names[0])[0];
    const char* model_id = names[1].c_str();
    Model* pResourceModel;
    switch (model_type) {
        case TYPE_D3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_type, model_id, D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_DYNAD3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_type, model_id, D3DXMESH_DYNAMIC);
            break;
        case TYPE_D3DXANIMESH_MODEL:
            pResourceModel = createModel<D3DXAniMeshModel>(model_type, model_id);
            break;
        case TYPE_MESH_MODEL:
            pResourceModel = createModel<MeshModel>(model_type, model_id);
            break;
        case TYPE_MESHSET_MODEL:
            pResourceModel = createModel<MeshSetModel>(model_type, model_id);
            break;
        case TYPE_MASSMESH_MODEL:
            pResourceModel = createModel<MassMeshModel>(model_type, model_id);
            break;
        case TYPE_CUBEMAPMESH_MODEL:
            pResourceModel = createModel<CubeMapMeshModel>(model_type, model_id);
            break;
        case TYPE_CUBEMAPMESHSET_MODEL:
            pResourceModel = createModel<CubeMapMeshSetModel>(model_type, model_id);
            break;
        case TYPE_MORPHMESH_MODEL:
            pResourceModel = createModel<MorphMeshModel>(model_type, model_id);
            break;
        case TYPE_MASSMORPHMESH_MODEL:
            pResourceModel = createModel<MassMorphMeshModel>(model_type, model_id);
            break;
        case TYPE_CUBEMAPMORPHMESH_MODEL:
            pResourceModel = createModel<CubeMapMorphMeshModel>(model_type, model_id);
            break;
        case TYPE_WORLDBOUND_MODEL:
            pResourceModel = createModel<WorldBoundModel>(model_type, model_id);
            break;
        case TYPE_SPRITE_MODEL:
            pResourceModel = createModel<SpriteModel>(model_type, model_id);
            break;
        case TYPE_SPRITESET_MODEL:
            pResourceModel = createModel<SpriteSetModel>(model_type, model_id);
            break;
        case TYPE_MASSSPRITE_MODEL:
            pResourceModel = createModel<MassSpriteModel>(model_type, model_id);
            break;
        case TYPE_BOARD_MODEL:
            pResourceModel = createModel<BoardModel>(model_type, model_id);
            break;
        case TYPE_BOARDSET_MODEL:
            pResourceModel = createModel<BoardSetModel>(model_type, model_id);
            break;
        case TYPE_MASSBOARD_MODEL:
            pResourceModel = createModel<MassBoardModel>(model_type, model_id);
            break;
        case TYPE_POINTSPRITE_MODEL:
            pResourceModel = createModel<PointSpriteModel>(model_type, model_id);
            break;
        case TYPE_MASSPOINTSPRITE_MODEL:
            pResourceModel = createModel<MassPointSpriteModel>(model_type, model_id);
            break;
        case TYPE_POINTSPRITESET_MODEL:
            pResourceModel = createModel<PointSpriteSetModel>(model_type, model_id);
            break;
        case TYPE_FRAMEDBOARD_MODEL:
            pResourceModel = createModel<FramedBoardModel>(model_type, model_id);
            break;
        case TYPE_FRAMEDSPRITE_MODEL:
            pResourceModel = createModel<FramedSpriteModel>(model_type, model_id);
            break;
        case TYPE_REGULARPOLYGONSPRITE_MODEL:
            pResourceModel = createModel<RegularPolygonSpriteModel>(model_type, model_id);
            break;
        case TYPE_REGULARPOLYGONBOARD_MODEL:
            pResourceModel = createModel<RegularPolygonBoardModel>(model_type, model_id);
            break;
        case TYPE_BONEANIMESH_MODEL:
            pResourceModel = createModel<BoneAniMeshModel>(model_type, model_id);
            break;
        case TYPE_SKINANIMESH_MODEL:
            pResourceModel = createModel<SkinAniMeshModel>(model_type, model_id);
            break;
        default:
            throwCriticalException("prm_idstr="<<prm_idstr<<" の '"<<model_type<<"' ・・・そんなモデル種別は知りません");
            pResourceModel = nullptr;
            break;
    }

    return pResourceModel;
}

template <typename T>
T* ModelManager::createModel(char prm_model_type, const char* prm_model_id) {
    T* pModel_new = NEW T(prm_model_id);
    pModel_new->_model_type = prm_model_type;
    pModel_new->restore();
    return pModel_new;
}

D3DXMeshModel* ModelManager::createD3DXMeshModel(char prm_model_type, const char* prm_model_id, DWORD prm_dwOptions) {
    D3DXMeshModel* pD3DXMeshModel_new = NEW D3DXMeshModel(prm_model_id, prm_dwOptions);
    pD3DXMeshModel_new->_model_type = prm_model_type;
    pD3DXMeshModel_new->restore();
    return pD3DXMeshModel_new;
}


//void ModelManager::obtainMetaModelInfo(ModelXFileFmt* prm_pModelDefineXFileFmt_out, char* prm_model_id) {
//    _TRACE_("ModelManager::getMetaModelInfo() prm_model_id="<<prm_model_id);
//    std::string model_def_file = std::string(prm_model_id) + ".modelx";
//    std::string model_def_filepath = Model::getMetaModelInfoPath(model_def_file);
//    obtainMetaModelInfo(prm_pModelDefineXFileFmt_out, model_def_filepath);
//}

void ModelManager::obtainMetaModelInfo(ModelXFileFmt* prm_pModelDefineXFileFmt_out, std::string prm_modelfile_filepath) {
    //    "xof 0303txt 0032 \n" \
    //    "template MetaModelInfo { " \
    //    "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
    //    "   DWORD XFileNum; " \
    //    "   array STRING XFileNames[XFileNum]; " \
    //    "   DWORD DrawSetNum; " \
    //    "   array FLOAT BaseTransformMatrix[16]; " \
    //    "}\n";

    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_modelx->CreateEnumObject(
                                     (void*)prm_modelfile_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainMetaModelInfo() '"<<prm_modelfile_filepath<<"' のCreateEnumObjectに失敗しました。modelx ファイルのフォーマットを確認して下さい。");
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //ループしているが、child は一つだけです。
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainMetaModelInfo() "<<prm_modelfile_filepath<<" のフォーマットエラー。 MeshModelDef { ... }  の MeshModelDef が見つからないです。");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainMetaModelInfo() "<<prm_modelfile_filepath<<" のフォーマットエラー。");
    }
    memcpy(&(prm_pModelDefineXFileFmt_out->XFileNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    int xfile_num = prm_pModelDefineXFileFmt_out->XFileNum;
    prm_pModelDefineXFileFmt_out->XFileNames = NEW std::string[xfile_num];
    char tmp_filename[256];
    for (int i = 0; i < xfile_num; i++) {
        strcpy(tmp_filename, pXData);
        size_t len = strlen(tmp_filename);
        pXData += sizeof(char) * len;
        pXData += sizeof(char); // '\0'
        prm_pModelDefineXFileFmt_out->XFileNames[i] = std::string(tmp_filename);
    }
    memcpy(&(prm_pModelDefineXFileFmt_out->DrawSetNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    FLOAT aMat[16];
    memcpy(aMat, pXData, sizeof(FLOAT)*16);
    pXData += sizeof(FLOAT)*16;
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._11 = aMat[0];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._12 = aMat[1];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._13 = aMat[2];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._14 = aMat[3];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._21 = aMat[4];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._22 = aMat[5];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._23 = aMat[6];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._24 = aMat[7];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._31 = aMat[8];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._32 = aMat[9];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._33 = aMat[10];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._34 = aMat[11];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._41 = aMat[12];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._42 = aMat[13];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._43 = aMat[14];
    prm_pModelDefineXFileFmt_out->BaseTransformMatrix._44 = aMat[15];

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

//void ModelManager::obtainMeshModelInfo(ModelXFileFmt* prm_pModelXFileFmt_out, std::string prm_meshx_filepath) {
//    _TRACE_("ModelManager::obtainMeshModelInfo() prm_meshx_filepath="<<prm_meshx_filepath);
//    //    "xof 0303txt 0032 \n" \
//    //    "template MeshModelDef { " \
//    //    "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
//    //    "   DWORD XFileNum; " \
//    //    "   array STRING XFileNames[XFileNum]; " \
//    //    "   DWORD DrawSetNum; " \
//    //    "   array FLOAT BaseTransformMatrix[16]; " \
//    //    "}\n";
//
//    ID3DXFileEnumObject* pID3DXFileEnumObject;
//    HRESULT hr = _pID3DXFile_meshx->CreateEnumObject(
//                                     (void*)prm_meshx_filepath.c_str(),
//                                     D3DXF_FILELOAD_FROMFILE,
//                                     &pID3DXFileEnumObject);
//    checkDxException(hr, S_OK, "ModelManager::obtainMeshModelInfo() '"<<prm_meshx_filepath<<"' のCreateEnumObjectに失敗しました。meshxファイルのフォーマットを確認して下さい。");
//    ID3DXFileData* pID3DXFileData = nullptr;
//    SIZE_T nChildren;
//    pID3DXFileEnumObject->GetChildren(&nChildren);
//    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
//        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
//    } //ループしているが、child は一つだけです。
//    if (pID3DXFileData == nullptr) {
//        throwCriticalException("ModelManager::obtainMeshModelInfo() "<<prm_meshx_filepath<<" のフォーマットエラー。 MeshModelDef { ... }  の MeshModelDef が見つからないです。");
//    }
//    SIZE_T xsize = 0;
//    char* pXData = nullptr;
//    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
//    if (pXData == nullptr) {
//        throwCriticalException("ModelManager::obtainMeshModelInfo() "<<prm_meshx_filepath<<" のフォーマットエラー。");
//    }
//    memcpy(&(prm_pModelXFileFmt_out->XFileNum), pXData, sizeof(DWORD));
//    pXData += sizeof(DWORD);
//    int xfile_num = prm_pModelXFileFmt_out->XFileNum;
//    prm_pModelXFileFmt_out->XFileNames = NEW std::string[xfile_num];
//    char tmp_filename[256];
//    for (int i = 0; i < xfile_num; i++) {
//        strcpy(tmp_filename, pXData);
//        size_t len = strlen(tmp_filename);
//        pXData += sizeof(char) * len;
//        pXData += sizeof(char); // '\0'
//        prm_pModelXFileFmt_out->XFileNames[i] = std::string(tmp_filename);
//    }
//    memcpy(&(prm_pModelXFileFmt_out->DrawSetNum), pXData, sizeof(DWORD));
//    pXData += sizeof(DWORD);
//    FLOAT aMat[16];
//    memcpy(aMat, pXData, sizeof(FLOAT)*16);
//    pXData += sizeof(FLOAT)*16;
//    prm_pModelXFileFmt_out->BaseTransformMatrix._11 = aMat[0];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._12 = aMat[1];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._13 = aMat[2];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._14 = aMat[3];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._21 = aMat[4];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._22 = aMat[5];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._23 = aMat[6];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._24 = aMat[7];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._31 = aMat[8];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._32 = aMat[9];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._33 = aMat[10];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._34 = aMat[11];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._41 = aMat[12];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._42 = aMat[13];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._43 = aMat[14];
//    prm_pModelXFileFmt_out->BaseTransformMatrix._44 = aMat[15];
//
//    pID3DXFileData->Unlock();
//    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
//    GGAF_RELEASE(pID3DXFileEnumObject);
//}

void ModelManager::obtainSpriteModelInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprx_filepath) {
    _TRACE_("ModelManager::obtainSpriteModelInfo() prm_sprx_filepath="<<prm_sprx_filepath);
    //    "xof 0303txt 0032 \n" \
    //    "template SpriteModelDef {" \
    //    "   <E4EECE4C-E106-11DC-9B62-346D55D89599>" \
    //    "   FLOAT  Width;" \
    //    "   FLOAT  Height;" \
    //    "   STRING TextureFile;" \
    //    "   DWORD  TextureSplitRows;" \
    //    "   DWORD  TextureSplitCols;" \
    //    "   DWORD  DrawSetNum; " \
    //    "   array FLOAT BaseTransformMatrix[16]; " \
    //    "}\n";
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_sprx->CreateEnumObject(
                                     (void*)prm_sprx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainSpriteModelInfo() '"<<prm_sprx_filepath<<"' のCreateEnumObjectに失敗しました。sprxファイルのフォーマットを確認して下さい。");
    //TODO:GUIDなんとかする。今は完全無視。
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //ループしているが、child は一つだけです。
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainSpriteModelInfo() "<<prm_sprx_filepath<<" のフォーマットエラー。 SpriteModelDef { ... }  の SpriteModelDef が見つからないです。");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainSpriteModelInfo() "<<prm_sprx_filepath<<" のフォーマットエラー。");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    memcpy(&(prm_pSpriteFmt_out->Width), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    memcpy(&(prm_pSpriteFmt_out->Height), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    strcpy(prm_pSpriteFmt_out->TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(prm_pSpriteFmt_out->TextureFile)+1));
    memcpy(&(prm_pSpriteFmt_out->TextureSplitRows), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pSpriteFmt_out->TextureSplitCols), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
//    memcpy(&(prm_pSpriteFmt_out->DrawSetNum), pXData, sizeof(DWORD));
//    pXData += sizeof(DWORD);
//
//    FLOAT aMat[16];
//    memcpy(aMat, pXData, sizeof(FLOAT)*16);
//    pXData += sizeof(FLOAT)*16;
//    prm_pSpriteFmt_out->BaseTransformMatrix._11 = aMat[0];
//    prm_pSpriteFmt_out->BaseTransformMatrix._12 = aMat[1];
//    prm_pSpriteFmt_out->BaseTransformMatrix._13 = aMat[2];
//    prm_pSpriteFmt_out->BaseTransformMatrix._14 = aMat[3];
//    prm_pSpriteFmt_out->BaseTransformMatrix._21 = aMat[4];
//    prm_pSpriteFmt_out->BaseTransformMatrix._22 = aMat[5];
//    prm_pSpriteFmt_out->BaseTransformMatrix._23 = aMat[6];
//    prm_pSpriteFmt_out->BaseTransformMatrix._24 = aMat[7];
//    prm_pSpriteFmt_out->BaseTransformMatrix._31 = aMat[8];
//    prm_pSpriteFmt_out->BaseTransformMatrix._32 = aMat[9];
//    prm_pSpriteFmt_out->BaseTransformMatrix._33 = aMat[10];
//    prm_pSpriteFmt_out->BaseTransformMatrix._34 = aMat[11];
//    prm_pSpriteFmt_out->BaseTransformMatrix._41 = aMat[12];
//    prm_pSpriteFmt_out->BaseTransformMatrix._42 = aMat[13];
//    prm_pSpriteFmt_out->BaseTransformMatrix._43 = aMat[14];
//    prm_pSpriteFmt_out->BaseTransformMatrix._44 = aMat[15];

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}
void ModelManager::obtainFramedSpriteModelInfo(FramedSpriteXFileFmt* prm_pFramedSpriteFmt_out, std::string prm_fsprx_filepath) {
    _TRACE_("ModelManager::obtainFramedSpriteModelInfo() prm_fsprx_filepath="<<prm_fsprx_filepath);
    //    "xof 0303txt 0032 \n" \
    //    "template FramedSpriteModelDef {" \
    //    "   <E2A64EB2-5F1B-42B4-B05A-19DF9EB9CD72>" \
    //    "   FLOAT  Width;" \
    //    "   FLOAT  Height;" \
    //    "   STRING TextureFile;" \
    //    "   DWORD  TextureSplitRows;" \
    //    "   DWORD  TextureSplitCols;" \
    //    "\n" \
    //    "   FLOAT  FrameWidth;" \
    //    "   FLOAT  FrameHeight;" \
    //    "   STRING FrameTextureFile;" \
    //    "   DWORD  FrameTextureSplitRows;" \
    //    "   DWORD  FrameTextureSplitCols;" \
    //    "}\n";
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_fsprx->CreateEnumObject(
                                     (void*)prm_fsprx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainFramedSpriteModelInfo() '"<<prm_fsprx_filepath<<"' のCreateEnumObjectに失敗しました。fsprxファイルのフォーマットを確認して下さい。");
    //TODO:GUIDなんとかする。今は完全無視。
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //ループしているが、child は一つだけです。
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainFramedSpriteModelInfo() "<<prm_fsprx_filepath<<" のフォーマットエラー。 FramedSpriteModelDef { ... }  の FramedSpriteModelDef が見つからないです。");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainFramedSpriteModelInfo() "<<prm_fsprx_filepath<<" のフォーマットエラー。");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    memcpy(&(prm_pFramedSpriteFmt_out->Width), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    memcpy(&(prm_pFramedSpriteFmt_out->Height), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    strcpy(prm_pFramedSpriteFmt_out->TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(prm_pFramedSpriteFmt_out->TextureFile)+1));
    memcpy(&(prm_pFramedSpriteFmt_out->TextureSplitRows), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pFramedSpriteFmt_out->TextureSplitCols), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    memcpy(&(prm_pFramedSpriteFmt_out->FrameWidth), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    memcpy(&(prm_pFramedSpriteFmt_out->FrameHeight), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    strcpy(prm_pFramedSpriteFmt_out->FrameTextureFile, pXData);
    pXData += (sizeof(char) * (strlen(prm_pFramedSpriteFmt_out->FrameTextureFile)+1));
    memcpy(&(prm_pFramedSpriteFmt_out->FrameTextureSplitRows), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pFramedSpriteFmt_out->FrameTextureSplitCols), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void ModelManager::obtainRegPolySpriteModelInfo(RegPolySpriteXFileFmt* prm_pRegPolySpriteFmt_out, std::string prm_rsprx_filepath) {
    _TRACE_("ModelManager::obtainRegPolySpriteModelInfo() prm_sprx_filepath="<<prm_rsprx_filepath);
    //    "xof 0303txt 0032 \n" \
    //    "template RegularPolygonModelDef {" \
    //    "   <964A6FAF-9C35-460C-920F-4A87D713BCA6>" \
    //    "   FLOAT  Width;" \
    //    "   FLOAT  Height;" \
    //    "   STRING TextureFile;" \
    //    "   DWORD  TextureSplitRows;" \
    //    "   DWORD  TextureSplitCols;" \
    //    "   DWORD  FanNum;" \
    //    "   DWORD  IsCW;" \
    //    "}\n";
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_rsprx->CreateEnumObject(
                                     (void*)prm_rsprx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainRegPolySpriteModelInfo() '"<<prm_rsprx_filepath<<"' のCreateEnumObjectに失敗しました。rsprxファイルのフォーマットを確認して下さい。");
    //TODO:GUIDなんとかする。今は完全無視。
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //ループしているが、child は一つだけです。
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainRegPolySpriteModelInfo() "<<prm_rsprx_filepath<<" のフォーマットエラー。 RegularPolygonModelDef { ... }  の RegularPolygonModelDef が見つからないです。");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainRegPolySpriteModelInfo() "<<prm_rsprx_filepath<<" のフォーマットエラー。");
    }

    memcpy(&(prm_pRegPolySpriteFmt_out->Width), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    memcpy(&(prm_pRegPolySpriteFmt_out->Height), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    strcpy(prm_pRegPolySpriteFmt_out->TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(prm_pRegPolySpriteFmt_out->TextureFile)+1));
    memcpy(&(prm_pRegPolySpriteFmt_out->TextureSplitRows), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pRegPolySpriteFmt_out->TextureSplitCols), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    memcpy(&(prm_pRegPolySpriteFmt_out->FanNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pRegPolySpriteFmt_out->IsCW), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}
void ModelManager::obtainPointSpriteModelInfo(PointSpriteXFileFmt* prm_pPointSpriteFmt_out, std::string prm_psprx_filepath) {
    _TRACE_("ModelManager::obtainPointSpriteModelInfo() prm_psprx_filepath="<<prm_psprx_filepath);
    //    "xof 0303txt 0032\n" \
    //    "template Vector {\n" \
    //    "  <3d82ab5e-62da-11cf-ab39-0020af71e433>\n" \
    //    "  FLOAT x;\n" \
    //    "  FLOAT y;\n" \
    //    "  FLOAT z;\n" \
    //    "}\n" \
    //    "template ColorRGBA {\n" \
    //    "  <35ff44e0-6c7c-11cf-8f52-0040333594a3>\n" \
    //    "  FLOAT red;\n" \
    //    "  FLOAT green;\n" \
    //    "  FLOAT blue;\n" \
    //    "  FLOAT alpha;\n" \
    //    "}\n" \
    //    "template PointSpriteModelDef {\n" \
    //    "  <2A355D47-C0C6-4979-92D0-3FCE3090C49A>\n" \
    //    "  FLOAT  SquareSize;\n" \
    //    "  STRING TextureFile;\n" \
    //    "  DWORD  TextureSplitRowCol;\n" \
    //    "  DWORD  VerticesNum;\n" \
    //    "  array  Vector    Vertices[VerticesNum];\n" \
    //    "  array  ColorRGBA VertexColors[VerticesNum];\n" \
    //    "  array  DWORD     InitUvPtnNo[VerticesNum];\n" \
    //    "  array  FLOAT     InitScale[VerticesNum];\n" \
    //    "}\n" \
    //    "\n";

    //スプライト情報読込みテンプレートの登録(初回実行時のみ)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData = nullptr;
    HRESULT hr = _pID3DXFile_psprx->CreateEnumObject((void*)prm_psprx_filepath.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainPointSpriteModelInfo() '"<<prm_psprx_filepath<<"' のCreateEnumObjectに失敗しました。psprx ファイルのフォーマットを確認して下さい。");

    //TODO:GUIDなんとかする。今は完全無視。
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainPointSpriteModelInfo() "<<prm_psprx_filepath<<" のフォーマットエラー。 PointSpriteModelDef { ... }  の PointSpriteModelDef が見つからないです。");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainPointSpriteModelInfo() "<<prm_psprx_filepath<<" のフォーマットエラー。");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    //    XFILE_FMT_HD xDataHd;
    //"  FLOAT  SquareSize;\n"
    memcpy(&(prm_pPointSpriteFmt_out->SquareSize), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    //"  STRING TextureFile;\n"
    strcpy(prm_pPointSpriteFmt_out->TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(prm_pPointSpriteFmt_out->TextureFile)+1));
    //"  DWORD  TextureSplitRowCol;\n"
    memcpy(&(prm_pPointSpriteFmt_out->TextureSplitRowCol), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    //"  DWORD  VerticesNum;\n"
    memcpy(&(prm_pPointSpriteFmt_out->VerticesNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    int vaetexs_num = prm_pPointSpriteFmt_out->VerticesNum;

    //"  array  Vector    Vertices[VerticesNum];\n"
    prm_pPointSpriteFmt_out->paD3DVECTOR_Vertices = NEW D3DVECTOR[vaetexs_num];
    memcpy(prm_pPointSpriteFmt_out->paD3DVECTOR_Vertices, pXData, sizeof(D3DVECTOR)*vaetexs_num);
    pXData += sizeof(D3DVECTOR)*prm_pPointSpriteFmt_out->VerticesNum;
    //"  array  ColorRGBA VertexColors[VerticesNum];\n"
    prm_pPointSpriteFmt_out->paD3DVECTOR_VertexColors = NEW D3DCOLORVALUE[vaetexs_num];
    memcpy(prm_pPointSpriteFmt_out->paD3DVECTOR_VertexColors, pXData, sizeof(D3DCOLORVALUE)*vaetexs_num);
    pXData += sizeof(D3DCOLORVALUE)*vaetexs_num;
    //"  array  DWORD     InitUvPtnNo[VerticesNum];\n"
    prm_pPointSpriteFmt_out->paInt_InitUvPtnNo = NEW DWORD[vaetexs_num];
    memcpy(prm_pPointSpriteFmt_out->paInt_InitUvPtnNo, pXData, sizeof(DWORD)*vaetexs_num);
    pXData += sizeof(DWORD)*vaetexs_num;
    //"  array  FLOAT     InitScale[VerticesNum];\n"
    prm_pPointSpriteFmt_out->paFLOAT_InitScale = NEW FLOAT[vaetexs_num];
    memcpy(prm_pPointSpriteFmt_out->paFLOAT_InitScale, pXData, sizeof(FLOAT)*vaetexs_num);
    pXData += sizeof(FLOAT)*vaetexs_num;

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

GgafCore::ResourceConnection<Model>* ModelManager::processCreateConnection(const char* prm_idstr, Model* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    ModelConnection* p = NEW ModelConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return p;
}

ModelManager::~ModelManager() {
    _TRACE3_("start-->");
    GGAF_RELEASE(_pID3DXFile_modelx);
//    GGAF_RELEASE(_pID3DXFile_meshx);

    GGAF_RELEASE(_pID3DXFile_sprx);
    GGAF_RELEASE(_pID3DXFile_psprx);
    GGAF_RELEASE(_pID3DXFile_fsprx);
    GGAF_RELEASE(_pID3DXFile_rsprx);
    GGAF_DELETE(_pModelTextureManager);
    _TRACE3_("するけども、ここでは既に何も解放するものがないはずです");
    releaseAll();
}

void ModelManager::restoreAll() {
    _TRACE3_("start-->");
    GgafCore::ResourceConnection<Model>* pCurrent = _pConn_first;
    _TRACE3_("restoreAll pCurrent="<<pCurrent);
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void ModelManager::onDeviceLostAll() {
    _TRACE3_("start-->");
    GgafCore::ResourceConnection<Model>* pCurrent = _pConn_first;
    _TRACE3_("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent) {
        _TRACE_(FUNC_NAME<<" ["<<pCurrent->peek()->_model_id<<"] onDeviceLost begin");
        pCurrent->peek()->onDeviceLost();
        _TRACE_(FUNC_NAME<<" ["<<pCurrent->peek()->_model_id<<"] onDeviceLost end");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void ModelManager::releaseAll() {
    _TRACE3_("start-->");
    GgafCore::ResourceConnection<Model>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}



//「経緯メモ（グチ） 2009/07/05」
//シェーダーに興味がわき、勉強を仕始めていた頃、D3DXLoadMeshFromX で読み込むと勝手に頂点バッファが増る時がある事に気がついて悩んでいた。
//D3DXLoadMeshFromX でXファイルを読み込むと思った通りの頂点数（頂点インデックス）になる保証が無い。
//例えば三角形ポリゴンでのBOXの場合、頂点8個、頂点インデックス12(*3)（面が12個）、法線ベクトル6個、法線インデックス12(*3)、となるが、
//このようなXファイルをテキストエディタで作って D3DXLoadMeshFromX で読み込むと頂点が24個になってしまう（と思う）。
//これは、Xファイルでは法線を面に紐つけて持たせれる意味合いのデータが作成できるにもかかわらず、DIRECTX側では法線情報を各頂点に持たせるため、
//頂点が8個では本来は面単位であるハズの法線が表現できなくなってしまうためと予想できる。
//問題は「予想」を「仕様」に置きかえれないところだった。
//親切(不親切)にも D3DXLoadMeshFromX 内で ID3DXMesh 構築時、面と面の陰影を正しくつけるため、つまりエッジをクッキリ見せるため
//法線が頂点より優先されて、頂点の隣接する面の数（法線数）分、頂点を増やす、という処理が勝手に行われるのであろう。
//しかし、シェーダーでのモーフ時や、複数オブジェクトをDrawIndexedPrimitiveでわけて表示する時等、
//勝手に頂点の数が変わってしまっては困るということが解るようになった。
//「自分で決めた頂点数で頂点バッファを作りたい。」という、基本的なことが出来ないため試行錯誤した。
//結論は、法線数＝頂点数のXファイルを作成すればいいのであるが、そんな事気にしてモデリングやってられない。
//D3DXLoadMeshFromX のメッシュ最適化などの記事はある。しかし、知りたいのは内部アルゴリズム「全て」である。
//D3DXLoadMeshFromX のソースコードさえあれば解決するのだが、当然公開なんてされて無い。
//そんなわけで、内部で何やってるか完璧にはわからない。ならば D3DXLoadMeshFromX は使えないのか？。という結論に行きついた。
//つまりシェーダーを効果的に使うには独自にXファイルを読み込むしかないのかな、めんどくさいなぁ、でもしかたないのか。何かいい方法は？
//要は、「頂点」「法線」「マテリアル」「UV」「必要な他の情報」を読めればいいだろう、ならばなんでもいいじゃないか。
//Xファイルなんて、めんどくさいフォーマットじゃなくても・・・というかXファイルってむしろ何さ？！、という事がだんだん解ってきた。
//しかし D3DXLoadMeshFromX が「使えない」と結論付けるまでの期間が長かったお陰で、私はXファイルマスターになっていた。
//そこで、せっかくなのでXファイルからモデル情報を読む処理を独自に作ろうと決めたのだった。
//とりあえず、メタセコイア、3DSMAXのエクスポートするXファイルの「静的」モデルが読み込めれば良いかな、シューティングのキャラだし。という考えで作成開始。
//そしてしばらくして Paul さんのサンプルコードを発見する。http://www.gamedev.net/reference/programming/features/xfilepc/
//「Loading and displaying .X files without DirectX」だと！。なんてドンピシャなトピックなんだ。というわけで採用決定。
//しかしこのサンプルは、結構未考慮な点が多くて大変だった。でも０から作るよりはマシで、勉強にもなったので良しとしよう。（GCCとVCの挙動差とか）
//考えれば頂点情報を自前で読み、管理する事は、いずれ必ず通る道だったろう。ただ、それ至るまでの時間がかかり過ぎだった。
//無限の組み合わ数とも思えるトライアンドエラーで、ゲームを作りたいという情熱が打ち砕かれそうだ。挫折してもオカシクナイ。
//このあたりの事って、他の日曜プログラマの人達はいったいどうやってるのだろうか？、みんな悩んでないのかなぁ。
//（・・・あぁしかしこれは、まだほんの序章に過ぎなかった！（笑））
