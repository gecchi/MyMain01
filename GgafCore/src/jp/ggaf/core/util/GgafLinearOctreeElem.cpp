#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

#include "jp/ggaf/core/util/GgafLinearOctreeSpace.h"
#include "jp/ggaf/core/util/GgafLinearOctree.h"

using namespace GgafCore;

GgafLinearOctreeElem::GgafLinearOctreeElem(GgafLinearOctree* prm_pLinearOctree, GgafObject* prm_pObject, uint32_t prm_kindbit) : GgafObject() ,
    _pLinearOctree(prm_pLinearOctree),
    _pObject(prm_pObject)
{
    _kindbit = prm_kindbit;
    _pSpace_current = nullptr;
    _pNext = nullptr;
    _pPrev = nullptr;
    _pRegLinkNext = nullptr;
}

void GgafLinearOctreeElem::clear() {
    if(_pSpace_current == nullptr) {
        //_TRACE_("GgafLinearOctreeElem::extract() �ł��܂���B�Ӑ}���Ă܂����H");
        return;
    }
    //��񃊃Z�b�g
    uint32_t index = _pSpace_current->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    while (true) {
        if (paSpace[index]._kindinfobit == 0 ) {
            break;
        } else {
            paSpace[index]._kindinfobit = 0;
            paSpace[index]._pElem_first = nullptr;
            paSpace[index]._pElem_last = nullptr;
        }

        if (index == 0) {
            break;
        }
        // �e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
    _pNext = nullptr;
    _pPrev = nullptr;
    _pSpace_current = nullptr;

//�v�f�͊e��ԂɃ��X�g�ɂԂ牺�����Ă��邽�߁Aclear() �̋@�\��{�����Y��Ɏ�������Ȃ�΁A
//������Ԃ� _kindinfobit �� XOR �Ȃǂ��ăr�b�g���A���Z�b�g���A
//_pElem_first�A_pElem_last �̃|�C���^�̍��i���X�g�j���������؂藣������������ׂ��ł���B
//�������A�ǂ��� clear() ���g�p����̂́A�S��ԑS�v�f�N���A����Ƃ������ł���̂ŁA
//_kindinfobit �́A�����l���� 0 ��ݒ�B���� _pElem_first �� _pElem_last �������Ȃ�nullptr�ŃN���A�B
//�P���� clear() �Ƃ�����ƁA��ԏ��͕���邱�Ƃ𒍈ӁA�A�v���P�[�V�������W�b�N���� clear() �͎g�p���Ȃ����ƁB
//��{�c���[�́A�o�^�ƁA�N���A�̂ݍs���Ƃ����݌v
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeSpace* const prm_pSpace_target) {
    if (_pSpace_current == prm_pSpace_target) {
        //_TRACE_("belongTo����ł���");
        return;
    } else {
        if (prm_pSpace_target->_pElem_first == nullptr) {
            //�P�Ԗڂɒǉ��̏ꍇ
            prm_pSpace_target->_pElem_first = this;
            prm_pSpace_target->_pElem_last = this;
//nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            _pNext = nullptr;
//            _pPrev = nullptr;
            _pSpace_current = prm_pSpace_target;
        } else {
            //�����ɒǉ��̏ꍇ
            prm_pSpace_target->_pElem_last->_pNext = this;
            _pPrev = prm_pSpace_target->_pElem_last;
//nullptr��clear���ݒ�ς݁B�ȗ����Ă����v�Ȃ͂��B
//            _pNext = nullptr;
            prm_pSpace_target->_pElem_last = this;
            _pSpace_current = prm_pSpace_target;
        }
    }
    //�����̗v�f�ԍ�
    uint32_t index = prm_pSpace_target->_my_index;
    GgafLinearOctreeSpace* const paSpace = _pLinearOctree->_paSpace;
    const uint32_t this_kindbit = this->_kindbit;
    //�e��Ԃ��ׂĂɗv�f��ʏ��𗬂�
    while (true) {
        if (paSpace[index]._kindinfobit & this_kindbit) {
            //������ʏ�񂪐ݒ�ς݂Ȃ�΁A����ȏ�̐e���ݒ�ςׁ݂̈A������
            break;
        } else {
            //��ԂɎ�ʏ�񂪖��ݒ�Ȃ�ΐݒ�
            paSpace[index]._kindinfobit |= this_kindbit;
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
