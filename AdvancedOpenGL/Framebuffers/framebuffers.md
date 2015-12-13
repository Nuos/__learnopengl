	Framebuffers

	,,,
	So far we've used several types of buffers:
	    A color buffer for writing color values
	    A depth buffer to write depth information
	    A stencil buffer that allows us discard vertain fragments based on some condition..

	The combination of these buffers is called a framebuffer 
	    AND is stored somewhere in memory.
	OpenGL gives us the flexibility to define our own framebuffers
	    AND thus define our own color and optionally a depth and stencil buffer.

	
	,,,
	The rendering operations we've done so far 
		WERE all done on top of the render buffers attached to the default framebuffer.
	The default framebuffer is created
		AND configured when you create your window (GLFW does this for us)
		BY creating our own framebuffer we can get an additional means to render to.

	The application of framebuffer might not immediately make sense
		BUT rendering your scene to a different framebuffer allows us 
		TO create mirrors in a scene or do cool post-processing effects for example.
	First we'll discuss how they actually work 
		AND then we'll use them by implementing those cool post-processing effects.

=======================================================================================

	=== Creating a framebuffer
	===
		First create a framebuffer object
		Second bind it as the active framebuffer
		Third do some operations
		Fourth unbind the framebuffer
			GLuint fbo;
			glGenFramebuffers(1, &fbo);

		By bind to the gl_framebuffer target all the following read-and-write framebuffer
		operations will affect the currently bound framebuffer.
			glBindFramebuffer();
		
		## gl_read_framebuffer -for all read operations like glReadPixels
		## gl_draw_framebuffer -used as the destination for rendering,clearing and others
		
		===
		===
		For a framebuffer to be complete
			THE following requirements have to be satisfied:
			## we have to attach at least one buffer  -color? depth? stencil?
			## there should be at least one color attachment
			## all attachments should be complete as well -reserved memory
			## each buffer should have the same number of samples
		
		=== if(glCheckFramebufferStatus(gl_framebuffer) == gl_framebuffer_complete)
		===
		All subsequent rendering operations will now render to the attachments 
			OF the currently bound framebuffer.
		Since our framebuffer is not the default framebuffer
			THE rendering commands will have no impact on the visual output of window
		For this reason it is called of off-screen rendering
			WHILE rendering to a different framebuffer.
			TO make sure all rendering operations will have a visual impact on the main window
			WE need to make the default framebuffer active again by binding to 0
				glBindFramebuffer(gl_framebuffer, 0);
		When we're done with all framebuffer operations
			DO not forget to delete the framebuffer object.
				glDeleteFramebuffer(1, &fbo);
		
		===
		===
		Before the completeness check is executed
		We need to attach one or more attachments to the framebuffer
		
		An attachment is a memory location that can act as a buffer for the framebuffer
		Think of it as an image

		When creating an attachment 
		WE have two options to make: textures OR renderbuffer objects
		
	=== Texture attachments
	===
		,,,
		when attaching a texture to a framebuffer
		all rendering commands will write to the texture
		as if it was a normal color/depth/stencil buffer

		the advantage of using textures is 
		that the result of all rendering operations will be stored as a texture image 
		that we can then easily use in our shaders
		
		,,,
		creating a texture for a framebuffer is roughly the same as a normal texture

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(gl_texture_2d, texture);
			glTexImage2D(gl_texture_2d,0,., 800, 600,...,NULL)
			glTexParameteri(gl_texture_2d,....)
			glTexparameteri(gl_texture_2d,....)

		The main differences here are that
		we set the dimensions equal to the screen size (although this is not required) and
		we pass NULL as the texture's data parameter
		
		For this texture, we're only allocating memory and not actually filling it
		Filling the texture will happen as soon as we render to the framebuffer
		
		Now that we've created a texture 
		the last thing we need to do is actually attach it to the framebuffer
		
			
		
		
		
		




 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 