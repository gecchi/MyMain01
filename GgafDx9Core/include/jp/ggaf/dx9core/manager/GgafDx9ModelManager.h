#ifndef GGAFDX9MODELMANAGER_H_
#define GGAFDX9MODELMANAGER_H_
namespace GgafDx9Core {

/**
 * ���f���C���X�^���X�Ǘ�.
 * ��ɁA���f�������X�g�ɂ��ێ����A���f����v�����ꂽ����<BR>
 * �������邩�A���邢�͐����ς�Ԃ����𔻒f���܂��B<BR>
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

    /**
     * GgafDx9BoardModel �I�u�W�F�N�g�𐶐��B .
     * X�t�@�C���̃t�H�[�}�b�g�́A�J�X�^���e���v���[�gX�t�@�C���� ggaf_spritemodel_define.x �̓��e�����g�p�����<BR>
     * @param prm_model_name ���f����`�̎��ʖ��B".sprx"��ǉ�����ƃX�v���C�g��`��X�t�@�C�����ɂȂ�B
     */
    GgafDx9BoardModel* createBoardModel(char* prm_model_name);

    GgafDx9MeshModel* createMeshModel(char* prm_model_name);
    GgafDx9MorphTwoMeshModel* createMorphTwoMeshModel(char* prm_model_name);
    GgafDx9MorphMeshModel* createMorphMeshModel(char* prm_model_name);

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������(���e�����K�{)
     */
    GgafDx9ModelManager(const char* prm_manager_name);

    /**
     * �I�[�o�[���C�h
     */
    GgafDx9Model* processCreateResource(char* prm_idstr);

    /**
     * GgafDx9D3DXMeshModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pD3DXMeshModel �č\�z����GgafDx9D3DXMeshModel
     */
    void restoreD3DXMeshModel(GgafDx9D3DXMeshModel* prm_pD3DXMeshModel);

    /**
     * GgafDx9SpriteModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pSpriteModel �č\�z����GgafDx9SpriteModel
     */
    void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);


    /**
     * GgafDx9PlateModel �I�u�W�F�N�g���č\�z����B .
     * @param prm_pPlateModel �č\�z����GgafDx9PlateModel
     */

    void restoreBoardModel(GgafDx9BoardModel* prm_pBoardModel);

    void restoreMeshModel(GgafDx9MeshModel* prm_pD3DXMeshModel);

    void restoreMorphTwoMeshModel(GgafDx9MorphTwoMeshModel* prm_pModel);
    void restoreMorphMeshModel(GgafDx9MorphMeshModel* prm_pModel);
    /**
     * �I�[�o�[���C�h
     */
    GgafCore::GgafResourceConnection<GgafDx9Model>* processCreateConnection(char* prm_idstr, GgafDx9Model* prm_pResource);

    /**
     * GgafDx9Model�I�u�W�F�N�g�����X�g�̊e�C���X�^���X�̓��e���č\�z�B .
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
    /** �O��`��Model��Id */
    static int _id_lastdraw;


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
