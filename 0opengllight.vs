#version 330 core
layout (location = 0) in vec3 position;
/** Since we added extra data to the vertex-array
 ** we should update the lighting's vertex-shader...
 ** 
 ** now that we added a normal vector to each of the vertices
 ** and updated the vertex-shader
 ** we should update the vertex-attribute-pointers as well.......
 */
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/** All the lighting calculations are done in the fragment-shaders
 ** so we need to forward
 **                      the normal vectors
 **                      from the vertex-shader to the fragment-shader...
 ** Caution!
 **   declare the corresponding input variable in the fragment-shaders...
 **/
out vec3 Normal;

/*** The actual fragment's-position
 *** We're going to do all the lighting calculations in world space
 *** so we want a vertex-position that is in world-space..
 *** we can accomplish this 
 ***    by multiplying the vertex position attribute 
 ***    with the model matrix only to transform it to world-space-coordinates.
 ***
 *** This can be easily accomplished in the vertex-shader 
 *** so let's declare an output variable and calculate its world-space-coordinates..
 *** add the corresponding input variable to the fragment-shader...
 ***/
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = normal;
}
