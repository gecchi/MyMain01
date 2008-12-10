#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ローテーションアクタークラス .
 * 子に予めアクターを登録しておき（ローテーションメンバーと呼ぶ）、空いているメンバーを取得する。<BR>
 * 取得したアクターを、ローテーション戻す（再度使いまわしをしたい）たい時は declareStop() して下さい。本クラスが自動的に拾います。<BR>
 * 敵弾など、何度も使いまわし、かつオブジェクト数制限したい場合等に有効。ストックと考えても良い。<BR>
 * また連続obtain()の場合、次のobtain()のアクターは必ず隣同士となっています。<BR>
 */
class RotationActor : public GgafDummyActor {

public:
	StgChecker* _pChecker;

 	RotationActor(string prm_name);

	/**
	 * 暇そうなローテーションメンバー（play中、またはplay予約されていない）が居れば、
	 * ローテーションの一番先頭に移動させます。<BR>
	 * ＜OverRide です＞<BR>
	 */
	virtual void processBehavior() {
		GgafMainActor* pActor = getSubFirst();
		while(true) {
			if (pActor->switchedToStop()) {
				pActor->declareMoveFirst();
			}
			if (pActor->isLast()) {
				break;
			} else {
				pActor = pActor -> getNext();
			}
		}
	};

	/**
	 * 暇そうなローテーションメンバー（play中、またはplay予約されていない）を取得する。<BR>
	 * 暇なローテーションメンバーが居ない場合 NULL が返ります。<BR>
	 * 取得できる場合、ポインタを返すと共に、そのアクターはローテーションの一番後ろに移動されます。<BR>
	 * @return 暇そうなローテーションメンバーアクター
	 */
	virtual GgafMainActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("RotationActor::getFreeOne() 子がありません");
 		}
 		GgafMainActor* pActor = getSubFirst();
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
 				pActor->declareMoveLast();
 				break;
 			}
 		} while(true);
 		return pActor;
 	};

 	virtual ~RotationActor() {
 	};
};


#endif /*ROTATIONACTOR_H_*/
