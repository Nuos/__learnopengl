sourcesite: http://learnopengl.com/

Website of The tutorial on which you can find all the source code and a lot useful materials and links:

************************************************************************************************************************
[Chinese version]
http://bullteacher.com/category/zh_learnopengl_com

[Source version]
http://www.learnopengl.com/

************************************************************************************************************************
[libs]
glew-1.13.0

glfw-3.1.1

glm-0.9.7.1

soil

************************************************************************************************************************
[Notions First]
can anybody give me a help that give a distinct definetion of the following concepts??? many thanks first..
[zero.] OpenGL-Target
[one..] OpenGL-context
[two..] OpenGL-object
[three] OpenGL-state
[four.] OpenGL-option

************************************************************************************************************************
Diffuse Lighting

  Diffuse lighting gives the object more brightness the closer its fragments are aligned to the light rays from a light source.
  
  -*- the lower the angle between two unit-vectors, the more the dot-product is inclined towards a value of 1.
  -*- when the angle between both vectors is 90-degrees, the dot-product becomes 0.
  -*- the resulting dot-product thus returns a scalar that we can use to calculate the light's impact on the fragment's color, resulting in differently lit fragments, based on their orientation towards  the light..
  
  SO, WHAT DO WE NEED TO CALCULATE DIFFUSE LIGHTING?
  
  ***  normal-vector    a vector that is perpendicular to the vertex's-surface..
  ***  the-directed-light-ray    a direction vector that is the difference vector between the light's position and the fragment's position. To calculate this light ray we need the light's position vector and the fragment's-position-vector...
  
************************************************************************************************************************


************************************************************************************************************************
