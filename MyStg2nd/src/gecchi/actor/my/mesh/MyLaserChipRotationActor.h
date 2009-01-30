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
	 * 暇そうなローテーションメンバー（play中、またはplay予約されていない）を取得する。<BR>
	 * 暇なローテーションメンバーが居ない場合 NULL が返ります。<BR>
	 * 取得できる場合、ポインタを返すと共に、そのアクターはローテーションの一番後ろに移動されます。<BR>
	 * @return 暇そうなローテーションメンバーアクター
	 */
	virtual GgafMainActor* obtain() {
 		if (_pSubFirst == NULL) {
 			throw_GgafCriticalException("MyLaserChipRotationActor::getFreeOne() 子がありません");
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
