import matplotlib.pyplot as plt

data = [1.958, 1.955, 1.081, 1.082]

deltas = [(data[i-1]-data[i]) * 1000 for i in range(1,len(data))]


print(deltas)
plt.plot(deltas)

plt.show()
