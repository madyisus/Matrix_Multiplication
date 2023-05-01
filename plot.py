import matplotlib.pyplot as plt
import pandas as pd
import sys

# Lee los argumentos entregados (skip a -python-)
data = sys.argv[1:]

# Crea la figura que contiene el plot
fig = plt.figure('Resultados',figsize= (10,5),tight_layout=True)
ax1 = fig.add_subplot(1,1,1)

# Lee cada archivo csv, toma los datos y crea el plot
for file in data:
    df = pd.read_csv(file)
    label = file.split('_')[0]
    x = df['n'].values
    y = df['time[ms]'].values*1e-6
    ax1.plot(x, y, label=label, marker='s',ms=2)

# Ajustes visuales
plt.xlabel('n')
plt.ylabel('time[s]')

# plt.title('Tiempo de ejecución para multiplicación de matrices')
plt.legend(loc="best")
plt.show()
