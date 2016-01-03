	Cubemaps

	*** glTexImage2D()
	
			The function glTexImage2D() generates the TEXTURE-IMAGE on the current-bound TEXTURE_OBJCET
	
			The function glTexImage2D() generates the texture image on the current bound texture object
				at the active texture unit 
			The function expects destination and source data from 
				where the source image is expected to be an array of data (usually a byte array)
			
			glTexImage2D(GLenum target,//specifies the texture target: gl_texture_1d, gl_texture_2d, gl_texture_3d
						 GLint level,//specifies the level-of-detail number
						 GLint internalFormat,//specifies the number of color components in the texture
						 GLsizei width,//the width of the texture image
						 GLsizei height,//the height of the texture image
						 GLint border,//this value must be ZERO
						 GLenum format,//the format of the pixel data
						 GLenum type,//the data type of the pixel data
						 const GLvoid* data//a pointer to the image data in memory
			);
					
					//Load and generate the texture
					int width, height ;
					unsigned char* image = SOIL_load_image(path, &width, &height, 0, soil_load_rgb);
					glTexImage2D(gl_Texture_2D, 0, gl_rgb, width, height, 0, gl_rgb, gl_unsigned_byte, image);
		
					
	***	glTexParameteri()// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
			
			The function glTexParameteri() set TEXTURE-PARAMETERS
			
			glTexParameteri(GLenum target,//the target texture of the active texture uint,
									// which must be gl_texture_2d/gl_texture_cube_map
							GLenum pname,//the symbolic name of a single-valued texture parameter
									// @pname can be gl_texture_min/mag_filter or gl_texture_wrap_s/t
							GLint param//the value of @pname
			);

			Des:
				Texture mapping is a technique that applies an image onto an object's surface
				as if the image were a decal or cellophane shrink-wrap
				
				The image is created in texture space
				with an (s,t) coordinate system
				
				A texture is a two-dimensional or cube-mapped image and 
				a set of parameters that determine how samples are derived from the image
				
				glTexParameter() assigns the value or values in @params to the texture parameter specified as @pname
				
	*** 
	=== creating a cubemap
		A cubemap is a texture like any other texture so to create one we generate a texture and
		bind it to the proper texture-target before we do any further  texture operations
		
			GLuint loadCubemap(std::vector<const GLchar*> faces)
			{
				int width = 0, height = 0;
				unsigned char* image = nullptr;
				
				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(gl_texture_cube_map, textureID);
				for (GLuint i = 0; i < faces.size(); ++i) {
					image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
					glTexImage2D(gl_texture_cube_map_positive_x + i, 
								 0, gl_rgb, width, height, 0, gl_rgb,
								 gl_unsigned_byte, image);
					SOIL_free_image_data(image);
					image = nullptr;
					width = height = 0;
				}
				
				glTexParameteri(gl_texture_cube_map, gl_texture_mag_filter, gl_linear);
				glTexParameteri(gl_texture_cube_map, gl_texture_min_filter, gl_linear);
				glTexParameteri(gl_texture_cube_map, gl_texture_wrap_s, gl_clamp_to_edge);
				glTexParameteri(gl_texture_cube_map, gl_texture_wrap_t, gl_clamp_to_edge);
				glTexParameteri(gl_texture_cube_map, gl_texture_wrap_r, gl_clamp_to_edge);
				glBindTexture(gl_texture_cube_map, 0);
				
				return textureID;
			}
			
		Then before drawing the objects that will use the cubemap
		we active the corresponding texture unit and bind the cubemap before rendering
		not much of a difference compared to normal 2D textures
		
		Within the fragment shader we also have to use a different sampler of the type samplerCube
		that we sample from using the texture function
		but this time using a vec3 direction vector instead of a vec2
		
			in vec3 textureDir;
			uniform samplerCube cubemap;
			void main()
			{
				color = texture(cubemap, textureDir);
			}
	
	
	
	
	/****			****/
	
	*** skybox
		#0 Loading a skybox  // GLuint loadCubemap(std::vector<const GLchar*> faces);
		#1 Displaying a skybox // cubeVAO- cubeVBO- cubeVertices[]-  new-set-of-shaders
				
				// vertex-shader
				#version 330 core
				layout (location = 0) in vec3 position;
				out vec3 TexCoords;
				uniform mat4 projection;
				uniform mat4 view;
				void main()
					gl_Position = projection * view * vec4(position, 1.0f);
					TexCoords = position;
				
				//fragment-shader
				#version 330 core
				in vec3 TexCoords;
				out vec4 color;
				uiform samplerCube skybox;
				void main() 
					color = texture(skybox, TexCoords);
		
		Rendering the skybox is easy now that we have a cubemap texture
		we simply bind the cubemap texture and 
		the skybox sampler is automatically filled with the skybox cubemap
		
		To draw the skybox we're going to draw it as the first object in the scene and disable depth writing
		This way the skybox will always be drawn at the background of all the other objects
		
			//
			glDepthMask(gl_false);
			skyboxShader.Use();
			// :.: set view and projection matrix
			glBindVertexArray(skyboxVAO);// vertices
			glBindTexture(gl_texture_cube_map, cubemapTexture);// texture
			glDrawArrays(gl_triangles, 0, 36);// primitive
			glBindVertexArray(0);
			glDepthMask(gl_true);
			// :.: draw rest of the scene
			
		The curent view matrix however transforms all the skybox's positions 
		by rotating, scaling and translating them
		so if the player moves the cubemap moves as well
		
		We want to remove the translation part of the view matrix 
		so movement doesn't affect the skybox's position vectors
		
		
		We could remove the translation section of transformation matrices
		by taking the upper-left-(3X3) matrix of the (4X4) matrix
		effectively removing the tanslation components
		We can achieve this by simply converting 
							the view matrix to a (3X3) matrix (removing translation) and
							converting it back to a (4X4) matrix
							glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
							
							This remvoes any translation
							but keeps all rotation transformations 
							so the user can still look around the scene
							
	**** An Optimization
		...
		If we render the skybox first we're running the fragment shader for each pixel on the screen
		even though only a small part of the skybox will eventually be visible
		Fragments that could have easily been discarded using early depth testing saving us valuable bandwidth
		
		SO to give us a slight performance boost 
		we're going to render the skybox's fragments
		wherever the early depth test passes greatly reducing the calls to the fragment shader
		
		....
		Perspective-division is performed after the vertex shader has run
		dividing the gl_Position's xyz-coordinates by its w-component
		
		...the z-component of the resulting division is applied its z-component translates to w/w = 1.0f
		
			// skybox.vs
			void main() 
				vec4 pos = projection * view * vec4(position, 1.0f);
				gl_Position = pox.xyww;
				TexCoords = position;
			
			The resulting normalized device coordinates will then 
			always have a z-value equal to 1.0f: the maximum depth value
			
			The skybox will as a result only be rendered wherever there are no objects visible
			(only then it will pass the depth test everything else is in front of the skybox)
										
	**** Environment mapping
	







 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 