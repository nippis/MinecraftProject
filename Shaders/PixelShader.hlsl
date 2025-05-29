cbuffer LightCBuf
{
	float3 lightPos;
}

static const float3 matColor = { 0.0f, 1.0f, 1.0f };
static const float3 ambient = { 0.10f, 0.10f, 0.10f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 1.0f;
static const float attQuad = 1.0f;

float4 main(float3 worldPos : POSITION, float3 n : NORMAL) : SV_TARGET
{
  const float3 vToL = lightPos - worldPos;
  const float distToL = length(vToL);
  const float3 dirToL = vToL / distToL;

  float3 matColor2 = matColor;
  matColor2[1] = floor(worldPos[0]+8 + 0.5) / 16;
  matColor2[2] = floor(worldPos[1]+8 + 0.5) / 16;
  //matColor2[2] = floor(worldPos[2]+8 + 0.5) / 16;
  
  const float att = attConst + attLin * distToL + attQuad * (distToL * distToL);
  
  const float3 diffuse = diffuseColor * diffuseIntensity * matColor2 * dot(dirToL, n);
  
  return float4(saturate(diffuse + ambient), 1.0f);

}