#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"

using namespace GgafCore;

GgafLinearOctreeElem::GgafLinearOctreeElem(GgafLinearOctreeOctant* prm_paLinearOctant, GgafObject* prm_pObject, uint32_t prm_kindbit) : GgafObject() ,
        _paLinearOctant(prm_paLinearOctant),
    _pObject(prm_pObject)
{
    _kindbit = prm_kindbit;
    _pOctant_current = nullptr;
    _pNext = nullptr;
    _pPrev = nullptr;
    _pRegLinkNext = nullptr;
}

void GgafLinearOctreeElem::clear() {
    if(_pOctant_current == nullptr) {
        //_TRACE_(FUNC_NAME<<" �ł��܂���B�Ӑ}���Ă܂����H");
        return;
    }
    //��񃊃Z�b�g
    uint32_t index = _pOctant_current->_my_index;
//    GgafLinearOctreeOctant* paOctant = _pLinearOctree->_paLinearOctant;
    while (true) {
        if (_paLinearOctant[index]._kindinfobit == 0 ) {
            break;
        } else {
            _paLinearOctant[index]._kindinfobit = 0;
            _paLinearOctant[index]._pElem_first = nullptr;
            _paLinearOctant[index]._pElem_last = nullptr;
        }

        if (index == 0) {
            break;
        }
        // �e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
    _pNext = nullptr;
    _pPrev = nullptr;
    _pOctant_current = nullptr;

//�v�f�͊e��ԂɃ��X�g�ɂԂ牺�����Ă��邽�߁Aclear() �̋@�\��{�����Y��Ɏ�������Ȃ�΁A
//������Ԃ� _kindinfobit �� XOR �Ȃǂ��ăr�b�g���A���Z�b�g���A
//_pElem_first�A_pElem_last �̃|�C���^�̍��i���X�g�j���������؂藣������������ׂ��ł���B
//�������A�ǂ��� clear() ���g�p����̂́A�S��ԑS�v�f�N���A����Ƃ������ł���̂ŁA
//_kindinfobit �́A�����l���� 0 ��ݒ�B���� _pElem_first �� _pElem_last �������Ȃ�nullptr�ŃN���A�B
//�P���� clear() �Ƃ�����ƁA��ԏ��͕���邱�Ƃ𒍈ӁA�A�v���P�[�V�������W�b�N���� clear() �͎g�p���Ȃ����ƁB
//��{�c���[�́A�o�^�ƁA�N���A�̂ݍs���Ƃ����݌v
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeOctant* const prm_pOctant_target) {
    if (_pOctant_current == prm_pOctant_target) {
        //_TRACE_("belongTo����ł���");
        return;
    } else {
        if (prm_pOctant_target->_pElem_first == nullptr) {
            //�P�Ԗڂɒǉ��̏ꍇ
            prm_pOctant_target->_pElem_first = this;
            prm_pOctant_target->_pElem_last = this;
//nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            _pNext = nullptr;
//            _pPrev = nullptr;
            _pOctant_current = prm_pOctant_target;
        } else {
            //�����ɒǉ��̏ꍇ
            prm_pOctant_target->_pElem_last->_pNext = this;
            _pPrev = prm_pOctant_target->_pElem_last;
//nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            _pNext = nullptr;
            prm_pOctant_target->_pElem_last = this;
            _pOctant_current = prm_pOctant_target;
        }
    }
    //�����̗v�f�ԍ�
    uint32_t index = prm_pOctant_target->_my_index;
//    GgafLinearOctreeOctant* const paOctant = _pLinearOctree->_paLinearOctant;
    const uint32_t this_kindbit = this->_kindbit;
    //�e��Ԃ��ׂĂɗv�f��ʏ��𗬂�
    while (true) {
        if (_paLinearOctant[index]._kindinfobit & this_kindbit) {
            //������ʏ�񂪐ݒ�ς݂Ȃ�΁A����ȏ�̐e���ݒ�ςׁ݂̈A������
            break;
        } else {
            //��ԂɎ�ʏ�񂪖��ݒ�Ȃ�ΐݒ�
            _paLinearOctant[index]._kindinfobit |= this_kindbit;
        }
        if (index == 0) {
            break;
        }
        //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
}

void GgafLinearOctreeElem::dump() {
    _TRACE_N_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
