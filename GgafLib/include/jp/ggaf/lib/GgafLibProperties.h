#ifndef GGAFLIBPROPERTIESH_
#define GGAFLIBPROPERTIESH_

#ifdef GGAF_PROPERTY
    #undef GGAF_PROPERTY
#endif
#define GGAF_PROPERTY(X) (GgafLib::GgafLibProperties::X)

namespace GgafLib {

class GgafLibProperties: public GgafDxCore::GgafDxProperties {
public:
    /** [r] �V�[���n�`�f�[�^�t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_SCENE_DATA;
    /** [r] �X�v���C���Ȑ����W���t�@�C��(dat�t�@�C��)�i�[�f�B���N�g�� */
    static std::string DIR_SPLINE_DATA;
    /** [r] �W���؋�ԃ��x���� */
    static int OCTREE_LEVEL;

    static void load(std::string prm_ini_filename); //shadows
    static void clean();                            //shadows
};

}
#endif /*GGAFLIBPROPERTIESH_*/

