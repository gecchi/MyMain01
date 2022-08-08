#include "DepositoryConnection.h"



using namespace GgafLib;
using namespace VioletVreath;

DepositoryConnection::DepositoryConnection(const char* prm_idstr, GgafCore::ActorDepository* prm_pResource) :
    GgafCore::ResourceConnection<GgafCore::ActorDepository> (prm_idstr, prm_pResource) {
}

void DepositoryConnection::processReleaseResource(GgafCore::ActorDepository* prm_pResource) {
    _TRACE_("DepositoryConnection::processReleaseResource�ŁA"<<prm_pResource->getName()<<"�J���Ƃ�����end()(�����łԂ���ꂽ��close()�R��̉\������)");
    prm_pResource->end();
    //�{���\�b�h��Actor��Scene�̃f�X�g���N�^�ŃR�l�N�V�����N���[�Y�ɂ�胊�\�[�X������s��ꂽ�Ȃ�΁A
    //���X���b�h����̊Ǘ��҂�delete���A DepositoryConnection ��������邱�ƂɂȂ�B
    //end() �̓��C���X���b�h����Ăяo�����悤�ɐ݌v���Ă���̂ŁA
    //�R�R�ɏ��������Ƃ��ɁA�{��end()�͔r���������Ȃ���΂����Ȃ��B
    //�������^�C�~���O�I�ɂقڂ��肦�Ȃ��̂ŁA�ʓ|�Ȃ��߂���Ă��Ȃ��B
    //TODO:�����ꂵ�悤�B
}
