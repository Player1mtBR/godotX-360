def can_build(env, platform):
    return platform != "xbox360"


def configure(env):
    pass


def get_doc_classes():
    return ["UPNP", "UPNPDevice"]


def get_doc_path():
    return "doc_classes"
