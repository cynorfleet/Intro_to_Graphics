#version 420 

in  vec4 vPosition;
in  vec4 vNormal;
out vec4 color;

uniform mat4 model_view;
uniform mat4 projection;

uniform vec4 lightPos;
uniform vec3 lightD, lightS, lightA;
uniform vec3 matlD, matlS, matlA;
uniform float shininess;

void main() 
{
	vec3 pos = (model_view * vPosition).xyz;
	vec3 L = normalize(lightPos.xyz - pos);
	vec3 E = normalize(-pos);
	vec3 H = normalize(L + E);
	vec3 N = normalize(model_view * vNormal).xyz;

	vec3 ambient = lightA*matlA;
float Kd = max( dot(L, N), 0.0 );
vec3 diffuse = Kd*lightD*matlD;
float Ks = pow( max(dot(N, H), 0.0), shininess );
vec3 specular = Ks * lightS*matlS;
if( dot(L, N) < 0.0 ) {
   specular = vec3(0.0, 0.0, 0.0);
} 
gl_Position = projection * model_view * vPosition;
color = vec4(ambient + diffuse + specular,1.0);

} 