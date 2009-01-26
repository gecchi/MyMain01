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
	static LPDIRECT3DTEXTURE9 _pTexture_First;
	/**
	 * GgafDx9Texture�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pTexture_New �ǉ�����GgafDx9Texture�I�u�W�F�N�g�̃|�C���^
	 */
	static void add(LPDIRECT3DTEXTURE9 prm_pTexture_New);

	/**
	 * GgafDx9Texture�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_ogg_name ogg��`�̎��ʖ��B".ogg"��ǉ�����ƃt�@�C�����ɂȂ�B
	 * @return	���]��GgafDx9Texture�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	static LPDIRECT3DTEXTURE9 find(std::string prm_ogg_name);

public:

	/**
	 * GgafDx9Texture�I�u�W�F�N�g���擾�B<BR>
	 * GgafDx9Texture �I�u�W�F�N�g���X�g�i�擪��_pTexture_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9Texture������j�ꍇ�A GgafDx9Texture �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * ������ std::string �̔�r��������܂ōs�����߁A�d���ł��B<BR>
	 * ���t���[�����s�����悤�Ȏg�p�͔�����ׂ��ł��B<BR>
	 * �������֐����łP��g�p���A�|�C���^��ێ�����Ƃ����g�p���@��z��B<BR>
	 * @param prm_ogg_name ogg��`�̎��ʖ��B".ogg"��ǉ�����ƃt�@�C�����ɂȂ�B
	 */
	static LPDIRECT3DTEXTURE9 get(std::string prm_ogg_name);


	/**
	 * GgafDx9Texture�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
	 */
	static void clear();

};


}
#endif /*GGAFDX9TEXTUREMANAGER_H_*/
