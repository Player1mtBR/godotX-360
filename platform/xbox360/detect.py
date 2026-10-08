import os


def is_active():
    return True


def get_name():
    return "Xbox 360"


def can_build():
    return os.path.isfile("/usr/local/xenon/bin/xenon-gcc")


def get_opts():
    from SCons.Variables import BoolVariable

    return [
        BoolVariable(
            "debug_symbols",
            "Add debugging symbols to release/release_debug builds",
            True,
        ),
    ]


def get_flags():
    return []


def configure(env):
    devkit = os.environ.get("DEVKITXENON", "/usr/local/xenon")

    env["CC"] = os.path.join(devkit, "bin", "xenon-gcc")
    env["CXX"] = os.path.join(devkit, "bin", "xenon-g++")
    env["LINK"] = os.path.join(devkit, "bin", "xenon-g++")
    env["AR"] = os.path.join(devkit, "bin", "xenon-ar")
    env["RANLIB"] = os.path.join(devkit, "bin", "xenon-ranlib")
    env["OBJCOPY"] = os.path.join(devkit, "bin", "xenon-objcopy")

    env.Append(
        CPPDEFINES=[
            "XENON",
            "XBOX360_ENABLED",
        ]
    )

    env.Append(
        CCFLAGS=[
            "-m32",
            "-maltivec",
            "-fno-pic",
            "-mpowerpc64",
            "-mhard-float",
        ]
    )

    env.Prepend(
        CPPPATH=[
            "#platform/xbox360",
        ]
    )

    env.Append(
        CPPPATH=[
            os.path.join(devkit, "usr", "include"),
        ]
    )

    env.Append(
        LIBPATH=[
            os.path.join(devkit, "usr", "lib"),
            os.path.join(devkit, "xenon", "lib", "32"),
        ]
    )

    env.Append(
        LINKFLAGS=[
            "-m32",
            "-maltivec",
            "-fno-pic",
            "-mpowerpc64",
            "-mhard-float",

            # Xenon application linker configuration.
            "-n",
            "-T" + os.path.join(os.getcwd(), "platform", "xbox360", "app.lds"),

            # Force Xenon startup/runtime objects out of libxenon.a.
            "-u", "read",
            "-u", "_start",
            "-u", "exc_base",
        ]
    )

    # libxenon is the Xenon runtime/platform library.
    env.Append(
        LIBS=[
            "xenon",
            "m",
        ]
    )

    env["bits"] = "32"
    env["arch"] = "ppc"

    print("Configuring for Xbox 360 / Xenon")
    print("  DEVKITXENON: " + devkit)
    print("  Compiler: " + env["CXX"])

    print("  CC:   " + str(env["CC"]))
    print("  CXX:  " + str(env["CXX"]))
    print("  LINK: " + str(env["LINK"]))
    print("  AR:   " + str(env["AR"]))
    print("  bits: " + str(env["bits"]))
    print("  arch: " + str(env["arch"]))
