#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Se �Ǘ��N���X .
 * �����ς� GgafDx9Se �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9SeManager : public GgafCore::GgafResourceManager<GgafDx9Se> {

public:

	/**
	 * �R���X�g���N�^
	 * @param prm_manager_name �}�l�[�W������(���e�����K�{)
	 */
	GgafDx9SeManager(const char* prm_manager_name);

	/**
	 * �I�[�o�[���C�h
	 */
	GgafDx9Se* processCreateResource(char* prm_idstr);

	/**
	 * �I�[�o�[���C�h
	 */
	GgafCore::GgafResourceConnection<GgafDx9Se>* processCreateConnection(char* prm_idstr, GgafDx9Se* prm_pResource);


	virtual ~GgafDx9SeManager() {};
};


}
#endif /*GGAFDX9SEMANAGER_H_*/
