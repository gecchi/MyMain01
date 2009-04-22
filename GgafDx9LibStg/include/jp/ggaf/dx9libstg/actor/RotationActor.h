#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * ���[�e�[�V�����A�N�^�[�N���X .
 * �q�ɗ\�߃A�N�^�[��o�^���Ă����i���[�e�[�V���������o�[�ƌĂԁj�A�󂢂Ă��郁���o�[���擾����B<BR>
 * �擾�����A�N�^�[���A���[�e�[�V�����߂��i�ēx�g���܂킵���������j�������� inactivateTree() ���ĉ������B�{�N���X�������I�ɏE���܂��B<BR>
 * �G�e�ȂǁA���x���g���܂킵�A���I�u�W�F�N�g�������������ꍇ���ɗL���B�X�g�b�N�ƍl���Ă��ǂ��B<BR>
 * �܂��A��obtain()�̏ꍇ�A����obtain()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă��܂��B<BR>
 */
class RotationActor : public GgafCore::GgafDummyActor {

public:
    StgChecker* _pChecker;

    RotationActor(const char* prm_name);

//    /**
//     * �ɂ����ȃ��[�e�[�V���������o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j������΁A
//     * ���[�e�[�V�����̈�Ԑ擪�Ɉړ������܂��B<BR>
//     * TODO:����͕��ׂ�������̂ł��܂��肽���Ȃ��ALaser�ȊO�͂Ȃ�ł������͂�
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processBehavior() {
//        static GgafMainActor* pActor;
//        pActor = getSubFirst();
//        while (true) {
//            if (pActor->onChangeToInactive()) {
//                pActor->moveFirst();
//            }
//            if (pActor->isLast()) {
//                break;
//            } else {
//                pActor = pActor->getNext();
//            }
//        }
//    }

    /**
     * �q�A�N�^�[�ւ͉e�������Ȃ�
     */
    virtual void activateTree() {
        activate();
    }

    virtual void inactivateTree() {
        inactivate();
    }

    /**
     * �ɂ����ȃ��[�e�[�V���������o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j���擾����B<BR>
     * �ɂȃ��[�e�[�V���������o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓��[�e�[�V�����̈�Ԍ��Ɉړ�����܂��B<BR>
     * @return �ɂ����ȃ��[�e�[�V���������o�[�A�N�^�[
     */
    virtual GgafCore::GgafMainActor* obtain() {
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("RotationActor::getFreeOne() �q������܂���");
        }
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        while(true) {
            if (pActor->isActive() || pActor->_is_active_flg_in_next_frame) {
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            } else {
                pActor->activate();
                pActor->moveLast(); //�擾�I
                break;
            }
        }
        return pActor;
    }

    virtual ~RotationActor() {
    }
};

}
#endif /*ROTATIONACTOR_H_*/
