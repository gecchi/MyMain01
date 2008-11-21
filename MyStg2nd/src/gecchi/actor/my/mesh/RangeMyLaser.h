#ifndef RANGENMYLASER_H_
#define RANGENMYLASER_H_

/**
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RangeMyLaser : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;
	MyLaserChip* _pHeadChip;
	DWORD _dwFrame_LastObtain;

	/** 0:Head取得可能/ 1:Head以外取得可能 / 2:取得不可能(HeadStopのため綺麗にしている) */
	int _state;

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
 			throw_GgafCriticalException("RangeMyLaser::obtain() 子がありません");
 		}
 		GgafActor* pActor = getSubFirst();
		if(pActor->isPlaying() || pActor->_willPlayNextFrame) {
			pActor = NULL;
		} else {
			if (_state == 0) {
				((MyLaserChip*)pActor)->_isHead = true;
				_pHeadChip = pActor;
				pActor->declareMoveLast();
				_dwFrame_LastObtain = _dwFrame;
				_state = 1;
			} else if (_state == 1) {
				if (_dwFrame_LastObtain+1 == _dwFrame) {
					//連続取得
					pActor->declareMoveLast();
					((MyLaserChip*)pActor)->_isHead = false;
				} else {
					//間隔ありのため空を一つかます
					pActor->declareMoveLast();
					pActor = pActor -> getNext();
					if(pActor->isPlaying() || pActor->_willPlayNextFrame) {
						pActor = NULL;
					} else {
						pActor->declareMoveLast();
						((MyLaserChip*)pActor)->_isHead = false;
					}
				}
			}
			break;
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
 				if (pActor == _pHeadChip) {
 					_state == 2;
 				}
 				break;
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
