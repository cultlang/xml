
load("//build_tools:macros.bzl", "header_generator", "dll_generator", "entrypoint_generator")

header_generator(  
    deps = [
    "//util", 
    "//types:headers", 
    "//lisp:headers",
    "@pugixml//:pugixml"
    ]
)

dll_generator(
    packages = [
    "types",
    "lisp",
    ],
    deps = [
    "@pugixml//:pugixml"
    ],
)
