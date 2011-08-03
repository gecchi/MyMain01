#ifndef GGAFACTORSTORE_H_
#define GGAFACTORSTORE_H_
namespace GgafCore {

/**
 * �A�N�^�[�X�g�A�[�i�l�ރo���N�j�N���X .
 * ���A�N�^�[�̃T�u�ɗ\�ߊ���A�N�^�[��o�^(addSubLast)���ăX�g�b�N����B<BR>
 * ������� dispatch() ���\�b�h�ŁA�X�g�b�N�̊������Ă��Ȃ��A�N�^�[�T���Ē񋟂���B<BR>
 * �A�N�^�[�͎g���I�������inactivate()����ƁA�X�g�b�N�ɖ߂������ƂɂȂ�B<BR>
 * �e�Ȃǉ��x���g���܂킵�����A�N�^�[��A�o���������������ꍇ���ɗL���ƂȂ�n�Y�ł���B<BR>
 * �A��dispatch()�̏ꍇ�A����dispatch()�̃A�N�^�[�͕K���ד��m�ƂȂ��Ă���Ƃ����@��������B<BR>
 * ����́Adispatch()�����A�N�^�[�́A�X�g�b�N���т̈�ԍŌ�ɉ񂳂�邽�߁B<BR>
 * �|�����C���i���[�U�[�j�̂ЂƓZ�܂�̒P�ʂƂ��Ďg�p�ł��邩������Ȃ��A�Ɩژ_�ށB<BR>
 * (��RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorStore : public GgafDummyActor {
public:

    GgafActorStore(const char* prm_name);

    /**
     * �ݏo�����o�[(GgafActor)��ǉ��o�^���܂�.
     * �X�g�b�N�̒ǉ��I�ȃC���[�W�ł��B<BR>
     * GgafNode<T>::addSubLast() �����s����O�ɁA�A�N�^�[��ʂ̂������p�����s���܂��B
     * �ŏ��ɓo�^�����A�N�^�[�̎�ʂ��A�{�X�g�A�[�̎�ʂƂȂ�܂��B
     * ����ȍ~�͓�����ʂ̃A�N�^�[��o�^���鐧��������܂��B<BR>
     * �܂��A�����̃A�N�^�[�ɂ� inactivateImmediately() �����s����A�����o�[�͔񊈓���Ԃɋ�������܂��B<BR>
     * @param prm_pSub �ݏo�����o�[�A�N�^�[
     */
    virtual void addSubLast(GgafActor* prm_pSub) override;


    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ��悤�ɂ��� .
     * �q�A�N�^�[�i�݂��o�������o�[�j�́Adispatch() �ł̂݊�����Ԃɂ����邽�߁B
     */
    virtual void activateTree() override {
        activate();
    }

//    virtual void inactivateTree() override {
//        inactivate();
//    }
    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ����� .
     * �q�A�N�^�[�i�݂��o�������o�[�j�́Adispatch() �ł̂݊�����Ԃɂ����邽�߁B
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        activateDelay(prm_offset_frames);
    }

//    virtual void inactivateTreeDelay(frame prm_offset_frames) override {
//        inactivateDelay(prm_offset_frames);
//    }

    /**
     * �����o�[�؂���� .
     * �ɂ����ȃ����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j�����݂���΁A�擾��������Ԃɂ���B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�A�N�^�[�� activate()�����s����A�|�C���^��Ԃ��Ƌ��ɁA���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * �ꎞ�I�ɃL������h������悤�ȃC���[�W<BR>
     * ���g�p�၄
     * <pre><code>
     * GgafMainActor* pActor = pStore->dispatch();
     * if (pActor) {
     *     //�A�N�^�[�̏�������
     *     //�E�E�E
     *
     * }
     *
     * </code></pre>
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[
     */
    virtual GgafCore::GgafMainActor* dispatch() {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorStore::dispatch() "<<getName()<<" �̎q������܂���");
        }
#endif
        GgafMainActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                pActor->moveLast(); //���t���[�����K�ɉ�
                pActor->activate(); //activate�������s�B
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
        }
        return pActor;
    }

    /**
     * �����I�ɃA�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����ȃT�u�����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j��
     * ���Ȃ��ꍇ�́A�������̃����o�[�𖳗����擾����B<BR>
     * dispatch() �����݂Ď��o���Ȃ��ꍇ�A�����I�Ƀ����o�[�B�̐擪�����o�[��Ԃ��܂��B<BR>
     * <b>�����Ӂ�</b><BR>
     * ���o����A�A�N�^�[�� active() �����s���Ă��A���̃A�N�^�[������
     * isActiveActor() == true �̏�Ԃ����肤�邽�߁AonActive() �R�[���o�b�N��
     * �Ă΂�Ȃ��\��������B<BR>
     * �����I��onActive() �R�[���o�b�N���Ăяo�������ꍇ�Ɏ��̂悤�ȃR�[�h��
     * ���Ȃ���΂����Ȃ������m��Ȃ��B
     * <pre><code>
     * GgafMainActor* pActor = pStore->dispatchForce();
     * if (pActor->isActiveActor()) {
     *     pActor->inactivateImmediately();
     *     pActor->onInactive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @return
     */
    virtual GgafCore::GgafMainActor* dispatchForce() {
        GgafMainActor* pActor = dispatch();
        if (pActor == NULL) {
            getSubFirst()->moveLastImmediately(); //���K�ɉ�
            pActor = getSubFirst();
        }
        return pActor;
    }

    /**
     * ���Z�b�g���̏��� .
     * �����o�[��S��inactivateImmediately()���܂��B
     */
    virtual void onReset() override;

    virtual ~GgafActorStore() {
    }
};

}
#endif /*GGAFACTORSTORE_H_*/
