#ifndef GGAFDX9SEMANAGER_H_
#define GGAFDX9SEMANAGER_H_

class GgafDx9SeManager {

public:
	/** GgafDx9Se�I�u�W�F�N�g�̃��X�g�̐擪�̃|�C���^�B�I�[��NULL */
	static GgafDx9Se* _pSe_First;
	/**
	 * GgafDx9Se�I�u�W�F�N�g�����X�g�ɒǉ��B<BR>
	 * @param �ǉ�����GgafDx9Se�I�u�W�F�N�g�̃|�C���^
	 */
	static void add(GgafDx9Se* prm_pSe_New);

	/**
	 * GgafDx9Se�I�u�W�F�N�g�����X�g���猟���B<BR>
	 * @param wav��`�̎��ʖ��B".wav"��ǉ�����ƃt�@�C�����ɂȂ�B
	 * @return	���]��GgafDx9Se�I�u�W�F�N�g�̃|�C���^�B���X�g�ɑ��݂��Ȃ������ꍇ NULL
	 */
	static GgafDx9Se* find(string prm_wave_name);

	/**
	 * GgafDx9Se�I�u�W�F�N�g���擾�B<BR>
	 * GgafDx9Se �I�u�W�F�N�g���X�g�i�擪��_pSe_First�j<BR>
	 * ���猟�����A�q�b�g�����i�����ς�GgafDx9Se������j�ꍇ�A GgafDx9Se �ɃL���X�g���Ă����Ԃ��B<BR>
	 * �q�b�g���Ȃ��ꍇ�� create ���s���C���X�^���X�����ナ�X�g�ɒǉ��������Ԃ��B<BR>
	 * @param wav��`�̎��ʖ��B".wav"��ǉ�����ƃt�@�C�����ɂȂ�B
	 */
	static GgafDx9Se* get(string prm_wave_name);


	/**
	 * GgafDx9Se�I�u�W�F�N�g�̃��X�g�����ׂ� delete ���s���B<BR>
	 */
	static void clear();

};

#endif /*GGAFDX9SEMANAGER_H_*/
