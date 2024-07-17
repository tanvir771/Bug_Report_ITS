cmake_minimum_required(VERSION 3.29.3)

project(Bug_Report
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD             14)
set(CMAKE_CXX_STANDARD_REQUIRED    ON)
set(CMAKE_CXX_EXTENSIONS          OFF)

set(BUG_TARGET_NAME Bug_Report)

add_executable(${BUG_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/Bug.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Bug.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/Customer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Customer.h
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/Product.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Product.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/Release.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Release.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/Request.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Request.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/ScenarioControl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/ScenarioControl.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)


target_include_directories(${BUG_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(TestProduct ${CMAKE_CURRENT_SOURCE_DIR}/testing/TestProduct.cpp)

target_include_directories(TestProduct PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_sources(TestProduct PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Product.cpp)
