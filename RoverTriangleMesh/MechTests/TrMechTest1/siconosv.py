#! /usr/bin/env python3
# Blender scripts

#needs blender. run it from the command line: blender --python pyBlend.py
#to debug without blender: blender --background --python pyBlend.py
#framerate given to the function should correspond to the timestep of the simulation

#needs numpy from python3 to be integrated into python by copying python module into module dir of .blender.

import bpy 
import shlex
import mathutils
import sys
import numpy
import time
import math
import random

bl_info = {  

    "name": "Siconos Visualization",  
    "author": "Jan Michalczyk",  
    "version": (1, 0),  
    "blender": (2, 6, 3),  
    "description": "Visualizes scenes from Siconos simulations",  
    "warning": "May contain bugs!",  
    "wiki_url": "",  
    "tracker_url": "",  
    "category": "Animation"

}

#main simulation class

#1)in the future for visualizing contact forces I'll make a switch in the inject keyframes function 
#2)ways to handle compound shapes in blender
#3)ways to handle mesh shapes in blender

class Simulation:

    def __init__(self, shape_filename='ref.txt', input_filename='input.dat', bind_filename='bindings.dat', dpos_filename='dpos.dat', spos_filename='spos.dat'):

        self.shape_filename = shape_filename

        self.input_filename = input_filename

        self.bind_filename = bind_filename

        self.dpos_filename = dpos_filename

        self.spos_filename = spos_filename

        #symbols recognizable by the parser

        self.symbols = ['Cone', 'Sphere', 'Box', 'Plane', 'Cylinder', 'Pyramid', 'Capsule']

        #dictionary for holding number of instances of each primitive

        self.instance_counters = dict()

        #dictionary holding moving objects on the scene - 'name_of_the_object':array_with_animation_data

        self.movables = dict()

        #dictionary holding the bindings from the bindings.dat file

        self.bindings = dict()

    def strToVect(self, st):

        tmp = st.split(' ')

        vec = []

        for num in tmp:

            num = float(num)

            vec.append(num)

        return vec

    def applyTransform(self, position, quaternion):

        ob = bpy.context.object

        ob.rotation_mode = 'QUATERNION'

        ob.rotation_quaternion = quaternion

        ob.location = position

        return ob

    def quatToEul(self, quaternion):

        q = mathutils.Quaternion(quaternion)
        e = q.to_euler()

        eul = [e.x, e.y, e.z]

        return numpy.array(eul)

    def makeMaterial(self, name, diffuse, alpha):

        mat = bpy.data.materials.new(name)
        mat.diffuse_color = diffuse
        mat.diffuse_shader = 'LAMBERT'
        mat.diffuse_intensity = 1.0
        mat.specular_intensity = 0.5
        mat.alpha = alpha
        mat.ambient = 1

        return mat

    def setMaterial(self, ob, mat):

        me = ob.data
        me.materials.append(mat)

    def assignMaterials(self, di):

        #di is a dictionary with id:rgb pairs

        mat = {}

        for i in di.keys():

            #making materials

            tmp = self.makeMaterial('mat' + str(i), di[i], (1,1,0), 0)

            mat[i] = tmp

        for ob in bpy.data.objects:

            l = ob.name.split("_")

            #if the object's name is of the form "object_num_num" then the material's assignment will execute

            if len(l) > 1:

                self.setMaterial(ob, mat[int(l[1])])

            else:

                continue

        return

    def createForceArrow(self, x, y, z, n, lbd = 0):

        """Creates an arrow from a given point along a given vector
        x,y,z is point to go from, n is a noral vector, and lbd is a scaling factor"""

        v = mathutils.Vector((x,y,z))

        up = mathutils.Vector((n[0],n[1],n[2]))

        rotation_quat = up.to_track_quat('Z', 'Y')

        my_Cylinder = bpy.ops.mesh.primitive_cylinder_add(vertices=16, radius=0.01, depth=lbd)
        ob1 = bpy.context.object
        ob1.name = 'my_Cylinder'

        bpy.ops.transform.translate(value=(0,0,(lbd/2+v.length)))

        my_Cone = bpy.ops.mesh.primitive_cone_add(vertices=40, radius1=0.1, radius2=0, depth=0.5, location=(0, 0, 0), rotation=(0, 0, 0))
        ob2 = bpy.context.object
        ob2.name = 'my_Cone'

        bpy.ops.transform.translate(value=(0,0,(lbd+v.length)))

        ob1.select = True
        ob2.select = True

        bpy.ops.object.join()

        #change location of tooltip to the bottom of the arrow

        newLoc = mathutils.Vector((0, 0, v.length))

        bpy.context.scene.cursor_location = newLoc

        bpy.ops.object.origin_set(type='ORIGIN_CURSOR')

        ob = bpy.context.object

        myName = 'Arrow'

        col = mathutils.Color((random.random(), random.random(), random.random()))

        ob.name = myName 
        ob.show_name = True
        me = ob.data

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        ob.rotation_mode = 'QUATERNION'

        ob.rotation_quaternion = rotation_quat

        ob.location = v

        return ob

    def createContactCone(self, x, y, z, mu):

        """Creates an inversed cone with the top placed at a given point, mu is a
        friction coeff"""

        #create an inversed cone at the specified point

        pos = mathutils.Vector((x,y,z))

        eul = mathutils.Euler((0.0, math.radians(180.0), 0.0), 'XYZ')

        myName = 'Cone'

        my_Cone = bpy.ops.mesh.primitive_cone_add(vertices=40, radius1=mu, radius2=0, depth=1, location=pos, rotation=eul)

        bpy.ops.transform.translate(value=(0,0,0.5))

        ob = bpy.context.object

        #shift the tooltip to the bottom of the cone

        bpy.context.scene.cursor_location = pos

        bpy.ops.object.origin_set(type='ORIGIN_CURSOR')

        #give a random color to the cone

        col = mathutils.Color((random.random(), random.random(), random.random()))

        ob.name = myName 
        ob.show_name = True
        me = ob.data

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        me.name = myName + '_' + 'Mesh'

        return ob

    def makePyramid(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:3]))

        myName = 'Pyramid' + '_' + str(li[3])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[3]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_Pyramid = bpy.ops.mesh.primitive_cone_add(vertices=4, radius1=params[0], radius2=0, depth=params[1], location=self.strToVect(' '.join(li[6:9]), rotation=self.quatToEul(self.strToVect(' '.join(li[9:13])))))

        ob = bpy.context.object

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeCone(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:3]))

        myName = 'Cone' + '_' + str(li[3])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[3]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_Cone = bpy.ops.mesh.primitive_cone_add(vertices=40, radius1=params[0], radius2=0, depth=params[1], location=self.strToVect(' '.join(li[6:9]), rotation=self.quatToEul(self.strToVect(' '.join(li[9:13])))))

        ob = bpy.context.object

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeBox(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:4]))

        #divide by two to scale corectly

        params = [i/2 for i in params]

        myName = 'Box' + '_' + str(li[4])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[4]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_Box = bpy.ops.mesh.primitive_cube_add(location=self.strToVect(' '.join(li[7:10])), rotation=self.quatToEul(self.strToVect(' '.join(li[10:14]))))

        ob = bpy.context.object
        ob.scale=(params)

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeSphere(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1]))

        myName = 'Sphere' + '_' + str(li[2])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[2]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_Sphere = bpy.ops.mesh.primitive_uv_sphere_add(size=params[0], location=self.strToVect(' '.join(li[5:8])))
        ob = bpy.context.object

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeCylinder(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:3]))

        myName = 'Cylinder' + '_' + str(li[3])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[3]) > 0:
            self.movables[myName] = numpy.empty(0) 

        rot = self.quatToEul(self.strToVect(' '.join(li[9:13])))    

        #we rotate the cylinder to make it along the y-axis as in bullet

        eul = mathutils.Euler(rot)

        eul.rotate_axis('Y', math.radians(90))

        my_Cylinder = bpy.ops.mesh.primitive_cylinder_add(radius=params[0], depth=params[1], location=self.strToVect(' '.join(li[6:9])), rotation=eul)

        ob = bpy.context.object

        #below line to put the applied roatation into effect 

        bpy.ops.object.transform_apply(rotation = True)

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeCapsule(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:3]))

        myFinalName = 'Capsule' + '_' + str(li[3])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[3]) > 0:
            self.movables[myFinalName] = numpy.empty(0) 

        rot = self.quatToEul(self.strToVect(' '.join(li[9:13])))    

        loc = self.strToVect(' '.join(li[6:9]))

        rad = params[0]
        height = params[1]

        #we create a capsule shape from a cylinder and two spheres

        my_Sphere1 = bpy.ops.mesh.primitive_uv_sphere_add(size=rad, location=(0,0,height/2), rotation=(0,0,0))
        ob1 = bpy.context.object
        ob1.name = 'my_Sphere1'

        my_Sphere2 = bpy.ops.mesh.primitive_uv_sphere_add(size=rad, location=(0,0,-height/2), rotation=(0,0,0))
        ob2 = bpy.context.object
        ob2.name = 'my_Sphere2'

        my_Cylinder = bpy.ops.mesh.primitive_cylinder_add(radius=rad, depth=height, location=(0,0,0), rotation=(0,0,0))
        ob3 = bpy.context.object
        ob3.name = 'my_Cylinder'

        ob1.select = True
        ob2.select = True
        ob3.select = True

        bpy.ops.object.join()

        ob = bpy.context.object

        #we rotate the capsule to make it along the y-axis as in bullet

        eul = mathutils.Euler(rot)

        eul.rotate_axis('Y', math.radians(90))

        ob.rotation_euler = eul

        #below line to put the applied roatation into effect 

        bpy.ops.object.transform_apply(rotation = True)

        ob.name = myFinalName 
        ob.show_name = True
        me = ob.data
        me.name = myFinalName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makePlane(self, li):

        #object geometric parameters

        params = self.strToVect(' '.join(li[1:4]))

        #divide by two to scale corectly

        params = [i/2 for i in params]

        myName = 'Plane' + '_' + str(li[4])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[4]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_Plane = bpy.ops.mesh.primitive_plane_add(location=self.strToVect(' '.join(li[7:10])), rotation=self.quatToEul(self.strToVect(' '.join(li[10:14]))))

        ob = bpy.context.object
        ob.scale=(params)

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def makeStlMesh(self, li):

        """Function to read an .stl mesh from the file and instantiate it on the scene"""

        myName = 'My_Mesh' + '_' + str(li[1])

        #if object is dynamic create an entry in the movables dictionary

        if int(li[1]) > 0:
            self.movables[myName] = numpy.empty(0) 

        my_mesh = bpy.ops.import_mesh.stl(filepath=li[0])

        ob = bpy.context.selected_objects[0]

        ob.location = self.strToVect(' '.join(li[4:7]))

        ob.rotation_euler = self.quatToEul(self.strToVect(' '.join(li[7:11])))

        ob.name = myName 
        ob.show_name = True
        me = ob.data
        me.name = myName + '_' + 'Mesh'

        #assign a random color to the primitive

        col = mathutils.Color((random.random(), random.random(), random.random()))

        mat = self.makeMaterial('random color' + str(random.random()), col, 1)

        self.setMaterial(ob, mat)

        return ob

    def prepareInput(self):

        """Prepares input to drawScene function (reads from ref.txt and input.dat).
        Returns a list of strings read by the drawScene() function.
        This function also fills the dictionary from the bindings.dat file"""

        # get the bindings of the objects

        with open(self.bind_filename, 'r') as bind_file:

            bind_lines = bind_file.readlines()

            for bind_line in bind_lines:

                lex = shlex.split(bind_line)

                self.bindings[int(lex[0])] = [int(lex[1])]

        # dictionary with pairs : position in the file (line number) - primitive specification

        shapes = dict() 

        # function's output - a list with strings which are inputs to the drawScene() function

        drawScene_input = list()

        with open(self.input_filename, 'r') as finput, open(self.shape_filename, 'r') as fshapes:

            shape_lines = fshapes.readlines()

            for idx, shape_line in enumerate(shape_lines):

                shapes[idx] = shape_line.replace("\n", "")

                self.instance_counters[shapes[idx].split()[0]] = 0

            input_lines = finput.readlines()

            for idx, input_line in enumerate(input_lines):

                lex = shlex.split(input_line)

                if int(lex[1]) < 0:

                    newLine = shapes[int(lex[0])] + ' ' + str(lex[1]) + ' ' + ' '.join(lex[1:])

                else:    

                    newLine = shapes[int(lex[0])] + ' ' + str(lex[1]) + ' ' + ' '.join(lex[1:])

                drawScene_input.append(newLine)

        return drawScene_input

    def drawScene(self):

        """Visualizes the initial scene state - places objects from the list returned by prepareInput()
        in their initial state. Returns a scene with objects placed at their initial positions and
        with their attributes"""

        scn = bpy.context.scene

        bpy.ops.object.select_by_type(type='MESH')

        bpy.ops.object.delete()

        lines = self.prepareInput()

        spos = numpy.loadtxt(self.spos_filename)

        #slicing of spos to get the id's vector (handling the 1D case os spos)

        if spos.ndim == 1:

            spos_id_slice = numpy.array([spos[1]])

        else:

            spos_id_slice = spos[:, 1]

        for line in lines:

            lex = shlex.split(line)

            symbol = lex[0]

            if symbol in self.symbols:

                #instantiation of objects

                if symbol == 'Box':

                    self.instance_counters[symbol] += 1

                    self.makeBox(lex)

                    if numpy.where(spos_id_slice == float(lex[5]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[5]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[5]))][0, 5:])

                elif symbol == 'Sphere':

                    self.instance_counters[symbol] += 1

                    self.makeSphere(lex)

                    if numpy.where(spos_id_slice == float(lex[3]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[3]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[3]))][0, 5:])

                elif symbol == 'Cylinder':

                    self.instance_counters[symbol] += 1

                    self.makeCylinder(lex)

                    if numpy.where(spos_id_slice == float(lex[4]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[4]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[4]))][0, 5:])

                elif symbol == 'Plane':

                    self.instance_counters[symbol] += 1

                    self.makePlane(lex)

                    if numpy.where(spos_id_slice == float(lex[5]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[5]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[5]))][0, 5:])

                elif symbol == 'Cone':

                    self.instance_counters[symbol] += 1

                    self.makeCone(lex)

                    if numpy.where(spos_id_slice == float(lex[4]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[4]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[4]))][0, 5:])

                elif symbol == 'Pyramid':

                    self.instance_counters[symbol] += 1

                    self.makePyramid(lex)

                    if numpy.where(spos_id_slice == float(lex[4]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[4]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[4]))][0, 5:])

                elif symbol == 'Capsule':

                    self.instance_counters[symbol] += 1

                    self.makeCapsule(lex)

                    if numpy.where(spos_id_slice == float(lex[4]))[0].size != 0:

                        if spos.ndim == 1:

                            self.applyTransform(spos[2:5], spos[5:])

                        else:

                            self.applyTransform(spos[numpy.where(spos_id_slice == float(lex[4]))][0, 2:5], spos[numpy.where(spos_id_slice == float(lex[4]))][0, 5:])

            elif '.stl' in symbol:

                self.instance_counters[symbol] += 1

                self.makeStlMesh(lex)

            bpy.ops.object.select_all()    

        return scn

    def injectKeyframes(self):

        """Injects keyframes in dynamic objects on the scene (reads from dpos.dat)"""

        #calculating the framerate (assuming 24 fps)
        #simTime and timeStep are in seconds

        #if my simulation lasts 10 sec then when using 24 fps i need
        #240 frames for the whole simulation.
        #if the simulation lasts 10 sec with a timestep of 0.005 s
        #then I have 2000 steps in the simulation.
        #to get my framerate i need to divide the total number of frames
        #per total number of timesteps.

        scn = bpy.context.scene

        #time evolution loading

        dpos = numpy.loadtxt(self.dpos_filename, ndmin=2)

        #calculating simTime and timeStep

        simTime = dpos[:, 0][dpos[:, 0].size - 1]

        timeStep = dpos[:, 0][numpy.where(dpos[:, 0] == 0)[0].size + 1] - dpos[:, 0][0]

        frameRate = (24*simTime)/(simTime/timeStep)

        #getting and preparing the scene

        frame_num = 0
        frame_total = simTime*24

        bpy.context.scene.frame_start = frame_num
        bpy.context.scene.frame_end = frame_total

        #picking lines corresponding to respective id's 

        #appending numpy arrays to the dictionary

        for key in self.movables.keys():

            idx = int(key.split("_")[1])

            self.movables[key] = dpos[numpy.where(dpos[:,1] == idx)]

        #Creation of actions for objects

        objects = self.movables.keys()

        for obj in bpy.data.objects:

            obj.rotation_mode = 'QUATERNION'

            if obj.name in objects:

                obj.animation_data_create()
                obj.animation_data.action = bpy.data.actions.new(name="MyAction")

                fcu_x = obj.animation_data.action.fcurves.new(data_path="location", index=0)
                fcu_y = obj.animation_data.action.fcurves.new(data_path="location", index=1)
                fcu_z = obj.animation_data.action.fcurves.new(data_path="location", index=2)

                fcu_rot0 = obj.animation_data.action.fcurves.new(data_path="rotation_quaternion", index=0)
                fcu_rot1 = obj.animation_data.action.fcurves.new(data_path="rotation_quaternion", index=1)
                fcu_rot2 = obj.animation_data.action.fcurves.new(data_path="rotation_quaternion", index=2)
                fcu_rot3 = obj.animation_data.action.fcurves.new(data_path="rotation_quaternion", index=3)

                fcu_x.keyframe_points.add(len(self.movables[obj.name]))
                fcu_y.keyframe_points.add(len(self.movables[obj.name]))
                fcu_z.keyframe_points.add(len(self.movables[obj.name]))

                fcu_rot0.keyframe_points.add(len(self.movables[obj.name]))
                fcu_rot1.keyframe_points.add(len(self.movables[obj.name]))
                fcu_rot2.keyframe_points.add(len(self.movables[obj.name]))
                fcu_rot3.keyframe_points.add(len(self.movables[obj.name]))

                for i in range(0, len(self.movables[obj.name])):

                    fcu_x.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][2]
                    fcu_y.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][3]
                    fcu_z.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][4]

                    fcu_rot0.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][5]
                    fcu_rot1.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][6]
                    fcu_rot2.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][7]
                    fcu_rot3.keyframe_points[i].co = i*frameRate, self.movables[obj.name][i][8]

        #turning back frames to the beginning             

        frame_num = 0    
        bpy.context.scene.frame_set(frame_num)

        #returning the scene         

        return scn         

    def runScene(self):

        bpy.ops.screen.animation_play()

if __name__ == "__main__":

    sim = Simulation()

    sim.drawScene()

    sim.injectKeyframes()
