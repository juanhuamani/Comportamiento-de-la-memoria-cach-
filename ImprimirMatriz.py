import matplotlib.pyplot as plt

def read_results(file_path):
    sizes = []
    times = []
    with open(file_path, 'r') as file:
        for line in file:
            size, time = map(int, line.split())
            sizes.append(size)
            times.append(time)
    return sizes, times

def plot_results(sizes1, times1, sizes2, times2):
    plt.figure(figsize=(10, 6))
    plt.plot(sizes1, times1, label='Multiplicación Clásica', marker='o', color='blue')
    plt.plot(sizes2, times2, label='Multiplicación por Bloques', marker='o', color='red')
    plt.xlabel('Tamaño de la Matriz')
    plt.ylabel('Tiempo de Ejecución (ms)')
    plt.title('Comparación de Tiempos de Ejecución')
    plt.legend()
    plt.grid(True)
    plt.savefig('comparacion_tiempos.png')
    plt.show()

sizes_clasica, times_clasica = read_results('resultados_multiplicacion_clasica.txt')
sizes_bloques, times_bloques = read_results('resultados_multiplicacion_bloques.txt')
sizes_bloques, times_bloques = zip(*sorted(zip(sizes_bloques, times_bloques)))
sizes_clasica, times_clasica = zip(*sorted(zip(sizes_clasica, times_clasica)))

plot_results(sizes_clasica, times_clasica, sizes_bloques, times_bloques)
