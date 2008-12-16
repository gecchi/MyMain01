#ifndef GGAFTRASHBOX_H_
#define GGAFTRASHBOX_H_

/**
 * �S�~�� .
 * �s�v�ɂȂ����I�u�W�F�N�g�́A�Ƃ肠�����R�R�ɓo�^�B<BR>
 * �����̗]�T�̂���Ƃ��ɐ_(GgafGod) �� DELETE ���Ă䂫�܂�<BR>
 * @version 1.00
 * @since 2008/12/16
 * @auther Masatoshi Tsuge
 */
class GgafTrashBox : public GgafObject {

public:

	GgafTrashRootActor* _pTrashRootActor;
	GgafTrashRootScene* _pTrashRootScene;

	GgafTrashBox();

	void add(GgafActor* prm_pActor);

	void add(GgafScene* prm_pScene);


	void cleane(int prm_iNumCleanNode);


	virtual ~GgafTrashBox();
};

#endif /*GGAFTRASHBOX_H_*/
