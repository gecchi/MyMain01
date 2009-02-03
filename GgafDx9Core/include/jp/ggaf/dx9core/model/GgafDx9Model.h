#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9Model : public GgafCore::GgafObject {
    friend class GgafDx9ModelManager;


protected:
public:
	/** ID */
	int _id;

	/** ���f����`�̎��ʖ��B(50�����܂�) */
	char* _model_name;
	/** ����GgafDx9Model�ւ̃|�C���^�B�I�[��NULL */
	//GgafDx9Model*	_pModel_Next;

    /**
	 * �R���X�g���N�^<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 */
	GgafDx9Model(char* prm_model_name);




	/**
	 * ���f����`�悵�܂�.
	 * @param prm_pActor_Target �`�悷�郂�f���̃A�N�^�[
	 * @return HRESULT
	 */
	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target) = 0;

	/**
	 * ���f�����č\�z���܂�.
	 */
	virtual void restore() = 0;

	/**
	 * ���f����������܂�.
	 */
	virtual void release() = 0;

	/**
	 * �f�o�C�X���X�g���R�[���o�b�N
	 */
	virtual void onDeviceLost() = 0;

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9ModelManager�ł���<BR>
	 */
	virtual ~GgafDx9Model();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9MODEL_H_*/
