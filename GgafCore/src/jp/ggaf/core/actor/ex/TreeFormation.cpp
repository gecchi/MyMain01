#include "jp/ggaf/core/actor/ex/TreeFormation.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/util/Status.h"

using namespace GgafCore;

TreeFormation::TreeFormation(const char* prm_name, frame prm_offset_frames_end) :
        Formation(prm_name, prm_offset_frames_end)
{
    _class_name = "TreeFormation";
    _pIte = nullptr;
    _can_summon = true;
    _is_append_member_experienced = false;
}

void TreeFormation::appendFormationMember(Actor* prm_pChild) {
#ifdef MY_DEBUG
    if (wasDeclaredEnd()) {
        //�I����҂̂�
        _TRACE_("�y�x���z TreeFormation::appendChild("<<NODE_INFO_P(prm_pChild)<<") ���Ɏ��ɂ䂭��߂�Formation�ł��B�q�ɒǉ����邱�Ƃ͂��������̂ł͂Ȃ����H�����̂��H�Bthis="<<NODE_INFO);
    }
#endif
    _num_formation_member++;
//    if (_pChildFirst == nullptr) {
//        //�c���Ɏ�ʂ𐳂����`���邽�߂ɁA����ǉ��̎�ʂ��A���g�̎�ʂɏ㏑�iTreeFormation�j������
//        //kind_t kind = prm_pChild->getCheckerKind();
//        //getStatus()->set(STAT_DEFAULT_ACTOR_KIND, kind);
//        setDefaultKind(prm_pChild->getCheckerKind());
//    } else {
//#ifdef MY_DEBUG
//        if (getCheckerKind() != prm_pChild->getCheckerKind()) {
//            throwCriticalException("�قȂ��ʂ̃A�N�^�[��o�^���悤�Ƃ��Ă��܂��B \n"
//                                       "�z��="<<getCheckerKind()<<"[_pChildFirst="<<_pChildFirst->getName()<<"] \n"
//                                       "����="<<prm_pChild->getCheckerKind()<<"["<<prm_pChild->getName()<<"]");
//        }
//#endif
//    }
    prm_pChild->_pFormation = this; //�����o�[�փt�H�[���[�V������ݒ�
    Formation::appendChild(prm_pChild);
    prm_pChild->inactivate(); //�t�H�[���[�V�����Ȃ̂�summon�܂Ŕ񊈓��B
    _is_append_member_experienced = true;
}

void TreeFormation::processFinal() {
    if (_was_all_sayonara || wasDeclaredEnd() || isInactivateScheduled()) {
        //�I����҂̂�
    } else {
        if (getChildFirst() == nullptr) {  //�z�����Ȃ��ꍇ�A�t�H�[���[�V�����͂Ȃ��������ƂɂȂ�A���g���I�����ȁH
            if (_is_append_member_experienced) {
                onSayonaraAll(); //�R�[���o�b�N
                sayonara(_offset_frames_end);
                _was_all_sayonara = true;
            } else {
                //�����������A�܂�����appendFormationMember()���o�����Ă��Ȃ��̂ŏI�����Ȃ��B
                //TreeFormation�Ƃ��Ă̖������ʂ����܂ł͎��˂Ȃ��B
            }
        }
    }
}

void TreeFormation::onEnd() {
    Formation::onEnd();
}

Actor* TreeFormation::summonMember(int prm_formation_child_num) {
    if (wasDeclaredEnd() || isInactivateScheduled()) {
        //�I����҂̂�
        return nullptr;
    }
    if (prm_formation_child_num > 0) {


        if (_can_summon) {
            if (_pIte) {
                //����ȍ~�� next
                _pIte = _pIte->getNext();
            } else {
                //����͎q�擪
                _pIte = getChildFirst();
                if (!_pIte) {
                    //�����o�[���ǉ�����ĂȂ�
                    _TRACE_("�y�x���z TreeFormation::summonMember() �����o�[���ǉ�����Ă܂���B���������̂ł́H�Bthis="<<NODE_INFO);
                    _can_summon = false; //���񂩂� summonMember() �s��
                    _num_formation_member = 0;
                    return nullptr;
                }
            }

            _num_summon++;
            _pIte->activate();

            if (_pIte->getNext() == getChildFirst()) {
                //�Ō�̂P��
                _can_summon = false; //���񂩂� summonMember() �s��
                _num_formation_member = _num_summon; //destroyedFollower �ґ��S�Ŕ���̈׍Đݒ�
            }
            if (prm_formation_child_num <= _num_summon) {
                //������ɒB����
                _can_summon = false; //���񂩂� summonMember() �s��
                _num_formation_member = _num_summon; //destroyedFollower �ґ��S�Ŕ���̈׍Đݒ�
            }

            return _pIte;
        } else {
            return nullptr;
        }
    } else {
        _can_summon = false; //���񂩂� summonMember() �s��
        _num_formation_member = _num_summon; //destroyedFollower �ґ��S�Ŕ���̈׍Đݒ�
        return nullptr;
    }
}

TreeFormation::~TreeFormation() {

}
