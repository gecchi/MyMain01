#ifndef GGAFDXMODELMANAGER_H_
#define GGAFDXMODELMANAGER_H_


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
    /** �J�X�^���e���v���[�gX�t�@�C���ǂݍ��ݗp�� IDirectXFile �̃|�C���^ */
    IDirectXFile* _pIDirectXFile_sprx;
    IDirectXFile* _pIDirectXFile_psprx;


    GgafDxD3DXMeshModel*         createD3DXMeshModel(char* prm_model_name, DWORD prm_dwOptions);
    GgafDxD3DXAniMeshModel*      createD3DXAniMeshModel(char* prm_model_name);
    GgafDxD3DXMeshModel*         createDynaMeshModel(char* prm_model_name);
    GgafDxSpriteModel*           createSpriteModel(char* prm_model_name);
    GgafDxSpriteSetModel*        createSpriteSetModel(char* prm_model_name);
    GgafDxBoardModel*            createBoardModel(char* prm_model_name);
    GgafDxBoardSetModel*         createBoardSetModel(char* prm_model_name);
    GgafDxMeshModel*             createMeshModel(char* prm_model_name);
    GgafDxMeshSetModel*          createMeshSetModel(char* prm_model_name);
    GgafDxCubeMapMeshModel*      createCubeMapMeshModel(char* prm_model_name);
    GgafDxCubeMapMeshSetModel*   createCubeMapMeshSetModel(char* prm_model_name);
    GgafDxMorphMeshModel*        createMorphMeshModel(char* prm_model_name);
    GgafDxCubeMapMorphMeshModel* createCubeMapMorphMeshModel(char* prm_model_name);
    GgafDxWorldBoundModel*       createWorldBoundModel(char* prm_model_name);
    GgafDxPointSpriteModel*      createPointSpriteModel(char* prm_model_name);

    /**
     * ��Ԃ�3�_v0 v1 v2 ���A���� v0v1 �� v1v2 �̐����p(�pv1)�����߂�
     * @param v0
     * @param v1
     * @param v2
     * @return �����p(���f�B�A��)
     */
    float getRadv1_v0v1v2(Frm::Vertex& v0, Frm::Vertex& v1, Frm::Vertex& v2);
public:
    GgafDxTextureManager* _pModelTextureManager;

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
    GgafDxModel* processCreateResource(char* prm_idstr, void* prm_p) override;

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
    void restoreSpriteModel(GgafDxSpriteModel* prm_pSpriteModel);

    void restoreSpriteSetModel(GgafDxSpriteSetModel* prm_pSpriteSetModel);


    /**
     * GgafDxBoardModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pBoardModel �č\�z����GgafDxBoardModel
     */
    void restoreBoardModel(GgafDxBoardModel* prm_pBoardModel);

    void restoreBoardSetModel(GgafDxBoardSetModel* prm_pBoardSetModel);

    void restoreMeshModel(GgafDxMeshModel* prm_pD3DXMeshModel);

    void restoreMeshSetModel(GgafDxMeshSetModel* prm_pD3DXMeshSetModel);

    void restoreMorphMeshModel(GgafDxMorphMeshModel* prm_pModel);

    void restorePointSpriteModel(GgafDxPointSpriteModel* prm_pPointSpriteModel);

    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDxModel>* processCreateConnection(char* prm_idstr, GgafDxModel* prm_pResource) override;

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
    static GgafDxModel* _pModelLastDraw;

    /**
     * ���f���}�l�[�W���[���Ǘ����郂�f�����X�g�̐擪���擾
     * @return �擪�̃��f��
     */
    GgafDxModelConnection* getFirstConnection() {
        return (GgafDxModelConnection*)_pFirstConnection;
    }

    virtual ~GgafDxModelManager();


    //
    //	/**
    //	 * GgafDxModel�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
    //	 */
    //	static void release();
    //
};

}
#endif /*GGAFDXMODELMANAGER_H_*/
