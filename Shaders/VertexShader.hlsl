cbuffer cbPerObject
{
  matrix WVP;
  matrix World;
  matrix NormalMatrix;
};

struct VOut
{
  float4 worldPos : TEXCOORD0;
  float4 normal : TEXCOORD1;
  float4 position : SV_POSITION;
  float4 color : TEXCOORD2;
};

VOut main( float4 pos : POSITION, float4 n : NORMAL, float4 col : COLOR )
{
  VOut output;

  output.worldPos = mul(pos, WVP);
  output.normal = mul(n, NormalMatrix);
  output.position = mul(pos, WVP);
  output.color = col;

  return output;
}