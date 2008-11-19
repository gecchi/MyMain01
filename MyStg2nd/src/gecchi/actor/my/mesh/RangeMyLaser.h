#ifndef RANGENMYLASER_H_
#define RANGENMYLASER_H_

/**
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RangeMyLaser : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;

	GgafActor* _pActor_MyLaserChipHead;
	GgafActor* _pActor_MyLaserChipTail;
	bool canObtain;

 	RangeMyLaser(string prm_name);

	void initialize() {};

	void processBehavior() {};

	void processJudgement() {};

	void processDrawPrior() {};

	void processDrawMain() {};

	void processDrawTerminate() {};

	void processHappen(int prm_no) {};

	void processFinal() {};

 	void processOnHit(GgafActor* prm_pActor_Opponent) {};


 	GgafActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("RangeMyLaser::getFreeOne() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
 		do {
 			if (pActor == _pActor_MyLaserChipHead) {

 			}???

			if(pActor->isPlaying() || pActor->_willPlayNextFrame) {
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

 		if (_pActor_MyLaserChipHead == NULL) {
 			_pActor_MyLaserChipHead = pActor;
 		}
 		return pActor;
 	};

 	void release(GgafActor* prm_pActorSub) {
 		if (_pSubFirst == NULL) {
			throw_GgafCriticalException("RangeMyLaser::release() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
 		do { //検索
 			if (pActor == prm_pActorSub) {
 				pActor->declareStop();


 				if (prm_pActorSub == _pActor_MyLaserChipHead && prm_pActorSub == _pActor_MyLaserChipTail) {
 					//ヘッドでありテイルならば最後の一つである。
 					_pActor_MyLaserChipHead = NULL;
 					_pActor_MyLaserChipTail = NULL;
 					canObtain = true;
 					break;
 				} else {
 					//そうじゃない場合ヘッドなら
 					if (_pActor_MyLaserChipHead == prm_pActorSub) {
						_pActor_MyLaserChipHead = NULL;
						if (_pActor_MyLaserChipTail == NULL) {//初めてのヘッドのリリースならばテイル発生し
							_pActor_MyLaserChipTail = prm_pActorSub;
						}
						//ヘッドは次のチップに引き継ぐ（ないとは言わせない）

					} else if (_pActor_MyLaserChipTail == prm_pActorSub) {

					}
					break;
 				}
 			} else {
				if (pActor->isLast()) {
					pActor = NULL;
					throw_GgafCriticalException("RangeMyLaser::release() 引数の "<<prm_pActorSub->getClassName()<<"["<<prm_pActorSub->getName()<<"]は居ません");
		 		} else {
					pActor = pActor->getNext();
				}
 			}
 		} while(true);
 	};


 	virtual ~RangeMyLaser() {
 	};
};


#endif /*RANGENMYLASER_H_*/
