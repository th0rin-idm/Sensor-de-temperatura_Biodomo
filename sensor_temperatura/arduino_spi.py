import matplotlib.pyplot as plt
from datetime import datetime
from matplotlib.animation import FuncAnimation
import serial

plt.style.use('ggplot')
x_data = []
y_data = []

figure, ax = plt.subplots()
line, = ax.plot_date(x_data, y_data, '-')

#ard = serial.Serial('/dev/ttyACM0', 9600)
ard = serial.Serial('COM6', 9600)


def grafico(frame):
    datos = ard.readline()
    temp = datos.decode('utf-8')
    print(temp)
    
    x_data.append(datetime.now())
    y_data.append(float(temp))  # Convierte el valor a un número flotante
    if len(y_data) > 60:
        del y_data[0]
        del x_data[0]
    
    line.set_data(x_data, y_data)
    ax.relim()
    ax.autoscale_view()
    return line,

animacion = FuncAnimation(figure, grafico, interval=1000)
plt.show()
