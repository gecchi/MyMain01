#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_


namespace GgafDx9Core {

/**
 * ���f���C���X�^���X�Ǘ�.
 * ��ɁA���f�������X�g�ɂ��ێ����A���f�����v�����ꂽ����<BR>
 * �������邩�A���邢�͐����ς�Ԃ����𔻒f���܂��B<BR>
 * TODO:���j�Ƃ�������N���X�Ŕ�剻�͂������Ȃ����A���������Ȃ��B
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDx9ModelManager : public GgafCore::GgafResourceManager<GgafDx9Model> {

private:
    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� IDirectXFile �̃|�C���^ */
    IDirectXFile* _pIDirectXFile_sprx;
    IDirectXFile* _pIDirectXFile_psprx;
    GgafDx9TextureManager* _pTextureManager;

    GgafDx9D3DXMeshModel*    createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);
    GgafDx9D3DXAniMeshModel* createD3DXAniMeshModel(char* prm_model_name);
    GgafDx9D3DXMeshModel*    createDynaMeshModel(char* prm_model_name);
    GgafDx9SpriteModel*      createSpriteModel(char* prm_model_name);
    GgafDx9SpriteSetModel*   createSpriteSetModel(char* prm_model_name);
    GgafDx9BoardModel*       createBoardModel(char* prm_model_name);
    GgafDx9BoardSetModel*    createBoardSetModel(char* prm_model_name);
    GgafDx9MeshModel*        createMeshModel(char* prm_model_name);
    GgafDx9MeshSetModel*     createMeshSetModel(char* prm_model_name);
    GgafDx9CubeMapMeshModel* createCubeMapMeshModel(char* prm_model_name);
    GgafDx9MorphMeshModel*   createMorphMeshModel(char* prm_model_name);
    GgafDx9PointSpriteModel* createPointSpriteModel(char* prm_model_name);

    /**
     * ��Ԃ�3�_v0 v1 v2 ���A���� v0v1 �� v1v2 �̐����p(�pv1)�����߂�
     * @param v0
     * @param v1
     * @param v2
     * @return �����p(���f�B�A��)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);
public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9ModelManager(const char* prm_manager_name);

    /**
     * ���f������ID�ɂ��A���f���I�u�W�F�N�g�𐶐����� .
     * <pre>
     * �����f������ID�̌`��������
     * �w���f���^�C�v  + "/" + ���f����`���x�ƂȂ��Ă���B
     *  "D/MyShip"   --> GgafDx9D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "d/MyShip"   --> GgafDx9D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip.x"�iD3DXMESH_DYNAMIC �I�v�V���������قȂ�j
     *  "A/Hone"     --> GgafDx9D3DXAniMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Hone.x"
     *  "X/Enemy"    --> GgafDx9MeshModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"
     *  "x/12/Enemy"- -> GgafDx9MeshSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Enemy.x"�B�����`��I�u�W�F�N�g���� 12 �Z�b�g
     *  "x/Enemy"    --> GgafDx9MeshSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Enemy.x"�B�Z�b�g���ȗ����͍ő�� 15 �Z�b�g
     *  "M/3/MyShip" --> GgafDx9MorphMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"�B���l�����ȗ��s�B
     *                   �v���C�}�����f����"MyShip_0.x"�A���[�t�^�[�Q�b�g1�`3��"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> GgafDx9SpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B
     *  "s/5/Bomb"   --> GgafDx9SpriteSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�����`��I�u�W�F�N�g���� 5 �Z�b�g
     *  "s/Bomb"     --> GgafDx9SpriteSetModel �̃��f��(�Z�b�g���ȗ��\�L)�B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�Z�b�g���ȗ����͍ő�� 18 �Z�b�g
     *  "B/Font"     --> GgafDx9BoardModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B
     *  "b/10/Font"  --> GgafDx9BoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�����`��I�u�W�F�N�g���� 10 �Z�b�g
     *  "b/Font"     --> GgafDx9BoardSetModel �̃��f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�Z�b�g���ȗ����͍ő�� 28 �Z�b�g
     *  "P/Star"     --> GgafDx9PointSpriteModel �̃��f���B�ǂݍ��ރt�@�C���� "Star.psprx"�B�����`��Z�b�g����8
     *  "C"          --> GgafDx9D3DXMeshModel �̃��f���B�ǂݍ��ރt�@�C���� "cube.x"
     *  </pre>
     * @param prm_idstr ���f������ID
     * @return ���f���I�u�W�F�N�g
     */
    GgafDx9Model* processCreateResource(char* prm_idstr, void* prm_p) override;

    /**
     * GgafDx9D3DXMeshModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pD3DXMeshModel �č\�z����GgafDx9D3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel);

    void restoreD3DXAniMeshModel(GgafDx9D3DXAniMeshModel* prm_pD3DXAniMeshModel);

    /**
     * GgafDx9SpriteModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pSpriteModel �č\�z����GgafDx9SpriteModel
     */
    void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

    void restoreSpriteSetModel(GgafDx9SpriteSetModel* prm_pSpriteSetModel);


    /**
     * GgafDx9BoardModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pBoardModel �č\�z����GgafDx9BoardModel
     */
    void restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel);

    void restoreBoardSetModel(GgafDx9BoardSetModel* prm_pBoardSetModel);

    void restoreMeshModel(GgafDx9MeshModel* prm_pD3DXMeshModel);

    void restoreMeshSetModel(GgafDx9MeshSetModel* prm_pD3DXMeshSetModel);

    void restoreMorphMeshModel(GgafDx9MorphMeshModel* prm_pModel);

    void restorePointSpriteModel(GgafDx9PointSpriteModel* prm_pPointSpriteModel);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource) override;

    /**
     * ���f���I�u�W�F�N�g���X�g�̊e�C���X�^���X�̓��e���č\�z�B .
     * �f�o�C�X���X�g��̕��A���ɌĂяo�����<BR>
     */
    void restoreAll();

    void onDeviceLostAll();

    void releaseAll();


    /** ���݃��f��ID */
    static int _id_max;

    /** ���f��ID�擾 */
    static int getNextId() {
        _id_max++;
        return _id_max;
    }
    /** �O��`��Model */
    static GgafDx9Model* _pModelLastDraw;

    /**
     * ���f���}�l�[�W���[���Ǘ����郂�f�����X�g�̐擪���擾
     * @return �擪�̃��f��
     */
    GgafDx9ModelConnection* getFirstConnection() {
        return (GgafDx9ModelConnection*)_pFirstConnection;
    }

    virtual ~GgafDx9ModelManager();


    //
    //	/**
    //	 * GgafDx9Model�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
    //	 */
    //	static void release();
    //
};

}
#endif /*GGAFDX9MODELMANAGER_H_*/
