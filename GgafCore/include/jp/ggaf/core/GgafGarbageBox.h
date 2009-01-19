#ifndef GGAFGARBAGEBOX_H_
#define GGAFGARBAGEBOX_H_
namespace GgafCore {


/**
 * �S�~�� .
 * �s�v�ɂȂ����I�u�W�F�N�g�́A�Ƃ肠�����R�R�ɓo�^�B<BR>
 * �R�R�ɓo�^����ƁA�����̗]�T�̂���Ƃ��ɍH�ꂪ���т��� DELETE ���Ă䂫�܂�<BR>
 * @version 1.00
 * @since 2008/12/16
 * @auther Masatoshi Tsuge
 */
class GgafGarbageBox : public GgafObject {

public:

	GgafGarbageRootActor* _pGarbageRootActor;
	GgafGarbageRootScene* _pGarbageRootScene;

	GgafGarbageBox();

	void add(GgafActor* prm_pActor);

	void add(GgafScene* prm_pScene);


	void cleane(int prm_iNumCleanNode);


	virtual ~GgafGarbageBox();
};


}
#endif /*GGAFGARBAGEBOX_H_*/
