#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {

/**
 * ���f���C���X�^���X�Ǘ�.
 * ��ɁA���f�������X�g�ɂ��ێ����A���f����v�����ꂽ����<BR>
 * �������邩�A���邢�͐����ς�Ԃ����𔻒f���܂��B<BR>
 * TODO:���j�Ƃ�������N���X�Ŕ�剻�͂������Ȃ����A���������Ȃ��B
 * @version 1.00
 * @since 2009/02/01
 * @author Masatoshi Tsuge
 */
class GgafDx9ModelManager : public GgafCore::GgafResourceManager<GgafDx9Model> {

private:
    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� IDirectXFile �̃|�C���^ */
    IDirectXFile* _pIDirectXFile;
    GgafDx9TextureManager* _pTextureManager;

    /**
     * GgafDx9D3DXMeshModel �I�u�W�F�N�g�𐶐��B .
     * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƃ��b�V����`��X�t�@�C�����ɂȂ�B
     * @param prm_dwOptions �I�v�V�����iD3DXLoadMeshFromX�̈����ɂȂ�j
     */
    GgafDx9D3DXMeshModel* createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);

    GgafDx9D3DXAniMeshModel* createD3DXAniMeshModel(char* prm_model_name);

    /**
     * GgafDx9D3DXMeshModel �I�u�W�F�N�g�𐶐��B .
     * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƃ��b�V����`��X�t�@�C�����ɂȂ�B
     * @param prm_dwOptions �I�v�V�����iD3DXLoadMeshFromX�̈����ɂȂ�j
     */
    GgafDx9D3DXMeshModel* createDynaMeshModel(char* prm_model_name);

    /**
     * GgafDx9SpriteModel �I�u�W�F�N�g�𐶐��B .
     * X�t�@�C���̃t�H�[�}�b�g�́A�J�X�^���e���v���[�gX�t�@�C���� ggaf_spritemodel_define.x �̓��e�����g�p�����<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".sprx"��ǉ�����ƃX�v���C�g��`��X�t�@�C�����ɂȂ�B
     */
    GgafDx9SpriteModel* createSpriteModel(char* prm_model_name);

    GgafDx9SpriteSetModel* createSpriteSetModel(char* prm_model_name);


    /**
     * GgafDx9BoardModel �I�u�W�F�N�g�𐶐��B .
     * X�t�@�C���̃t�H�[�}�b�g�́A�J�X�^���e���v���[�gX�t�@�C���� ggaf_spritemodel_define.x �̓��e�����g�p�����<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".sprx"��ǉ�����ƃX�v���C�g��`��X�t�@�C�����ɂȂ�B
     */
    GgafDx9BoardModel* createBoardModel(char* prm_model_name);
    GgafDx9BoardSetModel* createBoardSetModel(char* prm_model_name);

    GgafDx9MeshModel* createMeshModel(char* prm_model_name);
    GgafDx9MeshSetModel* createMeshSetModel(char* prm_model_name);

    GgafDx9MorphMeshModel* createMorphMeshModel(char* prm_model_name);

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
     *  "D/MyShip"   --> D3DXMeshModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "d/MyShip"   --> D3DXMeshModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"�iD3DXMESH_DYNAMIC �I�v�V���������قȂ�j
     *  "A/MyShip"   --> D3DXAniMeshModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "X/MyShip"   --> MeshModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"
     *  "x/MyShip"   --> MeshSetModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"�B�����`��Z�b�g����8
     *  "x/12/MyShip"--> MeshSetModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip.x"�B�����`��Z�b�g����12
     *  "M/3/MyShip" --> MorphMeshModel �� ���f���B�ǂݍ��ރt�@�C���� "MyShip_0.x", "MyShip_1.x", "MyShip_2.x", "MyShip_3.x"�B���l�����ȗ��s�B
     *                   �v���C�}�����f����"MyShip_0.x"�A���[�t�^�[�Q�b�g1�`3��"MyShip_1.x", "MyShip_2.x", "MyShip_3.x"
     *  "S/Bomb"     --> SpriteModel �� ���f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B
     *  "s/Bomb"     --> SpriteSetModel�� ���f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�����`��Z�b�g����8
     *  "s/16/Bomb"  --> SpriteSetModel�� ���f���B�ǂݍ��ރt�@�C���� "Bomb.sprx"�B�����`��Z�b�g����16
     *  "B/Font"     --> BoardModel�� ���f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B
     *  "b/Font"     --> BoardSetModel�� ���f���B�ǂݍ��ރt�@�C���� "Font.sprx"�B�����`��Z�b�g����8
     *  "C"          --> D3DXMeshModel �� ���f���B�ǂݍ��ރt�@�C���� "cube.x"
     *  </pre>
     * @param prm_idstr ���f������ID
     * @return ���f���I�u�W�F�N�g
     */
    GgafDx9Model* processCreateResource(char* prm_idstr);

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
    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource);

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
     * ��Ԃ�3�_v0 v1 v2 ���A���� v0v1 �� v1v2 �̐����p(�pv1)�����߂�
     * @param v0
     * @param v1
     * @param v2
     * @return �����p(���f�B�A��)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);

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
