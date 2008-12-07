#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_

/**
 * 下位アクタークラスへのインターフェイス .
 * GgafCoreライブラリの利用者は、新たにアクタークラスを作る場合本クラスを継承してアクタークラスを作ることにする。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafMainActor : public GgafActor {

protected:
	/** 管理者 */
    GgafLordActor* _pLordActor;
	/** 種別（グループ）を司るヘッドアクター */
	GgafHeadActor* _pHeadActor;

public:

	GgafMainActor(string prm_name);

	/**
	 * 管理者を設定する。 .
	 */
	virtual void setLordActor(GgafLordActor* prm_pLordActor);


	/**
	 * 所属ヘッドアクターを設定する。<BR>
	 */
	virtual void setHeadActor(GgafHeadActor* prm_pHeadActor);

	/**
	 * 管理アクター取得。 .
	 * @return 管理アクター
	 */
	virtual GgafLordActor* getLordActor();

	/**
	 * 所属ヘッドアクターを取得する。 .
	 * @return 所属ヘッドアクター
	 */
	virtual GgafHeadActor* getHeadActor();

    /**
	 * 神様に接見 .
	 * @return	呼ばれて出てきた神様
	 */
	virtual GgafGod* askGod();


	virtual ~GgafMainActor();
};


#endif /*GGAFMAINACTOR_H_*/
