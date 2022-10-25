import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import MultipleLocator
import numpy as np


@np.vectorize
def func_16(x: float, y: float) -> float:
    if x <= 1 or y <= -1:
        return 0.

    if 1 < x <= 2:
        if -1 < y <= 0:
            return 0.05
        if 0 < y <= 1:
            return 0.1
        if y > 1:
            return 0.2

    if x > 2:
        if -1 < y <= 0:
            return 0.2
        if 0 < y <= 1:
            return 0.55
        if y > 1:
            return 1


fig, ax = plt.subplots(subplot_kw={'projection': '3d'})

xa, ya = np.arange(-1, 3, 0.01), np.arange(-2, 2, 0.01)
X, Y = np.meshgrid(xa, ya)
Z = func_16(X, Y)

surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=False)

ax.set_zlim(-0.01, 1.01)
ax.zaxis.set_major_locator(MultipleLocator(0.1))

fig.colorbar(surf, shrink=0.5, aspect=5)

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.title('Слайд 16')

plt.show()
