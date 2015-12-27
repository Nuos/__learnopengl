	Framebuffers
	
	***				***********
		Creating a framebuffer
			==
			1st we create a framebuffer object
			2nd we bind it as the active framebuffer
			3rd we do some operations
			4th we unbind the framebuffer
			5th we delete the framebuffer object
		
			==
			For a framebuffer to be complete the following requirements have to be satisfied
				| we have to attach at least one buffer (color, depth or stencil buffer)
				| there should be at least one color attachment
				| all attachments should be complete as well (reserved memory)
				| each buffer should have the same number of samples
				
				==
				After creating-and-attaching some kind of attachment for/to the framebfufer
				it is a complete framebuffer(self-defined)
				
				AND ALL SUBSEQUENT RENDERING OPERATIONS WILL NOW RENDER TO THE CURRENTLY BOUND FRAMEBUFFER
				
				Since our framebuffer is not the default framebuffer
				the rendering commands will have no impact on the visual output of your window
				
				For this reason it is called off-screen rendering 
				while rendering to a different framebuffer
				
				To make sure all rendering operations will have a visual impact on the main window
				we need to make the default framebuffer active again by binding to ZERO-0 

	***				***********
		Texture attachments
			==
			When attaching a texture to a framebuffer
			all rendering commands will write to the texture 
			as if it was a normal color, depth or stencil buffer
			
			The advantage of using textures is that 
			the result of all rendering operations will be stored as a texture image that
			we can then easily use in our shaders
			
			==
			creating a texture for a framebuffer
				==
				For this texture
				we're only allocating memory and not actually filling it
				
				Filling the texture will happen as soon as we render to the framebuffer
			
			==
			attaching this texture to the framebuffer
				==
				Aside from the color attchments we can also attach a depth and a stencil texture to the framebuffer object
				
				It is also possible to attach both a depth buffer and a stencil buffer as a single texture

	***				***********
		Renderbuffer object attachments
			==
			Renderbuffer objects were introduced to OpenGL after textures as a possible type of framebuffer attachments
			so textures were the only attachments used in the good old days
			
			Just like a texture image 
			a renderbuffer object is an actual buffer
			E.G. an array of bytes, integers, pixels or whatever
			
			A renderbuffer object has the added advantage
			though that it stores its data in OpenGL's native rendering format 
			making it optimized for off-screen rendering to a framebuffer

				==
				Renderbuffer objects store all the render data directly into their buffer
				without any conversations to texture-specific formats
				thus making them faster as a writeable storage medium
				
				Because their data is already in its native format
				they are quite fast when writing data or simply copying their data to other buffers
				
				Operations like switching buffers are quite fast when using renderbuffer objects
			
			==
			creating a renderbuffer object
			
			== 
			binding this renderbuffer object
			
			==
			creating a depth and stencil renderbuffer object
			
			==
			attaching the renderbuffer object
			
	***				***********
		Rendering to a texture
			==
			We're going to render the scene into a color texture 
			ATTACHED to a framebuffer object we created
			
			And then draw this texture over a simple quad that spans the whole screen 
			
			The visual output is then exactly the same as without a framebuffer
			but this time it's all printed on top of a single quad
			
			
			===
			1st To create an actual framebuffer object
			2nd To bind it
			
			3rd To create a texture image that we attach as a color attachment to the framebuffer
				==
				We set the texture's dimensions equal to the width and height of the window
				and keep its data uninitialized
				
				We also want to make sure OpenGL is able to do depth(and optionally stencil testing) testing
				so we have to make sure to add a depth(and stencil) attachment to the framebuffer as well 
				
				Since we'll only be sampling the color buffer
				and not the other buffers we can create a renderbuffer object for this purpose
					==
					Creating a renderbuffer object as a depth and stencil attachment renderbuffer object
					
					Once we've allocated enough memory for the RBO we can unbind the renderbuffer
					
					Attaching the RBO to the depth and stencil attachment of the framebuffer
			
			4th Checking 
					
			5th	Unbinding the framebuffer

			===
			******
			===
				Not that the framebuffer is complete
				all we need to do to render to the framebuffer's buffers instead of the default framebuffer's 
				is simply bind to the framebuffer object
				
				All subsequent rendering commands will then influence the currently bound framebuffer
				
				All the depth and stencil operations will also 
				read from the currently bound framebuffer's depth and stencil attachments if they're available

			===
			******
			===
				So to draw the scene to a single texture we'll have to take the following steps
				#1st Render the scene as usual with the new framebuffer bound as the active framebuffer
				#2nd Bind to the default framebuffer
				#3rd Draw a quad that spans the entire screen with the new framebuffer's color buffer as its texture
					
				===
				shaders for quad
				create and configure a VAO for the screen quad
				
	***				***********
	***				***********
	***				***********
	***				***********
	,,,
	So far we've used several types of buffers:
	    A color buffer for writing color values
	    A depth buffer to write depth information
	    A stencil buffer that allows us discard certain fragments based on some condition..

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
		internal-format type should then become gl_depth_component to reflect the depth buffer's storage format
		
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
		a renderbuffer object is generally preferred since it's more optimized
		
		,,,
		http://stackoverflow.com/questions/23119433/why-do-glbindrenderbuffer-and-glrenderbufferstorage-each-take-a-target-paramet
		https://www.opengl.org/registry/specs/EXT/framebuffer_object.txt
		https://www.opengl.org/wiki/Renderbuffer_Object
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
		Renderbuffer objects could provide some optimizations in your framebuffer projects
		but it is important to realize
		when to use renderbuffer objects and 
		when to use textures
		
		The general rule is that
		if you never need to sample data from a specific buffer
		it is wise to use a renderbuffer object for that specific buffer
		if you need to someday sample data from a specific buffer like colours or depth values
		you should use a texture attachment instead
		
		Performance-wise it doesn't have an enormous impact though
		,,,
		
		=== Rendering to texture
		===
		,,,
		Now that we know how framebuffers (sort of) work 
		it's time to put them to good use 
		
		We're going to render the scene into a color texture 
		attached to a framebuffer object we created and 
		then draw this texture over a simple quad that spans the whole screen
		
		The visual output is then exactly the same as without a framebuffer
		but this time it's all printed on top of a single quad
		
		Now why is this useful? In the next section we'll see why.
		
		,,,
		First thing to do is to create an actual framebuffer object and bind it
		this is all relatively straightforward
			
			GLuint framebuffer;
			glGenFramebuffers(1, &framebuffer);
			glBindFramebuffer(gl_framebuffer, framebuffer);
		
		,,,
		Next we create a texture image that we attach as a color attachment to the framebuffer
		
		We set the texture's dimensions equal to the width and height of the window 
		and keep its data uninitialized
		
			,,,
			//Generate texture
			GLuint texColorBuffer;
			glGenTextures(1, &texColorBuffer);
			glBindTexture(gl_texture_2d, texColorBuffer);
			glTexImage2D(gl_texture_2d, 0, gl_rgb, 800, 600, 0, gl_rgb, gl_unsigned_byte, NULL);
			glTexParameteri(gl_texture_2d, gl_texture_min_filter, gl_linear);
			glTexParameteri(gl_texture_2d, gl_texture_mag_filter, gl_linear);
			glBindTexture(gl_texture_2d, 0);
			
			// Attach it to currently bound framebuffer object
			glFramebufferTexture2D(gl_framebuffer, gl_color_attachment0, gl_texture_2d, texColorBuffer, 0);
			,,,
		
		,,,
		We also want to make sure OpenGL is able to do depth testing 
			(and optionally stencil testing if you're into that)
		so we have to make sure to add a depth (and stencil) attachment to the framebuffer as well
		Since we'll only be sampling the color buffer and not the other buffers 
		we can create a renderbuffer-object for this purpose
		
		Remember that they're a good choice when you're not going to sample from the specific buffers ??
		
		,,,
		Creating a renderbuffer-object isn't too hard
		The only thing we have to remember is that 
		we're creating it as a depth and stencil attachment renderbuffer-object
		
		We set its internal format to gl_depth24_stencil8 
		which is enough precision for our purpose
			,,,
			GLuint RBO;
			glGenRenderbuffers(1, &RBO);
			glBindRenderbuffer(gl_renderbuffer, RBO);
			glRenderbufferStorage(gl_renderbuffer, gl_depth24_stencil8, 800, 600);
			glBindRenderbuffer(gl_renderbuffer, );
			,,,
			
		,,,
		Once we've allocated enough memory for the renderbuffer
		
		Then as a final step before we can complete the framebuffer 
		we attach the renderbuffer-object to the depth and stencil attachment of the framebuffer
			,,,
			glFramebufferRenderbuffer(gl_framebuffer, gl_depth_stencil_attachment, gl_renderbuffer, RBO);
			,,,
			
		,,,
		Then as a final measure we want to check if the framebuffer is actually complete and if it's not
		we print an error msg
			,,,
			if(glCheckFramebufferStatus(gl_framebuffer) != gl_framebuffer_complete) {
			    cout << "Error:framebuffer:framebuffer is not complete...\n\n"
			}
			glBindFramebuffer(gl_framebuffer, 0);
			,,,
			
		,,,
		Then also be sure to unbind the framebuffer to make sure 
		we're not accidentally rendering to the wrong framebuffer
		
		Now that the framebuffer is complete 
		all we need to do 
			to render to the framebuffer's buffers instead of the default framebuffers
		is simply bind to the framebuffer object
		
		All subsequent rendering commands will then influence the currently bound framebuffer
		
		All the depth and stencil operations will also read from the currently bound framebuffer's depth 
		and stencil attachments if they're available
		
		If you were to omit a depth buffer for example
		all  depth testing operations will no longer work
		because there's not a depth buffer present in the currently bound framebuffer
		
		,,,,,
		So
		to draw the scene to a single texture we'll have to take the following steps
			#1 render the scene as usual with the new framebuffer bound as the active framebuffer
			#2 bind to the default framebuffer
			#3 draw a quad that spans the entire screen with the new framebuffer's color buffer as its texture
		
		,,,
		We'll draw the same scene we've used in the depth testing tutorial
		but this time with the old-school container texture
		
		,,,
		To draw the quad we're going to create a fresh set of simple shaders
		We're not going to include any fancy matrix transformations
		since we'll just be supplying the vertex coordinates as normalized device coordinates
		So we can directly specify them as the output of the vertex shader
		
		The vertex shader looks like
			,,,
			#version 330 core
			layout (location = 0) in vec2 position;
			layout (location = 1) in vec2 texCoords;
			out vec2 TexCoords;
			void main()
			    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
				TexCoords = texCoords;
			,,,
		,,,
		The fragment shader will be even more basic since the only thing we have to do is sample from a texture
			,,,
			#version 330 core
			in vec2 TexCoords;
			out vec4 color;
			uniform sampler2D screenTexture;
			void main()
			    color = texture(screenTexture, TexCoords);
			,,,
		,,,
		It is then up to you to create and configure a VAO for the screen quad
		
		A render iteration of the framebuffer procedure then has the following structure
			,,,
			//First pass
			glBindFramebuffer();
			glClearColor()
			glClear()
			glEnable(gl_depth_test);
			
			//Second pass
			glBindFramebuffer();
			glClearColor()
			glClear()
			
			screenShader.Use();
			glBindVertexArray(quadVAO);
			glDisable(gl_depth_test);
			glBindTexture(gl_texture_2d, textureColorbuffer);
			glDrawArrays(gl_triangles, 0, 6);
			glBindVertexArray(0);
			
		,,,
		There are a few things to note
		First since each framebuffer we're using has its own set of buffers
		we want to clear each of those buffers with the appropriate bits set by calling glClear()
		
		Second when drawing the quad 
		we're disabling depth testing since we don't really care about depth testing 
		because we're drawing a simple quad
		
		we'll have to enable depth testing again when we draw the normal scene though
		
		
		,,,
		The left shows the visual output which is exactly the same as we've seen in the depth-testing tutorial
		But this time rendered to a simple quad
		
		If we render the scene in wireframe it becomes obvious
		we've only drawn a single quad in the default framebuffer
		
		
		,,,,
		So what was the use of this again??
		Because we can now freely access each of the pixels of the completely rendered scene 
		as a single texture image
		
		We can create some interesting effects in the fragment shader
		The combination of all these interesting effects are called post-processing effects..
		
		
	==== Post-processing
	====
		Now that the entire scene is rendered to a single texture we can create some interesting effects
		simply by manipulating the texture data
		
		In this section we'll show you some of the more popular post-processing effects 
		and how you might create your own with some added creativity
		
		===
		=== Inversion
		We have access to each of the colors of the render output 
		so it's not so hard return the inverse of these colors in the fragment shader
		
		We're taking the color of the screen texture and inverse it by subtracting it from 1.0
			,,,
			void main()
				color = vec4(vec3(1.0f - texture(screenTexture, TexCoords)), 1.0f);
			,,,
		
		===
		=== GrayScale
		Another interesting effect is to remove all colors from the scene 
		except the white, gray and black colors effectively grayscaling the entire image
		
		An easy way to do this is simply by taking all the color components and averaging their results
			,,,
			void main
				color = texture(screenTexture, TexCoords);
				float average = (color.r + color.g + color.b) / 3.0f;
				color = vec4(average, average, average, 1.0f);
			,,,
		,,,
		
		===
		=== Kernel effects
		Another advantage about doing post-processing on a single texture image is that
		we can actually sample color values from other parts of the texture
		
		We could for example take a small area around the current texture coordinate and
		sample multiple texture values around the current texture value
		
		we can then create interesting effects by combining them in creative ways.
		
		,,,
		
		===
		=== Blur
		,,,
		A kernel that creates a blur effect is defined as follows:
		,,,
		
		===
		=== Edge detection
		,,,
		It probably does not come as a surprise that 
		kernel like this are used as image-manipulating tools/filters in tools like Photoshop
		
		Because of a graphic card's ability to process fragments with extreme parallel capabilities
		we can manipulating images on a per-pixel basis in real-time with relative ease
		
		Image-editing tools therefore tend to use graphics cards more often for image-processing.

		,,,,,,,,,,,,
		|
		|
		|
		___________End__________
