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
	static IDirectXFile* _s_pIDirectXFile;

	/**
	 * GgafDx9MeshModel �I�u�W�F�N�g�𐶐��B .
	 * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƃ��b�V����`��X�t�@�C�����ɂȂ�B
	 * @param prm_dwOptions �I�v�V�����iD3DXLoadMeshFromX�̈����ɂȂ�j
	 */
	GgafDx9MeshModel* createMeshModel(std::string prm_model_name, DWORD prm_dwOptions);

	/**
	 * GgafDx9SpriteModel �I�u�W�F�N�g�𐶐��B .
	 * X�t�@�C���̃t�H�[�}�b�g�́A�J�X�^���e���v���[�gX�t�@�C���� ggaf_spritemodel_define.x �̓��e�����g�p�����<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƃX�v���C�g��`��X�t�@�C�����ɂȂ�B
	 */
	GgafDx9SpriteModel* createSpriteModel(std::string prm_model_name);

	/**
	 * GgafDx9SquareModel �I�u�W�F�N�g�𐶐��B .
	 * 1*1*1 �����̂̃��f��<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B
	 */
	GgafDx9SquareModel* createSquareModel(std::string prm_model_name);

	/**
	 * GgafDx9PlateModel �I�u�W�F�N�g�𐶐��B .
	 * X�t�@�C���̃t�H�[�}�b�g�́A�J�X�^���e���v���[�gX�t�@�C���� ggaf_spritemodel_define.x �̓��e�����g�p�����<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`��X�t�@�C�����ɂȂ�B
	 */
	GgafDx9PlateModel* createPlateModel(std::string prm_model_name);

public:

	static GgafDx9TextureManager* _pTextureManager;

	/**
	 * GgafDx9Model�I�u�W�F�N�g�����X�g�̊e�C���X�^���X�̓��e���č\�z�B .
	 * �f�o�C�X���X�g��̕��A���ɌĂяo�����<BR>
	 */
	void restoreAll();

	void onDeviceLostAll();


	GgafDx9ModelLead* lead(std::string prm_model_name, DWORD prm_dwOptions

	/**
	 * GgafDx9MeshModel�I�u�W�F�N�g���擾�B .
	 * GgafDx9Model �I�u�W�F�N�g���X�g�i�擪��_s_pModel_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9MeshModel������j�ꍇ�A GgafDx9MeshModel �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * ������ std::string �̔�r��������܂ōs�����߁A�d���ł��B<BR>
	 * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
	 * �������֐����łP��g�p���A�|�C���^��ێ�����Ƃ����g�p���@��z��B<BR>
	 * @param prm_model_name �X�v���C�g��`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 * @param prm_dwOptions �I�v�V�����iD3DXLoadMeshFromX�̈����ɂȂ�j
	 */
	GgafDx9MeshModel* obtainMeshModel(std::string prm_model_name, DWORD prm_dwOptions);

	/**
	 * GgafDx9SpriteModel�I�u�W�F�N�g���擾�B .
	 * �����ς� GgafDx9Model �I�u�W�F�N�g���X�g�i�擪��_s_pModel_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9SpriteModel������j�ꍇ�A GgafDx9SpriteModel �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * ������ std::string �̔�r��������܂ōs�����߁A�d���ł��B<BR>
	 * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
	 * �������֐����łP��g�p���A�|�C���^��ێ�����Ƃ����g�p���@��z��B<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B�i".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�j
	 */
	GgafDx9SpriteModel* obtainSpriteModel(std::string prm_model_name);

	/**
	 * GgafDx9SquareModel�I�u�W�F�N�g���擾�B .
	 * �����ς� GgafDx9Model �I�u�W�F�N�g���X�g�i�擪��_s_pModel_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9SquareModel������j�ꍇ�A GgafDx9SquareModel �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * ������ std::string �̔�r��������܂ōs�����߁A�d���ł��B<BR>
	 * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
	 * �������֐����łP��g�p���A�|�C���^��ێ�����Ƃ����g�p���@��z��B<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B�i".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�j
	 */
	GgafDx9SquareModel* obtainSquareModel(std::string prm_model_name);

	/**
	 * GgafDx9PlateModel�I�u�W�F�N�g���擾�B<BR>
	 * �����ς� GgafDx9Model �I�u�W�F�N�g���X�g�i�擪��_s_pModel_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9PlateModel������j�ꍇ�A GgafDx9PlateModel �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * ������ std::string �̔�r��������܂ōs�����߁A�d���ł��B<BR>
	 * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
	 * �������֐����łP��g�p���A�|�C���^��ێ�����Ƃ����g�p���@��z��B<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B�i".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�j
	 */
	static GgafDx9PlateModel* obtainPlateModel(std::string prm_model_name);

	/**
	 * GgafDx9Model�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
	 */
	static void release();

	/**
	 * GgafDx9MeshModel �I�u�W�F�N�g���č\�z����B .
	 * @param prm_pMeshModel �č\�z����GgafDx9MeshModel
	 */
	static void restoreMeshModel(GgafDx9MeshModel* prm_pMeshModel);

	/**
	 * GgafDx9SpriteModel �I�u�W�F�N�g���č\�z����B .
	 * @param prm_pSpriteModel �č\�z����GgafDx9SpriteModel
	 */
	static void restoreSpriteModel(GgafDx9SpriteModel* prm_pSpriteModel);

	/**
	 * GgafDx9SquareModel �I�u�W�F�N�g���č\�z����B .
	 * @param prm_pSquareModel �č\�z����GgafDx9SquareModel
	 */
	static void restoreSquareModel(GgafDx9SquareModel* prm_pSquareModel);


	/**
	 * GgafDx9PlateModel �I�u�W�F�N�g���č\�z����B .
	 * @param prm_pPlateModel �č\�z����GgafDx9PlateModel
	 */
	static void restorePlateModel(GgafDx9PlateModel* prm_pPlateModel);

};


}
#endif /*GGAFDX9MODELMANAGER_H_*/
