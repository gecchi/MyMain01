xof	0303txt	0032

template	Header	{
	<3D82AB43-62DA-11cf-AB39-0020AF71E433>
	WORD	major;
	WORD	minor;
	DWORD	flags;
}

template	Vector	{
	<3D82AB5E-62DA-11cf-AB39-0020AF71E433>
	FLOAT	x;
	FLOAT	y;
	FLOAT	z;
}

template	Coords2d	{
	<F6F23F44-7686-11cf-8F52-0040333594A3>
	FLOAT	u;
	FLOAT	v;
}

template	Matrix4x4	{
	<F6F23F45-7686-11cf-8F52-0040333594A3>
	array	FLOAT	matrix[16];
}

template	ColorRGBA	{
	<35FF44E0-6C7C-11cf-8F52-0040333594A3>
	FLOAT	red;
	FLOAT	green;
	FLOAT	blue;
	FLOAT	alpha;
}

template	ColorRGB	{
	<D3E16E81-7835-11cf-8F52-0040333594A3>
	FLOAT	red;
	FLOAT	green;
	FLOAT	blue;
}

template	IndexedColor	{
	<1630B820-7842-11cf-8F52-0040333594A3>
	DWORD	index;
	ColorRGBA	indexColor;
}

template	Boolean	{
	<4885AE61-78E8-11cf-8F52-0040333594A3>
	WORD	truefalse;
}

template	Boolean2d	{
	<4885AE63-78E8-11cf-8F52-0040333594A3>
	Boolean	u;
	Boolean	v;
}

template	MaterialWrap	{
	<4885AE60-78E8-11cf-8F52-0040333594A3>
	Boolean	u;
	Boolean	v;
}

template	TextureFilename	{
	<A42790E1-7810-11cf-8F52-0040333594A3>
	STRING	filename;
}

template	Material	{
	<3D82AB4D-62DA-11cf-AB39-0020AF71E433>
	ColorRGBA	faceColor;
	FLOAT	power;
	ColorRGB	specularColor;
	ColorRGB	emissiveColor;
	[...]
}

template	MeshFace	{
	<3D82AB5F-62DA-11cf-AB39-0020AF71E433>
	DWORD	nFaceVertexIndices;
	array	DWORD	faceVertexIndices[nFaceVertexIndices];
}

template	MeshFaceWraps	{
	<4885AE62-78E8-11cf-8F52-0040333594A3>
	DWORD	nFaceWrapValues;
	Boolean2d	faceWrapValues;
}

template	MeshTextureCoords	{
	<F6F23F40-7686-11cf-8F52-0040333594A3>
	DWORD	nTextureCoords;
	array	Coords2d	textureCoords[nTextureCoords];
}

template	MeshMaterialList	{
	<F6F23F42-7686-11cf-8F52-0040333594A3>
	DWORD	nMaterials;
	DWORD	nFaceIndexes;
	array	DWORD	faceIndexes[nFaceIndexes];
	[Material]
}

template	MeshNormals	{
	<F6F23F43-7686-11cf-8F52-0040333594A3>
	DWORD	nNormals;
	array	Vector	normals[nNormals];
	DWORD	nFaceNormals;
	array	MeshFace	faceNormals[nFaceNormals];
}

template	MeshVertexColors	{
	<1630B821-7842-11cf-8F52-0040333594A3>
	DWORD	nVertexColors;
	array	IndexedColor	vertexColors[nVertexColors];
}

template	Mesh	{
	<3D82AB44-62DA-11cf-AB39-0020AF71E433>
	DWORD	nVertices;
	array	Vector	vertices[nVertices];
	DWORD	nFaces;
	array	MeshFace	faces[nFaces];
	[...]
}

template	FrameTransformMatrix	{
	<F6F23F41-7686-11cf-8F52-0040333594A3>
	Matrix4x4	frameMatrix;
}

template	Frame	{
	<3D82AB46-62DA-11cf-AB39-0020AF71E433>
	[...]
}


template	XSkinMeshHeader	{
	<3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
	WORD	nMaxSkinWeightsPerVertex;
	WORD	nMaxSkinWeightsPerFace;
	WORD	nBones;
}

template	VertexDuplicationIndices	{
	<b8d65549-d7c9-4995-89cf-53a9a8b031e3>
	DWORD	nIndices;
	DWORD	nOriginalVertices;
	array	DWORD	indices[nIndices];
}

template	SkinWeights	{
	<6f0d123b-bad2-4167-a0d0-80224f25fabb>
	STRING	transformNodeName;
	DWORD	nWeights;
	array	DWORD	vertexIndices[nWeights];
	array	FLOAT	weights[nWeights];
	Matrix4x4	matrixOffset;
}


Frame	Frame_SCENE_ROOT	{

	FrameTransformMatrix	{
		1.000000,0.000000,0.000000,0.000000,
        0.000000,1.000000,0.000000,0.000000,
        0.000000,0.000000,1.000000,0.000000,
        0.000000,0.000000,0.000000,1.000000;;
	}

	Frame	Frame2_キューブ	{

		FrameTransformMatrix	{
			1.000000,0.000000,0.000000,0.000000,
            0.000000,1.000000,0.000000,0.000000,
            0.000000,0.000000,1.000000,0.000000,
            0.000000,0.000000,0.000000,1.000000;;
		}

		Mesh	Mesh_キューブ	{		CUBE
			96;
			-0.750000;-0.850000;-0.750000;,
			-0.750000;-0.850000;-0.750000;,
			-0.750000;-0.850000;-0.750000;,

			MeshNormals	{
				96;
				-0.707107;-0.707107;0.000000;,
				44;
				3;48,56,60;,
			}

			VertexDuplicationIndices	{
				96;
				93;
				0,
				0,
				92;
			}

			MeshMaterialList	{
				3;
				44;
				0,
				0,
				0,
				0;

				Material	{
					1.000000;0.000000;0.000000;1.000000;;
					51.200001;
					0.000000;0.000000;0.000000;;
					0.000000;0.000000;0.000000;;
				}
			}
		}

		Frame	Frame1_球	{			球

			FrameTransformMatrix	{
				1.000000,0.000000,0.000000,0.000000,
                0.000000,1.000000,0.000000,0.000000,
                0.000000,0.000000,1.000000,0.000000,
                0.000000,0.000000,1.500000,1.000000;;
			}

			Mesh	Mesh_球	{
				176;
				0.000000;-0.200000;0.000000;,
				0.000000;-0.200000;0.000000;,
				0.000000;0.200000;0.000000;;
				80;
				3;136,168,140;,
				3;134,167,137;;

				MeshNormals	{
					176;
					0.106596;-0.960422;0.257344;,
					0.106596;0.960422;-0.257344;,
					0.257344;0.960422;-0.106596;;
					80;
					3;136,168,140;,
					3;0,12,16;,
					3;130,163,164;,
					3;134,167,137;;
				}

				VertexDuplicationIndices	{
					176;
					169;
					0,
					0,
					168;
				}

				MeshMaterialList	{
					3;
					80;
					1,
					1,
					1;

					Material	{
						1.000000;0.000000;0.000000;1.000000;;
						51.200001;
						0.000000;0.000000;0.000000;;
						0.000000;0.000000;0.000000;;
					}
				}
			}

			Frame	Frame3_４面体	{

				FrameTransformMatrix	{
					1.000000,-0.000000,-0.000000,0.000000,
                   -0.000000,-0.000000,-1.000000,0.000000,
                    0.000000, 1.000000,-0.000000,0.000000,
                   -0.000000, 0.000000, 0.350000,1.000000;;
				}

				Mesh	Mesh_４面体	{
					12;
					0.060000;0.060000;0.060000;,
					-0.060000;-0.060000;0.060000;;
					4;
					3;9,3,0;,
					3;2,5,8;;

					MeshNormals	{
						12;
						0.577350;-0.577350;0.577350;,
						-0.577350;-0.577350;-0.577350;;
						4;
						3;9,3,0;,
						3;2,5,8;;
					}

					VertexDuplicationIndices	{
						12;
						10;
						0,
						9;
					}

					MeshMaterialList	{
						3;
						2;

						Material	{
							1.000000;0.000000;0.000000;1.000000;;
							51.200001;
							0.000000;0.000000;0.000000;;
							0.000000;0.000000;0.000000;;
						}
					}
				}
			} Frame3_４面体



		} Frame1_球



	} Frame2_キューブ


}

AnimationSet	AnimationSet_CubeAndSphere1	{

	Animation	Animation0	{
		{	Frame1_球	}
		AnimationKey	{
			0;            回転(0)、スケール変換(1)、ポジションのオフセット(2)
			61;
			0;4;1.000000,0.000000,0.000000,0.000000;;,           時刻（フレーム）; 変数の数; x; y; z;;
			1;4;1.000000,0.000000,0.000000,0.000000;;,
			59;4;1.000000,0.000000,0.000000,0.000000;;,
			60;4;1.000000,0.000000,0.000000,0.000000;;;
		}
		AnimationKey	{
			1;
			61;
			0;3;1.000000,1.000000,1.000000;;,
			1;3;1.000000,1.000000,1.000000;;,
			58;3;1.000000,1.000000,1.000000;;,
			59;3;1.000000,1.000000,1.000000;;,
			60;3;1.000000,1.000000,1.000000;;;
		}
		AnimationKey	{
			2;
			61;
			0;3;0.000000,0.000000,1.500000;;,
			1;3;0.148309,0.000000,1.491800;;,
			57;3;-0.448239,0.000000,1.406656;;,
			58;3;-0.298276,0.000000,1.448029;;,
			59;3;-0.148312,0.000000,1.491800;;,
			60;3;0.000000,0.000000,1.500000;;;
		}
	}

	Animation	Animation1	{
		{	Frame2_キューブ	}
		AnimationKey	{
			0;
			61;
			0;4;1.000000,0.000000,0.000000,0.000000;;,
			59;4;1.000000,0.000000,0.000000,0.000000;;,
			60;4;1.000000,0.000000,0.000000,0.000000;;;
		}
		AnimationKey	{
			1;
			61;
			0;3;1.000000,1.000000,1.000000;;,
			58;3;1.000000,1.000000,1.000000;;,
			59;3;1.000000,1.000000,1.000000;;,
			60;3;1.000000,1.000000,1.000000;;;
		}
		AnimationKey	{
			2;
			61;
			0;3;0.000000,0.000000,0.000000;;,
			1;3;0.000000,0.000000,0.000000;;,
			58;3;0.000000,0.000000,0.000000;;,
			59;3;0.000000,0.000000,0.000000;;,
			60;3;0.000000,0.000000,0.000000;;;
		}
	}

	Animation	Animation2	{
		{	Frame3_４面体	}
		AnimationKey	{
			0;
			61;
			0;4;-0.707107,-0.707107,0.000000,0.000000;;,
			1;4;-0.806686,-0.579368,0.094685,0.068003;;,
			2;4;-0.876664,-0.413251,0.222824,0.105037;;,
			3;4;-0.896784,-0.222615,0.371126,0.092127;;,
			56;4;-0.215120,-0.837309,-0.125073,-0.486820;;,
			57;4;-0.362799,-0.854857,-0.144915,-0.341462;;,
			58;4;-0.501821,-0.831423,-0.123274,-0.204242;;,
			59;4;-0.618910,-0.777331,-0.070213,-0.088185;;,
			60;4;-0.707107,-0.707107,0.000000,0.000000;;;
		}
		AnimationKey	{
			1;
			61;
			0;3;1.000000,1.000000,1.000000;;,
			1;3;1.000000,1.000000,1.000000;;,
			59;3;1.000000,1.000000,1.000000;;,
			60;3;1.000000,1.000000,1.000000;;;
		}
		AnimationKey	{
			2;
			61;
			0;3;-0.000000,0.000000,0.350000;;,
			1;3;-0.000000,-0.024785,0.326667;;,
			2;3;-0.000000,-0.052059,0.303333;;,
			58;3;0.000000,0.052059,0.303333;;,
			59;3;0.000000,0.024785,0.326667;;,
			60;3;0.000000,0.000000,0.350000;;;
		}
	}
}
