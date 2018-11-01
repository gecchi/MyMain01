
// �{�v���O������ Paul Coppens ����̍쐬���ꂽ�AX�t�@�C����ǂݍ��ރT���v��
// �����ɁA�Ǝ��ɉ��ǏC���i��f�o�b�O�j�����N���X���g�p���Ă��܂��B
// ���肪�Ƃ� Paul����B
//
// �y�Ώہz
// Frm ���O��Ԃ̃N���X
//
// �yLoading and displaying .X files without DirectX �z
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
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonBoardModel.h"
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
    //�e�N�X�`���}�l�W���[
    _pModelTextureManager = NEW GgafDxTextureManager("GgafDxTextureManager");

    //�|���S�����f����`�t�@�C��(�g���qsprx)�̃t�H�[�}�b�g��`
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
        throwGgafCriticalException("RegisterTemplates�Ɏ��s���܂����Bsprite_model_xfile_template ���m�F���ĉ������B");
    }
#endif

    //�|�C���g�X�v���C�g��`�t�@�C��(�g���qpsprx)�̃t�H�[�}�b�g��`
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
        throwGgafCriticalException("RegisterTemplates�Ɏ��s���܂����B\""<<CONFIG::DIR_SPRITE_MODEL[0]<<"ggaf_pointspritemodel_define.x\"���m�F���ĉ������B");
    }
#endif
}

GgafDxModel* GgafDxModelManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //�ŏ��̃X���b�V���ŕ���
    if (names.size() != 2) {
        throwGgafCriticalException("�����́A��Ɏ��̌`���ŗ^���Ă��������B�w���f���^�C�v1����  + \",\" + ���f����`��(�g���q .x ������������)�x\n"
                "���ۂ̈����́Aprm_idstr="<<prm_idstr);
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
            pResourceModel = createModel<GgafDxD3DXAniMeshModel>(model_name);
            break;
        case TYPE_MESH_MODEL:
            pResourceModel = createModel<GgafDxMeshModel>(model_name);
            break;
        case TYPE_MESHSET_MODEL:
            pResourceModel = createModel<GgafDxMeshSetModel>(model_name);
            break;
        case TYPE_MASSMESH_MODEL:
            pResourceModel = createModel<GgafDxMassMeshModel>(model_name);
            break;
        case TYPE_CUBEMAPMESH_MODEL:
            pResourceModel = createModel<GgafDxCubeMapMeshModel>(model_name);
            break;
        case TYPE_CUBEMAPMESHSET_MODEL:
            pResourceModel = createModel<GgafDxCubeMapMeshSetModel>(model_name);
            break;
        case TYPE_MORPHMESH_MODEL:
            // "M,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<GgafDxMorphMeshModel>(model_name);
            break;
        case TYPE_MASSMORPHMESH_MODEL:
            //"m,4,xxxxx_2" �̏ꍇ�A�Z�b�g���S�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����2�Ƃ����Ӗ�
            pResourceModel = createModel<GgafDxMassMorphMeshModel>(model_name);
            break;
        case TYPE_CUBEMAPMORPHMESH_MODEL:
            //"H,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<GgafDxCubeMapMorphMeshModel>(model_name);
            break;
        case TYPE_WORLDBOUND_MODEL:
            // "W,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<GgafDxWorldBoundModel>(model_name);
            break;
        case TYPE_SPRITE_MODEL:
            pResourceModel = createModel<GgafDxSpriteModel>(model_name);
            break;
        case TYPE_SPRITESET_MODEL:
            pResourceModel = createModel<GgafDxSpriteSetModel>(model_name);
            break;
        case TYPE_MASSSPRITE_MODEL:
            pResourceModel = createModel<GgafDxMassSpriteModel>(model_name);
            break;
        case TYPE_BOARD_MODEL:
            pResourceModel = createModel<GgafDxBoardModel>(model_name);
            break;
        case TYPE_BOARDSET_MODEL:
            pResourceModel = createModel<GgafDxBoardSetModel>(model_name);
            break;
        case TYPE_MASSBOARD_MODEL:
            pResourceModel = createModel<GgafDxMassBoardModel>(model_name);
            break;
        case TYPE_CUBE_MODEL:
            pResourceModel = createD3DXMeshModel(const_cast<char*>("cube"), D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_POINTSPRITE_MODEL:
            pResourceModel = createModel<GgafDxPointSpriteModel>(model_name);
            break;
        case TYPE_MASSPOINTSPRITE_MODEL:
            pResourceModel = createModel<GgafDxMassPointSpriteModel>(model_name);
            break;
        case TYPE_POINTSPRITESET_MODEL:
            pResourceModel = createModel<GgafDxPointSpriteSetModel>(model_name);
            break;
        case TYPE_FRAMEDBOARD_MODEL:
            pResourceModel = createModel<GgafDxFramedBoardModel>(model_name);
            break;
        case TYPE_REGULARPOLYGONSPRITE_MODEL:
            pResourceModel = createModel<GgafDxRegularPolygonSpriteModel>(model_name);
            break;
        case TYPE_REGULARPOLYGONBOARD_MODEL:
            pResourceModel = createModel<GgafDxRegularPolygonBoardModel>(model_name);
            break;
        default:
            throwGgafCriticalException("prm_idstr="<<prm_idstr<<" �� '"<<model_type<<"' �E�E�E����ȃ��f����ʂ͒m��܂���");
            pResourceModel = nullptr;
            break;
    }
    return pResourceModel;
}

template <typename T>
T* GgafDxModelManager::createModel(const char* prm_model_name) {
    T* pModel_new = NEW T(prm_model_name);
    pModel_new->restore();
    return pModel_new;
}

GgafDxD3DXMeshModel* GgafDxModelManager::createD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions) {
    GgafDxD3DXMeshModel* pD3DXMeshModel_new = NEW GgafDxD3DXMeshModel(prm_model_name, prm_dwOptions);
    pD3DXMeshModel_new->restore();
    return pD3DXMeshModel_new;
}

std::string GgafDxModelManager::getMeshFileName(std::string prm_model_name) {
    std::string xfile_name = CONFIG::DIR_MESH_MODEL[2] + "/" + prm_model_name + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�
    UTIL::strReplace(xfile_name, "//", "/");
    _TRACE_("1 xfile_name.c_str()="<<xfile_name.c_str());
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name; //�J�����g�ɑ��݂���΂����D��
    } else {
        xfile_name = CONFIG::DIR_MESH_MODEL[1] + "/" + prm_model_name+ ".x";
        UTIL::strReplace(xfile_name, "//", "/");
        _TRACE_("2 xfile_name.c_str()="<<xfile_name.c_str());
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name; //���[�U�[�X�L���ɑ��݂���΂����D��
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
            return xfile_name; //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            xfile_name = CONFIG::DIR_SPRITE_MODEL[0] + "/" +  prm_model_name + "." + prm_ext;
            UTIL::strReplace(xfile_name, "//", "/");
            if (PathFileExists(xfile_name.c_str()) ) {
                return xfile_name;
            } else {
                throwGgafCriticalException("�X�v���C�g���f����`�t�@�C����������܂���Bxfile_name="<<xfile_name);
            }
        }
    }
}

void GgafDxModelManager::obtainSpriteInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprite_x_filename) {
    //�X�v���C�g���Ǎ���
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
    checkDxException(hr, S_OK, "'"<<prm_sprite_x_filename<<"' ��CreateEnumObject�Ɏ��s���܂����Bsprx�t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");
    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //���[�v���Ă��邪�Achild �͈�����ł��B
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException(prm_sprite_x_filename<<" �̃t�H�[�}�b�g�G���[�B");
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
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData = nullptr;
    HRESULT hr = _pID3DXFile_psprx->CreateEnumObject((void*)prm_point_sprite_x_filename.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "'"<<prm_point_sprite_x_filename<<"' ��CreateEnumObject�Ɏ��s���܂����Bpsprx �t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException(prm_point_sprite_x_filename<<" �̃t�H�[�}�b�g�G���[�B");
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
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxModelConnection* p = NEW GgafDxModelConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return p;
}

GgafDxModelManager::~GgafDxModelManager() {
    _TRACE3_("start-->");
    GGAF_RELEASE(_pID3DXFile_sprx);
    GGAF_RELEASE(_pID3DXFile_psprx);
    GGAF_DELETE(_pModelTextureManager);
    _TRACE3_("���邯�ǂ��A�����ł͊��ɉ������������̂��Ȃ��͂��ł�");
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



//�u�o�܃����i�O�`�j 2009/07/05�v
//�V�F�[�_�[�ɋ������킫�A�׋����d�n�߂Ă������AD3DXLoadMeshFromX �œǂݍ��ނƏ���ɒ��_�o�b�t�@�����鎞�����鎖�ɋC�����ĔY��ł����B
//D3DXLoadMeshFromX ��X�t�@�C����ǂݍ��ނƎv�����ʂ�̒��_���i���_�C���f�b�N�X�j�ɂȂ�ۏ؂������B
//�Ⴆ�ΎO�p�`�|���S���ł�BOX�̏ꍇ�A���_8�A���_�C���f�b�N�X12(*3)�i�ʂ�12�j�A�@���x�N�g��6�A�@���C���f�b�N�X12(*3)�A�ƂȂ邪�A
//���̂悤��X�t�@�C�����e�L�X�g�G�f�B�^�ō���� D3DXLoadMeshFromX �œǂݍ��ނƒ��_��24�ɂȂ��Ă��܂��i�Ǝv���j�B
//����́AX�t�@�C���ł͖@����ʂɕR���Ď��������Ӗ������̃f�[�^���쐬�ł���ɂ�������炸�ADIRECTX���ł͖@�������e���_�Ɏ������邽�߁A
//���_��8�ł͖{���͖ʒP�ʂł���n�Y�̖@�����\���ł��Ȃ��Ȃ��Ă��܂����߂Ɨ\�z�ł���B
//���́u�\�z�v���u�d�l�v�ɒu��������Ȃ��Ƃ��낾�����B
//�e��(�s�e��)�ɂ� D3DXLoadMeshFromX ���� ID3DXMesh �\�z���A�ʂƖʂ̉A�e�𐳂������邽�߁A�܂�G�b�W���N�b�L�������邽��
//�@�������_���D�悳��āA���_�̗אڂ���ʂ̐��i�@�����j���A���_�𑝂₷�A�Ƃ�������������ɍs����̂ł��낤�B
//�������A�V�F�[�_�[�ł̃��[�t����A�����I�u�W�F�N�g��DrawIndexedPrimitive�ł킯�ĕ\�����鎞���A
//����ɒ��_�̐����ς���Ă��܂��Ă͍���Ƃ������Ƃ�����悤�ɂȂ����B
//�u�����Ō��߂����_���Œ��_�o�b�t�@����肽���B�v�Ƃ����A��{�I�Ȃ��Ƃ��o���Ȃ����ߎ��s���낵���B
//���_�́A�@���������_����X�t�@�C�����쐬����΂����̂ł��邪�A����Ȏ��C�ɂ��ă��f�����O����Ă��Ȃ��B
//D3DXLoadMeshFromX �̃��b�V���œK���Ȃǂ̋L���͂���B�������A�m�肽���͓̂����A���S���Y���u�S�āv�ł���B
//D3DXLoadMeshFromX �̃\�[�X�R�[�h��������Ή�������̂����A���R���J�Ȃ�Ă���Ė����B
//����Ȃ킯�ŁA�����ŉ�����Ă邩�����ɂ͂킩��Ȃ��B�Ȃ�� D3DXLoadMeshFromX �͎g���Ȃ��̂��H�B�Ƃ������_�ɍs�������B
//�܂�V�F�[�_�[�����ʓI�Ɏg���ɂ͓Ǝ���X�t�@�C����ǂݍ��ނ����Ȃ��̂��ȁA�߂�ǂ������Ȃ��A�ł��������Ȃ��̂��B�����������@�́H
//�v�́A�u���_�v�u�@���v�u�}�e���A���v�uUV�v�u�K�v�ȑ��̏��v��ǂ߂�΂������낤�A�Ȃ�΂Ȃ�ł���������Ȃ����B
//X�t�@�C���Ȃ�āA�߂�ǂ������t�H�[�}�b�g����Ȃ��Ă��E�E�E�Ƃ�����X�t�@�C�����Ăނ��뉽���H�I�A�Ƃ����������񂾂�����Ă����B
//������ D3DXLoadMeshFromX ���u�g���Ȃ��v�ƌ��_�t����܂ł̊��Ԃ������������A�ŁA����X�t�@�C���}�X�^�[�ɂȂ��Ă����B
//�����ŁA���������Ȃ̂�X�t�@�C�����烂�f������ǂޏ�����Ǝ��ɍ�낤�ƌ��߂��̂������B
//�Ƃ肠�����A���^�Z�R�C�A�A3DSMAX�̃G�N�X�|�[�g����X�t�@�C���́u�ÓI�v���f�����ǂݍ��߂�Ηǂ����ȁA�V���[�e�B���O�̃L���������B�Ƃ����l���ō쐬�J�n�B
//�����Ă��΂炭���� Paul ����̃T���v���R�[�h�𔭌�����Bhttp://www.gamedev.net/reference/programming/features/xfilepc/
//�uLoading and displaying .X files without DirectX�v���ƁI�B�Ȃ�ăh���s�V���ȃg�s�b�N�Ȃ񂾁B�Ƃ����킯�ō̗p����B
//���������̃T���v���́A���\���l���ȓ_�������đ�ς������B�ł��O��������̓}�V�ŁA�׋��ɂ��Ȃ����̂ŗǂ��Ƃ��悤�B�iGCC��VC�̋������Ƃ��j
//�l����Β��_�������O�œǂ݁A�Ǘ����鎖�́A������K���ʂ铹�������낤�B�����A���ꎊ��܂ł̎��Ԃ�������߂��������B
//�����̑g�ݍ��퐔�Ƃ��v����g���C�A���h�G���[�ŁA�Q�[������肽���Ƃ�����M���ł��ӂ��ꂻ�����B���܂��Ă��I�J�V�N�i�C�B
//���̂�����̎����āA���̓��j�v���O���}�̐l�B�͂��������ǂ�����Ă�̂��낤���H�A�݂�ȔY��łȂ��̂��Ȃ��B
//�i�E�E�E��������������́A�܂��ق�̏��͂ɉ߂��Ȃ������I�i�΁j�j
