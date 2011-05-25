#include "stdafx.h"
using namespace std;
using namespace GgafCore;


GgafLinearOctreeElem::GgafLinearOctreeElem(GgafObject* prm_pObject, UINT32 prm_kindbit) {
    _pSpace_Current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctreeElem::extract() {
    if(_pSpace_Current == NULL) {
        //_TRACE_("GgafLinearOctreeElem::extract() �ł��܂���B�Ӑ}���Ă܂����H");
        return;
    }
    //��񃊃Z�b�g
    UINT32 index = _pSpace_Current->_my_index;
    while(true) {
        //��ł�extract()����Ə��͕���邱�Ƃ𒍈ӁA�A�v���P�[�V�������W�b�N����extract() �͎g�p���Ȃ����ƁB
        //��{�c���[�́A�o�^�ƁA�N���A�̂ݍs���Ƃ����݌v
        if (_pLinearOctree->_paSpace[index]._kindinfobit == 0 ) {
            break;
        } else {
            _pLinearOctree->_paSpace[index]._kindinfobit = 0;
            _pLinearOctree->_paSpace[index]._pElemFirst = NULL;
            _pLinearOctree->_paSpace[index]._pElemLast = NULL;
        }

        if (index == 0) {
            break;
        }
        // �e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
    _pNext = NULL;
    _pPrev = NULL;
    _pSpace_Current = NULL;

//    if (this == _pSpace_Current->_pElemFirst && this == _pSpace_Current->_pElemLast) {
//        //�擪�������̏ꍇ
//        _pSpace_Current->_pElemFirst = NULL;
//        _pSpace_Current->_pElemLast = NULL;
//        _pSpace_Current = NULL;
//    } else if (this == _pSpace_Current->_pElemFirst) {
//        //�擪�������ꍇ
//        _pSpace_Current->_pElemFirst = _pNext;
//        _pSpace_Current->_pElemFirst->_pPrev = NULL;
//        _pNext = NULL;
//        _pSpace_Current = NULL;
//    } else if (this == _pSpace_Current->_pElemLast) {
//        //�����������ꍇ
//        _pSpace_Current->_pElemLast = _pPrev;
//        _pSpace_Current->_pElemLast->_pNext = NULL;
//        _pPrev = NULL;
//        _pSpace_Current = NULL;
//    } else {
//        //���Ԃ������ꍇ
//        _pPrev->_pNext = _pNext;
//        _pNext->_pPrev = _pPrev;
//        _pNext = NULL;
//        _pPrev = NULL;
//        _pSpace_Current = NULL;
//    }
}

void GgafLinearOctreeElem::addElem(GgafLinearOctreeSpace* prm_pSpace_target) {
    if (_pSpace_Current == prm_pSpace_target) {
        //_TRACE_("addElem����ł���");
        return;
    } else {
        if (prm_pSpace_target->_pElemFirst == NULL) {
            //�P�Ԗڂɒǉ��̏ꍇ
            prm_pSpace_target->_pElemFirst = this;
            prm_pSpace_target->_pElemLast = this;
            _pNext = NULL;
            _pPrev = NULL;
            _pSpace_Current = prm_pSpace_target;
        } else {
            //�����ɒǉ��̏ꍇ
            prm_pSpace_target->_pElemLast->_pNext = this;
            _pPrev = prm_pSpace_target->_pElemLast;
            _pNext = NULL;
            prm_pSpace_target->_pElemLast = this;
            _pSpace_Current = prm_pSpace_target;
        }
    }
    //�����̗v�f�ԍ�
    UINT32 index = prm_pSpace_target->_my_index;
    //�e��Ԃ��ׂĂɗv�f��ʏ��𗬂�
    while(true) {
//        _pLinearOctree->_paSpace[index]._kindinfobit =
//                _pLinearOctree->_paSpace[index]._kindinfobit | this->_kindbit;
        _pLinearOctree->_paSpace[index]._kindinfobit |= this->_kindbit;
        if (index == 0) {
            break;
        }
        //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
}

//void GgafLinearOctreeElem::moveToSpace(GgafLinearOctreeSpace* prm_pSpace_target) {
//    if (prm_pSpace_target == _pSpace_Current) {
//        return; //�ړ�����ł���
//    } else {
//        if(_pSpace_Current) {
//            extract(); //�����܂���
//        }
//        addElem(prm_pSpace_target); //����܂���
//        return;
//    }
//}

void GgafLinearOctreeElem::dump() {
    _TEXT_("o");
}

GgafLinearOctreeElem::~GgafLinearOctreeElem() {
}
