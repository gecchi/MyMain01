#ifndef GGAF_DX_MODELMANAGER_H_
#define GGAF_DX_MODELMANAGER_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/ResourceManager.hpp"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/util/XFile/framework/Frm_Mesh.h"
#include "jp/ggaf/dx/util/XFile/ToolBox/IOModel_X.h"

#define connectToModelTextureManager(X) ((GgafDx::TextureConnection*)pGOD->_pModelManager->_pModelTextureManager->connect((X), this))

#define TYPE_D3DXMESH_MODEL               'D'
#define TYPE_DYNAD3DXMESH_MODEL           'd'
#define TYPE_D3DXANIMESH_MODEL            'A'
#define TYPE_MESH_MODEL                   'X'
#define TYPE_MESHSET_MODEL                'x'
#define TYPE_MASSMESH_MODEL               't'
#define TYPE_CUBEMAPMESH_MODEL            'G'
#define TYPE_CUBEMAPMESHSET_MODEL         'g'
#define TYPE_MORPHMESH_MODEL              'M'
#define TYPE_MASSMORPHMESH_MODEL          'm'
#define TYPE_CUBEMAPMORPHMESH_MODEL       'H'
#define TYPE_WORLDBOUND_MODEL             'W'
#define TYPE_SPRITE_MODEL                 'S'
#define TYPE_SPRITESET_MODEL              's'
#define TYPE_MASSSPRITE_MODEL             'z'
#define TYPE_BOARD_MODEL                  'B'
#define TYPE_BOARDSET_MODEL               'b'
#define TYPE_MASSBOARD_MODEL              'w'
#define TYPE_CUBE_MODEL                   'C'
#define TYPE_POINTSPRITE_MODEL            'P'
#define TYPE_MASSPOINTSPRITE_MODEL        'p'
#define TYPE_POINTSPRITESET_MODEL         'o'
#define TYPE_FRAMEDBOARD_MODEL            'E'
#define TYPE_REGULARPOLYGONSPRITE_MODEL   'R'
#define TYPE_REGULARPOLYGONBOARD_MODEL    'r'
#define TYPE_BONEANIMESH_MODEL            '1'
#define TYPE_SKINANIMESH_MODEL            '2'

namespace GgafDx {

/**
 * ���f���C���X�^���X�Ǘ�.
 * ��ɁA���f�������X�g�ɂ��ێ����A���f�����v�����ꂽ����<BR>
 * �������邩�A���邢�͐����ς�Ԃ����𔻒f���܂��B<BR>
 * TODO:���j�Ƃ�������N���X�Ŕ�剻�͂������Ȃ����A���������Ȃ��B
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class ModelManager : public GgafCore::ResourceManager<Model> {

private:
    template <typename T> T* createModel(const char* prm_model_name);
    D3DXMeshModel*     createD3DXMeshModel(const char* prm_model_name, DWORD prm_dwOptions);
public:

    struct SpriteXFileFmt {
        FLOAT width;
        FLOAT height;
        char texture_file[256];
        DWORD row_texture_split;
        DWORD col_texture_split;
    };

    class PointSpriteXFileFmt {
    public:
        FLOAT SquareSize;
        char TextureFile[256];
        DWORD TextureSplitRowCol;
        DWORD VerticesNum;
        D3DVECTOR* paD3DVECTOR_Vertices;
        D3DCOLORVALUE* paD3DVECTOR_VertexColors;
        DWORD* paInt_InitUvPtnNo;
        FLOAT* paFLOAT_InitScale;
        PointSpriteXFileFmt() {
            SquareSize = 1;
            TextureSplitRowCol = 1;
            VerticesNum = 1;
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

    TextureManager* _pModelTextureManager;
    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� ID3DXFile �̃|�C���^ */
    ID3DXFile* _pID3DXFile_sprx;
    ID3DXFile* _pID3DXFile_psprx;
    static std::string getMeshFileName(std::string prm_model_name);
    static std::string getSpriteFileName(std::string prm_model_name, std::string prm_ext);
    void obtainSpriteInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprite_x_filename);
    void obtainPointSpriteInfo(PointSpriteXFileFmt* pPointSpriteFmt_out, std::string prm_point_sprite_x_filename);
public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    ModelManager(const char* prm_manager_name);

    /**
     * ���f������ID�ɂ��A���f���I�u�W�F�N�g�𐶐����� .
     * <pre>
     * �����f������ID�̌`��������
     * �w���f���^�C�v  + "," + ���f����`���x�ƂȂ��Ă���B
     *  "D,MyShip"   --> D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "d,MyShip"   --> D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"�iD3DXMESH_DYNAMIC �I�v�V���������قȂ�j
     *  "A,Hone"     --> D3DXAniMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Hone.x"
     *  "X,Enemy"    --> MeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"
     *  "x,12,Enemy"- -> MeshSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"�B�����`��I�u�W�F�N�g���� 12 �Z�b�g
     *  "x,Enemy"    --> MeshSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Enemy.x"�B�Z�b�g���ȗ����͍ő�� 15 �Z�b�g
     *  "t,12,Enemy"- -> MassMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"�B�����`��I�u�W�F�N�g���� 12 �Z�b�g
     *  "t,Enemy"    --> MassMeshModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Enemy.x"�B�Z�b�g���ȗ����͍ő�� 15 �Z�b�g
     *  "M,MyShip_3" --> MorphMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"�B���l�����ȗ��s�B
     *                   �v���C�}�����f����"MyShip_0.x"�A���[�t�^�[�Q�b�g1�`3��"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S,Bomb"     --> SpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B
     *  "s,5,Bomb"   --> SpriteSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�����`��I�u�W�F�N�g���� 5 �Z�b�g
     *  "s,Bomb"     --> SpriteSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�Z�b�g���ȗ����͍ő�� 18 �Z�b�g
     *  "B,Font"     --> BoardModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B
     *  "b,10,Font"  --> BoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�����`��I�u�W�F�N�g���� 10 �Z�b�g
     *  "b,Font"     --> BoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�Z�b�g���ȗ����͍ő�� 28 �Z�b�g
     *  "P,Star"     --> PointSpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Star.psprx"�B�����`��Z�b�g����8
     *  "C"          --> D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "cube.x"
     *  </pre>
     * @param prm_idstr ���f������ID
     * @param prm_p ���R�p�����[�^�A���ݖ��g�p
     * @return ���f���I�u�W�F�N�g
     */
    Model* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::ResourceConnection<Model>* processCreateConnection(const char* prm_idstr, Model* prm_pResource) override;

    /**
     * ���f���I�u�W�F�N�g���X�g�̊e�C���X�^���X�̓��e���č\�z�B .
     * �f�o�C�X���X�g��̕��A���ɌĂяo�����<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** �O��`��Model */
    static Model* _pModelLastDraw;

    /**
     * ���f���}�l�[�W���[���Ǘ����郂�f�����X�g�̐擪���擾
     * @return �擪�̃��f��
     */
    ModelConnection* getFirstConnection() const {
        return (ModelConnection*)_pConn_first;
    }

    virtual ~ModelManager();
};

}
#endif /*GGAF_DX_MODELMANAGER_H_*/
