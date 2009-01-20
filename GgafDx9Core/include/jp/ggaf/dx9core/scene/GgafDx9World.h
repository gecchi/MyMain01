#ifndef GGAFDX9WORLD_H_
#define GGAFDX9WORLD_H_
namespace GgafDx9Core {


#define MAX_DRAW_DEPTH_LEVEL 1000


class GgafDx9World : public GgafCore::GgafWorld {

public:

	/** �J���� */
	static GgafDx9CameraActor* _pCamera;

	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v */
    static GgafCore::GgafActor* _apActorDrawDepthLevel_first[];
	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v�ʍŏI�A�N�^�[ */
    static GgafCore::GgafActor* _apActorDrawDepthLevel_last[];


	GgafDx9World(std::string prm_name);


	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	virtual void drawMain();

	/**
	 * �`�惌�x���i�����j��o�^
	 * @param prm_iDrawDepthLevel ���x��
	 * @param prm_pActor �A�N�^�[
	 */
	static void setDrawDepthLevel(int prm_iDrawDepthLevel, GgafCore::GgafActor* prm_pActor);

	virtual ~GgafDx9World();
};


}
#endif /*GGAFDX9WORLD_H_*/
