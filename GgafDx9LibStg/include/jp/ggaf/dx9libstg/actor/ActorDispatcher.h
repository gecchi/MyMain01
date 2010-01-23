#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafDx9LibStg {

/**
 * �A�N�^�[�����҃N���X .
 * �q�ɗ\�߃A�N�^�[��o�^(enter ���\�b�h)���Ă����i�A�N�^�[�����҃����o�[�ƌĂԁj�A�󂢂Ă��郁���o�[���擾����B<BR>
 * �擾�����A�N�^�[���A�A�N�^�[�����Җ߂��i�ēx�g���܂킵���������j�������� inactivate() ���ĉ������B�{�N���X�������I�ɏE���܂��B<BR>
 * �G�e�ȂǁA���x���g���܂킵�A���I�u�W�F�N�g�������������ꍇ���ɗL���B�X�g�b�N�ƍl���Ă��ǂ��B<BR>
 * �܂��A��employ()�̏ꍇ�A����employ()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă��܂��B<BR>
 * (��RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class ActorDispatcher : public GgafCore::GgafDummyActor {

public:
    CollisionChecker* _pCollisionChecker;

    ActorDispatcher(const char* prm_name);

//    /**
//     * �ɂ����ȃA�N�^�[�����҃����o�[�iplay���A�܂���play�\�񂳂�Ă��Ȃ��j������΁A
//     * �A�N�^�[�����҂̈�Ԑ擪�Ɉړ������܂��B<BR>
//     * TODO:����͕��ׂ�������̂ł��܂��肽���Ȃ��ALaser�ȊO�͂Ȃ�ł������͂�
//     * ��OverRide �ł���<BR>
//     */
//    virtual void processBehavior() override {
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
     * �����o�[��o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�{�f�B�X�p�b�`���[�̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub);


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
     * �A�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����ȃ����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j������Ύ擾����B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[
     */
    virtual GgafCore::GgafMainActor* employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("ActorDispatcher::getFreeOne() �q������܂���");
        }
#endif
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        while(true) {
            if (pActor->isActive() || pActor->_is_active_flg_in_next_frame) {
                //���������A�����́A���t���[�������\��̏ꍇ�͌�����
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            } else {
                //pActor->activate(); //activate�͌Ăь��Ŗ����I�ɍs���悤�ɂ���
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
