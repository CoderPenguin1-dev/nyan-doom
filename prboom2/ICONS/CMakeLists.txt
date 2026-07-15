if(UNIX AND NOT APPLE)
    install(FILES penguino-doom.desktop DESTINATION share/applications)
    install(FILES penguino-doom.svg DESTINATION share/icons/hicolor/scalable/apps)
endif()
