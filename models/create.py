#!/usr/bin/env python

# http://blenderscripting.blogspot.com/2011/05/blender-25-python-finding-normal-vector.html

try:
    import bpy
except:
    print("Created for use from within blender's python console.")

import os
import struct

class exporter:
    def __init__(self, filename):
        self.output = os.path.dirname(os.path.realpath(__file__)) + "/%s.bin" % filename

    def pack_face(self, face):
        l = len(face)
        ret = b'' + l.to_bytes(1, 'little')
        for co in face:
            ret += struct.pack("fff", co[0], co[1], co[2])
        return ret

    def targets(self):
        return bpy.context.selected_objects

    def faces(self, targets):
        o = f = 0
        ngons = {3: 0, 4: 0}
        for obj in targets:
            o += 1
            for face in obj.data.faces:
                f += 1
                coords = []
                ngons[len(face.vertices)] += 1
                for vertex in face.vertices:
                    coords.append(obj.data.vertices[vertex].co)
                yield coords

        print("%i objects, %i faces exported." % (o, f))
        print("ngon count: %s." % repr(ngons))

    def main(self):
        f = open(self.output, "wb")
        for face in self.faces(self.targets()):
            f.write(self.pack_face(face))
        print("done.")
