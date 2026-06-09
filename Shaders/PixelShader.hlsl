cbuffer LightCBuf
{
	float4 lightPos;
}

static const float4 diffuseColor = { 1.0f, 1.0f, 1.0f, 0.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 1.0f;
static const float attQuad = 1.0f;

float4 main(float4 worldPos : TEXCOORD0, float4 n : TEXCOORD1, float4 position : SV_POSITION, float4 col : TEXCOORD2) : SV_TARGET
{
  const float4 vToL = lightPos - worldPos;
  const float4 dirToL = normalize(vToL);
  const float4 diffuse = diffuseColor * diffuseIntensity * col * dot(dirToL, n);
  const float4 ambient = col * 0.4f + float4(0.1f, 0.1f, 0.1f, 0.0f);
  
  return saturate(diffuse + ambient);

}