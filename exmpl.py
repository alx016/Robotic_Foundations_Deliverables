####################################################
#Control de un Robot con Retroalimentación de Estados
####################################################
#Importación de Librerias
import numpy as np
import math
from scipy.integrate import odeint
import matplotlib.pyplot as plt
####################################################
#Vector de Tiempo de Simulación
start = 0
stop = 20
step =1e-3
t = np.arange(start,stop,step)
####################################################
#Parametros del Robot
Bb = 0.01 #Fricción viscosa
lc = 0.5 #Distancia al centro de masa
l = 1 #Tamaño del brazo
m = 1 #Masa del brazo
g = 9.81 #Aceleración de la gravedad
Ib = (1/3)*m*pow(l,2)
Jm = 0.008
Bm = 0.04
k = 50
####################################################
#Ganancias del controlador
k = 50
k1 = 6.5
k2 = 0.01
k3 = 1.3
k4 = 0.5
####################################################
alfa1 = (Bb / Ib)
alfa2 = ((m*g*lc)/Ib)
alfa3 = Bm/Jm
alfa4 = k/Jm
####################################################
def f(x,t):
    d1 = np.exp(-3*t)
    d2 = 5*np.exp(-3*t)
    dx_dt = [0,0,0,0]
    #Referencia
    w = - k1*(x[0] - np.sin(t)) - k2*x[1] - k3*x[2] - k4*x[3]
    Tm = ( w - d2 + k*(x[2] - x[0]) + Bm*x[3])*Jm
    dx_dt[0] = x[1]
    dx_dt[1] = -alfa1*x[1] - alfa2*np.sin(x[0]) - k*(x[0] - x[2]) + d1
    dx_dt[2] = x[3]
    dx_dt[3] = -alfa3*x[3] - alfa4*(x[2] - x[0]) + d2 + Tm
    return dx_dt
####################################################
#Solución de las ecuaciones diferenciales
Solucion = odeint(f, y0 =[0,0,0,0],t=t)
print('Solución', Solucion)
#Graficas
#Posición Angular del Robot
plt.plot(t,Solucion[:,0], 'r', label='x1(t)')
plt.plot(t, np.sin(t))
plt.xlabel('Tiempo (seg)')
plt.ylabel('x1(t)')
plt.title('Angulo del Robot (rad)')
plt.grid()
plt.show()
