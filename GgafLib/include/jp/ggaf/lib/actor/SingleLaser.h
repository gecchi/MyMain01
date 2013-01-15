#ifndef SINGLELASER_H_
#define SINGLELASER_H_

namespace GgafLib {

/**
 * �P�����[�U�[ .
 * GgafDxCore::GgafDxMeshSetActor�Ɠ��l�ɕ������f���`��ɂ��A��������ژ_�ށB <BR>
 * �A���\�����ɁA�}�e���A���J���[�A�X�y�L�����[�̌v�Z���s��Ȃ��B<BR>
 * ���̑���ɁAGgafDxCore::GgafDxMeshSetActor ��������ɑ����̃Z�b�g���i����26�j���T�|�[�g�B<BR>
 * ��ʕ\���p�ɍœK������Ă���B<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDxCore::GgafDxMeshSetActor {
public:

    D3DXHANDLE _ah_matWorld[26];
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;
    SingleLaser(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);


    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

