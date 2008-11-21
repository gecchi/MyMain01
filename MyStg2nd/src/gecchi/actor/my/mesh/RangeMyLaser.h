#ifndef RANGENMYLASER_H_
#define RANGENMYLASER_H_

/**
 * ���@�̃V���b�g�ȂǁA��ʏ�ɃL�����N�^��MAX�����t�ŕ\���������ꍇ���ɗL���B
 */
class RangeMyLaser : public GgafDx9UntransformedActor {

public:
	StgChecker* _pChecker;
	MyLaserChip* _pHeadChip;
	DWORD _dwFrame_LastObtain;

	/** 0:Head�擾�\/ 1:Head�ȊO�擾�\ / 2:�擾�s�\(HeadStop�̂����Y��ɂ��Ă���) */
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
 			throw_GgafCriticalException("RangeMyLaser::obtain() �q������܂���");
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
					//�A���擾
					pActor->declareMoveLast();
					((MyLaserChip*)pActor)->_isHead = false;
				} else {
					//�Ԋu����̂��ߋ������܂�
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
			throw_GgafCriticalException("RangeMyLaser::release() �q������܂���");
 		}
 		GgafActor* pActor = getSubFirst();
 		do { //����
 			if (pActor == prm_pActorSub) {
 				pActor->declareStop();
 				if (pActor == _pHeadChip) {
 					_state == 2;
 				}
 				break;
 			} else {
				if (pActor->isLast()) {
					pActor = NULL;
					throw_GgafCriticalException("RangeMyLaser::release() ������ "<<prm_pActorSub->getClassName()<<"["<<prm_pActorSub->getName()<<"]�͋��܂���");
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
