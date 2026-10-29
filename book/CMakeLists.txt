# Finde gnuplot
find_program(GNUPLOT_EXECUTABLE gnuplot)
if(NOT GNUPLOT_EXECUTABLE)
    message(WARNING "Gnuplot wurde nicht gefunden. Die Grafiken werden nicht generiert.")
else()
    # Sammle alle .gp-Dateien im aktuellen Verzeichnis und Unterverzeichnissen
    file(GLOB_RECURSE GNUPLOT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.gp")
    
    # Ein Target, das alle Grafiken generiert
    add_custom_target(plots ALL
        COMMENT "Generiere alle Gnuplot-Grafiken..."
    )

    foreach(GP_FILE ${GNUPLOT_FILES})
        # Ermittle das Verzeichnis der Datei (z.B. "physik")
        get_filename_component(GP_DIR ${GP_FILE} DIRECTORY)
        # Ermittle den Dateinamen ohne Endung (z.B. "luftwiderstand")
        get_filename_component(GP_NAME ${GP_FILE} NAME_WE)
        # Die Zieldatei (das PDF, das generiert werden soll)
        set(OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${GP_DIR}/${GP_NAME}.tex")

        # Ein Custom Command, das die Datei generiert
        add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${GNUPLOT_EXECUTABLE} ${GP_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${GP_FILE}
            COMMENT "Gnuplot: ${GP_FILE} -> ${GP_NAME}.tex"
            VERBATIM
        )

        # Füge das Kommando zum Target hinzu
        add_custom_target(plot_${GP_NAME} DEPENDS ${OUTPUT_FILE})
        add_dependencies(plots plot_${GP_NAME})
    endforeach()
endif()