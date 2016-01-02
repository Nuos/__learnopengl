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







			