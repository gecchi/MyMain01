#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_
namespace GgafCore {


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
	 * 次のノード取得する。 .
	 * ＜OverRide です＞
	 * @return	次ノード
	 */
	virtual GgafMainActor* getNext() {
		return (GgafMainActor*)GgafActor::getNext();
	};

	/**
	 * 前のノード取得する。 .
	 * ＜OverRide です＞
	 * @return	前ノード
	 */
	virtual GgafMainActor* getPrev() {
		return (GgafMainActor*)GgafActor::getPrev();
	}

	/**
	 * 子ノードのグループの先頭ノードを取得する .
	 * 子ノードが存在しない場合はエラー。
	 * ＜OverRide です＞
	 * @return	子ノードの先頭ノード
	 */
	virtual GgafMainActor* getSubFirst(){
		return (GgafMainActor*)GgafActor::getSubFirst();
	}

	/**
	 * 自ツリーノードを連結リストから切り離し、独立する。 .
	 * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
	 * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
	 * ＜OverRide です＞
	 * @return	自ノードのポインタ
	 */
	virtual GgafMainActor* tear() {
		return (GgafMainActor*)GgafActor::tear();
	};

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


}
#endif /*GGAFMAINACTOR_H_*/
