#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_

#define GGAF_EVENT_NOLOOP_ANIMATION_FINISHED 201

class GgafDx9SpriteActor : public GgafDx9UntransformedActor {

private:

	/** �����A�j���t���[���p�J�E���^ */
	unsigned int _iCounter_AnimationFrame;


public:
	static const int ORDER_LOOP;
	static const int REVERSE_LOOP;
	static const int OSCILLATE_LOOP;
	static const int ORDER_NOLOOP;
	static const int REVERSE_NOLOOP;
	static const int NOT_ANIMATED;
	GgafDx9SpriteModel* _pSpriteModel;

	/** �A�j���p�^�[���ԍ��̏���ԍ� */
	unsigned int _iAnimationPatternNo_Top;
	/** ���ݕ\�����̃A�j���p�^�[���ԍ� */
	unsigned int _iAnimationPatternNo_Bottom;
	/** ���ݕ\�����̃A�j���p�^�[���ԍ� */
	unsigned int _iAnimationPatternNo_Active;
	/** �p�^�[���ƃp�^�[���̊Ԋu�t���[���� */
	unsigned int _iAnimationFrame_Interval;
	/** �A�j������ */
	unsigned int _iAnimationMethod;
	/** OSCILLATE_LOOP�p�̌��݂̃A�j������ */
	bool _oscillateAnimationOrderFlg;


	GgafDx9SpriteActor(string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ��OverRide �ł���<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9SpriteActor();		//�f�X�g���N�^

 	/**
	 * �A�j���[�V���������̃R�}�֐i�߂�
	 */
	virtual void nextAnimationFrame();

};


#endif /*GGAFDX9SPRITEACTORD_H_*/
