#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * ローテーションアクタークラス .
 * 子に予めアクターを登録しておき（ローテーションメンバーと呼ぶ）、空いているメンバーを取得する。<BR>
 * 取得したアクターを、ローテーション戻す（再度使いまわしをしたい）たい時は stop() して下さい。本クラスが自動的に拾います。<BR>
 * 敵弾など、何度も使いまわし、かつオブジェクト数制限したい場合等に有効。ストックと考えても良い。<BR>
 * また連続obtain()の場合、次のobtain()のアクターは必ず隣同士となっています。<BR>
 */
class RotationActor : public GgafCore::GgafDummyActor {

public:
	StgChecker* _pChecker;

 	RotationActor(const char* prm_name);

	/**
	 * 暇そうなローテーションメンバー（play中、またはplay予約されていない）が居れば、
	 * ローテーションの一番先頭に移動させます。<BR>
	 * TODO:これは負荷がかかるのであまりやりたくない、Laser以外はなんでもいいはず
	 * ＜OverRide です＞<BR>
	 */
	virtual void processBehavior() {
		static GgafMainActor* pActor;
		pActor = getSubFirst();
		while(true) {
			if (pActor->switchedToStop()) {
				pActor->moveFirst();
			}
			if (pActor->isLast()) {
				break;
			} else {
				pActor = pActor->getNext();
			}
		}
	};

	/**
	 * 子アクターへは影響させない
	 */
	virtual void play() {
		playAlone();
	}

	virtual void stop() {
		stopAlone();
	}

	virtual void pause() {
		pauseAlone();
	}


	/**
	 * 暇そうなローテーションメンバー（play中、またはplay予約されていない）を取得する。<BR>
	 * 暇なローテーションメンバーが居ない場合 NULL が返ります。<BR>
	 * 取得できる場合、ポインタを返すと共に、そのアクターはローテーションの一番後ろに移動されます。<BR>
	 * @return 暇そうなローテーションメンバーアクター
	 */
	virtual GgafCore::GgafMainActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("RotationActor::getFreeOne() 子がありません");
 		}
 		static GgafMainActor* pActor;
 		pActor= getSubFirst();
 		do {
 			if(pActor->isPlaying()) {
 				pActor = NULL;
 				break;
 			} else if (pActor->_willPlayNextFrame) {
 				if (pActor->isLast()) {
 					pActor = NULL;
 					break;
 				} else {
 					pActor = pActor->getNext();
 				}
 			} else {
 				pActor->moveLast();
 				break;
 			}
 		} while(true);
 		return pActor;
 	};

 	virtual ~RotationActor() {
 	};
};


}
#endif /*ROTATIONACTOR_H_*/
