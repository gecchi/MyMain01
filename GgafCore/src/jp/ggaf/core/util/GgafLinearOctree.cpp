#include "stdafx.h"
using namespace GgafCore;


GgafLinearOctree::GgafLinearOctree(int prm_level) {
    _top_space_level = prm_level;
    _top_level_dX = 0;
    _top_level_dY = 0;
    _top_level_dZ = 0;
    _root_X1 = 0;
    _root_Y1 = 0;
    _root_Z1 = 0;
    _root_X2 = 0;
    _root_Y2 = 0;
    _root_Z2 = 0;
    //�ׂ���쐬
    _paUint32_pow = NEW UINT32[(prm_level+1)+1];
    _paUint32_pow[0] = 1;
    for(int i = 1; i < (prm_level+1)+1; i++) {
        _paUint32_pow[i] = _paUint32_pow[i-1] * 8;
        //_TRACE_("_paUint32_pow["<<i<<"]="<<_paUint32_pow[i]);
    }
    //���`�W���ؔz��쐬
    _num_space = (int)((_paUint32_pow[_top_space_level+1] -1) / 7); //��Ԑ�
    _TRACE_("���`�����؋�Ԕz��v�f�� _num_space="<<_num_space);
    _paSpace = NEW GgafLinearOctreeSpace[_num_space];
    for (UINT32 i = 0; i < _num_space; i++) {
        _paSpace[i]._my_index = i;
    }
    _pRegElemFirst = nullptr;
}

void GgafLinearOctree::setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
    _root_X1 = X1;
    _root_Y1 = Y1;
    _root_Z1 = Z1;
    _root_X2 = X2;
    _root_Y2 = Y2;
    _root_Z2 = Z2;
    _top_level_dX = ((_root_X2-_root_X1) / ((float)(1<<_top_space_level))) + 1;
    _top_level_dY = ((_root_Y2-_root_Y1) / ((float)(1<<_top_space_level))) + 1;
    _top_level_dZ = ((_root_Z2-_root_Z1) / ((float)(1<<_top_space_level))) + 1; //+1�͋�Ԑ����I�[�o�[���Ȃ��悤�ɗ]�T���������邽��
    _TRACE_("�����؃��x��0���=" << _root_X2-_root_X1 << "x" << _root_Y2-_root_Y1 << "x" << _root_Z2-_root_Z1);
    _TRACE_("�����؃��x��"<<_top_space_level<<"���=" << _top_level_dX << "x" << _top_level_dY << "x" << _top_level_dZ);
}

void GgafLinearOctree::registElem(GgafLinearOctreeElem* prm_pElem,
                                  int tX1 ,int tY1 ,int tZ1,
                                  int tX2 ,int tY2 ,int tZ2) {

    //�͂ݏo��ꍇ�͕␳
    if (tX1 <= _root_X1)  { tX1 = _root_X1+1; }
    if (tX2 >= _root_X2)  { tX2 = _root_X2-1; }
    if (tY1 <= _root_Y1)  { tY1 = _root_Y1+1; }
    if (tY2 >= _root_Y2)  { tY2 = _root_Y2-1; }
    if (tZ1 <= _root_Z1)  { tZ1 = _root_Z1+1; }
    if (tZ2 >= _root_Z2)  { tZ2 = _root_Z2-1; }

    //�����W�̑召�����Ԃ����ꍇ�A�܂�Level0���O���ALevel0�S�̂��傫���ꍇ�͖�������
    if (tX1 >= tX2 || tY1 >= tY2 || tZ1 >= tZ2) {
        return; //��ԊO�͓o�^���Ȃ�
    }

    //BOX�̈���W�����Ԕz��v�f�ԍ��i���`�����ؔz��̗v�f�ԍ��j���Z�o .
    //�܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
    //���[�g�������ʂ���Ԕԍ�����v�Z���Ĕz���Index�����߂�B
    UINT32 index = 0xffffffff; //tX1,tY1,tZ1,tX2,tY2,tZ2 ����A����(index)�����߂�

    //BOX�̍�����O��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    UINT32 minnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (UINT32)((tX1 - _root_X1) / _top_level_dX),
                                  (UINT32)((tY1 - _root_Y1) / _top_level_dY),
                                  (UINT32)((tZ1 - _root_Z1) / _top_level_dZ)
                                );

    //BOX�̉E�㉜��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    UINT32 maxnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (UINT32)((tX2 - _root_X1) / _top_level_dX),
                                  (UINT32)((tY2 - _root_Y1) / _top_level_dY),
                                  (UINT32)((tZ2 - _root_Z1) / _top_level_dZ)
                                );                 //��_root_X2,_root_Y2,_root_Z2 �ƊԈႦ�Ă��܂���B


    //������BOX�́A�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
    UINT32 differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    UINT32 shift_num = 0;
    UINT32 lv = (UINT32)_top_space_level;
    for(UINT32 i = 0; i < lv; i++) {
        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
            shift_num = i+1;
        }
    }
    //xor����differ_bit_pos �� �E��3�r�b�g�V�t�g���A�}�X�N &B111(&H7) ��AND�����A&B000 ��
    //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
    //�܂肱��� differ_bit_pos �� �܂� �R�r�b�g�ɋ�؂�A����3�r�b�g���H������Ă���ӏ��̂����A
    //�ł������ʒu������ׂĂ���B
    //�H���Ⴄ3�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
    //���������čł�����3�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
    //�ő��ԕ���Level = 5�Ƃ��āA������O��6001�ԁA�E�㉜��6041�Ԃɏ������Ă���BOX���ɂ����
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
    //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
    //   �u������ԃ��x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
    //   �v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

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
    UINT32 morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
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
    // ����ŁA������O��6001�ԁA�E�㉜��6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11�Ԃł��������Ƃ��킩��B
    // ���Ƃ͂����z��Index�ɕϊ�����̂�

    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
    index = morton_order_space_num + (_paUint32_pow[_top_space_level-shift_num]-1)/7;
    //(_paUint32_pow[_top_space_level-shift_num]-1)/7;
    //�́A���`�����؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
    //���䐔��̘a
    // ��r^k = r^0 + r^1 + r^2 + ... + r^n
    // ��r^k = (1 - r^(n+1)) / (1 - r)
    //
    //���`8���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=8 ��
    //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 �ƂȂ�
    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
    // n = 2 - 1 = 1 ��������  (8^(1+1) - 1) / 7 = 9 ��
    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��9�Ƃ킩��B
    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 9+1 ��10�Ԗڂ���n�܂�B
    //�z���10�ԖڂƂ́A�z��v�f�ԍ���-1����9�ɂȂ�B
    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (8^x - 1) / 7 �ƂȂ�


#ifdef MY_DEBUG
    if (index > _num_space-1) {

        _TRACE_(
           "GgafLinearOctree::registElem() ��ԃI�[�o�[ !. \n"<<
           "Root=("<<_root_X1<<","<<_root_Y1<<","<<_root_Z1<<")-("<<_root_X2<<","<<_root_Y2<<","<<_root_Z2<<")\n"<<
           "Elem=("<<tX1<<","<<tY1<<","<<tZ1<<")-("<<tX2<<","<<tY2<<","<<tZ2<<")\n"<<
           "_top_level_dX="<<_top_level_dX<<" _top_level_dY="<<_top_level_dY<<" _top_level_dZ="<<_top_level_dZ<<"\n"<<
           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"<<
           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"<<
           "index="<<index<<" _num_space="<<_num_space
        );
        _TRACE_("Min_X_index="<<((UINT32)((tX1 - _root_X1) / _top_level_dX)));
        _TRACE_("Min_Y_index="<<((UINT32)((tY1 - _root_Y1) / _top_level_dY)));
        _TRACE_("Min_Z_index="<<((UINT32)((tZ1 - _root_Z1) / _top_level_dZ)));
        _TRACE_("Man_X_index="<<((UINT32)((tX2 - _root_X1) / _top_level_dX)));
        _TRACE_("Man_Y_index="<<((UINT32)((tY2 - _root_Y1) / _top_level_dY)));
        _TRACE_("Man_Z_index="<<((UINT32)((tZ2 - _root_Z1) / _top_level_dZ)));
    }
#endif

    //�o�^Elem���X�g�ɒǉ��i��ŃN���A���������ׁj
    if (prm_pElem->_pSpace_current == nullptr) {
        if (_pRegElemFirst == nullptr) {
            prm_pElem->_pRegLinkNext = nullptr;
            _pRegElemFirst = prm_pElem;
        } else {
            prm_pElem->_pRegLinkNext = _pRegElemFirst;
            _pRegElemFirst = prm_pElem;
        }
    } else {
#ifdef MY_DEBUG
        throwGgafCriticalException("GgafLinearOctree::registElem() �o�^���悤�Ƃ��������v�f�́A���̋�Ԃɏ�����Ԃł��B"<<
                                   "�N���A���Ȃ���Ă��Ȃ����A�Q�d�o�^���Ă��܂��B��������ԃC���f�b�N�X="<<(prm_pElem->_pSpace_current->_my_index)<<"  �v�f�ΏۃI�u�W�F�N�g="<<(prm_pElem->_pObject));
#endif
    }

    prm_pElem->_pLinearOctree = this;
    //�v�f����`�W���؋�Ԃɓo�^(����������)
    prm_pElem->belongTo(&(_paSpace[index]));
}

void GgafLinearOctree::clearElem() {
    if (_pRegElemFirst == nullptr) {
        return;
    }
    GgafLinearOctreeElem* pElem = _pRegElemFirst;
    while(true) {
        pElem->clear();
        pElem = pElem -> _pRegLinkNext;
        if (pElem == nullptr) {
            break;
        }
    }
    _pRegElemFirst = nullptr;
}

GgafLinearOctree::~GgafLinearOctree() {
    DELETEARR_IMPOSSIBLE_NULL(_paSpace);
    DELETEARR_IMPOSSIBLE_NULL(_paUint32_pow);
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

    int LV0 = 0;


    if (_paSpace[0]._kindinfobit == 0) {
        _TRACE_("8���؂ɉ��������I");
    } else {
        UTIL::strbin(_paSpace[LV0]._kindinfobit, aChar_strbit);
        _TEXT_("LV0."<<lv0_order_num<<"(POS:"<<lv0_order_pos<<")["<<LV0<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV0].dump();
        _TEXT_("\n");
    }

    UINT32 index_lv1_begin = LV0*8 + 1;
    if (index_lv1_begin > _num_space-1) { return; }

    for (UINT32 LV1 = index_lv1_begin, lv1_order_pos = 0; LV1 < index_lv1_begin+8; LV1++, lv1_order_num++, lv1_order_pos++) {
        if (_paSpace[LV1]._kindinfobit == 0) { continue; }
        UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
        _TEXT_("  LV1-"<<lv1_order_num<<"(POS:"<<lv1_order_pos<<")["<<LV1<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV1].dump();
        _TEXT_("\n");
        ////
        UINT32 index_lv2_begin = LV1*8 + 1;
        if (index_lv2_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N

        for (UINT32 LV2 = index_lv2_begin, lv2_order_pos = 0; LV2 < index_lv2_begin+8; LV2++, lv2_order_num++, lv2_order_pos++) {
            if (_paSpace[LV2]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
            UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
            _TEXT_("    LV2-"<<lv2_order_num<<"(POS:"<<lv2_order_pos<<")["<<LV2<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
            _paSpace[LV2].dump();
            _TEXT_("\n");
            ///
            UINT32 index_lv3_begin = LV2*8 + 1;
            if (index_lv3_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
            for (UINT32 LV3 = index_lv3_begin, lv3_order_pos = 0; LV3 < index_lv3_begin+8; LV3++, lv3_order_num++, lv3_order_pos++) {
                if (_paSpace[LV3]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                _TEXT_("      LV3-"<<lv3_order_num<<"(POS:"<<lv3_order_pos<<")["<<LV3<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                _paSpace[LV3].dump();
                _TEXT_("\n");
                ///
                UINT32 index_lv4_begin = LV3*8 + 1;
                if (index_lv4_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                for (UINT32 LV4 = index_lv4_begin, lv4_order_pos = 0; LV4 < index_lv4_begin+8; LV4++, lv4_order_num++, lv4_order_pos++) {
                    if (_paSpace[LV4]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                    UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                    _TEXT_("        LV4-"<<lv4_order_num<<"(POS:"<<lv4_order_pos<<")["<<LV4<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                    _paSpace[LV4].dump();
                    _TEXT_("\n");
                    ///
                    UINT32 index_lv5_begin = LV4*8 + 1;
                    if (index_lv5_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                    for (UINT32 LV5 = index_lv5_begin, lv5_order_pos = 0; LV5 < index_lv5_begin+8; LV5++, lv5_order_num++, lv5_order_pos++) {
                        if (_paSpace[LV5]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                        UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                        _TEXT_("          LV5-"<<lv5_order_num<<"(POS:"<<lv5_order_pos<<")["<<LV5<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                        _paSpace[LV5].dump();
                        _TEXT_("\n");
                        ///
                        UINT32 index_lv6_begin = LV5*8 + 1;
                        if (index_lv6_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                        for (UINT32 LV6 = index_lv6_begin, lv6_order_pos = 0; LV6 < index_lv6_begin+8; LV6++, lv6_order_num++, lv6_order_pos++) {
                            if (_paSpace[LV6]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                            UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                            _TEXT_("            LV6-"<<lv6_order_num<<"(POS:"<<lv6_order_pos<<")["<<LV6<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                            _paSpace[LV6].dump();
                            _TEXT_("\n");
                            ///
                            UINT32 index_lv7_begin = LV6*8 + 1;
                            if (index_lv7_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                            for (UINT32 LV7 = index_lv7_begin, lv7_order_pos = 0; LV7 < index_lv7_begin+8; LV7++, lv7_order_num++, lv7_order_pos++) {
                                if (_paSpace[LV7]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                                _TEXT_("              LV7-"<<lv7_order_num<<"(POS:"<<lv7_order_pos<<")["<<LV7<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                                _paSpace[LV7].dump();
                                _TEXT_("\n");
                                ///
                                UINT32 index_lv8_begin = LV7*8 + 1;
                                if (index_lv8_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                                for (UINT32 LV8 = index_lv8_begin, lv8_order_pos = 0; LV8 < index_lv8_begin+8; LV8++, lv8_order_num++, lv8_order_pos++) {
                                    if (_paSpace[LV8]._kindinfobit == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                    UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
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


