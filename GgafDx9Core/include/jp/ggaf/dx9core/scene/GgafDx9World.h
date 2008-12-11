#ifndef GGAFDX9WORLD_H_
#define GGAFDX9WORLD_H_

#define MAX_DRAW_DEPTH_LEVEL 1000


class GgafDx9World : public GgafWorld
{

public:

	/** �J���� */
	static GgafDx9CameraActor* _pCamera;

	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v */
    static GgafActor* _apActorDrawDepthLevel_first[];
	/** �A�N�^�[���������_�����O�̂��߂̉����̃��x���O���[�v�ʍŏI�A�N�^�[ */
    static GgafActor* _apActorDrawDepthLevel_last[];


	GgafDx9World(string prm_name);


	/**
	 * �t���[�����̕`�揈��<BR>
	 */
	virtual void drawMain();

	/**
	 * �`�惌�x���i�����j��o�^
	 * @param prm_iDrawDepthLevel ���x��
	 * @param prm_pActor �A�N�^�[
	 */
	static void setDrawDepthLevel(int prm_iDrawDepthLevel, GgafActor* prm_pActor);

	virtual ~GgafDx9World();
};

#endif /*GGAFDX9WORLD_H_*/
