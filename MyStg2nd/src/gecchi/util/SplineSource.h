#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace MyStg2nd {

/**
 * Spline�I�u�W�F�N�g�\�[�X .
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:
    GgafDx9Core::GgafDx9Spline3D* _pSp;
    double _accuracy;
    frame _spent_frame;
    ang_velo _ang_veloRzRyMv;
    std::string _classname;

    SplineSource(char* prm_idstr);

    /**
     * GgafDx9SplineProgram �I�u�W�F�N�g���쐬���� .
     * ��`�t�@�C���ɂ��AGgafDx9FixedFrameSplineProgram �� GgafDx9FixedVelocitySplineProgram ��
     * ���Âꂩ�̃I�u�W�F�N�g�𐶐����A�����Ԃ��B<BR>
     * �����X�v���C�����W���͋��ʁA������Ăяo���Ă��C���X�^���X�͈�B<BR>
     * @param prm_pForWhichActor �ǂ̃A�N�^�[�ׂ̈� GgafDx9SplineProgram �Ȃ̂����w��
     * @return
     */
    GgafDx9Core::GgafDx9SplineProgram* makeSplineProgram(GgafDx9Core::GgafDx9GeometricActor* prm_pForWhichActor);


    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/
