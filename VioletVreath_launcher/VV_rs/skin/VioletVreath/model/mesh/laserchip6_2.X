xof 0303txt 0032
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

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
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


Material PDX08_-_Default {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "blue.tga";
 }
}

Frame Plane01 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,14.988579,0.000000,24.627230,1.000000;;
 }

 Mesh  {
  20;
  -19.051748;0.000294;-24.049662;,
  -18.320049;0.000029;-24.627201;,
  -18.320049;0.000029;-24.627201;,
  -19.051792;-0.499676;-24.915735;,
  -15.150460;-0.499980;-24.915735;,
  -19.051796;0.500301;-24.915735;,
  -15.150458;0.500019;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -18.320049;0.000029;-24.627201;,
  -19.051792;0.500301;-24.915735;,
  -15.150585;0.000011;-24.049826;,
  -19.051748;0.000294;-24.049662;,
  -19.051792;-0.499676;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -15.150460;-0.499980;-24.915735;,
  -14.376286;0.000029;-24.627201;,
  -15.150458;0.500019;-24.915735;,
  -19.051796;0.500301;-24.915735;,
  -19.051748;0.000294;-24.049662;,
  -15.150585;0.000011;-24.049826;;
  12;
  3;1,4,12;,
  3;4,1,7;,
  3;2,10,0;,
  3;13,10,2;,
  3;14,5,6;,
  3;5,14,3;,
  3;5,15,6;,
  3;8,15,5;,
  3;9,10,16;,
  3;10,17,11;,
  3;18,4,19;,
  3;4,18,12;;

  MeshNormals  {
   13;
   0.000036;0.499982;-0.866036;,
   -0.000022;-0.037321;-0.999303;,
   -0.000076;-0.980267;0.197678;,
   0.077109;-0.988236;-0.132078;,
   -0.000067;-1.000000;0.000338;,
   0.000008;-0.846781;0.531942;,
   -0.000073;-1.000000;0.000367;,
   0.000076;0.975631;-0.219419;,
   0.000064;0.883971;0.467542;,
   0.000000;0.000000;-1.000000;,
   0.000000;0.499612;0.866249;,
   0.000063;0.865993;0.500057;,
   0.000020;0.000034;1.000000;;
   12;
   3;0,1,2;,
   3;1,0,3;,
   3;4,5,6;,
   3;3,5,4;,
   3;1,7,8;,
   3;7,1,9;,
   3;7,3,8;,
   3;10,3,7;,
   3;11,5,8;,
   3;5,7,12;,
   3;12,1,5;,
   3;1,12,2;;
  }

  MeshMaterialList  {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { PDX08_-_Default }
  }

  MeshTextureCoords  {
   20;
   0.000000;0.259850;,
   0.000000;0.971298;,
   0.000000;0.129925;,
   0.000000;0.945295;,
   1.000000;1.000000;,
   0.000000;0.910358;,
   1.000000;0.895648;,
   1.000000;0.979486;,
   0.000000;0.585715;,
   0.000000;0.259850;,
   1.000000;0.259850;,
   0.000000;0.259850;,
   0.000000;1.000000;,
   1.000000;0.129925;,
   0.500000;0.945295;,
   0.500000;0.711941;,
   1.000000;0.259850;,
   0.000000;0.259850;,
   0.000000;1.000000;,
   1.000000;1.000000;;
  }
 }
}