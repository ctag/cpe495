# <pep8 compliant>
#vim :set ts=4 sw=4 sts=4 et smarttab :
import bpy

#from willscadblend import WillScadBlend
import os

#filename = os.path.join(os.path.dirname(bpy.data.filepath), "addon-move3.py")
filename = '/DATA/code/3dump/blender-scripts/willscadblend.py'
exec(compile(open(filename).read(), filename, 'exec'))



# see http://blenderartists.org/forum/showthread.php?250906-what-is-the-fastest-%28easiest-%29-way-to-create-a-shortcut-for-a-custom-script
# see http://michelanders.blogspot.com/p/creating-blender-26-python-add-on.html


# **********  PANEL

class ScadPanel(bpy.types.Panel):
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'TOOLS'

    bl_context = "objectmode"
    bl_label = "openSCAD"

    def draw(self, context):
        layout = self.layout
        row1 = layout.row()
        row1.label(text="Import From:")

        row2 = layout.row()
        row2.operator("mesh.scadtestscript", text="Sample")
        row3 = layout.row()
        row3.operator("mesh.scadtestfile", text="File")

        #col = layout.column(align=True)
        #col.label(text="Import:")
        #col.operator("scad.import.file", text="from file")

        #col = layout.column(align=True)
        #col.operator("scad.import.origin_set", text="Origin")


        #active_object = context.active_object
        #if active_object and active_object.type in {'MESH', 'CURVE', 'SURFACE'}:






# ******************  OPS

class YourOperator(bpy.types.Operator):
    '''tries to load a simple openSCAD script to test SCAD importer'''
    bl_idname = "mesh.scadtestscript"
    bl_label = "import openSCAD sample"
    # like "My Operator"
    #bl_props = [] # list of props used, see release/io/export_ply.py for example
    bl_options = {'REGISTER', 'UNDO', 'PRESET'}
    @classmethod
    def poll(self, context):
        # checks to ensure your operator has what it needs
        return True # or False if context is not correct, ie no selected objects
        # NOTE: safe to always return true since we are adding objects?
    def execute(self, context):
        # your main part of the script should come in execute
        return WillScadBlend.test_script()
        #return ('FINISHED', ) # or 'CANCELLED' or any of the others, depending on what you need.




# ************************** END

def register():
    bpy.utils.register_class(ScadPanel)
    bpy.utils.register_class(YourOperator)


def unregister():
    bpy.utils.unregister_class(ScadPanel)


if __name__ == "__main__":
    register()

