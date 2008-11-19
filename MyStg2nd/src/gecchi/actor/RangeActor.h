#ifndef RANGENACTOR_H_
#define RANGENACTOR_H_

/**
 * ���@�̃V���b�g�ȂǁA��ʏ�ɃL�����N�^��MAX�����t�ŕ\���������ꍇ���ɗL���B
 */
class RangeActor : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;

	GgafActor* _pActor_RangeHeader;

 	RangeActor(string prm_name);

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
 			throw_GgafCriticalException("RangeActor::getFreeOne() �q������܂���");
 		}
 		GgafActor* pActor = getSubFirst();
 		do {
 			if (pActor == _pActor_RangeHeader) {

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

 		if (_pActor_RangeHeader == NULL) {
 			_pActor_RangeHeader = pActor;
 		}
 		return pActor;
 	};

 	void release(GgafActor* prm_pActorSub) {
 		if (_pSubFirst == NULL) {
			throw_GgafCriticalException("RangeActor::release() �q������܂���");
 		}
 		GgafActor* pActor = getSubFirst();
 		do { //����
 			if (pActor == prm_pActorSub) {
 				pActor->declareStop();
 				if (_pActor_RangeHeader == prm_pActorSub) {
 					_pActor_RangeHeader = NULL;
 				}
 				break;
 			} else {
				if (pActor->isLast()) {
					pActor = NULL;
					throw_GgafCriticalException("RangeActor::release() ������ "<<prm_pActorSub->getClassName()<<"["<<prm_pActorSub->getName()<<"]�͋��܂���");
		 		} else {
					pActor = pActor->getNext();
				}
 			}
 		} while(true);
 	};


 	virtual ~RangeActor() {
 	};
};


#endif /*RANGENACTOR_H_*/
