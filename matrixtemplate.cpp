#include <stdio.h>
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glm::mat4
Multiply( glm::mat4 a, glm::mat4 b )
{
	return a * b;
}



glm::vec3
Multiply( glm::mat4 a, glm::vec3 b )
{
	glm::vec4 v = glm::vec4(b, 1);
	v = a * v;
	return glm::vec3(v);
}



glm::vec3
ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale )
{
	
    //Identity matrix
	glm::mat4 identity_matrix = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));

    //Move 
    glm::mat4 inverse_matrix = translate(identity_matrix, centerPoint);

	//Scale
	glm::mat4 scale_matrix = glm::scale(inverse_matrix, scale);

	//Move 
	glm::mat4 translation_matrix = translate(scale_matrix, -centerPoint);


    return Multiply(translation_matrix, inputPoint);
	
}



glm::vec3
RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third )
{
    //Identity matrix
	glm::mat4 identity_matrix = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));

    //Move
    glm::mat4 inverse_matrix = translate(identity_matrix, centerPoint);

    //Rotate
    glm::mat4 rotate_matrix = Multiply(Multiply(Multiply(inverse_matrix, third), second), first);

    //Move 
	glm::mat4 translation_matrix = translate(rotate_matrix, -centerPoint);

    return Multiply(translation_matrix, inputPoint);
}



void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Andrew Snow";
	yourEmailAddress = "snowan@oregonstate.edu" ;
}


void
PrintMatrix( glm::mat4 mat )
{
	for( int row = 0; row < 4; row++ )
	{
		fprintf( stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3] );
	}
}

int main(){



    glm::vec3 vec1 = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 vec2 = glm::vec3(-2.0f, 0.0f, 0.0f);
	

    glm::mat4 firstRot = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 secondRot = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 thirdRot = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


    glm::vec3 result; //= Multiply(mat1, vec1);
    

	result = RotatePointAroundAnotherPoint(vec1, vec2, firstRot, secondRot, thirdRot ); 
    
    std::cout << result[0] << " " << result[1] << " " << result[2] << std::endl;



	return 0;
}
