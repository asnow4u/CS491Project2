#include <stdio.h>
#include <string>
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
	glm::vec3 origin = inputPoint - centerPoint;
	//Identity matrix
	glm::mat4 identity_matrix = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));

	//Move to origin
	glm::mat4 matrix = translate(identity_matrix, origin);

	//Scale
	matrix = scale(matrix, scale);

	//Move back
	matrix = translate(matrix, inputPoint);

	return origin;
}



glm::vec3
RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third )
{
	//???
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

	//teting
	glm::mat4 mat1 = glm::mat4(glm::vec4(2, 2, 2, 2), glm::vec4(3, 3, 3, 3), glm::vec4(4, 4, 4, 4), glm::vec4(3, 3, 3, 3));
	glm::mat4 mat2 = glm::mat4(glm::vec4(3, 3, 3, 3), glm::vec4(4, 4, 4, 4), glm::vec4(3, 3, 3, 3), glm::vec4(2, 2, 2, 2));
	glm::vec3 vec1 = glm::vec3(5, 5, 5);
	glm::vec3 vec2 = glm::vec3(3, 4, 5);
	glm::vec3 scale = glm::vec3(2, 2, 2);


	PrintMatrix(Multiply(mat1, mat2));

	std::cout << Multiply(mat1, vec1) << std::endl;

	ScalePointAroundAnotherPoint(vec1, vec2, scale);

	return 0;
}
