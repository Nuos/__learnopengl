#version 330 core
/**
 **  Here we declare the corresponding intput variable..
 **/
in vec3 Normal;
/***
 *** add the corresponding intpu variable...
 **/
in vec3 FragPos;

out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;

/**
 ** Sicne the light's position is just a single static variable
 ** we can simply declare it as a uniform in the fragment-shader...
 **
 ** and then update the uniform in the game loop..
 ** we use the lightPos-vector declared in the previous tutorial
 ** as the location of the liaght source...
 **/
uniform vec3 lightPos;

void main()
{
    //color = vec4(lightColor * objectColor, 1.0f);
    /*
     * Ambient lighting
     * 
     * adding Ambient-lighting to the scene is really easy.
     * we take the light's color, mulitiply it with a small constant Ambient-factor,
     * multiply this with the objec's color and use it as the fragment's-color...
     */
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    //vec3 result = ambient * objectColor;
    //color = vec4(result, 1.0f);
    
    /**
     ** Diffuse lighting
     **
     ** To calculate diffuse-ligthing, you need to do the following:
     ** -0- normal-vector| a vector that is perpendicular to the vertex's surface..
     ** -1- the directed-light-ray| a directiron-vector that is the difference vector 
     **     between the light's position and the fragment's position
     **     To calculate the light ray we need
     **                                      the light's position vector and 
     **                                      the fragment's position vector....
     **/
    
    /****
     **** Now that all the required variables are set
     **** we can start with the lighting calculations
     ***/
    // first. calculate the d-vector between the light-source adn the frag's position
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    
    // second. calculate the actual-diffuse-impact
    //   the light has on the current-fragment
    //   by taking the dot-product of the norm-and-lightDir-vector..
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;
    
    // third. now that we have both Ambient-and-Diffuse-component..
    //  we add both colors to each other
    //  and then multiply the result with the color of the object..
    //  to get the resulting fragment's-output-color...
    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}
