
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

#include "stdafx.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"

#include <Shlwapi.h>
#include <d3dx9xof.h>
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxD3DXAniMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteModel.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMeshSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardModel.h"
#include "jp/ggaf/dxcore/model/GgafDxBoardSetModel.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteModel.h"
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

int GgafDxModelManager::_id_max = 0;
GgafDxModel* GgafDxModelManager::_pModelLastDraw = nullptr;
GgafDxModelManager::GgafDxModelManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxModel> (prm_manager_name) {

    //�e�N�X�`���}�l�W���[
    _pModelTextureManager = NEW GgafDxTextureManager("GgafDxTextureManager");
    //�|���S�����f����`�t�@�C��(�g���qsprx)�̃t�H�[�}�b�g��`
    HRESULT hr;
    D3DXFileCreate( &_pID3DXFile_sprx );
    const char* paChar_SpriteModelineTemplate =
    "xof 0303txt 0032\n" \
    "template SpriteDef {" \
    "   <E4EECE4C-E106-11DC-9B62-346D55D89593>" \
    "   FLOAT  Width;" \
    "   FLOAT  Height;" \
    "   STRING TextureFile;" \
    "   DWORD  TextureSplitRows;" \
    "   DWORD  TextureSplitCols;" \
    "}";

    hr = _pID3DXFile_sprx->RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwGgafCriticalException("[GgafDxModelManager::GgafDxModelManager] RegisterTemplates�Ɏ��s���܂����BpaChar_SpriteModelineTemplate ���m�F���ĉ������B");
    }
#endif

    //�|�C���g�X�v���C�g��`�t�@�C��(�g���qpsprx)�̃t�H�[�}�b�g��`
    D3DXFileCreate( &_pID3DXFile_psprx );
    const char* paChar_PointSpriteModelineTemplate =
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
    hr = _pID3DXFile_psprx->RegisterTemplates(paChar_PointSpriteModelineTemplate, (DWORD)(strlen(paChar_PointSpriteModelineTemplate)));
#ifdef MY_DEBUG
    if(hr != S_OK) {
        throwGgafCriticalException("[GgafDxModelManager::GgafDxModelManager] RegisterTemplates�Ɏ��s���܂����B\""<<PROPERTY::DIR_SPRITE_MODEL[0]<<"ggaf_pointspritemodel_define.x\"���m�F���ĉ������B");
    }
#endif
}

GgafDxModel* GgafDxModelManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    //�U�蕪��
    char model_type = *prm_idstr; //���ꕶ��
    char* model_name = prm_idstr + 2; //�R�����ڈȍ~
    GgafDxModel* pResourceModel;
    switch (model_type) {
        case 'D':
            //D3DXMeshModel
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_SYSTEMMEM);
            break;
        case 'd':
            //DynaD3DXMeshModel
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_DYNAMIC);
            break;
        case 'A':
            //D3DXAniMeshModel
            pResourceModel = createD3DXAniMeshModel(model_name);
            break;
        case 'X':
            //MeshModel
            pResourceModel = createMeshModel(model_name);
            break;
        case 'x':
            //MeshSetModel
            pResourceModel = createMeshSetModel(model_name);
            break;
        case 'G':
            //CubeMapMeshModel
            pResourceModel = createCubeMapMeshModel(model_name);
            break;
        case 'g':
            //CubeMapMeshSetModel
            pResourceModel = createCubeMapMeshSetModel(model_name);
            break;
        case 'M':
            //MorphMeshModel "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createMorphMeshModel(model_name);
            break;
        case 'H':
            //CubeMapMorphMeshModel "H/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createCubeMapMorphMeshModel(model_name);
            break;
        case 'W':
            //WorldBoundModel "W/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
            pResourceModel = createWorldBoundModel(model_name);
            break;
        case 'S':
            //SpriteModel
            pResourceModel = createSpriteModel(model_name);
            break;
        case 's':
            //SpriteSetModel
            pResourceModel = createSpriteSetModel(model_name);
            break;
        case 'B':
            //BoardModel
            pResourceModel = createBoardModel(model_name);
            break;
        case 'b':
            //BoardSetModel
            pResourceModel = createBoardSetModel(model_name);
            break;
        case 'C':
            //cubeModel
            pResourceModel = createD3DXMeshModel(const_cast<char*>("cube"), D3DXMESH_SYSTEMMEM);
            break;
        case 'P':
            //PointSpriteModel
            pResourceModel = createPointSpriteModel(model_name);
            break;
        default:
            TRACE3("GgafDxModelManager::processCreateResource("<<prm_idstr<<") ����Ȏ�ʂ͂���܂���");
            throwGgafCriticalException("GgafDxModelManager::processCreateResource("<<prm_idstr<<") ����ȃ��f����ʂ͒m��܂���");
            pResourceModel = nullptr;
            break;
    }
    return pResourceModel;
}

GgafDxD3DXMeshModel* GgafDxModelManager::createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) {
    GgafDxD3DXMeshModel* pD3DXMeshModel_New = NEW GgafDxD3DXMeshModel(prm_model_name, prm_dwOptions);
    restoreD3DXMeshModel(pD3DXMeshModel_New);
    return pD3DXMeshModel_New;
}

GgafDxD3DXAniMeshModel* GgafDxModelManager::createD3DXAniMeshModel(char* prm_model_name) {
    GgafDxD3DXAniMeshModel* pD3DXAniMeshModel_New = NEW GgafDxD3DXAniMeshModel(prm_model_name);
    restoreD3DXAniMeshModel(pD3DXAniMeshModel_New);
    return pD3DXAniMeshModel_New;
}

GgafDxSpriteModel* GgafDxModelManager::createSpriteModel(char* prm_model_name) {
    GgafDxSpriteModel* pSpriteModel_New = NEW GgafDxSpriteModel(prm_model_name);
    restoreSpriteModel(pSpriteModel_New);
    return pSpriteModel_New;
}

GgafDxSpriteSetModel* GgafDxModelManager::createSpriteSetModel(char* prm_model_name) {
    GgafDxSpriteSetModel* pSpriteSetModel_New = NEW GgafDxSpriteSetModel(prm_model_name);
    restoreSpriteSetModel(pSpriteSetModel_New);
    return pSpriteSetModel_New;
}

GgafDxBoardModel* GgafDxModelManager::createBoardModel(char* prm_model_name) {
    GgafDxBoardModel* pBoardModel_New = NEW GgafDxBoardModel(prm_model_name);
    restoreBoardModel(pBoardModel_New);
    return pBoardModel_New;
}

GgafDxBoardSetModel* GgafDxModelManager::createBoardSetModel(char* prm_model_name) {
    GgafDxBoardSetModel* pBoardSetModel_New = NEW GgafDxBoardSetModel(prm_model_name);
    restoreBoardSetModel(pBoardSetModel_New);
    return pBoardSetModel_New;
}

GgafDxMeshModel* GgafDxModelManager::createMeshModel(char* prm_model_name) {
    GgafDxMeshModel* pMeshModel_New = NEW GgafDxMeshModel(prm_model_name);
    restoreMeshModel(pMeshModel_New);
    return pMeshModel_New;
}

GgafDxMeshSetModel* GgafDxModelManager::createMeshSetModel(char* prm_model_name) {
    GgafDxMeshSetModel* pMeshSetModel_New = NEW GgafDxMeshSetModel(prm_model_name);
    restoreMeshSetModel(pMeshSetModel_New);
    return pMeshSetModel_New;
}

GgafDxCubeMapMeshModel* GgafDxModelManager::createCubeMapMeshModel(char* prm_model_name) {
    GgafDxCubeMapMeshModel* pMeshCubeMapModel_New = NEW GgafDxCubeMapMeshModel(prm_model_name);
    restoreMeshModel((GgafDxMeshModel*)pMeshCubeMapModel_New);
    return pMeshCubeMapModel_New;
}

GgafDxCubeMapMeshSetModel* GgafDxModelManager::createCubeMapMeshSetModel(char* prm_model_name) {
    GgafDxCubeMapMeshSetModel* pMeshCubeMapSetModel_New = NEW GgafDxCubeMapMeshSetModel(prm_model_name);
    restoreMeshSetModel((GgafDxMeshSetModel*)pMeshCubeMapSetModel_New);
    return pMeshCubeMapSetModel_New;
}


GgafDxMorphMeshModel* GgafDxModelManager::createMorphMeshModel(char* prm_model_name) {
    // "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
    // ������prm_model_name �� "4/xxxxx" �Ƃ���������ɂȂ��Ă���B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c���B
    GgafDxMorphMeshModel* pMorphMeshModel_New = NEW GgafDxMorphMeshModel(prm_model_name);
    restoreMorphMeshModel(pMorphMeshModel_New);
    return pMorphMeshModel_New;
}

GgafDxCubeMapMorphMeshModel* GgafDxModelManager::createCubeMapMorphMeshModel(char* prm_model_name) {
    GgafDxCubeMapMorphMeshModel* pCubeMapMorphMeshModel_New = NEW GgafDxCubeMapMorphMeshModel(prm_model_name);
    restoreMorphMeshModel((GgafDxMorphMeshModel*)pCubeMapMorphMeshModel_New);
    return pCubeMapMorphMeshModel_New;
}


GgafDxWorldBoundModel* GgafDxModelManager::createWorldBoundModel(char* prm_model_name) {
    GgafDxWorldBoundModel* pWorldBoundModel_New = NEW GgafDxWorldBoundModel(prm_model_name);
    restoreMorphMeshModel((GgafDxWorldBoundModel*)pWorldBoundModel_New);
    return pWorldBoundModel_New;
}


GgafDxPointSpriteModel* GgafDxModelManager::createPointSpriteModel(char* prm_model_name) {
    GgafDxPointSpriteModel* pPointSpriteModel_New = NEW GgafDxPointSpriteModel(prm_model_name);
    restorePointSpriteModel(pPointSpriteModel_New);
    return pPointSpriteModel_New;
}
std::string GgafDxModelManager::getMeshFileName(std::string prm_model_name) {
    std::string xfile_name = PROPERTY::DIR_MESH_MODEL[2] + "/" + prm_model_name + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�
    UTIL::strReplace(xfile_name, "//", "/");
    _TRACE_("1 xfile_name.c_str()="<<xfile_name.c_str());
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name; //�J�����g�ɑ��݂���΂����D��
    } else {
        xfile_name = PROPERTY::DIR_MESH_MODEL[1] + "/" + prm_model_name+ ".x";
        UTIL::strReplace(xfile_name, "//", "/");
        _TRACE_("2 xfile_name.c_str()="<<xfile_name.c_str());
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name; //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            xfile_name = PROPERTY::DIR_MESH_MODEL[0] + "/" + prm_model_name+ ".x";
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
std::string GgafDxModelManager::getSpriteFileName(std::string prm_model_name) {
    std::string xfile_name = PROPERTY::DIR_SPRITE_MODEL[2] + "/" + prm_model_name + ".sprx";
    UTIL::strReplace(xfile_name, "//", "/");
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name;
    } else {
        xfile_name = PROPERTY::DIR_SPRITE_MODEL[1] + "/" +  prm_model_name + ".sprx";
        UTIL::strReplace(xfile_name, "//", "/");
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name; //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            xfile_name = PROPERTY::DIR_SPRITE_MODEL[0] + "/" +  prm_model_name + ".sprx";
            UTIL::strReplace(xfile_name, "//", "/");
            if (PathFileExists(xfile_name.c_str()) ) {
                return xfile_name;
            } else {
                throwGgafCriticalException("GgafDxModelManager::getSpriteFileName �X�v���C�g�t�@�C��(*.sprx)��������܂���Bxfile_name="<<xfile_name);
            }
        }
    }
}

std::string GgafDxModelManager::getPointSpriteFileName(std::string prm_model_name) {
    std::string xfile_name = PROPERTY::DIR_SPRITE_MODEL[2] + "/" + prm_model_name + ".psprx";
    UTIL::strReplace(xfile_name, "//", "/");
    if (PathFileExists(xfile_name.c_str()) ) {
        return xfile_name;
    } else {
        xfile_name = PROPERTY::DIR_SPRITE_MODEL[1] + "/" +  prm_model_name + ".psprx";
        UTIL::strReplace(xfile_name, "//", "/");
        if (PathFileExists(xfile_name.c_str()) ) {
            return xfile_name;  //���[�U�[�X�L���ɑ��݂���΂����D��
        } else {
            xfile_name = PROPERTY::DIR_SPRITE_MODEL[0] + "/" +  prm_model_name + ".psprx";
            UTIL::strReplace(xfile_name, "//", "/");
            if (PathFileExists(xfile_name.c_str()) ) {
                return xfile_name;
            } else {
                throwGgafCriticalException("GgafDxModelManager::getSpriteFileName �|�C���g�X�v���C�g�t�@�C��(*.psprx)��������܂���Bxfile_name="<<xfile_name);
            }
        }
    }
}

void GgafDxModelManager::restoreMeshModel(GgafDxMeshModel* prm_pMeshModel) {
    TRACE3("GgafDxModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //�yGgafDxMeshModel�č\�z�i���������j�����T�v�z
    //�P�j���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �� new
    //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDxMeshModel �Ɏ��̃����o���쐬�B
    //      �E���_�o�b�t�@�̎ʂ�
    //      �E���_�C���f�b�N�X�o�b�t�@�̎ʂ�
    //      �E�}�e���A���z��(�v�f�����}�e���A����)
    //      �E�e�N�X�`���z��(�v�f�����}�e���A����)
    //      �EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)


    std::string xfile_name = getMeshFileName(prm_pMeshModel->_model_name);
    if (xfile_name == "") {
        throwGgafCriticalException("GgafDxModelManager::restoreMeshModel ���b�V���t�@�C��(*.x)��������܂���B_model_name="<<prm_pMeshModel->_model_name);
    }
    HRESULT hr;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
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

    if (prm_pMeshModel->_pModel3D == nullptr) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }
        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }

        model_pModel3D->ConcatenateMeshes(); //���b�V�����q����

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices; //���b�V���A����̑����_��
        nFaces = model_pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
//        nFaceNormals = model_pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
        model_paVtxBuffer_org = NEW GgafDxMeshModel::VERTEX[nVertices];
        prm_pMeshModel->_size_vertices = sizeof(GgafDxMeshModel::VERTEX) * nVertices;
        prm_pMeshModel->_size_vertex_unit = sizeof(GgafDxMeshModel::VERTEX);
        int nTextureCoords = model_pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //���_�o�b�t�@�쐬�J�n�I
        //�@���ȊO�ݒ�
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            model_paVtxBuffer_org[i].x = model_pMeshesFront->_Vertices[i].data[0];
            model_paVtxBuffer_org[i].y = model_pMeshesFront->_Vertices[i].data[1];
            model_paVtxBuffer_org[i].z = model_pMeshesFront->_Vertices[i].data[2];
            model_paVtxBuffer_org[i].nx = 0.0f;
            model_paVtxBuffer_org[i].ny = 0.0f;
            model_paVtxBuffer_org[i].nz = 0.0f;
            model_paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                model_paVtxBuffer_org[i].tu = model_pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
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


            //����
            model_bounding_sphere_radius = (FLOAT)(sqrt(model_paVtxBuffer_org[i].x * model_paVtxBuffer_org[i].x +
                                                        model_paVtxBuffer_org[i].y * model_paVtxBuffer_org[i].y +
                                                        model_paVtxBuffer_org[i].z * model_paVtxBuffer_org[i].z));
            if (prm_pMeshModel->_bounding_sphere_radius < model_bounding_sphere_radius) {
                prm_pMeshModel->_bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        //���_�o�b�t�@�쐬
        prepareVtx((void*)model_paVtxBuffer_org, prm_pMeshModel->_size_vertex_unit,
                    model_pModel3D, paNumVertices,
                    prm_pMeshModel);

        GGAF_DELETE(paNumVertices);

        //�C���f�b�N�X�o�b�t�@�o�^
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDxMeshModel::INDEXPARAM* paParam = NEW GgafDxMeshModel::INDEXPARAM[nFaces]; //�ō��Ƀ}�e���A�����o���o���������ꍇnFaces�K�v

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
                //TRACE3("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                paParam[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
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
        prm_pMeshModel->_nMaterialListGrp = paramno;

        delete[] paParam;
    }

    if (prm_pMeshModel->_pIDirect3DVertexBuffer9 == nullptr) {

        //���_�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pMeshModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxMeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pMeshModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pMeshModel->_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pMeshModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pMeshModel->_size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pMeshModel->_model_name);
        memcpy(pVertexBuffer, model_paVtxBuffer_org, prm_pMeshModel->_size_vertices); //pVertexBuffer �� paVertex
        prm_pMeshModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMeshModel->_pIDirect3DIndexBuffer9 == nullptr) {
        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMeshModel->_pIDirect3DIndexBuffer9),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , model_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A���ݒ�
    int model_nMaterials = 0;
    setMaterial(model_pMeshesFront,
                &model_nMaterials, &model_paMaterial, &model_papTextureConnection);

    //���f���ɕێ�������
    prm_pMeshModel->_pModel3D = model_pModel3D;
    prm_pMeshModel->_pMeshesFront = model_pMeshesFront;

    prm_pMeshModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMeshModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pMeshModel->_paIndexParam = model_paIndexParam;
    prm_pMeshModel->_paMaterial_default = model_paMaterial;
    prm_pMeshModel->_papTextureConnection = model_papTextureConnection;
    prm_pMeshModel->_num_materials = model_nMaterials;


//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ nVertices="<<nVertices);
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
//            //�f�o�b�O
//            //_TRACE_("���_["<<i<<"] pos("<<x<<","<<y<<","<<z<<")\tuv("<<tu<<","<<tv<<")\tn("<<nx<<","<<ny<<","<<nz<<")\tt("<<tan_x<<","<<tan_y<<","<<tan_z<<")\tb("<<bin_x<<","<<bin_y<<","<<bin_z<<")");
//        }


//    {
//        //�f�o�b�O
//        _TRACE_("#���_�o�b�t�@ nVertices="<<nVertices);
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
//            _TRACE_("���_["<<i<<"] "<<x<<";"<<y<<";"<<z<<";,\t"<<nx<<";"<<ny<<";"<<nz<<";,\t"<<tu<<";"<<tv<<";,");
//        }
//
//
//        _TRACE_("#�C���f�b�N�X�o�b�t�@ nFaces="<<nFaces);
//        WORD vtx1,vtx2,vtx3;
//        for (int face = 0; face < nFaces; face++) {
//            vtx1 = model_paIdxBuffer_org[face*3 + 0];
//            vtx2 = model_paIdxBuffer_org[face*3 + 1];
//            vtx3 = model_paIdxBuffer_org[face*3 + 2];
//            _TRACE_("��["<<face<<"] 3;"<<vtx1<<","<<vtx2<<","<<vtx3<<";,");
//        }
//
//        _TRACE_("�}�e���A��  model_nMaterials="<<model_nMaterials);
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
//        _TRACE_("#�}�e���A�����X�g _nMaterialListGrp="<< prm_pMeshModel->_nMaterialListGrp);
//        for (UINT i = 0; i < prm_pMeshModel->_nMaterialListGrp; i++) {
//            int material_no = prm_pMeshModel->_paIndexParam[i].MaterialNo;
//            _TRACE_("MaterialGrp["<<i<<"] "<<material_no<<",");
//        }
//
//        _TRACE_("#IndexParam  _nMaterialListGrp="<< prm_pMeshModel->_nMaterialListGrp);
//        UINT MaterialNo;
//        INT BaseVertexIndex;
//        UINT MinIndex;
//        UINT NumVertices;
//        UINT StartIndex;
//        UINT PrimitiveCount;
//        for (UINT i = 0; i < prm_pMeshModel->_nMaterialListGrp; i++) {
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
}

//�}���y�P
//http://marupeke296.com/DXPS_No12_CalcTangentVectorSpace.html
//U����V�������߂�֐�
// 3���_��UV�l����w����W�ł�U���iTangent�j�y��V���iBinormal�j���Z�o
// p0, p1, p2    : ���[�J����Ԃł̒��_���W�i�|���S���`�揇�ɂ��邱�Ɓj
// uv0, uv1, uv2 : �e���_��UV���W
// outTangent    : U���iTangent�j�o��
// outBinormal   : V���iBinormal�j�o��

void GgafDxModelManager::calcTangentAndBinormal(
        D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
        D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
        D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
        D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal) {
    // 5������3�������_��
    D3DXVECTOR3 CP0[3] =
            { D3DXVECTOR3(p0->x, uv0->x, uv0->y), D3DXVECTOR3(p0->y, uv0->x, uv0->y), D3DXVECTOR3(p0->z, uv0->x, uv0->y), };
    D3DXVECTOR3 CP1[3] =
            { D3DXVECTOR3(p1->x, uv1->x, uv1->y), D3DXVECTOR3(p1->y, uv1->x, uv1->y), D3DXVECTOR3(p1->z, uv1->x, uv1->y), };
    D3DXVECTOR3 CP2[3] =
            { D3DXVECTOR3(p2->x, uv2->x, uv2->y), D3DXVECTOR3(p2->y, uv2->x, uv2->y), D3DXVECTOR3(p2->z, uv2->x, uv2->y), };

    // ���ʃp�����[�^����UV�����W�Z�o
    float U[3], V[3];
    static double lim = FLT_MAX/100.0;
    for (int i = 0; i < 3; ++i) {
        D3DXVECTOR3 V1 = CP1[i] - CP0[i];
        D3DXVECTOR3 V2 = CP2[i] - CP1[i];
        D3DXVECTOR3 VABC;
        D3DXVec3Cross(&VABC, &V1, &V2);

        if (ZEROf_EQ(VABC.x)) {
            // ��΂����I
            // �|���S����UV��̃|���S�����k�ނ��Ă܂��I
            //_TRACE_("���x���� GgafDxModelManager::calcTangentAndBinormal �|���S����UV��̃|���S�����k�ނ��Ă܂��I");
            U[i] = -SGN(VABC.y) * lim;
            V[i] = -SGN(VABC.z) * lim;
        } else {
            U[i] = -VABC.y / VABC.x;
            V[i] = -VABC.z / VABC.x;
        }
    }

    memcpy(outTangent, U, sizeof(float) * 3);
    memcpy(outBinormal, V, sizeof(float) * 3);

    // ���K�����܂�
    D3DXVec3Normalize(outTangent, outTangent);
    D3DXVec3Normalize(outBinormal, outBinormal);
}

void GgafDxModelManager::setMaterial(Frm::Mesh* in_pMeshesFront,
                                     int* pOut_material_num,
                                     D3DMATERIAL9**                pOut_paMaterial,
                                     GgafDxTextureConnection***    pOut_papTextureConnection) {

    for (std::list<Frm::Material*>::iterator material = in_pMeshesFront->_Materials.begin();
            material != in_pMeshesFront->_Materials.end(); material++) {
        (*pOut_material_num)++;
    }

    if ((*pOut_material_num) > 0) {
        (*pOut_paMaterial) = NEW D3DMATERIAL9[(*pOut_material_num)];
        (*pOut_papTextureConnection) = NEW GgafDxTextureConnection*[(*pOut_material_num)];

        char* texture_filename;
        int n = 0;
        for (std::list<Frm::Material*>::iterator material = in_pMeshesFront->_Materials.begin();
                material != in_pMeshesFront->_Materials.end(); material++) {
            (*pOut_paMaterial)[n].Diffuse.r = (*material)->_FaceColor.data[0];
            (*pOut_paMaterial)[n].Diffuse.g = (*material)->_FaceColor.data[1];
            (*pOut_paMaterial)[n].Diffuse.b = (*material)->_FaceColor.data[2];
            (*pOut_paMaterial)[n].Diffuse.a = (*material)->_FaceColor.data[3];

            (*pOut_paMaterial)[n].Ambient.r = (*material)->_FaceColor.data[0];
            (*pOut_paMaterial)[n].Ambient.g = (*material)->_FaceColor.data[1];
            (*pOut_paMaterial)[n].Ambient.b = (*material)->_FaceColor.data[2];
            (*pOut_paMaterial)[n].Ambient.a = (*material)->_FaceColor.data[3];

            (*pOut_paMaterial)[n].Specular.r = (*material)->_SpecularColor.data[0];
            (*pOut_paMaterial)[n].Specular.g = (*material)->_SpecularColor.data[1];
            (*pOut_paMaterial)[n].Specular.b = (*material)->_SpecularColor.data[2];
            (*pOut_paMaterial)[n].Specular.a = 1.000000f;
            (*pOut_paMaterial)[n].Power =  (*material)->_power;

            (*pOut_paMaterial)[n].Emissive.r = (*material)->_EmissiveColor.data[0];
            (*pOut_paMaterial)[n].Emissive.g = (*material)->_EmissiveColor.data[1];
            (*pOut_paMaterial)[n].Emissive.b = (*material)->_EmissiveColor.data[2];
            (*pOut_paMaterial)[n].Emissive.a = 1.000000f;

            texture_filename = (char*)((*material)->_TextureName.c_str());
            if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                (*pOut_papTextureConnection)[n] = (GgafDxTextureConnection*)_pModelTextureManager->connect(texture_filename, this);
            } else {
                //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                (*pOut_papTextureConnection)[n] = (GgafDxTextureConnection*)_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this);
            }
            n++;
        }
    } else {
        //�}�e���A����`���P�������̂ŁA�`��̂��߂ɖ������P�}�e���A�����쐬�B
        (*pOut_paMaterial)  = NEW D3DMATERIAL9[1];
        (*pOut_papTextureConnection) = NEW GgafDxTextureConnection*[1];
        setDefaultMaterial(&((*pOut_paMaterial)[0]));
        (*pOut_papTextureConnection)[0] = (GgafDxTextureConnection*)_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this);
        (*pOut_material_num) = 1;
    }
}

void GgafDxModelManager::setDefaultMaterial(D3DMATERIAL9* out_pD3DMATERIAL9) {
    out_pD3DMATERIAL9->Diffuse.r = 1.0f;
    out_pD3DMATERIAL9->Diffuse.g = 1.0f;
    out_pD3DMATERIAL9->Diffuse.b = 1.0f;
    out_pD3DMATERIAL9->Diffuse.a = 1.0f;

    out_pD3DMATERIAL9->Ambient.r = 1.0f;
    out_pD3DMATERIAL9->Ambient.g = 1.0f;
    out_pD3DMATERIAL9->Ambient.b = 1.0f;
    out_pD3DMATERIAL9->Ambient.a = 1.0f;

    out_pD3DMATERIAL9->Specular.r = 1.0f;
    out_pD3DMATERIAL9->Specular.g = 1.0f;
    out_pD3DMATERIAL9->Specular.b = 1.0f;
    out_pD3DMATERIAL9->Specular.a = 1.0f;
    out_pD3DMATERIAL9->Power = 0.0f;

    out_pD3DMATERIAL9->Emissive.r = 1.0f;
    out_pD3DMATERIAL9->Emissive.g = 1.0f;
    out_pD3DMATERIAL9->Emissive.b = 1.0f;
    out_pD3DMATERIAL9->Emissive.a = 1.0f;
}

void GgafDxModelManager::prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                                    Frm::Model3D* model_pModel3D,
                                    uint16_t* paNumVertices,
                                    GgafDxModel* prm_pModel) {
    //���O��
    //prm_paVtxBuffer �ɂ� x,y,z,tu,tv �͐ݒ�ς�

    Frm::Mesh* model_pMeshesFront = model_pModel3D->_Meshes.front();
    int nVertices = model_pMeshesFront->_nVertices; //���b�V���A����̑����_��
    int nFaces = model_pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
    int nFaceNormals = model_pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
    //�@���ݒ�B
    //���L���_�̖@���͕��ω������݂�I
    //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
    //���L���_�ɁA�ʂ������悤�ȕ��ʂɏW�������ꍇ�A�P���ɉ��Z���Ėʐ��Ŋ��镽�ω�������Ɩ@���͕΂��Ă��܂��B
    //�����ŁA���L���_�@���ւ̉e���x�����i���j���A���̖ʖ@������������ʂ̒��_�p�̑傫���Ō��߂�悤�ɂ����B
    //�@���̉e���x���� �� ���̖@�����������钸�_�̐����p �^ ���̒��_�ɂԂ牺����Sface�̐����p���v
    //�Ƃ����B�Ō�ɐ��K������B
    byte* paVtxBuffer = (byte*)prm_paVtxBuffer;
    float* paRad = NEW float[nFaces*3];
    float* paRadSum_Vtx = NEW float[nVertices];
    for (int v = 0; v < nVertices; v++) {
        paRadSum_Vtx[v] = 0;
    }
    std::fill_n(paRadSum_Vtx, nVertices, 0);
    unsigned short indexVertices_per_Face[3];
    unsigned short indexNormals_per_Face[3];
    for (int face_index = 0; face_index < nFaces; face_index++) {
        for (int v = 0; v < 3; v++) {
            //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            //�ʂɑ΂���@���C���f�b�N�X�R��
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //�@���������ꍇ
                indexNormals_per_Face[v] = (unsigned short)0;
            }
        }

        //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
        paRad[face_index*3+0] = getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                       );
        //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[face_index*3+0];

        //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
        paRad[face_index*3+1] = getRadv1_v0v1v2(
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                         model_pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                       );
        //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[face_index*3+1];

        //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
        paRad[face_index*3+2] = (float)(2*PI - (paRad[face_index*3+0] + paRad[face_index*3+1]));
        //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
        paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[face_index*3+2];
    }

    float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
    GgafDxModel::VERTEX_3D_BASE* pVtx;
    D3DXVECTOR3 p[3];
    D3DXVECTOR2 uv[3];
    D3DXVECTOR3 outTangent;
    D3DXVECTOR3 outBinormal;
    for (int face_index = 0; face_index < nFaces; face_index++) { //�S�|���S�������[�v
        //�|���S���i�O�p�ʁj�̒��_�C���f�b�N�X���R�i�[
        for (int v = 0; v < 3; v++) {
            indexVertices_per_Face[v] = model_pMeshesFront->_Faces[face_index].data[v];
            if (nFaceNormals > face_index) {
                indexNormals_per_Face[v] = model_pMeshesFront->_FaceNormals[face_index].data[v];
            } else {
                //�@���������ꍇ
                indexNormals_per_Face[v] = (unsigned short)0;
            }
        }
        if (nFaceNormals > face_index) {
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].x * rate);
                pVtx->ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].y * rate);
                pVtx->nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[v]].z * rate);
            }
        } else {
            //�@���������ꍇ�A�@�����v�Z���č�肾���B

            //�ʂɑ΂��钸�_�C���f�b�N�X�R��
            int indexVertices1 = model_pMeshesFront->_Faces[face_index].data[0];
            int indexVertices2 = model_pMeshesFront->_Faces[face_index].data[1];
            int indexVertices3 = model_pMeshesFront->_Faces[face_index].data[2];
            //�ʂ̒��_�R��
            D3DXVECTOR3 v1 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices1].data[0],
                model_pMeshesFront->_Vertices[indexVertices1].data[1],
                model_pMeshesFront->_Vertices[indexVertices1].data[2]
            );
            D3DXVECTOR3 v2 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices2].data[0],
                model_pMeshesFront->_Vertices[indexVertices2].data[1],
                model_pMeshesFront->_Vertices[indexVertices2].data[2]
            );
            D3DXVECTOR3 v3 = D3DXVECTOR3(
                model_pMeshesFront->_Vertices[indexVertices3].data[0],
                model_pMeshesFront->_Vertices[indexVertices3].data[1],
                model_pMeshesFront->_Vertices[indexVertices3].data[2]
            );

            D3DXPLANE Plane;
            // 3 �̓_���畽�ʂ��쐬
            D3DXPlaneFromPoints(&Plane, &v1, &v2, &v3);
            //���K����������(�@��)���Z�o
            D3DXPlaneNormalize(&Plane, &Plane);
            for (int v = 0; v < 3; v++) {
                rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                pVtx->nx += (Plane.a * rate);
                pVtx->ny += (Plane.b * rate);
                pVtx->nz += (Plane.c * rate);
            }
        }


        //���������������AU�� �ڃx�N�g���iTangent�j�y�� V�� �]�@���iBinormal�j�̕��ς��v�Z
        if (prm_pModel) {
            //���_�o�b�t�@�ɁATangent Binormal ���ߍ��ݗL��̏ꍇ
            for (int v = 0; v < 3; v++) { //p[3] �� uv[3] �Ƀp�����[�^�Z�b�g
                pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                p[v].x = pVtx->x;
                p[v].y = pVtx->y;
                p[v].z = pVtx->z;
                if (prm_pModel->_obj_model & Obj_GgafDxMeshModel) {
                    //GgafDxMeshModel�̏ꍇ
                    GgafDxMeshModel::VERTEX* pVtx_MeshModel = (GgafDxMeshModel::VERTEX*)pVtx;
                    uv[v].x = pVtx_MeshModel->tu;
                    uv[v].y = pVtx_MeshModel->tv;
                } else {
                    throwGgafCriticalException("�o���v�}�b�v��������ĂȂ��� prm_pModel="<<prm_pModel->getName()<<" _obj_model="<<prm_pModel->_obj_model);
                }
            }
            //�v�Z
            GgafDxModelManager::calcTangentAndBinormal(
                    &p[0], &uv[0],
                    &p[1], &uv[1],
                    &p[2], &uv[2],
                    &outTangent, &outBinormal); //�ʂɑ΂��� U���iTangent�j�y��V���iBinormal�j
            //���ʂ𒸓_�o�b�t�@�ɏ������݁i���ς��l���j
            for (int v = 0; v < 3; v++) {
                if (prm_pModel->_obj_model & Obj_GgafDxMeshModel) {
                    //GgafDxMeshModel�̏ꍇ
                    GgafDxMeshModel::VERTEX* pVtx_MeshModel = (GgafDxMeshModel::VERTEX*)(paVtxBuffer + (prm_size_of_vtx_unit*indexVertices_per_Face[v]));
                    rate = (paRad[face_index*3+v] / paRadSum_Vtx[indexVertices_per_Face[v]]);
                    pVtx_MeshModel->tan_x += (outTangent.x  * rate);
                    pVtx_MeshModel->tan_y += (outTangent.y  * rate);
                    pVtx_MeshModel->tan_z += (outTangent.z  * rate);
                    pVtx_MeshModel->bin_x += (outBinormal.x * rate);
                    pVtx_MeshModel->bin_y += (outBinormal.y * rate);
                    pVtx_MeshModel->bin_z += (outBinormal.z * rate);
                } else {
                    throwGgafCriticalException("�o���v�}�b�v��������ĂȂ��� prm_pModel="<<prm_pModel->getName()<<" _obj_model="<<prm_pModel->_obj_model);
                }
            }

        }

    }

    //X�t�@�C����FrameTransformMatrix(0�t���[���ڂ̏������A�j���[�V����)���l��
    int n = 0;
    int nVertices_begin = 0;
    int nVertices_end = 0;
    for (std::list<Frm::Bone*>::iterator iteBone = model_pModel3D->_toplevel_Skelettons.begin() ;
            iteBone != model_pModel3D->_toplevel_Skelettons.end(); iteBone++) {

        _TRACE_("(*iteBone)->_Name="<<((*iteBone)->_Name));

        if ((*iteBone)) {
            Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
            if (pMatPos == 0 || pMatPos== nullptr || pMatPos->isIdentity()) {
                //FrameTransformMatrix �͒P�ʍs��
                _TRACE_("FrameTransformMatrix is Identity");
            } else {
                _TRACE_("Execute FrameTransform!");
                D3DXMATRIX FrameTransformMatrix;
                FrameTransformMatrix._11 = pMatPos->data[0];
                FrameTransformMatrix._12 = pMatPos->data[1];
                FrameTransformMatrix._13 = pMatPos->data[2];
                FrameTransformMatrix._14 = pMatPos->data[3];
                FrameTransformMatrix._21 = pMatPos->data[4];
                FrameTransformMatrix._22 = pMatPos->data[5];
                FrameTransformMatrix._23 = pMatPos->data[6];
                FrameTransformMatrix._24 = pMatPos->data[7];
                FrameTransformMatrix._31 = pMatPos->data[8];
                FrameTransformMatrix._32 = pMatPos->data[9];
                FrameTransformMatrix._33 = pMatPos->data[10];
                FrameTransformMatrix._34 = pMatPos->data[11];
                FrameTransformMatrix._41 = pMatPos->data[12];
                FrameTransformMatrix._42 = pMatPos->data[13];
                FrameTransformMatrix._43 = pMatPos->data[14];
                FrameTransformMatrix._44 = pMatPos->data[15];

                if (n == 0) {
                    nVertices_begin = 0;
                    nVertices_end = paNumVertices[n];
                } else {
                    nVertices_begin += paNumVertices[n-1];
                    nVertices_end += paNumVertices[n];
                }

                D3DXVECTOR3 vecVertex;
                D3DXVECTOR3 vecNormal;
                D3DXVECTOR3 vecTangent;
                D3DXVECTOR3 vecBinormal;
                for (int i = nVertices_begin; i < nVertices_end; i++) {
                    pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
                    vecVertex.x = pVtx->x;
                    vecVertex.y = pVtx->y;
                    vecVertex.z = pVtx->z;
                    D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                    vecNormal.x = pVtx->nx;
                    vecNormal.y = pVtx->ny;
                    vecNormal.z = pVtx->nz;
                    D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);
                    pVtx->x = vecVertex.x;
                    pVtx->y = vecVertex.y;
                    pVtx->z = vecVertex.z;
                    pVtx->nx = vecNormal.x;
                    pVtx->ny = vecNormal.y;
                    pVtx->nz = vecNormal.z;

                    if (prm_pModel) {
                        //���_�o�b�t�@�ɁATangent Binormal ���ߍ��ݗL��̏ꍇ
                        if (prm_pModel->_obj_model & Obj_GgafDxMeshModel) {
                            //GgafDxMeshModel�̏ꍇ
                            GgafDxMeshModel::VERTEX* pVtx_MeshModel = (GgafDxMeshModel::VERTEX*)pVtx;
                            vecTangent.x = pVtx_MeshModel->tan_x;
                            vecTangent.y = pVtx_MeshModel->tan_y;
                            vecTangent.z = pVtx_MeshModel->tan_z;
                            D3DXVec3TransformNormal(&vecTangent, &vecTangent, &FrameTransformMatrix);
                            vecBinormal.x = pVtx_MeshModel->bin_x;
                            vecBinormal.y = pVtx_MeshModel->bin_y;
                            vecBinormal.z = pVtx_MeshModel->bin_z;
                            D3DXVec3TransformNormal(&vecBinormal, &vecBinormal, &FrameTransformMatrix);

                            pVtx_MeshModel->tan_x = vecTangent.x;
                            pVtx_MeshModel->tan_y = vecTangent.y;
                            pVtx_MeshModel->tan_z = vecTangent.z;
                            pVtx_MeshModel->bin_x = vecBinormal.x;
                            pVtx_MeshModel->bin_y = vecBinormal.y;
                            pVtx_MeshModel->bin_z = vecBinormal.z;

                        } else {
                            throwGgafCriticalException("�o���v�}�b�v��������ĂȂ��� prm_pModel="<<prm_pModel->getName()<<" _obj_model="<<prm_pModel->_obj_model);
                        }
                    }
                }
            }
        }
        n++;
    }
    //�Ō�ɖ@�����K�����Đݒ�
    D3DXVECTOR3 vec;
    for (int i = 0; i < nVertices; i++) {
        pVtx = (GgafDxModel::VERTEX_3D_BASE*)(paVtxBuffer + (prm_size_of_vtx_unit*i));
        vec.x = pVtx->nx;
        vec.y = pVtx->ny;
        vec.z = pVtx->nz;
        if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
            pVtx->nx = 0;
            pVtx->ny = 0;
            pVtx->nz = 0;
        } else {
            D3DXVec3Normalize( &vec, &vec);
            pVtx->nx = vec.x;
            pVtx->ny = vec.y;
            pVtx->nz = vec.z;
        }
        if (prm_pModel) {
            if (prm_pModel->_obj_model & Obj_GgafDxMeshModel) {
                GgafDxMeshModel::VERTEX* pVtx_MeshModel = (GgafDxMeshModel::VERTEX*)pVtx;
                vec.x = pVtx_MeshModel->tan_x;
                vec.y = pVtx_MeshModel->tan_y;
                vec.z = pVtx_MeshModel->tan_z;
                if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
                    pVtx_MeshModel->tan_x = 0;
                    pVtx_MeshModel->tan_y = 0;
                    pVtx_MeshModel->tan_z = 0;
                } else {
                    D3DXVec3Normalize( &vec, &vec);
                    pVtx_MeshModel->tan_x = vec.x;
                    pVtx_MeshModel->tan_y = vec.y;
                    pVtx_MeshModel->tan_z = vec.z;
                }
                vec.x = pVtx_MeshModel->bin_x;
                vec.y = pVtx_MeshModel->bin_y;
                vec.z = pVtx_MeshModel->bin_z;
                if (ZEROf_EQ(vec.x) && ZEROf_EQ(vec.y) && ZEROf_EQ(vec.z)) {
                    pVtx_MeshModel->bin_x = 0;
                    pVtx_MeshModel->bin_y = 0;
                    pVtx_MeshModel->bin_z = 0;
                } else {
                    D3DXVec3Normalize( &vec, &vec);
                    pVtx_MeshModel->bin_x = vec.x;
                    pVtx_MeshModel->bin_y = vec.y;
                    pVtx_MeshModel->bin_z = vec.z;
                }
            } else {
                throwGgafCriticalException("�o���v�}�b�v��������ĂȂ��� prm_pModel="<<prm_pModel->getName()<<" _obj_model="<<prm_pModel->_obj_model);
            }


        }
    }
    delete[] paRad;
    delete[] paRadSum_Vtx;
}


void GgafDxModelManager::restoreMorphMeshModel(GgafDxMorphMeshModel* prm_pMorphMeshModel) {
    TRACE3("GgafDxModelManager::restoreMorphMeshModel(" << prm_pMorphMeshModel->_model_name << ")");
    //�yGgafDxMorphMeshModel�č\�z�i���������j�����T�v�z
    //��{�I�ɂ�restoreMeshModel�̏�����������i�z��j�𑝂₵���悤�Ȃ���
    //�P�j�v���C�}���{���[�t�^�[�Q�b�g��N �́A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ ���쐬
    //�Q�j���ꂼ���X�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDxMeshModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E�v���C�}�����b�V�����_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���[�t�^�[�Q�b�g��N �̒��_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���_�C���f�b�N�X�o�b�t�@�̎ʂ��i�v���C�}�����b�V���̂݁j
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω��������B�v���C�}�����b�V���̂�)
    int morph_target_num = prm_pMorphMeshModel->_morph_target_num;

    std::string* paXfileName = NEW std::string[morph_target_num+1];

    for(int i = 0; i < morph_target_num+1; i++) {
        char* xfilename_base = prm_pMorphMeshModel->_model_name + 2; //�Q�����ڈȍ~  "2/ceres" �� "ceres"
        paXfileName[i] = getMeshFileName(std::string(xfilename_base) + "_" + (char)('0'+i));
        if (paXfileName[i] == "") {
             throwGgafCriticalException("GgafDxModelManager::restoreMorphMeshModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(std::string(xfilename_base) + "_" + (char)('0'+i)));
        }
    }
    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X* paIOX = nullptr;
    Frm::Model3D**                        model_papModel3D = nullptr;
    Frm::Mesh**                           model_papMeshesFront = nullptr;

    GgafDxMorphMeshModel::INDEXPARAM*     model_paIndexParam = nullptr;
    GgafDxMorphMeshModel::VERTEX_PRIMARY* model_paVtxBuffer_org_primary = nullptr;
    GgafDxMorphMeshModel::VERTEX_MORPH**  model_papaVtxBuffer_org_morph = nullptr;
    WORD*                                 model_paIdxBuffer_org = nullptr;
    D3DMATERIAL9*                         model_paMaterial = nullptr;

    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    if (prm_pMorphMeshModel->_papModel3D == nullptr) {
        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        model_papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        model_papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        model_papaVtxBuffer_org_morph = NEW GgafDxMorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
//        int nFaceNormals = 0;
        FLOAT model_bounding_sphere_radius;
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            model_papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfileName[pattern], model_papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("[GgafDxModelManager::restoreMorphMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B2/ �Ƃ��Y��Ă܂��񂩁H �Ώ�="<<paXfileName[pattern]);
            }
            //���b�V������������O�ɁA�����m�ۂ��Ă���
            int nMesh = (int)model_papModel3D[pattern]->_Meshes.size();
            uint16_t* paNumVertices = NEW uint16_t[nMesh];
            int index_Mesh = 0;
            for (std::list<Frm::Mesh*>::iterator iteMeshes = model_papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != model_papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            model_papModel3D[pattern]->ConcatenateMeshes(); //���b�V�����q����
            model_papMeshesFront[pattern] = model_papModel3D[pattern]->_Meshes.front();
            nVertices = model_papMeshesFront[pattern]->_nVertices;
            nTextureCoords = model_papMeshesFront[pattern]->_nTextureCoords;
            nFaces = model_papMeshesFront[pattern]->_nFaces;
//            nFaceNormals = model_papMeshesFront[pattern]->_nFaceNormals;

            if (nVertices*(morph_target_num+1) > 65535) {
                throwGgafCriticalException("[GgafDxModelManager::restoreMorphMeshModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMorphMeshModel->getName()<<"  nVertices:"<<nVertices<<"  �Z�b�g��:"<<(morph_target_num+1));
            }

            if (pattern == 0) {
                //�v���C�}�����b�V��
                model_paVtxBuffer_org_primary = NEW GgafDxMorphMeshModel::VERTEX_PRIMARY[nVertices];
                prm_pMorphMeshModel->_size_vertices_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY) * nVertices;
                prm_pMorphMeshModel->_size_vertex_unit_primary = sizeof(GgafDxMorphMeshModel::VERTEX_PRIMARY);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    model_paVtxBuffer_org_primary[i].x = model_papMeshesFront[pattern]->_Vertices[i].data[0];
                    model_paVtxBuffer_org_primary[i].y = model_papMeshesFront[pattern]->_Vertices[i].data[1];
                    model_paVtxBuffer_org_primary[i].z = model_papMeshesFront[pattern]->_Vertices[i].data[2];
                    model_paVtxBuffer_org_primary[i].nx = 0.0f;
                    model_paVtxBuffer_org_primary[i].ny = 0.0f;
                    model_paVtxBuffer_org_primary[i].nz = 0.0f;
                    model_paVtxBuffer_org_primary[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    if (i < nTextureCoords) {
                        model_paVtxBuffer_org_primary[i].tu = model_papMeshesFront[pattern]->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                        model_paVtxBuffer_org_primary[i].tv = model_papMeshesFront[pattern]->_TextureCoords[i].data[1];
                    } else {
                        model_paVtxBuffer_org_primary[i].tu = 0.0f;
                        model_paVtxBuffer_org_primary[i].tv = 0.0f;
                    }

                    //����
                    model_bounding_sphere_radius = (FLOAT)(sqrt(model_paVtxBuffer_org_primary[i].x * model_paVtxBuffer_org_primary[i].x +
                                                                model_paVtxBuffer_org_primary[i].y * model_paVtxBuffer_org_primary[i].y +
                                                                model_paVtxBuffer_org_primary[i].z * model_paVtxBuffer_org_primary[i].z));
                    if (prm_pMorphMeshModel->_bounding_sphere_radius < model_bounding_sphere_radius) {
                        prm_pMorphMeshModel->_bounding_sphere_radius = model_bounding_sphere_radius;
                    }
                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                model_papaVtxBuffer_org_morph[pattern-1] = NEW GgafDxMorphMeshModel::VERTEX_MORPH[nVertices];
                prm_pMorphMeshModel->_size_vertices_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH) * nVertices;
                prm_pMorphMeshModel->_size_vertex_unit_morph = sizeof(GgafDxMorphMeshModel::VERTEX_MORPH);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    model_papaVtxBuffer_org_morph[pattern-1][i].x = model_papMeshesFront[pattern]->_Vertices[i].data[0];
                    model_papaVtxBuffer_org_morph[pattern-1][i].y = model_papMeshesFront[pattern]->_Vertices[i].data[1];
                    model_papaVtxBuffer_org_morph[pattern-1][i].z = model_papMeshesFront[pattern]->_Vertices[i].data[2];
                    model_papaVtxBuffer_org_morph[pattern-1][i].nx = 0.0f;
                    model_papaVtxBuffer_org_morph[pattern-1][i].ny = 0.0f;
                    model_papaVtxBuffer_org_morph[pattern-1][i].nz = 0.0f;
                }
            }

            if (nVertices < nTextureCoords) {
                _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
                _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<paXfileName[pattern]);
            }

            //�@���ݒ��FrameTransformMatrix�K�p
            if (pattern == 0) { //�v���C�}�����b�V��
                prepareVtx((void*)model_paVtxBuffer_org_primary, prm_pMorphMeshModel->_size_vertex_unit_primary,
                           model_papModel3D[pattern], paNumVertices);
            } else {            //�^�[�Q�b�g���b�V��
                prepareVtx((void*)(model_papaVtxBuffer_org_morph[pattern-1]), prm_pMorphMeshModel->_size_vertex_unit_morph,
                           model_papModel3D[pattern], paNumVertices);
            }
            GGAF_DELETE(paNumVertices);

        }

        //�C���f�b�N�X�o�b�t�@�擾
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_papMeshesFront[0]->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_papMeshesFront[0]->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_papMeshesFront[0]->_Faces[i].data[2];
        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDxMeshModel::INDEXPARAM* paParam = NEW GgafDxMeshModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = UINT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = model_papMeshesFront[0]->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //TRACE3("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�ςȒl�ɂ��Ƃ�
                paParam[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
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

        model_paIndexParam = NEW GgafDxMorphMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            model_paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            model_paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            model_paIndexParam[i].MinIndex = paParam[i].MinIndex;
            model_paIndexParam[i].NumVertices = paParam[i].NumVertices;
            model_paIndexParam[i].StartIndex = paParam[i].StartIndex;
            model_paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        prm_pMorphMeshModel->_nMaterialListGrp = paramno;

        delete[] paParam;
    }

    if (prm_pMorphMeshModel->_pIDirect3DVertexDeclaration9 == nullptr) {

        int elemnum = (4+(2*morph_target_num))+1; //D3DVERTEXELEMENT9 �\���̂̔z��v�f��
        D3DVERTEXELEMENT9* paVtxelem = NEW D3DVERTEXELEMENT9[elemnum];
                                                         // 4 = �v���C�}�����b�V��
                                                         // (2*morph_target_num) = ���[�t�^�[�Q�b�g���b�V��
                                                         // 1 = D3DDECL_END()
        //�v���C�}�����b�V�������_�t�H�[�}�b�g
        //FVF�͎g���Ȃ��̂ŁACreateVertexDeclaration��
        //TODO:���_�t�H�[�}�b�g�𖈉�\�z�ł͂Ȃ��āA���f�����ɕێ����������B
        //�v���C�}�������_�t�H�[�}�b�g
        //float x, y, z; // ���_���W
        paVtxelem[0].Stream = 0;
        paVtxelem[0].Offset = 0;
        paVtxelem[0].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[0].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[0].Usage = D3DDECLUSAGE_POSITION;
        paVtxelem[0].UsageIndex = 0;
        //float nx, ny, nz; // �@��
        paVtxelem[1].Stream = 0;
        paVtxelem[1].Offset = sizeof(float)*3;
        paVtxelem[1].Type = D3DDECLTYPE_FLOAT3;
        paVtxelem[1].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[1].Usage = D3DDECLUSAGE_NORMAL;
        paVtxelem[1].UsageIndex = 0;
        //DWORD color; // ���_�J���[
        paVtxelem[2].Stream = 0;
        paVtxelem[2].Offset = sizeof(float)*6;
        paVtxelem[2].Type = D3DDECLTYPE_D3DCOLOR;
        paVtxelem[2].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[2].Usage = D3DDECLUSAGE_COLOR;
        paVtxelem[2].UsageIndex = 0;
        //float tu, tv; // �e�N�X�`�����W
        paVtxelem[3].Stream = 0;
        paVtxelem[3].Offset = sizeof(float)*6+sizeof(DWORD);
        paVtxelem[3].Type = D3DDECLTYPE_FLOAT2;
        paVtxelem[3].Method = D3DDECLMETHOD_DEFAULT;
        paVtxelem[3].Usage = D3DDECLUSAGE_TEXCOORD;
        paVtxelem[3].UsageIndex = 0;
        //���[�t�^�[�Q�b�g���b�V�������_�t�H�[�}�b�g
        for (int i = 4, s = 1; i < elemnum-1; i+=2, s++) {
            //float x, y, z; // ���_���W
            paVtxelem[i].Stream = s;
            paVtxelem[i].Offset = 0;
            paVtxelem[i].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i].Usage = D3DDECLUSAGE_POSITION;
            paVtxelem[i].UsageIndex = s;
            //float nx, ny, nz; // �@��
            paVtxelem[i+1].Stream = s;
            paVtxelem[i+1].Offset = sizeof(float)*3;
            paVtxelem[i+1].Type = D3DDECLTYPE_FLOAT3;
            paVtxelem[i+1].Method = D3DDECLMETHOD_DEFAULT;
            paVtxelem[i+1].Usage = D3DDECLUSAGE_NORMAL;
            paVtxelem[i+1].UsageIndex = s;
        }
        //D3DDECL_END()
        paVtxelem[elemnum-1].Stream = 0xFF;
        paVtxelem[elemnum-1].Offset = 0;
        paVtxelem[elemnum-1].Type = D3DDECLTYPE_UNUSED;
        paVtxelem[elemnum-1].Method = 0;
        paVtxelem[elemnum-1].Usage = 0;
        paVtxelem[elemnum-1].UsageIndex = 0;

        hr = GgafDxGod::_pID3DDevice9->CreateVertexDeclaration( paVtxelem, &(prm_pMorphMeshModel->_pIDirect3DVertexDeclaration9) );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] GgafDxGod::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(prm_pMorphMeshModel->_model_name));
        //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        GGAF_DELETEARR(paVtxelem);
    }

    //���_�o�b�t�@�쐬
    if (prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary == nullptr) {
        prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[morph_target_num];
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {

            if (pattern == 0) {
                //�v���C�}�����_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertices_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary),
                        nullptr);
                checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i�v���C�}���j model="<<(prm_pMorphMeshModel->_model_name));
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Lock(0, prm_pMorphMeshModel->_size_vertices_primary, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i�v���C�}���j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, model_paVtxBuffer_org_primary, prm_pMorphMeshModel->_size_vertices_primary); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Unlock();
            } else {
                //���[�t�^�[�Q�b�g���_�o�b�t�@
                hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertices_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDxMorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        nullptr);
                checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(prm_pMorphMeshModel->_model_name));
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, prm_pMorphMeshModel->_size_vertices_morph, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, model_papaVtxBuffer_org_morph[pattern-1], prm_pMorphMeshModel->_size_vertices_morph); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬�i�v���C�}���A���[�t�^�[�Q�b�g���ɓ����j
    if (prm_pMorphMeshModel->_pIDirect3DIndexBuffer9 == nullptr) {
        int nFaces = model_papMeshesFront[0]->_nFaces;

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMorphMeshModel->_pIDirect3DIndexBuffer9),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMorphMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , model_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }



    //�}�e���A���ݒ�
    //�}�e���A���̓v���C�}�����b�V���̃}�e���A�������A
    //�v���C�}���y�ёS���[�t�^�[�Q�b�g�̃}�e���A���Ƃ���B
    //�����model_papMeshesFront[0]�����g���A�c��͎g��Ȃ��B
    //TODO:�����I�ɂ̓��[�t�^�[�Q�b�g�ʂɃ}�e���A���ݒ�ł���Ε\���������B�������悤���A���������Ԑ�B
    int model_nMaterials = 0;
    setMaterial(model_papMeshesFront[0],
                &model_nMaterials, &model_paMaterial, &model_papTextureConnection);

    GGAF_DELETEARR(paIOX);
    GGAF_DELETEARR(paXfileName);

    //���f���ɕێ�������
    prm_pMorphMeshModel->_papModel3D = model_papModel3D;
    prm_pMorphMeshModel->_papMeshesFront = model_papMeshesFront;
    prm_pMorphMeshModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMorphMeshModel->_paVtxBuffer_org_primary = model_paVtxBuffer_org_primary;
    prm_pMorphMeshModel->_papaVtxBuffer_org_morph = model_papaVtxBuffer_org_morph;
    prm_pMorphMeshModel->_paIndexParam = model_paIndexParam;
    prm_pMorphMeshModel->_paMaterial_default = model_paMaterial;
    prm_pMorphMeshModel->_papTextureConnection = model_papTextureConnection;
    prm_pMorphMeshModel->_num_materials = model_nMaterials;
}

void GgafDxModelManager::restoreD3DXMeshModel(GgafDxD3DXMeshModel* prm_pD3DXMeshModel) {
    TRACE3("GgafDxModelManager::restoreD3DXMeshModel(" << prm_pD3DXMeshModel->_model_name << ")");
    //�yrestoreD3DXMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDxD3DXMeshModel�̃����o�ɃZ�b�g

    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDxD3DXMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    LPD3DXMESH pID3DXMesh; //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paMaterial; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDxTextureConnection** model_papTextureConnection; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD _num_materials;
    std::string xfile_name = getMeshFileName(prm_pD3DXMeshModel->_model_name);
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreD3DXMeshModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(prm_pD3DXMeshModel->_model_name));
    }

    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    hr = D3DXLoadMeshFromX(
           xfile_name.c_str(),         //[in]  LPCTSTR pFilename
           prm_pD3DXMeshModel->_dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
           GgafDxGod::_pID3DDevice9,   //[in]  LPDIRECT3DDEVICE9 pDevice
           nullptr,                       //[out] LPD3DXBUFFER* ppAdjacency
           &pID3DXBuffer,              //[out] LPD3DXBUFFER* ppMaterials
           nullptr,                       //[out] LPD3DXBUFFER* ppEffectInstances
           &_num_materials,            //[out] DWORD* pNumMaterials
           &pID3DXMesh                 //[out] LPD3DXMESH* pMesh
         );
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreD3DXMeshModel] D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfile_name);

    //�œK��
    DWORD *pAdjacency = NEW DWORD [ pID3DXMesh->GetNumFaces() * 3 ];
    hr = pID3DXMesh->GenerateAdjacency( 1e-6f, pAdjacency );
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreD3DXMeshModel] GenerateAdjacency������܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreD3DXMeshModel] D3DXMESHOPT_ATTRSORT�ł��܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, pAdjacency, nullptr, nullptr, nullptr );
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreD3DXMeshModel] D3DXMESHOPT_VERTEXCACHE�ł��܂���B�Ώ�="<<xfile_name);
    GGAF_DELETEARR(pAdjacency);

    //�}�e���A�������o��
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //��2008/02/02 �̔]�݂���
    // ����Ă��邱�ƃ���
    // GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
    //�\���̂𕨗��R�s�[�����ĕۑ����邱�Ƃɂ��܂���`�A�Ƃ肠�������`���܂��傤�B
    model_paMaterial = NEW D3DMATERIAL9[_num_materials];
    for( DWORD i = 0; i < _num_materials; i++){
        model_paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //�}�e���A����Diffuse���˂�Ambient���˂ɃR�s�[����
    //���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
    //�G�N�X�|�[�g���ꂽx�t�@�C���̃}�e���A����Ambient���˒l���ݒ肳��ĂȂ��i�����c�[���̂����H�j�B
    //�܂��قƂ��Diffuse=Ambient�Ŗ��Ȃ��n�Y�ƍl�����B
    //�����Ńf�t�H���g�ŁADiffuse���˒l��Ambient���˒l��ݒ肷�邱�Ƃɂ���A�Ƃ肠�����B
    //��2009/3/13��
    //�Œ�p�C�v���C���͂����g��Ȃ��Ȃ����B����ɔ����}�e���A��Diffuse�̓V�F�[�_�[�̃p�����[�^�݂̂ŗ��p���Ă���B
    //TODO:���݃}�e���A��Ambient�͎Q�Ƃ���Ȃ��B�������������H
    for( DWORD i = 0; i < _num_materials; i++) {
        model_paMaterial[i].Ambient = model_paMaterial[i].Diffuse;
    }

    //�e�N�X�`�������o��
    model_papTextureConnection = NEW GgafDxTextureConnection*[_num_materials];
    char* texture_filename;
    for( DWORD i = 0; i < _num_materials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
            model_papTextureConnection[i] = (GgafDxTextureConnection*)_pModelTextureManager->connect(texture_filename, this);
        } else {
            //�e�N�X�`������
            model_papTextureConnection[i] = (GgafDxTextureConnection*)_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this);
        }
    }
    GGAF_RELEASE(pID3DXBuffer);//�e�N�X�`���t�@�C�����͂�������Ȃ��̂Ńo�b�t�@���

    //X�t�@�C���ɖ@�����Ȃ��ꍇ�AFVF�ɖ@����ǉ����A�@�����v�Z���Ă�ݒ�B
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = nullptr;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           GgafDxGod::_pID3DDevice9,             // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreD3DXMeshModel]  pID3DXMesh->CloneMeshFVF()���s�B�Ώ�="<<xfile_name);
        D3DXComputeNormals(pID3DXMesh_tmp, nullptr); //�@���v�Z�iFace�̕\���ǂ����ɖ@�������邩�A�ǂ�����Ĕ��肵�Ă���̂��낤���E�E�E�j
        GGAF_RELEASE(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
    prm_pD3DXMeshModel->_pID3DXMesh = pID3DXMesh;
    prm_pD3DXMeshModel->_paMaterial_default = model_paMaterial;
    prm_pD3DXMeshModel->_papTextureConnection = model_papTextureConnection;
    prm_pD3DXMeshModel->_num_materials = _num_materials;
    prm_pD3DXMeshModel->_bounding_sphere_radius = 10.0f; //TODO:���E�����a�傫���Ƃ肠����100px

}

void GgafDxModelManager::restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel* prm_pD3DXAniMeshModel) {
    TRACE3("GgafDxModelManager::restoreD3DXAniMeshModel(" << prm_pD3DXAniMeshModel->_model_name << ")");
    //TODO:�쐬���H�I�I�I�I�I�I�I�I

    //�yrestoreD3DXAniMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDxD3DXAniMeshModel�̃����o�ɃZ�b�g
    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDxD3DXAniMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
//    LPD3DXMESH pID3DXAniMesh; //���b�V��(ID3DXAniMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paMaterial = nullptr; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDxTextureConnection** model_papTextureConnection = nullptr; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
//    DWORD _num_materials;
    std::string xfile_name = getMeshFileName(prm_pD3DXAniMeshModel->_model_name);
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(prm_pD3DXAniMeshModel->_model_name));
    }
    //AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
    std::ifstream ifs(xfile_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException(" GgafDxModelManager::restoreD3DXAniMeshModel ["<<xfile_name<<"] ���J���܂���");
    }
    std::string buf;
    bool isdone = false;
    int anim_ticks_per_second = 4800;
    std::string data;
    while(isdone == false && !ifs.eof()) {
        ifs >> data;
        if (data == "AnimTicksPerSecond" || data == "AnimTicksPerSecond{") {
            while(isdone == false) {
                ifs >> data;
                if (data == "{") {
                    continue;
                } else if (data == "}") {
                    isdone = true;
                    break;
                } else {
                    anim_ticks_per_second = atoi(data.c_str()); //"60;" �� 60�𓾂�
                    isdone = true;
                    break;
                }
            }
        }
    }
    ifs.close();

//    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    GgafDxAllocHierarchyWorldFrame* pAH = NEW GgafDxAllocHierarchyWorldFrame(); // CAllocHierarchyBase�̔h���N���X
    D3DXFRAME_WORLD* pFR; // ���[���h�ϊ��s��t���t���[���\����
    ID3DXAnimationController* pAC; // �A�j���[�V�����R���g���[��
    hr = D3DXLoadMeshHierarchyFromX(
            xfile_name.c_str(),
            D3DXMESH_SYSTEMMEM, //D3DXMESH_MANAGED,
            GgafDxGod::_pID3DDevice9,
            pAH,
            nullptr,
            (D3DXFRAME**)(&pFR),
            &pAC
         );
    _TRACE_("pAH="<<pAH<<" pFR="<<pFR<<" pAC="<<pAC<<" xfile_name.c_str()="<<xfile_name.c_str());
    checkDxException(hr, D3D_OK, "GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfile_name);
    if (pFR == nullptr) {
        throwGgafCriticalException("GgafDxModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �̃t���[����񂪎擾�ł��܂���I");
    }
    //�}�e���A���z����쐬
    std::list<D3DXFRAME_WORLD*> listFrame;
    getDrawFrameList(&listFrame, pFR); //�}�e���A��������m�肽�������߁A�t���[�������A���X�g��
    std::list<D3DXFRAME_WORLD*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //�t���[�����X�g������āA�}�e���A�������擾
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //�z�񐔂�����Ɖ������̂ō쐬
    model_paMaterial = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureConnection  = NEW GgafDxTextureConnection*[model_nMaterials];
    //���f���ێ��p�}�e���A���A�e�N�X�`���쐬�̂��߁A������x��
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == nullptr) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paMaterial[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //�}�e���A�����R�s�[

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != nullptr && lstrlen(texture_filename) > 0 ) {
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)_pModelTextureManager->connect(texture_filename, this);
                } else {
                    //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                    model_papTextureConnection[n] = (GgafDxTextureConnection*)_pModelTextureManager->connect(PROPERTY::WHITE_TEXTURE.c_str(), this);
                }
                n ++;
            }
        }
    }
    //���E��
    D3DXVECTOR3 vecCenter;
    FLOAT model_bounding_sphere_radius;
    D3DXFrameCalculateBoundingSphere(pFR, &vecCenter, &model_bounding_sphere_radius);
    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������

    prm_pD3DXAniMeshModel->_pAH = pAH;
    prm_pD3DXAniMeshModel->_pFR = pFR;
    prm_pD3DXAniMeshModel->_pAcBase = pAC;
    prm_pD3DXAniMeshModel->_bounding_sphere_radius = model_bounding_sphere_radius;
    _TRACE_("���E�����a="<<model_bounding_sphere_radius);
//    prm_pD3DXAniMeshModel->_advance_time_per_frame0 =  advanceTimePerFrame0; //�g���b�N0�ԂP���[�v�̎���
//    _TRACE_("�A�j���[�V�����Z�b�g0��_advance_time_per_frame");

//    prm_pD3DXAniMeshModel->_pID3DXAniMesh = pID3DXAniMesh;
    prm_pD3DXAniMeshModel->_paMaterial_default = model_paMaterial;
    prm_pD3DXAniMeshModel->_papTextureConnection = model_papTextureConnection;
    prm_pD3DXAniMeshModel->_num_materials = model_nMaterials;
    prm_pD3DXAniMeshModel->_anim_ticks_per_second = anim_ticks_per_second;
}

void GgafDxModelManager::getDrawFrameList(std::list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* pFrame) {
    if (pFrame->pMeshContainer) {
        //���b�V���R���e�i�L��
        pList->push_back(pFrame); //���X�g�ɒǉ�
    }
    if (pFrame->pFrameFirstChild) {
        // �q�t���[���L��
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameFirstChild);
    }
    if (pFrame->pFrameSibling) {
        //�Z��t���[���L��
        getDrawFrameList(pList, (D3DXFRAME_WORLD*)pFrame->pFrameSibling);
    }
}

void GgafDxModelManager::restoreSpriteModel(GgafDxSpriteModel* prm_pSpriteModel) {
    TRACE3("GgafDxModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");
    prm_pSpriteModel->_papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = getSpriteFileName(prm_pSpriteModel->_model_name);
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    hr = _pID3DXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restoreSpriteModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restoreSpriteModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
//    GUID* pGuid;
//    pID3DXFileData->GetType( pGuid );

    XFILE_SPRITE_FMT xdata;
    pXData = obtainSpriteFmtX(&xdata, pXData);

    prm_pSpriteModel->_fSize_SpriteModelWidthPx = xdata.width;
    prm_pSpriteModel->_fSize_SpriteModelHeightPx =  xdata.height;
    prm_pSpriteModel->_row_texture_split = xdata.row_texture_split;
    prm_pSpriteModel->_col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)_pModelTextureManager->connect(xdata.texture_file, this);

    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteModel->_papTextureConnection = NEW GgafDxTextureConnection*[1];
    prm_pSpriteModel->_papTextureConnection[0] = model_pTextureConnection;

    GgafDxSpriteModel::VERTEX* paVertex = NEW GgafDxSpriteModel::VERTEX[4];
    prm_pSpriteModel->_size_vertices = sizeof(GgafDxSpriteModel::VERTEX)*4;
    prm_pSpriteModel->_size_vertex_unit = sizeof(GgafDxSpriteModel::VERTEX);

    //���_�z��������f���ɕێ�������
    //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
    //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
    //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������
    float texWidth  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float texHeight = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
    double dU = 1.0 / texWidth  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
    double dV = 1.0 / texHeight / 100000.0; //�e�N�X�`���̍���1px��10000����1px
    double rev = 1.0;//0.99609308; //99609309�Ŋ���
    //����
    paVertex[0].x = (xdata.width / -2.0 / PX_UNIT)*rev;
    paVertex[0].y = (xdata.height / 2.0 / PX_UNIT)*rev;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = dU;
    paVertex[0].tv = dV;
    //�E��
    paVertex[1].x = (xdata.width / 2.0 / PX_UNIT)*rev;
    paVertex[1].y = (xdata.height / 2.0 / PX_UNIT)*rev;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = (1.0 / xdata.col_texture_split) - dU;
    paVertex[1].tv = dV;
    //����
    paVertex[2].x = (xdata.width / -2.0 / PX_UNIT)*rev;
    paVertex[2].y = (xdata.height / -2.0 / PX_UNIT)*rev;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = dU;
    paVertex[2].tv = (1.0 / xdata.row_texture_split) - dV;

    //�E��
    paVertex[3].x = (xdata.width / 2.0 / PX_UNIT)*rev;
    paVertex[3].y = (xdata.height / -2.0 / PX_UNIT)*rev;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = (1.0 / xdata.col_texture_split) - dU;
    paVertex[3].tv = (1.0 / xdata.row_texture_split) - dV;

    //����
    FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(paVertex[0].x * paVertex[0].x +
                                                      paVertex[0].y * paVertex[0].y +
                                                      paVertex[0].z * paVertex[0].z));
    prm_pSpriteModel->_bounding_sphere_radius = model_bounding_sphere_radius;


    //�o�b�t�@�쐬
    if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == nullptr) {

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSpriteModel->_size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_size_vertices); //pVertexBuffer �� paVertex
    prm_pSpriteModel->_pIDirect3DVertexBuffer9->Unlock();

    prm_pSpriteModel->_num_materials = 1;
    D3DMATERIAL9* model_paMaterial;
    model_paMaterial = NEW D3DMATERIAL9[prm_pSpriteModel->_num_materials];
    for( DWORD i = 0; i < prm_pSpriteModel->_num_materials; i++){
        //model_paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paMaterial[i].Diffuse.r = 1.0f;
        model_paMaterial[i].Diffuse.g = 1.0f;
        model_paMaterial[i].Diffuse.b = 1.0f;
        model_paMaterial[i].Diffuse.a = 1.0f;
        model_paMaterial[i].Ambient.r = 1.0f;
        model_paMaterial[i].Ambient.g = 1.0f;
        model_paMaterial[i].Ambient.b = 1.0f;
        model_paMaterial[i].Ambient.a = 1.0f;
    }
    prm_pSpriteModel->_paMaterial_default = model_paMaterial;
    //��n��
    pID3DXFileData->Unlock();
    GGAF_DELETEARR(paVertex);
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void GgafDxModelManager::restoreSpriteSetModel(GgafDxSpriteSetModel* prm_pSpriteSetModel) {
    TRACE3("GgafDxModelManager::restoreSpriteSetModel(" << prm_pSpriteSetModel->_model_name << ")");

    if (4*prm_pSpriteSetModel->_set_num > 65535) {
        throwGgafCriticalException("X[GgafDxModelManager::restoreSpriteSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pSpriteSetModel->getName()<<"  nVertices:4  �Z�b�g��:"<<(prm_pSpriteSetModel->_set_num));
    }
    if ( 2 * 3 * prm_pSpriteSetModel->_set_num > 65535) {
        throwGgafCriticalException("[GgafDxModelManager::restoreSpriteSetModel] ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pSpriteSetModel->getName()<<"  nFaces:2(*3)  �Z�b�g��:"<<(prm_pSpriteSetModel->_set_num));
    }

    prm_pSpriteSetModel->_papTextureConnection = nullptr;

    HRESULT hr;
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    std::string xfile_name; //�ǂݍ��ރX�v���C�g��`�t�@�C�����iX�t�@�C���`���j
    //"12/Bomb" or "8/Bomb" or "Bomb" ���� "Bomb" ������Ƃ肾���ăt���p�X���擾
    if (*(prm_pSpriteSetModel->_model_name + 1) == '/') {
        xfile_name = getSpriteFileName(std::string(prm_pSpriteSetModel->_model_name + 2));
    } else if (*(prm_pSpriteSetModel->_model_name + 2) == '/') {
        xfile_name = getSpriteFileName(std::string(prm_pSpriteSetModel->_model_name + 3));
    } else {
        xfile_name = getSpriteFileName(std::string(prm_pSpriteSetModel->_model_name));
    }
    hr = _pID3DXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restoreSpriteSetModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restoreSpriteSetModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
//    GUID* pGuid;
//    pID3DXFileData->GetType(pGuid);

    XFILE_SPRITE_FMT xdata;
    pXData = obtainSpriteFmtX(&xdata, pXData);
    prm_pSpriteSetModel->_fSize_SpriteSetModelWidthPx  = xdata.width;
    prm_pSpriteSetModel->_fSize_SpriteSetModelHeightPx = xdata.height;
    prm_pSpriteSetModel->_row_texture_split = xdata.row_texture_split;
    prm_pSpriteSetModel->_col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)_pModelTextureManager->connect(xdata.texture_file, this);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteSetModel->_papTextureConnection = NEW GgafDxTextureConnection*[1];
    prm_pSpriteSetModel->_papTextureConnection[0] = model_pTextureConnection;
    //�o�b�t�@�쐬
    if (prm_pSpriteSetModel->_pIDirect3DVertexBuffer9 == nullptr) {
        prm_pSpriteSetModel->_size_vertices = sizeof(GgafDxSpriteSetModel::VERTEX)*4;
        prm_pSpriteSetModel->_size_vertex_unit = sizeof(GgafDxSpriteSetModel::VERTEX);

        GgafDxSpriteSetModel::VERTEX* paVertex = NEW GgafDxSpriteSetModel::VERTEX[4 * prm_pSpriteSetModel->_set_num];

        float texWidth  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
        float texHeight = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
        double dU = 1.0 / texWidth  / 100000.0; //�e�N�X�`���̕�1px��100000����1px
        double dV = 1.0 / texHeight / 100000.0; //�e�N�X�`���̍���1px��100000����1px
        double rev = 1.0;//0.99609308; //99609309�Ŋ���
        //���_�z��������f���ɕێ�������
        //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
        //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
        //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������
        for (int i = 0; i < prm_pSpriteSetModel->_set_num; i++) {
            //����
            paVertex[i*4 + 0].x = (xdata.width / -2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 0].y = (xdata.height / 2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].nx = 0.0f;
            paVertex[i*4 + 0].ny = 0.0f;
            paVertex[i*4 + 0].nz = -1.0f;
            paVertex[i*4 + 0].tu = dU;
            paVertex[i*4 + 0].tv = dV;
            paVertex[i*4 + 0].index = (float)i;
            //�E��
            paVertex[i*4 + 1].x = (xdata.width / 2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 1].y = (xdata.height / 2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].nx = 0.0f;
            paVertex[i*4 + 1].ny = 0.0f;
            paVertex[i*4 + 1].nz = -1.0f;
            paVertex[i*4 + 1].tu = (1.0/xdata.col_texture_split) - dU;
            paVertex[i*4 + 1].tv = dV;
            paVertex[i*4 + 1].index = (float)i;
            //����
            paVertex[i*4 + 2].x = (xdata.width / -2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 2].y = (xdata.height / -2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].nx = 0.0f;
            paVertex[i*4 + 2].ny = 0.0f;
            paVertex[i*4 + 2].nz = -1.0f;
            paVertex[i*4 + 2].tu = dU;
            paVertex[i*4 + 2].tv = (1.0/xdata.row_texture_split) - dV;
            paVertex[i*4 + 2].index = (float)i;
            //�E��
            paVertex[i*4 + 3].x = (xdata.width / 2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 3].y = (xdata.height / -2.0 / PX_UNIT)*rev;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].nx = 0.0f;
            paVertex[i*4 + 3].ny = 0.0f;
            paVertex[i*4 + 3].nz = -1.0f;
            paVertex[i*4 + 3].tu = (1.0/xdata.col_texture_split) - dU;
            paVertex[i*4 + 3].tv = (1.0/xdata.row_texture_split) - dV;
            paVertex[i*4 + 3].index = (float)i;

        }

        //����
        FLOAT model_bounding_sphere_radius = (FLOAT)(sqrt(paVertex[0].x * paVertex[0].x +
                                                          paVertex[0].y * paVertex[0].y +
                                                          paVertex[0].z * paVertex[0].z));
        prm_pSpriteSetModel->_bounding_sphere_radius = model_bounding_sphere_radius;


        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteSetModel->_size_vertices * prm_pSpriteSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxSpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pSpriteSetModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteSetModel] _p1ID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteSetModel->_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = prm_pSpriteSetModel->_pIDirect3DVertexBuffer9->Lock(
                                       0,
                                       prm_pSpriteSetModel->_size_vertices * prm_pSpriteSetModel->_set_num,
                                       (void**)&pVertexBuffer,
                                       0
                                   );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteSetModel->_model_name);

        memcpy(
            pVertexBuffer,
            paVertex,
            prm_pSpriteSetModel->_size_vertices* prm_pSpriteSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pSpriteSetModel->_pIDirect3DVertexBuffer9->Unlock();
        GGAF_DELETEARR(paVertex);
    }

    //�C���f�b�N�X�o�b�t�@�쐬
    if (prm_pSpriteSetModel->_pIDirect3DIndexBuffer9 == nullptr) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * prm_pSpriteSetModel->_set_num];
        for (int i = 0; i < prm_pSpriteSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * prm_pSpriteSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pSpriteSetModel->_pIDirect3DIndexBuffer9),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreSpriteSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pSpriteSetModel->_model_name));

        void* pIndexBuffer;
        prm_pSpriteSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * prm_pSpriteSetModel->_set_num
        );
        prm_pSpriteSetModel->_pIDirect3DIndexBuffer9->Unlock();
        GGAF_DELETEARR(unit_paIdxBuffer);
        GGAF_DELETEARR(paIdxBufferSet);

        //�`�掞�p�����[�^�[
        GgafDxSpriteSetModel::INDEXPARAM* paIndexParam = NEW GgafDxSpriteSetModel::INDEXPARAM[prm_pSpriteSetModel->_set_num];
        for (int i = 0; i < prm_pSpriteSetModel->_set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        prm_pSpriteSetModel->_paIndexParam = paIndexParam;
    }

    prm_pSpriteSetModel->_num_materials = 1;
    D3DMATERIAL9* model_paMaterial = NEW D3DMATERIAL9[prm_pSpriteSetModel->_num_materials];
    for( DWORD i = 0; i < prm_pSpriteSetModel->_num_materials; i++){
        //model_paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paMaterial[i].Diffuse.r = 1.0f;
        model_paMaterial[i].Diffuse.g = 1.0f;
        model_paMaterial[i].Diffuse.b = 1.0f;
        model_paMaterial[i].Diffuse.a = 1.0f;
        model_paMaterial[i].Ambient.r = 1.0f;
        model_paMaterial[i].Ambient.g = 1.0f;
        model_paMaterial[i].Ambient.b = 1.0f;
        model_paMaterial[i].Ambient.a = 1.0f;
    }
    prm_pSpriteSetModel->_paMaterial_default = model_paMaterial;
    //��n��
    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void GgafDxModelManager::restoreBoardModel(GgafDxBoardModel* prm_pBoardModel) {
    TRACE3("GgafDxModelManager::restoreBoardModel(" << prm_pBoardModel->_model_name << ")");

    prm_pBoardModel->_papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name = getSpriteFileName(prm_pBoardModel->_model_name);

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    hr = _pID3DXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restoreBoardModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restoreBoardModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    XFILE_SPRITE_FMT xdata;
    pXData = obtainSpriteFmtX(&xdata, pXData);
    prm_pBoardModel->_fSize_BoardModelWidthPx  = xdata.width;
    prm_pBoardModel->_fSize_BoardModelHeightPx = xdata.height;
    prm_pBoardModel->_row_texture_split = xdata.row_texture_split;
    prm_pBoardModel->_col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)_pModelTextureManager->connect(xdata.texture_file, this);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pBoardModel->_papTextureConnection = NEW GgafDxTextureConnection*[1];
    prm_pBoardModel->_papTextureConnection[0] = model_pTextureConnection;

    GgafDxBoardModel::VERTEX* paVertex = NEW GgafDxBoardModel::VERTEX[4];
    prm_pBoardModel->_size_vertices = sizeof(GgafDxBoardModel::VERTEX)*4;
    prm_pBoardModel->_size_vertex_unit = sizeof(GgafDxBoardModel::VERTEX);

    //1px�������uv�̑傫�������߂�
//    float texWidth  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
//    float texHeight = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
    double dU = 0.0;//1.0 / texWidth  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
    double dV = 0.0;//1.0 / texHeight / 100000.0; //�e�N�X�`���̍���1px��10000����1px

    //����
    paVertex[0].x = 0.0f;
    paVertex[0].y = 0.0f;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = dU;
    paVertex[0].tv = dV;
    //�E��
    paVertex[1].x = xdata.width;
    paVertex[1].y = 0.0f;
    paVertex[1].z = 0.0f;
    paVertex[1].tu = (1.0 / xdata.col_texture_split) - dU;
    paVertex[1].tv = dV;
    //����
    paVertex[2].x = 0.0f;
    paVertex[2].y = xdata.height;
    paVertex[2].z = 0.0f;
    paVertex[2].tu = dU;
    paVertex[2].tv = (1.0 / xdata.row_texture_split) - dV;
    //�E��
    paVertex[3].x = xdata.width;
    paVertex[3].y = xdata.height;
    paVertex[3].z = 0.0f;
    paVertex[3].tu = (1.0 / xdata.col_texture_split) - dU;
    paVertex[3].tv = (1.0 / xdata.row_texture_split) - dV;

    //�o�b�t�@�쐬
    if (prm_pBoardModel->_pIDirect3DVertexBuffer9 == nullptr) {

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pBoardModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxBoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pBoardModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pBoardModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pBoardModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pBoardModel->_size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pBoardModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pBoardModel->_size_vertices); //pVertexBuffer �� paVertex
    prm_pBoardModel->_pIDirect3DVertexBuffer9->Unlock();
    prm_pBoardModel->_num_materials = 1;
    D3DMATERIAL9* model_paMaterial;
    model_paMaterial = NEW D3DMATERIAL9[prm_pBoardModel->_num_materials];
    for( DWORD i = 0; i < prm_pBoardModel->_num_materials; i++){
        model_paMaterial[i].Diffuse.r = 1.0f;
        model_paMaterial[i].Diffuse.g = 1.0f;
        model_paMaterial[i].Diffuse.b = 1.0f;
        model_paMaterial[i].Diffuse.a = 1.0f;
        model_paMaterial[i].Ambient.r = 1.0f;
        model_paMaterial[i].Ambient.g = 1.0f;
        model_paMaterial[i].Ambient.b = 1.0f;
        model_paMaterial[i].Ambient.a = 1.0f;
    }
    prm_pBoardModel->_paMaterial_default = model_paMaterial;

    //��n��
    pID3DXFileData->Unlock();
    GGAF_DELETEARR(paVertex);
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void GgafDxModelManager::restoreBoardSetModel(GgafDxBoardSetModel* prm_pBoardSetModel) {
    TRACE3("GgafDxModelManager::restoreBoardSetModel(" << prm_pBoardSetModel->_model_name << ")");

    if (4*prm_pBoardSetModel->_set_num > 65535) {
        throwGgafCriticalException("[GgafDxModelManager::restoreBoardSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pBoardSetModel->getName()<<"  nVertices:4  �Z�b�g��:"<<(prm_pBoardSetModel->_set_num));
    }

    prm_pBoardSetModel->_papTextureConnection = nullptr;
    HRESULT hr;
    std::string xfile_name; //�ǂݍ��ރX�v���C�g��`�t�@�C�����iX�t�@�C���`���j
    //"12/Moji" or "8/Moji" or "Moji" ���� "Moji" ������Ƃ肾���ăt���p�X���擾�B
    //TODO:���l3��("123/Moji"�Ƃ�)�������獢��B
    if (*(prm_pBoardSetModel->_model_name + 1) == '/') {
        xfile_name = getSpriteFileName(std::string(prm_pBoardSetModel->_model_name + 2));
    } else if (*(prm_pBoardSetModel->_model_name + 2) == '/') {
        xfile_name = getSpriteFileName(std::string(prm_pBoardSetModel->_model_name + 3));
    } else {
        xfile_name = getSpriteFileName(std::string(prm_pBoardSetModel->_model_name));
    }
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    hr = _pID3DXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restoreBoardSetModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
        pID3DXFileEnumObject->GetChild(childCount, &pID3DXFileData);
    }

    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restoreBoardSetModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    XFILE_SPRITE_FMT xdata;
    pXData = obtainSpriteFmtX(&xdata, pXData);
    prm_pBoardSetModel->_fSize_BoardSetModelWidthPx  = xdata.width;
    prm_pBoardSetModel->_fSize_BoardSetModelHeightPx = xdata.height;
    prm_pBoardSetModel->_row_texture_split = xdata.row_texture_split;
    prm_pBoardSetModel->_col_texture_split = xdata.col_texture_split;

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection* model_pTextureConnection = (GgafDxTextureConnection*)_pModelTextureManager->connect(xdata.texture_file, this);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pBoardSetModel->_papTextureConnection = NEW GgafDxTextureConnection*[1];
    prm_pBoardSetModel->_papTextureConnection[0] = model_pTextureConnection;

    if (prm_pBoardSetModel->_pIDirect3DVertexBuffer9 == nullptr) {

        prm_pBoardSetModel->_size_vertices = sizeof(GgafDxBoardSetModel::VERTEX)*4;
        prm_pBoardSetModel->_size_vertex_unit = sizeof(GgafDxBoardSetModel::VERTEX);
        GgafDxBoardSetModel::VERTEX* paVertex = NEW GgafDxBoardSetModel::VERTEX[4 * prm_pBoardSetModel->_set_num];

        //1px�������uv�̑傫�������߂�
//        float texWidth  = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
//        float texHeight = (float)(model_pTextureConnection->peek()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
        double dU = 0.0; //1.0 / texWidth  / 100000.0; //�e�N�X�`���̕�1px��10000����1px
        double dV = 0.0; //1.0 / texHeight / 100000.0; //�e�N�X�`���̍���1px��10000����1px
        for (int i = 0; i < prm_pBoardSetModel->_set_num; i++) {
            //����
            paVertex[i*4 + 0].x = 0.0f;
            paVertex[i*4 + 0].y = 0.0f;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].tu = dU;
            paVertex[i*4 + 0].tv = dV;
            paVertex[i*4 + 0].index = (float)i;
            //�E��
            paVertex[i*4 + 1].x = xdata.width;
            paVertex[i*4 + 1].y = 0.0f;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].tu = (1.0 / xdata.col_texture_split) - dU;
            paVertex[i*4 + 1].tv = dV;
            paVertex[i*4 + 1].index = (float)i;
            //����
            paVertex[i*4 + 2].x = 0.0f;
            paVertex[i*4 + 2].y = xdata.height;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].tu = dU;
            paVertex[i*4 + 2].tv = (1.0 / xdata.row_texture_split) - dV;
            paVertex[i*4 + 2].index = (float)i;
            //�E��
            paVertex[i*4 + 3].x = xdata.width;
            paVertex[i*4 + 3].y = xdata.height;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].tu = (1.0 / xdata.col_texture_split) - dU;
            paVertex[i*4 + 3].tv = (1.0 / xdata.row_texture_split) - dV;
            paVertex[i*4 + 3].index = (float)i;
         }

        //�o�b�t�@�쐬

        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxBoardSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pBoardSetModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pBoardSetModel->_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = prm_pBoardSetModel->_pIDirect3DVertexBuffer9->Lock(
                                                             0,
                                                             prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num,
                                                             (void**)&pVertexBuffer,
                                                             0
                                                           );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pBoardSetModel->_model_name);

        memcpy(
          pVertexBuffer,
          paVertex,
          prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pBoardSetModel->_pIDirect3DVertexBuffer9->Unlock();

        GGAF_DELETEARR(paVertex);
    }


    //�C���f�b�N�X�o�b�t�@�쐬
    if (prm_pBoardSetModel->_pIDirect3DIndexBuffer9 == nullptr) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * prm_pBoardSetModel->_set_num];
        for (int i = 0; i < prm_pBoardSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
            }
        }

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * prm_pBoardSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pBoardSetModel->_pIDirect3DIndexBuffer9),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreBoardSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pBoardSetModel->_model_name));

        void* pIndexBuffer;
        prm_pBoardSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * prm_pBoardSetModel->_set_num
        );
        prm_pBoardSetModel->_pIDirect3DIndexBuffer9->Unlock();
        GGAF_DELETEARR(unit_paIdxBuffer);
        GGAF_DELETEARR(paIdxBufferSet);

        //�`�掞�p�����[�^�[
        GgafDxBoardSetModel::INDEXPARAM* paIndexParam = NEW GgafDxBoardSetModel::INDEXPARAM[prm_pBoardSetModel->_set_num];
        for (int i = 0; i < prm_pBoardSetModel->_set_num; i++) {
            paIndexParam[i].MaterialNo = 0;
            paIndexParam[i].BaseVertexIndex = 0;
            paIndexParam[i].MinIndex = 0;
            paIndexParam[i].NumVertices = nVertices*(i+1);
            paIndexParam[i].StartIndex = 0;
            paIndexParam[i].PrimitiveCount = nFaces*(i+1);
        }
        prm_pBoardSetModel->_paIndexParam = paIndexParam;
    }

    prm_pBoardSetModel->_num_materials = 1;
    D3DMATERIAL9* model_paMaterial = NEW D3DMATERIAL9[prm_pBoardSetModel->_num_materials];
    for( DWORD i = 0; i < prm_pBoardSetModel->_num_materials; i++){
        //model_paMaterial[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paMaterial[i].Diffuse.r = 1.0f;
        model_paMaterial[i].Diffuse.g = 1.0f;
        model_paMaterial[i].Diffuse.b = 1.0f;
        model_paMaterial[i].Diffuse.a = 1.0f;
        model_paMaterial[i].Ambient.r = 1.0f;
        model_paMaterial[i].Ambient.g = 1.0f;
        model_paMaterial[i].Ambient.b = 1.0f;
        model_paMaterial[i].Ambient.a = 1.0f;
    }
    prm_pBoardSetModel->_paMaterial_default = model_paMaterial;

    //��n��
    pID3DXFileData->Unlock();
    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}

void GgafDxModelManager::restoreMeshSetModel(GgafDxMeshSetModel* prm_pMeshSetModel) {
    TRACE3("GgafDxModelManager::restoreMeshSetModel(" << prm_pMeshSetModel->_model_name << ")");
    std::string xfile_name; //�ǂݍ���X�t�@�C����
    //"12/Eres" or "8/Celes" or "Celes" ���� "Celes" ������Ƃ肾���ăt���p�X���擾
    //TODO:���l�R���ȏ�̎��͂���
    if (*(prm_pMeshSetModel->_model_name + 1) == '/') {
        xfile_name = getMeshFileName(std::string(prm_pMeshSetModel->_model_name + 2));
    } else if (*(prm_pMeshSetModel->_model_name + 2) == '/') {
        xfile_name = getMeshFileName(std::string(prm_pMeshSetModel->_model_name + 3));
    } else {
        xfile_name = getMeshFileName(std::string(prm_pMeshSetModel->_model_name));
    }
    if (xfile_name == "") {
         throwGgafCriticalException("GgafDxModelManager::restoreMeshSetModel ���b�V���t�@�C��(*.x)��������܂���Bmodel_name="<<(prm_pMeshSetModel->_model_name));
    }

    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = nullptr;
    Frm::Mesh* model_pMeshesFront = nullptr;

    GgafDxMeshSetModel::INDEXPARAM** model_papaIndexParam = nullptr;
    GgafDxMeshSetModel::VERTEX* unit_paVtxBuffer_org = nullptr;
    GgafDxMeshSetModel::VERTEX* model_paVtxBuffer_org = nullptr;
    WORD* unit_paIdxBuffer_org = nullptr;
    WORD* model_paIdxBuffer_org = nullptr;
    D3DMATERIAL9* model_paMaterial = nullptr;
    GgafDxTextureConnection** model_papTextureConnection = nullptr;

    int nVertices = 0;
    int nTextureCoords = 0;
    int nFaces = 0;
//    int nFaceNormals = 0;

    if (prm_pMeshSetModel->_pModel3D == nullptr) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMeshSetModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }

        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16_t* paNumVertices = NEW uint16_t[nMesh];
        int index_Mesh = 0;
        for (std::list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        model_pModel3D->ConcatenateMeshes(); //���b�V�����q����

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices;
        nTextureCoords = model_pMeshesFront->_nTextureCoords;
        nFaces = model_pMeshesFront->_nFaces;
//        nFaceNormals = model_pMeshesFront->_nFaceNormals;
        unit_paVtxBuffer_org = NEW GgafDxMeshSetModel::VERTEX[nVertices];

        if (nVertices*prm_pMeshSetModel->_set_num > 65535) {
            throwGgafCriticalException("[GgafDxModelManager::restoreMeshSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMeshSetModel->getName()<<"  nVertices:"<<nVertices<<"  �Z�b�g��:"<<(prm_pMeshSetModel->_set_num));
        }

        prm_pMeshSetModel->_nVertices = nVertices;
        prm_pMeshSetModel->_nFaces = nFaces;
        prm_pMeshSetModel->_size_vertices = sizeof(GgafDxMeshSetModel::VERTEX) * nVertices;
        prm_pMeshSetModel->_size_vertex_unit = sizeof(GgafDxMeshSetModel::VERTEX);

        //�@���ȊO�ݒ�
        FLOAT model_bounding_sphere_radius;
        for (int i = 0; i < nVertices; i++) {
            unit_paVtxBuffer_org[i].x = model_pMeshesFront->_Vertices[i].data[0];
            unit_paVtxBuffer_org[i].y = model_pMeshesFront->_Vertices[i].data[1];
            unit_paVtxBuffer_org[i].z = model_pMeshesFront->_Vertices[i].data[2];
            unit_paVtxBuffer_org[i].nx = 0.0f;
            unit_paVtxBuffer_org[i].ny = 0.0f;
            unit_paVtxBuffer_org[i].nz = 0.0f;
            unit_paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255); //���_�J���[�͍��̏��g���Ă��Ȃ�
            if (i < nTextureCoords) {
                unit_paVtxBuffer_org[i].tu = model_pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                unit_paVtxBuffer_org[i].tv = model_pMeshesFront->_TextureCoords[i].data[1];
            } else {
                unit_paVtxBuffer_org[i].tu = 0;
                unit_paVtxBuffer_org[i].tv = 0;
            }
            unit_paVtxBuffer_org[i].index = 0; //���_�ԍ��i�ނ��薄�ߍ��݁j

            //����
            model_bounding_sphere_radius = (FLOAT)(sqrt(unit_paVtxBuffer_org[i].x * unit_paVtxBuffer_org[i].x +
                                                        unit_paVtxBuffer_org[i].y * unit_paVtxBuffer_org[i].y +
                                                        unit_paVtxBuffer_org[i].z * unit_paVtxBuffer_org[i].z));
            if (prm_pMeshSetModel->_bounding_sphere_radius < model_bounding_sphere_radius) {
                prm_pMeshSetModel->_bounding_sphere_radius = model_bounding_sphere_radius;
            }
        }

        if (nVertices < nTextureCoords) {
            _TRACE_("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            _TRACE_("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }
        //�@���ݒ��FrameTransformMatrix�K�p
        prepareVtx((void*)unit_paVtxBuffer_org, prm_pMeshSetModel->_size_vertex_unit,
                   model_pModel3D, paNumVertices);
        GGAF_DELETE(paNumVertices);

        //�C���f�b�N�X�o�b�t�@�o�^
        unit_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            unit_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            unit_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            unit_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //���_�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_paVtxBuffer_org = NEW GgafDxMeshSetModel::VERTEX[nVertices * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nVertices; j++) {
                model_paVtxBuffer_org[(i*nVertices) + j] = unit_paVtxBuffer_org[j];
                model_paVtxBuffer_org[(i*nVertices) + j].index = (float)i; //+= (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paVtxBuffer_org);

        //�C���f�b�N�X�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_paIdxBuffer_org = NEW WORD[(nFaces*3) * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer_org[j*3 + 0] + (nVertices*i);
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer_org[j*3 + 1] + (nVertices*i);
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer_org[j*3 + 2] + (nVertices*i);
            }
        }
        GGAF_DELETEARR(unit_paIdxBuffer_org);

        //�}�e���A�����X�g���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        uint16_t* paFaceMaterials = NEW uint16_t[nFaces * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paFaceMaterials[(i*nFaces) + j] = model_pMeshesFront->_FaceMaterials[j];
            }
        }

        //�p�����[�^�����Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_papaIndexParam = NEW GgafDxMeshSetModel::INDEXPARAM*[prm_pMeshSetModel->_set_num];
        prm_pMeshSetModel->_paUint_material_list_grp_num = NEW UINT[prm_pMeshSetModel->_set_num];
        for (int set_index = 0; set_index < prm_pMeshSetModel->_set_num; set_index++) {
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
                    //TRACE3("BREAK! paramno="<<paramno);
                    prev_faceNoCnt_break = faceNoCnt_break;
                    faceNoCnt_break = faceNoCnt;

                    paParam[paramno].MaterialNo = materialno;
                    paParam[paramno].BaseVertexIndex = 0;
                    paParam[paramno].MinIndex = UINT_MAX; //����u���C�N���ɐݒ�A�K���u���C�N���������ߕςȒl�ɂ��Ƃ�
                    paParam[paramno].NumVertices = UINT_MAX; //����u���C�N���ɐݒ�
                    paParam[paramno].StartIndex = faceNoCnt*3;
                    paParam[paramno].PrimitiveCount = UINT_MAX; //����u���C�N���ɐݒ�

                    if (faceNoCnt > 0) {
                        paParam[paramno-1].MinIndex = min_num_vertices;
                        paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                        paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                        //���Z�b�g
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

            model_papaIndexParam[set_index] = NEW GgafDxMeshSetModel::INDEXPARAM[paramno];
            for (int i = 0; i < paramno; i++) {
                model_papaIndexParam[set_index][i].MaterialNo = paParam[i].MaterialNo;
                model_papaIndexParam[set_index][i].BaseVertexIndex = paParam[i].BaseVertexIndex;
                model_papaIndexParam[set_index][i].MinIndex = paParam[i].MinIndex;
                model_papaIndexParam[set_index][i].NumVertices = paParam[i].NumVertices;
                model_papaIndexParam[set_index][i].StartIndex = paParam[i].StartIndex;
                model_papaIndexParam[set_index][i].PrimitiveCount = paParam[i].PrimitiveCount;
            }

            prm_pMeshSetModel->_paUint_material_list_grp_num[set_index] = paramno;
            delete[] paParam;
        }

        GGAF_DELETEARR(paFaceMaterials);
    }

    if (prm_pMeshSetModel->_pIDirect3DVertexBuffer9 == nullptr) {
        //���_�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDxMeshSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pMeshSetModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshSetModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pMeshSetModel->_model_name));
        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pMeshSetModel->_pIDirect3DVertexBuffer9->Lock(
                                      0,
                                      prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num,
                                      (void**)&pVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pMeshSetModel->_model_name);

        memcpy(
          pVertexBuffer,
          model_paVtxBuffer_org,
          prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pMeshSetModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMeshSetModel->_pIDirect3DIndexBuffer9 == nullptr) {

        nFaces = model_pMeshesFront->_nFaces;

        hr = GgafDxGod::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * prm_pMeshSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMeshSetModel->_pIDirect3DIndexBuffer9),
                                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restoreMeshSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMeshSetModel->_model_name));

        void* pIndexBuffer;
        prm_pMeshSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          model_paIdxBuffer_org,
          sizeof(WORD) * nFaces * 3 * prm_pMeshSetModel->_set_num
        );
        prm_pMeshSetModel->_pIDirect3DIndexBuffer9->Unlock();
    }


    //�}�e���A���ݒ�
    int model_nMaterials = 0;
    setMaterial(model_pMeshesFront,
                &model_nMaterials, &model_paMaterial, &model_papTextureConnection);

    //���f���ɕێ�������
    prm_pMeshSetModel->_pModel3D = model_pModel3D;
    prm_pMeshSetModel->_pMeshesFront = model_pMeshesFront;

    prm_pMeshSetModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMeshSetModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pMeshSetModel->_papaIndexParam = model_papaIndexParam;
    prm_pMeshSetModel->_paMaterial_default = model_paMaterial;
    prm_pMeshSetModel->_papTextureConnection = model_papTextureConnection;
    prm_pMeshSetModel->_num_materials = model_nMaterials;
}

void GgafDxModelManager::restorePointSpriteModel(GgafDxPointSpriteModel* prm_pPointSpriteModel) {

    TRACE3("GgafDxModelManager::restorePointSpriteModel(" << prm_pPointSpriteModel->_model_name << ")");

    prm_pPointSpriteModel->_papTextureConnection = nullptr;
    HRESULT hr;
//    std::string xfile_name = PROPERTY::DIR_SPRITE_MODEL[0] + std::string(prm_pPointSpriteModel->_model_name) + ".psprx";
    std::string xfile_name = getPointSpriteFileName(prm_pPointSpriteModel->_model_name);
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    ID3DXFileEnumObject* pID3DXFileEnumObject;
    ID3DXFileData* pID3DXFileData;
    hr = _pID3DXFile_psprx->CreateEnumObject((void*)xfile_name.c_str(), D3DXF_FILELOAD_FROMFILE, &pID3DXFileEnumObject);
    checkDxException(hr, S_OK, "[GgafDxModelManager::restorePointSpriteModel] '"<<xfile_name<<"' ��CreateEnumObject�Ɏ��s���܂����B�t�@�C���̑��݂��m�F���ĉ������B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};
    SIZE_T nChildren;
    pID3DXFileEnumObject->GetChildren(&nChildren);
    for(SIZE_T childCount = 0; childCount < nChildren; ++childCount) {
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
//
    struct XFILE_FMT_HD {
        float SquareSize;
        char TextureFile[256];
        int TextureSplitRowCol;
        int VerticesNum;
    };
    SIZE_T xsize = 0;
    char* pXData = nullptr;
    pID3DXFileData->Lock(&xsize, (const void**)&pXData);
    if (pXData == nullptr) {
        throwGgafCriticalException("[GgafDxModelManager::restorePointSpriteModel] "<<xfile_name<<" �̃t�H�[�}�b�g�G���[�B");
    }
    //    GUID* pGuid;
    //    pID3DXFileData->GetType(pGuid);
    XFILE_FMT_HD xDataHd;
    //"  FLOAT  SquareSize;\n"
    memcpy(&(xDataHd.SquareSize), pXData, sizeof(float));
    pXData += sizeof(float);
    //"  STRING TextureFile;\n"
    strcpy(xDataHd.TextureFile, pXData);
    pXData += (sizeof(char) * (strlen(xDataHd.TextureFile)+1));
    //"  DWORD  TextureSplitRowCol;\n"
    memcpy(&(xDataHd.TextureSplitRowCol), pXData, sizeof(int));
    pXData += sizeof(int);
    //"  DWORD  VerticesNum;\n"
    memcpy(&(xDataHd.VerticesNum), pXData, sizeof(int));
    pXData += sizeof(int);
    //"  array  Vector    Vertices[VerticesNum];\n"
    D3DVECTOR* paD3DVECTOR_Vertices = NEW D3DVECTOR[xDataHd.VerticesNum];
    memcpy(paD3DVECTOR_Vertices, pXData, sizeof(D3DVECTOR)*xDataHd.VerticesNum);
    pXData += sizeof(D3DVECTOR)*xDataHd.VerticesNum;
    //"  array  ColorRGBA VertexColors[VerticesNum];\n"
    D3DCOLORVALUE* paD3DVECTOR_VertexColors = NEW D3DCOLORVALUE[xDataHd.VerticesNum];
    memcpy(paD3DVECTOR_VertexColors, pXData, sizeof(D3DCOLORVALUE)*xDataHd.VerticesNum);
    pXData += sizeof(D3DCOLORVALUE)*xDataHd.VerticesNum;
    //"  array  DWORD     InitUvPtnNo[VerticesNum];\n"
    int* paInt_InitUvPtnNo = NEW int[xDataHd.VerticesNum];
    memcpy(paInt_InitUvPtnNo, pXData, sizeof(int)*xDataHd.VerticesNum);
    pXData += sizeof(int)*xDataHd.VerticesNum;
    //"  array  FLOAT     InitScale[VerticesNum];\n"
    float* paFLOAT_InitScale = NEW float[xDataHd.VerticesNum];
    memcpy(paFLOAT_InitScale, pXData, sizeof(float)*xDataHd.VerticesNum);
    pXData += sizeof(float)*xDataHd.VerticesNum;

    //�ޔ�
    float model_fSquareSize = xDataHd.SquareSize;
    int model_texture_split_rowcol = xDataHd.TextureSplitRowCol;
    int model_vertices_num = xDataHd.VerticesNum;
    TRACE3("GgafDxModelManager::restorePointSpriteModel model_vertices_num="<<model_vertices_num);
    UINT model_size_vertices = sizeof(GgafDxPointSpriteModel::VERTEX)*model_vertices_num;
    UINT model_size_vertex_unit = sizeof(GgafDxPointSpriteModel::VERTEX);

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDxTextureConnection** model_papTextureConnection = NEW GgafDxTextureConnection*[1];
    model_papTextureConnection[0] = (GgafDxTextureConnection*)_pModelTextureManager->connect(xDataHd.TextureFile , this);
    GgafDxTexture* pTex = model_papTextureConnection[0]->peek();

    float texWidth  = (float)(pTex->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float texHeight = (float)(pTex->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
    if ((int)(texWidth*100000) != (int)(texHeight*100000)) {
        throwGgafCriticalException("[GgafDxModelManager::restorePointSpriteModel] �|�C���g�X�v���C�g�p�e�N�X�`��["<<pTex->getName()<<"]("<<texWidth<<"x"<<texHeight<<")�́A�����`�ł���K�v������܂��B");
    }
    FLOAT model_bounding_sphere_radius = 0;

    //���_�o�b�t�@�쐬
    GgafDxPointSpriteModel::VERTEX* model_paVtxBuffer_org = NEW GgafDxPointSpriteModel::VERTEX[model_vertices_num];

    float dis;
    for (int i = 0; i < model_vertices_num; i++) {
        model_paVtxBuffer_org[i].x = paD3DVECTOR_Vertices[i].x;
        model_paVtxBuffer_org[i].y = paD3DVECTOR_Vertices[i].y;
        model_paVtxBuffer_org[i].z = paD3DVECTOR_Vertices[i].z;
        model_paVtxBuffer_org[i].psize = (model_fSquareSize*model_texture_split_rowcol / texWidth) * paFLOAT_InitScale[i]; //PSIZE�ɂ̓s�N�Z���T�C�Y�ł͂Ȃ��{���𖄂ߍ��ށB
                                                                                                //�V�F�[�_�[�Ŋg��k���s�N�Z�����v�Z
        model_paVtxBuffer_org[i].color = D3DCOLOR_COLORVALUE(paD3DVECTOR_VertexColors[i].r,
                                                             paD3DVECTOR_VertexColors[i].g,
                                                             paD3DVECTOR_VertexColors[i].b,
                                                             paD3DVECTOR_VertexColors[i].a );
        model_paVtxBuffer_org[i].tu = (float)(paInt_InitUvPtnNo[i]);
        model_paVtxBuffer_org[i].tv = 0;

        dis = (FLOAT)(sqrt(model_paVtxBuffer_org[i].x * model_paVtxBuffer_org[i].x +
                           model_paVtxBuffer_org[i].y * model_paVtxBuffer_org[i].y +
                           model_paVtxBuffer_org[i].z * model_paVtxBuffer_org[i].z  )
                       + (((model_fSquareSize/PX_UNIT) * 1.41421356 ) / 2.0)
                     );

         if (model_bounding_sphere_radius < dis) {
             model_bounding_sphere_radius = dis;
         }
    }

    D3DMATERIAL9*   model_paMaterial = nullptr;
    if (prm_pPointSpriteModel->_pIDirect3DVertexBuffer9 == nullptr) {

        //���_�o�b�t�@�쐬
        hr = GgafDxGod::_pID3DDevice9->CreateVertexBuffer(
                model_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDxPointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(prm_pPointSpriteModel->_pIDirect3DVertexBuffer9),
                nullptr);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restorePointSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pPointSpriteModel->_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pPointSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, model_size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDxModelManager::restorePointSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pPointSpriteModel->_model_name);
        memcpy(pVertexBuffer, model_paVtxBuffer_org, model_size_vertices); //pVertexBuffer �� paVertex
        prm_pPointSpriteModel->_pIDirect3DVertexBuffer9->Unlock();
    }

    model_paMaterial = NEW D3DMATERIAL9[1];
    model_paMaterial[0].Diffuse.r = 1.0f;
    model_paMaterial[0].Diffuse.g = 1.0f;
    model_paMaterial[0].Diffuse.b = 1.0f;
    model_paMaterial[0].Diffuse.a = 1.0f;

    //���f���ɕێ�������
    prm_pPointSpriteModel->_paMaterial_default = model_paMaterial;
    prm_pPointSpriteModel->_papTextureConnection = model_papTextureConnection;
    prm_pPointSpriteModel->_num_materials = 1;
    prm_pPointSpriteModel->_fSquareSize = model_fSquareSize;
    prm_pPointSpriteModel->_fTexSize = texWidth;
    prm_pPointSpriteModel->_texture_split_rowcol = model_texture_split_rowcol;
    prm_pPointSpriteModel->_vertices_num = model_vertices_num;
    prm_pPointSpriteModel->_size_vertices = model_size_vertices;
    prm_pPointSpriteModel->_size_vertex_unit = model_size_vertex_unit;
    prm_pPointSpriteModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pPointSpriteModel->_bounding_sphere_radius = model_bounding_sphere_radius;
    pID3DXFileData->Unlock();
    GGAF_DELETEARR(paD3DVECTOR_Vertices);
    GGAF_DELETEARR(paD3DVECTOR_VertexColors);
    GGAF_DELETEARR(paInt_InitUvPtnNo);
    GGAF_DELETEARR(paFLOAT_InitScale);

    GGAF_RELEASE_BY_FROCE(pID3DXFileData);
    GGAF_RELEASE(pID3DXFileEnumObject);
}


GgafResourceConnection<GgafDxModel>* GgafDxModelManager::processCreateConnection(char* prm_idstr, GgafDxModel* prm_pResource) {
    TRACE3(" GgafDxModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxModelConnection* p = NEW GgafDxModelConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return p;
}

GgafDxModelManager::~GgafDxModelManager() {
    TRACE3("GgafDxModelManager::~GgafDxModelManager() start-->");
    GGAF_RELEASE(_pID3DXFile_sprx);
    GGAF_RELEASE(_pID3DXFile_psprx);
    GGAF_DELETE(_pModelTextureManager);
    TRACE3("GgafDxModelManager::releaseAll() ���邯�ǂ��A�����ł͊��ɉ������������̂��Ȃ��͂��ł�");
    releaseAll();
}

void GgafDxModelManager::restoreAll() {
    TRACE3("GgafDxModelManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
    TRACE3("restoreAll pCurrent="<<pCurrent);
    while (pCurrent) {
        pCurrent->peek()->restore();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDxModelManager::restoreAll() end<--");
}

void GgafDxModelManager::onDeviceLostAll() {
    TRACE3("GgafDxModelManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
    TRACE3("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent) {
        _TRACE_("GgafDxModelManager::onDeviceLostAll ["<<pCurrent->peek()->_model_name<<"] onDeviceLost begin");
        pCurrent->peek()->onDeviceLost();
        _TRACE_("GgafDxModelManager::onDeviceLostAll ["<<pCurrent->peek()->_model_name<<"] onDeviceLost end");
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDxModelManager::onDeviceLostAll() end<--");
}

void GgafDxModelManager::releaseAll() {
    TRACE3("GgafDxModelManager::releaseAll() start-->");
    GgafResourceConnection<GgafDxModel>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->release();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDxModelManager::releaseAll() end<--");
}

float GgafDxModelManager::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
    Frm::Vector V0;
    Frm::Vector V1;
    Frm::Vector V2;
    V0.x = v0.data[0]; V0.y = v0.data[1]; V0.z = v0.data[2];
    V1.x = v1.data[0]; V1.y = v1.data[1]; V1.z = v1.data[2];
    V2.x = v2.data[0]; V2.y = v2.data[1]; V2.z = v2.data[2];
    Frm::Vector V;
    V = V2 - V1;
    Frm::Vector W;
    W = V0 - V1;
    //�x�N�g�� V W �̐����p�����߂�
    //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
    //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
    //    �Ƃ����V�AW�x�N�g�����Ȃ��p��
    //    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
    //        =(vx*wx+vy*wy+vz*wz)
    //         �����[�g(vx^2+vy^2+vz^2)�����[�g(wx^2+wy^2+wz^2)
    float DOT, LV, LW, cosV1;
    //TRACE3("V=("<<V.x<<"."<<V.y<<","<<V.z<<")");
    //TRACE3("W=("<<W.x<<"."<<W.y<<","<<W.z<<")");
    DOT = V.Dot(W);
    LV = V.Abs();
    LW = W.Abs();
    cosV1 = DOT / LV / LW;
    if (ZEROf_EQ(cosV1)) {
        return (float)PI/2;
    } else {
        return cosV1;
    }

}

char* GgafDxModelManager::obtainSpriteFmtX(XFILE_SPRITE_FMT* pSpriteFmt_out, char* pLockedData) {
   memcpy(&(pSpriteFmt_out->width), pLockedData, sizeof(float));           pLockedData += sizeof(float);
   memcpy(&(pSpriteFmt_out->height), pLockedData, sizeof(float));          pLockedData += sizeof(float);
   strcpy(pSpriteFmt_out->texture_file, pLockedData);                      pLockedData += (sizeof(char) * (strlen(pSpriteFmt_out->texture_file)+1));
   memcpy(&(pSpriteFmt_out->row_texture_split), pLockedData, sizeof(int)); pLockedData += sizeof(int);
   memcpy(&(pSpriteFmt_out->col_texture_split), pLockedData, sizeof(int)); pLockedData += sizeof(int);
   return pLockedData;
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
