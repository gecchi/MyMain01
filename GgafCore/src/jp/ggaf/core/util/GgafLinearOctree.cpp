#include "stdafx.h"
using namespace std;
using namespace GgafCore;


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
    _paSpace = NEW GgafLinearOctreeSpace[_num_space];
    for (DWORD i = 0; i < _num_space; i++) {
        _paSpace[i]._my_index = i;
    }
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

void GgafLinearOctree::registElem(GgafLinearOctreeElem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
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
    DWORD index = getSpatialIndex(tX1, tY1, tZ1, tX2, tY2, tZ2);
    if (index > _num_space-1) { //Root��Ԃ��X�V�����ۂɋN���肤�邽�߁A���̔���͕K�v�B
        return;
    } else {
        prm_pElem->addElem(&(_paSpace[index]));
    }


//    if (index > _num_space-1) {
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
    GgafLinearOctreeElem* pElem = _pRegElemFirst;
    while(true) {

        pElem->extract();
        pElem = pElem -> _pRegLinkNext;
        if (pElem == NULL) {
            break;
        }

    }
    _pRegElemFirst = NULL;
}

DWORD GgafLinearOctree::getSpatialIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
    //TODO: �{���́AtX1 - _root_X1 �Ȃǂ����ɂȂ����ꍇ�̑Ή������Ȃ���΂����Ȃ����A�ǂ��������̂�


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

#ifdef MY_DEBUG
    if(index > _num_space-1) {
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
    char aChar_strbit[33];
    int lv0_order_num = 0;
    int lv1_order_num = 0;
    int lv2_order_num = 0;
    int lv3_order_num = 0;
    int lv4_order_num = 0;
    int lv5_order_num = 0;
    int lv6_order_num = 0;
    int lv7_order_num = 0;
    int lv8_order_num = 0;

    int lv0_order_pos = 0;
    int lv1_order_pos = 0;
    int lv2_order_pos = 0;
    int lv3_order_pos = 0;
    int lv4_order_pos = 0;
    int lv5_order_pos = 0;
    int lv6_order_pos = 0;
    int lv7_order_pos = 0;
    int lv8_order_pos = 0;

    int LV0 = 0;


    if (_paSpace[0]._kindinfobit == 0) {
        _TRACE_("8���؂ɉ��������I");
    } else {
        GgafUtil::strbin(_paSpace[LV0]._kindinfobit, aChar_strbit);
        _TEXT_("LV0."<<lv0_order_num<<"(POS:"<<lv0_order_pos<<")["<<LV0<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV0].dump();
        _TEXT_("\n");
    }

    DWORD index_lv1_begin = LV0*8 + 1;
    if (index_lv1_begin > _num_space-1) { return; }

    for (DWORD LV1 = index_lv1_begin, lv1_order_pos = 0; LV1 < index_lv1_begin+8; LV1++, lv1_order_num++, lv1_order_pos++) {
        if (_paSpace[LV1]._kindinfobit == 0) { continue; }
        GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
        _TEXT_("  LV1-"<<lv1_order_num<<"(POS:"<<lv1_order_pos<<")["<<LV1<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV1].dump();
        _TEXT_("\n");
        ////
        DWORD index_lv2_begin = LV1*8 + 1;
        if (index_lv2_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N

        for (DWORD LV2 = index_lv2_begin, lv2_order_pos = 0; LV2 < index_lv2_begin+8; LV2++, lv2_order_num++, lv2_order_pos++) {
            if (_paSpace[LV2]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
            GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
            _TEXT_("    LV2-"<<lv2_order_num<<"(POS:"<<lv2_order_pos<<")["<<LV2<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
            _paSpace[LV2].dump();
            _TEXT_("\n");
            ///
            DWORD index_lv3_begin = LV2*8 + 1;
            if (index_lv3_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
            for (DWORD LV3 = index_lv3_begin, lv3_order_pos = 0; LV3 < index_lv3_begin+8; LV3++, lv3_order_num++, lv3_order_pos++) {
                if (_paSpace[LV3]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                _TEXT_("      LV3-"<<lv3_order_num<<"(POS:"<<lv3_order_pos<<")["<<LV3<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                _paSpace[LV3].dump();
                _TEXT_("\n");
                ///
                DWORD index_lv4_begin = LV3*8 + 1;
                if (index_lv4_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                for (DWORD LV4 = index_lv4_begin, lv4_order_pos = 0; LV4 < index_lv4_begin+8; LV4++, lv4_order_num++, lv4_order_pos++) {
                    if (_paSpace[LV4]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                    GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                    _TEXT_("        LV4-"<<lv4_order_num<<"(POS:"<<lv4_order_pos<<")["<<LV4<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                    _paSpace[LV4].dump();
                    _TEXT_("\n");
                    ///
                    DWORD index_lv5_begin = LV4*8 + 1;
                    if (index_lv5_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                    for (DWORD LV5 = index_lv5_begin, lv5_order_pos = 0; LV5 < index_lv5_begin+8; LV5++, lv5_order_num++, lv5_order_pos++) {
                        if (_paSpace[LV5]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                        GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                        _TEXT_("          LV5-"<<lv5_order_num<<"(POS:"<<lv5_order_pos<<")["<<LV5<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                        _paSpace[LV5].dump();
                        _TEXT_("\n");
                        ///
                        DWORD index_lv6_begin = LV5*8 + 1;
                        if (index_lv6_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                        for (DWORD LV6 = index_lv6_begin, lv6_order_pos = 0; LV6 < index_lv6_begin+8; LV6++, lv6_order_num++, lv6_order_pos++) {
                            if (_paSpace[LV6]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                            GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                            _TEXT_("            LV6-"<<lv6_order_num<<"(POS:"<<lv6_order_pos<<")["<<LV6<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                            _paSpace[LV6].dump();
                            _TEXT_("\n");
                            ///
                            DWORD index_lv7_begin = LV6*8 + 1;
                            if (index_lv7_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                            for (DWORD LV7 = index_lv7_begin, lv7_order_pos = 0; LV7 < index_lv7_begin+8; LV7++, lv7_order_num++, lv7_order_pos++) {
                                if (_paSpace[LV7]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                                _TEXT_("              LV7-"<<lv7_order_num<<"(POS:"<<lv7_order_pos<<")["<<LV7<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                                _paSpace[LV7].dump();
                                _TEXT_("\n");
                                ///
                                DWORD index_lv8_begin = LV7*8 + 1;
                                if (index_lv8_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                                for (DWORD LV8 = index_lv8_begin, lv8_order_pos = 0; LV8 < index_lv8_begin+8; LV8++, lv8_order_num++, lv8_order_pos++) {
                                    if (_paSpace[LV8]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                    GgafUtil::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                                    _TEXT_("                LV8-"<<lv8_order_num<<"(POS:"<<lv8_order_pos<<")["<<LV8<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                                    _paSpace[LV8].dump();
                                    _TEXT_("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


