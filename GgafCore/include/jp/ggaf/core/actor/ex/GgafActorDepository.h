#ifndef GGAFACTORDEPOSITORY_H_
#define GGAFACTORDEPOSITORY_H_
namespace GgafCore {

/**
 * �A�N�^�[�ۊǏ��i�l�ރo���N�j�N���X .
 * ���A�N�^�[�̃T�u�ɗ\�ߊ���A�N�^�[��o�^(addSubLast)���ăX�g�b�N����B<BR>
 * dispatch() ���\�b�h���Ăяo�����ƁA�f�|�W�g�����̊������Ă��Ȃ��A�N�^�[�T���Ē񋟂���B<BR>
 * �A�N�^�[�͎g���I�������inactivate()����ƁA�X�g�b�N�ɖ߂������ƂɂȂ�B<BR>
 * �e�Ȃǉ��x���g���܂킵�����A�N�^�[��A�o���������������ꍇ���ɗL���ƂȂ�n�Y�ł���B<BR>
 * �A�� dispatch() �̏ꍇ�A����dispatch()�̃A�N�^�[�K���c���[�̗ד��m�ƂȂ��Ă���Ƃ����@��������B<BR>
 * ����́Adispatch() �����A�N�^�[�́A�X�g�b�N���т̈�ԍŌ�ɉ񂳂�邽�߁B<BR>
 * �|�����C���i���[�U�[�j�̂ЂƓZ�܂�̒P�ʂƂ��Ďg�p�ł��邩������Ȃ��A�Ɩژ_�ށB<BR>
 * (��RotationActor)
 * @version 1.00
 * @since 2008/08/11
 * @author Masatoshi Tsuge
 */
class GgafActorDepository : public GgafDummyActor {
public:
//    GgafCore::GgafLinkedListRing<GgafActor> _listDispatched;

    GgafActorDepository(const char* prm_name, GgafStatus* prm_pStat = NULL);

    /**
     * �ݏo�����o�[(GgafActor)��ǉ��o�^���܂�.
     * �X�g�b�N�̒ǉ��I�ȃC���[�W�ł��B<BR>
     * GgafNode<T>::addSubLast() �����s����O�ɁA�A�N�^�[��ʂ̂������p�����s���܂��B
     * �ŏ��ɓo�^�����A�N�^�[�̎�ʂ��A�{�f�|�W�g���̎�ʂƂȂ�܂��B
     * ����ȍ~�͓�����ʂ̃A�N�^�[��o�^���鐧��������܂��B<BR>
     * �܂��A�����̃A�N�^�[�ɂ� inactivateImmed() �����s����A�����o�[�͔񊈓���Ԃɋ�������܂��B<BR>
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
     * �����o�[�؂��������݁A�؂����ł���Ύ擾��������Ԃɂ���B .
     * �ɂ����ȃ����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j�����݂���΁A
     * �擾���A������Ԃɂ���i�x���ݒ�j�B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ NULL ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�A�N�^�[�� activate()�����s����A�|�C���^��Ԃ��Ƌ��ɁA
     * ���̃A�N�^�[�̓A�N�^�[�����҂̃T�u�̈�Ԍ��Ɉړ�����܂��B<BR>
     * �ꎞ�I�ɃL������h������悤�ȃC���[�W<BR>
     * ���g�p�၄
     * <pre><code>
     * GgafMainActor* pActor = pDepository->dispatch();
     * if (pActor) {
     *     //�A�N�^�[�̏�������
     *     //�E�E�E
     *
     * }
     *
     * </code></pre>
     *
     * @param prm_offset_frames ������Ԃɂ���x���t���[��
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[�̃|�C���^
     */
    virtual GgafCore::GgafMainActor* dispatch(int prm_offset_frames = 1) {
#ifdef MY_DEBUG
        if (_pSubFirst == NULL) {
            throwGgafCriticalException("GgafActorDepository::dispatch() this="<<getName()<<"("<<this<<") �̎q������܂���");
        }
        if (_is_active_flg == true || (_will_activate_after_flg == true && _frame_of_life+1 == _frame_of_life_when_activation)) {
            //�����t���O�������Ă��� ���邢�́A���t���[���Ŋ����t���O�����\��Ȃ��OK
        } else {
            throwGgafCriticalException("GgafActorDepository::dispatch() this="<<getName()<<"("<<this<<") ���񊈓��ȕ��͋C�ł��B���������̂ł͂Ȃ����H�I \n"<<
                                       "�e�� GgafActorDepositoryStore::dispatch() �œ����f�|�W�����A�����Ɏg�p�����ق��Ƃ����\����B");
        }
#endif
        frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
        GgafMainActor* pActor = getSubFirst();
        while (true) {
            if (pActor->_is_active_flg == false && pActor->_will_activate_after_flg == false) {
                pActor->moveLast(); //���t���[�����K�ɉ�
                pActor->activateDelay(offset_frames); //activate�������s�B
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
     * isActiveInTheTree() == true �̏�Ԃ����肤�邽�߁AonActive() �R�[���o�b�N��
     * �Ă΂�Ȃ��\��������B<BR>
     * �����I��onActive() �R�[���o�b�N���Ăяo�������ꍇ�Ɏ��̂悤�ȃR�[�h��
     * ���Ȃ���΂����Ȃ������m��Ȃ��B
     * <pre><code>
     * GgafMainActor* pActor = pDepository->dispatchForce();
     * if (pActor->isActiveInTheTree()) {
     *     pActor->inactivateImmed();
     *     pActor->onActive();
     * }
     * pActor->active();
     * </code></pre>
     *
     * @param prm_offset_frames ������Ԃɂ���x���t���[��
     * @return
     */
    virtual GgafCore::GgafMainActor* dispatchForce(frame prm_offset_frames = 1) {
        GgafMainActor* pActor = dispatch(prm_offset_frames);
        if (pActor == NULL) {
            getSubFirst()->moveLastImmed(); //���K�ɉ�
            pActor = getSubFirst();
        }
        return pActor;
    }

    /**
     * ���Z�b�g���̏��� .
     * �����o�[��S��inactivateImmed()���܂��B
     */
    virtual void onReset() override;

    virtual void end(frame prm_offset_frames = 1) override;

    virtual ~GgafActorDepository() {
    }
};

}
#endif /*GGAFACTORDEPOSITORY_H_*/
