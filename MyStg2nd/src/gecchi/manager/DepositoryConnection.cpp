#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DepositoryConnection::DepositoryConnection(char* prm_idstr, GgafActorDepository* prm_pResource) :
    GgafResourceConnection<GgafActorDepository> (prm_idstr, prm_pResource) {
}

void DepositoryConnection::processReleaseResource(GgafActorDepository* prm_pResource) {
    _TRACE_("DepositoryConnection::processReleaseResource�ŁA"<<prm_pResource->getName()<<"�J���Ƃ�����end()(�����łԂ���ꂽ��close()�R��̉\������)");
    prm_pResource->end();
    //�{���\�b�h��Actor��Scene�̃f�X�g���N�^�ŃR�l�N�V�����N���[�Y�ɂ�胊�\�[�X������s��ꂽ�Ȃ�΁A
    //�H��X���b�h����̐_��delete���A DepositoryConnection ��������邱�ƂɂȂ�B
    //end() �̓��C���X���b�h����Ăяo�����悤�ɐ݌v���Ă���̂ŁA
    //�R�R�ɏ��������Ƃ��ɁA�{��end()�͔r���������Ȃ���΂����Ȃ��B
    //�������^�C�~���O�I�ɂقڂ��肦�Ȃ��̂ŁA�ʓ|�Ȃ��߂���Ă��Ȃ��B
    //TODO:�����ꂵ�悤�B
}
