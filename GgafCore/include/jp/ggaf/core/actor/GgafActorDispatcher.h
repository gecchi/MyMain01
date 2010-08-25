#ifndef ACTORDISPATCHER_H_
#define ACTORDISPATCHER_H_
namespace GgafCore {

/**
 * �A�N�^�[�f�B�X�p�b�`���[�i�����ҁj�N���X .
 * ���A�N�^�[�̃T�u�ɗ\�ߊ���A�N�^�[��o�^(addSubLast)���ăX�g�b�N����B<BR>
 * ������� employ() ���\�b�h�ŁA�X�g�b�N�̊������Ă��Ȃ��A�N�^�[�T���Ē񋟂���B<BR>
 * �A�N�^�[�͎g���I�������inactivate()����ƁA�X�g�b�N�ɖ߂������ƂɂȂ�B<BR>
 * �e�Ȃǉ��x���g���܂킵�����A�N�^�[��A�o���������������ꍇ���ɗL���ƂȂ�n�Y�ł���B<BR>
 * �A��employ()�̏ꍇ�A����employ()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă���Ƃ����@��������B<BR>
 * ����́Aemploy()�����A�N�^�[�́A�X�g�b�N���т̈�ԍŌ�ɉ񂳂�邽�߁B<BR>
 * �|�����C���i���[�U�[�j�̂ЂƓZ�܂�̒P�ʂƂ��Ďg�p�ł��邩������Ȃ��A�Ɩژ_�ށB<BR>
 * (��RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDispatcher : public GgafDummyActor {

public:
    GgafActorDispatcher(const char* prm_name);

    /**
     * �����o�[��o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * �ŏ��ɓo�^�����A�N�^�[���A�{�f�B�X�p�b�`���[�̎�ʂƂȂ邽�߁A������ʂ�addSubLast���Ă��������B
     * @param prm_pSub �o�^�A�N�^�[
     */
    virtual void addSubLast(GgafActor* prm_pSub);


    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ�
     */
    virtual void activateTree() override {
        activate();
    }

//    virtual void inactivateTree() override {
//        inactivate();
//    }
    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ�
     */
    virtual void activateTreeAfter(frame prm_frame_offset) override {
        activateAfter(prm_frame_offset);
    }

//    virtual void inactivateTreeAfter(frame prm_frame_offset) override {
//        inactivateAfter(prm_frame_offset);
//    }

    /**
     * �A�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����ȃT�u�����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j������Ύ擾����B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * �ꎞ�I�ɃL������h������悤�ȃC���[�W<BR>
     * ���g�p�၄
     * <pre><code>
     * GgafMainActor* pActor = pDispatcher->employ();
     * if (pActor != NULL) {
     *     //�A�N�^�[�̏�������
     *     //�E�E�E
     *
     *     pActor->active();
     * }
     *
     * </code></pre>
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[
     */
    virtual GgafCore::GgafMainActor* employ() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcher::employ() "<<getName()<<" �̎q������܂���");
        }
#endif
        static GgafMainActor* pActor;
        pActor = getSubFirst();

        for (int i = 0; i <= 100000; i++) {
            if (pActor->_is_active_flg == false &&  pActor->_is_active_flg_in_next_frame == false &&  pActor->_on_change_to_inactive_flg == false) {
                //pActor->activate(); //activate�͌Ăь��Ŗ����I�ɍs���悤�ɂ���
                pActor->moveLast(); //���K�ɉ�
                break;//�擾�I
            } else {   //���������A�����́A���t���[�������\��̏ꍇ�͌�����
                if (pActor->isLast()) {
                    pActor = NULL;
                    break;
                } else {
                    pActor = pActor->getNext();
                    continue;
                }
            }
#ifdef MY_DEBUG
            if (i == 100000) {
                throwGgafCriticalException("GgafActorDispatcher::employ() "<<getName()<<" �̃����o�̖����t���O��������܂���B�z���[�v���Ă���\��������܂��B");
            }
#endif
        }
        return pActor;
    }

    /**
     * �����I�ɃA�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����ȃT�u�����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j��
     * ���Ȃ��Ă������I�Ɏ擾����B<BR>
     * employ() �����݂Ď��o���Ȃ��ꍇ�A�����I�ɐ擪�̃A�N�^�[��Ԃ��܂��B<BR>
     * <b>�����Ӂ�</b><BR>
     * ���o����A�A�N�^�[�� active() �����s���Ă��A���̃A�N�^�[������
     * isActive() == true �̏�Ԃ����肤�邽�߁AonActive() �R�[���o�b�N��
     * �Ă΂�Ȃ��\��������B<BR>
     * �����I��onActive() �R�[���o�b�N���Ăяo�������ꍇ�Ɏ��̂悤�ȃR�[�h��
     * ���Ȃ���΂����Ȃ������m��Ȃ��B
     * <pre><code>
     * GgafMainActor* pActor = pDispatcher->employForce();
     * if (pActor->isActive()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @return
     */
    virtual GgafCore::GgafMainActor* employForce() {
        GgafMainActor* pActor = employ();
        if (pActor == NULL) {
            pActor = getSubFirst();
        }
        return pActor;

    }

    virtual ~GgafActorDispatcher() {
    }
};

}
#endif /*ACTORDISPATCHER_H_*/
