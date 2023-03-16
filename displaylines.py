import matplotlib.pyplot as plt
import numpy

fig = plt.figure()

dim = 0;

def parseVect(vect):
    return [float(vect[1:vect.find("y")]),float(vect[vect.find("y")+1:vect.find("z")]),float(vect[vect.find("z")+1:])]

def readTo(file,endChar) :
    str = ""
    while True:
        c = file.read(1)
        if c == endChar:
            return str
        str += c

def readToAny(file,endChars) :
    str = ""
    while True:
        c = file.read(1)
        for endC in endChars:
            if c == endC:
                return str
        str += c

tailLen = 50

array = numpy.zeros([tailLen,7,0]);
frames = 0
with open("stars.txt", "r") as file:
    dim = int(file.read(1))

    while True:
        if file.read(1) == '':
            break;

        time = float(readTo(file,'c'))
        objCount = int(readTo(file,'m'))
        print(time, objCount)
        if array.shape[2] == 0:
            array = numpy.zeros([tailLen,7,objCount])
            for i in range(objCount):
                array[:,0,i] = float(readTo(file,'p'))
                array[:,1:4,i] = parseVect(readTo(file,'v'))
                array[:,4:7,i] = parseVect(readToAny(file,['m','\n']))
        else:
            for i in range(objCount):
                array[0,0,i] = float(readTo(file,'p'))
                array[0,1:4,i] = parseVect(readTo(file,'v'))
                array[0,4:7,i] = parseVect(readToAny(file,['m','\n']))

        fig.clear()
        if dim == 2:
            ax = plt.axes()
            ax.set(xlim=[-1,1],ylim=[-1,1])
            ax.plot(array[:,1,:],array[:,2,:])
            ax.scatter(array[0,1,:],array[0,2,:])
        else:
            ax = plt.axes(projection="3d")
            ax.set(xlim=[-1,1],ylim=[-1,1],zlim=[-1,1])
            for i in range(objCount):
                ax.plot(array[:,1,i],array[:,2,i],array[:,3,i])
            ax.scatter3D(array[0,1,:],array[0,2,:],array[0,3,:])

        plt.pause(0.0001)
        array = numpy.roll(array,1,axis=0)
        frames += 1


# plt.show()
