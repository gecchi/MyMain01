#ifndef GGAFDX9MODELLEAD_H_
#define GGAFDX9MODELLEAD_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9ModelLead : public GgafCore::GgafResourceLead<IDirect3DModel9> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DModel9 �e�N�X�`��
	 */
	GgafDx9ModelLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DModel9);

	/**
	 * �I�[�o�[���C�h
	 */
	void processReleaseResource(IDirect3DModel9* prm_pResource);

	/**
	 * �f�X�g���N�^<BR>
	 */
	virtual ~GgafDx9ModelLead() {
	};
};


}
#endif /*GGAFDX9MODELLEAD_H_*/
