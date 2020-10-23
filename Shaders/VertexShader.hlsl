cbuffer cbPerObject
{
  matrix WVP;
  matrix model;
};



struct VOut
{
  float3 worldPos : POSITION;
	float3 normal : NORMAL;
  float4 position : SV_POSITION;
};

VOut main( float3 pos : POSITION, float3 n : NORMAL )
{
  VOut output;

  output.worldPos = (float3) mul(float4(pos, 1.0f), model);
  output.normal = mul(n, (float3x3) model);
  output.position = mul(float4(pos, 1.0f), WVP);

  return output;
}