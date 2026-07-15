cmake_minimum_required(VERSION 3.5)


# 分组：ftp
set(Ftp_Cpp_Without_Prefix
    ascii_istream.cpp ascii_ostream.cpp binary_istream.cpp
    binary_ostream.cpp client.cpp control_connection.cpp data_connection.cpp
    file_list_reply.cpp file_size_reply.cpp istream_adapter.cpp net_utils.cpp
    ostream_adapter.cpp replies.cpp reply.cpp utils.cpp
)
set(Ftp_Header_Without_Prefix
    client.hpp detail/ascii_istream.hpp detail/ascii_ostream.hpp
    detail/binary_istream.hpp detail/binary_ostream.hpp
    detail/control_connection.hpp detail/data_connection.hpp
    detail/net_utils.hpp detail/utils.hpp
    file_list_reply.hpp file_size_reply.hpp
    ftp.hpp ftp_exception.hpp ftp_global.hpp observer.hpp
    replies.hpp reply.hpp stream/input_stream.hpp stream/istream_adapter.hpp
    stream/ostream_adapter.hpp stream/output_stream.hpp
    transfer_callback.hpp transfer_mode.hpp transfer_type.hpp
)

foreach(file IN LISTS Ftp_Cpp_Without_Prefix)
    list(APPEND Ftp_Src ${CMAKE_CURRENT_SOURCE_DIR}/ftp/${file})
endforeach()

foreach(file IN LISTS Ftp_Header_Without_Prefix)
    list(APPEND Ftp_Src ${CMAKE_CURRENT_SOURCE_DIR}/ftp/${file})
endforeach()

# 所有平台共用的源代码
set(InoRobUdf_Public_Src
    inorobudf_global.h
    udf.cpp
    udf.h
    udf_p.h
    pch.h
)

# 在VS中按目录层级组织源代码
# if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
# 	file(GLOB_RECURSE SOURCE_FILES "*.h")
# 	foreach(SOURCE_FILE ${SOURCE_FILES})
# 		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
# 		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
# 		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
#                 string(REPLACE "\\src\\Model\\InoRobUdf" "" SOURCE_PATH ${SOURCE_PATH})
# 		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
# 	endforeach(SOURCE_FILE)
	
# 	file(GLOB_RECURSE SOURCE_FILES "*.cpp")
# 	foreach(SOURCE_FILE ${SOURCE_FILES})
# 		get_filename_component(SOURCE_PATH ${SOURCE_FILE} DIRECTORY)
# 		string(REPLACE ${CMAKE_SOURCE_DIR} "" SOURCE_PATH ${SOURCE_PATH})
# 		string(REPLACE "/" "\\" SOURCE_PATH ${SOURCE_PATH})
#                 string(REPLACE "\\src\\Model\\InoRobUdf" "" SOURCE_PATH ${SOURCE_PATH})
# 		source_group(${SOURCE_PATH} FILES ${SOURCE_FILE})
# 	endforeach(SOURCE_FILE)
# endif()

# 工业 示教器2.0配置
if(  Platform_Industy_TP_2_0_Msvc_Win
  OR Platform_Industy_TP_2_0_Linux_Arm_Gcc
  OR Platform_Industy_TP_2_0_Linux_Gcc_X86_64)
    include(cmake/Industry_TP_2_0.cmake)
# 协作示教器配置
elseif(  Platform_Cobot_TP_MinGW_Win
      OR Platform_Cobot_TP_Msvc_Win
      OR Platform_Cobot_TP_Android_Arm_V7a
      OR Platform_Cobot_TP_Android_Arm_64_V8a
      OR Platform_Cobot_TP_Android_X86
      OR Platform_Cobot_TP_Android_X86_64)
    include(cmake/Cobot_TP.cmake)
endif()
