import pyaml


def pprint(data):
    pyaml.p(data, force_embed=False, vspacing=dict(split_lines=10))
