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
    GgafDxMassSpriteModel*       createMassSpriteModel(const char* prm_model_name);
    GgafDxBoardModel*            createBoardModel(const char* prm_model_name);
    GgafDxBoardSetModel*         createBoardSetModel(const char* prm_model_name);
    GgafDxMassBoardModel*        createMassBoardModel(const char* prm_model_name);
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

    struct SpriteXFileFmt {
        float width;
        float height;
        char texture_file[256];
        int row_texture_split;
        int col_texture_split;
    };

    class PointSpriteXFileFmt {
    public:
        float SquareSize;
        char TextureFile[256];
        int TextureSplitRowCol;
        int VerticesNum;
        D3DVECTOR* paD3DVECTOR_Vertices;
        D3DCOLORVALUE* paD3DVECTOR_VertexColors;
        int* paInt_InitUvPtnNo;
        float* paFLOAT_InitScale;
        PointSpriteXFileFmt() {
            paD3DVECTOR_Vertices = nullptr;
            paD3DVECTOR_VertexColors = nullptr;
            paInt_InitUvPtnNo = nullptr;
            paFLOAT_InitScale = nullptr;
        }
        ~PointSpriteXFileFmt() {
            GGAF_DELETE_NULLABLE(paD3DVECTOR_Vertices);
            GGAF_DELETE_NULLABLE(paD3DVECTOR_VertexColors);
            GGAF_DELETE_NULLABLE(paInt_InitUvPtnNo);
            GGAF_DELETE_NULLABLE(paFLOAT_InitScale);
        }
    };

    static GgafDxTextureManager* _pModelTextureManager;
    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� ID3DXFile �̃|�C���^ */
    static ID3DXFile* _pID3DXFile_sprx;
    static ID3DXFile* _pID3DXFile_psprx;
    static std::string getMeshFileName(std::string prm_model_name);
    static std::string getSpriteFileName(std::string prm_model_name);
    static std::string getPointSpriteFileName(std::string prm_model_name);

    static void obtainSpriteInfo(SpriteXFileFmt* pSpriteFmt_out, std::string prm_sprite_x_filename);
    static void obtainPointSpriteInfo(PointSpriteXFileFmt* pPointSpriteFmt_out, std::string prm_point_sprite_x_filename);
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
