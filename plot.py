import matplotlib.pyplot as plt
import pandas as pd
import sys

data = sys.argv[1:]

fig = plt.figure('Resultados',figsize= (10,5),tight_layout=True)
ax1 = fig.add_subplot(1,1,1)

for file in data:
    df = pd.read_csv(file)
    label = file.split('_')[0]
    x = df['n'].values
    y = df['time[ms]'].values*1e-6
    ax1.plot(x, y, label=label, marker='s',ms=2)


plt.xlabel('n')
plt.ylabel('time[s]')

# plt.title('Tiempo de ejecución para multiplicación de matrices')
plt.legend(loc="best")
plt.show()
