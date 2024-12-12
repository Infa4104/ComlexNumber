import matplotlib.pyplot as plt
import numpy as np
from scipy.interpolate import make_interp_spline

x,y  = [],[]

with open("file.txt","r") as f:
    for i,line in enumerate(f.readlines()):
        if i == 2000:
            break
        x.append(i)
        y.append(int(line)**(1/2))

for i,el in enumerate(y):
    y[i] = el/max(y)
# return 0;

idx = range(len(x))
xnew = np.linspace(min(idx), max(idx), 300)

spl = make_interp_spline(idx, y, k=3)
smooth = spl(xnew)

# plt.plot(x,y)
plt.grid(linestyle='--') 
# plt.show()
plt.plot(xnew, smooth)
plt.xticks(idx, x)
plt.show()