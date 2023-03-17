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


with open("stars.txt", "r") as file:
    dim = int(file.read(1))

    while True:
        if file.read(1) == '':
            break;

        time = float(readTo(file,'c'))
        objCount = int(readTo(file,'m'))
        print(time, objCount)
        if time > 99 :
            array = numpy.zeros([7,objCount])
            for i in range(objCount):
                array[0,i] = float(readTo(file,'p'))
                array[1:4,i] = parseVect(readTo(file,'v'))
                array[4:7,i] = parseVect(readToAny(file,['m','\n']))

            fig.clear()
            if dim == 2:
                ax = plt.axes()
                ax.set(xlim=[-1,1],ylim=[-1,1])
                ax.scatter(array[1,:],array[2,:],s=array[0,:]*10)
            else:
                ax = plt.axes(projection="3d")
                ax.set(xlim=[-1,1],ylim=[-1,1],zlim=[-1,1])
                ax.scatter3D(array[1,:],array[2,:],array[3,:],s=array[0,:]*10)
            break
        else:
            readTo(file,'\n')

plt.show()
