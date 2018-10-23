
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

#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"

#include <Shlwapi.h>
#include <d3dx9xof.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMassSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMassMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMassBoardModel.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMassPointSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxFramedBoardModel.h"
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonSpriteModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMeshSetModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxCubeMapMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/ex/GgafDxWorldBoundModel.h"
#include "jp/ggaf/dxcore/util/GgafDxWorldMatStack.h"
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchyWorldFrame.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxModel* GgafDxModelManager::_pModelLastDraw = nullptr;

GgafDxModelManager::GgafDxModelManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxModel> (prm_manager_name) {
    //テクスチャマネジャー
    _pModelTextureManager = NEW GgafDxTextureManager("GgafDxTextureManager");

    //板ポリゴンモデル定義ファイル(拡張子sprx)のフォーマット定義
    HRESULT hr;
    D3DXFileCreate( &_pID3DXFile_sprx );
    static const char* sprite_model_xfile_template =
    "xof 0303txt 0032\n" \
    "template SpriteDef {" \
    "   <E4EECE4C-E106-11DC-9B62-346D55D89593>" \
    "   FLOAT  Width;" \
    "   FLOAT  Height;" \
    "   STRING TextureFile;" \
    "   DWORD  TextureSplitRows;" \
    "   DWORD  TextureSplitCols;" \
    "}";
    hr = _pID3DXFile_sprx->RegisterTemplates(sprite_model_xfile_template, (DWORD)(strlen(sprite_model_xfile_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwGgafCriticalException("RegisterTemplatesに失敗しました。sprite_model_xfile_template を確認して下さい。");
    }
#endif

    //ポイントスプライト定義ファイル(拡張子psprx)のフォーマット定義
    D3DXFileCreate( &_pID3DXFile_psprx );
    static const char* pointsprite_model_xfile_template =
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
            "template PointSpriteDef {\n" \
            "  <E4EECE4C-E106-11DC-9B62-346D55D89593>\n" \
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
    hr = _pID3DXFile_psprx->RegisterTemplates(pointsprite_model_xfile_template, (DWORD)(strlen(pointsprite_model_xfile_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwGgafCriticalException("RegisterTemplatesに失敗しました。\""<<CONFIG::DIR_SPRITE_MODEL[0]<<"ggaf_pointspritemodel_define.x\"を確認して下さい。");
    }
#endif
}

GgafDxModel* GgafDxModelManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1); //最初のスラッシュで分割
    if (names.size() != 2) {
        throwGgafCriticalException("引数は、主に次の形式で与えてください。『モデルタイプ1文字  + \"/\" + モデル定義名(拡張子 .x を除いたもの)』\n"
                "実際の引数は、prm_idstr="<<prm_idstr);
    }
    char model_type = (names[0])[0];
    const char* model_name = names[1].c_str();
    GgafDxModel* pResourceModel;
    switch (model_type) {
        case TYPE_D3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_DYNAD3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_DYNAMIC);
            break;
        case TYPE_D3DXANIMESH_MODEL:
            pResourceModel = createD3DXAniMeshModel(model_name);
            break;
        case TYPE_MESH_MODEL:
            pResourceModel = createMeshModel(model_name);
            break;
        case TYPE_MESHSET_MODEL:
            pResourceModel = createMeshSetModel(model_name);
            break;
        case TYPE_MASSMESH_MODEL:
            pResourceModel = createMassMeshModel(model_name);
            break;
        case TYPE_CUBEMAPMESH_MODEL:
            pResourceModel = createCubeMapMeshModel(model_name);
            break;
        case TYPE_CUBEMAPMESHSET_MODEL:
            pResourceModel = createCubeMapMeshSetModel(model_name);
            break;
        case TYPE_MORPHMESH_MODEL:
            // "M/4/xxxxx" の場合、プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
            pResourceModel = createMorphMeshModel(model_name);
            break;
        case TYPE_MASSMORPHMESH_MODEL:
            //"m/4/xxxxx_2" の場合、セットが４プライマリのメッシュが1、モーフターゲットのメッシュが2つという意味
            pResourceModel = createMassMorphMeshModel(model_name);
            break;
        case TYPE_CUBEMAPMORPHMESH_MODEL:
            //"H/4/xxxxx" の場合、プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
            pResourceModel = createCubeMapMorphMeshModel(model_name);
            break;
        case TYPE_WORLDBOUND_MODEL:
            // "W/4/xxxxx" の場合、プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
            pResourceModel = createWorldBoundModel(model_name);
            break;
        case TYPE_SPRITE_MODEL:
            pResourceModel = createSpriteModel(model_name);
            break;
        case TYPE_SPRITESET_MODEL:
            pResourceModel = createSpriteSetModel(model_name);
            break;
        case TYPE_MESHSPRITE_MODEL:
            pResourceModel = createMassSpriteModel(model_name);
            break;
        case TYPE_BOARD_MODEL:
            pResourceModel = createBoardModel(model_name);
            break;
        case TYPE_BOARDSET_MODEL:
            pResourceModel = createBoardSetModel(model_name);
            break;
        case TYPE_MASSBOARD_MODEL:
            pResourceModel = createMassBoardModel(model_name);
            break;
        case TYPE_CUBE_MODEL:
            pResourceModel = createD3DXMeshModel(const_cast<char*>("cube"), D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_POINTSPRITE_MODEL:
            pResourceModel = createPointSpriteModel(model_name);
            break;
        case TYPE_MASSPOINTSPRITE_MODEL:
            pResourceModel = createMassPointSpriteModel(model_name);
            break;
        case TYPE_POINTSPRITESET_MODEL:
            pResourceModel = createPointSpriteSetModel(model_name);
            break;
        case TYPE_FRAMEDBOARD_MODEL:
            pResourceModel = createFramedBoardModel(model_name);
            break;
        case TYPE_REGULAR_POLYGON_SPRITE_MODEL:
            pResourceModel = createRegularPolygonSpriteModel(model_name);
            break;
        default:
            throwGgafCriticalException("prm_idstr="<<prm_idstr<<" の '"<<model_type<<"' ・・・そんなモデル種別は知りません");
            pResourceModel = nullptr;
            break;
    }
    return pResourceModel;
}

GgafDxD3DXMeshModel* GgafDxModelManager::createD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions) {
    GgafDxD3DXMeshModel* pD3DXMeshModel_new = NEW GgafDxD3DXMeshModel(prm_model_name, prm_dwOptions);
    pD3DXMeshModel_new->restore();
    return pD3DXMeshModel_new;
}

GgafDxD3DXAniMeshModel* GgafDxModelManager::createD3DXAniMeshModel(const char* prm_model_name) {
    GgafDxD3DXAniMeshModel* pD3DXAniMeshModel_new = NEW GgafDxD3DXAniMeshModel(prm_model_name);
    pD3DXAniMeshModel_new->restore();
    return pD3DXAniMeshModel_new;
}

GgafDxSpriteModel* GgafDxModelManager::createSpriteModel(const char* prm_model_name) {
    GgafDxSpriteModel* pSpriteModel_new = NEW GgafDxSpriteModel(prm_model_name);
    pSpriteModel_new->restore();
    return pSpriteModel_new;
}

GgafDxSpriteSetModel* GgafDxModelManager::createSpriteSetModel(const char* prm_model_name) {
    GgafDxSpriteSetModel* pSpriteSetModel_new = NEW GgafDxSpriteSetModel(prm_model_name);
    pSpriteSetModel_new->restore();
    return pSpriteSetModel_new;
}

GgafDxMassSpriteModel* GgafDxModelManager::createMassSpriteModel(const char* prm_model_name) {
    GgafDxMassSpriteModel* pMassSpriteModel_new = NEW GgafDxMassSpriteModel(prm_model_name);
    pMassSpriteModel_new->restore();
    return pMassSpriteModel_new;
}

GgafDxBoardModel* GgafDxModelManager::createBoardModel(const char* prm_model_name) {
    GgafDxBoardModel* pBoardModel_new = NEW GgafDxBoardModel(prm_model_name);
    pBoardModel_new->restore();
    return pBoardModel_new;
}

GgafDxBoardSetModel* GgafDxModelManager::createBoardSetModel(const char* prm_model_name) {
    GgafDxBoardSetModel* pBoardSetModel_new = NEW GgafDxBoardSetModel(prm_model_name);
    pBoardSetModel_new->restore();
    return pBoardSetModel_new;
}

GgafDxMassBoardModel* GgafDxModelManager::createMassBoardModel(const char* prm_model_name) {
    GgafDxMassBoardModel* pMassBoardModel_new = NEW GgafDxMassBoardModel(prm_model_name);
    pMassBoardModel_new->restore();
    return pMassBoardModel_new;
}

GgafDxMeshModel* GgafDxModelManager::createMeshModel(const char* prm_model_name) {
    GgafDxMeshModel* pMeshModel_new = NEW GgafDxMeshModel(prm_model_name);
    pMeshModel_new->restore();
    return pMeshModel_new;
}

GgafDxMeshSetModel* GgafDxModelManager::createMeshSetModel(const char* prm_model_name) {
    GgafDxMeshSetModel* pMeshSetModel_new = NEW GgafDxMeshSetModel(prm_model_name);
    pMeshSetModel_new->restore();
    return pMeshSetModel_new;
}

GgafDxMassMeshModel* GgafDxModelManager::createMassMeshModel(const char* prm_model_name) {
    GgafDxMassMeshModel* pMassMeshModel_new = NEW GgafDxMassMeshModel(prm_model_name);
    pMassMeshModel_new->restore();
    return pMassMeshModel_new;
}

GgafDxCubeMapMeshModel* GgafDxModelManager::createCubeMapMeshModel(const char* prm_model_name) {
    GgafDxCubeMapMeshModel* pMeshCubeMapModel_new = NEW GgafDxCubeMapMeshModel(prm_model_name);
    pMeshCubeMapModel_new->restore();
    return pMeshCubeMapModel_new;
}

GgafDxCubeMapMeshSetModel* GgafDxModelManager::createCubeMapMeshSetModel(const char* prm_model_name) {
    GgafDxCubeMapMeshSetModel* pMeshCubeMapSetModel_new = NEW GgafDxCubeMapMeshSetModel(prm_model_name);
    pMeshCubeMapSetModel_new->restore();
    return pMeshCubeMapSetModel_new;
}

GgafDxMorphMeshModel* GgafDxModelManager::createMorphMeshModel(const char* prm_model_name) {
    // "M/4/xxxxx" の場合、プライマリのメッシュが1、モーフターゲットのメッシュが4つという意味
    // ここでprm_model_name は "4/xxxxx" という文字列になっている。
    // モーフターゲット数が違うモデルは、別モデルという扱いにするため、モデル名に数値を残す。
    GgafDxMorphMeshModel* pMorphMeshModel_new = NEW GgafDxMorphMeshModel(prm_model_name);
    pMorphMeshModel_new->restore();
    return pMorphMeshModel_new;
}

GgafDxMassMorphMeshModel* GgafDxModelManager::createMassMorphMeshModel(const char* prm_model_name) {
    GgafDxMassMorphMeshModel* pMassMorphMeshModel_new = NEW GgafDxMassMorphMeshModel(prm_model_name);
    pMassMorphMeshModel_new->restore();
    return pMassMorphMeshModel_new;
}

GgafDxCubeMapMorphMeshModel* GgafDxModelManager::createCubeMapMorphMeshModel(const char* prm_model_name) {
    GgafDxCubeMapMorphMeshModel* pCubeMapMorphMeshModel_new = NEW GgafDxCubeMapMorphMeshModel(prm_model_name);
    pCubeMapMorphMeshModel_new->restore();
    return pCubeMapMorphMeshModel_new;
}

GgafDxWorldBoundModel* GgafDxModelManager::createWorldBoundModel(const char* prm_model_name) {
    GgafDxWorldBoundModel* pWorldBoundModel_new = NEW GgafDxWorldBoundModel(prm_model_name);
    pWorldBoundModel_new->restore();
    return pWorldBoundModel_new;
}

GgafDxPointSpriteModel* GgafDxModelManager::createPointSpriteModel(const char* prm_model_name) {
    GgafDxPointSpriteModel* pPointSpriteModel_new = NEW GgafDxPointSpriteModel(prm_model_name);
    pPointSpriteModel_new->restore();
    return pPointSpriteModel_new;
}

GgafDxMassPointSpriteModel* GgafDxModelManager::createMassPointSpriteModel(const char* prm_model_name) {
    GgafDxMassPointSpriteModel* pMassPointSpriteModel_new = NEW GgafDxMassPointSpriteModel(prm_model_name);
    pMassPointSpriteModel_new->restore();
    return pMassPointSpriteModel_new;
}

GgafDxPointSpriteSetModel* GgafDxModelManager::createPointSpriteSetModel(const char* prm_model_name) {
    GgafDxPointSpriteSetModel* pPointSpriteSetModel_new = NEW GgafDxPointSpriteSetModel(prm_model_name);
    pPointSpriteSetModel_new->restore();
    return pPointSpriteSetModel_new;
}

GgafDxFramedBoardModel* GgafDxModelManager::createFramedBoardModel(const char* prm_model_name) {
    GgafDxFramedBoardModel* pFramedBoardModel_new = NEW GgafDxFramedBoardModel(prm_model_name);
    pFramedBoardModel_new->restore();
    return pFramedBoardModel_new;
}

GgafDxRegularPolygonSpriteModel* GgafDxModelManager::createRegularPolygonSpriteModel(const char* prm_model_name) {
    GgafDxRegularPolygonSpriteModel* pRglrPlygnSpriteModel_new = NEW GgafDxRegularPolygonSpriteModel(prm_model_name);
    pRglrPlygnSpriteModel_new->restore();
    return pRglrPlygnSpriteModel_new;
}

std::string GgafDxModelManager::getMeshFileName(std::string prm_model_name) {
    std::string xfile_name = CONFIG::DIR_MESH_MODEL[2] + "/" + prm_model_name + ".x"; //モデル名＋".x"でXファイル名になる
    UTIL::strReplace(xfile_name, "//", "/");
    _TRACE_("1 xfile_name.c_str()="<<xfile_name.c_str());
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name; //カレントに存在すればそれを優先
    } else {
        xfile_name = CONFIG::DIR_MESH_MODEL[1] + "/" + prm_model_name+ ".x";
        UTIL::strReplace(xfile_name, "//", "/");
        _TRACE_("2 xfile_name.c_str()="<<xfile_name.c_str());
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name; //ユーザースキンに存在すればそれを優先
        } else {
            xfile_name = CONFIG::DIR_MESH_MODEL[0] + "/" + prm_model_name+ ".x";
            UTIL::strReplace(xfile_name, "//", "/");
            _TRACE_("3 xfile_name.c_str()="<<xfile_name.c_str());
            if (PathFileExists(xfile_name.c_str()) ) {
                return xfile_name;
            } else {
                return "";
            }
        }
    }
}

std::string GgafDxModelManager::getSpriteFileName(std::string prm_model_name, std::string prm_ext){
    std::string xfile_name = CONFIG::DIR_SPRITE_MODEL[2] + "/" + prm_model_name + "." + prm_ext;
    UTIL::strReplace(xfile_name, "//", "/");
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name;
    } else {
        xfile_name = CONFIG::DIR_SPRITE_MODEL[1] + "/" +  prm_model_name + "." + prm_ext;
        UTIL::strReplace(xfile_name, "//", "/");
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name; //ユーザースキンに存在すればそれを優先
        } else {
            xfile_name = CONFIG::DIR_SPRITE_MODEL[0] + "/" +  prm_model_name + "." + prm_ext;
            UTIL::strReplace(xfile_name, "//", "/");
            if (PathFileExists(xfile_name.c_str()) ) {
                return xfile_name;
            } else {
                throwGgafCriticalException("スプライトモデル定義ファイルが見つかりません。xfile_name="<<xfile_name);
            }
        }
    }
}

void GgafDxModelManager::obtainSpriteInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprite_x_filename) {
    //スプライト情報読込み
    // xof 0303txt 0032
    // template SpriteDef {
    //    <E4EECE4C-E106-11DC-9B62-346D55D89593>
    //    FLOAT  Width;
    //    FLOAT  Height;
    //    STRING TextureFile;
    //    DWORD  TextureSplitRows;
    //    DWORD  TextureSplitCols;
    // }
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_sprx->CreateEnumObject(
                                     (void*)prm_sprite_x_filename.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "'"<<prm_sprite_x_filename<<"' のCreateEnumObjectに失敗しました。sprxファイルのフォーマットを確認して下さい。");
    //TODO:GUIDなんとかする。今は完全無視。
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //ループしているが、child は一つだけです。
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException(prm_sprite_x_filename<<" のフォーマットエラー。");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    memcpy(&(prm_pSpriteFmt_out->width), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    memcpy(&(prm_pSpriteFmt_out->height), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    strcpy(prm_pSpriteFmt_out->texture_file, pXData);
    pXData += (sizeof(char) * (strlen(prm_pSpriteFmt_out->texture_file)+1));
    memcpy(&(prm_pSpriteFmt_out->row_texture_split), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    memcpy(&(prm_pSpriteFmt_out->col_texture_split), pXData, sizeof(DWORD));
    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void GgafDxModelManager::obtainPointSpriteInfo(PointSpriteXFileFmt* pPointSpriteFmt_out, std::string prm_point_sprite_x_filename) {
    //スプライト情報読込みテンプレートの登録(初回実行時のみ)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData = nullptr;
    HRESULT hr = _pID3DXFile_psprx->CreateEnumObject((void*)prm_point_sprite_x_filename.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "'"<<prm_point_sprite_x_filename<<"' のCreateEnumObjectに失敗しました。psprx ファイルのフォーマットを確認して下さい。");

    //TODO:GUIDなんとかする。今は完全無視。
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

//    "template PointSpriteDef { "
//    "  <E4EECE4C-E106-11DC-9B62-346D55D89593> "
//    "  FLOAT  SquareSize; "
//    "  STRING TextureFile; "
//    "  DWORD  TextureSplitRowCol; "
//    "  DWORD  VerticesNum; "
//    "  array  Vector    Vertices[VerticesNum]; "
//    "  array  ColorRGBA VertexColors[VerticesNum]; "
//    "  array  DWORD     InitUvPtnNo[VerticesNum]; "
//    "  array  FLOAT     InitScale[VerticesNum]; "
//    "} "

//    class PointSpriteXFileFmt {
//    public:
//        float SquareSize;
//        char TextureFile[256];
//        int TextureSplitRowCol;
//        int VerticesNum;
//        D3DVECTOR* paD3DVECTOR_Vertices;
//        D3DCOLORVALUE* paD3DVECTOR_VertexColors;
//        int* paInt_InitUvPtnNo;
//        float* paFLOAT_InitScale;
//    };

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException(prm_point_sprite_x_filename<<" のフォーマットエラー。");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    //    XFILE_FMT_HD xDataHd;
    //"  FLOAT  SquareSize;\n"
    memcpy(&(pPointSpriteFmt_out->SquareSize), pXData, sizeof(FLOAT));
    pXData += sizeof(FLOAT);
    //"  STRING TextureFile;\n"
    strcpy(pPointSpriteFmt_out->TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(pPointSpriteFmt_out->TextureFile)+1));
    //"  DWORD  TextureSplitRowCol;\n"
    memcpy(&(pPointSpriteFmt_out->TextureSplitRowCol), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    //"  DWORD  VerticesNum;\n"
    memcpy(&(pPointSpriteFmt_out->VerticesNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    int vaetexs_num = pPointSpriteFmt_out->VerticesNum;

    //"  array  Vector    Vertices[VerticesNum];\n"
    pPointSpriteFmt_out->paD3DVECTOR_Vertices = NEW D3DVECTOR[vaetexs_num];
    memcpy(pPointSpriteFmt_out->paD3DVECTOR_Vertices, pXData, sizeof(D3DVECTOR)*vaetexs_num);
    pXData += sizeof(D3DVECTOR)*pPointSpriteFmt_out->VerticesNum;
    //"  array  ColorRGBA VertexColors[VerticesNum];\n"
    pPointSpriteFmt_out->paD3DVECTOR_VertexColors = NEW D3DCOLORVALUE[vaetexs_num];
    memcpy(pPointSpriteFmt_out->paD3DVECTOR_VertexColors, pXData, sizeof(D3DCOLORVALUE)*vaetexs_num);
    pXData += sizeof(D3DCOLORVALUE)*vaetexs_num;
    //"  array  DWORD     InitUvPtnNo[VerticesNum];\n"
    pPointSpriteFmt_out->paInt_InitUvPtnNo = NEW DWORD[vaetexs_num];
    memcpy(pPointSpriteFmt_out->paInt_InitUvPtnNo, pXData, sizeof(DWORD)*vaetexs_num);
    pXData += sizeof(DWORD)*vaetexs_num;
    //"  array  FLOAT     InitScale[VerticesNum];\n"
    pPointSpriteFmt_out->paFLOAT_InitScale = NEW FLOAT[vaetexs_num];
    memcpy(pPointSpriteFmt_out->paFLOAT_InitScale, pXData, sizeof(FLOAT)*vaetexs_num);
    pXData += sizeof(FLOAT)*vaetexs_num;

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

GgafResourceConnection<GgafDxModel>* GgafDxModelManager::processCreateConnection(const char* prm_idstr, GgafDxModel* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成開始。");
    GgafDxModelConnection* p = NEW GgafDxModelConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" を生成終了。");
    return p;
}

GgafDxModelManager::~GgafDxModelManager() {
    _TRACE3_("start-->");
    GGAF_RELEASE(_pID3DXFile_sprx);
    GGAF_RELEASE(_pID3DXFile_psprx);
    GGAF_DELETE(_pModelTextureManager);
    _TRACE3_("するけども、ここでは既に何も解放するものがないはずです");
    releaseAll();
}

void GgafDxModelManager::restoreAll() {
    _TRACE3_("start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
    _TRACE3_("restoreAll pCurrent="<<pCurrent);
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void GgafDxModelManager::onDeviceLostAll() {
    _TRACE3_("start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
    _TRACE3_("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent) {
        _TRACE_(FUNC_NAME<<" ["<<pCurrent->peek()->_model_name<<"] onDeviceLost begin");
        pCurrent->peek()->onDeviceLost();
        _TRACE_(FUNC_NAME<<" ["<<pCurrent->peek()->_model_name<<"] onDeviceLost end");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void GgafDxModelManager::releaseAll() {
    _TRACE3_("start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
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
