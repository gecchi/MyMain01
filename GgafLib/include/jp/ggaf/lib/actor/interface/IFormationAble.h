#ifndef IFORMATIONABLE_H_
#define IFORMATIONABLE_H_

namespace GgafLib {
/**
 * �t�H�[���[�V�����A�N�^�[�C���^�[�t�F�C�X .
 * FormationActor ���Ǘ�����t�H�[���[�V�����v�f�̃A�N�^�[�́A
 * �{�N���X���p�����K�v������܂��B
 * �ڍׂ� FormationActor �̉���Q�ƂցB
 * @version 1.00
 * @since 2011/10/02
 * @author Masatoshi Tsuge
 */
class IFormationAble {
public:
    /** ���ݎ��g���Ǘ����ɂ�����Ă���A�t�H�[���[�V���� */
    GgafLib::FormationActor* _pFormation;

    /**
     * �R���X�g���N�^ .
     * �t�H�[���[�V�����������s�Ȃ������A�N�^�[�́A
     * ���̂悤�Ɋ����ő��d�p�����Ă��������B
     * <pre><code>
     * ���၄
     *
     * class SampleActor :
     *   public GgafLib::DefaultMeshSetActor, public GgafLib::IFormationAble {
     *
     *     SampleActor(const char* prm_name);
     * }
     *
     * SampleActor::SampleActor(const char* prm_name) :
     *   DefaultMeshSetActor(prm_name, "SampleActor", STATUS(SampleActor)), IFormationAble() {
     *
     *     _class_name = "EnemyEunomia";
     * }
     * </pre></code>
     */
    IFormationAble();

    /**
     * ���g���j�󂳂ꂽ�ꍇ�ɒʒm���郁�\�b�h .
     * �t�H�[���[�V�����i�ґ��j�̕ґ��S�Ń{�[�i�X�Ȃǂ̑S�Ŕ�����s�����߂ɁA<BR>
     * ���g���ґ��S�łɗL���ȏ��Łi��ʊO���ł͖����A�j�󂳂ꂽ�Ƃ��{�����j�̃^�C�~���O�ŁA<BR>
     * �{���\�b�h�����s���A�j��ɂ����ł�ʒm���ĉ������B<BR>
     * �ʒm���s�����Ƃɂ��A�Ǘ�����Ă��� FormationActor �I�u�W�F�N�g����A�ґ��S�Ŏ��ɁA
     *
     * FormationActor::onDestroyedFormation()
     *
     * �̃R�[���o�b�N���s���܂��B
     * �ґ��{�[�i�X�A�A�C�e���o������ FormationActor::onDestroyedFormation() �����ōs���ĉ������B
     * <pre><code>
     * ���၄
     * void SampleActor::onHit(GgafActor* prm_pOtherActor) {
     *    //���g�̑ϋv�̓`�F�b�N
     *    if (MyStgUtil::calcSampleStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
     *        //Hit�̑���̃`�F�b�N
     *        if (pOther->getKind() & KIND_MY) {
     *            //Hit�̑���͎��@�֘A�i���@�A���@���j�b�g�A���@���˒e)
     *            informDestroyedFollower(); //�ґ��S�Ŕ���ɗL���Ȕj���ʒm����
     *        }
     *    }
     * }
     * </pre></code>
     */
    void informDestroyedFollower();

    virtual ~IFormationAble();
};

}
#endif /*IFORMATIONABLE_H_*/
