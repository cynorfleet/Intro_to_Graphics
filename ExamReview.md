1. # glGenVertexArrays();
<!-- https://youtu.be/6-9XFm7XAT8?t=3050 -->

    ### What
        Requests a generated VAO names/index.

        Returns n names/indices to use as vertex-array objects for the passed-in array. These are used for allocating buffer objects.

    ### When
        Called when you need to find a location WHERE you can store vertex data on the GPU, typically done before you begin parsing vertex info.

2. # glBindVertexArray();
<!-- https://youtu.be/6-9XFm7XAT8?t=3050 -->

    ### What
        Binds(ties current VAO to array data) or makes the current VAO active.

    ### When
        Updating VBOs associated w/ this VAO

        Binding VAO for use in rendering

        After VAO has been generated

3. # GLuint Loc = glGetUniformLocation(program, “variable”);

    ### 
