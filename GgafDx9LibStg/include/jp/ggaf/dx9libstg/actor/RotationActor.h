#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ローテーションアクタークラス .
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RotationActor : public GgafDx9UntransformedActor {

public:
	StgMover* _pMover;
	StgChecker* _pChecker;

 	RotationActor(string prm_name);

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
 			throw_GgafCriticalException("RotationActor::getFreeOne() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
 		do {
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
 		return pActor;
 	};


 	virtual ~RotationActor() {
 	};
};


#endif /*ROTATIONACTOR_H_*/
