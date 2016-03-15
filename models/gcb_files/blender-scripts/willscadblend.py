#!/bin/env python

class WillScadBlend:
	def add_to_scene(obj):
		return
		TheScene = Blender.Scene.GetCurrent()
		TheScene.link(obj)
		TheScene.update()
		Blender.Window.Redraw()
		return

	def read_file(fname):
		#f = open(fname, 'r')
		#return f.read();
		#TODO: for now just return "xxx"
		return "cube(size = 1, center = false);\ncube(size = [1,2,3], center = true);"

	def b_cube(size=[1,1,1], center=[0,0,0]):
		#NOTE: first issue, cubes in blender are proper cubes. need to scale to change size, aparently
		#      or at least only on the bpy interface
		obj = bpy.ops.mesh.primitive_cube_add(view_align=False, enter_editmode=False, location=center, rotation=(0, 0, 0), layers=(True, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False))
		return obj

	def parse(txt):
		#for now just return a cube
		#add_to_scene(obj)
		return WillScadBlend.b_cube()

	def open_file(file_name):
		txt = read_file(file_name)
		return parse(txt)

	# entry points for the UI
	def test_file():
		# lazy prototype stage... TODO: show file diaload somehow
		return WillScadBlend.open_file('~/import.scad')

	def test_script():
		return WillScadBlend.parse('cube()')
