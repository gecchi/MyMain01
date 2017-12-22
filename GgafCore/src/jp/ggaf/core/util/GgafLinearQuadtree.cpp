#include "jp/ggaf/core/util/GgafLinearQuadtree.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafTreeSpace.hpp"
#include "jp/ggaf/core/util/GgafUtil.h"

using namespace GgafCore;

const uint32_t GgafLinearQuadtree::_POW4[(MAX_QUADTREE_LEVEL+1)+1] =
    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};

GgafLinearQuadtree::GgafLinearQuadtree(uint32_t prm_level,
                                       int x1, int y1,
                                       int x2, int y2) : GgafObject(),
_top_space_level(prm_level),
_root_x1(x1),
_root_y1(y1),
_root_x2(x2),
_root_y2(y2),
_top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<_top_space_level))) + 1 ), //+1�͋�Ԑ����I�[�o�[���Ȃ��悤�ɗ]�T���������邽��
_r_top_level_dx(1.0 / _top_level_dx),
_r_top_level_dy(1.0 / _top_level_dy),
_num_space((uint32_t)((_POW4[_top_space_level+1] -1) / 3))
{
    //���`�l���ؔz��쐬
    _TRACE_("GgafLinearQuadtree::GgafLinearQuadtree("<<prm_level<<") ���`�l���؋�Ԕz��v�f�� _num_space="<<_num_space);
    _paQuadrant = NEW GgafTreeSpace<2u>[_num_space];
    for (uint32_t i = 0; i < _num_space; i++) {
        _paQuadrant[i]._my_index = i;
    }
    _pRegElemFirst = nullptr;
    _TRACE_(FUNC_NAME<<" �l���؃��[�g���x��(level=0)�̋�Ԃ̍L��=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 );
    _TRACE_(FUNC_NAME<<" �l���ؖ��[���x��(level="<<_top_space_level<<")�̋�Ԃ̍L��=" << _top_level_dx << "x" << _top_level_dy );
}


void GgafLinearQuadtree::registerElem(GgafTreeElem<2u>* const prm_pElem,
                                      int tx1, int ty1,
                                      int tx2, int ty2 ) {

    //�͂ݏo��ꍇ�͕␳
    if (tx1 <= _root_x1)  { tx1 = _root_x1; }
    if (tx2 >= _root_x2)  { tx2 = _root_x2; }
    if (ty1 <= _root_y1)  { ty1 = _root_y1; }
    if (ty2 >= _root_y2)  { ty2 = _root_y2; }
    //�����W�̑召�����Ԃ����ꍇ�A�܂�Level0���O���ALevel0�S�̂��傫���ꍇ�͖�������
    if (tx1 >= tx2 || ty1 >= ty2) {
        return; //��ԊO�͓o�^���Ȃ�
    }

    //��tx1,ty1,tx2,ty2 ����A��Ԕԍ� �����߂遄
    //Rect(�v�f)�̈���W�����Ԕz��v�f�ԍ��i���`�l���ؔz��̗v�f�ԍ��j���Z�o .
    //�܂��ARect(�v�f)�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
    //���[�g�������ʂ���Ԕԍ�����v�Z���Ĕz��� index �����߂�B


    //Rect(�v�f)�̍����XY���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t minnum_in_toplevel = GgafLinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy)
                                        );

    //Rect(�v�f)�̉E����XY���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t maxnum_in_toplevel = GgafLinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy)
                                        );                 //��_root_x2,_root_y2 �ƊԈႦ�Ă��܂���B


    //������Rect(�v�f)�́A�ǂ̃��x���̋�Ԃɏ����i�����Ă���j���Ă���̂��A�ő�̃��x����Ԃ��擾
    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    uint32_t shift_num = 0;
    for (uint32_t i = 0; i < _top_space_level; i++) {
        if (((differ_bit_pos>>(i*2)) & 0x3) != 0 ) {
            shift_num = i+1;
        }
    }
    //xor����differ_bit_pos �� �E��2�r�b�g�V�t�g���A�}�X�N &B11(&H3) ��AND�����A&B000 ��
    //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
    //�܂肱��� differ_bit_pos �� �܂�2�r�b�g�ɋ�؂�A����2�r�b�g���H������Ă���ӏ��̂����A
    //�ł������ʒu������ׂĂ���B
    //�H���Ⴄ2�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
    //���������čł�����2�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
    //�ő��ԕ��� Level = 5 �Ƃ��āA���オ804�ԁA�E����877�Ԃɏ������Ă���Rect(�v�f)���ɂ����
    //
    //                                         L0 L1 L2 L3 L4 L5 �E�E�E�e���x����Ԃ̃��[�g�������ʒu
    //     804 = 00 00 00 00 00 00 00 00 00 00 00 11 01 00 10 00
    // XOR)877 = 00 00 00 00 00 00 00 00 00 00 00 11 01 10 11 01
    // ------------------------------------------------------------
    //      37 = 00 00 00 00 00 00 00 00 00 00 00 00 00 10 01 01
    //
    //                                                        11 �E�E�E �}�X�N
    //                                                     11
    //                                                  11
    //                                               11
    //  AND)                                      11     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
    // -------------------------------------------------------------
    //                                            00 00 10 01 01     <--- ������̃}�X�N���ʂ�  00 �ŁA���ꂪ��������A�A804�Ԃ�877�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
    //                                            f  f  t  t  t      if (differ_bit_pos>>(i*2)) & 0x3 != 0 ) �̔���
    //                                            5  4  3  2  1  0   shift_num(�V�t�g��)
    //                                            o  o  x(�ȍ~x)      �����Ԃɖ����ق�����Ă��锻��i������݂�j
    //
    //   ��L���A804�Ԃ�877�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
    //   �u������ԁiMAX�j���x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x3 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
    //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

    //����XOR���ʂ�
    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 11 �̏ꍇ�Ȃ�� shift_num=1
    //�����
    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)

    // 00 00 00 00 00 00 00 00 00 00 00 11 10 00 10 00 �̏ꍇ�� shift_num=5
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
    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*2);
    //�s�����̉��ʂ̃r�b�g��2�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
    //
    // minnum_in_toplevel>>(shift_num*2); �ɂ��āA
    // minnum_in_toplevel=804 �ł� 877�ł��ǂ���ł��悭
    //       L0 L1 L2 L3 L4 L5          L0 L1 L2
    // 804 = 00 11 01 00 10 00   -->    00 11 01 = 13
    // 877 = 00 11 01 10 11 01   -->    00 11 01 = 13
    //                ^^ ^^ ^^
    //                  (shift_num*2 �r�b�g����)
    //
    // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
    // ����ŁA���オ804�ԁA�E����877�ԂƂ���Rect(�v�f)�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�13��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
    // ���Ƃ͂����z��Index�ɕϊ�����̂�

    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�l���ؔz��̗v�f�ԍ������߂�
    const uint32_t index = morton_order_space_num + (_POW4[_top_space_level-shift_num]-1)/3;
    //(_POW4[_top_space_level-shift_num]-1)/7;
    //�́A���`�l���؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
    //���䐔��̘a
    // ��r^k = r^0 + r^1 + r^2 + ... + r^n
    // ��r^k = (1 - r^(n+1)) / (1 - r)
    //
    //���`4���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=4 ��
    //(1 - 4^(n+1)) / (1-4)  =  (1-4^(n+1)) / -3  =  (4^(n+1) - 1) / 3 �ƂȂ�
    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
    // n = 2 - 1 = 1 ��������  (4^(1+1) - 1) / 3 = 5 ��
    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��5�Ƃ킩��B
    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 5+1 ��6�Ԗڂ���n�܂�B
    //�z���6�ԖڂƂ́A�z��v�f�ԍ���-1����5�ɂȂ�B
    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (4^x - 1) / 3 �ƂȂ�


#ifdef MY_DEBUG
    if (index > _num_space-1) {

        _TRACE_(
           "GgafLinearQuadtree::registerElem() ��ԃI�[�o�[ !. \n"
           "Root=("<<_root_x1<<","<<_root_y1<<")-("<<_root_x2<<","<<_root_y2<<")\n"
           "Elem=("<<tx1<<","<<ty1<<")-("<<tx2<<","<<ty2<<")\n"
           "_top_level_dx="<<_top_level_dx<<" _top_level_dy="<<_top_level_dy<<"\n"
           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
           "index="<<index<<" _num_space="<<_num_space
        );
        _TRACE_("Min_x_index="<<((uint32_t)((tx1 - _root_x1) / _top_level_dx)));
        _TRACE_("Min_y_index="<<((uint32_t)((ty1 - _root_y1) / _top_level_dy)));
        _TRACE_("Man_x_index="<<((uint32_t)((tx2 - _root_x1) / _top_level_dx)));
        _TRACE_("Man_y_index="<<((uint32_t)((ty2 - _root_y1) / _top_level_dy)));
    }
#endif

    //�o�^����Elem�����X�g�ɒǉ����ĕێ����Ă����B
    //���R�́A��� clearAllElem() ��ĂɃN���A���������ׁB�����̎d�g�݂͍œK���̗]�n������B
    //�Ⴆ�Γo�^�ς݂̋��Index�݂̂�z��ŕێ����Č��clearAllElem() ����B�A�����X�g��葬���̂ł́B
    //TODO:�Ō�ɑS�v�f���l���؂���N���A������ǂ����@������܂ł́A���̕��@�ň�U�ێ�����E�E�E�Ȃ񂩂Ȃ�
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
        throwGgafCriticalException("�o�^���悤�Ƃ��������v�f�́A���̋�Ԃɏ�����Ԃł��B"
                                   "�N���A���Ȃ���Ă��Ȃ����A�Q�d�o�^���Ă��܂��B��������ԃC���f�b�N�X="<<(prm_pElem->_pSpace_current->_my_index)<<"  �v�f�ΏۃI�u�W�F�N�g="<<(prm_pElem->_pObject));
#endif
    }
    //�v�f����`�l���؋�Ԃɓo�^(����������)
    _paQuadrant[index].registerElem(prm_pElem);
}

void GgafLinearQuadtree::clearAllElem() {
    //�o�^�ς݂̗v�f���X�g���g�p���āA�l���؂��N���A
    GgafTreeElem<2u>* pElem = _pRegElemFirst;
    while (pElem) {
//        pElem->clear();
        if(pElem->_pSpace_current == nullptr) {
            //�X���[
        } else {
            uint32_t index = pElem->_pSpace_current->_my_index;
            while (true) {
                if (_paQuadrant[index]._kind_bit_field == 0 ) {
                    break;
                } else {
                    _paQuadrant[index]._kind_bit_field = 0;
                    _paQuadrant[index]._pElem_first = nullptr;
                    _paQuadrant[index]._pElem_last = nullptr;
                }
                if (index == 0) {
                    break;
                }
                // �e��ԗv�f�ԍ��ŌJ��Ԃ�
                index = (index-1)>>2;
            }
            pElem->_pNext = nullptr;
            pElem->_pPrev = nullptr;
            pElem->_pSpace_current = nullptr;
        }
        pElem = pElem->_pRegLinkNext;
    }
    _pRegElemFirst = nullptr;

}

GgafLinearQuadtree::~GgafLinearQuadtree() {
    GGAF_DELETEARR(_paQuadrant);
}
void GgafLinearQuadtree::putTree(uint32_t prm_index, int prm_lv, int prm_pos) {
    int space_no = prm_index;
    if (_paQuadrant[prm_index]._kind_bit_field != 0) {
        for (int i = 0; i < prm_lv; i++) {
            space_no -= _POW4[i];
            _TRACE_N_("  ");
        }
        UTIL::strbin(_paQuadrant[prm_index]._kind_bit_field, _aChar_strbit);
        _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /GgafTreeElem->");
        _paQuadrant[prm_index].dump();
        _TRACE_N_("\n");
    }
    uint32_t lower_level_index = (prm_index<<2) + 1;
    if ( lower_level_index >= _num_space) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        return; //�e��Ԃ֖߂�
    } else {
        //������
        for (int i = 0; i < (1<<2); i++) {
            putTree(lower_level_index+i, prm_lv+1, i);
        }
        return; //�e��Ԃ֖߂�
    }
}

void GgafLinearQuadtree::putTree() {
    putTree(0);
/*
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

    if (_paQuadrant[0]._kind_bit_field == 0) {
        _TRACE_("4���؂ɉ��������I");
    } else {
        UTIL::strbin(_paQuadrant[LV0]._kind_bit_field, aChar_strbit);
        _TRACE_N_("LV0."<<lv0_order_num<<"(POS:"<<lv0_order_pos<<")["<<LV0<<"]="<<aChar_strbit<<" /GgafTreeElem->");
        _paQuadrant[LV0].dump();
        _TRACE_N_("\n");
    }

    uint32_t index_lv1_begin = LV0*4 + 1;
    if (index_lv1_begin > _num_space-1) { return; }

    for (uint32_t LV1 = index_lv1_begin, lv1_order_pos = 0; LV1 < index_lv1_begin+4; LV1++, lv1_order_num++, lv1_order_pos++) {
        if (_paQuadrant[LV1]._kind_bit_field == 0) { continue; }
        UTIL::strbin(_paQuadrant[LV1]._kind_bit_field, aChar_strbit);
        _TRACE_N_("  LV1-"<<lv1_order_num<<"(POS:"<<lv1_order_pos<<")["<<LV1<<"]="<<aChar_strbit<<" /GgafTreeElem->");
        _paQuadrant[LV1].dump();
        _TRACE_N_("\n");
        ////
        uint32_t index_lv2_begin = LV1*4 + 1;
        if (index_lv2_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N

        for (uint32_t LV2 = index_lv2_begin, lv2_order_pos = 0; LV2 < index_lv2_begin+4; LV2++, lv2_order_num++, lv2_order_pos++) {
            if (_paQuadrant[LV2]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
            UTIL::strbin(_paQuadrant[LV2]._kind_bit_field, aChar_strbit);
            _TRACE_N_("    LV2-"<<lv2_order_num<<"(POS:"<<lv2_order_pos<<")["<<LV2<<"]="<<aChar_strbit<<" /GgafTreeElem->");
            _paQuadrant[LV2].dump();
            _TRACE_N_("\n");
            ///
            uint32_t index_lv3_begin = LV2*4 + 1;
            if (index_lv3_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
            for (uint32_t LV3 = index_lv3_begin, lv3_order_pos = 0; LV3 < index_lv3_begin+4; LV3++, lv3_order_num++, lv3_order_pos++) {
                if (_paQuadrant[LV3]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                UTIL::strbin(_paQuadrant[LV3]._kind_bit_field, aChar_strbit);
                _TRACE_N_("      LV3-"<<lv3_order_num<<"(POS:"<<lv3_order_pos<<")["<<LV3<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                _paQuadrant[LV3].dump();
                _TRACE_N_("\n");
                ///
                uint32_t index_lv4_begin = LV3*4 + 1;
                if (index_lv4_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                for (uint32_t LV4 = index_lv4_begin, lv4_order_pos = 0; LV4 < index_lv4_begin+4; LV4++, lv4_order_num++, lv4_order_pos++) {
                    if (_paQuadrant[LV4]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                    UTIL::strbin(_paQuadrant[LV4]._kind_bit_field, aChar_strbit);
                    _TRACE_N_("        LV4-"<<lv4_order_num<<"(POS:"<<lv4_order_pos<<")["<<LV4<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                    _paQuadrant[LV4].dump();
                    _TRACE_N_("\n");
                    ///
                    uint32_t index_lv5_begin = LV4*4 + 1;
                    if (index_lv5_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                    for (uint32_t LV5 = index_lv5_begin, lv5_order_pos = 0; LV5 < index_lv5_begin+4; LV5++, lv5_order_num++, lv5_order_pos++) {
                        if (_paQuadrant[LV5]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                        UTIL::strbin(_paQuadrant[LV5]._kind_bit_field, aChar_strbit);
                        _TRACE_N_("          LV5-"<<lv5_order_num<<"(POS:"<<lv5_order_pos<<")["<<LV5<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                        _paQuadrant[LV5].dump();
                        _TRACE_N_("\n");
                        ///
                        uint32_t index_lv6_begin = LV5*4 + 1;
                        if (index_lv6_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                        for (uint32_t LV6 = index_lv6_begin, lv6_order_pos = 0; LV6 < index_lv6_begin+4; LV6++, lv6_order_num++, lv6_order_pos++) {
                            if (_paQuadrant[LV6]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                            UTIL::strbin(_paQuadrant[LV6]._kind_bit_field, aChar_strbit);
                            _TRACE_N_("            LV6-"<<lv6_order_num<<"(POS:"<<lv6_order_pos<<")["<<LV6<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                            _paQuadrant[LV6].dump();
                            _TRACE_N_("\n");
                            ///
                            uint32_t index_lv7_begin = LV6*4 + 1;
                            if (index_lv7_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                            for (uint32_t LV7 = index_lv7_begin, lv7_order_pos = 0; LV7 < index_lv7_begin+4; LV7++, lv7_order_num++, lv7_order_pos++) {
                                if (_paQuadrant[LV7]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                UTIL::strbin(_paQuadrant[LV7]._kind_bit_field, aChar_strbit);
                                _TRACE_N_("              LV7-"<<lv7_order_num<<"(POS:"<<lv7_order_pos<<")["<<LV7<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                                _paQuadrant[LV7].dump();
                                _TRACE_N_("\n");
                                ///
                                uint32_t index_lv8_begin = LV7*4 + 1;
                                if (index_lv8_begin > _num_space-1) { continue; } //���̊K�w�ɂ�����邩Lv�`�F�b�N
                                for (uint32_t LV8 = index_lv8_begin, lv8_order_pos = 0; LV8 < index_lv8_begin+4; LV8++, lv8_order_num++, lv8_order_pos++) {
                                    if (_paQuadrant[LV8]._kind_bit_field == 0) { continue; }  //���������̂ŉ��ʕ\�����΂�
                                    UTIL::strbin(_paQuadrant[LV8]._kind_bit_field, aChar_strbit);
                                    _TRACE_N_("                LV8-"<<lv8_order_num<<"(POS:"<<lv8_order_pos<<")["<<LV8<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                                    _paQuadrant[LV8].dump();
                                    _TRACE_N_("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
*/
}


