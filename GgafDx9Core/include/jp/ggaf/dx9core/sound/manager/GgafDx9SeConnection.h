#ifndef GGAFDX9SECONNECTION_H_
#define GGAFDX9SECONNECTION_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9SeLead : public GgafCore::GgafResourceLead<GgafDx9Se> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name OGG���ʖ�(���t�@�C����)
	 * @param prm_pGgafDx9Se OGG
	 */
	GgafDx9SeLead(char* prm_idstr, GgafDx9Se* prm_pGgafDx9Se);

	/**
	 * �I�[�o�[���C�h
	 */
	void processReleaseResource(GgafDx9Se* prm_pResource);

	/**
	 * �f�X�g���N�^<BR>
	 */
	virtual ~GgafDx9SeLead() {
	};
};


}
#endif /*GGAFDX9SECONNECTION_H_*/
