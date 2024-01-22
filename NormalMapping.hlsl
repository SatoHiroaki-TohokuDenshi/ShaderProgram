//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture	: register(t0);	//テクスチャー
SamplerState	g_sampler	: register(s0);	//サンプラー

Texture2D		g_nmap		: register(t1);	//ノーマルマップ

//───────────────────────────────────────
// コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gModel : register(b0)
{
	float4x4	matWorld;		// ワールド行列
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matNormal;		// 法線変形行列
	float4		diffuseColor;	// マテリアルの色＝拡散反射係数
	float4		ambientColor;	// 環境光係数
	float4		specularColor;	// 鏡面反射係数
	float		shininess;		// 鏡面反射強度
	bool		isTextured;		// テクスチャーが貼られているかどうか
	bool		isNMap;			// テクスチャーが貼られているかどうか
};

cbuffer gModel : register(b1)
{
	float4		lightPos;		// 光源の位置
	float4		eyePos;			// 視点
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos  : SV_POSITION;		// 位置
	float2 uv	: TEXCOORD;			// UV座標
	float4 eyeDir	: POSITION;		// 視点ベクトル
	float4 nEyeDir	: POSITION1;	// ノーマルマップ用視線ベクトル
	float4 light	: POSITION2;	// ノーマルマップ用光源ベクトル
	float4 normal	: NORMAL;		// 法線
	float4 color	: COLOR;		// 色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);

	// UV座標はそのまま
	outData.uv = uv.xy;

	float3 binormal = cross(normal, tangent);

	// 法線を変形
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);

	outData.normal = normal;
	
	tangent.w = 0;
	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);

	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);

	// 光源の位置を正規化
	float4 light = normalize(lightPos);
	outData.color = saturate(dot(normal, light));

	// 視点ベクトルを獲得
	float4 posWorld = mul(pos, matWorld);
	outData.eyeDir = eyePos - posWorld;

	outData.nEyeDir = dot(outData.eyeDir, tangent);
	outData.nEyeDir = dot(outData.eyeDir, binormal);
	outData.nEyeDir = dot(outData.eyeDir, normal);
	outData.nEyeDir = 0;

	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightColor = float4(1.0, 1.0, 1.0, 1.0);		// 光源の色(強さ)

	float4 diffuse;		// 拡散反射
	float4 ambient;		// 環境光
	float4 specular;	// 鏡面反射

	if (isNMap) {
		inData.light = normalize(inData.light);

		float4 tmpNormal = g_nmap.Sample(g_sampler, inData.uv) * 2 - 1;
		tmpNormal.w = 0;
		tmpNormal = normalize(tmpNormal);

		float4 S = dot(tmpNormal, normalize(inData.light));
		S = clamp(S, 0, 1);

		//float4 nLight = dot(inData.normal, normalize(lightPos));
		//float4 ref = normalize(2 * nLight * inData.normal - normalize(lightPos));
		float4 ref = reflect(normalize(lightPos), tmpNormal);
		specular = pow(saturate(dot(ref, normalize(inData.eyeDir))), shininess) * specularColor;

		if (isTextured) {
			diffuse = g_texture.Sample(g_sampler, inData.uv) * S;
			ambient = g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = diffuseColor * S;
			ambient = diffuseColor * ambientColor;
		}

		diffuse = diffuseColor * S;
		ambient = diffuseColor * ambientColor* S;
	}
	else {
		if (isTextured) {
			diffuse = lightColor * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightColor * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = lightColor * diffuseColor * inData.color;
			ambient = lightColor * diffuseColor * ambientColor;
		}

		float4 nLight = dot(inData.normal, normalize(lightPos));
		float4 ref = normalize(2 * nLight * inData.normal - normalize(lightPos));
		specular = pow(saturate(dot(ref, normalize(inData.eyeDir))), shininess) * specularColor;
	}
	return diffuse;
	return (diffuse + ambient + specular);
}
