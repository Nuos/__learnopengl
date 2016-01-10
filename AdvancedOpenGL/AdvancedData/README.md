
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
		






















































































































































