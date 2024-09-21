#include "GgafDx_World3DimEffect.fxh"
float4x4 g_matWorld;

float3 g_vecLightFrom_World;
float4 g_colLightAmbient;
float4 g_colLightDiffuse;
float4 g_colMaterialDiffuse;

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


OUT_VS VS_GroundMesh(
      float4 prm_posModel_Local    : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*�ˉe�ϊ�
    //UV�͂��̂܂�
    out_vs.uv = prm_uv;

    //���_�J���[�v�Z

    //�@���� World �ϊ����Đ��K��
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse;
    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }


 //�J�����̈ʒu(0,0,-57.1259)
//���͐��E��(-1.0f, -1.0f, 0 )�Ƃ����_����(1.0f, 1.0f, 1,0f)�Ƃ����_��Ίp���Ƃ��钼���̂̐��E�Ɏ��߂��Ă��܂��Ă��܂�

//w�͎ˉe��ԁi�������ԁj�ɂ��钸�_���W������Ŋ��邱�Ƃɂ��
//�u���_���X�N���[���ɓ��e���邽�߂̗����̗̂̈�i-1��x��1�A-1��y��1������0��z��1�j�ɔ[�߂�v
//�Ƃ�����؂Ȗ�ڂ����Ă��܂��Bw���u�����n�v�ƌĂ΂��̂́A
//��̗�̂悤�Ɏ�����ɃJ�����̎��������ɍL�����Ă��钸�_�𓯂�XY���W�ɓ��e���邽�߂ł��B


    if ( out_vs.posModel_Proj.z < 60) {
        out_vs.color.a = (out_vs.posModel_Proj.z + 1.0)  / (57.1259*2);
//1 - (out_vs.posModel_Proj.z / 57.1259);
    }
    return out_vs;
}

float4 PS_GroundMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;

    //Blinker���l��
    colOut = getBlinkColor(colOut, colTex);
    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}


technique GroundMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_GroundMesh();
        PixelShader  = compile PS_VERSION PS_GroundMesh();
    }
}

