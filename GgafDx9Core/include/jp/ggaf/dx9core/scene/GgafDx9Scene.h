#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

/**
 * GgafDx9Core���O��ԁA���V�[���N���X.
 * GgafMainScene ���p�����������ł��B<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {

public:
	GgafDx9Scene(char* prm_name);

	virtual ~GgafDx9Scene();
};


}
#endif /*GGAFDX9SCENE_H_*/
