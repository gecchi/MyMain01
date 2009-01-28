#ifndef GGAFDX9TEXTUREPOINTER_H_
#define GGAFDX9TEXTUREPOINTER_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9TexturePointer : public GgafCore::GgafResourcePointer<IDirect3DTexture9> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @param prm_pIDirect3DTexture9 �e�N�X�`��
	 */
	GgafDx9TexturePointer(std::string prm_texture_file_name, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);


	/**
	 * �f�X�g���N�^<BR>
	 * delete����̂�GgafDx9TexturePointerManager�ł���<BR>
	 */
	virtual ~GgafDx9TexturePointer();		//�f�X�g���N�^
};


}
#endif /*GGAFDX9TEXTUREPOINTER_H_*/
