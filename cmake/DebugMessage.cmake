
function(cobot_tp_enable_separate_debug_info target installDestination)
    if (NOT Separate_Debug_Message)
        return()
    endif()
    if (NOT UNIX AND NOT MINGW)
        cobot_tp_internal_install_pdb_files(${target} ${installDestination})
        return()
    endif()
    get_target_property(target_type ${target} TYPE)
    if (NOT target_type STREQUAL "MODULE_LIBRARY" AND
        NOT target_type STREQUAL "SHARED_LIBRARY" AND
        NOT target_type STREQUAL "EXECUTABLE")
        return()
    endif()
    get_property(target_source_dir TARGET ${target} PROPERTY SOURCE_DIR)
    get_property(skip_separate_debug_info DIRECTORY "${target_source_dir}" PROPERTY _inocobottp_skip_separate_debug_info)
    if (skip_separate_debug_info)
        return()
    endif()

    unset(commands)

    set(copy_bin ${CMAKE_OBJCOPY})
    set(strip_bin ${CMAKE_OBJCOPY})
    if(QNX)
        set(debug_info_suffix sym)
        set(debug_info_keep --keep-file-symbols)
        set(strip_args "--strip-debug -R.ident")
    else()
        set(debug_info_suffix debug)
        set(debug_info_keep --only-keep-debug)
        set(strip_args --strip-debug)
    endif()

    set(debug_info_target "$<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_BASE_NAME:${target}>.${debug_info_suffix}")
    install(FILES ${debug_info_target}
        DESTINATION ${installDestination}
        COMPONENT DebugInfo
        EXCLUDE_FROM_ALL)

    list(APPEND commands
        COMMAND ${copy_bin} ${debug_info_keep} $<TARGET_FILE:${target}>
                ${copy_bin_out_arg} ${debug_info_target}
        COMMAND ${strip_bin} ${strip_args} $<TARGET_FILE:${target}>)

    list(APPEND commands COMMAND ${CMAKE_OBJCOPY}
            --add-gnu-debuglink=${debug_info_target} $<TARGET_FILE:${target}>)

    if(NOT CMAKE_HOST_WIN32)
        list(APPEND commands
            COMMAND chmod -x ${debug_info_target}
            )
    endif()
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        ${commands})
endfunction()


function(cobot_tp_internal_install_pdb_files target install_dir_path)
    if(MSVC)
        get_target_property(target_type ${target} TYPE)

        if(target_type STREQUAL "SHARED_LIBRARY"
                OR target_type STREQUAL "EXECUTABLE"
                OR target_type STREQUAL "MODULE_LIBRARY")
            install(FILES "$<TARGET_PDB_FILE:${target}>"
                    DESTINATION "${install_dir_path}"
                    OPTIONAL
                    COMPONENT DebugInfo
                    EXCLUDE_FROM_ALL
            )

        elseif(target_type STREQUAL "STATIC_LIBRARY")
            get_target_property(lib_dir "${target}" ARCHIVE_OUTPUT_DIRECTORY)
            if(NOT lib_dir)
                message(FATAL_ERROR
                        "Can't install pdb file for static library ${target}. "
                        "The ARCHIVE_OUTPUT_DIRECTORY path is not known.")
            endif()
            set(pdb_name "${INSTALL_CMAKE_NAMESPACE}${target}$<$<CONFIG:Debug>:d>.pdb")
            set(compile_time_pdb_file_path "${lib_dir}/${pdb_name}")

            install(FILES "${compile_time_pdb_file_path}"
                    DESTINATION "${install_dir_path}"
                    OPTIONAL
                    COMPONENT DebugInfo
                    EXCLUDE_FROM_ALL
            )
        endif()
    endif()
endfunction()
