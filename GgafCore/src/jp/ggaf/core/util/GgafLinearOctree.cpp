#include "stdafx.h"
using namespace std;
using namespace GgafCore;



////// GgafLinearOctree::Space //////

GgafLinearOctree::Space::Space() {
    _pElemFirst = NULL;
    _pElemLast = NULL;
    _my_index = 0;
    _kindinfobit = 0;
}

void GgafLinearOctree::Space::dump() {
    if (_pElemFirst == NULL) {
        _TEXT_("x");
    } else {
        Elem* pElem = _pElemFirst;
        while (true) {
            pElem->dump();

            if (pElem == _pElemLast) {
                break;
            }
            pElem = pElem -> _pNext;
        }
    }
}
GgafLinearOctree::Space::~Space() {
}


////// GgafLinearOctree::Elem //////

GgafLinearOctree::Elem::Elem(GgafObject* prm_pObject, DWORD prm_kindbit) {
    _pSpace_Current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctree::Elem::extract() {
    if(_pSpace_Current == NULL) {
        //_TRACE_("GgafLinearOctree::Elem::extract() �ł��܂���B�Ӑ}���Ă܂����H");
        return;
    }
    //��񃊃Z�b�g
    int index = _pSpace_Current->_my_index;
    while(true) {
        //��ł�extract()����Ə��͕���邱�Ƃ𒍈ӁA�A�v���P�[�V�������W�b�N����extract() �͎g�p���Ȃ����ƁB
        //��{�c���[�́A�o�^�ƁA�N���A���ݍs���Ƃ����݌v
        _pLinearOctree->_paSpace[index]._kindinfobit =
                        _pLinearOctree->_paSpace[index]._kindinfobit ^ _kindbit;

        if (index == 0) {
            break;
        }
        // �e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
    if (this == _pSpace_Current->_pElemFirst && this == _pSpace_Current->_pElemLast) {
        //�擪�������̏ꍇ
        _pSpace_Current->_pElemFirst = NULL;
        _pSpace_Current->_pElemLast = NULL;
        _pSpace_Current = NULL;
    } else if (this == _pSpace_Current->_pElemFirst) {
        //�擪�������ꍇ
        _pSpace_Current->_pElemFirst = _pNext;
        _pSpace_Current->_pElemFirst->_pPrev = NULL;
        _pNext = NULL;
        _pSpace_Current = NULL;
    } else if (this == _pSpace_Current->_pElemLast) {
        //�����������ꍇ
        _pSpace_Current->_pElemLast = _pPrev;
        _pSpace_Current->_pElemLast->_pNext = NULL;
        _pPrev = NULL;
        _pSpace_Current = NULL;
    } else {
        //���Ԃ������ꍇ
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        _pNext = NULL;
        _pPrev = NULL;
        _pSpace_Current = NULL;
    }
}

void GgafLinearOctree::Elem::addElem(Space* prm_pSpace_target) {
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
    int index = prm_pSpace_target->_my_index;
    //�e��Ԃ��ׂĂɗv�f��ʏ��𗬂�
    while(true) {
        _pLinearOctree->_paSpace[index]._kindinfobit =
                _pLinearOctree->_paSpace[index]._kindinfobit | this->_kindbit;
        if (index == 0) {
            break;
        }
        //���̐e��ԗv�f�ԍ��ŌJ��Ԃ�
        index = (index-1)>>3;
    }
}

//void GgafLinearOctree::Elem::moveToSpace(Space* prm_pSpace_target) {
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

void GgafLinearOctree::Elem::dump() {
    _TEXT_("o");
}

GgafLinearOctree::Elem::~Elem() {
}

////// GgafLinearOctree //////

GgafLinearOctree::GgafLinearOctree(int prm_level) {
    _top_space_level = prm_level;
    //�ׂ���쐬
    _paPow = NEW DWORD[SPACE_MAXLEVEL+1];
    _paPow[0] = 1;
    for(int i = 1; i < SPACE_MAXLEVEL + 1; i++) {
        _paPow[i] = _paPow[i-1] * 8;
    }
    //���`�W���ؔz��쐬
    _num_space = (_paPow[_top_space_level+1] -1) / 7; //��Ԑ�
    _TRACE_("_num_space="<<_num_space);
    _paSpace = NEW Space[_num_space];
    for (DWORD i = 0; i < _num_space; i++) {
        _paSpace[i]._my_index = i;
    }xx
    _pRegElemFirst = NULL;

}

void GgafLinearOctree::setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
    _root_X1 = X1;
    _root_Y1 = Y1;
    _root_Z1 = Z1;
    _root_X2 = X2;
    _root_Y2 = Y2;
    _root_Z2 = Z2;
    _top_level_dX = (_root_X2-_root_X1) / ((float)(1<<_top_space_level));
    _top_level_dY = (_root_Y2-_root_Y1) / ((float)(1<<_top_space_level));
    _top_level_dZ = (_root_Z2-_root_Z1) / ((float)(1<<_top_space_level));
}

void GgafLinearOctree::registElem(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
    if (prm_pElem->_pSpace_Current == NULL) {
        //�o�^Elem���X�g�ɒǉ�
        if (_pRegElemFirst == NULL) {
            prm_pElem->_pRegLinkNext = NULL;
            _pRegElemFirst = prm_pElem;
        } else {
            prm_pElem->_pRegLinkNext = _pRegElemFirst;
            _pRegElemFirst = prm_pElem;
        }
    }

    //��ԍ��W�C���f�b�N�X
    prm_pElem->_pLinearOctree = this;
    DWORD index = getSpaceIndex(tX1, tY1, tZ1, tX2, tY2, tZ2);
    if (index < _num_space) { //Root��Ԃ��X�V�����ۂɋN���肤�邽�߁A���̔���͕K�v�B

        prm_pElem->addElem(&(_paSpace[index]));
    }


//    if (index > _num_space) {
//        //_TRACE_("over space!!");
//        prm_pElem->extract();
//    } else {
//        prm_pElem->moveToSpace(_paSpace[index]);
//    }
}
void GgafLinearOctree::clearElem() {
    if (_pRegElemFirst == NULL) {
        return;
    }
    Elem* pElem = _pRegElemFirst;
    while(true) {

        pElem->extract();
        pElem = pElem -> _pRegLinkNext;
		if (pElem == NULL) {
            break;
        }

    }
    _pRegElemFirst = NULL;
}

DWORD GgafLinearOctree::getSpaceIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
    //�܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ������߂�

    //BOX�̍����O��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    DWORD minnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (DWORD)((tX1 - _root_X1) / _top_level_dX),
                                  (DWORD)((tY1 - _root_Y1) / _top_level_dY),
                                  (DWORD)((tZ1 - _root_Z1) / _top_level_dZ)
                                );

    //BOX�̉E������XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    DWORD maxnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (DWORD)((tX2 - _root_X1) / _top_level_dX),
                                  (DWORD)((tY2 - _root_Y1) / _top_level_dY),
                                  (DWORD)((tZ2 - _root_Z1) / _top_level_dZ)
                                );


    //������BOX�́A�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
    DWORD differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    DWORD shift_num = 0;
    for(DWORD i = 0; i < _top_space_level; i++) {
        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
            shift_num = i+1;
        }
    }
    //xor����differ_bit_pos �� �E��3�r�b�g�V�t�g���A�}�X�N &B111(&H7) ��AND�����A&B000 �łȂ��Ȃ��Ă���ʒu������ׂ�B
    //����� differ_bit_pos �� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ�������ׂĂ���
    //�H���Ⴄ3�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
    //�ł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
    //�ő��ԕ���Level = 5�Ƃ��āA�����O��6001�ԁA�E������6041�Ԃɏ������Ă���BOX���ɂ����
    //
    //�e���x����Ԃ̃��[�g�������ʒu lv0 lv1 lv2 lv3 lv4 lv5
    //     6001 = 00 000 000 000 000 000 001 011 101 110 001
    // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
    // -----------------------------------------------------
    //      232 = 00 000 000 000 000 000 000 000 011 101 000
    //
    //                                                   111
    //                                               111
    //                                           111
    //                                       111
    //  AND)                             111     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
    // ------------------------------------------------------
    //                                   000 000 011 101 000
    //                                    o   o   x   x   o      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) �̔���
    //                                    5   4   3   2   1   0   shift_num(�V�t�g��)
    //
    //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă�����
    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
    //   �u������ԃ��x���v��Lv2��Ԃł���Ƃ킩��B����𒲂ׂ邽�߂�
    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3�� �����߂�B
    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
    //   shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

    //����XOR���ʂ�
    // 000 000 000 000 000 000 000 111 �̏ꍇ�Ȃ�� shift_num=1
    //�����
    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)

    // 000 000 000 111 110 000 101 111 �Ȃǂ̏ꍇ�� shift_num=5
    //�����
    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����0 �܂胋�[�g��ԃ��x������
    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����4

    //�܂Ƃ߂��
    //�ő��ԕ���Level = 5 �̏ꍇ
    //shift_num   = 0 1 2 3 4 5
    //�������Level = 5 4 3 2 1 0
    //�ő��ԕ���Level=8 �̏ꍇ
    //shift_num   = 0 1 2 3 4 5 6 7 8
    //�������Level = 8 7 6 5 4 3 2 1 0

    //������Ԃ̃��[�g�������̒ʂ���Ԕԍ������߂�
    DWORD morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
    //�s�����̉��ʂ̃r�b�g��3�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
    //
    // minnum_in_toplevel>>(shift_num*3); �ɂ��āA
    // minnum_in_toplevel=6001 �ł� 6041�ł��ǂ���ł��悭
    //        lv0 lv1 lv2 lv3 lv4 lv5          lv0 lv1 lv2
    // 6001 = 000 001 011 101 110 001   -->    000 001 011 = 11
    // 6041 = 000 001 011 110 011 001   -->    000 001 011 = 11
    //                    ^^^ ^^^ ^^^
    //                  (shift_num*3 �r�b�g����)
    //
    // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
    // ����ŁA�����O��6001�ԁA�E������6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11�Ԃł��������Ƃ��킩��B
    // ���Ƃ͂����z��Index�ɕϊ�����̂�

    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
    DWORD index = morton_order_space_num + (_paPow[_top_space_level-shift_num]-1)/7;
    //(_paPow[_top_space_level-shift_num]-1)/7;
    //�́A���`�����؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
    //���䐔��̘a
    //     ��r^k = r^0 + r^1 + r^2 + ... + r^n
    //(1-r)��r^k = (1-r)(r^0 + r^1 + r^2 + ... + r^n)
    //          = (r^0 + r^1 + r^2 + ... + r^n) - (r^1 + r^2 + ... + r^n + r^(n+1))
    //          = 1 - r^(n+1)
    //�ł���̂�
    //��r^k = (1 - r^(n+1)) / (1 - r)
    //
    //���`8���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=8 ��
    //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 �ƂȂ�
    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�� +1 ���ȗ����Ă��܂����B
    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
    // n = 2 - 1 = 1 ��������  (8^(1+1) - 1) / 7 = 9 ��
    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��9�Ƃ킩��B
    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 9+1 ��10�Ԗڂ���n�܂�B
    //�z���10�ԖڂƂ́A�z��v�f�ԍ���-1����9�ɂȂ�B
    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (8^x - 1) / 7 �ƂȂ�

#ifdef OREDEBUG
    if(index > _num_space) {
//        _TRACE_("index > _num_space �ł��������ł��Bminnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
//                "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
//                "index="<<index);
    }
#endif
    return index;
}


GgafLinearOctree::~GgafLinearOctree() {
    DELETEARR_IMPOSSIBLE_NULL(_paSpace);
    DELETEARR_IMPOSSIBLE_NULL(_paPow);
}


void GgafLinearOctree::putTree() {
    int _paPow[8];
    _paPow[0] = 1;
    for(int i = 1; i < 8; i++) {
        _paPow[i] = _paPow[i-1] * 8;
    }
    int mn0 = 0;
    int idx0 = 0;
    int LV0 = 0;

    if (_paSpace[0]._kindinfobit == 0) {
        _TRACE_("�c���[�ɉ��������I");
    } else {
        _TEXT_("L0["<<LV0<<","<<mn0<<","<<idx0<<"]_kind="<<_paSpace[0]._kindinfobit<<" ");
        _paSpace[idx0].dump();
        _TEXT_("\n");
    }
    for (int LV1 = 0; LV1 < 8; LV1++) {
        int mn1 = LV1;
        int idx1 = _paPow[0] +
                    LV1;

        if (_paSpace[idx1]._kindinfobit == 0) {
            continue;
        } else {
            _TEXT_(" L1["<<LV1<<","<<mn1<<","<<idx1<<"]_kind="<<_paSpace[idx1]._kindinfobit<<" ");
            _paSpace[idx1].dump();
            _TEXT_("\n");
        }
        for (int LV2 = 0; LV2 < 8; LV2++) {
            int mn2 = LV1*_paPow[1] +
                      LV2;
            int idx2 = _paPow[0]+ _paPow[1] +
                       LV1*_paPow[1] +
                       LV2;


            if (_paSpace[idx2]._kindinfobit == 0) {
                continue;
            } else {
                _TEXT_("   L2["<<LV2<<","<<mn2<<","<<idx2<<"]_kind="<<_paSpace[idx2]._kindinfobit<<" ");
                _paSpace[idx2].dump();
                _TEXT_("\n");
            }
            for (int LV3 = 0; LV3 < 8; LV3++) {
                int mn3 = LV1*_paPow[2] +
                          LV2*_paPow[1] +
                          LV3;
                int idx3 = _paPow[0]+ _paPow[1] + _paPow[2] +
                            LV1*_paPow[2] +
                            LV2*_paPow[1] +
                            LV3;

                if (_paSpace[idx3]._kindinfobit == 0) {
                    continue;
                } else {
                    _TEXT_("    L3["<<LV3<<","<<mn3<<","<<idx3<<"]_kind="<<_paSpace[idx3]._kindinfobit<<" ");
                    _paSpace[idx3].dump();
                    _TEXT_("\n");
                }
                for (int LV4 = 0; LV4 < 8; LV4++) {
                    int mn4 =LV1*_paPow[3] +
                            LV2*_paPow[2] +
                            LV3*_paPow[1] +
                            LV4;
                    int idx4 = _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] +
                                LV1*_paPow[3] +
                                LV2*_paPow[2] +
                                LV3*_paPow[1] +
                                LV4;



                    if (_paSpace[idx4]._kindinfobit == 0) {
                        continue;
                    } else {
                        _TEXT_("     L4["<<LV4<<","<<mn4<<","<<idx4<<"]_kind="<<_paSpace[idx4]._kindinfobit<<" ");
                        _paSpace[idx4].dump();
                        _TEXT_("\n");
                    }
                    for (int LV5 = 0; LV5 < 8; LV5++) {
                        int mn5 =   LV1*_paPow[4] +
                                    LV2*_paPow[3] +
                                    LV3*_paPow[2] +
                                    LV4*_paPow[1] +
                                    LV5;
                        int idx5 =  _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] + _paPow[4] +
                                    LV1*_paPow[4] +
                                    LV2*_paPow[3] +
                                    LV3*_paPow[2] +
                                    LV4*_paPow[1] +
                                    LV5;

                        if (_paSpace[idx5]._kindinfobit == 0) {
                            continue;
                        } else {
                            _TEXT_("      L5["<<LV5<<","<<mn5<<","<<idx5<<"]_kind="<<_paSpace[idx5]._kindinfobit<<" ");
                            _paSpace[idx5].dump();
                            _TEXT_("\n");
                        }
                        for (int LV6 = 0; LV6 < 8; LV6++) {
                            int mn6 =   LV1*_paPow[5] +
                                        LV2*_paPow[4] +
                                        LV3*_paPow[3] +
                                        LV4*_paPow[2] +
                                        LV5*_paPow[1] +
                                        LV6;
                            int idx6 =  _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] + _paPow[4] + _paPow[5] +
                                        LV1*_paPow[5] +
                                        LV2*_paPow[4] +
                                        LV3*_paPow[3] +
                                        LV4*_paPow[2] +
                                        LV5*_paPow[1] +
                                        LV6;

                            if (_paSpace[idx6]._kindinfobit == 0) {
                                continue;
                            } else {
                                _TEXT_("       L6["<<LV6<<","<<mn6<<","<<idx6<<"]_kind="<<_paSpace[idx6]._kindinfobit<<" ");
                                _paSpace[idx6].dump();
                                _TEXT_("\n");
                            }

                        }

                    }
                }
            }
        }
    }
}


