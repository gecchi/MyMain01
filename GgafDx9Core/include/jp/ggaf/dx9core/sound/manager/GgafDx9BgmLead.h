#ifndef GGAFDX9BGMLEAD_H_
#define GGAFDX9BGMLEAD_H_
namespace GgafDx9Core {

/**
 * ���f�����N���X.
 * �L����(�A�N�^�[)�̌`���F�Ȃǂ�ێ�����N���X�ł��B<BR>
 */
class GgafDx9BgmLead : public GgafCore::GgafResourceLead<GgafDx9Bgm> {

public:

	/**
	 * �R���X�g���N�^<BR>
	 * @param prm_texture_file_name OGG���ʖ�(���t�@�C����)
	 * @param prm_pGgafDx9Bgm OGG
	 */
	GgafDx9BgmLead(char* prm_idstr, GgafDx9Bgm* prm_pGgafDx9Bgm);

	/**
	 * �I�[�o�[���C�h
	 */
	void processReleaseResource(GgafDx9Bgm* prm_pResource);

	/**
	 * �f�X�g���N�^<BR>
	 */
	virtual ~GgafDx9BgmLead() {
	};
};


}
#endif /*GGAFDX9BGMLEAD_H_*/
