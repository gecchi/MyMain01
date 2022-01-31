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
#define TYPE_FRAMEDSPRITE_MODEL           'F'
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
    D3DXMeshModel*     createD3DXMeshModel(const char* prm_model_id, DWORD prm_dwOptions);

protected:
    template <typename T> T* createModel(const char* prm_model_id);

public:
    struct MeshXFileFmt {
        DWORD XFileNum;
        std::string* XFileNames;
        DWORD DrawSetNum; //0�̏ꍇ�͍ő�
        D3DXMATRIX BaseTransformMatrix;
        MeshXFileFmt() {
            XFileNum = 0;
            XFileNames = nullptr;
            DrawSetNum = 1;
            D3DXMatrixIdentity(&BaseTransformMatrix);
        }
        ~MeshXFileFmt() {
            GGAF_DELETEARR_NULLABLE(XFileNames);
        }
    };

    struct SpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;
        DWORD DrawSetNum;
        D3DXMATRIX BaseTransformMatrix;
    };

    struct FramedSpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;

        FLOAT FrameWidth;
        FLOAT FrameHeight;
        char FrameTextureFile[256];
        DWORD FrameTextureSplitRows;
        DWORD FrameTextureSplitCols;
    };

    struct RegPolySpriteXFileFmt {
        FLOAT Width;
        FLOAT Height;
        char TextureFile[256];
        DWORD TextureSplitRows;
        DWORD TextureSplitCols;

        DWORD  FanNum;
        DWORD  IsCW; //1:���v��� / 0:�����v���
        D3DXMATRIX BaseTransformMatrix;

        RegPolySpriteXFileFmt() {
            D3DXMatrixIdentity(&BaseTransformMatrix);
        }
        ~RegPolySpriteXFileFmt() {
        }
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
        DWORD DrawSetNum;
        D3DXMATRIX BaseTransformMatrix;
        PointSpriteXFileFmt() {
            SquareSize = 1;
            TextureSplitRowCol = 1;
            VerticesNum = 1;
            paD3DVECTOR_Vertices = nullptr;
            paD3DVECTOR_VertexColors = nullptr;
            paInt_InitUvPtnNo = nullptr;
            paFLOAT_InitScale = nullptr;
            DrawSetNum = 1;
            D3DXMatrixIdentity(&BaseTransformMatrix);
        }
        ~PointSpriteXFileFmt() {
            GGAF_DELETE_NULLABLE(paD3DVECTOR_Vertices);
            GGAF_DELETE_NULLABLE(paD3DVECTOR_VertexColors);
            GGAF_DELETE_NULLABLE(paInt_InitUvPtnNo);
            GGAF_DELETE_NULLABLE(paFLOAT_InitScale);
        }
    };

    TextureManager* _pModelTextureManager;
    /** X�t�@�C���ǂݍ��ݗp�� ID3DXFile �̃|�C���^�imeshx ���f����`�ǂݍ��񂾂��Ɓj */
    ID3DXFile* _pID3DXFile_meshx;
    ID3DXFile* _pID3DXFile_sprx;
    ID3DXFile* _pID3DXFile_fsprx;
    ID3DXFile* _pID3DXFile_rsprx;
    ID3DXFile* _pID3DXFile_psprx;

    void obtainMeshModelInfo(MeshXFileFmt* prm_pMeshXFileFmt_out, std::string prm_meshx_filepath);
    void obtainSpriteModelInfo(SpriteXFileFmt* prm_pSpriteFmt_out, std::string prm_sprx_filepath);
    void obtainFramedSpriteModelInfo(FramedSpriteXFileFmt* prm_pFramedSpriteFmt_out, std::string prm_fsprx_filepath);
    void obtainRegPolySpriteModelInfo(RegPolySpriteXFileFmt* prm_pRegPolySpriteFmt_out, std::string prm_rsprx_filepath);
    void obtainPointSpriteModelInfo(PointSpriteXFileFmt* prm_pPointSpriteFmt_out, std::string prm_psprx_filepath);
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
     * �w���f���^�C�v(TYPE_XXX_MODEL)  + "," + ���f����`���x�ƂȂ��Ă���B
     *  "D,MyShip"   --> D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.meshx"
     *  "d,MyShip"   --> D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.meshx"�iD3DXMESH_DYNAMIC �I�v�V���������قȂ�j
     *  "A,Hone"     --> D3DXAniMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Hone.meshx"
     *  "X,Enemy"    --> MeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.meshx"
     *  "x,Enemy"    --> MeshSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.meshx"�B�i�Z�b�g���ȗ����͍ő�� 15 �Z�b�g�j
     *  "t,Enemy"    --> MassMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.meshx"�B�i�Z�b�g���ȗ����͍ő�� 512 �Z�b�g�j
     *  "M,MyShip"   --> MorphMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.meshx"
     *  "S,Bomb"     --> SpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B
     *  "s,Bomb"     --> SpriteSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�i�Z�b�g���ȗ����͍ő�� 18 �Z�b�g�j
     *  "B,Font"     --> BoardModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B
     *  "b,Font"     --> BoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�i�Z�b�g���ȗ����͍ő�� 28 �Z�b�g�j
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
