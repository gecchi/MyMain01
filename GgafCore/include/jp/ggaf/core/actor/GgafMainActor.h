#ifndef GGAFMAINACTOR_H_
#define GGAFMAINACTOR_H_
namespace GgafCore {


/**
 * 普通のアクター(演者).
 * 下位アクタークラスへのインターフェイスであり、<BR>
 * 新たにアクタークラスを作る場合本クラスを継承してアクタークラスを作ることとする。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafMainActor : public GgafActor {

protected:
	/** 管理者 */
    GgafLordActor* _pLordActor;
	/** 種別（グループ）を司る団長 */
	GgafHeadActor* _pHeadActor;

public:

	GgafMainActor(const char* prm_name);

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
	 * 団長を設定する。<BR>
	 */
	virtual void setHeadActor(GgafHeadActor* prm_pHeadActor);

	/**
	 * 管理者取得。 .
	 * @return 管理者
	 */
	virtual GgafLordActor* getLordActor();

	/**
	 * 団長を取得する。 .
	 * @return 団長
	 */
	virtual GgafHeadActor* getHeadActor();

    /**
	 * 神に謁見 .
	 * @return	呼ばれて出てきた神
	 */
	virtual GgafGod* askGod();


	virtual ~GgafMainActor();
};


}
#endif /*GGAFMAINACTOR_H_*/
