
	Advanced GLSL
		
		This tutorial will discuss some interesting built-in variables
		new ways to organize shader's input and output and 
		a very useful tool called uniform buffer objects
		
	Vertex shader variables
	-----------------------
	***
		gl_PointSize
		---
			One of the render primitives we're able to choose from is GL_POINTS
			in which case each single vertex is a primitives and rendered as a point
			
			It is possible to set the size of the points being rendered
			via OpenGL's glPointSize() function 
			but we can also influence this value in the vertex shader
		---
			An output variable defined by GLSL is called gl_PointSize 
			that is a float variable 
			where you can set the point's width and height in pixels
			
			By describing the point's size in the vertex shader 
			you can influence this point value per vertex
		---
			Influencing the point sizes in the vertex shader is disabled by default
			but if you want to enable this 
			you'll have to enable OpenGL's GL_PROGRMA_POINT_SIZE
				// c++ source
				...
				glEnable(gl_program_point_size);
				// vertex shader source
				...
				void main()
					gl_Position = projection * view * model * vec4(position, 1.0f);
					gl_PointSize = gl_Position.z;//12.0f, 20.0f, 50.0f, OR 100.0f

	***
		gl_VertexID
		***
			The gl_Position and gl_PointSize are output variables 
			since their value is read as output from the vertex shader
			We can influence the result by writing to them
			
			The vertex shader also gives us an interesting input variable
			that we can only read from 
			called gl_VertexID
		***
			The integer variable gl_VertexID holds the current ID of the vertex we're drawing
			
			When doing indexd rendering (with glDrawElements()) 
			this variable holds the current index of the vertex we're drawing
			
			When drawing without indices (via glDrawArrays())
			this variable holds the number of the currently processed vertex 
			since the start of the render call
		***
			
	
	Fragment shader variables
	-------------------------
		within the fragment shader we also have access to some interesting variables
		GLSL gives us two interesting input variables called
			gl_FragCoord
			gl_FrontFacing

		gl_FragCoord
		***
			The z-component of the gl_FragCoord vector 
			is equal to the depth value of that particular fragment
			
			The x- and y- component of the gl_FragCoord
			are the window-space coordinates of the fragment
			originating from the bottom-left of the window
			
			We have specified a window of 800X600 with glViewport()
			so the window-space coordinates of the fragment will 
			have x values between 0 and 800
			and y values between 0 and 600
				// fragment shader source
				...
				void main()
					if (gl_FragCoord.x < 400) 
						color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
					else
						color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
		***
			
		gl_FrontFacing
		***
		
		gl_FragDepth
		***

	Interface blocks
	-------------------------
		So far
		every time we wanted to send data from the vertex to the fragment shader
		we declared several matching input/output variables
		
		To help us organize these variables 
		GLSL offers us something called -interface block-
		that allows us to group together those variables
			// vertex shader source
			#version 330 core
			layout (location = 0) in vec3 position;
			layout (location = 1) in vec2 texCoords;
			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			out VS_OUT {
			   vec2 TexCoords;
			} vs_out;
			
			void main()
				gl_Position = projection * view * model * vec4(position, 1.0f);
				vs_out.TexCoords = texCoords;
			***********
			
			// fragment shader source
			#version 330 core
			out vec4 color;
			in VS_OUT {
			   vec2 TexCoords;
			} fs_in;
			uniform sampler2D texture;
			void main() 
				color = texture(texture, fs_in.TexCoords);
			************
		
	Uniform buffer objects
	Uniform buffer objects
	------------------------- 
	






























































































 