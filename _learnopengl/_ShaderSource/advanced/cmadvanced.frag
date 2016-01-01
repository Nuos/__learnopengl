#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture1;

float near = 1.0f;
float far = 100.0f;

float LinearizeDepth(float depth);

void main()
{
   color = texture(texture1, TexCoords);
   //color = vec4(vec3(gl_FragCoord.z), 1.0f);

   ////////////////////////////////
   // visualizing the depth buffer
   //float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
   //color = vec4(vec3(depth), 1.0f);
}

float LinearizeDepth(float depth)
{
  float z = depth * 2.0f - 1.0f; // back to NDC
  return (2.0f * near * far) / (far + near - z * (far - near));
}