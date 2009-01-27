#ifndef GGAFDX9TEXTUREMANAGER_H_
#define GGAFDX9TEXTUREMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9Texture �Ǘ��N���X .
 * �����ς� GgafDx9Texture �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9TextureManager {
protected:
	/** GgafDx9Texture�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	static GgafDx9Texture* _pTexture_First;
	/**
	 * GgafDx9Texture�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pTexture_New �ǉ�����GgafDx9Texture�I�u�W�F�N�g�̃|�C���^
	 */
	static void add(GgafDx9Texture* prm_pTexture_New);

	/**
	 * GgafDx9Texture�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 * @return	���]��GgafDx9Texture�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	static GgafDx9Texture* find(std::string prm_texture_file_name);

public:

	/**
	 * GgafDx9Texture�I�u�W�F�N�g���擾�B<BR>
	 * ���f���I�u�W�F�N�g�́A���������A���̃��\�b�h���P�񂾂��Ăяo���ăe�N�X�`�����擾����B<BR>
	 * �e�N�X�`���́A�ێ����X�g�ɑ��݂���΂����Ԃ��A���݂��Ȃ���� new ���܂��B<BR>
	 * �e�N�X�`����ێ����X�g����擾�����ꍇ�A�Q�ƃJ�E���^�������܂��B�i���f���������P��Ɍ��肷��̂͂��̂��߁j<BR>
	 * new �����ꍇ�A�Q�ƃJ�E���^��1�ł��B<BR>
	 * �Q�ƃJ�E���^�̓��f���� delete ���Ƀe�N�X�`����������邩�ǂ����̔��f�Ɏg�p�����B<BR>
	 * @param prm_texture_file_name �e�N�X�`�����ʖ�(���t�@�C����)
	 */
	static GgafDx9Texture* obtain(std::string prm_texture_file_name);

	static void remove(GgafDx9Texture* prm_pTexture);

	/**
	 * GgafDx9Texture�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
	 */
	static void release();

};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
