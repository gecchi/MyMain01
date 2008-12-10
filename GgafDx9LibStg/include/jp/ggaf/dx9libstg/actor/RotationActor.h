#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ���[�e�[�V�����A�N�^�[�N���X .
 * �q�ɗ\�߃A�N�^�[��o�^���Ă����i���[�e�[�V���������o�[�ƌĂԁj�A�󂢂Ă��郁���o�[���擾����B<BR>
 * �擾�����A�N�^�[���A���[�e�[�V�����߂��i�ēx�g���܂킵���������j�������� declareStop() ���ĉ������B�{�N���X�������I�ɏE���܂��B<BR>
 * �G�e�ȂǁA���x���g���܂킵�A���I�u�W�F�N�g�������������ꍇ���ɗL���B�X�g�b�N�ƍl���Ă��ǂ��B<BR>
 * �܂��A��obtain()�̏ꍇ�A����obtain()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă��܂��B<BR>
 */
class RotationActor : public GgafDummyActor {

public:
	StgChecker* _pChecker;

 	RotationActor(string prm_name);

	/**
	 * �ɂ����ȃ��[�e�[�V���������o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j������΁A
	 * ���[�e�[�V�����̈�Ԑ擪�Ɉړ������܂��B<BR>
	 * ��OverRide �ł���<BR>
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
	 * �ɂ����ȃ��[�e�[�V���������o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j���擾����B<BR>
	 * �ɂȃ��[�e�[�V���������o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
	 * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓��[�e�[�V�����̈�Ԍ��Ɉړ�����܂��B<BR>
	 * @return �ɂ����ȃ��[�e�[�V���������o�[�A�N�^�[
	 */
	virtual GgafMainActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("RotationActor::getFreeOne() �q������܂���");
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
