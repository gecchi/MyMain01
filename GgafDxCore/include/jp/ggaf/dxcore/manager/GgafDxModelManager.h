#ifndef GGAFDXCORE_GGAFDXMODELMANAGER_H_
#define GGAFDXCORE_GGAFDXMODELMANAGER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/GgafResourceManager.hpp"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dxcore/util/XFile/ToolBox/IOModel_X.h"

#define connectToModelTextureManager(X) ((GgafDxCore::GgafDxTextureConnection*)P_GOD->_pModelManager->_pModelTextureManager->connect((X), this))

namespace GgafDxCore {

/**
 * ���f���C���X�^���X�Ǘ�.
 * ��ɁA���f�������X�g�ɂ��ێ����A���f�����v�����ꂽ����<BR>
 * �������邩�A���邢�͐����ς�Ԃ����𔻒f���܂��B<BR>
 * TODO:���j�Ƃ�������N���X�Ŕ�剻�͂������Ȃ����A���������Ȃ��B
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDxModelManager : public GgafCore::GgafResourceManager<GgafDxModel> {



private:
    GgafDxD3DXMeshModel*         createD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions);
    GgafDxD3DXAniMeshModel*      createD3DXAniMeshModel(const char* prm_model_name);
    GgafDxD3DXMeshModel*         createDynaMeshModel(const char* prm_model_name);
    GgafDxSpriteModel*           createSpriteModel(const char* prm_model_name);
    GgafDxSpriteSetModel*        createSpriteSetModel(const char* prm_model_name);
    GgafDxBoardModel*            createBoardModel(const char* prm_model_name);
    GgafDxBoardSetModel*         createBoardSetModel(const char* prm_model_name);
    GgafDxMeshModel*             createMeshModel(const char* prm_model_name);
    GgafDxMeshSetModel*          createMeshSetModel(const char* prm_model_name);
    GgafDxMassMeshModel*         createMassMeshModel(const char* prm_model_name);
    GgafDxCubeMapMeshModel*      createCubeMapMeshModel(const char* prm_model_name);
    GgafDxCubeMapMeshSetModel*   createCubeMapMeshSetModel(const char* prm_model_name);
    GgafDxMorphMeshModel*        createMorphMeshModel(const char* prm_model_name);
    GgafDxCubeMapMorphMeshModel* createCubeMapMorphMeshModel(const char* prm_model_name);
    GgafDxWorldBoundModel*       createWorldBoundModel(const char* prm_model_name);
    GgafDxPointSpriteModel*      createPointSpriteModel(const char* prm_model_name);

public:

    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� ID3DXFile �̃|�C���^ */
    ID3DXFile* _pID3DXFile_sprx;
    ID3DXFile* _pID3DXFile_psprx;
    struct XFILE_SPRITE_FMT {
        float width;
        float height;
        char texture_file[256];
        int row_texture_split;
        int col_texture_split;
    };


    void setMaterial(Frm::Mesh* in_pMeshesFront,
                     int* pOut_material_num,
                     D3DMATERIAL9**                pOut_paMaterial,
                     GgafDxTextureConnection***    pOut_papTextureConnection);
    void setDefaultMaterial(D3DMATERIAL9* out_pD3DMATERIAL9);

    /**
     * ��Ԃ�3�_v0 v1 v2 ���A���� v0v1 �� v1v2 �̐����p(�pv1)�����߂�
     * @param v0
     * @param v1
     * @param v2
     * @return �����p(���f�B�A��)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);

    /**
     * 3D���_�o�b�t�@��FrameTransformMatrix�ϊ��Ɩ@����ݒ�B
     * @param prm_paVtxBuffer
     * @param prm_size_of_vtx_unit
     * @param model_pModel3D
     * @param paNumVertices ���_�A���O�̒��_�T�u�Z�b�g���̔z��
     *        �i���f�����T�u�Z�b�g�P�ʂŌʊ�i�ʒu�A��]�A�g��j��ێ����Ă�ꍇ�j
     */
    void prepareVtx(void* prm_paVtxBuffer, UINT prm_size_of_vtx_unit,
                    Frm::Model3D* model_pModel3D,
                    uint16_t* paNumVertices,
                    GgafDxModel* prm_pModel = nullptr);

    /**
     * ID3DXFileData�̃f�[�^�|�C���^����A�iX�t�@�C���t�H�[�}�b�g�ʂ�Ɂj�X�v���C�g�������o���B
     * @param pSpriteFmt_out
     * @param pLockedData ID3DXFileData->lock() �̃f�[�^�|�C���^
     * @return
     */
    char* obtainSpriteFmtX(XFILE_SPRITE_FMT* pSpriteFmt_out, char* pLockedData);

    static std::string getMeshFileName(std::string prm_model_name);
    static std::string getSpriteFileName(std::string prm_model_name);
    static std::string getPointSpriteFileName(std::string prm_model_name);

    static void calcTangentAndBinormal(
            D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
            D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
            D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
            D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal);

    GgafDxTextureManager* _pModelTextureManager;

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDxModelManager(const char* prm_manager_name);

    /**
     * ���f������ID�ɂ��A���f���I�u�W�F�N�g�𐶐����� .
     * <pre>
     * �����f������ID�̌`��������
     * �w���f���^�C�v  + "/" + ���f����`���x�ƂȂ��Ă���B
     *  "D/MyShip"   --> GgafDxD3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "d/MyShip"   --> GgafDxD3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"�iD3DXMESH_DYNAMIC �I�v�V���������قȂ�j
     *  "A/Hone"     --> GgafDxD3DXAniMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Hone.x"
     *  "X/Enemy"    --> GgafDxMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"
     *  "x/12/Enemy"- -> GgafDxMeshSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"�B�����`��I�u�W�F�N�g���� 12 �Z�b�g
     *  "x/Enemy"    --> GgafDxMeshSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Enemy.x"�B�Z�b�g���ȗ����͍ő�� 15 �Z�b�g
     *  "t/12/Enemy"- -> GgafDxMassMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"�B�����`��I�u�W�F�N�g���� 12 �Z�b�g
     *  "t/Enemy"    --> GgafDxMassMeshModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Enemy.x"�B�Z�b�g���ȗ����͍ő�� 15 �Z�b�g
     *  "M/3/MyShip" --> GgafDxMorphMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"�B���l�����ȗ��s�B
     *                   �v���C�}�����f����"MyShip_0.x"�A���[�t�^�[�Q�b�g1�`3��"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> GgafDxSpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B
     *  "s/5/Bomb"   --> GgafDxSpriteSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�����`��I�u�W�F�N�g���� 5 �Z�b�g
     *  "s/Bomb"     --> GgafDxSpriteSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�Z�b�g���ȗ����͍ő�� 18 �Z�b�g
     *  "B/Font"     --> GgafDxBoardModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B
     *  "b/10/Font"  --> GgafDxBoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�����`��I�u�W�F�N�g���� 10 �Z�b�g
     *  "b/Font"     --> GgafDxBoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�Z�b�g���ȗ����͍ő�� 28 �Z�b�g
     *  "P/Star"     --> GgafDxPointSpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Star.psprx"�B�����`��Z�b�g����8
     *  "C"          --> GgafDxD3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "cube.x"
     *  </pre>
     * @param prm_idstr ���f������ID
     * @param prm_p ���R�p�����[�^�A���ݖ��g�p
     * @return ���f���I�u�W�F�N�g
     */
    GgafDxModel* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    /**
     * GgafDxD3DXMeshModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pD3DXMeshModel �č\�z����GgafDxD3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDxD3DXMeshModel* prm_pD3DXMeshModel);

    void restoreD3DXAniMeshModel(GgafDxD3DXAniMeshModel* prm_pD3DXAniMeshModel);
    void getDrawFrameList(std::list<D3DXFRAME_WORLD*>* pList, D3DXFRAME_WORLD* frame);
    /**
     * GgafDxSpriteModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pSpriteModel �č\�z����GgafDxSpriteModel
     */
//    void restoreSpriteModel(GgafDxSpriteModel* prm_pSpriteModel);

//    void restoreSpriteSetModel(GgafDxSpriteSetModel* prm_pSpriteSetModel);


    /**
     * GgafDxBoardModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pBoardModel �č\�z����GgafDxBoardModel
     */
//    void restoreBoardModel(GgafDxBoardModel* prm_pBoardModel);

//    void restoreBoardSetModel(GgafDxBoardSetModel* prm_pBoardSetModel);

//    void restoreMeshModel(GgafDxMeshModel* prm_pD3DXMeshModel);

    void restoreMeshSetModel(GgafDxMeshSetModel* prm_pD3DXMeshSetModel);

//    void restoreMassMeshModel(GgafDxMassMeshModel* prm_pD3DXMassMeshModel);

    void restoreMorphMeshModel(GgafDxMorphMeshModel* prm_pModel);

//    void restorePointSpriteModel(GgafDxPointSpriteModel* prm_pPointSpriteModel);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDxModel>* processCreateConnection(const char* prm_idstr, GgafDxModel* prm_pResource) override;

    /**
     * ���f���I�u�W�F�N�g���X�g�̊e�C���X�^���X�̓��e���č\�z�B .
     * �f�o�C�X���X�g��̕��A���ɌĂяo�����<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** �O��`��Model */
    static GgafDxModel* _pModelLastDraw;

    /**
     * ���f���}�l�[�W���[���Ǘ����郂�f�����X�g�̐擪���擾
     * @return �擪�̃��f��
     */
    GgafDxModelConnection* getFirstConnection() const {
        return (GgafDxModelConnection*)_pConn_first;
    }

    virtual ~GgafDxModelManager();
};

}
#endif /*GGAFDXCORE_GGAFDXMODELMANAGER_H_*/
