#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ���[�e�[�V�����A�N�^�[�N���X .
 * ���@�̃V���b�g�ȂǁA��ʏ�ɃL�����N�^��MAX�����t�ŕ\���������ꍇ���ɗL���B
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
 			throw_GgafCriticalException("RotationActor::getFreeOne() �q������܂���");
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
