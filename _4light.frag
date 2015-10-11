#version 330 core
/*
 * the vec3-Normal is delivered from the vertex-shader
 * because all the lighting calculations are done in the fragment-shader
 * and it is a attribute of each vertex...*****/
in vec3 Normal;
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
/*
 * now we got the-normal-vector for each vertex
 * but we still need 
 *                  the light's-position-vector and 
 *                  the fragment's-position-vector
 * since the light's position is just a single static variable 
 * we can simply declare it as a uniform in the fragment shader
 *
 * and then update the uniform in the game loop(or outside since it doesn't change)
 ****/
uniform vec3 lightPos;


/*
 * And Lastly,
 * add the cooresponding input variable to the fragment-shader..
 * AND now that
 * all the required variables are set 
 * we can start with the lighting calculations in fragment-shader....***************/
 in vec3 FragPos;

void main()
{
    //color = vec4(lightColor * objectColor, 1.0f);

    // here adding ambient lighting factor to the object
    float ambientStrength = 0.4f;
    vec3 ambient = ambientStrength * lightColor;
    //vec3 result = ambient * objectColor;
    //color = vec4(result, 1.0f);

    /*********************************************************
     * First, calculate the direction-vector 
     *        between the light-source and the fragment's-position...
     *************************************/
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    /********************************************************
     * Second, calculate the actual diffuse impact 
     *         the light has on the current-fragment
     *             by taking the dot-product of THE-norm-and-lightDir-vector..
     *
     * The resulting-value is then 
     *     multiplied with the light's-color to get the diffuse-component,
     *     resulting in a darker diffuse component 
     *     the greater the angle is between both vectors.
     ***************************************************************/
     float diff = max(dot(norm, lightDir), 0.0f);
     vec3 diffuse = diff * lightColor;
     vec3 result = (ambient + diffuse) * objectColor;
     color = vec4(result, 1.0f);

}
