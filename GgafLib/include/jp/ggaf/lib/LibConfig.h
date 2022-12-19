#ifndef GGAFLIBCONFIGH_
#define GGAFLIBCONFIGH_
#include "jp/ggaf/dx/Config.h"

#ifdef CONFIG
    #undef CONFIG
#endif
#define CONFIG GgafLib::LibConfig

namespace GgafLib {

class LibConfig: public GgafDx::Config {
public:
    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_WALL;
    /** [r] ���[���h�q�b�g�`�F�b�N�̔����؋�ԃ��x���� */
    static int WORLD_HIT_CHECK_OCTREE_LEVEL;
    /** [r] ���[���h�q�b�g�`�F�b�N�̎l���؋�ԃ��x���� */
    static int WORLD_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] �r���[�q�b�g�`�F�b�N�̎l���؋�ԃ��x���� */
    static int VIEW_HIT_CHECK_QUADTREE_LEVEL;
    /** [r] �q�b�g�`�F�b�N�Ɏg�p�����ԕ����Atrue�F�l���؏ꍇ�^false�F�����؁i�f�t�H���g�j */
    static bool ENABLE_WORLD_HIT_CHECK_2D;

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_WALL;

public:
    static void loadProperties(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAFLIBCONFIGH_*/

