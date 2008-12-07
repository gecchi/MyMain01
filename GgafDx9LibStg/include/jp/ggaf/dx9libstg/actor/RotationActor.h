#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ローテーションアクタークラス .
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RotationActor : public GgafDummyActor {

public:
	StgChecker* _pChecker;

 	RotationActor(string prm_name);

 	GgafActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("RotationActor::getFreeOne() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
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

 	void release(GgafActor* prm_pActorSub) {
 		if (_pSubFirst == NULL) {
			throw_GgafCriticalException("RotationActor::release() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
 		do { //検索
 			if (pActor == prm_pActorSub) {
 				pActor->declareStop();
 				pActor->declareMoveFirst();
 				break;
 			} else {
				if (pActor->isLast()) {
					pActor = NULL;
					throw_GgafCriticalException("RotationActor::release() 引数の "<<prm_pActorSub->getClassName()<<"["<<prm_pActorSub->getName()<<"]は居ません");
		 		} else {
					pActor = pActor->getNext();
				}
 			}
 		} while(true);
 	};


 	virtual ~RotationActor() {
 	};
};


#endif /*ROTATIONACTOR_H_*/
