#ifndef SMPUNIVERSE_H_
#define SMPUNIVERSE_H_

#ifdef P_UNIVERSE
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((VVViewer::VvvCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

namespace VVViewer {

/**
 * VVViewer�̂��̐�
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvUniverse : public GgafLib::DefaultUniverse {

public:
    VvvWorld* pWorld_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    VvvUniverse(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override {}

    virtual ~VvvUniverse();
};

}
#endif /*SMPUNIVERSE_H_*/
