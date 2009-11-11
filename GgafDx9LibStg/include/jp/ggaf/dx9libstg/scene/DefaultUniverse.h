#ifndef DEFAULTUNIVERSE_H_
#define DEFAULTUNIVERSE_H_
namespace GgafDx9LibStg {

/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDx9Core::GgafDx9Universe ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * Ggaf���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 */
class DefaultUniverse : public GgafDx9Core::GgafDx9Universe {

public:

    GgafCore::GgafLinearOctree* _pLinearOctree;

    DefaultUniverse(const char* prm_name);

    virtual void nextFrame();
    /**
     * 8���؃��[�g��ԍX�V
     * GgafDx9Camera::processBehavior()
     * ���[�g��Ԃ����߂�u�J�������W�ړ��v ����A����
     * GgafDx9GeometricActor::processPreJudgement() �� _pChecker->updateHitArea();
     * �u�I�u�W�F�N�g�̏�����ԍX�V�v �����O�Ɏ��s����K�v������B
     * ���[�g��ԍX�V���s�̏ꏊ��ς���Ƃ��͏�L�ɒ��ӂ𕥂�����
     */
    virtual void processJudgement();

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
