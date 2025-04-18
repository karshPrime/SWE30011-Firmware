idf_component_register(
    SRCS
        "main.cpp"
        "Ground.cpp"
        "Actions.cpp"
        "Messenger.cpp"
        "ECG.cpp"
        "Motion.cpp"

    INCLUDE_DIRS
        "include"

    REQUIRES
        "arduino"
        "Adafruit_NeoPixel"
)
