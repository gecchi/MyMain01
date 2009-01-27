#ifndef GGAFDX9TEXRURE_H_
#define GGAFDX9TEXRURE_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9Texture : public GgafCore::GgafObject {

public:
	/** �Q�Ƃ��Ă��郂�f���I�u�W�F�N�g�� */
	int _iRefModelNum;

	/** �e�N�X�`�����ʖ�(���t�@�C����) */
	std::string			_texture_file_name;
	/** �e�N�X�`�� */
	LPDIRECT3DTEXTURE9 _pIDirect3DTexture9;
	/** ����GgafDx9Texture�ւ̃|�C���^�B�I�[��NULL */
	GgafDx9Texture*	_pTexture_Next;

	/** �O��`��Texture��`�� */
	static std::string _id_lastdraw;

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DTexture9 �e�N�X�`��
	 */
	GgafDx9Texture(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

	/**
	 *
	 */
	void release();

	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9TextureManager�ł���<BR>
	 */
	virtual ~GgafDx9Texture();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9TEXRURE_H_*/
