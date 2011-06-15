#ifndef GGAFACTORDISPATCHERDISPATCHER_H_
#define GGAFACTORDISPATCHERDISPATCHER_H_
namespace GgafCore {

/**
 * �A�N�^�[�f�B�X�p�b�`���[�̃p�b�`���[�N���X .
 * GgafActorDispatcher �́A�T�u�̓o�^�A�N�^�[(GgafActor)���ɂ����ȃ����o�[�� employ() ����̂ɑ΂��A
 * GgafActorDispatcherDispatcher �́A�T�u�̓o�^�f�B�X�p�b�`���[(GgafActorDispatcher) �� �o�^�A�N�^�[(GgafActor)���A
 * �S���ɂ��Ă���f�B�X�p�b�`���[��D��I��employ() ����B
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDispatcherDispatcher : public GgafActorDispatcher {

private :

    virtual void addSubLast(GgafActor* prm_pSub) override;

public:
    GgafActorDispatcherDispatcher(const char* prm_name);

    /**
     * �f�B�X�p�b�`���[��o�^���܂�.
     * ��̓I�ɂ́AaddSubLast() ���Ăяo���A��ʂ������p���܂��B
     * ���̂��߁A�o�^�A�N�^�[�ς݃f�B�X�p�b�`���[��o�^���ĉ������B
     * @param prm_pSub �o�^�f�B�X�p�b�`���[
     */
    virtual void addSubLast(GgafActorDispatcher* prm_pSub) {
        addSubLast((GgafActor*)prm_pSub);
    }


    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ�������߂�B
     */
    virtual void activateTree() override {
        //�Q��̌p�����̖{����activateTree()�����s
        GgafDummyActor::activateTree();
    }

//    virtual void inactivateTree() override {
//        inactivate();
//    }
    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ�������߂�B
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        //�Q��̌p�����̖{����activateTree()�����s
        GgafDummyActor::activateTreeDelay();
    }

//    virtual void inactivateTreeDelay(frame prm_offset_frames) override {
//        inactivateDelay(prm_offset_frames);
//    }

    /**
     * �f�B�X�p�b�`���[���o�� .
     * �ɂ����ȃf�B�X�p�b�`���[�i�o�^�����o�[���S�ĉɂȃf�B�X�p�b�`���[�j������Ύ擾����B<BR>
     * �ɂ����ȃf�B�X�p�b�`���[���Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�|�C���^��Ԃ��Ƌ��ɁA���̃f�B�X�p�b�`���[�̓T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * ���g�p�၄
     * <pre><code>
     * GgafActorDispatcher* pDispatcher = pDispatcherDispatcher->employ();
     * if (pDispatcher) {
     *     GgafMainActor* pActor = pDispatcher->employ();
     *     if (pActor) {
     *         //�A�N�^�[�̏�������
     *         //�E�E�E
     *
     *         pActor->active();
     *     }
     * }
     *
     * </code></pre>
     * @return �ɂ����ȃf�B�X�p�b�`���[ or NULL
     */
    virtual GgafActorDispatcher* employ() override {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDispatcherDispatcher::employ() "<<getName()<<" �̎q������܂���");
        }
#endif
        GgafActorDispatcher* pDispatcher = (GgafActorDispatcher*)getSubFirst();
        for (int i = 0; i <= 100000; i++) {
            if (pDispatcher->_active_member == 0) {
                pDispatcher->moveLast(); //���K�ɉ�
                _active_member++;
                break;//�擾�I
            } else {
                if (pDispatcher->isLast()) {
                    pDispatcher = NULL;
                    break;
                } else {
                    pDispatcher = (GgafActorDispatcher*)(pDispatcher->getNext());
                    continue;
                }
            }
#ifdef MY_DEBUG
            if (i == 100000) {
                throwGgafCriticalException("GgafActorDispatcherDispatcher::employ() "<<getName()<<" �̃����o�̖����t���O��������܂���B�z���[�v���Ă���\��������܂��B");
            }
#endif
        }
        return pDispatcher;
    }

    /**
     * �����I�ɃA�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����ȃT�u�����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j��
     * ���Ȃ��Ă������I�Ɏ擾����B<BR>
     * employ() �����݂Ď��o���Ȃ��ꍇ�A�����I�ɐ擪�̃A�N�^�[��Ԃ��܂��B<BR>
     * <b>�����Ӂ�</b><BR>
     * ���o����A�A�N�^�[�� active() �����s���Ă��A���̃A�N�^�[������
     * isActiveActor() == true �̏�Ԃ����肤�邽�߁AonActive() �R�[���o�b�N��
     * �Ă΂�Ȃ��\��������B<BR>
     * �����I��onActive() �R�[���o�b�N���Ăяo�������ꍇ�Ɏ��̂悤�ȃR�[�h��
     * ���Ȃ���΂����Ȃ������m��Ȃ��B
     * <pre><code>
     * GgafMainActor* pActor = pDispatcherDispatcher->employForce();
     * if (pActor->isActiveActor()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @return
     */
    virtual GgafActorDispatcher* employForce() {
        GgafActorDispatcher* pDispatcher = employ();
        if (pDispatcher == NULL) {
            getSubFirst()->moveLastImmediately(); //���K�ɉ�
            pDispatcher = (GgafActorDispatcher*)getSubFirst();
        }
        return pDispatcher;
    }

    /**
     * ���Z�b�g���̏��� .
     */
    virtual void onReset() override {

    }

    virtual ~GgafActorDispatcherDispatcher() {
    }
};

}
#endif /*GGAFACTORDISPATCHERDISPATCHER_H_*/
