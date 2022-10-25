import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import MultipleLocator
import numpy as np


@np.vectorize
def func_29(x: float, y: float) -> float:
    if x <= 0 or y <= -1:
        return 0.

    if 0 < x <= 3:
        if -1 < y <= 0:
            return x * (y + 1) / 3
        if y > 0:
            return x / 3

    if x > 3:
        if -1 < y <= 0:
            return y + 1
        if y > 0:
            return 1.


fig, ax = plt.subplots(subplot_kw={'projection': '3d'})

xa, ya = np.arange(-1, 4, 0.01), np.arange(-2, 1, 0.01)
X, Y = np.meshgrid(xa, ya)
Z = func_29(X, Y)

surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, linewidth=0, antialiased=False)

ax.set_zlim(-0.01, 1.01)
ax.zaxis.set_major_locator(MultipleLocator(0.1))

fig.colorbar(surf, shrink=0.5, aspect=5)

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.title('Слайд 29')

plt.show()
