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

			glFramebufferTexture2D(gl_framebuffer, 
								   gl_color_attachment0, 
								   gl_texture_2d,
								   texture,
								   0);

			@param target
				the framebuffer type -we're targeting(draw/read/OR-both)
			@param attachment
				the type of attachment we're going to attach
				right now we're attaching a color attachment
				the 0 at the end suggests we can attach more than 1 color attachment
			@param textarget
				the type of the texture you want to attach
			@param texture
				the actual texture to attach
			@param level
				the mipmap level
		
		===
		===
		,,,
		aside from the color attachments
		we can also attach a depth and a stencil texture to the framebuffer object
		
		to attach a depth attachment we specify the attachment type as gl_depth_attachment
		note that the texture's format and 
		internalformat type should then become gl_depth_component to reflect the depth buffer's storage format
		
		to attach a stencil buffer you use gl_stencil_attachment as the second argument and
		specify the texture's formats as gl_stencil_index
		
		,,,
		it is also possible to attach both a-depth-buffer and a-stencil-buffer as a single texture
		
		each 32-bit value of the texture then 
		consists for 24-bits of depth information and 8-bits of stencil information
		
		to attach a depth and stencil buffer as one texture we use the gl_depth_stencil_attachment type and
		configure the texture's formats to contain combined depth and stencil value
		
		 an example of attaching a-depth-and-stencil-buffer as one texture to the framebuffer is given below
			glTexImage2D(gl_texture_2d,
						 0,
						 gl_depth24_stencil8,
						 800, 600,
						 0,
						 gl_depth_stencil,
						 gl_usigned_int_24_8,
						 NULL);
			glFramebufferTexture2D( gl_framebuffer,
									gl_depth_stencil_attachment,
									gl_texture_2d,
									texture,
									0);

		=== Renderbuffer object attachments
		===
		,,,
		Renderbuffer objects were introduced to OpenGL 
		after textures as a possible type of framebuffer attachments
		so textures were the only attachments used in the good old days

		Just like a texture image
		a renderbuffer object is an actual buffer E.g. 
			an array of bytes- integers- pixels- or whatever-

		A renderbuffer object has the added advantage
		though that it stores its data in OpenGL's native rendering format
		making it optimized for off-screen rendering to a framebuffer

		,,,
		Renderbuffer objects store all the render data directly into their buffer
		without any conversions to texture-specific formats
		thus making them faster as a writeable storage medium

		However- renderbuffer objects are generally write-only
		thus you cannot read from them (like with texture-access)

		It is possible to read from them via glReadPixels() though
		that returns a specified area of pixels from the currently bound framebuffer
		but not directly from the attachment itself

		,,,
		Because their data is already in its native format 
		they are quite fast when writing data or simply copying their data to other buffers

		Operations like switching buffers are thus quite fast when using renderbuffer objects

		The glfwSwapBuffers() we've been using at the end of each render iteration
		might as well be implemented with renderbuffer objects
		  we simply write to a renderbuffer image
		  and swap to the other one at the end
		
		Renderbuffer objects are perfect for these kind of operations
		
		,,,
		Creating a renderbuffer object looks similar to the framebuffer's code
			GLuint RBO;
			glGenRenderbuffers(1, &RBO);

		And similarly we want to bind the renderbuffer object 
		so all subsequent renderbuffer operations affect the current RBO
			glBindRenderBuffer(	gl_renderbuffer, 
								RBO
							);

		,,,
		Since renderbuffer objects are generally write-only
		they are often used as depth and stencil attachments since 
		most of the time we don't really need to read values from the depth and stencil buffers
		but still care about depth-and-stencil-testing
		
		We need the depth-and-stencil-values for testing
		but don't need to sample these values so a renderbuffer object suits this perfectly
		
		When we're not sampling from these buffers
		a renderbuffer object is generally perferred since it's more optimized
		
		,,,
		Creating a depth-and-stencil-renderbuffer-object is done
		by calling the glRenderbufferStorage()
			glRenderbufferStorage(	gl_renderbuffer,
									gl_depth24_stencil8, 
									800, 600
								);

		,,,
		Creating a renderbuffer object is similar to texture objects
		the difference being that this object is specifically designed to be used as an image
		instead of a general purpose data buffer like a texture

		Here we've chosen the gl_depth24_stencil8 as the internal format
		which holds both the depth and stencil buffer with 24-and-8-bits respectively
		
		,,,
		Last thing left to do is actually attach the renderbuffer object
			glFramebufferRenderbuffer(	gl_framebuffer, 
										gl_depth_stencil_attachment, 
										gl_renderbuffer, 
										RBO
									);

		,,,



		
		




 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 