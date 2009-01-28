#ifndef GGAFDX9TEXRURE_H_
#define GGAFDX9TEXRURE_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9Texture : public GgafCore::GgafResource<IDirect3DTexture9> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DTexture9 �e�N�X�`��
	 */
	GgafDx9Texture(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 * �I�[�o�[���C�h
	 */
	void releaseResourceProcess();

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9TextureManager�ł���<BR>
	 */
	virtual ~GgafDx9Texture();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9TEXRURE_H_*/
