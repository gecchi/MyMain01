#include "jp/ggaf/lib/manager/CameraWorkerConnection.h"

using namespace GgafLib;

CameraWorkerConnection::CameraWorkerConnection(const char* prm_idstr, CameraWorker* prm_pResource) :
    GgafCore::ResourceConnection<CameraWorker> (prm_idstr, prm_pResource) {
}

void CameraWorkerConnection::processReleaseResource(CameraWorker* prm_pResource) {
    _TRACE_("CameraWorkerConnection::processReleaseResource��"<<prm_pResource->getName()<<"�J���Ƃ�����end() (�����łԂ���ꂽ��close()�R��̉\������)");
    //GGAF_DELETE(prm_pResource);
    prm_pResource->end();
    //�{���\�b�h��Actor��Scene�̃f�X�g���N�^�ŃR�l�N�V�����N���[�Y�ɂ�胊�\�[�X������s��ꂽ�Ȃ�΁A
    //���X���b�h����̐_��delete���A DepositoryConnection ��������邱�ƂɂȂ�B
    //end() �̓��C���X���b�h����Ăяo�����悤�ɐ݌v���Ă���̂ŁA
    //�R�R�ɏ��������Ƃ��ɁA�{��end()�͔r���������Ȃ���΂����Ȃ��B
    //�������^�C�~���O�I�ɂقڂ��肦�Ȃ��̂ŁA�ʓ|�Ȃ��߂���Ă��Ȃ��B
    //TODO:�����ꂵ�悤�B
}
