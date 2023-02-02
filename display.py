import matplotlib.pyplot as plt
import numpy

fig = plt.figure()

def readTo(file,endChar) :
    str = ""
    while True:
        c = file.read(1)
        if c == endChar:
            break
        str += c
    return str

with open("stars.txt", "r") as file:
    while file.read(1) != '': #S or '' (end line)

        #paceObjs:t(time)d(dim)n(count)m(mass1),(mass2),...,x(x1),(x2),...,y

        readTo(file,"t") #paceObjs:t
        time = float(readTo(file,"d")) #(time)d
        dim = int(readTo(file,"n")) #(dim)n
        count = int(readTo(file,"m")) #(count)m
        print(time)
        array = numpy.zeros([dim*2+1,count])
        # mass
        for i in range(count):
            array[0,i] = float(readTo(file,","))
        file.read(1) # x
        # posx
        for i in range(count):
            array[1,i] = float(readTo(file,","))
        file.read(1) # y
        # posy
        for i in range(count):
            array[2,i] = float(readTo(file,","))
        if dim == 3 :
            file.read(1) # z
        else:
            file.read(2) # vx
        # velx or posz
        for i in range(count):
            array[3,i] = float(readTo(file,","))
        file.read(2) # vy or vx
        #vely or velx
        for i in range(count):
            array[4,i] = float(readTo(file,","))

        if dim == 3 :
            file.read(2) # vy
            # vely
            for i in range(count):
                array[5,i] = float(readTo(file,","))
            file.read(2) # vz
            # velz
            for i in range(count):
                array[6,i] = float(readTo(file,","))
        file.read(1) # \n

        fig.clear()
        if dim == 2:
            ax = plt.axes()
            ax.set(xlim=[-1,1],ylim=[-1,1])
            ax.scatter(array[1,:],array[2,:])
        else:
            ax = plt.axes(projection="3d")
            ax.set(xlim=[-1,1],ylim=[-1,1],zlim=[-1,1])
            ax.scatter3D(array[1,:],array[2,:],array[3,:])

        plt.pause(0.00001)


# plt.show()
