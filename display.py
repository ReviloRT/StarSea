import matplotlib.pyplot as plt
import numpy

fig = plt.figure()

dim = 0;

def parseVect(vect):
    if dim == 2:
        return parseVect2(vect)
    if dim == 3:
        return parseVect3(vect)

def parseVect2(vect):
    return [float(vect[1:vect.find("y")]),float(vect[vect.find("y")+1:])]

def parseVect3(vect):
    return [float(vect[1:vect.find("y")]),float(vect[vect.find("y")+1:vect.find("z")]),float(vect[vect.find("z")+1:])]

def readTo(file,endChar) :
    str = ""
    while True:
        c = file.read(1)
        if c == endChar:
            break
        str += c
    return str

with open("stars.txt", "r") as file:
    dim = int(file.read(1))

    while True:
        if file.read(1) == '':
            break;

        file.read(1)
        time = float(readTo(file,"O"))
        print(time)

        array = numpy.zeros([2,dim*2+1])

        file.read(1)
        array[0,0] = float(readTo(file,"p"))
        array[0,1:dim+1] = parseVect(readTo(file,"v"))
        array[0,dim+1:2*dim+1] = parseVect(readTo(file,"O"))
        file.read(1)
        array[1,0] = float(readTo(file,"p"))
        array[1,1:dim+1] = parseVect(readTo(file,"v"))
        array[1,dim+1:2*dim+1] = parseVect(readTo(file,"\n"))

        fig.clear()
        if dim == 2:
            ax = plt.axes()
            ax.set(xlim=[-1,1],ylim=[-1,1])
            ax.scatter(array[:,1],array[:,2])
        else:
            ax = plt.axes(projection="3d")
            ax.set(xlim=[-1,1],ylim=[-1,1],zlim=[-1,1])
            ax.scatter3D(array[:,1],array[:,2],array[:,3])

        plt.pause(0.00001)


# plt.show()
