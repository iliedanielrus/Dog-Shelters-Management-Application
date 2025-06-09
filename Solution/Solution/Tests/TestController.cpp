#include "TestController.h"
#include "TestDog.h"
#include "TestRepository.h"
#include "TestAdminService.h"
#include "TestUserService.h"
#include "TestTextFileRepo.h"

void testAll()
{
	testAllDog();
	testAllRepository();
	testAllAdminService();
	testAllUserService();
	testAllTextFileRepo();
}