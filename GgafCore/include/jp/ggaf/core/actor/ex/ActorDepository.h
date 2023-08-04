#ifndef GGAF_CORE_ACTORDEPOSITORY_H_
#define GGAF_CORE_ACTORDEPOSITORY_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include <typeinfo>
#include "jp/ggaf/core/actor/ex/DestructActor.h"

namespace GgafCore {

/**
 * �A�N�^�[�ۊǏ��i�l�ރo���N�j�N���X .
 * ���A�N�^�[�̎q�ɗ\�ߊ���A�N�^�[��o�^(appendChild)���ăX�g�b�N����B<BR>
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
class ActorDepository : public DestructActor {
private:
    //�g�p�s��
    void appendChild(Actor* prm_pChild) override {
    }

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     */
    ActorDepository(const char* prm_name);

    /**
     * �ݏo�����o�[(Actor)��ǉ��o�^���܂� .
     * �X�g�b�N�̒ǉ��I�ȃC���[�W�ł��B<BR>
     * Node<T>::appendChild() �����s����O�ɁA�A�N�^�[��ʂ̂������p�����s���܂��B
     * �ŏ��ɓo�^�����A�N�^�[�̎�ʂ��A�{�f�|�W�g���̎�ʂƂȂ�܂��B
     * ����ȍ~�͓�����ʂ̃A�N�^�[��o�^���鐧��������܂��B<BR>
     * �܂��A�����̃A�N�^�[�ɂ� inactivateImmed() �����s����A�����o�[�͔񊈓���Ԃɋ�������܂��B<BR>
     * @param prm_pChild �ݏo�����o�[�A�N�^�[
     */
    virtual void put(Actor* prm_pChild);

    /**
     * �ݏo�����o�[(�����^)����C�ɒǉ��o�^���܂�.
     * @param prm_num �����o�[��
     */
    template <typename T>
    void putn(const int prm_num) {
        const char* type = typeid(T).name();
        for (int i = 0; i < prm_num; i++) {
            std::string name = std::string(type) + "("+XTOS(i)+")";
            put(NEW T(name.c_str()));
        }
    }

    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ��悤�ɂ��� .
     * �q�A�N�^�[�i�݂��o�������o�[�j�́Adispatch() �ł̂݊�����Ԃɂ����邽�߁B
     */
    virtual void activateTree() override {
        activate();
    }

    /**
     * activate�n�͎q�A�N�^�[�ւ͉e�������Ȃ����� .
     * �q�A�N�^�[�i�݂��o�������o�[�j�́Adispatch() �ł̂݊�����Ԃɂ����邽�߁B
     */
    virtual void activateTreeDelay(frame prm_offset_frames) override {
        activateDelay(prm_offset_frames);
    }

    /**
     * �����o�[�؂��������݁A�؂����ł���Ύ擾��������Ԃɂ���B .
     * �ɂ����ȃ����o�[�i��active���A�܂���active�\�񂳂�Ă��Ȃ��j�����݂���΁A
     * �擾���A������Ԃɂ���i�x���ݒ�j�B<BR>
     * �ɂȃ����o�[�����Ȃ��ꍇ nullptr ���Ԃ�܂��B<BR>
     * �擾�ł���ꍇ�A�A�N�^�[�� activate()�����s����A�|�C���^��Ԃ��Ƌ��ɁA
     * ���̃A�N�^�[�̓A�N�^�[�����҂̎q�̈�Ԍ��Ɉړ�����܂��B<BR>
     * �ꎞ�I�ɃL������h������悤�ȃC���[�W<BR>
     * ���g�p�၄
     * <pre><code>
     * MainActor* pActor = pDepository->dispatch();
     * if (pActor) {
     *     //�A�N�^�[�̏�������
     *     //�E�E�E
     *
     * }
     * </code></pre>
     *
     * @param prm_offset_frames ������Ԃɂ���x���t���[��
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[�̃|�C���^
     */
    virtual MainActor* dispatch(int prm_offset_frames = 1) {
#ifdef MY_DEBUG
        if (_pChildFirst == nullptr) {
            throwCriticalException("this="<<NODE_INFO<<" �̎q������܂���");
        }
        if (_is_active_flg || _frame_of_life+1 == _frame_of_life_when_activation) {
            //�����t���O�������Ă��遨��薳��
            //���邢�́A���t���[���Ŋ����t���O�����\�聨�f�|�W�g�������������̓���t���[���������̂��ߋ���
        } else {
            //���R�R�ɗ���ꍇ�ŁA�z����p�^�[���͎��̂悤�ȏꍇ��
            //�@ ���[�U�[�`�b�v�̃Z�b�g�؂����ŁAActorDepositoryStore::dispatch() ���s���A�`�b�v�̃Z�b�g�̃f�|�W�g���𓾂����A�����Ɏg�p�����P�t���[���ȏ�ق��Ƃ�����A
            //   �����f�|�W�g������A�`�b�vdispatch()���悤�Ƃ����ꍇ�B
            //     �� ���̏ꍇ�A�ȉ��̌x�����b�Z�[�W���A���ŕ\������邱�ƂɂȂ�̂ŏC�����Ȃ���΂Ȃ�Ȃ��B
            throwCriticalException("this="<<NODE_INFO<<" ���񊈓��ȃf�|�W�g����dispatch()�������͋C�ł��B");
        }
#endif
        frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
        MainActor* pActor = (MainActor*)_pChildFirst;
        while (true) {
            if (pActor->_is_active_flg == false && pActor->isActivateScheduled() == false) {
                //�擾�I
                pActor->moveLast(); //���K�ɉ�
                pActor->activateDelay(offset_frames); //activate�������s�B
                break;
            } else {   //���������A�����́A���t���[�������\��̏ꍇ�͌�����
                if (pActor->_is_last_flg) {
                    pActor = nullptr;
                    break;
                } else {
                    pActor = (MainActor*)(pActor->_pNext);
                    continue;
                }
            }
        }
        //TODO:������onDispatch() �R�[���o�b�N�H
        return pActor;
    }

    /**
     * �����I�ɃA�N�^�[���o�� .
     * �A�N�^�[�����҂̉ɂ����Ȏq�����o�[�iactive���A�܂���active�\�񂳂�Ă��Ȃ��j��
     * ���Ȃ��ꍇ�́A�������̃����o�[�𖳗���艡��肵�Ď擾����B<BR>
     * dispatch() �����݂Ď��o���Ȃ��ꍇ�A�����I�Ƀ����o�[�B�̐擪�����o�[��Ԃ��܂��B<BR>
     * <b>�����Ӂ�</b><BR>
     * ���o����A�A�N�^�[�� active() �����s���Ă��A���̃A�N�^�[�����Ɋ�����Ԃ̉\��������A�܂�
     * isActiveInTheTree() �� true �̏�Ԃ����肤�邽�߁AonActive() �R�[���o�b�N�͌Ă΂�Ȃ��\��������B<BR>
     * �����ŁA������ inactivateImmed() �����s���A�������� onInctive() �R�[���o�b�N���Ăяo���Ă���B<BR>
     *
     * @param prm_offset_frames ������Ԃɂ���x���t���[��
     * @return �A�N�^�[�����҂̉ɂ����ȃ����o�[�A�N�^�[�̃|�C���^�A�����́A�擪�̃A�N�^�[
     */
    virtual MainActor* dispatchForce(int prm_offset_frames = 1) {
        MainActor* pActor = dispatch(prm_offset_frames);
        if (pActor == nullptr) {
            pActor = (MainActor*)getChildFirst(); //�����G�ɐ擪�擾
            pActor->moveLast(); //���K�ɉ�
            frame offset_frames = (prm_offset_frames < 1 ? 1 : prm_offset_frames);
            pActor->inactivateImmed(); //�����񊈐�
            pActor->onInactive();      //nextFrame() �ŌĂяo�����ׂ� onInactive() ���Ăяo����Ȃ��̂ŁA�����ŌĂ�
            pActor->activateDelay(offset_frames); //activate�������s�B
        }
        //TODO:������onDispatch() �R�[���o�b�N�H
        return pActor;
    }

    /**
     * ���Z�b�g���̏��� .
     * �����o�[��S��inactivateImmed()���܂��B
     */
    virtual void onReset() override;

    virtual void end(frame prm_offset_frames = 1) override;

    virtual ~ActorDepository() {
    }
};

}
#endif /*GGAF_CORE_ACTORDEPOSITORY_H_*/
