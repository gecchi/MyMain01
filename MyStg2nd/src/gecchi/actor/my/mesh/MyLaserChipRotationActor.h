#ifndef MYLASERCHIPROTATIONACTOR_H_
#define MYLASERCHIPROTATIONACTOR_H_
namespace MyStg2nd {

class MyLaserChipRotationActor : public RotationActor {

public:
	MyLaserChipRotationActor(std::string prm_name);

	virtual void processBehavior() {
		static GgafMainActor* pActor;
		pActor = getSubFirst();
		while(true) {
			if (pActor->switchedToStop()) {
				pActor->moveFirst();
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
 			throw_GgafCriticalException("MyLaserChipRotationActor::getFreeOne() �q������܂���");
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
 				pActor->moveLast();
 				break;
 			}
 		} while(true);
 		return pActor;
 	};

 	virtual ~MyLaserChipRotationActor() {
 	};
};


}
#endif /*MYLASERCHIPROTATIONACTOR_H_*/
