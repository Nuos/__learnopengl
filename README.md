sourcesite: http://learnopengl.com/

Website of The tutorial on which you can find all the source code and a lot useful materials and links:

************************************************************************************************************************
[Chinese version]
http://bullteacher.com/category/zh_learnopengl_com

[Source version]
http://www.learnopengl.com/

************************************************************************************************************************
[libs]
#3 glew-1.13.0

#2 glfw-3.1.1

#1 glm-0.9.7.1

#0 soil

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
Materials (12-20-2015)

	#0 extensions specs
	
	https://www.opengl.org/registry/specs/EXT/framebuffer_object.txt
	
	#1 opengl wiki
	
	https://www.opengl.org/wiki

************************************************************************************************************************
Conceptions  (12-20-2015)

	# Renderbuffer Object

		http://stackoverflow.com/questions/23119433/why-do-glbindrenderbuffer-and-glrenderbufferstorage-each-take-a-target-paramet

		http://stackoverflow.com/questions/17711673/render-off-screen-with-fbo-and-renderbuffer-and-pixel-transfer-of-color-depth

		http://stackoverflow.com/questions/9909473/opengl-es-2-0-buffer-setup

		https://www.opengl.org/wiki/Renderbuffer_Object


	# Framebuffers
	
		/ in the OpenGL rendering pipeline  The final rendering destination is called framebuffer
		/ framebuffer is a collection of 2D arrays or storages utilized by OpenGL:0)colour buffers, 1)depth buffer, 2)stencil buffer and 3)accumulation buffer
		/ by default OpenGL uses the framebuffer as a rendering destination that is created and managed entirely by the window system  This default framebuffer is called window-system-provided framebuffer
		
		//the OpenGL extension GL_ARB_framebuffer_object provides an interface to create additional non-displayable framebuffer objects (FBO)
		//this framebuffer is called application-created framebuffer in order to distinguish from the default 
		//by using FBO an OpenGL application can redirect the rendering output to the application-created FBO other than the traditional window-system-provided framebuffer
		//And it is fully controlled by OpenGL...
		

		/similar to window-system-provided framebuffer /a FBO contains a collection of rendering destinations:0)color buffer,1)depth buffer, 2)stencil buffer
		/These logical buffers in a FBO are called framebuffer-attachable images (which are 2D arrays of pixels that can be attached to a FBO)
		
		//there are two types of framebuffer-attachable images: 0)texture images, 1)renderbuffer images
		//If an image of a texture object is attached to a framebuffer OpenGL performs "render to texture"
		//If an image of a renderbuffer object is attached to a framebuffer, then OpenGL performs "offscreen rendering"
		
		https://www.opengl.org/wiki/Framebuffer

		https://www.opengl.org/wiki/Framebuffer_Object

		http://www.lighthouse3d.com/tutorials/opengl_framebuffer_objects/

		https://www.khronos.org/opengles/sdk/docs/man/xhtml/glFramebufferRenderbuffer.xml

		http://www.songho.ca/opengl/gl_fbo.html


	# OpenGL Frame Buffer Object

		http://www.songho.ca/opengl/gl_fbo.html#renderbuffer


	# OffScreen Rendering

	
	# OpenGL Rendering Pipeline
	
	# Kernel image processing

		https://en.wikipedia.org/wiki/Kernel_(image_processing)#Convolution

		https://docs.gimp.org/en/plug-in-convmatrix.html (principle and example)

		http://www.songho.ca/dsp/convolution/convolution2d_example.html

	# Skyboxes
		
		A Skybox is a cube that encompasses the entire scene and contains 6 images of a surrounding environment
		
		http://www.custommapmakers.org/skyboxes.php (resources online)


************************************************************************************************************************

