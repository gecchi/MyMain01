#ifndef GGAFDX9BGMMANAGER_H_
#define GGAFDX9BGMMANAGER_H_

/**
 * GgafDx9Bgm �Ǘ��N���X .
 * �����ς� GgafDx9Bgm �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 */
class GgafDx9BgmManager {

public:
	/** GgafDx9Bgm�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	static GgafDx9Bgm* _pBgm_First;
	/**
	 * GgafDx9Bgm�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param prm_pBgm_New �ǉ�����GgafDx9Bgm�I�u�W�F�N�g�̃|�C���^
	 */
	static void add(GgafDx9Bgm* prm_pBgm_New);

	/**
	 * GgafDx9Bgm�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param prm_ogg_name ogg��`�̎��ʖ��B".ogg"��ǉ�����ƃt�@�C�����ɂȂ�B
	 * @return	���]��GgafDx9Bgm�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	static GgafDx9Bgm* find(string prm_ogg_name);

	/**
	 * GgafDx9Bgm�I�u�W�F�N�g���擾�B<BR>
	 * GgafDx9Bgm �I�u�W�F�N�g���X�g�i�擪��_pBgm_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9Bgm������j�ꍇ�A GgafDx9Bgm �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * @param prm_ogg_name ogg��`�̎��ʖ��B".ogg"��ǉ�����ƃt�@�C�����ɂȂ�B
	 */
	static GgafDx9Bgm* get(string prm_ogg_name);


	/**
	 * GgafDx9Bgm�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
	 */
	static void clear();

};

#endif /*GGAFDX9BGMMANAGER_H_*/
