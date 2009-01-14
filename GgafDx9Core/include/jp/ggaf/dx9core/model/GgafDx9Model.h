#ifndef GGAFDX9MODEL_H_
#define GGAFDX9MODEL_H_

class GgafDx9Model : public GgafObject {
    friend class GgafDx9ModelManager;

protected:
	/** ���f����`�̎��ʖ��B */
	string			_model_name;
	/** ����GgafDx9Model�ւ̃|�C���^�B�I�[��NULL */
	GgafDx9Model*	_pModel_Next;

public:

	/** �O��`��Model��`�� */
	static string _s_modelname_lastdraw;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_model_name ���f����`�̎��ʖ��B".x"��ǉ�����ƒ�`X�t�@�C�����ɂȂ�B
	 */
	GgafDx9Model(string prm_model_name);

	virtual HRESULT draw(GgafDx9BaseActor* prm_pActor_Target) = 0;

	virtual void restore() = 0;

	virtual void onDeviceLost() = 0;
	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9ModelManager�ł���<BR>
	 */
	virtual ~GgafDx9Model();		//�f�X�g���N�^
};

#endif /*GGAFDX9MODEL_H_*/
