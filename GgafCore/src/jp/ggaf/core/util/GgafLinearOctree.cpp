#include "jp/ggaf/core/util/GgafLinearOctree.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"


using namespace GgafCore;

const uint32_t GgafLinearOctree::_POW8[(MAX_OCTREE_LEVEL+1)+1] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};

GgafLinearOctree::GgafLinearOctree(uint32_t prm_level,
                                   int x1, int y1, int z1,
                                   int x2, int y2, int z2) : GgafObject(),
_top_space_level(prm_level),
_root_x1(x1),
_root_y1(y1),
_root_z1(z1),
_root_x2(x2),
_root_y2(y2),
_root_z2(z2),
_top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dz( ((_root_z2-_root_z1) / ((float)(1<<_top_space_level))) + 1 ), //+1�͋�Ԑ����I�[�o�[���Ȃ��悤�ɗ]�T���������邽��
_r_top_level_dx(1.0 / _top_level_dx),
_r_top_level_dy(1.0 / _top_level_dy),
_r_top_level_dz(1.0 / _top_level_dz),
_num_space((uint32_t)((_POW8[_top_space_level+1] -1) / 7))
{
    //���`�����ؔz��쐬
    _TRACE_("GgafLinearOctree::GgafLinearOctree("<<prm_level<<") ���`�����؋�Ԕz��v�f�� _num_space="<<_num_space);
    _paOctant = NEW GgafTreeSpace<3u>[_num_space];
    for (uint32_t i = 0; i < _num_space; i++) {
        _paOctant[i]._my_index = i;
    }
    _pRegElemFirst = nullptr;
    _TRACE_(FUNC_NAME<<" �����؃��[�g���x��(level=0)�̋�Ԉʒu=(" << _root_x1 << "," << _root_y1 << "," << _root_z1 << ")-(" << _root_x2 << "," << _root_y2 << "," << _root_z2 << ")");
    _TRACE_(FUNC_NAME<<" �����؃��[�g���x��(level=0)�̋�Ԃ̍L��=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 << "x" << _root_z2-_root_z1);
    _TRACE_(FUNC_NAME<<" �����ؖ��[���x��(level="<<_top_space_level<<")�̋�Ԃ̍L��=" << _top_level_dx << "x" << _top_level_dy << "x" << _top_level_dz);

}

void GgafLinearOctree::registerElem(GgafTreeElem<3u>* const prm_pElem,
                                    int tx1, int ty1, int tz1,
                                    int tx2, int ty2, int tz2) {

    //�͂ݏo��ꍇ�͕␳
    if (tx1 <= _root_x1)  { tx1 = _root_x1; }
    if (tx2 >= _root_x2)  { tx2 = _root_x2; }
    if (ty1 <= _root_y1)  { ty1 = _root_y1; }
    if (ty2 >= _root_y2)  { ty2 = _root_y2; }
    if (tz1 <= _root_z1)  { tz1 = _root_z1; }
    if (tz2 >= _root_z2)  { tz2 = _root_z2; }
    //�����W�̑召�����Ԃ����ꍇ�A�܂�Level0���O���ALevel0�S�̂��傫���ꍇ�͖�������
    if (tx1 >= tx2 || ty1 >= ty2 || tz1 >= tz2) {
        return; //��ԊO�͓o�^���Ȃ�
    }

    //��tx1,ty1,tz1,tx2,ty2,tz2 ����A��Ԕԍ� �����߂遄
    //BOX�̈���W�����Ԕz��v�f�ԍ��i���`�����ؔz��̗v�f�ԍ��j���Z�o .
    //�܂��ABOX�̏������ Level �ƁA���̋��Level�̃��[�g�������ʂ���Ԕԍ�������
    //���[�g�������ʂ���Ԕԍ�����v�Z���Ĕz��� index �����߂�B


    //BOX�̍�����O��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t minnum_in_toplevel = GgafLinearOctree::getMortonOrderNumFromXYZindex(
                                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy),
                                            (uint32_t)((tz1 - _root_z1) * _r_top_level_dz)
                                        );

    //BOX�̉E�㉜��XYZ���W�_�����������Ԃ́A�ő僌�x����ԂŃ��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t maxnum_in_toplevel = GgafLinearOctree::getMortonOrderNumFromXYZindex(
                                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy),
                                            (uint32_t)((tz2 - _root_z1) * _r_top_level_dz)
                                        );                 //��_root_x2,_root_y2,_root_z2 �ƊԈႦ�Ă��܂���B


    //������BOX�́A�ǂ̃��x���̋�Ԃɏ������Ă���̂��擾
    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    uint32_t shift_num = 0;
    for (uint32_t i = 0; i < _top_space_level; i++) {
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
    //                               lv0 lv1 lv2 lv3 lv4 lv5 ����e���x����Ԃ̃��[�g�������ʒu
    //     6001 = 00 000 000 000 000 000 001 011 101 110 001
    // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
    // -----------------------------------------------------
    //      232 = 00 000 000 000 000 000 000 000 011 101 000
    //
    //                                                   111 �E�E�E �}�X�N
    //                                               111
    //                                           111
    //                                       111
    //  AND)                             111     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
    // ------------------------------------------------------
    //                                   000 000 011 101 000     <--- ������̃}�X�N���ʂ�  000 �ŁA���ꂪ��������A6001�Ԃ�6041�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
    //                                    f   f   t   t   f      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) �̔���
    //                                    5   4   3   2   1   0  shift_num(�V�t�g��)
    //                                    o   o   x(�ȍ~x)        �����Ԃɖ����ق�����Ă��锻��i������݂�j
    //
    //   ��L���A6001�Ԃ�6041�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
    //   �u������ԃ��x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x7 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
    //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I

    //����XOR���ʂ�
    // 00 000 000 000 000 000 000 000 000 111 �̏ꍇ�Ȃ�� shift_num=1
    //�����
    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)

    // 00 000 000 000 000 111 110 000 101 111 �Ȃǂ̏ꍇ�� shift_num=5
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
    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
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
    // ����ŁA������O��6001�ԁA�E�㉜��6041�ԂƂ���BOX�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�11��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
    // ���Ƃ͂����z��Index�ɕϊ�����̂�

    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�����ؔz��̗v�f�ԍ������߂�
    const uint32_t index = morton_order_space_num + (_POW8[_top_space_level-shift_num]-1)/7;
    //(_POW8[_top_space_level-shift_num]-1)/7;
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
           "GgafLinearOctree::registerElem() ��ԃI�[�o�[ !. \n"
           "Root=("<<_root_x1<<","<<_root_y1<<","<<_root_z1<<")-("<<_root_x2<<","<<_root_y2<<","<<_root_z2<<")\n"
           "Elem=("<<tx1<<","<<ty1<<","<<tz1<<")-("<<tx2<<","<<ty2<<","<<tz2<<")\n"
           "_top_level_dx="<<_top_level_dx<<" _top_level_dy="<<_top_level_dy<<" _top_level_dz="<<_top_level_dz<<"\n"
           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
           "index="<<index<<" _num_space="<<_num_space
        );
        _TRACE_("Min_x_index="<<((uint32_t)((tx1 - _root_x1) / _top_level_dx)));
        _TRACE_("Min_y_index="<<((uint32_t)((ty1 - _root_y1) / _top_level_dy)));
        _TRACE_("Min_z_index="<<((uint32_t)((tz1 - _root_z1) / _top_level_dz)));
        _TRACE_("Man_x_index="<<((uint32_t)((tx2 - _root_x1) / _top_level_dx)));
        _TRACE_("Man_y_index="<<((uint32_t)((ty2 - _root_y1) / _top_level_dy)));
        _TRACE_("Man_z_index="<<((uint32_t)((tz2 - _root_z1) / _top_level_dz)));
    }
#endif

    //�o�^����Elem�����X�g�ɒǉ����ĕێ����Ă����B
    //���R�́A��� clearAllElem() ��ĂɃN���A���������ׁB�����̎d�g�݂͍œK���̗]�n������B
    //�Ⴆ�Γo�^�ς݂̋��Index�݂̂�z��ŕێ����Č��clearAllElem() ����B�A�����X�g��葬���̂ł́B
    //TODO:�Ō�ɑS�v�f�𔪕��؂���N���A������ǂ����@������܂ł́A���̕��@�ň�U�ێ�����E�E�E�Ȃ񂩂Ȃ�
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
    //�v�f����`�����؋�Ԃɓo�^(����������)
    _paOctant[index].registerElem(prm_pElem);
}

void GgafLinearOctree::clearAllElem() {
    //�o�^�ς݂̗v�f���X�g���g�p���āA�����؂��N���A
    GgafTreeElem<3u>* pElem = _pRegElemFirst;
    while (pElem) {

        //pElem->clear();

        if(pElem->_pSpace_current == nullptr) {
            //�X���[
        } else {
            uint32_t index = pElem->_pSpace_current->_my_index;
            while (true) {
                if (_paOctant[index]._kind_bit_field == 0 ) {
                    break;
                } else {
                    _paOctant[index]._kind_bit_field = 0;
                    _paOctant[index]._pElem_first = nullptr;
                    _paOctant[index]._pElem_last = nullptr;
                }
                if (index == 0) {
                    break;
                }
                // �e��ԗv�f�ԍ��ŌJ��Ԃ�
                index = (index-1)>>3;
            }
            pElem->_pNext = nullptr;
            pElem->_pPrev = nullptr;
            pElem->_pSpace_current = nullptr;
        }
        pElem = pElem->_pRegLinkNext;
    }
    _pRegElemFirst = nullptr;
}

GgafLinearOctree::~GgafLinearOctree() {
    GGAF_DELETEARR(_paOctant);
}

void GgafLinearOctree::putTree(uint32_t prm_index, int prm_lv, int prm_pos) {
    int space_no = prm_index;
    if (_paOctant[prm_index]._kind_bit_field != 0) {
        for (int i = 0; i < prm_lv; i++) {
            space_no -= _POW8[i];
            _TRACE_N_("  ");
        }
        UTIL::strbin(_paOctant[prm_index]._kind_bit_field, _aChar_strbit);
        _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /GgafTreeElem->");
        _paOctant[prm_index].dump();
        _TRACE_N_("\n");
    }
    uint32_t lower_level_index = (prm_index<<3) + 1;
    if ( lower_level_index >= _num_space) {
        //�v�f���I�[�o�[�A�܂胊�[�t
        return; //�e��Ԃ֖߂�
    } else {
        //������
        for (int i = 0; i < (1<<3); i++) {
            putTree(lower_level_index+i, prm_lv+1, i);
        }
        return; //�e��Ԃ֖߂�
    }
}

void GgafLinearOctree::putTree() {
    putTree(0);
}


