xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}


Frame Plane01 {
 

 FrameTransformMatrix {
  -0.000000,-0.851680,0.000000,0.000000,-0.000000,-0.000000,-0.851680,0.000000,0.851680,-0.000000,-0.000000,0.000000,0.000000,-0.000000,0.000000,1.000000;;
 }

 Mesh {
  8;
  -0.002252;-0.000946;-3.116537;,
  2.735762;-0.012468;-0.380102;,
  -2.737109;-0.000946;-0.380102;,
  0.002762;-0.002074;118.235985;,
  -0.000673;0.017007;-3.116537;,
  -0.000673;2.735489;-0.380102;,
  -0.000675;-2.737382;-0.380102;,
  -0.004548;0.001780;118.235992;;
  4;
  3;0,1,2;,
  3;3,2,1;,
  3;4,5,6;,
  3;7,6,5;;

  MeshNormals {
   5;
   -0.002105;-0.999996;-0.002104;,
   -0.002105;-0.999998;0.000039;,
   -0.002105;-0.999998;0.000039;,
   1.000000;-0.000000;0.000000;,
   1.000000;-0.000000;0.000033;;
   4;
   3;0,1,1;,
   3;2,1,1;,
   3;3,4,4;,
   3;4,4,4;;
  }

  MeshTextureCoords {
   8;
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;,
   0.000000;0.000000;,
   1.000000;0.000000;,
   0.000000;1.000000;,
   1.000000;1.000000;;
  }

  MeshMaterialList {
   1;
   4;
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.964706;1.000000;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;
   }
  }
 }
}