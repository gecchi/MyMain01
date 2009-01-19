#ifndef GGAFGARBAGEBOX_H_
#define GGAFGARBAGEBOX_H_
namespace GgafCore {


/**
 * ゴミ箱 .
 * 不要になったオブジェクトは、とりあえずココに登録。<BR>
 * ココに登録すると、処理の余裕のあるときに工場がちびちび DELETE してゆきます<BR>
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
