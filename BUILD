cc_binary(
    name="gootik",
    srcs = glob([
        "src/**/*.h",
        "src/**/*.cpp",
    ]),
    deps = [
        "@sdl2",
    ],
    copts = [
        "-stdlib=libc++",
        "-Iexternal/sdl2/Headers"
    ],
    linkopts = [
        "-F/Library/Frameworks",
        "-framework SDL2",
        # "-framework SDL2_image",
        "-ldl",
        "-lm"
    ]
)
