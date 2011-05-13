
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

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


int GgafDx9ModelManager::_id_max = 0;
GgafDx9Model* GgafDx9ModelManager::_pModelLastDraw = NULL;
GgafDx9ModelManager::GgafDx9ModelManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDx9Model> (prm_manager_name) {

    //�e�N�X�`���}�l�W���[
    _pTextureManager = NEW GgafDx9TextureManager("GgafDx9TextureManager");
    //�|���S����`�t�@�C���Ǎ���
    HRESULT hr;
    DirectXFileCreate( &_pIDirectXFile_sprx );
    char* paChar_SpriteModelineTemplate = GgafUtil::getFileText(CFG_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_spritemodel_define.x");
    if (paChar_SpriteModelineTemplate == NULL) {
        throwGgafCriticalException("[GgafDx9ModelManager::GgafDx9ModelManager] �X�v���C�g���Ǎ��݃e���v���[�g\""<<CFG_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\" ���J���܂���B");
    }
    hr = _pIDirectXFile_sprx->RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::GgafDx9ModelManager] RegisterTemplates�Ɏ��s���܂����B\""<<CFG_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\"���m�F���ĉ������B");
    }
    DELETE_IMPOSSIBLE_NULL(paChar_SpriteModelineTemplate);

    //�|���S����`�t�@�C���Ǎ���
    DirectXFileCreate( &_pIDirectXFile_psprx );
    char* paChar_PointSpriteModelineTemplate = GgafUtil::getFileText(CFG_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_pointspritemodel_define.x");
    if (paChar_PointSpriteModelineTemplate == NULL) {
        throwGgafCriticalException("[GgafDx9ModelManager::GgafDx9ModelManager] �|�C���g�X�v���C�g���Ǎ��݃e���v���[�g\""<<CFG_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_pointspritemodel_define.x\" ���J���܂���B");
    }
    hr = _pIDirectXFile_psprx->RegisterTemplates(paChar_PointSpriteModelineTemplate, (DWORD)(strlen(paChar_PointSpriteModelineTemplate)));
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::GgafDx9ModelManager] RegisterTemplates�Ɏ��s���܂����B\""<<CFG_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_pointspritemodel_define.x\"���m�F���ĉ������B");
    }
    DELETE_IMPOSSIBLE_NULL(paChar_PointSpriteModelineTemplate);

}

GgafDx9Model* GgafDx9ModelManager::processCreateResource(char* prm_idstr, void* prm_p) {
    //�U�蕪��
    char model_type = *prm_idstr; //���ꕶ��
    char* model_name = prm_idstr + 2; //�R�����ڈȍ~
    GgafDx9Model* pResourceModel;
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
            pResourceModel = createD3DXMeshModel("cube", D3DXMESH_SYSTEMMEM);
            break;
        case 'P':
            //PointSpriteModel
            pResourceModel = createPointSpriteModel(model_name);
            break;
        default:
            TRACE3("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����Ȏ�ʂ͂���܂���");
            throwGgafCriticalException("GgafDx9ModelManager::processCreateResource("<<prm_idstr<<") ����ȃ��f����ʂ͒m��܂���");
            pResourceModel = NULL;
            break;
    }
    return pResourceModel;
}

GgafDx9D3DXMeshModel* GgafDx9ModelManager::createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions) {
    GgafDx9D3DXMeshModel* pD3DXMeshModel_New = NEW GgafDx9D3DXMeshModel(prm_model_name, prm_dwOptions);
    restoreD3DXMeshModel(pD3DXMeshModel_New);
    return pD3DXMeshModel_New;
}

GgafDx9D3DXAniMeshModel* GgafDx9ModelManager::createD3DXAniMeshModel(char* prm_model_name) {
    GgafDx9D3DXAniMeshModel* pD3DXAniMeshModel_New = NEW GgafDx9D3DXAniMeshModel(prm_model_name);
    restoreD3DXAniMeshModel(pD3DXAniMeshModel_New);
    return pD3DXAniMeshModel_New;
}

GgafDx9SpriteModel* GgafDx9ModelManager::createSpriteModel(char* prm_model_name) {
    GgafDx9SpriteModel* pSpriteModel_New = NEW GgafDx9SpriteModel(prm_model_name);
    restoreSpriteModel(pSpriteModel_New);
    return pSpriteModel_New;
}

GgafDx9SpriteSetModel* GgafDx9ModelManager::createSpriteSetModel(char* prm_model_name) {
    GgafDx9SpriteSetModel* pSpriteSetModel_New = NEW GgafDx9SpriteSetModel(prm_model_name);
    restoreSpriteSetModel(pSpriteSetModel_New);
    return pSpriteSetModel_New;
}

GgafDx9BoardModel* GgafDx9ModelManager::createBoardModel(char* prm_model_name) {
    GgafDx9BoardModel* pBoardModel_New = NEW GgafDx9BoardModel(prm_model_name);
    restoreBoardModel(pBoardModel_New);
    return pBoardModel_New;
}

GgafDx9BoardSetModel* GgafDx9ModelManager::createBoardSetModel(char* prm_model_name) {
    GgafDx9BoardSetModel* pBoardSetModel_New = NEW GgafDx9BoardSetModel(prm_model_name);
    restoreBoardSetModel(pBoardSetModel_New);
    return pBoardSetModel_New;
}

GgafDx9MeshModel* GgafDx9ModelManager::createMeshModel(char* prm_model_name) {
    GgafDx9MeshModel* pMeshModel_New = NEW GgafDx9MeshModel(prm_model_name);
    restoreMeshModel(pMeshModel_New);
    return pMeshModel_New;
}

GgafDx9MeshSetModel* GgafDx9ModelManager::createMeshSetModel(char* prm_model_name) {
    GgafDx9MeshSetModel* pMeshSetModel_New = NEW GgafDx9MeshSetModel(prm_model_name);
    restoreMeshSetModel(pMeshSetModel_New);
    return pMeshSetModel_New;
}

GgafDx9CubeMapMeshModel* GgafDx9ModelManager::createCubeMapMeshModel(char* prm_model_name) {
    GgafDx9CubeMapMeshModel* pMeshCubeMapModel_New = NEW GgafDx9CubeMapMeshModel(prm_model_name);
    restoreMeshModel((GgafDx9MeshModel*)pMeshCubeMapModel_New);
    return pMeshCubeMapModel_New;
}

GgafDx9CubeMapMeshSetModel* GgafDx9ModelManager::createCubeMapMeshSetModel(char* prm_model_name) {
    GgafDx9CubeMapMeshSetModel* pMeshCubeMapSetModel_New = NEW GgafDx9CubeMapMeshSetModel(prm_model_name);
    restoreMeshSetModel((GgafDx9MeshSetModel*)pMeshCubeMapSetModel_New);
    return pMeshCubeMapSetModel_New;
}


GgafDx9MorphMeshModel* GgafDx9ModelManager::createMorphMeshModel(char* prm_model_name) {
    // "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
    // ������prm_model_name �� "4/xxxxx" �Ƃ���������ɂȂ��Ă���B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c���B
    GgafDx9MorphMeshModel* pMorphMeshModel_New = NEW GgafDx9MorphMeshModel(prm_model_name);
    restoreMorphMeshModel(pMorphMeshModel_New);
    return pMorphMeshModel_New;
}

GgafDx9CubeMapMorphMeshModel* GgafDx9ModelManager::createCubeMapMorphMeshModel(char* prm_model_name) {
    // "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V����1�A���[�t�^�[�Q�b�g�̃��b�V����4�Ƃ����Ӗ�
    // ������prm_model_name �� "4/xxxxx" �Ƃ���������ɂȂ��Ă���B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c���B
    GgafDx9CubeMapMorphMeshModel* pCubeMapMorphMeshModel_New = NEW GgafDx9CubeMapMorphMeshModel(prm_model_name);
    restoreMorphMeshModel((GgafDx9MorphMeshModel*)pCubeMapMorphMeshModel_New);
    return pCubeMapMorphMeshModel_New;
}


GgafDx9PointSpriteModel* GgafDx9ModelManager::createPointSpriteModel(char* prm_model_name) {
    GgafDx9PointSpriteModel* pPointSpriteModel_New = NEW GgafDx9PointSpriteModel(prm_model_name);
    restorePointSpriteModel(pPointSpriteModel_New);
    return pPointSpriteModel_New;
}

void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //�yGgafDx9MeshModel�č\�z�i���������j�����T�v�z
    //�P�j���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �� new
    //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDx9MeshModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E���_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���_�C���f�b�N�X�o�b�t�@�̎ʂ�
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A����)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A����)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)


    string xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�
    HRESULT hr;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = NULL;
    Frm::Mesh*    model_pMeshesFront = NULL;

    GgafDx9MeshModel::INDEXPARAM* model_paIndexParam = NULL;
    GgafDx9MeshModel::VERTEX*     model_paVtxBuffer_org = NULL;
    WORD*                         model_paIdxBuffer_org = NULL;
    D3DMATERIAL9*                 model_paD3DMaterial9 = NULL;
    GgafDx9TextureConnection**    model_papTextureCon = NULL;
    int nVertices = 0;
    int nFaces = 0;
    int nFaceNormals = 0;

    if (prm_pMeshModel->_pModel3D == NULL) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDx9ModelManager::restoreMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }
        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16* paNumVertices = NEW uint16[nMesh];
        int index_Mesh = 0;
        for (list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }

        model_pModel3D->ConcatenateMeshes(); //���b�V�����q����

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices; //���b�V���A����̑����_��
        nFaces = model_pMeshesFront->_nFaces;       //���b�V���A����̑��ʐ�
        nFaceNormals = model_pMeshesFront->_nFaceNormals; //���b�V���A����̑��@����
        model_paVtxBuffer_org = NEW GgafDx9MeshModel::VERTEX[nVertices];
        prm_pMeshModel->_size_vertices = sizeof(GgafDx9MeshModel::VERTEX) * nVertices;
        prm_pMeshModel->_size_vertex_unit = sizeof(GgafDx9MeshModel::VERTEX);
        int nTextureCoords = model_pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //���_�o�b�t�@�쐬�J�n�I
        //�@���ȊO�ݒ�
        FLOAT model_radius_bounding_sphere;
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

            //����
            model_radius_bounding_sphere = (FLOAT)(GgafDx9Util::sqrt_fast(model_paVtxBuffer_org[i].x * model_paVtxBuffer_org[i].x +
                                                 model_paVtxBuffer_org[i].y * model_paVtxBuffer_org[i].y +
                                                 model_paVtxBuffer_org[i].z * model_paVtxBuffer_org[i].z));
            if (prm_pMeshModel->_radius_bounding_sphere < model_radius_bounding_sphere) {
                prm_pMeshModel->_radius_bounding_sphere = model_radius_bounding_sphere;
            }
        }



        //�@���ݒ�B
        //���L���_�̖@���͕��ω������݂�I
        //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
        //���L���_�ɁA�ʂ������悤�ȕ��ʂɏW�������ꍇ�A�P���ɉ��Z���Ėʐ��Ŋ��镽�ω�������Ɩ@���͕΂��Ă��܂��B
        //�����ŁA���L���_�@���ւ̉e���x�����i���j���A���̖ʖ@������������ʂ̒��_�p�̑傫���Ō��߂�悤�ɂ����B
        //�@���̉e���x���� �� ���̖@�����������钸�_�̐����p �^ ���̒��_�ɂԂ牺����Sface�̐����p���v
        //�Ƃ����B�Ō�ɐ��K������B

        float* paRad = NEW float[nFaces*3];
        float* paRadSum_Vtx = NEW float[nVertices];
        for (int i = 0; i < nVertices; i++) {
            paRadSum_Vtx[i] = 0;
        }
        std::fill_n(paRadSum_Vtx, nVertices, 0);
        static unsigned short indexVertices_per_Face[3];
        static unsigned short indexNormals_per_Face[3];
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
                indexVertices_per_Face[j] = model_pMeshesFront->_Faces[i].data[j];
                //�ʂɑ΂���@���C���f�b�N�X�R��
                if (nFaceNormals > i) {
                    indexNormals_per_Face[j] = model_pMeshesFront->_FaceNormals[i].data[j];
                } else {
                    //�@���������ꍇ
                    indexNormals_per_Face[j] = (unsigned short)0;
                }
            }

            //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
            paRad[i*3+0] = getRadv1_v0v1v2(
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                           );
            //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

            //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
            paRad[i*3+1] = getRadv1_v0v1v2(
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                           );
            //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

            //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
            paRad[i*3+2] = (float)(2*PI - (paRad[i*3+0] + paRad[i*3+1]));
            //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
        }

        static float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                indexVertices_per_Face[j] = model_pMeshesFront->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                if (nFaceNormals > i) {
                    indexNormals_per_Face[j] = model_pMeshesFront->_FaceNormals[i].data[j];
                } else {
                    //�@���������ꍇ
                    indexNormals_per_Face[j] = (unsigned short)0;
                }

            }
            if (nFaceNormals > i) {
                rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].x * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].y * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].z * rate);
                rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].x * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].y * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].z * rate);
                rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].x * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].y * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].z * rate);
            } else {
                //�@���������ꍇ�A�@�����v�Z���č�肾���B

                //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                int indexVertices1 = model_pMeshesFront->_Faces[i].data[0];
                int indexVertices2 = model_pMeshesFront->_Faces[i].data[1];
                int indexVertices3 = model_pMeshesFront->_Faces[i].data[2];
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

                rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].nx += (Plane.a * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].ny += (Plane.b * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[0]].nz += (Plane.c * rate);
                rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].nx += (Plane.a * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].ny += (Plane.b * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[1]].nz += (Plane.c * rate);
                rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].nx += (Plane.a * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].ny += (Plane.b * rate);
                model_paVtxBuffer_org[indexVertices_per_Face[2]].nz += (Plane.c * rate);
            }
        }


        int n = 0;
        int nVertices_begin = 0;
        int nVertices_end = 0;
        for (std::list<Frm::Bone*>::iterator iteBone = model_pModel3D->_toplevel_Skelettons.begin() ;
                iteBone != model_pModel3D->_toplevel_Skelettons.end(); iteBone++) {

            _TRACE_("(*iteBone)->_Name="<<((*iteBone)->_Name));

            //X�t�@�C����FrameTransformMatrix(0�t���[���ڂ̏������A�j���[�V����)���l��
            if ((*iteBone)) {
                Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
                if (pMatPos == 0 || pMatPos== NULL || pMatPos->isIdentity()) {
                    //FrameTransformMatrix �͒P�ʍs��
                    _TRACE_("FrameTransformMatrix is Identity");
                } else {
                    _TRACE_("Execute FrameTransform!");
                    static D3DXMATRIX FrameTransformMatrix;
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

                    static D3DXVECTOR3 vecVertex;
                    static D3DXVECTOR3 vecNormal;
                    for (int i = nVertices_begin; i < nVertices_end; i++) {
                        vecVertex.x = model_paVtxBuffer_org[i].x;
                        vecVertex.y = model_paVtxBuffer_org[i].y;
                        vecVertex.z = model_paVtxBuffer_org[i].z;
                        D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                        vecNormal.x = model_paVtxBuffer_org[i].nx;
                        vecNormal.y = model_paVtxBuffer_org[i].ny;
                        vecNormal.z = model_paVtxBuffer_org[i].nz;
                        D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);

                        model_paVtxBuffer_org[i].x = vecVertex.x;
                        model_paVtxBuffer_org[i].y = vecVertex.y;
                        model_paVtxBuffer_org[i].z = vecVertex.z;
                        model_paVtxBuffer_org[i].nx = vecNormal.x;
                        model_paVtxBuffer_org[i].ny = vecNormal.y;
                        model_paVtxBuffer_org[i].nz = vecNormal.z;
                    }
                }
            }
            n++;
        }
        DELETE_IMPOSSIBLE_NULL(paNumVertices);

        //�Ō�ɖ@�����K�����Đݒ�
        static D3DXVECTOR3 vec;
        for (int i = 0; i < nVertices; i++) {
            vec.x = model_paVtxBuffer_org[i].nx;
            vec.y = model_paVtxBuffer_org[i].ny;
            vec.z = model_paVtxBuffer_org[i].nz;
            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                model_paVtxBuffer_org[i].nx = 0;
                model_paVtxBuffer_org[i].ny = 0;
                model_paVtxBuffer_org[i].nz = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                model_paVtxBuffer_org[i].nx = vec.x;
                model_paVtxBuffer_org[i].ny = vec.y;
                model_paVtxBuffer_org[i].nz = vec.z;
            }
        }
//        TRACE3("�@�����K����----------------------------");
//        for (int i = 0; i < nVertices; i++) {
//            TRACE3("["<<i<<"]=" << model_paVtxBuffer_org[i].x << "\t, " << model_paVtxBuffer_org[i].y << "\t, " << model_paVtxBuffer_org[i].z << "\t, " << model_paVtxBuffer_org[i].nx << "\t, " << model_paVtxBuffer_org[i].ny << "\t, " << model_paVtxBuffer_org[i].nz << "\t, " << model_paVtxBuffer_org[i].tu << "\t, " << model_paVtxBuffer_org[i].tv);
//        }
//        TRACE3("--------------------------------------");

        //�C���f�b�N�X�o�b�t�@�o�^
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //�}�e���A�����X�g
//        UINT aMaterialsGrp = UINT[nFaces];
//        for (int i = 0; i < nFaces; i++) {
//            aMaterialsGrp[i] =  model_pMeshesFront->_FaceMaterials[i];
//        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDx9MeshModel::INDEXPARAM* paParam = NEW GgafDx9MeshModel::INDEXPARAM[nFaces]; //�ō��Ƀ}�e���A�����o���o���������ꍇnFaces�K�v

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

        model_paIndexParam = NEW GgafDx9MeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            model_paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            model_paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            model_paIndexParam[i].MinIndex = paParam[i].MinIndex;
            model_paIndexParam[i].NumVertices = paParam[i].NumVertices;
            model_paIndexParam[i].StartIndex = paParam[i].StartIndex;
            model_paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        prm_pMeshModel->_nMaterialListGrp = paramno;
        delete[] paRad;
        delete[] paRadSum_Vtx;
        delete[] paParam;
    }

    if (prm_pMeshModel->_pIDirect3DVertexBuffer9 == NULL) {

        //���_�o�b�t�@�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pMeshModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDx9MeshModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pMeshModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pMeshModel->_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pMeshModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pMeshModel->_size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pMeshModel->_model_name);
        memcpy(pVertexBuffer, model_paVtxBuffer_org, prm_pMeshModel->_size_vertices); //pVertexBuffer �� paVertex
        prm_pMeshModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMeshModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = model_pMeshesFront->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMeshModel->_pIDirect3DIndexBuffer9),
                                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , model_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A�����J�E���g
    int model_nMaterials = 0;
    for (list<Frm::Material*>::iterator material = model_pMeshesFront->_Materials.begin(); material != model_pMeshesFront->_Materials.end(); material++) {
        model_nMaterials++;
    }

    model_paD3DMaterial9 = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureCon = NEW GgafDx9TextureConnection*[model_nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = model_pMeshesFront->_Materials.begin(); material != model_pMeshesFront->_Materials.end(); material++) {
        model_paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        model_paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        model_paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        model_paD3DMaterial9[n].Specular.a = 1.000000f;
        model_paD3DMaterial9[n].Power =  (*material)->_power;

        model_paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        model_paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        model_paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        model_paD3DMaterial9[n].Emissive.a = 1.000000f;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
        n++;
    }

    //���f���ɕێ�������
    prm_pMeshModel->_pModel3D = model_pModel3D;
    prm_pMeshModel->_pMeshesFront = model_pMeshesFront;

    prm_pMeshModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMeshModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pMeshModel->_paIndexParam = model_paIndexParam;
    prm_pMeshModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pMeshModel->_papTextureCon = model_papTextureCon;
    prm_pMeshModel->_dwNumMaterials = model_nMaterials;

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
//            a = model_paD3DMaterial9[i].Diffuse.a;
//            r = model_paD3DMaterial9[i].Diffuse.r;
//            g = model_paD3DMaterial9[i].Diffuse.g;
//            b = model_paD3DMaterial9[i].Diffuse.b;
//            _TRACE_("nMaterial["<<i<<"] Diffuse(rgba)=("<<r<<","<<g<<","<<b<<","<<a<<")");
//            a = model_paD3DMaterial9[i].Ambient.a;
//            r = model_paD3DMaterial9[i].Ambient.r;
//            g = model_paD3DMaterial9[i].Ambient.g;
//            b = model_paD3DMaterial9[i].Ambient.b;
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

void GgafDx9ModelManager::restoreMorphMeshModel(GgafDx9MorphMeshModel* prm_pMorphMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreMorphMeshModel(" << prm_pMorphMeshModel->_model_name << ")");
    //�yGgafDx9MorphMeshModel�č\�z�i���������j�����T�v�z
    //��{�I�ɂ�restoreMeshModel�̏�����������i�z��j�𑝂₵���悤�Ȃ���
    //�P�j�v���C�}���{���[�t�^�[�Q�b�g��N �́A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ ���쐬
    //�Q�j���ꂼ���X�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDx9MeshModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E�v���C�}�����b�V�����_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���[�t�^�[�Q�b�g��N �̒��_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���_�C���f�b�N�X�o�b�t�@�̎ʂ��i�v���C�}�����b�V���̂݁j
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A�����B�v���C�}�����b�V���̂�)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω��������B�v���C�}�����b�V���̂�)
    int morph_target_num = prm_pMorphMeshModel->_morph_target_num;

    string* paXfileName = NEW string[morph_target_num+1];

    for(int i = 0; i < morph_target_num+1; i++) {
        char* xfilename_base = prm_pMorphMeshModel->_model_name + 2; //�Q�����ڈȍ~  "2/ceres" �� "ceres"
        paXfileName[i] = CFG_PROPERTY(DIR_MESH_MODEL) + string(xfilename_base) + "_" + (char)('0'+i) + ".x"; //"ceres_0.x"�ƂȂ�
    }
    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X* paIOX = NULL;
    Frm::Model3D**                         model_papModel3D = NULL;
    Frm::Mesh**                            model_papMeshesFront = NULL;

    GgafDx9MorphMeshModel::INDEXPARAM*     model_paIndexParam = NULL;
    GgafDx9MorphMeshModel::VERTEX_PRIMARY* model_paVtxBuffer_org_primary = NULL;
    GgafDx9MorphMeshModel::VERTEX_MORPH**  model_papaVtxBuffer_org_morph = NULL;
    WORD*                                  model_paIdxBuffer_org = NULL;
    D3DMATERIAL9*                          model_paD3DMaterial9 = NULL;

    GgafDx9TextureConnection** model_papTextureCon = NULL;

    if (prm_pMorphMeshModel->_papModel3D == NULL) {
        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        model_papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        model_papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        model_papaVtxBuffer_org_morph = NEW GgafDx9MorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices = 0;
        int nTextureCoords = 0;
        int nFaces = 0;
        int nFaceNormals = 0;
        FLOAT model_radius_bounding_sphere;
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            model_papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfileName[pattern], model_papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("[GgafDx9ModelManager::restoreMorphMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<paXfileName[pattern]);
            }
            //���b�V������������O�ɁA�����m�ۂ��Ă���
            int nMesh = (int)model_papModel3D[pattern]->_Meshes.size();
            uint16* paNumVertices = NEW uint16[nMesh];
            int index_Mesh = 0;
            for (list<Frm::Mesh*>::iterator iteMeshes = model_papModel3D[pattern]->_Meshes.begin();
                    iteMeshes != model_papModel3D[pattern]->_Meshes.end(); iteMeshes++) {
                paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
                index_Mesh++;
            }
            model_papModel3D[pattern]->ConcatenateMeshes(); //���b�V�����q����
            model_papMeshesFront[pattern] = model_papModel3D[pattern]->_Meshes.front();
//            _TRACE_("---");
            nVertices = model_papMeshesFront[pattern]->_nVertices;
//            _TRACE_("pattern="<<pattern<<"/nVertices="<<nVertices);
            nTextureCoords = model_papMeshesFront[pattern]->_nTextureCoords;
//            _TRACE_("pattern="<<pattern<<"/nTextureCoords="<<nTextureCoords);
            nFaces = model_papMeshesFront[pattern]->_nFaces;
//            _TRACE_("pattern="<<pattern<<"/nFaces="<<nFaces);
            nFaceNormals = model_papMeshesFront[pattern]->_nFaceNormals;
//            _TRACE_("pattern="<<pattern<<"/nFaceNormals="<<nFaceNormals);

            if (nVertices*(morph_target_num+1) > 65535) {
                throwGgafCriticalException("[GgafDx9ModelManager::restoreMorphMeshModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMorphMeshModel->getName()<<"  nVertices:"<<nVertices<<"  �Z�b�g��:"<<(morph_target_num+1));
            }
//            if (nFaces * 3 * (morph_target_num+1) > 65535) {
//                throwGgafCriticalException("[GgafDx9ModelManager::restoreMorphMeshModel] ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMorphMeshModel->getName()<<"  nFaces:"<<nFaces<<"(*3)  �Z�b�g��:"<<(morph_target_num+1));
//            }

            if (pattern == 0) {
                //�v���C�}�����b�V��
                model_paVtxBuffer_org_primary = NEW GgafDx9MorphMeshModel::VERTEX_PRIMARY[nVertices];
                prm_pMorphMeshModel->_size_vertices_primary = sizeof(GgafDx9MorphMeshModel::VERTEX_PRIMARY) * nVertices;
                prm_pMorphMeshModel->_size_vertex_unit_primary = sizeof(GgafDx9MorphMeshModel::VERTEX_PRIMARY);
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
                    model_radius_bounding_sphere = (FLOAT)(GgafDx9Util::sqrt_fast(model_paVtxBuffer_org_primary[i].x * model_paVtxBuffer_org_primary[i].x +
                                                         model_paVtxBuffer_org_primary[i].y * model_paVtxBuffer_org_primary[i].y +
                                                         model_paVtxBuffer_org_primary[i].z * model_paVtxBuffer_org_primary[i].z));
                    if (prm_pMorphMeshModel->_radius_bounding_sphere < model_radius_bounding_sphere) {
                        prm_pMorphMeshModel->_radius_bounding_sphere = model_radius_bounding_sphere;
                    }
                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                model_papaVtxBuffer_org_morph[pattern-1] = NEW GgafDx9MorphMeshModel::VERTEX_MORPH[nVertices];
                prm_pMorphMeshModel->_size_vertices_morph = sizeof(GgafDx9MorphMeshModel::VERTEX_MORPH) * nVertices;
                prm_pMorphMeshModel->_size_vertex_unit_morph = sizeof(GgafDx9MorphMeshModel::VERTEX_MORPH);
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

            int nTextureCoords = model_papMeshesFront[pattern]->_nTextureCoords;
            if (nVertices < nTextureCoords) {
                TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
                TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<paXfileName[pattern]);
            }

            //�@���ݒ�B
            //restoreMeshModel�̐����Ɠ��l
            float* paRad = NEW float[nFaces*3];
            float* paRadSum_Vtx = NEW float[nVertices];
            for (int i = 0; i < nVertices; i++) {
                paRadSum_Vtx[i] = 0;
            }
            std::fill_n(paRadSum_Vtx, nVertices, 0);
            static unsigned short indexVertices_per_Face[3];
            static unsigned short indexNormals_per_Face[3];
            for (int i = 0; i < nFaces; i++) {
                for (int j = 0; j < 3; j++) {
                    //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
                    indexVertices_per_Face[j] = model_papMeshesFront[pattern]->_Faces[i].data[j];
                    //�ʂɑ΂���@���C���f�b�N�X�R��
                    if (nFaceNormals > i) {
                        indexNormals_per_Face[j] = model_papMeshesFront[pattern]->_FaceNormals[i].data[j];
                    } else {
                        //�@���������ꍇ
                        indexNormals_per_Face[j] = (unsigned short)0;
                    }
                }

                //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
                paRad[i*3+0] = getRadv1_v0v1v2(
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[2]],
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[0]],
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[1]]
                               );
                //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

                //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
                paRad[i*3+1] = getRadv1_v0v1v2(
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[0]],
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[1]],
                                 model_papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[2]]
                               );
                //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

                //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
                paRad[i*3+2] = (float)(2*PI - (paRad[i*3+0] + paRad[i*3+1]));
                //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
            }

            float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
            for (int i = 0; i < nFaces; i++) {
                for (int j = 0; j < 3; j++) {
                    indexVertices_per_Face[j] = model_papMeshesFront[pattern]->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                    if (nFaceNormals > i) {
                        indexNormals_per_Face[j] = model_papMeshesFront[pattern]->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
                    } else {
                        //�@���������ꍇ
                        indexNormals_per_Face[j] = (unsigned short)0;
                    }
                }
                if (nFaceNormals > i) {
                    rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                    if (pattern == 0) { //�v���C�}�����b�V��
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].x * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].y * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].z * rate);
                    } else {            //���[�t�^�[�Q�b�g���b�V��
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].x * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].y * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].z * rate);
                    }
                    rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                    if (pattern == 0) { //�v���C�}�����b�V��
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].x * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].y * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].z * rate);
                    } else {            //���[�t�^�[�Q�b�g���b�V��
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].x * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].y * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].z * rate);
                    }
                    rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                    if (pattern == 0) { //�v���C�}�����b�V��
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].x * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].y * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].z * rate);
                    } else {            //���[�t�^�[�Q�b�g���b�V��
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nx += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].x * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].ny += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].y * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nz += (model_papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].z * rate);
                    }
                } else {
                    //�@���������ꍇ
                    int indexVertices1 = model_papMeshesFront[pattern]->_Faces[i].data[0];
                    int indexVertices2 = model_papMeshesFront[pattern]->_Faces[i].data[1];
                    int indexVertices3 = model_papMeshesFront[pattern]->_Faces[i].data[2];
                    D3DXVECTOR3 v1 = D3DXVECTOR3(
                        model_papMeshesFront[pattern]->_Vertices[indexVertices1].data[0],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices1].data[1],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices1].data[2]
                    );
                    D3DXVECTOR3 v2 = D3DXVECTOR3(
                        model_papMeshesFront[pattern]->_Vertices[indexVertices2].data[0],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices2].data[1],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices2].data[2]
                    );
                    D3DXVECTOR3 v3 = D3DXVECTOR3(
                        model_papMeshesFront[pattern]->_Vertices[indexVertices3].data[0],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices3].data[1],
                        model_papMeshesFront[pattern]->_Vertices[indexVertices3].data[2]
                    );

                    D3DXPLANE Plane;
                    // 3 �̓_���畽�ʂ��쐬
                    D3DXPlaneFromPoints(&Plane, &v1, &v2, &v3);
                    //���K����������(�@��)���Z�o
                    D3DXPlaneNormalize(&Plane, &Plane);

                    if (pattern == 0) { //�v���C�}�����b�V��
                        rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].nx += (Plane.a * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].ny += (Plane.b * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[0]].nz += (Plane.c * rate);
                        rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].nx += (Plane.a * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].ny += (Plane.b * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[1]].nz += (Plane.c * rate);
                        rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].nx += (Plane.a * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].ny += (Plane.b * rate);
                        model_paVtxBuffer_org_primary[indexVertices_per_Face[2]].nz += (Plane.c * rate);
                    } else {
                        rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nx += (Plane.a * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].ny += (Plane.b * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nz += (Plane.c * rate);
                        rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nx += (Plane.a * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].ny += (Plane.b * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nz += (Plane.c * rate);
                        rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nx += (Plane.a * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].ny += (Plane.b * rate);
                        model_papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nz += (Plane.c * rate);
                    }
                }
            }
            //X�t�@�C����FrameTransformMatrix(0�t���[���ڂ̏������A�j���[�V����)���l��
            int n = 0;
            int nVertices_begin = 0;
            int nVertices_end = 0;
            D3DXMATRIX FrameTransformMatrix;

            for (std::list<Frm::Bone*>::iterator iteBone = model_papModel3D[pattern]->_toplevel_Skelettons.begin() ;
                    iteBone != model_papModel3D[pattern]->_toplevel_Skelettons.end(); iteBone++) {
                _TRACE_("(*iteBone)->_Name="<<((*iteBone)->_Name));

                if ((*iteBone)) {
                    Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
                    if (pMatPos == 0 || pMatPos== NULL || pMatPos->isIdentity()) {
                        //FrameTransformMatrix �͒P�ʍs��
                        _TRACE_("pattern=["<<pattern<<"] FrameTransformMatrix is Identity");
                    } else {
                        _TRACE_("pattern=["<<pattern<<"] Execute FrameTransform!");
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
                        if (pattern == 0) {
                            for (int i = nVertices_begin; i < nVertices_end; i++) {
                                vecVertex.x = model_paVtxBuffer_org_primary[i].x;
                                vecVertex.y = model_paVtxBuffer_org_primary[i].y;
                                vecVertex.z = model_paVtxBuffer_org_primary[i].z;
                                D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                                vecNormal.x = model_paVtxBuffer_org_primary[i].nx;
                                vecNormal.y = model_paVtxBuffer_org_primary[i].ny;
                                vecNormal.z = model_paVtxBuffer_org_primary[i].nz;
                                D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);

                                model_paVtxBuffer_org_primary[i].x = vecVertex.x;
                                model_paVtxBuffer_org_primary[i].y = vecVertex.y;
                                model_paVtxBuffer_org_primary[i].z = vecVertex.z;
                                model_paVtxBuffer_org_primary[i].nx = vecNormal.x;
                                model_paVtxBuffer_org_primary[i].ny = vecNormal.y;
                                model_paVtxBuffer_org_primary[i].nz = vecNormal.z;
                            }
                        } else {
                            for (int i = nVertices_begin; i < nVertices_end; i++) {
                                vecVertex.x = model_papaVtxBuffer_org_morph[pattern-1][i].x;
                                vecVertex.y = model_papaVtxBuffer_org_morph[pattern-1][i].y;
                                vecVertex.z = model_papaVtxBuffer_org_morph[pattern-1][i].z;
                                D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                                vecNormal.x = model_papaVtxBuffer_org_morph[pattern-1][i].nx;
                                vecNormal.y = model_papaVtxBuffer_org_morph[pattern-1][i].ny;
                                vecNormal.z = model_papaVtxBuffer_org_morph[pattern-1][i].nz;
                                D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);

                                model_papaVtxBuffer_org_morph[pattern-1][i].x = vecVertex.x;
                                model_papaVtxBuffer_org_morph[pattern-1][i].y = vecVertex.y;
                                model_papaVtxBuffer_org_morph[pattern-1][i].z = vecVertex.z;
                                model_papaVtxBuffer_org_morph[pattern-1][i].nx = vecNormal.x;
                                model_papaVtxBuffer_org_morph[pattern-1][i].ny = vecNormal.y;
                                model_papaVtxBuffer_org_morph[pattern-1][i].nz = vecNormal.z;
                            }
                        }
                    }
                }
                n++;
            }
            DELETE_IMPOSSIBLE_NULL(paNumVertices);

            //�Ō�ɖ@�����K�����Đݒ�
            D3DXVECTOR3 vec;
            for (int i = 0; i < nVertices; i++) {
                if (pattern == 0) { //�v���C�}�����b�V��
                    vec.x = model_paVtxBuffer_org_primary[i].nx;
                    vec.y = model_paVtxBuffer_org_primary[i].ny;
                    vec.z = model_paVtxBuffer_org_primary[i].nz;
                    if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                        model_paVtxBuffer_org_primary[i].nx = 0;
                        model_paVtxBuffer_org_primary[i].ny = 0;
                        model_paVtxBuffer_org_primary[i].nz = 0;
                    } else {
                        D3DXVec3Normalize( &vec, &vec);
                        model_paVtxBuffer_org_primary[i].nx = vec.x;
                        model_paVtxBuffer_org_primary[i].ny = vec.y;
                        model_paVtxBuffer_org_primary[i].nz = vec.z;
                    }
                } else {           //���[�t�^�[�Q�b�g���b�V��
                    vec.x = model_papaVtxBuffer_org_morph[pattern-1][i].nx;
                    vec.y = model_papaVtxBuffer_org_morph[pattern-1][i].ny;
                    vec.z = model_papaVtxBuffer_org_morph[pattern-1][i].nz;
                    if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                        model_papaVtxBuffer_org_morph[pattern-1][i].nx = 0;
                        model_papaVtxBuffer_org_morph[pattern-1][i].ny = 0;
                        model_papaVtxBuffer_org_morph[pattern-1][i].nz = 0;
                    } else {
                        D3DXVec3Normalize( &vec, &vec);
                        model_papaVtxBuffer_org_morph[pattern-1][i].nx = vec.x;
                        model_papaVtxBuffer_org_morph[pattern-1][i].ny = vec.y;
                        model_papaVtxBuffer_org_morph[pattern-1][i].nz = vec.z;
                    }
                }
            }
            delete[] paRad;
            delete[] paRadSum_Vtx;
        } //for (int pattern = 0; pattern < 2; pattern++)


        //�C���f�b�N�X�o�b�t�@�擾
        model_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            model_paIdxBuffer_org[i*3 + 0] = model_papMeshesFront[0]->_Faces[i].data[0];
            model_paIdxBuffer_org[i*3 + 1] = model_papMeshesFront[0]->_Faces[i].data[1];
            model_paIdxBuffer_org[i*3 + 2] = model_papMeshesFront[0]->_Faces[i].data[2];
        }

        //�}�e���A�����X�g
//        UINT aMaterialsGrp = UINT[nFaces];
//        for (int i = 0; i < nFaces; i++) {
//            aMaterialsGrp[i] =  model_pMeshesFront->_FaceMaterials[i];
//        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDx9MeshModel::INDEXPARAM* paParam = NEW GgafDx9MeshModel::INDEXPARAM[nFaces];

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

        model_paIndexParam = NEW GgafDx9MorphMeshModel::INDEXPARAM[paramno];
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

    if (prm_pMorphMeshModel->_pIDirect3DVertexDeclaration9 == NULL) {

        int elemnum = (4+(2*morph_target_num))+1; //D3DVERTEXELEMENT9 �\���̂̔z��v�f��
        D3DVERTEXELEMENT9* paDecl = NEW D3DVERTEXELEMENT9[elemnum];
                                                         // 4 = �v���C�}�����b�V��
                                                         // (2*morph_target_num) = ���[�t�^�[�Q�b�g���b�V��
                                                         // 1 = D3DDECL_END()
        //�v���C�}�����b�V�������_�t�H�[�}�b�g
        //FVF�͎g���Ȃ��̂ŁACreateVertexDeclaration��
        //TODO:���_�t�H�[�}�b�g�𖈉�\�z�ł͂Ȃ��āA���f�����ɕێ����������B
        //�v���C�}�������_�t�H�[�}�b�g
        //float x, y, z; // ���_���W
        paDecl[0].Stream = 0;
        paDecl[0].Offset = 0;
        paDecl[0].Type = D3DDECLTYPE_FLOAT3;
        paDecl[0].Method = D3DDECLMETHOD_DEFAULT;
        paDecl[0].Usage = D3DDECLUSAGE_POSITION;
        paDecl[0].UsageIndex = 0;
        //float nx, ny, nz; // �@��
        paDecl[1].Stream = 0;
        paDecl[1].Offset = sizeof(float)*3;
        paDecl[1].Type = D3DDECLTYPE_FLOAT3;
        paDecl[1].Method = D3DDECLMETHOD_DEFAULT;
        paDecl[1].Usage = D3DDECLUSAGE_NORMAL;
        paDecl[1].UsageIndex = 0;
        //DWORD color; // ���_�J���[
        paDecl[2].Stream = 0;
        paDecl[2].Offset = sizeof(float)*6;
        paDecl[2].Type = D3DDECLTYPE_D3DCOLOR;
        paDecl[2].Method = D3DDECLMETHOD_DEFAULT;
        paDecl[2].Usage = D3DDECLUSAGE_COLOR;
        paDecl[2].UsageIndex = 0;
        //float tu, tv; // �e�N�X�`�����W
        paDecl[3].Stream = 0;
        paDecl[3].Offset = sizeof(float)*6+sizeof(DWORD);
        paDecl[3].Type = D3DDECLTYPE_FLOAT2;
        paDecl[3].Method = D3DDECLMETHOD_DEFAULT;
        paDecl[3].Usage = D3DDECLUSAGE_TEXCOORD;
        paDecl[3].UsageIndex = 0;
        //���[�t�^�[�Q�b�g���b�V�������_�t�H�[�}�b�g
        for (int i = 4, s = 1; i < elemnum-1; i+=2, s++) {
            //float x, y, z; // ���_���W
            paDecl[i].Stream = s;
            paDecl[i].Offset = 0;
            paDecl[i].Type = D3DDECLTYPE_FLOAT3;
            paDecl[i].Method = D3DDECLMETHOD_DEFAULT;
            paDecl[i].Usage = D3DDECLUSAGE_POSITION;
            paDecl[i].UsageIndex = s;
            //float nx, ny, nz; // �@��
            paDecl[i+1].Stream = s;
            paDecl[i+1].Offset = sizeof(float)*3;
            paDecl[i+1].Type = D3DDECLTYPE_FLOAT3;
            paDecl[i+1].Method = D3DDECLMETHOD_DEFAULT;
            paDecl[i+1].Usage = D3DDECLUSAGE_NORMAL;
            paDecl[i+1].UsageIndex = s;
        }
        //D3DDECL_END()
        paDecl[elemnum-1].Stream = 0xFF;
        paDecl[elemnum-1].Offset = 0;
        paDecl[elemnum-1].Type = D3DDECLTYPE_UNUSED;
        paDecl[elemnum-1].Method = 0;
        paDecl[elemnum-1].Usage = 0;
        paDecl[elemnum-1].UsageIndex = 0;

        hr = GgafDx9God::_pID3DDevice9->CreateVertexDeclaration( paDecl, &(prm_pMorphMeshModel->_pIDirect3DVertexDeclaration9) );
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] GgafDx9God::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(prm_pMorphMeshModel->_model_name));
        //�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        DELETEARR_IMPOSSIBLE_NULL(paDecl);
    }

    //���_�o�b�t�@�쐬
    if (prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary == NULL) {
        prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[morph_target_num];
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {

            if (pattern == 0) {
                //�v���C�}�����_�o�b�t�@
                hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertices_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDx9MorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary),
                        NULL);
                checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i�v���C�}���j model="<<(prm_pMorphMeshModel->_model_name));
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Lock(0, prm_pMorphMeshModel->_size_vertices_primary, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i�v���C�}���j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, model_paVtxBuffer_org_primary, prm_pMorphMeshModel->_size_vertices_primary); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Unlock();
            } else {
                //���[�t�^�[�Q�b�g���_�o�b�t�@
                hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertices_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDx9MorphMeshModel::FVF,
                        D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        NULL);
                checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(prm_pMorphMeshModel->_model_name));
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, prm_pMorphMeshModel->_size_vertices_morph, (void**)&pVertexBuffer, 0);
                checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, model_papaVtxBuffer_org_morph[pattern-1], prm_pMorphMeshModel->_size_vertices_morph); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }


    //�C���f�b�N�X�o�b�t�@�f�[�^�쐬�i�v���C�}���A���[�t�^�[�Q�b�g���ɓ����j
    if (prm_pMorphMeshModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = model_papMeshesFront[0]->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMorphMeshModel->_pIDirect3DIndexBuffer9),
                                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMorphMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , model_paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A��
    //�}�e���A���̓v���C�}�����b�V���̃}�e���A�������A
    //�v���C�}���y�ёS���[�t�^�[�Q�b�g�̃}�e���A���Ƃ���B
    //�����model_papMeshesFront[0]�����g���A�c��͎g��Ȃ��B
    //TODO:�����I�ɂ̓��[�t�^�[�Q�b�g�ʂɃ}�e���A���ݒ�ł���Ε\���������B�������悤���B
    int model_nMaterials = 0;
    for (list<Frm::Material*>::iterator material =  model_papMeshesFront[0]->_Materials.begin();
            material !=  model_papMeshesFront[0]->_Materials.end(); material++) {
        model_nMaterials++;
    }

    model_paD3DMaterial9 = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureCon = NEW GgafDx9TextureConnection*[model_nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = model_papMeshesFront[0]->_Materials.begin(); material != model_papMeshesFront[0]->_Materials.end(); material++) {
        model_paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        model_paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        model_paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        model_paD3DMaterial9[n].Specular.a = 1.000000f;
        model_paD3DMaterial9[n].Power =  (*material)->_power;

        model_paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        model_paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        model_paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        model_paD3DMaterial9[n].Emissive.a = 1.000000f;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
        n++;
    }

    if (model_nMaterials != n) {
        TRACE3("GgafDx9ModelManager::restoreMorphMeshModel(" << prm_pMorphMeshModel->_model_name << ") ���Ȃ݂Ƀ}�e���A���������������ł��Bmodel_nMaterials="<<model_nMaterials<<"/n="<<n);
    }

    DELETEARR_IMPOSSIBLE_NULL(paIOX);
    DELETEARR_IMPOSSIBLE_NULL(paXfileName);

    //���f���ɕێ�������
    prm_pMorphMeshModel->_papModel3D = model_papModel3D;
    prm_pMorphMeshModel->_papMeshesFront = model_papMeshesFront;
    prm_pMorphMeshModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMorphMeshModel->_paVtxBuffer_org_primary = model_paVtxBuffer_org_primary;
    prm_pMorphMeshModel->_papaVtxBuffer_org_morph = model_papaVtxBuffer_org_morph;
    prm_pMorphMeshModel->_paIndexParam = model_paIndexParam;
    prm_pMorphMeshModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pMorphMeshModel->_papTextureCon = model_papTextureCon;
    prm_pMorphMeshModel->_dwNumMaterials = model_nMaterials;
}

void GgafDx9ModelManager::restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreD3DXMeshModel(" << prm_pD3DXMeshModel->_model_name << ")");
    //�yrestoreD3DXMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDx9D3DXMeshModel�̃����o�ɃZ�b�g
    //TODO:GgafDx9D3DXMeshModel�͂����K�v�����̂�������Ȃ��B

    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDx9D3DXMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    LPD3DXMESH pID3DXMesh; //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paD3DMaterial9; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDx9TextureConnection** model_papTextureCon; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD dwNumMaterials;
    string xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pD3DXMeshModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�

    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    hr = D3DXLoadMeshFromX(
           xfile_name.c_str(),         //[in]  LPCTSTR pFilename
           prm_pD3DXMeshModel->_dwOptions, //[in]  DWORD Options  D3DXMESH_SYSTEMMEM D3DXMESH_VB_DYNAMIC
           GgafDx9God::_pID3DDevice9,  //[in]  LPDIRECT3DDEVICE9 pDevice
           NULL,                       //[out] LPD3DXBUFFER* ppAdjacency
           &pID3DXBuffer,              //[out] LPD3DXBUFFER* ppMaterials
           NULL,                       //[out] LPD3DXBUFFER* ppEffectInstances
           &dwNumMaterials,            //[out] DWORD* pNumMaterials
           &pID3DXMesh                 //[out] LPD3DXMESH* pMesh
         );
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfile_name);

    //�œK��
    DWORD *pAdjacency = NEW DWORD [ pID3DXMesh->GetNumFaces() * 3 ];
    hr = pID3DXMesh->GenerateAdjacency( 1e-6f, pAdjacency );
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] GenerateAdjacency������܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, pAdjacency, NULL, NULL, NULL );
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXMESHOPT_ATTRSORT�ł��܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, pAdjacency, NULL, NULL, NULL );
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXMESHOPT_VERTEXCACHE�ł��܂���B�Ώ�="<<xfile_name);
    DELETEARR_IMPOSSIBLE_NULL(pAdjacency);

    //�}�e���A�������o��
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //��2008/02/02 �̔]�݂���
    // ����Ă��邱�ƃ���
    // GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
    //�\���̂𕨗��R�s�[�����ĕۑ����邱�Ƃɂ��܂���`�A�Ƃ肠�������`���܂��傤�B
    model_paD3DMaterial9 = NEW D3DMATERIAL9[dwNumMaterials];
    for( DWORD i = 0; i < dwNumMaterials; i++){
        model_paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //�}�e���A����Diffuse���˂�Ambient���˂ɃR�s�[����
    //���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
    //�G�N�X�|�[�g���ꂽx�t�@�C���̃}�e���A����Ambient���˒l���ݒ肳��ĂȂ��i�����c�[���̂����H�j�B
    //�܂��قƂ��Diffuse=Ambient�Ŗ��Ȃ��n�Y�ƍl�����B
    //�����Ńf�t�H���g�ŁADiffuse���˒l��Ambient���˒l��ݒ肷�邱�Ƃɂ���A�Ƃ肠�����B
    //��2009/3/13��
    //�Œ�p�C�v���C���͂����g��Ȃ��Ȃ����B����ɔ����}�e���A��Diffuse�̓V�F�[�_�[�̃p�����[�^�݂̂ŗ��p���Ă���B
    //TODO:���݃}�e���A��Ambient�͎Q�Ƃ���Ȃ��B�������������H
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        model_paD3DMaterial9[i].Ambient = model_paD3DMaterial9[i].Diffuse;
    }

    //�e�N�X�`�������o��
    model_papTextureCon = NEW GgafDx9TextureConnection*[dwNumMaterials];
    char* texture_filename;
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            model_papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`������
            model_papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
    }
    RELEASE_IMPOSSIBLE_NULL(pID3DXBuffer);//�e�N�X�`���t�@�C�����͂�������Ȃ��̂Ńo�b�t�@���

    //X�t�@�C���ɖ@�����Ȃ��ꍇ�AFVF�ɖ@����ǉ����A�@�����v�Z���Ă�ݒ�B
    if(pID3DXMesh->GetFVF() != (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)) {
        LPD3DXMESH pID3DXMesh_tmp = NULL;
        hr = pID3DXMesh->CloneMeshFVF(
                           pID3DXMesh->GetOptions(),             // [in]  DWORD Options,
                           D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1, // [in]  DWORD FVF,
                           GgafDx9God::_pID3DDevice9,            // [in]  LPDIRECT3DDEVICE9 pDevice,
                           &pID3DXMesh_tmp                       // [out] LPD3DXMESH *ppCloneMesh
                         );
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel]  pID3DXMesh->CloneMeshFVF()���s�B�Ώ�="<<xfile_name);
        D3DXComputeNormals(pID3DXMesh_tmp, NULL); //�@���v�Z�iFace�̕\���ǂ����ɖ@�������邩�A�ǂ�����Ĕ��肵�Ă���̂��낤���E�E�E�j
        RELEASE_IMPOSSIBLE_NULL(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
    prm_pD3DXMeshModel->_pID3DXMesh = pID3DXMesh;
    prm_pD3DXMeshModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pD3DXMeshModel->_papTextureCon = model_papTextureCon;
    prm_pD3DXMeshModel->_dwNumMaterials = dwNumMaterials;
    prm_pD3DXMeshModel->_radius_bounding_sphere = 10.0f; //TODO:���E�����a�傫���Ƃ肠����100px

}

void GgafDx9ModelManager::restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel* prm_pD3DXAniMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreD3DXAniMeshModel(" << prm_pD3DXAniMeshModel->_model_name << ")");
    //TODO:�쐬���I�I�I�I�I�I�I�I




    //�yrestoreD3DXAniMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDx9D3DXAniMeshModel�̃����o�ɃZ�b�g
    //TODO:GgafDx9D3DXAniMeshModel�͂����K�v�����̂�������Ȃ��B
    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDx9D3DXAniMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    LPD3DXMESH pID3DXAniMesh; //���b�V��(ID3DXAniMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* model_paD3DMaterial9 = NULL; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDx9TextureConnection** model_papTextureCon = NULL; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD dwNumMaterials;
    string xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pD3DXAniMeshModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�


    //AnimTicksPerSecond�̒l��Ǝ��Ɏ��o��
    ifstream ifs(xfile_name.c_str());
    if (ifs.fail()) {
        throwGgafCriticalException(" GgafDx9ModelManager::restoreD3DXAniMeshModel ["<<xfile_name<<"] ���J���܂���");
    }
    string buf;
    bool isdone = false;
    int anim_ticks_per_second = 4800;
    string data;
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

    LPD3DXBUFFER pID3DXBuffer; //�󂯎��p�o�b�t�@�i�}�e���A���p�j
    HRESULT hr;
    //X�t�@�C���̃t�@�C�����[�h
    GgafDx9AllocHierarchyWorldFrame* pAH = NEW GgafDx9AllocHierarchyWorldFrame(); // CAllocHierarchyBase�̔h���N���X
    D3DXFRAME_WORLD* pFR; // ���[���h�ϊ��s��t���t���[���\����
    ID3DXAnimationController* pAC; // �A�j���[�V�����R���g���[��
    hr = D3DXLoadMeshHierarchyFromX(
            xfile_name.c_str(),
            D3DXMESH_MANAGED,
            GgafDx9God::_pID3DDevice9,
            pAH,
            NULL,
            (D3DXFRAME**)(&pFR),
            &pAC
         );
    checkDxException(hr, D3D_OK, "GgafDx9ModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �ǂݍ��݂Ɏ��s���܂����B�Ώ�="<<xfile_name);
    if (pFR == NULL) {
        throwGgafCriticalException("GgafDx9ModelManager::restoreD3DXAniMeshModel "<<xfile_name<<" �̃t���[����񂪎擾�ł��܂���I");
    }
    //�}�e���A���z����쐬
    list<D3DXFRAME_WORLD*> listFrame;
    getDrawFrameList(&listFrame, pFR); //�}�e���A��������m�肽�������߁A�t���[�������A���X�g��
    list<D3DXFRAME_WORLD*>::iterator it = listFrame.begin();
    int model_nMaterials = 0;
    //�t���[�����X�g������āA�}�e���A�������擾
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == NULL) {
            continue;
        } else {
            model_nMaterials += (int)((*it)->pMeshContainer->NumMaterials);
        }
    }
    //�z�񐔂�����Ɖ������̂ō쐬
    model_paD3DMaterial9 = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureCon  = NEW GgafDx9TextureConnection*[model_nMaterials];
    //���f���ێ��p�}�e���A���A�e�N�X�`���쐬�̂��߁A������x��
    it = listFrame.begin();
    int n = 0;
    char* texture_filename;
    for (int i = 0; it != listFrame.end(); i++, it++) {
        if ((*it)->pMeshContainer == NULL) {
            continue;
        } else {
            for (int j = 0; j < (int)((*it)->pMeshContainer->NumMaterials); j++) {
//                (*it)->pMeshContainer->pMaterials[j].MatD3D.Diffuse
                model_paD3DMaterial9[n] = (*it)->pMeshContainer->pMaterials[j].MatD3D; //�}�e���A�����R�s�[

                texture_filename = (*it)->pMeshContainer->pMaterials[j].pTextureFilename;
                if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
                    model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
                } else {
                    //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
                    model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
                }
                n ++;
            }
        }
    }
    //���E��
    D3DXVECTOR3 vecCenter;
    FLOAT model_radius_bounding_sphere;
    D3DXFrameCalculateBoundingSphere(pFR, &vecCenter, &model_radius_bounding_sphere);
    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������







    prm_pD3DXAniMeshModel->_pAH = pAH;
    prm_pD3DXAniMeshModel->_pFR = pFR;
    prm_pD3DXAniMeshModel->_pAcBase = pAC;
    prm_pD3DXAniMeshModel->_radius_bounding_sphere = model_radius_bounding_sphere;
    _TRACE_("���E�����a="<<model_radius_bounding_sphere);
//    prm_pD3DXAniMeshModel->_advance_time_per_frame0 =  advanceTimePerFrame0; //�g���b�N0�ԂP���[�v�̎���
//    _TRACE_("�A�j���[�V�����Z�b�g0��_advance_time_per_frame");

//    prm_pD3DXAniMeshModel->_pID3DXAniMesh = pID3DXAniMesh;
    prm_pD3DXAniMeshModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pD3DXAniMeshModel->_papTextureCon = model_papTextureCon;
    prm_pD3DXAniMeshModel->_dwNumMaterials = model_nMaterials;
    prm_pD3DXAniMeshModel->_anim_ticks_per_second = anim_ticks_per_second;
}

void GgafDx9ModelManager::getDrawFrameList(list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* pFrame) {
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

void GgafDx9ModelManager::restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel) {
    TRACE3("GgafDx9ModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");

    prm_pSpriteModel->_papTextureCon = NULL;
    prm_pSpriteModel->_paRectUV = NULL;


    HRESULT hr;
    string xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteModel->_model_name) + ".sprx";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    checkDxException(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_SpriteModelWidth;
    float* pFloat_Size_SpriteModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        // PersonID�e���v���[�g�f�[�^���擾
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_SpriteModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_SpriteModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        prm_pSpriteModel->_fSize_SpriteModelWidthPx = *pFloat_Size_SpriteModelWidth;
        prm_pSpriteModel->_fSize_SpriteModelHeightPx = *pFloat_Size_SpriteModelHeight;
        prm_pSpriteModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pSpriteModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileData);
    //�e�N�X�`���擾�����f���ɕێ�������
    //string texture_filename = CFG_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* model_pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteModel->_papTextureCon = NEW GgafDx9TextureConnection*[1];
    prm_pSpriteModel->_papTextureCon[0] = model_pTextureCon;

    GgafDx9SpriteModel::VERTEX* paVertex = NEW GgafDx9SpriteModel::VERTEX[4];
    prm_pSpriteModel->_size_vertices = sizeof(GgafDx9SpriteModel::VERTEX)*4;
    prm_pSpriteModel->_size_vertex_unit = sizeof(GgafDx9SpriteModel::VERTEX);

    //���_�z��������f���ɕێ�������
    //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
    //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
    //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������

    //����
    paVertex[0].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[0].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[0].z = 0.0f;
    paVertex[0].nx = 0.0f;
    paVertex[0].ny = 0.0f;
    paVertex[0].nz = -1.0f;
    paVertex[0].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[0].tu = 0.0f;
    paVertex[0].tv = 0.0f;
    //�E��
    paVertex[1].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[1].y = *pFloat_Size_SpriteModelHeight / 2 / PX_UNIT;
    paVertex[1].z = 0.0f;
    paVertex[1].nx = 0.0f;
    paVertex[1].ny = 0.0f;
    paVertex[1].nz = -1.0f;
    paVertex[1].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[1].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit);// - (pxU/2);
    paVertex[1].tv = 0.0f;
    //����
    paVertex[2].x = *pFloat_Size_SpriteModelWidth / -2 / PX_UNIT;
    paVertex[2].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[2].z = 0.0f;
    paVertex[2].nx = 0.0f;
    paVertex[2].ny = 0.0f;
    paVertex[2].nz = -1.0f;
    paVertex[2].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[2].tu = 0.0f;
    paVertex[2].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit);// - (pxV/2);
    //�E��
    paVertex[3].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[3].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit);// - (pxU/2);
    paVertex[3].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit);// - (pxV/2);


    //����
    FLOAT model_radius_bounding_sphere = (FLOAT)(GgafDx9Util::sqrt_fast(paVertex[0].x * paVertex[0].x +
                                               paVertex[0].y * paVertex[0].y +
                                               paVertex[0].z * paVertex[0].z));
    prm_pSpriteModel->_radius_bounding_sphere = model_radius_bounding_sphere;


    //�o�b�t�@�쐬
    if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDx9SpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSpriteModel->_size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_size_vertices); //pVertexBuffer �� paVertex
    prm_pSpriteModel->_pIDirect3DVertexBuffer9->Unlock();

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(model_paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭�����猩�����������B

    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* model_paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_uvflip = row*(*pInt_ColNum_TextureSplit)+col;
            model_paRectUV[pattno_uvflip]._aUV[0].tu = (float)(1.0f/(*pInt_ColNum_TextureSplit)*col);
            model_paRectUV[pattno_uvflip]._aUV[0].tv = (float)(1.0f/(*pInt_RowNum_TextureSplit)*row);

            model_paRectUV[pattno_uvflip]._aUV[1].tu = (float)((1.0f/(*pInt_ColNum_TextureSplit)*(col+1)));
            model_paRectUV[pattno_uvflip]._aUV[1].tv = (float)(1.0f/(*pInt_RowNum_TextureSplit)*row);

            model_paRectUV[pattno_uvflip]._aUV[2].tu = (float)(1.0f/(*pInt_ColNum_TextureSplit)*col);
            model_paRectUV[pattno_uvflip]._aUV[2].tv = (float)((1.0f/(*pInt_RowNum_TextureSplit)*(row+1)));

            model_paRectUV[pattno_uvflip]._aUV[3].tu = (float)((1.0f/(*pInt_ColNum_TextureSplit)*(col+1)));
            model_paRectUV[pattno_uvflip]._aUV[3].tv = (float)((1.0f/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pSpriteModel->_paRectUV = model_paRectUV;
    prm_pSpriteModel->_pattno_uvflip_Max=pattnum-1;
    prm_pSpriteModel->_dwNumMaterials = 1;
    D3DMATERIAL9* model_paD3DMaterial9;
    model_paD3DMaterial9 = NEW D3DMATERIAL9[prm_pSpriteModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pSpriteModel->_dwNumMaterials; i++){
        //model_paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paD3DMaterial9[i].Diffuse.r = 1.0f;
        model_paD3DMaterial9[i].Diffuse.g = 1.0f;
        model_paD3DMaterial9[i].Diffuse.b = 1.0f;
        model_paD3DMaterial9[i].Diffuse.a = 1.0f;
        model_paD3DMaterial9[i].Ambient.r = 1.0f;
        model_paD3DMaterial9[i].Ambient.g = 1.0f;
        model_paD3DMaterial9[i].Ambient.b = 1.0f;
        model_paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pSpriteModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreSpriteSetModel(GgafDx9SpriteSetModel* prm_pSpriteSetModel) {
    TRACE3("GgafDx9ModelManager::restoreSpriteSetModel(" << prm_pSpriteSetModel->_model_name << ")");

    if (4*prm_pSpriteSetModel->_set_num > 65535) {
        throwGgafCriticalException("X[GgafDx9ModelManager::restoreSpriteSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pSpriteSetModel->getName()<<"  nVertices:4  �Z�b�g��:"<<(prm_pSpriteSetModel->_set_num));
    }

    if ( 2 * 3 * prm_pSpriteSetModel->_set_num > 65535) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteSetModel] ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pSpriteSetModel->getName()<<"  nFaces:2(*3)  �Z�b�g��:"<<(prm_pSpriteSetModel->_set_num));
    }

    prm_pSpriteSetModel->_papTextureCon = NULL;
    prm_pSpriteSetModel->_paRectUV = NULL;


    HRESULT hr;
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    string xfile_name; //�ǂݍ��ރX�v���C�g��`�t�@�C�����iX�t�@�C���`���j
    //"12/Bomb" or "8/Bomb" or "Bomb" ���� "Bomb" ������Ƃ肾���ăt���p�X���擾
    if (*(prm_pSpriteSetModel->_model_name + 1) == '/') {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteSetModel->_model_name + 2) + ".sprx";
    } else if (*(prm_pSpriteSetModel->_model_name + 2) == '/') {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteSetModel->_model_name + 3) + ".sprx";
    } else {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteSetModel->_model_name) + ".sprx";
    }
    hr = _pIDirectXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    checkDxException(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreSpriteSetModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_SpriteSetModelWidth;
    float* pFloat_Size_SpriteSetModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteSetModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        // PersonID�e���v���[�g�f�[�^���擾
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_SpriteSetModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_SpriteSetModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);
        prm_pSpriteSetModel->_fSize_SpriteSetModelWidthPx = *pFloat_Size_SpriteSetModelWidth;
        prm_pSpriteSetModel->_fSize_SpriteSetModelHeightPx = *pFloat_Size_SpriteSetModelHeight;
        prm_pSpriteSetModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pSpriteSetModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteSetModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileData);
    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDx9TextureConnection* model_pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteSetModel->_papTextureCon = NEW GgafDx9TextureConnection*[1];
    prm_pSpriteSetModel->_papTextureCon[0] = model_pTextureCon;
    //�o�b�t�@�쐬
    if (prm_pSpriteSetModel->_pIDirect3DVertexBuffer9 == NULL) {
        prm_pSpriteSetModel->_size_vertices = sizeof(GgafDx9SpriteSetModel::VERTEX)*4;
        prm_pSpriteSetModel->_size_vertex_unit = sizeof(GgafDx9SpriteSetModel::VERTEX);

        GgafDx9SpriteSetModel::VERTEX* paVertex = NEW GgafDx9SpriteSetModel::VERTEX[4 * prm_pSpriteSetModel->_set_num];
        //���_�z��������f���ɕێ�������
        //UV�͍���̂P���i�A�j���p�^�[���O�j���f�t�H���g�Őݒ肷��B
        //�V�F�[�_�[���`�掞�ɃA�j���p�^�[���ԍ����݂�UV���W�����炷�d�l�Ƃ�����ƁB
        //x,y �� ��2 �Ƃ́A���f�����S�����[�J�����W�̌��_���S�Ƃ���������
        for (int i = 0; i < prm_pSpriteSetModel->_set_num; i++) {

            paVertex[i*4 + 0].x = *pFloat_Size_SpriteSetModelWidth / -2 / PX_UNIT;
            paVertex[i*4 + 0].y = *pFloat_Size_SpriteSetModelHeight / 2 / PX_UNIT;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].nx = 0.0f;
            paVertex[i*4 + 0].ny = 0.0f;
            paVertex[i*4 + 0].nz = -1.0f;
            paVertex[i*4 + 0].tu = 0.0f;
            paVertex[i*4 + 0].tv = 0.0f;
            paVertex[i*4 + 0].index = (float)i;
            //�E��
            paVertex[i*4 + 1].x = *pFloat_Size_SpriteSetModelWidth / 2 / PX_UNIT;
            paVertex[i*4 + 1].y = *pFloat_Size_SpriteSetModelHeight / 2 / PX_UNIT;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].nx = 0.0f;
            paVertex[i*4 + 1].ny = 0.0f;
            paVertex[i*4 + 1].nz = -1.0f;
            paVertex[i*4 + 1].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit);// - (pxU/2);
            paVertex[i*4 + 1].tv = 0.0f;
            paVertex[i*4 + 1].index = (float)i;
            //����
            paVertex[i*4 + 2].x = *pFloat_Size_SpriteSetModelWidth / -2 / PX_UNIT;
            paVertex[i*4 + 2].y = *pFloat_Size_SpriteSetModelHeight / -2 / PX_UNIT;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].nx = 0.0f;
            paVertex[i*4 + 2].ny = 0.0f;
            paVertex[i*4 + 2].nz = -1.0f;
            paVertex[i*4 + 2].tu = 0.0f;
            paVertex[i*4 + 2].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit);// - (pxV/2);
            paVertex[i*4 + 2].index = (float)i;
            //�E��
            paVertex[i*4 + 3].x = *pFloat_Size_SpriteSetModelWidth / 2 / PX_UNIT;
            paVertex[i*4 + 3].y = *pFloat_Size_SpriteSetModelHeight / -2 / PX_UNIT;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].nx = 0.0f;
            paVertex[i*4 + 3].ny = 0.0f;
            paVertex[i*4 + 3].nz = -1.0f;
            paVertex[i*4 + 3].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit);// - (pxU/2);
            paVertex[i*4 + 3].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit);// - (pxV/2);
            paVertex[i*4 + 3].index = (float)i;

//            _TRACE_("paVertex["<<(i*4 + 0)<<"].x ="<<paVertex[i*4 + 0].x );
//            _TRACE_("paVertex["<<(i*4 + 0)<<"].y ="<<paVertex[i*4 + 0].y );
//            _TRACE_("paVertex["<<(i*4 + 0)<<"].z ="<<paVertex[i*4 + 0].z );
//            _TRACE_("paVertex["<<(i*4 + 0)<<"].index ="<<paVertex[i*4 + 0].index );
//            _TRACE_("paVertex["<<(i*4 + 1)<<"].x ="<<paVertex[i*4 + 1].x );
//            _TRACE_("paVertex["<<(i*4 + 1)<<"].y ="<<paVertex[i*4 + 1].y );
//            _TRACE_("paVertex["<<(i*4 + 1)<<"].z ="<<paVertex[i*4 + 1].z );
//            _TRACE_("paVertex["<<(i*4 + 1)<<"].index ="<<paVertex[i*4 + 1].index );
//            _TRACE_("paVertex["<<(i*4 + 2)<<"].x ="<<paVertex[i*4 + 2].x );
//            _TRACE_("paVertex["<<(i*4 + 2)<<"].y ="<<paVertex[i*4 + 2].y );
//            _TRACE_("paVertex["<<(i*4 + 2)<<"].z ="<<paVertex[i*4 + 2].z );
//            _TRACE_("paVertex["<<(i*4 + 2)<<"].index ="<<paVertex[i*4 + 2].index );
//            _TRACE_("paVertex["<<(i*4 + 3)<<"].x ="<<paVertex[i*4 + 3].x );
//            _TRACE_("paVertex["<<(i*4 + 3)<<"].y ="<<paVertex[i*4 + 3].y );
//            _TRACE_("paVertex["<<(i*4 + 3)<<"].z ="<<paVertex[i*4 + 3].z );
//            _TRACE_("paVertex["<<(i*4 + 3)<<"].index ="<<paVertex[i*4 + 3].index );

        }

        //����
        FLOAT model_radius_bounding_sphere = (FLOAT)(GgafDx9Util::sqrt_fast(paVertex[0].x * paVertex[0].x +
                                                   paVertex[0].y * paVertex[0].y +
                                                   paVertex[0].z * paVertex[0].z));
        prm_pSpriteSetModel->_radius_bounding_sphere = model_radius_bounding_sphere;


        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteSetModel->_size_vertices * prm_pSpriteSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDx9SpriteSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pSpriteSetModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteSetModel] _p1ID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteSetModel->_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = prm_pSpriteSetModel->_pIDirect3DVertexBuffer9->Lock(
                                       0,
                                       prm_pSpriteSetModel->_size_vertices * prm_pSpriteSetModel->_set_num,
                                       (void**)&pVertexBuffer,
                                       0
                                   );
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteSetModel->_model_name);

        memcpy(
            pVertexBuffer,
            paVertex,
            prm_pSpriteSetModel->_size_vertices* prm_pSpriteSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pSpriteSetModel->_pIDirect3DVertexBuffer9->Unlock();
        DELETEARR_IMPOSSIBLE_NULL(paVertex);
    }

    //�C���f�b�N�X�o�b�t�@�쐬
    if (prm_pSpriteSetModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nVertices = 4;
        int nFaces = 2;
        WORD* unit_paIdxBuffer = NEW WORD[(nFaces*3)];
        unit_paIdxBuffer[0] = 0;
        unit_paIdxBuffer[1] = 1;
        unit_paIdxBuffer[2] = 2;

        unit_paIdxBuffer[3] = 1;
        unit_paIdxBuffer[4] = 3;
        unit_paIdxBuffer[5] = 2;

        //_TRACE_("prm_pSpriteSetModel->_set_num="<<prm_pSpriteSetModel->_set_num);
        WORD* paIdxBufferSet = NEW WORD[(nFaces*3) * prm_pSpriteSetModel->_set_num];
        for (int i = 0; i < prm_pSpriteSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer[j*3 + 0] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer[j*3 + 1] + (nVertices*i);
                paIdxBufferSet[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer[j*3 + 2] + (nVertices*i);
//                _TRACE_("paIdxBufferSet["<<(((i*nFaces*3)+(j*3)) + 0)<<"] = unit_paIdxBuffer["<<(j*3 + 0)<<"] + (nVertices*"<<i<<")="<<(unit_paIdxBuffer[j*3 + 0] + (nVertices*i)));
//                _TRACE_("paIdxBufferSet["<<(((i*nFaces*3)+(j*3)) + 1)<<"] = unit_paIdxBuffer["<<(j*3 + 1)<<"] + (nVertices*"<<i<<")="<<(unit_paIdxBuffer[j*3 + 1] + (nVertices*i)));
//                _TRACE_("paIdxBufferSet["<<(((i*nFaces*3)+(j*3)) + 2)<<"] = unit_paIdxBuffer["<<(j*3 + 2)<<"] + (nVertices*"<<i<<")="<<(unit_paIdxBuffer[j*3 + 2] + (nVertices*i)));
            }
        }

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * prm_pSpriteSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pSpriteSetModel->_pIDirect3DIndexBuffer9),
                                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pSpriteSetModel->_model_name));

        void* pIndexBuffer;
        prm_pSpriteSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * prm_pSpriteSetModel->_set_num
        );
        prm_pSpriteSetModel->_pIDirect3DIndexBuffer9->Unlock();
        DELETEARR_IMPOSSIBLE_NULL(unit_paIdxBuffer);
        DELETEARR_IMPOSSIBLE_NULL(paIdxBufferSet);

        //�`�掞�p�����[�^�[
        GgafDx9SpriteSetModel::INDEXPARAM* paIndexParam = NEW GgafDx9SpriteSetModel::INDEXPARAM[prm_pSpriteSetModel->_set_num];
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

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(model_paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭�����猩�����������B
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* model_paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_uvflip = row*(*pInt_ColNum_TextureSplit)+col;
            model_paRectUV[pattno_uvflip]._aUV[0].tu = (float)(1.0f/(*pInt_ColNum_TextureSplit)*col);
            model_paRectUV[pattno_uvflip]._aUV[0].tv = (float)(1.0f/(*pInt_RowNum_TextureSplit)*row);

            model_paRectUV[pattno_uvflip]._aUV[1].tu = (float)((1.0f/(*pInt_ColNum_TextureSplit)*(col+1)));
            model_paRectUV[pattno_uvflip]._aUV[1].tv = (float)(1.0f/(*pInt_RowNum_TextureSplit)*row);

            model_paRectUV[pattno_uvflip]._aUV[2].tu = (float)(1.0f/(*pInt_ColNum_TextureSplit)*col);
            model_paRectUV[pattno_uvflip]._aUV[2].tv = (float)((1.0f/(*pInt_RowNum_TextureSplit)*(row+1)));

            model_paRectUV[pattno_uvflip]._aUV[3].tu = (float)((1.0f/(*pInt_ColNum_TextureSplit)*(col+1)));
            model_paRectUV[pattno_uvflip]._aUV[3].tv = (float)((1.0f/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pSpriteSetModel->_paRectUV = model_paRectUV;
    prm_pSpriteSetModel->_pattno_uvflip_Max=pattnum-1;
    prm_pSpriteSetModel->_dwNumMaterials = 1;
    D3DMATERIAL9* model_paD3DMaterial9 = NEW D3DMATERIAL9[prm_pSpriteSetModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pSpriteSetModel->_dwNumMaterials; i++){
        //model_paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paD3DMaterial9[i].Diffuse.r = 1.0f;
        model_paD3DMaterial9[i].Diffuse.g = 1.0f;
        model_paD3DMaterial9[i].Diffuse.b = 1.0f;
        model_paD3DMaterial9[i].Diffuse.a = 1.0f;
        model_paD3DMaterial9[i].Ambient.r = 1.0f;
        model_paD3DMaterial9[i].Ambient.g = 1.0f;
        model_paD3DMaterial9[i].Ambient.b = 1.0f;
        model_paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pSpriteSetModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    //��n��
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel) {
    TRACE3("GgafDx9ModelManager::restoreBoardModel(" << prm_pBoardModel->_model_name << ")");

    prm_pBoardModel->_papTextureCon = NULL;
    prm_pBoardModel->_paRectUV = NULL;

    HRESULT hr;
    string xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pBoardModel->_model_name) + ".sprx";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    checkDxException(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreBoardModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_BoardModelWidth;
    float* pFloat_Size_BoardModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_BoardModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_BoardModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);

        prm_pBoardModel->_fSize_BoardModelWidthPx = *pFloat_Size_BoardModelWidth;
        prm_pBoardModel->_fSize_BoardModelHeightPx = *pFloat_Size_BoardModelHeight;
        prm_pBoardModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pBoardModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDx9TextureConnection* model_pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pBoardModel->_papTextureCon = NEW GgafDx9TextureConnection*[1];
    prm_pBoardModel->_papTextureCon[0] = model_pTextureCon;

    GgafDx9BoardModel::VERTEX* paVertex = NEW GgafDx9BoardModel::VERTEX[4];
    prm_pBoardModel->_size_vertices = sizeof(GgafDx9BoardModel::VERTEX)*4;
    prm_pBoardModel->_size_vertex_unit = sizeof(GgafDx9BoardModel::VERTEX);

    //1px�������uv�̑傫�������߂�
    float texWidth  = (float)(model_pTextureCon->refer()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float texHeight = (float)(model_pTextureCon->refer()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
     float pxU = 1.0f / texWidth; //�e�N�X�`���̕�(px)�Ŋ���
     float pxV = 1.0f / texHeight; //�e�N�X�`���̍���(px)�Ŋ���

    //����
    paVertex[0].x = 0.0f;
    paVertex[0].y = 0.0f;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = (pxU/100);
    paVertex[0].tv = (pxV/100);
    //�E��
    paVertex[1].x = *pFloat_Size_BoardModelWidth;
    paVertex[1].y = 0.0f;
    paVertex[1].z = 0.0f;
    paVertex[1].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit) - (pxU/100); //�͂��ɏ��������
    paVertex[1].tv = (pxV/100);
    //����
    paVertex[2].x = 0.0f;
    paVertex[2].y = *pFloat_Size_BoardModelHeight;
    paVertex[2].z = 0.0f;
    paVertex[2].tu = (pxU/100);
    paVertex[2].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit) - (pxV/100); //�͂��ɏ��������
    //�E��
    paVertex[3].x = *pFloat_Size_BoardModelWidth;
    paVertex[3].y = *pFloat_Size_BoardModelHeight;
    paVertex[3].z = 0.0f;
    paVertex[3].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit) - (pxU/100);
    paVertex[3].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit) - (pxV/100);

    //�o�b�t�@�쐬
    if (prm_pBoardModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pBoardModel->_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDx9BoardModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pBoardModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pBoardModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pBoardModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pBoardModel->_size_vertices, (void**)&pVertexBuffer, 0);
    checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pBoardModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pBoardModel->_size_vertices); //pVertexBuffer �� paVertex
    prm_pBoardModel->_pIDirect3DVertexBuffer9->Unlock();

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(model_paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭������]���ȏ����������������B
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* model_paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_uvflip = row*(*pInt_ColNum_TextureSplit)+col;
            model_paRectUV[pattno_uvflip]._aUV[0].tu = (float)(1.0f*col/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[0].tv = (float)(1.0f*row/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[1].tu = (float)(1.0f*(col+1)/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[1].tv = (float)(1.0f*row/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[2].tu = (float)(1.0f*col/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[2].tv = (float)(1.0f*(row+1)/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[3].tu = (float)(1.0f*(col+1)/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[3].tv = (float)(1.0f*(row+1)/(*pInt_RowNum_TextureSplit));
        }
    }
    prm_pBoardModel->_paRectUV = model_paRectUV;
    prm_pBoardModel->_pattno_max = pattnum-1;
    prm_pBoardModel->_dwNumMaterials = 1;
    D3DMATERIAL9* model_paD3DMaterial9;
    model_paD3DMaterial9 = NEW D3DMATERIAL9[prm_pBoardModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pBoardModel->_dwNumMaterials; i++){
        //model_paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paD3DMaterial9[i].Diffuse.r = 1.0f;
        model_paD3DMaterial9[i].Diffuse.g = 1.0f;
        model_paD3DMaterial9[i].Diffuse.b = 1.0f;
        model_paD3DMaterial9[i].Diffuse.a = 1.0f;
        model_paD3DMaterial9[i].Ambient.r = 1.0f;
        model_paD3DMaterial9[i].Ambient.g = 1.0f;
        model_paD3DMaterial9[i].Ambient.b = 1.0f;
        model_paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pBoardModel->_paD3DMaterial9_default = model_paD3DMaterial9;

    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreBoardSetModel(GgafDx9BoardSetModel* prm_pBoardSetModel) {
    TRACE3("GgafDx9ModelManager::restoreBoardSetModel(" << prm_pBoardSetModel->_model_name << ")");

    if (4*prm_pBoardSetModel->_set_num > 65535) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pBoardSetModel->getName()<<"  nVertices:4  �Z�b�g��:"<<(prm_pBoardSetModel->_set_num));
    }
//    if ( 2 * 3 * prm_pBoardSetModel->_set_num > 65535) {
//        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardSetModel] ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pBoardSetModel->getName()<<"  nFaces:2(*3)  �Z�b�g��:"<<(prm_pBoardSetModel->_set_num));
//    }

    prm_pBoardSetModel->_papTextureCon = NULL;
    prm_pBoardSetModel->_paRectUV = NULL;

    HRESULT hr;
    string xfile_name; //�ǂݍ��ރX�v���C�g��`�t�@�C�����iX�t�@�C���`���j
    //"12/Moji" or "8/Moji" or "Moji" ���� "Moji" ������Ƃ肾���ăt���p�X���擾�B
    //TODO:���l3��("123/Moji"�Ƃ�)�������獢��B
    if (*(prm_pBoardSetModel->_model_name + 1) == '/') {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pBoardSetModel->_model_name + 2) + ".sprx";
    } else if (*(prm_pBoardSetModel->_model_name + 2) == '/') {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pBoardSetModel->_model_name + 3) + ".sprx";
    } else {
        xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pBoardSetModel->_model_name) + ".sprx";
    }
    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile_sprx->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    checkDxException(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreBoardSetModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_Size_BoardSetModelWidth;
    float* pFloat_Size_BoardSetModelHeight;
    int* pInt_RowNum_TextureSplit;
    int* pInt_ColNum_TextureSplit;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardSetModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        pIDirectXFileData->GetData("TextureFile"     , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("Width"           , &Size, (void**)&pFloat_Size_BoardSetModelWidth);
        pIDirectXFileData->GetData("Height"          , &Size, (void**)&pFloat_Size_BoardSetModelHeight);
        pIDirectXFileData->GetData("TextureSplitRows", &Size, (void**)&pInt_RowNum_TextureSplit);
        pIDirectXFileData->GetData("TextureSplitCols", &Size, (void**)&pInt_ColNum_TextureSplit);

        prm_pBoardSetModel->_fSize_BoardSetModelWidthPx = *pFloat_Size_BoardSetModelWidth;
        prm_pBoardSetModel->_fSize_BoardSetModelHeightPx = *pFloat_Size_BoardSetModelHeight;
        prm_pBoardSetModel->_row_texture_split = *pInt_RowNum_TextureSplit;
        prm_pBoardSetModel->_col_texture_split = *pInt_ColNum_TextureSplit;
    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreBoardSetModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDx9TextureConnection* model_pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pBoardSetModel->_papTextureCon = NEW GgafDx9TextureConnection*[1];
    prm_pBoardSetModel->_papTextureCon[0] = model_pTextureCon;

    if (prm_pBoardSetModel->_pIDirect3DVertexBuffer9 == NULL) {

        prm_pBoardSetModel->_size_vertices = sizeof(GgafDx9BoardSetModel::VERTEX)*4;
        prm_pBoardSetModel->_size_vertex_unit = sizeof(GgafDx9BoardSetModel::VERTEX);
        GgafDx9BoardSetModel::VERTEX* paVertex = NEW GgafDx9BoardSetModel::VERTEX[4 * prm_pBoardSetModel->_set_num];

        //1px�������uv�̑傫�������߂�
        float texWidth  = (float)(model_pTextureCon->refer()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
        float texHeight = (float)(model_pTextureCon->refer()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)
        float pxU = 1.0f / texWidth; //�e�N�X�`���̕�(px)�Ŋ���
        float pxV = 1.0f / texHeight; //�e�N�X�`���̍���(px)�Ŋ���

        for (int i = 0; i < prm_pBoardSetModel->_set_num; i++) {
            //����
            paVertex[i*4 + 0].x = 0.0f;
            paVertex[i*4 + 0].y = 0.0f;
            paVertex[i*4 + 0].z = 0.0f;
            paVertex[i*4 + 0].tu = (pxU/100);
            paVertex[i*4 + 0].tv = (pxV/100);
            paVertex[i*4 + 0].index = (float)i;
            //�E��
            paVertex[i*4 + 1].x = *pFloat_Size_BoardSetModelWidth;
            paVertex[i*4 + 1].y = 0.0f;
            paVertex[i*4 + 1].z = 0.0f;
            paVertex[i*4 + 1].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit) - (pxU/100);
            paVertex[i*4 + 1].tv = (pxV/100);
            paVertex[i*4 + 1].index = (float)i;
            //����
            paVertex[i*4 + 2].x = 0.0f;
            paVertex[i*4 + 2].y = *pFloat_Size_BoardSetModelHeight;
            paVertex[i*4 + 2].z = 0.0f;
            paVertex[i*4 + 2].tu = (pxU/100);
            paVertex[i*4 + 2].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit) - (pxV/100);
            paVertex[i*4 + 2].index = (float)i;
            //�E��
            paVertex[i*4 + 3].x = *pFloat_Size_BoardSetModelWidth;
            paVertex[i*4 + 3].y = *pFloat_Size_BoardSetModelHeight;
            paVertex[i*4 + 3].z = 0.0f;
            paVertex[i*4 + 3].tu = 1.0f/(float)(*pInt_ColNum_TextureSplit) - (pxU/100);
            paVertex[i*4 + 3].tv = 1.0f/(float)(*pInt_RowNum_TextureSplit) - (pxV/100);
            paVertex[i*4 + 3].index = (float)i;
         }

        //�o�b�t�@�쐬

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDx9BoardSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pBoardSetModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardSetModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pBoardSetModel->_model_name));
        //���_�o�b�t�@�쐬
        //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
        void *pVertexBuffer;
        hr = prm_pBoardSetModel->_pIDirect3DVertexBuffer9->Lock(
                                                             0,
                                                             prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num,
                                                             (void**)&pVertexBuffer,
                                                             0
                                                           );
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pBoardSetModel->_model_name);

        memcpy(
          pVertexBuffer,
          paVertex,
          prm_pBoardSetModel->_size_vertices * prm_pBoardSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pBoardSetModel->_pIDirect3DVertexBuffer9->Unlock();

        DELETEARR_IMPOSSIBLE_NULL(paVertex);
    }


    //�C���f�b�N�X�o�b�t�@�쐬
    if (prm_pBoardSetModel->_pIDirect3DIndexBuffer9 == NULL) {
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

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                                sizeof(WORD) * nFaces * 3 * prm_pBoardSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pBoardSetModel->_pIDirect3DIndexBuffer9),
                                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pBoardSetModel->_model_name));

        void* pIndexBuffer;
        prm_pBoardSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          paIdxBufferSet,
          sizeof(WORD) * nFaces * 3 * prm_pBoardSetModel->_set_num
        );
        prm_pBoardSetModel->_pIDirect3DIndexBuffer9->Unlock();
        DELETEARR_IMPOSSIBLE_NULL(unit_paIdxBuffer);
        DELETEARR_IMPOSSIBLE_NULL(paIdxBufferSet);

        //�`�掞�p�����[�^�[
        GgafDx9BoardSetModel::INDEXPARAM* paIndexParam = NEW GgafDx9BoardSetModel::INDEXPARAM[prm_pBoardSetModel->_set_num];
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


    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(model_paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭������]���ȏ����������������B
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* model_paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_uvflip = row*(*pInt_ColNum_TextureSplit)+col;
            model_paRectUV[pattno_uvflip]._aUV[0].tu = (float)(1.0f*col/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[0].tv = (float)(1.0f*row/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[1].tu = (float)(1.0f*(col+1)/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[1].tv = (float)(1.0f*row/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[2].tu = (float)(1.0f*col/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[2].tv = (float)(1.0f*(row+1)/(*pInt_RowNum_TextureSplit));

            model_paRectUV[pattno_uvflip]._aUV[3].tu = (float)(1.0f*(col+1)/(*pInt_ColNum_TextureSplit));
            model_paRectUV[pattno_uvflip]._aUV[3].tv = (float)(1.0f*(row+1)/(*pInt_RowNum_TextureSplit));
        }
    }
    prm_pBoardSetModel->_paRectUV = model_paRectUV;
    prm_pBoardSetModel->_pattno_max = pattnum-1;
    prm_pBoardSetModel->_dwNumMaterials = 1;
    D3DMATERIAL9* model_paD3DMaterial9 = NEW D3DMATERIAL9[prm_pBoardSetModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pBoardSetModel->_dwNumMaterials; i++){
        //model_paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        model_paD3DMaterial9[i].Diffuse.r = 1.0f;
        model_paD3DMaterial9[i].Diffuse.g = 1.0f;
        model_paD3DMaterial9[i].Diffuse.b = 1.0f;
        model_paD3DMaterial9[i].Diffuse.a = 1.0f;
        model_paD3DMaterial9[i].Ambient.r = 1.0f;
        model_paD3DMaterial9[i].Ambient.g = 1.0f;
        model_paD3DMaterial9[i].Ambient.b = 1.0f;
        model_paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pBoardSetModel->_paD3DMaterial9_default = model_paD3DMaterial9;

    //��n��

    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreMeshSetModel(GgafDx9MeshSetModel* prm_pMeshSetModel) {
    TRACE3("GgafDx9ModelManager::restoreMeshSetModel(" << prm_pMeshSetModel->_model_name << ")");
    string xfile_name; //�ǂݍ���X�t�@�C����
    //"12/Ceres" or "8/Celes" or "Celes" ���� "Celes" ������Ƃ肾���ăt���p�X���擾
    //TODO:���l�R���ȏ�̎��͂���
    if (*(prm_pMeshSetModel->_model_name + 1) == '/') {
        xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshSetModel->_model_name + 2) + ".x";
    } else if (*(prm_pMeshSetModel->_model_name + 2) == '/') {
        xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshSetModel->_model_name + 3) + ".x";
    } else {
        xfile_name = CFG_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshSetModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�
    }


    HRESULT hr;
    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* model_pModel3D = NULL;
    Frm::Mesh* model_pMeshesFront = NULL;

    GgafDx9MeshSetModel::INDEXPARAM** model_papaIndexParam = NULL;
    GgafDx9MeshSetModel::VERTEX* unit_paVtxBuffer_org = NULL;
    GgafDx9MeshSetModel::VERTEX* model_paVtxBuffer_org = NULL;
    WORD* unit_paIdxBuffer_org = NULL;
    WORD* model_paIdxBuffer_org = NULL;
    D3DMATERIAL9* model_paD3DMaterial9 = NULL;
    GgafDx9TextureConnection** model_papTextureCon = NULL;

    int nVertices = 0;
    int nTextureCoords = 0;
    int nFaces = 0;
    int nFaceNormals = 0;

    if (prm_pMeshSetModel->_pModel3D == NULL) {
        model_pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, model_pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDx9ModelManager::restoreMeshSetModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }

        //���b�V������������O�ɁA�����m�ۂ��Ă���
        int nMesh = (int)model_pModel3D->_Meshes.size();
        uint16* paNumVertices = NEW uint16[nMesh];
        int index_Mesh = 0;
        for (list<Frm::Mesh*>::iterator iteMeshes = model_pModel3D->_Meshes.begin();
                iteMeshes != model_pModel3D->_Meshes.end(); iteMeshes++) {
            paNumVertices[index_Mesh] = ((*iteMeshes)->_nVertices);
            index_Mesh++;
        }
        model_pModel3D->ConcatenateMeshes(); //���b�V�����q����

        model_pMeshesFront = model_pModel3D->_Meshes.front();
        nVertices = model_pMeshesFront->_nVertices;
        nTextureCoords = model_pMeshesFront->_nTextureCoords;
        nFaces = model_pMeshesFront->_nFaces;
        nFaceNormals = model_pMeshesFront->_nFaceNormals;
        unit_paVtxBuffer_org = NEW GgafDx9MeshSetModel::VERTEX[nVertices];

        if (nVertices*prm_pMeshSetModel->_set_num > 65535) {
            throwGgafCriticalException("[GgafDx9ModelManager::restoreMeshSetModel] ���_�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMeshSetModel->getName()<<"  nVertices:"<<nVertices<<"  �Z�b�g��:"<<(prm_pMeshSetModel->_set_num));
        }

//        if ( nFaces * 3 * prm_pMeshSetModel->_set_num > 65535) {
//            throwGgafCriticalException("[GgafDx9ModelManager::restoreMeshSetModel] ���_�C���f�b�N�X�� 65535�𒴂�����������܂���B\n�Ώ�Model�F"<<prm_pMeshSetModel->getName()<<"  nFaces:"<<nFaces<<"(*3)  �Z�b�g��:"<<(prm_pMeshSetModel->_set_num));
//        }

        prm_pMeshSetModel->_nVertices = nVertices;
        prm_pMeshSetModel->_nFaces = nFaces;
        prm_pMeshSetModel->_size_vertices = sizeof(GgafDx9MeshSetModel::VERTEX) * nVertices;
        prm_pMeshSetModel->_size_vertex_unit = sizeof(GgafDx9MeshSetModel::VERTEX);

        //�@���ȊO�ݒ�
        FLOAT model_radius_bounding_sphere;
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
            model_radius_bounding_sphere = (FLOAT)(GgafDx9Util::sqrt_fast(unit_paVtxBuffer_org[i].x * unit_paVtxBuffer_org[i].x +
                                                 unit_paVtxBuffer_org[i].y * unit_paVtxBuffer_org[i].y +
                                                 unit_paVtxBuffer_org[i].z * unit_paVtxBuffer_org[i].z));
            if (prm_pMeshSetModel->_radius_bounding_sphere < model_radius_bounding_sphere) {
                prm_pMeshSetModel->_radius_bounding_sphere = model_radius_bounding_sphere;
            }
        }

        int nTextureCoords = model_pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //�@���ݒ�B
        //�������@�� restoreMeshModel �Ɠ����B�v�Q�ƁB
        float* paRad = NEW float[nFaces*3];
        float* paRadSum_Vtx = NEW float[nVertices];
        for (int i = 0; i < nVertices; i++) {
            paRadSum_Vtx[i] = 0;
        }
        std::fill_n(paRadSum_Vtx, nVertices, 0);
        unsigned short indexVertices_per_Face[3];
        unsigned short indexNormals_per_Face[3];
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                //�ʂɑ΂��钸�_�C���f�b�N�X�R��(A,B,C�Ƃ���)
                indexVertices_per_Face[j] = model_pMeshesFront->_Faces[i].data[j];
                //�ʂɑ΂���@���C���f�b�N�X�R��
                if (nFaceNormals > i) {
                    indexNormals_per_Face[j] = model_pMeshesFront->_FaceNormals[i].data[j];
                } else {
                    //�@���������ꍇ
                    indexNormals_per_Face[j] = (unsigned short)0;
                }
            }

            //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
            paRad[i*3+0] = getRadv1_v0v1v2(
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                           );
            //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

            //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
            paRad[i*3+1] = getRadv1_v0v1v2(
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                             model_pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                           );
            //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

            //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
            paRad[i*3+2] = (float)(2*PI - (paRad[i*3+0] + paRad[i*3+1]));
            //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
        }

        float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                indexVertices_per_Face[j] = model_pMeshesFront->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                if (nFaceNormals > i) {
                    indexNormals_per_Face[j] = model_pMeshesFront->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
                } else {
                    //�@���������ꍇ
                    indexNormals_per_Face[j] = (unsigned short)0;

                }
            }
            if (nFaceNormals > i) {
                rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].x * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].y * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[0]].z * rate);
                rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].x * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].y * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[1]].z * rate);
                rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].nx += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].x * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].ny += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].y * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].nz += (model_pMeshesFront->_Normals[indexNormals_per_Face[2]].z * rate);
            } else {


                //�@���������ꍇ�A�@�����v�Z���č�肾���B

                //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                int indexVertices1 = model_pMeshesFront->_Faces[i].data[0];
                int indexVertices2 = model_pMeshesFront->_Faces[i].data[1];
                int indexVertices3 = model_pMeshesFront->_Faces[i].data[2];
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

                rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].nx += (Plane.a * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].ny += (Plane.b * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[0]].nz += (Plane.c * rate);
                rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].nx += (Plane.a * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].ny += (Plane.b * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[1]].nz += (Plane.c * rate);
                rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].nx += (Plane.a * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].ny += (Plane.b * rate);
                unit_paVtxBuffer_org[indexVertices_per_Face[2]].nz += (Plane.c * rate);

            }
        }
        int n = 0;
        int nVertices_begin = 0;
        int nVertices_end = 0;
        for (std::list<Frm::Bone*>::iterator iteBone = model_pModel3D->_toplevel_Skelettons.begin() ;
                iteBone != model_pModel3D->_toplevel_Skelettons.end(); iteBone++) {

            _TRACE_("(*iteBone)->_Name="<<((*iteBone)->_Name));
            //X�t�@�C����FrameTransformMatrix(0�t���[���ڂ̏������A�j���[�V����)���l��
            if ((*iteBone)) {
                Frm::Matrix* pMatPos = &((*iteBone)->_MatrixPos);
                if (pMatPos == 0 || pMatPos== NULL || pMatPos->isIdentity()) {
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
                    for (int i = nVertices_begin; i < nVertices_end; i++) {
                        vecVertex.x = unit_paVtxBuffer_org[i].x;
                        vecVertex.y = unit_paVtxBuffer_org[i].y;
                        vecVertex.z = unit_paVtxBuffer_org[i].z;
                        D3DXVec3TransformCoord(&vecVertex, &vecVertex, &FrameTransformMatrix);
                        vecNormal.x = unit_paVtxBuffer_org[i].nx;
                        vecNormal.y = unit_paVtxBuffer_org[i].ny;
                        vecNormal.z = unit_paVtxBuffer_org[i].nz;
                        D3DXVec3TransformNormal(&vecNormal, &vecNormal, &FrameTransformMatrix);

                        unit_paVtxBuffer_org[i].x = vecVertex.x;
                        unit_paVtxBuffer_org[i].y = vecVertex.y;
                        unit_paVtxBuffer_org[i].z = vecVertex.z;
                        unit_paVtxBuffer_org[i].nx = vecNormal.x;
                        unit_paVtxBuffer_org[i].ny = vecNormal.y;
                        unit_paVtxBuffer_org[i].nz = vecNormal.z;
                    }
                }
            }
            n++;
        }
        DELETE_IMPOSSIBLE_NULL(paNumVertices);

        //�Ō�ɖ@�����K�����Đݒ�
        D3DXVECTOR3 vec;
        for (int i = 0; i < nVertices; i++) {
            vec.x = unit_paVtxBuffer_org[i].nx;
            vec.y = unit_paVtxBuffer_org[i].ny;
            vec.z = unit_paVtxBuffer_org[i].nz;
            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                unit_paVtxBuffer_org[i].nx = 0;
                unit_paVtxBuffer_org[i].ny = 0;
                unit_paVtxBuffer_org[i].nz = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                unit_paVtxBuffer_org[i].nx = vec.x;
                unit_paVtxBuffer_org[i].ny = vec.y;
                unit_paVtxBuffer_org[i].nz = vec.z;
            }
        }
//        TRACE3("�@�����K����----------------------------");
//        for (int i = 0; i < nVertices; i++) {
//            TRACE3("["<<i<<"]=" << unit_paVtxBuffer_org[i].x << "\t, " << unit_paVtxBuffer_org[i].y << "\t, " << unit_paVtxBuffer_org[i].z << "\t, " << unit_paVtxBuffer_org[i].nx << "\t, " << unit_paVtxBuffer_org[i].ny << "\t, " << unit_paVtxBuffer_org[i].nz << "\t, " << unit_paVtxBuffer_org[i].tu << "\t, " << unit_paVtxBuffer_org[i].tv);
//        }
//        TRACE3("--------------------------------------");


        //�C���f�b�N�X�o�b�t�@�o�^
        unit_paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            unit_paIdxBuffer_org[i*3 + 0] = model_pMeshesFront->_Faces[i].data[0];
            unit_paIdxBuffer_org[i*3 + 1] = model_pMeshesFront->_Faces[i].data[1];
            unit_paIdxBuffer_org[i*3 + 2] = model_pMeshesFront->_Faces[i].data[2];
        }

        //���_�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_paVtxBuffer_org = NEW GgafDx9MeshSetModel::VERTEX[nVertices * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nVertices; j++) {
                model_paVtxBuffer_org[(i*nVertices) + j] = unit_paVtxBuffer_org[j];
                model_paVtxBuffer_org[(i*nVertices) + j].index = (float)i; //+= (nVertices*i);
            }
        }
        DELETEARR_IMPOSSIBLE_NULL(unit_paVtxBuffer_org);

        //�C���f�b�N�X�o�b�t�@���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_paIdxBuffer_org = NEW WORD[(nFaces*3) * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 0] = unit_paIdxBuffer_org[j*3 + 0] + (nVertices*i);
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 1] = unit_paIdxBuffer_org[j*3 + 1] + (nVertices*i);
                model_paIdxBuffer_org[((i*nFaces*3)+(j*3)) + 2] = unit_paIdxBuffer_org[j*3 + 2] + (nVertices*i);
            }
        }
        DELETEARR_IMPOSSIBLE_NULL(unit_paIdxBuffer_org);

        //�}�e���A�����X�g���Z�b�g�����J��Ԃ��R�s�[�ō쐬
        uint16* paFaceMaterials = NEW uint16[nFaces * prm_pMeshSetModel->_set_num];
        for (int i = 0; i < prm_pMeshSetModel->_set_num; i++) {
            for (int j = 0; j < nFaces; j++) {
                paFaceMaterials[(i*nFaces) + j] = model_pMeshesFront->_FaceMaterials[j];
            }
        }

        //�p�����[�^�����Z�b�g�����J��Ԃ��R�s�[�ō쐬
        model_papaIndexParam = NEW GgafDx9MeshSetModel::INDEXPARAM*[prm_pMeshSetModel->_set_num];
        prm_pMeshSetModel->_pa_nMaterialListGrp = NEW UINT[prm_pMeshSetModel->_set_num];
        for (int set_index = 0; set_index < prm_pMeshSetModel->_set_num; set_index++) {
            GgafDx9MeshSetModel::INDEXPARAM* paParam = NEW GgafDx9MeshSetModel::INDEXPARAM[nFaces * (set_index+1)];
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

            model_papaIndexParam[set_index] = NEW GgafDx9MeshSetModel::INDEXPARAM[paramno];
            for (int i = 0; i < paramno; i++) {
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].MaterialNo = paParam["<<i<<"].MaterialNo = "<<paParam[i].MaterialNo);
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].BaseVertexIndex = paParam["<<i<<"].BaseVertexIndex = "<<paParam[i].BaseVertexIndex);
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].MinIndex = paParam["<<i<<"].MinIndex = "<<paParam[i].MinIndex);
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].NumVertices = paParam["<<i<<"].NumVertices = "<<paParam[i].NumVertices);
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].StartIndex = paParam["<<i<<"].StartIndex = "<<paParam[i].StartIndex);
//                _TRACE_("model_papaIndexParam["<<set_index<<"]["<<i<<"].PrimitiveCount = paParam["<<i<<"].PrimitiveCount = "<<paParam[i].PrimitiveCount);
                model_papaIndexParam[set_index][i].MaterialNo = paParam[i].MaterialNo;
                model_papaIndexParam[set_index][i].BaseVertexIndex = paParam[i].BaseVertexIndex;
                model_papaIndexParam[set_index][i].MinIndex = paParam[i].MinIndex;
                model_papaIndexParam[set_index][i].NumVertices = paParam[i].NumVertices;
                model_papaIndexParam[set_index][i].StartIndex = paParam[i].StartIndex;
                model_papaIndexParam[set_index][i].PrimitiveCount = paParam[i].PrimitiveCount;
            }

            prm_pMeshSetModel->_pa_nMaterialListGrp[set_index] = paramno;

            //_TRACE_("prm_pMeshSetModel->_pa_nMaterialListGrp["<<set_index<<"]="<<prm_pMeshSetModel->_pa_nMaterialListGrp[set_index]);
            delete[] paParam;
        }

        DELETEARR_IMPOSSIBLE_NULL(paFaceMaterials);
        delete[] paRad;
        delete[] paRadSum_Vtx;
    }

    if (prm_pMeshSetModel->_pIDirect3DVertexBuffer9 == NULL) {
        //���_�o�b�t�@�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num,
                D3DUSAGE_WRITEONLY,
                GgafDx9MeshSetModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT
                &(prm_pMeshSetModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshSetModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pMeshSetModel->_model_name));

//        char str[256];
//        sprintf (str, "VertexBuffer %s = %p \n",prm_pMeshSetModel->_model_name, prm_pMeshSetModel->_pIDirect3DVertexBuffer9);
//        MessageBox(GgafDx9God::_pHWndPrimary, str, TEXT("���"), MB_OK );

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pMeshSetModel->_pIDirect3DVertexBuffer9->Lock(
                                      0,
                                      prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num,
                                      (void**)&pVertexBuffer,
                                      0
                                    );
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshSetModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pMeshSetModel->_model_name);

        memcpy(
          pVertexBuffer,
          model_paVtxBuffer_org,
          prm_pMeshSetModel->_size_vertices * prm_pMeshSetModel->_set_num
        ); //pVertexBuffer �� paVertex
        prm_pMeshSetModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMeshSetModel->_pIDirect3DIndexBuffer9 == NULL) {

        int nFaces = model_pMeshesFront->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3 * prm_pMeshSetModel->_set_num,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_DEFAULT,
                                &(prm_pMeshSetModel->_pIDirect3DIndexBuffer9),
                                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshSetModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMeshSetModel->_model_name));

        void* pIndexBuffer;
        prm_pMeshSetModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(
          pIndexBuffer ,
          model_paIdxBuffer_org,
          sizeof(WORD) * nFaces * 3 * prm_pMeshSetModel->_set_num
        );
        prm_pMeshSetModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A�����J�E���g
    int model_nMaterials = 0;
    for (list<Frm::Material*>::iterator material = model_pMeshesFront->_Materials.begin(); material != model_pMeshesFront->_Materials.end(); material++) {
        model_nMaterials++;
    }

    //�}�e���A��
    model_paD3DMaterial9 = NEW D3DMATERIAL9[model_nMaterials];
    model_papTextureCon = NEW GgafDx9TextureConnection*[model_nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = model_pMeshesFront->_Materials.begin(); material != model_pMeshesFront->_Materials.end(); material++) {
        model_paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        model_paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        model_paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        model_paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        model_paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        model_paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        model_paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        model_paD3DMaterial9[n].Specular.a = 1.000000f;
        model_paD3DMaterial9[n].Power =  (*material)->_power;

        model_paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        model_paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        model_paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        model_paD3DMaterial9[n].Emissive.a = 1.000000f;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
            model_papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
        n++;
    }

    if (model_nMaterials != n) {
        TRACE3("GgafDx9ModelManager::restoreMeshSetModel(" << prm_pMeshSetModel->_model_name << ") ���Ȃ݂Ƀ}�e���A���������������ł��Bmodel_nMaterials="<<model_nMaterials<<"/n="<<n);
    }

    //���f���ɕێ�������
    prm_pMeshSetModel->_pModel3D = model_pModel3D;
    prm_pMeshSetModel->_pMeshesFront = model_pMeshesFront;

    prm_pMeshSetModel->_paIdxBuffer_org = model_paIdxBuffer_org;
    prm_pMeshSetModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pMeshSetModel->_papaIndexParam = model_papaIndexParam;
    prm_pMeshSetModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pMeshSetModel->_papTextureCon = model_papTextureCon;
    prm_pMeshSetModel->_dwNumMaterials = model_nMaterials;
}

void GgafDx9ModelManager::restorePointSpriteModel(GgafDx9PointSpriteModel* prm_pPointSpriteModel) {

    TRACE3("GgafDx9ModelManager::restorePointSpriteModel(" << prm_pPointSpriteModel->_model_name << ")");

    prm_pPointSpriteModel->_papTextureCon = NULL;
    HRESULT hr;
    string xfile_name = CFG_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pPointSpriteModel->_model_name) + ".psprx";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)
    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile_psprx->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    checkDxException(hr, DXFILE_OK, "[GgafDx9ModelManager::restorePointSpriteModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

    //TODO:GUID�Ȃ�Ƃ�����B���͊��S�����B
    //const GUID PersonID_GUID ={ 0xB2B63407,0x6AA9,0x4618, 0x95, 0x63, 0x63, 0x1E, 0xDC, 0x20, 0x4C, 0xDE};

    char** ppaChar_TextureFile;
    float* pFloat_SquareSize;
    int* pInt_TextureSplitRowCol;
    int* pInt_VerticesNum;
    D3DVECTOR* paD3DVECTOR_Vertices;
    D3DCOLORVALUE* paD3DVECTOR_VertexColors;
    int* paInt_InitUvPtnNo;
    float* paFLOAT_InitScale;

    // 1�Z�b�g�����Ǎ���
    hr = pIDirectXFileEnumObject->GetNextDataObject(&pIDirectXFileData);
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePointSpriteModel] "<<xfile_name<<" �̓Ǎ��݂Ɏ��s���܂����B���ږ�����������");
    }
    const GUID *pGuid;
    pIDirectXFileData->GetType( &pGuid );
    //if( *pGuid == PersonID_GUID ) {
    if(true) {
        DWORD Size;
        // PersonID�e���v���[�g�f�[�^���擾
        pIDirectXFileData->GetData("SquareSize"     , &Size, (void**)&pFloat_SquareSize);
        pIDirectXFileData->GetData("TextureFile"    , &Size, (void**)&ppaChar_TextureFile);
        pIDirectXFileData->GetData("TextureSplitRowCol", &Size, (void**)&pInt_TextureSplitRowCol);
        pIDirectXFileData->GetData("VerticesNum"    , &Size, (void**)&pInt_VerticesNum);
        pIDirectXFileData->GetData("Vertices"       , &Size, (void**)&paD3DVECTOR_Vertices);
        pIDirectXFileData->GetData("VertexColors"   , &Size, (void**)&paD3DVECTOR_VertexColors);
        pIDirectXFileData->GetData("InitUvPtnNo"    , &Size, (void**)&paInt_InitUvPtnNo);
        pIDirectXFileData->GetData("InitScale"      , &Size, (void**)&paFLOAT_InitScale);

    } else {
        throwGgafCriticalException("[GgafDx9ModelManager::restorePointSpriteModel] "<<xfile_name<<" ��GUID����v���܂���B");
    }
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileData);
    //�ޔ�
    float model_fSquareSize = *pFloat_SquareSize;
    int model_texture_split_rowcol = *pInt_TextureSplitRowCol;
    int model_vertices_num = *pInt_VerticesNum;
    TRACE3("GgafDx9ModelManager::restorePointSpriteModel model_vertices_num="<<model_vertices_num);
    UINT model_size_vertices = sizeof(GgafDx9PointSpriteModel::VERTEX)*model_vertices_num;
    UINT model_size_vertex_unit = sizeof(GgafDx9PointSpriteModel::VERTEX);

    //�e�N�X�`���擾�����f���ɕێ�������
    GgafDx9TextureConnection** model_papTextureCon = NULL;
    model_papTextureCon = NEW GgafDx9TextureConnection*[1];
    model_papTextureCon[0] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);

    float texWidth  = (float)(model_papTextureCon[0]->refer()->_pD3DXIMAGE_INFO->Width); //�e�N�X�`���̕�(px)
    float texHeight = (float)(model_papTextureCon[0]->refer()->_pD3DXIMAGE_INFO->Height); //�e�N�X�`���̍���(px)���Ɠ����ɂȂ�
    FLOAT model_radius_bounding_sphere = 0;

    //���_�o�b�t�@�쐬
    GgafDx9PointSpriteModel::VERTEX* model_paVtxBuffer_org = NEW GgafDx9PointSpriteModel::VERTEX[model_vertices_num];


//    GgafDx9UvFlipper uvflipper(NULL);
//    uvflipper.setRotation(model_texture_split_rowcol,
//                                   1.0f / model_texture_split_rowcol,
//                                   1.0f / model_texture_split_rowcol );
//    uvflipper.forcePtnNoRange(0, model_texture_split_rowcol * model_texture_split_rowcol-1);
//    float u = 0;
//    float v = 0;
    float dis;
    for (int i = 0; i < model_vertices_num; i++) {
//        uvflipper.setPtnNo(paInt_InitUvPtnNo[i]);
//        uvflipper.getUV(u, v);
        model_paVtxBuffer_org[i].x = paD3DVECTOR_Vertices[i].x;
        model_paVtxBuffer_org[i].y = paD3DVECTOR_Vertices[i].y;
        model_paVtxBuffer_org[i].z = paD3DVECTOR_Vertices[i].z;
        model_paVtxBuffer_org[i].psize = (model_fSquareSize*model_texture_split_rowcol / texWidth) * paFLOAT_InitScale[i]; //PSIZE�ɂ̓s�N�Z���T�C�Y�ł͂Ȃ��{���𖄂ߍ��ށB
                                                                                                //�V�F�[�_�[�Ŋg��k���s�N�Z�����v�Z
        model_paVtxBuffer_org[i].color = D3DCOLOR_COLORVALUE(paD3DVECTOR_VertexColors[i].r,
                                                             paD3DVECTOR_VertexColors[i].g,
                                                             paD3DVECTOR_VertexColors[i].b,
                                                             paD3DVECTOR_VertexColors[i].a );
//        model_paVtxBuffer_org[i].tu = u;
//        model_paVtxBuffer_org[i].tv = v;
        model_paVtxBuffer_org[i].tu = (float)(paInt_InitUvPtnNo[i]);
        model_paVtxBuffer_org[i].tv = 0;

        dis = (FLOAT)(GgafDx9Util::sqrt_fast(model_paVtxBuffer_org[i].x * model_paVtxBuffer_org[i].x +
                                             model_paVtxBuffer_org[i].y * model_paVtxBuffer_org[i].y +
                                             model_paVtxBuffer_org[i].z * model_paVtxBuffer_org[i].z  )
                       + (((model_fSquareSize/PX_UNIT) * 1.41421356 ) / 2.0)
                     );

         if (model_radius_bounding_sphere < dis) {
             model_radius_bounding_sphere = dis;
         }
    }

//    for (int i = 0; i < model_vertices_num; i++) {
//        _TRACE_("rmodel_paVtxBuffer_org["<<i<<"].x = "<<(model_paVtxBuffer_org[i].x));
//        _TRACE_("rmodel_paVtxBuffer_org["<<i<<"].y = "<<(model_paVtxBuffer_org[i].y));
//        _TRACE_("rmodel_paVtxBuffer_org["<<i<<"].z = "<<(model_paVtxBuffer_org[i].z));
//    }
    D3DMATERIAL9*   model_paD3DMaterial9 = NULL;


    if (prm_pPointSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

        //���_�o�b�t�@�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                model_size_vertices,
                D3DUSAGE_WRITEONLY,
                GgafDx9PointSpriteModel::FVF,
                D3DPOOL_DEFAULT, //D3DPOOL_DEFAULT D3DPOOL_MANAGED
                &(prm_pPointSpriteModel->_pIDirect3DVertexBuffer9),
                NULL);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restorePointSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pPointSpriteModel->_model_name));

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pPointSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, model_size_vertices, (void**)&pVertexBuffer, 0);
        checkDxException(hr, D3D_OK, "[GgafDx9ModelManager::restorePointSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pPointSpriteModel->_model_name);
        memcpy(pVertexBuffer, model_paVtxBuffer_org, model_size_vertices); //pVertexBuffer �� paVertex
        prm_pPointSpriteModel->_pIDirect3DVertexBuffer9->Unlock();
    }

    model_paD3DMaterial9 = NEW D3DMATERIAL9[1];
    model_paD3DMaterial9[0].Diffuse.r = 1.0f;
    model_paD3DMaterial9[0].Diffuse.g = 1.0f;
    model_paD3DMaterial9[0].Diffuse.b = 1.0f;
    model_paD3DMaterial9[0].Diffuse.a = 1.0f;

    //���f���ɕێ�������
    prm_pPointSpriteModel->_paD3DMaterial9_default = model_paD3DMaterial9;
    prm_pPointSpriteModel->_papTextureCon = model_papTextureCon;
    prm_pPointSpriteModel->_dwNumMaterials = 1;
    prm_pPointSpriteModel->_fSquareSize = model_fSquareSize;
    prm_pPointSpriteModel->_fTexSize = texWidth;
    prm_pPointSpriteModel->_texture_split_rowcol = model_texture_split_rowcol;
    prm_pPointSpriteModel->_vertices_num = model_vertices_num;
    prm_pPointSpriteModel->_size_vertices = model_size_vertices;
    prm_pPointSpriteModel->_size_vertex_unit = model_size_vertex_unit;
    prm_pPointSpriteModel->_paVtxBuffer_org = model_paVtxBuffer_org;
    prm_pPointSpriteModel->_radius_bounding_sphere = model_radius_bounding_sphere;
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}


GgafResourceConnection<GgafDx9Model>* GgafDx9ModelManager::processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource) {
    TRACE3(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDx9ModelConnection* p = NEW GgafDx9ModelConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDx9ModelManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return p;
}

GgafDx9ModelManager::~GgafDx9ModelManager() {
    TRACE3("GgafDx9ModelManager::~GgafDx9ModelManager() start-->");
    RELEASE_IMPOSSIBLE_NULL(_pIDirectXFile_sprx);
    RELEASE_IMPOSSIBLE_NULL(_pIDirectXFile_psprx);
    DELETE_IMPOSSIBLE_NULL(_pTextureManager);
    TRACE3("GgafDx9ModelManager::releaseAll() ���邯�ǂ��A�����ł͊��ɉ������������̂��Ȃ��͂��ł�");
    releaseAll();
}

void GgafDx9ModelManager::restoreAll() {
    TRACE3("GgafDx9ModelManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    TRACE3("restoreAll pCurrent="<<pCurrent);
    while (pCurrent) {
        pCurrent->refer()->restore();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::restoreAll() end<--");
}

void GgafDx9ModelManager::onDeviceLostAll() {
    TRACE3("GgafDx9ModelManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    TRACE3("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent) {
        pCurrent->refer()->onDeviceLost();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::onDeviceLostAll() end<--");
}

void GgafDx9ModelManager::releaseAll() {
    TRACE3("GgafDx9ModelManager::releaseAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    while (pCurrent) {
        pCurrent->refer()->release();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::releaseAll() end<--");
}

float GgafDx9ModelManager::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
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
    if (cosV1 == 0) {
        return (float)PI/2;
    } else {
        return cosV1;
    }

}




//�u�o�܃����i�O�`�j 2009/07/05�v
//�V�F�[�_�[�ɋ������킫�A�׋����d�n�߂Ă������AD3DXLoadMeshFromX �œǂݍ��ނƏ���ɒ��_�o�b�t�@�����鎞�����鎖�ɋC�����ĔY��ł����B
//D3DXLoadMeshFromX ��X�t�@�C����ǂݍ��ނƎv�����ʂ�̒��_���i���_�C���f�b�N�X�j�ɂȂ�ۏ؂������B
//�Ⴆ�ΎO�p�`�|���S���ł�BOX�̏ꍇ�A���_8�A���_�C���f�b�N�X12(*3)�i�ʂ�12�j�A�@���x�N�g��6�A�@���C���f�b�N�X12(*3)�A�ƂȂ邪�A
//���̂悤��X�t�@�C�����e�L�X�g�G�f�B�^�ō���� D3DXLoadMeshFromX �œǂݍ��ނƒ��_��24�ɂȂ��Ă��܂��B
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
//�����̑g�ݍ��퐔�Ƃ��v����g���C�A���h�G���[�ŁA�d���ł��Ȃ���΂���Ă��Ȃ��B���܂��Ă��I�J�V�N�i�C�B�i�E�E�E�������A����͂܂����͂ɉ߂��Ȃ������I�i�΁j�j
//���̂�����̎����āA���̃t���[�v���O���}�̐l�B�͂��������ǂ�����Ă�̂��낤���H�A�݂�ȔY��łȂ��̂��Ȃ��B
