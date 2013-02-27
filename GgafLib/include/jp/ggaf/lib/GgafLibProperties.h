#ifndef GGAFLIBPROPERTIESH_
#define GGAFLIBPROPERTIESH_

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
    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_WALL;
    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_SPLINE;
    /** [r] �W���؋�ԃ��x���� */
    static int OCTREE_LEVEL;

public:
    static void load(std::string prm_properties_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFLIBPROPERTIESH_*/

