#ifndef GGAFLIBPROPERTIESH_
#define GGAFLIBPROPERTIESH_
#include "jp/ggaf/dxcore/GgafDxProperties.h"

#include <Shlwapi.h>

#ifdef PROPERTY
    #undef PROPERTY
#endif
#define PROPERTY GgafLib::GgafLibProperties

namespace GgafLib {

class GgafLibProperties: public GgafDxCore::GgafDxProperties {
public:
    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_WALL;
    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g���� */
    static std::string DIRNAME_RESOURCE_SPLINE;
    /** [r] �����؋�ԃ��x���� */
    static int OCTREE_LEVEL;
    /** [r] �l���؋�ԃ��x���� */
    static int QUADTREE_LEVEL;
    /** [r] �q�b�g�`�F�b�N�Ɏg�p�����ԕ����͎l���؏ꍇtrue�^����ȊO��false */
    static bool IS_HIT_CHECK_3D;
    /** [r] �q�b�g�`�F�b�N�Ɏg�p�����ԕ����͔����؏ꍇtrue�^����ȊO��false */
    static bool IS_HIT_CHECK_2D;

    ////// �ȉ��́A��L�v���p�e�B���琶�������ǂݏo����p�v���p�e�B ////////

    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_WALL;
    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_SPLINE;


public:
    static void load(std::string prm_properties_filename); //shadows
};

}
#endif /*GGAFLIBPROPERTIESH_*/

