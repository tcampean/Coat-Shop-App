cmake_minimum_required(VERSION 3.17)
project(a10_912_Campean_Tudor_Alexandru_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:\\Qt\\6.0.3\\mingw81_64")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(QT_VERSION 6)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)

include_directories(.)

add_executable(a10_912_Campean_Tudor_Alexandru_1
        Coat.cpp
        Coat.h
        Repository.cpp
        Repository.h Service.cpp Service.h UI.cpp UI.h main.cpp HTMLRepository.cpp HTMLRepository.h CSVRepository.cpp CSVRepository.h Validators.cpp Validators.h WriteRepository.cpp WriteRepository.h GUI.cpp GUI.h CoatTableModel.cpp CoatTableModel.h UndoRedo.cpp UndoRedo.h)

target_link_libraries(a10_912_Campean_Tudor_Alexandru_1 Qt6::Core Qt6::Gui Qt6::Widgets )
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)