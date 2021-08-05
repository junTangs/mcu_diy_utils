import KalmanFilter

from PIDControler import PID
import numpy as np
import matplotlib.pyplot as plt




filter = KalmanFilter.KalmanFilter(7.5,0.4)
x1 = []
x2 = []
x3 = []
for i in range(1000):
    x = 5*np.math.sin(i*0.01)+(np.random.rand()-0.5)
    x1.append(x)
    x2.append(filter.calculate(x))
    x3.append(5*np.math.sin(i*0.01))
    
x = np.arange(1000)
plt.plot(x,np.array(x1))
plt.plot(x,np.array(x2))
plt.plot(x,np.array(x3))


plt.show()

# pid  = PID(0.8,0.0018,0.0,0)
# print(pid.kp)

# class system:
#     def __init__(self) -> None:
#         self.integral = 0
#         self.last = 0
    
#     def cal(self,var):
#         self.integral += 0.1*var+0.5 + 0.1*(var - self.last) +  0.5*self.last
#         self.last = var
#         return self.integral
        

# sys = system()

# feedback = 0
# var = 0

# x1 = []
# x2 = []

# for i in range(1000):
    
#     if i < 100:
#         pid.targetVal = 0
#     else:
#         pid.targetVal = 100
#         var += pid.calculate(feedback)
        
#         feedback = sys.cal(var) 
    
#     x1.append(feedback)
#     x2.append(pid.targetVal)
    
# x = np.arange(1000)
# plt.plot(x,np.array(x1))
# plt.plot(x,np.array(x2))

# plt.show()
