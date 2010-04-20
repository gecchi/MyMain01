#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core���O��ԁA���V�[���N���X.
 * GgafMainScene ���p�����������ł��B<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
public:
    GgafDx9Scene(const char* prm_name);
    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
