
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

#include "jp/ggaf/dx/manager/ModelManager.h"

#include <d3dx9xof.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

#include "jp/ggaf/dx/God.h"
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

ModelManager::ModelManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Model> (prm_manager_name) {
    //�e�N�X�`���}�l�W���[
    _pModelTextureManager = NEW TextureManager("TextureManager");
    HRESULT hr;
    D3DXFileCreate( &_pID3DXFile_meshx );

    static const char* meshx_template =
        "xof 0303txt 0032 \n" \
        "template MeshModelDef { " \
        "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
        "   DWORD XFileNum; " \
        "   array STRING XFileNames[XFileNum]; " \
        "   DWORD DrawSetNum; " \
        "   array FLOAT BaseTransformMatrix[16]; " \
        "}\n";
    hr = _pID3DXFile_meshx->RegisterTemplates(meshx_template, (DWORD)(strlen(meshx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplates�Ɏ��s���܂����Bmeshx_template ���m�F���ĉ������B");
    }
#endif

    //�|���S�����f����`�t�@�C��(�g���qsprx)�̃t�H�[�}�b�g��`
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
        "   DWORD  DrawSetNum; " \
        "}\n";
    hr = _pID3DXFile_sprx->RegisterTemplates(sprx_template, (DWORD)(strlen(sprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplates�Ɏ��s���܂����Bsprx_template ���m�F���ĉ������B");
    }
#endif

    //�g����X�v���C�g��`�t�@�C��(�g���qrsprx)�̃t�H�[�}�b�g��`
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
        throwCriticalException("RegisterTemplates�Ɏ��s���܂����Bfsprx_template ���m�F���ĉ������B");
    }
#endif

    //���p�`�X�v���C�g��`�t�@�C��(�g���qrsprx)�̃t�H�[�}�b�g��`
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
        "   array FLOAT BaseTransformMatrix[16]; " \
        "}\n";
    hr = _pID3DXFile_rsprx->RegisterTemplates(rsprx_template, (DWORD)(strlen(rsprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplates�Ɏ��s���܂����Brsprx_template ���m�F���ĉ������B");
    }
#endif

    //�|�C���g�X�v���C�g��`�t�@�C��(�g���qpsprx)�̃t�H�[�}�b�g��`
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
            "  DWORD  DrawSetNum;\n" \
            "  array  FLOAT     BaseTransformMatrix[16];\n" \
            "}\n" \
            "\n";
    hr = _pID3DXFile_psprx->RegisterTemplates(psprx_template, (DWORD)(strlen(psprx_template)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwCriticalException("RegisterTemplates�Ɏ��s���܂����Bpsprx_template ���m�F���ĉ������B");
    }
#endif
}

Model* ModelManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1); //�ŏ��̃X���b�V���ŕ���
    if (names.size() != 2) {
        throwCriticalException("�����́A��Ɏ��̌`���ŗ^���Ă��������B�w���f���^�C�v1����  + \",\" + ���f����`��(�g���q .x ������������)�x\n"
                "���ۂ̈����́Aprm_idstr="<<prm_idstr);
    }
    char model_type = (names[0])[0];
    const char* model_id = names[1].c_str();
    Model* pResourceModel;
    switch (model_type) {
        case TYPE_D3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_id, D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_DYNAD3DXMESH_MODEL:
            pResourceModel = createD3DXMeshModel(model_id, D3DXMESH_DYNAMIC);
            break;
        case TYPE_D3DXANIMESH_MODEL:
            pResourceModel = createModel<D3DXAniMeshModel>(model_id);
            break;
        case TYPE_MESH_MODEL:
            pResourceModel = createModel<MeshModel>(model_id);
            break;
        case TYPE_MESHSET_MODEL:
            pResourceModel = createModel<MeshSetModel>(model_id);
            break;
        case TYPE_MASSMESH_MODEL:
            pResourceModel = createModel<MassMeshModel>(model_id);
            break;
        case TYPE_CUBEMAPMESH_MODEL:
            pResourceModel = createModel<CubeMapMeshModel>(model_id);
            break;
        case TYPE_CUBEMAPMESHSET_MODEL:
            pResourceModel = createModel<CubeMapMeshSetModel>(model_id);
            break;
        case TYPE_MORPHMESH_MODEL:
            // "M,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<MorphMeshModel>(model_id);
            break;
        case TYPE_MASSMORPHMESH_MODEL:
            //"m,4,xxxxx_2" �̏ꍇ�A�Z�b�g���S�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����2�Ƃ����Ӗ�
            pResourceModel = createModel<MassMorphMeshModel>(model_id);
            break;
        case TYPE_CUBEMAPMORPHMESH_MODEL:
            //"H,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<CubeMapMorphMeshModel>(model_id);
            break;
        case TYPE_WORLDBOUND_MODEL:
            // "W,xxxxx_4" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createModel<WorldBoundModel>(model_id);
            break;
        case TYPE_ACTOR_MODEL:
            pResourceModel = createModel<SpriteModel>(model_id);
            break;
        case TYPE_SPRITESET_MODEL:
            pResourceModel = createModel<SpriteSetModel>(model_id);
            break;
        case TYPE_MASSACTOR_MODEL:
            pResourceModel = createModel<MassSpriteModel>(model_id);
            break;
        case TYPE_BOARD_MODEL:
            pResourceModel = createModel<BoardModel>(model_id);
            break;
        case TYPE_BOARDSET_MODEL:
            pResourceModel = createModel<BoardSetModel>(model_id);
            break;
        case TYPE_MASSBOARD_MODEL:
            pResourceModel = createModel<MassBoardModel>(model_id);
            break;
        case TYPE_CUBE_MODEL:
            pResourceModel = createD3DXMeshModel(const_cast<char*>("cube"), D3DXMESH_SYSTEMMEM);
            break;
        case TYPE_POINTSPRITE_MODEL:
            pResourceModel = createModel<PointSpriteModel>(model_id);
            break;
        case TYPE_MASSPOINTACTOR_MODEL:
            pResourceModel = createModel<MassPointSpriteModel>(model_id);
            break;
        case TYPE_POINTSPRITESET_MODEL:
            pResourceModel = createModel<PointSpriteSetModel>(model_id);
            break;
        case TYPE_FRAMEDBOARD_MODEL:
            pResourceModel = createModel<FramedBoardModel>(model_id);
            break;
        case TYPE_REGULARPOLYGONACTOR_MODEL:
            pResourceModel = createModel<RegularPolygonSpriteModel>(model_id);
            break;
        case TYPE_REGULARPOLYGONBOARD_MODEL:
            pResourceModel = createModel<RegularPolygonBoardModel>(model_id);
            break;
        case TYPE_BONEANIMESH_MODEL:
            pResourceModel = createModel<BoneAniMeshModel>(model_id);
            break;
        case TYPE_SKINANIMESH_MODEL:
            pResourceModel = createModel<SkinAniMeshModel>(model_id);
            break;
        default:
            throwCriticalException("prm_idstr="<<prm_idstr<<" �� '"<<model_type<<"' �E�E�E����ȃ��f����ʂ͒m��܂���");
            pResourceModel = nullptr;
            break;
    }
    return pResourceModel;
}

template <typename T>
T* ModelManager::createModel(const char* prm_model_id) {
    T* pModel_new = NEW T(prm_model_id);
    pModel_new->restore();
    return pModel_new;
}

D3DXMeshModel* ModelManager::createD3DXMeshModel(const char* prm_model_id, DWORD prm_dwOptions) {
    D3DXMeshModel* pD3DXMeshModel_new = NEW D3DXMeshModel(prm_model_id, prm_dwOptions);
    pD3DXMeshModel_new->restore();
    return pD3DXMeshModel_new;
}


void ModelManager::obtainMeshModelInfo(MeshXFileFmt* prm_pMeshXFileFmt_out, std::string prm_meshx_filepath) {
    _TRACE_("ModelManager::obtainMeshModelInfo() prm_meshx_filepath="<<prm_meshx_filepath);
    //    "xof 0303txt 0032 \n" \
    //    "template MeshModelDef { " \
    //    "   <02ED1962-4073-44FB-9BC3-BFC40F8BC537> " \
    //    "   DWORD XFileNum; " \
    //    "   array STRING XFileNames[XFileNum]; " \
    //    "   DWORD DrawSetNum; " \
    //    "   array FLOAT BaseTransformMatrix[16]; " \
    //    "}\n";

    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_meshx->CreateEnumObject(
                                     (void*)prm_meshx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainMeshModelInfo() '"<<prm_meshx_filepath<<"' ��CreateEnumObject�Ɏ��s���܂����Bmeshx�t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //���[�v���Ă��邪�Achild �͈�����ł��B
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainMeshModelInfo() "<<prm_meshx_filepath<<" �̃t�H�[�}�b�g�G���[�B MeshModelDef { ... }  �� MeshModelDef ��������Ȃ��ł��B");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainMeshModelInfo() "<<prm_meshx_filepath<<" �̃t�H�[�}�b�g�G���[�B");
    }
    memcpy(&(prm_pMeshXFileFmt_out->XFileNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    int xfile_num = prm_pMeshXFileFmt_out->XFileNum;
    prm_pMeshXFileFmt_out->XFileNames = NEW std::string[xfile_num];
    char tmp_filename[256];
    for (int i = 0; i < xfile_num; i++) {
        strcpy(tmp_filename, pXData);
        size_t len = strlen(tmp_filename);
        pXData += sizeof(char) * len;
        pXData += sizeof(char); // '\0'
        prm_pMeshXFileFmt_out->XFileNames[i] = std::string(tmp_filename);
    }
    memcpy(&(prm_pMeshXFileFmt_out->DrawSetNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
    FLOAT aMat[16];
    memcpy(aMat, pXData, sizeof(FLOAT)*16);
    pXData += sizeof(FLOAT)*16;
    prm_pMeshXFileFmt_out->BaseTransformMatrix._11 = aMat[0];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._12 = aMat[1];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._13 = aMat[2];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._14 = aMat[3];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._21 = aMat[4];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._22 = aMat[5];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._23 = aMat[6];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._24 = aMat[7];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._31 = aMat[8];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._32 = aMat[9];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._33 = aMat[10];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._34 = aMat[11];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._41 = aMat[12];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._42 = aMat[13];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._43 = aMat[14];
    prm_pMeshXFileFmt_out->BaseTransformMatrix._44 = aMat[15];

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}
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
    //    "}\n";
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_sprx->CreateEnumObject(
                                     (void*)prm_sprx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainSpriteModelInfo() '"<<prm_sprx_filepath<<"' ��CreateEnumObject�Ɏ��s���܂����Bsprx�t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");
    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //���[�v���Ă��邪�Achild �͈�����ł��B
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainSpriteModelInfo() "<<prm_sprx_filepath<<" �̃t�H�[�}�b�g�G���[�B SpriteModelDef { ... }  �� SpriteModelDef ��������Ȃ��ł��B");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainSpriteModelInfo() "<<prm_sprx_filepath<<" �̃t�H�[�}�b�g�G���[�B");
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
    memcpy(&(prm_pSpriteFmt_out->DrawSetNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);
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
    checkDxException(hr, S_OK, "ModelManager::obtainFramedSpriteModelInfo() '"<<prm_fsprx_filepath<<"' ��CreateEnumObject�Ɏ��s���܂����Bfsprx�t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");
    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //���[�v���Ă��邪�Achild �͈�����ł��B
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainFramedSpriteModelInfo() "<<prm_fsprx_filepath<<" �̃t�H�[�}�b�g�G���[�B FramedSpriteModelDef { ... }  �� FramedSpriteModelDef ��������Ȃ��ł��B");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainFramedSpriteModelInfo() "<<prm_fsprx_filepath<<" �̃t�H�[�}�b�g�G���[�B");
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
    //    "   array FLOAT BaseTransformMatrix[16]; " \
    //    "}\n";
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    HRESULT hr = _pID3DXFile_rsprx->CreateEnumObject(
                                     (void*)prm_rsprx_filepath.c_str(),
                                     D3DXF_FILELOAD_FROMFILE,
                                     &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainRegPolySpriteModelInfo() '"<<prm_rsprx_filepath<<"' ��CreateEnumObject�Ɏ��s���܂����Brsprx�t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");
    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    ID3DXFileData* pID3DXFileData = nullptr;
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    } //���[�v���Ă��邪�Achild �͈�����ł��B
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainRegPolySpriteModelInfo() "<<prm_rsprx_filepath<<" �̃t�H�[�}�b�g�G���[�B RegularPolygonModelDef { ... }  �� RegularPolygonModelDef ��������Ȃ��ł��B");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainRegPolySpriteModelInfo() "<<prm_rsprx_filepath<<" �̃t�H�[�}�b�g�G���[�B");
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

    FLOAT aMat[16];
    memcpy(aMat, pXData, sizeof(FLOAT)*16);
    pXData += sizeof(FLOAT)*16;
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._11 = aMat[0];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._12 = aMat[1];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._13 = aMat[2];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._14 = aMat[3];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._21 = aMat[4];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._22 = aMat[5];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._23 = aMat[6];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._24 = aMat[7];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._31 = aMat[8];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._32 = aMat[9];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._33 = aMat[10];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._34 = aMat[11];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._41 = aMat[12];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._42 = aMat[13];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._43 = aMat[14];
    prm_pRegPolySpriteFmt_out->BaseTransformMatrix._44 = aMat[15];

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
    //    "  DWORD  DrawSetNum;\n" \
    //    "  array  FLOAT     BaseTransformMatrix[16];\n" \
    //    "}\n" \
    //    "\n";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData = nullptr;
    HRESULT hr = _pID3DXFile_psprx->CreateEnumObject((void*)prm_psprx_filepath.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "ModelManager::obtainPointSpriteModelInfo() '"<<prm_psprx_filepath<<"' ��CreateEnumObject�Ɏ��s���܂����Bpsprx �t�@�C���̃t�H�[�}�b�g���m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for (SIZE_T childCount = 0; childCount < nChildren; childCount++) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }
    if (pID3DXFileData == nullptr) {
        throwCriticalException("ModelManager::obtainPointSpriteModelInfo() "<<prm_psprx_filepath<<" �̃t�H�[�}�b�g�G���[�B PointSpriteModelDef { ... }  �� PointSpriteModelDef ��������Ȃ��ł��B");
    }
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwCriticalException("ModelManager::obtainPointSpriteModelInfo() "<<prm_psprx_filepath<<" �̃t�H�[�}�b�g�G���[�B");
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
    //"  DWORD  DrawSetNum; "
    memcpy(&(prm_pPointSpriteFmt_out->DrawSetNum), pXData, sizeof(DWORD));
    pXData += sizeof(DWORD);

    FLOAT aMat[16];
    memcpy(aMat, pXData, sizeof(FLOAT)*16);
    pXData += sizeof(FLOAT)*16;
    prm_pPointSpriteFmt_out->BaseTransformMatrix._11 = aMat[0];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._12 = aMat[1];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._13 = aMat[2];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._14 = aMat[3];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._21 = aMat[4];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._22 = aMat[5];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._23 = aMat[6];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._24 = aMat[7];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._31 = aMat[8];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._32 = aMat[9];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._33 = aMat[10];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._34 = aMat[11];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._41 = aMat[12];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._42 = aMat[13];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._43 = aMat[14];
    prm_pPointSpriteFmt_out->BaseTransformMatrix._44 = aMat[15];

    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

GgafCore::ResourceConnection<Model>* ModelManager::processCreateConnection(const char* prm_idstr, Model* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    ModelConnection* p = NEW ModelConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return p;
}

ModelManager::~ModelManager() {
    _TRACE3_("start-->");
    GGAF_RELEASE(_pID3DXFile_sprx);
    GGAF_RELEASE(_pID3DXFile_psprx);
    GGAF_RELEASE(_pID3DXFile_fsprx);
    GGAF_RELEASE(_pID3DXFile_rsprx);
    GGAF_DELETE(_pModelTextureManager);
    _TRACE3_("���邯�ǂ��A�����ł͊��ɉ������������̂��Ȃ��͂��ł�");
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
