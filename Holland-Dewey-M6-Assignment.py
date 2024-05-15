# Import the required packages
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn import metrics
import csv
import os
os.environ['OMP_NUM_THREADS'] = '1'

# Load the data from the input file and convert it to a numpy array
input_file = 'sales.csv'
file_reader = csv.reader(open(input_file, 'r'), delimiter=',')
X = []
for count, row in enumerate(file_reader):
    if not count:
        names = row[1:]
        continue
    X.append([float(x) for x in row[1:]])
X = np.array(X)

# Define the number of clusters, create the KMeans object (kmeans) using the initialization
# parameters, and train the kmeans model with the input data.
num_samples = X.shape[0]
num_clusters = 9
num_clusters = min(num_samples, 9)

# Create KMeans object
kmeans = KMeans(init='k-means++', n_clusters=num_clusters, n_init=10)

# Train the KMeans clustering model
kmeans.fit(X)

# Extract and print the centers of the clusters.
cluster_centers = kmeans.cluster_centers_
print("Cluster Centers:")
print(cluster_centers)

# Plot the centers of clusters
plt.scatter(cluster_centers[:, 0], cluster_centers[:, 1],
            marker='o', s=210, linewidths=4, color='black',
            zorder=12, facecolors='black')

# Define the range of values for the x and y axes
x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1

# Plot the boundaries of the clusters
plt.title('Boundaries of clusters')
plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)
plt.xticks(())
plt.yticks(())
plt.show()

# Create two subsets from data and centers of only second and third attributes.
X_2d = X[:, 1:3]
cluster_centers_2d = cluster_centers[:, 1:3]

# Define the step size for the meshgrid it kept giving me a memory dump had to make it a very small number
step_size = 0.01

# Define the grid of points using the sub-dataset X_2d.
x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
x_vals, y_vals = np.meshgrid(np.arange(x_min, x_max, step_size),
                            np.arange(y_min, y_max, step_size))

# Predict the outputs for all the points on the grid using the trained kmeans model.
output = kmeans.predict(np.c_[x_vals.ravel(), y_vals.ravel()])

# Plot all output values and color each region.
output = output.reshape(x_vals.shape)
plt.figure()
plt.clf()
plt.imshow(output, interpolation='nearest', extent=(x_vals.min(), x_vals.max(),
                                                   y_vals.min(), y_vals.max()), cmap=plt.cm.Paired, aspect='auto', origin='lower')

# Overlay input data points on top of these colored regions.
plt.scatter(X[:, 0], X[:, 1], marker='o', facecolors='none',
            edgecolors='black', s=80)

# Plot the centers of the clusters obtained using the K-Means algorithm.
cluster_centers = k
