#cmake软件要求的必要格式，设置cmake的最低版本
cmake_minimum_required(VERSION 3.15)

#生成的VS解决方案的名称
project(CMakeProject)

#将第三方库路径用字符LIBPACK_DIR来代替，并将路径设置为D:\MSTMMSim\LibPack
set(LIBPACK_DIR D:/MSTMMSim/LibPack)

#设置项目中的.h头文件分组，分组名称为Headers
SET(Header_Files
     csv_MatrixXd_IO.h
	 IClude.h
	 InputDate.h
	 InputFile.h
	 
)
SOURCE_GROUP("Headers" FILES ${Header_Files})

#设置项目中的.cpp源文件分组，分组名称为Sources
SET(Source_Files
     InputFile.cpp
	 Main.cpp
	 InputDate.cpp
)
SOURCE_GROUP("Sources" FILES ${Source_Files})

#设置项目中.ui文件分组(VS项目中的文件分组)，分组名称为Forms
SET(Forms_Files

)
SOURCE_GROUP("Forms" FILES ${Forms_Files})

#设置项目中其它文件(例如资源文件等)分组，分组名称为Resources
#此项目中暂时没有资源文件
SET(Resources_Files

)
SOURCE_GROUP("Resources" FILES ${Resources_Files})

#需要生成ui_xxx.h的xxx.ui文件集合UIC_SRCS
SET(UIC_SRCS

)

#需要生成moc_xxx.cpp的xxx.h文件集合MOC_HDRS
SET(MOC_HDRS

)

#要先用find_package找到Qt的库，才能调用其中的函数
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#调用Qt的UIC.exe将生成ui_xxx.h
#集合UIC_SRCS中的xxx.ui文件，生成的ui_xxx.h文件存放到集合UIC_HDRS中
qt5_wrap_ui(UIC_HDRS ${UIC_SRCS})

#调用Qt的MOC.exe将xxx.h生成moc_xxx.cpp
#集合MOC_HDRS中的xxx.h文件，生成的moc_xxx.cpp文件存放到集合MOC_SRCS中
qt5_wrap_cpp(MOC_SRCS ${MOC_HDRS})

#将生成的moc_xxx.cpp文件集合MOC_SRCS设置一个分组名称为“Moc”
SOURCE_GROUP("Moc" FILES ${MOC_SRCS})

#将所有的源文件分组形成一个集合SRCS
SET(SRCS
	${Header_Files}
	${Source_Files}
	${Forms_Files}
	${Resources_Files}
	${MOC_SRCS}
)

#设置附加包含目录
#CMAKE_CURRENT_SOURCE_DIR为源代码所在目录
#CMAKE_CURRENT_BINARY_DIR为cmake的生成的工程文件build目录
#其余为需要的第三方库路径
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${LIBPACK_DIR}/include
	${LIBPACK_DIR}/include/QtCore
	${LIBPACK_DIR}/include/QtWidgets
	${LIBPACK_DIR}/include/QtGui
	${LIBPACK_DIR}/include/QtXml
	${LIBPACK_DIR}/include/Qwt
	${LIBPACK_DIR}/include/eigen3/Eigen
     ${LIBPACK_DIR}/include/eigen3
)

#设置第三方lib库的路径
link_directories(${LIBPACK_DIR}/lib)

#MSVC代表Microsoft Visual C++
#如果生成的是MSCV工程，则设置工程的启动方式为WINDOWS，程序入口为mainCRTStartup
#MSVC默认为Console控制台项目
#如果不设置此选项，则程序运行时，会先出现一个Console控制台，再出现程序主界面
#此项设置必须在ADD_EXECUTABLE语句之前
#if(MSVC)
	#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif()

#将所有源文件添加到名为CMakeProject的项目中
#此处的CMakeProject为项目名称，非解决方案的名称
#项目名称可以与解决方案同名
ADD_EXECUTABLE(CMakeProject ${SRCS})

#编译宏定义
target_compile_definitions(CMakeProject PUBLIC "H5_BUILT_AS_DYNAMIC_LIB")

# 因为大量使用模板,导致代码增大,MSVC下要用/bigobj选项,否则会报错:error C1128
# GNU compiler 要用 -Wa,-mbig-obj 选项

target_compile_options(CMakeProject 
	PRIVATE 
	$<$<CXX_COMPILER_ID:MSVC>:/bigobj> 
	$<$<CXX_COMPILER_ID:GNU>:-Wa,-mbig-obj>) 

add_definitions(-DUNICODE -D_UNICODE)


#如果是MSCV平台，设置程序的默认启动项目为CMakeProject
#cmake默认会额外自动生成ALL_BUILD和ZERO_CHECK两个项目
#在VS中构建ALL_BUILD项目会导致工程中的所有项目均被构建，相当于生成解决方案
#构建ZERO_CHECK项目会检查生成工程的CMakeLists.txt文件(也就是本文件)是否有更新。
#如果有更新，将会自动运行CMake重新生成工程文件。
if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CMakeProject)
endif()

#设置所依赖的第三方库的lib文件为一个集合LIBS
#其中optimized表示Release模式下用到的lib文件
#debug表示debug模式下用到的lib文件
#target_link_libraries命令将第三方库lib链接到CMakeProject项目中
set(LIBS
	optimized Qt5Core.lib
	optimized Qt5Widgets.lib
	optimized Qt5Gui.lib
	optimized Qt5Xml.lib
	optimized qwt.lib
	debug Qt5Cored.lib
	debug Qt5Widgetsd.lib
	debug Qt5Guid.lib
	debug Qt5Xmld.lib
	debug qwtd.lib
	optimized qwtplot3d.lib
	optimized OpenGL32.Lib
	optimized GlU32.lib
	optimized hdf5.lib
	optimized hdf5_cpp.lib
	debug Qt5Test.lib
	debug OpenGL32.Lib
	debug GlU32.lib
	debug hdf5_D.lib
	debug hdf5_cpp_D.lib

)
target_link_libraries(CMakeProject ${LIBS})
