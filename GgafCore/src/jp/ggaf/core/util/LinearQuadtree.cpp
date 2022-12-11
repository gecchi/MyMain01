#include "jp/ggaf/core/util/LinearQuadtree.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/TreeNode.hpp"
#include "jp/ggaf/core/util/Util.h"

using namespace GgafCore;

LinearQuadtree::LinearQuadtree(uint32_t prm_level,
                               int x1, int y1,
                               int x2, int y2) : LinearTree(prm_level),
_root_x1(x1),
_root_y1(y1),
_root_x2(x2),
_root_y2(y2),
_top_level_dx( (_root_x2-_root_x1) / ((float)(1<<_top_space_level)) ),
_top_level_dy( (_root_y2-_root_y1) / ((float)(1<<_top_space_level)) ),
_r_top_level_dx(1.0 / _top_level_dx),
_r_top_level_dy(1.0 / _top_level_dy)
{
#ifdef MY_DEBUG
    if (prm_level > MAX_QUADTREE_LEVEL) {
        throwCriticalException("LinearQuadtree::LinearQuadtree() ��ԃ��x���I�[�o�[�I prm_level="<<prm_level);
    }
#endif
    _TRACE_("LinearQuadtree::LinearQuadtree("<<prm_level<<") ���`�l���؋�Ԕz��v�f�� _num_space="<<_num_space);
    _TRACE_(FUNC_NAME<<" �l���؃��[�g���x��(level=0)�̋�Ԉʒu=(" << _root_x1 << "," << _root_y1 << ")-(" << _root_x2 << "," << _root_y2 << ")");
    _TRACE_(FUNC_NAME<<" �l���؃��[�g���x��(level=0)�̋�Ԃ̍L��=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 );
    _TRACE_(FUNC_NAME<<" �l���ؖ��[���x��(level="<<_top_space_level<<")�̋�Ԃ̍L��=" << (uint32_t)_top_level_dx << "x" << (uint32_t)_top_level_dy );
}

void LinearQuadtree::registerElem(TreeElem<2u>* const prm_pElem,
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

    //Rect(�v�f)�̍����XY���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t minnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy)
                                        );

    //Rect(�v�f)�̉E����XY���W�_�����������Ԃ́A�ő僌�x���̋�ԁi��������Ȃ��ł��[����ԁj�Ń��[�g�������ʂ���Ԕԍ��͉��Ԃ����擾
    const uint32_t maxnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy)
                                        );                 //��_root_x2,_root_y2 �ƊԈႦ�Ă��܂���B
    //��Ԃɓo�^����i���ʉ��j
    LinearTree::registerElem(prm_pElem, minnum_in_toplevel, maxnum_in_toplevel);
    //�ȉ��͋��ʉ��O�̃R�[�h
//    //������Rect(�v�f)�́A�ǂ̃��x���̋�Ԃɏ����i�����Ă���j���Ă���̂��A�ő�̃��x����Ԃ��擾
//    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
//    uint32_t shift_num = 0;
//    for (uint32_t i = 0; i < _top_space_level; i++) {
//        if (((differ_bit_pos>>(i*2)) & 0x3) != 0 ) {
//            shift_num = i+1;
//        }
//    }
//    //xor����differ_bit_pos �� �E��2�r�b�g�V�t�g���A�}�X�N &B11(&H3) ��AND�����A&B000 ��
//    //�Ȃ��Ȃ��Ă���ꍇ�Ashift_num�ɒl�����B
//    //�܂肱��� differ_bit_pos �� �܂�2�r�b�g�ɋ�؂�A����2�r�b�g���H������Ă���ӏ��̂����A
//    //�ł������ʒu������ׂĂ���B
//    //�H���Ⴄ2�r�b�g�̈ʒu�́A���̃��x���̃��g�[�������ʒu���H������Ă��邱�Ƃ��Ӗ�����B
//    //���������čł�����2�r�b�g���H������Ă���ӏ�(�V�t�g�񐔁�shift_num)��菊����ԃ��x�����킩��
//    //�ő��ԕ��� Level = 5 �Ƃ��āA���オ804�ԁA�E����877�Ԃɏ������Ă���Rect(�v�f)���ɂ����
//    //
//    //                                         L0 L1 L2 L3 L4 L5 �E�E�E�e���x����Ԃ̃��[�g�������ʒu
//    //     804 = 00 00 00 00 00 00 00 00 00 00 00 11 01 00 10 00
//    // XOR)877 = 00 00 00 00 00 00 00 00 00 00 00 11 01 10 11 01
//    // ------------------------------------------------------------
//    //      37 = 00 00 00 00 00 00 00 00 00 00 00 00 00 10 01 01
//    //
//    //                                                        11 �E�E�E �}�X�N
//    //                                                     11
//    //                                                  11
//    //                                               11
//    //  AND)                                      11     <--- �����܂ōs���āA�ł�����3�r�b�g���H������Ă���ӏ���3��ڂ��������Ƃ�����
//    // -------------------------------------------------------------
//    //                                            00 00 10 01 01     <--- ������̃}�X�N���ʂ�  00 �ŁA���ꂪ��������A�A804�Ԃ�877�Ԃ̃��[�g�������ʒu�������ł���i=�����Ԃɏ����j���Ӗ�����
//    //                                            f  f  t  t  t      if (differ_bit_pos>>(i*2)) & 0x3 != 0 ) �̔���
//    //                                            5  4  3  2  1  0   shift_num(�V�t�g��)
//    //                                            o  o  x(�ȍ~x)      �����Ԃɓ����Ă��锻��i������݂�j
//    //
//    //   ��L���A804�Ԃ�877�Ԃ͋�ԃ��x��1�A���x��2 �܂ł͓�����ԃ��x���ɑ����Ă������A
//    //   ��ԃ��x��3���烂�[�g�������ʒu���قȂ��Ă��܂����Ƃ�����B���������āA
//    //   �u������ԁiMAX�j���x���v��Lv2��Ԃł���Ɗm��ł���B����𒲂ׂ邽�߂�
//    //   XOR��0�ȊO�ɂȂ�ō��̃V�t�g��  shift_num = 3 �����߂�B
//    //   ���߂邽�߂ɂ́A�E��3�r�b�g�V�t�g���� 0x3 �� AND�𒲂ׂ邱�Ƃ��J��Ԃ��K�v������Ƃ������Ƃ��B
//    //   Level = 5�̏ꍇ�A5��J��Ԃ��A�v�� shift_num �̃V�t�g�񐔂𒲂ׂ�΁A������ԃ��x��������I
//
//    //����XOR���ʂ�
//    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 11 �̏ꍇ�Ȃ�� shift_num=1
//    //�����
//    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����4(=��ԃ��x��5�ŐH���Ⴄ)
//    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����7(=��ԃ��x��8�ŐH���Ⴄ)
//
//    // 00 00 00 00 00 00 00 00 00 00 00 11 10 00 10 00 �̏ꍇ�� shift_num=5
//    //�����
//    //�ő��ԕ���Level=5 �̏ꍇ�͏�����ԃ��x����0 �܂胋�[�g��ԃ��x������
//    //�ő��ԕ���Level=8 �̏ꍇ�͏�����ԃ��x����4
//
//    //�܂Ƃ߂��
//    //�ő��ԕ���Level = 5 �̏ꍇ
//    //shift_num   = 0 1 2 3 4 5
//    //�������Level = 5 4 3 2 1 0
//    //�ő��ԕ���Level=8 �̏ꍇ
//    //shift_num   = 0 1 2 3 4 5 6 7 8
//    //�������Level = 8 7 6 5 4 3 2 1 0
//
//    //������Ԃ̃��[�g�������̒ʂ���Ԕԍ������߂�
//    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*2);
//    //�s�����̉��ʂ̃r�b�g��2�r�b�g�P�ʂŏ������A�����̃��[�g�������ԍ������߂�
//    //
//    // minnum_in_toplevel>>(shift_num*2); �ɂ��āA
//    // minnum_in_toplevel=804 �ł� 877�ł��ǂ���ł��悭
//    //       L0 L1 L2 L3 L4 L5          L0 L1 L2
//    // 804 = 00 11 01 00 10 00   -->    00 11 01 = 13
//    // 877 = 00 11 01 10 11 01   -->    00 11 01 = 13
//    //                ^^ ^^ ^^
//    //                  (shift_num*2 �r�b�g����)
//    //
//    // �̂悤�ɕs�����̃r�b�g���E�փV�t�g���Ă���
//    // ����ŁA���オ804�ԁA�E����877�ԂƂ���Rect(�v�f)�́A�������Lv2�̏ꍇ�́A���[�g�������ʂ���Ԕԍ�13��(0�Ԃ��琔����)�ł��������Ƃ��킩��B
//    // ���Ƃ͂����z��Index�ɕϊ�����̂�
//
//    //�������(�V�t�g��)�Ƃ��̋�Ԃ̃��[�g�������ʂ���Ԕԍ�������`�l���ؔz��̗v�f�ԍ������߂�
//    const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/3;
//    //(_POW4[_top_space_level-shift_num]-1)/7;
//    //�́A���`�l���؋�Ԕz��́A������ԃ��x���̍ŏ��̋�Ԃ̗v�f�ԍ�������킷�B
//    //���䐔��̘a
//    // ��r^k = r^0 + r^1 + r^2 + ... + r^n
//    // ��r^k = (1 - r^(n+1)) / (1 - r)
//    //
//    //���`4���؂̔z��v�f�̋�ԃ��x�����܂ł̍��v��֐��� r=4 ��
//    //(1 - 4^(n+1)) / (1-4)  =  (1-4^(n+1)) / -3  =  (4^(n+1) - 1) / 3 �ƂȂ�
//    //�����ŁA������Ԃ̍ŏ��̋�ԗv�f�����߂邽�߁A n = ������ԃ��x��-1 �̌v�Z�l�i�e��ԃ��x���܂ł̗v�f���j�́A
//    //���̎��̗v�f��������ԃ��x���̐擪�̗v�f�ɂȂ�͂����I�B�Ƃ������ߕ�������B
//    //���������čŌ�ɒl�� +1 �������̂��ق����l�ł��邪�A�z���0�Ԃ���n�܂邽�߁A+1 -1 = 0 �ŁA�ȗ����Ă��܂����B
//    //��̗�ł����� shift_num = 3 �ŁA�ő��ԕ���Level(_top_space_level) = 5 �ł���̂�
//    // 5 - 3 = 2 �ŏ�����ԃ��x���� 2
//    // n = 2 - 1 = 1 ��������  (4^(1+1) - 1) / 3 = 5 ��
//    //������Ԃ̃��x��2����e�̋�ԃ��x���ł���A��ԃ��x��1�܂ł̔z��v�f�����v��5�Ƃ킩��B
//    //���]�̏�����ԃ��x���� 2�̍ŏ��̋�Ԃ͔z��� 5+1 ��6�Ԗڂ���n�܂�B
//    //�z���6�ԖڂƂ́A�z��v�f�ԍ���-1����5�ɂȂ�B
//    //+1 ���� -1 ����̂Ō��ǁA������ԃ��x��x�̍ŏ��̔z��v�f�ԍ���  (4^x - 1) / 3 �ƂȂ�
//
}

LinearQuadtree::~LinearQuadtree() {
}

