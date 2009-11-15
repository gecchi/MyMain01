#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * �A�N�^�[�����҃N���X .
 * �q�ɗ\�߃A�N�^�[��o�^���Ă����i�A�N�^�[�����҃����o�[�ƌĂԁj�A�󂢂Ă��郁���o�[���擾����B<BR>
 * �擾�����A�N�^�[���A�A�N�^�[�����Җ߂��i�ēx�g���܂킵���������j�������� inactivate() ���ĉ������B�{�N���X�������I�ɏE���܂��B<BR>
 * �G�e�ȂǁA���x���g���܂킵�A���I�u�W�F�N�g�������������ꍇ���ɗL���B�X�g�b�N�ƍl���Ă��ǂ��B<BR>
 * �܂��A��employ()�̏ꍇ�A����employ()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă��܂��B<BR>
 */
class ActorDispatcher : public GgafCore::GgafDummyActor {

public:
    StgChecker* _pStgChecker;

    ActorDispatcher(const char* prm_name);

//    /**
//     * �ɂ����ȃA�N�^�[�����҃����o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j������΁A
//     * �A�N�^�[�����҂̈�Ԑ擪�Ɉړ������܂��B<BR>
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
     * �ɂ����ȃA�N�^�[�����҂̃����o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j������΁Aactivate() ���Ď擾����B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * @return �ɂ����ȃA�N�^�[�����҂̃����o�[�A�N�^�[
     */
    virtual GgafCore::GgafMainActor* employ() {
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("ActorDispatcher::getFreeOne() �q������܂���");
        }
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        while(true) {
            if (pActor->isActive() || pActor->_is_active_flg_in_next_frame || pActor->_on_change_to_inactive_flg) {
                //���������A�����́A���t���[�������\��A�����́A���t���[���񊈓��\��̏ꍇ�͌�����
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

    virtual ~ActorDispatcher() {
    }
};

}
#endif /*ACTORDISPATCHER_H_*/
