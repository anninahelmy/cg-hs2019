Assignment 7 - Joana Portmann, Ann Kiener

We started by implementing to projection and view matrices since this was described
as the most difficult part. We filled in the code in m_constructLightProjectionMatrix()
and then also in m_constructLightViewMatrix(). We also defined the upVectors and
used the current eye's view matrix and the mat4::look_at function to help
pointing the camera through the specified cube face.

Then we enabled the glBlendFunc so that with each iteration the lights add to the 
rendering and do not overwrite it. We studied the documentation and quickly had a 
solution for this part of the assignment.

Then for the second main part of this exercise and particularly the 
implementation of the Phong shading model in phong_shadow.frag, we filled
in the missing code which renders the diffuse and specular contributions to unshaded 
fragments only. This was familiar to us from previous assignments.

 - Problem: The Vertex Light vector pointed at first in the wrong direction, so we
		had to debug for awhile to figure out what was wrong since there 
		was no shadow.


Then also in the part 'writing fragment shaders' we implemented the missing code
in shadowmap_gen.frag, which also was not too difficult to compute the distance from
the light to the scene by keeping in mind what was discussed in the lecture.