////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// Auther:Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

int g_kind; //�`�b�v��� 1:���� 2:���� 3:�擪 �i�������擪�͖������D��j

float g_X; //��O���s���`�b�vX
float g_Y; //��O���s���`�b�vY
float g_Z; //��O���s���`�b�vZ

float4x4 g_matWorld;  //���g��World�ϊ��s��
float4x4 g_matWorld_front;  //��O���s���`�b�v��World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���u�����h�̉e���o�Ȃ��悤�Ɂi��O����`�悳��Ȃ��悤�Ɂj�A
	//�X���ɂ���Ē��_��y,z�𔽓]
	//
	//�y���_�o�b�t�@�i�f�t�H���g�j�̕`�揇�z
	//
	//         ������
	//         ��
	//
	//          �_
	//         �� �_   
	//         ���C �_ 
	//  (0,0,0)��    ��        ����
	// ����������----����   ����
	//  �_  �B �F�_  ��   �_  
	//    �_   �F  �_��  �A �_ 
	//       ������������������
	//         ��    ��
	//          �_ �@��  �_   
	//            �_ ��    �_ �����i�����j
	//               ��      ��
	//

	if (abs(g_Z - g_matWorld._43) < 0.9) {
		if (abs(g_Y - g_matWorld._42) < 0.5) {
			prm_pos.z = 0;
		}
	}

	if (g_Z < g_matWorld._43) {      //�������O   
		if (g_Y > g_matWorld._42) {      //�������
			if (g_X > g_matWorld._41) {      //������E
				//�������O�ŁA�������ŁA������E
				//
				//                                ����
				//                           ���� �^�� 
				//                              �^  
				//                    ��
				//                 �^ ��
				//               �^ �@��
				//              ��    ��
				//            ������������������
				//         �^   �F  �^��  �A �^
				//       �^ �B  �F�^  ��   �^
				//      ����������----����
				//              ��    ��
				//              ���C �^
				//    y         �� �^
				//   ��          �^
				// ������x
				//   ��
				prm_pos.y = -prm_pos.y;

			} else {
				//�������O�ŁA�������ŁA�E���獶
				//
				// ����     
				// ���_ ����
				//     �_   
				//               ��
				//               �� �_
				//               ���@ �_
				//               ��    ��
				//       ������������������
				//        �_ �A  ���_  �F   �_
				//          �_   ��  �_�F  �B �_
				//             ����----����������
				//               ��    ��
				//                �_ �C��
				//    y             �_ ��
				//   ��               �_
				// ������x
				//   ��
				prm_pos.y = -prm_pos.y;
				prm_pos.z = -prm_pos.z;

			}
		} else {                          //�ォ�牺
			if (g_X > g_matWorld._41) {
				//�������O�ŁA�ォ�牺�ŁA������E
				//
				//          �_
				//         �� �_   
				//         ���C �_ 
				//         ��    ��   
				// ����������----����
				//  �_ �B  �F�_  ��   �_  
				//    �_   �F  �_��  �A �_ 
				//       ������������������
				//         ��    ��
				//          �_ �@��
				//    y       �_ ��     �_ ����  
				//   ��          ��       �_��
				// ������x                ����
				//   ��
				//���̂܂܂ŕ`�揇�ύX�s�p �Ǝv������


			} else {
				//�������O�ŁA�ォ�牺�ŁA�E���獶
				//
				//                      �^
				//                    �^ ��
				//                  �^ �C��
				//                 ��    ��
				//               ����----����������
				//            �^   ��  �^�F  �B �^
				//          �^ �A  ���^  �F   �^
				//         ������������������
				//                 ��    ��
				//            �^   ���@ �^
				//     ���� �^     �� �^
				//      ���^       ��
				//    y ����
				//   �� 
				// ������x
				//   �� 
				prm_pos.z = -prm_pos.z;               

			}
		}
	} else {                        //��O���牜 
		if (g_Y > g_matWorld._42) {      //�������
			if (g_X > g_matWorld._41) {      //������E
				//��O���牜�ŁA�������ŁA������E
				//
				//                                ����
				//                           ���� �^��
				//                              �^  
				//                  �^        �^
				//       ��       �^ �� 
				//       ��     �^ �C��
				//       ��    ��    ��
				//       ��  ����----����������
				//       ��    ��  �^�F  �B �^
				//     �^���A  ���^  �F   �^
				//     ������������������
				//       ��    ��    ��
				//       ��    ���@ �^
				// ��������������������������
				//       ��    �� 
				//       ��    
				//       ��
				//
				//���̂܂܂ŕ`�揇�ύX�s�p

			} else {
				//��O���牜�ŁA�������ŁA�E���獶
               //
				//          ��
				//          ��
				//  ����������
				//      ���_��    ��
				//          ��    �� �_
				//          ���_  ���C �_
				//          ��    ��    ��
				//        ����������----����
				//        �_�� �B �F�_  ��   �_
				//          ���A  �F  �_��  �A �_
				//          ��  ������������������
				//          ��    ��    ��
				//          ��     �_ �@��
				//  ��������������������������������
				//          ��          ��
				//          ��
				//          ��
				prm_pos.z = -prm_pos.z;

			}
		} else {
			if (g_X > g_matWorld._41) {
				//��O���牜�ŁA�ォ�牺�ŁA������E
				//
				//       ��    ��
				//       ��    �� �_
				//       ��    ���@ �_
				//       ��    ��    ��
				//     ������������������
				//     �_�� �A ���_  �F   �_
				//       ���A  ��  �_�F  �B �_
				//       ��  ����----����������
				//       ��    ��    ��
				//       ��     �_ �C�� �_
				// ������������������������������
				//       ��         �_      �_
				//       ��                   �_������
				//       ��                   ����
				prm_pos.y = -prm_pos.y;

			} else {
				//��O���牜�ŁA�ォ�牺�ŁA�E���獶
				//
				//                      ��
				//          ��       �^ ��
				//          ��     �^ �@��
				//          ��    ��    ��
				//          ���^������������������
				//          ��    �F  �^�� �A  �^
				//        �^���B  �F�^  ��   �^
				//        ����������----����
				//          ��    ��    ��
				//          ���^  ���C �^
				//    ����������������������������
				//      ���^��     |�^ 
				//  ����������    
				//          ��
				//
				prm_pos.y = -prm_pos.y;
				prm_pos.z = -prm_pos.z;

			}
		}
	}

	float4 posWorld;
	if (prm_pos.x > 0) {        
		float4x4 matWorld = g_matWorld_front;
		matWorld._41 = g_X;  // ��O���̃`�b�v���W��
		matWorld._42 = g_Y;  
		matWorld._43 = g_Z;  
		posWorld = mul( prm_pos, matWorld );  // World�ϊ�
	} else {
		//���_�v�Z
		posWorld = mul( prm_pos, g_matWorld );        // World�ϊ�
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View�ϊ�
	out_vs.pos          = mul(posWorldView, g_matProj);  // �ˉe�ϊ�

	//UV
	if (g_kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (g_kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		out_vs.uv = prm_uv;
	}
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One;

		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}



