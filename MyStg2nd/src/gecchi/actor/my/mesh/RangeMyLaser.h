#ifndef RANGENMYLASER_H_
#define RANGENMYLASER_H_

/**
 * ���@�̃V���b�g�ȂǁA��ʏ�ɃL�����N�^��MAX�����t�ŕ\���������ꍇ���ɗL���B
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
 			throw_GgafCriticalException("RangeMyLaser::getFreeOne() �q������܂���");
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
			throw_GgafCriticalException("RangeMyLaser::release() �q������܂���");
 		}
 		GgafActor* pActor = getSubFirst();
 		do { //����
 			if (pActor == prm_pActorSub) {
 				pActor->declareStop();


 				if (prm_pActorSub == _pActor_MyLaserChipHead && prm_pActorSub == _pActor_MyLaserChipTail) {
 					//�w�b�h�ł���e�C���Ȃ�΍Ō�̈�ł���B
 					_pActor_MyLaserChipHead = NULL;
 					_pActor_MyLaserChipTail = NULL;
 					canObtain = true;
 					break;
 				} else {
 					//��������Ȃ��ꍇ�w�b�h�Ȃ�
 					if (_pActor_MyLaserChipHead == prm_pActorSub) {
						_pActor_MyLaserChipHead = NULL;
						if (_pActor_MyLaserChipTail == NULL) {//���߂Ẵw�b�h�̃����[�X�Ȃ�΃e�C��������
							_pActor_MyLaserChipTail = prm_pActorSub;
						}
						//�w�b�h�͎��̃`�b�v�Ɉ����p���i�Ȃ��Ƃ͌��킹�Ȃ��j

					} else if (_pActor_MyLaserChipTail == prm_pActorSub) {

					}
					break;
 				}
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
