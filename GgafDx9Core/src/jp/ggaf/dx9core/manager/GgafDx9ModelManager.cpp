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
    DirectXFileCreate( &_pIDirectXFile );
    char* paChar_SpriteModelineTemplate = GgafUtil::getFileText(GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + "ggaf_spritemodel_define.x");
    if (paChar_SpriteModelineTemplate == NULL) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] �X�v���C�g���Ǎ��݃e���v���[�g\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\" ���J���܂���B");
    }
    HRESULT hr = _pIDirectXFile->RegisterTemplates(paChar_SpriteModelineTemplate, (DWORD)(strlen(paChar_SpriteModelineTemplate)));
    if(hr != DXFILE_OK) {
        throwGgafCriticalException("[GgafDx9ModelManager::restoreSpriteModel] RegisterTemplates�Ɏ��s���܂����B\""<<GGAFDX9_PROPERTY(DIR_SPRITE_MODEL)<<"ggaf_spritemodel_define.x\"���m�F���ĉ������B");
    }
    DELETE_IMPOSSIBLE_NULL(paChar_SpriteModelineTemplate);
}

GgafDx9Model* GgafDx9ModelManager::processCreateResource(char* prm_idstr) {
    //�U�蕪��
    char model_type = *prm_idstr; //���ꕶ��
    char* model_name = prm_idstr + 2; //�R�����ڈȍ~
    GgafDx9Model* pResourceModel;
    switch (model_type) {
        case 'D':
            //MeshModel
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_SYSTEMMEM);
            break;
        case 'd':
            //DynaMeshModel
            pResourceModel = createD3DXMeshModel(model_name, D3DXMESH_DYNAMIC);
            break;
        case 'X':
            //MeshModel
            pResourceModel = createMeshModel(model_name);
            break;
        case 'M': // "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V�����P�A���[�t�^�[�Q�b�g�̃��b�V�����R�Ƃ����Ӗ�
            pResourceModel = createMorphMeshModel(model_name);
            break;
        case 'S':
            //SpriteModel
            pResourceModel = createSpriteModel(model_name);
            break;
        case 'B':
            //BoardModel
            pResourceModel = createBoardModel(model_name);
            break;
        case 'C':
            //cubeModel
            pResourceModel = createD3DXMeshModel("cube", D3DXMESH_SYSTEMMEM);
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

GgafDx9SpriteModel* GgafDx9ModelManager::createSpriteModel(char* prm_model_name) {

    GgafDx9SpriteModel* pSpriteModel_New = NEW GgafDx9SpriteModel(prm_model_name);
    restoreSpriteModel(pSpriteModel_New);
    return pSpriteModel_New;
}

GgafDx9BoardModel* GgafDx9ModelManager::createBoardModel(char* prm_model_name) {
    GgafDx9BoardModel* pBoardModel_New = NEW GgafDx9BoardModel(prm_model_name);
    restoreBoardModel(pBoardModel_New);
    return pBoardModel_New;
}

GgafDx9MeshModel* GgafDx9ModelManager::createMeshModel(char* prm_model_name) {
    GgafDx9MeshModel* pMeshModel_New = NEW GgafDx9MeshModel(prm_model_name);
    restoreMeshModel(pMeshModel_New);
    return pMeshModel_New;
}

GgafDx9MorphMeshModel* GgafDx9ModelManager::createMorphMeshModel(char* prm_model_name) {
    // "M/4/xxxxx" �̏ꍇ�A�v���C�}���̃��b�V�����P�A���[�t�^�[�Q�b�g�̃��b�V�����R�Ƃ����Ӗ�
    // ������prm_model_name �� "4/xxxxx" �Ƃ���������ɂȂ��Ă���B
    // ���[�t�^�[�Q�b�g�����Ⴄ���f���́A�ʃ��f���Ƃ��������ɂ��邽�߁A���f�����ɐ��l���c���B
    GgafDx9MorphMeshModel* pMorphMeshModel_New = NEW GgafDx9MorphMeshModel(prm_model_name);
    restoreMorphMeshModel(pMorphMeshModel_New);
    return pMorphMeshModel_New;
}

void GgafDx9ModelManager::restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreMeshModel(" << prm_pMeshModel->_model_name << ")");
    //�yGgafDx9MeshModel�č\�z�i���������j�����T�v�z
    //�P�j���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ ���쐬
    //�Q�jX�t�@�C������A�Ǝ��Ɏ��̏���ǂݍ��݁A���_�o�b�t�@�A���_�C���f�b�N�X�o�b�t�@ �ɗ������ށB
    //�R�j�Q�j���s�Ȃ��ߒ��ŁA������ GgafDx9MeshModel �Ɏ��̃����o���쐬�B
    //�@�@�@�@�E���_�o�b�t�@�̎ʂ�
    //�@�@�@�@�E���_�C���f�b�N�X�o�b�t�@�̎ʂ�
    //�@�@�@�@�E�}�e���A���z��(�v�f�����}�e���A����)
    //�@�@�@�@�E�e�N�X�`���z��(�v�f�����}�e���A����)
    //�@�@�@�@�EDrawIndexedPrimitive�p�����z��(�v�f�����}�e���A�����X�g���ω�������)


    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pMeshModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�
    HRESULT hr;
//    LPDIRECT3DVERTEXBUFFER9 pIDirect3DVertexBuffer9;
//    LPDIRECT3DINDEXBUFFER9 pIDirect3DIndexBuffer9;
//    D3DMATERIAL9* paD3DMaterial9;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X iox;

    Frm::Model3D* pModel3D = NULL;
    Frm::Mesh* pMeshesFront = NULL;

    GgafDx9MeshModel::INDEXPARAM* paIndexParam = NULL;
    GgafDx9MeshModel::VERTEX* paVtxBuffer_org = NULL;
    WORD* paIdxBuffer_org = NULL;
    D3DMATERIAL9* paD3DMaterial9 = NULL;
    GgafDx9TextureConnection** papTextureCon = NULL;

    if (prm_pMeshModel->_pModel3D == NULL) {
        pModel3D = NEW Frm::Model3D();

        bool r = iox.Load(xfile_name, pModel3D);
        if (r == false) {
            throwGgafCriticalException("[GgafDx9ModelManager::restoreMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<xfile_name);
        }
        pModel3D->ConcatenateMeshes();
        pMeshesFront = pModel3D->_Meshes.front();

        int nVertices = pMeshesFront->_nVertices;
        int nFaces = pMeshesFront->_nFaces;

        paVtxBuffer_org = NEW GgafDx9MeshModel::VERTEX[nVertices];
        prm_pMeshModel->_size_vertecs = sizeof(GgafDx9MeshModel::VERTEX) * nVertices;
        prm_pMeshModel->_size_vertec_unit = sizeof(GgafDx9MeshModel::VERTEX);

        //�@���ȊO�ݒ�
        for (int i = 0; i < nVertices; i++) {
            paVtxBuffer_org[i].x = pMeshesFront->_Vertices[i].data[0];
            paVtxBuffer_org[i].y = pMeshesFront->_Vertices[i].data[1];
            paVtxBuffer_org[i].z = pMeshesFront->_Vertices[i].data[2];
            paVtxBuffer_org[i].nx = 0.0f;
            paVtxBuffer_org[i].ny = 0.0f;
            paVtxBuffer_org[i].nz = 0.0f;
            paVtxBuffer_org[i].color = D3DCOLOR_ARGB(255,255,255,255);
            paVtxBuffer_org[i].tu = pMeshesFront->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
            paVtxBuffer_org[i].tv = pMeshesFront->_TextureCoords[i].data[1];
        }

        int nTextureCoords = pMeshesFront->_nTextureCoords;
        if (nVertices < nTextureCoords) {
            TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
            TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<xfile_name);
        }

        //�@���ݒ�B
        //���L���_�̖@���͕��ω������݂�I
        //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
        //���L���_�ɁA�ʂ������ʂɏW�������ꍇ�A�P���ɕ��ω��i���Z���Ċ���j����Ɩ@���͕΂��Ă��܂��B
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
                indexVertices_per_Face[j] = pMeshesFront->_Faces[i].data[j];
                //�ʂɑ΂���@���C���f�b�N�X�R��
                indexNormals_per_Face[j] = pMeshesFront->_FaceNormals[i].data[j];
            }

            //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
            paRad[i*3+0] = getRadv1_v0v1v2(
                             pMeshesFront->_Vertices[indexVertices_per_Face[2]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[1]]
                           );
            //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

            //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
            paRad[i*3+1] = getRadv1_v0v1v2(
                             pMeshesFront->_Vertices[indexVertices_per_Face[0]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[1]],
                             pMeshesFront->_Vertices[indexVertices_per_Face[2]]
                           );
            //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

            //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
            paRad[i*3+2] = 2*PI - (paRad[i*3+0] + paRad[i*3+1]);
            //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
            paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
        }

        static float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
        for (int i = 0; i < nFaces; i++) {
            for (int j = 0; j < 3; j++) {
                indexVertices_per_Face[j] = pMeshesFront->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                indexNormals_per_Face[j] = pMeshesFront->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
            }
            rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
            paVtxBuffer_org[indexVertices_per_Face[0]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[0]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[0]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[0]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[0]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[0]].z * rate);
            rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
            paVtxBuffer_org[indexVertices_per_Face[1]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[1]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[1]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[1]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[1]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[1]].z * rate);
            rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
            paVtxBuffer_org[indexVertices_per_Face[2]].nx += (pMeshesFront->_Normals[indexNormals_per_Face[2]].x * rate);
            paVtxBuffer_org[indexVertices_per_Face[2]].ny += (pMeshesFront->_Normals[indexNormals_per_Face[2]].y * rate);
            paVtxBuffer_org[indexVertices_per_Face[2]].nz += (pMeshesFront->_Normals[indexNormals_per_Face[2]].z * rate);
        }

        //�Ō�ɖ@�����K�����Đݒ�
        static D3DXVECTOR3 vec;
        for (int i = 0; i < nVertices; i++) {
            vec.x = paVtxBuffer_org[i].nx;
            vec.y = paVtxBuffer_org[i].ny;
            vec.z = paVtxBuffer_org[i].nz;
            if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                paVtxBuffer_org[i].nx = 0;
                paVtxBuffer_org[i].ny = 0;
                paVtxBuffer_org[i].nz = 0;
            } else {
                D3DXVec3Normalize( &vec, &vec);
                paVtxBuffer_org[i].nx = vec.x;
                paVtxBuffer_org[i].ny = vec.y;
                paVtxBuffer_org[i].nz = vec.z;
            }
        }
        TRACE3("�@�����K����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        for (int i = 0; i < nVertices; i++) {
            TRACE3("["<<i<<"]=" << paVtxBuffer_org[i].x << "\t, " << paVtxBuffer_org[i].y << "\t, " << paVtxBuffer_org[i].z << "\t, " << paVtxBuffer_org[i].nx << "\t, " << paVtxBuffer_org[i].ny << "\t, " << paVtxBuffer_org[i].nz << "\t, " << paVtxBuffer_org[i].tu << "\t, " << paVtxBuffer_org[i].tv);
        }
        TRACE3("�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[");
        //�C���f�b�N�X�o�b�t�@�o�^
        paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            paIdxBuffer_org[i*3 + 0] = pMeshesFront->_Faces[i].data[0];
            paIdxBuffer_org[i*3 + 1] = pMeshesFront->_Faces[i].data[1];
            paIdxBuffer_org[i*3 + 2] = pMeshesFront->_Faces[i].data[2];
        }

        //�}�e���A�����X�g
//        UINT aMaterialsGrp = UINT[nFaces];
//        for (int i = 0; i < nFaces; i++) {
//            aMaterialsGrp[i] =  pMeshesFront->_FaceMaterials[i];
//        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDx9MeshModel::INDEXPARAM* paParam = NEW GgafDx9MeshModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = INT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = pMeshesFront->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //TRACE3("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = INT_MAX; //����u���C�N���ɐݒ�A�ςȒl�ɂ��Ƃ�
                paParam[paramno].NumVertices = INT_MAX; //����u���C�N���ɐݒ�
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = INT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = INT_MAX;
                }
                paramno++;
            }

            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDx9MeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            paIndexParam[i].MinIndex = paParam[i].MinIndex;
            paIndexParam[i].NumVertices = paParam[i].NumVertices;
            paIndexParam[i].StartIndex = paParam[i].StartIndex;
            paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
        }
        prm_pMeshModel->_nMaterialListGrp = paramno;
        delete[] paRad;
        delete[] paRadSum_Vtx;
        delete[] paParam;
    }

    if (prm_pMeshModel->_pIDirect3DVertexBuffer9 == NULL) {

        //���_�o�b�t�@�쐬
        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pMeshModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9MeshModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pMeshModel->_pIDirect3DVertexBuffer9),
                NULL);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pMeshModel->_model_name));

//        char str[256];
//        sprintf (str, "VertexBuffer %s = %p \n",prm_pMeshModel->_model_name, prm_pMeshModel->_pIDirect3DVertexBuffer9);
//        MessageBox(GgafDx9God::_hWnd, str, TEXT("���"), MB_OK );

        //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
        void *pVertexBuffer;
        hr = prm_pMeshModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pMeshModel->_size_vertecs, (void**)&pVertexBuffer, 0);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pMeshModel->_model_name);
        memcpy(pVertexBuffer, paVtxBuffer_org, prm_pMeshModel->_size_vertecs); //pVertexBuffer �� paVertex
        prm_pMeshModel->_pIDirect3DVertexBuffer9->Unlock();
    }


    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMeshModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = pMeshesFront->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_MANAGED,
                                &(prm_pMeshModel->_pIDirect3DIndexBuffer9),
                                NULL);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A��
    int nMaterials = pMeshesFront->_nMaterials;
    paD3DMaterial9 = NEW D3DMATERIAL9[nMaterials];
    papTextureCon = NEW GgafDx9TextureConnection*[nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = pMeshesFront->_Materials.begin(); material != pMeshesFront->_Materials.end(); material++) {
        Sleep(1);
        paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        paD3DMaterial9[n].Specular.a = 1.000000;
        paD3DMaterial9[n].Power =  (*material)->_power;

        paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        paD3DMaterial9[n].Emissive.a = 1.000000;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
            papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
        n++;
    }

    if (nMaterials != n) {
        TRACE3("���Ȃ݂Ƀ}�e���A���������������ł��BnMaterials="<<nMaterials<<"/n="<<n);
    }

    //���f���ɕێ�������
    prm_pMeshModel->_pModel3D = pModel3D;
    prm_pMeshModel->_pMeshesFront = pMeshesFront;

    prm_pMeshModel->_paIdxBuffer_org = paIdxBuffer_org;
    prm_pMeshModel->_paVtxBuffer_org = paVtxBuffer_org;
    prm_pMeshModel->_paIndexParam = paIndexParam;
    prm_pMeshModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pMeshModel->_papTextureCon = papTextureCon;
    prm_pMeshModel->_dwNumMaterials = nMaterials;
}




void GgafDx9ModelManager::restoreMorphMeshModel(GgafDx9MorphMeshModel* prm_pMorphMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreMorphMeshModel(" << prm_pMorphMeshModel->_model_name << ")");
    //�yGgafDx9MorphMeshModel�č\�z�i���������j�����T�v�z
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
        paXfileName[i] = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(xfilename_base) + "_" + (char)('0'+i) + ".x"; //"ceres_0.x"�ƂȂ�
    }
    HRESULT hr;
//    LPDIRECT3DVERTEXBUFFER9 pIDirect3DVertexBuffer9;
//    LPDIRECT3DINDEXBUFFER9 pIDirect3DIndexBuffer9;
//    D3DMATERIAL9* paD3DMaterial9;

    //�������ޒ��_�o�b�t�@�f�[�^�쐬
    ToolBox::IO_Model_X* paIOX = NULL;
    Frm::Model3D** papModel3D = NULL;
    Frm::Mesh** papMeshesFront = NULL;

    GgafDx9MorphMeshModel::INDEXPARAM* paIndexParam = NULL;
    GgafDx9MorphMeshModel::VERTEX_PRIMARY* paVtxBuffer_org_primary = NULL;
    GgafDx9MorphMeshModel::VERTEX_MORPH** papaVtxBuffer_org_morph = NULL;
    WORD* paIdxBuffer_org = NULL;
    D3DMATERIAL9* paD3DMaterial9 = NULL;
    GgafDx9TextureConnection** papTextureCon = NULL;

    if (prm_pMorphMeshModel->_papModel3D == NULL) {
        paIOX = NEW ToolBox::IO_Model_X[morph_target_num+1];
        papModel3D = NEW Frm::Model3D*[morph_target_num+1];
        papMeshesFront = NEW Frm::Mesh*[morph_target_num+1];
        papaVtxBuffer_org_morph = NEW GgafDx9MorphMeshModel::VERTEX_MORPH*[morph_target_num];
        int nVertices;
        int nFaces;

        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            papModel3D[pattern] = NEW Frm::Model3D();
            bool r = paIOX[pattern].Load(paXfileName[pattern], papModel3D[pattern]);
            if (r == false) {
                throwGgafCriticalException("[GgafDx9ModelManager::restoreMorphMeshModel] X�t�@�C���̓Ǎ��ݎ��s�B�Ώ�="<<paXfileName[pattern]);
            }
            papModel3D[pattern]->ConcatenateMeshes();
            papMeshesFront[pattern] = papModel3D[pattern]->_Meshes.front();

            nVertices = papMeshesFront[pattern]->_nVertices;
            nFaces = papMeshesFront[pattern]->_nFaces;

            if (pattern == 0) {
                //�v���C�}�����b�V��
                paVtxBuffer_org_primary = NEW GgafDx9MorphMeshModel::VERTEX_PRIMARY[nVertices];
                prm_pMorphMeshModel->_size_vertecs_primary = sizeof(GgafDx9MorphMeshModel::VERTEX_PRIMARY) * nVertices;
                prm_pMorphMeshModel->_size_vertec_unit_primary = sizeof(GgafDx9MorphMeshModel::VERTEX_PRIMARY);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    paVtxBuffer_org_primary[i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    paVtxBuffer_org_primary[i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    paVtxBuffer_org_primary[i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    paVtxBuffer_org_primary[i].nx = 0.0f;
                    paVtxBuffer_org_primary[i].ny = 0.0f;
                    paVtxBuffer_org_primary[i].nz = 0.0f;
                    paVtxBuffer_org_primary[i].color = D3DCOLOR_ARGB(255,255,255,255);
                    paVtxBuffer_org_primary[i].tu = papMeshesFront[pattern]->_TextureCoords[i].data[0];  //�o�������UV���W�ݒ�
                    paVtxBuffer_org_primary[i].tv = papMeshesFront[pattern]->_TextureCoords[i].data[1];
                }
            } else {
                //���[�t�^�[�Q�b�g���b�V��
                papaVtxBuffer_org_morph[pattern-1] = NEW GgafDx9MorphMeshModel::VERTEX_MORPH[nVertices];
                prm_pMorphMeshModel->_size_vertecs_morph = sizeof(GgafDx9MorphMeshModel::VERTEX_MORPH) * nVertices;
                prm_pMorphMeshModel->_size_vertec_unit_morph = sizeof(GgafDx9MorphMeshModel::VERTEX_MORPH);
                //�@���ȊO�ݒ�
                for (int i = 0; i < nVertices; i++) {
                    papaVtxBuffer_org_morph[pattern-1][i].x = papMeshesFront[pattern]->_Vertices[i].data[0];
                    papaVtxBuffer_org_morph[pattern-1][i].y = papMeshesFront[pattern]->_Vertices[i].data[1];
                    papaVtxBuffer_org_morph[pattern-1][i].z = papMeshesFront[pattern]->_Vertices[i].data[2];
                    papaVtxBuffer_org_morph[pattern-1][i].nx = 0.0f;
                    papaVtxBuffer_org_morph[pattern-1][i].ny = 0.0f;
                    papaVtxBuffer_org_morph[pattern-1][i].nz = 0.0f;
                }
            }

            int nTextureCoords = papMeshesFront[pattern]->_nTextureCoords;
            if (nVertices < nTextureCoords) {
                TRACE3("nTextureCoords="<<nTextureCoords<<"/nVertices="<<nVertices);
                TRACE3("UV���W�����A���_�o�b�t�@�����z���Ă܂��B���_���܂ł����ݒ肳��܂���B�Ώ�="<<paXfileName[pattern]);
            }

            //�@���ݒ�B
            //���L���_�̖@���͕��ω������݂�I
            //�y2009/03/04�̔]�݂��ɂ��A�C�f�B�A�z
            //���L���_�ɁA�ʂ������ʂɏW�������ꍇ�A�P���ɕ��ω��i���Z���Ċ���j����Ɩ@���͕΂��Ă��܂��B
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
                    indexVertices_per_Face[j] = papMeshesFront[pattern]->_Faces[i].data[j];
                    //�ʂɑ΂���@���C���f�b�N�X�R��
                    indexNormals_per_Face[j] = papMeshesFront[pattern]->_FaceNormals[i].data[j];
                }

                //���_�C���f�b�N�X A �̊p(��CAB)�����߂āA�z��ɕێ�
                paRad[i*3+0] = getRadv1_v0v1v2(
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[2]],
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[0]],
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[1]]
                               );
                //A �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[0]] += paRad[i*3+0];

                //���_�C���f�b�N�X B �̊p(��ABC)�����߂āA�z��ɕێ�
                paRad[i*3+1] = getRadv1_v0v1v2(
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[0]],
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[1]],
                                 papMeshesFront[pattern]->_Vertices[indexVertices_per_Face[2]]
                               );
                //B �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[1]] += paRad[i*3+1];

                //���_�C���f�b�N�X C �̊p(��ACB)�����߂āA�z��ɕێ�
                paRad[i*3+2] = 2*PI - (paRad[i*3+0] + paRad[i*3+1]);
                //C �̒��_�C���f�b�N�X�ԍ��ɕR���āA�p�����Z
                paRadSum_Vtx[indexVertices_per_Face[2]] += paRad[i*3+2];
            }

            static float rate; //���̖@���̏o�Ă��钸�_�̐����p�̗��B�܂�@���x�N�g���Ɋ|���闦�B���̖@���x�N�g���̉e���̋����B
            for (int i = 0; i < nFaces; i++) {
                for (int j = 0; j < 3; j++) {
                    indexVertices_per_Face[j] = papMeshesFront[pattern]->_Faces[i].data[j];       //�ʂɑ΂��钸�_�C���f�b�N�X�R��
                    indexNormals_per_Face[j] = papMeshesFront[pattern]->_FaceNormals[i].data[j];  //�ʂɑ΂���@���C���f�b�N�X�R��
                }
                rate = (paRad[i*3+0] / paRadSum_Vtx[indexVertices_per_Face[0]]);
                if (pattern == 0) { //�v���C�}�����b�V��
                    paVtxBuffer_org_primary[indexVertices_per_Face[0]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].x * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[0]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].y * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[0]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].z * rate);
                } else {            //���[�t�^�[�Q�b�g���b�V��
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].x * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].y * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[0]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[0]].z * rate);
                }
                rate = (paRad[i*3+1] / paRadSum_Vtx[indexVertices_per_Face[1]]);
                if (pattern == 0) { //�v���C�}�����b�V��
                    paVtxBuffer_org_primary[indexVertices_per_Face[1]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].x * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[1]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].y * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[1]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].z * rate);
                } else {            //���[�t�^�[�Q�b�g���b�V��
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].x * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].y * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[1]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[1]].z * rate);
                }
                rate = (paRad[i*3+2] / paRadSum_Vtx[indexVertices_per_Face[2]]);
                if (pattern == 0) { //�v���C�}�����b�V��
                    paVtxBuffer_org_primary[indexVertices_per_Face[2]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].x * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[2]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].y * rate);
                    paVtxBuffer_org_primary[indexVertices_per_Face[2]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].z * rate);
                } else {            //���[�t�^�[�Q�b�g���b�V��
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nx += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].x * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].ny += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].y * rate);
                    papaVtxBuffer_org_morph[pattern-1][indexVertices_per_Face[2]].nz += (papMeshesFront[pattern]->_Normals[indexNormals_per_Face[2]].z * rate);
                }
            }

            //�Ō�ɖ@�����K�����Đݒ�
            static D3DXVECTOR3 vec;
            for (int i = 0; i < nVertices; i++) {
                if (pattern == 0) { //�v���C�}�����b�V��
                    vec.x = paVtxBuffer_org_primary[i].nx;
                    vec.y = paVtxBuffer_org_primary[i].ny;
                    vec.z = paVtxBuffer_org_primary[i].nz;
                    if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                        paVtxBuffer_org_primary[i].nx = 0;
                        paVtxBuffer_org_primary[i].ny = 0;
                        paVtxBuffer_org_primary[i].nz = 0;
                    } else {
                        D3DXVec3Normalize( &vec, &vec);
                        paVtxBuffer_org_primary[i].nx = vec.x;
                        paVtxBuffer_org_primary[i].ny = vec.y;
                        paVtxBuffer_org_primary[i].nz = vec.z;
                    }
                } else {           //���[�t�^�[�Q�b�g���b�V��
                    vec.x = papaVtxBuffer_org_morph[pattern-1][i].nx;
                    vec.y = papaVtxBuffer_org_morph[pattern-1][i].ny;
                    vec.z = papaVtxBuffer_org_morph[pattern-1][i].nz;
                    if (vec.x == 0 && vec.y == 0 && vec.z == 0) {
                        papaVtxBuffer_org_morph[pattern-1][i].nx = 0;
                        papaVtxBuffer_org_morph[pattern-1][i].ny = 0;
                        papaVtxBuffer_org_morph[pattern-1][i].nz = 0;
                    } else {
                        D3DXVec3Normalize( &vec, &vec);
                        papaVtxBuffer_org_morph[pattern-1][i].nx = vec.x;
                        papaVtxBuffer_org_morph[pattern-1][i].ny = vec.y;
                        papaVtxBuffer_org_morph[pattern-1][i].nz = vec.z;
                    }
                }
            }
            delete[] paRad;
            delete[] paRadSum_Vtx;
        } //for (int pattern = 0; pattern < 2; pattern++)


        //�C���f�b�N�X�o�b�t�@�擾
        paIdxBuffer_org = NEW WORD[nFaces*3];
        for (int i = 0; i < nFaces; i++) {
            paIdxBuffer_org[i*3 + 0] = papMeshesFront[0]->_Faces[i].data[0];
            paIdxBuffer_org[i*3 + 1] = papMeshesFront[0]->_Faces[i].data[1];
            paIdxBuffer_org[i*3 + 2] = papMeshesFront[0]->_Faces[i].data[2];
        }

        //�}�e���A�����X�g
//        UINT aMaterialsGrp = UINT[nFaces];
//        for (int i = 0; i < nFaces; i++) {
//            aMaterialsGrp[i] =  pMeshesFront->_FaceMaterials[i];
//        }

        //�`�掞�iDrawIndexedPrimitive�j�̃p�����[�^���X�g�쐬
        GgafDx9MeshModel::INDEXPARAM* paParam = NEW GgafDx9MeshModel::INDEXPARAM[nFaces];

        int prev_materialno = -1;
        int materialno = 0;
        int paramno = 0;
        int faceNoCnt_break = 0;
        int prev_faceNoCnt_break = -1;
        UINT max_num_vertices = 0;
        UINT min_num_vertices = INT_MAX;

        int faceNoCnt;
        for (faceNoCnt = 0; faceNoCnt < nFaces; faceNoCnt++) {
            materialno = papMeshesFront[0]->_FaceMaterials[faceNoCnt];
            if (prev_materialno != materialno) {
                //TRACE3("BREAK! paramno="<<paramno);
                prev_faceNoCnt_break = faceNoCnt_break;
                faceNoCnt_break = faceNoCnt;

                paParam[paramno].MaterialNo = materialno;
                paParam[paramno].BaseVertexIndex = 0;
                paParam[paramno].MinIndex = INT_MAX; //����u���C�N���ɐݒ�A�ςȒl�ɂ��Ƃ�
                paParam[paramno].NumVertices = INT_MAX; //����u���C�N���ɐݒ�
                paParam[paramno].StartIndex = faceNoCnt*3;
                paParam[paramno].PrimitiveCount = INT_MAX; //����u���C�N���ɐݒ�

                if (faceNoCnt > 0) {
                    paParam[paramno-1].MinIndex = min_num_vertices;
                    paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
                    paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt_break - prev_faceNoCnt_break);
                    //���Z�b�g
                    max_num_vertices = 0;
                    min_num_vertices = INT_MAX;
                }
                paramno++;
            }

            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (max_num_vertices <  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                max_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 0]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 0];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 1]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 1];
            }
            if (min_num_vertices >  paIdxBuffer_org[faceNoCnt*3 + 2]) {
                min_num_vertices = paIdxBuffer_org[faceNoCnt*3 + 2];
            }
            prev_materialno = materialno;
        }
        if (nFaces > 0) {
            paParam[paramno-1].MinIndex = min_num_vertices;
            paParam[paramno-1].NumVertices = (UINT)(max_num_vertices - min_num_vertices + 1);
            paParam[paramno-1].PrimitiveCount = (UINT)(faceNoCnt - faceNoCnt_break);
        }

        paIndexParam = NEW GgafDx9MorphMeshModel::INDEXPARAM[paramno];
        for (int i = 0; i < paramno; i++) {
            paIndexParam[i].MaterialNo = paParam[i].MaterialNo;
            paIndexParam[i].BaseVertexIndex = paParam[i].BaseVertexIndex;
            paIndexParam[i].MinIndex = paParam[i].MinIndex;
            paIndexParam[i].NumVertices = paParam[i].NumVertices;
            paIndexParam[i].StartIndex = paParam[i].StartIndex;
            paIndexParam[i].PrimitiveCount = paParam[i].PrimitiveCount;
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
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] GgafDx9God::_pID3DDevice9->CreateVertexDeclaration ���s model="<<(prm_pMorphMeshModel->_model_name));
//�X�g���[�����擾        hr = m_pDecl->GetDeclaration( m_pElement, &m_numElements);

        DELETEARR_IMPOSSIBLE_NULL(paDecl);
    }

    if (prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary == NULL) {
        prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph = NEW LPDIRECT3DVERTEXBUFFER9[morph_target_num];
        for (int pattern = 0; pattern < morph_target_num+1; pattern++) {
            //���_�o�b�t�@�쐬
            if (pattern == 0) {
                hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertecs_primary,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDx9MorphMeshModel::FVF,
                        D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary),
                        NULL);
                mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i�v���C�}���j model="<<(prm_pMorphMeshModel->_model_name));
                //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Lock(0, prm_pMorphMeshModel->_size_vertecs_primary, (void**)&pVertexBuffer, 0);
                mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i�v���C�}���j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, paVtxBuffer_org_primary, prm_pMorphMeshModel->_size_vertecs_primary); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_pIDirect3DVertexBuffer9_primary->Unlock();
            } else {
                hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                        prm_pMorphMeshModel->_size_vertecs_morph,
                        D3DUSAGE_WRITEONLY,
                        0, //GgafDx9MorphMeshModel::FVF,
                        D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                        &(prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]),
                        NULL);
                mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateVertexBuffer ���s�i���[�t:"<<pattern-1<<"�j model="<<(prm_pMorphMeshModel->_model_name));
                //�o�b�t�@�֍쐬�ςݒ��_�f�[�^�𗬂�����
                void *pVertexBuffer;
                hr = prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Lock(0, prm_pMorphMeshModel->_size_vertecs_morph, (void**)&pVertexBuffer, 0);
                mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s�i���[�t:"<<pattern-1<<"�j model="<<prm_pMorphMeshModel->_model_name);
                memcpy(pVertexBuffer, papaVtxBuffer_org_morph[pattern-1], prm_pMorphMeshModel->_size_vertecs_morph); //pVertexBuffer �� paVertex
                prm_pMorphMeshModel->_paIDirect3DVertexBuffer9_morph[pattern-1]->Unlock();
            }
        }
    }



    //�������ރC���f�b�N�X�o�b�t�@�f�[�^�쐬
    if (prm_pMorphMeshModel->_pIDirect3DIndexBuffer9 == NULL) {
        int nFaces = papMeshesFront[0]->_nFaces;

        hr = GgafDx9God::_pID3DDevice9->CreateIndexBuffer(
                               sizeof(WORD) * nFaces * 3,
                                D3DUSAGE_WRITEONLY,
                                D3DFMT_INDEX16,
                                D3DPOOL_MANAGED,
                                &(prm_pMorphMeshModel->_pIDirect3DIndexBuffer9),
                                NULL);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreMorphMeshModel] _pID3DDevice9->CreateIndexBuffer ���s model="<<(prm_pMorphMeshModel->_model_name));
        void* pIndexBuffer;
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Lock(0,0,(void**)&pIndexBuffer,0);
        memcpy(pIndexBuffer , paIdxBuffer_org , sizeof(WORD) * nFaces * 3);
        prm_pMorphMeshModel->_pIDirect3DIndexBuffer9->Unlock();
    }

    //�}�e���A��
    int nMaterials = papMeshesFront[0]->_nMaterials;
    paD3DMaterial9 = NEW D3DMATERIAL9[nMaterials];
    papTextureCon = NEW GgafDx9TextureConnection*[nMaterials];

    char* texture_filename;
    int n = 0;
    for (list<Frm::Material*>::iterator material = papMeshesFront[0]->_Materials.begin(); material != papMeshesFront[0]->_Materials.end(); material++) {
        Sleep(1);
        paD3DMaterial9[n].Diffuse.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Diffuse.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Diffuse.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Diffuse.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Ambient.r = (*material)->_FaceColor.data[0];
        paD3DMaterial9[n].Ambient.g = (*material)->_FaceColor.data[1];
        paD3DMaterial9[n].Ambient.b = (*material)->_FaceColor.data[2];
        paD3DMaterial9[n].Ambient.a = (*material)->_FaceColor.data[3];

        paD3DMaterial9[n].Specular.r = (*material)->_SpecularColor.data[0];
        paD3DMaterial9[n].Specular.g = (*material)->_SpecularColor.data[1];
        paD3DMaterial9[n].Specular.b = (*material)->_SpecularColor.data[2];
        paD3DMaterial9[n].Specular.a = 1.000000;
        paD3DMaterial9[n].Power =  (*material)->_power;

        paD3DMaterial9[n].Emissive.r = (*material)->_EmissiveColor.data[0];
        paD3DMaterial9[n].Emissive.g = (*material)->_EmissiveColor.data[1];
        paD3DMaterial9[n].Emissive.b = (*material)->_EmissiveColor.data[2];
        paD3DMaterial9[n].Emissive.a = 1.000000;

        texture_filename = (char*)((*material)->_TextureName.c_str());
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`���������͐^�����ȃe�N�X�`���ɒu������
            papTextureCon[n] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
        }
        n++;
    }

    if (nMaterials != n) {
        TRACE3("���Ȃ݂Ƀ}�e���A���������������ł��BnMaterials="<<nMaterials<<"/n="<<n);
    }

    DELETEARR_IMPOSSIBLE_NULL(paIOX);
    DELETEARR_IMPOSSIBLE_NULL(paXfileName);

    //���f���ɕێ�������
    prm_pMorphMeshModel->_papModel3D = papModel3D;
    prm_pMorphMeshModel->_papMeshesFront = papMeshesFront;
    prm_pMorphMeshModel->_paIdxBuffer_org = paIdxBuffer_org;
    prm_pMorphMeshModel->_paVtxBuffer_org_primary = paVtxBuffer_org_primary;
    prm_pMorphMeshModel->_papaVtxBuffer_org_morph = papaVtxBuffer_org_morph;
    prm_pMorphMeshModel->_paIndexParam = paIndexParam;
    prm_pMorphMeshModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pMorphMeshModel->_papTextureCon = papTextureCon;
    prm_pMorphMeshModel->_dwNumMaterials = nMaterials;
}


void GgafDx9ModelManager::restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel) {
    TRACE3("GgafDx9ModelManager::restoreD3DXMeshModel(" << prm_pD3DXMeshModel->_model_name << ")");
    //�yrestoreD3DXMeshModel�č\�z�i���������j�����T�v�z
    //1)D3DXLoadMeshFromX���g�p����X�t�@�C����ǂݍ���
    //2)GgafDx9D3DXMeshModel�̃����o�ɃZ�b�g
    //TODO:GgafDx9D3DXMeshModel�͂����K�v�����̂�������Ȃ��B

    //X�t�@�C���̃��[�h���ĕK�v�ȓ��e��GgafDx9D3DXMeshModel�����o�ɐݒ肵�C���X�^���X�Ƃ��Ċ�����������
    LPD3DXMESH pID3DXMesh; //���b�V��(ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�j
    D3DMATERIAL9* paD3DMaterial9; //�}�e���A��(D3DXMATERIAL�\���̂̔z��̐擪�v�f���w���|�C���^�j
    GgafDx9TextureConnection** papTextureCon; //�e�N�X�`���z��(IDirect3DTexture9�C���^�[�t�F�C�X�ւ̃|�C���^��ێ�����I�u�W�F�N�g�j
    DWORD dwNumMaterials;
    string xfile_name = GGAFDX9_PROPERTY(DIR_MESH_MODEL) + string(prm_pD3DXMeshModel->_model_name) + ".x"; //���f�����{".x"��X�t�@�C�����ɂȂ�

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
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXLoadMeshFromX�ɂ�郍�[�h�����s�B�Ώ�="<<xfile_name);

    //�œK��
    DWORD *pAdjacency = NEW DWORD [ pID3DXMesh->GetNumFaces() * 3 ];
    hr = pID3DXMesh->GenerateAdjacency( 1e-6f, pAdjacency );
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] GenerateAdjacency������܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT, pAdjacency, NULL, NULL, NULL );
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXMESHOPT_ATTRSORT�ł��܂���B�Ώ�="<<xfile_name);
    hr = pID3DXMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, pAdjacency, NULL, NULL, NULL );
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel] D3DXMESHOPT_VERTEXCACHE�ł��܂���B�Ώ�="<<xfile_name);
    DELETEARR_IMPOSSIBLE_NULL(pAdjacency);

    //�}�e���A�������o��
    D3DXMATERIAL* paD3DMaterial9_tmp = (D3DXMATERIAL*)(pID3DXBuffer->GetBufferPointer());
    //��2008/02/02 �̔]�݂���
    // ����Ă��邱�ƃ���
    // GetBufferPointer()�Ŏ擾�ł��� D3DXMATERIAL�\���̔z��̃����o��MatD3D (D3DMATERIAL9�\����) ���~�����B
    //�i��GgafDx9D3DXMeshModel�̃����o�[�����ɂ��������߁j�B pID3DXBuffer_tmp �̕��͂������Ɖ��(Release())���悤�Ƃ����B
    // ������������ D3DXMATERIAL�\���̔z���������悤���A�����ɂ͏����Ȃ���������񂪁c�i�n�}��G�j�B
    // �����ł������Ȃ��̂ŁApaD3DMaterial9_tmp �̍\���̂𕨗��R�s�[�����ĕۑ����邱�Ƃɂ��܂���`�A���`���`���܂��傤�B
    paD3DMaterial9 = NEW D3DMATERIAL9[dwNumMaterials];
    for( DWORD i = 0; i < dwNumMaterials; i++){
        paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
    }

    //�}�e���A����Diffuse���˂�Ambient���˂ɃR�s�[����
    //���R�FAmbient���C�g���g�p�����������B���̂��߂ɂ͓��RAmbient���˒l���}�e���A���ɐݒ肵�Ȃ���΂����Ȃ���
    //x�t�@�C���̃}�e���A���ɂ�Ambient���˒l�͐ݒ�ł��Ȃ��i�݂����j�A������Diffuse���˒l��
    //Ambient���˒l���p���邱�Ƃɂ���B�Ƃ肠�����B
    //��2009/3/13��
    //�Œ�@�\�͂����g��Ȃ��B�}�e���A��Diffuse�̓V�F�[�_�[�̃p�����[�^�݂̂ŗ��p���Ă���B
    //TODO:�}�e���A��Ambient�͎g��Ȃ��B�������������H
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        paD3DMaterial9[i].Ambient = paD3DMaterial9[i].Diffuse;
    }

    //�e�N�X�`�������o��
    papTextureCon = NEW GgafDx9TextureConnection*[dwNumMaterials];
    char* texture_filename;
    for( DWORD i = 0; i < dwNumMaterials; i++) {
        texture_filename = paD3DMaterial9_tmp[i].pTextureFilename;
        if (texture_filename != NULL && lstrlen(texture_filename) > 0 ) {
            papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection(texture_filename);
        } else {
            //�e�N�X�`������
            papTextureCon[i] = (GgafDx9TextureConnection*)_pTextureManager->getConnection("white.png");
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
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreD3DXMeshModel]  pID3DXMesh->CloneMeshFVF()���s�B�Ώ�="<<xfile_name);
        D3DXComputeNormals(pID3DXMesh_tmp, NULL); //�@���v�Z
        RELEASE_IMPOSSIBLE_NULL(pID3DXMesh);
        pID3DXMesh = pID3DXMesh_tmp;
    }

    //���b�V���A�}�e���A���A�e�N�X�`���̎Q�ƁA�}�e���A���������f���I�u�W�F�N�g�ɕێ�������
    prm_pD3DXMeshModel->_pID3DXMesh = pID3DXMesh;
    prm_pD3DXMeshModel->_paD3DMaterial9_default = paD3DMaterial9;
    prm_pD3DXMeshModel->_papTextureCon = papTextureCon;
    prm_pD3DXMeshModel->_dwNumMaterials = dwNumMaterials;
}

void GgafDx9ModelManager::restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel) {
    TRACE3("GgafDx9ModelManager::restoreSpriteModel(" << prm_pSpriteModel->_model_name << ")");

    prm_pSpriteModel->_pTextureCon = NULL;
    prm_pSpriteModel->_paRectUV = NULL;


    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pSpriteModel->_model_name) + ".sprx";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    mightDx9Exception(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreSpriteModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

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

    //�e�N�X�`���擾�����f���ɕێ�������
    //string texture_filename = GGAFDX9_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pSpriteModel->_pTextureCon = pTextureCon;

    GgafDx9SpriteModel::VERTEX* paVertex = NEW GgafDx9SpriteModel::VERTEX[4];
    prm_pSpriteModel->_size_vertecs = sizeof(GgafDx9SpriteModel::VERTEX)*4;
    prm_pSpriteModel->_size_vertec_unit = sizeof(GgafDx9SpriteModel::VERTEX);


//    //1px�������uv�̑傫�������߂�
//     D3DSURFACE_DESC d3dsurface_desc;
//     pTextureCon->view()->GetLevelDesc(0, &d3dsurface_desc);
//     float pxU = 1.0 / d3dsurface_desc.Width; //�e�N�X�`���̕�(px)�Ŋ���
//     float pxV = 1.0 / d3dsurface_desc.Height; //�e�N�X�`���̍���(px)�Ŋ���


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
    paVertex[1].tu = 1.0/(float)(*pInt_ColNum_TextureSplit);// + (pxU/2);
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
    paVertex[2].tv = 1.0/(float)(*pInt_RowNum_TextureSplit);// + (pxV/2);
    //�E��
    paVertex[3].x = *pFloat_Size_SpriteModelWidth / 2 / PX_UNIT;
    paVertex[3].y = *pFloat_Size_SpriteModelHeight / -2 / PX_UNIT;
    paVertex[3].z = 0.0f;
    paVertex[3].nx = 0.0f;
    paVertex[3].ny = 0.0f;
    paVertex[3].nz = -1.0f;
    paVertex[3].color = D3DCOLOR_ARGB(255,255,255,255);
    paVertex[3].tu = 1.0/(float)(*pInt_ColNum_TextureSplit);// + (pxU/2);
    paVertex[3].tv = 1.0/(float)(*pInt_RowNum_TextureSplit);// + (pxV/2);

    //�o�b�t�@�쐬
    if (prm_pSpriteModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pSpriteModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9SpriteModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pSpriteModel->_pIDirect3DVertexBuffer9),
                NULL);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pSpriteModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pSpriteModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pSpriteModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreSpriteModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pSpriteModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pSpriteModel->_size_vertecs); //pVertexBuffer �� paVertex
    prm_pSpriteModel->_pIDirect3DVertexBuffer9->Unlock();

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭�����猩�����������B

    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_ani = row*(*pInt_ColNum_TextureSplit)+col;
            paRectUV[pattno_ani]._aUV[0].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[0].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[1].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[1].tv = (float)(1.0/(*pInt_RowNum_TextureSplit)*row);

            paRectUV[pattno_ani]._aUV[2].tu = (float)(1.0/(*pInt_ColNum_TextureSplit)*col);
            paRectUV[pattno_ani]._aUV[2].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));

            paRectUV[pattno_ani]._aUV[3].tu = (float)((1.0/(*pInt_ColNum_TextureSplit)*(col+1)));
            paRectUV[pattno_ani]._aUV[3].tv = (float)((1.0/(*pInt_RowNum_TextureSplit)*(row+1)));
        }
    }
    prm_pSpriteModel->_paRectUV = paRectUV;
    prm_pSpriteModel->_pattno_ani_Max=pattnum-1;
    prm_pSpriteModel->_dwNumMaterials = 1;
    D3DMATERIAL9* paD3DMaterial9;
    paD3DMaterial9 = NEW D3DMATERIAL9[prm_pSpriteModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pSpriteModel->_dwNumMaterials; i++){
        //paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        paD3DMaterial9[i].Diffuse.r = 1.0f;
        paD3DMaterial9[i].Diffuse.g = 1.0f;
        paD3DMaterial9[i].Diffuse.b = 1.0f;
        paD3DMaterial9[i].Diffuse.a = 1.0f;
        paD3DMaterial9[i].Ambient.r = 1.0f;
        paD3DMaterial9[i].Ambient.g = 1.0f;
        paD3DMaterial9[i].Ambient.b = 1.0f;
        paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pSpriteModel->_paD3DMaterial9_default = paD3DMaterial9;
    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
    RELEASE_SAFETY(pIDirectXFileData);
    RELEASE_IMPOSSIBLE_NULL(pIDirectXFileEnumObject);
}

void GgafDx9ModelManager::restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel) {
    TRACE3("GgafDx9ModelManager::restoreBoardModel(" << prm_pBoardModel->_model_name << ")");

    prm_pBoardModel->_pTextureCon = NULL;
    prm_pBoardModel->_paRectUV = NULL;

    HRESULT hr;
    string xfile_name = GGAFDX9_PROPERTY(DIR_SPRITE_MODEL) + string(prm_pBoardModel->_model_name) + ".sprx";

    //�X�v���C�g���Ǎ��݃e���v���[�g�̓o�^(������s���̂�)

    IDirectXFileEnumObject* pIDirectXFileEnumObject;
    IDirectXFileData* pIDirectXFileData;
    hr = _pIDirectXFile->CreateEnumObject((void*)xfile_name.c_str(), DXFILELOAD_FROMFILE, &pIDirectXFileEnumObject);
    mightDx9Exception(hr, DXFILE_OK, "[GgafDx9ModelManager::restoreBoardModel] "<<xfile_name<<"��CreateEnumObject�Ɏ��s���܂����B");

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
    //string texture_filename = GGAFDX9_PROPERTY(DIR_TEXTURE_MODEL) + string(*ppaChar_TextureFile);
    GgafDx9TextureConnection* pTextureCon = (GgafDx9TextureConnection*)_pTextureManager->getConnection(*ppaChar_TextureFile);
    //�e�N�X�`���̎Q�Ƃ�ێ�������B
    prm_pBoardModel->_pTextureCon = pTextureCon;

    GgafDx9BoardModel::VERTEX* paVertex = NEW GgafDx9BoardModel::VERTEX[4];
    prm_pBoardModel->_size_vertecs = sizeof(GgafDx9BoardModel::VERTEX)*4;
    prm_pBoardModel->_size_vertec_unit = sizeof(GgafDx9BoardModel::VERTEX);

    //1px�������uv�̑傫�������߂�
     D3DSURFACE_DESC d3dsurface_desc;
     pTextureCon->view()->GetLevelDesc(0, &d3dsurface_desc);
     float pxU = 1.0 / d3dsurface_desc.Width; //�e�N�X�`���̕�(px)�Ŋ���
     float pxV = 1.0 / d3dsurface_desc.Height; //�e�N�X�`���̍���(px)�Ŋ���

    //����
    paVertex[0].x = 0.0f;
    paVertex[0].y = 0.0f;
    paVertex[0].z = 0.0f;
    paVertex[0].tu = 0.0f;
    paVertex[0].tv = 0.0f;
    //�E��
    paVertex[1].x = *pFloat_Size_BoardModelWidth;
    paVertex[1].y = 0.0f;
    paVertex[1].z = 0.0f;
    paVertex[1].tu = 1.0/(float)(*pInt_ColNum_TextureSplit) + (pxU/10); //�͂��ɏ�����(1/10px)���
    paVertex[1].tv = 0.0f;
    //����
    paVertex[2].x = 0.0f;
    paVertex[2].y = *pFloat_Size_BoardModelHeight;
    paVertex[2].z = 0.0f;
    paVertex[2].tu = 0.0f;
    paVertex[2].tv = 1.0/(float)(*pInt_RowNum_TextureSplit) + (pxV/10); //�͂��ɏ�����(1/10px)���
    //�E��
    paVertex[3].x = *pFloat_Size_BoardModelWidth;
    paVertex[3].y = *pFloat_Size_BoardModelHeight;
    paVertex[3].z = 0.0f;
    paVertex[3].tu = 1.0/(float)(*pInt_ColNum_TextureSplit) + (pxU/10);
    paVertex[3].tv = 1.0/(float)(*pInt_RowNum_TextureSplit) + (pxV/10);

    //�o�b�t�@�쐬
    if (prm_pBoardModel->_pIDirect3DVertexBuffer9 == NULL) {

        hr = GgafDx9God::_pID3DDevice9->CreateVertexBuffer(
                prm_pBoardModel->_size_vertecs,
                D3DUSAGE_WRITEONLY,
                GgafDx9BoardModel::FVF,
                D3DPOOL_MANAGED, //D3DPOOL_DEFAULT
                &(prm_pBoardModel->_pIDirect3DVertexBuffer9),
                NULL);
        mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardModel] _pID3DDevice9->CreateVertexBuffer ���s model="<<(prm_pBoardModel->_model_name));
    }
    //���_�o�b�t�@�쐬
    //���_�����r�f�I�J�[�h���_�o�b�t�@�փ��[�h
    void *pVertexBuffer;
    hr = prm_pBoardModel->_pIDirect3DVertexBuffer9->Lock(0, prm_pBoardModel->_size_vertecs, (void**)&pVertexBuffer, 0);
    mightDx9Exception(hr, D3D_OK, "[GgafDx9ModelManager::restoreBoardModel] ���_�o�b�t�@�̃��b�N�擾�Ɏ��s model="<<prm_pBoardModel->_model_name);

    memcpy(pVertexBuffer, paVertex, prm_pBoardModel->_size_vertecs); //pVertexBuffer �� paVertex
    prm_pBoardModel->_pIDirect3DVertexBuffer9->Unlock();

    //�S�p�^�[����UV���̔z��쐬�����f���ɕێ�������
    //��2009/3/13��
    //�V�F�[�_�[��UV���삷��悤�ɂȂ��Ă���A�`�掞��UV����̏��(paRectUV[n]._aUV[0])�ȊO�͎g�p���Ȃ��Ȃ����B
    //TODO:���΂炭������]���ȏ����������������B
    int pattnum = (*pInt_ColNum_TextureSplit) * (*pInt_RowNum_TextureSplit);
    GgafDx9RectUV* paRectUV = NEW GgafDx9RectUV[pattnum];
    for (int row = 0; row < *pInt_RowNum_TextureSplit; row++) {
        for (int col = 0; col < *pInt_ColNum_TextureSplit; col++) {
            int pattno_ani = row*(*pInt_ColNum_TextureSplit)+col;
            paRectUV[pattno_ani]._aUV[0].tu = (float)(1.0*col/(*pInt_ColNum_TextureSplit));
            paRectUV[pattno_ani]._aUV[0].tv = (float)(1.0*row/(*pInt_RowNum_TextureSplit));

            paRectUV[pattno_ani]._aUV[1].tu = (float)(1.0*(col+1)/(*pInt_ColNum_TextureSplit));
            paRectUV[pattno_ani]._aUV[1].tv = (float)(1.0*row/(*pInt_RowNum_TextureSplit));

            paRectUV[pattno_ani]._aUV[2].tu = (float)(1.0*col/(*pInt_ColNum_TextureSplit));
            paRectUV[pattno_ani]._aUV[2].tv = (float)(1.0*(row+1)/(*pInt_RowNum_TextureSplit));

            paRectUV[pattno_ani]._aUV[3].tu = (float)(1.0*(col+1)/(*pInt_ColNum_TextureSplit));
            paRectUV[pattno_ani]._aUV[3].tv = (float)(1.0*(row+1)/(*pInt_RowNum_TextureSplit));
        }
    }
    prm_pBoardModel->_paRectUV = paRectUV;
    prm_pBoardModel->_pattno_max = pattnum-1;
    prm_pBoardModel->_dwNumMaterials = 1;
    D3DMATERIAL9* paD3DMaterial9;
    paD3DMaterial9 = NEW D3DMATERIAL9[prm_pBoardModel->_dwNumMaterials];
    for( DWORD i = 0; i < prm_pBoardModel->_dwNumMaterials; i++){
        //paD3DMaterial9[i] = paD3DMaterial9_tmp[i].MatD3D;
        paD3DMaterial9[i].Diffuse.r = 1.0f;
        paD3DMaterial9[i].Diffuse.g = 1.0f;
        paD3DMaterial9[i].Diffuse.b = 1.0f;
        paD3DMaterial9[i].Diffuse.a = 1.0f;
        paD3DMaterial9[i].Ambient.r = 1.0f;
        paD3DMaterial9[i].Ambient.g = 1.0f;
        paD3DMaterial9[i].Ambient.b = 1.0f;
        paD3DMaterial9[i].Ambient.a = 1.0f;
    }
    prm_pBoardModel->_paD3DMaterial9_default = paD3DMaterial9;

    //��n��
    DELETEARR_IMPOSSIBLE_NULL(paVertex);
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
    RELEASE_IMPOSSIBLE_NULL(_pIDirectXFile);
    _pTextureManager->dump();
    DELETE_IMPOSSIBLE_NULL(_pTextureManager);
    TRACE3("GgafDx9ModelManager::releaseAll() ���邯�ǂ��A�����ł͊��ɉ������������̂��Ȃ��͂��ł�");
    releaseAll();
}

void GgafDx9ModelManager::restoreAll() {
    TRACE3("GgafDx9ModelManager::restoreAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    TRACE3("restoreAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->restore();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::restoreAll() end<--");
}

void GgafDx9ModelManager::onDeviceLostAll() {
    TRACE3("GgafDx9ModelManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    TRACE3("onDeviceLostAll pCurrent="<<pCurrent);
    while (pCurrent != NULL) {
        pCurrent->view()->onDeviceLost();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::onDeviceLostAll() end<--");
}

void GgafDx9ModelManager::releaseAll() {
    TRACE3("GgafDx9ModelManager::releaseAll() start-->");
    GgafResourceConnection<GgafDx9Model>* pCurrent = _pFirstConnection;
    while (pCurrent != NULL) {
        pCurrent->view()->release();
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDx9ModelManager::releaseAll() end<--");
}

float GgafDx9ModelManager::getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2) {
    static Frm::Vector V0;
    static Frm::Vector V1;
    static Frm::Vector V2;
    V0.x = v0.data[0]; V0.y = v0.data[1]; V0.z = v0.data[2];
    V1.x = v1.data[0]; V1.y = v1.data[1]; V1.z = v1.data[2];
    V2.x = v2.data[0]; V2.y = v2.data[1]; V2.z = v2.data[2];
    static Frm::Vector V;
    V = V2 - V1;
    static Frm::Vector W;
    W = V0 - V1;
    //�x�N�g�� V W �̐����p�����߂�
    //    V=(vx,vy,vz)=(bx-ax,by-ay,bz-az)
    //    W=(wx,wy,wz)=(cx-ax,cy-ay,cz-az)
    //    �Ƃ����V�AW�x�N�g�����Ȃ��p��
    //    cos��=(V�AW�x�N�g���̓��ρj���iV�̑傫���j���iW�̑傫���j
    //        =(vx*wx+vy*wy+vz*wz)
    //         �����[�g(vx^2+vy^2+vz^2)�����[�g(wx^2+wy^2+wz^2)
    static float DOT, LV, LW, cosV1;
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


