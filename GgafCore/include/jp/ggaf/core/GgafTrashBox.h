#ifndef GGAFTRASHBOX_H_
#define GGAFTRASHBOX_H_

/**
 * ゴミ箱 .
 * 不要になったオブジェクトは、とりあえずココに登録。<BR>
 * 処理の余裕のあるときに神(GgafGod) が DELETE してゆきます<BR>
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
