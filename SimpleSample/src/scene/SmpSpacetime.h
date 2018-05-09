#ifndef SMPSPACETIME_H_
#define SMPSPACETIME_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

namespace SimpleSample {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultSpacetime ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpSpacetime : public GgafLib::DefaultSpacetime {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~SmpSpacetime();
};

}
#endif /*SMPSPACETIME_H_*/
