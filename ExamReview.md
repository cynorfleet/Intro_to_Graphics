# Christian Norfleet #
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
        - Program: specifies the index location of the desired Shader

        - "variable": is the name of the variable in the Shader
    #### What
       glGetUniformLocation returns an integer that represents the location of a specific uniform variable within a program object.

       GLuint vPosition stores that integer in vPosition
    ####  When
       The actual locations assigned to uniform variables are not known until the program object is linked successfully. After linking has occurred, the command glGetUniformLocation can be used to obtain the location of a uniform variable.
4. ## GLuint vPosition = glGetAttribLocation(program, “vPosition”);
<!-- https://youtu.be/6-9XFm7XAT8?t=3500 -->
    #### Parameters
        - Program: specifies the index location of the desired Shader

        - "vPosition": is the name of the variable in the Shader
    #### What
       glGetAttribLocation connects application data to Shader variables. Tells application where in the shader the attribute (variable) is.
    #### When
       May be called after data is sent to GPU via Gen/Bind.
5. ## glUniformMatrix4fv(ModelViewLoc, 1, GL_TRUE, model_view);
<!-- http://ogldev.atspace.co.uk/www/tutorial06/tutorial06.html -->
    #### Parameters
        - ModelViewLoc: an integer value of location of the uniform variable (retrieved after shader compilation using glGetUniformLocation()

        - 1: indicates the number of matrices we are updating

        - GL_TRUE: indicates whether the matrix is supplied in row-major or column-major order.
        Row-major means the matrix is supplied row after row, starting from the top. Column-major
        is the same but in columns.

        - model_view: starting address of the matrix in memory
    #### What
6. ## glEnableVertexAttribArray(vPosition);
<!-- https://youtu.be/6-9XFm7XAT8?t=3677 -->
    #### What
       Enables the specified array

       Allows switching of attributes (variables in the shader).
    #### Where
       After glGetAttribLocation is called
7. ## glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
<!-- https://youtu.be/6-9XFm7XAT8?t=3718 -->
    #### What
       Tells opengl what format the attributes are in.

       vPosition consists of:
        - 4 element arrays
        - of Type GL_FLOAT
        - Does not normalize them
        - data starts at the 1st element of vPosition (offset)
        - data ends at the last element of vPosition (offset)
    #### WHERE
       After vertex is enabled (glVertexAttribPointer)
       
8. ## glDrawArrays(GL_TRIANGLES, start, length);
<!-- https://youtu.be/6-9XFm7XAT8?t=3775 -->
    #### What
       Draw the arrays as triangles.

       Start is the first vertex of the first triangle to which u wish to draw.

       Length is the amount of vertices for which u wish to draw.
    #### Where
       To be called once all the "plumbing" is complete.

9. ## LookAt()
<!-- https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml -->
    #### Parameters
        - eye: location of the camera
        - at: where you want the camera pointed at
        - up: which axis is the up direction
    #### What
       creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector
    #### Where
       Display Function
       
10. ## RotateX(theta)
<!-- https://youtu.be/6-9XFm7XAT8?t=7404  -->
    #### Parameters
         - theta: a uniform variable containg the angle for rotation.
    #### What
       A rotation matrix which rotates about the x-axis, preserving the x values
    #### Where
       Either in the shader or the application
        
11. ## glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
<!-- https://www.opengl.org/sdk/docs/man/html/glClear.xhtml -->
    #### What
        sets the bitplane area of the window to values previously selected by glClearColor, glClearDepth, and glClearStencil
    #### Where
        Display Function.
        
12. ## Ortho()
<!-- http://www.gamedev.net/topic/634155-problems-with-glmortho/ -->
    #### Parameters
         - GLdouble left: Specify the coordinates for the left vertical clipping planes.
         - GLdouble right: Specify the coordinates for the right vertical clipping planes.
         - GLdouble bottom: Specify the coordinates for the bottom clipping planes.
         - GLdouble top: Specify the coordinates for the top horizontal clipping planes.
         - GLdouble nearVal: Specify the distances to the nearer depth clipping planes.
         These values are negative if the plane is to be behind the viewer.
         - GLdouble farVal: Specify the distances to the arther depth clipping planes.
         These values are negative if the plane is to be behind the viewer.
    #### What
       If the current matrix is the projection matrix, and the projection matrix is the identity matrix, then multiplying that specific matrix into the projection matrix makes for an orthographic projection.

        A transformation that produces a parallel projection
    #### Where
       When specifying projection matrix
        
13. ## Perspective()
<!-- https://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml -->
    #### Parameters
         - GLdouble fov: specifies, in degrees, the angle in the y direction that is visible to the user
         - GLdouble aspect: is the aspect ratio of the scene, which is width divided by the height
         - GLdouble near: Specifies the distance from the viewer to the near clipping plane
         (always positive).
         - GLdouble far: Specifies the distance from the viewer to the far clipping plane
         (always positive).
    #### What
       Specifies a viewing frustum into the world coordinate system
        
14. ## glDrawArrays(GL_TRIANGLES, start, length);
<!-- https://youtu.be/6-9XFm7XAT8?t=3775 -->
    #### What
       Draw the arrays as triangles.

       Start is the first vertex of the first triangle to which u wish to draw.

       Length is the amount of vertices for which u wish to draw.
    #### Where
       To be called once all the "plumbing" is complete
