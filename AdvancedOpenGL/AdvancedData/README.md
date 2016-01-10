
	Advanced Data
		Tutorials for advanced data transfer
		
	****
		We've been extensively using buffers in OpenGL to store data for quite some time now
		
		There are more interesting ways to manipulate buffers and
		also other interesting methods to pass large amounts of data to the shaders via textures
		
		This tutorial we'll discuss some more interesting buffer functions and 
		how we can use texture objects to store large amounts of data
		
	***
		A buffer in OpenGL is only an object that manages a certain piece of memory
		We giving a meaning to a buffer when binding it to a specific buffer target
		
		A buffer only a vertex array buffer
		when we bind it to GL_array_buffer
		but we could just as easily bind it to GL_element_array_buffer
		
		OpenGL internally stores a buffer per target and
		based on the target, processes the buffers differently
		
	***
		So far we've been filling the memory managed by the buffer objects by calling glBufferData() 
		which allocates a piece of memory and adds data into this memory
		
		If we were to pass NULL as its data argument
		the function would only allocate memory and not fill it
		
		This is useful if we first want to reserve a specific amount of memory and
		later come back to this buffer to fill it piece by piece

	***
		Instead of filling the entire buffer with one function call
		we can also fill specific regions of the buffer by calling glBufferData()
		
		glBufferSubData() expects 
			a buffer target- 
			an offset- 
			the size of the data- 
			the actual data-
		as its arguments
		
		What's new with this function is that we can now give an offset that
		specifies from where we want to fill the buffer
		
		This allows us to insert/update only certain parts of the buffer's memory 
		
		Do note that the buffer should have enough allocated memory 
		so a call to glBufferData() is necessary before calling glBufferSubData() on the buffer
			//
			glBufferSubData(gl_array_buffer, 24, sizeof(data), &data);
	
	*****
		Yet another method for getting data into a buffer is to ask for a pointer to the buffer's memory
		and directly copy the data to the buffer by yourself
		
		By calling glMapBuffer() 
		OpenGL returns a pointer to the currently bound buffers memory for us to operate on
			//
			float data[] = {
			    0.5f, 1.0f, -0.35f
				...
			};
			glBindBuffer(gl_array_buffer, buffer);
							// get pointer
			void* ptr = glMapBuffer(gl_array_buffer, gl_write_only);
							// now copy data into memory
			memcpy(ptr, data, sizeof(data));
							// make sure to tell OpenGL we're done with the pointer
			glUnmapBuffer(gl_array_buffer);
			***
				By telling OpenGL we're finished with the pointer operations via glUnmapBuffer()
				OpenGL knows you're done 
				
				By unmapping
				the pointer becomes invalid and the function returns gl_true 
				if OpenGL was able to map our data successfully to the buffer
				
			***
				Using glMapBuffer() is useful to directly map data to a buffer
				without first storing it in temporary memory
				
				Think of directly reading data from file and copying into the buffer's memory
	
	
	
	
	Batching Vertex Attributes
	***
		Using glVertexAttribPointer() 
		we were able to specify the attribute layout of the vertex array buffer's content
		
		Within the vertex array buffer we interleaved the attributes
		that is we placed 
						the position- 
						normal and/or texture coordinates- next to each  other for each vertex
		Now that we know a bit more about buffers we could take different approach
		
		What we could also do is 
		batch all the vector data into per attribute type instead of interleaving them
		Instead of an interleaved layout 123123123123 we take a batched approach 111122223333
		
		When loading vertex data from file 
		you generally retrieve 
							an array of positions-
							an array of normals-
							an array of texture coordinates-
		
		It might cost some effort to combine these arrays into one large array of interleaved data
		Taking the batching approach is an easier solution that 
		we can easily implement using glBufferSubData()
			//
			GLfloat positions[] = { ... };
			GLfloat normals[] = { ... };
			GLfloat tex[] = { ... };
			// fill buffer
			glBufferSubData(gl_array_buffer, 0, sizeof(positions), &positions);
			glBufferSubData(gl_array_buffer, sizeof(positions), sizeof(normals), &normals);
			glBufferSubData(gl_array_buffer, + sizeof(normals), sizeof(tex), &tex);
			//
		***
			This way we can directly transfer the attribute arrays as a whole into the buffer
			without first having to process them
		
			We could also combined them in one large array and
			fill the buffer right away using glBufferData()
			but using glBufferSubData() lends itself perfectly for tasks like these
			
		***
		We'll also have to update the vertex attribute pointers to reflect these changes
			//
			glVertexAttribPointer(0, 3, gl_float, gl_false, 3*sizeof(GLfloat), 0);
			glVertexAttribPointer(1, 3,*,*, 3*sizeof(GLfloat), (GLvoid*)(sizeof(positions)));
			glVertexAttribPointer(2, 2,*,*, 2*sizeof(GLfloat), (GLvoid*)(sizeof(positions) + sizeof(normals)))
		***
			Note that the stride parameter is equal to the size of the vertex attribute
			since the next vertex attribute vector can be found directly after its 3/2 components
		
		***
		This gives us yet another approach of setting and specifying vertex attributes
		Using either approach has no immediate benefit to OpenGL
		it is mostly a more organized way to set vertex attributes
		
		The approach you want to use is purely based on your preference and the type of application
		
		
	Copying Buffers
	******
		void glCopyBufferSubData(
		  GLenum readtarget,//the target from whose data store data should be read
		  GLenum writetarget,//the target to whose data store data should be written
		  GLintptr readoffset,// the offset -in bytes- within the data store of readtarget
		  GLintptr writeoffset,// the offset -in bytes- within the data source of writetarget
		  GLsizeiptr size// the size -in bytes- of the data to be copied from rtarget to wtarget
		);
		***
		What if we wanted to read and write data into two different buffers 
		that are both vertex array buffers
		
		We can't bind two buffers at the same time to the same buffer target
		For this reason, and this reason alone
		OpenGL gives us two more buffer targets called 
								gl_copy_read_buffer-
								gl_copy_write_buffer-
		
		We then bind buffers of our choice to these new buffer targets and 
		set those targets as the readtarget and writetarget argument
		
		glCopyBufferSubData() then reads data of a given size from a given readoffset and
		writes it into the writetarget buffer at writeoffset
			// Eg.
			GLfloat vertexData[] = { ... };
			glBindBuffer(gl_copy_read_buffer, vbo1);
			glBindBuffer(gl_copy_write_buffer, vbo2);
			glCopyBufferSubData(gl_copy_read_buffer, 
								gl_copy_write_buffer,
								0,0,
								sizeof(vertexData)
			);
		
			***
			We could also done this by 
			only binding the writetarget buffer to one of the new buffer target types
			// Eg.
			GLfloat vertexData[] = { ... };
			glBindBuffer(gl_array_buffer, vbo1);
			glBindBuffer(gl_copy_write_buffer, vbo2);
			glCopyBufferSubData(gl_array_buffer, gl_copy_write_buffer, 0, 0, sizeof(vertexData));
			
 :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) :) 
 
 
 