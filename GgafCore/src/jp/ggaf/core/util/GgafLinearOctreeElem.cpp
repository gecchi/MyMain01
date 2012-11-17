#include "stdafx.h"
using namespace GgafCore;


GgafLinearOctreeElem::GgafLinearOctreeElem(GgafObject* prm_pObject, UINT32 prm_kindbit) {
    _pSpace_current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctreeElem::clear() {
    if(_pSpace_current == NULL) {
        //_TRACE_("GgafLinearOctreeElem::extract() �ł��܂���B�Ӑ}���Ă܂����H");
        return;
    }
    //��񃊃Z�b�g
    UINT32 index = _pSpace_current->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    while(true) {
        if (paSpace[index]._kindinfobit == 0 ) {
            break;
        } else {
            paSpace[index]._kindinfobit = 0;
            paSpace[index]._pElem_first = NULL;
            paSpace[index]._pElem_last = NULL;
        }

        if (index == 0) {
            break;
        }
        // �e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
    _pNext = NULL;
    _pPrev = NULL;
    _pSpace_current = NULL;

//�v�f�͊e��ԂɃ��X�g�ɂԂ牺�����Ă��邽�߁Aclear() �̋@�\��{�����Y��Ɏ�������Ȃ�΁A
//������Ԃ� _kindinfobit �� XOR �Ȃǂ��ăr�b�g���A���Z�b�g���A
//_pElem_first�A_pElem_last �̃|�C���^�̍��i���X�g�j���������؂藣������������ׂ��ł���B
//�������A�ǂ��� clear() ���g�p����̂́A�S��ԑS�v�f�N���A����Ƃ������ł���̂ŁA
//_kindinfobit �́A�����l���� 0 ��ݒ�B���� _pElem_first �� _pElem_last �������Ȃ�NULL�ŃN���A�B
//�P���� clear() �Ƃ�����ƁA��ԏ��͕���邱�Ƃ𒍈ӁA�A�v���P�[�V�������W�b�N���� clear() �͎g�p���Ȃ����ƁB
//��{�c���[�́A�o�^�ƁA�N���A�̂ݍs���Ƃ����݌v
}

void GgafLinearOctreeElem::belongTo(GgafLinearOctreeSpace* prm_pSpace_target) {
    if (_pSpace_current == prm_pSpace_target) {
        //_TRACE_("belongTo����ł���");
        return;
    } else {
        if (prm_pSpace_target->_pElem_first == NULL) {
            //�P�Ԗڂɒǉ��̏ꍇ
            prm_pSpace_target->_pElem_first = this;
            prm_pSpace_target->_pElem_last = this;
            _pNext = NULL;
            _pPrev = NULL;
            _pSpace_current = prm_pSpace_target;
        } else {
            //�����ɒǉ��̏ꍇ
            prm_pSpace_target->_pElem_last->_pNext = this;
            _pPrev = prm_pSpace_target->_pElem_last;
            _pNext = NULL;
            prm_pSpace_target->_pElem_last = this;
            _pSpace_current = prm_pSpace_target;
        }
    }
    //�����̗v�f�ԍ�
    UINT32 index = prm_pSpace_target->_my_index;
    GgafLinearOctreeSpace* paSpace = _pLinearOctree->_paSpace;
    //�e��Ԃ��ׂĂɗv�f��ʏ��𗬂�
    while(true) {
        paSpace[index]._kindinfobit |= this->_kindbit;
        if (index == 0) {
            break;
        }
        //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
}

void GgafLinearOctreeElem::dump() {
    _TEXT_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
