#version 330
#define NUM_LIGHTS 10

struct LightProperties {
	bool isEnabled;
	int type;
	vec3 ambient;
	vec3 color;
	vec3 position;
	//vec3 halfVector;
	vec3 coneDirection;
	float spotCosCutoff;
	float spotExponent;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};


in vec4 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

layout (location = 0) out vec4 fColor;

uniform sampler2D texture_sample;
uniform vec4 diffuse_color;
uniform LightProperties lights[NUM_LIGHTS];

void main()
{
	vec4 fTexColor = texture2D(texture_sample, fTexCoord);
	fColor = fTexColor * diffuse_color;

	vec3 scatteredlight = vec3(0.0);
	for (int i = 0; i < NUM_LIGHTS; ++i)
	{
		if (lights[i].isEnabled)
		{
			vec3 dir = lights[i].position;
			float atten = 1.0;
			if (lights[i].type != 0)
			{
				dir -= vec3(fPosition);
				float dist = length(dir);
				dir /= dist;

				atten = 1.0 / (lights[i].constantAttenuation + dist * lights[i].linearAttenuation
								+ dist * dist * lights[i].quadraticAttenuation);

				if (lights[i].type == 2)
				{
					float spotCos = dot(dir, -lights[i].coneDirection);
					if (spotCos < lights[i].spotCosCutoff)
						atten = 0.0;
					else
						atten *= pow(spotCos, lights[i].spotExponent);
				}
			}
			float diffuse = max(0.0, dot(fNormal, dir));
			// float specular = ...
			scatteredlight += lights[i].ambient * atten + lights[i].color * diffuse * atten;
		}
	}

	fColor = vec4(scatteredlight, 1.0) * fColor;
	fColor = min(fColor, vec4(1.0));

	/*vec4 gamma = vec4(1.0/2.2);
	fColor = pow(fColor, gamma);*/		// something called gamma correction
}
