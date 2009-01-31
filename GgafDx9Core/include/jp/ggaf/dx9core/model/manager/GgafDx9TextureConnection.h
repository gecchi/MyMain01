#ifndef GGAFDX9TEXTURECONNECTION_H_
#define GGAFDX9TEXTURECONNECTION_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9TextureLead : public GgafCore::GgafResourceLead<IDirect3DTexture9> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DTexture9 �e�N�X�`��
	 */
	GgafDx9TextureLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 * �I�[�o�[���C�h
	 */
	void processReleaseResource(IDirect3DTexture9* prm_pResource);

	/**
	 * �f�X�g���N�^<BR>
	 */
	virtual ~GgafDx9TextureLead() {
	};
};


}
#endif /*GGAFDX9TEXTURECONNECTION_H_*/
