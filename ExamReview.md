1. ## glGenVertexArrays();
<!-- https://youtu.be/6-9XFm7XAT8?t=3050 -->

    #### What
       Requests a generated VAO names/index.

       Returns n names/indices to use as vertex-array objects for the passed-in array. These are used for allocating buffer objects.

    #### When
       Called when you need to find a location WHERE you can store vertex data on the GPU, typically done before you begin parsing vertex info.

2. ## glBindVertexArray();
<!-- https://youtu.be/6-9XFm7XAT8?t=3050 -->

    #### What
       Binds(ties current VAO to array data) or makes the current VAO active.

    #### When
       Updating VBOs associated w/ this VAO.

       Binding VAO for use in rendering.

       After VAO has been generated.

3. ## GLuint Loc = glGetUniformLocation(program, “variable”);
<!-- https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetUniformLocation.xml -->

    #### Parameters
       Program: specfies the index location of the desired Shader

       "variable": is the name of the variable in the Shader

    #### What
       glGetUniformLocation returns an integer that represents the location of a specific uniform variable within a program object.

       GLuint vPosition stores that integer in vPosition

    ####  When
       The actual locations assigned to uniform variables are not known until the program object is linked successfully. After linking has occurred, the command glGetUniformLocation can be used to obtain the location of a uniform variable.

4. ## GLuint vPosition = glGetAttribLocation(program, “vPosition”);
<!-- https://youtu.be/6-9XFm7XAT8?t=3500 -->

    #### Parameters
       Program: specfies the index location of the desired Shader

       "vPosition": is the name of the variable in the Shader

    #### What
      glGetAttribLocation connects application data to Shader variables. It will link

    #### When
       May be called after data is sent to GPU via Gen/Bind.

5. ## glUniformMatrix4fv(ModelViewLoc, 1, GL_TRUE, model_view);
<!-- http://ogldev.atspace.co.uk/www/tutorial06/tutorial06.html -->

    #### Parameters
       ModelViewLoc: an integer value of location of the uniform variable (retrieved after shader compilation using glGetUniformLocation()

       1: indicates the number of matrices we are updating

       GL_TRUE: indicates whether the matrix is supplied in row-major or column-major order. Row-major means the matrix is supplied row after row, starting from the top. Column-major is the same but in columns.

       model_view: starting address of the matrix in memory

    #### What

6. ## glEnableVertexAttribArray(vPosition);
